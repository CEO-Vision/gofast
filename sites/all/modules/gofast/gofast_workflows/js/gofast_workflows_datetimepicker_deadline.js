(function ($, Drupal, Gofast) {
  
//  $(document).ready(function() {
//    $('#conference_date input.date-clear.form-text').val('');
//  });
  
  Drupal.behaviors.createWorkflowsDeadlineDateTimePicker = {
    attach: function (context, settings) {
      var pickedDateTime = $('.form-item-deadline > div > input').val();
      var user = Gofast.get('user');
      var format = '';
      switch (user.language) {
//        case 'fr':
//          format = 'dd-mm-yyyy hh:ii';
//          break;
        // For now, put it like this. Come back to fix this later  
        case 'en':
          format = 'mm-dd-yyyy';
          break;
        case 'fr':
          format = 'dd-mm-yyyy';
          break;
        default:
          format = 'mm-dd-yyyy';
          break;
      }
      $('.form-item-deadline > div > input').datetimepicker({
        format: format,
        todayBtn: 'linked',
        todayHighlight: true,
        clearBtn: true,
        language: user.language,
        fontAwesome: true,
        autoclose: true,
        bootcssVer: 3,
        minView: 2
      });
      
    }
  };
})(jQuery, Drupal, Gofast);