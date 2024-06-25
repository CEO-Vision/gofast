(function ($, Gofast, Drupal) {
  Drupal.gofast_cmis = Drupal.gofast_cmis || {};

  Drupal.gofast_cmis.reloadPreview = function(force_pdfjs = false) {
    if((Gofast.isMobile() || Gofast.isTablet()) && $("#pdf_frame").length){
      $("#pdf_frame").addClass("mode-gf-full");
      return;
    }
    $('#refresh-preview').addClass('disabled');
    if($('iframe[name="frameEditor"]').length > 0){
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
         $("#pdf_frame").contents().find("#viewerContainer").not("scroll-processed").on("scroll", function(){
           clearTimeout(Gofast.wait_scroll_pdf);
           // we get the text color from context to avoid displaying black on black if the user is in dark mode
           let textColor = getComputedStyle($("#pdf_frame").contents()[0].documentElement).getPropertyValue("--main-color");
           if(!$("#pdf_frame").contents().find("#loading-annotations").length){
            $("#pdf_frame").contents().find("#toolbarViewerRight").prepend('<div id="loading-annotations" style="color: ' + textColor + '; margin-top: 7px;">' + Drupal.t('Loading annotations...') + '</div>');
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
