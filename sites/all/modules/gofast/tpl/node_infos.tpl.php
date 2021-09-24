<div id='node-info-content-unprocessed' class='not-processed'>
  <div class='loader-node-info'></div>
</div>
<script type='text/javascript'>
  jQuery(document).ready(function() {
    Drupal.behaviors.gofast_right_block_breadcrumb = {
      attach: function(context) {
        if (jQuery("#node-info-content-unprocessed").hasClass("not-processed")) {
          jQuery("#node-info-content-unprocessed").removeClass("not-processed");
          jQuery(".breadcrumb-gofast").append("<div class='loader-breadcrumb'></div>");

          //Check locations of the node
          jQuery.get(location.origin + "/gofast/check-locations/" + Gofast.get('node').id, function(data) {
            response = JSON.parse(data);
            if (typeof(response.message) != "undefined" && response.message.length > 0) {
              jQuery("#fullscreen-node").before('<div class="alert alert-block alert-dismissible alert-error messages error">' + response.message + '</div>');
            }
            //Locations are successfully checked, process the breadcrumb, the right block and the menu
            Gofast.gofast_refresh_fast_actions_node(Gofast.get('node').id);
            Gofast.processAjax(location.origin + "/gofast/node-info/" + Gofast.get('node').id, true);
            jQuery.get(location.origin + "/gofast/node-breadcrumb/" + Gofast.get('node').id, function(data) {
              jQuery(".loader-breadcrumb").remove();
              jQuery(".breadcrumb-gofast").replaceWith(data);
            });
          });
        }
      }
      };
    });
</script>