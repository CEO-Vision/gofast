(function($) {
  $(document).ready(function() {
//    $("ul.book_block").sortable({
//      connectWith: "ul"
//      
//    });
//    $("ul.subcomments").sortable({
//      connectWith: "ul"
//    });
    if ($('.forum-post-content p').find('img').length > 0) {
      $('.forum-post-content p').css('overflow', 'auto');
    }
  });
})(jQuery)


