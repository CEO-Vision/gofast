(function ($, Drupal, Gofast) {
  'use strict';

  $(document).ready(function () {
    var pathname = window.location.pathname;
    if (pathname === "/Welcome") {
      initConfigAnimation();
    }
    initTabs();
    initGlobalVar();

    // Step1 : change domain name
    $("#validateDomainNameAndNext").on("click", function (event) {
      validateDomain(event);
    });

    //Step2: configure SSL certificate
    getSSLChoice();
    $("#validateSSLCertificateAndnext").on("click", function (event) {
      validateSSL(event);
    });
    $("#lastSSLCertificate").on("click", function (event) {
      backSSL(event);
    });

    //Step3 : SMTP server
    initSMTP();
    $("#validateSMTPAndnext").on("click", function (event) {
      validateSMTP(event);
    });
    $("#lastSMTP").on("click", function (event) {
      backSMTP(event);
    });

    //Step4 : Create ADM
    $("#validateUserAdmAndnext").on("click", function (event) {
      validateAdm(event);
    });
    $("#lastUserAdmAndnext").on("click", function (event) {
      backAdm(event);
    });

    /******************************************/
    /************ Step5 : Final ***************/
    /******************************************/
    $("#finalSubmit").on("click", function (event) {
      validateConfig(event);
    });
    $("#backfinalSubmit").on("click", function (event) {
      backFinal(event);
    });


    bindTabClick();
    $('aside').hide();

    $('form input').on('keyup keypress', function (e) {
      var keyCode = e.keyCode || e.which;
      if (keyCode === 13) {
        e.preventDefault();
        return false;
      }
    });

  });


  // [name] is the name of the event "click", "mouseover", ..
  // same as you'd pass it to bind()
  // [fn] is the handler function
  $.fn.bindFirst = function (obj, name, fn) {
    // bind as you normally would
    // don't want to miss out on any jQuery magic
    $(obj).bind(name, fn);

    // Thanks to a comment by @Martin, adding support for
    // namespaced events too.
    var handlers = $._data(obj, 'events')[name.split('.')[0]];
    // take out the handler we just inserted from the end
    var handler = handlers.pop();
    // move it at the beginning
    handlers.splice(0, 0, handler);
  };

  /**
   *
   * @param {*} url
   * @param {*} options
   */
  function submitStep(url, options) {
    $.post(url, options, function (data) {
      var myData = JSON.parse(data);
      managerMessage(myData.type, myData.message, null, myData.options);
      if (myData.type !== "error") {
        switch (url) {
          case "/validateDomainName":
            var checker = Gofast.chekerDomainname;
            var loader = 'loaderDomainName';
            var hrefTrigger = 'sslCertificate';
            Gofast.submitdomainname = true;
            var hrefPrevious = "domainName";
            break;
          case "/validateSSLCertificate":
            var checker = Gofast.chekerSslcertificate;
            var loader = 'loaderSslCertificate';
            var hrefTrigger = 'smtp';
            Gofast.submitsslcertificate = true;
            var hrefPrevious = "sslCertificate";
            break;
          case "/validateSMTPServer":
            var checker = Gofast.chekerSmtp;
            var loader = 'loaderSmtp';
            var hrefTrigger = 'userAdm';
            Gofast.submitsmtp = true;
            var hrefPrevious = 'smtp';
            break;
          case "/validateADMUser":
            var checker = Gofast.chekerAdmuser;
            var loader = 'loaderUserAdm';
            var hrefTrigger = 'end';
            Gofast.submitadmuser = true;
            var hrefPrevious = 'userAdm';
            break;
          default:
            console.log("Error please contacting CEO-Vision");
            break;
        }
        if (checker === false) {
          checker = true;
          $('#' + loader).trigger("click");
        } else {
          $('#' + loader).trigger("click");
          $('#' + loader).trigger("click");
        }
        Gofast.is_event = true;
        $("[href=#" + hrefTrigger + "]").trigger("click");
        $("[href=#" + hrefPrevious + "] span div").removeClass('visibility-hidden');
        if (hrefTrigger == "end") {
          prepareSummary();
        }
      } else {
        $("[href=#" + hrefPrevious + "] span div").addClass('visibility-hidden');
      }
    });
  }


  /**
   * @function checkEmptyInputForm
   * @param {Array} elements
   * Check Input element give in parameter is empty and put the right color.
   * Give an array in paramater in the format {'JQuery identifier' : inputValue}
   */
  function checkEmptyInputForm(elements) {
    var toaster_options = initToastrOptions();
    var isEmpty = false;
    $.each(elements, function (indexInArray, element) {
      if (element == '') {
        setWarningFields(indexInArray);
        isEmpty = true;
      } else {
        setDefaultFields(indexInArray);
      }
    });
    if (isEmpty){
      Gofast.toast(Drupal.t('Please register all informations !', {}, { 'context': 'gofast' }), 'warning', null, toaster_options);
    }
    return isEmpty;
  }

  /**
 * @function checkInvalidCharacForm
 * @param {Array} elements
 * Check Input element give in parameter is empty and put the right color.
 * Give an array in paramater in the format {'JQuery identifier' : inputValue}
 */
  function checkInvalidCharacForm(elements) {
    var toaster_options = initToastrOptions();
    var specialChars = "<>@!#$%^&*()_+[]{}?:;|'\"\\,/~`=";
    var isInvalidField = false;
    var checkInvalid = function (string) {
      if(string !== ""){
        for (var i = 0; i < specialChars.length; i++) {
          if (string.indexOf(specialChars[i]) > -1) {
            return true
          }
        }
      }else{
        return false;
      }
      return false;
    }
    $.each(elements, function (indexInArray, element) {
      var isInvalid = checkInvalid(element);
      if (isInvalid) {
        setWarningFields(indexInArray);
        isInvalidField = true;
      } else {
        setDefaultFields(indexInArray);
        $('#' + indexInArray).focusin(function () {
          $(this).css('border-color', '#66afe9');
          $(this).css('box-shadow', 'inset 0 1px 1px rgba(0,0,0,.075),0 0 8px rgba(102,175,233,0.6)');
        });
        $('#' + indexInArray).focusout(function () {
          $(this).css('border-color', '#cccccc');
          $(this).css('box-shadow', 'none');
        });
      }
    });
    if(isInvalidField){
      Gofast.toast(Drupal.t('Please check the fields. The following characters are banned : ', {}, { 'context': 'gofast' }) + "<div class='banChar'> < > @ ! # $ % ^ & * ( ) _ + [ ] { } ? : ; | ' \ \" / ~` =</div>", 'error', null, toaster_options);
    }
    return isInvalidField;
  }



  /**
   * @function uploadFile
   * @param {string} idInputFile
   * @param {string} fr
   * Read and display the InputFile into an input
   */
  function uploadFile(idInputFile, fr) {
    var entree, fichier;
    var toaster_options = initToastrOptions();
    entree = document.getElementById(idInputFile);
    if (!entree.files[0]) {
      Gofast.toast(Drupal.t('Please select file before click !', {}, {
        'context': 'gofast'
      }), 'warning', null, toaster_options);
    } else {
      fichier = entree.files[0];
      fr.readAsText(fichier);
      return fr;
    }
  }
  /**
   * @function getFileExtension
   * @param {string} filename
   * @returns Extension of filename
   */
  function getFileExtension(filename) {
    return filename.split('.').pop();
  }

  /**
   *
   * @param {*} type
   * @param {*} message
   * @param {*} title
   * @param {*} options
   */
  function managerMessage(type, message, title, options) {
    Gofast.toast(Drupal.t(message, {}, { 'context': 'gofast_graphic_config' }), type, title, options);
  }

  /**
   * @function initToastrOptions
   * Initialize toastr options
   */
  function initToastrOptions(){
    var toaster_options = {
      tapToDismiss: true,
      toastClass: 'toast',
      containerId: 'toast-container',
      debug: false,
      showMethod: 'fadeIn', // fadeIn, slideDown, and show are built into jQuery
      showDuration: 500,
      showEasing: 'swing', // swing and linear are built into jQuery
      onShown: undefined,
      hideMethod: 'fadeOut',
      hideDuration: 1000,
      hideEasing: 'swing',
      onHidden: undefined,
      extendedTimeOut: 1000,
      iconClasses: {
        error: 'toast-error',
        info: 'toast-info',
        success: 'toast-success',
        warning: 'toast-warning'
      },
      iconClass: 'toast-info',
      positionClass: 'toast-top-right',
      timeOut: 8000, // Set timeOut and extendedTimeOut to 0 to make it sticky
      titleClass: 'toast-title',
      messageClass: 'toast-message',
      target: 'body',
      closeHtml: '<button type="button">&times;</button>',
      newestOnTop: true,
      preventDuplicates: true,
      progressBar: false
    }
    return toaster_options;
  }

  /**
   * @function initConfigAnimation()
   * Initialiaze the configuration animation
   */
  function initConfigAnimation(){
    $('body').wrapInner(
      '<div class="pt-wrapper"></div>');
    $('body').append('<div class="pt-conf-page"><div class="message_config">' + Drupal.t('Welcome to the') + '</div></hr></div>');
    $('.pt-conf-page').append('<img src="/sites/all/themes/bootstrap-gofast/Logo GoFAST Community Version.png" class="logo_welcome_config_page img-responsive">');
    $('.pt-conf-page').addClass('pt-page-meltedSlideOut');

    setTimeout(function () {
      $("#graphicconfig").removeClass('gofast_display_none');
    }, 2000);

    setTimeout(function () {
      $('body').append('<div class="pt-conf-page1"><div class="message_config"> ' + Drupal.t('Configuration of your GoFAST Community Plateform') + '</div></hr></div>');
      $('.pt-conf-page1').addClass('pt-page-meltedSlideinAndout');
    }, 4000);
  }

/**
 * @function initTabs()
 * Initialize all items and set default values before the configuration
 */
  function initTabs(){
    $("#finalSubmit").attr("disabled", "disabled");
    $("form#gofast-graphic-config-frame div div").removeClass("tabs-left");

    $("form#gofast-graphic-config-frame").append("<div id='loaderDomainName'>domainName</div>");
    $("#loaderDomainName").hide();
    $("form#gofast-graphic-config-frame").append("<div id='loaderSslCertificate'>SSLCertificate</div>");
    $("#loaderSslCertificate").hide();
    $("form#gofast-graphic-config-frame").append("<div id='loaderSmtp'>Smtp</div>");
    $("#loaderSmtp").hide();
    $("form#gofast-graphic-config-frame").append("<div id='loaderUserAdm'>UserAdm</div>");
    $("#loaderUserAdm").hide();

    $("[href=#domainName] span").append("<div class='circle-loader'><div class='checkmark draw'></div></div>");
    $("[href=#domainName] span div").addClass('visibility-hidden');
    $('#loaderDomainName').click(function () {
      $('[href=#domainName] span div').toggleClass('load-complete');
      $('[href=#domainName] span div.checkmark').toggle();
    });
    $("[href=#sslCertificate] span").append("<div class='circle-loader'><div class='checkmark draw'></div></div>");
    $("[href=#sslCertificate] span div").addClass('visibility-hidden');
    $('#loaderSslCertificate').click(function () {
      $('[href=#sslCertificate] span div').toggleClass('load-complete');
      $('[href=#sslCertificate] span div.checkmark').toggle();
    });
    $("button#edit-submit").hide();
    $("[href=#smtp] span").append("<div class='circle-loader'><div class='checkmark draw'></div></div>");
    $("[href=#smtp] span div").addClass('visibility-hidden');
    $('#loaderSmtp').click(function () {
      $('[href=#smtp] span div').toggleClass('load-complete');
      $('[href=#smtp] span div.checkmark').toggle();
    });
    $("[href=#userAdm] span").append("<div class='circle-loader'><div class='checkmark draw'></div></div>");
    $("[href=#userAdm] span div").addClass('visibility-hidden');
    $('#loaderUserAdm').click(function () {
      $('[href=#userAdm] span div').toggleClass('load-complete');
      $('[href=#userAdm] span div.checkmark').toggle();
    });
  }
/**
 * @function initGlobalVar
 * Dont need to comment ;)
 */
  function initGlobalVar(){
    Gofast.submitdomainname = false;
    Gofast.submitsslcertificate = false;
    Gofast.submitsmtp = false;
    Gofast.submitadmuser = false;
    Gofast.submitfinish = false;

    Gofast.chekerDomainname = false;
    Gofast.chekerSslcertificate = false;
    Gofast.chekerSmtp = false;
    Gofast.chekerAdmuser = false;
  }

  /**
   * @function setDefaultFields()
   * @param {string} fieldName
   * Set the css of the form input(fieldName) to default
   */
  function setDefaultFields(fieldName){
    $('#' + fieldName).css('border-color', '#cccccc');
    $('#' + fieldName).parent().find('label').css('color', '#333');
    $('#' + fieldName).css('box-shadow', 'none');
    $('#' + fieldName).focusin(function () {
      $(this).css('border-color', '#66afe9');
      $(this).css('box-shadow', 'inset 0 1px 1px rgba(0,0,0,.075),0 0 8px rgba(102,175,233,0.6)');
    });
    $('#' + fieldName).focusout(function () {
      $(this).css('border-color', '#cccccc');
      $(this).css('box-shadow', 'none');
    });
  }

  /**
  * @function setWarningFields()
  * @param {string} fieldName
  * Set the css of the form input(fieldName) to warning
  */
  function setWarningFields(fieldName) {
    $('#' + fieldName).css('border-color', '#a94442');
    $('#' + fieldName).parent().find('label').css('color', '#a94442');
    $('#' + fieldName).css('box-shadow', 'inset 0 1px 1px rgba(0,0,0,0.075)');
    $('#' + fieldName).focusin(function(){
      $(this).css('border-color', '#a94442');
      $(this).css('box-shadow', 'inset 0 1px 1px rgba(0, 0, 0, 0.075), 0 0 6px #ce8483');
    });
    $('#' + fieldName).focusout(function () {
      $(this).css('border-color', '#cccccc');
      $(this).css('box-shadow', 'none');
    });
    $('#' + fieldName).on('input', function () {
      $(this).css('border-color', '#66afe9');
      $(this).parent().find('label').css('color', '#333');
      $(this).css('box-shadow', 'inset 0 1px 1px rgba(0,0,0,.075),0 0 8px rgba(102,175,233,0.6)');
    });
  }

  /**
   * @function getSSLChoice()
   * Get the user choix (Self signed or True cert)
   */
  function getSSLChoice(){
    Gofast.choosenOption = "optionOne";
    $("#sslCertificateOptionOne a").on("click", function (event) {
      if ($("#sslCertificateOptionOne").hasClass("collapsed") & !$("#sslCertificateOptionTwo").hasClass("collapsed")) {
        $("#sslCertificateOptionTwo a").trigger("click");
        Gofast.choosenOption = "optionOne";
      }
      if ($("#sslCertificateOptionTwo").hasClass("collapsed") & !$("#sslCertificateOptionOne").hasClass("collapsed")) {
        event.preventDefault();
      }
    });
    $("#sslCertificateOptionTwo a").on("click", function (event) {
      if ($("#sslCertificateOptionTwo a").hasClass("collapsed") & !$("#sslCertificateOptionOne").hasClass("collapsed")) {
        $("#sslCertificateOptionOne a").trigger("click");
        Gofast.choosenOption = "optionTwo";
      }
    });
  }
  function prepareSummary() {
    if (Gofast.submitdomainname && Gofast.submitsslcertificate && Gofast.submitsmtp && Gofast.submitadmuser === true) {
      $(".configSummary").remove();// if summary already exist, so remove then. If not it does it for nothing.
      $("#end").prepend("<div class='configSummary panel panel-default'>\n\
                            <div class='panel-heading'>\n\
                              "+ Drupal.t("Configuration Summary") + "\n\
                            </div>\n\
                            <div class='panel-body'>\n\
                              <ul class='configSummary'>\n\
                                <h6>"+ Drupal.t("Admin user informations") + "</h6>\n\
                                <li><b>"+ Drupal.t('Login: ') + "</b>" + $('#fieldIdentifier').val() + "</li>\n\   \n\
                                <li><b>"+ Drupal.t('Last Name: ') + "</b>" + $('#fieldName').val() + "</li>\n\
                                <li><b>"+ Drupal.t('First Name: ') + "</b>" + $('#fieldfirstName').val() + "</li>\n\
                                <li><b>"+ Drupal.t('Email: ') + "</b>" + $("#fieldUseEmail").val() + "</li>\n\
                                <li id='show_password'><b>"+ Drupal.t('Password: ') + "</b>" + "*********  <i class='fa fa-eye eye_password' aria-hidden='true'></i></li>\n\
                                <li id='hide_password' style='display:none;'><b>"+ Drupal.t('Password: ') + "</b>" + $("#userAdmPassWord").val() + "   <i class='fa fa-eye eye_password' aria-hidden='true'></i></li>\n\
                              </ul>\n\
                              <ul class='configSummary'>\n\
                                <h6>"+ Drupal.t("New Technical Password") + "</h6>\n\
                                <li id='hide_password_technical' style='display:none;'><b>"+ Drupal.t('Technical password: ') + "</b>" + $("#technical_pwd").val() + "  <i class='fa fa-eye eye_technical' aria-hidden='true'></i></li>\n\
                                <li id='show_password_technical'><b>"+ Drupal.t('Technical password: ') + "</b>" + "*********  <i class='fa fa-eye eye_technical' aria-hidden='true'></i></li>\n\
                              </ul>\n\
                              <ul class='configSummary'>\n\
                                <h6>"+ Drupal.t("New Domain Name") + "</h6>\n\
                                <li>"+ $('#fieldSubDomain').val() + "." + $('#fieldDomain').val() + "." + $('#fieldExtention').val() + "</li>\n\
                              </ul>\n\
                            </div>\n\
                            <div class='alert alert-block alert-dismissible alert-warning messages warning'>\n\
                              <div>\n\
                                <div style='display:inline-block'>"+ Drupal.t('Services are not available, please wait') + "</div>\n\
                                <div class='loader-services' style='display:inline-block'></div>\n\
                              </div>\n\
                            </div>\n\
                        </div>");
      $('.eye_technical').click(function () {
        if ($('#hide_password_technical').css('display') == 'none') {
          $('#show_password_technical').css('display', 'none');
          $('#hide_password_technical').css('display', 'list-item');
        } else {
          $('#show_password_technical').css('display', 'list-item');
          $('#hide_password_technical').css('display', 'none');
        }
      });
      $('.eye_password').click(function () {
        if ($('#hide_password').css('display') == 'none') {
          $('#show_password').css('display', 'none');
          $('#hide_password').css('display', 'list-item');
        } else {
          $('#show_password').css('display', 'list-item');
          $('#hide_password').css('display', 'none');
        }
      });
      waitAlfrescoUp();
    }

  }

  function waitAlfrescoUp() {
    $.ajax(location.origin + "/alfresco/", {
      type: "POST",
      statusCode: {
        200: function () {
          console.log('alfresco:200');
        },
        201: function () {
          console.log('alfresco:201');
        },
        400: function () {
          console.log('alfresco:400');
        },
        404: function () {
          console.log('alfresco:404');
        }
      }, success: function () {
        $('.configSummary .alert-warning').remove();
        $('#finalSubmit').attr('disabled', false);
      }, error: function () {
        console.log("alfresco:Service are not available yet, please wait");
        waitAlfrescoUp();
      },
    });
  }

  function waitHttpRequest() {
    var intervalID = setInterval(function () {
      $.ajax({
        url: location.origin + "/sites/all/modules/gofast/gofast_graphic_config/validate.txtinfo",
        type: "GET",
        success: function (data, status, xhr) {
          setTimeout(function () { window.location.href = location.origin; }, 20000);
        }
      });
    }, 5000);
  }

  function validateDomain(event) {
    var toaster_options = initToastrOptions();
    event.preventDefault();
    var subDomain = $('#fieldSubDomain').val();
    var Domain = $('#fieldDomain').val();
    var Extention = $('#fieldExtention').val();
    var elements = {
      'fieldSubDomain': subDomain,
      'fieldDomain': Domain,
      'fieldExtention': Extention
    };
    if (checkEmptyInputForm(elements) == false && checkInvalidCharacForm(elements) == false){
      $("[href=#domainName] span div").removeClass('visibility-hidden');
      submitStep("/validateDomainName", { subdomain: subDomain, domain: Domain, extention: Extention });
    }
  }


  function validateSSL(event) {
    var toaster_options = initToastrOptions();
    event.preventDefault();
    if (Gofast.choosenOption == "optionOne") {
      /**** Check existence files ****/
      var stepExistOK = false;
      var existPrivate = document.getElementById("fieldPrivateKey").files[0];
      var existPublic = document.getElementById("fieldPublicKey").files[0];
      if (existPrivate === undefined) {
        setWarningFields('fieldPrivateKey');
        Gofast.toast(Drupal.t('Please upload your private key !', {}, { 'context': 'gofast' }), 'warning', null, toaster_options);
        stepExistOK === false;
      }
      else {
        stepExistOK === true;
      }
      if (existPublic === undefined) {
        setWarningFields('fieldPublicKey');
        Gofast.toast(Drupal.t('Please upload your public key !', {}, { 'context': 'gofast' }), 'warning', null, toaster_options);
        stepExistOK === false;
      }
      else {
        stepExistOK === true;
      }
      /**** Check extentions files ****/
      var stepExtentionOK = false;
      var resultPrivate = getFileExtension(document.getElementById("fieldPrivateKey").files[0].name);
      var resultPublic = getFileExtension(document.getElementById("fieldPublicKey").files[0].name);
      if (resultPrivate === "key") {
        stepExtentionOK === true;
      }
      else {
        setWarningFields('fieldPrivateKey');
        Gofast.toast(Drupal.t('Incorrect extention file! It must be ".key" extention.', {}, { 'context': 'gofast' }), 'warning', null, toaster_options);
        stepExtentionOK = false;
      }
      if (resultPublic === "crt") {
        stepExtentionOK = true;
      }
      else {
        setWarningFields('fieldPublicKey');
        Gofast.toast(Drupal.t('Incorrect extention file! It must be ".crt" extention.', {}, { 'context': 'gofast' }), 'warning', null, toaster_options);
        stepExtentionOK = false;
      }
      /*** ajax request for pass de files and check them ****/
      if (stepExtentionOK === true) {
        $("[href=#sslCertificate] span div").removeClass('visibility-hidden');
        var reader1 = new FileReader();
        var reader2 = new FileReader();
        reader1.onload = function () {
          Gofast.tempPrivateFile = reader1.result;
          reader2.onload = function () {
            Gofast.tempPublicFile = reader2.result;
            var elements = { PrivateFile: Gofast.tempPrivateFile, PublicFile: Gofast.tempPublicFile };
            submitStep("/validateSSLCertificate", elements);
          };
          reader2 = uploadFile("fieldPublicKey", reader2);
        };
        reader1 = uploadFile("fieldPrivateKey", reader1);
      }
    }
    if (Gofast.choosenOption == "optionTwo") {
      var country = $("#fieldCountry option:selected").text();
      var province = $("#fieldProvince").val();
      var city = $("#fieldCity").val();
      var compagny = $("#fieldOrganization").val();
      var typeSite = $("#fieldOrganizationalUnit").val();
      var nameSite = $("#fieldcommonName").val();
      var emailAddres = $("#fieldEmailAddress").val();
      if (country && province && city && compagny && typeSite && nameSite && emailAddres !== "") {
        setDefaultFields('fieldCountry');
        setDefaultFields('fieldProvince');
        setDefaultFields('fieldCity');
        setDefaultFields('fieldOrganization');
        setDefaultFields('fieldOrganizationalUnit');
        setDefaultFields('fieldcommonName');
        setDefaultFields('fieldEmailAddress');
        if (!validateEmail(emailAddres)){
          setWarningFields('fieldEmailAddress');
          Gofast.toast(Drupal.t('The email address is not valid!', {}, { 'context': 'gofast' }), 'error', null, toaster_options);
        }else{
          //$("[href=#sslCertificate] span div").removeClass('visibility-hidden');
          var elements = { Country: country, Province: province, City: city, Compagny: compagny, TypeSite: typeSite, NameSite: nameSite, EmailAddres: emailAddres };
          submitStep('/validateSSLCertificate', elements);
          $("[href=#sslCertificate] span div").removeClass('visibility-hidden');
        }
      }
      else {
        var elements = {
          'fieldCountry': country,
          'fieldProvince': province,
          'fieldCity': city,
          'fieldOrganization': compagny,
          'fieldOrganizationalUnit': typeSite,
          'fieldcommonName': nameSite,
          'fieldEmailAddress': emailAddres
        };
        checkEmptyInputForm(elements);
      }
    }
  }

  function backSSL(event) {
    event.preventDefault();
    $("[href=#domainName]").trigger('click');
    $("[href=#domainName] span div").addClass('visibility-hidden');
    $("#loaderDomainName").trigger("click");
    Gofast.is_event = true;
    $("[href=#domainName]").trigger("click");
    Gofast.chekerDomainname = false;
  }

  function initSMTP() {
    Gofast.securityServerSmtp = "none";
    $("#edit-smtp-security-").on("click", function () {
      Gofast.securityServerSmtp = "none";
    });
    $("#edit-smtp-security-tls").on("click", function () {
      Gofast.securityServerSmtp = "TLS";
    });
    $("#edit-smtp-security-ssl").on("click", function () {
      Gofast.securityServerSmtp = "SSL";
    });
  }

  function validateSMTP(event) {
    var toaster_options = initToastrOptions();
    event.preventDefault();
    var URLServerSmtp = $("#edit-smtp-server").val();
    var userNameSmtp = $("#edit-smtp-username").val();
    var passwordUserSmtp = $("#edit-smtp-password").val();
    var portServerSmtp = $("#edit-smtp-port").val();
    var emailUser = $("#recipient-email").val();
    var siteName = $('#fieldSubDomain').val();
    var siteEmail = userNameSmtp;
    if (URLServerSmtp && portServerSmtp && Gofast.securityServerSmtp !== "") {
      if (!validateEmail(emailUser)) {
        setWarningFields('recipient-email');
        Gofast.toast(Drupal.t('The email address is not valid!', {}, { 'context': 'gofast' }), 'error', null, toaster_options);
      } else {
        var elements = {
          siteemail: siteEmail,
          urlserversmtp: URLServerSmtp,
          usernamesmtp: userNameSmtp,
          passwordusersmtp: passwordUserSmtp,
          securityserversmtp: Gofast.securityServerSmtp,
          portserversmtp: portServerSmtp,
          emailuser: emailUser,
          sitename: siteName
        };
        submitStep('/validateSMTPServer', elements);
        $("[href=#smtp] span div").removeClass('visibility-hidden');
      }
    }
    else {
      var elements = {
        'edit-smtp-server': URLServerSmtp,
        'edit-smtp-port': portServerSmtp,
        'recipient-email': siteEmail
      };
      checkEmptyInputForm(elements);
    }
  }


  function backSMTP(event) {
    event.preventDefault();
    Gofast.is_event = true;
    $("[href=#sslCertificate]").trigger("click"); // change thumbnails
    $("[href=#sslCertificate] span div").addClass('visibility-hidden');
    $("#loaderSslCertificate").trigger("click");
    Gofast.is_event = true;
    $("[href=#sslCertificate]").trigger("click");
    Gofast.chekerSslcertificate = false;
  }

  function validateAdm(event) {
    var toaster_options = initToastrOptions();
    event.preventDefault();
    var error = false;
    var userID = $("#fieldIdentifier").val();
    var userLDAPName = $("#fieldName").val();
    var userLDAPLastName = $("#fieldfirstName").val();
    var userEMail = $("#fieldUseEmail").val();
    var userPassWord = $("#userAdmPassWord").val();
    var userPassWordBis = $("#userAdmPassWordBis").val();
    var userTitle = $("#fieldTitle").val();
    var userPhoneNumber = $("#fieldPhoneNumber").val();
    var userMobilePhoneNumber = $("#fieldMobilePhoneNumber").val();
    var userTechnicalPassword = $("#technical_pwd").val();
    var userTechnicalPasswordBis = $("#technical_pwd_bis").val();
    if (userID && userLDAPName && userLDAPLastName && userEMail && userPassWord && userTechnicalPassword !== "") {
      if (userID.length<4){
        error = true;
        setWarningFields('fieldIdentifier');
        Gofast.toast(Drupal.t('The lenght of your login name is to short! You must provide at least four characters.', {}, { 'context': 'gofast' }), 'error', null, toaster_options);
      }else{
        setDefaultFields('fieldIdentifier');
      }
      if (userID == "admin"){
        error = true;
        setWarningFields('fieldIdentifier');
        Gofast.toast(Drupal.t("Identifier can't be 'admin', please change it", {}, { 'context': 'gofast' }), 'error', null, toaster_options);
      }else{
        setDefaultFields('fieldIdentifier');
      }
      if (!validateEmail(userEMail)){
        error = true;
        setWarningFields('fieldUseEmail');
        Gofast.toast(Drupal.t('The email address is not valid!', {}, { 'context': 'gofast' }), 'error', null, toaster_options);
      }else{
        setDefaultFields('fieldUseEmail');
      }
      if (!matchPassword(userPassWord, userPassWordBis)) {
        error = true;
        setWarningFields('userAdmPassWord');
        setWarningFields('userAdmPassWordBis');
        Gofast.toast(Drupal.t('The two password fields are not equal!', {}, { 'context': 'gofast' }), 'error', null, toaster_options);
      }else{
        setDefaultFields('userAdmPassWord');
        setDefaultFields('userAdmPassWordBis');
      }
      if (!validatePassword(userPassWord)){
        error = true;
        setWarningFields('userAdmPassWord');
        Gofast.toast(Drupal.t('The user password is not correct! Enter at least 8 characters! One upper case, one lower case and one special characters.', {}, { 'context': 'gofast' }), 'error', null, toaster_options);
      }else{
        setDefaultFields('userAdmPassWord');
      }
      if (userPhoneNumber.length < 9){
        error = true;
        setWarningFields('fieldPhoneNumber');
        Gofast.toast(Drupal.t('The phone number is to short! Enter at least 10 characters!', {}, { 'context': 'gofast' }), 'error', null, toaster_options);
      }else{
        setDefaultFields('fieldPhoneNumber');
      }
      if (userMobilePhoneNumber.length < 9) {
        error = true;
        setWarningFields('fieldMobilePhoneNumber');
        Gofast.toast(Drupal.t('The mobile phone number is to short! Enter at least 10 characters!', {}, { 'context': 'gofast' }), 'error', null, toaster_options);
      }else{
        setDefaultFields('fieldMobilePhoneNumber');
      }
      if (!matchPassword(userTechnicalPassword, userTechnicalPasswordBis)) {
        error = true;
        setWarningFields('technical_pwd');
        setWarningFields('technical_pwd_bis');
        Gofast.toast(Drupal.t('The two password fields are not equal!', {}, { 'context': 'gofast' }), 'error', null, toaster_options);
      }else{
        setDefaultFields('technical_pwd');
        setDefaultFields('tectechnical_pwd_bishnical_pwd');
      }
      if (!validatePassword(userTechnicalPassword)) {
        error = true;
        setWarningFields('technical_pwd');
        Gofast.toast(Drupal.t('The technical password is not correct! Enter at least 8 characters! One upper case, one lower case and one special characters. The character \' is forbidden ', {}, { 'context': 'gofast' }), 'error', null, toaster_options);
      }else{
        setDefaultFields('technical_pwd');
      }
      if (error != true){
        var elements = {
          userid: userID,
          userldapname: userLDAPName,
          userldaplastname: userLDAPLastName,
          useremail: userEMail,
          userpassword: userPassWord,
          userpasswordbis: userPassWordBis,
          usertitle: userTitle,
          userphonenumber: userPhoneNumber,
          usermobilephonenumber: userMobilePhoneNumber,
          usertechnicalpassword: userTechnicalPassword,
          usertechnicalpasswordbis: userTechnicalPasswordBis
        };
        submitStep('/validateADMUser', elements);
        $("[href=#userAdm] span div").removeClass('visibility-hidden');
      }
    }else {
      var elements = {
        'fieldIdentifier': userID,
        'fieldName': userLDAPName,
        'fieldfirstName': userLDAPLastName,
        'fieldUseEmail': userEMail,
        'userAdmPassWord': userPassWord,
        'userAdmPassWordBis': userPassWordBis,
        'technical_pwd': userTechnicalPassword,
        'technical_pwd_bis': userTechnicalPasswordBis
      };
      checkEmptyInputForm(elements);
    }
  }

  function backAdm(event) {
    event.preventDefault();
    $("[href=#smtp]").trigger("click"); // change thumbnails
    $("[href=#smtp] span div").addClass('visibility-hidden');
    $("#loaderSmtp").trigger("click");
    Gofast.is_event = true;
    $("[href=#smtp]").trigger("click");
    Gofast.chekerSmtp = false;
  }

  function validateConfig(event) {
    event.preventDefault();
    $('body').append('<div class="pt-conf-page1"><div class="message_config"><p>' + Drupal.t('Your configuration is being applied') + '</p><p>' + Drupal.t('Please wait') + '</p>' + "<p class='pleasewait'>" + Drupal.t('This process may takes a few minutes') + '</p>' + '</div></hr></div>');
    $('.pt-conf-page1').addClass('pt-page-meltedSlideinAndout');
    setTimeout(function () {
      Gofast.addLoading();
      waitHttpRequest();
    }, 5000);
    var form = $("#gofast-graphic-config-frame");
    var url = form.attr('action');
    $.ajax({
      type: "POST",
      url: url,
      data: form.serialize(),
      cache: false,
      success: function () {
        console.log("Form submited");
      }
    });
  }

  function backFinal(event) {
    event.preventDefault();
    $("[href=#userAdm]").trigger("click"); // change thumbnails
    // reset the loader
    $('#loaderUserAdm').trigger("click");
    $("[href=#userAdm] span div").addClass('visibility-hidden');
    Gofast.is_event = true;
    $("[href=#userAdm]").trigger("click");
    Gofast.chekerAdmuser = false;
  }

  function validateEmail(email) {
    var re = /^(([^<>()\[\]\\.,;:\s@"]+(\.[^<>()\[\]\\.,;:\s@"]+)*)|(".+"))@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\])|(([a-zA-Z\-0-9]+\.)+[a-zA-Z]{2,}))$/;
    return re.test(String(email).toLowerCase());
  }

  function validatePassword(str) {
    var mysql_error = /^.*[^']$/;
    var re = /^(?=.*\d)(?=.*[!@#$%^&*])(?=.*[a-z])(?=.*[A-Z]).{8,}$/;
    if (mysql_error.test(str)) {
      return re.test(str);
    }else{
      return false;
    }
  }

  function matchPassword(password,passwordbis){
    if(password == passwordbis){
      return true;
    }else{
      return false;
    }
  }

  function bindTabClick() {
    $.each($('.vertical-tab-button a'), function (k, tab) {
      $().bindFirst(tab, 'click', function (e) {
        if (Gofast.is_event !== true) {
          e.preventDefault();
          e.stopPropagation();
          e.stopImmediatePropagation();
        }
        else {
          Gofast.is_event = false;
        }
      });
    });
    $('.vertical-tabs-list > li').addClass('disabled');
  }
})(jQuery, Drupal, Gofast);

