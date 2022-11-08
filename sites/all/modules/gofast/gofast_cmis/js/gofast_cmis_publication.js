(function ($, Gofast, Drupal) {
  'use strict';
  Gofast.manage_publication_process = function(){
    var panels = $(".manage-publications-panel");
    var panelsProgressBar = $("#publications-panels-progress .progress-bar");
    var numberOfPanels = panels.length;
    var processedPanels = 0;
    var timeout = 0;
    
    //For each panel, process the request and check the result
    $.each(panels, function(i, panel){
      setTimeout(function(){
        //Retrieve nid
        var nid = $(panel).find('#nid').text();
        if(nid > 0){}else{
          $(panel).find('.panel-body').find(".manage-publications-info").html("<i class='fa fa-times' style='color:red' aria-hidden='true'></i> " + Drupal.t("This file can't be multifilled currently. Please try again later.", {}, {context: 'gofast:taxonomy'}));
          return true;
        }
        //Retrieve publications
        var locations = $(panel).find('#locations').text();
        $(panel).find('.panel-body').find(".manage-publications-info").html("<i class='fa fa-arrow-right' style='color:#3498db' aria-hidden='true'></i> " + Drupal.t("Processing...", {}, {context: 'gofast:taxonomy'}));
       
        //Retrieve transformation
        var transformation = $(panel).find('#transformation').text();
        
        //Retrieve title 
        var title = $(panel).find('#title').text();
        var locations_nid = $(panel).find('#locations_nid').text();
        var broadcast = $(panel).find('#is_broadcast').text();
        
        //Process the request
        $.post(location.origin + "/cmis/manage_publications/process", {process_nid : nid, process_locations : locations, process_transformation : transformation , process_title : title, process_locations_nid : locations_nid, is_broadcast : broadcast}).done(function(data){
          if(data.length != 0){
              if(data != 'is_publication'){
                  var publications_output = JSON.parse(data);
              }else{
                  var publications_output = data;
              }
              var type = publications_output;
              if(type != 'is_publication'){
                  var success = true;

                  //Fetch into the locations array
                  publications_output.forEach(function(location){
                    var found = false;
                    //Fetch into all supposed locations
                    $.each($(panel).find('.panel-body').find('ul').find('li'), function(i, slocation){
                      if($(slocation).text().trim() == location){
                        $(slocation).html($(slocation).text() + " <i class='fa fa-check' style='color:green' aria-hidden='true'></i>");
                        found = true;
                        return true;
                      }
                    });
                    if(!found){
                      //Not found in the original expected locations
                      $(panel).find('.panel-body').find('ul').append("<li>" + location + " <i class='fa fa-plus' style='color:red' aria-hidden='true'></i></li>");
                      success = false;
                    }
                  });
                  //Check if all locations was applied
                  $.each($(panel).find('.panel-body').find('ul').find('li'), function(i, plocation){
                    if($(plocation).html().indexOf("fa-plus") != -1){
                      success = false;
                    }else if($(plocation).html().indexOf("fa-check") == -1){
                      $(plocation).html($(plocation).text() + " <i class='fa fa-times' style='color:red' aria-hidden='true'></i>");
                      success = false;
                    }
                  });
            }else{
              $.each($(panel).find('.panel-body').find('ul').find('li'), function(i, slocation){
                  $(slocation).html($(slocation).text() + " <i class='fa fa-plus' style='color:red' aria-hidden='true'></i>");
              });
              var success = false;
            }
          }else{
              $.each($(panel).find('.panel-body').find('ul').find('li'), function(i, slocation){
                  $(slocation).html($(slocation).text() + " <i class='fa fa-plus' style='color:red' aria-hidden='true'></i>");
              });
              var success = false;
          }
          if (success) {
            // update progress bar
            processedPanels++;
            const progressWidth = Math.round((100 / numberOfPanels) * processedPanels);
            panelsProgressBar.css({width: progressWidth + "%"});
            panelsProgressBar.attr("aria-valuenow", progressWidth);
            // panelsProgressBar.html(processedPanels + " / " + numberOfPanels);
            panelsProgressBar.html(progressWidth + "%");
          }
          if(success && type == 'no_pdf'){
            $(panel).find('.panel-body').find(".manage-publications-info").html("<i class='fa fa-warning' style='color:#ffc107' aria-hidden='true'></i> " + Drupal.t("The pdf preview of the original document doesn't exist", {}, {context: 'gofast:taxonomy'}));             
          }else if (success){    
            $(panel).find('.panel-body').find(".manage-publications-info").html("<i class='fa fa-check' style='color:green' aria-hidden='true'></i> " + Drupal.t("Processed !", {}, {context: 'gofast:taxonomy'}));
          }else if(type == 'is_publication'){
            $(panel).find('.panel-body').find(".manage-publications-info").html("<i class='fa fa-times' style='color:red' aria-hidden='true'></i> " + Drupal.t("This document is already a publication!", {}, {context: 'gofast:taxonomy'}));             
          }else{
            $(panel).find('.panel-body').find(".manage-publications-info").html("<i class='fa fa-times' style='color:red' aria-hidden='true'></i> " + Drupal.t("Processed but you might not have some necessary rights.", {}, {context: 'gofast:taxonomy'}));
          }
        });
      }, timeout);
      timeout = timeout+2000;
    });
  };
})(jQuery, Gofast, Drupal);