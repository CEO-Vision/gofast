

(function ($, Gofast, Drupal) {
  'use strict';


  /**
   * Init Gofast settings and globals
   *  Drupal.settings.gofast.* are initialized in gofast.js anyway.
   */
  Gofast.global = Gofast.global || {} ;
  Gofast.user = Gofast.user || {};

  Gofast.user.overProfile = false;

  // Settings take a while before being set. Handle init in a behavior to
  // prevent falsy fallback override.
  Drupal.behaviors.userInitSettings = {
    attach : function (context, settings) {
      Drupal.settings.gofast = Drupal.settings.gofast || {};
      Drupal.settings.gofast.user = Drupal.settings.gofast.user || {};
    }
  };

  Gofast.user.showProfilePopup = function () {
    Gofast.user.overProfile = true;

    var uid = this.id.split('-')[0], url,
        ogContext = Drupal.settings.ogContext,
        popup = $(this).find('.profile-popup'),
        throbber = '<i aria-hidden="true" class="icon glyphicon glyphicon-refresh glyphicon-spin"></i>';

    popup.html(throbber).mouseleave(Gofast.user.hideProfilePopup);

    url = '/profile/popup/' + uid;
    if (ogContext && ogContext.groupType === 'node' && ogContext.gid) {
      url += '/' + ogContext.gid;
    }

    $.ajax({
      url       : url,
      dataType  : 'html',
      beforeSend: function(xhr) {
        Gofast.xhrPool = Gofast.xhrPool || {};
        Gofast.xhrPool.xhrShowProfilePopup = xhr;
      },
      'complete': function() {
        delete Gofast.xhrPool.xhrShowProfilePopup;
      },
      success   : function (response) {
        if (Gofast.user.overProfile === true) {
          popup.html(response);
          Drupal.attachBehaviors();
        }
      }
    });
  };

  Gofast.user.hideProfilePopup = function() {
    Gofast.user.overProfile = false;
    $(this).find('.profile-popup').children().remove();
  };

  Drupal.behaviors.gofastUserProfilePopup = {
    attach : function (context, settings) {
      var config = {
        sensitivity: 7,
        interval: 100,
        over: Gofast.user.showProfilePopup,
        timeout: 0,
        out: Gofast.user.hideProfilePopup
      };
      $('.user-picture.profile-to-popup:not(.gofast-popup-processed)').addClass('gofast-popup-processed').each(function() {
        $(this).hoverIntent(config);
      });
    }
  };

  Drupal.behaviors.gofastUserSaveLang = {
    attach : function (context, settings) {
      $('.gofast-save-lang').addClass('gofast-processed').click(function(e) {
        e.preventDefault();
        Gofast.user.saveLang();
      });
    }
  };

  Gofast.user.saveLang = function (lang, user) {
    user = user || Drupal.settings.gofast.user;

    if (!lang) {
      var params = Gofast.getQueryVariables();
      lang = params && params.language;
    }

    $.ajax({
      url: Drupal.settings.basePath + 'profile/save-language/' + lang,
      beforeSend: function(xhr) {
        Gofast.xhrPool = Gofast.xhrPool || {};
        Gofast.xhrPool.xhrSaveLanguage = xhr;
      },
      'complete': function() {
        delete Gofast.xhrPool.xhrSaveLanguage;
      },
      success: function (data, textStatus, jqXHR) {
        Gofast.updateStatusMessages(data);
      },
      error: function (data, textStatus, jqXHR) {
        console.log(data, textStatus, jqXHR);
      }
    });
  };

  /*
   * [GOFAST-6242]
   */
  Gofast.user.SubmitForm = function () {
      Drupal.CTools.Modal.dismiss();
      $("input[name='email_already_exists_confirmed']").val("1");
      $('#submit_create_user').trigger( "mousedown"); // click =event ne marche pas
  };

     Gofast.user.Unblock_user = function (Uid) {
    $.ajax({
      url : '/gofast/user/'+Uid+'/unblock',
      type : 'POST',
      success : function(data){
                  Drupal.CTools.Modal.dismiss();
                  Gofast.toast(Drupal.t("User unblocked", {}, {context: "gofast:gofast_user"}));
                  Gofast.processAjax('/user/' + Uid);
              }
          });
    };

  /*
   * [GOFAST-7326] make the user editable inputs working like the kanban ones
   */
  Gofast.user.UserEditableInputs = async function (account_uid) {
    let profileDTO = {};

    // retrieving data transfer object of user profile info
    if (Object.entries(profileDTO).length === 0) {
      try {
        const response = await fetch(
          Drupal.settings.basePath + "gofast/user/"+account_uid+"/profile/get"
        );
        profileDTO = await response.json();
      } catch (e) {
        console.log(e.message);
      }
    }

    // defining properties of the inputs to render the DTO fields where we want and as we want
    const ldapInputs = {
      firstname: {
        wrapperSelector: "#profile-firstname",
        inputElClass: "GofastUser__firstNameInput",
        type: "text",
      },
      lastname: {
        wrapperSelector: "#profile-lastname",
        inputElClass: "GofastUser__lastNameInput",
        type: "text",
      },
      job: {
        wrapperSelector: "#profile-job",
        inputElClass: "GofastUser__jobInput",
        type: "text",
      },
      phone: {
        wrapperSelector: ".profile-phone-info",
        inputElClass: "GofastUser__phoneInput",
        type: "text",
        // pattern is for front-side (UX) validation
        pattern: "^[\+]?[(]?[0-9]{3}[)]?[-\s\.]?[0-9]{3}[-\s\.]?[0-9]{4,6}$",
      },
      email: {
        wrapperSelector: ".profile-email-info",
        inputElClass: "GofastUser__emailInput",
        type: "text",
        pattern: ".+\@.+\..+",
      },
      department: {
        wrapperSelector: ".profile-department-info",
        inputElClass: "GofastUser__departmentInput",
        type: "text",
      },
      birthdate: {
        wrapperSelector: ".profile-birthdate-info",
        inputElClass: "GofastUser__birthdateInput",
        type: "date",
      },
      expiration_date: {
        wrapperSelector: ".profile-expiration-date-info",
        inputElClass: "GofastUser__expirationDateInput",
        type: "expiration_date",
      },
      manager: {
        wrapperSelector: ".profile-manager-info",
        inputElClass: "GofastUser__managerInput",
        type: "userselect",
      },
      description: {
        wrapperSelector: ".profile-description-info",
        inputElClass: "GofastUser__descriptionInput",
        type: "text",
      },
      skills: {
        wrapperSelector: ".profile-skills-info",
        inputElClass: "GofastUser__skillsInput",
        type: "tags",
      },
      interests: {
        wrapperSelector: ".profile-passions-info",
        inputElClass: "GofastUser__passionsInput",
        type: "tags",
      },
      hobbies: {
        wrapperSelector: ".profile-hobbies-info",
        inputElClass: "GofastUser__hobbiesInput",
        type: "tags",
      }
    };

    // declaring a reference pseudo-constructor in order to update the user profile fields on the db
    const UserEditableInput = (userId, field, inputEl, initialValue, type, pattern = null) => {
      let _userEditableInput = {
        // object properties let us mutate the values afterwards if needed
        field: null,
        inputEl: null,
        initialValue: null,
        type: null,
        pattern: null,
        placeholder: null,

        // we made it from PHP to JSON for the GET request
        // but we have to go the other way back for the POST request
        dtoFieldToUserFormFieldMap: {
          firstname: {field: "ldap_user_givenname", placeholder: "First name"},
          lastname: {field: "ldap_user_sn", placeholder: "Last name"},
          job: {field: "ldap_user_title", placeholder: "Job position"},
          phone: {field: "ldap_user_telephonenumber", placeholder: "Your phone number"},
          email: {field: "mail", placeholder: "Your email address"},
          department: {field: "ldap_user_o", placeholder: "Your organisation"},
          birthdate: {field: "field_birthdate", placeholder: "Your birthdate"},
          expiration_date: {field: "field_extranet_expiration_date", placeholder: ""},
          manager: {field: "ldap_user_manager", placeholder: "Your manager"},
          description: {field: "ldap_user_description", placeholder: "Description"},
          skills: {field: "field_skills", placeholder: "Your skills"},
          interests: {field: "field_interests", placeholder: "Your interests"},
          hobbies: {field: "field_hobbies", placeholder: "Your hobbies"},
        },

        // update callback
        userProfileUpdate: async function (userId, field, value, initialValue) {
          let formData = new FormData();
          // we don't forget to translate the DTO field into a Drupal user form field
          formData.append("pk", userId);
          formData.append("name", this.dtoFieldToUserFormFieldMap[field].field);
          formData.append("value", value);
          // we don't change the backend logic to avoid breaking other stuff relying on it
          if (field === "birthdate") {
            formData.append("date_str", (new Date(value)).getTime());
          }
          if (field === "expiration_date") {
            formData.append("expiration_date_timestamp", value)
          }
          if (field === "manager") {
            if(typeof value.ldap_user_prov_entries_value != "undefined"){
              formData.set("value", value.ldap_user_prov_entries_value.replace('gofastLDAP|', ''));
            }
          }
          if(field === "skills"){
            formData.delete("value");
            value.forEach(function(val, idx, arr){
              formData.append("value[]", val.name);
            });
            formData.append("vid", $('#skills_id').attr('data-vid'));
            formData.append("enforce", $('#skills_id').attr('data-enforce'));
          }
          if(field === "interests"){
            formData.delete("value");
            value.forEach(function(val, idx, arr){
              formData.append("value[]", val.name);
            });
            formData.append("vid", $('#passions_id').attr('data-vid'));
            formData.append("enforce", $('#passions_id').attr('data-enforce'));
          }
          if(field === "hobbies"){
            formData.delete("value");
            value.forEach(function(val, idx, arr){
              formData.append("value[]", val.name);
            });
            formData.append("vid", $('#hobbies_id').attr('data-vid'));
            formData.append("enforce", $('#hobbies_id').attr('data-enforce'));
          }

          const url = Drupal.settings.basePath + "update_field";

          try {
            await fetch(url, {
              method: "POST",
              body: formData,
            });
          } catch(e) {
            console.log(e.message);
          }
        },

        // nulls everything but the helpers
        clear() {
          Object.keys(this).filter(k => typeof this[k] !== "function" && typeof this[k] !== "object").forEach(k => this[k] = null);
        },

        init(userId, field, inputEl, initialValue, type, pattern = null) {
          this.userId = userId;
          this.field = field;
          this.inputEl = inputEl;
          this.initialValue = initialValue;
          this.type = type;
          this.editableInput = null;
          // we pass the update callback inside the generic GofastEditableInput pseudo-constructor
          let userEditableInputProps = {
            save: async (newData) => {
              let emailValid = false;
              if (field == "email") {
                emailValid = await Gofast.user.validateUserEmail(newData);
              }
              // If the email is not valid, don't save the new data and show the last valid value
              if(field == "email" && newData != "" && !emailValid){
                newData = this.initialValue;
                if(this.editableInput){
                  this.editableInput.DOM.input.value = newData
                  this.editableInput.saveData(newData)
                }
              }
              if (newData !== this.initialValue) {
                // Set the initial value to the last valid data
                this.initialValue = newData
                const response = this.userProfileUpdate(
                  this.userId,
                  this.field,
                  newData,
                  this.initialValue
                );
              }
            },
          };
          // for frontside validation
          if (pattern) {
            this.pattern = pattern;
            userEditableInputProps.pattern = pattern;
          }
          // for custom default value (e.g. "job position", "your organisation")
          if (this.dtoFieldToUserFormFieldMap[field].placeholder) {
            userEditableInputProps.placeholder = this.dtoFieldToUserFormFieldMap[field].placeholder;
          }
          // for frontside "security"
          if (userId !== Drupal.settings.gofast.user.uid) {
            userEditableInputProps.isEditable = false;
          }
          const userEditableInput = GofastEditableInput(
            inputEl,
            initialValue,
            type,
            userEditableInputProps,
          );
          this.editableInput = userEditableInput
        },
      };

      _userEditableInput.init(userId, field, inputEl, initialValue, type, pattern);

      return _userEditableInput;
    };

    // generating the editable inputs and inserting them into the templates with the right style
    // as well as the right object callbacks for db update
    for (const key in ldapInputs) {
      if (!ldapInputs.hasOwnProperty(key)) {
        continue;
      }

      const inputWrapper = document.querySelector(
        ldapInputs[key].wrapperSelector
      );
      if (inputWrapper && inputWrapper.innerHTML.trim() == "") {
        const inputEl = document.createElement("div");
        inputEl.classList.add(ldapInputs[key].inputElClass, "EditableInput");
        // for datetime fields, we convert the timestamp into a date string
        if (key === "birthdate") profileDTO[key] = new Date(profileDTO[key]);
        if (key === "manager") {
          if(profileDTO[key].uid > 0){
            const userTeam = await Gofast.user.GetUserTeam(account_uid, profileDTO[key].uid);
            Gofast.user.ShowUserTeam(userTeam);
          }else{
            const userTeam = await Gofast.user.GetUserTeam(account_uid);
            if(userTeam.length !== 0){
              Gofast.user.ShowUserTeam(userTeam);
            }else{
              Gofast.user.ShowUserTeam("");
            }
          }
          if(profileDTO["relationships"]){
            Gofast.user.ShowRelation(profileDTO["relationships"]);
          }else{
            Gofast.user.ShowRelation("");
          }
        }
        let initialValue =
          (typeof profileDTO[key] === "object" && profileDTO[key].hasOwnProperty("value"))
            ? profileDTO[key].value
            : profileDTO[key];
        // this auto-initializes and uses GofastEditableInput to mutate the input DOM element
        let userEditableInput = UserEditableInput(
          account_uid,
          key,
          inputEl,
          initialValue,
          ldapInputs[key].type,
          ldapInputs[key].hasOwnProperty("pattern") ? ldapInputs[key].pattern : null
        );

        inputWrapper.classList.remove("spinner", "py-4");
        inputWrapper.appendChild(inputEl);
      }
    }
  }

  Gofast.user.GetUserTeam = async function(account_uid, manager_uid) {
    let userTeam = [];
    if(manager_uid){
    try {
      const response = await fetch(
        Drupal.settings.basePath + "gofast/user/"+account_uid+"/profile/get/"+manager_uid+"/team"
      );
        userTeam = await response.json();
      } catch (e) {
        console.log(e.message);
      }
    }else{
      try {
        const response = await fetch(
          Drupal.settings.basePath + "gofast/user/"+account_uid+"/profile/get/team"
        );
        userTeam = await response.json();
      } catch (e) {
        console.log(e.message);
      }
    }
    return userTeam;
  }

  Gofast.user.ShowUserTeam = function(userTeam) {
    var teamContainer = document.querySelector(".profile-team-info");
    if (userTeam.length === 0) {
      teamContainer.innerHTML = "<div class=\"text-muted\">" + Drupal.t("No team mate has been found.") + "</div>";
      return;
    }
    teamContainer.innerHTML = "";
    let i = 0;
    for (const teamMate of userTeam) {
      const mateTemplate = teamMate.picture;
      teamContainer.insertAdjacentHTML("beforeend", mateTemplate);
      i++;
      if (i % 5 == 0){
        var teamClass = "profile-team-info-" + i;
        teamContainer.insertAdjacentHTML("afterend", '</div><div class="profile-team-info ' + teamClass + ' symbol-group symbol-hover d-none">');
        teamContainer = document.querySelector("." + teamClass);
      }
    }
    if(i >= 5){
      let moreNumber = parseInt(i, 10) - 5;
      document.querySelector(".profile-team-info:not(.d-none)").insertAdjacentHTML("beforeend", "<div class='symbol symbol-circle symbol-light-danger more-info'><span class='symbol-label font-weight-bold'> +" +  moreNumber + "</span></div>");
      $(".profile-team-info").parent().find(".symbol-group").last().append("<div class='symbol symbol-circle symbol-light-danger less-info d-none'><span class='symbol-label font-weight-bold'> - </span></div>");
      Drupal.attachBehaviors();
    }
    // @todo my team modal
  }

  Gofast.user.ShowRelation = function(userRelations){
    var teamContainer = document.querySelector(".profile-relationships-info");
    if (userRelations.length === 0) {
      teamContainer.innerHTML = "<div class=\"text-muted\">" + Drupal.t("No relationships has been found.") + "</div>";
      return;
    }
    teamContainer.innerHTML = "";
    let i = 0;
    for (const relation of userRelations) {
      const mateTemplate = relation.picture;
      teamContainer.insertAdjacentHTML("beforeend", mateTemplate);
      i++;
      if (i % 5 == 0){
        var teamClass = "profile-relationships-info-" + i;
        teamContainer.insertAdjacentHTML("afterend", '</div><div class="profile-relationships-info ' + teamClass + ' symbol-group symbol-hover d-none">');
        teamContainer = document.querySelector("." + teamClass);
      }
    }
    if(i >= 5){
      let moreNumber = parseInt(i, 10) - 5;
      document.querySelector(".profile-relationships-info:not(.d-none)").insertAdjacentHTML("beforeend", "<div class='symbol symbol-circle symbol-light-danger more-info'><span class='symbol-label font-weight-bold'> +" + moreNumber + "</span></div>");
      $(".profile-relationships-info").parent().find(".symbol-group").last().append("<div class='symbol symbol-circle symbol-light-danger less-info d-none'><span class='symbol-label font-weight-bold'> - </span></div>");
      Drupal.attachBehaviors();
    }
  }

  Drupal.behaviors.gofastUserMoreInfo = {
    attach : function (context, settings) {
      $('.more-info:not(.more-info-processed)').addClass('more-info-processed').each(function() {
        $(this).click(function (e) {
          e.preventDefault();
          $(this).parents(".symbol-group").parent().find('.symbol-group.d-none').removeClass('d-none');
          $(this).parents(".symbol-group").parent().find('.less-info').removeClass('d-none');
          $(this).addClass('d-none');
        });
      });
      $('.less-info:not(.more-info-processed)').addClass('more-info-processed').each(function() {
        $(this).click(function (e) {
          e.preventDefault();
          $(this).parents(".symbol-group").parent().find('.symbol-group:not(:first)').addClass('d-none');
          $(this).parents(".symbol-group").parent().find('.more-info').removeClass('d-none');
          $(this).addClass('d-none');
        });
      });
    }
  }

  /**
   * User profile edition forms. Process states for roles checkboxes so that
   * only one non-technical role can be assigned to a user (radios would not
   * do the job for technical roles values).
   */
  Drupal.behaviors.gofastUserAdminRolesStates = {
    attach : function (context, settings) {
      $('.GofastForm__Field--Roles label.checkbox').each(function() {
        $(this).addClass('switch switch-icon switch-sm gofast-switch-icon');
      });

      var $roles = $('.user-roles-force-single input[type=checkbox]', context);
      $roles.once('single-role', function () {
        $(this).on('change', function () {
          if ($(this).hasClass("role_contributor")) {
            $roles.not(this).not(':disabled').prop('checked', false);
            $('.field-name-is-extranet').find('input').prop('disabled', false);
          }
          if ($(this).hasClass("role_administrator") || $(this).hasClass("role_business_adm")) {
            $('.role_contributor').prop('checked', false);
            $('.field-name-is-extranet').find('input').prop('checked', false);
            $('.field-name-is-extranet').find('input').prop('disabled', true);
          }
        });
      });
    }
  };
  
   Drupal.behaviors.gofastUserFormMailCheck = {
    attach : function (context, settings) {
      var $form_element = $("#user-register-form");
      var $input_mail = $('#user-register-form #edit-mail', context);
      if($form_element.length == 0){
        $form_element = $("#user-profile-form");
        $input_mail = $("#user-profile-form #edit-mail");
      }
      if($form_element.length == 0){
        return
      }
      $input_mail.once('check_mail_processed', function() {
        $(this).on('blur', function(e) {
            // we do nothing if we don't have a valid email
            if (!/^[a-zA-Z0-9.!#$%&'*+/=?^_`{|}~-]+@[a-zA-Z0-9-]+(?:\.[a-zA-Z0-9-]+)*$/.test($(this).val())) {
              return;
            }
            var current_domain = window.location.hostname.replace(/^[^.]+\./g, "");
            var mail_domain = $(this).val().split('@').pop();
            if(current_domain !== mail_domain){             
                $("#edit-sasl-auth-und").prop("checked", false );             
                $($form_element).find('input[type="password"]').prop('disabled', false);
                $($form_element).find('.form-item-select-pass').show(300);
                $("input[name*='is_extranet']").prop("checked", true ).trigger("change");
            }
           
            //GOFAST-7400 check if GF is sync with LDAP and if LDAP user already exists with this email, to be sur to
            // not make mistake with other fields ( id, etc)
            var path = 'gofast/user/check/ldap?mail='+$(this).val();
            $.ajax({
              url: Drupal.settings.basePath + path,
              type: 'GET',
              dataType: 'json',
              success: function (data) {
               if(data.login){
                if($($form_element).find('#edit-name').val() != data.login){
                  var message = Drupal.t("A user with same email already exists into your internal directory, with username ", {}, {context: "gofast:gofast_user"})+" : "+data.login;
                  message += '<br/>';
                  message += Drupal.t("Please, check before to create this user", {}, {context: "gofast:gofast_user"});

                  Gofast.toast(message, "warning");
                  if($("#ldap_already_exists_message").length == 0){
                    $(".ldap-account").append("<div id='ldap_already_exists_message' style='color:red;'>"+message+"</div>");
                  }else{
                    $("#ldap_already_exists_message").html(message);
                  }
                }
               }else{
                $("#ldap_already_exists_message").remove();
               }
              }
            });
            
        });
      });
    }
  };

   Drupal.behaviors.popupMembersFilter = {
    attach: function(context, settings) {
        if ($('#popup-member-list-filter-search-input').length > 0) {
            $('#popup-member-list-filter-search-input').on('keyup', function(e){
                var s=$(this).val().toLowerCase();
                if(s.length > 2){
                    $('#popup-member-list > li').each(function(){
                        if ($(this).find('.popup-member-list-name').text().toLowerCase().search(s) > -1  || $(this).find('.popup-member-list-role').text().toLowerCase().search(s) > -1) {
                             $(this).show();
                        }
                        else{
                            $(this).hide();
                        }
                    });
                }
                else{
                     $('#popup-member-list > li').show();
                }
            });
        }
    }
  };
  /**
   * Check session every minutes to disconnect properly when required.
   * @see GOFAST-6538
   */
  window.setInterval(function () {
    var path = 'gofast/user/whoami';
    //dont reload page if we already are on the login page to prevent multiple login form submition ( see GOFAST-6902 )
    if($("#block-user-login").size() == 0){
        $.ajax({
          url: Drupal.settings.basePath + path,
          type: 'GET',
          dataType: 'json',
          success: function (data) {
            if (!data.uid || data.uid === '0' && window.location.pathname !== "/Welcome") {
              // Signed out but client still runinng, refresh the page to ensure
              // the front-end is fully disconnected (ie. required for idle tabs).
                 window.location.reload();
            }
          }
        });
    }
  }, 600000);

  Drupal.behaviors.extranetConfig = {
    attach: function (context, settings) {
      let content = $('body', context);
      $(document).one('DOMNodeInserted', content, function() {    
        let groups = $('#og-user-node-add-more-wrapper').find('#ztree_component_user').children('li:nth-child(2)');
        let organizations = $('#og-user-node-add-more-wrapper').find('#ztree_component_user').children('li:nth-child(3)');
    if(groups.length == 1 &&  organizations.length == 1 && !$("#user-register-form").hasClass("gofast-extranet-processed")){     
        $("#user-register-form").addClass("gofast-extranet-processed");      
        let groups = $('#og-user-node-add-more-wrapper').find('#ztree_component_user').children('li:nth-child(2)');
        let organizations = $('#og-user-node-add-more-wrapper').find('#ztree_component_user').children('li:nth-child(3)');
        let config = Drupal.settings.filterExtranet.config;
        let html_extranet_message = "<div id='extranet_message' style='color:red;'>"+Drupal.t("The GoFast configuration doesn't allow you to add external users into some internal spaces types")+"</div>";
        if(config && config['group_add_external_user'] === 1 && config['organization_add_external_user'] === 1){
          var click = 2;
          if($("[id^='edit-is-extranet-und']").is(':checked') === true){
            click = 3;
            groups.css("pointer-events", "none");
            organizations.css("pointer-events", "none");
            groups.css("background-color", "#d3d3d3");
            organizations.css("background-color", "#d3d3d3");
            $("#og-user-node-add-more-wrapper").before(html_extranet_message);
          }
          $("[id^='edit-is-extranet-und']").on("change", function() {
            if(click % 2 === 1){
              groups.css("pointer-events", "auto");
              organizations.css("pointer-events", "auto");
              groups.css("background-color", "#ffffff");
              organizations.css("background-color", "#ffffff");
              $("#extranet_message").remove();
            }else{
              let groupsChecks = [];
              $('#ztree_component_user > li:nth-child(2) span.checkbox_true_full, #ztree_component_user > li:nth-child(2) span.checkbox_true_part').each(function( index ){
                groupsChecks[index] = $(this);
              });
              groupsChecks.forEach(element => element.click());
              let organizationsChecks = [];
              $('#ztree_component_user > li:nth-child(3) span.checkbox_true_full, #ztree_component_user > li:nth-child(3) span.checkbox_true_part').each(function( index ){
                organizationsChecks[index] = $(this);
              });
              organizationsChecks.forEach(element => element.click());
              groups.css("pointer-events", "none");
              organizations.css("pointer-events", "none");
              groups.css("background-color", "#d3d3d3");
              organizations.css("background-color", "#d3d3d3");
              $("#og-user-node-add-more-wrapper").before(html_extranet_message);
            }
            click++;
          });
        }
        else if(config && config['group_add_external_user'] === 1){
          var click = 2;
          if($("[id^='edit-is-extranet-und']").is(':checked') === true){
            click = 3;
            groups.css("pointer-events", "none");
            groups.css("background-color", "#d3d3d3");
            $("#og-user-node-add-more-wrapper").before(html_extranet_message);
          }
          $("[id^='edit-is-extranet-und']").on("change", function() {
            if(click % 2 === 1){
              $("#extranet_message").remove();
              groups.css("pointer-events", "auto");
              groups.css("background-color", "#ffffff");
            }else{
              let groupsChecks = [];
              $('#ztree_component_user > li:nth-child(2) span.checkbox_true_full, #ztree_component_user > li:nth-child(2) span.checkbox_true_part').each(function( index ){
                groupsChecks[index] = $(this);
              });
              groupsChecks.forEach(element => element.click());
              groups.css("pointer-events", "none");
              groups.css("background-color", "#d3d3d3");
              $("#og-user-node-add-more-wrapper").before(html_extranet_message);
            }
            click++;
          });
        }
        else if(config && config['organization_add_external_user'] === 1){
          var click = 2;
          if($("[id^='edit-is-extranet-und']").is(':checked') === true){
            click = 3;
            organizations.css("pointer-events", "none");
            organizations.css("background-color", "#d3d3d3");
            $("#og-user-node-add-more-wrapper").before(html_extranet_message);
          }
          $("[id^='edit-is-extranet-und']").on("change", function() {
            if(click % 2 === 1){
              organizations.css("pointer-events", "auto");
              organizations.css("background-color", "#ffffff");
              $("#extranet_message").remove();
            }else{
              let organizationsChecks = [];
              $('#ztree_component_user > li:nth-child(3) span.checkbox_true_full, #ztree_component_user > li:nth-child(3) span.checkbox_true_part').each(function( index ){
                organizationsChecks[index] = $(this);
              });
              organizationsChecks.forEach(element => element.click());
              organizations.css("pointer-events", "none");
              organizations.css("background-color", "#d3d3d3");
              $("#og-user-node-add-more-wrapper").before(html_extranet_message);
            }
            click++;
          });
        }
      }
      });
    }
  };

  
  Drupal.behaviors.initExpirationDateInput = {
    attach: function (context, settings) {
      let is_extranet_checkbox = $('input[name="is_extranet[und]"]')
      let expiration_input_group = $("#edit-expiration-date-group");
      let enable_expiration_date_checkbox = $("#edit-enable-expiration-date")
      let date_time_picker_input = $(".gofastDatetimepickerExpirationDate")

      if(is_extranet_checkbox.length != 0 && !is_extranet_checkbox.hasClass("processed")){
        is_extranet_checkbox.addClass("processed");
        // Show expiration date group only if the switch "is extranet" is enabled
        if(is_extranet_checkbox.is(":checked")){
          expiration_input_group.removeClass("d-none")
        } else {
          expiration_input_group.addClass("d-none")
        }
        // Enable expiration date input only of the switch "enable expiration date" is enabled
        if(enable_expiration_date_checkbox.is(":checked")){
          date_time_picker_input.removeAttr("disabled")
        } else {
          date_time_picker_input.val("")
          date_time_picker_input.attr("disabled", "")
        }
        // Update visibility of expiration date group when changing "is extranet" switch status
        is_extranet_checkbox.on("change", () => {
          if(is_extranet_checkbox.is(":checked")){
            expiration_input_group.removeClass("d-none")
          } else {
            expiration_input_group.addClass("d-none")
          }
        })
        // Enable / Disable input when changing status of "enable expiration date"
        enable_expiration_date_checkbox.on("change", () => {
          if(enable_expiration_date_checkbox.is(":checked")){
            date_time_picker_input.removeAttr("disabled")
          } else {
            date_time_picker_input.val("")
            date_time_picker_input.attr("disabled", "")
          }
        })

        // Put the actual value from timestamp to date as default value
        if(date_time_picker_input.length && !date_time_picker_input.hasClass("processed")){
          let timestamp = date_time_picker_input.val();
          let date_value = ""
          if(timestamp != ""){
            // Convert timestamp to well formatted string with the user date pattern
            date_value = moment.unix(timestamp).format(window.GofastConvertDrupalDatePattern("bootstrapDate").toUpperCase());
          }
          date_time_picker_input.addClass("processed")
          Gofast.user.setDateTimePickerExpirationDate(date_time_picker_input, date_value);
        }
      }
    }
  };

  Gofast.user.setDateTimePickerExpirationDate = function(element, value) {
    
    element.datetimepicker({
      locale: window.GofastLocale, 
      timepicker: false,
      format: window.GofastConvertDrupalDatePattern("bootstrapDate").toUpperCase(),
      minDate: new Date(),
      keepOpen: true,
    });

    element.val(value)
    element.on("blur", e => element.datetimepicker("hide"));
    element.on("show.datetimepicker update.datetimepicker change.datetimepicker", (e) => {
      GofastWidgetsCallbacks.dateTimePickerCallback();
    });
    
  }
  
  Gofast.user.validateUserEmail = async function(email) {
    var isValid = false;

    await $.post("/gofast/user/check/mail", {mail: email}).done((data) => {
      isValid = data.isValid
      if(!data.isValid && data.error != undefined){
        var message = "";
        var messageType = "warning";
        switch(data.error) {
          case "already exist":
            message = Drupal.t("A user with same email already exists, with username : %username", {"%username": data.login}, {context: "gofast:gofast_user"});
            messageType = "error";
            break;
          case "invalid":
            message = Drupal.t("The e-mail address %mail is not valid.", {"%mail": email}, {context: "gofast:gofast_user"});
            messageType = "error";
            break;
        }
        Gofast.toast(message, messageType);
      }
    })
    return isValid;
  }
})(jQuery, Gofast, Drupal);
