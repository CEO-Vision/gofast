(function ($, Drupal, Gofast) {
  
//  $(document).ready(function() {
//    $('#conference_date input.date-clear.form-text').val('');
//  });
  
  Drupal.behaviors.createConferenceDateTimePicker = {
    attach: function (context, settings) {
      var pickedDateTime = $('#conference_date input.date-clear.form-text').val();
      var user = Gofast.get('user');
      var format = '';
      switch (user.language) {
//        case 'fr':
//          format = 'dd-mm-yyyy hh:ii';
//          break;
        // For now, put it like this. Come back to fix this later  
        case 'en':
          format = 'mm-dd-yyyy hh:ii';
          break;
        case 'fr':
          format = 'dd-mm-yyyy hh:ii';
          break;
        default:
          format = 'mm-dd-yyyy hh:ii';
          break;
      }
      $('#conference_date input.date-clear.form-text').datetimepicker({
        format: format,
        todayBtn: 'linked',
        todayHighlight: true,
        clearBtn: true,
        language: user.language,
        fontAwesome: true,
        startDate: new Date(),
        autoclose: true,
        bootcssVer: 3
      }).on('changeDate', function(e) {
        pickedDateTime = $(this).val();
      }).on('hide', function(e) {
        if (pickedDateTime !== '') {
          $('#conference_date input.date-clear.form-text').val(pickedDateTime);
          
          var current_date = new Date($('#conference_date input.date-clear.form-text').data("datetimepicker").viewDate);
          current_date.setHours(current_date.getHours()+1);
          $('#conference_end_date input.date-clear.form-text').data("datetimepicker").setUTCDate(current_date);
        }
      });
      
    }
  };
})(jQuery, Drupal, Gofast);