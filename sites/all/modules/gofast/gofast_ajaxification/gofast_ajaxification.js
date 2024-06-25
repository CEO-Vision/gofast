(function ($, Gofast, Drupal) {

  Gofast.exclude_ajax_url.push("/user/password");
  Gofast.exclude_ajax_url.push("/space/admin/members");
  Gofast.processAjax = function (href, isStateChange, isFromHistoryNavigation = false) {
    if (href.indexOf('javascript') != -1 || href == "#") {
      return;
    }

    //each module can fill this global variable to excluse some url from ajaxification
    let endpoint = href.split("?")[0].replace(location.origin, "");
    //we want excluded urls to be excluded even if they have query params or base url
    if (Gofast.exclude_ajax_url.indexOf(endpoint) != -1) {
      window.location.href = href;
      return;
    }

    // Hide side menu on mobile devices, when click on menu items.
    if ($('.gofast-mobile').length) {
      $('.aside-overlay').click();
    }

    href = decodeURI(href);
    // Encode all '%' that are alone 
    // because it's not possible to decodeURI on '%' when there is not two digit after
    href = href.replaceAll(/%(?!\w{2})/gm, "%25")
    href = decodeURI(href);
    href = href.replaceAll(/%(?!\w{2})/gm, "%25")
    href = href.replace(/\+/g, '%2B');
    var href_ajax = "gofast_ajaxification/nojs";

    if ($('.popover').length > 0) {
      $('.popover').popover('hide');
    }
    $("[data-toggle='tooltip']").tooltip("dispose");
    if (Gofast.tour.components.fakeCursor.cursor != null) {
      Gofast.tour.components.fakeCursor.destroy();
    }

    // search case
    if(Drupal.settings.gofast_search_path && href.startsWith("/" + Drupal.settings.gofast_search_path)) {
      let terms = href.replace("/" +  Drupal.settings.gofast_search_path + "/", "");
      terms = terms.split("?")[0]; // remove query string from search query if any
      // GOFAST-10214 - prevent search query if query contains a slash
      let hasSlash = !!terms.match(new RegExp(/\/|%2F/g))
      if (hasSlash) {
        Gofast.toast(Drupal.t("It is forbidden to make a search query with slashes"), "error");
        return;
      }
    }

    // var url_callback = "gofast_ajax/nojs";
    $('.gofast-clipboard').after('<span id="ajax_button"></span>');
    var base = $('#ajax_button').attr('id');
    var element_settings = {
      //url: 'https://' + window.location.hostname + Drupal.settings.basePath + Drupal.settings.pathPrefix + href_ajax + '?url=' + encodeURIComponent(href) + (view_dom_id ? '&view_dom_id=' + view_dom_id : ''),
      url: 'https://' + window.location.hostname + Drupal.settings.basePath + Drupal.settings.pathPrefix + href_ajax + '?url=' + encodeURIComponent(href),
      event: 'click',
      method: 'replaceWith',
      progress: {
        type: 'throbber'
      }
    };

    Drupal.ajax[base] = new Drupal.ajax(base, $("#ajax_button").get(0), element_settings);

    // Override ajax complete handler.
    Drupal.ajax[base].options.complete = function (xmlhttprequest, status) {

      Drupal.ajax[base].ajaxing = false;
      if (status === 'error' || status === 'parsererror') {
        Drupal.ajax[base].error(xmlhttprequest, encodeURIComponent(href));
        return false;
      }
      Gofast.ajaxingNav = false;
      $(document).trigger('ajax-nav-success');

      //Register any URL change
      var params = {};
      if(location.search) {
        let searchParams = new URLSearchParams(location.search)
        params = Object.fromEntries(searchParams)
      }

    };
    $("#ajax_button").trigger("click"); // triggers the ajax object that handles the xhr.
    $(document).trigger('ajax-navigate'); // triggers en event with document as context so other module can react on ajax nav.
    Gofast.ajaxingNav = true;

    $("#ajax_button").remove();

    if ((href.indexOf(location.origin + "/gofast/node-info") == -1 && href.indexOf(location.origin + "/gofast/delete_space") == -1) && !isFromHistoryNavigation) {
      if (href.indexOf('?') !== -1) { //Need to push the path without parameters, and then, the parameters
        window.history.pushState(null, "", href.substring(0, href.indexOf('?')) + encodeURI(href.substring(href.indexOf('?'))));
      }
      else {
        window.history.pushState(null, document.title, href);
      }
    }
    
    if ($("#expl-forum").length) {
      if($("#expl-forum").hasClass("active") && $("#explorer-toggle").hasClass("open")){
        Gofast.reloadForums();
      }
    }

    if (Drupal.settings.gofast_selected_book && Gofast.get("node").type != "article") {
      delete Drupal.settings.gofast_selected_book;
      Gofast.selectCurrentWikiArticle();
    }

    setTimeout(function () {
      // Reset the search input field
      if ($('#search-block-form input[type="text"]').next().length > 0) { // Check if the search input field is replace by auto-suggestion.
        $('#search-block-form input[type="text"]').next().remove();
        $('#search-block-form input[type="text"]').val('');
      }
    }, 200);

    jQuery(".tooltip").remove();
  };

  $(document).ready(function () {
    // override to handle signaling when pushState is called
    if (typeof window.history.originalPushState == "undefined") {
      window.history.originalPushState = window.history.pushState;
      window.history.pushState = function (state, title, url) {
        if(!url.startsWith(location.origin)){
          url = location.origin + url
        }
        // Don't make push state if it's the same url
        if(decodeURI(url) == decodeURI(location.href)){
          return;
        }
        let urlObj = new URL(url);
        if(location.pathname == urlObj.pathname){
          window.history.replaceState(state, title, url);
          return
        }
        window.history.originalPushState(state, title, url);
        Gofast.updateHistory()
      };
    }

    //Will contain the last URL to use in navigation events
    var params = {};


    //Disable ajax if we are in a temporary session in order to change password
    if(typeof Drupal.settings.pass_reset != "undefined"){
        return;
    }
    Gofast.updateHistory()

    $(window).bind('hashchange', function (event) { //Register any URL change
      Gofast.updateHistory()
    });
    // ajax_call when user use back/next on the browser
    window.addEventListener('popstate', function (event) {
      var oldHistory = Gofast.History;
      var searchParams = new URLSearchParams(location.search)
      
      //Check if we have to process an ajax navigation
      if (searchParams.has("path") && oldHistory.params.hasOwnProperty("path")) {
        //A navigation occured but we don't need to switch page. Call module to handle this event
        if(Gofast._settings.isEssential){
          Gofast.Essential.processEssentialAjax(location.href.replace(this.location.origin, ""))
        } else {
          Gofast.ITHit.navigate('/alfresco/webdav' + searchParams.get("path"), null, null, true);
        }
      } else if(Gofast.History.pathname == window.location.pathname){ //Check if URI has really changed (Prevent Hash changes to trigger navigation)
        //GOFAST-10522 Pathnames are the same, do nothing in that case
      } else{
        //We need to navigate in ajax to another page
        if (Gofast._settings.isEssential) {
          //processEssentialAjax just need the path (ex: /node/...) so remove the start of the full href
          Gofast.Essential.processEssentialAjax(location.href.replace(location.origin, ""));
        } else {
          Gofast.processAjax(location.href, null, true);
        }
      }
      Gofast.updateHistory()
    }, false);

    $(document).on('submit', '#search-block-form ', function (e) {
      e.preventDefault();
      Gofast.xhrPool.abortAll();
      var params = '';
      // GOFAST-7605 - we use the original form input as reference to avoid "undefined" retain filters
      var retain_filters = $("[name=retain-filters]").val();
      if (retain_filters === "1") {
        params = location.search
      }
      var terms = $(this).find('input').filter('[type="text"][name="search_block_form"]').val();
      // GOFAST-6737
      terms = encodeURIComponent(terms);
      if(!Gofast._settings.isEssential || Gofast._settings.isMobileDevice){
        Gofast.processAjax('/search/solr/' + terms + params, true);
      } else {
        Gofast.Essential.solrSearch(terms + params);
      }
    });

    $(document).on('submit', '#search-form', function (e) {
      e.preventDefault();
      Gofast.xhrPool.abortAll();
      var params = '';
      // GOFAST-7605 - we use the original form input as reference to avoid "undefined" retain filters
      var retain_filters = $("[name=retain-filters]").val();
      if (retain_filters === "1") {
        var uri = decodeURIComponent($(document)[0].URL);
        // Encode all '%' that are alone 
        // because it's not possible to decodeURI on '%' when there is not two digit after
        uri = uri.replaceAll(/%(?!\w{2})/gm, "%25")
        uri = decodeURIComponent(uri)
        uri = uri.replaceAll(/%(?!\w{2})/gm, "%25")
        var fq = decodeURIComponent(uri).lastIndexOf('?f[0]');
        if (fq != -1) {
          params = uri.substr(fq);
        }
      }
      var terms = $(this).find('[name=keys]').val();
      // GOFAST-6737
      terms = encodeURIComponent(terms);
      if(!Gofast._settings.isEssential || Gofast._settings.isMobileDevice){
        Gofast.processAjax('/search/solr/' + terms + params, true);
      } else {
        Gofast.Essential.solrSearch(terms + params);
      }
      Drupal.attachBehaviors();
    });

    var saml = "";

    if(Drupal.settings.saml_enabled){
        //Don't ajaxify logout if SAML is enabled for CORS issues purpose
        saml = ', a[href="/user/logout"]';
    }
    $(document).on('click', 'a:not(li#gofast-flag-lang-switch a, #block-gofast-views-activity-stream-filters a, a.gofast-callto, #report_result a, .gofast_search_link, .gofast_space_filters.gofast_search_submit, .gofast_user_filters, .auto-refresh a, .form-wrapper .panel-heading a, .delete_message_ajax, .fivestar-widget a, .permalink, .forum-post-number a, .flag-link-toggle, .jsxc_menu a, .alert-block a, .field-revisions a, #block-gofast-test-handler-activity-stream-filters a, .cke_dialog a, .cke a, .nav.nav-tabs a, .nav.nav-pills a, #gofast-admin-settings a, .ui-popup-container a, .ui-footer a, :has(i.fa-cloud-download), .alfresco_download_edit_url, .mCSB_scrollTools_vertical.mCSB_scrollTools a, div#fullscreen-node > div.forum-post a, a.ctools-use-modal, a.use-ajax, #toolbar a, .xeditable-field, a[target=\"_blank\"], #revision-list a, #gofast-ldap-admin-entries button, .feed-icon a, #link_start_replication, .dynatable-sort-header, .gofast-non-ajax' + saml + ', #edit-saml-sp-drupal-login-links > a, .gofast-node-actions > a, .document__editable--field > a, .document__editable--label, #dropdown-node-dropdown, .contextual-actions > a, #gf-topbar-menu > ul > li > a:not(.brand-logo, .menu-profile), .menu-toggle:not(.mega-menu-item, .menu-profile), #blog-placeholder, li#gofast-mobile-lang-switch a)', function (e) {
      Gofast.xhrPool.abortAll();
      var href = $(this).attr('href') ? $(this).attr('href') : '';

      // You can put here url's to exclude from ajaxification

      // exclude href's who containt "spacesStore", links from version hitory on node or gofast_audit_xls for downloading xls audit file
      if (href.includes("SpacesStore") || href.includes("gofast_audit_xls")) {
        return;
      }

      if (href.indexOf('javascript') > 0){
        return;
      }

      if (href.indexOf('/admin/config') !== -1){
        return;
      }

      // exclude logout or redirect to version from ajaxification
      if (href.indexOf('/user/logout') == 0 || href.indexOf('/gofast/user/login/version/mobile') == 0 || href.indexOf('/gofast/user/login/version/standard') == 0) {
        return;
      }

      if ((href.indexOf('data:application') < 0 && href.indexOf('http') < 0 && href.indexOf('https') < 0) || href.indexOf(location.hostname) >= 0) {
        // !$(e.currentTarget).find(">:first-child").hasClass('gofast-title') is to avoid the event on the link <a href="#"> containing the first child <a href="/node/<id node>"> whose class is gofast-title or username
        // <a href="#"> contains another <a href="/node/<id node>"> is weird, fix this later in gofast_search module.
        if (!e.ctrlKey && !$(e.target).hasClass('facetapi-collapsible-handle') && !$(e.currentTarget).find(">:first-child").hasClass('gofast-title') && !$(e.currentTarget).find(">:first-child").hasClass('username')) {
          e.preventDefault();

          $('.navbar-nav li').removeClass('active');
          var parent = $(e.target).parent();
          if (parent.is('li')) {
            parent.addClass('active');
          }
          if (href) {
            if ($(e.target).parents('.form-autocomplete').length <= 0) {
              if ((
              href.indexOf('/user/logout') !== 0 && href.indexOf('/user/password') !== 0
              && href.indexOf('language=') < 0
              && href.indexOf('webform') < 0
              && href.indexOf('gofast/browser') < 0
              && window.location.pathname.indexOf('gofast/browser') < 0
              && href.indexOf('#') < 0
              )) {
                if (Gofast._settings.isEssential && !Gofast._settings.isMobileDevice){
                  Gofast.Essential.processEssentialAjax(href);
                }else{
                  Gofast.processAjax(href, true);
                }
              }
              else {
                if(Gofast._settings.isEssential && href.startsWith("/node/") && !Gofast._settings.isMobileDevice){
                  // avoid triggering twice essential navigation if there is a double-click
                  if (e.detail == 2) {
                    return;
                  }
                  Gofast.Essential.processEssentialNodeAjax(href);
                } else {
                  // This if is used to fix ajaxification when clicking on the "search string" in the search popup
                  if ((href.indexOf('#') === 0 && $(e.target).parents('#search-block-form').length === 1)) {
                    Gofast.processAjax('/search/solr/' + $(e.target).text(), true);
                }
                else {
                    //special case for search snippet hash
                    var hash = href.substr(href.indexOf('#'));
                    if (hash == '#search=') {
                      var searched_word = $(this).text();
                      var original_url = href.split(/[?#]/)[0];
                      href = original_url + "?search=" + searched_word;
  
                      }
                      Gofast.processAjax(href, true);
                  }
                }
              }
            }
          }
        }
      }
    });


  });
  Gofast.xhrPool = Gofast.xhrPool || {};
  Gofast.xhrPool.abortAll = function () {
    $.each(this, function (index, xhr) {
      if (typeof xhr !== 'function' && !$.isNumeric(index)) {
        xhr.abort();
        delete xhr[index];
      }
    });
  };
  Gofast.updateHistory = function(){
    let params = {}
    if(location.search){
      params = new URLSearchParams(location.search)
      params = Object.fromEntries(params)
    }
    Gofast.History = Gofast.History || [];
    Gofast.History = {href: location.href, pathname: location.pathname, hash: location.hash, params: params};
  }
  $(document).on("page-loaded", () => {
    if(location.pathname.startsWith("/subscriptions")){
      Drupal.CTools.Modal.showCtoolsModal("/modal/nojs/subscriptions", "/activity");
    }
  })
})(jQuery, Gofast, Drupal);

