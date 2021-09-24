(function($, Gofast, Drupal) {  
  
  //Hide unwanted elements, clear some margins, set panels
  $('#modal-content > .clearfix > ul, div.webform-submission-navigation').hide();
  $('.webform-submission-info').addClass('panel panel-info').css('padding', '0px');
  $('.webform-submission-info > legend').addClass('panel-heading').css('font-size', 'inherit');
  $('.webform-submission-info > .webform-submission-info-text').addClass('panel-body').css('padding', '10px');
  $('.webform-submission').addClass('panel panel-info').css('padding', '0px');
  $('.webform-submission').html('<div class=\"panel-body\">' + $('.webform-submission').html() + '</div>');
  $('.webform-submission').prepend('<div class=\"panel-heading\">' + Drupal.t('Submission values', {}, {context: 'gofast:gofast_webform'}) + '</div>');
  
  //Add legends to fields Date & IP
  $($('.webform-submission-info-text > div')[2]).html(Drupal.t('Date: ', {}, {context: 'gofast:gofast_workflow'}) + $($('.webform-submission-info-text > div')[2]).html());
  $($('.webform-submission-info-text > div')[3]).html(Drupal.t('IP: ', {}, {context: 'gofast:gofast_workflow'}) + $($('.webform-submission-info-text > div')[3]).html());
  
  //Stylize webform components
  $('.webform-submission').find('.webform-component').addClass('panel panel-default');
  
  $('.webform-submission').find('.webform-component').each(function(k, v){
    $(v).html('<div class=\"panel-body\">' + $(v).html() + '</div>');
  });
  
  $('.webform-submission').find('.webform-component').each(function(k, v){
    var label = $(v).find('label').addClass('panel-heading');
    $(v).prepend(label);
  });
  
  //Hide unwanted user picture
  $('.webform-submission-info > .user-picture').hide();
  
  //Attach Drupal behaviors
  Drupal.attachBehaviors();
  
})(jQuery, Gofast, Drupal);