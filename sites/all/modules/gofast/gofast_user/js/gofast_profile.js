(function ($, Drupal, Gofast) {  
  // Init Gofast settings and globals
  Gofast.global = Gofast.global || {} ;
  Drupal.settings.gofast = Drupal.settings.gofast || {} ;
  
  Drupal.settings.gofast.profile = Drupal.settings.gofast.profile || {};
  
  Gofast.load_user_profile_teams = function(){
      var profile_uid = $('#gf_user_groups').data('profileuid');
      $.ajax({
        'type': "POST",
        'url': '/gofast/user/' + profile_uid + '/myteam', //TODO : change user uid for loading 
        'data': {},  
        'success': function (data) {
            var parser = new DOMParser();
            var el = parser.parseFromString(data, "text/html");
            var myteam = $(el).find('section#block-gofast-user-my-team');
            $(document).find('section#block-gofast-user-my-relationships').after(myteam);
        }
      }); 
  };
  
  Gofast.load_user_profile_spaces = function(){
      var profile_uid = $('#gf_user_groups').data('profileuid');
        $.ajax({
          'type': "POST",
          'url': '/gofast/user/'+profile_uid+'/groups',
          'data': {},  
          'success': function (data) {

              var parser = new DOMParser();
              var el = parser.parseFromString(data, "text/html");
              var groups = $(el).find('table.profile-info-table');

              $(document).find('#gf_user_groups').html(groups);
              
              
              var ua = navigator.userAgent;
              /* MSIE used to detect old browsers and Trident used to newer ones*/
              var is_ie = ua.indexOf("MSIE ") > -1 || ua.indexOf("Trident/") > -1;
              if(is_ie != true){
                  jQuery('.profile-groups>div').mCustomScrollbar({theme: 'dark-thin'});
                  jQuery('.profile-organisations>div').mCustomScrollbar({theme: 'dark-thin'});
                  jQuery('.profile-public>div').mCustomScrollbar({theme: 'dark-thin'});
                  jQuery('.profile-extranet>div').mCustomScrollbar({theme: 'dark-thin'});
                  jQuery('.profile-userlists>div').mCustomScrollbar({theme: 'dark-thin'});
                  jQuery('.mCustomScrollbar').css('overflow-y','hidden');
              }
          }
        }); 
  };
  
})(jQuery, Drupal, Gofast);