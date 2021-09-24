// jQuery for Drupal 7 [BEGIN]
(function ($, Gofast, Drupal) {
  
  /*$(window).bind("load", function() {
      if($('#gofast_notifications_popup').length != 0) $('#gofast_notifications_popup').css({'marginLeft' : $('#gofast_view-privatemsg-privatemsg_bloc_notifications').offset().left - $(".container").offset().left - parseInt($(".container").css("padding-left"))});
  });
  
  
  Drupal.behaviors.gofast_notifications_popup = {
    attach: function (context, settings) {
      context = $(context);
            
      
      $('#gofast_notifications_popup:not(.ajax-processed)', context).addClass('ajax-processed').each(function() {
        if (Drupal.settings.gofast_notifications_tree) {
          var data_tree = Drupal.settings.gofast_notifications_tree.data_tree;
          $('#gofast_notifications_popup').html(data_tree);
//          $(data_tree).children('.view-filters').appendTo(".view-content");
//          console.log($(data_tree).children('.view-filters'));
        }
      });
      
      
      var notifications_menu = $("#gofast_view-privatemsg-privatemsg_bloc_notifications");
      var notifications = $("#gofast_notifications_popup");
      var el = notifications_menu.add(notifications);
      el.hover(
        function(){
          notifications.css({
            'display' : 'block',
          });
        },
        
        function(){
          notifications.css('display', 'none');
        }
      );
      
    }
  }*/
 
 
}(jQuery, Gofast, Drupal));