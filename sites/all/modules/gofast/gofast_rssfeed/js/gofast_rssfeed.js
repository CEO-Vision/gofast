(function ($, Gofast, Drupal) {
  "use strict";
  jQuery(document).ready(function () {
    Gofast.addRssFeed = function () {
      var title = jQuery("#title_rssfeed").val();
      var link = jQuery("#url_rssfeed").val();

      Gofast.closeModal();
      Gofast.addLoading();

      jQuery.post(
        location.origin + "/rssfeed/add",
        { rssfeed_title: title, url: link },
        function (response) {
          Gofast.removeLoading();

          if (response === "true") {
            Gofast.toast(
              Drupal.t(
                "The rss feed has been added",
                {},
                { context: "gofast:gofast_rssfeed" }
              ),
              "success"
            );
            jQuery('a[href="#edit-rssfeeds"]').remove("processed");
            Gofast.loadSettingsTab("edit-rssfeed");
            jQuery('a[href="#edit-rssfeeds"]').addClass("processed");
          } else {
            Gofast.toast(
              Drupal.t(
                "The feed URL is invalid. Please enter a fully-qualified URL, such as<br /><br /><blockquote>http://fr.news.yahoo.com/?format=rss</blockquote>",
                {},
                { context: "gofast:gofast_rssfeed" }
              ),
              "warning"
            );
          }
        },
        "text"
      );
    };

    Gofast.editRssFeed = function (fid) {
      var title = jQuery("#title_rssfeed").val();
      var link = jQuery("#url_rssfeed").val();

      Gofast.closeModal();
      Gofast.addLoading();

      jQuery.post(
        location.origin + "/rssfeed/edit",
        { rssfeed_title: title, url: link, rssfeed_fid: fid },
        function (response) {
          Gofast.removeLoading();
          if (response === "true") {
            Gofast.toast(
              Drupal.t(
                "The rss feed has been edited",
                {},
                { context: "gofast:gofast_rssfeed" }
              ),
              "success"
            );
            jQuery('a[href="#edit-rssfeeds"]').remove("processed");
            Gofast.loadSettingsTab("edit-rssfeed");
            jQuery('a[href="#edit-rssfeeds"]').addClass("processed");
          } else {
            Gofast.toast(
              Drupal.t(
                "The feed URL is invalid. Please enter a fully-qualified URL, such as<br /><br /><blockquote>http://fr.news.yahoo.com/?format=rss</blockquote>",
                {},
                { context: "gofast:gofast_rssfeed" }
              ),
              "warning"
            );
          }
        },
        "text"
      );
    };

    Gofast.deleteRssFeed = function (fid) {
      Gofast.closeModal();
      Gofast.addLoading();

      jQuery.post(
        location.origin + "/rssfeed/delete",
        { rssfeed_fid: fid },
        function (response) {
          Gofast.removeLoading();
          if (response === "true") {
            Gofast.toast(
              Drupal.t(
                "The rss feed has been deleted",
                {},
                { context: "gofast:gofast_rssfeed" }
              ),
              "success"
            );
            jQuery('a[href="#edit-rssfeeds"]').remove("processed");
            Gofast.loadSettingsTab("edit-rssfeed");
            jQuery('a[href="#edit-rssfeeds"]').addClass("processed");
          } else {
            Gofast.toast(
              Drupal.t(
                "The rss feed has not been deleted",
                {},
                { context: "gofast:gofast_rssfeed" }
              ),
              "warning"
            );
          }
        },
        "text"
      );
    };

    jQuery("a.gf-add-rssfeed").bind("click", function () {
      displayModal("add");
    });

    jQuery(".fa-pencil").bind("click", function () {
      var title = jQuery(this)
        .parent()
        .parent()
        .find(".gf-title_rssfeed")
        .text();
      var url = jQuery(this).parent().parent().find(".gf-url_rssfeed").text();
      var fid = jQuery(this).parent().parent().find(".gf-fid_rssfeed").text();
      title = jQuery.trim(title);
      url = jQuery.trim(url);
      fid = jQuery.trim(fid);
      displayModal("edit", title, url, fid);
    });

    jQuery(".fa-times").bind("click", function () {
      var title = jQuery(this)
        .parent()
        .parent()
        .find(".gf-title_rssfeed")
        .text();
      var fid = jQuery(this).parent().parent().find(".gf-fid_rssfeed").text();
      title = jQuery.trim(title);
      fid = jQuery.trim(fid);
      displayModal("delete", title, null, fid);
    });
  });
})(jQuery, Gofast, Drupal);
