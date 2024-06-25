
(function ($, Drupal, Gofast) {
  'use trict';

  $(document).ready(function () {
    if ($("#dashboard-block-last-commented").length > 0) {
      $.post(
        location.origin + "/dashboard/ajax/last_commented",
        function (data) {
          $("#dashboard-block-last-commented").replaceWith(data);
        }
      );
    }

    if ($("#dashboard-block-mail").length > 0) {
      $.post(location.origin + "/dashboard/ajax/mail", function (data) {
        $("#dashboard-block-mail").replaceWith(data);
      });
    }
    $(window).on("unbookmark", (e, nodeCategory) => {
      $.get(`/gofast/dashboard/get_bookmark_block_content/${nodeCategory}`).done((content) => {
        $(`[id^=dashboard_block_favorites_${nodeCategory}]`).html(content)
      })
    })
  });
})(jQuery, Drupal, Gofast);


