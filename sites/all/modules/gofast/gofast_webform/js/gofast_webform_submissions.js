(function($, Gofast, Drupal) {  
  
  //Attach Drupal behaviors to process the rendered builder
  Drupal.attachBehaviors();
  
  //Unbind click and tap events as we don't need to reload te builder anymore
  $('#webform-submissions-tab').off('tap').off('mouseup');
  
  //Dismiss modal because we use ctools modal to ajaxify this call
  Drupal.CTools.Modal.dismiss();
  
  //Format the table
  $('.view-webform-submissions > .view-header').hide();
  $('.view-webform-submissions > .view-content > table > thead > tr > th > a').each(function(k, v){
    //Remove links in table header
    $(this).replaceWith($(v).text()); 
  });
  
  //Edit actions to format them and use ctools to ajaxify the calls
  $('#webformSubmissions table > tbody > tr').each(function(k,v) {
    $(v).find('td').last().find('a').each(function(ka, va){
      $(va).attr('href', '/gofast/webform' + $(va).attr('href'))
              .addClass('ctools-use-modal').css('color', 'white')
              .replaceWith('<button class=\"btn btn-sm btn-primary\"><i class=\"fa fa-search\" aria-hidden=\"true\"></i> ' + $(va)[0].outerHTML + '</button>');
    });
  });
  
  $('#webformSubmissions table > tbody > tr').each(function(k,v) {
    $(v).find('td').last().find('button').each(function(k,v){
      $(v).click(function(){
        $(v).find('a').click();
      });
    });
  });
  
  $('#webformSubmissions table > tbody > tr').each(function(k,v) {
    $($(v).find('td').last().find('button')[1]).removeClass('btn-primary')
            .addClass('btn-success')
            .find('i')
            .removeClass('fa-search')
            .addClass('fa-pencil');
  });
  
  $('#webformSubmissions table > tbody > tr').each(function(k,v) {
    $($(v).find('td').last().find('button')[2]).removeClass('btn-primary')
            .addClass('btn-danger')
            .find('i')
            .removeClass('fa-search')
            .addClass('fa-trash');
  });
  
  //Attach Drupal behaviors again to process the modified actions
  Drupal.attachBehaviors();
  
})(jQuery, Gofast, Drupal);