(function ($, Gofast, Drupal) {
    $(document).ready(function() {
        
        $("html").on('click', '.forum-explorer-element-open', function() {
            let _this = $(this).parent().parent();
            let id = $(_this).attr('id');
            let childs_parents_doms = $(_this).siblings().find(".forum-explorer-element-parent");
            let parents = $(_this).siblings();
            $.each(childs_parents_doms, function(k, elem) {
                if($(elem).text().trim() === id) {
                    if($(elem).parent().attr('class').includes("forum-explorer-element-visible")) {
                        $(elem).parent().find(".forum-explorer-element-open").addClass("ki-bold-arrow-next").removeClass("ki-bold-arrow-down");
                    }
                    $(elem).parent().toggleClass("forum-explorer-element-visible").toggleClass("forum-explorer-element-collapsed");
                }
            });

            if($(this).attr('class').includes('ki-bold-arrow-next')) {
                $(this).removeClass("ki-bold-arrow-next").addClass("ki-bold-arrow-down");
            }else $(this).addClass("ki-bold-arrow-next").removeClass("ki-bold-arrow-down");

            //When a dom is collapsed, collapse all its childs, grandchilds etc..
            $.each(childs_parents_doms, function(k, elem) {
                let act_id = $(elem).text().trim();
                let par = $(parents).filter("[id='" + act_id + "']");
                if($(par).filter("[class*=\"forum-explorer-element-collapsed\"]").length) {
                    $(elem).parent().removeClass("forum-explorer-element-visible").addClass("forum-explorer-element-collapsed");
                    $(elem).parent().find(".forum-explorer-element-open").addClass("ki-bold-double-arrow-down").removeClass("ki-bold-double-arrow-up");
                }
            });
        });
    });
    
    Gofast.reloadForums = function($forumTreeParentElement = null){
        if (!$forumTreeParentElement) {
            $forumTreeParentElement = $("#expl-forum");
        }
        if ($forumTreeParentElement.length) {
            const urlParam = window.location.pathname.split('/')[2] || "-1";
            var spinner = ' <div class="spinner spinner-track spinner-primary d-inline-flex gofast-spinner-xxl position-absolute" style="top: calc(50% - 6em); left: calc(50% - 4em);"></div>';
            $forumTreeParentElement.html(spinner);
            $.get(window.origin + "/gofast/forum/explorer/" + urlParam).done((data) => $forumTreeParentElement.html(data)); 
        }
    }

    Gofast.selectCurrentForum = function(nid = null){
        var urlParam = window.location.pathname.split('/')[2] || "-1";
        if(nid != null){
            urlParam = nid
        }
        const waitForForumElementInterval = setInterval(() => {
            const $forumElement = $(".forum-explorer-wrapper [id='-1'][data-nid='" + urlParam + "']");
            if (!$forumElement.length) {
                return;
            }
            clearInterval(waitForForumElementInterval);
            $forumElement.addClass("gofastHighlightedForum bg-primary text-white rounded");
            if (window.location.hash == "#comment-init" || !window.location.hash.startsWith("#comment-")) {
                $forumElement[0].scrollIntoView({behavior: "smooth", block: "center"});
            }
        }, 100);
    }

})(jQuery, Gofast, Drupal);
