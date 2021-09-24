(function ($, Drupal, Gofast) {
  
//  $(document).ready(function() {
//    $('#conference_end_date input.date-clear.form-text').val('');
//  });
  
  Drupal.behaviors.createConferenceDateTimePickerEnd = {
    attach: function (context, settings) {
      var pickedDateTime = $('#conference_end_date input.date-clear.form-text').val();
      var user = Gofast.get('user');
      var format = '';
      var date = new Date();
      date.setHours(date.getHours() + 1);
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
          //format = 'yyyy-mm-dd hh:ii';
          break;
      }
      $('#conference_end_date input.date-clear.form-text').datetimepicker({
        format: format,
        todayBtn: 'linked',
        todayHighlight: true,
        clearBtn: true,
        language: user.language,
        fontAwesome: true,
        startDate: date,
        autoclose: true,
        bootcssVer: 3
      }).on('changeDate', function(e) {
        pickedDateTime = $(this).val();
      }).on('hide', function(e) {
        if (pickedDateTime !== '') {
          $('#conference_end_date input.date-clear.form-text').val(pickedDateTime);
        }
      });
      
    }
  };
})(jQuery, Drupal, Gofast);