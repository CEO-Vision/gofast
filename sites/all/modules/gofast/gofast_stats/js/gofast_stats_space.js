(function ($, Gofast, Drupal) {
  'use strict';
  $(document).ready(function(){
    var nid = $(".gofast-og-page").attr("id").replace("node-", "");
    //Trigger calls at the click event on the header
    $("#users_stats_header").click(function(){
      if($("#users_stats_header").hasClass("processed")){ //Already loaded
      }else{ //Need to be loaded
        $("#users_stats_header").addClass('processed');
        
        Drupal.attachBehaviors();
        Gofast.stats_filters = [];
        //Trigger event on users stats filters
        $("#users_stats_filter_apply").click(function(e){
          e.preventDefault();

          //Retrieve selected spaces
          var spaces = $("#users_stats_filter > form > div > div > div > .selection-tags > span").find('.labelize-metadata');
          var spaces_ids = [];

          $.each(spaces, function(k, tag){
            spaces_ids.push($(tag).data('id'));
          });
          Gofast.stats_filters = spaces_ids;
          load_users_chart(nid);
          load_state_doughnut(nid);
          load_active_doughnut(nid);
          
          if(spaces_ids.length === 0){
            $("#users_doughnut_role_container").show();
          }else{
            $("#users_doughnut_role_container").hide();
          }
        });
        
        /*
        * USERS CHART
        * Load the users chart and implements listeners
        */
       load_users_chart(nid);
       $("#user_charts_btn_group_1w").click(function(){Drupal.user_charts_period = "1week"; load_users_chart(nid);});
       $("#user_charts_btn_group_1m").click(function(){Drupal.user_charts_period = "1month"; load_users_chart(nid);});
       $("#user_charts_btn_group_1y").click(function(){Drupal.user_charts_period = "1year"; load_users_chart(nid);});
       $("#user_charts_btn_group_2y").click(function(){Drupal.user_charts_period = "2year"; load_users_chart(nid);});
       $("#user_charts_btn_group_3y").click(function(){Drupal.user_charts_period = "3year"; load_users_chart(nid);});

       /*
        * STATE DOUGHNUT
        * Get the users state doughnut (blocked or allowed)
        */
       load_state_doughnut(nid);

       /*
        * ACTIVE DOUGHNUT
        * Get the users active/inactive state
        */
       load_active_doughnut(nid);

       /*
        * ROLES BAR
        * Get the users roles bars
        */
       //Get the users state role
       $.post(location.origin + "/api", {ressource : "stats", action : "get_members_doughnut_roles", params : [nid]}).done(function(api_return){
         var data = api_return;

         var options = {
            chart: {
              type: 'bar',
              height: '450px',
              toolbar: {
                  show: false
              }
            },
            series: data.data.datasets,
            xaxis: {
              categories: data.data.labels
            },
          };

          var chart = new ApexCharts(document.querySelector('#users_doughnut_roles'), options);
          chart.render();
         $("#users_doughnut_role_loader").remove();
       });
     }
    });
    
    
    $("#documents_stats_header").click(function(){
      if($("#documents_stats_header").hasClass("processed")){ //Already loaded
      }else{ //Need to be loaded
        $("#documents_stats_header").addClass('processed');
        /*
        * USERS CHART
        * Load the users chart and implements listeners
        */
       load_documents_chart(nid);
       $("#document_charts_btn_group_1w").click(function(){Drupal.document_charts_period_space = '1week'; load_documents_chart(nid);});
       $("#document_charts_btn_group_1m").click(function(){Drupal.document_charts_period_space = '1month'; load_documents_chart(nid);});
       $("#document_charts_btn_group_1y").click(function(){Drupal.document_charts_period_space = '1year'; load_documents_chart(nid);});
       $("#document_charts_btn_group_2y").click(function(){Drupal.document_charts_period_space = '2year'; load_documents_chart(nid);});
       $("#document_charts_btn_group_3y").click(function(){Drupal.document_charts_period_space = '3year'; load_documents_chart(nid);});
       $("#document_charts_btn_group_periodic").click(function(){Drupal.document_charts_mode_space = 'periodic'; load_documents_chart(nid);});
       $("#document_charts_btn_group_evolution").click(function(){Drupal.document_charts_mode_space = 'evolution';load_documents_chart(nid);});
       
       load_document_radar("category", nid);
       $("#document_charts_btn_group_category").click(function(){load_document_radar("category", nid)});
       $("#document_charts_btn_group_state").click(function(){load_document_radar("state", nid)});
       $("#document_charts_btn_group_criticity").click(function(){load_document_radar("criticity", nid)});
      }
    });
    
    if(Gofast.stats_to_load == "user"){
        $("#users_stats_header").click();
    }else{
        $("#documents_stats_header").click();
    }
  });
  
      $("#spaces_stats_header").click(function(){
      if($("#spaces_stats_header").hasClass("processed")){ //Already loaded
        $(".stats_container").css('display', 'none');
        $("#stats-menu").find("li").removeClass("active");
        $("#spaces_stats_header").addClass("active");
        $("#spaces_stats_container").css('display', 'block');
      }else{ //Need to be loaded
        $("#spaces_stats_header").addClass('processed');
        $(".stats_container").css('display', 'none');
        $("#stats-menu").find("li").removeClass("active");
        $("#spaces_stats_header").addClass("active");
        $("#spaces_stats_container").css('display', 'block');
      }
    });
  
  /*
   * This function loads the users chart, according to the given period
   */
  function load_users_chart(nid){
    $("#user_charts_btn_group").css("display", "none");
    
    if(typeof(Drupal.user_charts_period) === "undefined"){
      Drupal.user_charts_period = "1month";
    }
    
    //Get the users chart
    $.post(location.origin + "/api", {ressource : "stats", action : "get_users_chart", params : [Drupal.user_charts_period, nid, Gofast.stats_filters]}).done(function(api_return){
      var data = api_return;
      var canvas = $("#users_chart");
      if(canvas){
        canvas.remove();
        $("#users_chart_container").append('<div id="users_chart"></div>');
      }else{
        $("#users_chart_container").append('<div id="users_chart"></div>');
      }
       
      var options = {
        chart: {
          type: 'bar',
          height: '400px',
          toolbar: {
              show: false
          }
        },
        series: data.data.datasets,
        xaxis: {
          categories: data.data.labels
        },
      };

      var chart = new ApexCharts(document.querySelector('#users_chart'), options);
      chart.render();
      $("#user_charts_btn_group").css("display", "block");
      $("#users_chart_loader").remove();
    });
  }
  
  function load_state_doughnut(nid){
    $.post(location.origin + "/api", {ressource : "stats", action : "get_users_doughnut_state", params : [nid, Gofast.stats_filters]}).done(function(api_return){
        var data = api_return;
        var canvas = $("#users_doughnut_state");
        if(canvas){
          canvas.remove();
          $("#users_doughnut_state_container").append('<div id="users_doughnut_state"></div>');
        }else{
          $("#users_doughnut_state_container").append('<div id="users_doughnut_state"></div>');
        }

        var options = {
            chart: {
              type: 'pie',
              height: '225px',
              toolbar: {
                show: false
              }
            },
            series: data.data.datasets.data,
            labels: data.data.labels,
        };
        
        var chart = new ApexCharts(document.querySelector('#users_doughnut_state'), options);
        chart.render();
        
      $("#users_doughnut_state_loader").remove();
    });
  }
  
  function load_active_doughnut(nid){
    $.post(location.origin + "/api", {ressource : "stats", action : "get_users_doughnut_active", params : [nid, Gofast.stats_filters]}).done(function(api_return){
         var data = api_return;
         var canvas = $("#users_doughnut_active");
          if(canvas){
            canvas.remove();
            $("#users_doughnut_active_container").append('<div id="users_doughnut_active"></div>');
          }else{
            $("#users_doughnut_active_container").append('<div id="users_doughnut_active"></div>');
          }
        
         var options = {
            chart: {
              type: 'pie',
              height: '225px',
              toolbar: {
                  show: false
              }
            },
            series: data.data.datasets.data,
            labels: data.data.labels,
          };

          var chart = new ApexCharts(document.querySelector('#users_doughnut_active'), options);
          chart.render();

         $("#users_doughnut_active_loader").remove();
       });
  }
  
  /*
   * This function loads the users chart, according to the given period
   */
  function load_documents_chart(nid){
    $("#document_charts_btn_group").css("display", "none");
    $("#document_charts_mode_btn_group").css("display", "none");
    
    if(typeof(Drupal.document_charts_period_space) === "undefined"){
      Drupal.document_charts_period_space = "1month";
    }
    if(typeof(Drupal.document_charts_mode_space) === "undefined"){
      Drupal.document_charts_mode_space = "evolution";
    }
    
    if(Drupal.document_charts_mode_space == "evolution"){
      var type = "area";
    }else{
      var type = "bar";
    }
    //Get the documents chart
    $.post(location.origin + "/api", {ressource : "stats", action : "get_documents_chart", params : [Drupal.document_charts_period_space, Drupal.document_charts_mode_space, nid]}).done(function(api_return){
      var data = api_return;
      var canvas = $("#documents_chart");
      if(canvas){
        canvas.remove();
        $("#documents_chart_container").append('<div id="documents_chart"></div>');
      }else{
        $("#documents_chart_container").append('<div id="documents_chart"></div>');
      }
       
      var options = {
        chart: {
          type: type,
          height: '400px',
          toolbar: {
              show: false
          }
        },
        series: data.data.datasets,
        xaxis: {
          categories: data.data.labels
        },
      };
      
      if(type == "area"){
          options.dataLabels = {enabled: false};
      }

      var chart = new ApexCharts(document.querySelector('#documents_chart'), options);
      chart.render();
      
      $("#document_charts_btn_group").css("display", "block");
      $("#document_charts_mode_btn_group").css("display", "block");
      $("#documents_chart_loader").remove();
    });
  }
  
  /*
   * Load the apropriate radar for document metadatas
   */
  function load_document_radar(metadata, nid){
    $("#document_charts_btn_group_cs").css("display", "none");
    $.post(location.origin + "/api", {ressource : "stats", action : "get_" + metadata, params : [nid]}).done(function(api_return){
         var data = api_return;
         var canvas = $("#documents_radar_category_state");
         if(canvas){
           canvas.remove();
           $("#documents_radar_category_state_container").prepend('<div id="documents_radar_category_state"></div>');
         }else{
           $("#documents_radar_category_state_container").prepend('<div id="documents_radar_category_state"></div>');
         }
      
         var options = {
            chart: {
              type: "radialBar",
              height: '500px',
              toolbar: {
                  show: false
              }
            },
            series: data.data.datasets.data,
            labels: data.data.labels,
            plotOptions: {
                radialBar: {
                  dataLabels: {
                    total: {
                      show: true,
                      label: data.data.datasets.total_label,
                      formatter: function (w) {
                        return Object.values(data.data.datasets.percentage).reduce((a, b) => {
                          return a + b;
                        }, 0);
                      }
                    },
                    value: {
                        formatter: function (val) {
                          return data.data.datasets.percentage[val];
                        }
                    }
                  }
              }
            }
         };
          
         var chart = new ApexCharts(document.querySelector('#documents_radar_category_state'), options);
         chart.render();
         $("#document_charts_btn_group_cs").css("display", "block");
         $("#documents_radar_category_state_loader").remove();
       });
  }
})(jQuery, Gofast, Drupal);
