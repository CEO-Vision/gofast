(function ($, Gofast, Drupal) {
  Gofast.gofast_workflow_stats = {
    /*
     * Launch statistics generation process
    */
    generate: function(){
      if($("#workflowsStatsContainer").hasClass("loading")){
        return;
      }
      $("#workflowsStatsContainer").addClass("loading");
      
      // Get processus type
      var title = $('#select2-edit-type-container').attr('title');
      var type = $('.form-item-type').find("select#edit-type").val();
      $('#workflowsStatsContainer').empty();
      $('#workflowsStatsHeader').removeClass("d-none").css("display", "flex");
      $('#workflowsStatsType').html(title);
      if(type == "all"){
        $('#workflowsStatsContainer').removeClass("d-flex").removeClass("flex-wrap");
        $('#workflowsStatsContainer').append('<div class="text-center pt-15 mt-15 pb-15 mb-15"><p>' + Drupal.t('Select a "Process Type" from the filters and click "Search"') + '</p></div>');
        $("#workflowsStatsContainer").removeClass("loading");
        return;
      }else{
        $("#workflowsStatsContainer").addClass("d-flex").addClass("flex-wrap").addClass("justify-content-center");
        $("#workflowsStatsContainer").append('<div class="spinner spinner-track spinner-primary m-auto"></div>');
      }
      
      $.get('/gofast_workflow_dashboard_stats/' + type, function(fid){
        var checkInterval = setInterval(function(){
          $.get(location.origin + "/gofast_workflow_dashboard_stats_display_check?fid=" + fid, function(data){
            if(data !== "Waiting"){
              // Prevent having statistics duplicated
              if(!$("#workflowsStatsContainer").hasClass("loading")){
                return
              }
              $("#workflowsStatsContainer").removeClass("loading");
              clearInterval(checkInterval);
              data = JSON.parse(data);
              if(data.length == 0){
                $("#workflowsStatsContainer .spinner").remove();
                $('#workflowsStatsContainer').removeClass("d-flex").removeClass("flex-wrap");
                $('#workflowsStatsContainer').append('<div class="text-center pt-15 mt-15 pb-15 mb-15"><p>' + Drupal.t('This type of process does not generate data graphs.', {}, {context: "gofast:gofast_workflows_stats"}) + '</p></div>');
                return;
              }
              var i = 0;
              let htmlType = $('#select2-edit-type-container').attr('title');
              for(var field in data){
                var series_label = data[field];
                var graph_type = data[field].graph_type;
                  var format_type = data[field].format_type;
                  var series = [];
                  var label = [];
                  
                  // Delete useless values
                  delete series_label.label;
                  delete series_label.graph_type;
                  if(series_label.format_type != undefined){
                    delete series_label.format_type;
                  }
                  
                  for(var sl in series_label){
                    label.push(sl);
                    series.push(series_label[sl]);
                  }
                  
                  var type = graph_type ? graph_type : 'pie';
                  if(type == "text"){
                    continue;
                  }
                  var options = Gofast.gofast_workflow_stats.getChartOptions(type, format_type, series, label);
                  $("#workflowsStatsContainer .spinner").remove();
                  $('#workflowsStatsContainer').append('<div class="col-12 col-md-6 col-xl-4"><div class="card-label">' + field + '</div><div id="chart' + i + '"></div></div>')
                  var chart = new ApexCharts(document.querySelector("#chart" + i), options);
                  chart.render();
                  
                  i++;
              }
            } 
         });
        }, 1500);
      });
    },
    
    getChartOptions: function(type, format_type, series, label){
      switch (type) {
        case "pie":
          var options = {
            width: 380,
            responsive: [{
              breakpoint: 480,
              options: {
                chart: {
                  width: 200
                },
                legend: {
                  position: 'bottom'
                }
              }
            }],
            series: series,
            labels : label,
            chart: {
              type: type
            },
          }
          break;
        case "bar":
          
        // Format series data options for bar chart
          var categories = "";
          var cur_series = [];
          if (format_type == "multiple") {
            for (let index in label) {
              var name = label[index];
              var cur_values = [];
              for (let series_value in series[index]) {
                cur_values.push(series[index][series_value]);
              }
              cur_series.push({ name: name, data: cur_values });
            }
            categories = Object.keys(series[0]);
          } else {
            cur_series.push({ data: series });
            categories = label;
          }
          
          options = {
            height: 380,
            chart: {
              type: type
            },
            plotOptions: {
              bar: {
                horizontal: false
              }
            },
            series: cur_series,
            xaxis: {
              categories: categories
            }
          }
          break;
        default:
      }

      return options;
    },
    
    downloadDatas: function(){
      var type = $('.form-item-type').find("select#edit-type").val();
      Gofast.modal('<div class="loader-sync-status"></div> ' + Drupal.t("Please hold on while your export is being generating. This process may take a few minutes.", {}, {context : "gofast_stats"}), Drupal.t("Your export is being generating", {}, {context : "gofast_stats"}));
      //Check filters
      
      if(typeof e === "object"){
          e.preventDefault();
      }
      $.get('/gofast_workflow_dashboard_stats/download/' + type, function(fid){
        var downloadInterval = setInterval(function(){
          $.get(location.origin + "/gofast_workflow_dashboard_stats_check?fid=" + fid, function(file){
             if(file !== "Waiting"){
                 clearInterval(downloadInterval);
                 Gofast.closeModal();
                 window.location = location.origin + "/gofast_workflow_dashboard_stats_check?fid=" + fid;
             } 
          });
      }, 1000); 
      });
    },
  }
  
})(jQuery, Gofast, Drupal);
