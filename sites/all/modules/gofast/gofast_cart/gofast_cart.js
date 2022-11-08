(function ($, Gofast, Drupal) {
    
    Drupal.behaviors.remove_item_from_cart = {
      attach : function (context, settings) { 
        $('.GofastCart__tBody tr').each(function(){
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
        if (!$('.GofastCart__tBody').children().length){
            $("#cart_toolbar_manage button").attr('disabled',true);
            $("#cart_toolbar_process").attr('disabled',true);
            $("#remove_all_documents").attr('disabled',true);
            $("#remove_all_documents").removeAttr("onclick");
            $('.GofastCart__emptyPlaceholder').html(
                    '<div class="align-content-center d-flex justify-content-center p-5 pt-10"><span class="font-size-h3 font-weight-bolder text-muted text-uppercase" style="letter-spacing: 0.05rem;">'
                    + Drupal.t("You have no content into your cart", {}, {context: "gofast:cart"})
                    + '</span></div>'
                );
        }
      }
    }; 
    
    Drupal.behaviors.applyPopoverOnCart = {
        attach: function (context, settings) {
            if ($(".gofast__popover").length) {
                $('.gofast__popover').popover();
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
            var tbody = $('.GofastCart__tBody');

            var els = tbody.children();
            $.each(els, function(k, elem){
                var fileName = elem.getElementsByClassName("GofastCart__rowTitle")[0].innerText.trim();           
                var path = $(elem).find(".GofastCart__rowLocation .breadcrumb-gofast .breadcrumb").attr("fullpath");
                
                // Prevent multifilled documents
                var split = path.split("%0A");
                var path = split[0];

                path = "/alfresco/webdav/Sites/"+path;          
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
          $("#remove_all_documents").toggleClass("d-flex");
          $("#remove_from_cart").after("<button disabled='true' id='undo_remove' class='btn btn-default btn-sm d-flex'><i class='fa fa-undo text-danger'></i>  " + Drupal.t('No') +"  </button>");
          $("#remove_from_cart").after("<button disabled='true' id='validate_remove' class='btn btn-default btn-sm d-flex'><i class='fa fa-check-circle text-success'></i>  "+Drupal.t('Yes')+"  </button>");
            setTimeout(function() {
                $('#validate_remove').prop('disabled', false);
                $('#undo_remove').prop('disabled', false);
            }, 1000);
            $('#undo_remove').click(function(){
                $("#validate_remove").remove();
                $("#undo_remove").remove();
                $("#remove_all_documents").toggleClass("d-flex");
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