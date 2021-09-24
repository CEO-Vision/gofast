(function ($, Gofast, Drupal) {
  'use strict';
    /*
     * 
     * Function that allows to asynchronously send an email to each recipient with each document
     */
    Gofast.manage_linksharing_process = function(){
        var panels = $(".manage-linksharing-panel");
        var timeout = 0;

        /* for each panel, process the request and check the result */
        $.each(panels, function(i, panel){
          setTimeout(function(){

            /* Retrieve uid */ 
            var uid = $(panel).find('#uid').text();

            /* Retrieve nids */ 
            var nids = $(panel).find('#nids').text();

            /* Retrieve title */
            var subject = $(panel).find('#subject').text();

            /* Retrieve message */
            var message = $(panel).find('#message').text();

            /* Process the request */ 
            $.post(location.origin + "/linksharing/manage_linksharing/process", {process_uid : uid, process_nids : nids,process_subject:subject,process_message:message}).done(function(data){       
            $(panel).find('.panel-body').find(".manage-linksharing-info").html("<i class='fa fa-check' style='color:green' aria-hidden='true'></i> " + Drupal.t("Processed !", {}, {context: 'gofast:taxonomy'}));
            });
          }, timeout);
          timeout = timeout+2000;
        });
    };


    $(document).ready(function() {
      $('#gofast-multi-link-sharing-form div button').removeClass('btn-default');
      $('#gofast-multi-link-sharing-form div button').removeClass('btn-sm');
      $('.gofast_search_link').click(function () {
        window.location.href = "/public/sharing_dl?hash="+$( "#hash_link" ).html();
        /*$.ajax({
            url: "/public/sharing_dl",
            method : "GET",
            data: { hash: $( "#hash_link" ).html()},
            async:false,
           beforeSend: function() {
           Gofast.addLoading();
  }
        }).done(function(data ) {
            Gofast.removeLoading();           
        });*/
      });   
      $('#edit-check-all').not(".processed").click(function(e){
        e.preventDefault();
        if($('#edit-check-all').attr("data-state")=="active"){
            $('#edit-links>div input').each(function(){
                $(this).prop('checked',true);
            });
            $('#edit-check-all').html("<i class='fa fa-times'></i>" + Drupal.t(' Uncheck all documents'));
            $('#edit-check-all').attr("data-state","inactive");
        }else if ($('#edit-check-all').attr("data-state")=="inactive"){
            $('#edit-links>div input').each(function(){
                $(this).prop('checked',false);
            });
            $('#edit-check-all').html("<i class='fa fa-check'></i>" + Drupal.t (' Check all documents'));
            $('#edit-check-all').attr("data-state","active");
          }
        }).addClass("processed");
        
        $('#gofast-multi-link-sharing-form > div > div > .form-submit').click(function(e){
            e.preventDefault();
            Gofast.addLoading();
            $('#gofast-multi-link-sharing-form').submit();
        })
    });
    
})(jQuery, Gofast, Drupal);     