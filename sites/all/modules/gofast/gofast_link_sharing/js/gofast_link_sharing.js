(function ($, Gofast, Drupal) {
  'use strict';
    /*
     * 
     * Function that allows to asynchronously send an email to each recipient with each document
     */
    Gofast.manage_linksharing_process = function(){
        var panels = $(".manage-linksharing-panel");
        var panelsProgressBar = $("#link-panels-progress .progress-bar");
        var numberOfPanels = panels.length;
        var processedPanels = 0;
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
            $.post(location.origin + "/linksharing/manage_linksharing/process", {process_uid : uid, process_nids : nids,process_subject:subject,process_message:message}).done(function(data) {       
              // update progress bar
              processedPanels++;
              const progressWidth = Math.round((100 / numberOfPanels) * processedPanels);
              panelsProgressBar.css({width: progressWidth + "%"});
              panelsProgressBar.attr("aria-valuenow", progressWidth);
              // panelsProgressBar.html(processedPanels + " / " + numberOfPanels);
              panelsProgressBar.html(progressWidth + "%");
              
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
      });   
      $('#edit-check-all').on("change", function(e){
        e.preventDefault();
        if($(this).prop('checked') == true){
            $('.gofast_link_sharing_checkbox input').each(function(){
                $(this).prop('checked',true);
            });
        }else {
            $('.gofast_link_sharing_checkbox input').each(function(){
                $(this).prop('checked',false);
            });
          }
        }).addClass("processed");
    });
    
})(jQuery, Gofast, Drupal);     