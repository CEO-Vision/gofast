(function ($, Drupal, Gofast) {

  Drupal.behaviors.verticalTabs = {
    attach: function (context) {
      $('.vertical-tabs-panes:not(".vertical-tabs-processed")').addClass('vertical-tabs-processed').each(function () {
        $(this).addClass('tab-content');
        var focusID = $(':hidden.vertical-tabs-active-tab', this).val();
        if (typeof focusID === 'undefined' || !focusID.length) {
          focusID = false;
        }
        var tab_focus;

        // Check if there are some fieldsets that can be converted to vertical-tabs
        var $fieldsets = $('> fieldset', this);
        if ($fieldsets.length === 0) {
          return;
        }

        // Create the tab column.
        var tab_list = $('<ul class="nav nav-tabs vertical-tabs-list"></ul>');
        $(this).wrap('<div class="tabbable tabs-left vertical-tabs clearfix"></div>').before(tab_list);

        // Transform each fieldset into a tab.
        $fieldsets.each(function () {
          var vertical_tab = new Drupal.verticalTab({
            title: $('> legend', this).text(),
            fieldset: $(this)
          });
          tab_list.append(vertical_tab.item);
          $(this)
                  .removeClass('collapsible collapsed panel panel-default')
                  .addClass('tab-pane vertical-tabs-pane')
                  .data('verticalTab', vertical_tab)
                  .find('> legend').remove();
          $(this).find('> div').removeClass('panel-collapse collapse').addClass('fade');
          if (this.id === focusID) {
            tab_focus = $(this);
          }
        });
        
        $('> li:first', tab_list).addClass('first');
        $('> li:last', tab_list).addClass('last');

        if (!tab_focus) {
          // If the current URL has a fragment and one of the tabs contains an
          // element that matches the URL fragment, activate that tab.
          if (window.location.hash && $(this).find(window.location.hash).length) {
            tab_focus = $(this).find(window.location.hash).closest('.vertical-tabs-pane');
          }else if( window.location.search.substring(1).indexOf('template')=== 0){
            tab_focus = $('> .vertical-tabs-pane:eq(1)', this);
          } else {
            tab_focus = $('> .vertical-tabs-pane:first', this);
          }
        }
        if (tab_focus.length) {
          tab_focus.data('verticalTab').focus();
        }
      });
    }
  };

  Drupal.ajax.prototype.commands.success_creating_node = function (ajax, response) {
    if(Gofast.get('dev_mode')) {
      console.log(ajax);
      console.log(response);
    }
    Drupal.CTools.Modal.dismiss();
    if(Drupal.settings.isMobile){
        window.location.href = location.origin + "/" + response.data;
    }else{
        Gofast.processAjax(response.data, false); // Gofast.removeLoading is called inside processAjax function
    }
  };
  Drupal.ajax.prototype.commands.error_creating_node = function (ajax, response) {
    if(Gofast.get('dev_mode')) {
      console.log(ajax);
      console.log(response);
    }
    $('html, body').animate({scrollTop: $('#messages-placeholder').offset().top - $('header').height() - 20}, 'slow');
    $(response.wrapper).html(response.form).promise().done(function() {
      for (var i = 0; i < response.custom_fields.length; i++) {
        var field = response.custom_fields[i].replace(/_/gi, '-');
        if (response.errors.hasOwnProperty(response.custom_fields[i])) {
          $('#edit-' + field).css('border', '1px solid #a94442');
        } else {
          $('#edit-' + field).css('border', '');
        }
      }
      Drupal.attachBehaviors();
      
    });
  };
}(jQuery, Drupal, Gofast));