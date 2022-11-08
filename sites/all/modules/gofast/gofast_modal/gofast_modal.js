
/**
 * @file
 *
 * Overrides for CTools Modal.
 *
 */

(function ($, Drupal, Gofast) {
  if (!(Drupal && Drupal.CTools && Drupal.CTools.Modal)) {
    console.error('CTools modal is not loaded.');
    return;
  }

  Drupal.gofast_modal = Drupal.gofast_modal || {};


  /**
   * Click function for modals that can be cached.
   */
  Drupal.CTools.Modal.clickAjaxCacheLink = function () {
    Gofast.addLoading();
    Drupal.CTools.Modal.show(Drupal.CTools.Modal.getSettings(this));
    return Drupal.CTools.AJAX.clickAJAXCacheLink.apply(this);
  };

  /**
   * Handler to prepare the modal for the response
   */
  Drupal.CTools.Modal.clickAjaxLink = function () {
    Gofast.addLoading();
    Drupal.CTools.Modal.show(Drupal.CTools.Modal.getSettings(this));
    return false;
  };

  Drupal.CTools.Modal.show = function(choice) {
    var opts = {};

    if (choice && typeof choice === 'string' && Drupal.settings[choice]) {
      // This notation guarantees we are actually copying it.
      $.extend(true, opts, Drupal.settings[choice]);
    }
    else if (choice) {
      $.extend(true, opts, choice);
    }

    var defaults = {
      modalTheme: 'CToolsModalDialog',
      throbberTheme: 'CToolsModalThrobber',
      animation: 'show',
      animationSpeed: 'fast',
      modalSize: {
        type: 'fixed',
        width: 'auto',
        height: 'auto',
        addWidth: 0,
        addHeight: 0,
        // How much to remove from the inner content to make space for the
        // theming.
        contentRight: 25,
        contentBottom: 45
      },
      modalOptions: {
        // Check IE 10 backdrop opacity bug
        opacity: 0.55,
        background: '#000'
      },
      modalContentOptions: {
        overflow: 'auto'
      },
      draggable: true,
      resizable: true
    };

    var settings = {};
    $.extend(true, settings, defaults, Drupal.settings.CToolsModal, opts);

    if (Drupal.CTools.Modal.currentSettings && Drupal.CTools.Modal.currentSettings !== settings) {
      Drupal.CTools.Modal.modal.remove();
      Drupal.CTools.Modal.modal = null;
    }

    Drupal.CTools.Modal.currentSettings = settings;
    Drupal.CTools.Modal.initSettings = settings;

    if (!Drupal.CTools.Modal.modal) {
      Drupal.CTools.Modal.modal = $(Drupal.theme(settings.modalTheme));
      // Eventually no need to trigger this function on resize.
//      if (settings.modalSize.type === 'scale') {
//        $(window).bind('resize', resize);
//      }
    }

    if ($(".dropdown-menu")) $(".dropdown-menu").removeClass("show");

    $('body').addClass('modal-open');

    //Close any opened menu
    $(".gofast-node-actions").removeClass('open').addClass('close');

    $('.modal-title', Drupal.CTools.Modal.modal).html(settings.loadingText);
    Drupal.CTools.Modal.modalContent(Drupal.CTools.Modal.modal, settings.modalOptions, settings.animation, settings.animationSpeed);
    $('#modalContent .modal-body').html(Drupal.theme(settings.throbberTheme));

    $(document).bind('keydown', function(event) {
      if (event.keyCode == 27 && !$('#modalContent').length) {
        $('body').removeClass('modal-open');
        return false;
      }
    });

    if (settings.modalSize.type !== 'scale') {
      Gofast.apply(settings.modalContentOptions, {
        'max-height': Gofast.getWindowHeight() *.8,
        'max-width': Gofast.getWindowWidth() *.8
      });
    }

    $('#modal-content').css(settings.modalContentOptions);
  };

  /**
   * modalContent
   * @param content string to display in the content box
   * @param css obj of css attributes
   * @param animation (fadeIn, slideDown, show)
   * @param speed (valid animation speeds slow, medium, fast or # in ms)
   * @param modalClass class added to div#modalContent
   */
  Drupal.CTools.Modal.modalContent = function(content, css, animation, speed, modalClass) {
    // If our animation isn't set, make it just show/pop
    if (!animation) {
      animation = 'show';
    }
    else {
      // If our animation isn't "fadeIn" or "slideDown" then it always is show
      if (animation != 'fadeIn' && animation != 'slideDown') {
        animation = 'show';
      }
    }

    if (!speed) {
      speed = 'fast';
    }

    // Build our base attributes and allow them to be overriden
    css = jQuery.extend({
      position: 'absolute',
      left: '0px',
      margin: '0px',
      background: '#000',
      opacity: '.55'
    }, css);

    // Add opacity handling for IE.
    css.filter = 'alpha(opacity=' + (100 * css.opacity) + ')';
    content.hide();

    // If we already have modalContent, remove it.
    if ($('#modalBackdrop').length) $('#modalBackdrop').remove();
    if ($('#modalContent').length) $('#modalContent').remove();

    // Get our dimensions

    // Get the docHeight and (ugly hack) add 50 pixels to make sure we dont have a *visible* border below our div
    var docHeight = $(document).height() + 50;
    var docWidth = $(document).width();
    var winHeight = $(window).height();
    if ( docHeight < winHeight ) docHeight = winHeight;

    // Create our divs
    $('body').append('<div id="modalBackdrop" class="backdrop-' + modalClass + '" style="z-index: 1000; display: none;"></div><div id="modalContent" class="modal-' + modalClass + '" style="z-index: 1001; position: absolute;">' + $(content).html() + '</div>');

    // Get a list of the tabbable elements in the modal content.
    var getTabbableElements = function () {
      var tabbableElements = $('#modalContent :tabbable'),
          radioButtons = tabbableElements.filter('input[type="radio"]');

      // The list of tabbable elements from jQuery is *almost* right. The
      // exception is with groups of radio buttons. The list from jQuery will
      // include all radio buttons, when in fact, only the selected radio button
      // is tabbable, and if no radio buttons in a group are selected, then only
      // the first is tabbable.
      if (radioButtons.length > 0) {
        // First, build up an index of which groups have an item selected or not.
        var anySelected = {};
        radioButtons.each(function () {
          var name = this.name;

          if (typeof anySelected[name] === 'undefined') {
            anySelected[name] = radioButtons.filter('input[name="' + name + '"]:checked').length !== 0;
          }
        });

        // Next filter out the radio buttons that aren't really tabbable.
        var found = {};
        tabbableElements = tabbableElements.filter(function () {
          var keep = true;

          if (this.type == 'radio') {
            if (anySelected[this.name]) {
              // Only keep the selected one.
              keep = this.checked;
            }
            else {
              // Only keep the first one.
              if (found[this.name]) {
                keep = false;
              }
              found[this.name] = true;
            }
          }

          return keep;
        });
      }

      return tabbableElements.get();
    };

    // Keyboard and focus event handler ensures only modal elements gain focus.
    modalEventHandler = function( event ) {
      var target = null;
      if ( event ) { //Mozilla
        target = event.target;
      } else { //IE
        event = window.event;
        target = event.srcElement;
      }

      var parents = $(target).parents().get();
      for (var i = 0; i < parents.length; ++i) {
        var position = $(parents[i]).css('position');
        if (position == 'absolute' || position == 'fixed') {
          return true;
        }
      }

      if ($(target).is('#modalContent, body') || $(target).filter('*:visible').parents('#modalContent').length) {
        // Allow the event only if target is a visible child node
        // of #modalContent.
        return true;
      }
      else {
        var tabbableElements = getTabbableElements();
        if (!tabbableElements.length) {
          return;
        }
        getTabbableElements()[0].focus();
      }

      event.preventDefault();
    };
    $('body').bind( 'focus', modalEventHandler );
    $('body').bind( 'keypress', modalEventHandler );

    // Keypress handler Ensures you can only TAB to elements within the modal.
    // Based on the psuedo-code from WAI-ARIA 1.0 Authoring Practices section
    // 3.3.1 "Trapping Focus".
    modalTabTrapHandler = function (evt) {
      // We only care about the TAB key.
      if (evt.which != 9) {
        return true;
      }

      var tabbableElements = getTabbableElements(),
          firstTabbableElement = tabbableElements[0],
          lastTabbableElement = tabbableElements[tabbableElements.length - 1],
          singleTabbableElement = firstTabbableElement == lastTabbableElement,
          node = evt.target;

      // If this is the first element and the user wants to go backwards, then
      // jump to the last element.
      if (node == firstTabbableElement && evt.shiftKey) {
        if (!singleTabbableElement) {
          lastTabbableElement.focus();
        }
        return false;
      }
      // If this is the last element and the user wants to go forwards, then
      // jump to the first element.
      else if (node == lastTabbableElement && !evt.shiftKey) {
        if (!singleTabbableElement) {
          firstTabbableElement.focus();
        }
        return false;
      }
      // If this element isn't in the dialog at all, then jump to the first
      // or last element to get the user into the game.
      else if ($.inArray(node, tabbableElements) == -1) {
        // Make sure the node isn't in another modal (ie. WYSIWYG modal).
        var parents = $(node).parents().get();
        for (var i = 0; i < parents.length; ++i) {
          var position = $(parents[i]).css('position');
          if (position == 'absolute' || position == 'fixed') {
            return true;
          }
        }

        if (evt.shiftKey) {
          lastTabbableElement.focus();
        }
        else {
          firstTabbableElement.focus();
        }
      }
    };
    $('body').bind('keydown', modalTabTrapHandler);

    // Create our content div, get the dimensions, and hide it
    var modalContent = $('#modalContent').remove();

  }

  Drupal.CTools.Modal.closeOnBlur = function(bool) {
    $(".modal:not('#gofastKanbanModal')").first().data("bs.modal")._config.backdrop = bool ? true : "static";
  }

  /**
   * AJAX responder command to place HTML within the modal.
   */
  Drupal.CTools.Modal.modal_display = function(ajax, response, status) {
    var target = "#gofast_basicModal";

    if (ajax.allowStretch != undefined && ajax.allowStretch == true) {
      $("#modal-content").removeClass("w-100");
    }

    // Recenter modal
    $(target).css({
      top: 0,
      left: 0
    });

    $('#modal-title').html(response.title);

    /// In some cases classes are added to the object, then we deleted to prevent CSS override (exemple : modal-workflow)
    $(target + ' #modal-content').removeClass();
    $(target + ' #modal-content').addClass('modal-body');
    // Simulate an actual page load by scrolling to the top after adding the
    // content. This is helpful for allowing users to see error messages at the
    // top of a form, etc.
    $('#modal-content').html(response.output).scrollTop(0);

    if ($('#modal-content').hasClass('ctools-modal-loading')) {
      $('#modal-content').removeClass('ctools-modal-loading');
    }
    else {
      // If the modal was already shown, and we are simply replacing its
      // content, then focus on the first focusable element in the modal.
      // (When first showing the modal, focus will be placed on the close
      // button by the show() function called above.)
      $('#modal-content :focusable:first').focus();
    }

    // Render modal draggable
    $(target).draggable({ handle: '.modal-header' });

    if($('#modal-content #remove_from_cart').length) {
        const linkRemoved = $('#remove_from_cart').detach();
        const btnCartActions = $('#cart_toolbar_manage').detach();
        const btnCart = $('#modal-content button').detach();

        $('#modal-footer').html(btnCartActions);
        $('#modal-footer').append(btnCart);
        $('#modal-footer').append(linkRemoved);
    }else{
      var button = $('#modal-content .btn:not(.no-footer)').clone();
      $('#modal-content .btn:not(.no-footer)').hide();
      $('#modal-footer').html(button);

      // Remove form actions from content
      $('.node-forum-form .card-footer').attr('style', 'display: none !important')
      $('#modal-footer button').click(function (e) {
        e.preventDefault();
        e.stopPropagation();
        var _buttonIdFooter = $(this).attr('id');
        var _buttonIdContent = $('#modal-content #' + _buttonIdFooter);

        // Fix probleme on some modals with submit button with mousedown event
        var events = $._data(_buttonIdContent[0], "events");
        if(events != undefined && events.mousedown != undefined && events.mousedown.length != 0){
          $(_buttonIdContent).trigger('mousedown');
        }

        $(_buttonIdContent).trigger('click');
      });
    }

    //Allow to put custom elements in the footer
    if($('.modal-footer-element').length){
      var footer_element = $('.modal-footer-element');
      footer_element.detach().appendTo($('#modal-footer'));
    }

    // Change size of modal (depend of content)
    $(target + " .modal-dialog").addClass('modal-xl');

    if($('#modal-content #bonita_form_process').length != 0 || $('#modal-content #bonita_form').length != 0){
        setTimeout(function(){$('.modal-content').css("min-width", "850px");}, 1800);
         setTimeout(function(){$('.modal-content').css("width", "auto");}, 1800);
    }
    Drupal.attachBehaviors();

    Gofast.removeLoading();
    $(target).modal('show').data('triggered', false);

    //Remove backdrop when we have a comment modal
    if($('.comment-form').length>0) {
        $('.modal-backdrop.fade.show').hide();
        Drupal.CTools.Modal.closeOnBlur(false);
        return;
    }
    Drupal.CTools.Modal.closeOnBlur(true);
  };



  Drupal.CTools.Modal.dismiss = function() {
    var target = "#gofast_basicModal";
    $(target).modal('hide');
  };

  /**
   * Provide the HTML to create a nice looking loading progress bar.
   */
  Drupal.theme.prototype.CToolsModalThrobber = function () {
    var html = '';
    html += '<div class="loading-spinner" style="width: 200px; margin: -20px 0 0 -100px; position: absolute; top: 45%; left: 50%">';
    html += '  <div class="progress progress-striped active">';
    html += '    <div class="progress-bar" style="width: 100%;"></div>';
    html += '  </div>';
    html += '</div>';

    return html;
  };

  Gofast.manage_archive_process = function() {
    var panels = $(".manage-archive-panel");
    var panelsProgressBar = $("#archives-panels-progress .progress-bar");
    var numberOfPanels = panels.length;
    var processedPanels = 0;

    //For each panel, process the request and check the result
    $.each(panels, function(i, panel) {
      var nid = $(panel).find('#nid').text();
      $.post(location.origin + "/cmis/manage_archives/process", { process_nid : nid }).done(function(data) {
        let success = false;
        if(data == "succesfully_archived") {
            $(panel).find('.panel-body').find('ul').find('li').append("<i class='fa fa-check' style='color:green' aria-hidden='true'></i>");
            $(panel).find('.panel-body').find(".manage-archive-info").html("<i class='fa fa-check' style='color:red' aria-hidden='true'></i> " + Drupal.t("This document has succesfully been archived", {}, {context: 'gofast:cmis'}));
            success = true;
        }
        if (data == "already_archived") {
            $(panel).find('.panel-body').find('ul').find('li').append("<i class='fa fa-times' style='color:red' aria-hidden='true'></i>");
            $(panel).find('.panel-body').find(".manage-archive-info").html("<i class='fa fa-times' style='color:red' aria-hidden='true'></i> " + Drupal.t("This document is already an archive!", {}, {context: 'gofast:cmis'}));
            success = true;
        }
        if (success) {
            // update progress bar
            processedPanels++;
            const progressWidth = Math.round((100 / numberOfPanels) * processedPanels);
            panelsProgressBar.css({width: progressWidth + "%"});
            panelsProgressBar.attr("aria-valuenow", progressWidth);
            // panelsProgressBar.html(processedPanels + " / " + numberOfPanels);
            panelsProgressBar.html(progressWidth + "%");
        }
      });
    });
  }

  Drupal.behaviors.cancelButton = {
    attach: function (context, settings) {
      $('#modal-content #edit-cancel').click(function (e) {
        e.preventDefault();
        e.stopPropagation();
        Drupal.CTools.Modal.dismiss();
      });
    }
  };        
  
  $(document).ready(function() {
    $(document).on('flagGlobalAfterLinkUpdate', function(e, data) {
      var response = data.ajax_data;
      for (var i in response) {
        if (response.hasOwnProperty(i) && response[i]['command'] && Drupal.ajax.prototype.commands[response[i]['command']]) {
          Drupal.ajax.prototype.commands[response[i]['command']](Drupal.ajax.prototype, response[i], 'success');
        }
      }
    });
    $(document).on("hidden.bs.modal", function(e) {
      $('#modal-footer').removeClass('d-none').addClass('d-flex');
      $("#modal-content").addClass("w-100"); // put modal width back to default
    });
  });


})(jQuery, Drupal, Gofast);
