(function ($, Gofast, Drupal) {
  'use strict';
  $(document).ready(function(){
    /*
    * Handle the #ogspace tab
    */
    $('#tab_ogaudit:not(.event_processed)').addClass("event_processed").on("show.bs.tab", function (e) {
      var currentGid = $(".gofast-og-page").attr("id").replace("node-", "");
      if (typeof currentGid == "undefined") {
        return;
      }
      $(this).parent().siblings().children().removeClass("active");
      $.get("/gofast_audit/space_audit/" + currentGid)
        .done(function(data) {
          $("#ogaudit").html(data);
        })
        .fail(function(response) {
          if (response.status == 403) {
            Gofast.toast(Drupal.t("You are not allowed to see the audit page for this space", {}, {context: "gofast:gofast_audit"}), "error");
          } else {
            Gofast.toast(Drupal.t("Something went wrong!"), "error");
          }
          $("#ogtab_documents").click();
        });
      
    })

    $('#tab_ogmemberstats:not(.event_processed), #tab_ogdocumentstats:not(.event_processed)').on("show.bs.tab", function (e) {
      var currentGid = $(".gofast-og-page").attr("id").replace("node-", "");
      if (typeof currentGid == "undefined") {
        return;
      }
      $(this).parent().siblings().children().removeClass("active");
      var target = $(e.currentTarget).attr("id");
      if (target == "tab_ogmemberstats") {
        Gofast.stats_to_load = "user";
        if($(e.currentTarget).hasClass("event_processed")){
          $("#documents_stats").hide().removeClass("show");
          $("#users_stats").show().addClass("show");
          $("#users_stats_header").trigger("click", [currentGid]);
          return;
        }
        $.post("/gofast_stats/space_stats_async", {currentGid, "is_user_tab": true}).done(function(data) {
          $("#users_stats").replaceWith(data);
          $("#documents_stats").hide().removeClass("show");
          $("#users_stats").show().addClass("show");
          $('#tab_ogmemberstats').addClass("event_processed")
          $("#users_stats_header").trigger("click", [currentGid]);
        });
      }
      else if (target == "tab_ogdocumentstats") {
        Gofast.stats_to_load = "document";
        if($(e.currentTarget).hasClass("event_processed")){
          $("#users_stats").hide().removeClass("show");
          $("#documents_stats").show().addClass("show");
          $("#documents_stats_header").trigger("click", [currentGid]);
          return;
        }
        $.post("/gofast_stats/space_stats_async", {currentGid, "is_document_tab": true}).done(function(data) {
          $("#documents_stats").replaceWith(data);
          $("#users_stats").hide().removeClass("show");
          $("#documents_stats").show().addClass("show");
          $('#tab_ogdocumentstats').addClass("event_processed")
          $("#documents_stats_header").trigger("click", [currentGid]);
        })
      }

    });

    //Trigger calls at the click event on the header
    $("#users_stats_header").click(function(e, currentGid = false){
      setup_charts_buttons({"#user_chart_container_mode_buttons": Drupal.user_charts_mode, "#user_chart_container_period_buttons": Drupal.user_charts_period})

      if($(".GofastNodeOg").attr("data-nid") != undefined){
        currentGid = +$(".GofastNodeOg").attr("data-nid");
      }
      if(currentGid){
        const oldNid = $("#users_stats_header").attr("data-nid");
        if(oldNid && oldNid != currentGid){
          $("#users_stats_header").removeClass("processed");
        }
        $("#users_stats_header").attr("data-nid", currentGid);
      }

      if($("#users_stats_header").hasClass("processed")){ //Already loaded
          
      }else{ //Need to be loaded
        $("#users_stats_header").addClass('processed');
        if (currentGid) {
          Gofast.stats_filters = [currentGid];
        }
        //Trigger event on users stats filters
        $("#users_stats_filter_apply").click(function(e){
          e.preventDefault();

          //Retrieve selected spaces
          var spaces = $("#users_stats_filter > form > div > div > .input-group > tags > tag");
          var spaces_ids = [];

          $.each(spaces, function(k, tag){
            spaces_ids.push($(tag).attr('value'));
          });
          if (spaces_ids.length !== 0) {
            Gofast.stats_filters = spaces_ids;
          } else {
            Gofast.stats_filters = undefined;
          }
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
       load_users_chart();
       $("#user_chart_container_mode_buttons button").on("click", (e) => {
        Drupal.user_charts_mode = $(e.currentTarget).data("filter");
        load_users_chart();
       })
       $("#user_chart_container_period_buttons button").on("click", (e) => {
        Drupal.user_charts_period = $(e.currentTarget).data("filter");
        load_users_chart();
       })

       /*
        * STATE DOUGHNUT
        * Get the users state doughnut (blocked or allowed)
        */
       load_state_doughnut([currentGid]);

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

    $("#documents_stats_header").click(function(e, currentGid = false){
      setup_charts_buttons({"#documents_chart_container_mode_buttons": Drupal.document_charts_mode, "#documents_chart_container_period_buttons": Drupal.document_charts_period, "#documents_radar_container_metadata_buttons": Drupal.radar_charts_metadata});

      if($(".GofastNodeOg").attr("data-nid") != undefined){
        currentGid = +$(".GofastNodeOg").attr("data-nid");
      }
      
      if(currentGid){
        const oldNid = $("#documents_stats_header").attr("data-nid");
        if(oldNid && oldNid != currentGid){
          $("#documents_stats_header").removeClass("processed");
        }
        $("#documents_stats_header").attr("data-nid", currentGid);
      }
      $("#space-stats-switch-tooltip").popover()
      $("#space-stats-switch-input").on("change", () => {
        let scope = "";
        if($("#space-stats-switch-input").is(":checked")) {
          scope = "all";
        } else {
          scope = "space_only";
        }
        $("#space-stats-switch-input").data("scope", scope);
        load_documents_chart(currentGid);
        load_document_radar(currentGid);
      })
      if($("#documents_stats_header").hasClass("processed")){ //Already loaded
          
      }else{ //Need to be loaded
        $("#documents_stats_header").addClass('processed');
        
        /*
        * USERS CHART
        * Load the users chart and implements listeners
        */
        load_documents_chart(currentGid);
        $("#documents_chart_container_mode_buttons button").click((e) => {
          Drupal.document_charts_mode = $(e.currentTarget).data("filter");
          load_documents_chart(currentGid);
        })
        $("#documents_chart_container_period_buttons button").click((e) => {
          Drupal.document_charts_period = $(e.currentTarget).data("filter");
          load_documents_chart(currentGid);
        })
       
      if ($("#documents_doughnut_storage_container .stats-loader-container").length) {
        /*
        * STORAGE DOUGHNUT
        * Get the storage informations
        */
        $.post(location.origin + "/api", {ressource : "stats", action : "get_documents_storage"}).done(function(api_return){
          var data = api_return;
          
          var options = {
            chart: {
              type: 'pie',
              height: '100%',
              toolbar: {
                  show: false
              }
            },
            tooltip: {
              y: {
                // Format bytes to the good format
                formatter: function(val){
                  
                  const units = ['B', 'KB', 'MB', 'GB', 'TB'];
                  var bytes = 0;
                  bytes = Math.max(val, 0);
                  const pow = Math.floor((bytes ? Math.log(bytes) : 0) / Math.log(1024));
                  const powLimited = Math.min(pow, units.length - 1);

                  bytes /= Math.pow(1024, powLimited);

                  const result = bytes.toFixed(2);
                  return result;
                }
              }
            },
            series: data.data.datasets.data,
            labels: data.data.labels
          };
          
          var chart = new ApexCharts(document.querySelector('#documents_doughnut_storage'), options);
          $("#documents_doughnut_storage_container .stats-loader-container").remove();
          $("#documents_doughnut_storage").removeClass("d-none")
          chart.render();
          
        });
      } 
       
      if ($("#documents_doughnut_indexation_container .stats-loader-container").length) {
       /*
        * INDEXATION DOUGHNUT
        * Get the indexations informations
        */
        $.post(location.origin + "/api", {ressource : "stats", action : "get_documents_indexation"}).done(function(api_return){
          var data = api_return;
          
          var options = {
            chart: {
              type: 'pie',
              height: '100%',
              toolbar: {
                  show: false
              }
            },
            series: data.data.datasets.data,
            labels: data.data.labels
          };
          
          var chart = new ApexCharts(document.querySelector('#documents_doughnut_indexation'), options);
          $("#documents_doughnut_indexation_container .stats-loader-container").remove();
          $("#documents_doughnut_indexation").removeClass("d-none");
          chart.render();
          
        });
      }
       
        load_document_radar(currentGid);
        $(".radar-chart-btn-group > button").on("click", (e) => {
          let metadata = $(e.currentTarget).data("filter");
          Drupal.radar_charts_metadata = metadata;
          load_document_radar(currentGid);
        })
      }
    });
  
      $("#spaces_stats_header").click(function(){
        setup_charts_buttons({"#space_chart_container_mode_buttons": Drupal.space_charts_mode, "#space_chart_container_period_buttons": Drupal.space_charts_period, "#space_bar_activity_buttons": null})
      if($("#spaces_stats_header").hasClass("processed")){ //Already loaded
          
      }else{ //Need to be loaded
        $("#spaces_stats_header").addClass('processed');
        
        /*
        * SPACES CHART
        * Load the users chart and implements listeners
        */
       
        load_spaces_chart();
        $("#space_chart_container_mode_buttons > button").click((e) => {
          Drupal.space_charts_mode = $(e.currentTarget).data("filter");
          load_spaces_chart();
        })
        $("#space_chart_container_period_buttons > button").click((e) => {
          Drupal.space_charts_period = $(e.currentTarget).data("filter");
          load_spaces_chart();
        })

        get_top_spaces('activity');
        $("#space_bar_activity_buttons > button").click((e) => {
          get_top_spaces($(e.currentTarget).data("filter"))
        })
      }
    });

    if(location.hash == "#documents_stats"){
      if($("#tab_ogdocumentstats").length){
        $("#tab_ogdocumentstats").trigger("show.bs.tab")
      }
    } else if(location.hash == "#users_stats"){
      if($("#tab_ogmemberstats").length){
        $("#tab_ogmemberstats").trigger("show.bs.tab")
      }
    } else if(location.hash == "#ogaudit") {
      if($("#tab_ogaudit").length){
        $("#tab_ogaudit").trigger("show.bs.tab")
      }
    }
    $("#gofastBrowserNavTabs .nav-link:not([id=tab_ogmemberstats], [id=tab_ogdocumentstats])").on("show.bs.tab", () => {
      $("#users_stats").hide().removeClass("show");
      $("#documents_stats").hide().removeClass("show");
    })
    
    const statsHashes = ["#users_stats", "#documents_stats", "#spaces_stats", "#ogaudit"];
    if (statsHashes.includes(location.hash)) {
      $('.nav.nav-tabs a[href="' + location.hash + '"]').click();
    } else if (window.location.pathname == "/gofast_stats/dashboard") {
      setTimeout(() => $("#users_stats_header").click(), 250);
    }
  });
  /*
   * This function loads the users chart, according to the given period
   */
  function load_users_chart(){
    
    const chart_id = "users_chart";
    const chart_element = $(`#${chart_id}`)

    $("#users_chart_container .stats-loader-container").removeClass("d-none");
    if(typeof(Drupal.user_charts_period) === "undefined"){
      Drupal.user_charts_period = $("#user_chart_container_period_buttons > button.default-value").data("filter");
    }
    
    if(typeof(Drupal.user_charts_mode) === "undefined"){
      Drupal.user_charts_mode = $("#user_chart_container_mode_buttons > button.default-value").data("filter");
    }

    chart_element.remove()
    var type = "bar";
    if(Drupal.user_charts_mode == "evolution"){
      type = "area";
    }
    //Get the users chart
    $.post(location.origin + "/api", {ressource : "stats", action : "get_users_chart", params : [Drupal.user_charts_period, null, Gofast.stats_filters, Drupal.user_charts_mode]}).done(function(api_return){
      var data = api_return;
      
      chart_element.remove()
      $(`#${chart_id}_container .stats-container`).append(`<div id="${chart_id}" class="flex-grow-1"></div>`);
      
      var options = {
        chart: {
          type: type,
          height: '100%',
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

      var chart = new ApexCharts(document.querySelector(`#${chart_id}`), options);
      $(`#${chart_id}_container .stats-loader-container`).addClass("d-none");
      chart.render();
    });
  }
  
  /*
   * This function loads the users chart, according to the given period
   */
  function load_active_doughnut(){
    const chart_id = "users_doughnut_active";
    const chart_element = $(`#${chart_id}`)
    $(`#${chart_id}_container .stats-loader-container`).removeClass("d-none");
    chart_element.remove();

    $.post(location.origin + "/api", {ressource : "stats", action : "get_users_doughnut_active", params: [null, Gofast.stats_filters]}).done(function(api_return){
      var data = api_return;
      $(`#${chart_id}_container`).append(`<div id="${chart_id}"></div>`);
      
      var options = {
        chart: {
          type: 'pie',
          height: '100%',
          toolbar: {
              show: false
          }
        },
        series: data.data.datasets.data,
        labels: data.data.labels,
      };
      
      var chart = new ApexCharts(document.querySelector(`#${chart_id}`), options);
      $(`#${chart_id}_container .stats-loader-container`).addClass("d-none");
      chart.render();
    });
  }
  
  /*
   * This function loads the users chart, according to the given period
   */
  function load_state_doughnut(){
    
    const chart_id = "users_doughnut_state"
    const chart_element = $(`#${chart_id}`)
    $(`#${chart_id}_container .stats-loader-container`).removeClass("d-none");
    chart_element.remove();

    $.post(location.origin + "/api", {ressource : "stats", action : "get_users_doughnut_state", params: [null, Gofast.stats_filters]}).done(function(api_return){
        var data = api_return;
        
        $(`#${chart_id}_container`).append(`<div id="${chart_id}"></div>`);

        var options = {
            chart: {
              type: 'pie',
              height: '100%',
              toolbar: {
                show: false
              }
            },
            series: data.data.datasets.data,
            labels: data.data.labels,
        };
        
        var chart = new ApexCharts(document.querySelector(`#${chart_id}`), options);
        $(`#${chart_id}_container .stats-loader-container`).addClass("d-none");
        chart.render();
    });
  }
  
  /*
   * This function loads the users chart, according to the given period
   */
  function load_roles_bar(){
    $("#users_doughnut_role_container .stats-loader-container").removeClass("d-none");
    var canvas = $("#users_doughnut_roles");
    if(canvas){
      canvas.remove();
    }
    //Get the users state role
    $.post(location.origin + "/api", {ressource : "stats", action : "get_users_doughnut_roles", params: [Gofast.stats_filters]}).done(function(api_return){
      var data = api_return;
      $("#users_doughnut_role_container").append('<div id="users_doughnut_roles"></div>');
      
        
      var options = {
        chart: {
          type: 'bar',
          height: '100%',
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
      $("#users_doughnut_role_container .stats-loader-container").addClass("d-none");
      chart.render();
      
      $("#users_doughnut_role_loader").remove();
    });
  }
  
  /*
   * This function loads the users chart, according to the given period
   */
  function load_documents_chart(gid = false){
    let element_id = "documents_chart";
    $("#documents_chart_container .stats-loader-container").removeClass("d-none");
    let scope = "all";
    if($("#space-stats-switch-input").length){
      scope = $("#space-stats-switch-input").data("scope");
    }
    
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
    $("#"+element_id).remove();
    //Get the documents chart
    $.post(location.origin + "/api", {ressource : "stats", action : "get_documents_chart", params : [Drupal.document_charts_period, Drupal.document_charts_mode, gid, scope]}).done(function(api_return){
      var data = api_return;
      
      $("#"+element_id).remove();
      $("#"+element_id+"_container .stats-container").append('<div id="'+element_id+'" class="flex-grow-1"></div>');
       
      var options = {
        chart: {
          type: type,
          height: '100%',
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

      var chart = new ApexCharts(document.querySelector('#'+element_id), options);
      $("#documents_chart_container .stats-loader-container").addClass("d-none");
      chart.render();
      
      // hide all types except "Documents"
      // and temporarily empty the chart "update" method to avoid update rendering at each iteration (which is very time-consuming and may cause some random errors)
      // @see https://github.com/apexcharts/apexcharts.js/issues/1787
      const update = chart.update;
      chart.update = () => { return Promise.resolve(); };
      for(var i in data.data.datasets){
          if(i != 0){
            chart.hideSeries(data.data.datasets[i].name);
          }
      }
      chart.update = update;
      chart.update();
      $("#"+element_id+"_loader").remove();
    });
  }
  
  /*
   * This function loads the users chart, according to the given period
   */
  function load_spaces_chart(){
    
    const chart_id = "spaces_chart";
    const chart_element = $(`#${chart_id}`)
    $(`#${chart_id}_container .stats-loader-container`).removeClass("d-none");
    if(typeof(Drupal.space_charts_period) === "undefined"){
      Drupal.space_charts_period = $("#space_chart_container_period_buttons > button.default-value").data("filter");
    }
    if(typeof(Drupal.space_charts_mode) === "undefined"){
      Drupal.space_charts_mode = $("#space_chart_container_mode_buttons > button.default-value").data("filter");
    }
    
    if(Drupal.space_charts_mode == "evolution"){
      var type = "area";
    }else{
      var type = "bar";
    }
    
    chart_element.remove()
    //Get the spaces chart
    $.post(location.origin + "/api", {ressource : "stats", action : "get_spaces_chart", params : [Drupal.space_charts_period, Drupal.space_charts_mode]}).done(function(api_return){
      var data = api_return;
      chart_element.remove()

      $(`#${chart_id}_container`).append(`<div id="${chart_id}"></div>`);
       
      var options = {
        chart: {
          type: type,
          height: '100%',
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

      var chart = new ApexCharts(document.querySelector(`#${chart_id}`), options);
      $(`#${chart_id}_container .stats-loader-container`).addClass("d-none");
      chart.render();
      
      // hide all types except "Documents"
      // and temporarily empty the chart "update" method to avoid update rendering at each iteration (which is very time-consuming and may cause some random errors)
      // @see https://github.com/apexcharts/apexcharts.js/issues/1787
      const update = chart.update;
      chart.update = () => { return Promise.resolve(); };
      for(var i in data.data.datasets){
          if(i != 0){
            chart.hideSeries(data.data.datasets[i].name);
          }
      }
      chart.update = update;
      chart.update();
      
      $("#spaces_chart_loader").remove();
      $("#space_charts_btn_group").css("display", "block");
      $("#space_charts_mode_btn_group").css("display", "block");
    });
  }
  
  /*
   * Load the apropriate radar for document metadatas
   */
  function load_document_radar(gid = false){
    $("#documents_radar_category_state_container .radar-box").addClass("d-none");
    $("#documents_radar_category_state_container .stats-loader-container").removeClass("d-none");
    let metadata = Drupal.radar_charts_metadata ?? "category"
    let element_id = "documents_radar_category_state"
    let scope = $("#space-stats-switch-input").data("scope");
    $("#"+element_id).remove()
    $.post(location.origin + "/api", {ressource : "stats", action : "get_" + metadata, params: [gid, scope]}).done(function(api_return){
         var data = api_return;
         
         $("#"+element_id).remove()
         $("#"+element_id+"_container .radar-box").prepend('<div id="'+element_id+'"></div>');
      
         var options = {
            chart: {
              type: "radialBar",
              height: '100%',
              width: '100%',
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
                        if(data.data.datasets.total_label == "N/A"){
                          return "";
                        }
                        
                        let total = 0;
                        Object.entries(data.data.datasets.percentage).forEach(([key,value]) => {
                          let nb_occurrences = data.data.datasets.data.filter((percentage) => percentage == key).length;
                          total += nb_occurrences * value;
                        });
                        return total;
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
          let chart = new ApexCharts(document.querySelector('#'+element_id), options);
          $(".radar-chart-container .stats-loader-container").addClass("d-none");
          $("#documents_radar_category_state_container .radar-box").removeClass("d-none");
          chart.render();
          
         $("#"+element_id+"_loader").remove();
       });
  }
  
  /*
  * SPACES TOP BAR
  * Get the top 10 spaces, according to some criterias
  */
  function get_top_spaces(criteria){
    $("#spaces_bar_top_box .stats-loader-container").removeClass("d-none");
    $("#spaces_bar_top").remove();
       $.post(location.origin + "/api", {ressource : "stats", action : "get_top_spaces", params : [criteria]}).done(function(api_return){
         var data = api_return;
        $("#spaces_bar_top").remove();
        $("#spaces_bar_top_box").append('<div id="spaces_bar_top"></div>');
         
         var options = {
           chart: {
             type: 'bar',
             height: '100%',
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
         $("#spaces_bar_top_box .stats-loader-container").addClass("d-none");
         chart.render();
       });
  }
  
  /*
   * Handle the downloading of stats
   */
  Gofast.download_stats = function(stats_name){
      Gofast.modal('<div class="loader-sync-status"></div> ' + Drupal.t("Please hold on while your export is being generating. This process may take a few minutes.", {}, {context : "gofast_stats"}), Drupal.t("Your export is being generating", {}, {context : "gofast_stats"}));
      //Check filters
      var xid_param = "";
      var spaces = $("#users_stats_filter > form > div > div > .input-group > tags > tag");
      var filters = [];

      if (stats_name == "global_doc_stats") {
        filters = {};
        if ($("#gofast-stats-list-docs-form #edit-date").data("datepicker")?.dates?.length) {
          filters.date = $("#gofast-stats-list-docs-form #edit-date").data("datepicker").dates[0].getTime();
        }
        const $spaces = $("#gofast-stats-list-docs-form .form-item-og .checkbox input:checked");
        if ($spaces.length) {
          filters.spaces = [];
          $spaces.each(function() {
            filters.spaces.push($(this).val());
          });
        }
        const $fields = $("#gofast-stats-list-docs-form .form-item-list-fields .checkbox input:checked");
        if ($fields.length) {
          filters.fields = [];
          $fields.each(function() {
            filters.fields.push($(this).val());
          });
        }
      } else {
        $.each(spaces, function(k, tag){
          filters.push($(tag).attr('value'));
        });
      }

      
      if(typeof filters !== "undefined" && filters !== null && Object.keys(filters).length > 0){
          //Parse filters
          xid_param = "?xid=";
          if(Array.isArray(filters)) {
            filters.forEach(function(elem){
                xid_param += elem + ","; 
            });
            //Remove last comma
            xid_param = xid_param.substr(0, xid_param.length -1);
          } else {
            xid_param = "?xid=" + btoa(JSON.stringify(filters)); // base64 encode to avoid adding special characters in URL
          }
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
  Gofast.downloadSpaceState = function(){
    // Make an array from the values of selected fields
    const selectedFields = Array.from($("#document-fields-space-export .all-fields-row input[type=checkbox]:checked"), (el) => $(el).val())
    const getSubpspaces = $("#space-stats-switch-input").is(":checked")
    const currentGid = $(".gofast-og-page").attr("id").replace("node-", "");
    let date = "";
    if ($("#gofastDocumentsStatsDatetimepicker").data("datepicker")?.dates?.length) {
      date = $("#gofastDocumentsStatsDatetimepicker").data("datepicker").dates[0].getTime() / 1000;
    }
    Drupal.CTools.Modal.dismiss();
    Gofast.modal('<div class="loader-sync-status"></div> ' + Drupal.t("Please hold on while your export is being generating. This process may take a few minutes.", {}, {context : "gofast_stats"}), Drupal.t("Your export is being generating", {}, {context : "gofast_stats"}));
    $.post("/gofast_stats/space_document_stats_export", { 
      fields: selectedFields, 
      get_subspaces: getSubpspaces,
      gid: currentGid,
      date: date
    }).done((response) => {
      var downloadInterval = setInterval(function(){
        $.get(location.origin + "/gofast_stats/download/" + response, function(file){
           if(file !== "Waiting"){
               clearInterval(downloadInterval);
               Gofast.closeModal();
               window.location = location.origin + "/gofast_stats/download/" + response;
           } 
        });
      }, 1000); 
    })
  }
  // Setup highlight on filter buttons of charts
  function setup_charts_buttons(all_charts_ids = []) {
    Object.entries(all_charts_ids).forEach(([id, value]) => {
      $(id).find("> button").on("click", (e) => {
        $(id).find("> button").blur()
        $(id).find("> button").removeClass("active")
        $(e.currentTarget).addClass("active");
      })
      if(value == null){
        $(id).find("> button.default-value").addClass("active");
      } else {
        $(id).find(`> button[data-filter=${value}]`).addClass("active")
      }
    })
  }
})(jQuery, Gofast, Drupal);
