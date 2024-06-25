(function($, Drupal, Gofast) {
  Gofast = Gofast || {};

  Gofast.tabletOrientationHandler = function(e, showBackdrop = false) {
    // don't show landscape mode backdrop on document pages
    if (!showBackdrop && Gofast.get("node").type == "alfresco_item" && new RegExp(/^\/node\/(\d)+$/).test(location.pathname)) {
      $("#landscape-backdrop").addClass("d-none");
    } else {
      $("#landscape-backdrop").removeClass("d-none");
    }
  };

  $(document).ready(function() {

    $('#edit-show-password').removeAttr('checked');

    $(document).on('change', '#edit-show-password', function(e) {
      var type = $('#edit-pass').attr('type');
      $('#edit-pass').attr('type', type === 'password' ? 'text' : 'password');
    });

    $('.gofast_mobile_link[href="/browser"]').click(function(e){
      if($(window).width() >= 768){
        window.location.href = "/gofast/browser";
        e.preventDefault();
      }
    });

    if (Gofast.isTablet()) {
      // init
      Gofast.tabletOrientationHandler();
      // update
      $(document).on('ajax-navigate ajax-browser-navigate', Gofast.tabletOrientationHandler);
    }
  });

  Drupal.behaviors.annotateButonShowHide = {
    attach: function () {
          var pathname = window.location.pathname; // Returns path
          var isNode = pathname.indexOf("node/"); // path exist
          if (isNode >= 0) { // 0 or more = we are in the node path
            // show "Mode Annotate" when we are in node path
            if (Drupal.settings.isEssential) {
              setTimeout(function () { $("#pdf_frame").contents().find("#gfPresentationMode").show(); }, 3000);
            }
          }
    }
  };

  Drupal.behaviors.homeNavigation = {
    attach: function (context, settings) {
      $('.navigation_simplified:not(.navigation_simplified_processed)').addClass('navigation_simplified_processed').each(function () {
        $('.navigation_simplified_processed a[data-toggle="tab"]:not(".disabled")').click(function (e) {
          $(this).tab('show');
          $('html, body').scrollTop(0);
        });
        if (location.hash !== '') {
          $('.navigation_simplified_processed a[href="' + location.hash + '"]').tab('show');
          $('html, body').scrollTop(0);
        }
        $('.navigation_simplified_processed a[data-toggle="tab"]').on('shown.bs.tab', function (e) {
          var location_parts = $(e.target).attr('href').split('#');
          if (location_parts[1] == "navBrowser") {
            Gofast.ITHit.reset_full_browser_size();
          }
          $('html, body').scrollTop(0);
          return location.hash = location_parts[1];
        });
      });
    }
  };

  Drupal.behaviors.initSliderBar = {
    attach: function () {
      var navbarHeight = $('#navbar').height();
      $('#mySidebar').css('top', navbarHeight);
      $('#mySidebar').css('width', '250px');
      Gofast.triggerNav = function (){
        if($('.gofast_mobile_sidebar').css('display') == 'none'){
          $('.gofast_mobile_sidebar').css('display','block');
        }else{
          $('.gofast_mobile_sidebar').css('display', 'none');
        }
      }

      $(".gofast_mobile_sidebar ul li a[data-toggle!=collapse]").click(function(){
        $('.gofast_mobile_sidebar').css('display', 'none');
      });
    }
  }

  Drupal.behaviors.kanbanChange = {
    attach: function () {
       $(".gf_kanban_simplified:not(.kanban_processed)").addClass("kanban_processed").each(function () {
          $('select#select-gid-kanban').change(function(e){
            var mobile_nid = $(this).children("option:selected").val();
            Gofast.Poll.abort(); // stop pool to reset our context
            Gofast._settings.gofast.context.mobile_nid = mobile_nid;

            $('.gf_kanban_simplified').data('kid', mobile_nid);
            $('#gofastKanban').data('kid', mobile_nid);
            Gofast.reInitKanban(mobile_nid);
            Gofast.Poll.run();
          });
          Gofast._settings.gofast.context.mobile_nid = jQuery("#select-gid-kanban").val();
          //Gofast.reloadKanbanFromPolling(mobile_nid);
        });
      }
    }

  Drupal.behaviors.scrollTopNav = {
    attach: function () {
      $('.navigation_simplified .nav a').on('shown.bs.tab', function () {
        $(window).scrollTop(0);
      })
    }
  }

  // Show sidebar with filters / meta block.
  Drupal.behaviors.toogleSideContent = {
    attach: function () {
        $("[id^='side-content-toggle']").once().on('click', function () {
          var mobile = $('.is-mobile');
          if (mobile.hasClass('open')) {
            mobile.removeClass('open');
          } else {
            mobile.addClass('open');
          }
        })
    }
  }

})(jQuery, Drupal, Gofast);
