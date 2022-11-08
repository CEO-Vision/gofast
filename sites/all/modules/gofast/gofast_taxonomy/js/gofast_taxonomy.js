(function ($, Gofast, Drupal) {
  'use strict';
  Gofast.taxonomy_add_locations_process = function(){
    var panels = $(".add-locations-panel");
    var panelsNumber = panels.length;
    var barWidth = $('#modal-content .progress').width(); 
    var progressBarPart = barWidth / panelsNumber;
    var timeout = 0;
    
    //For each panel, process the request and check the result
    $.each(panels, function(i, panel){
      setTimeout(function(){
        //Retrieve nid  
        var nid = $(panel).find('#nid').text();
        if(nid > 0){}else{
          $(panel).find('.panel-body').find(".add-locations-info").html("<i class='fa fa-times' style='color:red' aria-hidden='true'></i> " + Drupal.t("This file can't be multifilled currently. Please try again later.", {}, {context: 'gofast:taxonomy'}));
          return true;
        }
        //Retrieve locations
        var locations = $(panel).find('#locations').text();
        $(panel).find('.panel-body').find(".add-locations-info").html("<i class='fa fa-arrow-right' style='color:#3498db' aria-hidden='true'></i> " + Drupal.t("Processing...", {}, {context: 'gofast:taxonomy'}));
        
        //retrieve if one of the location is a broadcast location, so we must exect request as admin on the server side
        var is_broadcast = $(panel).find('#is_broadcast').text();
        
        //Process the request
        $.post(location.origin + "/taxonomy/add_locations/process", {process_nid : nid, process_locations : locations, broadcast : is_broadcast}).done(function(data){
          var locations_output = JSON.parse(data);
          var success = true;
          
          //Fetch into the locations array
          locations_output.forEach(function(location){
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
          if(success){
            $(panel).find('.panel-body').find(".add-locations-info").html("<i class='fa fa-check' style='color:green' aria-hidden='true'></i> " + Drupal.t("Processed !", {}, {context: 'gofast:taxonomy'}));
          }else{
            $(panel).find('.panel-body').find(".add-locations-info").html("<i class='fa fa-times' style='color:red' aria-hidden='true'></i> " + Drupal.t("Processed but you might not have some necessary rights.", {}, {context: 'gofast:taxonomy'}));
          }
          var barProgressValue = ($('#modal-content .progress-bar').width()-1) / barWidth * 100;
          var progressBarPartValue = progressBarPart / barWidth * 100;
          var progressValue = barProgressValue + progressBarPartValue ; 
          $('#modal-content .progress-bar').width(progressValue / 100 * barWidth) ; 
          $('#modal-content .progress-bar').html(Math.floor(progressValue) + "%");
          if(Math.floor(progressValue) -1 >= 100 || ($('.add-locations-info .fa-arrow-right').length == '0' && $('.add-locations-info .fa-clock-o').length == '0')){
              $('#modal-content .progress-bar').width('100%');
              $('.progress-bar').removeClass('progress-bar-striped');
              $('.progress-bar').addClass('progress-bar-success');
              $('.progress-bar').html(Drupal.t('Completed',{},{'context' : "gofast:gofast_taxonomy"}));
          }
        });
      }, timeout);
      timeout = timeout+2000;
    });
  };
  
  
  Gofast.taxonomy_manage_locations_process = function(){
    var panels = $(".manage-locations-panel");
    var panelsNumber = panels.length;
    var barWidth = $('#modal-content .progress').width(); 
    var progressBarPart = barWidth / panelsNumber;
    var timeout = 0;
    
    //For each panel, process the request and check the result
    $.each(panels, function(i, panel){
      setTimeout(function(){
        //Retrieve nid
        var nid = $(panel).find('#nid').text();
        if(nid > 0){}else{
          $(panel).find('.panel-body').find(".manage-locations-info").html("<i class='fa fa-times' style='color:red' aria-hidden='true'></i> " + Drupal.t("This file can't be multifilled currently. Please try again later.", {}, {context: 'gofast:taxonomy'}));
          return true;
        }
        //Retrieve locations
        var locations = $(panel).find('#locations').text();
        var locations_gids = $(panel).find('#locations-gids').text();
        $(panel).find('.panel-body').find(".manage-locations-info").html("<i class='fa fa-arrow-right' style='color:#3498db' aria-hidden='true'></i> " + Drupal.t("Processing...", {}, {context: 'gofast:taxonomy'}));
        
        //retrieve if one of the location is a broadcast location, so we must exect request as admin on the server side
        var is_broadcast = $(panel).find('#is_broadcast').text();
        
        //Process the request
        $.post(location.origin + "/taxonomy/manage_locations/process", {
          process_nid : nid,
          process_locations : locations,
          process_locations_gids: locations_gids,
          broadcast : is_broadcast})
        .done(function(data){
          var locations_output = JSON.parse(data);
          var success = true;
          
          //Fetch into the locations array
          locations_output.forEach(function(location){
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
          if(success){
            $(panel).find('.panel-body').find(".manage-locations-info").html("<i class='fa fa-check' style='color:green' aria-hidden='true'></i> " + Drupal.t("Processed !", {}, {context: 'gofast:taxonomy'}));
          }else{
            $(panel).find('.panel-body').find(".manage-locations-info").html("<i class='fa fa-times' style='color:red' aria-hidden='true'></i> " + Drupal.t("Processed but you might not have some necessary rights.", {}, {context: 'gofast:taxonomy'}));
          }
          var barProgressValue = ($('#modal-content .progress-bar').width()-1) / barWidth * 100;
          var progressBarPartValue = progressBarPart / barWidth * 100;
          var progressValue = barProgressValue + progressBarPartValue ; 
          $('#modal-content .progress-bar').width(progressValue / 100 * barWidth) ; 
          $('#modal-content .progress-bar').html(Math.floor(progressValue) + "%");
          if(Math.floor(progressValue) -1 >= 100 || ($('.add-locations-info .fa-arrow-right').length == '0' && $('.add-locations-info .fa-clock-o').length == '0')){
              $('#modal-content .progress-bar').width('100%');
              $('.progress-bar').removeClass('progress-bar-striped');
              $('.progress-bar').addClass('progress-bar-success');
              $('.progress-bar').html(Drupal.t('Completed',{},{'context' : "gofast:gofast_taxonomy"}));
          }
        });
      }, timeout);
      timeout = timeout+2000;
    });
  };

  Gofast.taxonomy_manage_folders_locations_process = function(){
    debugger;
    var panels = $(".manage-folders-locations-panel");
    var timeout = 0;

    //For each panel, process the request and check the result
    $.each(panels, function (i, panel) {
      setTimeout(function () {
        //Retrieve nid
        $(panel).find('.panel-body').find(".manage-folders-locations-info").html("<i class='fa fa-times' style='color:red' aria-hidden='true'></i> " + Drupal.t("This file can't be multifilled currently. Please try again later.", {}, { context: 'gofast:taxonomy' }));
        //Retrieve folder
        var folder = $(panel).find('#folder').text();
        if (folder.length > 0) { } else {
          $(panel).find('.panel-body').find(".manage-folders-locations-info").html("<i class='fa fa-times' style='color:red' aria-hidden='true'></i> " + Drupal.t("This folder can't be multifilled currently. Please try again later.", {}, { context: 'gofast:taxonomy' }));
          return true;
        }
        //Retrieve locations
        var locations = $(panel).find('#locations').text();
        $(panel).find('.panel-body').find(".manage-folders-locations-info").html("<i class='fa fa-arrow-right' style='color:#3498db' aria-hidden='true'></i> " + Drupal.t("Processing...", {}, { context: 'gofast:taxonomy' }));

        //retrieve if one of the location is a broadcast location, so we must exect request as admin on the server side
        var is_broadcast = $(panel).find('#is_broadcast').text();

        //Process the request
        $.post(location.origin + "/taxonomy/manage_folders_locations/process", {process_folder: folder, process_locations: locations, broadcast: is_broadcast }).done(function (data) {
          var locations_output = JSON.parse(data);
          var success = true;

          //Fetch into the locations array
          locations_output.forEach(function (location) {
            var found = false;
            //Fetch into all supposed locations
            $.each($(panel).find('.panel-body').find('ul').find('li'), function (i, slocation) {
              if ($(slocation).text().trim() == location) {
                $(slocation).html($(slocation).text() + " <i class='fa fa-check' style='color:green' aria-hidden='true'></i>");
                found = true;
                return true;
              }
            });
            if (!found) {
              //Not found in the original expected locations
              $(panel).find('.panel-body').find('ul').append("<li>" + location + " <i class='fa fa-plus' style='color:red' aria-hidden='true'></i></li>");
              success = false;
            }
          });
          //Check if all locations was applied
          $.each($(panel).find('.panel-body').find('ul').find('li'), function (i, plocation) {
            if ($(plocation).html().indexOf("fa-plus") != -1) {
              success = false;
            } else if ($(plocation).html().indexOf("fa-check") == -1) {
              $(plocation).html($(plocation).text() + " <i class='fa fa-times' style='color:red' aria-hidden='true'></i>");
              success = false;
            }
          });
          if (success) {
            
            // Mirorring is finished
            $(panel).find('.panel-body').find(".manage-folders-locations-info").html("<i class='fa fa-check' style='color:green' aria-hidden='true'></i> " + Drupal.t("Processed !", {}, { context: 'gofast:taxonomy' }));
            
            // Synchronize permission
            $(panel).find('.panel-body').find(".manage-folders-locations-info").after("<div id='permission-synchro-docs' class='mt-20'> " + Drupal.t("Directory document permissions are being recalculated") + "<i class='spinner spinner-track spinner-primary spinner-sm ml-5'></i></div>");
            
            // Ajax request to synchronize the permissions of all documents inside folder mirroring
            $.ajax({
              url: location.origin + "/taxonomy/manage_folders_locations/sync_permissions",
              type: "POST",
              data: {
                folder: folder,
              },
              success: function (data) {
              
                // Replace spinner by check icon
                $('#permission-synchro-docs').find('.spinner').replaceWith("<i class='fa fa-check ml-5' style='color:green' aria-hidden='true'></i>");
                
              }
            });

          } else {
            $(panel).find('.panel-body').find(".manage-folders-locations-info").html("<i class='fa fa-times' style='color:red' aria-hidden='true'></i> " + Drupal.t("Processed but you might not have some necessary rights.", {}, { context: 'gofast:taxonomy' }));
          }
        });
      }, timeout);
      timeout = timeout + 2000;
    });
  };


  Gofast.taxonomy_manage_taxonomy_process = function(){
    var panels = $(".manage-locations-panel");
    var panelsProgressBar = $("#locations-panels-progress .progress-bar");
    var numberOfPanels = panels.length;
    var processedPanels = 0;
    var timeout = 0;
    
    //For each panel, process the request and check the result
    $.each(panels, function(i, panel){
      setTimeout(function(){
        //Retrieve nid
        var nid = $(panel).find('#nid').text();
        if(nid > 0){}else{
          $(panel).find('.panel-body').find(".manage-locations-info").html("<i class='fa fa-times' style='color:red' aria-hidden='true'></i> " + Drupal.t("This modification cannot be done currently. Please try again later.", {}, {context: 'gofast:taxonomy'}));
          return true;
        }
        //Retrieve vid
        var vid = $(panel).find('#vid').text();
        //Retrieve field
        var field = $(panel).find('#field').text();
        //Retrieve value
        var value = $(panel).find('#value').text();
        $(panel).find('.panel-body').find(".manage-locations-info").html("<i class='fa fa-arrow-right' style='color:#3498db' aria-hidden='true'></i> " + Drupal.t("Processing...", {}, {context: 'gofast:taxonomy'}));
        
        //Process the request
        $.post(location.origin + "/taxonomy/manage_taxonomy/process", {process_nid : nid, process_vid : vid, process_field : field, process_value : value}).done(function(data) {
          if (field == "field_date") data = window.GofastFormatAsDrupalDate(data, Drupal.settings.date_format_short, false);
          // update progress bar
          processedPanels++;
          const progressWidth = Math.round((100 / numberOfPanels) * processedPanels);
          panelsProgressBar.css({width: progressWidth + "%"});
          panelsProgressBar.attr("aria-valuenow", progressWidth);
          // panelsProgressBar.html(processedPanels + " / " + numberOfPanels);
          panelsProgressBar.html(progressWidth + "%");
          
          if(data.indexOf("[") !== -1){
            var tags = [];
            JSON.parse(data).forEach(function(v){tags.push(v.tid)});
            var avalue = value.split(',');
            
            //Check if value matches the returned data
            if(Drupal.arr_diff(tags, avalue).length == 0){
              $(panel).find('.panel-body').find(".manage-locations-info").html("<i class='fa fa-check' style='color:green' aria-hidden='true'></i> " + Drupal.t("Processed !", {}, {context: 'gofast:taxonomy'}));
            }else{
              $(panel).find('.panel-body').find(".manage-locations-info").html("<i class='fa fa-times' style='color:red' aria-hidden='true'></i> " + Drupal.t("Error, you might not have some necessary rights.", {}, {context: 'gofast:taxonomy'}));
            }
          }else{
            //Check if value matches the returned data
            if(value == data || value.split(" - ")[0] == data.split(" - ")[0]){
              $(panel).find('.panel-body').find(".manage-locations-info").html("<i class='fa fa-check' style='color:green' aria-hidden='true'></i> " + Drupal.t("Processed !", {}, {context: 'gofast:taxonomy'}));
            }else{
              $(panel).find('.panel-body').find(".manage-locations-info").html("<i class='fa fa-times' style='color:red' aria-hidden='true'></i> " + Drupal.t("Error, you might not have some necessary rights.", {}, {context: 'gofast:taxonomy'}));
            }
          }
        });
      }, timeout);
      timeout = timeout+1000;
    });
  };
  
Drupal.arr_diff = function(a1, a2){

    // Merge the arrays
    var mergedArr = a1.concat(a2);

    // Get the elements which are unique in the array
    // Return the diff array
    return mergedArr.filter(function (e) {
        // Check if the element is appearing only once
        return mergedArr.indexOf(e) === mergedArr.lastIndexOf(e);
    });

}
})(jQuery, Gofast, Drupal);
