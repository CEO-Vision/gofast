jQuery(document).ready(function () {
  jQuery(".view-gofast-userlist-members tbody .row-first").remove();
  jQuery(".view-gofast-userlist-members > div").append(
    "<nav class='text-center'>"
  );
  jQuery(".view-gofast-userlist-members > div nav").append(
    "<ul class='pagination pagination-sm' style='margin-top:20px;margin-bottom:5px;' id='userlist_members'></ul>"
  );
  jQuery(".view-gofast-userlist-members tbody").pager({
    pagerSelector: "#userlist_members",
    perPage: 2,
    numPageToDisplay: 5,
  });
  jQuery(".view-gofast-userlist-members .col-first").remove();

  jQuery(".user_member_picture")
    .parent()
    .parent()
    .parent()
    .parent()
    .css("width", "100%");
});
