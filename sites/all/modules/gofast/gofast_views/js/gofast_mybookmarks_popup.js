// jQuery for Drupal 7 [BEGIN]
(function ($, Gofast, Drupal) {
  
  $(window).bind("load", function() {
      if($('#gofast_mybookmarks_popup').length != 0) $('#gofast_mybookmarks_popup').css({'marginLeft' : $('#gofast_view-gofast_flag_bookmarks-block_1').offset().left - $(".container").offset().left - parseInt($(".container").css("padding-left"))});
  });
  
  
  Drupal.behaviors.gofast_mybookmarks_popup = {
    attach: function (context, settings) {
      context = $(context);
      
      mybookmarks_menu = $("#gofast_view-gofast_flag_bookmarks-block_1"),
      mybookmarks = $("#gofast_mybookmarks_popup"),
      el = mybookmarks_menu.add(mybookmarks);
      el.hover(
        function(){
          mybookmarks.css({
            'display' : 'block',
          });
        },
        
        function(){
          mybookmarks.css('display', 'none');
        }
      );
      
      
      $('#gofast_mybookmarks_popup:not(.ajax-processed)', context).addClass('ajax-processed').each(function() {
        if (Drupal.settings.gofast_mybookmarks_tree) {
          data_tree = Drupal.settings.gofast_mybookmarks_tree.data_tree;
          console.log(Drupal.settings.gofast_mybookmarks_tree.title);
          $('#gofast_mybookmarks_popup').html(data_tree);
        }
      });
      
    }
  }
 
 
}(jQuery, Gofast, Drupal));