/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

(function ($, Drupal, Gofast) {
  
//  $(document).ready(function() {
//    $('#conference_date input.date-clear.form-text').val('');
//  });


  
  Drupal.behaviors.createKanbanTaskDeadlineTimePicker = {
    attach: function (context, settings) {
      
      $('input[name="field_date_picker"]').attr('id', 'field_date_picker');
      var hidden_field_id = $('#task_deadline').find('input[name^="field_date"]').attr('id');
              
      var pickedDateTime = $('#field_date_picker').val();
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
      $('#field_date_picker').datetimepicker({
        format: format,
        todayBtn: 'linked',
        todayHighlight: true,
        clearBtn: true,
        language: user.language,
        fontAwesome: true,
        startDate: new Date(),
        autoclose: true,
        bootcssVer: 3,
        linkField: hidden_field_id,
        linkFormat:'yyyy-mm-dd hh:ii'
      }).on('changeDate', function(e) {
        pickedDateTime = $(this).val();
      }).on('hide', function(e) {
        if (pickedDateTime !== '') {
          $('#field_date_picker').val(pickedDateTime);
          
          var current_date = new Date($('#field_date_picker').data("datetimepicker").viewDate);
          current_date.setHours(current_date.getHours()+1);
        }
      });
      
    }
  };
})(jQuery, Drupal, Gofast);
