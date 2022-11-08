(function ($, Gofast, Drupal) {
  'use strict';
  
  Drupal.behaviors.gofast_stats_space_async = {
        attach: function (context, settings) {
           if (!$(".gofast-og-page").length || typeof $(".gofast-og-page").attr("id") == "undefined") {
             return;
           }
           var currentGid = $(".gofast-og-page").attr("id").replace("node-", "");
           if (typeof currentGid == "undefined") {
             return;
           }
           if($("#tab_ogmemberstats:not(.stats_processed)").parent().parent().find("a").hasClass("active")){
               $("#tab_ogmemberstats").click();
           }
           $("#tab_ogmemberstats:not(.stats_processed)").addClass("stats_processed");
           $("#tab_ogdocumentstats:not(.stats_processed)").addClass("stats_processed");
           $('a[data-toggle="tab"].stats_processed').on("show.bs.tab", function (e) {
                var target = $(e.target).attr("id");
                if (target == "tab_ogmemberstats") {
                  $("#tab_ogdocumentstats").removeClass("active");
                  Gofast.stats_to_load = "user";
                  $("#ogmemberstats").load( "/gofast_stats/space_stats_async", {currentGid});
                }
                else if (target == "tab_ogdocumentstats") {
                  $("#tab_ogmemberstats").removeClass("active");
                  Gofast.stats_to_load = "document";
                  $("#ogmemberstats").load( "/gofast_stats/space_stats_async", {currentGid});
                }
                $("#" + target).addClass("active");
           });
        }
    };
 
  $(document).ready(function(){
    
    //Delete the breadcrumb
   // $(".breadcrumb-gofast").css('display', 'none');
    
    //Trigger calls at the click event on the header
    $("#users_stats_header").click(function(){
      if($("#users_stats_header").hasClass("processed")){ //Already loaded
          
      }else{ //Need to be loaded
        $("#users_stats_header").addClass('processed');
        
        Gofast.stats_filters = [];
        //Trigger event on users stats filters
        $("#users_stats_filter_apply").click(function(e){
          e.preventDefault();

          //Retrieve selected spaces
          var spaces = $("#users_stats_filter > form > div > div > .input-group > tags > tag");
          var spaces_ids = [];

          $.each(spaces, function(k, tag){
            spaces_ids.push($(tag).attr('value'));
          });
          Gofast.stats_filters = spaces_ids;
          load_users_chart();
          load_state_doughnut();
          load_active_doughnut();
          load_roles_bar();
          
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
       load_users_chart('1month');
       $("#user_charts_btn_group_1w").click(function(){Drupal.user_charts_period = '1week'; load_users_chart();});
       $("#user_charts_btn_group_1m").click(function(){Drupal.user_charts_period = '1month'; load_users_chart();});
       $("#user_charts_btn_group_1y").click(function(){Drupal.user_charts_period = '1year'; load_users_chart();});
       $("#user_charts_btn_group_2y").click(function(){Drupal.user_charts_period = '2year'; load_users_chart();});
       $("#user_charts_btn_group_3y").click(function(){Drupal.user_charts_period = '3year'; load_users_chart();});

       /*
        * STATE DOUGHNUT
        * Get the users state doughnut (blocked or allowed)
        */
       load_state_doughnut();

       /*
        * ACTIVE DOUGHNUT
        * Get the users active/inactive state
        */
       load_active_doughnut();

       /*
        * ROLES BAR
        * Get the users roles bars
        */
       load_roles_bar();
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
       load_documents_chart();
       $("#document_charts_btn_group_1w").click(function(){Drupal.document_charts_period = '1week'; load_documents_chart();});
       $("#document_charts_btn_group_1m").click(function(){Drupal.document_charts_period = '1month'; load_documents_chart();});
       $("#document_charts_btn_group_1y").click(function(){Drupal.document_charts_period = '1year'; load_documents_chart();});
       $("#document_charts_btn_group_2y").click(function(){Drupal.document_charts_period = '2year'; load_documents_chart();});
       $("#document_charts_btn_group_3y").click(function(){Drupal.document_charts_period = '3year'; load_documents_chart();});
       $("#document_charts_btn_group_periodic").click(function(){Drupal.document_charts_mode = 'periodic'; load_documents_chart();});
       $("#document_charts_btn_group_evolution").click(function(){Drupal.document_charts_mode = 'evolution';load_documents_chart();});
       
       /*
        * STORAGE DOUGHNUT
        * Get the storage informations
        */
       $.post(location.origin + "/api", {ressource : "stats", action : "get_documents_storage"}).done(function(api_return){
         var data = api_return;
         
          var options = {
            chart: {
              type: 'pie',
              height: '200px',
              toolbar: {
                  show: false
              }
            },
            series: data.data.datasets.data,
            labels: data.data.labels
          };
          
          var chart = new ApexCharts(document.querySelector('#documents_doughnut_storage'), options);
          chart.render();
          
         $("#documents_doughnut_storage_loader").remove();
       });
       
       /*
        * INDEXATION DOUGHNUT
        * Get the indexations informations
        */
       $.post(location.origin + "/api", {ressource : "stats", action : "get_documents_indexation"}).done(function(api_return){
         var data = api_return;
         
          var options = {
            chart: {
              type: 'pie',
              height: '200px',
              toolbar: {
                  show: false
              }
            },
            series: data.data.datasets.data,
            labels: data.data.labels
          };
          
          var chart = new ApexCharts(document.querySelector('#documents_doughnut_indexation'), options);
          chart.render();
          
         $("#documents_doughnut_indexation_loader").remove();
       });
       
       load_document_radar("category");
       $("#document_charts_btn_group_category").click(function(){load_document_radar("category")});
       $("#document_charts_btn_group_state").click(function(){load_document_radar("state")});
       $("#document_charts_btn_group_criticity").click(function(){load_document_radar("criticity")});
      }
    });
    
    $("#users_stats_header").click();
  
      $("#spaces_stats_header").click(function(){
      if($("#spaces_stats_header").hasClass("processed")){ //Already loaded
          
      }else{ //Need to be loaded
        $("#spaces_stats_header").addClass('processed');
        
        /*
        * SPACES CHART
        * Load the users chart and implements listeners
        */
        load_spaces_chart();
        $("#space_charts_btn_group_1w").click(function(){Drupal.space_charts_period = '1week'; load_spaces_chart();});
        $("#space_charts_btn_group_1m").click(function(){Drupal.space_charts_period = '1month'; load_spaces_chart();});
        $("#space_charts_btn_group_1y").click(function(){Drupal.space_charts_period = '1year'; load_spaces_chart();});
        $("#space_charts_btn_group_2y").click(function(){Drupal.space_charts_period = '2year'; load_spaces_chart();});
        $("#space_charts_btn_group_3y").click(function(){Drupal.space_charts_period = '3year'; load_spaces_chart();});
        $("#space_charts_btn_group_periodic").click(function(){Drupal.space_charts_mode = 'periodic'; load_spaces_chart();});
        $("#space_charts_btn_group_evolution").click(function(){Drupal.space_charts_mode = 'evolution';load_spaces_chart();});
        
        get_top_spaces('activity');
        $("#space_bar_btn_group_activity").click(function(){get_top_spaces("activity")});
        $("#space_bar_btn_group_content").click(function(){get_top_spaces("content")});
        $("#space_bar_btn_group_members").click(function(){get_top_spaces("members")});
      }
    });
  });
  /*
   * This function loads the users chart, according to the given period
   */
  function load_users_chart(){
    $("#user_charts_btn_group").css("display", "none");
    
    if(typeof(Drupal.user_charts_period) === "undefined"){
      Drupal.user_charts_period = "1month";
    }
    
    //Get the users chart
    $.post(location.origin + "/api", {ressource : "stats", action : "get_users_chart", params : [Drupal.user_charts_period, null, Gofast.stats_filters]}).done(function(api_return){
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
  
  /*
   * This function loads the users chart, according to the given period
   */
  function load_active_doughnut(){
    $.post(location.origin + "/api", {ressource : "stats", action : "get_users_doughnut_active", params: [null, Gofast.stats_filters]}).done(function(api_return){
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
          height: '200px',
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
  function load_state_doughnut(){
    $.post(location.origin + "/api", {ressource : "stats", action : "get_users_doughnut_state", params: [null, Gofast.stats_filters]}).done(function(api_return){
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
              height: '200px',
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
  
  /*
   * This function loads the users chart, according to the given period
   */
  function load_roles_bar(){
    //Get the users state role
    $.post(location.origin + "/api", {ressource : "stats", action : "get_users_doughnut_roles"}).done(function(api_return){
      var data = api_return;
      var canvas = $("#users_doughnut_roles");
        if(canvas){
          canvas.remove();
          $("#users_doughnut_role_container").append('<div id="users_doughnut_roles"></div>');
        }else{
          $("#users_doughnut_role_container").append('<div id="users_doughnut_roles"></div>');
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

      var chart = new ApexCharts(document.querySelector('#users_doughnut_roles'), options);
      chart.render();
      
      $("#users_doughnut_role_loader").remove();
    });
  }
  
  /*
   * This function loads the users chart, according to the given period
   */
  function load_documents_chart(){
    $("#document_charts_btn_group").css("display", "none");
    $("#document_charts_mode_btn_group").css("display", "none");
    
    if(typeof(Drupal.document_charts_period) === "undefined"){
      Drupal.document_charts_period = "1month";
    }
    if(typeof(Drupal.document_charts_mode) === "undefined"){
      Drupal.document_charts_mode = "evolution";
    }
    if(Drupal.document_charts_mode == "evolution"){
      var type = "area";
    }else{
      var type = "bar";
    }
    //Get the documents chart
    $.post(location.origin + "/api", {ressource : "stats", action : "get_documents_chart", params : [Drupal.document_charts_period, Drupal.document_charts_mode]}).done(function(api_return){
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
      
      //Hide all types except 'Documents'
      for(var i in data.data.datasets){
          if(i != 0){
            chart.toggleSeries(data.data.datasets[i].name);
          }
      }
      
      $("#document_charts_btn_group").css("display", "block");
      $("#document_charts_mode_btn_group").css("display", "block");
      $("#documents_chart_loader").remove();
    });
  }
  
  /*
   * This function loads the users chart, according to the given period
   */
  function load_spaces_chart(){
    $("#space_charts_btn_group").css("display", "none");
    $("#space_charts_mode_btn_group").css("display", "none");
    
    if(typeof(Drupal.space_charts_period) === "undefined"){
      Drupal.space_charts_period = "1month";
    }
    if(typeof(Drupal.space_charts_mode) === "undefined"){
      Drupal.space_charts_mode = "evolution";
    }
    
    if(Drupal.space_charts_mode == "evolution"){
      var type = "area";
    }else{
      var type = "bar";
    }
    //Get the spaces chart
    $.post(location.origin + "/api", {ressource : "stats", action : "get_spaces_chart", params : [Drupal.space_charts_period, Drupal.space_charts_mode]}).done(function(api_return){
      var data = api_return;
      var canvas = $("#spaces_chart");
      if(canvas){
        canvas.remove();
        $("#spaces_chart_container").append('<div id="spaces_chart"></div>');
      }else{
        $("#spaces_chart_container").append('<div id="spaces_chart"></div>');
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

      var chart = new ApexCharts(document.querySelector('#spaces_chart'), options);
      chart.render();
      
      //Hide all types except 'Documents'
      for(var i in data.data.datasets){
          if(i != 0){
            chart.toggleSeries(data.data.datasets[i].name);
          }
      }
      
      $("#spaces_chart_loader").remove();
      $("#space_charts_btn_group").css("display", "block");
      $("#space_charts_mode_btn_group").css("display", "block");
    });
  }
  
  /*
   * Load the apropriate radar for document metadatas
   */
  function load_document_radar(metadata){
    $("#document_charts_btn_group_cs").css("display", "none");
    $.post(location.origin + "/api", {ressource : "stats", action : "get_" + metadata}).done(function(api_return){
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
          
         $("#documents_radar_category_state_loader").remove();
         $("#document_charts_btn_group_cs").css("display", "block");
       });
  }
  
  /*
  * SPACES TOP BAR
  * Get the top 10 spaces, according to some criterias
  */
  function get_top_spaces(criteria){
       $.post(location.origin + "/api", {ressource : "stats", action : "get_top_spaces", params : [criteria]}).done(function(api_return){
         var data = api_return;
         var canvas = $("#spaces_bar_top");
         if(canvas){
           canvas.remove();
           $("#spaces_bar_top_container").prepend('<div id="spaces_bar_top" max-height="400"></div>');
         }else{
           $("#spaces_bar_top_container").prepend('<div id="spaces_bar_top" max-height="400"></div>');
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
           plotOptions: {
               bar: {
                   horizontal: true
               }
           }
         };
         
         var chart = new ApexCharts(document.querySelector('#spaces_bar_top'), options);
         chart.render();
         $("#spaces_bar_top_loader").remove();
       });
  }
  
  /*
   * Handle the downloading of stats
   */
  Gofast.download_users_stats = function(stats_name){
      Gofast.modal('<div class="loader-sync-status"></div> ' + Drupal.t("Please hold on while your export is being generating. This process may take a few minutes.", {}, {context : "gofast_stats"}), Drupal.t("Your export is being generating", {}, {context : "gofast_stats"}));
      //Check filters
      var xid_param = "";
      var spaces = $("#users_stats_filter > form > div > div > .input-group > tags > tag");
      var filters = [];

      $.each(spaces, function(k, tag){
        filters.push($(tag).attr('value'));
      });
      
      if(typeof filters !== "undefined" && filters !== null && filters.length > 0){
          //Parse filters
          xid_param = "?xid=";
          filters.forEach(function(elem){
              xid_param += elem + ","; 
          });
          
          //Remove last comma
          xid_param = xid_param.substr(0, xid_param.length -1);
      } else if ($(".gofast-og-page").length){
        xid_param = "?xid=" + $(".gofast-og-page").attr("id").replace("node-", "");
      }
      
      $.get(location.origin + "/gofast_stats/" + stats_name + xid_param, function(response){
         var downloadInterval = setInterval(function(){
             $.get(location.origin + "/gofast_stats/download/" + response, function(file){
                if(file !== "Waiting"){
                    clearInterval(downloadInterval);
                    Gofast.closeModal();
                    window.location = location.origin + "/gofast_stats/download/" + response;
                } 
             });
         }, 1000); 
      });
  };
})(jQuery, Gofast, Drupal);
