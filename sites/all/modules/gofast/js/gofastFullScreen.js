(function ($, Gofast, Drupal) {
  "use strict";

  function applyIcons(fullScreenButtonIcon) {
    
    if (Gofast._settings.nodeIsFullScreenMode){
      fullScreenButtonIcon.removeClass("fa-arrows-alt");
      fullScreenButtonIcon.addClass("fa-compress");
    }else{
      fullScreenButtonIcon.removeClass("fa-compress");
      fullScreenButtonIcon.addClass("fa-arrows-alt");
    }

  }

  Gofast.configureFullScreenMode = function (fullScreenButtonIcon = null) {
    if (fullScreenButtonIcon === null){
      fullScreenButtonIcon = $("#toggle-fitscreen > i");
    }
    
    $('#breadcrumb-alt-actions > .dropdown > .dropdown-menu > .navi > .collapsed' +
        ' > div > .navi-link').removeClass('flex-row-reverse');
    $('#breadcrumb-alt-actions > .dropdown > .dropdown-menu > .navi > .collapsed' +
        ' > div > .navi-link > .navi-icon > i').removeClass('fa-arrow-right').addClass('fa-arrow-left');
    $('#breadcrumb-alt-actions > .dropdown > .dropdown-menu > .navi > .collapsed')
        .find('.dropdown > .dropdown-menu').addClass('dropleft')
   
    applyIcons(fullScreenButtonIcon);
  }

  Gofast.toggleFullScreen = function () {
    if ($("#toggle-fitscreen").length) {
      let cnt = $(".fullScreen");
      let fullScreenButtonIcon = $("#toggle-fitscreen > i");
      let sideBar = $(".sideContent");
      if(sideBar.length && !Gofast._settings.isEssential){
        sideBar.toggleClass("d-none");
      }
      cnt.toggleClass("active");
      if (cnt.hasClass("active")) {
        Gofast._settings.nodeIsFullScreenMode = true;
        applyIcons(fullScreenButtonIcon)
      } else {
        Gofast._settings.nodeIsFullScreenMode = false;
        applyIcons(fullScreenButtonIcon)
      }
    }
    if(Gofast._settings.isEssential && $("#fullscreenNavigationButtons").length){
      if($("#fullscreenNavigationButtons").css("display") == "none"){
        $("#node-full-screen-button").click()
        Gofast._settings.nodeIsFullScreenMode = true
      } else {
        $("#node-normal-screen-button").click()
        Gofast._settings.nodeIsFullScreenMode = false
      }
    }
  };
  

  Drupal.behaviors.gofastFullScreen = {
    attach: function (context, settings) {
      let btn = document.querySelector("#toggle-fitscreen:not(.processed)");
      if (btn != undefined) {
        btn.classList.add("processed");
        btn.addEventListener("click", Gofast.toggleFullScreen);
      }
    },
  };
})(jQuery, Gofast, Drupal);
