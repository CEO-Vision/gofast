(function ($, Drupal, Gofast) {
  "use strict";
  Drupal.behaviors.initSideBarMobile = {
    attach: function (context) {
      function showMobilePanel() {
        $("#gofast_mobile_panel").css("right", "");
        $("#gofast_mobile_arrow").css(
          "right",
          $("#gofast_mobile_panel").width()
        );

        // if tablet
        if (Gofast.isTablet() || Gofast.isMobile()){
          $("#gofast_mobile_panel").css("overflow", "unset");
          $("#gofast_mobile_arrow").css("z-index", 1);
        }

        $("#gofast_mobile_arrow span")
          .removeClass("glyphicon-menu-left")
          .addClass("glyphicon-menu-right");
      }

      function hideMobilePanel() {
        $("#gofast_mobile_panel").css(
          "right",
          -$("#gofast_mobile_panel").width()
        );
        $("#gofast_mobile_arrow").css("right", "");

        // if tablet
        if (Gofast.isTablet() || Gofast.isMobile()) {
          $("#gofast_mobile_panel").css("overflow", "auto");
        }

        $("#gofast_mobile_arrow span")
          .removeClass("glyphicon-menu-right")
          .addClass("glyphicon-menu-left");
      }

      function resizeOnOrientationChange() {
        $("#gofast_mobile_arrow").css({
          top:
            ($("#gofast_mobile_panel").height() -
              $("#gofast_mobile_arrow").height()) /
            2,
        });

        if ($("#gofast_mobile_arrow span").hasClass("glyphicon-menu-right")) {
          // Panel is being shown
          showMobilePanel();
        } else {
          hideMobilePanel();
        }
      }

      $("#gofast_mobile_panel").css("top", $("header").height());
      if (!$("#gofast_mobile_arrow").hasClass("gofast-processed")){
        hideMobilePanel();
        $("#gofast_mobile_arrow").addClass("gofast-processed");
      }

      $("#gofast_mobile_arrow").css({
        top:
          ($("#gofast_mobile_panel").height() -
            $("#gofast_mobile_arrow").height()) /
          2,
      });

      setTimeout(function () {
        $("#gofast_mobile_panel, #gofast_mobile_arrow").css(
          "visibility",
          "visible"
        );
      }, 1000);

      $("div#gofast_mobile_arrow").swipe({
        threshold: 20,
        tap: function (e) {
          if ($(this).find("span").hasClass("glyphicon-menu-left")) {
            showMobilePanel();
          } else if ($(this).find("span").hasClass("glyphicon-menu-right")) {
            hideMobilePanel();
          }
        },
        swipeRight: function (e) {
          hideMobilePanel();
        },
        swipeLeft: function (e) {
          showMobilePanel();
        },
      });

      // Listen for orientation changes

      $(window).on("orientationchange, resize", function (e) {
        resizeOnOrientationChange();
      });
    },
  };
})(jQuery, Drupal, Gofast);
