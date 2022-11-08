/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

(function ($, Gofast, Drupal) {
    
    Gofast.gofast_sorting_room = {
        BuildSortingRoomModal : function(e){
            var element = $(e.target);
            //Stop propagation of the click event
            e.preventDefault();
            e.stopImmediatePropagation();
            var data = [];
            //Get selected elements
            var selected = $('#file_browser_full_files_table').find('.selected').find('.item-path');
            if (selected.length == 0){
              var selected = $('#file_browser_mobile_files_table').find('.selected').find('.item-path');
            }
            $.each(selected, function(k, elem){
              var path = elem.innerText;
              
           //Remove slash at the end if needed
              if(path.substr(-1, 1) === "/"){
                path = path.substring(0, path.length - 1);
              }

              var type = $(elem).parent().find('.item-real-type').text();
              data.push({url: path, type: type});
            });
            data = JSON.stringify(data);

            //Send selected elements to Drupal
            var user_id = Gofast.get("user").uid;
              $.post( "/gofast/variable/set", { name: "ithit_bulk_"+user_id, value: data }).done(function( data ) {
                if($(element[0]).hasClass('toggle_sorting_room') || $(element[0]).parentsUntil('ul').hasClass('toggle_sorting_room')){
                  $('.toggle_sorting_room').removeAttr("onclick");
                  $('.toggle_sorting_room').click();
                }else{
                    if($(element[0]).hasClass('action_sorting_room') || $(element[0]).parentsUntil('ul').hasClass('action_sorting_room')){
                        $('.action_sorting_room').removeAttr("onclick");
                        $('.action_sorting_room').click();
                    }else{
                        if($(element[0]).hasClass('toggle_transfer_room') || $(element[0]).parentsUntil('ul').hasClass('toggle_transfer_room')){
                        $('.toggle_transfer_room').removeAttr("onclick");
                        $('.toggle_transfer_room').click();
                    }
                        
                    }
                }
              });
        }
    };
    
    
})(jQuery, Gofast, Drupal);
