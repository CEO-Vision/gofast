/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
/**
 * Library JS to instanciate and manage special component for MENU.
 * 
 * This component required the following specific template to work
 * cf.
 * - gofast-menu-header-menu-item.tpl.php
 * - gofast_menu_menu_content.tpl.php
 * - gofast-menu-menu-item.tpl.php
 * 
 * ---------------------------------
 * see HOW TO USE in GOFAST-6891
 * 
 */
var GFMegaMenu = function () {

    //Private propoerties
    var _menuElement;
    var _menuObject;
    var _ajaxUrl;
    var _debug;
    var _subMenusCall;
    var _time = 800;
    var _memoizedHtml = {};

    //Private functions
    var _init = function () {

        _menuObject = new Object(_menuElement, {
            async: {
                url: _ajaxUrl,
                param: ''
            }
        });

        _subMenusCall = null;
        _debug = false;

    };

    var _log = function (msg) {
        if (_debug) {
            console.log(msg);
        }
    }

    var _getSubMenus = function (url, params, callback) {

        _log("_getSubMenus - START");
        var gid = url.split("?gid=")[1] || 0;
        var already_html = _memoizedHtml[gid] || "";
        _subMenusCall = null;
        if (already_html == "") {
            _subMenusCall = jQuery.ajax({
                url: url,
                data: params,
                dataType: 'html',
                success: function (data) {
                    _memoizedHtml[gid] = data;
                    if ("undefined" !== callback && typeof (callback) === "function") {
                        callback(data);
                    }
                },
                always: function (data) {
                    _subMenusCall = null;
                }
            });
        } else if ("undefined" !== callback && typeof (callback) === "function") {
            callback(already_html);
        }
        _log("_getSubMenus - END");
    };

    var _moveToLeft = function () {
        _log("_moveToLeft - START");

        var currentWidth = parseInt(jQuery('div.gf-megamenu').width());
        var maxWidth = parseInt(jQuery('div.gf-megamenu').css("max-width"));

        var elColumn = jQuery('div.gf-megamenu').find('li.menu-item:first');
        var columnWidth = parseInt(jQuery(elColumn).innerWidth());
        
        if(! jQuery('#gf-megamenu-sidebar-left').hasClass('d-none')){
            currentWidth = currentWidth - 20 ;
        }

        if ((currentWidth + columnWidth) > maxWidth) {
            
            //Get column to hide
            var columnToHide = jQuery('div.gf-megamenu').find('li:first').siblings(':visible:not(.gf-megamenu-sidebar):first');
            jQuery(columnToHide).hide();

            /*
             columnToHide.animate({
             opacity: 0.25,
             width: "toggle"
             }, 400, function () {
             // Animation complete.
             });
             
             var options = {
             'effect': 'slide',
             'easing': 'swing',
             'duration' : 1000
             };
             columnToHide.hide(options);
             */

            //display/hide the div with arrow
            _showSideBar('left');
        }
        _log("_moveToLeft - END");

    };

    var _moveToRight = function () {
        _log("_moveToRight - START");

        var currentWidth = parseInt(jQuery('div.gf-megamenu').width());
        var maxWidth = parseInt(jQuery('div.gf-megamenu').css("max-width"));

        var elColumn = jQuery('div.gf-megamenu').find('li.menu-item:first');
        var columnWidth = parseInt(jQuery(elColumn).innerWidth());

        if ((currentWidth - columnWidth) < maxWidth) {
            
            //Get column to hide
            var firstVisibleColumn = jQuery('div.gf-megamenu').find('li:first').siblings(':visible:not(.gf-megamenu-sidebar):first');
            var columnToShow = jQuery(firstVisibleColumn).prev(':not(.gf-megamenu-sidebar)');

            jQuery(columnToShow).show("slow");
            /*
             var options = {
             'effect': 'slide',
             'easing': 'swing',
             'duration' : 1000
             };
             columnToShow.show(options);
             */

            var stillHiddenSiblings = jQuery('div.gf-megamenu').find('li:first').siblings(':hidden:not(.gf-megamenu-sidebar)');
            if (stillHiddenSiblings.length == 0) {
                _hideSideBar('left');
            }
        }
        _log("_moveToRight - END");
    };

    var _hideSideBar = function (side) {
        jQuery('#gf-megamenu-sidebar-' + side).addClass('d-none');
    };

    var _hideSubmenu = function (item, classAlso) {

        _log('_hideSubmenu START');

        var parent_item = jQuery(item).parents('li:first').get(0);

        // remove submenu activation class
        if (classAlso) {
            jQuery(parent_item).removeClass('menu-item-hover');
            jQuery(parent_item).removeClass('menu-item-active-tab');
        }

        // clear timeout
        parent_item.removeAttribute('data-hover');

        if (parent_item.getAttribute('data-menu-toggle-class')) {
            jQuery(parent_item).removeClass(body, item.getAttribute('data-menu-toggle-class'));
        }

        var timeout = parent_item.getAttribute('data-timeout');
        parent_item.removeAttribute('data-timeout');
        clearTimeout(timeout);

        _log('_hideSubmenu END');
    };

    var _showSideBar = function (side) {
        _log('_showSideBar END');
        
        jQuery('#gf-megamenu-sidebar-' + side).removeClass('d-none');
        
        _log('_showSideBar END');
    };

    var _cleanSubMenus = function (submenu_container) {
        _log("_cleanSubMenus - START");
        if (submenu_container.next().length > 0) {

            submenu_container.nextUntil().each(function () {

                if (!jQuery(this).hasClass('gf-megamenu-sidebar') && !jQuery(this).hasClass('gf-megamenu-empty')) {
                    jQuery(this).remove();
                    _moveToRight();
                }
            });
        }
        _log("_cleanSubMenus - END");
    };

    var _onMenuLeave = function (event) {
        _log("_onMenuLeave - START");

        if (event.type == "mouseout") {
            event.stopPropagation();
        }

        if (event.type == "mouseleave" /*&& jQuery(event.target).hasClass('.gf-megamenu') */) {
            event.stopPropagation();
            var item = event.target;

            var parent_item = jQuery(item).parents('li:first').get(0);

            var timeout = setTimeout(function() {
                if ( parent_item.getAttribute('data-hover') == '1' ) {
                    _hideSubmenu(item, true);
                }
            }, _time);

            parent_item.setAttribute('data-hover', '1');
            parent_item.setAttribute('data-timeout', timeout);

        }

        _log("_onMenuLeave - END");
    };

    var _onMenuNavigate = function (event) {

        _log("_onMenuNavigate - START");

        if (event.type == "mouseleave") {

            var currentMenuCol = event.target;
            var target = event.relatedTarget;

            _abortSubMenuCall();

            if (target.tagName != 'LI' || !jQuery(target).hasClass('gf-megamenu-col')) {
                var targetMenuCol = jQuery(target).parents('li.gf-megamenu-col').get(0);
            } else {
                var targetMenuCol = target;
            }

            if (jQuery(currentMenuCol).index() > jQuery(targetMenuCol).index()) {

                var item = event.target;
                var submenu_container = jQuery(item);

                _cleanSubMenus(submenu_container);
            }
        }

        _log("_onMenuNavigate - END");
    }

    var _onMenuHover = function (event) {
        _log("_onMenuHover - START");

        if (event.type == "mouseenter") {

            _abortSubMenuCall();

            var item = event.target;
            var submenu_container = jQuery(item).parent().parent();

            _highlightMenu(item);

            if (jQuery(item).hasClass('menu-item-submenu')) {

                _moveToLeft();
                _loadSubMenu(item);

            } else {
                _cleanSubMenus(submenu_container);  
                _hasSubMenu(item, function(item){
                    //has new submenu => load them
                    jQuery(item).addClass('menu-item-submenu');
                    jQuery(item).find('a.menu-link').append('<i class="menu-arrow"></i>');
                    _loadSubMenu(item);
                });
            }

        } else if (event.type == "mouseleave") {

            _abortSubMenuCall();

        }
        _log("_onMenuHover - END");
    };

    var _hasSubMenu = function(item, callback){
         
        //check if there is submenu
        var gid = jQuery(item).attr("data-gid");
        var params = {};
        var url = _ajaxUrl;

        _getSubMenus(url + '?gid=' + gid, params, function (data) {
            var frag = document.createRange().createContextualFragment(data);
            if(jQuery(frag).find('span.menu-text').length > 0){                
                if(callback != null){
                    callback(item);
                }
            }
        });
    }

    var _addEmptySubMenu = function (item) {

        _log('_addEmptySubMenu - START');

        var submenu_container = jQuery(item).parent().parent();

        if (jQuery(item).hasClass('gf-megamenu-static-submenu')) {
            submenu_container = jQuery(item).parent().parent().next();
        }

        jQuery(submenu_container).after('<li class="gf-megamenu-empty menu-item p-2 overflow-hidden w-275px"></li>');

        _log('_addEmptySubMenu - END');
    }

    var _loadSubMenu = function (item) {
        _log('_loadSubMenu - START');

        var submenu_container = jQuery(item).parent().parent();

        if (jQuery(item).hasClass('gf-megamenu-static-submenu')) {
            _hideSideBar('left');
            submenu_container = jQuery(item).parent().parent().next();
        }

        var gid = jQuery(item).attr("data-gid");
        var elemId = jQuery(item).attr("id");
        var params = {};
        var url = _ajaxUrl;

        _cleanSubMenus(submenu_container);
        if (jQuery(submenu_container).next('.gf-megamenu-empty').length == 0) {
            _addEmptySubMenu(item);
        }

        _getSubMenus(url + '?gid=' + gid, params, function (data) {
            var frag = document.createRange().createContextualFragment(data);
            _attachEvents(frag);
            jQuery(submenu_container).after(frag);
            jQuery('.gf-megamenu-empty').remove();
            
            //load perfect scroll bar
            jQuery('[data-scroll="true"]').each(function() { 
                var el = jQuery(this);
    
                KTUtil.scrollInit(this, {
                    mobileNativeScroll: true,
                    handleWindowResize: true,
                    rememberPosition: (el.data('remember-position') == 'true' ? true : false)
                });
            });
            
        });

        _log('_loadSubMenu - END');

    };

    var _attachEvents = function (submenu_container) {

        _log("_attachEvents - START");

        var menu_container = _menuElement.find('.gf-megamenu');

        $(menu_container).each(function () {
            this.addEventListener("mouseleave", _onMenuLeave, false);
            
            //Required to by-pass Keen (KTMenu) default behaviours
            this.addEventListener("mouseout", _onMenuLeave, false);
        });

        $(menu_container).find('li.gf-megamenu-col').each(function () {
            this.addEventListener("mouseleave", _onMenuNavigate, false);
        });

        $(submenu_container).find('.gf-megamenu-submenu').each(function () {
            this.addEventListener("mouseenter", _onMenuHover, false);
            this.addEventListener("mouseleave", _onMenuHover, false);
        });

        // the hover on the select dropdown is detected as a menu mouseleave, so the block below is here to keep the menu open even if the menu hover is not detected in this case
        const waitForWorfklowsSelectInterval = setInterval(function() {
            if(!$("#gofast_block_delta-gofast_workflows_light_dashboard-gofast_workflows select").length) {
                return;
            }
            // prevent triggering a mouseout event when a select dropdown is open
            $("#gofast_block_delta-gofast_workflows_light_dashboard-gofast_workflows select").on("select2:open", (e) => {
                e.stopPropagation();
                window.GFTopbarMenu.pauseDropdownHoverTime = Infinity;
            });
            // go back to normal behavior when hovering the menu again
            $("#gf-topbar-menu .menu-submenu").on("mouseenter", () => {
                var isSelectOpen = false;
                // Don't close tab is select is still focused
                $("#gofast_block_delta-gofast_workflows_light_dashboard-gofast_workflows select").each((i, el) => {
                    if($(".gofast_wf_profil .gofastSelect2").eq(1).data("select2").isOpen()){
                        isSelectOpen = true;
                        return
                    }
                })
                if(!isSelectOpen){
                    window.GFTopbarMenu.pauseDropdownHoverTime = 0
                }
            });
            // force-hide the menu if clicking outside
            $(document).on("click", (e) => {
                if ($(e.target).closest("#gf-topbar-menu").length) {
                    return;
                }
                window.GFTopbarMenu.pauseDropdownHoverTime = 0;
                window.GFTopbarMenu.hideDropdowns();
            });
            clearInterval(waitForWorfklowsSelectInterval);
        }, 250);

        _log("_attachEvents - END");

    };

    var _highlightMenu = function (item) {
        _log('highlightMenu - START');

        jQuery(item).addClass('menu-item-here');
        jQuery(item).siblings().removeClass('menu-item-here');

        _log('highlightMenu - END');
    };

    var _addClassOnMenuColumns = function (currentNode) {

        if (!currentNode) {
            _menuElement.children('div').children('div').children('ul').children('li').addClass('gf-megamenu-col');
        } else {
            jQuery(currentNode).addClass('gf-megamenu-col');
        }
    }

    var _addSideBars = function () {

        // Build LeftSideBar
        var sideBarLeft = document.createElement("li");
        jQuery(sideBarLeft).attr('id', 'gf-megamenu-sidebar-left');
        jQuery(sideBarLeft).attr("class", "w-20px gf-megamenu-sidebar bg-secondary d-none");

        var sideIconContainer = document.createElement("span");
        jQuery(sideIconContainer).attr("style", "align-items:center;");
        jQuery(sideIconContainer).attr("class", "h-100 d-inline-flex");
        jQuery(sideIconContainer).html('<i class="menu-icon fas n-color fas fa-angle-double-left"></i>');

        sideBarLeft.appendChild(sideIconContainer);

        // Build RightSideBar
//        var sideBarRight = document.createElement("li");
//        jQuery(sideBarRight).attr('id', 'gf-megamenu-sidebar-left');
//        jQuery(sideBarRight).attr("class", "w-20px gf-megamenu-sidebar bg-secondary d-none");
//        
//        var sideIconContainer = document.createElement("span");
//        jQuery(sideIconContainer).attr("style", "align-items:center;");
//        jQuery(sideIconContainer).attr("class", "h-100 d-inline-flex");
//        jQuery(sideIconContainer).html('<i class="menu-icon fas n-color fas fa-angle-double-right"></i>');
//
//        sideBarRight.appendChild(sideIconContainer);


        //Append sideBars to Menu
        jQuery('div.gf-megamenu').find('li:first').after(sideBarLeft);
//        jQuery('div.gf-megamenu').find('li:last').after(sideBarRight);
    }

    var _abortSubMenuCall = function () {

        _log('_abortSubMenuCall - START');

        if (_subMenusCall !== null) {
            _subMenusCall.abort();
            jQuery('.gf-megamenu-empty').remove();
        }

        _log('_abortSubMenuCall - END');
    };

    //Publics methods
    return{
        init: function (menuId, ajaxUrl, options) {
            _menuElement = jQuery(document).find('#' + menuId);
            if (!_menuElement) {
                return;
            }
            _ajaxUrl = ajaxUrl;

            // Initialize menu
            _init();

            _addSideBars();

            _addClassOnMenuColumns();

            _attachEvents(_menuElement);
        },
        getMenuElement: function () {
            return _menuElement;
        },
        getMenu: function () {
            return _menuObject;
        },
        enableDebug: function () {
            _debug = true;
            return _debug;
        },
        loadSubMenu: function(item){
            _loadSubMenu(item);
            return _loadSubMenu;  
        },
        cleanSubMenus: function(item){
            _cleanSubMenus(item.parent().parent());
            return _cleanSubMenus;  
        },
        disableDebug: function () {
            _debug = false;
            return _debug;
        },
        moveToLeft: function () {
            _moveToLeft();
        },
        addSideBars: function () {
            _addSideBars();
        }
    };


}();

function test() {

}


jQuery(document).ready(function () {

    // console.log('GF MEGA MENU LIB LOADED');
    Gofast = Gofast || {};
    GFMegaMenu.init('gf-spaces-menu', '/gofast/menu/get');
    Gofast.spacesMenu = GFMegaMenu;
});


