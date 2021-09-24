
(function ($, Gofast, Drupal, Tab) {

  var observeDOM = (function(){
    var MutationObserver = window.MutationObserver || window.WebKitMutationObserver;

    return function( obj, callback ){
      if (!obj || obj.nodeType !== 1)
        return;

      if (MutationObserver){
        // define a new observer
        var obs = new MutationObserver(function(mutations, observer){
          callback(mutations);
        })
        // have the observer observe foo for changes in children
        obs.observe(obj, { childList:true, subtree:true });
      }

      else if (window.addEventListener){
        obj.addEventListener('DOMNodeInserted', callback, false);
        obj.addEventListener('DOMNodeRemoved', callback, false);
      }
    }
  })();

  function setDisplayName(userName) {
    var riotNameEncode = encodeURIComponent(localStorage.mx_user_id);

    $.ajax({
      url: "https://" + Drupal.settings.GOFAST_COMM + "/_matrix/client/r0/profile/" + riotNameEncode + "/displayname?access_token=" + localStorage.mx_access_token,
      type: "PUT",
      contentType: "application/json",
      data: JSON.stringify({"displayname": userName}),
      dataType: "json",
      success: function (data) {
//        console.log(data);
      },
      error: function (err) {
        console.error('Gofast Riot', arguments);
      }
    });
  }

  function SaveUserRiot(data) {
    localStorage.mx_access_token = data.access_token;
    localStorage.mx_user_id = data.user_id;
    localStorage.mx_device_id = data.device_id;
    localStorage.mx_hs_url = data['well_known']['m.homeserver'].base_url;
  }

  Gofast._riot = function() {
    return {
      unloaded: true,

      User: Gofast.get('user'),
      nbConnexion: 0,
      iframeRefresh: 0,
      UserTimeLogin: 0,

      isExpanded: false,
      isCollapsed: true,
      widthCollapsed: $('#conteneurIframe').width(), // defined in css
      widthExpanded: 480,

      _reset: function () {
        this._reset.maxCall = this._reset.maxCall || 1;

        $('#IframeRiotBloc').hide();
        $('#blocConnexionRiot').show();

        // Prevent infinite loop (ie. if for some reason matrix is down, or if
        // the browser has a corrupted indexedDB and cannot recover).
        if (this._reset.called && this._reset.called >= this._reset.maxCall) {
          console.error('Gofast Riot', '_reset() called more than ' + this._reset.maxCall + ' times.');
          Gofast.Riot.errorDialog();
          return;
        }

        console.log('Gofast Riot', '_reset()');

//        // Assuming we may have a corrupted indexed DB and since we can't check
//        // all the data, the logic here is that if any thing is missing, then
//        // everything else need to be missed as well to prevent unexpected
//        // behavior.
//
//        [ // Force clean indexed DB
//          'matrix-js-sdk:crypto',
//          'matrix-js-sdk:riot-web-sync',
//          'logs'
//        ].forEach(function (dbName) {
//          window.indexedDB.deleteDatabase(dbName);
//        });

        // Will refresh iframe and trigger load event, Gofast.Riot.init, login etc.
        Gofast.Riot.logout();

        // Clean matrix localStorage as well before login is called.
        for (var prop in localStorage) {
          prop.startsWith('mx_') && delete localStorage[prop];
        }

        Gofast.Riot.unloaded = true;
        this._reset.called = (this._reset.called || 0) + 1;
      },

      errorDialog: function () {
        $('#IframeRiotBloc').hide();

        var imgSrc = '/sites/all/libraries/riot/img/feather-customised/warning-triangle.d050a38.svg';
        var warning = '<img src="' + imgSrc + '" width="32" height="32">';
        var lang = Gofast.Riot.User.language in {0: 'fr', 1: 'en'} ? Gofast.Riot.User.language : 'en';
        var docUrl = 'https://gofast-docs.readthedocs.io/'+ lang + '/latest/docs-gofast-users/doc-gofast-problemes-connus.html#volet-du-chat-vide-et-hors-connexion'
        var forumUrl = 'https://community.ceo-vision.com/categories';
        var replacements = {
          '!here': '<a href="' + docUrl + '">' + Drupal.t('here') + ' </a>',
          '!forums': '<a href="' + forumUrl + '">' + Drupal.t('User Forums') + ' </a>'
        };

        var msg = Drupal.t('Your browser is encountering issues with the Chat.') + '<br><br>'
                + Drupal.t('Please find the solution !here, and do not hesitate to ask your questions in our !forums.', replacements);

        $('#blocConnexionRiot p').html(warning + '<br><br>' + msg);
        $('#blocConnexionRiot').show();
      },

      checkHTML: function () {
        var $mxChat = $('#IframeRiot,#IframeRiotBloc').contents().find('section#matrixchat');
        Gofast.Riot.unloaded = !($mxChat.length && $mxChat.find('div.mx_MatrixChat').length);
        return !Gofast.Riot.unloaded;
      },

      onHandleClick: function () {
        if (Math.floor($('#conteneurIframe').innerWidth()) <= Gofast.Riot.widthCollapsed) {
          Gofast.Riot.expand();
        }
        else {
          Gofast.Riot.collapse();
        }
      },

      expand: function () {
        var w = Gofast.Riot.widthExpanded;
        $('#conteneurIframe').animate({width: w + 'px'});
        Gofast.Riot.isExpanded = true;
        Gofast.Riot.isCollapsed = false;

        // Just in case (done in iframe load handler).
        $('iframe#IframeRiotBloc').css('visibility', 'visible');

        // If nothing has loaded
        if (Gofast.Riot.unloaded && Gofast.Riot.checkHTML() === false) {
          $('#IframeRiotBloc').hide();
          $('#blocConnexionRiot').show();

          if (this._reset.called) {
            Gofast.Riot.errorDialog();
          }
        }
      },

      collapse: function () {
        var w = Gofast.Riot.widthCollapsed;
        $('#conteneurIframe').animate({width: w + 'px'});
        Gofast.Riot.isExpanded = false;
        Gofast.Riot.isCollapsed = true;
        $('#blocConnexionRiot').hide();
      },

      /**
       * Add a class to the chat view that corresponds to whether it belongs to
       * a room or a user (rooms|people).
       */
      tagView: function (active) {
        var $frames = $('iframe#IframeRiotBloc,iframe#IframeRiot').contents();
        var $active = active && $(active) || $frames.find('.mx_RoomTile_selected');
        var view = $active.closest('.mx_RoomSublist').attr('aria-label') || '';
        var tags = { 'Rooms': 'en', 'Salons': 'fr', 'Groepsgesprekken': 'nl' };
        $frames.find('.mx_MatrixChat').toggleClass('people', !(view in tags) );
      },

      preventFocusStealing: function () {
        var $mxChat = $(this).contents().find('#matrixchat');

        $mxChat.once('focusin', function() {
          $(this).on('focusin', function(e) {
            if (Gofast.Riot.isCollapsed) {
              // Riot is actually stealing the focus.
              Gofast.Riot._stealFocus = true;
            }
            else {
              // We don't know, consider it's legit.
              Gofast.Riot._stealFocus = false;
            }
          });
        });

        $(window).once('focusout', function () {
          $(this).on('focusout', function (e) {
            if (Gofast.Riot.isCollapsed) {
              // Let the 'focusin' handler run.
              setTimeout(function(){
                if (Gofast.Riot._stealFocus) {
                  // Some text may have been typed in the wrong input element.
                  var _$input = $mxChat.find('.mx_BasicMessageComposer_input'),
                      _text = _$input.text();

                  // Distinguish previously typed in text (saved locally before a
                  // refresh) from the stolen one.
                  if (Gofast.Riot._msgInputText) {
                    _text = _text.substr(Gofast.Riot._msgInputText.length)
                  }

                  // If any, put this text back to the original input element.
                  if (_text) {
                    _$input[0].innerText = Gofast.Riot._msgInputText || '';
                    if ($(e.target).prop('tagName') === 'INPUT') {
                      var text = $(e.target).val();
                      $(e.target).val(text + _text);
                    }
                  }

                  // Give the focus back to the original element.
                  $(e.target).focus();

                  // Always reset the flag to prevent infinite loop.
                  Gofast.Riot._stealFocus = false;
                }
              }, 1);
            }
          });
        });
      },

      preventDisplayBug: function () {
        var me = this;
        $(me).contents().find('#matrixchat').once('observeDOM', function () {
          observeDOM(this, function(mut){
            var errorClass = {
              mx_GenericErrorPage: 1,   // ugly dialogs, won't help the user that much
              mx_CompatibilityPage: 1,  // browser is purportedly missing required features.
              mx_ErrorView: 1           // browser is purportedly missing required features (1.7.3).
            };

            try {
              mut.forEach(function (r) {
                var t = 100; // ms

                if (r.addedNodes[0]) {
                  var nodeClass = r.addedNodes[0].className;

                  // Check for error messsages.
                  if (nodeClass in errorClass) {
                    var errorView = r.addedNodes[0];
                    var [error, msg] = errorView.innerText.split("\n", 2);

                    switch (error) {
                      // break in case where we may want to display the error message
                      case '<some exception>':
                        break;

                      // Otherwise
                      case 'Unsupported browser':
                      case 'Sorry, your browser is not able to run Riot.':
                      default:
                        // Immediately break the loop then reset all (see catch).
                        throw new (function(e, m) {
                          this.error = e;
                          this.message = m;
                          this.name = nodeClass;
                        })(error, msg);
                    }
                  }
                  else if (r.target.id === 'matrixchat') {
                    // at least one element is loading
                    Gofast.Riot.unloaded = false;
                    $('#blocConnexionRiot').hide();
                    $('#IframeRiotBloc').show();
                  }

                  // msg composer is loaded along with .mx_MessageComposer_avatar
                  // element, we can't access it directly since it's an HTML string.
                  if (r.addedNodes[0].className === 'mx_MessageComposer_avatar') {
                    // 'load' event does not bubble so we trigger here a custom.
                    $(r.addedNodes[0]).trigger('lazyload');

                    var msgComposer = r.nextSibling.children && r.nextSibling.children[1],
                        msgInput = msgComposer && msgComposer.children && msgComposer.children[1];

                    // Keep an eye on previously typed in text if any.
                    if (msgInput && Gofast.Riot.isCollapsed) {
                      Gofast.Riot._msgInputText = msgInput.innerText;
                    }

                    // Leave some time for msg elements to load then auto-resize
                    // iframe then reset (in case msgInput got wrong overflow-x).
             /*        setTimeout(function() {
                       $(me).css('width', 'auto');
                       setTimeout(function() {
                         $(me).css('width', '100%');
                       }, t);
                    }, t); */
                  }

                  // When section#matrixchat elements are loaded, prevent wrong
                  // overflow on Firefox.
                  if (r.target.id === 'matrixchat' && r.addedNodes[0].className === 'mx_MatrixChat_wrapper') {
                    // Leave some time for the elements to populate the DOM.
                    var fixOverflow = function() {
                      $(r.target).css('overflow', 'unset');
                    };
                    // must occur last, ugly but better than an overflow bug.
                    setTimeout(fixOverflow, 3*t);
                    setTimeout(fixOverflow, 10*t);
                    setTimeout(fixOverflow, 20*t);
                  }
                }
              });
            }
            catch (e) {
              if (e.name in errorClass) {
                console.error('Gofast Riot', e.name);
                console.error('Gofast Riot', e.error, e.message);
                // Even if _reset already run once, riot/browser has better
                // chance to recover after the error message pops up so give
                // it another try after 15 seconds delay if still necessary.
                Gofast.Riot._reset();
                setTimeout(function() {
                  if (!Gofast.Riot.checkHTML()) {
                    Gofast.Riot._reset.maxCall = 2;
                    Gofast.Riot._reset();
                  }
                }, 15000);
              }
              else {
                // javascript error
                throw e;
              }
            }
          });
        });

        // We need to know when panels or dialogs are loaded so we can attach
        // event handler on transient DOM elements (ie. the settings panel or
        // the annoying dialog).
        var $iframe = $('#IframeRiot,#IframeRiotBloc').contents().find('body');
        $iframe.once('observeDOM', function () {
          observeDOM(this, function(mut){
            mut.forEach(function (r) { // r as 'record'
              if (r.addedNodes[0]) {
                // When settings panel loaded.
                if (r.addedNodes[0].id === 'mx_Dialog_StaticContainer') {
                  var $panel = $(r.addedNodes[0]);
                  $panel.once('observeDOM', Gofast.Riot.notifications.onSettingsDialog);
                  return;
                }

                // When an error dialog pops up detached from its container.
                if (r.addedNodes[0].className && r.addedNodes[0].className.includes('mx_ErrorDialog')) {
                  // Let children elements populates the dialog.
                  setTimeout(Gofast.Riot.handleDialog, 100, dialog);
                  return;
                }

                // When a dialog pops up (coming within its container)
                if (r.addedNodes[0].id === 'mx_Dialog_Container') {
                  var container = r.addedNodes[0],
                      wrapper = container.children && container.children[0],
                      dialog = wrapper && wrapper.children && wrapper.children[0];
                  if (dialog) {
                    // Let children elements populates the dialog.
                    setTimeout(Gofast.Riot.handleDialog, 100, dialog);
                  }
                  return;
                }

                // When a dialog pops up (dialog wrapper comes separated from its container)
                if (r.addedNodes[0].className && r.addedNodes[0].className.includes('mx_Dialog_wrapper')) {
                  var wrapper = r.addedNodes[0];
                      dialog = wrapper && wrapper.children && wrapper.children[0];
                  if (dialog) {
                    // Let children elements populates the dialog.
                    setTimeout(Gofast.Riot.handleDialog, 100, dialog);
                  }
                }
              }
            });
          });
        });
      },

      handleDialog: function (dialog) {
        if (typeof dialog.innerText !== 'string') {
          console.error('Gofast Riot', 'error', 'handleDialog');
          return;
        }

        var [title, msg] = dialog.innerText.split("\n", 2);
        var string = (title || '')
                .toLowerCase()
                .replace('à', 'a')
                .replace('é', 'e')
                .replace(/gofast|riot|element/g, '')
                .trim();

        switch (string) {
          case '':
            // Content is coming separated from this dialog object (another record).
            break;

          case 'missing session data':
          case 'donnees de session manquantes':
          case 'donnees de la session manquantes':
          case 'sessiegegevens ontbreken':
            // Handle error 'Missing session data', spare the user
            // having to sign out and back in manually.
            console.error('Gofast Riot', title, msg);
            Gofast.Riot._reset();
            break;

          case 'signed out':
          case 'deconnecte':
          case 'afgemeld':
            // If user just logged out, it's normal, otherwise reset.
            if (!Gofast.getCookie('gofast_user')) {
              // User is logged out and his access token is now invalid,
              // so we can prevent a useless /whoami request on the
              // next login.
              delete localStorage.mx_access_token;
            }
            else {
              console.error('Gofast Riot', title, msg);
              Gofast.Riot._reset();
            }
            break;

          // @todo check fr, add others
          case 'updating':
          case 'mise a jour':
          case 'mise a jour d\'':
          case 'mise a jour de':
          case 'wordt bijgewerkt':
            setTimeout(function() {
              // User does not have to see this.
              var $btn = $(dialog).find('button.mx_Dialog_primary');
              $btn.length && $btn.click();
              console.log('Gofast Riot', 'skipping dialog:', title, msg);
            }, 1000);
            break;

          case 'another error':
            // do something.

          default:
            if (!title.match(/^(?:signed out|deconnecte)/)) {
              console.error('Gofast Riot', 'unhandled mx dialog', dialog);
            }
        }
      },

      sessions: {
        maxAge: 36000, // 10h in seconds

        check: function() {
          // Get sessions
          $.ajax({
            url: 'https://' + Drupal.settings.GOFAST_COMM + '/_matrix/client/r0/devices',
            type: 'GET',
            contentType: 'application/json; charset=utf-8',
            beforeSend: function (xhr) {
              xhr.setRequestHeader('Authorization', 'Bearer ' + localStorage.mx_access_token);
            },
            success: function (data) {
              if (data.devices && data.devices.filter) {
                var oldDevices = data.devices.filter(function(device){
                  // Remove unused and old sessions, except mobile sessions.
                  var unused = device.last_seen_ts === null && device.device_id !== localStorage.mx_device_id;
                  var tooOld = device.last_seen_ts && (device.last_seen_ts + Gofast.Riot.sessions.maxAge*1000) < Date.now();
                  var mobile = device.display_name && device.display_name.match(/android|ios/i);
                  return !mobile && (unused || tooOld);
                });
                Gofast.Riot.sessions.clean(oldDevices);
              }
            },
            error: function (xhr, textStatus, error) {
              var errMsg = textStatus;
              if (xhr.responseText) {
                errMsg = $.parseJSON(xhr.responseText);
              }
              console.error('Gofast Riot', errMsg);
            }
          });
        },

        clean: function (devices) {
          var data = {
            devices: devices.map(function(device){
              return device.device_id;
            }),
            auth: {
               type: 'm.login.password',
               user: Gofast.Riot.User.name,
               password: Drupal.settings.TOKEN_RIOT
            }
          };

          $.ajax({
            url: 'https://' + Drupal.settings.GOFAST_COMM + '/_matrix/client/r0/delete_devices',
            type: 'POST',
            data: JSON.stringify(data),
            contentType: 'application/json; charset=utf-8',
            beforeSend: function (xhr) {
              xhr.setRequestHeader('Authorization', 'Bearer ' + localStorage.mx_access_token);
            },
            success: function (data) {
              console.log('cleaned old sessions', data);
            },
            error: function (xhr, textStatus, error) {
              var errMsg = textStatus;
              if (xhr.responseText) {
                errMsg = $.parseJSON(xhr.responseText);
              }
              console.error('Gofast Riot', errMsg);
            }
          });
        }
      },

      notifications : {
        defaults : {
          notifications_enabled: true,        // Enable desktop notifications for this session
          audio_notifications_enabled: true,  // Enable audible notifications for this session
          notifications_body_enabled: true,   // Show message in desktop notification
        },

        onSettingsDialog: function () {
          // When on the notitications tab, listen for notifications switch
          // click events (the master switch button, because Riot doesn't link
          // its value to a localstorage settings, it uses pushrules instead.
          observeDOM(this, function(mut){
            mut.forEach(function (record) {
              if (!record.addedNodes[0] || record.addedNodes[0].className !== 'mx_TabbedView_tabPanel')
                return;
              var $notifTab = $('.mx_NotificationUserSettingsTab', record.addedNodes[0]);
              if ($notifTab.length) {
                // Set timeout to let new elements poulates the DOM.
                setTimeout(function () {
                  $notifTab.find('.mx_ToggleSwitch').first()
                  .once('mx_ToggleSwitch-click').on('click', function (e) {
                    var $switch = e.currentTarget && $(e.currentTarget);
                    if ($switch.attr('aria-checked') === 'true') { // switching to 'false' (unchecked)
                      // Remember this setting to prevent overriding user pref.
                      localStorage.notifications_master_disabled = 1;
                    }
                    else {
                      // delete the flag if exists.
                      delete localStorage.notifications_master_disabled;
                    }
                  });
                }, 500);
              }
            });
          });
        },

        check: function() {
          this.check._checked = true;

          if (! 'Notification' in window) {
            return; // IE probably
          }

          if (Notification.permission === 'granted') {
            // Ensure not to keep a false flag resulting from a previous session
            // in private mode.
            delete localStorage.notifications_browser_permission_deny;

            // If the user did not explicitly disable notifications, ensure it
            // is enabled.
            if (!localStorage.notifications_master_disabled) {
              Gofast.Riot.notifications.enable();
            }

            // Apply defaults, the user should still be able to override them
            // via Riot user-settings panel.
            Gofast.Riot.notifications.setIfUnset();
          }
          else if (Notification.permission === 'denied' && localStorage.notifications_browser_permission_deny) {
            // User made his choice not to receive notifications at the browser
            // level and we already reask him for confirmation just to be sure
            // he is aware of this setting.
            console.log('Gofast Riot', 'notifications denied (browser)');
          }
          else {
            // Ask confirmation. Notification permission may only be requested
            // from inside a short running user-generated event handler, so we
            // attach a click event handler to the main page elements and as
            // soon as the event fires ask for user confirmation, then unbind
            // the handler.
            var $el = $('#IframeRiot,#IframeRiotBloc').contents().find('body').add('body');
            $el.once('notifications-check').on('click', function(e) {
              Notification.requestPermission().then(function (permission) {
                if (permission === 'granted') {
                  // remove flag and reset to defaults.
                  delete localStorage.notifications_browser_permission_deny;
                  for (var setting in Gofast.Riot.notifications.defaults)
                    delete localStorage[setting];
                  Gofast.Riot.notifications.enable();
                  Gofast.Riot.notifications.setIfUnset();
                }
                else {
                  // Save choice to prevent reasking at every new session.
                  // In private/incognito window the script may also land here
                  // directly.
                  localStorage.notifications_browser_permission_deny = true;
                }
              });
              $el.off('click');
              return true;
            });
          }
        },

        enable: function () {
          // https://matrix.org/docs/spec/client_server/latest#put-matrix-client-r0-pushrules-scope-kind-ruleid-enabled
          var ruleID = '.m.rule.master', // "don't notify"
              scope = 'global',
              kind = 'override';

          var path = '/_matrix/client/r0/pushrules/'+scope+'/'+kind+'/'+ruleID+'/enabled';

          $.ajax({
            url: 'https://' + Drupal.settings.GOFAST_COMM + path,
            type: 'PUT',
            contentType: 'application/json; charset=utf-8',
            beforeSend: function (xhr) {
              xhr.setRequestHeader('Authorization', 'Bearer ' + localStorage.mx_access_token);
            },
            data: JSON.stringify(
              // .m.rule.master means "don't notify"
              { enabled: false }
            ),
            success: function () {
              console.log('Gofast Riot', 'Notifications enabled.');
            },
            error: function (xhr, textStatus, error) {
              var errMsg = textStatus;
              if (xhr.responseText) {
                var errJson = $.parseJSON(xhr.responseText);
                if (errJson) {
                  errMsg = JSON.stringify(errJson);
                }
              }
              console.error('Gofast Riot', errMsg);
            }
          });
        },

        setIfUnset: function () {
          for (var setting in Gofast.Riot.notifications.defaults) {
            if (typeof localStorage[setting] === 'undefined') {
              localStorage[setting] = Gofast.Riot.notifications.defaults[setting];
            }
          }
        }
      },

      // https://matrix.org/docs/spec/client_server/latest#get-matrix-client-r0-sync
      // syncFilter and syncSince parameters are to reduce the response size of
      // sync requests (can be huge).
      syncPath: '/_matrix/client/r0/sync',
      syncMethod: 'GET',
      syncTimeout: 30000,
      syncInterval: 5000,
      syncSince: null,
      syncPolling: false,
      syncFilter: {
        room: {
          timeline: {
            types: [
              'm.room.member'
            ]
          },
          state: {
            types: [
              'm.room.member'
            ]
          }
        },
        event_fields: [
          'type',
          'content'
        ],
        account_data: {
          types: []
        },
        presence: {
          types: []
        }
      },

      logout: function () {
        $.ajax({
          url: "https://" + Drupal.settings.GOFAST_COMM + "/_matrix/client/r0/logout?access_token=" + localStorage.mx_access_token,
          type: "POST",
          contentType: "application/json; charset=utf-8",
          success: function (data) {
            console.log('Gofast Riot', 'logged out');
          },
          error: function (xhr, textStatus, error) {
            var errMsg = textStatus;
            if (xhr.responseText) {
              var errJson = $.parseJSON(xhr.responseText);
              if (errJson) {
                errMsg = JSON.stringify(errJson);
              }
            }
            console.error('Gofast Riot', errMsg);
          },
          complete: function () {
            var iframe = document.getElementById('IframeRiot');
            if (iframe && iframe.src) {
              iframe.src = iframe.src;
            }
            iframe = document.getElementById('IframeRiotBloc');
            iframe.src = iframe.src;
          }
        });
      },

      poll: function() {
        Gofast.Riot.syncPolling = true;
        var params = [
          'access_token=' + localStorage.mx_access_token,
          'filter=' + JSON.stringify(Gofast.Riot.syncFilter),
          'timeout=' + Gofast.Riot.syncTimeout
        ];

        if (Gofast.Riot.syncSince) {
          params.push('since=' + Gofast.Riot.syncSince);
        }

        var query = params.join('&');

        $.ajax({
          url: 'https://' + Drupal.settings.GOFAST_COMM + Gofast.Riot.syncPath + '?' + query,
          type: Gofast.Riot.syncMethod,
          contentType: 'application/json; charset=utf-8',
          success: function (data) {
            // Automativally accept all pending invitations.
            var invite = data.rooms && data.rooms.invite || {};
            for (var roomID in invite) {
              Gofast.Riot.acceptInvite(roomID);
            }
            // Automatically forget rooms from which user leaved or has been
            // kicked off.
            var leave = data.rooms && data.rooms.leave || {};
            for (var roomID in leave) {
              Gofast.Riot.forgetRoom(roomID);
            }
            if (data.next_batch) {
              Gofast.Riot.syncSince = data.next_batch;
            }
          },
          beforeSend: function (xmlhttprequest, options) {
            Gofast.xhrPool = Gofast.xhrPool || {};
            Gofast.xhrPool.riotSyncPolling = xmlhttprequest;
          },
          error: function (xhr, textStatus, error) {
            if (error === 'abort')
              return;
            var errMsg = textStatus;
            if (xhr.responseText) {
              errMsg = $.parseJSON(xhr.responseText);
            }
            console.error('Gofast Riot', 'polling', errMsg);
          },
          complete: function() {
            // wait 5 sec. and repeat.
            if (!Tab || Tab.now()) {
              setTimeout(Gofast.Riot.poll, Gofast.Riot.syncInterval);
            }
            else {
              Gofast.Riot.syncPolling = false;
            }
          }
        });
      },

      pollAbort: function () {
        if (Gofast.xhrPool && Gofast.xhrPool.riotSyncPolling) {
          Gofast.xhrPool.riotSyncPolling.abort();
        }
        Gofast.Riot.syncPolling = false;
      },

      acceptInvite: function (roomID) {
        var path = '/_matrix/client/r0/join/' + encodeURI(roomID),
            query = 'access_token=' + localStorage.mx_access_token;

        $.ajax({
          url: 'https://' + Drupal.settings.GOFAST_COMM + path + '?' + query,
          type: 'POST',
          contentType: 'application/json; charset=utf-8',
          success: function (data) {
            console.log('Gofast Riot', 'room invite accepted', roomID);
          },
          error: function (xhr, textStatus, error) {
            var errMsg = textStatus;
            if (xhr.responseText) {
              errMsg = $.parseJSON(xhr.responseText);
            }
            console.error('Gofast Riot', errMsg);
          }
        });
      },

      forgetRoom: function (roomID) {
        var path = '/_matrix/client/r0/rooms/' + encodeURI(roomID) + '/forget',
            query = 'access_token=' + localStorage.mx_access_token;

        $.ajax({
          url: 'https://' + Drupal.settings.GOFAST_COMM + path + '?' + query,
          type: 'POST',
          contentType: 'application/json; charset=utf-8',
          success: function (data) {
            console.log('Gofast Riot', 'room forgotten', roomID);
          },
          error: function (xhr, textStatus, error) {
            var errMsg = textStatus;
            if (xhr.responseText) {
              errMsg = $.parseJSON(xhr.responseText);
            }
            console.error('Gofast Riot', errMsg);
          }
        });
      },

      init: function () {
        if (!Gofast.Riot.User.uid != 0)
          return;

        if (localStorage.mx_access_token) {
          // Check access_token and reinit if necessary.
          Gofast.Riot.validateToken();
        }
        else {
          // Connect and save token to local storage.
          Gofast.Riot.login();
        }

        if (Gofast.get('avatarUrl')) {
          Gofast.Riot.syncAvatar(Gofast.get('avatarUrl'));
        }
      },

      onSessionFound: function (data) {
        console.log('Gofast Riot', 'session found', data.user_id);
        if (!Gofast.Riot.notifications.check._checked) {
          Gofast.Riot.notifications.check();
        }
        setTimeout(function () {
          // If for some reason mx chat isn't loaded, reset all.
          if (Gofast.Riot.unloaded && Gofast.Riot.checkHTML() === false) {
            Gofast.Riot._reset();
          }
          // Else if not already polling, poll for sync events
          else if (!Gofast.Riot.syncPolling && (!Tab || Tab.now())) {
            Gofast.Riot.poll();
          }
        }, 10000);
      },

      validateToken: function () {
        $.ajax({
          url: "https://" + Drupal.settings.GOFAST_COMM + "/_matrix/client/r0/account/whoami?access_token=" + localStorage.mx_access_token,
          type: 'GET',
          dataType: 'json',
          success: Gofast.Riot.onSessionFound,
          error: function (xhr, textStatus, err) {
            var errMsg = textStatus;
            if (xhr.responseText) {
              var errJson = $.parseJSON(xhr.responseText);
              errMsg = errJson.error || 'unknown error';
              if (errJson.errcode === 'M_UNKNOWN_TOKEN') {
                Gofast.Riot.login();
              }
            }
            console.error('Gofast Riot', errMsg);
          }
        });
      },

      onLogin: function (data) {
        console.log('Gofast Riot', 'login succeeded', Gofast.Riot.User.name);
        SaveUserRiot(data);

        $.ajax({
          url: window.location.origin + '/SaveRiotToken',
          type: 'POST',
          data: {token: data.access_token},
          dataType: 'html',
          success: function (data) {
            //console.log(arguments);
          },
          error: function (err) {
            console.error('Gofast Riot', arguments);
          },
          complete: function () {
            $('#blocConnexionRiot').hide();
            $('#IframeRiotBloc').show();
            var iframe = document.getElementById('IframeRiotBloc');
            iframe.src = iframe.src;
            // If on a conversation page, still need refresh.
            if (iframe = document.getElementById('IframeRiot')) {
              iframe.src = iframe.src;
            }
            if (iframe = document.getElementById('gf_conversation')) {
              iframe.src = iframe.src;
            }
          }
        });

          // change display name on caht Element (RIOT)
          setDisplayName(Gofast.Riot.User.displayName);

        Gofast.Riot.sessions.check();
      },

      onLoginError: function (xhr, textStatus, error) {
        var errMsg = textStatus, errJson;
        if (xhr.responseText) {
          errMsg = xhr.responseText;
          errJson = $.parseJSON(xhr.responseText);
          if (errJson && errJson.error) {
            var invalidPassword = errJson.error.toLowerCase() === 'invalid password';
            if (Gofast.Riot.nbConnexion < 2 && invalidPassword) {
              Gofast.Riot.nbConnexion++;
              //appel pour chercher le nouveau token;
              $.ajax({
                url: window.location.origin + '/GetRiotTokenJS',
                type: 'POST',
                data: {uname: Gofast.Riot.User.name},
                dataType: 'html',
                success: function (data) {
                  Drupal.settings.TOKEN_RIOT = data;
                },
                error: function (err) {
                  console.error('Gofast Riot', arguments);
                },
                complete: function () {
                  Gofast.Riot.login();
                }
              });
            }
            if (errJson.errcode === 'M_UNKNOWN') {
              // nginx or matrix probably down, prevent reset
              Gofast.Riot._reset.called = 5;
            }
          }
        }
        console.error('Gofast Riot', errMsg);
      },

      login: function () {
        $('#IframeRiotBloc').hide();
        $('#blocConnexionRiot').css('display', 'flex');

        $.ajax({
          url: "https://" + Drupal.settings.GOFAST_COMM + "/_matrix/client/r0/login",
          type: "POST",
          contentType: "application/json; charset=utf-8",
          data: JSON.stringify({user: Gofast.Riot.User.name.toLowerCase(), password: Drupal.settings.TOKEN_RIOT, type: "m.login.password"}),
          dataType: "json",
          success: Gofast.Riot.onLogin,
          error: Gofast.Riot.onLoginError
        });
      },

      uploadContent: function (filename, data) {
        var query = 'filename=' + encodeURIComponent(filename);
        var url = 'https://' + Drupal.settings.GOFAST_COMM + '/_matrix/media/r0/upload?' + query;
        var callback = typeof arguments[2] === 'function' && arguments[2];

        $.ajax({
          url: url,
          type: 'POST',
          processData: false,
          contentType: data.type,
          data: data,
          dataType: 'json',
          beforeSend: function (xhr) {
            xhr.setRequestHeader('Authorization', 'Bearer ' + localStorage.mx_access_token);
          },
          success: function(data) {
            console.log(data);
            if (callback) {
              callback.call(null, data.content_uri);
            }
          },
          error: function (xhr, textStatus, err) {
            var errMsg = textStatus;
            if (xhr.responseText) {
              var errJson = $.parseJSON(xhr.responseText);
              errMsg = errJson.error || 'unknown error';
            }
            console.error('Gofast Riot', errMsg);
          }
        });
      },

      setAvatar: function (contentURI) {
        var username = encodeURIComponent(localStorage.mx_user_id);
        var path = '/_matrix/client/r0/profile/' + username + '/avatar_url';
        var query = 'access_token=' + localStorage.mx_access_token;

        $.ajax({
          url: 'https://' + Drupal.settings.GOFAST_COMM + path + '?' + query,
          type: 'PUT',
          contentType: 'application/json',
          data: JSON.stringify({avatar_url: contentURI}),
          dataType: 'json',
          success: function (data) {
            if (contentURI) {
              console.log('Gofast Riot', 'user avatar set', contentURI);
              var mediaID = contentURI.split('/').last();
              Gofast.Riot.refreshThumbnail(mediaID);
            }
            else {
              console.log('Gofast Riot', 'user avatar removed');
            }
          },
          error: function (err) {
            console.error('Gofast Riot', arguments);
          }
        });
      },

      syncAvatar: function (avatarUrl) {
        // Our version of jQuery can't handle blob, use XMLHttpRequest directly.
        var xhr = new XMLHttpRequest();
        xhr.open('GET', avatarUrl);
        xhr.responseType = 'blob';
        xhr.onerror = function() {
          console.error('network error');
        };
        xhr.onload = function() {
          if (xhr.status === 200) {
            var blob = xhr.response;
            var filename = avatarUrl.split('/').last();
            Gofast.Riot.uploadContent(filename, blob, Gofast.Riot.setAvatar);
          }
        };
        xhr.send();
      },
            refreshThumbnail: function (mediaID) {
        var userID = localStorage.mx_user_id,
          $frames = $('iframe#IframeRiotBloc,iframe#IframeRiot').contents(),
          $el = $frames.find('.mx_BaseAvatar_image[title="' + userID + '"]'),
          $leftEl = $frames.find('.mx_LeftPanel_container .mx_TopLeftMenuButton .mx_BaseAvatar_image'),
          serverName = encodeURIComponent(Drupal.settings.GOFAST_COMM),
          path = '/_matrix/media/r0/thumbnail/' + serverName + '/' + mediaID;

        $el.add($leftEl).each(function (i, img) {
          var w = $(img).attr('width'),
            h = $(img).attr('height'),
            query = 'width=' + w + '&height=' + h + '&method=crop',
            url = 'https://' + Drupal.settings.GOFAST_COMM + '/' + path + '?' + query;

          $(img).attr('src', url);
          $(img).prev('.mx_BaseAvatar_initial').remove();
        });
      },
      switchMinimized: function () {
        /* BEGIN minimized Riot LeftPanel */
        // Function callback that Wait for an element until it exist on the Iframe
        // if the element (LeftPanel) Exist we  give it maxWidth and afterit reduce the width
        // to force Elment Listner to switch to minimized version
        var waitForEl = function (callback, count) {
          if ($('iframe#IframeRiotBloc,iframe#IframeRiot').contents().has('.mx_LeftPanel').length > 0) {
            callback();
          } else {
            setTimeout(function () {
              if (!count) {
                count = 0;
              }
              count++;
              if (count < 500) { // Max CAllback 500 time
                waitForEl(callback, count);
              } else { return; }
            }, 250);
          }
        };

        waitForEl(function () {
          // work the magic
          $('iframe#IframeRiotBloc,iframe#IframeRiot').width('1001px');
          setTimeout(
            function () {
              $('iframe#IframeRiotBloc,iframe#IframeRiot').width('100%');
            }, 100);
          console.log("GoFast Switching minimized Riot LeftPanel");
        });
        /* END minimized Riot LeftPanel */
      },
      avatarSyncCheck: function() {
        // If user has a Gofast avatar set different than anonymous but not set
        // in Riot, trigger sync operation. Ensure the operation runs only once
        // so that we don't land in a failure loop, should it happen.
        var riotAvatarUnset = $(this).find('.mx_BaseAvatar_initial').length > 0;
        var gofastAvatar = Gofast.Riot.User.avatar;
        var anonAvatar = Gofast.Riot.User.avatar_anon;

        if (riotAvatarUnset && !localStorage.gofast_mx_avatar_synced) {
          if (gofastAvatar && gofastAvatar !== anonAvatar) {
            Gofast.Riot.syncAvatar(gofastAvatar);
          }
          localStorage.gofast_mx_avatar_synced = true;
        }

        // GOFAST-6730 - Fix wrong sync that could have occured.
        if (gofastAvatar === anonAvatar && !riotAvatarUnset) {
          // This will remove riot avatar.
          Gofast.Riot.setAvatar('');
        }
      }

    }; // Gofast.Riot
  }; // Gofast._riot

  $(document).ready(function () {
    if (!$('.block-gofast-riot').length && !$('#IframeRiot').length) {
      // No chat on this page
      return;
    }

    if (window.parent && window.parent.location.toString() !== this.URL) {
      // This is a child window, not our document.
      return;
    }

    Gofast.Riot = Gofast.Riot || Gofast._riot();

    if (!Gofast.getCookie('gofast_user') || !Gofast.Riot.User.uid) {
      // anonymous user.
      return;
    }

    if (Tab) {
      Tab.on('wakeup', function () {
        // Init/reinit when tab wakes up.
        Gofast.Riot.init();
      });
    }

    // Expand/collapse Riot bloc when clicking the handle. The binding is done
    // here in document.ready() and not in iframe 'load' event handler because
    // we want the user to be able to expand the container in case the iframe
    // does not load at all.
    $('#animateRiot').once('animated', function () {
      $(this).click(Gofast.Riot.onHandleClick);
    });

    var iframe = $("#IframeRiotBloc");

    // Expand Riot bloc when clicking on the bloc (iFrame).

      iframe.on("load", function () { //Make sure it is fully loaded
        iframe.contents().click(function (event) {
          iframe.trigger("click");
        });
        Gofast.Riot.switchMinimized();
      });

      iframe.click(function () {
        if (Math.floor($('#conteneurIframe').innerWidth()) <= Gofast.Riot.widthCollapsed) {
          Gofast.Riot.expand();
        }
      });

    // In case the iframe 'load' event does not fire or not in time,
    setTimeout(function () {
      if (Gofast.Riot.unloaded && Gofast.Riot.checkHTML() === false) {
        Gofast.Riot._reset();
        return;
      }
      var $login = $('iframe#IframeRiotBloc').contents().find('.mx_AuthPage');
      if ($login.length) {
        delete localStorage.mx_access_token;
        Gofast.Riot.init();
      }
    }, 15000);

    $(this).on('ajax-navigate', function () {
      // When navigating in ajax, cancel the current polling request if any.
      Gofast.Riot.pollAbort();
    });

    $(this).on('ajax-nav-success', function () {
      var visibility = window.location.pathname === '/conversation' ? 'hidden' : 'visible';
      $('iframe#IframeRiotBloc').css('visibility', visibility);
      Gofast.Riot.init();
    });

    $(this).on('avatarChange', function (e, data, uid) {
      var avatarUrl = data && data.pictureUrl;
      // Sync avatar if owner of the account.
      if (avatarUrl && Gofast.Riot.User.uid === uid) {
        Gofast.Riot.syncAvatar(avatarUrl);
      }
    });

    // Sort rooms by activity. Always show rooms with unread messages first.
    localStorage['mx_listOrder_im.vector.fake.recent'] = 'IMPORTANCE'; // | NATURAL
    localStorage['mx_tagSort_im.vector.fake.recent'] = 'RECENT'; // | ALPHABETIC
    localStorage['mx_im.vector.fake.recent_sortBy'] = "RECENT"; // | ALPHABETIC

    // Same for user list.
    localStorage['mx_listOrder_im.vector.fake.direct'] = 'IMPORTANCE';
    localStorage['mx_tagSort_im.vector.fake.direct'] = 'RECENT';
    localStorage['mx_im.vector.fake.direct_sortBy'] = "RECENT"; // | ALPHABETIC

    if (Gofast._settings.isMobile == false || typeof Gofast._settings.isMobile == 'undefined') {
      $('#IframeRiot').css({ 'margin-left': '32px' }); // Riot block change margin oly on Gofast Plus version
    }
  }); /* END document.ready() */


  /**
   * When Riot iframe is loaded in side block.
   */
  $('iframe#IframeRiotBloc').load(function() {
    var iframe = this;
    var $iframe_body = $(iframe).contents().find('body');


    // Hide v-scrollbar as soon as we can (scroll is implemented internally).
    // Applied here because 'load' usally fires before css are loaded.
    $iframe_body.css({
      overflow: 'hidden',
      'background-color': '#f2f5f8' // initially transparent
    });

    if (!Gofast._accessors) {
      // 'load' event fired before Gofast.initSettings() call !
      setTimeout(function() {
        Gofast.initSettings();
        $(iframe).trigger('load');
      }, 100);
      return;
    }

    Gofast.Riot = Gofast.Riot || Gofast._riot();

    if (!Gofast.getCookie('gofast_user') || !Gofast.Riot.User.uid) {
      // anonymous user.
      return;
    }

    // iframe is hidden by default.
    if (window.location.pathname !== '/conversation') {
      $(iframe).css('visibility', 'visible');
    }

    // Ensure this is set to default
    Gofast.Riot.unloaded = true;

    // Delegated handler for expanding the bloc if needed when clicking on a
    // room tile or "Start chat" button.
    $iframe_body.on('click', 'div.mx_RoomTile,.mx_AccessibleButton.mx_RoomSublist_auxButton', function() {
      if (Gofast.Riot.isCollapsed) {
        Gofast.Riot.expand();
      }
      // We also add a class to the chat view that corresponds to whether it
      // belongs to a room or a user (rooms|people).
      Gofast.Riot.tagView(this);
    });

    // Tag the view once loaded (rooms|people).
    $iframe_body.one('lazyload', '.mx_MatrixChat', function() {
      setTimeout(Gofast.Riot.tagView, 1000);
    });

    // Make tooltips always visible regardless of the bloc being collapsed or not.
    var $tooltip;

    // Apply this css (iframe scope) regardless of riot theme. This hides the
    // default tooltip container that cannot overflow from the iframe when the
    // bloc is collapsed and also hides the horizontal resize handle that makes
    // the pointer buggy and is useless in bloc mode (not in conversation page).
    var $head = $(iframe).contents().find('head');
    var style = '.mx_Tooltip_wrapper, .mx_ResizeHandle_horizontal { display:none; }';
    $('<style type="text/css">' + style + '</style>').appendTo($head);

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
          // hover intent was not long enough to make the toolip appear.
          return;
        }

        // Adjust styles according to bloc state.
        var top = parseInt($tooltip.css('top')) + 50;
        var right = parseInt($tooltip.css('right'));

        $tooltip.css({
          top: top + 'px',
          left: 'unset',
          right: right + 10 + 'px'
        });

        // Insert the tooltip into the DOM outside the iframe so it can expand
        // properly.
        $tooltip.appendTo('#conteneurIframe');
      }, 100);
    });

    $iframe_body.on('mouseout', 'div.mx_RoomTile,.mx_RoomSublist_headerText', function(e) {
      if ($tooltip) {
        $tooltip.remove();
        $tooltip = null;
      }
    });

    // Prevent displaying rooms|users list settings.
    $iframe_body.on('contextmenu', '.mx_RoomSublist_stickable .mx_AccessibleButton', function(e) {
      e.preventDefault();
      return false;
    });

    // Check if gofast avatar needs to be synced.
    $iframe_body.one('lazyload', '.mx_MessageComposer_avatar', Gofast.Riot.avatarSyncCheck);

    // Prevent displaying rooms|users list settings.
    $iframe_body.on('contextmenu', '.mx_RoomSublist_stickable .mx_AccessibleButton', function(e) {
      e.preventDefault();
      return false;
    });

    Gofast.Riot.preventFocusStealing.call(this);  // GOFAST-6151
    Gofast.Riot.preventDisplayBug.call(this);     // GOFAST-6303, GOFAST-6258

    Gofast.Riot.init();
  });

  /**
   * When Riot iframe is loaded in conversation page.
   */
  $('iframe#IframeRiot').load(function() {
    var iframe = this;

    if (!Gofast._accessors) {
      // 'load' event fired before Gofast.initSettings() call !
      setTimeout(function() {
        Gofast.initSettings();
        $(iframe).trigger('load');
      }, 100);
      return;
    }

    if (!Gofast.getCookie('gofast_user') || !Gofast.Riot.User.uid) {
      // anonymous user.
      return;
    }

    var $iframe_body = $(iframe).contents().find('body');

    // Prevent displaying rooms|users list settings.
    $iframe_body.on('contextmenu', '.mx_RoomSublist_stickable .mx_AccessibleButton', function(e) {
      e.preventDefault();
      return false;
    });

    // Delegated handler for adding a class to the chat view that corresponds to
    // whether it belongs to a room or a user (rooms|people).
    $iframe_body.on('click', 'div.mx_RoomTile,.mx_AccessibleButton.mx_RoomSublist_auxButton', function() {
      Gofast.Riot.tagView(this);
    });

    // Tag the view once loaded (rooms|people).
    $iframe_body.one('lazyload', '.mx_MatrixChat', function() {
      setTimeout(Gofast.Riot.tagView, 1000);
    });

    Gofast.Riot.preventDisplayBug.call(this);
    Gofast.Riot.init();
  });

})(jQuery, Gofast, Drupal, ifvisible);


// mx_ErrorView

