

/* Dev Test on IE :  
 *   http://msdn.microsoft.com/en-us/library/dd565628(v=vs.85).aspx 
 *   http://msdn.microsoft.com/en-us/library/dd565624(v=vs.85).aspx
 */


function urlDecode(str) {
  return decodeURIComponent((str + '').replace(/\+/g, '%20'));
}


function SelectText(element) {
  var text = document.getElementById(element);
  if ($.browser.msie) {
    var range = document.body.createTextRange();
    range.moveToElementText(text);
    range.select();
  }
  else if ($.browser.mozilla || $.browser.opera) {
    var selection = window.getSelection();
    var range = document.createRange();
    range.selectNodeContents(text);
    selection.removeAllRanges();
    selection.addRange(range);
  }
  else if ($.browser.safari) {
    var selection = window.getSelection();
    selection.setBaseAndExtent(text, 0, text, 1);
  }
} 


(function($){

  /**
   * Returns the text of an element, ignoring all child elements
   * @returns string
   */
  $.fn.getText = function() {
    return this
      .clone()        // clone the element
      .children()     // select all the children
      .remove()       // remove all the children
      .end()          // again go back to selected element
      .text();        // and get text
  };
  
  $.fn.filterByText = function(text) {
    return this.filter(':contains('+ text +')').find('*').filter(function() {
      return $(this).getText().indexOf(text) !== -1;
    });
  }
  
  
  $.fn.exists = function() { return this.length > 0; }
  
    
  /**
   * Center matched element on the screen (relative to the viewport : position 
   * fixed) - or in another element (relative to that element : position 
   * absolute).
   * @param relativeElement If set, matched element is centered inside this 
   * element.
   */
  $.fn.center = function () {
    var winW = getWindowWidth(), winH = getWindowHeight();
    // @TODO : centrer relativement à un élément passé en paramètre.
    // - position absolute / fixed en fonction de la présence d'argument
    // - ignorer arg si = $(window) ou $(document)
    // - prendre en compte yScroll = w.pageYOffset || e.scrollTop || g.scrollTop
    // top : yScroll + (winH - $(this).outerHeight()) / 2    
    return this.css({
      position: 'fixed',
      top:      Math.max(0, (Math.round(winH - $(this).outerHeight()) / 3)) + 'px',
      left:     Math.max(0, (Math.round(winW - $(this).outerWidth()) / 2)) + 'px'
    });
  }

  // Event "destroyed" :
  // -> permet de déclencher du code quand un element est enlevé du DOM
  $.event.special.destroyed = {
    remove: function(o) {
      if (o.handler) {
        o.handler(); // .apply(this,arguments);
        //o.handler.apply(this,arguments);
      }
    }
  }
  
})(jQuery);

    
    
/***** Extend String.prototype *****/

// Create 'capitalize' method
if (!('capitalize' in String.prototype)) {
  String.prototype.capitalize = function() {
    return this.charAt(0).toUpperCase() + this.slice(1);
  }
}

//// Create a string ruler (in px)...
//window.ruler = false;
//String.prototype.visualLength = function(){
//  if (ruler === false) ruler = document.getElementById("str-ruler");
//  ruler.innerHTML = this;
//  return ruler.offsetWidth;  // consumes a large amount of cpu.
//}
//
////// ... so we can properly trim string
////String.prototype.trimToPx = function(length){
////  var tmp = this;
////  var trimmed = this;
////  if (tmp.visualLength() > length){
////    trimmed += "...";
////    while (trimmed.visualLength() > length){
////      tmp = tmp.substring(0, tmp.length-1);
////      trimmed = tmp + "...";
////    }
////  }  
////  return trimmed;
////}
////
////
////Drupal.behaviors.trimString = function(){
////    return;
////    var text, len;
////    $jq('.to-trim:not(.trimmed)').addClass('trimmed').each(function(){
////      var $this = $jq(this);
////      text = $this.text();
////      len = $this.attr('trimLength');
////      if (len) $this.text(text.trimToPx(len));
////    });
////}



/******************************************************************************/
// Add ECMA262-5 method binding if not supported natively
if (!('bind' in Function.prototype)) {
    Function.prototype.bind= function(owner) {
        var that = this;
        if (arguments.length<=1) {
            return function() {
                return that.apply(owner, arguments);
            };
        } else {
            var args = Array.prototype.slice.call(arguments, 1);
            return function() {
                return that.apply(owner, arguments.length===0? args : args.concat(Array.prototype.slice.call(arguments)));
            };
        }
    };
}

// Add ECMA262-5 string trim if not supported natively
if (!('trim' in String.prototype)) {
    String.prototype.trim= function() {
        return this.replace(/^\s+/, '').replace(/\s+$/, '');
    };
}

// Add ECMA262-5 Array methods if not supported natively
if (!('indexOf' in Array.prototype)) {
    Array.prototype.indexOf= function(find, i /*opt*/) {
        if (i===undefined) i= 0;
        if (i<0) i+= this.length;
        if (i<0) i= 0;
        for (var n= this.length; i<n; i++)
            if (i in this && this[i]===find)
                return i;
        return -1;
    };
}

if (!('lastIndexOf' in Array.prototype)) {
    Array.prototype.lastIndexOf= function(find, i /*opt*/) {
        if (i===undefined) i= this.length-1;
        if (i<0) i+= this.length;
        if (i>this.length-1) i= this.length-1;
        for (i++; i-->0;) /* i++ because from-argument is sadly inclusive */
            if (i in this && this[i]===find)
                return i;
        return -1;
    };
}

if (!('forEach' in Array.prototype)) {
    Array.prototype.forEach= function(action, that /*opt*/) {
        for (var i= 0, n= this.length; i<n; i++)
            if (i in this)
                action.call(that, this[i], i, this);
    };
}

if (!('map' in Array.prototype)) {
    Array.prototype.map= function(mapper, that /*opt*/) {
        var other= new Array(this.length);
        for (var i= 0, n= this.length; i<n; i++)
            if (i in this)
                other[i]= mapper.call(that, this[i], i, this);
        return other;
    };
}

if (!('filter' in Array.prototype)) {
    Array.prototype.filter= function(filter, that /*opt*/) {
        var other= [], v;
        for (var i=0, n= this.length; i<n; i++)
            if (i in this && filter.call(that, v= this[i], i, this))
                other.push(v);
        return other;
    };
}

if (!('every' in Array.prototype)) {
    Array.prototype.every= function(tester, that /*opt*/) {
        for (var i= 0, n= this.length; i<n; i++)
            if (i in this && !tester.call(that, this[i], i, this))
                return false;
        return true;
    };
}

if (!('some' in Array.prototype)) {
    Array.prototype.some= function(tester, that /*opt*/) {
        for (var i= 0, n= this.length; i<n; i++)
            if (i in this && tester.call(that, this[i], i, this))
                return true;
        return false;
    };
}

if (!Array.prototype.last) {
    Array.prototype.last = function() {
        return this[this.length - 1];
    }
}


/******************************************************************************/


  // Global var declaration
  var gofast = {
    AjaxFileBrowserLoader : {
      loaded : false
    },
    hdH : 96, // default header height
    // Set goFast views/block property
    privatemsg : {
      privatemsg_bloc_notifications : {
        needRefresh : true,
        firstLoad : true
      },
      privatemsg_bloc : {
        needRefresh : true,
        firstLoad : true
      }
    },
    gofast_flag_bookmarks : {
      block_1 : {
        needRefresh : true,
        firstLoad : true
      }
    },
    aggregator : {
      'category-1' : {
        needRefresh : true,
        firstLoad : true
      }
    },
    workflow : {
      'workflow_bloc' : {
        needRefresh : true,
        firstLoad : true
      },
      'workflow_document_bloc' : {
        needRefresh : true,
        firstLoad : true
      }
    },
    lastClicked : '', // ajaxResponder ??
    pageLoadAsync : false
  };
  
Drupal.settings.gofast = Drupal.settings.gofast || {};
Drupal.settings.gofast.status = Drupal.settings.gofast.status || {};
Drupal.settings.gofast.status.reference = Drupal.settings.gofast.status.reference || {sid: 0, timestamp: new Date().getTime()};
Drupal.settings.drupalMessages = Drupal.settings.drupalMessages || false;

/**
 * Handle highlighting behavior on primary menu links (ajax nav)
 */ 
Drupal.behaviors.menuHighlight = function() {
  var menu = $jq('#primary-menu a:not(.highlight-processed)').addClass('highlight-processed'),
   books_menu = $jq('#adv_book_bloc_div a:not(.highlight-processed)').addClass('highlight-processed');
  menu.click(function() {
    $jq(menu).add(books_menu).removeClass('active');
    $jq(this).add($jq(this).closest('.expanded').find('a:first')).addClass('active');
  });
  books_menu.click(function() {
    $jq(menu).add(books_menu).removeClass('active');
    $jq(this).add($jq('a[href*="books_block_in_menu"]')).addClass('active');
  });
}


function processSidebar () {
  var bloc = $jq('#sidebar-last, #colonne_droite');

  if (!bloc.length) {
    return;
  }
  
  bloc.filter(function() {
    return !($jq(this).hasClass('_fixed') || $jq(this).find('#block-user-0').length > 0);
  }).addClass('_fixed');

  bloc.find('#sidebar-last-inner, #sidebar_fix').not('.scroll_bloc').addClass('scroll_bloc');
  set_bloc_properties();

  // Make the bloc scrollable.
  $jq('.scroll_bloc').not('.scroll-processed').addClass('scroll-processed').mCustomScrollbar({
    horizontalScroll : false,
    scrollInertia    : 0,
    mouseWheelPixels : 40,
    scrollButtons    : {
      enable      : true,
      scrollType  : "continuous",
      scrollSpeed : 25
    },
    advanced         : {
      updateOnBrowserResize: false,
      updateOnContentResize: true
    }
  });

  $jq(window).resize(function(){
    set_bloc_properties();
    $jq('.scroll_bloc.scroll-processed').data("mCS_maxHeight", getWindowHeight() - gofast.hdH - 40);
    $jq('.scroll_bloc.scroll-processed').mCustomScrollbar("update");
  });
}


Drupal.behaviors.processSidebar = function (context) {
  // Si refresh de la vue en ajax on ne fait rien
  if (isview == "true"){
    return;
  }
  
  processSidebar();
};


/**
 * Add possibility to close Drupal message status
 */
Drupal.behaviors.msg_status_close_button = function(context) { 
  // Add a 'close' button on each message
  var msg = $jq('#content-messages .messages, #content-help .help').not('.close_processed').addClass('close_processed');
  $jq('<img class="msg-close-button" src="/sites/all/modules/imce/css/close.png" alt="'+Drupal.t('Close')+'" title="'+Drupal.t('Close')+'"/>').prependTo(msg);
  // Add a click handler on close button
  $jq('.msg-close-button').not('.button-processed').addClass('button-processed').click(function(){
    $jq(this).parent().remove();
    if (!$jq(msg.selector).length) {
      $jq(this).parent().parent().parent().remove();
    }
    // Reset block position
    set_bloc_properties();
  });
};


Drupal.behaviors.toastMessages = function(){
  var messages = Drupal.settings.drupalMessages,
    container = $('#content-messages-inner');
  if (messages) {
    if (container.length) container.prepend(messages);
    else $('#content-group-inner').prepend(wrapDrupalMessage(messages));
    Drupal.settings.drupalMessages = false;
    Drupal.behaviors.msg_status_close_button();
    set_bloc_properties();
  }
}


function wrapDrupalMessage(msg){
  return '<div id="content-top" class="content-top row nested">\n\
    <div id="content-top-inner" class="content-top-inner inner">\n\
    <div id="content-messages" class="content-messages block">\n\
    <div id="content-messages-inner" class="content-messages-inner inner clearfix">'
    + msg + '</div></div></div></div>';
}


$jq(document).ready(function(){
  gofast.hdH = $jq('#gofast-header').height();
  
  // Display or hide status attachments if any in status box.
  setTimeout(function(){
    // Loading attachment may take some time, we check display after a while.
    statusFbsmpDisplay();
  }, 10000);
  

  var currentUrl = $jq(document)[0].URL;
  currentUrl = currentUrl.split('/');
  var n = currentUrl.length;
  // Get url parameters
  var snipUrl = currentUrl[n-1],          
  args = parseURLParams(snipUrl);
  // Remove them from url
  if (args) {
    var index = snipUrl.indexOf("?") !== -1 ? snipUrl.indexOf("?") : snipUrl.indexOf("#");
    snipUrl = index === -1 ? snipUrl : snipUrl.substring(0,index);
  }


/****** CEO-Vision admin interface ******/

  if (snipUrl.indexOf('ceo_vision_admin') !== -1) {

    if (!$('#edit-logo').is(':checked')) {
      $('#edit-logo-upload-ceo-wrapper').css("display","none");
    }
    if (!$('#edit-toggle-image').is(':checked')) {
      $('#edit-user-wallpaper-wrapper').css("display","none");
    }
    
    function CheckLogo() {
      if ($('#edit-logo').is(':checked')) {
        $('#edit-site-name').attr("disabled","disabled");
        $('#edit-logo-upload-ceo-wrapper').show("slow");
      }
      else {
        $('#edit-site-name').removeAttr("disabled");
        $('#edit-logo-upload-ceo-wrapper').hide("slow");
      }
    }
    
    function CheckToggleImage() {
      $('#edit-toggle-image').is(':checked') ?
        $('#edit-user-wallpaper-wrapper').show("slow") :
        $('#edit-user-wallpaper-wrapper').hide("slow");
    }
    
    CheckLogo();
    CheckToggleImage();
    
    $('#edit-logo').click(CheckLogo);
    $('#edit-toggle-image').click(CheckToggleImage);
    
    // TEST LDAP CONNECTION (ldap settings ceo_vision_admin)
    $('#ldap_test_ok').click(function(){
        
        var lang = Drupal.settings.lang ? '/'+Drupal.settings.lang : '',
        ldap_server = $("#edit-ldap-server-adress").val(),
        ldap_port = $("#edit-ldap-port").val(),
        ldap_base_dn = $("#edit-ldap-basedn").val(),
        ldap_bind_dn = $("#edit-ldap-binddn").val(),
        ldap_bind_password  = $("#edit-ldap-bindpw").val();

        $.ajax({
            url:lang+"/ceo_vision_admin/test-ldap",
            data:'ldap_server='+ldap_server+'&ldap_port='+ldap_port+'&ldap_base_dn='+ldap_base_dn+'&ldap_bind_dn='+ldap_bind_dn+'&ldap_bind_password='+ldap_bind_password,
            dataType: 'json',
            success:testLdapConnection
        });
    });

  } // ceo_vision_admin 
  
  
  
  // Remove the fake first leaf menu for group / orga (prevents shadow quirks)
  $('#primary-menu .og_group_menu').each(function(){
    var el = $(this).prev('ul.menu');
    if (el.length) el.remove();
  });
  
  processSidebar();
  
}); // End $jq(document).ready()



Drupal.behaviors.AddJsFilterAnnuaire = function(context){
    /******** Group Directory *********/
 
  //if(currentUrl[n-2].indexOf("og") != -1 && snipUrl == "list_grid") {
  
    var currentUrl = $jq(document)[0].URL;
    currentUrl = currentUrl.split('/');
    var n = currentUrl.length;
    // Get url parameters
    var snipUrl = currentUrl[n-1],
    args = parseURLParams(decodeURIComponent(snipUrl));
  
    if ($jq("#views-exposed-form-og-list-ceo-vision-page-1").size() != 0){
        if ($jq("#views-exposed-form-og-list-ceo-vision-page-1").hasClass("filter_js_processed")){
            return;
        }

      if (args['og_node_type[]'] != "undefined") {
          var og = args['og_node_type[]'] == "group_node" ? "group" : "orga";
          $('.is_selected').removeClass('is_selected');
          $('#og_type_filter_'+og).addClass('is_selected');
      }
       
      // NO FILTER (default)
      $('#og_type_filter_all').click(function(){
          $('.is_selected').removeClass('is_selected');
          $(this).addClass('is_selected');
          $('#edit-og-node-type').children().removeAttr('selected');
          $('#views-exposed-form-og-list-ceo-vision-page-1').submit();
      });
      // FILTERING BY ORGANISATION
      $('#og_type_filter_orga').click(function (){
          $('.is_selected').removeClass('is_selected');
          $(this).addClass('is_selected');
          $('#edit-og-node-type').children().removeAttr('selected');
          $('#edit-og-node-type > option[value="orga"]').attr('selected', 'selected');
          $('#views-exposed-form-og-list-ceo-vision-page-1').submit();
      });
      // FILTERING BY GROUP
      $('#og_type_filter_group').click(function (){
          $('.is_selected').removeClass('is_selected');
          $(this).addClass('is_selected');
          $('#edit-og-node-type').children().removeAttr('selected');
          $('#edit-og-node-type > option[value="group_node"]').attr('selected', 'selected');
          $('#views-exposed-form-og-list-ceo-vision-page-1').submit();
      }); 
      $jq("#views-exposed-form-og-list-ceo-vision-page-1").addClass("filter_js_processed");
  }
  
  
  
   //if(snipUrl == "user_listing_grid"){
    if ($jq("#views-exposed-form-user-grid-listing-page-1").size() != 0){
        if ($jq("#views-exposed-form-user-grid-listing-page-1").hasClass("filter_js_processed")){
            return;
        }
   
        
    // PROFILE GRID VIEWS FILTER
    var b = new Boolean(0);
    var c = new Boolean(0);
    
    // ajaxify  user link 
    var links = $jq("#nom a:not(.ajax-navigate-processed)");
    $.each(links, function(){
        var link = $jq(this).attr('href');
        if (link.length && getUidFromLink(link)) {
            var uid = getUidFromLink(link);
            $jq(this).attr({
               nid: uid,
               uid: 'true'
            });
            $jq(this).attr('class', 'ajax-navigate');
        }
    });
    
    function check_selected() {
        $.each($('.profile_filters'), function(){
          c = $(this).hasClass('is_selected');
          b |= c;
        });
        var all = $('.all_profile_views');
        if (!b){
          all.add(all.parent())
            .addClass('is_selected')
            .attr('title', no_filter[0]);
        } else {
          all.add(all.parent())
            .removeClass('is_selected')
            .attr('title', no_filter[1]);     
        }
        b = 0;
    }
    
    var name_filters = new Array(),
    group_filters = new Array(),
    skill_filters = new Array(),
    no_filter = $('.all_profile_views').attr('title');
    no_filter = no_filter.split('/');
    $('.all_profile_views').parent().addClass('is_selected');
    $('.all_profile_views').attr('title', no_filter[0]);
    
    //if(currentUrl[n-1].indexOf("user_listing_grid?relationships=1") != -1 && currentUrl[n-1].length == 33){
    if (args.relationships == 1) {
        $('.all_profile_views').removeClass('is_selected');
        $('.all_profile_views').attr('title', no_filter[1]);
        $('.my_relations_filter').addClass('is_selected');
        $('#edit-approved > option[value="1"]').attr('selected','selected');
    }
    
    //if(currentUrl[n-1].indexOf("user_listing_grid?value_group=") != -1){
    if (args.value_group){
        $jq('.all_profile_views').removeClass('is_selected');
        $jq('.all_profile_views').attr('title', no_filter[1]);
        //var args = parseURLParams(currentUrl[n-1]);
        $jq('#'+args.value_group).closest('.filters_fieldset').removeClass('collapsed');
        //var type = $('#'+arg.value_group).parents().eq(1);// parents("#orga_fieldset");
        //type.children(".collapse-processed a").click();
        $jq('#'+args.value_group).addClass('is_selected');
        group_filters.push(args.value_group);
        $("#edit-value-group").attr("value", group_filters.join('/'));
    }
    
    // No filter
    $('.all_profile_views').click(function(){
        // Reset filters & Highlights elements
        $('.is_selected').removeClass('is_selected');
        $(this).parent().addClass('is_selected');
        $(this).addClass('is_selected');
        $(this).attr('title', no_filter[0]);
        name_filters = [];
        group_filters = [];
        skill_filters = [];
        $('#edit-approved > option[value="All"]').attr('selected','selected');
        $("#edit-value-alpha").attr("value", '');
        $("#edit-value-group").attr("value", '');
        $('#edit-status > option[value="1"]').attr('selected','selected');
        $("#views-exposed-form-user-grid-listing-page-1").submit();
    });
    
    // Relationships filter
    $('.my_relations_filter').click(function(){
        if ($(this).hasClass('is_selected')){
            $(this).removeClass('is_selected');
            $('#edit-approved > option[value="All"]').attr('selected','selected');
        } else {
            $(this).addClass('is_selected');
            $('#edit-approved > option[value="1"]').attr('selected','selected');
        }
        check_selected();
        $("#views-exposed-form-user-grid-listing-page-1").submit();
    });
    
     // Blocked users filter
    $('.status_filter').click(function(){
        if ($(this).hasClass('is_selected')){
            $(this).removeClass('is_selected');
            $('#edit-status > option[value="1"]').attr('selected','selected');
        } else {
            $(this).addClass('is_selected');
            $('#edit-status > option[value="0"]').attr('selected','selected');
        }
        check_selected();
        $("#views-exposed-form-user-grid-listing-page-1").submit();
    });
    
    // Name filter
    $('.profile_views_name_filter').click(function(){
          if ($(this).hasClass('is_selected')) {
              // Remove filter from array and remove class                      
              var index = name_filters.indexOf($(this).html().replace(/-/g,','));
              name_filters.splice(index, 1);
              $(this).removeClass('is_selected'); 
          } else {
              // Add filter & class
              name_filters.push($(this).html().replace(/-/g,','));
              $(this).addClass('is_selected');
          }
          check_selected();
          $("#edit-value-alpha").attr("value", name_filters);
          $("#views-exposed-form-user-grid-listing-page-1").submit();
      });
      
    // Group filter
    $('.profile_views_group_filter').click(function(){
         if ($(this).hasClass('is_selected')) {
              // Remove filter from array and remove class                      
              var index = group_filters.indexOf($(this).attr("id"));
              group_filters.splice(index, 1);
              $(this).removeClass('is_selected'); 
          } else {
              // Add filter & class
              group_filters.push($(this).attr("id"));
              $(this).addClass('is_selected');
          }
          check_selected();
          $("#edit-value-group").attr("value", group_filters.join('/'));
          $("#views-exposed-form-user-grid-listing-page-1").submit();
      });
      
    // Skill filter
    $('.profile_views_skill_filter').click(function(){
          if ($(this).hasClass('is_selected')) {
              // Remove filter from array and remove class                      
              var index = skill_filters.indexOf($(this).attr("id"));
              skill_filters.splice(index, 1);
              $(this).removeClass('is_selected'); 
          } else {
              // Add filter & class
              skill_filters.push($(this).attr("id"));
              $(this).addClass('is_selected');
              //$("#edit-value-skill").attr("value", group_filters.join('/'));
          }
          check_selected();
          $("#views-exposed-form-user-grid-listing-page-1").submit();
      });
      
    // SUBMIT 
    $("#views-exposed-form-user-grid-listing-page-1").submit(function(){
          gofastAddLoading();
           if (skill_filters.length > 0) {
             // Create a cookie to retrieve skills filter data in ceo_vision_ui_views_query_alter()
             var filter_values = skill_filters.join(",");
             setCookie("skills", filter_values, 5);
          }
          else { 
            setCookie("skills", 0, 5);
          }  
      });
      
     $jq("#views-exposed-form-user-grid-listing-page-1").addClass("filter_js_processed");
  } //End - PROFILE GRID VIEWS FILTER
}



Drupal.behaviors.userDirectory = function(context){
  
      // Tag blocked accounts
      $jq(".locked_status_True").text(Drupal.t('Blocked'));
      // Ajax link transform (user profile view)
      $jq("#nom a:not(.ajax-navigate-processed)").addClass('ajax-navigate-processed').each(function(){
          var link = $jq(this).attr('href'),
          uid = getUidFromLink(link);
          if(link.length && uid) {
             $jq(this).attr({
               nid : uid,
               uid : 'true'
             });
             $jq(this).click(function () {
                if (uid == 'undefined') {
                   location.href = $jq(this).attr('href'); 
                }
                try{
                    YAHOO.util.History.navigate('q', "user/"+uid); 
                }
                catch(err){
                  location.href("/node/"+uid);
                }
                return false;
             });
          }        
      });
};


// ***** FIL D'ACTIVITÉ *****

Drupal.behaviors.filteringActivityThread = function(context){
    if (!$(".view-display-id-block_3").length || $('#block-ceo_vision_ajax_navigate-0').hasClass('filters-processed')){
      return;
    }
    
    // Init variables
    var contentByGroup = new Array();
    var contentByStatus = new Array();

    if($('#edit-username').val() != null && $('#edit-username').val() != ''){
        $('.all_contents_filter').removeClass('is_selected');
        $('.my_contents_filter').addClass('is_selected');
    }
    if($('#edit-private').val() == 0) {
        $('.all_contents_filter').removeClass('is_selected');
        $('.public_contents_filter').addClass('is_selected');
    }
    if($('#edit-group-nid').val() != null && $('#edit-private').val() != 0){
        $('.all_contents_filter').removeClass('is_selected');
        contentByGroup = $('#edit-group-nid').val();
        $.each(contentByGroup, function(){
            $('#'+this).addClass('is_selected');
            // Uncollapse parent fieldset if exists
            $($($('#'+this).parent()).parent()).removeClass('collapsed');
        });
    }
    if($('#edit-status').val() != null && $('#edit-status').val() != ''){
        $('.all_contents_filter').removeClass('is_selected');
        var statusStr = $('#edit-status').val();
        contentByStatus = statusStr.split(',');
        $.each(contentByStatus, function(){
            $jq("[id='"+this+"']").addClass('is_selected');
        });
        // Uncollapse parent fieldset
        $('#status_content').removeClass('collapsed');
        $('#status_content > div.fieldset-wrapper').css('display','block;')
    }


    // All Contents
    $('.all_contents_filter').click(function(){
        // Reset filters, highlight element
        $('.is_selected').removeClass('is_selected');
        $(this).addClass('is_selected');
        $('#edit-group-nid').children().removeAttr('selected');
        $('#edit-username').attr('value','');
        $('#edit-private > option[value="All"]').attr('selected','selected');
        $('#edit-status').attr('value', '');
        //$('#edit-group-nid-op > option').removeAttr('selected');
        $('#edit-group-nid-op > option[value="or"]').attr('selected','selected');
        contentByGroup = [];
        contentByStatus = [];
//        $('#views-exposed-form-og-tracker-ceo-vision-block-3').submit();
        formSubmit($('#views-exposed-form-og-tracker-ceo-vision-block-3'), 'contentsActivity_formState');
    });

    // My content
    $('.my_contents_filter').click(function(){
        if($(this).hasClass('is_selected')){
            $(this).removeClass('is_selected');
            $('#edit-username').attr('value','');
            if(contentByGroup.length < 1 && contentByStatus.length < 1 && $('.public_contents_filter').hasClass('is_selected') == false){
              $('.all_contents_filter').addClass('is_selected');
            }
        }
        else{
            $('.all_contents_filter').removeClass('is_selected');
            $(this).addClass('is_selected');
            $('#edit-username').attr('value', $(this).attr('id'));
        }
        formSubmit($('#views-exposed-form-og-tracker-ceo-vision-block-3'), 'contentsActivity_formState');
    });

    // Public Contents
    $('.public_contents_filter').click(function(){
        if($(this).hasClass('is_selected')) {
            $(this).removeClass('is_selected');
            // reset og filter
            $('#edit-private > option[value="All"]').attr('selected','selected');
            $('#edit-group-nid').children().removeAttr('selected');
            $('#edit-group-nid-op > option[value="or"]').attr('selected','selected');
            // Highlight "All contents" filter if no filter is set 
            if($('.my_contents_filter, .og_contents_filter, status_content_filter').hasClass('is_selected') == false) {
                $('.all_contents_filter').addClass('is_selected');
            }
        }
        else{
            $(this).addClass('is_selected');
            $('.all_contents_filter, .og_contents_filter').removeClass('is_selected');
            contentByGroup = [];
            // Desactivate group filters (reverse operator & select all groups, no private)
            $('#edit-private > option[value="0"]').attr('selected','selected');
            // $('#edit-group-nid').removeAttr('selected');
            $('#edit-group-nid').children().attr('selected','selected');
            $('#edit-group-nid-op > option[value="not"]').attr('selected','selected');
        }
        formSubmit($('#views-exposed-form-og-tracker-ceo-vision-block-3'), 'contentsActivity_formState');
    });

    $('.og_contents_filter').click(function(){
        if($(this).hasClass('is_selected')) {
            // Remove filter from array and remove class
            var index = contentByGroup.indexOf($(this).attr("id"));
            contentByGroup.splice(index, 1);
            $(this).removeClass('is_selected'); 
            // Highlight "All contents" filter if no filter is set 
            if(contentByGroup.length < 1 && contentByStatus.length < 1 && $('.my_contents_filter').hasClass('is_selected') == false) {
                $('.all_contents_filter').addClass('is_selected');
            }
        }else{
            $(this).addClass('is_selected');
            $('.all_contents_filter, .public_contents_filter').removeClass('is_selected');
            // Check filters
            $('#edit-private > option[value="All"]').attr('selected','selected');
            $('#edit-group-nid').children().removeAttr('selected');
            $('#edit-group-nid-op > option[value="or"]').attr('selected','selected');
            contentByGroup.push($(this).attr("id"));
        }
        // foreach selected group, set attribute
        $('#edit-group-nid').children().removeAttr('selected');
        contentByGroup.forEach(function(id){                                     
            $('#edit-group-nid > option[value="'+id+'"]').attr('selected','selected');
        });
        formSubmit($('#views-exposed-form-og-tracker-ceo-vision-block-3'), 'contentsActivity_formState');
    });

    // Contents by Status
    $('.status_contents_filter').click(function(){
        if($(this).hasClass('is_selected')) {
            // Remove filter from array and remove class                    
            var index = contentByStatus.indexOf($(this).attr("id"));
            contentByStatus.splice(index, 1);
            $(this).removeClass('is_selected');
            // Highlight "All contents" filter if no filter is set 
            if(contentByGroup.length < 1 && contentByStatus.length < 1 && $('.my_contents_filter').hasClass('is_selected') == false){
                $('.all_contents_filter').addClass('is_selected');
            }
        }
        else{
            $(this).addClass('is_selected');
            $('.all_contents_filter').removeClass('is_selected');
            contentByStatus.push($(this).attr("id"));
        }
        contentByGroup.forEach(function(id){
            $('#edit-group-nid > option[value="'+id+'"]').attr('selected','selected');
        });
        $('#edit-status').attr('value', contentByStatus);
        formSubmit($('#views-exposed-form-og-tracker-ceo-vision-block-3'), 'contentsActivity_formState');
    });
    
    $('#block-ceo_vision_ajax_navigate-0').addClass('filters-processed');
};



Drupal.behaviors.booksMenuConstruct = function () {
    //si refresh d'une vue en ajax on ne fait rien
    if (isview == "true"){
      return;
    }
    
    var book_primary_link = $jq('a[href*="books_block_in_menu"]'),
     books_menu = book_primary_link.parent();
    
    if (books_menu.length === 0 || books_menu.hasClass('hover-book-processed')) {
      return;
    }
      
    var books = $jq("#adv_book_bloc_div"),
    maxHeight = getWindowHeight() - gofast.hdH - 30; // minimal windows height (768px) - header height (96px)

    if ($jq.browser.msie  && parseInt($jq.browser.version, 10) === 8) {
      books.css('width', '300px');
      gofast.hdH = $jq('#gofast-header').height();
    }

    books.not('.scroll-processed').addClass('scroll-processed adv-book-block-menu').mCustomScrollbar({
      horizontalScroll : false,
      scrollInertia    : 0,
      mouseWheelPixels : 40,
      scrollButtons    : {
        enable         : true,
        scrollType     : "continuous",
        scrollSpeed    : 25
      },
      advanced         : {
        updateOnBrowserResize: false,
        updateOnContentResize: true
      }
    });

    $jq('.mCustomScrollBox').css('max-height', maxHeight+'px');
    books.filter('.scroll-processed').mCustomScrollbar("update");

    $jq(window).resize(function(){
      // Update maxHeight & scroll
      maxHeight = getWindowHeight() - gofast.hdH - 30;
      books.filter('.scroll-processed').data("mCS_maxHeight", maxHeight);
      books.filter('.scroll-processed').mCustomScrollbar("update");
    });

    book_primary_link.click(function(e){
        e.preventDefault();
    });

    var el = books_menu.add(books),
    books_y = gofast.hdH - 1;

    el.hover(
        function(){
            var books_x = books_menu.offset().left;
            books.css({
                'display' : 'block',
                'top' : books_y + 'px',
                'left' : books_x + 'px',
                'max-height' : maxHeight + 'px'
            });
            books_menu.addClass('ceov_box_shadow').css('background-color', gofast_background_header_menu_css);
        },
        function(){
            books.css('display', 'none');
            books_menu.removeClass('ceov_box_shadow').css('background-color', gofast_background_header_settings_css);
        }
    );

    books_menu.addClass('hover-book-processed');
};



Drupal.behaviors.scroolToAnchor = function (context) {
  $jq('.scrolltoanchor:not(.scrolltoanchor-processed)').addClass('scrolltoanchor-processed').click(function(e){
      e.preventDefault();
      scrollToAnchor(this);
  });
};


function scrollToAnchor(el, relative){
  var target = '#' + $jq(el).attr('anchor');
  // Get the top offset of the target anchor
  if ($jq(target).length == 1) {
    var target_top = $jq(target).offset().top;
    if (relative) {
      // Offset must be relative to the header's height
      target_top -= gofast.hdH + 10;
    }
    // Goto that anchor by setting the body scroll top to anchor top
    $jq('html, body').animate({scrollTop:target_top}, 500);
  } else {
    var descendant = $jq('span[anchor="' + $jq(el).attr('anchor') + '"]').parent();
    while(!descendant.hasClass("toc")){
      descendant = descendant.parent();
    }
    var nid = descendant.attr("id").replace("toc_", "");
    YAHOO.util.History.navigate('q', "node/"+nid);
    $jq("#node-" + nid).waitUntilExists(function() {
      scrollToAnchor(el, relative);
    });
  }
}


Drupal.behaviors.iframeResize = function () {
    var winH = getWindowHeight() - gofast.hdH - 70;
    $('#content_node iframe:not(.resized)').addClass('resized').attr('height', winH);
};



/* PDF plugin bug fix for IE */
if ($jq.browser.msie && parseInt($jq.browser.version, 10) === 8) {
  Drupal.behaviors.pdfBugFixIE = function() {
    
    var pdf = $('#pdf_frame'),
     elements = $(' .primary-links-grid ul a, #adv_book_bloc_div, .gofast-block');
 
    if (pdf.length) {
      var hidePdf = function() { pdf.css('visibility', 'hidden'); },
      showPdf = function() { if ($('#modalContent').length === 0) { pdf.css('visibility', 'visible'); } }
      checkOffset = function() {
        // Hide pdf iframe if it is over header
        $(window).scrollTop() + gofast.hdH > pdf.offset().top ? hidePdf() : showPdf();
      };
      checkOffset();
      // Hide pdf iframe when hovering over nav links
      elements.not('.pdf-ie-fixed').addClass('pdf-ie-fixed').bind('mouseenter', hidePdf).bind('mouseleave', showPdf);
      // Check offset & hide iframe when scrolling down
      $(window).bind('scroll', checkOffset);
    } 
    // S'il n'y a pas d'iFrame on s'assure que les handlers ne soient plus appelés.
    else if ($('.pdf-ie-fixed').length) {
      // Unbind events 
      $('.pdf-ie-fixed').removeClass('pdf-ie-fixed').unbind('mouseenter', hidePdf).unbind('mouseleave', showPdf);
      $(window).unbind('scroll', checkOffset);
    }
  };
}


Drupal.behaviors.nodeAccesLink = function(context){
    $jq(context).find('a.access-denied:not(.access-processed)').addClass('access-processed').click(function(e){
      e.preventDefault();
      var tip = $jq('<div class="gofast-tool-tip" style="margin:5px 0;">'+Drupal.t('You are not authorized to access this page.')+'</div>');
      $jq(this).after(tip);
      tip.slideToggle().delay(3000).slideToggle();
    });
};



function setCookie(name, value, expiration) {
   if (typeof expiration === 'undefined') expiration = 0;
   var date = new Date();
   date.setTime(date.getTime() + (expiration * 1000));
   var expires = '; expires=' + date.toGMTString();
   document.cookie = name + '=' + value + expires + '; path=/';
}



function getCookie(c_name){
  var i, x ,y, ARRcookies = document.cookie.split(";");
  for (i=0; i < ARRcookies.length; i++) {
    x = ARRcookies[i].substr(0,ARRcookies[i].indexOf("="));
    y = ARRcookies[i].substr(ARRcookies[i].indexOf("=")+1);
    x = x.replace(/^\s+|\s+$/g,"");
    if (x == c_name) {
      return unescape(y);
    }
  }
  return false;
}


function deletecookie(name, path) {
  if (typeof path === 'undefined') path = '/';
  document.cookie = name + '=; expires=Thu, 01 Jan 1970 00:00:01 GMT; path=' + path;
}


function testLdapConnection(data){
    if (data.connection == true) {
        $("#ldap_connect_success").css('color','green').html(Drupal.t("Connection performs successfully..."));
    }
    else {
        $("#ldap_connect_success").css('color','red').html(Drupal.t("Connection fails..."));
    }
}


/** Form Submit Function 
 *  $("#form_ID").submit() sometimes does not run as expected
 */
function formSubmit(form, cookieName) {
    if(cookieName) {
        // Serializing form & put the form state in a cookie
        var formState = form.serialize();
        setCookie(cookieName, formState, 31536000);
    }
    gofastAddLoading();
    form.submit();
}


function formInit(selector, cookieName) {
    // get serialized string from cookie    
   var cookieData = getCookie(cookieName);
   // if cookie exists continue
   if (cookieData != null) {
        //alert(cookieData);
        // split cookieData string into an array of fields and their values
        var cookieArray = cookieData.split('&');
        // go through each field and split it too to get field name and it's value
        $.each(cookieArray, function(k, v) {
          var field = v.split('=');
          // populate field with data
          $(selector+' [name="'+field[0]+'"]').val(urlDecode(field[1]));
        });
//        $(selector).submit();
    }
    return false;
}


function parseURLParams(url) {
  var queryStart = url.indexOf("?") + 1;
  var queryEnd   = url.indexOf("#") + 1 || url.length + 1;
  var query      = url.slice(queryStart, queryEnd - 1);

  if (query === url || query === "") return false;

  var params  = {};
  var nvPairs = query.replace(/\+/g, " ").split("&");

  for (var i=0; i<nvPairs.length; i++) {
    var nv = nvPairs[i].split("=");
    var n  = decodeURIComponent(nv[0]);
    var v  = decodeURIComponent(nv[1]);
    if ( !(n in params) ) {
      params[n] = [];
    }
    params[n].push(nv.length === 2 ? v : null);
  }
  return params;
}


//function loadSubmit() {
//  var ProgressImage = document.getElementById('progress_image');
//  document.getElementById('progress').style.display = 'block';
//  setTimeout(function(){ProgressImage.src = ProgressImage.src},100);
//  return true;
//}


function set_bloc_properties(){
  var main_offset = $jq('#content-region').offset() || $jq('#main').offset();
  if (!main_offset) return;

  var winH = getWindowHeight(),
   scroll_bloc_height = Math.round(winH - main_offset.top - 30), //getWindowHeight() - gofast.hdH -40,
   fixed_bloc_x = Math.round(main_offset.left + 780), // 780 : content width
   scrollRight = getWindowWidth() < 1060 ? '35px' : '15px',
   pdf_frame = $jq("#pdf_frame");

  $jq('#sidebar-last._fixed, #colonne_droite._fixed').css({'left': fixed_bloc_x + 'px', 'top' : main_offset.top + 'px'});
  $jq('#sidebar-last-inner.sidebar-last-inner.inner.clearfix.scroll_bloc, #sidebar_fix.scroll_bloc, .mCustomScrollBox').css('max-height', scroll_bloc_height + 'px');

  if ($jq("#colonne_droite").css("display") == "none"){
    pdf_frame.attr('height', winH - 50);
  }
  else{
    pdf_frame.attr('height', scroll_bloc_height - 35);
  }

  $jq('.scroll_bloc .mCustomScrollBox .mCSB_scrollTools').css('right', scrollRight);
}


function printStackTrace() {
  var callstack = [];
  var isCallstackPopulated = false;
  try {
    i.dont.exist+=0; //doesn't exist- that's the point
  } catch(e) {
    if (e.stack) { //Firefox
      var lines = e.stack.split('\n');
      for (var i=0, len=lines.length; i<len; i++) {
        if (lines[i].match(/^\s*[A-Za-z0-9\-_\$]+\(/)) {
          callstack.push(lines[i]);
        }
      }
      //Remove call to printStackTrace()
      callstack.shift();
      isCallstackPopulated = true;
    }
    else if (window.opera && e.message) { //Opera
      var lines = e.message.split('\n');
      for (var i=0, len=lines.length; i<len; i++) {
        if (lines[i].match(/^\s*[A-Za-z0-9\-_\$]+\(/)) {
          var entry = lines[i];
          //Append next line also since it has the file info
          if (lines[i+1]) {
            entry += " at " + lines[i+1];
            i++;
          }
          callstack.push(entry);
        }
      }
      //Remove call to printStackTrace()
      callstack.shift();
      isCallstackPopulated = true;
    }
  }
  if (!isCallstackPopulated) { //IE and Safari
    var currentFunction = arguments.callee.caller;
    while (currentFunction) {
      var fn = currentFunction.toString();
      var fname = fn.substring(fn.indexOf("function") + 8, fn.indexOf('')) || 'anonymous';
      callstack.push(fname);
      currentFunction = currentFunction.caller;
    }
  }
  output(callstack);
}

function output(arr) {
  // Output however you want
  alert(arr.join('\n\n'));
}


function getUidFromLink(link){
    //alert(link);
    var arr = link.split('/'),
    n = arr[arr.length-1];
    if(arr[arr.length-2] == "user"){
        return n;
    }
    else{
        return false;
        // ou chercher mieux dans l'url..
    }
}


  /***** Facebook Status Box Behavior *****/

  // Extends gofast settings
  gofast.inStatusBox = 0;
  gofast.statusViewPage = 1;
  gofast.statusRefreshTime = 30000;
  gofast.statusBoxTimer = new Date().getTime() - gofast.statusRefreshTime;
  gofast.statusSubmitting = 0;  // true while saving a status
  gofast.statusLoadingMore = 0; // true while loading more items -> prevents callback function from looping
  gofast.statusIsNew = false;
  gofast.statusReference = {
    sid: 0, // reference from the last updated item in user' status stream view, needed to compare against last submitted status
    timestamp: new Date().getTime()
  };

Drupal.behaviors.statusBlock = function(context){

    var statusBlock = $jq('#block-ceo_vision_admin-gofast-status:not(.status-block-processed)').addClass('status-block-processed');
    if (!statusBlock.length) return;
    
    // Reset max-height while resizing window
    $jq(window).resize(function(){
      statusBlockSetMaxHeight();
    });
    
    // Mouse event handlers : Show/hide the statuses stream view.
    var statusOnMouseOver = function() {
      gofast.inStatusBox = 1;
      // Show attachment (it should be hidden) unless the form is focused 
      if (!$jq(this).find('*:focus').length > 0 && $jq('#fbsmp-wrapper-replace').css('display') === 'none') {
        $jq('#my-last-status .fbsmp').css('display','block');
      }
      if (!gofast.statusSubmitting) {
        // Reset height of status box
        $jq('#my-last-status .facebook-status-item').height() > gofast.hdH ?
        $jq('#my-last-status').css('height','auto') : $jq('#my-last-status').css('height',gofast.hdH);
        // Show the appropriate view & refresh if needed
        statusShowView();
      }
    },
            
    statusOnMouseOut = function(){
      gofast.inStatusBox = 0;
      // If a textarea has focus when mouse goes outside the block, do nothing 
      // until that element blur, else hide status view.
      if (!$jq(this).find('*:focus').length > 0 && $jq('#fbsmp-wrapper-replace').css('display') == 'none') {
        $jq('#gofast-status-view').css('display', 'none');
        $jq('#my-last-status').css('height', gofast.hdH);
        statusFbsmpDisplay();
      }
    },
            
    // hoverIntent settings :
    config = {sensitivity: 4, interval: 80, over: statusOnMouseOver, timeout: 250, out: statusOnMouseOut};
    
    // Attach handlers to hoverIntent events for the statusBlock.
    $(statusBlock).hoverIntent(config);
        
    // Adjust hovering behavior with click() events.
    $jq('html').click(function(){
      if ($jq('#gofast-status-view').css('display') !== 'none'){
        // Hide elements.
        $jq('#gofast-status-view').css('display','none');
        $jq('#my-last-status').css('height', gofast.hdH);
        // Leave focus.
        $jq('[id*="facebook-status-box"]').blur();
        statusFbsmpDisplay();
      }
    });
    
    // Don't run the function above if the clicked element is the status block.
    statusBlock.click(function(event){
      event.stopPropagation();
    });
    
/* Commented if we use mCustomScrollbar()
    // Auto-load more items when scroll reaches the bottom of the view.
    var view = $jq('#gofast-status-view .view-content'),
    lastScroll = view.scrollTop();
    
    view.scroll(function(){
      var currentScroll = $(this).scrollTop();
      if (currentScroll > lastScroll){
        // Scrolling Down
        if(currentScroll + $jq(this).height() > $jq(this).find('.views-table').height() - 50) {
          // Reaching bottom -> load more items 
          // Unbind scroll event prevents multiple runs of this function
          $jq(this).unbind('scroll');
          statusLoadMore();
          setTimeout(function(){
            view.bind('scroll');
          }, 3000);
        }        
      }
      lastScroll = currentScroll;
    });
/**/
    if (!$jq('#block-ceo_vision_admin-gofast-status .ajax-loader').length) {
      // Insert ajax loader to display while loading more items
      var load = '<div class="ajax-loader"></div>';
      $jq(load).insertAfter($jq('#gofast-status-view'));
      
      // Insert text to display when all items are already loaded.
      $jq('<div class="no-item">'+Drupal.t('No more item.')+'</div>')
        .insertAfter($jq('#gofast-status-view'));
    }
};



Drupal.behaviors.statusScrollBar = function(){
  var $block = $jq('#gofast-status-view .view-content:not(.scroll-processed)');
  
  if (!$block.length) {
     return;
  }
  
  $block.addClass('scroll-processed').mCustomScrollbar({
    horizontalScroll : false,
    scrollInertia    : 0,
    mouseWheelPixels : 40,
    scrollButtons    : {
      enable      : true,
      scrollType  : "continuous",
      scrollSpeed : 25
    },
    advanced         : {
      updateOnBrowserResize: false,
      updateOnContentResize: true
    },
    callbacks        : {
      onTotalScroll: function(){
        // gofast.statusLoadingMore prevents callback function from looping.
        if (!gofast.statusLoadingMore) statusLoadMore();
      }
    }
  });
  // Resize event is handled in statusBlock() behavior
};


//Drupal.behaviors.statusAddStatusButton = function(context){
//    if($jq('.add-button').length != 0) return;
//    var button = '<div class="add-button"></div>',
//    img = '<img alt="'+Drupal.t('Add a status')+'" src="/drupal/sites/all/themes/fusion/fusion_starter/img/new/add2.png">';
//    $jq(button).html(img).insertBefore('#my-last-status .facebook-status-participants');
//}


Drupal.behaviors.statusAddStatus = function(context){
    if($jq('.add-button').length != 0) return;
    var add = '<div class="add-button">'+Drupal.t('Add')+'</div>';
    $jq(add).insertBefore('#my-last-status .facebook-status-participants');
};



Drupal.behaviors.statusBox = function(context) {
    
    var box = $jq('#my-last-status');
    if (isview == "true" || box.hasClass('fbss-box-processed'))
      return;

    statusFbsmpDisplay();
    
    // Replace remaining chars utility
    box.find('.facebook-status-chars').insertAfter(box.find('#fbsmp-wrapper-replace'));

    // Add tooltip in status box, define click handler
    box.find('.facebook-status-content, .add-button')
      .attr('title', Drupal.t('Click to add a new status'))
      .click(function(){
        statusShowForm();
      });

    $jq('#gofast-status-view').click(function(event){
      event.stopPropagation();
      if ($jq(event.target).prop('tagName') == 'A') return;
      $jq('[id*="facebook-status-box"]').blur();
    });
    
    $jq('#my-last-status .facebook-status-item').height() > gofast.hdH ?
      box.css('height','auto') :
      box.css('height',gofast.hdH);
    
    box.addClass('fbss-box-processed');
};



Drupal.behaviors.statusBoxForm = function(context) {
    
    if($jq('#my-last-status form').hasClass('fbss-form-processed')) return;

    // Add secondary submit button 
    var button = $jq('<div class="gofast-button" id="replacement-button">'+Drupal.t('Publish')+'</div>')
      .insertAfter('#my-last-status .fbsmp-wrapper-outer')
      .css('display','none');
      
    // Form submit
    button.click(function(){
        
      gofast.statusSubmitting = 1;
      var form = $(this).parents('form'),
      element = form.find('.facebook-status-submit');
      
      // Check remaining characters count. If negative, no submit.
      var remaining = parseInt($jq('.facebook-status-chars').text(), 10);
      
      if (remaining >= 0){
        // Submit the form (via AHAH if possible)
        if (Drupal.settings.ahah && Drupal.settings.ahah[element[0].id]) {
          element.trigger(Drupal.settings.ahah[element[0].id].event);
          statusSubmitOp();
        }
        else {
          form.submit();
        }
      } else {
        // Notice user that his message is too long.
        statusMessageIsTooLong(remaining); 
      }
      gofast.statusSubmitting = 0;
    });
    
    // KeyPress event
    $jq('#my-last-status textarea').bind('keypress', function(e){
      // Escape form
      if (e.keyCode == '27') {
        e.preventDefault();
        $jq(e.target).blur();
      }
      // Shift+Enter -> submit form (cf. facebook_enter.js) + refresh all
      if (e.keyCode == '13' && e.shiftKey) {
        gofast.statusSubmitting = 1;
        // Running facebook_status_enter.js (behavior+patch) :
        // - statusSubmitOp();
        // - gofast.statusSubmitting = 0;
      }
    });
    
    // Replace 'file' button (image upload) sauf pour IE & Opera car echec upload -> cf fbsmp/plugins/photo.inc
    $jq('#my-last-status #fbsmp-wrapper-replace').delegate('#upload-img-button', 'click', function(){
      //$jq('[id*="facebook-status-box"]').attr('enctype', 'multipart/form-data');
      $jq('#my-last-status #edit-fbsmp-photo-upload').click();
    });
    
    // Filename display when a file is selected
    $jq('#my-last-status #fbsmp-wrapper-replace').delegate('#edit-fbsmp-photo-upload', 'change', function(){
      var file = $jq('#edit-fbsmp-photo-upload').val();
      $jq('#my-last-status #upload-img-button').text(file);
      $jq('#my-last-status #upload-img-button').hover(
        function(){$jq(this).text(Drupal.t('Choose a file ...'));},
        function(){$jq(this).text(file);}
      );
    });
    
    $jq('#my-last-status form').blur(function(){
      $jq(this).find('textarea, #fbsmp-wrapper-replace:first, .facebook-status-chars').add(button).css('display','none');
      $jq(this).siblings().add($jq('#my-last-status .facebook-status-sender-picture')).css('display', 'block');
      statusBlockSetMaxHeight();
    });
    
    $jq('#my-last-status form').addClass('fbss-form-processed');
};



Drupal.behaviors.linkAutoComplete = function(context){
   $jq(context).find('#autocomplete li').each(function(){
     $jq(this).attr('title', $jq(this).text());
   });
}


/**
 * Autocompletion pour les destinataires d'un mail / messages
 * UI : Les suggestions séléctionnées (les adresses/noms/groupes) se 
 * transforment en items cliquable (suppressible)
 */
Drupal.behaviors.labelize = function(context){  
  var labelize = {},
   select = function(data) {
    data = data.data || data;
    
    var value = $jq(this).get(0).autocompleteValue || this.defaultValue,
      autocomplete = data.autocomplete,
      form = data.form,
      values = data.values;

    autocomplete.val('').focus();
    
    if (!$jq('.selection-tags', form).length) {
      $jq('<div class="selection-tags"></div>').insertAfter(autocomplete);
    }      
    if (values.indexOf(value) === -1) {

      values.push(value);
      var title = value.indexOf('og|members|@') !== -1 ? Drupal.t('Members of') + ' ' + value.replace(/<.*>/g, '') : value;
      title = 'title="' + title + '"';
      var item = '<span class="tagging-tag processed"' + title + '>' + value + '</span>';
      $jq('.selection-tags', form).append(item);
      // Add a click event handler that enables user to remove this item
      $jq('.tagging-tag.processed:not(.remove)').addClass('remove').click(function() {
        var index = values.indexOf(value);
        if (index !== -1) values.splice(index, 1);
        $jq(this).remove();
        autocomplete.focus();
      });
    }
  },

  prevent = function(e) {
    var autocomplete = e.data.autocomplete,
    form = e.data.form;
    console.log(e.data);
    // Prevents wrong behaviors induced by wrong click events
    if (e.which === 2 || e.which === 3) {      
      e.preventDefault();
      autocomplete.val('');
      $jq('#autocomplete li.selected', form).removeClass('selected');
    }    
    // Prevents double-click to fill twice
    setTimeout(function(){ autocomplete.val('');}, 200);
  },

  onSubmit = function(e) {
    var address = [], 
      pattern = e.data.autocomplete.hasClass('pm') ? new RegExp('.*?<(.+)>', 'g') : new RegExp('.*?<(.+@.+)>', 'g');
    for (var i = 0, j = e.data.values.length; i < j; i++) {
      address.push((e.data.values[i]).replace(pattern, '$1'));
    }
    $jq('#edit-addrs-hidden', e.data.form).val(address.join());
  };


  // Bind events to handlers for each instances of a labelized text input
  $jq('input.labelize-autocomplete').each(function(){
    var autocomplete = $jq(this),
      form = $jq(this).closest('form'),
      values = [],
      data = {
        autocomplete  : autocomplete,
        form          : form,
        values        : values
      };
    // Labelize default value if set
    if (autocomplete.hasClass('labelizeDefault')) {
      // Allow time for the popup to be resized in the first place
      setTimeout(function(){
        var def = autocomplete.val();
        select.call({defaultValue: def}, data);
        autocomplete.removeClass('labelizeDefault');        
      }, 200);
    }
    form.not('.labelized').addClass('labelized')  
      .submit(data, onSubmit)
      .delegate('#autocomplete li', 'click', data, select)
      .delegate('#autocomplete li', 'mousedown', data, prevent);

    autocomplete.not('.labelized').addClass('labelized').keydown(function(e) {
      if (!e) e = window.event;
      if (e.keyCode === 13) {
        e.preventDefault();
        var that = $jq(this),
          selection = $jq('#autocomplete li.selected', form);        
        if (selection.length) {
          select.call(selection, data);
          setTimeout(function(){ that.val('').focus(); }, 100);
          setTimeout(function(){ that.val('').focus(); }, 200);
        }
      }
    });
    
  });
  
}



Drupal.behaviors.statusDelete = function(context){

   $jq('.facebook-status-delete a:not(.ajax-processed)').addClass('ajax-processed').click(function(e){
      
     e.preventDefault();
     // Other confirmation dialog could have been loaded without neither validation
     // nor cancellation so it has to be removed before showing a new one.
     $jq('#confirm').slideToggle(400, function(){$jq(this).remove();});
     
     var confirm = getConfirmationDialog(null, 'delete-fbss-confirm'),
     href = $jq(this).attr('href'),
     lang = Drupal.settings.lang ? '/'+Drupal.settings.lang : '';
     if(lang && href.indexOf(lang) === -1) {
       href = lang+href;
     }
     
     confirm.insertAfter($jq(this).closest('.facebook-status-details')).slideToggle(400);
     
     confirm.find('#_no_').click(function(){
       confirm.slideToggle(400, function(){$jq(this).remove();});
     });
     
     confirm.find('#_yes_').click(function(){
       // Preserve context
       var that = this;
       // Send request to remove status from database
       $jq.ajax({
            url:href+'-ajax',
            dataType: 'json',
            error: function(){/*console.log('request error'); confirm.remove()*/;},
            success: function(response){
              // Remove status from DOM or alert
              response.deleted ? 
                statusRemoveStatus($jq(that).closest('.facebook-status-item')) :
                confirm.slideToggle(400, function(){
                  $jq(this).remove();
                  alert("MySQL : L'opération de suppression a échoué.");
                });
            }
       });
     });
     
   });
};




Drupal.behaviors.statusCommentDelete = function(context){

   $jq('.fbss-comments-delete-link a:not(.ajax-processed)').addClass('ajax-processed').click(function(e){
     
     e.preventDefault();
     
     var confirm = getConfirmationDialog(null, 'delete-fbss-comment-confirm'),
     href = $jq(this).attr('href'),
     lang = Drupal.settings.lang ? '/'+Drupal.settings.lang : '';
     if(lang && href.indexOf(lang) === -1) {
       href = lang+href;
     }
     // Other confirmation dialog could have been loaded without neither validation
     // nor cancellation so it has to be removed before showing a new one.
     $jq('#confirm').slideToggle(400, function(){$jq(this).remove();});
     confirm.insertAfter($jq(this).closest('.fbss-comments-closure')).slideToggle(400);
     
     confirm.find('#_no_').click(function(){
       confirm.slideToggle(400, function(){$jq(this).remove();});
     });
     
     confirm.find('#_yes_').click(function(){
       // Preserve context
       var that = this;
       // Send a request to remove comment from database
       $jq.ajax({
            url:href+'-ajax',
            dataType: 'json',
            error: function(){/*console.log('request error'); confirm.remove()*/;},
            success: function(response){
              response.deleted ? 
                // Remove comment from DOM or do nothing
                statusRemoveComment($jq(that).closest('.facebook-status-subitem.fbss-comments-comment')) :
                confirm.slideToggle(400, function(){
                  $jq(this).remove();
                  alert("MySQL : L'opération de suppression a échoué.");
                });
            }
       });
     });

   });
};



Drupal.behaviors.statusCommentLink = function(context){
  
   var commentLink = $jq('.fbss-comments-show-comment-form-link:not(.comment-link-processed)')
     .css('display','none')
     .addClass('comment-link-processed');

   if(commentLink.length > 0){
     var imgLink = '<img width="16px" height="16px" title="'+Drupal.t('Add a comment')
       +'" alt="'+Drupal.t('Comment')
       +'" src="/drupal/sites/all/themes/fusion/fusion_starter/img/new/comment.png"'
       +'class="comment-status-image"/>';
   
     commentLink.closest('.content').find('.facebook-status-links').prepend(imgLink);
     
     $jq('.comment-status-image').click(function(){
       $jq(this).closest('.content').find('.fbss-comments-show-comment-form:first').click();
     });
   }
};



// @TODO -> Repost attachment
Drupal.behaviors.statusRepostFast = function(context){

    $jq('#gofast-status-view .facebook-status-repost:not(.repost-fast-processed)').addClass('repost-fast-processed').click(function(e){
      e.preventDefault();
      e.stopPropagation();     
      var status = $jq(this).closest('.content'),
      statusMsg = status.find('.facebook-status-content'),
      sender = status.find('.facebook-status-sender'),
      repost = 'Rt: @'+sender.text()+' \n'+statusMsg.text(), 
      attachment = status.find('.fbss_attachment');    
      // Replace status field by status form
      statusShowForm();
      // Prefill the form with the status to repost
      $jq('#my-last-status textarea:first').val(repost);
      // Load attachment if any
//      if(attachment.size() != 0){
//        
//      }
    });
};



Drupal.behaviors.statusLinkTitle = function(context){
   $jq('#block-ceo_vision_admin-gofast-status .fbsmp-link-title:not(.long-title-processed)').addClass('long-title-processed').each(function(){
     var title = $jq(this).text();
     $jq(this).attr('title', title);
     $jq(this).text(title.trimToPx(160));
   });
};



/**
 * Display a loaded view or refresh it if needed 
 * @param arg : string keyword (what to refresh)
 */
function statusShowView(arg){
    var elapsed = (new Date().getTime() - gofast.statusBoxTimer) > gofast.statusRefreshTime;
    if (elapsed){
      $('#status-ajax-loader').fadeIn(300);
      statusRefreshView(arg);
    } else {
      $jq('#gofast-status-view').css('display','block');
      statusBlockSetMaxHeight();
    }
}

/**
 * Refresh / Get new content view
 */
function statusRefreshView(arg){

  var el;
  gofast.statusViewPage = 1;
  if (!arg) arg = 'view';

  if (arg === 'all') {
    el = $jq('#block-ceo_vision_admin-gofast-status')
    $jq('#gofast-status-view').remove();
  } else {
    el = $jq('#gofast-status-view'),
    el.contents().remove();
  }

  query = statusGetRefreshQuery(),
  lang = Drupal.settings.lang ? '/' + Drupal.settings.lang : '';

  el.load(lang + '/gofast-fbss-status-box/refresh/' + arg + query, '', function(){
    var viewContent = el.find('.view-content');
    if (viewContent.length) {
      Drupal.attachBehaviors(el);
      // Reset scroll position (?)
      viewContent.scrollTop(0);
      if (gofast.inStatusBox) {
        $jq('#gofast-status-view').css('display','block');
        statusBlockSetMaxHeight();
      }
      // Try loading more items if the view max-height is superior to the content height
      if (gofast.inStatusBox && !isScrollable($jq('#gofast-status-view .view-content'))) {
        statusLoadMore();
      }
    } else {
        for (var base in Drupal.settings.ahah) {
            if (base == "last"){
              delete Drupal.settings.ahah[base];
            }
        }
    }
    $('#status-ajax-loader').css('display', 'none');
    // Reset timer & the last updated status reference (sid)
    gofast.statusBoxTimer = new Date().getTime();
  });
}

function statusRefreshBox(){

  var el = $jq('#my-last-status'),
  query = statusGetRefreshQuery(),
  lang = Drupal.settings.lang ? '/' + Drupal.settings.lang : '';

  el.load(lang+'/gofast-fbss-status-box/refresh/box' + query, '', function(){
    el.removeClass('fbss-box-processed');
    Drupal.attachBehaviors(this);
    $jq('#status-ajax-loader').fadeOut(300);
    el.fadeIn(300);
    gofast.statusBoxTimer = new Date().getTime() - gofast.statusRefreshTime;
  });
}



/**
 * Replace last status box field by the status box form on click,
 * focus on the first form element
 */
function statusShowForm(){

    // Hide last status
    var el = $jq('#my-last-status');
    el.find('form').siblings().not('.facebook-status-participants')
      .add('.facebook-status-sender-picture', el)
      .css('display', 'none');
    
    // Display form element, focus, adjust box height
    el.find('textarea:first').css('display','block').focus();
    el.find('.facebook-status-chars, #fbsmp-wrapper-replace:first, #replacement-button').css('display','block');
    el.css('height','auto');
    statusBlockSetMaxHeight();
}




function statusRemoveStatus(el){
    $jq(el).slideToggle(400, function(){
      var container = $jq(this).closest('tr');
      // Reapply properly Odd/Even class & remove container
      var even = container.nextAll('tr.odd').removeClass('odd');
      container.nextAll('tr.even').removeClass('even').addClass('odd');
      even.addClass('even');
      container.remove();
      statusRefreshBox();
    });
}



function statusRemoveComment(el){
    $jq(el).slideToggle(400, function(){
      var showLink = $jq(this).closest('.fbss-comments').find('a.fbss-comments-show-comments-link');
      if(showLink.length > 0){
        // Update the "Show all X comments" link if exists
        var linkText = showLink.text(),
        i = linkText.match(/\d+/);
        showLink.text(linkText.replace(/\d+/, i-1));
      }
      $jq(this).remove();
    });
}


function statusSubmitOp(){
    $jq('#gofast-status-view').slideToggle(400, function(){
      $jq('[id*="facebook-status-box"]').blur();
      $jq('#my-last-status').height(gofast.hdH);
      $jq('#status-ajax-loader').fadeIn(300);
      $jq('#my-last-status .facebook-status-participants').siblings().css('visibility','hidden');
      setTimeout(function(){
        statusRefreshView('all');
        gofast.inStatusBox = 0;
        // Loading attachment may take some time, check display after a while.
        statusFbsmpDisplay();
      }, 3000);
    });
}


function statusMessageIsTooLong(remaining){
    var fbssMaxChars = Drupal.settings.facebook_status.maxlength,
    el = $jq('.facebook-status-negative'),
    charLeft = el.text(),
    params = {
      '%maxchars' : fbssMaxChars,
      '%chars' : fbssMaxChars-remaining
    };
    el.html(Drupal.t('You may use %maxchars characters max.', params)) // ... but you are using %chars characters.
      .css('font-size', '0.95em');
    setTimeout(function(){
      el.text(charLeft).css('font-size', '1em');
    }, 3000);
}


function statusLoadMore(){
    gofast.statusViewPage++; 
    gofast.statusLoadingMore = true;
    
    var query = statusGetRefreshQuery(),
    lang = Drupal.settings.lang ? '/'+Drupal.settings.lang : '',
    loader = $jq('#block-ceo_vision_admin-gofast-status .ajax-loader');

    loader.css({
      'position' : 'relative',
      'bottom'   : '11px',
      'display'  : 'block'
    });
    
    $jq.ajax({
        url:lang+'/gofast-fbss-status-box/loadmore/' + gofast.statusViewPage + query,
        dataType: 'html',
        error: function(){/*console.log('request error');*/},
        success: function(response){
            
          response = $jq(response);
          
          // Look for new content
          var newContent = response.find('.view-content tr:not(:first)').removeClass('views-row-first');
          
          if (newContent.length > 0) { // more items are ready to load

            // Dynamic SCRIPT : 
            // We need to extend Drupal.settings object with new ahah form settings. 
            // Insert plain text JS into head script element
            var docHead = document.getElementsByTagName("head")[0],
            newScript = document.createElement("script"),
            ua = navigator.userAgent,            
            // Get plain text js from the first element of response
            extend = $jq(response[0]).text();            
            // Insert js into script element
            if (ua.match(/(msie)\/?\s*(\.?\d+(\.\d+)*)/i))
              newScript.text = extend; // The IE way
            else
              newScript.innerHTML = extend;
            // Set attribute and load element into the DOM
            newScript.setAttribute("type","text/javascript");
            docHead.appendChild(newScript);
            
            // Load new items into the DOM
            var lastItem = $jq('#gofast-status-view').find('.view-content tr.views-row-last').removeClass('views-row-last');
            newContent.each(function(){
              $jq(this).insertAfter(lastItem);
              lastItem = $jq(this);
            });
            
            Drupal.attachBehaviors(newContent);
            commentDefaultValue(newContent); // -> fbss_comments.js
          }
          
          else{ // There is no more item
            gofast.statusViewPage--; 
            $jq('#block-ceo_vision_admin-gofast-status .no-item').slideToggle();       
            setTimeout(function(){
               $jq('#block-ceo_vision_admin-gofast-status .no-item').slideToggle();
            }, 3000);
          }
          
          loader.css('display','none');
          gofast.statusLoadingMore = false;
            
        } // Ajax success:
    }); // $jq.ajax()
}

// @todo: utiliser Drupal.settings pour récupérer la valeur directement sans $jq
function statusGetContext(){
  var context = $jq('meta[name="context"]').attr('content');
  return context ? context : 'user';
}
// @todo: idem
function statusGetRecipientID(){
  return $jq('meta[name="recipientID"]').attr('content');
}


function gofast_update_context(data) {
  // Checking for a possible change in the current context or status recipient.
  // Get old data to compare with new ones.
  var oldContext = $jq('meta[name="context"]').attr('content'),
  oldRecipientID = $jq('meta[name="recipientID"]').attr('content');
  // Updating data
  $jq('meta[name="context"]').attr('content',data.context);
  $jq('meta[name="recipientID"]').attr('content',data.recipientID);
  // If a change occured, we need to refresh the status box. The content view 
  // will be refreshed as usual (on hover) by resetting the refresh timer.
  if (oldContext !== data.context || oldRecipientID !== data.recipientID) {
    // Refresh the status box
    $('#status-ajax-loader').fadeIn();
    statusRefreshBox();
  }
}



/**
 * If we haven't enough space in status box, we don't display attachment.
 */ 
function statusFbsmpDisplay() {
  if ($jq('#my-last-status .content').height() > gofast.hdH && !gofast.inStatusBox) {
    $jq('#my-last-status .fbsmp').css('display','none');
  }
}


function statusBlockSetMaxHeight(){
  var $content = $jq('#gofast-status-view .view-content');
  if (!$content.length) return;
  
  var maxHeight = getWindowHeight() - $jq('#my-last-status').height() - 25;
  $content
    .css('max-height', maxHeight+'px')
    .data("mCS_maxHeight", maxHeight)
    .mCustomScrollbar("update");
}


function getWindowHeight(){
    var w = window,
    e = document.documentElement,
    g = document.getElementsByTagName("body")[0];
    return w.innerHeight || e.clientHeight || g.clientHeight;
}

function getWindowWidth(){
    var w = window,
    e = document.documentElement,
    g = document.getElementsByTagName("body")[0];
    return w.innerWidth || e.clientWidth || g.clientWidth;
}


function getCurrentUrl(){
  return window.location.protocol + "//" 
       + window.location.host
       + window.location.pathname 
       + window.location.search 
       + window.location.hash;
}


function statusGetRefreshQuery(){
    //var originalPath = getCurrentUrl();
    return '?context=' + statusGetContext()
      + '&recipientID=' + statusGetRecipientID()
      + '&originalPath=' + window.location.pathname
      //+ '&fragment=' + window.location.hash
      + '&statusViewPage=' + gofast.statusViewPage;
}


function getConfirmationDialog(msg, elClass, border){
    msg = msg == null || msg == 'undefined' || msg == '' ? Drupal.t('Delete')+'?' : msg;
    border = border || border == 'undefined' ? '<div class="confirm-border"></div>' : '' ;
    return $jq('<div id="confirm" class="'+elClass+'" style="display:none;"> '+border+' <div style="float:left;">'+msg+' </div> <div style="float:right;"> <div id="_no_" class="gofast-button" style="float:right;">'+Drupal.t('No')+'</div><div id="_yes_" class="gofast-button" style="float:right; margin-right:3px;">'+Drupal.t('Yes')+'</div></div></div>');
}


/**
 * @param {object} obj A jQuery object
 * @returns {boolean} True if obj is scrollable
 */
  function isScrollable(obj) {
      var box = obj[0];
      return !(box.scrollHeight === box.clientHeight);
  }





// Prevents redirect when cancelling modal form
Drupal.behaviors.modalConfirmationForm = function(){
  var link = $jq('#modal-content').find('.form-button a:not(.cancel-dismiss)');
  if (link && link.text() === Drupal.t('Cancel')){
    link.addClass('cancel-dismiss').parent().click(function() {
      Drupal.CTools.Modal.dismiss();
      return false;
    });
  }
};


Drupal.behaviors.gofastBlocks = function(){
  var popped = false, 
      offsetLeft = -50;
            
  if (!$jq('body').hasClass('delegated')){
    $jq(document).click(function(){
      if (!$jq('#modalContent').length){
        popped = false;
        $jq('.gofast-block-outer').css({visibility: 'hidden'});
      }
    });
  }

  $jq('.gofast-block:not(.gofast-block-processed)').addClass('gofast-block-processed').each(function(i){
    var block = $jq(this).children('.gofast-block-outer').addClass('_' + i),
    others = $jq('.gofast-block-outer:not("._' + i + '")');
            
    $jq(this).mouseenter(function(){
      $jq('.pointeur', block).css({left: -offsetLeft + 17});
      others.css({visibility: 'hidden'});
    
     if(block.hasClass("gofast-block-inverse")){
         var offsetLeftInverse = -400;
         var left_position = $jq(this).offset().left + offsetLeftInverse;
          $jq('.pointeur', block).css({left: -offsetLeftInverse + 17});      
     }else{
        
         var left_position = $jq(this).offset().left + offsetLeft;
     }
      block.css({
        left: left_position ,
        visibility: 'visible'
      });
      
      loadBlockIfNeeded($jq(this));
    });

    block.find('*').mousedown(function(){
      popped = true;
    }).click(function(e){
      e.stopPropagation(); 
    });

    $jq(this).mouseleave(function(){
      // Timeout is used to allow mouseenter and click events to be fired before
      // testing 'popped' flag, thus letting handlers revert it just in time.
      setTimeout(function(){
        if (!popped) block.css({visibility: 'hidden'});
      }, 10);
    });
  });
};


/**
 * S'assure que les blocs du header soit bien "processed".
 */
Drupal.behaviors.recallViewsAjax = function(){
  if (!Drupal.Views){
    // Drupal.Views is undefined, we have to load some scripts before the
    // behavior ViewAjaxView throws an error.
   var tmp = Drupal.behaviors.ViewsAjaxView;
   Drupal.behaviors.ViewsAjaxView = function(){ return; };
   var path = '/drupal/sites/all/modules/views/js/';
   loadScript('/drupal/misc/tabledrag.js');
   // Ensure base.js is entirely loaded before loading ajax.js
   loadScript(path+'base.js', loadScript, path+'ajax.js');
   // Ensure ajax_view.js is entirely loaded before calling behavior.
   loadScript(path+'ajax_view.js', callViewsAjaxView, tmp);
   tmp = null;
 }
};


function callViewsAjaxView(func){
  Drupal.behaviors.ViewsAjaxView = func;
  Drupal.behaviors.ViewsAjaxView();
}


function loadScript(url, callback){
   // Adding the script tag to the head
   var head = document.getElementsByTagName('head')[0],
   script = document.createElement('script');
   script.type = 'text/javascript';
   script.src = url;
   if (callback){
     // Bind the event to the callback function , retrieve args.
     // There are several events for cross browser compatibility
     var arg = arguments[2] ? arguments[2] : '';
     script.onreadystatechange = function() { callback(arg); };
     script.onload = function() { callback(arg); };
   }
   // Fire the loading
   head.appendChild(script);
}



Drupal.behaviors.hideViewFilters = function(){
 
   var show = '>>> '+Drupal.t('Show filters'),
   hide = '<<< '+Drupal.t('Hide filters');
   
   $jq('.gofast-block .view-filters:not(.filters-processed)').addClass('filters-processed').each(function(){
     var that = $jq(this);     
     that.before('<div class="show-filters blue-hover">'+show+'</div>');
     that.prev().click(function(){
       that.slideToggle();
       $jq(this).text(function(){
         return $jq(this).text() == show ? hide : show;
       });
     });
   });
};



Drupal.behaviors.msgMarkAsRead = function(context){
  $jq('.modal-msg:not(.modal-msg-processed)', context).addClass('modal-msg-processed').click(function(){
    var that = $jq(this);
    if(that.prev('.msg-new').length > 0){
      // Unread -> Read
      that.prev('.msg-new').remove();
      that.hasClass('gofast-notification') ?
        msgRefreshUnreadCount({privatemsg:0, notification:-1}) :
        msgRefreshUnreadCount({privatemsg:-1, notification:0});
    }
  })
};



Drupal.behaviors.msgDeleteMsg = function(context){
  
   $jq('.delete_message_ajax:not(.ajax-processed)').addClass('ajax-processed').click(function(e){
      
     e.preventDefault();
     // Drupal.t("Are you sure you want to delete this message?"),
     var confirm = getConfirmationDialog(null, 'delete-msg-confirm', false),
     href = $jq(this).attr('href'),
     id = $jq(this).attr("id").split("_"),
     lang = Drupal.settings.lang ? '/'+Drupal.settings.lang : '';
     if(lang && href.indexOf(lang) === -1) {
       href = lang+href;
     }
     // Other confirmation dialog could have been loaded without neither validation
     // nor cancellation so it has to be removed before showing a new one.
     $jq('#confirm').slideToggle(400, function(){$jq(this).remove();});
     confirm.insertAfter($jq(this).closest('tr').find('.views-field-subject a')).slideToggle(400);
     
     confirm.find('#_no_').click(function(){
       confirm.slideToggle(400, function(){$jq(this).remove();});
     });

     confirm.find('#_yes_').click(function(){
       // Send request to remove msg from database
       $jq.ajax({
            url:href,
            data:'mid='+id[1],
            dataType: 'json',
            error: function(){/* console.log('request error'); confirm.remove(); */},
            success: function(response){
              // Remove from DOM or alert
              response.deleted ? 
                msgRemoveMsg(response) :
                confirm.slideToggle(400, function(){
                  $jq(this).remove();
                  alert("MySQL : L'opération de suppression a échoué.");
                });
            }
       });
     });
   });
};



Drupal.behaviors.msgDeleteAll = function(context){

  $jq('a.delete_all_message_ajax:not(.delete-all-processed)', context).addClass("delete-all-processed").click(function(e){
    e.preventDefault();
    var confirmMsg = Drupal.t("Are you sure you want to delete all notification's messages?"),
    confirm = getConfirmationDialog(confirmMsg, 'delete-msg-confirm', false),
    href = $jq(this).attr('href'),
    id = $jq(this).attr("id").split("_");

    $jq('#confirm').slideToggle(400, function(){$jq(this).remove();}); // prevents duplicates
    confirm.insertAfter($jq(this)).slideToggle(400);

    confirm.find('#_no_').click(function(){
      confirm.slideToggle(400, function(){$jq(this).remove();});
    });

    confirm.find('#_yes_').click(function(){
      // Send request to remove msg from database
      $jq.ajax({
        url:href,
        data:'all_notifications=true&mid='+id[1],
        dataType: 'json',
        error: function(){/*console.log('request error');*/},
        success: function(response){
           // Remove from DOM or alert
           if(response.deleted){
             confirm.remove();
             msgRemoveAllNotification();
           }else{
             confirm.slideToggle(400, function(){
               $jq(this).remove();
               alert("MySQL : L'opération de suppression a échoué.");
             });
           }
        }
      });
    });
  });
};



function msgRemoveAllNotification(){
  $jq(".view-display-id-privatemsg_bloc_notifications .view-content").slideToggle(400, function(){
    $jq(this).parent().html(Drupal.t("You haven't got any notification."));
    // Reset unread notification count
    var countNotification = parseInt($jq('.unread_notifications').text());
    if(isNaN(countNotification)) countNotification = 0;
    msgRefreshUnreadCount({privatemsg:0, notification:'-'+countNotification});
  });
}



function msgRemoveMsg(data){
  var message = $jq("#message_"+data.mid).parent().parent(),
   isNotif = message.find('a.modal-msg').hasClass('gofast-notification');
  message.fadeOut();
  // Reset unread count if needed
  if (message.find('.msg-new').length > 0){
    isNotif ?
      msgRefreshUnreadCount({privatemsg:0, notification:-1}) :
      msgRefreshUnreadCount({privatemsg:-1, notification:0});
  }
  // Refresh if no msg left on the current page
  if (!message.siblings().filter(function(){ return $jq(this).css('display') !== 'none'; }).length){
    var selector;
    if (isNotif){
      selector = '#gofast_view-privatemsg-privatemsg_bloc_notifications';
      gofast.privatemsg.privatemsg_bloc_notifications.needRefresh = true;
    } else {
      selector = '#gofast_view-privatemsg-privatemsg_bloc';
      gofast.privatemsg.privatemsg_bloc.needRefresh = true;
    }
    loadBlockIfNeeded($jq(''+selector));
  }
}



function msgGetUnreadCount(){
  $jq.ajax({
    url:'/unread_msg_count',
    dataType: 'json',
    error: function(){/*console.log('request error');*/},
    success: function(count){
      msgSetUnreadCount(count);
    }
  });
}


function msgSetUnreadCount(count){
  
  var notifUnread = $jq('.unread_notifications'),
  msgUnread = $jq('.unread_messages'), 
  oldCount;
  
  if (count.notification > 0) {
    oldCount = parseInt(notifUnread.text());
    if(isNaN(oldCount)) oldCount = 0;
    notifUnread.text(count.notification);
    if(oldCount < count.notification) {
      gofast.privatemsg.privatemsg_bloc_notifications.needRefresh = true;
    }
  } else {
    notifUnread.text('');
  }
  if (count.privatemsg > 0) {
    oldCount = parseInt(msgUnread.text());
    if (isNaN(oldCount)) oldCount = 0;
    msgUnread.text(count.privatemsg)
    if (oldCount < count.privatemsg) {
      gofast.privatemsg.privatemsg_bloc.needRefresh = true;
    }
  } else {
    msgUnread.text('');
  }
}


function msgRefreshUnreadCount(count){
    var oldCount = parseInt($jq('.unread_notifications').text());
    if (isNaN(oldCount)) oldCount = 0;
    count.notification = parseInt(count.notification) + oldCount;
    
    oldCount = parseInt($jq('.unread_messages').text());
    if (isNaN(oldCount)) oldCount = 0;
    count.privatemsg = parseInt(count.privatemsg) + oldCount;
    
    msgSetUnreadCount(count);
}


/**
 * Checks if the content (view/block) needs to be loaded or refreshed and
 * performs suitable action.
 * @param {JQuery object} content
 */
function loadBlockIfNeeded(content){ 
    var id = content.attr('id'),
    title = content.attr('class').replace(/gofast| |-|block|processed|pdf-ie-fixed/g, '').capitalize();
    id = id.split('-');
    
    if (id.length > 3) { // Handle possible use of '-' in block naming
      for (var i=3; i<id.length; i++) {
        id[2] += '-' + id[i];
      }
    }

    if (id[0] === 'gofast_view' && gofast[id[1]][id[2]]['needRefresh']) {
      gofastLoadBlock(id[1], id[2], title, content.find('.gofast-block-inner'), 0);
    } 
    else if (id[0] === 'gofast_block' && gofast[id[1]][id[2]]['needRefresh']) {
      //gofastLoadBlock(id[1], id[2], null, content.find('.gofast-block-inner'), 1);
      gofastLoadBlock(id[1], id[2], title, content.find('.gofast-block-inner'), 1);
    }
}


/**
 * Performs ajax request
 * Loads a themed view (block) inside container.
 * If isBloc is true, the function will return the module block view op based
 * on viewName as module name and displayID as delta.
 */
function gofastLoadBlock(viewName, displayID, title, container, isBloc){
  
    var load = $jq('<div class="ajax-loader"></div>').css('display', 'block');
    if (gofast[viewName][displayID]['firstLoad'] && container.find('.ajax-loader').size() === 0) {
      container.prepend(load);
    }
    
    var path = getCurrentUrl(),
    lang = Drupal.settings.lang ? '/' + Drupal.settings.lang : '',
    query = {
        'viewName':viewName,
        'displayID':displayID,
        'subject':title,
        'original_path':path,
        'isBloc': isBloc
    };

    container.load(lang + '/gofast_get_block', query, function() {
      gofast[viewName][displayID]['needRefresh'] = false;
      Drupal.attachBehaviors($jq(this));
      if (gofast[viewName][displayID]['firstLoad']) {
        gofast[viewName][displayID]['firstLoad'] = false;
        load.remove();
      }
    });
}


function checkCommentsWrapper(nid, wrapperID){
    var type = wrapperID.indexOf('forum') != -1 ? 'post' : 'node',
    content = $jq('div[id="'+type+'-'+nid+'"]').parent();
    if($jq('#'+wrapperID).size() == 0){
      content.append('<div id="'+wrapperID+'"></div>');
    }
}



function isFunction(functionToCheck) {
  var getType = {};
  return functionToCheck && getType.toString.call(functionToCheck) === '[object Function]';
}



function imageRefresh(oldPath, newPath){
  // Add a query to force the browser to reload even if new path is unchanged
  var timestamp = new Date().getTime(),
    img = $jq('img[src*="'+oldPath+'"]');
  img.removeClass('refreshed');
  newPath += '?refresh='+timestamp;
  // Register a behavior to refresh images
  Drupal.behaviors.imageForceRefresh = function(){
    img.not('.refreshed').attr('src', newPath).addClass('refreshed');
  }
}



/* behavior */
function formFieldEditable(){

  var selfFields = $jq('#div_view_profile.self,').add('.block.self').find('.edit-cell, .profile-about-me, .editable'),
  admFields = $jq('#div_view_profile.adm,').find('.edit-cell.profile-manager, .editable'),
  //fields = $jq('#div_view_profile.self,').add('.block.self').find('.edit-cell, .profile-about-me, .editable'),
  dblFields = $jq('.self .profile-title_orga, .self .profile-name_firstname, .adm .profile-title_orga, .adm .profile-name_firstname'),
  title = Drupal.t('Click to edit, then press Enter to validate'),
  title2 = Drupal.t('Click to edit, then click OK to validate');
  
  selfFields.add(admFields).not('.row-processed').attr('title', title).addClass('row-processed editable-highlight').click(function(e){
    e.stopPropagation();
    $jq(this).find('.edit, .edit_node_profile').not(':has(form)').trigger('click');
  });
  
  dblFields.not('.row-processed').addClass('row-processed');
  dblFields.find('.edit').attr('title', title).addClass('editable-highlight');
  
  // Overwrite title attribute for fields that need a click to submit
  $jq('.click-to-submit').attr('title', title2);
  
  selfFields.add(admFields).find('.edit, .edit_node_profile')
    .delegate('form.jeditable-field input', 'focus', formFieldEditableOnFocus)
    .delegate('form.jeditable-field input', 'blur', formFieldEditableOnBlur)
    .bind('keydown', function(e){
      // Bind keydown events with "onBlur" handler (escape/enter keycodes)
      if (e.keyCode == '27' || e.keyCode == '13') {
        formFieldEditableOnBlur.call(this);
      }
    });
   
   $jq('.self #profile-about-me:not(about-me-processed)')
     .addClass('about-me-processed')
     .delegate('textarea', 'focus', function(){
       $jq(this).css('max-width', '90%').closest('.editable-highlight').css({
          margin: '-3px -5px',
          padding: '2px 4px',
          outline: 'none',
          border: '1px solid #00bce9',
          'border-radius': '5px',
//          'box-shadow': '0 0 5px #2da1ec',
          'background-color': '#F1F1F1',
       });
     })
     .delegate('textarea', 'blur', function(){
       $jq(this).closest('.editable-highlight').removeAttr('style');
     });
}


function formFieldEditableOnBlur(){
  var el = $jq(this);
  el.css('background-color', 'inherit');
  el.closest('.jeditable-focused').removeClass('jeditable-focused').addClass('editable-highlight');
  el.closest('.jrow-focused').removeClass('jrow-focused').addClass('row-processed');
}

function formFieldEditableOnFocus(){
  var el = $jq(this);
  el.css('background-color', '#F1F1F1');
  el.closest('.editable-highlight').removeClass('editable-highlight').addClass('jeditable-focused');
  el.closest('.row-processed').removeClass('row-processed').addClass('jrow-focused');
}

// ?
  
function updateQueryStringParameter(uri, key, value) {
  var regex = new RegExp("([?|&])" + key + "=.*?(&|$)", "i"),
  separator = uri.indexOf('?') !== -1 ? "&" : "?";
  if (uri.match(regex)) {
    return uri.replace(regex, '$1' + key + "=" + value + '$2');
  }
  else {
    return uri + separator + key + "=" + value;
  }
}


function loadUrl(newLocation){
  window.location = newLocation;
  return false;
}


function gofastAddLoading(){
  if ($('#backdrop, #gofast-throbber').length > 0) return;
  
  var throbber = '<div id="gofast-throbber">loading...</div>',
  backdrop = '<div id="backdrop" style="z-index: 1000; display: none;"></div>',

   // Get the docHeight and (ugly hack) add 50 pixels to make sure we dont have 
   // a *visible* border below our div. (modal.js)
   docHeight = $(document).height() + 50,
   docWidth = $(document).width(),
   css = {
     position: 'fixed',
     top: '0px',
     left: '0px',
     margin: '0px',
     background: '#000',
     opacity: '.55',
     display: 'none',
     height: docHeight + 'px',
     width: docWidth + 'px'
  };
  
  // Special handling for IE :=|
  if ($.browser.msie) {
    // Add opacity handling
    css.filter = 'alpha(opacity=' + (100 * css.opacity) + ')';
    if ($.browser.version === '10.0') {
      css.background = 'none';
      css['background-color'] = 'transparent';
    }
    if ($.browser.version === '8.0') css.background = '#fff';
    // IE bugfix : Eviter que les contenus ActiveX restent affichés 
    
    var pdf = $('#pdf_frame');
    if (pdf.length > 0) pdf.css('visibility','hidden');
  }
  
  $('body').append(backdrop + throbber);
  $('#backdrop').css(css).fadeIn();
  $('#gofast-throbber').center();
}


function gofastRemoveLoading(){
  $('#backdrop, #gofast-throbber').remove();
  if ($.browser.msie) {
    var pdf = $('#pdf_frame'), modal = $('#modalContent');
    if (pdf.length && !modal.length) {
      pdf.css('visibility','visible');
    }
  }
}


function gofastResize(el){
  // Resize element according to its width/height ratio
  var width = el.width(), height = el.height();

  while (height/width > 1) {
    height -= 1;
    width += 1;
  }
  while (width/height > 3) {
    width -= 1;
    height += 1;
  }

  width = Math.round(width);
  height = Math.round(height);
  // CTools Modal fix 
  var content = el.find('.ctools-modal-content'); // contient header (height = 20px) 
  if (content.length) {
    var contentInner = content.find('#modal-content'), wH = getWindowHeight();
    // Set the modal shape
    contentInner.css({width: width, height: height, 'max-height': wH - 100, 'max-width': 950});
    content.css({width: contentInner.outerWidth(), height: contentInner.outerHeight() + 20});
    el.css({width: content.outerWidth() + 25, height: content.outerHeight() + 25, 'max-height': wH - 50});
    // Reset some to remove outer scroll
    contentInner.css({height: ''});
    content.css({height: '', 'max-height': wH - 40});
    el.css({height: '', 'max-height': wH - 20});
    
    var avatarForm = el.find('#gofast-image-form');
    if (avatarForm.length){
      // Recenter after a while (let the browser load and resize img before)
      setTimeout(function() {
        el.center();
      }, 1000);
    }
  }
  el.css('overflow', 'auto');

  // Since busy browser migth have been wrong about the content dimensions on
  // the first run : wait a moment, refresh element, test its dimensions and
  // redo if it looks weird.
  setTimeout(function() {
    el = $(el);
    if (el.width() < el.height()) {
      gofastResize(el);
      el.center();
    }
  }, 200);
}


function gofastDynamicPopup(context){
  var popup = $(context), css;
  // Register behavior
  Drupal.behaviors.gofastDynamicPopup = function(){
    popup = popup || $('#modalContent');
    css = {height: 'auto', width: 'auto'};
    $('.ctools-modal-content, #modal-content', popup).css('max-height', '');
    popup.css(css);
    $('.ctools-modal-content, #modal-content', popup).css(css);
    popup.center();
  };
  Drupal.behaviors.gofastDynamicPopup();
  var avatar = $jq('#gofast-image-form');
  if (avatar.length) {
    avatar.css('overflow', 'auto');
    avatar.not('delegated').addClass('delegated').delegate(popup, 'resize', function(){
      setTimeout(Drupal.behaviors.gofastDynamicPopup, 200);
    });
  }
}


Drupal.behaviors.searchBlockFocus = function(){
  $jq('#edit-search-block-form-1:not(.focus-processed)').addClass('focus-processed')
    .focus(function(){
      $jq(this).closest('.container-inline').addClass('focused');
    })
    .blur(function(){
      $jq(this).closest('.container-inline').removeClass('focused');
    })
};


function gofastLdapConnectionDialog(noreload, callback, arg){
  
  gofastAddLoading();
  var name_ldap_technical_account;
  var lang = Drupal.settings.lang ? '/'+Drupal.settings.lang : '',
    url = lang + '/ajax/gofast_ldap_auth',
    title  = Drupal.t('LDAP directory - Authentication'),
    text   = Drupal.t('Please enter the password of user '+name_ldap_technical_account+' to connect to your directory : '),
    input  = '<input type="password" name="ldap_pass" id="ldap-input" maxlength="128" size="25" />',
    button = '<input id="ldap-submit" type="submit" value="OK" autofocus="autofocus" style="margin:5px;"/>', // 
    html   = '<div id="ldap-prompt" style="position:center; text-align:center;"><p>' + text + '</p>' + input + button + '<br /><br /></div>';
    
  var authentication = function(){
    $.ajax({
      url:url,
      type:'POST',
      data:'ldap_pass='+$('#ldap-input').val(),
      dataType: 'json',
      success:function(response){
        if (response) {
          if (noreload) {
            Drupal.CTools.Modal.dismiss();
            arg = arg || null;
            return callback ? callback.apply(arg) : true;
          }
          location.reload(true);
        }
        else gofastLdapConnectionDialog();
      },
      error:function(){
//        console.log('error');
      }
    });
  };
  
  gofastAddLoading();
  gofast_modal(title, html);
    
//  Drupal.CTools.Modal.show();
//  $('#modal-title').html(title);
//  $('#modal-content').html(html);
//  
//  setTimeout(function(){
//    var modal = $('#modalContent');
//    gofastResize(modal);
//    modal.center();
//    gofastRemoveLoading();
//    $('#modalBackdrop').add(modal).css('visibility', 'visible');
//    $jq('#modalContent').draggable({handle: ".modal-header"});
//  }, 300);

  $('#ldap-submit').click(authentication);
  $('#ldap-input').keypress(function(e) {
    if (e.which === 13) authentication();
  });
}


// deprecated: use placeholder attr. for html5 ready browsers (voir fallback dessous)
Drupal.behaviors.gofastTextFieldAutoClear = function(){

  // Clear text field when focused if default value wasn't changed.
  $jq('.auto-clear:not(.auto-clear-processed)').addClass('auto-clear-processed').each(function(){
    var that = $jq(this), defaultColor = that.css('color'), defaultFontStyle = that.css('font-style');
    that.css({'font-style': 'normal', 'color':'#999'})
      .focus(function() {
        if (this.value === this.defaultValue) {
          that.css({'font-style': defaultFontStyle, 'color': defaultColor});
          this.value = '';
        }
      })
      .blur(function() {
        if (this.value === '') {
          that.css({'font-style': 'normal', 'color':'#777'});
          this.value = this.defaultValue;
        }
      });
  });
};

if (!('placeholder' in document.createElement('input'))) {
  Drupal.behaviors.gofastPlaceholderFallback = function () {
    var marker = 'placeholding';
    $('input[placeholder], textarea[placeholder]').not('.placeholder-fallback').addClass('placeholder-fallback').each(function() {
      // Active placeholder for this element

      if (this.value == "") {
        $(this).addClass(marker).attr(marker, true);
        this.value = $(this).attr('placeholder');
        // Bind events
        $(this).focus(function() {
          // alert($(this).val());
          // alert($(this).attr('placeholder'));
          // Remove placeholder if marker is active (testing the value wouldn't 
          // make it possible to type the same value as the placeholder).
          if ($(this).attr(marker)) {
            $(this).removeClass(marker).attr(marker, false); 

            if($(this).attr('placeholder') == $(this).val()){
              this.value = '';
            }
          }
        }).blur(function() {
          if (!$.trim(this.value)) {      
            $(this).addClass(marker).attr(marker, true); 
            this.value = $(this).attr('placeholder');
          }
        });
        $(this).focus().blur();
      }
    });
    
    // Clear default placeholder values on form submit.
    $('form').submit(function() {
      $(this).find('input[placeholder], textarea[placeholder]').each(function() {
        if (this.value === $(this).attr(marker)) {
          this.value = '';
        }
      });
    });
  };
}


/**
 * Search : Display fallback for empty sort block
 */
Drupal.behaviors.solrEmptySortBlock = function () {
  var sortBlock = $('.apachesolr-sort-wrapper:not(.empty-processed)').addClass('empty-processed');
  if (sortBlock && sortBlock.text().trim() === '') {
    sortBlock.css('display', 'none');
  }
};


Drupal.behaviors.solrShowTeaser = function () {
  $jq('.search-result .show-teaser:not(.shtsr-processed)').addClass('shtsr-processed').each(function() {
    $jq(this).click(function(e) {
      e.preventDefault();

      var title = $jq(this).closest('div.search-result').find('dt.title span.title').clone(),
       teaser = $jq(this).next('.search-teaser').clone().css('display', 'block');
       
      // Remove highlighted snippet from title.
      $jq(title).find('em').replaceWith(function(){
        return $jq('<span />').append($jq(this).contents());
      });

      // Fallback if teaser is empty...
      if (teaser.text().trim() === '') {
        teaser = '<div style="font-style:italic; color:#999;">' + Drupal.t('There is no teaser for this document, or it has not yet been indexed.') + '</div>';
      }
      
      gofastAddLoading();
      Drupal.CTools.Modal.show({modalSize:{width:780}});
      $jq('#modal-title').html(title.html() + ' <span> (' + Drupal.t('teaser') + ')</span>');
      $jq('#modal-content').html(teaser);
      
      // Process title for ajax navigation (cloning is not sufficient).
      $jq('#modal-title').find('a.ajax-navigate').click(function(e) {
        e.preventDefault();
        try { 
          Drupal.CTools.Modal.dismiss();
          YAHOO.util.History.navigate('q', 'node/' + $jq(this).attr('nid')); 
        }
        catch (err) { location.href('/node/' + $jq(this).attr('nid')); }
      });
      
      setTimeout(function() {
        var modal = $('#modalContent');
        modal.center();
        gofastRemoveLoading();
        $jq('#modalBackdrop').add(modal).css('visibility', 'visible');
        $jq('#modalContent').draggable({handle: '.modal-header'});
      }, 300);
    });
  });
};


Drupal.behaviors.solrSearchCtxt = function () {
  var el = $jq('#edit-search-block-form-1'), ctxt, placeholder;
  if (el.length) {
    ctxt = statusGetContext();
    if (ctxt === 'user') {
      placeholder = Drupal.settings.gofast.solrCtxt === 'private' ? 
        Drupal.t('Search in my private contents') :
        Drupal.t('Search');
    }
    else if (ctxt === 'og') {
      placeholder = Drupal.settings.gofast.solrCtxt ? 
        Drupal.t('Search in') + ' ' + Drupal.settings.gofast.solrCtxt :
        Drupal.t('Search in this space');
    }
    
    // Set / update placeholder
    el.attr('value', '');
    el.attr('placeholder', placeholder);
//    el.focus().blur(); // trigger fallback

    // Enable fq for private search
    el.closest('form:not(.fq-processed)').addClass('fq-processed').submit(function(){
      if (Drupal.settings.gofast.solrCtxt === 'private')
        setCookie('solrSearchFilterQuery', 'private=true', 5);
    });
  }
};




/* Fonction qui permet d'ajouter la classe "error" sur l'explorateur alfresco 
 * lorsque FAPI fait un form_set_error sur le champ emplacements (node-form) */
Drupal.behaviors.selectLocationError = function(){
  var field = $('#node-form #edit-emplacement.error'),
  browser = $('#node-form #og_show_emplacement_form:not(.error)');
  if (field.length && browser.length) {
    browser.addClass('error').focus(function() {
      browser.removeClass('error');
    });
  }
}



function resetBackgroundSettings(settings){
  settings.toggle_background_image ?
    $jq('#edit-toggle-image').prop('checked', true) :
    $jq('#edit-toggle-image').prop('checked', false);

  $jq('#edit-color').val(settings.background_color_default);
  $jq('#edit-user-wallpaper').val(settings.background_image_path);
    
  $('#edit-toggle-image').is(':checked') ?
    $('#edit-user-wallpaper-wrapper').show("slow") :
    $('#edit-user-wallpaper-wrapper').hide("slow");  
    
  $jq("#edit-color-header").val(settings.background_header);
  $jq("#edit-color-header-menu").val(settings.background_menu);
  $jq("#edit-color-popups").val(settings.background_popups);
  $jq("#edit-color-header-font").val(settings.font_menu);
}




function createsubfolder(link, nid){
    gofastAddLoading();
    Drupal.CTools.Modal.show();
    $('#modal-title').html(Drupal.t('Create subfolder'));
    $('#modal-content').html('<input id="subfolder_name" class="auto-clear" type="text" value="'+Drupal.t("Title")+'"><input id="subfolder_valid_span" class="form-submit" onClick="createsubfolderajax(this, \''+nid+'\')" type="submit" value="'+Drupal.t("Save")+'"><input id="subfolder_hidden_id" type="hidden" value="'+link.id+'">');
    setTimeout(function(){
      // Les propriétés de l'object modal mettent un petit
      // temps pour s'actualiser, d'où le timeout pour que 
      // les fonctions de resize/center s'executent 
      // correctement.
      var modal = $('#modalContent');
      Drupal.behaviors.popupdraggable();
      gofastResize(modal);
      modal.center();
      gofastRemoveLoading();
      $('#modalBackdrop').add(modal).css('visibility', 'visible');
      Drupal.behaviors.gofastTextFieldAutoClear();
    }, 200);
}


function createsubfolderajax(link, nid){
    var path = unescape($jq("#subfolder_hidden_id").val());
    var foldername = $jq("#subfolder_name").val();
    Drupal.CTools.Modal.dismiss();
    var lang = Drupal.settings.lang ? '/'+Drupal.settings.lang : '';
    gofastAddLoading();
    $.ajax({
        url: lang + '/doctree/createsubfolder',
        data:'path='+path+'&foldername='+foldername,
        dataType: 'json',

        success:function(data){
            gofastRemoveLoading();
            //location.reload(); 
             $.ajax({
                    url: lang + '/doctree/refreshtree',
                    data:'nid='+nid,
                    dataType: 'html',

                    success:function(data2){
                        gofastRemoveLoading();
                        $jq('#tree1').unbind(); 
                        $jq("#tree1").html(data2);
                        //location.reload(); 

                    }
               });
        }
    });
}
    

function stopJS(){
  //throw "stop execution";
  throw new Error('This is not an error. This is just to abort javascript for debugging.');
}


/**
 * @params url If not set, use the current url
 * @returns last snippet of url ignoring query params
 */
function getUrlLastPart(){
  var url = arguments[0] || $jq(document)[0].URL;
  url = url.split('/');
  var snipUrl = url.last(),
   index = snipUrl.indexOf("?") != -1 ? snipUrl.indexOf("?") : snipUrl.indexOf("#");
  return index == -1 ? snipUrl : snipUrl.substring(0,index);
}


function escapeHtml(rawInput) {
  return rawInput
    .replace(/&/g, "&amp;")
    .replace(/</g, "&lt;")
    .replace(/>/g, "&gt;")
    .replace(/"/g, "&quot;")
    .replace(/'/g, "&#039;");
}


function safeHtml(rawInput){
  // safeInput = input.text(rawInput).html(); 
  // Since html() method doesn't return anything from input form fields with 
  // Chrome and Opera & Safari? (except with <textarea>) we have to use a temp 
  // object.
  // First prevent escaped new lines (textarea with IE)
  rawInput = rawInput.replace(/(\r\n|\r|\n)/g, '_-*-_'); // this special char pattern is a tag to replace with new lines later.
  var safeInput = $('<div></div>').text(rawInput).html();
  return safeInput.replace(/(_-\*-_)/g, '<br />');  
}


function gofastSetTitle(str){
  // <title> Reset 
  var title = document.getElementsByTagName('title')[0];
  title.text = str;    
}


// Unselectable properties fallback for IE & Opera 
if ($.browser.msie || $.browser.opera){
  Drupal.behaviors.unselectableFallback = function(){
    var el = $('.unselectable:not(.unselectable-fixed)').addClass('unselectable-fixed');
    if (el.length) {
      el.attr('unselectable', 'on').find('*').attr('unselectable', 'on');
    }
  }
}


function gofastUserSyncLDAP() {
    // Si AD est dispo on simule un clic sur un lien modal
    var lang = Drupal.settings.lang ? '/'+Drupal.settings.lang : '',
      context = $('<a class="ctools-use-modal ctools-use-modal-processed" href="' + lang + '/modal/nojs/pupop_gofast_ldap_sync_form"></a>');
    Drupal.settings.ldapAuthenticated ?
      Drupal.CTools.Modal.clickAjaxLink.apply(context) :
      gofastLdapConnectionDialog(true, Drupal.CTools.Modal.clickAjaxLink, context);
}


Drupal.behaviors.moveldapSyncMsg = function() {
  var form = $jq('#gofast-ldap-sync-form:not(.msg-processed)');
  form.addClass('msg-processed').prev('.messages, .error').insertAfter(form.children('div').last());
}


/**
 * Maintient le formulaire d'ajout de membre de groupe à sa place lorsqu'on 
 * utilise le pager de la vue.
 * @returns {undefined}
 */
Drupal.behaviors.manageMembersPagerFix = function(context) {
  var form = $jq('#ceo-vision-ui-managemembersform' ,context),
    view = form.next('.view-ceov-og-members-block');
  if (form.length && view.length) {
    form.insertAfter(view);
  }
}


/**
 * When a message conversation is loaded, let the browser scroll down to the
 * last response. 
 * @returns {undefined}
 */
Drupal.behaviors.privateMessageConversation = function() {
  var modal = $jq('#modal-content'), msgBox;
  if (modal.length) {
    msgBox = modal.find('#privatemsg-ajax-new textarea');
    if (msgBox.length) {
      var target = modal.find('.privatemsg-box-fb').last();
      modal.scrollTop(target.position().top);
    }
  }
}

// http://api.jqueryui.com/autocomplete/
// http://mtgbuddy.com/ac.html  
//Drupal.behaviors.solrSearchAutocomplete = function () {
//  $('#edit-keys, #edit-search-block-form-1').autocomplete({
//    'source': function (_request, _response) {
//      $.ajax({
//        'url': '/test-autocomplete',
//        'data': {
//          'term': _request['term']
//        },
//        'success': function (_dta) {
//          _response(_dta);
//        }
//      });
//    }
//  }).data('ui-autocomplete')._renderItem = function (_ul, _item) {
//    return $('<li></li>')
//    .data('item.autocomplete', _item)
//    .append('<a href="/cards/' + _item['slug'] + '/">' + _item['name'] + '</a>')
//    .appendTo(_ul);
//  };
//}

Drupal.behaviors.solrSearchFilterPersistence = function(context) {
  var $context = $(context).find('.search-params-wrapper');
  if (!$context.length) return;
  
  var toogleOption = function (item, value) {
    $(item).toggleClass('item-checked');
    return value === '1' ? '0' : '1'; 
  };
  
  // Prevents search to preform when clicking options list.
  $('button:not(.prevent-submit)', $context).addClass('prevent-submit').click(function(e) {
    e.preventDefault();
  });

  $('#search-options-dropdown li:not(.item-processed)', $context).addClass('item-processed').each(function(){
    var item = $(this),
     itemId = item.attr('item'),
     formItem = $('input:hidden[name=' + itemId + ']');

    $(this).click(function(){
      formItem.val(toogleOption(item, formItem.val()));
      setCookie('searchparameters_formState', $('#search-form').serialize(), 31536000);
    });
  });
};


Drupal.behaviors.solrSearchResultsActions = function() {
  var callback = function() {
    $(this).find('.fileexplorerbuttons').toggle();
    handlericoneactions($(this).find('.icone_actions'), true);
  }, 
  config = {
    sensitivity: 1,  // number = sensitivity threshold (must be 1 or higher)    
    interval: 100,   // number = milliseconds for onMouseOver polling interval    
    over: callback,  // function = onMouseOver callback (REQUIRED)    
    timeout: 200,    // number = milliseconds delay before onMouseOut
    out: callback    // function = onMouseOut callback (REQUIRED)
  };
  $('.search-result dt.title:not(.actions-processed)').addClass('actions-processed').each(function() {
    $(this).hoverIntent(config);
  });
}


Drupal.behaviors.privateMessageShowParticipants = function() {
  var callback = function() { $(this).find('.to-extend').slideToggle(); }, 
  config = {
    sensitivity: 1, 
    interval: 100, 
    over: callback, 
    timeout: 200,
    out: callback 
  };
  $('.gofast-block .pm-participants:not(.pm-processed)').addClass('extend-processed').each(function() {
    $(this).hoverIntent(config);
  });
}

/*
  @sensitivity: If the mouse travels fewer than this number of pixels between polling 
  intervals, then the "over" function will be called. With the minimum sensitivity 
  threshold of 1, the mouse must not move between polling intervals. With higher 
  sensitivity thresholds you are more likely to receive a false positive. Default 
  sensitivity: 7

  @interval: The number of milliseconds hoverIntent waits between reading/comparing 
  mouse coordinates. When the user's mouse first enters the element its coordinates 
  are recorded. The soonest the "over" function can be called is after a single 
  polling interval. Setting the polling interval higher will increase the delay 
  before the first possible "over" call, but also increases the time to the next 
  point of comparison. Default interval: 100

  @over: Required. The function you'd like to call onMouseOver. Your function 
  receives the same "this" and "event" objects as it would from jQuery's hover 
  method.

  @timeout: A simple delay, in milliseconds, before the "out" function is called. If 
  the user mouses back over the element before the timeout has expired the "out" 
  function will not be called (nor will the "over" function be called). This is 
  primarily to protect against sloppy/human mousing trajectories that temporarily 
  (and unintentionally) take the user off of the target element... giving them time 
  to return. Default timeout: 0

  @out: Required. The function you'd like to call onMouseOut. Your function receives 
  the same "this" and "event" objects as it would from jQuery's hover method. Note, 
  hoverIntent will only call the "out" function if the "over" function has been 
  called on that same run.
*/


Drupal.behaviors.initStatusReference = function() {
  Drupal.settings.gofast = Drupal.settings.gofast || {};
  Drupal.settings.gofast.status = Drupal.settings.gofast.status || {};
  gofast.statusReference = Drupal.settings.gofast.status.reference || {sid: 0, timestamp: new Date().getTime()};
}


function gofastProcessPollingData(data){
  if (data) {
    // Update unread msg count (privatemsg/notification )
    msgSetUnreadCount(data);
    // Check for new status
    statusCheckNewStatus(data);
    
    if(typeof wfSetUnreadCount === 'function'){
        wfSetUnreadCount(data);
    }
  }
}


function statusCheckNewStatus(data) {

  if (data.gofastStatusPoll) {
    // Highlight new submitted status
    if (data.gofastStatusPoll.isNew && data.gofastStatusPoll.newStatus) {
      var wrapper = $('#my-last-status').parent(),
       newStatus = $(data.gofastStatusPoll.newStatus);

      newStatus.css({
        position      : 'relative',
        top           : '0px',
        padding       : '5px 5px 0',
        background    : '#fff',
        height        : (gofast.hdH - 5) + 'px',
        opacity       : '0',
        // IE handling
        filter        : 'alpha(opacity=0)',
        '-ms-filter'  : 'alpha(opacity=0)'
      });

      wrapper.css({
        'max-height'  : gofast.hdH + 'px',
        overflow      : 'hidden'
      });

      wrapper.append(newStatus);

      $(newStatus).animate({
        opacity: '1',
        top: -gofast.hdH + 'px'
      }, 1500, function() {
        // Animation complete.
        var that = $(this);
        setTimeout(function(){
          that.fadeOut(1500, function() {
            // Reset style & remove element
            wrapper.css({'max-height': '', overflow: ''});
            $(this).remove();
          });
        }, 5000);
      });
    }
    
    // Refresh reference
    gofast.statusReference = data.gofastStatusPoll.reference;
  }
}

$(document).ready(function() {
  if (Drupal.settings.gofastIgnoreHash === true) {
    // A page refresh just occured.
    window.location.hash = '';
    gofast.pageLoadAsync = false;
  }

  var eventName = 'beforeunload', 
  fnHandler = function (e) {
    e = e || window.event;

    // Prevents browsers from showing confirmation dialog.
    e.stopPropagation ? e.stopPropagation() : e.cancelBubble = true;
    if (gofast.pageLoadAsync === true && window.location.hash !== '') {
      // We are performing a page refresh. In order to load appropriated content
      // the page context along with the location pathname and hash are sent to 
      // the server using a cookie.
      var data = { // encoded 3 times ..?
        context : onSearchPage() ? 'search' : statusGetContext(), // use fbss context but let "search" context override it to handle search queries.
        path : decodeURI(decodeURI(decodeURI(window.location.pathname))), 
        hash : decodeURI(decodeURI(decodeURI(window.location.hash))).replace(/\+/g, '%2B')
      }; 
      setCookie('__unload', JSON.stringify(data), 3);
    }
  };
  
  // Handle page reloads/refresh when content was loaded asynchronously.
  if (window.addEventListener) {
    window.addEventListener(eventName, fnHandler);
  }
  else {
    window.attachEvent('on' + eventName, fnHandler);
  }
});


Drupal.behaviors.pageLoadAsyncFlag = function () {
  // Record whether the last page was loaded asynchronously or not.
  $('a:not(._lpa, .lang-switch)').addClass('_lpa').click(function (e) {
    var $this = $jq(e.target).closest('a'),
     path = getCurrentUrl().split('#')[0] + '#';
    // Do not track <a> elements that don't behave like 'links'.
    if (!$this[0].hasAttribute('href') || $this.attr('href').indexOf('#') === 0 || $this.attr('href') === path || $this.hasClass('ctools-use-modal-processed')) {
      // Assuming the current page content is preserved, do nothing.
      return;
    }
    gofast.pageLoadAsync = $this.hasClass('ajax-navigate-processed') || $this.hasClass('apachesolr-ajax-processed');
  });
};


/** 
 * Helper that returns whether user is on a search page or not.
 * @returns {boolean}
 */
function onSearchPage() {
  return $('#search-form').length;
}


Drupal.behaviors.cmdDisp = function (context) {
  var ctxt = $jq(context);
  $jq('a.cmd_d', ctxt).addClass('cmd_d-processed').one('click', function(e) {
    e.preventDefault();
    var that = $(this);
    $.ajax({
      url: that.attr('href'),
      data: 'cmdAsync=1',
      dataType: 'html',
      error: function(){console.log('request error');},
      success: function(response){
        var html = $jq(response).get(0);
        $jq(html).insertAfter(that);
      }
    });
  });
};

/**
 * Process "go" links to allow ajax-compatible behavior (Solr search results). 
 * Extends highlighting feature to a target page requested asynchronously.
 */
Drupal.behaviors.gofastSearchGoHighlight = function (context) {  
  var ctxt = $(context);
  $('.search-results a.go-search-snippet:not(.snippet-processed)', ctxt).addClass('snippet-processed').each(function() {
    var word = $(this).attr('word'), snippet = $(this).attr('snippet');
    if (word && snippet) {
      Drupal.settings.gofast.highlight = Drupal.settings.gofast.highlight || {};
      $(this).click(function(){
        Drupal.settings.gofast.highlight.word = word;
        Drupal.settings.gofast.highlight.snippet = snippet;
      });
    }
  });
};


Drupal.behaviors.solrExpandableFacets = function (context) {
  $('.facetapi-facetapi_links li.collapsed:not(.expandable)').addClass('expandable').each(function() {
    var facet = $(this);
    $(this).find('.facet-expandable').click(function () {
      $(facet).toggleClass('collapsed');
      $(this).toggleClass('expanded');
    });
  });
};



/**
 * Highlight matched string within the page content
 * @param {type} word
 * @param {type} snippet
 */
function gofastSearchHighlightElement(word, snippet) {
  var target, scrolltop, content, match;
  
  // Filter out html entities
  word = $jq("<div/>").html(word).text();
  snippet = $jq("<div/>").html(snippet).text();
  
  content = $jq('#content_node, #comments, #forum-comments');
  
  if (content.length) {
    match = $(content).filterByText(snippet);
    match.length ? $jq(match).highlight(snippet) : content.highlight(word);
  }
  
  target = $jq('.search_highlight');
  if (target.length) {
    // Scroll down to the first target. Offset is relative to the header's height.
    scrolltop = target.offset().top - (gofast.hdH + 10);
    $jq('html, body').animate({scrollTop : scrolltop}, 500);

    // Allow user to remove highlighting :
    // Show a tip while hovering highlighted snippets
    var tip = $jq('<span class="gofast-button">' + Drupal.t('Click to remove highlighting') + '</span>').css({
      position      : 'absolute',
      background    : '#333',
      color         : '#eee',
      'font-size'   : '10px',
      'font-family' : 'Arial'
    });
    // Set mouse events callback (over/out) and hover intent parameters
    var over = function() {
      var pos = $(this).position();
      $(this).css('cursor', 'pointer');
      $(tip).appendTo(this).css({top : pos.top + 10 + 'px'}).show().add(this).click(function(e) {
        e.preventDefault(); // element could be an anchor tag
        tip.remove();
        $(target).unbind().css('cursor', 'auto').removeClass('search_highlight');
      })
    }, out = function() { 
      $(this).css('cursor', 'auto');
      tip.remove();
    }, config = {
        sensitivity: 1, 
        interval: 150, 
        over: over, 
        timeout: 250,
        out: out 
    }
    // Bind target
    $(target).hoverIntent(config);
  }
}

function processOgTabs(ogActiveTabDefault) {
  $jq(document).ready(function() {
    // Remember the last active tab.
    $jq('a[fragment]:not(".tabs_processed")').addClass('tabs_processed').each(function(i) {
      $jq(this).click(function(e) {
        var $value_cookie = JSON.parse(getCookie('ogActiveTab')) || {};
        $value_cookie[Drupal.settings.gofast.nid] = {
          id : parseInt($jq(this).attr('fragment')),
          tab: i
        };
        setCookie('ogActiveTab', JSON.stringify($value_cookie), 60*60*24);
      });
    });

    // Select the correct tabs
    ogTabsGetLast(ogActiveTabDefault);
    
    // Process tabs.
    $jq('#tabs2:not(".tabs_processed")').addClass('tabs_processed').tabs({selected:Drupal.settings.gofast.ogActiveTab.tab});
    $jq('#tabs:not(".tabs_processed")').addClass('tabs_processed').tabs();
  });
}


function ogTabsGetLast(ogActiveTabDefault) {
  Drupal.settings.gofast = Drupal.settings.gofast || {nid:0};
  // Select last active tab or fallback to default.
  var memorizedTab = JSON.parse(getCookie('ogActiveTab')) || {};
  return Drupal.settings.gofast.ogActiveTab = memorizedTab[Drupal.settings.gofast.nid] || ogActiveTabDefault;
}


function gofastAjaxFileBrowser(url, credentials) {
  var forceReload = false;

  $jq(document).ready(function() {
    Drupal.settings.gofast.ogActiveTab = Drupal.settings.gofast.ogActiveTab || ogTabsGetLast({tab : 0, id : false});
    
    if (Drupal.settings.gofast.ogActiveTab.id === 2) {
      // Load the browser if the tab is active (tab #fragment).
      InitAjaxFileBrowser(LoadAjaxFileBrowser);
    }
    else {
      // Else bind the browser init function to click event.
      $jq('#browserTabLink:not(".load-processed")').addClass('load-processed').one('click', function() {
        InitAjaxFileBrowser(LoadAjaxFileBrowser);
      });
    }
    
    // Bind a force reload behavior with double click event.
    $jq('#browserTabLink:not(".reload-processed")').addClass('reload-processed').dblclick(function() {
      forceReload = true;  
      InitAjaxFileBrowser(LoadAjaxFileBrowser);
    });
  });
  
  function InitAjaxFileBrowser(callback) {
    var container = $jq('#AjaxFileBrowserContainer');
    if (!container.length) {
      // Container get lost!
      container = $jq('<div id="AjaxFileBrowserContainer" class="ih_style" style="width:100%; height:100%;"></div>');
      forceReload = true;
    }
    if (Object.prototype.toString.call(callback) === '[object Function]') {
      callback(container);
    } 
    else {
      LoadAjaxFileBrowser(container);
    }
  }
                  
  function LoadAjaxFileBrowser(container) {
    container.appendTo('#FakeAjaxFileBrowserContainerContainer');
     var baseUrl = window.location.protocol + "//" + window.location.host;
     var memorize_last_url_ajax_file_browser = getCookie('memorize_last_url_ajax_file_browser');
     
   // memorize_last_url_ajax_file_browser = decodeURIComponent(escape(memorize_last_url_ajax_file_browser));
    
     if (memorize_last_url_ajax_file_browser != false){
        var selected_folder = "alfresco/webdav"+memorize_last_url_ajax_file_browser;
     }
     else{
        var selected_folder = url;
     }
     
    var n=selected_folder.indexOf("Espaces Utilisateurs");
    if (n == -1){
        var root_url = baseUrl+"/alfresco/webdav/Sites/"
    }
    else{
        var root_url = baseUrl+"/alfresco/webdav/Espaces Utilisateurs/"
    }

    // Create the AJAX File Browser Settings object.
    // http://www.webdavsystem.com/ajaxfilebrowser/programming/settings_reference
    var settings = {
      BasePath: '/drupal/sites/all/libraries/ajax_file_browser/Browser/',
      //BasePath: '/drupal/sites/all/libraries/ajax_file_browser_sources/BrowserSource/',
      Id: 'AjaxFileBrowserContainer',             // (required) ID of the HTML control in which Ajax File Browser will be created
      Url: root_url,     // (required) the root folder to be displyed in Ajax File browser
      Style: 'height:100%;width:100%',            // (required) always provide size of the control
      MsOfficeTemplatesPath: url + '/templates/', // path to MS Office templates, always specify full path
      SelectedFolder: selected_folder,            // folder to be selected, same as SetSelectedFolderAsync call
      ThemeName: 'windows_8',             // theme name (folder name under /themes/ folder, for examle 'clean', 'golden', 'lumina', 'modern', 'soft', 'windows_8', etc)
      IconsSize: 16,                      // icon size (available options are: 16, 24, 32, 48, 64, 72)
      Platform: 'auto',                   // platform (available options are: 'desktop', 'tablet', 'mobile', 'auto')
      SearchAutocompleteEnable: true,     // enable auto-complete in search field
      SearchDynamicEnable: false,         // update search results list while typing
      EnableHistoryNavigation: false,
      OpenHistoryLink: false,
       Panels: {
        AddressBar: {Show : false}
      },
      Phrases: phrases    
    };
    
    // Force authentication before doing anything.
    sendXHR('GET', url, null, false, [{name : 'Authorization', value : credentials}]);

    if (gofast.AjaxFileBrowserLoader.loaded === false || forceReload) {
      gofast.AjaxFileBrowserLoader = new ITHit.WebDAV.Client.AjaxFileBrowserLoader(settings);
      gofast.AjaxFileBrowserLoader.oninit = function (ajaxFileBrowser) {
        //This event is fired when control is loaded and created.
        gofast.ajaxFileBrowser = ajaxFileBrowser;
        ITHit.Events.AddListener(gofast.ajaxFileBrowser, 'OnOpenItem', onOpenItem);
        ITHit.Events.AddListener(gofast.ajaxFileBrowser.GetMenuManager(), 'OnShowMenu', onShowMenu);
        //ITHit.Events.AddListener(gofast.ajaxFileBrowser, 'OnSelectedFolderChanged', onSelectedFolderChanged);
        this.loaded = true;

        //pour IE8 et 9 on cache le formulaire d'upload
        if ($jq.browser.msie  && parseInt($jq.browser.version, 10) < 10) {
          var html_fallback_upload_file = "<input type='button' onClick='ceo_vision_fallback_upload_ie9();' style='cursor:pointer;padding:2px;' value='"+Drupal.t("Click here to upload a file in this folder")+"'>";
          $jq(".uploadPanel").html(html_fallback_upload_file);
        }
      };

      // Starts loading Ajax File Browser files asynchronously 
      gofast.AjaxFileBrowserLoader.LoadAsync();
    }
    else {
      // Control is already loaded (the page must have been loded through ajax).
      // Update url in settings object.
      
      gofast.AjaxFileBrowserLoader.Settings.SelectedFolder = selected_folder;
      gofast.AjaxFileBrowserLoader.Settings.MsOfficeTemplatesPath = url + '/templates/';

      // Check that update control functions exist before calling it, force 
      // reload otherwise.
     
      if (Object.prototype.toString.call(gofast.ajaxFileBrowser.SetSelectedFolderAsync) === '[object Function]') {
        // Update root folder to be displayed in browser.
        var current_root_url = gofast.ajaxFileBrowser.GetUrl();
        if (current_root_url != root_url || gofast.ajaxFileBrowser.GetSelectedFolder().DisplayName == "Espaces Utilisateurs"){
          gofast.ajaxFileBrowser.SetUrl(root_url, false);
          //gofast.ajaxFileBrowser.SetSelectedFolderAsync(selected_folder, false);
        }
        gofast.ajaxFileBrowser.SetSelectedFolderAsync(selected_folder, false);   
      }
      else {
        forceReload = true;
        LoadAjaxFileBrowser(container);
      }
    }
            
    function onOpenItem(oHierarchyItem) {
      if (oHierarchyItem.ResourceType !== ITHit.WebDAV.Client.ResourceType.Folder) {
        var baseUrl = window.location.protocol + "//" + window.location.host;
     
        // Retrieve the document's nid.
        $jq.ajax({
          url: baseUrl + '/ajax/getnidfromhref',
          data: encodeURI('href=' + oHierarchyItem.Href.replace("&", "%26").replace("+", "%2B")),
          dataType: 'json',
          success : function (data) {
              if (data === false || isNaN(data)) {
              gofast_modal_message(Drupal.t('%filename is unavailable for the moment, but it should be ready within one minute.', {'%filename':oHierarchyItem.DisplayName}));
            }
            else {
              $jq('#AjaxFileBrowserContainer').appendTo('#AjaxFileBrowserContainerContainer');
              //on memorise le chemin courant avant de naviger vers le noeud, pour pouvoir s'en servir comme selectedFolder lorsque l'on fera "back"
              onSelectedFolderChanged();
              YAHOO.util.History.navigate('q', 'node/' + data);
            }
          },
          error : function (jqXHR, textStatus, errorThrown) { }
        });
        return false;
      }
    }
    
    function onShowMenu(menu, aContextMenuHierarchyItems) {

        if (menu.Id != 'FilesViewPanelFileMenu'){
            return;
        }


        // Insert new menu item before 'Copy' menu item.
        var index = getMenuIndexByMenuId(menu, 'Delete');
        if (index != -1) {
            // insert new menu item and separator
            menu.Children.splice(index + 1, 0,

                { Type: 'MenuItem', Text: Drupal.t("Open in a new tab"), OnClick: function(){openInNewTab(aContextMenuHierarchyItems);} },
                { Type: 'MenuSeparator' }
                );
        }
        
        
        // on supprime quelques menu   
        var index = getMenuIndexByMenuId(menu, 'CustomProperties');
        if (index != -1) {
            menu.Children.splice(index, 1);
        }
        var index = getMenuIndexByMenuId(menu, 'Properties');
        if (index != -1) {
            menu.Children.splice(index, 1);
        }
        var index = getMenuIndexByMenuId(menu, 'OpenContainingFolderInFM');
        if (index != -1) {
            menu.Children.splice(index, 1);
        }
        var index = getMenuIndexByMenuId(menu, 'Versions');
        if (index != -1) {
            menu.Children.splice(index, 1);
        }
        
        // Rename 'Update file' menu item.
        var index = getMenuIndexByMenuId(menu, 'UpdateFile');
        if (index != -1) {
            menu.Children[index].Text = Drupal.t('Upload a new version');
        }
    }
    
    
    function openInNewTab(aContextMenuHierarchyItems){
         var baseUrl = window.location.protocol + "//" + window.location.host;
      
        // Retrieve the document's nid.
        $jq.ajax({
          url: baseUrl + '/ajax/getnidfromhref',
          data: 'href=' + aContextMenuHierarchyItems[0].Href.replace("&", "%26").replace("+", "%2B"),
          dataType: 'json',
          success : function (data) {
              if (data === false || isNaN(data)) {
              gofast_modal_message(Drupal.t('%filename is unavailable for the moment, but it should be ready within one minute.', {'%filename':aContextMenuHierarchyItems[0].DisplayName}));
            }
            else {
              var win = window.open("/node/"+data, '_blank');
            }
          },
          error : function (jqXHR, textStatus, errorThrown) { }
        });
        return false;
    }
    
    function onSelectedFolderChanged() {
       var href = gofast.ajaxFileBrowser.GetSelectedFolder().Href;
       var href = href.replace("/alfresco/webdav", "");
      
       setCookie('memorize_last_url_ajax_file_browser',decodeURIComponent(href) , 31536000);
    }
    
    function getMenuIndexByMenuId(menu, menuId) {
        for (var i = 0, l = menu.Children.length; i < l; i++) {
            if (menu.Children[i].Id == menuId) {
               return i;
            }
        }
        return -1;
    }
    
    //on supprime le cookie qui memorise le chemin courant
    deletecookie('memorize_last_url_ajax_file_browser');
  }
}

      
function ceo_vision_fallback_upload_ie9(){
    var selected_folder = gofast.ajaxFileBrowser.GetSelectedFolder();
    var href = selected_folder.Href;
    var destination = href.replace(/\//g, "_");
    destination = destination.replace("_alfresco_webdav", "");
    destination = destination.substring(0, destination.length - 1);
    setCookie("destination", decodeURIComponent(destination), 60*60*24);
    YAHOO.util.History.navigate('q', "user/form_add_document");
}

function sendXHR(method, path, params, async, headers, callback) {
  var xhr = new XMLHttpRequest();
  xhr.open(method, path, async);
  
  Object.prototype.toString.call(callback) === '[object Function]' ?
    xhr.onreadystatechange = callback : xhr.onreadystatechange = handleStateChange;
    
  if (method === 'POST') 
    xhr.setRequestHeader('Content-type', 'application/x-www-form-urlencoded')
  
  if (Object.prototype.toString.call(headers) === '[object Array]') {
    for (var i = 0, len = headers.length; i < len; i++) {
      xhr.setRequestHeader(headers[i].name, headers[i].value);
    }
  }
  
  xhr.send(params);

  function handleStateChange() {
    if (xhr.readyState === 4) {
      // The request is complete
      if (xhr.status >= 200 && xhr.status < 300) {
        // Succeeded, we can check response with xhr.responseText or (for 
        // requests with XML replies) xhr.responseXML.
      }
    }
  }
}

/**
 * Helper function. Displays HTML content in a modal popup.
 * 
 * @param html string<br />
 *  HTML content to display.
 * @param title string [optional]<br />
 *  Set the title of the modal.
 * @param options object [optional]<br />
 *  Fill this object to override modal defaults.
 * @param draggable boolean [optional]<br />
 *  Whether to let the modal be draggable or not (default: true).
 * @param delay number [optional]<br />
 *  Give the modal some time to be processed before running resize and center
 * function. Increment this when encountering modal size issue (default: 200).
 * @param resizable boolean [optional]<br />
 *  Whether to let the modal be resizable or not (default: true).
 * @see <b>ctools/js/modal.js</b> for dealing with modal options overrides.
 */
function gofast_modal(html, title, options, draggable, delay, resizable) {
  gofastAddLoading();
  
  if (typeof html === 'undefined') return gofastRemoveLoading();
  
  var opts = {}, modal;
  options = options || {};
  
  $.extend(true, opts, options);
  draggable = draggable !== false;
  resizable = resizable !== false;
  delay = delay || 200;
  
  Drupal.CTools.Modal.show(opts);
  if (title) $('#modal-title').html(title);
  $('#modal-content').html(html);

  // Les propriétés de l'objet modal mettent un petit temps pour s'actualiser
  // d'où le timeout pour que les fonctions de resize/center s'executent bien.  
  setTimeout(function(){
    modal = $('#modalContent');
    gofastResize(modal);
    modal.center();
    
    gofastRemoveLoading();
    $('#modalBackdrop').add(modal).css('visibility', 'visible');
    
    if (draggable) $jq('#modalContent').draggable({handle:'.modal-header'});
    
    if (resizable) {
      $jq('#modal-content').resizable();
      $jq('.ui-resizable-e, .ui-resizable-s').css({width:'auto', height:'auto'});
      // Release modal content width settings so that resize can work properly.
      $(modal).add('.ctools-modal-content, #modal-content').css({width:'auto', 'max-width':'none'});
    }
  }, delay);
}


function gofast_modal_message(message, title) {
  if (typeof message === 'undefined') return;
  if (typeof title === 'undefined') title = 'GoFast';
  
  message = '<p class="gofast-modal-message">' + message + '</p>';
  var args = [message, title];

  if (arguments.length > 2) {
    // Allow gofast_modal() parameters to be passed.
    for (var i = 2; i < arguments.length; i++) {
      args.push(arguments[i]);
    }
  }
  else {
    // Pass in messages defaults.
    args = args.concat([{modalSize:{width:'500px'}}, true, 200]);
  }

  gofast_modal.apply(undefined, args);
}


Drupal.behaviors.removeCurrentAvatar = function () {
  $jq('#edit-field-imagefield-crop-0-filefield-remove:not(.remove-processed)').addClass('remove-processed').mousedown(function() {    
    setTimeout(function() {
      $jq('.jcrop-preview-wrapper').css({display:'none'});
    }, 500);
  });
};




//class Test {
//
//    static function myHandler( msg : String, stack : Array<String> ) {
//        js.Lib.alert(msg);
//        return true;
//    }
//
//    static function main() {
//        js.Lib.setErrorHandler(myHandler);
//        throw "Error";
//    }
//}


// right click  
// //  var test = $('#switch-lang:not(.tested)').addClass('tested');
//  if (test.length) {
//    test[0].oncontextmenu = function() { return false; };
//    test.mousedown(function(e) {
//      if (e.button === 2) console.log(location.href);
//    });
//  }