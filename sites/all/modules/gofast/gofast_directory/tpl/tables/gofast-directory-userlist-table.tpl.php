<div class="card card-custom card-stretch mt-4" style="height: 97%;">
  <div class="card-body p-5 d-flex flex-column h-100">
    <div class="h-100 w-100">
      <div id="gofastDirectoryUserlistsTable" class="datatable datatable-bordered datatable-head-custom h-100" data-columns='<?php echo $columns ?>'></div>
    </div>
  </div>
</div>
<script defer>
  Drupal.behaviors.gofast_directories_userlist_breadcrumb = {
    attach: function(context) {
      if (jQuery("[id^='contextual-actions-loading-'].not-processed").length) {
        jQuery("[id^='contextual-actions-loading-']").each(function() {
          $(this).removeClass('not-processed');
          const nid = $(this).attr("id").replace("contextual-actions-loading-", "");
          jQuery.get(location.origin + "/gofast/node-actions/" + nid, function(data) {
            jQuery("#contextual-actions-loading-" + nid).remove();
            jQuery('#userlist-node-actions-' + nid).replaceWith(data);
            Drupal.attachBehaviors();
          });
        });
      }
    }
  }
</script>