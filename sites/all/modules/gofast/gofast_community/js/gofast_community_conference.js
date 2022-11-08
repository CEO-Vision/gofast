(function ($, Drupal, Gofast) {
  'use strict';

  $(document).ready(function(){
    
    // remove link for not access the the page
    $("ul li ul li a[title|='Jitsi-meet conference']")
      .attr("href","");

    $("ul li ul li a[title|='Jitsi-meet conference']")
      .on('click', function () {        
        // create modal when link is clicked
        Gofast.modal(
          '<div><p>' + Drupal.t('If you want to know more about meetings in the enterprise version,') + ' <a href=\"https://www.ceo-vision.com/fr/passer-a-la-ged-collaborative-gofast-enterprise" target="blank">' +
          Drupal.t("click here.") +' </a></p></div>',                
          Drupal.t("Feature available in enterprise version only"),
          {}, 
          {'context' : 'gofast'});        
    });

  });
  
})(jQuery,  Drupal, Gofast);


