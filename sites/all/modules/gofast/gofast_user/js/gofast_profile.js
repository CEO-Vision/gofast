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
    
    var userlistSection = $('.GofastUserProfile .GofastUserProfile__detail #gf_user_groups .profile-info-table .profile-userlists');
    var groupsSection = $('.GofastUserProfile .GofastUserProfile__detail #gf_user_groups .profile-info-table .profile-groups');
    var requestSection = $('.GofastUserProfile .GofastUserProfile__detail #gf_user_groups .profile-info-table .profile-groups_requested');
    var orgaSection = $('.GofastUserProfile .GofastUserProfile__detail #gf_user_groups .profile-info-table .profile-organisations');
    var publicSection = $('.GofastUserProfile .GofastUserProfile__detail #gf_user_groups .profile-info-table .profile-public');
    var extranetSection = $('.GofastUserProfile .GofastUserProfile__detail #gf_user_groups .profile-info-table .profile-extranet');
    
    Gofast.load_user_profile_section('userlists', userlistSection);
    Gofast.load_user_profile_section('group', groupsSection);
    Gofast.load_user_profile_section('requests', requestSection);
    Gofast.load_user_profile_section('organisation', orgaSection);
    Gofast.load_user_profile_section('public', publicSection);
    Gofast.load_user_profile_section('extranet', extranetSection);
    
  };
  
  // Ajax request to load user spaces
  Gofast.load_user_profile_section = function(section, element){  
    var profile_uid = $('#gf_user_groups').data('profileuid');
    
    $.ajax({
      'type': "GET",
      'url': '/gofast/user/' + profile_uid + '/get_section',
      'data': {'section': section},
      'async': true,
      'success': function (data) {
        console.log(section + ' async loading finished');
        // Check if data is empty
        element.find('.spinner').replaceWith(data);
        
        /** Browser patch */
        var ua = navigator.userAgent;
        /* MSIE used to detect old browsers and Trident used to newer ones*/
        var is_ie = ua.indexOf("MSIE ") > -1 || ua.indexOf("Trident/") > -1;
        if (is_ie != true) {
          jQuery('.profile-groups>div').mCustomScrollbar({ theme: 'dark-thin' });
          jQuery('.profile-organisations>div').mCustomScrollbar({ theme: 'dark-thin' });
          jQuery('.profile-public>div').mCustomScrollbar({ theme: 'dark-thin' });
          jQuery('.profile-extranet>div').mCustomScrollbar({ theme: 'dark-thin' });
          jQuery('.profile-userlists>div').mCustomScrollbar({ theme: 'dark-thin' });
          jQuery('.mCustomScrollbar').css('overflow-y', 'hidden');
        }
      }
    });
  }
  
})(jQuery, Drupal, Gofast);
