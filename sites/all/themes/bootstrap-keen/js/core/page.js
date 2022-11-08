jQuery(document).ready(function () {
  var width = jQuery("#content-main-container").width();
  var padding = 52;
  var min_width = width + padding;
  if (min_width < 1080) {
    min_width = 1080;
  }

  // Toggle the Explorer
  jQuery("#explorer-toggle").on("click", function (e) {
    if(jQuery("#explorer-forum.nav-link.active").length && jQuery(".explorer.open").length) {
        jQuery("#explorer-forum.nav-link.active").toggleClass('active');
    } else if (jQuery('.tab-pane.active#expl-forum').length && !jQuery("#explorer .nav-link.active").length && !jQuery(".explorer.open").length) {
        jQuery("#explorer-forum.nav-link").addClass('active');
    }
    jQuery(".explorer").toggleClass("open");
    jQuery("#explorer-toggle").toggleClass("open");
    
     if($("#explorer-file-browser").hasClass("active")){
            if(Gofast.ITHitMobile.memorizedPath != null){
              setTimeout(function(){          
               var memorized_path = Gofast.ITHitMobile.memorizedPath;
               Gofast.ITHitMobile.memorizedPath = null;
               Gofast.ITHitMobile.navigate(memorized_path);
              }, 500); 
            }
     }
     
     if($("#explorer-forum").hasClass("active")){
        if(Gofast.lastUrlForumTab !== ''){
          setTimeout(function(){
             Gofast.reloadForums();     
          }, 500); 
        }
     }
  });
  
    
   $("#explorer-file-browser").on('click', function(){
    if(Gofast.ITHitMobile.memorizedPath != null ){
      setTimeout(function(){          
       var memorized_path = Gofast.ITHitMobile.memorizedPath;
       Gofast.ITHitMobile.memorizedPath = null;
       Gofast.ITHitMobile.navigate(memorized_path);
      }, 500); 
    }
   })
   
    $("#explorer-forum").on('click', function(){
        if(Gofast.lastUrlForumTab !== ''){
          setTimeout(function(){
             Gofast.reloadForums();     
          }, 500); 
        }
    })

  // Toggle the Riot
  jQuery("#riot-toggle").on("click", function (e) {
    jQuery(".riot").toggleClass("open");
    jQuery("#riot-toggle").toggleClass("open");
  });

  // Sticky the NavBar
  jQuery("#main-container").on("scroll", function () {
    //console.log(jQuery(this).scrollTop());
    let scroll = jQuery(this).scrollTop();

    if (scroll > 60) {
      jQuery("#navigation").addClass("sticky");
    } else {
      jQuery("#navigation").removeClass("sticky");
    }
  });

  //Init with explorer tab in the explorer. We store forums and book values
  init_explorer_tabs();

  //  When we are viewing an article node, display the fullscreen mode after loading
  init_article_fullscreen();

  //Removes that we don't want in specific explorer tabs
  function init_explorer_tabs() {
    //File Browser
    let fb = jQuery("#file-browser")
      .find(".region-explorer")
      .find(".main-ajax-file-browser")
      .detach();
    jQuery("#file-browser").find(".region-explorer").empty();
    jQuery("#file-browser").find(".region-explorer").append(fb);

    init_disable_and_show_tabs();
  }

  function init_disable_and_show_tabs() {
    jQuery("#explorer-file-browser").addClass("active");
    // actives classes will eventually be toggled after at the module-level depending on then-given context
  }

  function init_article_fullscreen() {
    let need_fs = Gofast.Fullscreen_node;
    if (jQuery(".node-article").length && !need_fs) {
      Gofast.toggle_fitscreen();
      Gofast.success_fullscreen = true;
      Gofast.Fullscreen_node = true;
      //We change the button async since it isnt always loaded when document is ready
      setTimeout(function () {
        let button = jQuery("#toggle-fitscreen");
        button.find("i").removeClass("fa-arrows-alt").addClass("fa-compress");
      }, 2000);
    }
  }

  jQuery("#content-main-container").ajaxComplete(function () {
    init_explorer_tabs();
    init_article_fullscreen();
  });

  function triggerMobileNavigation() {
    if (
      typeof Gofast.ITHit === "undefined" ||
      Gofast.ITHit.ready === false ||
      typeof Gofast.ITHitMobile === "undefined"
    ) {
      //Not yet ready
      if (typeof Drupal.settings.pass_reset !== "undefined") {
        //We are in password recovery mode, cancel action !
        jQuery("#file_browser_mobile_container").remove();
        jQuery("#ithit-toggle").remove();
        return;
      }
      setTimeout(triggerMobileNavigation, 1000);
    } else {
      //Ready !
      if (typeof Drupal.settings.pass_reset !== "undefined") {
        //We are in password recovery mode, cancel action !
        jQuery("#file_browser_mobile_container").remove();
        jQuery("#ithit-toggle").remove();
        return;
      }
      if (!Gofast.mobileNavigationHandled) {
        //Navigation hasn't already been handled (by node themes for exemple)
        Gofast.ITHitMobile.navigate(Gofast.ITHitMobile.currentPath);
      }
      //Set drag and drop zone for upload
      if (jQuery("#file_browser_mobile_files").length !== 0) {
        Gofast.ITHit.UploaderMobile.DropZones.AddById(
          "file_browser_mobile_files"
        );
      }
      //Add events handlers for upload queue
      Gofast.ITHitMobile.attachUploadEvents();
      //Attach browser events
      Gofast.ITHitMobile.attachBrowserEvents();
      //Set margin to main container if needed
      if (
        Gofast.getCookie("mobile_browser_toggle") === "shown" &&
        parseInt(jQuery(".main-container").css("margin-left")) <= 250 &&
        parseInt(jQuery(".main-container").position().left) <= 250
      ) {
        jQuery(".main-container").css("margin-left", "250px");
      }
    }
  }
  triggerMobileNavigation();

  //Override bootstrap popover destroy function as it breaks ajaxifying
  Drupal.behaviors.bootstrapPopovers.detach = function(context, settings) {
    return;
  };
});
