(function ($, Drupal, Gofast) {
Drupal.behaviors.formsAttributesFieldsetSummaries = {
  attach: function (context) {
    if ($('fieldset.group-taxonomies').length > 0) {
      $('fieldset.group-taxonomies:not(.group-taxonomies-processed)', context).addClass('group-taxonomies-processed').drupalSetSummary(function (context) {
        var $select_keyword = $('#edit-field-tags-und');
        var val = $select_keyword.val();
       if(val == ""){
           val = Drupal.t("None", {}, {'context' : 'gofast'});
       }
        var string_return_keywords = Drupal.t("Keywords", {}, {'context' : 'gofast'})+":"+" "+val;

        var $select_category = $('#edit-field-category-und');
        var val = $select_category.val();

        if (val === '_none') {
          var string_return_category = Drupal.t("Category", {}, {'context' : 'gofast'}) +" : "+ Drupal.t('None', {}, {'context' : 'gofast'});
        }
        else {
           var string_return_category =  Drupal.t("Category", {}, {'context' : 'gofast'}) +" : "+ Drupal.checkPlain($select_category.find(':selected').text());
        }
        return Drupal.checkPlain(string_return_keywords + " " + string_return_category);
      });
    }
    
  }
};


Drupal.behaviors.formsBookFieldsetSummaries = {
  attach: function (context) {
    if ($('fieldset.group-book').length > 0) {
      $('fieldset.group-book:not(.group-book-processed)', context).addClass('group-book-processed').drupalSetSummary(function (context) {
        var $select = $('.form-item-book-bid select');
        var val = $select.val();

        if (val === '0') {
          return Drupal.t('Not in book', {}, {'context' : 'gofast'});
        }
        else if (val === 'new') {
          return Drupal.t('New book', {}, {'context' : 'gofast'});
        }
        else {
          return Drupal.checkPlain($select.find(':selected').text());
        }
      });
    }
  }
};

Drupal.behaviors.formsStateFieldsetSummaries = {
  attach: function (context) {
    if ($('fieldset.group-state').length > 0) {
      $('fieldset.group-state:not(.group-state-processed)', context).addClass('group-state-processed').drupalSetSummary(function (context) {

        //on recupere dans les settings les id des états de workflow
        if (typeof Drupal.settings.gofast_workflow != 'undefined'){
          var array_states_workflow = JSON.parse(Drupal.settings.gofast_workflow.tid_states);
        } else {
          var array_states_workflow = new Array();
        }
        var $select_state = $('#edit-field-state-und');

        var val = $select_state.val();
        var val_string;
          if(val == "_none"){
              val_string = Drupal.t("None", {}, {'context' : 'gofast'});
          }else{
              val_string = Drupal.checkPlain($select_state.find(':selected').text());
          }

        if(typeof array_states_workflow[val] != 'undefined'){
            //on affiche le champs des validateurs
            $("#field-validators-values").css("display", "block");
        }else{
            $("#field-validators-values").css("display", "none");
            //on vide les champs validateurs
             $('input[id*="edit-field-validators-und-"].form-control').each(function(){      
                $(this).val("");
            });
        }
        var string_return_keywords = Drupal.t("State", {}, {'context' : 'gofast'})+":"+" "+val_string;

        var $select_validators = "";
        $('input[id*="edit-field-validators-und-"].form-control').each(function(){
          $select_validators = $select_validators + " " + $(this).val();
        });

        if ($select_validators === '' || $select_validators === ' ') {
          var string_return_validators = "";
        }
        else {
           var string_return_validators =  Drupal.t("Validators", {}, {'context' : 'gofast'}) +" : "+ $select_validators;
        }
        return Drupal.checkPlain(string_return_keywords + " " + string_return_validators);
      });
    }
  }
};

Drupal.behaviors.formsDeadlineFieldsetSummaries = {
  attach: function (context) {
    if ($('fieldset.group-deadline').length > 0) {
      $('fieldset.group-deadline:not(.group-deadline-processed)', context).addClass('group-deadline-processed').drupalSetSummary(function (context) {

        var $input_deadline = $('#edit-field-date-und-0-value-datepicker-popup-0');
        var value_deadline = $input_deadline.val();
        var string_return = "";
        if (value_deadline === '') {
          string_return = Drupal.t('No deadline selected', {}, {'context' : 'gofast'});
        }
        else {
         var $input_deadline_hour = $('#edit-field-date-und-0-value-timeEntry-popup-1');
         var value_deadline_hour = $input_deadline_hour.val();         
         string_return = Drupal.checkPlain(value_deadline) + " " + Drupal.checkPlain(value_deadline_hour);
        }

        return string_return;
      });
    }
  }
};

Drupal.behaviors.formsLanguageFieldsetSummaries = {
  attach: function (context) {
    if ($('fieldset.group-language').length > 0) {
      $('fieldset.group-language:not(.group-language-processed)', context).addClass('group-language-processed').drupalSetSummary(function (context) {

        var $select_language = $('#edit-language');
        var val = $select_language.val();

        var string_return = Drupal.checkPlain($select_language.find(':selected').text());    
        return string_return;

      });
    }
  }
};

Drupal.behaviors.formsLinksFieldsetSummaries = {
  attach: function (context) {
    if ($('fieldset.group-links').length > 0) {
      $('fieldset.group-links:not(.group-links-processed)', context).addClass('group-links-processed').drupalSetSummary(function (context) {

        var $input_external_links = $('#edit-field-external-page-url-und-0-value');
        var value_external_links = $input_external_links.val();
        var $input_internal_links = $('#edit-field-target-link-und-0-target-id');
        var value_internal_links = $input_internal_links.val();

        var string_return = "";
        var string_return_external;
        var string_return_internal;
        if (value_external_links === '') {
          string_return_external = Drupal.t('No external links selected', {}, {'context' : 'gofast'});
        }
        else {
         string_return_external = Drupal.t("External links", {}, {'context' : 'gofast'}) + " : " + Drupal.checkPlain(value_external_links);
        }

        if (value_internal_links === '') {
          string_return_internal = Drupal.t('No internal links selected', {}, {'context' : 'gofast'});
        }
        else {
          string_return_internal = Drupal.t("Internal links", {}, {'context' : 'gofast'}) + " : " + Drupal.checkPlain(value_internal_links);
        }
        string_return = string_return_external + " " + string_return_internal;
        return string_return;
      });
    }
  }
};
})(jQuery, Drupal, Gofast);