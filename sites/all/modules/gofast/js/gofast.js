
/**
 * @file
 *  Provides GoFast Essential front-end functionalities.
 *
 *  This file is part of the Gofast main library and is loaded on every page.
 *  Do not insert code that has to be run on specific page.
 */

(function ($, Gofast, Drupal) {
  'use strict';

  /**
   * Init Gofast settings and globals
   */
  Gofast.global = Gofast.global || {};
  window.CKEDITOR_BASEPATH = "/sites/all/libraries/ckeditor/";
  Gofast.exclude_ajax_url = [];
  Gofast.additionalGFBNodes = [];

    Drupal.behaviors.gofastBootstrapSwitchInit = {
    attach: function(context, settings){
       var checked = $("#edit-prevent-notify-update").attr("checked");
       if(checked == "checked"){
           var state = true;
       }else{
           var state = false;
       }

        $("#edit-prevent-notify-update").bootstrapSwitch({'state' : state, 'handleWidth': 20, 'labelText' : "Notification" });
        if(!$("#edit-prevent-notify-update").hasClass("bootstrap-switch-processed")){
            $('#edit-prevent-notify-update').on("switchChange.bootstrapSwitch", function (event, state) {
                Gofast.preventNotifyToggle();
            });
            $('#edit-prevent-notify-update').addClass("bootstrap-switch-processed");
        }

      var checked_search = $("#edit-strict_search-update").attr("checked");

       if(checked_search == "checked"){
           var state = true;
       }else{
           var state = false;
       }

        $("#edit-strict_search-update").bootstrapSwitch({'state' : state });
        if(!$("#edit-strict_search-update").hasClass("bootstrap-switch-processed")){
            $('#edit-strict_search-update').on("switchChange.bootstrapSwitch", function (event, state) {
                Gofast.StrictSearchToggle();
            });
            $('#edit-strict_search-update').addClass("bootstrap-switch-processed");
        }
    }
  };

  Drupal.behaviors.hideSelectVersionLoginIfMobileTablette = {
    attach: function (context, settings) {
      if (Gofast.isTablet() || Gofast.isMobile()) {
        $('#edit-simplified-login').hide();
        $('#edit-submit').width('100%');
      }
    }
  };

  Drupal.behaviors.hideNodeInfos = {
      attach: function(context, settings){
        if(window.location.href == Drupal.settings.gofast.baseUrl+'/'){
            $('#block-gofast-gofast-node-infos').hide();
        }
        if(!Drupal.settings.isMobile){
            $("#pdf_frame").contents().find("#gfPresentationMode").hide();
        }
    }
  };

  Drupal.behaviors.gofastStatus = {
      attach: function(context, settings){
        if(!Gofast.statusPolling){
          Gofast.statusPolling = true;
          statusPoll(true);
        }
    }
  };


  Drupal.behaviors.initRenanmeOgOnMobile = {
    attach: function () {
      if (jQuery(".mobile-rename-node").length > 0) {
        //Allow to rename the node
        jQuery(".panel.panel-info").find('.panel-heading').click(function () {
          jQuery("#panel-heading-title").hide();
          jQuery("#panel-heading-title-edit").show();
        });

        jQuery('#panel-heading-title-edit').find('.btn-danger').click(function (e) {
          jQuery("#panel-heading-title").show();
          jQuery("#panel-heading-title-edit").hide();
          e.stopPropagation();
        });

        jQuery('#panel-heading-title-edit').find('.btn-success').click(function (e) {
          jQuery("#panel-heading-title").show();
          jQuery("#panel-heading-title-edit").hide();
          jQuery("#panel-heading-title").html("<div class='loader-deleting'></div>");
          var title = jQuery("#panel-heading-title-edit").find('input').val();

          jQuery.post(location.origin + "/update_node_field", {
            name: "title",
            pk: Gofast.get('node').id,
            value: title
          }, function () {
            location.reload();
          });
          e.stopPropagation();
        });
      }
    }

  }

  Gofast.gofastOpenRenameInputOnMobile = function () {
    jQuery("#panel-heading-title").hide();
    jQuery("#panel-heading-title-edit").show();
  }

 Gofast.gofast_onlyoffice_show_warning = function (link, e) {
             var link_display = link;
             var html_message = "<h2>"+Drupal.t("Warning" , {}, {'context' : 'gofast'})+"</h2>";
             html_message = html_message + "<div>"+Drupal.t("Use OnlyOffice on doc, xls or ppt (or equivalent in Open formats) files will automatically convert it into docx, xlsx or pptx, and this can alter the formatting of the document. If you do not want to transform the format, please use Word or LibreOffice by choosing <b>Edit from my PC</b>." , {}, {'context' : 'gofast'})+"</div>";
             html_message = html_message + "<br /><div><a href=\""+link_display+"\" target=\"_blank\" class='gofast-callto'><button onClick='Gofast.closeModal();' class='btn btn-success'>"+Drupal.t("Continue" , {}, {'context' : 'gofast'})+"</button></a>";
             //html_message = html_message + "<input style='margin-left:10px;margin-right:6px;' type='checkbox' id='onlyoffice_warning_display' value='onlyoffice_warning_display' />"+Drupal.t("Hide this warning in the futur" , {}, {'context' : 'gofast'});
             html_message = html_message + "</div>";
             Gofast.modal(html_message, Drupal.t("Edit with OnlyOffice" , {}, {'context' : 'gofast'}));
             e.stopPropagation();
  }

    Gofast.gofast_refresh_fast_actions_node = function (nid) {
       $.get(location.origin + "/gofast/node-actions/"+nid, {}, function( data ) {
           $("#breadcrumb-alt-actions").replaceWith(data);
           Drupal.attachBehaviors();
      });
  }

  function statusPoll(){
    return;
    $.ajax({
        url : Drupal.settings.gofast.baseUrl+'/gofast/status',
        type : 'GET',
        dataType: 'html',
        success : function(content, status){
          $(".gofast-status-btn").remove();
          $("#platform-status").remove();
          if(content !== ""){ //Status to display
            $('#navbar').append('<div class="visible-lg gofast-status-btn"><i style="color: #8b7132;font-size: 1.7em;margin-top: 4px;" class="fa fa-exclamation-triangle fa-2x" aria-hidden="true"></i></div>');
            $('#navbar').append('<div id="platform-status">' + content + '</div>');
          }
        },
      });
    setTimeout(statusPoll, 15000);
  }

  Drupal.behaviors.permalinkToClipBoard = {
    attach: function (context, settings) {
      //$('.view-gofast-activity-feed a').addClass('ajax-link');

      $('.forum-post-number a', context).once('permalink', function (e) {
        $(this).attr({
          'data-toggle': 'tooltip',
          'data-placement': 'right',
          'title': Drupal.t('Copy to clipboard', {}, {'context' : 'gofast'})
        }).click(function (e) {
          e.preventDefault();
          // Make sure the permalink has an absolute url.
         /* var basePath = History.getBaseUrl() + Drupal.settings.basePath,
                  pattern = new RegExp('^(?:\/|' + basePath + ')'),
                  permalink = basePath + $(this).attr('href').replace(pattern, '');*/
        var url_relative = $(this).attr('href').replace(Gofast.get('baseUrl'), "");
          Gofast.copyToClipboard(Gofast.get('baseUrl') + url_relative);
          $('body').click();
          return false;
        });
      });
      // Attr title without tooltips bootstrap
      $('.permalink', context).once('permalink', function (e) {
        $(this).attr({
           'title' : Drupal.t('Copy to clipboard', {}, {'context' : 'gofast'})
        }).click(function (e) {
          e.preventDefault();
        var url_relative = $(this).attr('href').replace(Gofast.get('baseUrl'), "");
          Gofast.copyToClipboard(Gofast.get('baseUrl') + url_relative);
          $('body').click();
          return false;
        });
      });
    }
  };

  Drupal.behaviors.initializeCustomScrollbar = {
    attach: function (context, settings) {
      Gofast.initializeCustomScrollbar();
    }
  };

  Gofast.initializeCustomScrollbar = function () {
    if(typeof Gofast.get("user") != "undefined"){
        if (Gofast.get("user").uid !== 0) {
            if($('#modalContent').length === 0){
                $('.region-sidebar-second:not(#gofast_mobile_panel .region-sidebar-second)').css({
                  'height': $(window).height() - 100,
                  'position': 'fixed'
                }).mCustomScrollbar({
                  axis: 'y',
                  theme: 'dark',
                  horizontalScroll: false,
                  scrollInertia: 0,
                  mouseWheelPixels: 40,
                  scrollButtons: {
                    enable: true,
                    scrollType: "continuous",
                    scrollSpeed: 25
                  },
                  advanced: {
                    updateOnBrowserResize: false,
                    updateOnContentResize: true
                  },
                  callbacks: {
                    onScroll: function () {
                      //trigger xeditable cancel button to close popover when scroll on mobile and tablet only
                      if ($(".editable-cancel").length && (Gofast.isMobile() || Gofast.isTablet())) {
                        $(".editable-cancel").click();
                      }
                    }
                  }
                }).css({
                  'width': 'initial',
                  'min-width': '180px',
                  'max-width': '400px',
                });

                $('.region-sidebar-second:not(#gofast_mobile_panel .region-sidebar-second) .mCSB_draggerContainer').css('padding-bottom', 0);
                $(window).resize(function () {
                  $('.region-sidebar-second:not(#gofast_mobile_panel .region-sidebar-second)').css('height', $(window).height() - 100);
                  $('.region-sidebar-second:not(#gofast_mobile_panel .region-sidebar-second)').mCustomScrollbar('update');
                });

              if (Gofast._settings.isMobile == true && Gofast.isMobile() == true){
                  jQuery('.region-sidebar-second:not(#gofast_mobile_panel .region-sidebar-second)').css('max-width', '80%');
                  $('.region-sidebar-second:not(#gofast_mobile_panel .region-sidebar-second)').css('height', "95%");
                } else if (Gofast._settings.isMobile == true && Gofast.isTablet() == true){
                  $('.region-sidebar-second:not(#gofast_mobile_panel .region-sidebar-second)').css('height', "95%");
                }
            }
          }
    }
  };


  /**
 * Ajax callback to show confirm form to restart a service
 */
 Gofast.dashboardStopConfirm = function (service) {
    var sentence_confirmation = Drupal.t('Are you sur you want to stop this service ?', {}, {'context' : 'gofast'});
    var html_content = sentence_confirmation+"<br /><input type='button' class='btn btn-info btn-sm' onClick='Gofast.dashboardRestart(\""+service+"\", \"stop\");' value='"+Drupal.t('Stop', {}, {'context' : 'gofast'})+"'/>";
    Gofast.modal(html_content, Drupal.t('Stop service', {}, {'context' : 'gofast'})+" "+service);
 };
 /**
 * Ajax callback to show confirm form to restart a service
 */
 Gofast.dashboardRestartConfirm = function (service) {
    var sentence_confirmation = Drupal.t('Are you sur you want to restart this service ?', {}, {'context' : 'gofast'});
    var html_content = sentence_confirmation+"<br /><input type='button' class='btn btn-info btn-sm' onClick='Gofast.dashboardRestart(\""+service+"\", \"restart\");' value='"+Drupal.t('Restart', {}, {'context' : 'gofast'})+"'/>";
    Gofast.modal(html_content, Drupal.t('Restart service', {}, {'context' : 'gofast'})+" "+service);
 };

 /**
 * Ajax callback to show confirm form to disable auto-restart
 */
 Gofast.dashboardDisableARConfirm = function (service) {
    var sentence_confirmation = Drupal.t('Are you sur you want to disable auto-restart for this service ?', {}, {'context' : 'gofast'});
    var html_content = sentence_confirmation+"<br /><input type='button' class='btn btn-info btn-sm' onClick='Gofast.dashboardRestart(\""+service+"\", \"disableAR\");' value='"+Drupal.t('Disable auto-restart', {}, {'context' : 'gofast'})+"'/>";
    Gofast.modal(html_content, Drupal.t('Disable auto-restart', {}, {'context' : 'gofast'})+" "+service);
 };

  /**
 * Ajax callback to show confirm form to disable auto-restart
 */
 Gofast.dashboardEnableARConfirm = function (service) {
    var sentence_confirmation = Drupal.t('Are you sur you want to enable auto-restart for this service ?', {}, {'context' : 'gofast'});
    var html_content = sentence_confirmation+"<br /><input type='button' class='btn btn-info btn-sm' onClick='Gofast.dashboardRestart(\""+service+"\", \"enableAR\");' value='"+Drupal.t('Enable auto-restart', {}, {'context' : 'gofast'})+"'/>";
    Gofast.modal(html_content, Drupal.t('Enable auto-restart', {}, {'context' : 'gofast'})+" "+service);
 };

/**
 * Ajax callback to show confirm form to restart a service
 */
 Gofast.dashboardRestart = function (service, action) {
   if(action == "restart"){
        $.ajax({
                           url:"/gofast/dashboard/restart?service="+service,
                           type: "GET",
                           dataType:'json',
                           success:function(response){
                             if(response == "OK"){
                                 var html_content = Drupal.t('The service will be restarted in few minutes', {}, {'context' : 'gofast'});
                                 Gofast.modal(html_content, Drupal.t('Restart service', {}, {'context' : 'gofast'}));
                             }else{
                                 var html_content = Drupal.t('An error occured', {}, {'context' : 'gofast'});
                                 Gofast.modal(html_content, Drupal.t('Error', {}, {'context' : 'gofast'}));
                             }
                           }
                         });
  }else if(action == "stop"){
         $.ajax({
                           url:"/gofast/dashboard/stop?service="+service,
                           type: "GET",
                           dataType:'json',
                           success:function(response){
                             if(response == "OK"){
                                 var html_content = Drupal.t('The service will be stopped in few minutes', {}, {'context' : 'gofast'});
                                 Gofast.modal(html_content, Drupal.t('Stop service', {}, {'context' : 'gofast'}));
                             }else{
                                 var html_content = Drupal.t('An error occured', {}, {'context' : 'gofast'});
                                 Gofast.modal(html_content, Drupal.t('Error', {}, {'context' : 'gofast'}));
                             }
                           }
                         });
  }else if(action == "enableAR" || action == "disableAR"){
         $.ajax({
                           url:"/gofast/dashboard/autorestart?service="+service+"&action="+action,
                           type: "GET",
                           dataType:'json',
                           success:function(response){
                             if(response == "OK"){
                                 if(action == "enableAR"){
                                    var html_content = Drupal.t('The AR is now enabled for this service', {}, {'context' : 'gofast'});
                                 }else if(action == "disableAR"){
                                    var html_content = Drupal.t('The AR is now disabled for this service', {}, {'context' : 'gofast'});
                                 }
                                 Gofast.modal(html_content, Drupal.t('Auto restart', {}, {'context' : 'gofast'}));
                             }else{
                                 var html_content = Drupal.t('An error occured', {}, {'context' : 'gofast'});
                                 Gofast.modal(html_content, Drupal.t('Error', {}, {'context' : 'gofast'}));
                             }
                           }
                         });
  }
 };

  /**
   * Update status/warning/error messages. To use in ajax callbacks.
   */
  Gofast.updateStatusMessages = function (data) {
    // We don't use replaceWith() to prevent multiple replacements (one for each
    // previous instance of '.alert').
    var el = $('.alert:first').prev() || $('.page-header');
    $('.alert').remove();
    el.after(data);
  };

   /*Gofast.setMemorizedPath = function (path) {
    Gofast.setCookie('memorize_last_url_ajax_file_browser', encodeURIComponent(path), 31536000);
    //TODO understand why ithit-state-hidden doesn't work
    if(typeof Gofast.ajaxFileBrowser !== 'undefined' && ! $('#ithit-toggle').hasClass('ithit-state-hidden2')){
      //console.log('Update ITHIT mobile location');
      if(typeof Gofast.ajaxFileBrowser.SetSelectedFolderAsync == 'function'){

        if( Gofast.ajaxFileBrowser._Tree().NodeExists("/alfresco/webdav" + path +"/") != false){
          Gofast.ajaxFileBrowser.SetSelectedFolderAsync("alfresco/webdav" + path);
        }else{
          Gofast.ajaxFileBrowser.SetSelectedFolderAsync("alfresco/webdav/Sites/");
        }
      }
    }else{
      //console.log('DO NOT update ITHIT mobile location');
    }
  };*/

  Gofast.loadcomments = function(nid,noScroll=false){
      $("#gofast_over_content .text-center .pagination").html("<div class='loader-chat'></div>");
       Gofast.removeLoading();
       $.ajax({
            url : Drupal.settings.gofast.baseUrl+'/gofast/all_comments/render/'+nid,
            type : 'GET',
            dataType: 'html',
            async: true,
            success : function(content){
                $("#comments-container").html(content);
                Drupal.attachBehaviors("#comments-container");
                if(location.href.indexOf("#") != -1){
                  var hash = location.href.substring(location.href.indexOf("#")+1);
                  if (noScroll == false){
                    Gofast.scrollToComment("#" + hash);
                  }
                }
                setTimeout(function(){
                        Gofast.checkReply();
                }, 500);
              }
          });
  };

  Gofast.checkReply = function(){
    if(location.pathname.indexOf('replytocomment') !== -1){
      //We came from a notification and we want to reply to a comment
      var pathname = location.pathname.split('/');
      var cid = '';
      var nid = '';
      while(!jQuery.isNumeric(cid)){ //We find the comment ID
        cid = pathname.pop();
      }
      while(!jQuery.isNumeric(nid)){ //Then, the node ID
        nid = pathname.pop();
      }
      var links = jQuery('.comment-reply a');
      jQuery.each(links, function(){ //We try to find the reply link and to click on it
        if(jQuery(this).attr('href') === "/gofast/nojs/comment/reply/" + nid + "/" + cid){
          //A 1 sec timeout is some times needed on poor networks
            jQuery(this).click();
        }
      });
    }
  }

  Drupal.behaviors.ogTabs = {
    attach: function (context, settings) {
      $('.gofast-og-page:not(.gofast-og-page-processed)').addClass('gofast-og-page-processed').each(function () {
        $('.gofast-og-page a[data-toggle="tab"]:not(".disabled")').click(function (e) {
          $(this).tab('show');
          $('html, body').scrollTop(0);
        });
        if (location.hash !== '') {
          $('.gofast-og-page a[href="' + location.hash + '"]').tab('show');
          $('html, body').scrollTop(0);
        }
        $('.gofast-og-page a[data-toggle="tab"]').on('shown.bs.tab', function (e) {
          var location_parts = $(e.target).attr('href').split('#');
          return location.hash = location_parts[1];
        });
      });
    }
  };


  $(document).ready(function () {
    if (Gofast._settings.isMobile == false || typeof Gofast._settings.isMobile == 'undefined') {
      $('.menu.nav.navbar-nav > .last').before($('#block-search-form'));
    }
    $('#search-block-form .input-group-btn').html($('#dropdown-menu-page-search'));
    $('#dropdown-menu-page-search').show();
    var sidebar = $('.aside');
    var mainMenu = $('#navbar');
    var breadcrumb = $('.breadcrumb');
    var pageHeader = $('.page-header');
    var mainZone = $('#main-content').parent();
    var fullscreenNode = $('#fullscreen-node');
    var mainContainer = $('.main-container');
    var comments = $('.comment-wrapper');
    var nodeContent = $('#fullscreen-node .content.well');
    var footer = $('.footer');
    var gofastOverContent = $('#gofast_over_content');
    var gofastOverContentOldClass = gofastOverContent.attr('class');

    Gofast.toggle_fitscreen = function (fitscreenBtn) {
      fitscreenBtn = $(fitscreenBtn);
      if (typeof sidebar === 'undefined'){
        var sidebar = $('aside');
      }
      if (sidebar.css('display') === 'block') {
        sidebar.css('display', 'none');
        mainMenu.css('display', 'none');
        pageHeader.css('display', 'none');
        //breadcrumb.css('display', 'none');
        comments.css('display', 'none');
        footer.css('display', 'none');
        mainZone.css('width', '100%');
        fullscreenNode.css('width', '100%');
        mainContainer.css('width', '100%');
        if ($(".gofast-og-page").length == 0){
          gofastOverContent.attr('class', 'col-md-12');
        }
//        $('body').each(function () {
//          // this.style.setProperty('padding-top', '0px', 'important');
//        });
        $('body.navbar-is-fixed-top').addClass('gf-full-page');
        nodeContent.css('margin-bottom', '0px');
        fitscreenBtn.find('i').removeClass('fa-arrows-alt').addClass('fa-compress');
//        var maxFrameHeight = $(window).height() - fullscreenNode.css('padding-top').replace('px', '') * 2 - $('.gofast-header').outerHeight(true) - 50;
//        $('#pdf_frame').attr('height', maxFrameHeight);
        //Remove added CSS used when return from fullscreen
        $('body :first').css('padding-top', '0px');

        if (Gofast.Riot) {
          // remember initial width (68 comes from gofast_riot.css)
          this.toggle_fitscreen._RiotWidthCollapsed = Gofast.Riot.widthCollapsed || 68;
          $("#conteneurIframe").width("0px");
          Gofast.Riot.widthCollapsed = 0;
        }
      }
      else {
        sidebar.css('display', 'block');
        mainMenu.css('display', 'block');
        pageHeader.css('display', 'block');
        //breadcrumb.css('display', 'block');
        comments.css('display', 'block');
        footer.css('display', 'block');
        mainContainer.css('width', '');
        mainZone.css('width', '');
        fullscreenNode.css('width', '');
        $('body.navbar-is-fixed-top').removeClass('gf-full-page');
    //    $('body :first').css('padding-top', '70px');
        nodeContent.css('margin-bottom', '20px');
        fitscreenBtn.find('i').removeClass('fa-compress').addClass('fa-arrows-alt');
        $('#pdf_frame').attr('height', '800px');
        if (Gofast._settings.isMobile == false || typeof Gofast._settings.isMobile == "undefined") {
          if ($(".gofast-og-page").length == 0) {
            gofastOverContent.attr('class', "col-lg-8");
          }
        }
        if (Gofast.Riot) {
          var w  = this.toggle_fitscreen._RiotWidthCollapsed || 68; // from gofast_riot.css
          $("#conteneurIframe").width(w + 'px');
          Gofast.Riot.widthCollapsed = w;
        }
      }

      //Resize the file browser
      var eastbar = $("#file_browser_full_tree_container > .ui-resizable-handle");
      if (eastbar.length > 0){
        var pageX = eastbar.offset().left;
        var pageY = eastbar.offset().top;

        (eastbar.trigger("mouseover")
                .trigger({ type: "mousedown", which: 1, pageX: pageX, pageY: pageY })
                .trigger({ type: "mousemove", which: 1, pageX: pageX - 1, pageY: pageY })
                .trigger({ type: "mousemove", which: 1, pageX: pageX, pageY: pageY })
                .trigger({ type: "mouseup", which: 1, pageX: pageX, pageY: pageY }));
      }
  };

    $('#toggle-fullscreen').on('click', function () {
      if ($.fullscreen.isFullScreen()) {
        $.fullscreen.exit();
      } else {
        $(this).parent().parent().parent().fullscreen({overflow: 'auto'});
      }
    });

    $(this).on('fscreenchange', function () {
      if ($.fullscreen.isFullScreen()) {
        $('#view-fullscreen').find('i').removeClass('fa-desktop').addClass('fa-compress');
      } else {
        $('#view-fullscreen').find('i').removeClass('fa-compress').addClass('fa-desktop');
        $('#pdf_frame').attr('height', '700px');
      }
    });

    // This shouldn't be put in the loadOnDocumentReady because loadOnDocumentReady is also used for ajaxification.
    // These shouldn't be reloaded each time ajaxifying
    $('.field-group-tabs-wrapper:first .vertical-tab-button a').each(function () {
      $(this).attr('href', '#');
    });

    $('.field-group-tab').each(function () {
      if ($(this).attr('style')) {
        $(this).css('display', '');
      }
    });

    $('.gofast-disabled').prop('disabled', true);

    // Remove header when coming from calendar
    if (typeof Gofast.getQueryVariables('deadline') === 'string' && typeof Gofast.getQueryVariables('gid') === 'string') {
      $('h1.page-header').hide();
    }
  });

  /**
   * Returns the current, full url, including query string and hash.
   */
  Gofast.getCurrentUrl = function () {
    return window.location.protocol + "//"
            + window.location.host
            + window.location.pathname
            + window.location.search
            + window.location.hash;
  };

  /**
   * Returns variables present in the query as an object.
   */
  Gofast.getQueryVariables = function (variable) {
    var ret = {},
            query = window.location.search.substring(1),
            vars = query.split('&');
    if (variable)
      for (var i = 0; i < vars.length; i++) {
        var pair = vars[i].split('=');
        if (decodeURIComponent(pair[0]) === variable) {
          ret = decodeURIComponent(pair[1]);
        }
      }
    else
      for (var i = 0; i < vars.length; i++) {
        var pair = vars[i].split('=');
        ret[decodeURIComponent(pair[0])] = decodeURIComponent(pair[1]);
      }
    return ret;
  };

  Gofast.selectText = function (element) {
    var text = document.getElementById(element);
    if ($.browser.msie) {
      var range = document.body.createTextRange();
      range.moveToElementText(text);
      range.select();
    } else if ($.browser.mozilla || $.browser.opera) {
      var selection = window.getSelection();
      var range = document.createRange();
      range.selectNodeContents(text);
      selection.removeAllRanges();
      selection.addRange(range);
    } else if ($.browser.safari) {
      var selection = window.getSelection();
      selection.setBaseAndExtent(text, 0, text, 1);
    }
  };

  /**
   * Highlight matched string within a page content
   *
   * @param {string} word - the string to highlight
   * @param {string} snippet - highlighting will focus on this context.
   */
  Gofast.highlightElement = function (word, snippet, el) {
    var target, scrolltop, content, match;

    // Decode html entities (decimal)
    word = $('<div/>').html(word).text();
    snippet = $('<div/>').html(snippet).text();

    content = el && $(el).length ? el && $(el) : $('.region-content');

    if (content.length) {
      match = $(content).filterByText(snippet);
      match.length ? $(match).highlight(snippet) : content.highlight(word);
    }

    target = $('.highlight');
    if (target.length) {
      // Scroll down to the first target. Offset is relative to the header's height.
      scrolltop = target.offset().top - (150); /* @todo : get header height */
      $('html, body').animate({scrollTop: scrolltop}, 500);

      // Allow user to remove highlighting :
      // Show a tip while hovering highlighted snippets
      var tip = $('<span class="gofast-button">' + Drupal.t('Click to remove highlighting', {}, {'context' : 'gofast'}) + '</span>').css({
        position: 'absolute',
        background: '#333',
        color: '#eee',
        'font-size': '10px',
        'font-family': 'Arial'
      });

      // Set mouse events callback (over/out) and hover intent parameters
      var over, out, config;
      over = function () {
        var pos = $(this).position();
        $(this).css('cursor', 'pointer');
        $(tip).appendTo(this).css({top: pos.top + 10 + 'px'}).show().add(this).click(function (e) {
          e.preventDefault(); // element could be an anchor tag
          tip.remove();
          $(target).unbind().css('cursor', 'auto').removeClass('highlight');
        });
      };
      out = function () {
        $(this).css('cursor', 'auto');
        tip.remove();
      };
      config = {
        sensitivity: 1,
        interval: 150,
        over: over,
        timeout: 250,
        out: out
      };

      // Bind target
      $(target).hoverIntent(config);
    }
  };

  Gofast.js_get_url = function (end_url) {
    var myUrl = $(document)[0].URL;
    var l = myUrl.split('/');
    var goodUrl = l[0] + "//" + l[2] + Drupal.settings.basePath;
    var burl = goodUrl + end_url;

    return burl;
  };

    /*
   * Set
   */
  Drupal.behaviors.gofast_node_actions_menu_direction = {
    attach: function (context, settings) {
      $(".gofast-node-actions").on("click", function(e){
        if(e.clientY > (3/5*$(window).height())){
          $(".gofast-dropdown-menu:not(.dropdown-menu-right)").css("bottom", "100%").css("top", "inherit");
          $(".gofast-dropdown-menu.dropdown-menu-right").css("top", "inherit").css("bottom", "0px");
          Gofast.last_menu_align = "down";
        }
        else{
          $(".gofast-dropdown-menu:not(.dropdown-menu-right)").css("top", "100%").css("bottom", "inherit");
          $(".gofast-dropdown-menu.dropdown-menu-right").css("top", "inherit").css("bottom", "0px");
          Gofast.last_menu_align = "up";
        }
      });


    }
  };

  Drupal.behaviors.gofast_contextual_actions_submenu_display_onclick = {
    attach: function (context, settings) {
        $('.contextual-actions .dropdown-submenu .dropdown-toogle').on({"click":function(e){
                e.stopPropagation();
                if($('.contextual-actions .dropdown-submenu .gofast-dropdown-menu.processed').length !== 0){
                    if($('.contextual-actions .dropdown-submenu .gofast-dropdown-menu').css('display') === "none"){
                        $('.contextual-actions .dropdown-submenu .gofast-dropdown-menu').css('display','block');
                    }else{
                        $('.contextual-actions .dropdown-submenu .gofast-dropdown-menu').css('display','none');
                    }
                }else{
                    $('.contextual-actions .dropdown-submenu .gofast-dropdown-menu').css('display','block');
                    $('.contextual-actions .dropdown-submenu .gofast-dropdown-menu').addClass('processed');
                }
            }
        });
        $('.gofast-node-actions .dropdown-submenu .dropdown-toogle').on({"click":function(e){
                e.stopPropagation();
                if($('.gofast-node-actions .dropdown-submenu .gofast-dropdown-menu.processed').length !== 0){
                    if($('.gofast-node-actions .dropdown-submenu .gofast-dropdown-menu').css('display') === "none"){
                        $('.gofast-node-actions .dropdown-submenu .gofast-dropdown-menu').css('display','block');
                    }else{
                        $('.gofast-node-actions .dropdown-submenu .gofast-dropdown-menu').css('display','none');
                    }
                }else{
                    $('.gofast-node-actions .dropdown-submenu .gofast-dropdown-menu').css('display','block');
                    $('.gofast-node-actions .dropdown-submenu .gofast-dropdown-menu').addClass('processed');
                }
            }
        });
    }
  };

  /**
   * Trim all strings inside '.to-trim'-class elements. Attribute 'trimLength'
   * must be set on such element, so that strings are truncated to that length.
   */
  Drupal.behaviors.trimString = {
    attach: function () {
      var text, len;
      $('.to-trim:not(.trimmed)').addClass('trimmed').each(function () {
        text = $(this).text();
        len = $(this).attr('trimLength');
        if (len)
          $(this).text(text.trimToPx(len));
      });
    }
  };

  /**
   * Autocompletion pour les destinataires d'un mail / messages
   * UI : Les suggestions séléctionnées (les adresses/noms/groupes) se
   * transforment en items cliquable (suppressible)
   */
  Drupal.behaviors.labelize = {
    attach: function (context) {
      var labelize = {},
              select = function (data) {
                data = data.data || data;
                //var value = $.trim($($(this).get(0)).text()) || this.defaultValue,
                var value = $.trim($($(this).children()).html()) || this.defaultValue,
                        autocomplete = data.autocomplete,
                        form = data.form,
                        form_item = data.autocomplete.form_item,
                        values = data.values,
                        hidden_values = autocomplete.parent().siblings('input[id=' + autocomplete.attr('id') + '-values]');
                autocomplete.val('').focus();

                if (!$('.selection-tags', autocomplete.parent()).length) {
                  $('<div class="selection-tags"></div>').insertAfter(autocomplete);
                }

                var parsedItem = $('<output>').append(value);
                var metadata = parsedItem.find('.labelize-metadata').data();
                var itemContent = parsedItem.not('.labelize-metadata').html();
                if (!metadata) {
                  itemContent ='<span style=\"line-height:24px;\">'+value+'</span>';
                  metadata = null;
                }

                var allow_insert = autocomplete.hasClass('labelize-insert');

                var id = metadata !== null ? metadata.id : value;
                var id_type = metadata !== null ? metadata.id + metadata.type : value;
                if (!values[id_type] && ((allow_insert && metadata === null) || metadata !== null)) {
                  var title = "";
                  var id = '';
                  var data = '';
                  if (metadata === null) {
                    title = id = data = value;
                  } else {
                    if (metadata.type === "node") {
                      title = Drupal.t('Members of', {}, {'context' : 'gofast'}) + ' ' + metadata.name;
                    } else if (metadata.type === "user" || metadata.type === 'userlist') {
                      title = metadata.name;
                    } else if (metadata.type === "taxonomy_term") {
                      title = metadata.name;
                    } else {
                      title = itemContent;
                    }
                    id = metadata.id;
                    data = metadata;
                  }
                  values[id_type] = data;
                  title = 'title="' + title + '"';
                  var item = '<span class="tagging-tag processed" ' + title + '>' + itemContent + '&nbsp;<i class="fa fa-times"></i>';
                  if (!metadata) {
                    var labelize_metadata = '<span class="labelize-metadata" data-type="" data-id="' + id + '" data-value="' + value + '" ></span>';
                    item += labelize_metadata;
                  }
                  item += '</span>';
                  autocomplete.parent().find('.selection-tags').append(item);
                  if(typeof modalContentResize !== "undefined"){
                    modalContentResize();
                  }
                  // Add a click event handler that enables user to remove this item
                  autocomplete.parent().find('.tagging-tag.processed:not(.remove)').addClass('remove').click(function () {
                    var id = $(this).find('.labelize-metadata').data('id');
                    var id_type = $(this).find('.labelize-metadata').data('id') + $(this).find('.labelize-metadata').data('type');
                    var existing_hidden_value = autocomplete.parent().siblings('input[id=' + autocomplete.attr('id') + '-values]').val();
                    var new_value = existing_hidden_value.split(' ').filter(function(i){
                      // Non-strict comparison intended for strings to match numbers or conversely.
                      return i != id;
                    }).join(' ');
                    autocomplete.parent().siblings('input[id=' + autocomplete.attr('id') + '-values]').val(new_value);
                    if (values[id_type])
                      delete values[id_type];
                    $(this).remove();
                    autocomplete.focus();
                  });
                }
                else {
                  autocomplete.focus();
                }
                var existing_hidden_value = autocomplete.parent().siblings('input[id=' + autocomplete.attr('id') + '-values]').val();
                var new_value = existing_hidden_value.split(' ').filter(function(i){
                  return i !== id;
                }).concat(id).join(' ');
                autocomplete.parent().siblings('input[id=' + autocomplete.attr('id') + '-values]').val(new_value);
                if (data.type == "node" & $(this).parent().parent().parent().hasClass('form-item-list-participants')){
                   //Conference case, we need to process tthe given space
                   setTimeout(function () {
                     Gofast.conference.autocomplete_process(this);
                   }, 500);
                }
              },
              prevent = function (e) {
                var autocomplete = e.data.autocomplete,
                        form = e.data.form,
                        form_item = e.data.form_item;
                // Prevents wrong behaviors induced by wrong click events
                if (e.which === 2 || e.which === 3) {
                  e.preventDefault();
                  autocomplete.val('');
                  $('.dropdown li.selected', form_item).removeClass('selected');
                }
                // Prevents double-click to fill twice
                setTimeout(function () {
                  autocomplete.val('');
                }, 200);
              },
              onSubmit = function (e) {
                var autocomplete = e.data.autocomplete,
                        form = e.data.form,
                        form_item = e.data.form_item,
                        hidden_values = autocomplete.parent().siblings('input[id=' + autocomplete.attr('id') + '-values]');
                var myvalues = [];
                for (var property in e.data.values) {
                  if (e.data.values.hasOwnProperty(property)) {
                    myvalues.push(e.data.values[property]);
                  }
                }
                hidden_values.val(JSON.stringify(myvalues));
              };

      // Bind events to handlers for each instances of a labelized text input

      $('input.labelize-autocomplete:not(.labelize-autocomplete-processed)', context).addClass('labelize-autocomplete-processed').each(function () {
        // This adds the requiered hidden field that will transport the values
        if (!$("input[name*='" + $(this).attr('id') + "-hidden-values']", $(this).parent()).length) {
          $(this).parent().after('<input type="hidden" id="' + $(this).attr('id') + '-values" name="' + $(this).attr('id') + '-hidden-values"/>');
        }

        var autocomplete = $(this),
                form = $(this).closest('form'),
                form_item = $(this).closest('div.form-item'),
                values = [],
                data = {
                  autocomplete: autocomplete,
                  form: form,
                  form_item : form_item,
                  values: values
                },
        hidden_values = autocomplete.parent().siblings('input[id=' + autocomplete.attr('id') + '-values]');

        // Labelize default value if set
        if (autocomplete.val() !== '') {
          // Allow time for the popup to be resized in the first place
          setTimeout(function () {
            var def = autocomplete.val();
            var def_values = def.split(',');
            for (var i = 0; i < def_values.length; i++) {
              if (def_values[i] !== '') {
                select.call({defaultValue: def_values[i]}, data);
              }
            }
            autocomplete.val('').focus().removeClass('labelizeDefault');
          }, 200);
        }

        // This binds submit on every labelized field
        form.submit(data, onSubmit);

        //When submit the userlist form, give
        $('#submit_userlist').mousedown(function(){
            var e={};
            e.data=data;
            onSubmit(e);
            $('#submit_userlist').attr("disabled", "true");
            $.ajax({
                statusCode : {
                   408 : function( ){
                       window.location.replace(window.location.href);
                       //window.location.replace(window.location.origin+"/userlists");
                   }
                }
            });
        });

        form_item.not('.labelized').addClass('labelized')
               .on('click', '.dropdown li', data, prevent)
               .on('mousedown', '.dropdown li', data, select);

        autocomplete.not('.labelized').addClass('labelized').on('keydown', function (e) {
          if (!e)
            e = window.event;
          if (e.keyCode === 13) {
            selectElement(e, $(this), select, data);
          }
        }) ;

        function selectElement(event, input_field, select, data) {
          event.preventDefault();
          var selection = $('.dropdown li.active', form_item);
          if (selection.length) {
            select.call(selection, data);
            setTimeout(function () {
              input_field.val('').focus();
            }, 100);
            setTimeout(function () {
              input_field.val('').focus();
            }, 200);
          }
          else if (input_field.hasClass('labelize-insert')) {
            var text = input_field.val();
            if (text) {
              select.call({defaultValue: text}, data);
              setTimeout(function () {
                input_field.val('').focus();
              }, 200);
            }
          }
        }
      });
    }
  };

  /**
   * Hide protected attributes without altering the underlying value.
   */
  Drupal.behaviors.gofastProtectedAttributes = {
    attach: function (context, settings) {
      var pAttr = Gofast.global.protectedAttr || [];
      pAttr.forEach(function (item, i) {
        $(item.selector, context).once('protected', function () {
          var element = this;
          item.attrList.forEach(function (attr, i) {
            if (element.attributes.getNamedItem(attr)) {
              var val = $(element).val();
              element.attributes.removeNamedItem('value');
              $(element).val(val);
            }
          });
        });
      });
    }
  };

  /**
   * Retrieve the full_screen attribute in the url to know if we display the node in full screen
   */
  Drupal.behaviors.gofastFullscreenNode = {
    attach: function (context, settings) {
        if(Gofast.success_fullscreen != true){
            var href = window.location.href;
            var url = new URL(href);

            if(!!navigator.userAgent.match(/Trident.*rv\:11\./)){
                var full_screen = url.parameterNames.indexOf("full_screen");
                if(full_screen !== -1){
                    full_screen = "1";
                }
            }else{
                var full_screen = url.searchParams.get("full_screen");
            }


            if(full_screen == '1' && Gofast.success_fullscreen != true && Gofast.Fullscreen_node != true){
                Gofast.toggle_fitscreen(null);
                Gofast.Fullscreen_node = true;
                Gofast.success_fullscreen = true;
            }else{
                Gofast.success_fullscreen = false;
            }
        }
    }
  };

  Gofast.conference = Gofast.conference || {};

  Gofast.conference.attach_before_submit = function(){
        if($("#submit_conference").length === 0 || $("#submit_conference").hasClass('gofast-processed')){
          return;
        }
        $("#submit_conference").addClass('gofast-processed');
        //Set dates to proper format before submit
        var submitButon = $("#submit_conference")[0];
        $().bindFirst(submitButon, 'mousedown', function(){
          //If we are in french language, we need to switch days and month
          var user = Gofast.get('user');
          if(user.language == 'fr'){
            //Get values
            var start = $(".form-item-field-date-und-0-value-date").find('input').val();
            var end = $(".form-item-field-end-date-und-0-value-date").find('input').val();
            //Transform values
            start = start.substring(3,5) + '-' + start.substring(0,2) + start.substring(5);
            end = end.substring(3,5) + '-' + end.substring(0,2) + end.substring(5);
            //Replace values
            $('#conference_date input.date-clear.form-text').val(start);
            $(".form-item-field-end-date-und-0-value-date").find('input').val(end);
          }

          //Now, the fields are formated in english. But, because the 'end_date' field
          //was firstly created with a bad format, we need to reformat it to yyyy-mm-dd
          var end = $(".form-item-field-end-date-und-0-value-date").find('input').val();
          end = end.substring(6, 10) + "-" + end.substring(0, 5) + end.substring(10);
          $('#conference_end_date input.date-clear.form-text').val(end);
        });
  };

    /*
     * Make the audit node block asynchronous
     */
    Drupal.behaviors.gofast_audit_node_block = {
        attach: function (context,settings) {
            if($('#block-gofast-gofast-audit-node-page').length > 0){
                if(!$('#block-gofast-gofast-audit-node-page').hasClass('processed')){
                    $('#block-gofast-gofast-audit-node-page').addClass('processed');
                    if (Gofast.get('node') !== undefined){
                        var nid = Gofast.get('node').id;
                        $.post(location.origin + "/gofast/node/"+nid+"/get_audit_node").done(function(data){
                            if($('.loader_audit_node').length !== 0){
                                $('.loader_audit_node').remove();
                                $('#block-gofast-gofast-audit-node-page').append(data);
                                Gofast.auditPageBindPagination();
                            }
                        });
                    }
                }
            }
        }
    };


    Gofast.auditPageBindPagination = function () {
            $('#block-gofast-gofast-audit-node-page .pagination li a').click(function(event){
                event.preventDefault();
                event.stopPropagation();
                $.post(location.origin + $(this).attr("href")).done(function(data){
                    $('.view-gofast-audit-node').remove();
                    $('#audit_node_button').remove();
                    $('#block-gofast-gofast-audit-node-page').append(data);
                    Gofast.auditPageBindPagination();
                });
            });
    };

  /*
   * Login page transitions
   */
  $(document).ready(function(){
    Gofast.block.load("gofast_workflows_light_dashboard", "gofast_workflows", "Workflow", $("#gofast_block_delta-gofast_workflows_light_dashboard-gofast_workflows .gofast-block-inner"),  "1", "1");
    window.onerror = function(message, url, lcount){
      //var user = Gofast.get("user");
      //$.post(location.origin + "/gofast/js-error", {useragent : navigator.userAgent, request : location.href, url : url, message : message, line : lcount});
    }
     if( $('#user-login-form').length ){
      $('head').append('<link href="sites/all/themes/bootstrap-gofast/fonts/Roboto.css" rel="stylesheet">');
      $('body').css('-webkit-perspective', '1200px');
      $('body').css('-ms-perspective', '1200px');
      $('body').wrapInner('<div class="pt-wrapper"></div>');
      $('body').append('<div class="pt-page"><div class="message">' + Drupal.settings.message_welcom + '</div></hr></div>');
      $('#edit-submit').click(function(){
        $('.pt-wrapper').addClass('pt-page-rotateSlideOut');
        $('#navbar').addClass('disappear');
        $('.pt-page').addClass('pt-page-rotateSlideIn');
      });
      $('.pt-page').append('<div class="poweredbyGofast"></div>');
      $('.poweredbyGofast').append('<div>Powered by</div>');
      $('.poweredbyGofast').append('<div><img class="logo_welcome_page" src="/sites/all/themes/bootstrap-gofast/Logo_GoFAST de CEO-Vision_fr_blanc.png" "></div>');
      $('.poweredbyGofast').append('<span class="text-version">Version:'+ Drupal.settings.gofast_version.replace('7.x-','') +'</span>');
    }

    $.getScript('/sites/all/modules/flag/theme/flag.js', function() {
        Drupal.behaviors.flagLink.attach(document);
    });
    // enable tooltip
    $('[data-toggle="tooltip"]').tooltip();

    /* BEGIN hide print Iframe Preview button */
    var waitForPreviewIframe = function (callback, count) {
      if ($('iframe#pdf_frame').contents().has('#print').length > 0) {
        callback();
      } else {
        setTimeout(function () {
          if (!count) {
            count = 0;
          }
          count++;
          if (count < 500) { // Max CAllback 500 time
            waitForPreviewIframe(callback, count);
          } else { return; }
        }, 250);
      }
    };

    waitForPreviewIframe(function () {
      Gofast.HidePrintButton();
    });
    /* END minimized Riot LeftPanel */

  });

  //Add missing translations to the page context
  Drupal.t('No', {}, {'context' : 'gofast'});
  Drupal.t('Yes', {}, {'context' : 'gofast'});
  Drupal.t('Delete', {}, {'context' : 'gofast'});

  var waitUserAvailable = setInterval(function(){
    if(typeof Drupal.settings !== "object" || typeof Drupal.settings.gofast !== "object" || typeof Drupal.settings.gofast.user !== "object"){
        return;
    }

    clearInterval(waitUserAvailable);

    if(Drupal.settings.gofast.user.display_carousel){
        var waitForClass = setInterval(function(){
            if($("#gofast_carousel_link").hasClass("ctools-use-modal-processed")){
                $("#gofast_carousel_link").click();
                clearInterval(waitForClass);
            }
        }, 200);
    }
  }, 200);

  /**
  * Build an error message from an Ajax response.
  */
  Drupal.ajaxError = function (xmlhttp, uri, customMessage) {
    var statusCode, statusText, pathText, responseText, readyStateText, message;
    if (xmlhttp.status) {
      statusCode = "\n" + Drupal.t("An AJAX HTTP error occurred.") +  "\n" + Drupal.t("HTTP Result Code: !status", {'!status': xmlhttp.status});
    }
    else {
      statusCode = "\n" + Drupal.t("An AJAX HTTP request terminated abnormally.");
    }
    statusCode += "\n" + Drupal.t("Debugging information follows.");
    pathText = "\n" + Drupal.t("Path: !uri", {'!uri': uri} );
    statusText = '';
    // In some cases, when statusCode == 0, xmlhttp.statusText may not be defined.
    // Unfortunately, testing for it with typeof, etc, doesn't seem to catch that
    // and the test causes an exception. So we need to catch the exception here.
    try {
      statusText = "\n" + Drupal.t("StatusText: !statusText", {'!statusText': $.trim(xmlhttp.statusText)});
    }
    catch (e) {}

    responseText = '';
    // Again, we don't have a way to know for sure whether accessing
    // xmlhttp.responseText is going to throw an exception. So we'll catch it.
    try {
      responseText = "\n" + Drupal.t("ResponseText: !responseText", {'!responseText': $.trim(xmlhttp.responseText) } );
    } catch (e) {}

    // Make the responseText more readable by stripping HTML tags and newlines.
    responseText = responseText.replace(/<("[^"]*"|'[^']*'|[^'">])*>/gi,"");
    responseText = responseText.replace(/[\n]+\s+/g,"\n");

    // We don't need readyState except for status == 0.
    readyStateText = xmlhttp.status == 0 ? ("\n" + Drupal.t("ReadyState: !readyState", {'!readyState': xmlhttp.readyState})) : "";

    // Additional message beyond what the xmlhttp object provides.
    customMessage = customMessage ? ("\n" + Drupal.t("CustomMessage: !customMessage", {'!customMessage': customMessage})) : "";

    message = statusCode + pathText + statusText + customMessage + responseText + readyStateText;
    //@CEO-Vision patch
    //Won't display technical error message
    //return message;
    console.error('Ajax error', message);
    return "<strong>" + Drupal.t("A network error has occurred.") + "</strong><br />" + Drupal.t("Please save your work and reload this page.");
  };

  /**
   * Prevent redirect when clicking admin toolbar toogle.
   */
  Drupal.behaviors.adminToolbar = {
    attach: function(context) {
      $('#toolbar a.toggle', context).once('toolbar-href', function(e) {
        $(this).attr('href', '#');
      });
    }
  };


  /**
   * //For each tag we need to retrieve and set tha subscribe button
   */
  Drupal.behaviors.tagsSetSubButton = {
    attach: function (context) {
      $('.gofast-tags-noedit', context).once('gofast-tags-noedit', function (e) {

        var value = '';
        var tag_value = $(this);
        tag_value.html(value);

        var param_url = tag_value.data("name").replace("/", "*\*") + '[GOFAST_TAG_SEPARATOR]' + tag_value.data("id") + '/' + Drupal.settings.gofast.node.id;
           $.ajax({ //Call to get subscribe button
             url: Drupal.settings.gofast.baseUrl + '/xeditable/get/subscribe/' + param_url,
            type: 'GET',
            dataType: 'html',
            success: function (content, status) {
              value = tag_value.html();
              value = value.slice(0, -5);
              value += content;
              tag_value.html(value);
              $.getScript('/sites/all/modules/flag/theme/flag.js', function () {
                Drupal.behaviors.flagLink.attach(document);
              });
            }
          });
      });
    }
  };

  $(document).bind('flagGlobalAfterLinkUpdate', function (event, data) { //Reformat tag display when AJAX subscribing to it
    if (data.flagName === 'subscribe_term') {//It's a term
      jQuery('.flag.flag-link-toggle.flag-processed').parent('p').children().remove()
      var flag = $('.flag-subscribe-term-' + data.contentId).find('a');
      var iflag = flag.first();

      //Format flag
      flag.css("padding", "0");
      flag.css("padding-left", "3");

      //Remove text from flag
      flag.html(flag.html().replace(Drupal.t('Subscribe', {}, { 'context': 'gofast' }), ""));
      flag.html(flag.html().replace(Drupal.t('Unsubscribe', {}, { 'context': 'gofast' }), ""));

      //Format as red for unflag case
      if (flag.hasClass("unflag-action")) {
        iflag.css('color', 'red');
      }
    }
  });

  $(document).bind('flagGlobalBeforeLinkUpdate', function (event, data) { //Rebuilding tag name
    let tmpdata = decodeURI(data.newLink);
    let tmp1 = tmpdata.split('get/subscribe/');
    let tmp2 = tmp1[1].split('[GOFAST_TAG_SEPARATOR]');
    //When we have / at the beginning, replaced by **
    let newtag = tmp2[0].replace('**', '/');
    data.newLink = data.newLink + '<p style="margin-top:5px; float: left;">' + newtag + '</p>';
  });

  Drupal.t("Meetings", {}, {context: 'gofast_cdel'});
  Drupal.t("Documents deadlines", {}, {context: 'gofast_cdel'});
  Drupal.t("Tasks", {}, {context: 'gofast_cdel'});


  //some translation strings
  Drupal.t("The rss feed has been added", {}, {context: 'gofast:gofast_rssfeed'});
  Drupal.t("The feed URL is invalid. Please enter a fully-qualified URL, such as<br /><br /><blockquote>http://fr.news.yahoo.com/?format=rss</blockquote>", {}, {context: 'gofast:gofast_rssfeed'});
  Drupal.t("The rss feed has been edited", {}, {context: 'gofast:gofast_rssfeed'});
  Drupal.t("The rss feed has been deleted", {}, {context: 'gofast:gofast_rssfeed'});
  Drupal.t("The rss feed has not been deleted", {}, {context: 'gofast:gofast_rssfeed'});

  // Initialize CKEditor Object if not already.
  Drupal.settings.ckeditor = Drupal.settings.ckeditor || {};

  // Init hooks
  Gofast.hooks = [];

})(jQuery, Gofast, Drupal);

