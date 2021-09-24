// jQuery for Drupal 7 [BEGIN]
(function ($, Gofast, Drupal) {

    console.log('in headlines script');

    var headlineBlock = $('#block-views-gofast-aggregator-block');
    var headlineMenuItem = $('#gofast_block-gofast_aggregator-block');
    // prevent page reload when clicking on pagination
    var paginationLinks = headlineBlock.find('.pagination > li > a');

    paginationLinks.each(function () {
        $(this).click(function (event) {
            event.preventDefault();
        });
    });

    //-------------------------------------------------- OLD STUFF ---------------

    /*$(window).bind("load", function() {
     if($('#gofast_headlines_popup').length != 0) $('#gofast_headlines_popup').css({'marginLeft' : $('#gofast_block-aggregator-category-1').offset().left - $(".container").offset().left - parseInt($(".container").css("padding-left"))});
     });
     
     
     Drupal.behaviors.gofast_headlines_popup = {
     attach: function (context, settings) {
     context = $(context);
     
     headlines_menu = $("#gofast_block-gofast_aggregator-block"),
     headlines = $("#block-views-gofast-aggregator-block"),
     el = headlines_menu.add(headlines);
     el.hover(
     function(){
     headlines.css({
     'display' : 'block',
     });
     },
     
     function(){
     headlines.css('display', 'none');
     }
     );
     
     
     $('#gofast_headlines_popup:not(.ajax-processed)', context).addClass('ajax-processed').each(function() {
     if (Drupal.settings.gofast_headlines_popup) {
     data_tree = Drupal.settings.gofast_headlines_popup.data_tree;
     $('#gofast_headlines_popup').html(data_tree);
     }
     });
     
     }
     }*/


}(jQuery, Gofast, Drupal));