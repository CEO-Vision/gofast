/**
 * @file
 *  Provides GoFast Essential front-end functionalities.
 *
 *  This file is part of the Gofast main library and is loaded on every page.
 *  Do not insert code that has to be run on specific page.
 */
(function ($, Gofast, Drupal) {
  Gofast.auditAction= {
    download:function(nid){
      if(nid.length > 0){
          $.post(location.origin + "/gofast/audit/download", {node_id : nid}).done(function(data) {	    });
      }
    },
    downloadSelected: function (files) { // downloadSelected for audit
      $.post(location.origin + "/gofast/audit/downloadSelected", { files: files }).done(function (data) {
      });
    },
  };

  /*
   * Handle the downloading of stats
   */
    Gofast.download_audit_export = function(){
      Gofast.modal('<div class="loader-sync-status"></div> ' + Drupal.t("Please hold on while your export is being generating. This process may take a few minutes.", {}, {context : "gofast_stats"}), Drupal.t("Your export is being generating", {}, {context : "gofast_stats"}));
      // Replicate last datatable query string to replicate current sorting and filtering to export
      const query_param = $("#audit_export_xls_button > a").attr("data-query");
      $.get(location.origin + "/gofast_audit_export_xlsx?"+query_param, function(response){
         var downloadInterval = setInterval(function(){
             $.get(location.origin + "/gofast_audit_export_xlsx/download/" + response, function(file){
                if(file !== "Waiting"){
                    clearInterval(downloadInterval);
                    Gofast.closeModal();
                    window.location = location.origin + "/gofast_audit_export_xlsx/download/" + response;
                } 
             });
         }, 1000); 
      });
  };
})(jQuery, Gofast, Drupal);

