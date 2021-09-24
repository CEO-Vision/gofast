(function ($, Drupal, Gofast) {
  'use strict';
  
  $(document).ready(function(){
       
    /*
    $('#gofast_block_delta-gofast_workflows_light_dashboard-gofast_workflows')
    .mouseenter(function () {
      var thewidth =  $('#gofast_block_delta-gofast_workflows_light_dashboard-gofast_workflows .gofast-block-outer').width()+21.5;
      $('<div class="gofast-block-outer-link"><p>' + Drupal.t("If you want to know more about workflows in the enterprise version,") + ' <a href="https://www.ceo-vision.com/fr/passer-a-la-ged-collaborative-gofast-enterprise" target="_blank">' + Drupal.t("click here.") + '</a> </p></div>')
                .insertBefore('#gofast_block_delta-gofast_workflows_light_dashboard-gofast_workflows .gofast-block-outer');
      $('div.gofast-block-outer-link').css("width",thewidth+"px");      
    });
    
    $('#gofast_block_delta-gofast_workflows_light_dashboard-gofast_workflows')
    .mouseleave(function () {
      $('.gofast-block-outer-link').remove();
    });
    */
   
   //add class on workflow icone:
   $('.updated-workflow').addClass('badge-error');
   $('.updated-workflow').css('visibility', 'visible');
   

    $('#gofast_block_delta-gofast_workflows_light_dashboard-gofast_workflows :not(.gofast-block-outer)')
    .mouseenter(function () {
      
      $('#gofast_block_delta-gofast_workflows_light_dashboard-gofast_workflows .gofast-block-outer').html("");
      
      $.ajax({
        'type': "POST",
        'url': '/community/rapiddashboard',
        'data': { },
        'success': function (data) {
          
          var parser = new DOMParser();
          var el = parser.parseFromString(data, "text/html");
          var html = $(el).find('div:first').html();

          $('#gofast_block_delta-gofast_workflows_light_dashboard-gofast_workflows .gofast-block-outer').html(html);
          
        }
      });
      
      var thewidth =  $('#gofast_block_delta-gofast_workflows_light_dashboard-gofast_workflows .gofast-block-outer').width()+21.5;
       $('#gofast_block_delta-gofast_workflows_light_dashboard-gofast_workflows .gofast-block-outer').width(thewidth+"px");
          
    });
    
    $('#gofast_block_delta-gofast_workflows_light_dashboard-gofast_workflows')
      .mouseleave(function () {
         
//        $('#gofast_block_delta-gofast_workflows_light_dashboard-gofast_workflows .gofast-block-outer .gofast-block-inner').remove();
//        $('#gofast_block_delta-gofast_workflows_light_dashboard-gofast_workflows .gofast-block-outer .pointeur').remove();
//        $('#gofast_block_delta-gofast_workflows_light_dashboard-gofast_workflows .gofast-block-outer').html("");
    });
    
//    $('#gofast_block_delta-gofast_workflows_light_dashboard-gofast_workflows').focusout(function(){
//       $('#gofast_block_delta-gofast_workflows_light_dashboard-gofast_workflows .gofast-block-outer').html("");
//    });

  });   
  
})(jQuery, Drupal, Gofast);



