(function ($, Gofast, Drupal) {
  'use strict';
  Gofast.initializeAnnotator = function() {
    setTimeout(function() { 
      var user = '<div id="current_user" data-key="' + encodeURIComponent(JSON.stringify(Gofast.get("user"))) + '"></div>';
      var nid = '<div id="nid" data-key="' + Gofast.get("node").id + '"></div>';   
      if($("#pdf_frame").contents().find("body").find("#current_user").length === 0){
        $("#pdf_frame").contents().find("body").append(user).append(nid);
      }else{
        $("#pdf_frame").contents().find("body").find("#nid").attr("data-key",Gofast.get("node").id);
        $("#pdf_frame").contents().find("body").find("#current_user").attr("data-key",encodeURIComponent(JSON.stringify(Gofast.get("user"))));
      }
    }, 2000);
   }
  Drupal.behaviors.initializeAnnotator = {
    attach: function(context, setting) {
      Gofast.initializeAnnotator();
    }
  };
})(jQuery, Gofast, Drupal);