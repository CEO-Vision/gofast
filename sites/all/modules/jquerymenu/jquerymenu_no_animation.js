// $Id: jquerymenu_no_animation.js,v 1.4 2010/05/05 07:50:55 aaronhawkins Exp $

(function ($) {
    
Drupal.behaviors.jquerymenu = { 
    attach:function(context) {

$('ul.jquerymenu .active').parents('li').removeClass('closed').addClass('open');
$('ul.jquerymenu .active').parents('li').children('span.parent').removeClass('closed').addClass('open');

  $('ul.jquerymenu:not(.jquerymenu-processed)', context).addClass('jquerymenu-processed').each(function(){
    $(this).find("li.parent span.parent").click(function(){
      momma = $(this).parent();
      if ($(momma).hasClass('closed')){
        $(momma).removeClass('closed').addClass('open');
        $(this).removeClass('closed').addClass('open');
      }
      else{
        $(momma).removeClass('open').addClass('closed');
        $(this).removeClass('open').addClass('closed');
      }
    });
    showit = function() {
      $(this).children().show();
    }
    hideit = function() {
      $(this).children().hide();
    }
    $(this).find(".editbox").hover(showit, hideit);
  });
}
}})(jQuery);