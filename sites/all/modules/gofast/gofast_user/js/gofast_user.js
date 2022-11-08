

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
          manager: {field: "ldap_user_manager", placeholder: "Your manager"},
          description: {field: "ldap_user_description", placeholder: "Description"},
          skills: {field: "field_skills", placeholder: "Your skills"},
          interests: {field: "field_interests", placeholder: "Your interests"},
          hobbies: {field: "field_hobbies", placeholder: "Your hobbies"},
        },

        // update callback
        userProfileUpdate: async function (userId, field, value) {
          let formData = new FormData();
          // we don't forget to translate the DTO field into a Drupal user form field
          formData.append("pk", userId);
          formData.append("name", this.dtoFieldToUserFormFieldMap[field].field);
          formData.append("value", value);
          // we don't change the backend logic to avoid breaking other stuff relying on it
          if (field === "birthdate") {
            formData.append("date_str", (new Date(value)).getTime());
          }
          if (field === "manager") {
            if(value !== undefined){
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
          // we pass the update callback inside the generic GofastEditableInput pseudo-constructor
          let userEditableInputProps = {
            save: (newData) => {
              if (newData !== this.initialValue) {
                const response = this.userProfileUpdate(
                  this.userId,
                  this.field,
                  newData
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
        $(this).addClass('switch switch-icon font-size-h6');
      });

      $('.og-roles-force-single:not(".processed")').addClass('processed').on('change', function(e){
        if($('#'+e.target.id).hasClass('role_administrator')){
          $('.field-name-is-extranet').find('input').prop('checked', false);
          $('.field-name-is-extranet').find('input').prop('disabled', true);
        }

        if($('#'+e.target.id).hasClass('role_contributor')){
          $('.field-name-is-extranet').find('input').prop('disabled', false);
        }
        
        // Check if single role is selected
        var item_checked = $('.og-roles-force-single .form-checkbox:checked');
        // if item is empty disabled submit button and add message to the right
        if(item_checked.length == 0){
          $('.form-submit').prop('disabled', true);
          $('.form-submit').addClass('disabled');
          if($('.form-item-submit-message') != undefined){
            $('#modal-footer #edit-submit').after('<div class="form-item form-type-textfield form-item-submit-message"><i class="fas fa-exclamation-triangle mr-2" style="color:#FFA800"></i>'+ Drupal.t('Please select at least one role') +'</div>');
          }
        }else{
          $('.form-submit').prop('disabled', false);
          $('.form-submit').removeClass('disabled');
          $('.form-item-submit-message').remove();
        }
        
      });
    }
  };
  
   Drupal.behaviors.gofastUserFormMailCheck = {
    attach : function (context, settings) {
      var $input_mail = $('#user-register-form #edit-mail', context);
      $input_mail.once('check_mail_processed', function() {
        $(this).on('blur', function() {
            // we do nothing if we don't have a valid email
            if (!/^[a-zA-Z0-9.!#$%&'*+/=?^_`{|}~-]+@[a-zA-Z0-9-]+(?:\.[a-zA-Z0-9-]+)*$/.test($(this).val())) {
              return;
            }
            var current_domain = window.location.hostname.replace(/^[^.]+\./g, "");
            var mail_domain = $(this).val().split('@').pop();
            if(current_domain !== mail_domain){             
                $("#edit-sasl-auth-und").prop("checked", false );             
                $('#user-register-form input[type="password"]').prop('disabled', false);
                $('#user-register-form .form-item-select-pass').toggle(300);
                $("input[name*='is_extranet']").prop("checked", true );
            }
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

})(jQuery, Gofast, Drupal);
