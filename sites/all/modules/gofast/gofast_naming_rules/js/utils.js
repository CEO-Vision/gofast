/**
 * @file
 *
 * Provides object with all callable utilities related to naming rules
 *
 */
(function ($, Gofast, Drupal) {
  Gofast = Gofast || {};

  Gofast.namingRules = {
    handlers: {
      /**
       * toggle the #gofast_naming_rules_warning element depending on whether the given tid matches a naming rule or not
       * @return true if a naming rule is found, otherwise  false
       */
      async toggleWarning(tid) {
        const data = await Gofast.namingRules.handlers.getNamingRule(tid);
        if (!data) {
          $("#gofast_naming_rules_warning").removeClass("d-block").addClass("d-none");
          return false;
        }
        $("#gofast_naming_rules_warning").find("rule").html(data);
        $("#gofast_naming_rules_warning").removeClass("d-none").addClass("d-block");
        return true;
      },
      /**
       * @param {*} tid
       * @returns the naming rule as a technical string, otherwise an empty string
       */
      async getNamingRule(tid) {
        let data = "";
        await $.get("/taxonomy/" + tid + "/naming_rules/get?readable=true&themed=true").done(
          (response) => (data = response)
        );
        return data;
      },
    },
    events: {
      toggleWarningOnSelect: (selector) => {
        $(selector).on("select2:select", function () {
          const value = parseInt($(this).val());
          if (value <= 0) {
            $("#gofast_naming_rules_warning").removeClass("d-block").addClass("d-none");
            return;
          }
          Gofast.namingRules.handlers.toggleWarning(value);
        });
      },
      toggleWarningOnInput: (selector) => {
        $(selector).on("change", function () {
          let tags = $(".modal input#edit-categories").val();
          if (!tags) {
            $("#gofast_naming_rules_warning").removeClass("d-block").addClass("d-none");
            return;
          }
          tags = JSON.parse(tags);
          for (const tag of tags) {
            const value = parseInt(tag.value);
            const hasNamingRule =
              Gofast.namingRules.handlers.toggleWarning(value);
            if (hasNamingRule) {
              break;
            }
          }
        });
      },
    },
    intervals: {
      waitForElement: null,
    }
  };
})(jQuery, Gofast, Drupal);
