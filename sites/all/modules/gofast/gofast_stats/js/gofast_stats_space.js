(function ($, Gofast, Drupal) {
  'use strict';
  $(document).ready(function(){
    var nid = $(".gofast-og-page").attr("id").replace("node-", "");
    //Trigger calls at the click event on the header
    $("#users_stats_header").click(function(){
      if($("#users_stats_header").hasClass("processed")){ //Already loaded
          $(".stats_container").css('display', 'none');
          $("#stats-menu").find("li").removeClass("active");
          $("#users_stats_header").addClass("active");
          $("#users_stats_container").css('display', 'block');
      }else{ //Need to be loaded
        $("#users_stats_header").addClass('processed');
        $(".stats_container").css('display', 'none');
        $("#stats-menu").find("li").removeClass("active");
        $("#users_stats_header").addClass("active");
        $("#users_stats_container").css('display', 'block');
        
        Drupal.attachBehaviors();
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
    });
    
    
    $("#documents_stats_header").click(function(){
      if($("#documents_stats_header").hasClass("processed")){ //Already loaded
        $(".stats_container").css('display', 'none');
        $("#stats-menu").find("li").removeClass("active");
        $("#documents_stats_header").addClass("active");
        $("#documents_stats_container").css('display', 'block');
      }else{ //Need to be loaded
        $("#documents_stats_header").addClass('processed');
        $(".stats_container").css('display', 'none');
        $("#stats-menu").find("li").removeClass("active");
        $("#documents_stats_header").addClass("active");
        $("#documents_stats_container").css('display', 'block');
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
    
    $("#users_stats_header").click();
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
  
  function load_state_doughnut(nid){
    $.post(location.origin + "/api", {ressource : "stats", action : "get_users_doughnut_state", params : [nid, Gofast.stats_filters]}).done(function(api_return){
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
  
  function load_active_doughnut(nid){
    $.post(location.origin + "/api", {ressource : "stats", action : "get_users_doughnut_active", params : [nid, Gofast.stats_filters]}).done(function(api_return){
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
      var type = "line";
    }else{
      var type = "bar";
    }
    //Get the documents chart
    $.post(location.origin + "/api", {ressource : "stats", action : "get_documents_chart", params : [Drupal.document_charts_period_space, Drupal.document_charts_mode_space, nid]}).done(function(api_return){
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
   * Load the apropriate radar for document metadatas
   */
  function load_document_radar(metadata, nid){
    $("#document_charts_btn_group_cs").css("display", "none");
    $.post(location.origin + "/api", {ressource : "stats", action : "get_" + metadata, params : [nid]}).done(function(api_return){
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
         $("#document_charts_btn_group_cs").css("display", "block");
         $("#documents_radar_category_state_loader").remove();
       });
  }
})(jQuery, Gofast, Drupal);