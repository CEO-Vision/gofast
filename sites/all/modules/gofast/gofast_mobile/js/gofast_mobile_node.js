(function($, Drupal, Gofast) {
  'use strict';
  $(document).ready(function() {
    
    $('#gofast_mobile_panel').on('scroll', function(e) {
      if(Math.ceil($(this).scrollTop() + $(this).innerHeight()) >= $(this)[0].scrollHeight) {
        $('#gofast_mobile_node_actions li:last-child').css('margin-bottom', 20);
      }
    });

  });
})(jQuery, Drupal, Gofast);
