(function ($, Gofast, Drupal) {

  Gofast.exclude_ajax_url.push("/user/password");

  Gofast.processAjax = function (href, isStateChange) {
    if (href.indexOf('javascript') != -1 || href == "#") {
      return;
    }

    //each module can fill this global variable to excluse some url from ajaxification
    if (Gofast.exclude_ajax_url.indexOf(href) != -1) {
      window.location.href = href;
      return;
    }

    //before ajax navigate, remove fullscreen if any
    if (typeof sidebar === 'undefined') {
      var sidebar = $('aside');
    }

    if (sidebar.css('display') != 'block') {
      if (Gofast.success_fullscreen != true) {
        Gofast.toggle_fitscreen(null);
      }
      else {
        Gofast.success_fullscreen = false;
      }
    }

    href = decodeURI(decodeURI(href));

    var href_ajax = "gofast_ajaxification/nojs";

    if ($('.popover').length > 0) {
      $('.popover').popover('hide');
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

      if (location.search) {
        var parts = location.search.substring(1).split('&');

        for (var i = 0; i < parts.length; i++) {
          var nv = parts[i].split('=');
          if (!nv[0])
            continue;
          params[nv[0]] = nv[1] || true;
        }
      }
      Gofast.History.push({href: location.href, pathname: location.pathname, hash: location.hash, params: params});

    };
    $("#ajax_button").trigger("click"); // triggers the ajax object that handles the xhr.
    $(document).trigger('ajax-navigate'); // triggers en event with document as context so other module can react on ajax nav.
    Gofast.ajaxingNav = true;

    $("#ajax_button").remove();

    var title = "GoFast";
    Gofast.currentPageTitle = Drupal.settings.title ? Drupal.settings.title : title;

    // GOFAST-6737 - Double escape forward slashes
    if (href.startsWith('/search/solr/')) {
      var terms = href.replace(/^\/search\/solr\//, '');
      terms = terms.replace(/\/|%2F/g, '%252F');
      href = '/search/solr/' + terms;
    }

    if (History.pushState && (href.indexOf(location.origin + "/gofast/node-info") == -1 && href.indexOf(location.origin + "/gofast/delete_space") == -1)) {
      if (href.indexOf('?') !== -1) { //Need to push the path without parameters, and then, the parameters
        History.pushState(null, "", href.substring(0, href.indexOf('?')));
        History.pushState(null, "", href.substring(href.indexOf('?')));
      }
      else {
        History.pushState(null, "", href);
      }
    }

    document.title = Gofast.currentPageTitle;

    $(document).trigger('afterAjaxification');
    window.scrollTo(0, 0);
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
    //Will contain the last URL to use in navigation events
    var params = {};


    //Disable ajax if we are in a temporary session in order to change password
    if(typeof Drupal.settings.pass_reset != "undefined"){
        return;
    }

    if (location.search) {
      var parts = location.search.substring(1).split('&');
      for (var i = 0; i < parts.length; i++) {
        var nv = parts[i].split('=');
        if (!nv[0])
          continue;
        params[nv[0]] = nv[1] || true;
      }
    }
    Gofast.History = [{href: location.href, pathname: location.pathname, hash: location.hash, params: params}];

    $(window).bind('hashchange', function (event) { //Register any URL change
      var params = {};

      if (location.search) {
        var parts = location.search.substring(1).split('&');

        for (var i = 0; i < parts.length; i++) {
          var nv = parts[i].split('=');
          if (!nv[0])
            continue;
          params[nv[0]] = nv[1] || true;
        }
      }
      Gofast.History.push({href: location.href, pathname: location.pathname, hash: location.hash, params: params});
    });

    // ajax_call when user use back/next on the browser
    window.addEventListener('popstate', function (event) {
      var oldHistory = {};
      if (typeof Gofast.History[Gofast.History.length - 1] !== "undefined") {
        oldHistory = Gofast.History[Gofast.History.length - 1];
      }

      //Check if we have to process an ajax navigation
      if (oldHistory.pathname !== location.pathname) {
        //We need to navigate in ajax to another page
        Gofast.processAjax(location.href);
      }
      else {
        //A navigation occured but we don't need to switch page. Call module to handle this event
        $(document).trigger('urlChanged', oldHistory);
      }
    }, false);

    $(document).on('submit', '#search-block-form ', function (e) {
      e.preventDefault();
      Gofast.xhrPool.abortAll();
      var params = '';
      var retain_filters = $("#facetapi_search_filters").find("[item=retain-filters]").attr("checked");
      if (retain_filters === "checked") {
        var uri = decodeURIComponent(decodeURIComponent($(document)[0].URL));
        var fq = decodeURIComponent(uri).lastIndexOf('?f[0]');
        if (fq != -1) {
          params = uri.substr(fq);
        }
      }
      var terms = $(this).find('input').filter('[type="text"][name="search_block_form"]').val();
      // GOFAST-6737
      terms = encodeURIComponent(terms);
      Gofast.processAjax('/search/solr/' + terms + params, true);
    });

    $(document).on('submit', '#search-form', function (e) {
      e.preventDefault();
      Gofast.xhrPool.abortAll();
      var params = '';
      var retain_filters = $("#facetapi_search_filters").find("[item=retain-filters]").attr("checked");
      if (retain_filters === "checked") {
        var uri = decodeURIComponent(decodeURIComponent($(document)[0].URL));
        var fq = decodeURIComponent(uri).lastIndexOf('?f[0]');
        if (fq != -1) {
          params = uri.substr(fq);
        }
      }
      var terms = $(this).find('[name=keys]').val();
      // GOFAST-6737
      terms = encodeURIComponent(terms);
      Gofast.processAjax('/search/solr/' + terms + params, true);
    });

    var saml = "";

    if(Drupal.settings.saml_enabled){
        //Don't ajaxify logout if SAML is enabled for CORS issues purpose
        saml = ', a[href="/user/logout"]';
    }
    $(document).on('click', 'a:not(div#gofast-lang-switch a, #block-gofast-views-activity-stream-filters a, a.gofast-callto, #report_result a, .gofast_search_link, .gofast_space_filters.gofast_search_submit, .gofast_user_filters, .auto-refresh a, .form-wrapper .panel-heading a, .delete_message_ajax, .fivestar-widget a, .permalink, .forum-post-number a, .flag-link-toggle, .jsxc_menu a, .alert-block a, .field-revisions a, #block-gofast-test-handler-activity-stream-filters a, .cke_dialog a, .cke a, .nav.nav-tabs a, #gofast-admin-settings a, .ui-popup-container a, .ui-footer a, :has(i.fa-cloud-download), .alfresco_download_edit_url, .mCSB_scrollTools_vertical.mCSB_scrollTools a, div#fullscreen-node > div.forum-post a, a.ctools-use-modal, a.use-ajax, #toolbar a, .xeditable-field, .main-container a[target=\"_blank\"], #revision-list a, #gofast-ldap-admin-entries button, .feed-icon a, #link_start_replication, .dynatable-sort-header, .gofast-non-ajax' + saml + ', #edit-saml-sp-drupal-login-links > a)', function (e) {
      Gofast.xhrPool.abortAll();
      var href = $(this).attr('href') ? $(this).attr('href') : '';

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
              if ((href.indexOf('/user/logout') !== 0 && href.indexOf('/user/password') !== 0 && href.indexOf('language=') < 0 && href.indexOf('webform') < 0 && href.indexOf('gofast/browser') < 0 && window.location.pathname.indexOf('gofast/browser') < 0 && href.indexOf('#') < 0)) {
                Gofast.processAjax(href, true);
              }
              else {
                // This if is used to fix ajaxification when clicking on the "search string" in the search popup
                if ((href.indexOf('#') === 0 && $(e.target).parents('#search-block-form').length === 1)) {
                  Gofast.processAjax('/search/solr/' + $(e.target).text(), true);
                }
                else {
                  if (href.indexOf('comment') >= 0) {
                    var hash = href.substr(href.indexOf('#'));
                    Gofast.scrollToComment(hash);
                  }
                  else {
                    //spacial case for search snipper hash
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
})(jQuery, Gofast, Drupal);

