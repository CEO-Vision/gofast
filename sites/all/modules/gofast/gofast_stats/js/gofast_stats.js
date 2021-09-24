(function ($, Gofast, Drupal) {
  'use strict';
   
  Drupal.behaviors.gofast_stats_space_async = {
        attach: function (context, settings) {
           if($("#tab_ogstats:not(.stats_processed)").parent().hasClass('active')){
               $("#tab_ogstats:not(.stats_processed)").addClass("stats_processed");
               $("#ogstats").load( "/gofast_stats/space_stats_async");
           } 
           $("#tab_ogstats:not(.stats_processed)").addClass("stats_processed").click(function(){             
                $("#ogstats").load( "/gofast_stats/space_stats_async");
           })
        }
    };
 
  $(document).ready(function(){
    
    //Delete the breadcrumb
   // $(".breadcrumb-gofast").css('display', 'none');
    
    //Trigger calls at the click event on the header
    $("#users_stats_header").click(function(){
      if($("#users_stats_header").hasClass("processed")){ //Already loaded
          $(".stats_container").css('display', 'none');
          $("li").removeClass("active");
          $("#users_stats_header").addClass("active");
          $("#users_stats_container").css('display', 'block');
      }else{ //Need to be loaded
        $("#users_stats_header").addClass('processed');
        $(".stats_container").css('display', 'none');
        $("li").removeClass("active");
        $("#users_stats_header").addClass("active");
        $("#users_stats_container").css('display', 'block');
        
        Gofast.stats_filters = [];
        //Trigger event on users stats filters
        $("#users_stats_filter > form > div > button").click(function(e){
          e.preventDefault();

          //Retrieve selected spaces
          var spaces = $("#users_stats_filter > form > div > div > div > .selection-tags > span").find('.labelize-metadata');
          var spaces_ids = [];

          $.each(spaces, function(k, tag){
            spaces_ids.push($(tag).data('id'));
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
        $(".stats_container").css('display', 'none');
        $("li").removeClass("active");
        $("#documents_stats_header").addClass("active");
        $("#documents_stats_container").css('display', 'block');
      }else{ //Need to be loaded
        $("#documents_stats_header").addClass('processed');
        $(".stats_container").css('display', 'none');
        $("li").removeClass("active");
        $("#documents_stats_header").addClass("active");
        $("#documents_stats_container").css('display', 'block');
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

         var ctx = document.getElementById("documents_doughnut_storage").getContext('2d');
         var myChart = new Chart(ctx, {
             type: 'doughnut',
             data: data.data
         });
         $("#documents_doughnut_storage_loader").remove();
       });
       
       /*
        * INDEXATION DOUGHNUT
        * Get the indexations informations
        */
       $.post(location.origin + "/api", {ressource : "stats", action : "get_documents_indexation"}).done(function(api_return){
         var data = api_return;

         var ctx = document.getElementById("documents_doughnut_indexation").getContext('2d');
         var myChart = new Chart(ctx, {
             type: 'doughnut',
             data: data.data
         });
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
        $(".stats_container").css('display', 'none');
        $("li").removeClass("active");
        $("#spaces_stats_header").addClass("active");
        $("#spaces_stats_container").css('display', 'block');
      }else{ //Need to be loaded
        $("#spaces_stats_header").addClass('processed');
        $(".stats_container").css('display', 'none');
        $("li").removeClass("active");
        $("#spaces_stats_header").addClass("active");
        $("#spaces_stats_container").css('display', 'block');
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
        $("#users_chart_container").append('<canvas id="users_chart" max-height="400"></canvas>');
      }else{
        $("#users_chart_container").append('<canvas id="users_chart" max-height="400"></canvas>');
      }
       
      var ctx = document.getElementById("users_chart").getContext('2d');
      var myChart = new Chart(ctx, {
          type: 'bar',
          data: data.data,
      });
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
        $("#users_doughnut_active_container").append('<canvas id="users_doughnut_active" max-height="400"></canvas>');
      }else{
        $("#users_doughnut_active_container").append('<canvas id="users_doughnut_active" max-height="400"></canvas>');
      }
      
      var ctx = document.getElementById("users_doughnut_active").getContext('2d');
      var myChart = new Chart(ctx, {
        type: 'doughnut',
        data: data.data
      });
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
          $("#users_doughnut_state_container").append('<canvas id="users_doughnut_state" max-height="400"></canvas>');
        }else{
          $("#users_doughnut_state_container").append('<canvas id="users_doughnut_state" max-height="400"></canvas>');
        }
      
        var ctx = document.getElementById("users_doughnut_state").getContext('2d');
        var myChart = new Chart(ctx, {
          type: 'doughnut',
          data: data.data
      });
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
          $("#users_doughnut_role_container").append('<canvas id="users_doughnut_roles" max-height="400"></canvas>');
        }else{
          $("#users_doughnut_role_container").append('<canvas id="users_doughnut_roles" max-height="400"></canvas>');
        }
        
      var ctx = document.getElementById("users_doughnut_roles").getContext('2d');
      var myChart = new Chart(ctx, {
        type: 'bar',
        data: data.data,
        options: {
          scales: {
            yAxes: [{
              ticks: {
                beginAtZero:true
              }
            }]
          },
          legend: {
            display: false
          }
        }
      });
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
      var type = "line";
    }else{
      var type = "bar";
    }
    //Get the documents chart
    $.post(location.origin + "/api", {ressource : "stats", action : "get_documents_chart", params : [Drupal.document_charts_period, Drupal.document_charts_mode]}).done(function(api_return){
      var data = api_return;
      var canvas = $("#documents_chart");
      if(canvas){
        canvas.remove();
        $("#documents_chart_container").append('<canvas id="documents_chart" max-height="400"></canvas>');
      }else{
        $("#documents_chart_container").append('<canvas id="documents_chart" max-height="400"></canvas>');
      }
       
      var ctx = document.getElementById("documents_chart").getContext('2d');
      Drupal.myChart = new Chart(ctx, {
          type: type,
          data: data.data,
      });
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
      var type = "line";
    }else{
      var type = "bar";
    }
    //Get the spaces chart
    $.post(location.origin + "/api", {ressource : "stats", action : "get_spaces_chart", params : [Drupal.space_charts_period, Drupal.space_charts_mode]}).done(function(api_return){
      var data = api_return;
      var canvas = $("#spaces_chart");
      if(canvas){
        canvas.remove();
        $("#spaces_chart_container").append('<canvas id="spaces_chart" max-height="400"></canvas>');
      }else{
        $("#spaces_chart_container").append('<canvas id="spaces_chart" max-height="400"></canvas>');
      }
       
      var ctx = document.getElementById("spaces_chart").getContext('2d');
      Drupal.myChart = new Chart(ctx, {
          type: type,
          data: data.data,
      });
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
           $("#documents_radar_category_state_container").prepend('<canvas id="documents_radar_category_state" max-height="400"></canvas>');
         }else{
           $("#documents_radar_category_state_container").prepend('<canvas id="documents_radar_category_state" max-height="400"></canvas>');
         }
      
         var ctx = document.getElementById("documents_radar_category_state").getContext('2d');
         var myChart = new Chart(ctx, {
             type: 'radar',
             data: data.data
         });
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
           $("#spaces_bar_top_container").prepend('<canvas id="spaces_bar_top" max-height="400"></canvas>');
         }else{
           $("#spaces_bar_top_container").prepend('<canvas id="spaces_bar_top" max-height="400"></canvas>');
         }
         
         var ctx = document.getElementById("spaces_bar_top").getContext('2d');
         var myChart = new Chart(ctx, {
             type: 'horizontalBar',
             data: data.data,
             options: {
              scales: {
                  xAxes: [{
                      ticks: {
                          beginAtZero:true
                      }
                  }]
              }
            },
         });
         $("#spaces_bar_top_loader").remove();
       });
  }
  
  /*
   * Handle the downloading of stats
   */
  Gofast.download_users_stats = function(stats_name, filters){
      Gofast.modal('<div class="loader-sync-status"></div> ' + Drupal.t("Please hold on while your export is being generating. This process may take a few minutes.", {}, {context : "gofast_stats"}), Drupal.t("Your export is being generating", {}, {context : "gofast_stats"}));
      //Check filters
      var xid_param = "";
      if(typeof filters !== "undefined" && filters !== null && filters.length > 0){
          //Parse filters
          xid_param = "?xid=";
          filters.each(function(k, elem){
              var xid = $(elem).find(".labelize-metadata").data("id");
              xid_param += xid + ","; 
          });
          
          //Remove last comma
          xid_param = xid_param.substr(0, xid_param.length -1);
      }
      
      $.get(location.origin + "/gofast_stats/" + stats_name + xid_param, function(response){
         var downloadInterval = setInterval(function(){
             $.get(location.origin + "/gofast_stats/download/" + response, function(file){
                if(file !== "Waiting"){
                    clearInterval(downloadInterval);
                    modalContentClose();
                    window.location = location.origin + "/gofast_stats/download/" + response;
                } 
             });
         }, 1000); 
      });
  };
})(jQuery, Gofast, Drupal);