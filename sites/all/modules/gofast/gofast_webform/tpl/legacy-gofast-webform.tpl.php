<!-- we may have to implement this script from GOFAST-3 webform container, so we keep it here for reference -->
<?php if (FALSE) : ?>
  <script type='text/javascript'>
    //Add ajaxification to the submit button
    jQuery('.webform-submit, .webform-next').addClass('ctools-use-modal');
    jQuery(".node-webform > .content.well.well-sm").find(".field-name-body").html("<div class='panel panel-default'><div class='panel-heading'><?php echo t("Description") ?></div><div class='panel-body'>" + jQuery(".node-webform > .content.well.well-sm").find(".field-name-body").html() + '</div></div>');

    var form = jQuery(".node-webform > .content.well.well-sm").find("form");
    if (form.length === 0) {
      jQuery(".node-webform > .content.well.well-sm").append("<div class='panel panel-danger'><div class='panel-heading'><i class='fa fa-lock' aria-hidden='true'></i> <?php echo t("Locked Form") ?></div></div>");
    } else {
      form.html("<div class='panel panel-default'><div class='panel-heading'><?php echo t("Form") ?></div><div class='panel-body'>" + jQuery(".node-webform > .content.well.well-sm").find("form").html() + '</div></div>');
    }
  </script>
<?php endif; ?>