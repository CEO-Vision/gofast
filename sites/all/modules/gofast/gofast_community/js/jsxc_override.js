(function ($, Gofast, Drupal) {
  
  // Detach the jsxc.muc.onPresence callback and attach our own callback (ceo-vision.com)
  $(document).unbind('presence.jsxc', jsxc.muc.onPresence);
  $(document).unbind('init.window.jsxc', jsxc.muc.initWindow);
  
  
 /**
 * @CEO-VISION JSXC Override
 * Patch JSXC bug (no control on value return by Strophe.getBareJidFromJid methode)
 * 
 * @memberOf jsxc.gui.window
 * @param {String} bid
 * @returns {jQuery} Window object
 */
  jsxc.jidToBid = function(jid){
    if(Strophe.getBareJidFromJid(jid) !== null)
      return Strophe.unescapeNode(Strophe.getBareJidFromJid(jid).toLowerCase());
    else
      return null;
  };

  jsxc.gui.template['chatWindow'] = '<li class="jsxc_windowItem">\n' +
'   <div class="jsxc_window">\n' +
'      <div class="jsxc_bar">\n' +
'         <div class="jsxc_avatar jsxc_statusIndicator"></div>\n' +
'         <div class="jsxc_tools">\n' +
'            <div class="jsxc_settings">\n' +
'               <div class="jsxc_more"></div>\n' +
'               <div class="jsxc_inner jsxc_menu">\n' +
'                  <ul>\n' +
'                     <li>\n' +
'                        <a class="jsxc_verification" href="#">\n' +
'                           <span data-i18n="Authentication"></span>\n' +
'                        </a>\n' +
'                     </li>\n' +
'                     <li>\n' +
'                        <a class="jsxc_clear" href="#">\n' +
'                           <span data-i18n="clear_history"></span>\n' +
'                        </a>\n' +
'                     </li>\n' +
/*
 * HIDE WHILE NOT WORKING
'                     <li>\n' +
'                        <a class="jsxc_sendFile" href="#">\n' +
'                           <span data-i18n="Send_file"></span>\n' +
'                        </a>\n' +
'                     </li>\n' +
*/
'                  </ul>\n' +
'               </div>\n' +
'            </div>\n' +
'            <div class="jsxc_close">×</div>\n' +
'         </div>\n' +
'         <div class="jsxc_caption">\n' +
'            <div class="jsxc_name" />\n' +
'            <div class="jsxc_lastmsg">\n' +
'               <span class="jsxc_unread" />\n' +
'               <span class="jsxc_text" />\n' +
'            </div>\n' +
'            <div class="jsxc_status-msg" />\n' +
'         </div>\n' +
'      </div>\n' +
'      <div class="jsxc_fade">\n' +
'         <div class="jsxc_overlay">\n' +
'            <div>\n' +
'               <div class="jsxc_body" />\n' +
'               <div class="jsxc_close" />\n' +
'            </div>\n' +
'         </div>\n' +
'         <div class="jsxc_textarea" />\n' +
'         <div class="jsxc_emoticons">\n' +
'            <div class="jsxc_inner">\n' +
'               <ul>\n' +
'                  <li class="jsxc_clear"></li>\n' +
'               </ul>\n' +
'            </div>\n' +
'         </div>\n' +
'         <div class="jsxc_transfer jsxc_otr jsxc_disabled" />\n' +
'         <textarea class="jsxc_textinput" data-i18n="[placeholder]Message"></textarea>\n' +
'      </div>\n' +
'   </div>\n' +
'</li>\n' +
'';

/**
 * @CEO-VISION JSXC Override
 * @memberOf jsxc.gui.window
 * @param {String} bid
 * @returns {jQuery} Window object
 */
jsxc.gui.window.init = function (bid) {
      if (jsxc.gui.window.get(bid).length > 0) {
         return jsxc.gui.window.get(bid);
      }

      var win = jsxc.gui.windowTemplate.clone().attr('data-bid', bid).appendTo('#jsxc_windowList > ul');
      var data = jsxc.storage.getUserItem('buddy', bid);

      // Attach jid to window
      win.data('jid', data.jid);

      // Add handler

      // @TODO generalize this. Duplicate of jsxc.roster.add
      var expandClick = function() {
         win.trigger('extra.jsxc');

         $('body').click();

         if (!win.find('.jsxc_menu').hasClass('jsxc_open')) {
            win.find('.jsxc_menu').addClass('jsxc_open');

            $('body').one('click', function() {
               win.find('.jsxc_menu').removeClass('jsxc_open');
            });
         }

         return false;
      };

      win.find('.jsxc_more').click(expandClick);
      win.find('.jsxc_menu').click(function() {
         $('body').click();
      });

      win.find('.jsxc_verification').click(function() {
         jsxc.gui.showVerification(bid);
      });

      win.find('.jsxc_fingerprints').click(function() {
         jsxc.gui.showFingerprints(bid);
      });

      win.find('.jsxc_transfer').click(function() {
         jsxc.otr.toggleTransfer(bid);
      });

      // @CEO-VISION : avoid minimized chat popup if the username is clicked ( i.e. load user profile).
      win.find('.jsxc_bar').click(function(e) {
        if (!$(e.target).is('a')){ 
          jsxc.gui.window.toggle(bid);
        }
      });

      win.find('.jsxc_close').click(function() {
         jsxc.gui.window.close(bid);
      });

      win.find('.jsxc_clear').click(function() {
         jsxc.gui.window.clear(bid);
      });

      win.find('.jsxc_sendFile').click(function() {
         $('body').click();

         if ($(this).hasClass('jsxc_disabled')) {
            return;
         }

         jsxc.gui.window.sendFile(bid);
      });

      win.find('.jsxc_tools').click(function() {
         return false;
      });

      var textinputBlurTimeout;
      win.find('.jsxc_textinput').keyup(function(ev) {
         var body = $(this).val();

         // I'm composing a message
         if (ev.which !== 13) {
            jsxc.xmpp.chatState.startComposing(bid);
         }

         if (ev.which === 13 && !ev.shiftKey) {
            body = '';

            jsxc.xmpp.chatState.endComposing(bid);
         }

         jsxc.storage.updateUserItem('window', bid, 'text', body);

         if (ev.which === 27) {
            jsxc.gui.window.close(bid);
         }
      }).keypress(function(ev) {
         if (ev.which !== 13 || ev.shiftKey || !$(this).val()) {
            resizeTextarea.call(this);
            return;
         }

         jsxc.gui.window.postMessage({
            bid: bid,
            direction: jsxc.Message.OUT,
            msg: $(this).val()
         });

         $(this).css('height', '').val('');

         ev.preventDefault();
      }).focus(function() {
         if (textinputBlurTimeout) {
            clearTimeout(textinputBlurTimeout);
         }

         // remove unread flag
         jsxc.gui.readMsg(bid);

         resizeTextarea.call(this);
      }).blur(function() {
         var self = $(this);

         textinputBlurTimeout = setTimeout(function() {
            self.css('height', '');
         }, 1200);
      }).mouseenter(function() {
         $('#jsxc_windowList').data('isOver', true);
      }).mouseleave(function() {
         $('#jsxc_windowList').data('isOver', false);
      });

      function resizeTextarea() {
         if (!$(this).data('originalHeight')) {
            $(this).data('originalHeight', $(this).outerHeight());
         }
         // compensate rounding error
         if ($(this).outerHeight() < (this.scrollHeight - 1) && $(this).val()) {
            $(this).height($(this).data('originalHeight') * 1.5);
         }
      }

      win.find('.jsxc_textarea').click(function() {
         // check if user clicks element or selects text
         if (typeof getSelection === 'function' && !getSelection().toString()) {
            win.find('.jsxc_textinput').focus();
         }
      });

      win.find('.jsxc_textarea').slimScroll({
         height: '234px',
         distance: '3px'
      });

      win.find('.jsxc_name').disableSelection();

      win.find('.slimScrollDiv').resizable({
         handles: 'w, nw, n',
         minHeight: 234,
         minWidth: 250,
         resize: function(event, ui) {
            jsxc.gui.window.resize(win, ui);
         },
         start: function() {
            win.removeClass('jsxc_normal');
         },
         stop: function() {
            win.addClass('jsxc_normal');
         }
      });

      win.find('.jsxc_window').css('bottom', -1 * win.find('.jsxc_fade').height());

      if ($.inArray(bid, jsxc.storage.getUserItem('windowlist')) < 0) {

         // add window to windowlist
         var wl = jsxc.storage.getUserItem('windowlist') || [];
         wl.push(bid);
         jsxc.storage.setUserItem('windowlist', wl);

         // init window element in storage
         jsxc.storage.setUserItem('window', bid, {
            minimize: true,
            text: '',
            unread: 0
         });

         jsxc.gui.window.hide(bid);
      } else {

         if (jsxc.storage.getUserItem('window', bid).unread) {
            jsxc.gui._unreadMsg(bid);
         }
      }

      $.each(jsxc.gui.emotions, function(i, val) {
         var ins = val[0].split(' ')[0];
         var li = $('<li>');
         li.append(jsxc.gui.shortnameToImage(':' + val[1] + ':'));
         li.find('div').attr('title', ins);
         li.click(function() {
            win.find('.jsxc_textinput').val(win.find('.jsxc_textinput').val() + ins);
            win.find('.jsxc_textinput').focus();
         });
         win.find('.jsxc_emoticons ul').prepend(li);
      });

      jsxc.gui.toggleList.call(win.find('.jsxc_emoticons'));

      jsxc.gui.window.restoreChat(bid);

      jsxc.gui.update(bid);

      jsxc.gui.updateWindowListSB();

      // create related otr object
      if (jsxc.master && !jsxc.otr.objects[bid]) {
         jsxc.otr.create(bid);
      } else {
         jsxc.otr.enable(bid);
      }

      $(document).trigger('init.window.jsxc', [win]);

      return win;
   },


/**
 * @CEO-VISION 
 * Update current user status
 * @param {type} pres
 * @returns {undefined}
 */
  jsxc.gui.updateStatus = function (pres) {
    
    var self = jsxc.gui;
    self.changePresence(pres);
    $('#jsxc_presence > span').attr('data-i18n', $('li[data-pres="' + pres + '"]').attr('data-i18n'));
    var roomNames = jsxc.storage.getUserItem('roomNames');
    if (roomNames) {
      for (var i = 0; i < roomNames.length; i++) {
        var userJid = jsxc.storage.getItem("jid");
        var username = Strophe.getNodeFromJid(userJid);
        jsxc.storage.updateUserItem("res", roomNames[i], username, jsxc.CONST.STATUS.indexOf(pres));
      }
    }
  };


  /** 
   * @CEO-VISION JSXC Override
   * Custom update avatar (contrib stuff ?) : to get GoFAST Avatar
   * @memberOf jsxc.gui
   * @param {jQuery} el Elements with subelement .jsxc_avatar
   * @param {string} bid bid
   * @param {string} avatar avatar
  */
  jsxc.gui.avatar.update = function (el, bid, avatar) {
    var setAvatar = function (src) {
      if (src === 0 || src === '0') {
        if (typeof jsxc.options.defaultAvatar === 'function') {
          jsxc.options.defaultAvatar.call(el, bid);
          return;
        }
        jsxc.gui.avatarPlaceholder(el.find('.jsxc_avatar'), bid);
        return;
      }

      el.find('.jsxc_avatar').removeAttr('style');

      el.find('.jsxc_avatar').css({
        'background-image': 'url(' + src + ')',
        'text-indent': '999px'
      });
    };

    if (typeof avatar === 'undefined') {
      setAvatar(0);
      return;
    }

    var avatarSrc = '';
    if (jsxc.jidToBid(jsxc.storage.getItem("jid")) === bid) { // Dedicated for current's user avatar only
      avatarSrc = jsxc.storage.getUserItem('avatar', avatar);
    } else { // this is for the buddies
      avatarSrc = jsxc.storage.getUserItem('buddy', bid).avatar;
    }

    if (avatarSrc !== null) {
      setAvatar(avatarSrc);
    }
  };


 /**
  * @CEO-VISION JSXC Override : add link to user profile
  * Updates Information in roster and chatbar
  * @param {String} bid bar jid
  */
  jsxc.gui.update = function(bid) {
    var data = jsxc.storage.getUserItem('buddy', bid);

    if (!data) {
       jsxc.debug('No data for ' + bid);
       return;
    }

    var ri = jsxc.gui.roster.getItem(bid); // roster item from user
    var we = jsxc.gui.window.get(bid); // window element from user
    var ue = ri.add(we); // both
    var spot = $('.jsxc_spot[data-bid="' + bid + '"]');

    // Attach data to corresponding roster item
    ri.data(data);

    // Add online status
    jsxc.gui.updatePresence(bid, jsxc.CONST.STATUS[data.status]);

    // Change name and add title
    ue.find('.jsxc_name:first').add(spot).text(data.name).attr('title', $.t('is_', {
       status: $.t(jsxc.CONST.STATUS[data.status])
    }));

    //------------------------------------
    // @CEO-VISION : added link to Gofast user profile
    if (data.link) {
      we.find('.jsxc_name:first').add(spot).html('<a href="' + data.link + '">' + data.name + '</a>');
    } else {
      we.find('.jsxc_name:first').add(spot).text(data.name);
    }
    ri.find('.jsxc_name:first').add(spot).text(data.name);
    //------------------------------------

    // Update gui according to encryption state
    switch (data.msgstate) {
       case 0:
          we.find('.jsxc_transfer').removeClass('jsxc_enc jsxc_fin').attr('title', $.t('your_connection_is_unencrypted'));
          we.find('.jsxc_settings .jsxc_verification').addClass('jsxc_disabled');
          we.find('.jsxc_settings .jsxc_transfer').text($.t('start_private'));
          break;
       case 1:
          we.find('.jsxc_transfer').addClass('jsxc_enc').attr('title', $.t('your_connection_is_encrypted'));
          we.find('.jsxc_settings .jsxc_verification').removeClass('jsxc_disabled');
          we.find('.jsxc_settings .jsxc_transfer').text($.t('close_private'));
          break;
       case 2:
          we.find('.jsxc_settings .jsxc_verification').addClass('jsxc_disabled');
          we.find('.jsxc_transfer').removeClass('jsxc_enc').addClass('jsxc_fin').attr('title', $.t('your_buddy_closed_the_private_connection'));
          we.find('.jsxc_settings .jsxc_transfer').text($.t('close_private'));
          break;
    }

    // update gui according to verification state
    if (data.trust) {
       we.find('.jsxc_transfer').addClass('jsxc_trust').attr('title', $.t('your_buddy_is_verificated'));
    } else {
       we.find('.jsxc_transfer').removeClass('jsxc_trust');
    }

    // update gui according to subscription state
    if (data.sub && data.sub !== 'both') {
       ue.addClass('jsxc_oneway');
    } else {
       ue.removeClass('jsxc_oneway');
    }

    var info = Strophe.getBareJidFromJid(data.jid) + '\n';
    info += $.t('Subscription') + ': ' + $.t(data.sub) + '\n';
    info += $.t('Status') + ': ' + $.t(jsxc.CONST.STATUS[data.status]);

    ri.find('.jsxc_name').attr('title', info);

    jsxc.gui.avatar.update(ri.add(we.find('.jsxc_bar')), data.jid, data.avatar);

    $(document).trigger('update.gui.jsxc', [bid]);
 };



/**
 * Roster override,  see @CEO-VISION directives 
 */
jsxc.gui.roster.init = function () {
  
    $(jsxc.options.rosterAppend + ':first').append($(jsxc.gui.template.get('roster')));

    if (jsxc.options.get('hideOffline')) {
       $('#jsxc_menu .jsxc_hideOffline').text($.t('Show_offline'));
       $('#jsxc_buddylist').addClass('jsxc_hideOffline');
    }

    $('#jsxc_menu .jsxc_settings').click(function() {
       jsxc.gui.showSettings();
    });

    $('#jsxc_menu .jsxc_hideOffline').click(function() {
       var hideOffline = !jsxc.options.get('hideOffline');

       if (hideOffline) {
          $('#jsxc_buddylist').addClass('jsxc_hideOffline');
       } else {
          $('#jsxc_buddylist').removeClass('jsxc_hideOffline');
       }

       $(this).text(hideOffline ? $.t('Show_offline') : $.t('Hide_offline'));

       jsxc.options.set('hideOffline', hideOffline);
    });

    if (jsxc.options.get('muteNotification')) {
       jsxc.notification.muteSound();
    }

    $('#jsxc_menu .jsxc_muteNotification').click(function() {

       if (jsxc.storage.getUserItem('presence') === 'dnd') {
          return;
       }

       // invert current choice
       var mute = !jsxc.options.get('muteNotification');

       if (mute) {
          jsxc.notification.muteSound();
       } else {
          jsxc.notification.unmuteSound();
       }
    });

    $('#jsxc_roster .jsxc_addBuddy').click(function() {
       jsxc.gui.showContactDialog();
    });

    $('#jsxc_roster .jsxc_onlineHelp').click(function() {
       window.open(jsxc.options.onlineHelp, 'onlineHelp');
    });

    $('#jsxc_roster .jsxc_about').click(function() {
       jsxc.gui.showAboutDialog();
    });

    // @CEO-VISION : removed default behaviour to implement our own (cf. gofast_chat.js)
    $('#jsxc_toggleRoster').click(function() {
       //jsxc.gui.roster.toggle();
    });

    $('#jsxc_presence li').click(function() {
       var self = $(this);
       var pres = self.data('pres');

       if (pres === 'offline') {
          jsxc.xmpp.logout(false);
       } else {
          jsxc.gui.changePresence(pres);
       }
    });

    $('#jsxc_buddylist').slimScroll({
       distance: '3px',
       height: ($('#jsxc_roster').height() - 31) + 'px',
       width: $('#jsxc_buddylist').width() + 'px',
       color: '#fff',
       opacity: '0.5'
    });

    $('#jsxc_roster > .jsxc_bottom > div').each(function() {
       jsxc.gui.toggleList.call($(this));
    });

    var rosterState = jsxc.storage.getUserItem('roster') || (jsxc.options.get('loginForm').startMinimized ? 'hidden' : 'shown');

    $('#jsxc_roster').addClass('jsxc_state_' + rosterState);
    $('#jsxc_windowList').addClass('jsxc_roster_' + rosterState);

    var pres = jsxc.storage.getUserItem('presence') || 'online';
    $('#jsxc_presence > span').text($('#jsxc_presence .jsxc_' + pres).text());
    jsxc.gui.updatePresence('own', pres);

    jsxc.gui.tooltip('#jsxc_roster');

    jsxc.notice.load();

    jsxc.gui.roster.ready = true;
    $(document).trigger('ready.roster.jsxc', [rosterState]);
    $(document).trigger('ready-roster-jsxc', [rosterState]);
    
    //Prevent multiple enteries in buddylist
    var buddyList = $("#jsxc_buddylist").find('.jsxc_rosteritem');
    var uniqueList = [];
    $.each(buddyList, function(k,v){
      if(uniqueList.indexOf(v.getAttribute('data-bid')) === -1){
        uniqueList.push(v.getAttribute('data-bid'));
      }
      else{
        console.log('Deleting duplicated entry for ' + v.getAttribute('data-bid'));
        v.remove();
      }
    });
};

/**
 * Roster override to relog the user when he gets disconnected in a GoFast session
 */
jsxc.gui.roster.noConnection = function(){
  if(typeof Drupal.settings.userName === "undefined" || Drupal.settings.userName === null){ //Variable declaration
    return;
  }
  if(typeof Gofast.chatReconnecting === "undefined" || Gofast.chatReconnecting === null){ //Variable declaration
    Gofast.chatReconnecting = 0;
  }
  if(Gofast.chatReconnecting > 5){ //Too many chat reconnecting request
    $('.chat-issue').remove();
    $('#jsxc_roster').prepend($('<p>' + Drupal.t("Please log in again. ", {}, {'context' : 'gofast:gofast_chat'}) + '</p>').append(' <a>' + $.t('Login') + '</a>').click(function() {
      jsxc.gui.showLoginBox();
    }));
    return;
  }
  Gofast.chatReconnecting++;
  if(Gofast.chatReconnecting > 0 ){ //A chat reconnecting request is pending
    return;
  }
  $('#jsxc_roster').addClass('jsxc_noConnection');
  $('#jsxc_buddylist').empty();
  $('#jsxc_roster').prepend('<p class="chat-issue">' + Drupal.t("Please wait a few seconds.", {}, {'context' : 'gofast:gofast_chat'}) + '</p>');
  $('#jsxc_roster').prepend('<div class="chat-issue loader-chat"></div>');
  $('#jsxc_roster').prepend('<p class="chat-issue">' + Drupal.t("Connecting...", {}, {'context' : 'gofast:gofast_chat'}) + '</p>');
  
  $(document).on('stateUIChange.jsxc', function(e, state){
    if(state === 1){
      $('.chat-issue').remove();
      Gofast.chatReconnecting = 0;
    }
  });
  
  if (jsxc.role_allocation && !jsxc.master) { //That's not the master tab
    return;
  }
  
  //Try to reconnect the user
  if(Drupal.settings.userName.indexOf('@') !== -1){
      var uname = Drupal.settings.userName.substring(0, Drupal.settings.userName.indexOf('@'));
  }
  else{
    var uname = Drupal.settings.userName;
  }
  var jid = uname + "@" + Drupal.settings.XMPP_DOMAIN;
};

// ----------------------------------------------------------------
// MUC
// ---------------------------------------------------------------

/**
 * @CEO-VISION JSXC Override
 * Override default function to be able to add a link attribute (link to user profile)
 * @param {type} room
 * @param {type} nickname
 * @param {type} password
 * @param {type} roomName
 * @param {type} subject
 * @param {type} bookmark
 * @param {type} autojoin
 * @param {type} group
 * @returns {undefined}
 */
  jsxc.muc.join = function (room, nickname, password, roomName, subject, bookmark, autojoin, group) {
    var self = jsxc.muc;

    jsxc.storage.setUserItem('buddy', room, {
      jid: room,
      name: roomName || room,
      sub: 'both',
      type: 'groupchat',
      state: self.CONST.ROOMSTATE.INIT,
      subject: subject,
      bookmarked: bookmark || false,
      autojoin: autojoin || false,
      nickname: nickname,
      // @CEO-VISION ------------------
      link: (group ? group : null),
      //-------------------------------
      config: null
    });

    jsxc.xmpp.conn.muc.join(room, nickname, null, null, null, password);

    if (bookmark) {
      jsxc.xmpp.bookmarks.add(room, roomName, nickname, autojoin);
    }
  };
  
/**
 * @CEO-VISION JSXC Override
 * Override default function to be able to selfExit a room
 * @param {type} room
 * @returns {undefined}
 */
  jsxc.muc.onExited = function (room) {
    var self = jsxc.muc;
    var own = jsxc.storage.getUserItem('ownNicknames') || {};
    var roomdata = jsxc.storage.getUserItem('buddy', room) || {};

    jsxc.storage.setUserItem('roomNames', self.conn.muc.roomNames);

    delete own[room];
    jsxc.storage.setUserItem('ownNicknames', own);
    jsxc.storage.removeUserItem('member', room);
    jsxc.storage.removeUserItem('chat', room);

    jsxc.gui.window.close(room);

//    jsxc.storage.updateUserItem('buddy', room, 'state', self.CONST.ROOMSTATE.EXITED);
//    if (roomdata.bookmarked) {
//      jsxc.gui.roster.purge(room);
//    }

    //@CEO-VISION--------------------
    jsxc.gui.roster.remove(room);

    jsxc.storage.updateUserItem('buddy', room, 'state', self.CONST.ROOMSTATE.EXITED);

    var selfExitCloseRooms = jsxc.storage.getUserItem('selfExitCloseRooms') || [];
    if (selfExitCloseRooms.indexOf(roomdata.jid) < 0) {
      selfExitCloseRooms.push(roomdata.jid);
    }
    jsxc.storage.setUserItem('selfExitCloseRooms', selfExitCloseRooms);
    
    if (!roomdata.bookmarked) {
      jsxc.gui.roster.purge(room);
    }
    //-------------------------------
    
  };
  
  
   /**
   * @CEO-VISION JSXC Override
   * Override to :
   * - replace JID by nickname
   * @param {type} event
   * @param {type} from
   * @param {type} status
   * @param {type} presence
   * @returns {Boolean}
   */
  jsxc.muc.onPresence = function (event, from, status, presence) {

    var self = jsxc.muc;
    var room = jsxc.jidToBid(from);
    var roomdata = jsxc.storage.getUserItem('buddy', room);
    var xdata = $(presence).find('x[xmlns^="' + Strophe.NS.MUC + '"]');

    if (self.conn.muc.roomNames.indexOf(room) < 0 || xdata.length === 0) {
      return true;
    }
    
    var res = Strophe.getResourceFromJid(from) || '';
    var nickname = Strophe.unescapeNode(res);
    var own = jsxc.storage.getUserItem('ownNicknames') || {};
    var member = jsxc.storage.getUserItem('member', room) || {};
    var codes = [];

    xdata.find('status').each(function () {
      var code = $(this).attr('code');

      jsxc.debug('[muc][code]', code);

      codes.push(code);
    });

    if (roomdata.state === self.CONST.ROOMSTATE.INIT) {
      // successfully joined
      
      roomdata.status = jsxc.CONST.STATUS.indexOf('online');
      jsxc.storage.setUserItem('buddy', room, roomdata);

      jsxc.storage.setUserItem('roomNames', jsxc.xmpp.conn.muc.roomNames);

      if (jsxc.gui.roster.getItem(room).length === 0) {
        var bl = jsxc.storage.getUserItem('buddylist');
        bl.push(room);
        jsxc.storage.setUserItem('buddylist', bl);

        jsxc.gui.roster.add(room);
      }

      if ($('#jsxc_dialog').length > 0) {
        // User joined the room manually 
        jsxc.gui.window.open(room);
        jsxc.gui.dialog.close();
      }
    }

    var jid = xdata.find('item').attr('jid') || null;

    if (status === 0) {
      if (xdata.find('destroy').length > 0) {
        
        // @CEO-VISION PATCH - Disabled for NOW
//        jsxc.storage.updateUserItem('buddy', room, 'state', self.CONST.ROOMSTATE.AWAIT_DESTRUCTION);
        
        // room has been destroyed
        member = {};

        jsxc.gui.window.postMessage({
          bid: room,
          direction: jsxc.Message.SYS,
          msg: $.t('This_room_has_been_closed', {}, {'context' : 'gofast:gofast_chat'})
        });

        self.close(room);
      } else {

        delete member[nickname];

        self.removeMember(room, nickname);

        var newNickname = xdata.find('item').attr('nick');

        if (codes.indexOf('303') > -1 && newNickname) {
          // user changed his nickname

          newNickname = Strophe.unescapeNode(newNickname);

          // prevent to display enter message
          member[newNickname] = {};

          jsxc.gui.window.postMessage({
            bid: room,
            direction: jsxc.Message.SYS,
            msg: $.t('is_now_known_as', {
              oldNickname: nickname,
              newNickname: newNickname,
              escapeInterpolation: true
            }, {'context' : 'gofast:gofast_chat'})
          });
        } else if (codes.length === 0 || (codes.length === 1 && codes.indexOf('110') > -1)) {
          // normal user exit
          jsxc.gui.window.postMessage({
            bid: room,
            direction: jsxc.Message.SYS,
            msg: $.t('left_the_building', {
              nickname: nickname,
              escapeInterpolation: true
            }, {'context' : 'gofast:gofast_chat'})
          });
        }
        
        // @CEO-VISION---------
//Disabled PATCH for NOW !!
//        if (jsxc.storage.getUserItem('member', room)) {
//          jsxc.storage.updateUserItem('buddy', room, 'status', 5);
//        }
        //---------------------

      }
    } else {
      // new member joined
      
      if (!member[nickname] && own[room]) {
        jsxc.gui.window.postMessage({
          bid: room,
          direction: jsxc.Message.SYS,
          msg: $.t('entered_the_room', {
            nickname: nickname,
            escapeInterpolation: true
          }, {'context' : 'gofast:gofast_chat'})
        });
      }

      member[nickname] = {
        // @CEO-VISION---------
        jid: jid ? jid : nickname + "@" + jsxc.options.xmpp.domain, // jid: jid,
       //----------------------
        status: status,
        roomJid: from,
        affiliation: xdata.find('item').attr('affiliation'),
        role: xdata.find('item').attr('role')
      };

      self.insertMember(room, nickname, member[nickname]);
    }

    jsxc.storage.setUserItem('member', room, member);

    $.each(codes, function (index, code) {
      // call code functions and trigger event

      if (typeof self.onStatus[code] === 'function') {
        self.onStatus[code].call(this, room, nickname, member[nickname] || {}, xdata);
      }

      $(document).trigger('status.muc.jsxc', [code, room, nickname, member[nickname] || {}, presence]);
    });

    return true;
  };
  
  /**
 * @CEO-VISION JSXC Override
 * Override default function to :
 * - hide fields containing server URL, bookmark, autojoin, nickname
 * - fill room list with those from Gofast
 * - override room name to comply with GOFASt Group Name
 * - add user and create room in a setTimeout()
 * - Hide warning "You already joined the ...."
 * Open join dialog.
 * 
 * @memberOf jsxc.muc
 * @param {string} [r] - room jid
 * @param {string} [p] - room password
 */
jsxc.muc.showJoinChat = function (r, p) {
  var self = jsxc.muc;
  var dialog = jsxc.gui.dialog.open(jsxc.gui.template.get('joinChat'));

  // hide second step button
  dialog.find('.jsxc_join').hide();

  // prepopulate room jid
  if (typeof r === 'string') {
    dialog.find('#jsxc_room').val(r);
  }

  // prepopulate room password
  if (typeof p === 'string') {
    dialog.find('#jsxc_password').val(p);
  }

  // display conference server and hide the field
  var serverInputTimeout;
  dialog.find('#jsxc_server').val(jsxc.options.get('muc').server);
  dialog.find('#jsxc_server').on('input', function() {
     var self = $(this);

     if (serverInputTimeout) {
        clearTimeout(serverInputTimeout);
        dialog.find('.jsxc_inputinfo.jsxc_room').hide();
     }
     dialog.find('.jsxc_inputinfo.jsxc_server').hide().text('');
     dialog.find('#jsxc_server').removeClass('jsxc_invalid');

     if (self.val() && self.val().match(/^[.-0-9a-zA-Z]+$/i)) {
        dialog.find('.jsxc_inputinfo.jsxc_room').show().addClass('jsxc_waiting');

        serverInputTimeout = setTimeout(function() {
           loadRoomList(self.val());
        }, 1800);
     }
  }).trigger('input');

  // @CEO-VISION---------
  dialog.find('#jsxc_server').parent().parent().hide();
  // --------------------

  // handle error response
  var error_handler = function (event, condition, room) {
    var msg;

    switch (condition) {
      case 'not-authorized':
        // password-protected room
        msg = $.t('A_password_is_required');
        break;
      case 'registration-required':
        // members-only room
        msg = $.t('You_are_not_on_the_member_list');
        break;
      case 'forbidden':
        // banned users
        msg = $.t('You_are_banned_from_this_room');
        break;
      case 'conflict':
        // nickname conflict
        msg = $.t('Your_desired_nickname_');
        break;
      case 'service-unavailable':
        // max users
        msg = $.t('The_maximum_number_');
        break;
      case 'item-not-found':
        // locked or non-existing room
        msg = $.t('This_room_is_locked_');
        break;
      case 'not-allowed':
        // room creation is restricted
        msg = $.t('You_are_not_allowed_to_create_');
        break;
      default:
        jsxc.warn('Unknown muc error condition: ' + condition);
        msg = $.t('Error') + ': ' + condition;
    }

    // clean up strophe.muc rooms
    var roomIndex = self.conn.muc.roomNames.indexOf(room);

    if (roomIndex > -1) {
      self.conn.muc.roomNames.splice(roomIndex, 1);
      delete self.conn.muc.rooms[room];
    }

    $('<p>').addClass('jsxc_warning').text(msg).appendTo(dialog.find('.jsxc_msg'));
  };

  $(document).on('error.muc.jsxc', error_handler);

  $(document).on('close.dialog.jsxc', function () {
    $(document).off('error.muc.jsxc', error_handler);
  });

  //----------------------------------------------
  // @CEO-VISION : load room list
  //We Override the JSXC system as we list all available spaces channels user can
  //get in.
  var html_selector = "<select name='room' id='jsxc_room' class='form-control' required></select>";
  $('#jsxc_room').replaceWith(html_selector);
  var User = Gofast.get("user");
  $.ajax({ //Retrieve my rooms and fill the selector
    url : Drupal.settings.gofast.baseUrl+'/og/api/get/spaces/user/'+User.uid,
    type : 'GET',
    dataType: 'html',
    success : function(content, status){ //We edit the display (button + membership sentence)
      var myGroups = JSON.parse(content);
      for(var g in myGroups){
        var group_name = myGroups[g].substr(0, myGroups[g].lastIndexOf("_#"));
        var group_room_id = myGroups[g].toLowerCase();
        $('#jsxc_room').append($('<option>', {
          value: group_room_id,
          text: group_name
        }));
      }
    }
  });
  //----------------------------------------------

  dialog.find('#jsxc_nickname').attr('placeholder', Strophe.getNodeFromJid(self.conn.jid));
  // @CEO-VISION---------
  dialog.find('#jsxc_nickname').parent().parent().hide();
  //---------------------

  dialog.find('#jsxc_bookmark').change(function () {
    if ($(this).prop('checked')) {
      $('#jsxc_autojoin').prop('disabled', false);
      $('#jsxc_autojoin').parent('.checkbox').removeClass('disabled');
    } else {
      $('#jsxc_autojoin').prop('disabled', true).prop('checked', false);
      $('#jsxc_autojoin').parent('.checkbox').addClass('disabled');
    }
  }).parent().parent().parent().hide(); // @CEO-VISION hide bookmark

  //CEO-VISION ----------------- Hide autojoin
  dialog.find('#jsxc_autojoin').parent().parent().parent().hide();

  dialog.find('.jsxc_continue').click(function (ev) {
    ev.preventDefault();

    var room = ($('#jsxc_room').val()) ? jsxc.jidToBid($('#jsxc_room').val()) : null;
    var nickname = $('#jsxc_nickname').val() || Strophe.getNodeFromJid(self.conn.jid);
    var server = dialog.find('#jsxc_server').val();

    //CEO-VISION
    var password = $('#jsxc_password').val() || null;

    if (!room || !room.match(/^[^"&\'\/:<>@\s]+$/i)) {
      $('#jsxc_room').addClass('jsxc_invalid').keyup(function () {
        if ($(this).val()) {
          $(this).removeClass('jsxc_invalid');
        }
      });
      return false;
    }

    if (dialog.find('#jsxc_server').hasClass('jsxc_invalid')) {
        return false;
     }

    if (!room.match(/@(.*)$/)) {
      room += '@' + server;
    }

    // @CEO-VISION -----------------------
    var title = room.substr(0, room.lastIndexOf("_#"));
    var gid = room.substr(room.lastIndexOf("_#")+2, room.lastIndexOf("@"));
    // -----------------------------------

    if (jsxc.xmpp.conn.muc.roomNames.indexOf(room) < 0) {

      // not already joined

        var discoReceived = function(roomName, subject) {
           // we received the room information

           jsxc.gui.dialog.resize();

           dialog.find('.jsxc_continue').hide();

           dialog.find('.jsxc_join').show().effect('highlight', {
              color: 'green'
           }, 4000);

           dialog.find('.jsxc_join').click(function(ev) {
              ev.preventDefault();

              var bookmark = $("#jsxc_bookmark").prop("checked");
              var autojoin = $('#jsxc_autojoin').prop('checked');
              var password = $('#jsxc_password').val() || null;

              // clean up

              jsxc.gui.window.clear(room);
              jsxc.storage.setUserItem('member', room, {});

              self.join(room, nickname, password, roomName, subject, bookmark, autojoin);

              return false;
           });
        };

        dialog.find('.jsxc_msg').append($('<p>').text($.t('Loading_room_information')).addClass('jsxc_waiting'));
        jsxc.gui.dialog.resize();

        self.conn.disco.info(room, null, function(stanza) {
           dialog.find('.jsxc_msg').html('<p>' + $.t('This_room_is') + '</p>');

           var table = $('<table>');

           $(stanza).find('feature').each(function() {
              var feature = $(this).attr('var');

              if (feature !== '' && i18next.exists(feature)) {
                 var tr = $('<tr>');
                 $('<td>').text($.t(feature + '.keyword')).appendTo(tr);
                 $('<td>').text($.t(feature + '.description')).appendTo(tr);
                 tr.appendTo(table);
              }

              if (feature === 'muc_passwordprotected') {
                 dialog.find('#jsxc_password').parents('.form-group').removeClass('jsxc_hidden');
                 dialog.find('#jsxc_password').attr('required', 'required');
                 dialog.find('#jsxc_password').addClass('jsxc_invalid');
              }
           });

           dialog.find('.jsxc_msg').append(table);

           var roomName = $(stanza).find('identity').attr('name');
           var subject = $(stanza).find('field[var="muc#roominfo_subject"]').attr('label');

           //TODO display subject, number of occupants, etc.

           discoReceived(roomName, subject);
        }, function() {
           dialog.find('.jsxc_msg').empty();
           $('<p>').text($.t('Room_not_found_')).appendTo(dialog.find('.jsxc_msg'));

           discoReceived();
        });

        // @CEO-VISION ----------------------------------
        setTimeout(function() {
          jsxc.gui.window.clear(room);
          jsxc.storage.setUserItem('member', room, {});
          jsxc.muc.join(room, nickname, '', title, '', true, true, gid);
          jsxc.muc.conn.muc.createInstantRoom(room);
          jsxc.muc.conn.muc.setTopic(room, title);
          jsxc.gui.window.open(room, false);
        }, 2000);  
        Gofast.toast('', "info", Drupal.t("Joining conversation...", {}, {'context' : 'gofast:gofast_chat'}));
        //-------------------------------------------------------
    } else {
     // $('<p>').addClass('jsxc_warning').text($.t('You_already_joined_this_room')).appendTo(dialog.find('.jsxc_msg'));
      jsxc.gui.window.open(room, false);
    }
     return false;   
  });

  dialog.find('input').keydown(function (ev) {

    if (ev.which !== 13) {
      // reset messages and room information

      dialog.find('.jsxc_warning').remove();

      if (dialog.find('.jsxc_continue').is(":hidden") && $(this).attr('id') !== 'jsxc_password') {
        dialog.find('.jsxc_continue').show();
        dialog.find('.jsxc_join').hide().off('click');
        dialog.find('.jsxc_msg').empty();
        dialog.find('#jsxc_password').parents('.form-group').addClass('jsxc_hidden');
        dialog.find('#jsxc_password').attr('required', '');
        dialog.find('#jsxc_password').removeClass('jsxc_invalid');
        jsxc.gui.dialog.resize();
      }

      return;
    }

    if (!dialog.find('.jsxc_continue').is(":hidden")) {
      dialog.find('.jsxc_continue').click();
    } else {
      dialog.find('.jsxc_join').click();
    }
  });

  function loadRoomList(server) {
     if (!server) {
        dialog.find('.jsxc_inputinfo').hide();

        return;
     }

     // load room list
     self.conn.muc.listRooms(server, function(stanza) {
        // workaround: chrome does not display dropdown arrow for dynamically filled datalists
        $('#jsxc_roomlist option:last').remove();

        $(stanza).find('item').each(function() {
           var r = $('<option>');
           var rjid = $(this).attr('jid').toLowerCase();
           var rnode = Strophe.getNodeFromJid(rjid);
           var rname = $(this).attr('name') || rnode;

           r.text(rname);
           r.attr('data-jid', rjid);
           r.attr('value', rnode);

           $('#jsxc_roomlist select').append(r);
        });

        var set = $(stanza).find('set[xmlns="http://jabber.org/protocol/rsm"]');

        if (set.length > 0) {
           var count = set.find('count').text() || '?';

           dialog.find('.jsxc_inputinfo').show().removeClass('jsxc_waiting').text($.t('Could_load_only', {
              count: count
           }));
        } else {
           dialog.find('.jsxc_inputinfo').hide();
        }
     }, function(stanza) {
        var errTextMsg = $(stanza).find('error text').text() || null;
        jsxc.warn('Could not load rooms', errTextMsg);

        if (errTextMsg) {
           dialog.find('.jsxc_inputinfo.jsxc_server').show().text(errTextMsg);
        }

        if ($(stanza).find('error remote-server-not-found')) {
           dialog.find('#jsxc_server').addClass('jsxc_invalid');
        }

        dialog.find('.jsxc_inputinfo.jsxc_room').hide();
     });
  }


};

 /**
   * @CEO-VISION JSXC Override
   * Override default function to Add Profile_Link
   * @param {type} room
   * @param {type} nickname
   * @param {type} memberdata
   * @returns {undefined}
   */
  jsxc.muc.insertMember = function (room, nickname, memberdata) {
    var self = jsxc.muc;
    var win = jsxc.gui.window.get(room);
    var jid = memberdata.jid; // in fact, this is jid
    var ownBid = jsxc.jidToBid(jsxc.storage.getItem('jid'));
    var m = win.find('.jsxc_memberlist li[data-nickname="' + nickname + '"]');


    if (m.length === 0) {
      var title = jsxc.escapeHTML(nickname);

      m = $('<li><div class="jsxc_avatar"></div><div class="jsxc_name"/></li>');
      m.attr('data-nickname', nickname);
      win.find('.jsxc_memberlist ul').append(m);

      if (typeof jid === 'string') {

        m.find('.jsxc_name').text(jsxc.jidToBid(jid));
        title = title + '\n' + jsxc.jidToBid(jid);
        
        // @CEO-VISION-----------------------------------------
        var profileLink = null;
        var name = '';

        if (jsxc.jidToBid(jid) === jsxc.jidToBid(jsxc.storage.getItem("jid"))) {
          profileLink = jsxc.storage.getUserItem("link", "own");
          name = jsxc.storage.getUserItem("name", "own");
          m.find("div:first").addClass("jsxc_" + jsxc.storage.getUserItem("presence"));
          //jsxc.gui.updateAvatar(m, jsxc.jidToBid(jid), 'own');
          jsxc.gui.avatar.update(m, jsxc.jidToBid(jid), 'own');
          
        } else {
        // -------------------------------------------------  
        
          var data = jsxc.storage.getUserItem('buddy', jsxc.jidToBid(jid));
          if (data !== null && typeof data === 'object') {
            // @CEO-VISION-----------------------------------------
            profileLink = data.link;
            name = data.name;
            m.find("div:first").addClass("jsxc_" + jsxc.CONST.STATUS[data.status]);
            // ------------------------------------------------- 
            jsxc.gui.avatar.update(m, jsxc.jidToBid(jid), data.avatar);
          }
        }

        // @CEO-VISION-----------------------------------------
        if (profileLink && name) {
          m.find('.jsxc_name').html('<a href="' + profileLink + '">' + name + '</a>');
        } else {
          m.find('.jsxc_name').text(name);
        }
        // -------------------------------------------------

      } else {
        m.find('.jsxc_name').text(nickname);
        jsxc.gui.avatarPlaceholder(m.find('.jsxc_avatar'), nickname);
      }

      m.attr('title', title);
    }
  };
  

// ----------------------------------------------------------------
// SCREEN SHARING
// ---------------------------------------------------------------

  // Desktop sharing extension
  jsxc.options.screenMediaExtension = {
    firefox: location.href,
    chrome: Drupal.settings.XMPP_CHROME_EXT_URL
  };
  
  /**
   * @CEO-VISION JSXC Override 
   * Overriding default function to be able to load extension from Chrome store
   * @param {type} jid
   * @returns {undefined}
   */                      
  jsxc.webrtc.startScreenSharing = function(jid){
    var self = this;

      if (Strophe.getResourceFromJid(jid) === null) {
         jsxc.debug('We need a full jid');
         return;
      }
      self.last_caller = jid;

      jsxc.switchEvents({
         'mediaready.jingle': function(ev, stream) {
            self.initiateScreenSharing(jid, stream);
         },
         'mediafailure.jingle': function(ev, err) {
            var browser = self.conn.jingle.RTC.webrtcDetectedBrowser;

            var screenMediaExtension = jsxc.options.get('screenMediaExtension') || {};
            if (screenMediaExtension[browser] &&
               (err.name === 'EXTENSION_UNAVAILABLE' || (err.name === 'NotAllowedError' && browser === 'firefox'))) {
               if(browser === 'chrome'){
                  // Try to install the chrome extension
                  if(!document.getElementById('linkChromeExtension')) {
                    var link = document.createElement('link');
                    link.id = 'linkChromeExtension';
                    link.rel = 'chrome-webstore-item';
                    link.href = Drupal.settings.XMPP_CHROME_EXT_URL;
                    document.head.appendChild(link);
                  }
                  chrome.webstore.install(Drupal.settings.XMPP_CHROME_EXT_URL, function(){
                    //Chrome extension was successfully installed, we reload extensions and start the screensharing
                    setTimeout(function() {
                    jsxc.gui.dialog.close();
                    jsxc.gui.dialog.open(Drupal.t("The extension was successfully installed. Please reload the page to enable the extension.", {}, {'context': 'gofast'}), null, false);
                    }, 500);
                  }, function(message){
                    jsxc.gui.dialog.close();
                    jsxc.gui.dialog.open(Drupal.t("Sorry, we can't download the GoFAST Screensharing extention. Reason: " + message, {}, {'context': 'gofast'}), null, false);
                  });
               }
            }
         }
      });

      self.reqUserMedia(['screen']);
  };

  /**
   * @CEO-VISION JSXC Override 
   * Called if media failes.
   * @private
   * @memberOf jsxc.webrtc
   */
   jsxc.webrtc.onMediaFailure =  function(ev, err) {
      var self = jsxc.webrtc;
      var msg;
      err = err || {};
      self.setStatus('media failure');

      switch (err.name) {
         case 'NotAllowedError':
         case 'PERMISSION_DENIED':
            jsxc.gui.dialog.close();
            jsxc.gui.dialog.open(Drupal.t("You or your browser has refused to give audio/video permissions.", {}, {'context': 'gofast'}), null, false);
            break;
         case 'EXTENSION_UNAVAILABLE':
            jsxc.gui.dialog.close();
            jsxc.gui.dialog.open(Drupal.t("You need to install the GoFAST Screensharing extension to use this functionnality.", {}, {'context': 'gofast'}), null, false);
            break;
         case 'HTTPS_REQUIRED':
         default:    
      }
      jsxc.debug('media failure: ' + err.name);
   };
// ----------------------------------------------------------------

 /**
   * @CEO-VISION JSXC Override 
   * Override default function to force a new user logged to be added in roster
   * This patch should have be done on server side (EJABBERD), but recompiling ERLANG seemed to complicated
   * see GOFAST-2902 in JIRA
   * @param {type} presence
   * @returns {Boolean}
   */
  jsxc.xmpp.onPresence = function(presence) {
    /*
     * <presence xmlns='jabber:client' type='unavailable' from='' to=''/>
     *
     * <presence xmlns='jabber:client' from='' to=''> <priority>5</priority>
     * <c xmlns='http://jabber.org/protocol/caps'
     * node='http://psi-im.org/caps' ver='caps-b75d8d2b25' ext='ca cs
     * ep-notify-2 html'/> </presence>
     *
     * <presence xmlns='jabber:client' from='' to=''> <show>chat</show>
     * <status></status> <priority>5</priority> <c
     * xmlns='http://jabber.org/protocol/caps' node='http://psi-im.org/caps'
     * ver='caps-b75d8d2b25' ext='ca cs ep-notify-2 html'/> </presence>
     */
    jsxc.debug('onPresence', presence);

    var ptype = $(presence).attr('type');
    var from = $(presence).attr('from');
    var jid = Strophe.getBareJidFromJid(from).toLowerCase();
    var r = Strophe.getResourceFromJid(from);
    var bid = jsxc.jidToBid(jid);
    var data = jsxc.storage.getUserItem('buddy', bid) || {};
    var res = jsxc.storage.getUserItem('res', bid) || {};
    var status = null;
    var xVCard = $(presence).find('x[xmlns="vcard-temp:x:update"]');

    if (jid === Strophe.getBareJidFromJid(jsxc.storage.getItem("jid"))) {
       return true;
    }
    
    if (jid.match("admin")){
      return false;
    }
    
    //GOFAST-3184 Security Update
      if(jsxc.xmpp.conn != null){
        jsxc.xmpp.conn.pass = null;
      }
    //remove loader chat spinner as we are connected
    $(".chat-issue").remove();

    // ---------------------------------------------------------------
    // @CEO-VISION patch to FORCE add user to roster (after login)
      if(!ptype){          
        //add new user to roster !
        var bl = jsxc.storage.getUserItem('buddylist');
        var temp = 'created';

        if (bl.indexOf(bid) < 0) {
           bl.push(bid); // (INFO) push returns the new length
           jsxc.storage.setUserItem('buddylist', bl);

           var temp = jsxc.storage.saveBuddy(bid, {
             jid: jid,
             name: from,
             sub: 'both' //auto subscribe both user side
          });  

          //reload data variable with updated values;
          data = jsxc.storage.getUserItem('buddy', bid);
          jsxc.gui.roster.add(bid);
        }
      }
    // ---------------------------------------------------------------

    if (ptype === 'error') {
       $(document).trigger('error.presence.jsxc', [from, presence]);

       var error = $(presence).find('error');

       //TODO display error message
       jsxc.error('[XMPP] ' + error.attr('code') + ' ' + error.find(">:first-child").prop('tagName'));
       return true;
    }

    // incoming friendship request
    if (ptype === 'subscribe') {
       var bl = jsxc.storage.getUserItem('buddylist');

       if (bl.indexOf(bid) > -1) {
          jsxc.debug('Auto approve contact request, because he is already in our contact list.');

          jsxc.xmpp.resFriendReq(jid, true);
          if (data.sub !== 'to') {
             jsxc.xmpp.addBuddy(jid, data.name);
          }

          return true;
       }

       jsxc.storage.setUserItem('friendReq', {
          jid: jid,
          approve: -1
       });
       jsxc.notice.add({
          msg: $.t('Friendship_request'),
          description: $.t('from') + ' ' + jid,
          type: 'contact'
       }, 'gui.showApproveDialog', [jid]);

       return true;
    } else if (ptype === 'unavailable' || ptype === 'unsubscribed') {
       status = jsxc.CONST.STATUS.indexOf('offline');
    } else {

       var show = $(presence).find('show').text();
       if (show === '') {
          status = jsxc.CONST.STATUS.indexOf('online');
       } else {
          status = jsxc.CONST.STATUS.indexOf(show);
       }
    }

    if (status === 0) {
       delete res[r];
    } else if (r) {
       res[r] = status;
    }

    var maxVal = [];
    var max = 0,
       prop = null;
    for (prop in res) {
       if (res.hasOwnProperty(prop)) {
          if (max <= res[prop]) {
             if (max !== res[prop]) {
                maxVal = [];
                max = res[prop];
             }
             maxVal.push(prop);
          }
       }
    }

  if (data.status === 0 && max > 0) {
       // buddy has come online
       jsxc.notification.notify({
          title: data.name,
          msg: $.t('has_come_online'),
          source: bid
       });
    }

    if (data.type !== 'groupchat') {
       data.status = max;
    }

    data.res = maxVal;
    data.jid = jid;

    // Looking for avatar
    if (xVCard.length > 0 && data.type !== 'groupchat') {
       var photo = xVCard.find('photo');

       if (photo.length > 0 && photo.text() !== data.avatar) {
          jsxc.storage.removeUserItem('avatar', data.avatar);
          data.avatar = photo.text();
       }
    }

    // Reset jid
    if (jsxc.gui.window.get(bid).length > 0) {
       jsxc.gui.window.get(bid).data('jid', jid);
    }

    jsxc.storage.setUserItem('buddy', bid, data);
    jsxc.storage.setUserItem('res', bid, res);

    jsxc.debug('Presence (' + from + '): ' + jsxc.CONST.STATUS[status]);

    jsxc.gui.update(bid);
    jsxc.gui.roster.reorder(bid);

    $(document).trigger('presence.jsxc', [from, status, presence]);

    // preserve handler
    return true;
 };


 // @CEO-VISION Patch for mutli-tab for JSXC 3.2.1
 /*$(document).unbind('stateUIChange.jsxc');
 $(document).on('stateChange.jsxc', function(ev, state) {
   if (state === jsxc.CONST.STATE.READY) {
      jsxc.xmpp.httpUpload.init();
   }
});*/
                              
                              
                              

  $(document).on('presence.jsxc', jsxc.muc.onPresence);
  $(document).on('init.window.jsxc', jsxc.muc.initWindow);

})(jQuery, Gofast, Drupal);
