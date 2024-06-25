(function ($, Gofast, Drupal) {

    Drupal.behaviors.loadSettingsGeneral = {
        attach: function(context, settings){   

            //Load general settings by default
            if($('#gofastSettingsTabs').not('.processed').length){
                $('#gofastSettingsTabs').addClass('processed'); 

                //Bind click events to all the tabs to load their content asynchronously;
                const settingsTabIds = ["edit-general", "edit-smtp", "edit-rssfeed", "edit-ldap", "edit-users", "edit-documents", "edit-spaces", "edit-sso", "edit-visibility", "edit-indexing", "edit-integrity", "edit-categories", "edit-custom-link", "edit-signature", "edit-signature-digitalsign", "edit-pastell","edit-esup", "edit-tags", "edit-webhook", "edit-bluemind"];
                for (const settingsTabId of settingsTabIds) {
                    $('html').on('click', '#gofastSettingsTabs .' + settingsTabId + ':not(".active")', function(){
                      let dataFormId = $(this).data("form-id");
                      loadSettingsTab(settingsTabId, dataFormId);
                    });
                    
                }
                $('html').on('click', '#gofastSettingsTabs .edit-update:not(".active")', function(){Gofast.processAjax("/admin/config/gofast/update");});

                //load first displayed tab
                if ($("#gofastSettingsTabs .nav-link[href=\"" + window.location.hash +"\"]").length) {
                    $("#gofastSettingsTabs .nav-link[href=\"" + window.location.hash +"\"]").click();
                } else {
                    $("#gofastSettingsTabs a").first().click();
                }
            }

            //Hide irrelevant inputs when needed
            Gofast.displayTargetsBySourceCheckbox(".form-item-has-custom-link", [".form-item-custom-link-label", ".form-item-custom-link-link"]);
            Gofast.displayTargetsBySourceCheckbox(".form-item-disable-login", [".form-item-disable-password-reset > label", ".form-item-disable-password-reset > div"]);
            Gofast.displayTargetsBySourceCheckbox(".form-item-has-signature-background", [".form-item-files-signature-background"]);
        }
    };

    Drupal.behaviors.processCategories = {
        attach: function(context, settings){
            var form = $("#gofast-admin-category-settings-form");
            if(form.length > 0 && ! form.hasClass('processed')){
                form.addClass('processed');

                //Hide unwanted tabs
                form.find('fieldset[id^="edit-add-edit-"]').not('#edit-add-edit-0').hide();

                //Bind events on dropdown
                form.find('select#edit-add-edit-action').change(function() {
                    var selectedValue = parseInt($(this).val());

                    //Hide other fieldsets
                    form.find('fieldset[id^="edit-add-edit-"]').hide();

                    //Display corresponding fieldset
                    var fieldset = form.find('#edit-add-edit-' + selectedValue);
                    fieldset.show();
                });
            }
        }
    };

    // Here the content of the tab is fetched and attached to the matching div
    Gofast.loadSettingsTab = function(tab){
        loadSettingsTab(tab);
    };

    Gofast.displayTargetsBySourceCheckbox = function(sourceCheckboxSelector, targetsSelectors) {
        if (!$(sourceCheckboxSelector)) {
            return;
        }
        let sourceCheckbox = $(sourceCheckboxSelector + " input");
        // Hide the input on form load if needed
        if (!$(sourceCheckbox).prop("checked")) {
            for(const targetSelector of targetsSelectors) $(targetSelector).addClass("d-none");
        }
        // Hide/unhide the input on checkbox change
        $(sourceCheckbox).on("change", () => {
            if ($(sourceCheckbox).prop("checked")) {
                for(const targetSelector of targetsSelectors) $(targetSelector).removeClass("d-none");
            } else {
                for(const targetSelector of targetsSelectors) $(targetSelector).addClass("d-none");
            }
        });
    }

  function loadSettingsTab(tab, formID = null) {
    // Container
    var container = $("#gofastAdminTabContent");
    var spinner   = $('.loader-settings');
    
    // Function to hide all children except the one with a specific id
    var hideAllExcept = function(id) {
      container.children().each(function () {
        if ($(this).attr('id') !== id+'-container') {
          $(this).css('display', 'none');
        } else {
          $(this).css('display', 'block');
        }
      });
    }

    if (formID !== null) {
      var potentialForm = $('#' + formID);
      // If form is already present in the DOM
      if (potentialForm.length) {
        hideAllExcept(formID);
        return;
      }
    }

    hideAllExcept(formID);
    // add spinner
    spinner.show();
    // Only fetch new form via AJAX if there is no formID or if it's not found in DOM
    $.post(location.origin + "/admin/config/gofast/global/getform/" + tab, function (output) {

      if (formID !== null) {
        // Check if the form container already exists in the DOM
        var existingContainerEl = $(`#${formID}-container`);

        // If the form container does not exist, then append it
        if (existingContainerEl.length === 0) {
          var containerEl = $(`<div id="${formID}-container"></div>`)
          var form = JSON.parse(output)['html'];
          var newForm = $(form);

          spinner.hide();
          containerEl.append(newForm);
          container.append(containerEl);
          Drupal.attachBehaviors();
          attachSettingsFormAjax(container, "#gofastAdminTabContent");
        }
      }
    });
  }
    // event listener to ajaxify the form submission
    function attachSettingsFormAjax(container, tab){
        $(container).find('form').submit(function(event) {
            //Submit this form in ajax
            event.preventDefault();
            var form = $(this);
            Gofast.addLoading();
            $.ajax({
                type: form.attr('method'),
                url: form.attr('action'),
                data: new FormData(this),
                processData: false,
                contentType: false,
            }).done(function(data) {
                try{
                    var html = JSON.parse(data)['html'];
                }catch(e){
                    Gofast.toast(data, 'error');
                    Gofast.removeLoading();
                }
                
              var new_container = $(tab).html(html);
              new_container.find("form[id]").each(function() {
                var currentId = $(this).attr("id");
                $(this).attr("id", currentId + "-container");
              });
              attachSettingsFormAjax(new_container, tab);
              Drupal.attachBehaviors();
              var errors = JSON.parse(data)['error'];
                if(errors === null){
                    Gofast.toast(Drupal.t('Your configuration has been saved.'), 'success');
                }else{
                    $.each(errors, function(k, error){
                        Gofast.toast(error, 'error');
                    });
                }
                Gofast.removeLoading();
            }).fail(function(data) {
                Gofast.toast(data, 'error');
                Gofast.removeLoading();
            });
        });
        if (document.querySelector(".uppy-Root")) window.initFileInput({maxFileSize: 1000000, maxNumberOfFiles: 1, allowedFileTypes: ["image/*"]}, true);
    }
  
    Gofast.removeActiveClassFromTabs = function () {
        $(".navi-link").not(this).removeClass("active");
    };
  
    /**
     * Binds LDAP 'Test connection' button to a connection attempt that returns
     * connection + binding status.
     */
    Drupal.behaviors.gofastLDAPConnectionTest = {
        attach: function (context, settings) {
            if($('#ldap-connection-test').length == 0){
                return;
            }
            $('#ldap-connection-test', context).once('ldap-connect', function () {
                $(this).on('click', function () {
                    var serverProperties = {},
                    serverPropList = ["sid", "name", "ldap_type", "address", "port", "tls", "followrefs", "binding_service_acct", "binddn", "bindpw", "basedn"],
                    ldapAdminForm = $(this).closest('form');

                    serverPropList.forEach(function (prop, i) {
                        var element = $('[name="' + prop + '"]', ldapAdminForm),
                        type = element.length && element.get(0).type || '',
                        check = {checkbox: 1, radio: 1},
                        value = type in check ? element.prop('checked') && 1 || 0 : element.val();

                        // Prevents sending undefined values to let server fallback with
                        // its own defaults.
                        if (typeof value !== undefined) {
                            serverProperties[prop] = value;
                        }
                    });

                    $.ajax({
                        type: 'POST',
                        url: '/admin/config/gofast/ldap/test-connection',
                        data: {ldapConnectionTest: serverProperties},
                        dataType: 'json',
                        'beforeSend': function (xhr) {
                            Gofast.xhrPool = Gofast.xhrPool || {};
                            Gofast.xhrPool.xhrTestLdapConnection = xhr;  // before jQuery send the request we will add it into our object
                        },
                        'complete': function () {
                            delete Gofast.xhrPool.xhrTestLdapConnection;
                        },
                        error: function (response) {
                            console.log(response);
                        },
                        success: function (response) {
                            console.log('success');
                            var statusEl = $('#ldap-connection-status');
                            response.connectionStatus === true ?
                            statusEl.css({color: 'green'}).html(Drupal.t('Connection performed successfully.', {}, {'context' : 'gofast:gofast_ldap'})) :
                                    statusEl.css({color: 'red'}).html(Drupal.t('Connection failed.', {}, {'context' : 'gofast:gofast_ldap'}));
                        }
                    });
                });
            });
        }
    };

    /**
     * Button to force synchronization
     */
    Drupal.behaviors.forceSynch = {
        attach: function (context, settings) {
            if($('#edit-force-sync').length == 0){
                return;
            }
            $('#edit-force-sync', context).once('synchronize', function () {
                $(this).on('click', function (e) {
                    e.preventDefault();
                    Gofast.addLoading();
                    $.post( "/gofast/variable/set", { name: "gofast_ldap_last_sync", value: "1" }).done(function( data ) {
                        $('#gofast-admin-ldap-settings-form').submit();
                    });
                });
            });
        }
    };
})(jQuery, Gofast, Drupal);

