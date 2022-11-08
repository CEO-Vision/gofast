(function ($, Gofast, Drupal) {
  Drupal.gofast_cmis = Drupal.gofast_cmis || {};

  Drupal.gofast_cmis.reloadPreview = function(force_pdfjs = false) {
    $('#refresh-preview').addClass('disabled');
    if(jQuery('iframe[name="frameEditor"]').length > 0){
        Gofast.docEditor.destroyEditor();
        Gofast.process_onlyoffice_editor();
    }else{
      $("#container_preview_element").html("");
      $.get("/gofast/get_preview_element/" + Gofast.get('node').id + "?force_pdfjs=" + force_pdfjs, function(data){
        $("#container_preview_element").html(data);
        
        //Trigger annotator
        Drupal.gofast_cmis.triggerAnnotator();
      })
    }
     Gofast.Poll.run();
  };
  
  Drupal.gofast_cmis.triggerAnnotator = function() {
   //Trigger annotator
   if($("#pdf_frame").length){
     var wait_pdf = setInterval(function(){
       if($("#pdf_frame").contents().find("#viewer").find("div").length){
         clearInterval(wait_pdf);
         $("#pdf_frame")[0].contentWindow.dispatchEvent(new Event('resize'));
         
         //Load annotations again on scrolling
         $("#pdf_frame").contents().find("#viewerContainer").not("scroll-processed").on( "scroll", function(){
           clearTimeout(Gofast.wait_scroll_pdf);
           
           if(!$("#pdf_frame").contents().find("#loading-annotations").length){
            $("#pdf_frame").contents().find("#toolbarViewerRight").prepend('<div id="loading-annotations" style="margin-top: 7px;">' + Drupal.t('Loading annotations...') + '</div>');
           }
           
           Gofast.wait_scroll_pdf = setTimeout(function(){
             if($("#pdf_frame").contents().find(".annotator-editor").hasClass('annotator-hide')){
               //Check if no annotations are in progress
               $("#pdf_frame")[0].contentWindow.dispatchEvent(new Event('resize'));
               $("#pdf_frame").contents().find("#loading-annotations").remove();
             }
           }, 1100);
         }).addClass("scroll-processed");
       }
     }, 200);
   }
}

})(jQuery, Gofast, Drupal);
