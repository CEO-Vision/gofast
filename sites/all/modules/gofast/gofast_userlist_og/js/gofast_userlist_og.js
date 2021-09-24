(function ($, Gofast, Drupal) {
  'use strict';
  Drupal.behaviors.UserlistAutocompleteExtraInfo = {
    attach: function (context, settings) {

      var slideInfo = {
        init: function () {
          var that = this;
          var $autocompleteFields = $('.form-autocomplete', this.config.$autocompleteContainers);
          
          /*
          $autocompleteFields.each(function () {
            that.processAutocompleteResult(this);
          });
          */

          $autocompleteFields.once('gofast_userlist_og').on('autocompleteSelect', function (event, node) {            
            that.processAutocompleteResult(node);
          });
        },
        processAutocompleteResult: function (field) {

          var etid = $(field).find('.labelize-metadata').data('id');
          var entity_type = $(field).find('.labelize-metadata').data('type');

          //console.log('etid ='+etid+' - of type ='+entity_type);          
          this.storeExtraInfo(etid, entity_type);

        },
        storeExtraInfo : function(entity_id, entity_type){
           this.config.$autocompleteContainers.find('input[name="member_entity_type"]').val(entity_type);
           this.config.$autocompleteContainers.find('input[name="member_entity_id"]').val(entity_id);

        },
        config: {
          throbber: '',
          slideInfoRequestPath: Drupal.settings.basePath + 'gofast_userlist_og_autocomplete/',
          $autocompleteContainers: $('#edit-og-user-body', context)
        }
      };
      slideInfo.init();

    }
  };


})(jQuery, Gofast, Drupal);