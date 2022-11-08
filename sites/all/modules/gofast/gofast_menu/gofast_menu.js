(function ($, Gofast, Drupal) {
    'use strict';

    var menuIntervalId;

    Gofast.block = Gofast.block || {};
    Gofast.global = Gofast.global || {};

    // Set goFast views/block property
    Gofast.apply(Gofast.global, {
        gofast_private_msg: {
            gofast_inbox: {
                needRefresh: true,
                firstLoad: true
            },
            //Disabled until this is finished
            /*gofast_notifications: {
        needRefresh: true,
        firstLoad: true
      }*/
        },
        gofast_flag_bookmarks: {
            gofast_flag_bookmarks: {
                needRefresh: true,
                firstLoad: true
            }
        },
        gofast_aggregator: {
            gofast_aggregator: {
                needRefresh: true,
                firstLoad: true
            }
        },
        gofast_workflows_light_dashboard: {
            gofast_workflows: {
                needRefresh: true,
                firstLoad: true
            },
            gofast_workflows_light_dashboard_document: {
                needRefresh: true,
                firstLoad: true
            }
        }
    });

    Drupal.behaviors.gofastBlocks = {
        attach: function (context) {
            //if (Gofast.isGofastBlockTriggered === false) {
            Gofast.isGofastBlockTriggered = true;
            var pinnedItem = false;

            // Adds a little pin to the menu item.
            function pinItem(mainElementId) {
                $(mainElementId).filter(function () {
                    return $(this).data('pinned') === false;
                }).data('pinned', true).find('.pinned').animate({
                    top: "4px",
                    opacity: 1
                }, 150);
                pinnedItem = mainElementId;
            }

            // Removes the little pin on the menu item.
            function unpinItems() {
                var pinedItems = $('.nav-block').filter(function () {
                    return $(this).data('pinned') === true;
                });
                pinedItems.each(function () {
                    var element = $(this);
                    element.data('pinned', false).find('.pinned').animate({
                        top: "-40px",
                        opacity: 0
                    }, 150);
                });
            }

            // Updates the menu item count (badge)
            function updateCount(menuItem, count) {
                count = count === undefined ? 0 : parseInt(count);
                var badge = $(menuItem).find('.unread_count.badge.badge-notify');
                //        if (count === 0) {
                //          badge.css('visibility', 'hidden');
                //        }
                if (count > 0) {
                    badge.css('visibility', 'visible');
                }
                if (badge.html() !== count.toString()) {
                    badge.html(count.toString());
                    if (count === 0 && badge.hasClass("badge-error")) {
                        badge.removeClass("badge-error");
                    }
                    if (count > 0 && !badge.hasClass("badge-error")) {
                        badge.addClass("badge-error");
                    }
                    menuItem.data('forceRefresh', true);

                    // Force element update
                    if (pinnedItem === menuItem) {
                        Gofast.block.loadIfNeeded(menuItem);
                    }
                }
                menuItem.data('forceRefresh', false);
            }

            // Pulls information to get update of the content
            function pullItemUpdate(menuItem) {
                var request = null;
                switch (menuItem.attr('id')) {
                    case "gofast_view-gofast_private_msg-gofast_inbox":
                        request = "/messages/get_unread_count";
                        break;
                    case "gofast_view-gofast_private_msg-gofast_notifications":
                        request = "/notifications/get_unread_count";
                        break;
                }
                if (request !== null) {
                    $.ajax({
                        url: request,
                        method: "POST",
                        timeout: 5000,
                        'beforeSend': function(xhr) {
                            Gofast.xhrPool = Gofast.xhrPool || {};
                            Gofast.xhrPool.xhrGetUnreadCount = xhr;  // before jQuery send the request we will add it into our object
                        },
                        'complete': function() {
                            delete Gofast.xhrPool.xhrGetUnreadCount;
                        }
                    }).done(function (msg) {
                        var messageCount = $.parseJSON(msg).count;
                        updateCount(menuItem, messageCount);
                    });
                    //          setInterval(function () {
                    //            $.ajax({
                    //              url: request,
                    //              method: "POST",
                    //              timeout: 5000,
                    //              'beforeSend': function(xhr) {
                    //                Gofast.xhrPool = Gofast.xhrPool || {};
                    //                Gofast.xhrPool.xhrGetUnreadCount = xhr;  // before jQuery send the request we will add it into our object
                    //              },
                    //              'complete': function() {
                    //                delete Gofast.xhrPool.xhrGetUnreadCount;
                    //              }
                    //            }).done(function (msg) {
                    //              var messageCount = $.parseJSON(msg).count;
                    //              updateCount(menuItem, messageCount);
                    //            });
                    //          }, 50000); //15 seconds
                }
            }

            if (!$('body').hasClass('delegated')) {
                $(document).click(function (event) {
                    if (!$('#modalContent').length && event.which != 3) {
                        pinnedItem = false;
                        $('.gofast-block-outer').hide();
                        unpinItems();
                    }
                });
            }

            // We ensure this binding will be executed only one time
            $('.navigation-section--left .nav-block', context).once('', function () {
                var item = $(this),
                block = item.find('.gofast-block-outer');

                // Initialize count on page load.
                updateCount(item, item.data('unread'));
                // Then start pull request new events.
                //pullItemUpdate(item);

                item.mouseenter(function () {
                    $('.gofast-block-outer').hide();
                    block.css('display', 'block');
                    block.css('width', $(document).width() / 2);
                    if (item.data('forceRefresh') === undefined) {
                        item.data('forceRefresh', true);
                    }
                    Gofast.block.loadIfNeeded($(this));
                    if (pinnedItem && pinnedItem !== item) {
                        unpinItems();
                        pinItem(item);
                    }
                });

                item.find('*').mousedown(function () {
                    if (!pinnedItem) {
                        pinItem(item);
                    }
                }).click(function (e) {
                    if($(this).attr('class') !== 'bookmarksTab'){
                        e.stopPropagation();
                    }
                });

                item.mouseleave(function () {
                    // Timeout is needed because we want to test 'pinnedItem' after triggering delegated mouseenter event (if exists) :
                    // mouseleave block -> mouseenter popup -> !pinnedItem -> test pinnedItem
                    if (!pinnedItem) {
                        setTimeout(function () {
                            block.hide();
                            if (pinnedItem) {
                                unpinItems();
                            }
                        }, 10);
                    }
                });
            });
            //}
        }

    };


    /**
     * S'assure que les blocs du header soit bien "processed".
     */
    //  Drupal.behaviors.recallViewsAjax = {
    //    attach: function() {
    //      if (!Drupal.Views){
    //        // Drupal.Views is undefined, we have to load some scripts before the
    //        // behavior ViewAjaxView throws an error.
    //        var tmp = Drupal.behaviors.ViewsAjaxView;
    //        Drupal.behaviors.ViewsAjaxView = function(){ return; };
    //        var path = '/drupal/sites/all/modules/views/js/';
    //        Gofast.loadScript('/drupal/misc/tabledrag.js');
    //        // Ensure base.js is entirely loaded before loading ajax.js
    //        Gofast.loadScript(path+'base.js', Gofast.loadScript, path+'ajax.js');
    //        // Ensure ajax_view.js is entirely loaded before calling behavior.
    //        Gofast.loadScript(path+'ajax_view.js', callViewsAjaxView, tmp);
    //        tmp = null;
    //      }
    //    }
    //  };


    //function callViewsAjaxView(func) {
    //  Drupal.behaviors.ViewsAjaxView = func;
    //  Drupal.behaviors.ViewsAjaxView();
    //}


    Gofast.loadScript = function (url, callback) {
        // Adding the script tag to the head
        var head = document.getElementsByTagName('head')[0],
        script = document.createElement('script');
        script.type = 'text/javascript';
        script.src = url;
        if (callback) {
            // Bind the event to the callback function , retrieve args.
            // There are several events for cross browser compatibility
            var arg = arguments[2] ? arguments[2] : '';
            script.onreadystatechange = function () {
                callback(arg);
            };
            script.onload = function () {
                callback(arg);
            };
        }
        // Fire the loading
        head.appendChild(script);
    };

    Drupal.behaviors.gofastBlockCollapseFilters = {
        attach: function (context, settings) {
            var show = '<span class="glyphicon glyphicon-resize-full"></span> ' + Drupal.t('Show filters', {}, {'context' : 'gofast'});
            var hide = '<span class="glyphicon glyphicon-resize-small"></span> ' + Drupal.t('Hide filters', {}, {'context' : 'gofast'});
            $('.nav-block .view-filters:not(.filters-processed)').addClass('filters-processed').each(function () {
                var elem = $(this);
                elem.before('<a class="btn gofast_toggle_filters gofast-button">' + show + '</a>');
                elem.hide();
                elem.prev().click(function () {
                    Drupal.attachBehaviors();
                    elem.slideToggle();
                    if ($(this).html() === show)
                        $(this).html(hide);
                    else
                        $(this).html(show);
                });
            });
        }
    }



    /**
     * Checks if the content (view/block) needs to be loaded or refreshed and
     * performs suitable action.
     * @param {JQuery object} content
     */
    Gofast.block.loadIfNeeded = function (content) {
        var id = content.attr('id');
        var title = "";
        if(typeof content.attr('block_title') != "undefined"){
            title = content.attr('block_title').capitalize();
        }else{
            title = content.attr('class').replace(/gofast| |-|block|processed|pdf-ie-fixed/g, '').capitalize();
        }
        id = id.split('-');

        if (id.length > 3) { // Handle possible use of '-' in block naming
            for (var i = 3; i < id.length; i++) {
                id[2] += '-' + id[i];
            }
        }

        //    if (id[0] === 'gofast_view' && Gofast[id[1]][id[2]]['needRefresh']) {
        //      Gofast.block.load(id[1], id[2], title, content.find('.gofast-block-inner'), 0);
        //    }
        //    else if (id[0] === 'gofast_block' && Gofast[id[1]][id[2]]['needRefresh']) {
        //
        //      Gofast.block.load(id[1], id[2], title, content.find('.gofast-block-inner'), 1);
        //    }

        // If the content is not already loaded then we trigger load
        if (!content.hasClass('gofast-block-processed') || content.data('forceRefresh')) {
            if (id[0] === 'gofast_view') {
                Gofast.block.load(id[1], id[2], title, content.find('.gofast-block-inner'), 0, 0);
            } else if (id[0] === 'gofast_block') {
                Gofast.block.load(id[1], id[2], title, content.find('.gofast-block-inner'), 1, 0);
            } else if (id[0] === 'gofast_block_delta') {
                Gofast.block.load(id[1], id[2], title, content.find('.gofast-block-inner'), 1, 1);
            }
            content.data('forceRefresh', false);
        }
    };


    //get main menu elements asynchronously
    Drupal.behaviors.gofastMenuAsync = {
        attach: function (context, settings) {
            if (typeof Gofast.processBookmarksBlock === "function" && !$('.view-gofast-flag-bookmarks').hasClass('processed')) {
                Gofast.processBookmarksBlock();
                $('.view-gofast-flag-bookmarks').addClass('processed');
            }
            if ($('.view-gofast-flag-bookmarks.page-dashboard-spaces').length) {
                if (typeof Gofast.processBookmarksBlock === "function" && !$('.view-gofast-flag-bookmarks.page-dashboard-spaces').hasClass('processed2')) {
                    // alert("debug");
                    Gofast.processBookmarksBlock("page-dashboard-spaces");
                    $('.view-gofast-flag-bookmarks.page-dashboard-spaces').addClass('processed2');
                }
            }
        }
    };

    /*
     * Refresh the last recenlty read block in the burger menu
     */
    Drupal.behaviors.async_last_recently_read_menu = {
        attach: function (context, settings) {
            $('#async_recently_read:not(.processed)', context).addClass('processed').parent().hover(function () {
                if ($('#recenlty_read_block_menu').length >= 0) {
                    $('#recenlty_read_block_menu', context).remove();
                }
                $('.recenlty-read-actions-loading').show();
                $.post(location.origin + "/gofast/last_recenlty_read").done(function (data) {
                    if ($('#recenlty_read_block_menu').length >= 0) {
                        $('#recenlty_read_block_menu').remove();
                    }
                    $('.recenlty-read-actions-loading', context).hide();
                    $('#async_recently_read').parent().find('h2').after('<div id="recenlty_read_block_menu">' + data + '</div>');
                });
            });
            $('.block-recently-read:not(.processed)', context).addClass('processed').hover(function (e) {
                if ($('#recenlty_read_block_menu').length >= 0) {
                    $('#recenlty_read_block_menu',context).remove();
                }
                $('.recenlty-read-actions-loading').show();
                $.post(location.origin + "/gofast/last_recenlty_read").done(function (data) {
                    if ($('#recenlty_read_block_menu').length >= 0) {
                        $('#recenlty_read_block_menu').remove();
                    }
                    $('.recenlty-read-actions-loading').hide();
                    $('.block-recently-read').find('h2').after('<div id="recenlty_read_block_menu">' + data + '</div>');
                    $("#recenlty_read_block_menu a").click(function(e){
                        e.preventDefault();
                        e.stopPropagation();
                        e.stopImmediatePropagation();
                        Gofast.processAjax(e.currentTarget.href);
                    });
                });
            });
    
      
            let recentlyReads = document.querySelector('#recenlty_read_block_menu:not(.processed)');
            let recentlyReadsButton = document.querySelector('#recenlty_read_block_menu:not(.processed) a');
            if(recentlyReads){
                recentlyReads.classList.add('processed');
                let container = recentlyReads.querySelector('.gofast-block-inner');
                let loader = recentlyReads.querySelector('.loader-blog');
        
                $('#recenlty_read_block_menu').mouseover(function() {
                    if(!recentlyReads.classList.contains('gofast-menu-active')) {
                        recentlyReads.classList.add('gofast-menu-active');
                        $.post(location.origin + "/gofast/last_recenlty_read").done(function (data) {
                            container.innerHTML = data;                            
                        }); 
                    }
                })
                        .mouseleave(function() {
                            recentlyReads.classList.remove('gofast-menu-active');
                })
            }

        }
    };
    Drupal.behaviors.async_bookmarks_menu = {
        attach: function(context, settings) {
            let bookmarks = document.querySelector('#gofast_topbar_flag_bookmarks:not(.processed)');
            let bookmarksButton = document.querySelector('#gofast_topbar_flag_bookmarks:not(.processed) a');

            if(bookmarks){
                bookmarks.classList.add('processed');
                let container = bookmarks.querySelector('.gofast-block-inner');
                let loader = bookmarks.querySelector('.loader-blog');
                
                $('#gofast_topbar_flag_bookmarks').mouseover(function() {
                    if(!bookmarks.classList.contains('gofast-menu-active')) {
                        bookmarks.classList.add('gofast-menu-active');
                        $.post(location.origin + "/gofast/get/personnal_favorites").done(function (data) {
                            container.innerHTML = data; 
                            $('#contentFavoritesTab').removeClass('active');
                            Gofast.Display_ContentFolders();
                        }); 
                    }
                })
                .mouseleave(function({target}) {
                    // if the mouseleave is triggered by a pagination click, do not set the menu to fetch the whole content again (which would navigate the user back to page 1)
                    if (target.classList.contains("page_link")) {
                        return;
                    }
                    bookmarks.classList.remove('gofast-menu-active');
                $('.block-bookmarks .gofast-bookmarks-block-inner section').empty();
                })

            }
        }
    };   
    
    Drupal.behaviors.async_rssFeed_menu = {
        attach: function(context, settings) {
            let rss = document.querySelector('#gofast_aggregator:not(.processed)');
            let rssButton = document.querySelector('#gofast_aggregator:not(.processed) a');
            
            if(rss){
                let container = rss.querySelector('.gofast-block-inner');              
                
                $('#gofast_aggregator').mouseover(function() {
                    if(!rss.classList.contains('gofast-menu-active')) {
                        rss.classList.add('gofast-menu-active');
                        if(rss.classList.contains('processed')) {
                            return;
                        }
                        $.post(location.origin + "/gofast/get/rssFeed").done(function (data) {
                            container.innerHTML = data["output"];
                            $('#gofastRssContent').pager({
                                pagerSelector: '#gofast-rss-content-pager',
                                perPage: 10,
                                numPageToDisplay: 5,
                                isFlex: true
                            });
                            rss.classList.add('processed');
                        }); 
                    }
                })
                .mouseleave(function() {
                    rss.classList.remove('gofast-menu-active');
                })
            }     
        }
    };
    
    Drupal.behaviors.async_privateMessages_menu = {
        attach: function(context, settings) {
            let pm = document.querySelector('#gofast_private_msg_inbox:not(.processed)');
            let pmButton = document.querySelector('#gofast_private_msg_inbox:not(.processed) a');

            if(pm){
                pm.classList.add('processed');
                let container = pm.querySelector('.gofast-block-inner');
                let loader = pm.querySelector('.loader-blog');
                
                $('#gofast_private_msg_inbox').mouseover(function() {
                    if(!pm.classList.contains('gofast-menu-active')) {
                        pm.classList.add('gofast-menu-active');
                        $.post(location.origin + "/gofast/get/privateMessages").done(function (data) {
                            container.innerHTML = data["output"];  
                        }); 
                    }
                })
                        .mouseleave(function() {
                            pm.classList.remove('gofast-menu-active');
                })

            }
        }
    };  
    

    Gofast.block.loadMenuAsync = function (gid, elemId) {
        clearInterval(menuIntervalId);
        //var already_html =  $("#"+elemId).html();
        var already_html = "";
        //        if (already_html == "") {
        //            $.ajax({
        //                url: "/gofast/menu/get",
        //                data: 'gid=' + gid,
        //                dataType: 'html',
        //                success: function (data) {
        //                    
        //                    
        //                    //Slide menu to left or right if needed
        //                 
        //                    var submenu_container = $("#" + elemId).parent().parent();                    
        //                    if($(submenu_container).next().length > 0){
        //                        var next_sibilings =  $(submenu_container).nextUntil();
        ////                        console.log(next_sibilings);
        //                        $(submenu_container).nextUntil().each(function(){
        ////                            console.log("next_sibilings => removed");
        //                            $(this).remove();
        //                        });
        //                    }
        //                    $(submenu_container).after(data);
        //                    
        //                    Drupal.attachBehaviors($(submenu_container).next());
        //
        //                    clearInterval(menuIntervalId);
        //                }
        //            });
        //        }
    }

    /**
     * Performs ajax request
     * Loads a themed view (block) inside container.
     * If isBloc is true, the function will return the module block view op based
     * on viewName as module name and displayID as delta.
     */
    Gofast.block.load = function (viewName, displayID, title, container, isBloc, isBlocDelta) {
        var load = $('<div class="ajax-loader"></div>').css('display', 'block');
        if (Gofast.global[viewName][displayID]['firstLoad'] && container.find('.ajax-loader').size() === 0) {
            container.prepend(load);
        }

        var path = Gofast.getCurrentUrl(),
        query = {
            'viewName': viewName,
            'displayID': displayID,
            'subject': title,
            'original_path': path,
            'isBloc': isBloc,
            'isBlockDelta': isBlocDelta,
        };


        $.ajax({
            type: "POST",
            url: '/gofast_get_block',
            data: query,
            dataType: 'json',
            'beforeSend': function(xhr) {
                Gofast.xhrPool = Gofast.xhrPool || {};
                Gofast.xhrPool.xhrGetBlocks = xhr;  // before jQuery send the request we will add it into our object
            },
            'complete': function() {
                delete Gofast.xhrPool.xhrGetBlocks;
            },
            success: function (result) {
                Gofast.global[viewName][displayID]['needRefresh'] = false;
                if (typeof Drupal.settings.views === 'undefined') {
                    Drupal.settings.views = {
                        ajaxViews: result.view,
                        ajax_path: '/views/ajax'
                    };
                } else {
                    Drupal.settings.views.ajaxViews = result.view;
                    Drupal.settings.views.ajax_path = '/views/ajax';
                }

                container.html(result.output);
                Drupal.attachBehaviors();
                if (Gofast.global[viewName][displayID]['firstLoad']) {
                    Gofast.global[viewName][displayID]['firstLoad'] = false;
                    load.remove();
                }
                if(viewName == "gofast_flag_bookmarks"){
                    $('#gofast_view-gofast_flag_bookmarks-gofast_flag_bookmarks .block-title').remove();
                    if(typeof Gofast.processBookmarksBlock !== undefined && !$('.view-gofast-flag-bookmarks.view-display-id-page_1').hasClass('processed2')){
                        Gofast.processBookmarksBlock("view-display-id-page_1");
                        $('.view-gofast-flag-bookmarks.view-display-id-page_1').addClass('processed2');
                    }
                    if($('.view-gofast-flag-bookmarks.view-display-id-gofast_flag_bookmarks').length){
                        if(typeof Gofast.processBookmarksBlock !== undefined && !$('.view-gofast-flag-bookmarks.view-display-id-gofast_flag_bookmarks').hasClass('processed2')){
                            Gofast.processBookmarksBlock("view-display-id-gofast_flag_bookmarks");
                            $('.view-gofast-flag-bookmarks.view-display-id-gofast_flag_bookmarks').addClass('processed2');
                        }
                    }

                    if($('.view-gofast-flag-bookmarks.page-dashboard-spaces').length){
                        if(typeof Gofast.processBookmarksBlock !== undefined && !$('.view-gofast-flag-bookmarks.page-dashboard-spaces').hasClass('processed2')){
                            // alert("debug");
                            Gofast.processBookmarksBlock("page-dashboard-spaces");
                            $('.view-gofast-flag-bookmarks.page-dashboard-spaces').addClass('processed2');
                        }
                    }
                }

                /*$(".block-bookmarks").find("section").bind("DOMSubtreeModified", function(e) {
            processBookmarksBlock(e);
        });*/
            }
        });

        Gofast.processBookmarksBlock = function(filterClass){
            //Iterate into each element of this block
            if(typeof filterClass == "undefined"){
                filterClass = "view-display-id-page_1";
            }
            // debugger;
            $("#navbar .view-gofast-flag-bookmarks."+filterClass+" > div > table > tbody > tr").each(function(k, item){
                //Reformat all unflag links
                $(item).find("td:last").find("a:not('.dropdown-placeholder, .dropdown-toggle')").html('<span style="color:red;" class="fa fa-trash"></span>');

                $(item).find("td.views-field-nothing").find("a").click(function(e){ //Process clicks in ajax
                    e.preventDefault();
                    e.stopPropagation();
                    e.stopImmediatePropagation();
                    Gofast.processAjax(e.currentTarget.href);
                });

                //Check folder bookmarks
                var titleItem = $(item).find(".gofast_flag_title > a");
                if(titleItem.text().indexOf("[GFOLDER]") !== -1){
                    $(item).find("td:last").find("a").attr('title', Drupal.t('Remove this post from your bookmarks'));
                    titleItem.text(titleItem.text().substr(0, titleItem.text().indexOf("[GFOLDER]")));
                    $(item).find(".gofast_flag_title > span").addClass('fa-folder');
                    $(item).find("td:last").find("a").attr('href', "#");
                    $(item).find("td:last").find("a").click(function(e){ //Replace click event
                        e.preventDefault();
                        e.stopPropagation();
                        e.stopImmediatePropagation();

                        //Get folder emplacement
                        var href = encodeURIComponent($(item).find(".views-field-field-emplacement").text());
                        var folder_reference = encodeURIComponent($(item).find(".views-field-field-reference").text());
                        $(item).find("td:last").html('<div class="loader-paginate"></div>');
                        $.post(location.origin + "/ajax_file_browser/unbookmark_folder", {folder_reference: folder_reference}, function(){
                            Gofast.toast(Drupal.t("Folder removed from bookmarks"), "success");
                            //                                $(".block-bookmarks").data('forceRefresh', true);
                            //                                Gofast.block.loadIfNeeded($(".gofast-block"));
                            $(item).remove();
                        });
                    });
                }
            });
        };


        Gofast.Display_FavoritesFolders = function(event){
            if(!$('#foldersFavoritesTab').hasClass('active')) {
                $('.block-bookmarks #gofastFavoriteFolderTabContent div').empty();
                if($('.block-bookmarks .gofast-bookmarks-block-inner .loader-blog').length == 0){
                    if($('.block-bookmarks .gofast-bookmarks-block-inner section .view-gofast-flag-bookmarks').length !== 0){
                        $('.block-bookmarks .gofast-bookmarks-block-inner section .view-gofast-flag-bookmarks').remove();
                        $('.block-bookmarks .gofast-bookmarks-block-inner section').append('<div class="loader-blog"></div>');
                    }else{
                        $('.block-bookmarks .gofast-bookmarks-block-inner .dashboard-folders-placeholder').remove();
                        $('.block-bookmarks .gofast-bookmarks-block-inner').append('<div class="loader-blog"></div>');
                    }
                    $.post(location.origin + "/gofast/bookmarks/favorites_folders").done(function(data){
                        $('#path_pager_bookmarks_folders').remove();
                        $('.block-bookmarks .gofast-bookmarks-block-inner .loader-blog').remove();
                        $('#gofastFavoriteFolderTabContent div').append(data);
                        $('.view-display-id-gofast_bookmarks_folders ul.pagination').parent().remove();
                        jQuery('.view-display-id-gofast_bookmarks_folders table tbody').pager({pagerSelector : '#path_pager_bookmarks_folders', perPage: 6, numPageToDisplay : 5, showPrevNext: true});
                        $('.menu-topbar-favorites-folders-delete').on('click', function(e) {
                            e.preventDefault();
                            e.stopPropagation();
                            e.stopImmediatePropagation();
                            const href = $(this).find('a').attr('href');
                            this.parentElement.remove();
                            $.get({
                                url: href
                            });
                        })
                        //                        Gofast.processBookmarksBlock("view-display-id-gofast_bookmarks_folders");
                        //                        Drupal.attachBehaviors();
                        //                        Gofast.bookmarksPageBindPagination();
                    });
                }
            }
        }

        Gofast.Display_ContentFolders = function(event){
            if(!$('#contentFavoritesTab').hasClass('active')) {
                $('.block-bookmarks #gofastFavoriteContentTabContent div').empty();
                if($('.block-bookmarks .gofast-bookmarks-block-inner .loader-blog').length == 0){
                    if($('.block-bookmarks .gofast-bookmarks-block-inner section .gofastFlagBookmarks').length !== 0){
                        $('.block-bookmarks .gofast-bookmarks-block-inner section .gofastFlagBookmarks').remove();
                        $('.block-bookmarks .gofast-bookmarks-block-inner').append('<div class="loader-blog"></div>');
                    }else{
                        $('.block-bookmarks .gofast-bookmarks-block-inner .dashboard-folders-placeholder').remove();
                        $('.block-bookmarks .gofast-bookmarks-block-inner').append('<div class="loader-blog"></div>');
                    }
                    $.post(location.origin + "/gofast/bookmarks/favorites_contents").done(function(data){
                        if($('.block-bookmarks .gofast-bookmarks-block-inner section .gofastFlagBookmarks').length == 0){
                            $('#path_pager_bookmarks_folders').remove();
                            $('.block-bookmarks .gofast-bookmarks-block-inner .loader-blog').remove();
                            $('#gofastFavoriteContentTabContent div').html(data);
                            $('.menu-topbar-favorites-delete').on('click', function(e) {
                                e.preventDefault();
                                let href = $(this).find('a').attr('href');
                                this.parentElement.remove();
                                $.get({
                                    url: href
                                });
                            })
                            //                            Gofast.processBookmarksBlock("view-display-id-gofast_flag_bookmarks");
                            //                            Drupal.attachBehaviors();
                            //                            Gofast.bookmarksPageBindPagination();
                        }
                    });
                }
            }
        }

        Gofast.bookmarksPageBindPagination = function () {
            $('.view-gofast-flag-bookmarks .pagination li a').click(function(event){
                event.preventDefault();
                event.stopPropagation();
                $.post(location.origin + $(this).attr("href")).done(function(data){
                    $('.block-bookmarks .gofast-block-inner section .view-gofast-flag-bookmarks').remove();
                    $('.block-bookmarks .gofast-block-inner section').append(data);
                    Gofast.bookmarksPageBindPagination();
                });
            });
        };


        Drupal.behaviors.delayButton = {
            attach: function (context, settings) {
                var hoverTimeout;
                $('.gofast-about-btn').hover(function(e) {
                    e.preventDefault;
                    $('.gofast-about-btn > .dropdown-content').show();
                    clearTimeout(hoverTimeout);
                    $(this).addClass('hovered');
                }, function() {
                    var $self = $(this);
                    hoverTimeout = setTimeout(function() {
                        $self.removeClass('hovered');
                        $('.gofast-about-btn > .dropdown-content').fadeOut(200);
                    }, 500);
                });
                $('#dropdown-menu-page').hover(function(e) {
                    e.preventDefault;
                    $('#dropdown-menu-page > .dropdown-content').show();
                    clearTimeout(hoverTimeout);
                    $(this).addClass('hovered');
                }, function() {
                    var $self = $(this);
                    hoverTimeout = setTimeout(function() {
                        $self.removeClass('hovered');
                        $('#dropdown-menu-page > .dropdown-content').fadeOut(200);
                    }, 500);
                });

                $('#dropdown-menu-page-search').hover(function(e) {
                    e.preventDefault;
                    $('#dropdown-menu-page-search > .dropdown-content').show();
                    clearTimeout(hoverTimeout);
                    $(this).addClass('hovered');
                }, function() {
                    var $self = $(this);
                    hoverTimeout = setTimeout(function() {
                        $self.removeClass('hovered');
                        $('#dropdown-menu-page-search > .dropdown-content').fadeOut(200);
                    }, 500);
                });
            }
        }

        container.parents('.nav-block').addClass('gofast-block-processed');
    };

})(jQuery, Gofast, Drupal);
