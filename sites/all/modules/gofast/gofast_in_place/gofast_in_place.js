(function ($) {
//    jQuery(document).ready(function($) {
//        setTimeout('Drupal.gofast_in_place.test_in_place()',2000);      
//        ;
//    })
   Drupal.gofast_in_place = Drupal.gofast_in_place || {};  
    Drupal.behaviors.extend_in_place_editing = {
          attach: function() {
              $(".edit-processed.edit-field").each(function(){
                  $(this).once('extend_in_place_editing', function() {
                    $(this).click(function(){
                           
                             $(this).removeClass("timeout_in_place_editing");
                            //on recupere le numero de noeud du champs que l'on vient de cliquer
                            var nid = $(this).attr("data-edit-field-id");
                            nid = nid.split("/");
                            nid = nid[1];  
                            console.log(nid);
                            var node_entity = $(this).closest("#node-"+nid);
                            if(node_entity.length == 0){
                                entity_instance_id = 0;
                            }else{
                                console.log(node_entity);
                                var entity_instance_id = node_entity.attr("data-edit-entity-instance-id");
                            }
                            var button_edit = $("[data-edit-entity-instance-id='"+entity_instance_id+"'] .contextual-links-wrapper .quick-edit a");
                           
                            button_edit.click();
                            $(this).addClass("timeout_in_place_editing");
                            setTimeout('Drupal.gofast_in_place.timeout_in_place_editing()',500);                         
                    });
                  })
              })
          }
     }
   
    
    Drupal.gofast_in_place.timeout_in_place_editing = function(){ 
        console.log("timeout_in_place_editing");
              $(".timeout_in_place_editing").trigger( "click" );
              $(".timeout_in_place_editing").focus();
              $(".timeout_in_place_editing").removeClass("timeout_in_place_editing");
              
              
    }
    
//    Drupal.gofast_in_place.test_in_place = function(){
//  
//              
//              $("#node-232 .contextual-links-wrapper .quick-edit a").click();
//              Drupal.behaviors.extend_in_place_editing.attach();
//    }
    
     
    

})(jQuery);