(function ($, Gofast, Drupal) {
  'use strict';
  Drupal.behaviors.gofastReloadMenu = {
    attach: function(context, settings){
      //Polling
      if($("#activity-feed-container").length || $(".apachesolr_search-results").length){
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
		jQuery.post(location.origin+"/activity/ajax/microblogging/menu/"+nid, function(data){
		    var newdiv = div.replaceWith(data);
		    Drupal.attachBehaviors();
		    container.find(".gofast-node-actions").addClass("open");

		    //Align menu
		    console.log(Gofast.last_menu_align);
		    if(Gofast.last_menu_align === "up"){
			$(".gofast-dropdown-menu:not(.dropdown-menu-right)").css("top", "100%").css("bottom", "inherit");
			$(".gofast-dropdown-menu.dropdown-menu-right").css("top", "inherit").css("bottom", "0px");
		    }else{
			$(".gofast-dropdown-menu:not(.dropdown-menu-right)").css("bottom", "100%").css("top", "inherit");
			$(".gofast-dropdown-menu.dropdown-menu-right").css("top", "inherit").css("bottom", "0px");
		    }
		});
	    }else{
		//Load menu
		jQuery.post(location.origin+"/activity/ajax/menu/"+nid, function(data){
		  var newdiv = div.replaceWith(data);
		  Drupal.attachBehaviors();
		  container.find(".gofast-node-actions").addClass("open");

		  //Align menu
		  console.log(Gofast.last_menu_align);
		  if(Gofast.last_menu_align === "up"){
		    $(".gofast-dropdown-menu:not(.dropdown-menu-right)").css("top", "100%").css("bottom", "inherit");
		    $(".gofast-dropdown-menu.dropdown-menu-right").css("top", "inherit").css("bottom", "0px");
		  }else{
		    $(".gofast-dropdown-menu:not(.dropdown-menu-right)").css("bottom", "100%").css("top", "inherit");
		    $(".gofast-dropdown-menu.dropdown-menu-right").css("top", "inherit").css("bottom", "0px");
		  }
		});
	    }
          }
        });

        if(Gofast.ActivityPolling && $(".loader-activity-items").length){
          activityPolling(true);
        }
        if(!Gofast.ActivityPolling){
          Gofast.ActivityPolling = true;
          activityPolling();
        }
        if(! $("#activity-feed-container").hasClass("processed")){
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

  function loadPage(e){
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
      //loader in pagination item
      $("#" + e.target.id).html("<div class='loader-paginate'></div>");
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
    if($(".check-display-blog").hasClass('selected')){
      var display_blog = 1;
    }
    if(! $(".no_filter").hasClass('selected')){
      var spaces = [];
      var states = [];
      var types = [];
      //var users = [];

      var spaces_filter = $(".og_contents_filter").not(".state_contents_filter").not(".type_contents_filter").filter(".selected");
      var states_filter = $(".state_contents_filter").filter(".selected");
      //var users_filter = $(".users_contents_filter").filter(".selected");
      var types_filter = $(".type_contents_filter").filter(".selected");

      spaces_filter.each(function(i, e){
          if(this.id != ""){
                spaces.push(this.id);
            }
      });
      spaces = JSON.stringify(spaces);

      states_filter.each(function(i, e){
        states.push(this.getAttribute('ids'));
      });
      states = JSON.stringify(states);

//      users_filter.each(function(i, e){
//        users.push(this.getAttribute('ids'));
//      });
//      users = JSON.stringify(users);

      types_filter.each(function(i, e){
        types.push(this.getAttribute('id'));
      });
      types = JSON.stringify(types);
    }
    if(Gofast._settings.isMobile == false || typeof Gofast._settings.isMobile == 'undefined'){
      var mobile = 0;
    }else{
      var mobile = 1;
    }
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
       // 'users' : users,
        'types' : types,
        'display_blog' : display_blog,
        'mobile' : mobile
      },
      success : function(content, status){
        $("#activity-feed-page").remove();
        $("#activity-feed").replaceWith(content);
        getPagination(spaces, states, types /*, users*/);
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
              $("#activity-feed-pagination").append("<li ><a id='page_" + (i+1) + "' class='activity-feed-page-button' href='#'><< "+ Drupal.t("First", {}, {'context': 'gofast:activity_feed'}) +"</a></li>");
            }
          }
          else if((i-current_page) > 4 ) { //Too far according to the current page to display
            if(i == (pages-1)){
              $("#activity-feed-pagination").append("<li ><a id='page_" + (i+1) + "' class='activity-feed-page-button' href='#'>>> "+ Drupal.t("Last", {}, {'context': 'gofast:activity_feed'}) +"</a></li>");
            }
          }
          else{
            if( (i+1) == current_page){
              $("#activity-feed-pagination").append("<li class='active' ><a id='page_" + (i+1) + "' class='activity-feed-page-button' href='#'>" + (i+1) + "</a></li>");
            }
            else{
              $("#activity-feed-pagination").append("<li ><a id='page_" + (i+1) + "' class='activity-feed-page-button' href='#'>" + (i+1) + "</a></li>");
            }
          }
        }
        $("#activity-feed-pagination").show();
        $("#activity-feed-pagination").find("a").on('click', function(e){
            e.stopImmediatePropagation();
            loadPage(e);
        });
        $(".loader-activity-feed").hide();
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
            loadPage('filter');
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
