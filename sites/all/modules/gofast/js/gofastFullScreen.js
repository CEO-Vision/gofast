(function ($, Gofast, Drupal) {
  "use strict";

  Gofast.toggleFullScreen = function () {
    if (!document.querySelector("#toggle-fitscreen")) {
      return;
    }
    let cnt = document.querySelector(".fullScreen");
    let fullScreenButtonIcon = document.querySelector("#toggle-fitscreen > i");
    let sideBar = document.querySelector(".sideContent");
    if(sideBar != 'undefined' && sideBar != null){
      sideBar.classList.toggle("d-none");
    }
    cnt.classList.toggle("active");
    if (cnt.classList.contains("active")) {
      fullScreenButtonIcon.classList.remove("fa-arrows-alt");
      fullScreenButtonIcon.classList.add("fa-compress");
      return;
    }
    fullScreenButtonIcon.classList.remove("fa-compress");
    fullScreenButtonIcon.classList.add("fa-arrows-alt");
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
