(function ($, Gofast, Drupal) {
    
    Drupal.behaviors.remove_item_from_cart = {
      attach : function (context, settings) { 
        $('.view-gofast-flag-cart table tr').each(function(){
            var item = $(this);
            $(this).find('.unflag-action').click(function(){
                var nid = $(this).attr('href').split('?')[0].split('/')[4];
                $('#cart_node_id option').each(function(){
                   if($(this).text() === nid){
                       $(this).remove();
                   } 
                });
                $(item).remove();
            });
        });
        if ($(".view-empty",context).length){
            $("#file_browser_toolbar_manage").attr('disabled',true);
            $("#remove_all_documents").attr('disabled',true);
            $("#remove_all_documents").removeAttr("onclick");
        }
      }
    }; 
  
    Gofast.Cart = {
        bulkSelectedCart: function(e, nid){
            var element = $(e.target);
            //Stop propagation of the click event
            e.preventDefault();
            e.stopImmediatePropagation();
            var data = [];

            if(nid){
              data.push({url: nid, type: "Node"});
            }else{
              //Get selected elements
              var selected = $('#cart_node_id option');
              $.each(selected, function(k, elem){
                var nid = elem.innerText;
                var type = "Resource";
                data.push({url: nid, type: type});
              });
            }
            data = JSON.stringify(data);

            //Send selected elements to Drupal
            var user_id = Gofast.get("user").uid;
              $.post( "/gofast/variable/set", { name: "ithit_bulk_cart_"+user_id, value: data }).done(function( data ) {
                if($(element[0]).hasClass('manage-taxonomy') || $(element[0]).parentsUntil('ul').hasClass('manage-taxonomy')){
                  $('.bulk_taxonomy').click();
                }else if($(element[0]).hasClass('add-locations') || $(element[0]).parentsUntil('ul').hasClass('add-locations')){
                  $('.bulk_add_locations').click();
                }else if($(element[0]).hasClass('manage-publications') || $(element[0]).parentsUntil('ul').hasClass('manage-publications')){
                  $('.bulk_publications').click();
                }else if($(element[0]).hasClass('manage-mail-sharing') || $(element[0]).parentsUntil('ul').hasClass('manage-mail-sharing')) {
                  $('.bulk_mail_sharing').click();
                }else if($(element[0]).hasClass('bulk-archive') || $(element[0]).parentsUntil('ul').hasClass('bulk-archive')){
                  $('.bulk_archive').click();
                }else{  
                  $('.bulk_add_to_cart').click();
                }
              });
        },
        downloadSelectedCart: function(){
            var tbody = $('tbody');
            tbody.each(function() {
                var span = this.getElementsByTagName('span');
                if ($(span).hasClass('flag-wrapper flag-cart') === true) {
                    tbody = this;
                    return tbody;
                }
            });
            var els = tbody.children;
            
            $.each(els, function(k, elem){
                var fileName = elem.getElementsByTagName("a")[0].innerText;
                var path = encodeURI(elem.getElementsByClassName('views-field views-field-field-emplacement')[0].innerText);

                // Prevent multifilled documents
                var split = path.split(',');
                var path = split[0];

                path = path.replace("/Sites/", "/alfresco/webdav/Sites/");
                var fileNamePath = "/" + fileName;
                path = path.padEnd(path.length + fileNamePath.length, fileNamePath);
                Gofast.ITHit.queue.push({
                uuid: Gofast.ITHit.generate_uuid(),
                path : path,
                displayNamePath: fileName + ' (' + decodeURIComponent(path).replace('/alfresco/webdav/Sites/', '') + ')',
                fileName: fileName,
                operation: 'download',
                displayOperation: Drupal.t('Download', {}, {context: 'gofast:cart'}),
                progression: 0,
                status: 0
              });
            });
        },
        remove: function(){
            $("#remove_all_documents").hide();
          $("#remove_from_cart").after("<button disabled='true' id='validate_remove' class='btn btn-default btn-sm' style='float: right;right: 0;margin-bottom: 10px;margin-right: 60px;'><i style='color:#5CB85C' class='fa fa-check-circle'></i>  "+Drupal.t('Yes')+"  </button>");
          $("#remove_from_cart").after("<button disabled='true' id='undo_remove' class='btn btn-default btn-sm' style='float: right;right: 0;margin-bottom: 10px;'><i style='color:#D9534F' class='fa fa-undo'></i>  " + Drupal.t('No') +"  </button>");
            setTimeout(function() {
                $('#validate_remove').prop('disabled', false);
                $('#undo_remove').prop('disabled', false);
            }, 1000);
            $('#undo_remove').click(function(){
                $("#validate_remove").remove();
                $("#undo_remove").remove();
                $("#remove_all_documents").show();
            });
            $('#validate_remove').click(function(){
                Gofast.closeModal();
                Gofast.addLoading();
                $.get(location.origin + "/gofast_cart_remove_all", function(){
                    Gofast.toast(Drupal.t("Removed from your cart", {}, {context: "gofast:gofast_cart"}), "success");
                    Gofast.removeLoading();
                });
            });
        }
    };
})(jQuery, Gofast, Drupal);