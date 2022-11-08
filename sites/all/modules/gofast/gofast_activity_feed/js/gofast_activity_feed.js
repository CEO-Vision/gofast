(function ($, Gofast, Drupal) {
  'use strict';

  Gofast.blurDropdown = function() {
    $(".dropdown-menu").hide();
    $(document).off("click", Gofast.blurDropdown);
  }

  Gofast.fixDropdownPosition = function(e) {
    e.preventDefault();
    e.stopImmediatePropagation();
    e.stopPropagation();

    const dropdown = e.relatedTarget;
    const $dropdownMenus = $(dropdown).parent().find(".dropdown-menu");

    // for the menu element to actually have a size
    $dropdownMenus[0].style.display = "initial";

    let { x: dropdownX, y: dropdownY } = dropdown.getBoundingClientRect();
    let dropdownWidth = $dropdownMenus[0].clientWidth;
    let dropdownHeight = $dropdownMenus[0].clientHeight;

    $(".dropdown-menu").hide();

    const mustBePositionedLeft = (dropdownX > (3/5 * window.innerWidth));

    // defaults to middle position
    let verticalPosition = Math.floor(dropdownY - (dropdownHeight / 2));
    // if overflows top or is about to overflow top, put it 10px below window top
    if (verticalPosition <= 10) {
      verticalPosition = 10;
    }
    // if overflows bottom or is about to overflow bottom, put it 10px above window bottom
    if ((dropdownY + dropdownHeight) >= (window.innerHeight - 10)) {
      verticalPosition = (window.innerHeight - dropdownHeight - 10);
    }

    const originalBottomPosition = window.innerHeight - (verticalPosition + dropdownHeight);

    for (let i = 0; i < $dropdownMenus.length; i++) {
      $dropdownMenus[i].style.display = "initial";
      // we admit there are no sub-submenus and sub-menus links are stacked in top of each other, so horizontalFactor is at level 0 or 1 while verticalFactor is incremental
      const horizontalFactor = i > 0 ? 1 : 0;
      const verticalFactor = $dropdownMenus.length - i - 1;
      let subpanelXOffset = mustBePositionedLeft ? -(dropdownWidth * (horizontalFactor + 1)) : dropdownWidth * horizontalFactor; // we offset the subpanels to the left or right depending on the position of the previous panel
      let verticalPositionString = "top:" + verticalPosition + "px !important;";
      if (i > 0) {
        let subpanelYOffset = verticalFactor * 50;
        verticalPositionString = "bottom:" + (originalBottomPosition + subpanelYOffset) + "px !important;";
        subpanelXOffset += mustBePositionedLeft ? 5 : -5; // slight overlap to avoid a gap triggering a mouseleave event
      }
      $($dropdownMenus[i]).css("cssText",
      (i === 0 ? "display: block; " : "") + "position: fixed; height: max-content; " + verticalPositionString + " left: " + Math.floor(dropdownX + subpanelXOffset) + "px;");
    }
    $(document).on("click", Gofast.blurDropdown);
  }

  Drupal.behaviors.gofastReloadMenu = {
    attach: function(context, settings){
      //Polling
      if($("#activity-feed-container").length || $(".apachesolr_search-results").length || $("#gofastDirectorySpacesTable").length){
        //Load menu asyncly
        $(".dropdown-placeholder").not(".dropdown-processed").addClass("dropdown-processed").click(function(){
          if(! $(this).hasClass("dropdown-processing")){
            var nid = this.id.substring(21);
            if($(this).parents('#gofast-node-actions-microblogging').length > 0){
              var microblogging = true;
            }
            var div = $(this).parent();
            var container = div.parent();

            //Animation
            $(this).addClass("dropdown-processing");

            $("#dropdownactive-placeholder-" + nid).show();
            if(microblogging === true){
              $.post(location.origin+"/activity/ajax/microblogging/menu/"+nid,).done(function(data){
                const newDropdown = $(div.replaceWithPush(data)).closest(".dropdown");
                newDropdown.off("click");
                newDropdown.on("show.bs.dropdown", Gofast.fixDropdownPosition);
                Drupal.attachBehaviors();
                container.find(".gofast-node-actions > a").click();
              });
            } else {
              //Load menu
              $.post(location.origin+"/activity/ajax/menu/"+nid, {isFromActivityFeed: true}).done(function(data){
                const newDropdown = $(div.replaceWithPush(data)).closest(".dropdown");
                newDropdown.off("click");
                newDropdown.on("show.bs.dropdown", Gofast.fixDropdownPosition);;
                Drupal.attachBehaviors();
                container.find(".gofast-node-actions > a").click();
              });
            }
          }
        });

        if(Gofast.ActivityPolling && $(".loader-activity-items").length){
         // activityPolling(true);
        }
        if(!Gofast.ActivityPolling){
          Gofast.ActivityPolling = true;
          activityPolling();
        }   
        if(!$("#activity-feed-container").hasClass("processed") && $("#activity-feed-container").length){
          getPagination();
          $("#activity-feed-container").addClass("processed");
        }
        $("#block-gofast-views-activity-stream-filters").not("processed").on("filters_updated", function(e){
          loadPage("filter");
          e.stopImmediatePropagation();
        }).addClass("processed");
        $(".check-display-blog").not("processed").click(function(e){
          if($(this).hasClass('selected')) {
            $.cookie('display_blog',0);
            $(this).removeClass('selected');
          }
          else {
            $.cookie('display_blog',1);
            $(this).addClass('selected');
          }
          e.stopImmediatePropagation();
          e.preventDefault();
          $('#block-gofast-views-activity-stream-filters').trigger("filters_updated");
        }).addClass('processed');
      }
    }
  };

  Drupal.behaviors.applyPopoverOnAuditPage = {
    attach: function (context, settings) {
      if ($(".gofast__popover").length) {
        $('.gofast__popover').popover();
      }
    }
  };

  function loadPage(e, fromPoll = false){  
    if (!fromPoll) {
      //Remove all <tr> elements from the table except the table header
      $("#activity-feed-container").find("tr").not(":first").remove();

      // Insert spinner after #activity-feed 
    // Insert spinner after #activity-feed 
      // Insert spinner after #activity-feed 
      $(".GofastActivityFeed__table").after('<div class="GofastActivityFeed__loader"><div class="spinner spinner-track spinner-primary d-inline-flex gofast-spinner-xxl"></div></div>');
    }

    if(e !== "filter"){ //Click on pagination button
      e.preventDefault();
      //Retrieve the clicked page
      var page = e.target.id.replace("page_", "");
      //Remove old id from href
      var oldURL = document.location.href;
      var index = 0;
      var newUrl = oldURL;
      index = oldURL.indexOf('?');
      if(index == -1){
        index = oldURL.indexOf('#');
      }
      if(index != -1){
        newUrl = oldURL.substring(0, index);
      }
      var newUrl = newUrl + "?page=" + page;
      window.history.pushState({url: "newUrl"},"",newUrl);
    }
    else{ //Click on a filter
      //Retrieve the current page
      var param = Gofast.getAllUrlParams(document.location.href).page;
      if (param != null){
          var page = param ;
      }else{
          var page = $("#activity-feed-pagination").find(".active").find("a").html();
      }
    }

    //Retrieve the filters to pass through request's params
    if(typeof getFiltersFromCookies !== "undefined"){
      var { no_filter, space_filters, type_filters, state_filters, actors_filters, display_blog, user_filter } = getFiltersFromCookies();
      var spaces = [];
      var states = [];
      var types = [];
      var actors = [];
      var blog = 0;
      var private_filter = 0;

      if(no_filter != true) {
        blog = display_blog ? 1 : 0;
        private_filter = user_filter ? 1 : 0;

        space_filters.forEach(filter => {
          spaces.push(filter.id);
        });

        spaces = private_filter ? [] : JSON.stringify(spaces);

        state_filters.forEach(filter => {
          states.push(filter.id);
        });
        
        if(actors_filters == undefined){
          actors_filters = [];
        }
        actors_filters.forEach(filter => {
          actors.push(filter.id);
        });

        states = JSON.stringify(states);

        actors = JSON.stringify(actors);

        types = JSON.stringify(type_filters);
      }
    }
    if(Gofast._settings.isMobile == false || typeof Gofast._settings.isMobile == 'undefined'){
      var mobile = 0;
    }else{
      var mobile = 1;
    }
    $('.gofast__popover').popover('dispose');
    //Push the ajax request
    $.ajax({
      url : Drupal.settings.gofast.baseUrl+'/activity/page',
      type : 'POST',
      dataType: 'html',
      data: {
        'is_count' : 0,
        'page' : page,
        'spaces' : spaces,
        'states' : states,
        'private_filter' : private_filter,
        'actors' : actors,
        'types' : types,
        'display_blog' : blog,
        'mobile' : mobile
      },
      success : function(content, status){
        $("#activity-feed").replaceWith(content);
        $(".GofastActivityFeed__loader").remove();
        getPagination(spaces, states, types /*, users*/);
        $('.gofast__popover').popover();
        Drupal.attachBehaviors();

        //remove tooltip
       $('.tooltip').each(function(key, elt){
          $(elt).remove();
        });
      },
      fail : function(){
        console.log('Activity feed AJAX error');
      }
    });

    //remove tooltip
    $('.tooltip').each(function(key, elt){
      $(elt).remove();
    });
  }

  Gofast.reload_activity_feed = function() {
    loadPage("filter");
    console.log('############# Reload Activity');
  }

  function getPagination(spaces, states, types/*, users*/){
    //Retrieve the current page
    var param = Gofast.getAllUrlParams(document.location.href).page;
    var currentPage = 1;
    if (param != null){
        var currentPage = param ;
    }else{
        var currentPage = $("#activity-feed-pagination").find(".active").find("a").html();
    }

    //Get the pagination (loaded in ajax in order to improve performances)
    $.ajax({
      url : Drupal.settings.gofast.baseUrl+'/activity/ajax',
      type : 'POST',
      dataType: 'json',
      data: {
        'is_count' : 1,
        'spaces' : spaces,
        'states' : states,
        'page' : currentPage,
        //'users' : users,
        'types' : types
      },
      success : function(content, status){
        var count = content;
        var paginate = Drupal.settings.activity_feed.items_per_page;
        var pages = Math.ceil(count/paginate);
        var current_page = $("#activity-feed-page").html();
        $("#activity-feed-pagination").empty();
        for(var i=0; i<pages; i++){
          if((current_page-i) > 6 ){ //Too early according to the current page to display
            if(i == 0){
              $("#activity-feed-pagination").append("<a id='page_" + (i+1) + "' class='activity-feed-page-button btn btn-icon btn-sm border-0 btn-light mr-2 my-1' href='#'><<</a>");
            }
          }
          else if((i-current_page) > 4 ) { //Too far according to the current page to display
            if(i == (pages-1)){
              $("#activity-feed-pagination").append("<a id='page_" + (i+1) + "' class='activity-feed-page-button btn btn-icon btn-sm border-0 btn-light mr-2 my-1' href='#'>>></a>");
            }
          }
          else{
            if( (i+1) == current_page){
              $("#activity-feed-pagination").append("<a id='page_" + (i+1) + "' class='activity-feed-page-button btn btn-icon btn-sm border-0 btn-light btn-hover-primary active mr-2 my-1' href='#'>" + (i+1) + "</a>");
            }
            else{
              $("#activity-feed-pagination").append("<a id='page_" + (i+1) + "' class='activity-feed-page-button btn btn-icon btn-sm border-0 btn-light mr-2 my-1' href='#'>" + (i+1) + "</a>");
            }
          }
        }
        $("#activity-feed-pagination").show();
        $("#activity-feed-pagination").find("a").on('click', function(e){
            e.stopImmediatePropagation();          
            loadPage(e);
        });
        Gofast.removeLoading();
      }
    });
  }

  function activityPolling(unique){
    // Set the name of the hidden property and the change event for visibility
        var hidden, visibilityChange;
        if (typeof document.hidden !== "undefined") { // Opera 12.10 and Firefox 18 and later support
          hidden = "hidden";
          visibilityChange = "visibilitychange";
        } else if (typeof document.msHidden !== "undefined") {
          hidden = "msHidden";
          visibilityChange = "msvisibilitychange";
        } else if (typeof document.webkitHidden !== "undefined") {
          hidden = "webkitHidden";
          visibilityChange = "webkitvisibilitychange";
        }

    if(!unique){
      setTimeout(activityPolling, 30000);
    }
    if($(".gofast-node-actions").hasClass('open')){
      return;
    }

    if($(".dropdown-placeholder").hasClass('dropdown-processing')){
      return;
    }
    if($("[id^=ckeditor_microblogging_]").css('display') === 'inline'){
	return;
    }

    if($("#activity-feed-container").length){
        if(document.hidden == false){
              if(Gofast._settings.isMobile == false || typeof Gofast._settings.isMobile == 'undefined'){
                var mobile = 0;
              }else{
                var mobile = 1;
              }
             if(mobile == 1){
               const tabIds = ["mobileHomeTab_activity", "mobileHomeTab_filebrowser", "mobileHomeTab_dashboard"];
               for (const tabId of tabIds) {
                if($("#" + tabId).hasClass("active")){
                  loadPage('filter', true);
                }else{                   
                    $("#" + tabId).click(function(){                     
                        loadPage('filter', true);
                    })
                } 
               }
               loadPage('filter', true);
             }else{
               loadPage('filter', true);
             }         
        }else{
             console.log("Activity feed not loaded because of non focused tab");
        }
    }
  }

  $(document).ready(function(){
    if($('.breadcrumb-gofast').size() > 1){
      $('.breadcrumb-gofast').first().remove();
    }
  });

})(jQuery, Gofast, Drupal);
