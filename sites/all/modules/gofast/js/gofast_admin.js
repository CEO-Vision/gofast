(function ($, Gofast, Drupal) {
  Drupal.behaviors.loadSettingsGeneral = {
    attach: function(context, settings){
      if($(".edit-general").length !== 0 && !$(".edit-general").hasClass('processed')){
        $(".edit-general").addClass('processed');
        $(".vertical-tabs-panes").find('fieldset').not("#edit-retention").html('<div class="loader-settings"></div>');
        $('form[id^="gofast-admin-settings"]')[0].outerHTML = $('form[id^="gofast-admin-settings"]')[0].outerHTML.replace("<form", "<div").replace('</form>', '</div>');
        loadSettingsTab('edit-general');

        jQuery('a[href^="#edit-smtp"]').not('.processed').click(function(){if(!jQuery('a[href="#edit-smtp"]').hasClass('processed')){loadSettingsTab('edit-smtp'); $('a[href="#edit-smtp"]').addClass('processed');}});
        jQuery('a[href^="#edit-rssfeeds"]').not('.processed').click(function(){if(!jQuery('a[href="#edit-rssfeeds"]').hasClass('processed')){loadSettingsTab('edit-rssfeed'); $('a[href="#edit-rssfeeds"]').addClass('processed');}});
        jQuery('a[href^="#edit-ldap"]').not('.processed').click(function(){if(!jQuery('a[href="#edit-ldap"]').hasClass('processed')){loadSettingsTab('edit-ldap'); $('a[href="#edit-ldap"]').addClass('processed');}});
        jQuery('a[href^="#edit-users"]').not('.processed').click(function(){if(!jQuery('a[href="#edit-users"]').hasClass('processed')){loadSettingsTab('edit-users'); $('a[href="#edit-users"]').addClass('processed');}});
        jQuery('a[href^="#edit-documents"]').not('.processed').click(function(){if(!jQuery('a[href="#edit-documents"]').hasClass('processed')){loadSettingsTab('edit-documents'); $('a[href="#edit-documents"]').addClass('processed');}});
        jQuery('a[href^="#edit-spaces"]').not('.processed').click(function(){if(!jQuery('a[href="#edit-spaces"]').hasClass('processed')){loadSettingsTab('edit-spaces'); $('a[href="#edit-spaces"]').addClass('processed');}});
        jQuery('a[href^="#edit-sso"]').not('.processed').click(function(){if(!jQuery('a[href="#edit-sso"]').hasClass('processed')){loadSettingsTab('edit-sso'); $('a[href="#edit-sso"]').addClass('processed');}});
        jQuery('a[href^="#edit-indexing"]').not('.processed').click(function(){if(!jQuery('a[href="#edit-indexing"]').hasClass('processed')){loadSettingsTab('edit-indexing'); $('a[href="#edit-indexing"]').addClass('processed');}});
        jQuery('a[href^="#edit-integrity"]').not('.processed').click(function(){if(!jQuery('a[href="#edit-integrity"]').hasClass('processed')){loadSettingsTab('edit-integrity'); $('a[href="#edit-integrity"]').addClass('processed');}});
        jQuery('a[href^="#edit-categories"]').not('.processed').click(function(){if(!jQuery('a[href="#edit-categories"]').hasClass('processed')){loadSettingsTab('edit-categories'); $('a[href="#edit-categories"]').addClass('processed');}});
        jQuery('a[href^="#edit-visibility"]').not('.processed').click(function(){if(!jQuery('a[href="#edit-visibility"]').hasClass('processed')){loadSettingsTab('edit-visibility'); $('a[href="#edit-visibility"]').addClass('processed');}});
        jQuery('a[href^="#edit-retention"]').not('.processed').click(function(){if(!jQuery('a[href="#edit-retention"]').hasClass('processed')){loadSettingsTab('edit-retention'); $('a[href="#edit-retention"]').addClass('processed');}});
        jQuery('a[href^="#edit-signature"]').not('.processed').click(function(){if(!jQuery('a[href="#edit-signature"]').hasClass('processed')){loadSettingsTab('edit-signature'); $('a[href="#edit-signature"]').addClass('processed');}});
        jQuery('a[href^="#edit-pastell"]').not('.processed').click(function(){if(!jQuery('a[href="#edit-pastell"]').hasClass('processed')){loadSettingsTab('edit-pastell'); $('a[href="#edit-pastell"]').addClass('processed');}});
        jQuery('a[href^="#edit-update"]').not('.processed').click(function(){if(!jQuery('a[href="#edit-update"]').hasClass('processed')){Gofast.processAjax("/admin/config/gofast/update"); $('a[href="#edit-retention"]').addClass('processed');}});

      }
    }
  };

  Drupal.behaviors.processCategories = {
    attach: function(context, settings){
      var form = $("#gofast-admin-category-settings-form");
      if(form.length > 0 && ! form.hasClass('processed')){
        form.addClass('processed');

        //Hide unwanted tabs
        form.find('fieldset[id^="edit-add-edit-"]').not('#edit-add-edit-0').hide();

        //Bind events on dropdown
        form.find('select#edit-add-edit-action').change(function() {
          var selectedValue = parseInt($(this).val());

          //Hide other fieldsets
          form.find('fieldset[id^="edit-add-edit-"]').hide();

          //Display corresponding fieldset
          var fieldset = form.find('#edit-add-edit-' + selectedValue);
          fieldset.show();
        });
      }
    }
  };
  Gofast.loadSettingsTab = function(tab){
      loadSettingsTab(tab);
  }
  function loadSettingsTab(tab){
    $.post(location.origin + "/admin/config/gofast/global/getform/" + tab, function(output){
      var form = JSON.parse(output)['html'];
      var container = $("." + tab).html(form);
      Drupal.attachBehaviors();
      attachSettingsFormAjax(container, tab);
    });
  }

  function attachSettingsFormAjax(container, tab){
    $(container).find('form').submit(function(event) {
        //Submit this form in ajax
        event.preventDefault();
        var form = $(this);
        Gofast.addLoading();
        $.ajax({
          type: form.attr('method'),
          url: form.attr('action'),
          data: new FormData(this),
          processData: false,
          contentType: false,
        }).done(function(data) {
          try{
            var html = JSON.parse(data)['html'];
          }catch(e){
            Gofast.toast(data, 'error');
            Gofast.removeLoading();
          }
          var new_container = $("." + tab).html(html);
          attachSettingsFormAjax(new_container, tab);
          Drupal.attachBehaviors();
          var errors = JSON.parse(data)['error'];
          if(errors === null){
            Gofast.toast(Drupal.t('Your configuration has been saved.'), 'success');
          }else{
            $.each(errors, function(k, error){
              Gofast.toast(error, 'error');
            });
          }
          Gofast.removeLoading();
        }).fail(function(data) {
          Gofast.toast(data, 'error');
          Gofast.removeLoading();
        });
    });
  }

  /**
   * Binds LDAP 'Test connection' button to a connection attempt that returns
   * connection + binding status.
   */
  Drupal.behaviors.gofastLDAPConnectionTest = {
    attach: function (context, settings) {
      if($('#ldap-connection-test').length == 0){
        return;
      }
      $('#ldap-connection-test', context).once('ldap-connect', function () {
        $(this).on('click', function () {
          var serverProperties = {},
                  serverPropList = ["sid", "name", "ldap_type", "address", "port", "tls", "followrefs", "binding_service_acct", "binddn", "bindpw", "basedn"],
                  ldapAdminForm = $(this).closest('form');

          serverPropList.forEach(function (prop, i) {
            var element = $('[name="' + prop + '"]', ldapAdminForm),
                    type = element.length && element.get(0).type || '',
                    check = {checkbox: 1, radio: 1},
            value = type in check ? element.prop('checked') && 1 || 0 : element.val();

            // Prevents sending undefined values to let server fallback with
            // its own defaults.
            if (typeof value !== undefined) {
              serverProperties[prop] = value;
            }
          });

          $.ajax({
            type: 'POST',
            url: '/admin/config/gofast/ldap/test-connection',
            data: {ldapConnectionTest: serverProperties},
            dataType: 'json',
            'beforeSend': function (xhr) {
              Gofast.xhrPool = Gofast.xhrPool || {};
              Gofast.xhrPool.xhrTestLdapConnection = xhr;  // before jQuery send the request we will add it into our object
            },
            'complete': function () {
              delete Gofast.xhrPool.xhrTestLdapConnection;
            },
            error: function (response) {
              console.log(response);
            },
            success: function (response) {
              console.log('success');
              var statusEl = $('#ldap-connection-status');
              response.connectionStatus === true ?
                      statusEl.css({color: 'green'}).html(Drupal.t('Connection performed successfully.', {}, {'context' : 'gofast:gofast_ldap'})) :
                      statusEl.css({color: 'red'}).html(Drupal.t('Connection failed.', {}, {'context' : 'gofast:gofast_ldap'}));
            }
          });
        });
      });
    }
  };

  /**
   * Button to force synchronization
   */
  Drupal.behaviors.forceSynch = {
    attach: function (context, settings) {
      if($('#edit-force-sync').length == 0){
        return;
      }
      $('#edit-force-sync', context).once('synchronize', function () {
        $(this).on('click', function (e) {
          e.preventDefault();
          Gofast.addLoading();
          $.post( "/gofast/variable/set", { name: "gofast_ldap_last_sync", value: "1" }).done(function( data ) {
            $('#gofast-admin-ldap-settings-form').submit();
          });
        });
      });
    }
  };
})(jQuery, Gofast, Drupal);

