

(function ($, Gofast, Drupal) {
  'use strict';


  /**
   * Init Gofast settings and globals
   *  Drupal.settings.gofast.* are initialized in gofast.js anyway.
   */
  Gofast.global = Gofast.global || {} ;
  Gofast.user = Gofast.user || {};

  Gofast.user.overProfile = false;

  // Provide a handy user object (alias for Drupal.settings.gofast.user).
  var User;

  // Settings take a while before being set. Handle init in a behavior to
  // prevent falsy fallback override.
  Drupal.behaviors.userInitSettings = {
    attach : function (context, settings) {
      Drupal.settings.gofast = Drupal.settings.gofast || {};
      Drupal.settings.gofast.user = Drupal.settings.gofast.user || {};
      User = Drupal.settings.gofast.user;
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
    user = user || User;

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
      modalContentClose();
      $("input[name='email_already_exists_confirmed']").val("1");
      $('#submit_create_user').trigger( "mousedown"); // click =event ne marche pas
  };

     Gofast.user.Unblock_user = function (Uid) {
    $.ajax({
      url : '/gofast/user/'+Uid+'/unblock',
      type : 'POST',
      success : function(data){
                  modalContentClose();
                  Gofast.processAjax('/user/' + Uid);
              }
          });
    };

  /**
   * User profile edition forms. Process states for roles checkboxes so that
   * only one non-technical role can be assigned to a user (radios would not
   * do the job for technical roles values).
   */
  Drupal.behaviors.gofastUserAdminRolesStates = {
    attach : function (context, settings) {
      var $roles = $('.user-roles-force-single input[type=checkbox]', context);
      $roles.once('single-role', function() {
        $(this).on('change', function() {
          if (this.checked) {
            $roles.not(this).not(':disabled').prop('checked', false);
          }
        });
      });

      if($('.role_administrator').is(':checked')){
        $('.field-name-is-extranet').find('input').prop('checked', false);
        $('.field-name-is-extranet').find('input').prop('disabled', true);
      }

      $('.og-roles-force-single').on('change', function(e){
        if($('#'+e.target.id).hasClass('role_administrator')){
          $('.field-name-is-extranet').find('input').prop('checked', false);
          $('.field-name-is-extranet').find('input').prop('disabled', true);
        }

        if($('#'+e.target.id).hasClass('role_contributor')){
          $('.field-name-is-extranet').find('input').prop('disabled', false);
        }
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
