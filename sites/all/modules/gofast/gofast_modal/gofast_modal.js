
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
    
    var resize = function(e) {
      if (e && e.target && e.target !== window) {
        return;
      }
      
      // Refresh settings.
      var settings = Drupal.CTools.Modal.currentSettings;
      
      // When creating the modal, it actually exists only in a theoretical
      // place that is not in the DOM. But once the modal exists, it is in the
      // DOM so the context must be set appropriately.
      var context = e ? document : Drupal.CTools.Modal.modal;
      var width = 0;
      var height = 0;

      //  Handle fixed navbars. Grab the body top offset in pixels.
      var topOffset = parseInt($('body').css("padding-top"), 10);

      if (settings.modalSize.type === 'scale') {
        width = $(window).width() * settings.modalSize.width;
        height = ($(window).height() - topOffset) * settings.modalSize.height;
      }
      else {
        width = settings.modalSize.width;
        height = settings.modalSize.height;
      }

      // Add padding for the offset.
      $('#modalContent').css('padding-top', topOffset + 'px');
      
      // Use the additionol pixels for creating the width and height.
      var mDialogW = width, mDialogH = height,
          mBodyW = width, mBodyH = height;
  
      if (width === 'auto') {
        // Try to rely on the main content width (that is reponsive).
        var section = $('.main-container section:first');
        width = section.length && section.width() || width;
      }
  
      if (width !== 'auto') {
        mDialogW = width + settings.modalSize.addWidth/* + 'px'*/;
        mBodyW = (width - settings.modalSize.contentRight)/* + 'px'*/;
      }
      if (height !== 'auto') {
        mDialogH = height + settings.modalSize.addHeight/* + 'px'*/;
        mBodyH = (height - settings.modalSize.contentBottom)/* + 'px'*/;
      }
      
      $('div.ctools-modal-dialog', context).css({width: mDialogW, height: mDialogH});
      $('div.ctools-modal-dialog .modal-body', context).css({width: mBodyW, height: mBodyH});
      
      if (!e) {
        // Remember processed width & height on init.
        Gofast.apply(settings.modalContentOptions, {width: mBodyW, height: mBodyH});        
        Gofast.apply(Drupal.CTools.Modal.initSettings, settings);
      }
    };

    if (!Drupal.CTools.Modal.modal) {
      Drupal.CTools.Modal.modal = $(Drupal.theme(settings.modalTheme));
      // Eventually no need to trigger this function on resize.
//      if (settings.modalSize.type === 'scale') {
//        $(window).bind('resize', resize);
//      }
    }

    $('body').addClass('modal-open');

    resize();
    
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
    var modalContent = $('#modalContent').css('top','-1000px');

    $('#modalBackdrop').css(css).css('top', 0).css('height', docHeight + 'px').css('width', docWidth + 'px');

    // Bind a click for closing the modalContent
    modalContentClose = function(){close(); return false;};
    $('.close').bind('click', modalContentClose);

    // Bind a keypress on escape for closing the modalContent
    modalEventEscapeCloseHandler = function(event) {
      if (event.keyCode == 27) {
        close();
        return false;
      }
    };

    $(document).bind('keydown', modalEventEscapeCloseHandler);

    // Per WAI-ARIA 1.0 Authoring Practices, initial focus should be on the
    // close button, but we should save the original focus to restore it after
    // the dialog is closed.
    var oldFocus = document.activeElement;
    $('.close').focus();

    // Close the open modal content and backdrop
    function close() {
      // Unbind the events
      $(window).unbind('resize',  modalContentResize);
      $('body').unbind( 'focus', modalEventHandler);
      $('body').unbind( 'keypress', modalEventHandler );
      $('body').unbind( 'keydown', modalTabTrapHandler );
      $('.close').unbind('click', modalContentClose);
      $('body').unbind('keypress', modalEventEscapeCloseHandler);
      $(document).trigger('CToolsDetachBehaviors', $('#modalContent'));

      // Set our animation parameters and use them
      if ( animation == 'fadeIn' ) animation = 'fadeOut';
      if ( animation == 'slideDown' ) animation = 'slideUp';
      if ( animation == 'show' ) animation = 'hide';

      // Close the content
      modalContent.hide()[animation](speed);

      // Remove the content
      $('#modalContent').remove();
      $('#modalBackdrop').remove();

      // Restore focus to where it was before opening the dialog
      $(oldFocus).focus();
    };

    // Move and resize the modalBackdrop and modalContent on window resize.
    modalContentResize = function(e,verticaly, horizontaly) {
      if(verticaly == undefined){
          verticaly = false;
      }
      if(horizontaly == undefined){
          horizontaly = false;
      }
      if (e && e.target && e.target !== window) {
        return;
      }
      
      var settings = Drupal.CTools.Modal.currentSettings;
      
      if (settings.resizable) {
        if (verticaly == true){
            $('#modalContent .ui-resizable').css({height:'auto'});
        }else if(horizontaly == true){
            $('#modalContent .ui-resizable').css({width:'auto'});
        }else{
            $('#modalContent .ui-resizable').css({width:'auto', height:'auto'});
        }
        if (Drupal.CTools.Modal.delayedTask) {
          clearTimeout(Drupal.CTools.Modal.delayedTask);
        }
        Drupal.CTools.Modal.delayedTask = setTimeout(function() {
          $('#modalContent .ui-resizable').css({
            height: function(){ return $(this).height() },
            width: function(){ return $(this).width() }
          });
          $('#modalContent').add('.ctools-modal-dialog', '#modal-content').css({width: 'auto', 'max-width': 'none'});
        }, 100);
      }
      
      // Reset the backdrop height/width to get accurate document size.
      $('#modalBackdrop').css('height', '').css('width', '');

      // Position code lifted from:
      // http://www.quirksmode.org/viewport/compatibility.html
      var wt = 0;
      if (self.pageYOffset) { // all except Explorer
        wt = self.pageYOffset;
      } else if (document.documentElement && document.documentElement.scrollTop) { // Explorer 6 Strict
        wt = document.documentElement.scrollTop;
      } else if (document.body) { // all other Explorers
        wt = document.body.scrollTop;
      }

      // Get our heights
      var docHeight = $(document).height(),
          docWidth = $(document).width(),
          winHeight = $(window).height(),
          winWidth = $(window).width();
      if ( docHeight < winHeight ) docHeight = winHeight;

      // Get where we should move content to
      var modalContent = $('#modalContent'),
          mdcTop = wt + ( winHeight / 2 ) - ( modalContent.outerHeight() / 2),
          mdcLeft = ( winWidth / 2 ) - ( modalContent.outerWidth() / 2);

      // Apply the changes
      $('#modalBackdrop').css('height', docHeight + 'px').css('width', docWidth + 'px').show();
      modalContent.css('top', mdcTop + 'px').css('left', mdcLeft + 'px').show();
     
      var initWidth = Drupal.CTools.Modal.initSettings.modalContentOptions.width,
          initHeight = Drupal.CTools.Modal.initSettings.modalContentOptions.width,
          css = {};
      if (initWidth > winWidth*.9) css['max-width'] = winWidth *.9;
      if (initHeight > winHeight*.9) css['max-height'] = winHeight *.9;
      if (!$.isEmptyObject(css)) $('#modal-content').css(css);
           
    $('#cke_edit-body-value .cke_resizer_vertical ').css('display','none');
    //Get height of Ckeditor for resizing when the modal is resize
    Gofast.ckeditor_size = $('.cke_contents').height();
    };
 
  }; 
  

  
  
  /**
   * AJAX responder command to place HTML within the modal.
   */
  Drupal.CTools.Modal.modal_display = function(ajax, response, status) {
    if ($('#modalContent').length == 0) {
      Drupal.CTools.Modal.show(Drupal.CTools.Modal.getSettings(ajax.element));
    }

    $('#modal-title').html(response.title);
    // Simulate an actual page load by scrolling to the top after adding the
    // content. This is helpful for allowing users to see error messages at the
    // top of a form, etc.
    $('#modal-content').html(response.output).scrollTop(0);

    // Attach behaviors within a modal dialog.
    var settings = response.settings || ajax.settings || Drupal.settings;
    Drupal.attachBehaviors('#modalContent', settings);

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
    
    var modalContent = $('#modalContent'),
        currentSettings = Drupal.CTools.Modal.currentSettings,
        docHeight = $(document).height() + 50,
        winHeight = $(window).height(),
        winWidth = $(window).width();

    if (docHeight < winHeight) docHeight = winHeight;
    
    // Apply UI behavior before processing modal display to avoid some quirks.
    if (currentSettings.draggable) {
      $('#modalContent').draggable({handle: '.modal-header'});      
    }
    if (currentSettings.resizable && $('.modal-content > .ui-resizable').length <= 0) {
      Drupal.CTools.Modal.resizable();
    }
    
    // Release modal content width settings so that resize can work properly, it
    // also removes superficial padding.
    $('#modalContent').add('.ctools-modal-dialog'/*, #modal-content'*/).css({width: 'auto', 'max-width': 'none'});
    
    // Position code lifted from http://www.quirksmode.org/viewport/compatibility.html
    var wt = 0;
    if (self.pageYOffset) { // all except Explorer
      wt = self.pageYOffset;
    } else if (document.documentElement && document.documentElement.scrollTop) { // Explorer 6 Strict
      wt = document.documentElement.scrollTop;
    } else if (document.body) { // all other Explorers
      wt = document.body.scrollTop;
    }
    
    var mdcTop = wt + ( winHeight / 2 ) - (  modalContent.outerHeight() / 2);
    var mdcLeft = ( winWidth / 2 ) - ( modalContent.outerWidth() / 2);    
    
    // Replace the loading backdrop/throbber with the modal backdrop.
    Gofast.removeLoading();
    if (currentSettings.modalOptions.background !== 'none') {
      $('#modalBackdrop').show();
    }
        
    // Place the modal and display it.
    $("div > a#edit-cancel").hide();
    modalContent.css({top: mdcTop + 'px', left: mdcLeft + 'px'}).hide();
    $('.modal-dialog', modalContent).css({visibility: 'visible'});
    modalContent[currentSettings.animation](currentSettings.speed);
   
  };
  
  Drupal.CTools.Modal.resizable = function() {
    $('#modal-content')
            .wrap('<div/>')
            .parent()
            .css({
              display: 'inline-block',
              overflow: 'hidden',
              //overflow: 'visible',
              height: function(){return $(this).height();},
              width: function(){return $(this).width();}
            })
            .resizable({
              create: function(e, ui) {
                Gofast.initial_size = $('#modalContent .ui-resizable').height();
                Gofast.textarea_size = $('#edit-message').height();
              },
              start: function (e, ui) {
                Gofast.initial_size = $('#modalContent .ui-resizable').height();
                $('#modal-content').css({'max-width':'', 'max-height':''});
              },
              stop: function (e, ui) {
                $('#modal-content').css({
                  'max-height': function(){return $('#modalContent .ui-resizable').height();},
                  'max-width': function(){return $('#modalContent .ui-resizable').width();}     
                })
              }
            })
            .resize(function(){
                Gofast.size_resizing = $('#modalContent .ui-resizable').height();
                Gofast.final_size = Gofast.size_resizing - Gofast.initial_size; 
                Gofast.textarea_size_final = Gofast.textarea_size + Gofast.final_size;
                Gofast.ckeditor_size_final = Gofast.ckeditor_size + Gofast.final_size;
                $('#edit-message').css('height', Gofast.textarea_size_final);
                $('.cke_contents').css('height', Gofast.ckeditor_size_final);
            })  
            .find('#modal-content')
            .css({
              overflow:'auto',
              //overflow: 'visible',
              width:'100%',
              height:'100%'
            });
              //Hide resize parts of textarea in linksharing
      $('.resizable-textarea > #edit-message').css('resize','none');
      $('.resizable-textarea > .grippie').css('display','none');
      $('.ui-resizable-e, .ui-resizable-s').css({width: 'auto', height: 'auto'});
      $('.ui-resizable-se').css({'margin-bottom': '-6px'});
  };

  Drupal.CTools.Modal.dismiss = function() {
    if (Drupal.CTools.Modal.modal) {
      $('body').removeClass('modal-open');
      Drupal.CTools.Modal.unmodalContent(Drupal.CTools.Modal.modal);
    }
  };

  /**
   * Provide the HTML to create the modal dialog in the Bootstrap style.
   */
  Drupal.theme.prototype.CToolsModalDialog = function () {
    var html = '';
    html += '<div id="ctools-modal">';
    html += '  <div class="ctools-modal-dialog modal-dialog" style="visibility:hidden;">';
    html += '    <div class="modal-content">';
    html += '      <div class="modal-header">';
    html += '        <button type="button" class="close ctools-close-modal" aria-hidden="true">&times;</button>';
    html += '        <h5 id="modal-title" class="modal-title">&nbsp;</h5>';
    html += '      </div>';
    html += '      <div id="modal-content" class="modal-body">';
    html += '      </div>';
    html += '    </div>';
    html += '  </div>';
    html += '</div>';

    return html;
  };

  /**
   * Provide the HTML to create the uploading modal dialog in the Bootstrap style.
   */
  Drupal.theme.prototype.uploading_dragdrop = function() {
    var html = '';
    html += '<div id="ctools-modal">';
    html += '  <div id="uploading-modal-dialog" class="ctools-modal-dialog modal-dialog" style="visibility:hidden;">';
    html += '    <div class="modal-content">';
    html += '      <div class="modal-header">';
    html += '        <button type="button" class="close ctools-close-modal" aria-hidden="true">&times;</button>';
    html += '        <h4 id="modal-title" class="modal-title">&nbsp;</h4>';
    html += '      </div>';
    html += '      <div id="modal-content" class="modal-body">';
    html += '      </div>';
    html += '    </div>';
    html += '  </div>';
    html += '</div>';

    return html;
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
  
  $(function() {
    Drupal.ajax.prototype.commands.modal_display = Drupal.CTools.Modal.modal_display;
    Drupal.ajax.prototype.commands.modal_dismiss = Drupal.CTools.Modal.modal_dismiss;
  });
  
  Drupal.behaviors.modalAutoResize = {
    resizeModal: function (modal, ov, ovY) {
      var room = 150,
          modalHeight = modal.innerHeight(),
          modalContentHeight = 0;

      $.each(modal.children(), function(key){
        modalContentHeight += $(this).innerHeight();
      });
  
      if(modalHeight > modalContentHeight) {
        var newHeight = modalContentHeight + 50;
        modal.parent().height(modalHeight).animate({height: newHeight}, {duration: 200, queue: false});
      }

      if (Gofast.getWindowHeight() > modalHeight + room) {
        ov = Gofast.checkOverflow(modal);

        if (ov && ov.y && ov.y > ovY) {
          var newHeight = Math.min(Gofast.getWindowHeight() - room, modalHeight + (ov.y - ovY));

          modal.animate({height: newHeight, maxHeight: newHeight}, {duration: 400, queue: false});

          if (modal.parent().hasClass('ui-resizable')) {
            var uirHeight = modal.parent().height() + (newHeight - modalHeight);
            modal.parent().animate({height: uirHeight}, {duration: 400, queue: false});
          }
        }
      }
    },
    attach: function (context, settings) {
      var modalAutoResizeBehavior = this;
      
      if ($(context).attr('id') !== 'modalContent')
        return;

      $(context).find('.modal-body').once('modalAutoResize', function () {
        var modal = $(this),
                ov = Gofast.checkOverflow(modal),
                ovY = ov && ov.y || 0;

        modal.find('input.autocomplete').on('autocomplete', function () {
          //modalAutoResizeBehavior.resizeModal(modal, ov, ovY);
        });
        
        modal.find('.panel-heading a').on('click', function () {
          setTimeout(function() {
            modalAutoResizeBehavior.resizeModal(modal, ov, ovY);
          }, 200);
        });

        if (typeof CKEDITOR !== 'undefined') {
          CKEDITOR.on('instanceReady', function () {
            modalAutoResizeBehavior.resizeModal(modal, ov, ovY);
          });
        }
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
  });
})(jQuery, Drupal, Gofast);
