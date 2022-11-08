(function ($, Gofast, Drupal) {

  Gofast._riot = function() {
    return {
      //############### PROPERTIES ###############
     
     // Our GoFAST current User
      User: Gofast.get('user'),
      
      // Is our Riot instancied
      isInit: false,
      
      // Is the right bloc expanded
      isExpanded: false,
      
      //Width of the right block when collapsed
      widthCollapsed: $('#conteneurIframe').width() < 100 ?  $('#conteneurIframe').width() : 68, // defined in css
      
      //Width of the right block when expended
      widthExpanded: 480,
      
      //Is our session ready in the browser
      sessionReady: false,
      
      //Our access token to Element
      accessToken: "",
      
      intervals : {
        //Interval to display Element
        displayInterval: null,
        
        //Interval to add event when we switch room
        switchRoomEventInterval: null,
        
        //Interval to minimize the Element client
        minimizedEventInterval: null,
        
        //Interval to apply bubble events
        bubbleEventsInteval: null,
        
        //Interval to process tooltips
        tooltipsInterval: null,
        
        //Interval to ckeck if the js session corresponds to the localstorage session
        //WARNING : This interval is not used as Gofast.sessionCheckInterval has been set
        //To prevent it from being destroyed
        sessionCheckInterval: null,

        //Wait for the full content of the window to be loaded before interferring with elements inside
        waitForFullMatrixLoadInterval: null,
      },
      
      // Settings to implement in the local storage for Element notifications
      notifications : {
        defaults : { //TO ENABLE AGAIN AUTOMATICALY
          notifications_enabled: true,        // Enable desktop notifications for this session
          audio_notifications_enabled: true,  // Enable audible notifications for this session
          notifications_body_enabled: true,   // Show message in desktop notification
        },
      },
      
      //############### METHODS ###############
      
      /*
       * Initialize Element, check if we have a session and display
      */
      init: function () {
        //Inform that we are initializing Element
        Gofast.Riot.isInit = true;
        
        //Preconfiguration
        Gofast.Riot.processHandleClickEvent();
        Gofast.Riot.preconfigure();
        
        //Log in
        if(!localStorage.riot_access_token){
          // Connect and save token to local storage.
          Gofast.Riot.login();
        }else{
          Gofast.Riot.checkLogin();
        }
        
        //Display Element
        Gofast.Riot.display();
      },
      
      /*
       *
      */
      destroy: function(collapse = true){      
        for (const interval in Gofast.Riot.intervals) {
          clearInterval(Gofast.Riot.intervals[interval]);
        }  
        
        if (collapse) {
          Gofast.Riot.collapse();
        }
        $("#IframeRiotBloc").attr("src", "")
        Gofast.Riot = null;
        Gofast.Riot = Gofast._riot();
      },
      
      /*
       * Preconfigure Element before instanciation
      */
      preconfigure: function(){
        // Sort rooms by activity. Always show rooms with unread messages first.
        localStorage['mx_listOrder_im.vector.fake.recent'] = 'IMPORTANCE'; // | NATURAL
        localStorage['mx_tagSort_im.vector.fake.recent'] = 'RECENT'; // | ALPHABETIC
        localStorage['mx_im.vector.fake.recent_sortBy'] = "RECENT"; // | ALPHABETIC

        // Same for user list.
        localStorage['mx_listOrder_im.vector.fake.direct'] = 'IMPORTANCE';
        localStorage['mx_tagSort_im.vector.fake.direct'] = 'RECENT';
        localStorage['mx_im.vector.fake.direct_sortBy'] = "RECENT"; // | ALPHABETIC

        // Localization
        localStorage['mx_local_settings'] = JSON.stringify({language: Drupal.settings.gofast.language});

        // Browser compatiblity check
        Gofast.Riot.checkBrowserCompatibility();
        
        //Force minimized client
        localStorage['mx_lhs_size'] = 0;
        
        //Copy Riot token if available for Element to consume it to log in
        if(typeof localStorage['riot_access_token'] == "string"){
          localStorage['mx_access_token'] = localStorage['riot_access_token'];
        }
      },
      
      /*
       * We make the same browser compatibility check Element does
       * except for the ES2020 check which may fail at times even with modern browsers
       * @see checkBrowserFeatures function in src/vector/index.ts in Element source code
       */
      checkBrowserCompatibility: function(){
        const tests = [
          typeof window.Promise.prototype.finally === "function",
          window.RegExp.prototype && !!Object.getOwnPropertyDescriptor(window.RegExp.prototype, "dotAll"),
          typeof window.Object.fromEntries === "function"
        ];
        const isBrowserCompatible = !tests.includes(false);
        if (isBrowserCompatible) {
          window.localStorage.setItem('mx_accepts_unsupported_browser', String(true));
        }
      },
      
      /*
       * Ask Element for a session
      */
      login: function () {
        $.ajax({
          url: "https://" + Drupal.settings.GOFAST_COMM + "/_matrix/client/r0/login",
          type: "POST",
          contentType: "application/json; charset=utf-8",
          data: JSON.stringify({user: Gofast.Riot.User.name.toLowerCase(), password: Drupal.settings.TOKEN_RIOT, type: "m.login.password"}),
          dataType: "json",
          success: Gofast.Riot.onLogin,
          error: Gofast.Riot.handleFailure,
          timeout: Gofast.Riot.handleFailure,
        });
      },
      
      /*
       * Check if our element session is valid
      */
     checkLogin: function(){
      $.ajax({
        url: "https://" + Drupal.settings.GOFAST_COMM + "/_matrix/client/r0/account/whoami?access_token=" + localStorage.riot_access_token,
        type: 'GET',
        dataType: 'json',
        success: Gofast.Riot.onLogin,
        error: Gofast.Riot.login
      });
     },
      
      /*
       * After getting an Element session, save it in the browser
      */
      onLogin: function (data) {
        if(data.access_token){
          //Save the session in the browser
          Gofast.Riot.save_user(data);
          
          //Save the session in the backend
          $.ajax({
            url: window.location.origin + '/SaveRiotToken',
            type: 'POST',
            data: {token: data.access_token},
            dataType: 'html',
          });
          
          Gofast.Riot.accessToken = data.access_token;
        }else{
          Gofast.Riot.accessToken = localStorage.riot_access_token;
        }
        
        //Our session is ready
        Gofast.Riot.sessionReady = true;
        
        //Start to check for session changes (other tabs etc..)
        Gofast.Riot.startSessionCheck();
      },
      
      /*
       * Check periodically if we have been disconnected on another tab
       * Try to switch to a new session
      */
      startSessionCheck: function(){
        clearInterval(Gofast.Riot.intervals.sessionCheckInterval);
        Gofast.Riot.intervals.sessionCheckInterval = setInterval(function(){
          if(!localStorage.riot_access_token && Gofast.Riot.isInit){
            Gofast.Riot.destroy();
          }
          else if(localStorage.riot_access_token && localStorage.riot_access_token != Gofast.Riot.accessToken){
            if(Gofast.Riot.isInit){
              Gofast.Riot.destroy();
            }
            Gofast.Riot.init();
          }
        }, 1000);
      },
      
      /*
       * Save our Element session in the local storage
      */
      save_user: function (data) {
        localStorage.mx_access_token = data.access_token;
        localStorage.riot_access_token = data.access_token;
        localStorage.mx_user_id = data.user_id;
        localStorage.mx_device_id = data.device_id;
        localStorage.mx_hs_url = data['well_known']['m.homeserver'].base_url;
      },

      handleFailure: function(){
        // first we check if the COMM server is up
        const pingCommEndpoint = "https://" + Drupal.settings.GOFAST_COMM;
        $.get(pingCommEndpoint).done(function(data, status) {
          if (status != "success") {
            Gofast.toast(Drupal.t("The Element server is not available. Please try again later.", {}, {context: "gofast:gofast_riot"}), "error");
            Gofast.Riot.destroy();
            return;
          }
        });
        // if COMM server is up, we add a reload button to be able to re-init the riot block from scratch
        $("#IframeRiotBloc").attr("src", "");
        $("#IframeRiotBloc").hide();
        $(".gofastRiotReload").removeClass("d-none");
      },
      
      /*
       * Element is ready, display it
      */
      display: function(){
        //Wait for our session to be ready
        clearInterval(Gofast.Riot.intervals.displayInterval)
        let displayAttemptsCounter = 0;
        Gofast.Riot.intervals.displayInterval = setInterval(async function(){
          // if it has been more than 30 seconds we're trying to connect
          if (displayAttemptsCounter > 100) {
            Gofast.Riot.handleFailure();
            clearInterval(Gofast.Riot.intervals.displayInterval);
            return;
          }
          if(!Gofast.Riot.sessionReady){
            displayAttemptsCounter++;
            return;
          }
          
          //Display Element
          $(".gofastRiotReload").addClass("d-none");
          $("#IframeRiotBloc").attr("src", "/sites/all/libraries/riot/index.html?v=6")

          clearInterval(Gofast.Riot.intervals.displayInterval);

          //Wait for content to be fully loaded
          await new Promise((resolve, reject) => {
            Gofast.Riot.intervals.waitForFullMatrixLoadInterval = setInterval(() => {
              if (!document.querySelector("#IframeRiotBloc") || !document.querySelector("#IframeRiotBloc").contentWindow.document.querySelector(".mx_MatrixChat ")) {
                return;
              }
              clearInterval(Gofast.Riot.intervals.waitForFullMatrixLoadInterval);
              //Our session is ready, display and process Element
              Gofast.Riot.applyBubbleEvents();
              Gofast.Riot.processTooltips();
              Gofast.Riot.initFetchEvent('#IframeRiotBloc');
              Gofast.Riot.initFetchListener();
              resolve();
            }, 100);
          });
        }, 300);
      },
      
      /*
       * Check our bubble elements and check if they have the click event to open the client automatically
      */
      applyBubbleEvents: function(){
        //Constantly (every 1.5s) check if the bubbles are clickable
        clearInterval(Gofast.Riot.intervals.bubbleEventsInteval);
        
        Gofast.Riot.intervals.bubbleEventsInteval = setInterval(function(){
          var $iframe_body = $("#IframeRiotBloc").contents().find('body');
          
          $iframe_body.find('div.mx_RoomTile,.mx_AccessibleButton.mx_RoomSublist_auxButton').not("click-expand-processed").on('click', function() {
            if(!Gofast.Riot.isExpanded){
              Gofast.Riot.expand();
            }
          }).addClass("click-expand-processed");
        }, 1500);
      },
      
      processTooltips: function(){

        Gofast.Riot.intervals.tooltipsInterval = setInterval(function() {
          if (!$("#IframeRiotBloc").contents().find('body').find(".mx_RoomSublist_minimized").length || $("#IframeRiotBloc").contents().find('body').find(".mx_RoomSublist_minimized .mx_RoomSublist_skeletonUI").length > 0) {
            return;
          }
          
          // Make tooltips always visible regardless of the bloc being collapsed or not.
          var $tooltip;

          // Apply this css (iframe scope) regardless of riot theme. This hides the
          // default tooltip container that cannot overflow from the iframe when the
          // bloc is collapsed and also hides the horizontal resize handle that makes
          // the pointer buggy and is useless in bloc mode (not in conversation page).
          var $head = $("#IframeRiotBloc").contents().find('head');
          var style = '.mx_Tooltip_wrapper, .mx_ResizeHandle_horizontal { display:none; }';
          $('<style type="text/css">' + style + '</style>').appendTo($head);

          var $iframe_body = $("#IframeRiotBloc").contents().find('body');
          $iframe_body.on('mouseover', 'div.mx_AccessibleButton', function(e) {
            setTimeout(function() {
              // Remove any previous tooltip if any.
              if ($tooltip) {
                $tooltip.remove();
              }

              if (Gofast.Riot.isExpanded) {
                // Nothing to do, just display original tooltip.
                $(e.delegateTarget).find('.mx_Tooltip_wrapper').css('display', 'block');
                return;
              }

              // We make a copy, no detach() otherwise react will throw an error
              // when trying to remove the compoenent.
              $tooltip = $(e.delegateTarget).find('.mx_Tooltip').clone();

              if (!$tooltip.length) {
                // hover intent was not long enough to make the toolip appear OR there is no mx_Tooltip
                if (typeof $(e.delegateTarget).attr("aria-label") != "undefined" && typeof $(e.delegateTarget).attr("title") == "undefined") {
                  $(e.delegateTarget).attr("title",  $(e.delegateTarget).attr("title") ??  $(e.delegateTarget).attr("aria-label"));
                }
                return;
              }

              // Adjust styles according to bloc state.
              var top = parseInt($tooltip.css('top')) + 50;
              var right = parseInt($tooltip.css('right'));

              $tooltip.css({
                top: top + 'px',
                left: 'unset',
                right: right + 10 + 'px',
              });

              // Insert the tooltip into the DOM outside the iframe so it can expand
              // properly.
              $tooltip.appendTo('#conteneurIframe');
            }, 100);
          });

          $iframe_body.on('mouseout', 'div.mx_RoomTile,.mx_RoomSublist_headerText', function(e) {
            if (!$tooltip.length && typeof $(e.delegateTarget).attr("aria-label") != "undefined" && typeof $(e.delegateTarget).attr("title") != "undefined") {
              $(e.delegateTarget).removeAttr("title");
            }
            if ($tooltip) {
              $tooltip.remove();
              $tooltip = null;
            }
          });
          clearInterval(Gofast.Riot.intervals.tooltipsInterval);
        });
      },

      /** temporary fix, issue opened at Element Web: https://github.com/vector-im/element-web/issues/22951 */
      generateDownloadLink: function(endpoint) {
        const link = document.createElement('a');
        link.setAttribute("href", endpoint);
        link.setAttribute("target", "_blank");
        link.setAttribute('download', "download");
        document.body.appendChild(link);
        link.click();
        document.body.removeChild(link);
      },

      /** temporary fix, issue opened at Element Web: https://github.com/vector-im/element-web/issues/22951 */
      initFetchListener: function() {
          // GOFAST-8052 - make download button work inside the iframe
          document.addEventListener("riotFetchRequest", ({detail}) => {
            if(detail.endpoint.includes("media/r0/download")) {
              this.generateDownloadLink(detail.endpoint);
              // there are two download link elements we have to set
              const downloadLinkHoverable = detail.downloadLinkElement.closest(".mx_EventTile").querySelector(".mx_MessageActionBar_downloadButton");
              const downloadLinkElement = detail.downloadLinkElement.closest(".mx_EventTile").querySelector(".mx_MFileBody");
              [downloadLinkHoverable, downloadLinkElement].forEach((el) => {
                el.addEventListener("click", e => {
                  e.preventDefault();
                  this.generateDownloadLink(detail.endpoint);
                });
              });
            }
          });
      },

      /** temporary fix, issue opened at Element Web: https://github.com/vector-im/element-web/issues/22951 */
      initFetchEvent: function(selector) {
          // override fetch method of iframe in order to be able to listen to AJAX calls made from the instance of the fetch API used by Element Web
          const iframeWindow = document.querySelector(selector).contentWindow;
          let mousePosX = 0;
          let mousePosY = 0;
          iframeWindow.document.addEventListener("mousemove", e => {
            mousePosX = e.clientX;
            mousePosY = e.clientY;
          });
          (function(riotWindow, fetch) {
            if (typeof fetch !== 'function') return;
            riotWindow.fetch = function() {
              const downloadLinkElement = iframeWindow.document.elementFromPoint(mousePosX, mousePosY);
              const result = fetch.apply(this, arguments);
              riotWindow.parent.document.dispatchEvent(new CustomEvent("riotFetchRequest", {
                detail: {endpoint: arguments[0], downloadLinkElement}
              }));
              return result;
            }
          
          }(iframeWindow, iframeWindow.fetch));
      },
      
      processHandleClickEvent: function(){
        $('#animateRiot').once('animated', function () {
          $(this).click(Gofast.Riot.onHandleClick);
        });
        $(".gofastRiotReload").on("click", function(){
          Gofast.Riot.destroy(false);
          Gofast.Riot.isInit = false; // this will not unset the login token in local storage so sessions will remain synced after init
          Gofast.Riot.init();
        });
      },
      
      /*
       * Handle the click on the expand/collapse bubble button
      */
      onHandleClick: function () {
        if (Math.floor($('#conteneurIframe').innerWidth()) <= Gofast.Riot.widthCollapsed) {
          Gofast.Riot.expand();
        }
        else {
          Gofast.Riot.collapse();
        }
      },
      
      /*
       * Expand de right block
      */
      expand: function () {
        var w = Gofast.Riot.widthExpanded;
        $('#conteneurIframe').animate({width: w + 'px'});
        Gofast.Riot.isExpanded = true;
      },
      
      /*
       * Collapse the right block
      */
      collapse: function () {
        var w = Gofast.Riot.widthCollapsed;
        $('#conteneurIframe').animate({width: w + 'px'});
        Gofast.Riot.isExpanded = false;
      },
    };
  };
  
  $(document).ready(function(){
    //Initialize our Riot library
    Gofast.Riot = Gofast._riot();
    //Initialize Element
    Gofast.Riot.init();
  });

})(jQuery, Gofast, Drupal, ifvisible);
