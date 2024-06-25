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
      if (jQuery("[id^='dropdown-placeholder-'].not-processed").length) {
        jQuery("[id^='dropdown-placeholder-'].not-processed").each(function() {
          $(this).removeClass('not-processed');
          $(this).addClass("dropdown-processed")
          const nid = $(this).attr("id").replace("dropdown-placeholder-", "");
          $(this).on("click", () => {
            // Make the request only the first time
            if(jQuery(`#dropdownactive-placeholder-${nid}`).length){
              jQuery.get(location.origin + "/gofast/node-actions/" + nid, function(data) {
                // Because core.datatable.js tweak dropdown, we need to update the new dropdown with the data
                const dropdownStyle = jQuery(`#dropdownactive-placeholder-${nid}`).attr("style")
                const newDropdownMenu = $(data).find(".dropdown-menu");
                jQuery(`#dropdownactive-placeholder-${nid}`).replaceWith(newDropdownMenu)
                newDropdownMenu.attr("style", dropdownStyle)
                jQuery('#dropdown-placeholder-' + nid).append($(data).find(".dropdown-menu"));
              });
            }
          })
        });
      }
    }
  }
  // Clean dropdown in the body to prevent duplicated dropdown
  jQuery("body").on("hidden.bs.dropdown", (e) => {
    jQuery("body").find(">.dropdown-menu").remove()
    $(e.target).find("[id^=dropdownactive-placeholder-]").remove()
  })
</script>