(function ($, Gofast, Drupal) {
  'use strict';
  
  
  $(document).ready(function(){
    Drupal.behaviors.onlyoffice_community = {
      attach: function (context, settings) {
          if($("#contextual_btn_onlyoffice").length !== 0 && !$("#contextual_btn_onlyoffice").hasClass('community-processed')){
            $("#contextual_btn_onlyoffice").removeAttr("onclick");

            $("#contextual_btn_onlyoffice").on('click', function (e) {
              e.preventDefault();
              Gofast.modal(
                '<div><p>' + Drupal.t('If you want to know more about OnlyOffice and collaborative edition in the enterprise version,') + ' <a href="https://www.ceo-vision.com/fr/GoFAST-Travail-Collaboratif-Co-Edition-de-fichiers-Office" target="_blank">' + Drupal.t('click here.') +  '</a></p></div>',          
                Drupal.t("Feature available in enterprise version only"), 
                {},
                {'context' : 'gofast'}
              );  
            });
            
            $("#contextual_btn_onlyoffice").addClass('community-processed');
          }
      }
    }
  });
  
})(jQuery, Gofast, Drupal);



