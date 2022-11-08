// Toggle the Explorer
jQuery("#explorer-toggle").on('click', function(e) {
  jQuery(".explorer").toggleClass("open");
  jQuery("#explorer-toggle").toggleClass("open");
});

// Toggle the Riot
jQuery("#riot-toggle").on('click', function(e) {
  jQuery(".riot").toggleClass("open");
  jQuery("#riot-toggle").toggleClass("open");
});

// Sticky the NavBar
jQuery("#main-container").on('scroll', function() {
  //console.log(jQuery(this).scrollTop());
  let scroll = jQuery(this).scrollTop();

  if (scroll > 60) {
      jQuery("#navigation").addClass("sticky");
  }
  else {
      jQuery("#navigation").removeClass("sticky");
  }
  
});

jQuery(document).ready(function() {
  var width = jQuery('#content-main-container').width();
  var padding = 52;
  var min_width = width + padding;
  if (min_width < 1080) {
    min_width = 1080;
  }
  //jQuery('#content-main-container').css('min-width', min_width+'px');
  console.log(width);
  //Init with explorer tab in the explorer. We store forums and book values
  init_explorer_tabs();
  
  //  When we are viewing an article node, display the fullscreen mode after loading
  init_article_fullscreen();

  
  
});
  
  //Removes that we don't want in specific explorer tabs
function init_explorer_tabs() {

    //File Browser
    let fb = jQuery('#file-browser').find('.region-explorer').find('.main-ajax-file-browser').detach();
    jQuery('#file-browser').find('.region-explorer').empty();
    jQuery('#file-browser').find('.region-explorer').append(fb);

    init_disable_and_show_tabs();
}
  
function init_disable_and_show_tabs() {
    let forum_node = jQuery('.forum-post-title').length && jQuery('.forum-post-content');
    //No books to display, lock the tab
    if(jQuery('.node-article').length === 0) {
        //jQuery("#explorer-wiki").click(false);
    }else{
        jQuery('.explorer-main-container').find('.tab-pane.active').removeClass('active');
        jQuery('.explorer-main-container').find('.nav-item.active').removeClass('active');
        jQuery('#explorer-wiki').parent().addClass('active');
        jQuery('#wiki').addClass('active');
    }
    
    //No comments to display, lock the tab
    if(jQuery('.node-article').length === 0 && jQuery('.node-alfresco-item').length === 0 && jQuery('.node-webform').length === 0 && forum_node === 0) {
       // jQuery("#explorer-forum").click(false);   
    }
    
    if(forum_node !== 0) {
        jQuery('.explorer-main-container').find('.tab-pane.active').removeClass('active');
        jQuery('.explorer-main-container').find('.nav-item.active').removeClass('active');
        jQuery('#explorer-forum').parent().addClass('active');
        jQuery('#expl-forum').addClass('active');
    }
}


  
function init_article_fullscreen() {
    let need_fs = Gofast.Fullscreen_node;
    if(jQuery('.node-article').length && !need_fs) {
        Gofast.toggle_fitscreen();
        Gofast.success_fullscreen = true;
        Gofast.Fullscreen_node = true;
        //We change the button async since it isnt always loaded when document is ready
        setTimeout(function(){
            let button = jQuery('#toggle-fitscreen');
            button.find('i').removeClass('fa-arrows-alt').addClass('fa-compress');
        }, 2000)
    }
  }
  
jQuery('#content-main-container').ajaxComplete(function() {
    //console.log("OuiOuiOui");
    init_explorer_tabs();
    init_article_fullscreen();
})

jQuery('#expl-forum').find('.scrolltoanchor').click(function() {
    if(this.pathname !== window.location.pathname) {
        Gofast.addLoading();
        var GofastSettings = Drupal.settings.gofast;
        window.location.href = this;
    }
})
