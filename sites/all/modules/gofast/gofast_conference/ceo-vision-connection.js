// Gofast : This is a backup of ceo-vision-connection.js on the server srv03.ceo-vision.com
var randomString = function(length) { // Generate the random anonymous XMPP accounts
  var text = "";
  var possible = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
  for(var i = 0; i < length; i++) {
      text += possible.charAt(Math.floor(Math.random() * possible.length));
  }
  return text;
};

var getCookie = function(name) { // Get cookie from javascript
  var nameEQ = name + "=";
  var ca = document.cookie.split(';');
  for(var i=0;i < ca.length;i++) {
      var c = ca[i];
      while (c.charAt(0)==' ') c = c.substring(1,c.length);
      if (c.indexOf(nameEQ) == 0) return c.substring(nameEQ.length,c.length);
  }
  return null;
};

var callbackError = function(error) {
  alert(error);
  window.location.href = window.location.origin;
};

var gofast_conference = {
  token: '',
  nid: '',
  domain: ''
};

function loginGofastConference(token,nid,domain) {
  if (typeof window.localStorage !== 'undefined' && token && nid && domain) {
    gofast_conference.token = token;
    gofast_conference.nid = nid;
    gofast_conference.domain = domain;
    var username = getCookie('gofast_user');
    //var conferenceAuthDomain = decodeURIComponent(getCookie('conference_auth_domain'));
    var url = gofast_conference.domain + '/conference/login';

    $.ajax({
      'url': url,
      'data': {
        'username': username,
        'nid': nid,
        'token': token
      },
      'type': 'POST',
      'dataType': 'json',
      'async': true
    }).done(function(result) {
      if (typeof result.error !== 'undefined') {
          callbackError(result.error);
      } else {
          if (result.xmppAccount !== '') {
              window.localStorage.setItem('xmpp_username_override', result.xmppAccount + '@' + config.hosts.domain);
              window.localStorage.setItem('xmpp_password_override', result.xmppPassword);
              window.localStorage.setItem('displayname', result.conference_displayname);
              window.XMPPAttachInfo = {
                status: "error"
              };
              if (window.APP && window.APP.connect.status === "ready") {
                window.APP.connect.handler();
              }
          } else {               
                window.localStorage.setItem('xmpp_username_override', randomString(8) + '@' + config.hosts.domain);
                window.localStorage.setItem('xmpp_password_override', randomString(8));
                window.XMPPAttachInfo = {
                  status: "error"
                };
                if (window.APP && window.APP.connect.status === "ready") {
                  window.APP.connect.handler();
                }
          }
      }
    });
  } else {
    window.location.href = window.location.origin;
  }
}

$(document).ready(function(){
	$(window).unload(function(){
		if (gofast_conference.token && gofast_conference.nid && gofast_conference.domain) {
			var token = gofast_conference.token;
			var nid = gofast_conference.nid;
			var username = getCookie('gofast_user');
			//var conferenceAuthDomain = decodeURIComponent(getCookie('conference_auth_domain'));
			var url = gofast_conference.domain + '/conference/logout';
			$.ajax({
			  'url': url,
			  'data': {
				'username': username,
				'nid': nid,
				'token': token
			  },
			  'type': 'POST',
			  'dataType': 'json',
			  'async': false // /!\ IMPORTANT : ensure that this is a synchronous (the ajax callback is triggered before the tab is closed)
			}).done(function(result) {
                window.localStorage.removeItem('displayname');
				if (typeof result.error !== 'undefined') {
				  callbackError(result.error);
				}
			});
		}
	});
});