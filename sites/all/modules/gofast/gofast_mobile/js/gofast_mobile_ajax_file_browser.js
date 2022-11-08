(function($, Drupal, Gofast) {
  'use strict';
  $(document).ready(function() {
    
    var port = window.location.port === '' ? '' : ':' + window.location.port;
    var baseUrl = window.location.protocol + '//' + window.location.hostname + port;
    var webDavServerPath = baseUrl + '/alfresco/webdav/Sites';
    var originalTitle = document.title;
    var selectingItemColor = '#90C3D4';
    var ITHitController = '';
    
    function resizeMobileBrowser() {
      var panelWrapperHeight = $('.ui-panel-wrapper').height() - $('div[data-role="footer"]').height();
      $('.ui-panel-wrapper').css('height', panelWrapperHeight);
      $('.ui-panel-wrapper > .ui-content').css('height', panelWrapperHeight);
      $('div[data-role="header"], div#ithit_tree_panel, div#ithit_upload_panel').css('top', $('header').height());
    }
    
    function getHrefByDisplayName(type, folderURL, displayName) {
      var href = '';
      var itemsList = ITHitController.Commands.FoldersCollection._Items[folderURL];
      $.each(itemsList, function(key, item) {
        if (item.ResourceType === type && item.DisplayName === displayName) {
          href = item.Href;
          return false; // break each loop
        }
      });
      return href;
    }
    
    function redirectToTheDocument(documentURL) {
      // Retrieve the document's nid.
      $.ajax({
        'url': '/ajax/getnidfromhref',
        'data': encodeURI('href=' + documentURL),
        'dataType': 'json',
        'async': true,
        'beforeSend': function(xhr) {
          Gofast.addLoading();
        }
      }).done(function(data) {
        if (data === false || isNaN(data)) {
          Gofast.modal('<div class="panel panel-default">\n\
                            <div class="panel-body" id="uploading_progress_panel">\n\
                              <div id="uploading_error_messages" class="alert alert-danger" style="display:none;">\n\
                                <ul></ul>\n\
                              </div>\n\
                              <div id="uploading_buttons_actions_all"></div>\n\
                                <div style="clear:both;" id="uploading_0" file-name="logo gofast détouré_eng.png" xhr-id="0" file-id="0">\n\
\n\                               <div class="loader-replicate"></div>\n\
                                  <span id="uploading_replicating" style="font-weight:bold;">'+Drupal.t('You will be redirected to @path  in a few seconds...', {'@path': documentURL.split('/').pop()}, {'context': 'gofast:gofast_ajax_file_browser'}) +'</span>\n\
                                </div>\n\
                              </div>\n\
                          </div>', Drupal.t('Almost ready', {}, {'context': 'gofast'}), {
            'modalSize': {
              'type': 'scale',
              'width': .5,
              'height': .5
            },
            'modalTheme': 'uploading_dragdrop'
          });
          //Start replication as it seems to be needed
          $.ajax({
            url: '/cmis/replicate',
            data: encodeURI('href=' + documentURL),
            dataType: 'json'
          }).done(function (data) {
            $(".ctools-close-modal").trigger("click");
            Gofast.goto('/node/' + data);
          });
        }
        else {
          Gofast.goto('/node/' + data);
        }
        
      });
    }
    
    function initAjaxFileBrowser() {
      // Authenticate to WebDAV server (Alfresco)
      Gofast.sendXHR('GET', webDavServerPath, '', false, [{name: 'Authorization', value: Drupal.settings.credentials}]);
      var settings = {
        BasePath: '/sites/all/libraries/ajax_file_browser/Browser/',
        Id: 'AjaxFileBrowserMobileContainer',
        Url: webDavServerPath,              
        Style: 'height: 100%; width: 100%',
        SelectedFolder: webDavServerPath,
        ThemeName: 'windows_8',             
        Platform: 'mobile',
        ViewModeMobile: 'list',
        EditModeMobile: 'auto',
        EnableHistoryNavigation: false,
        Phrases: phrases
      };
      var ajaxMobileFileBrowserLoader = new ITHit.WebDAV.Client.AjaxFileBrowserLoader(settings);
      
      ajaxMobileFileBrowserLoader.oninit = function(ajaxFileBrowser) {
        ITHitController = ITHit.WebDAV.Client.AjaxFileBrowserMobile.Controller.GetByIndex(0);
        // /!\ IMPORANT : Desactivate the ajaxification when clicking on the <a>
        ITHit.Components.jQuery.mobile.ajaxEnabled = false;
        
        // /!\ IMPORANT : Desactivate the ITHIT DetectDevice to prevent from opening the document in an other tab
        ITHit.oNS.Controller.prototype.OpenDocument = function() {};
       
        $('div#ithit_page_list').css('top', $('header').height());
       
        resizeMobileBrowser();
      };
      ajaxMobileFileBrowserLoader.LoadAsync();
    };
    initAjaxFileBrowser();
    
    // Load the overriding css file right after the ithit css is loaded
    // And modify body's css to prevent the unexpected flickers.
    $('head').on('DOMNodeInserted', 'style', function(e) {
      if (e.target.textContent.indexOf('ui-mobile') >= 0) {
        $('head').append('<link rel="stylesheet" href="/sites/all/modules/gofast/gofast_mobile/css/override_ajax_file_browser_mobile.css?'+Date.now() + '" />');
      }
    });
    
    $(document).on('click', '.ui-checkbox, .ui-btn:not("> .item-arrow, .iconFolders, .iconUp, .button-item, .button-cancel, [data-overwriteaction=\"rewrite\"], [data-overwriteaction=\"rewrite_all\"], [data-overwriteaction=\"skip\"], [data-overwriteaction=\"skip_all\"], [data-overwriteaction=\"cancel\"], .iconRefresh, .iconDelete, .iconCut, .iconCopy, .iconPaste, .iconUpload"), .dialog-simpleForm .button-accept', function(e) {
//      setTimeout(function() {
//        resizeMobileBrowser();
//      }, 0);
    });
    
    $(window).on('orientationchange, resize',function(e) {
      setTimeout(function(){
        $('.ui-header').css('top', $('header').height());
        $('#ithit_page_list').css('padding-top', $('.ui-header').height());
      }, 500);
    });
    
    // Highlight the selecting item
    $(document).on('tap', 'li.itemType-file > a.button-item', function(e) {
      e.preventDefault();
      e.stopPropagation();
      $('li.itemType-file > a.button-item').css('background-color', '');
      $(this).css('background-color', selectingItemColor);
    });
    
    // Redirect to the node on which we double click
    $(document).on('doubletap', 'li.itemType-file > a.button-item', function(e) {
      e.preventDefault();
      var displayName = $(this).find('h2').text();
      var documentURL = getHrefByDisplayName('Resource', ITHitController._url, displayName);
      redirectToTheDocument(documentURL);
    });
  });
})(jQuery, Drupal, Gofast);


