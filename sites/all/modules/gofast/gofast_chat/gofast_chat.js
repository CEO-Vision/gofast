var count_get_ticket = 0;


(function ($, Gofast, Drupal) { 
    $(document).ready(function() {

      if(location.href.indexOf("/kanban/") !== -1){
          //Won't display chat in Kanban
          return;
      }
      
      var User = Gofast.get("user");
      var user_language = User.language;
      // required to load correct language for NL cf. GOFAST-4011
      if(user_language === 'nl'){
         user_language = 'nl-NL';
      }

      var jsxcOptions = {
        appName: "GoFAST",
        lang: user_language,
        autoLang: false,
        hideOfflineContacts: false,
        connectionCallback: function(jid, status){
            console.log("JSXC dev : Connection callback with status : " + status);
            if(status === 6){
              Gofast.connect_to_ejabberd();
            }
        },
        onUserRequestsToGoOnline: function(){
            Gofast.connect_to_ejabberd();
        }
      };

      //Instanciate JSXC
      window.jsxc = new JSXC(jsxcOptions);

      if (User.uid != 0) {
          //Initiate connexion to JSXC if our account is not already registered
          if(jsxc.numberOfCachedAccounts == 0){
              Gofast.connect_to_ejabberd();
          }
          
          //Display JSXC actions
          var toggleInterval = setInterval(function(){
              if($("#jsxc-roster").length == 1){
                  clearInterval(toggleInterval);
                  $('#jsxc-hidden-actions').prependTo('#jsxc-roster');
                  $(".jsxc-contact-list").css("margin-top", "0px");
                  $("#jsxc-hidden-actions").css("display", "block");
              }
          }, 200);

          //Add "Join a space room" menu entry
          jsxc.addMenuEntry({
              id: "join-space-room",
              handler: function(){
                  $("#jsxc-hidden-actions > .join-space-room").click();
              },
              label: Drupal.t("Join a space room", {}, {context: "gofast:gofast_chat"})
          });

          //Add "Start conversation" menu entry
          jsxc.addMenuEntry({
              id: "start-conversation",
              handler: function(){
                  $("#jsxc-hidden-actions > .start-conversation").click();
              },
              label: Drupal.t("Add a contact", {}, {context: "gofast:gofast_chat"})
          });

          //Add "Start conversation" menu entry
          jsxc.addMenuEntry({
              id: "manage-relations",
              handler: function(){
                 $("#jsxc-hidden-actions > .manage-relations").click();
              },
              label: Drupal.t("Manage my relations", {}, {context: "gofast:gofast_chat"})
          });
      }

      window.addEventListener('online',  function(){
          Gofast.connect_to_ejabberd();
      });
    });
  
    /*
    * Join or create a MUC room
    * @using: JSXC API
    */
    Gofast.join_space_room = function (jid, name, creation, password) {
        console.log("Calling");
        console.log(jid);
        console.log(name);
        console.log(creation);
        console.log(password);
        //Retrieve current user informations
        var User = Gofast.get("user");

        if(User.name.indexOf('@') !== -1){
          var uname = User.name.substring(0, User.name.indexOf('@'));
        }
        else{
          var uname = User.name;
        }
            
        //Retrieve the current JSXC account
        var account = jsxc.getAccount(uname.toLowerCase() + "@" + Drupal.settings.XMPP_DOMAIN);
        
        //Create the MUC locally
        var contact = account.createMultiUserContact(jid + '@conference.' + Drupal.settings.XMPP_DOMAIN, User.displayName, name, password);
            
        //Join the MUC (will create it if it doesn't exists)
        contact.join();
        contact.addToContactList();
        contact.openChatWindow();
            
        if(creation){
            //This is a MUC creation, configure it
            jsonRoomForm = contact.getRoomConfigurationForm().then(function (form) {
            form.type = "submit";

            form.fields.forEach(function (field) {
                if (field.name === "muc#roomconfig_roomname") {
                    field.values = [name];
                }
                if (field.name === "muc#roomconfig_persistentroom") {
                    field.values = ["1"];
                }
                if (field.name === "mam") {
                    field.values = ["1"];
                }
                if (field.name === "public_list") {
                    field.values = ["0"];
                }
                if (field.name === "muc#roomconfig_passwordprotectedroom") {
                    field.values = ["1"];
                }
                if (field.name === "muc#roomconfig_allowinvites") {
                    field.values = ["0"];
                }
                if (field.name === "muc#roomconfig_moderatedroom") {
                    field.values = ["0"];
                }
                if (field.name === "muc#roomconfig_publicroom") {
                    field.values = ["0"];
                }
                if (field.name === "muc#roomconfig_roomsecret") {
                    field.values = [password];
                }
            });

            contact.submitRoomConfigurationForm(form);
            });
        }
    };
    
    Gofast.connect_to_ejabberd = function(){
        jsxc.enableDebugMode();
        var User = Gofast.get("user");
        var user_language = User.language;
        // required to load correct language for NL cf. GOFAST-4011
        if(user_language === 'nl'){
          user_language = 'nl-NL';
        }

        //Prevent having '@' char in jids
        if(User.name.indexOf('@') !== -1){
          var uname = User.name.substring(0, User.name.indexOf('@'));
        }
        else{
          var uname = User.name;
        }
        
        //Check if another tab is already connecting or connected
        try{
            var account = jsxc.getAccount(uname.toLowerCase() + "@gofast-comm-internal.ceo-vision.com");
            var connection = account.account.connection.connection;
            
            if(connection.connected){
                console.log("JSXC is already connected");
                return;
            }
            if(connection.do_authentication || connection.do_bind || connection.do_session){
                console.log("JSXC is already connecting on another tab");
                return;
            }
        }catch(e){
            //An error here means we have no connected account, catch it silently
        }
        
        if(count_get_ticket > 5){
            return;
        }
        
        //First, we need to retrieve a valid token for this user
        $.get(location.origin + "/api/login/ejabberd", function(response){
            count_get_ticket = count_get_ticket + 1;          
            var token = response.token;
            var promise = jsxc.start(Drupal.settings.XMPP_CHAT_URL, uname + '@' + Drupal.settings.XMPP_DOMAIN, token);

            promise.catch(function(error){
                console.log("Error in JSXC promise : " + error);
                if(error === "Account with this jid already exists."){
                    console.log("Fatal error in JSXC promise : " + error);
                    return;
                }

                //The connexion has failed, force the generation of a new token and try to reconnect
                $.get(location.origin + "/api/login/ejabberd?force=true", function(response){
                    count_get_ticket = count_get_ticket + 1;                     
                    var token = response.token;
                    localStorage.clear();
                    jsxc.enableDebugMode();
                    var promise = jsxc.start(Drupal.settings.XMPP_CHAT_URL, uname + '@' + Drupal.settings.XMPP_DOMAIN, token)
                    
                    promise.catch(function(error){
                        console.log("Fatal error in JSXC promise : " + error);
                    });
                });
            });
        });
    };
})(jQuery, Gofast, Drupal);