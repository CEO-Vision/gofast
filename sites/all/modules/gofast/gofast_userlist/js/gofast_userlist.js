(function ($, Gofast, Drupal) {
  "use strict";

  Gofast.userlist = Gofast.userlist || {};

  Gofast.userlist.showPopup = function (elt) {
    Gofast.userlist.overPopup = true;

    var ulid = $(elt).data("ulid");
    var url,
      ogContext = Drupal.settings.ogContext,
      popup = $(elt).parent().find(".userlist-location-popup"),
      throbber =
        '<i aria-hidden="true" class="icon glyphicon glyphicon-refresh glyphicon-spin"></i>';

    //before loading hide all popup already displayed
    $("#edit-userlists")
      .find(".userlist-location-popup>.details")
      .children()
      .remove();

    url = "/userlist/location_popup/" + ulid;
    if (ogContext && ogContext.groupType === "node" && ogContext.gid) {
      url += "/" + ogContext.gid;
    }

    $.ajax({
      url: url,
      dataType: "html",
      beforeSend: function (xhr) {
        Gofast.xhrPool = Gofast.xhrPool || {};
        Gofast.xhrPool.xhrShowPopup = xhr;
      },
      complete: function () {
        delete Gofast.xhrPool.xhrShowPopup;
      },
      success: function (response) {
        if (Gofast.userlist.overPopup === true) {
          popup.find(".details").html(response);
          Drupal.attachBehaviors();
        }
      },
    });
  };

  Gofast.userlist.hidePopup = function (elt) {
    Gofast.userlist.overPopup = false;
    $(elt)
      .parent()
      .find(".userlist-location-popup>.details")
      .children()
      .remove();
  };

  Drupal.behaviors.gofastUserListPopup = {
    attach: function (context, settings) {
      var config = {
        sensitivity: 7,
        interval: 100,
        over: Gofast.userlist.showPopup,
        timeout: 0,
        out: Gofast.userlist.hidePopup,
      };
      $(".userlist-location-popup:not(.gofast-popup-processed)")
        .addClass("gofast-popup-processed")
        .each(function () {
          $(this).hoverIntent(config);
        });
    },
  };

  Gofast.load_userlist_profile_spaces = function(){
    var profile_ulid = $('#gf_userlist_groups').data('profileulid');
      $.ajax({
        'type': "POST",
        'url': '/gofast/userlist/'+profile_ulid+'/groups',
        'data': {},
        'success': function (data) {

            var parser = new DOMParser();
            var el = parser.parseFromString(data, "text/html");
            var groups = $(el).find('table.profile-info-table');

            $(document).find('#gf_userlist_groups').html(groups);


            var ua = navigator.userAgent;
            /* MSIE used to detect old browsers and Trident used to newer ones*/
            var is_ie = ua.indexOf("MSIE ") > -1 || ua.indexOf("Trident/") > -1;
            if(is_ie != true){
                jQuery('.profile-groups>div').mCustomScrollbar({theme: 'dark-thin'});
                jQuery('.profile-organisations>div').mCustomScrollbar({theme: 'dark-thin'});
                jQuery('.profile-public>div').mCustomScrollbar({theme: 'dark-thin'});
                jQuery('.profile-extranet>div').mCustomScrollbar({theme: 'dark-thin'});
                jQuery('.profile-userlists>div').mCustomScrollbar({theme: 'dark-thin'});
                jQuery('.mCustomScrollbar').css('overflow-y','hidden');
            }
        }
      });
  };
})(jQuery, Gofast, Drupal);