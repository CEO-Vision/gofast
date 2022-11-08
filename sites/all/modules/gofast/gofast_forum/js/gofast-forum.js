(function ($, Gofast, Drupal) {
    Gofast.lastUrlForumTab = '';
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
    
    Gofast.reloadForums = function(){
        if ($("#expl-forum").length) {
            const urlParam = window.location.pathname.split('/')[2] || "-1";
            if($("#expl-forum").hasClass("active") && $("#explorer-toggle").hasClass("open")){
               var spinner = ' <div class="spinner spinner-track spinner-primary d-inline-flex gofast-spinner-xxl position-absolute" style="top: calc(50% - 6em); left: calc(50% - 4em);"></div>';
               $("#expl-forum").html(spinner);
               $.get(window.origin + "/gofast/forum/explorer/" + urlParam).done((data) => $("#expl-forum").html(data));
               Gofast.lastUrlForumTab = '';
            }else{              
                Gofast.lastUrlForumTab =  urlParam;
            }
        }
    }

})(jQuery, Gofast, Drupal);
