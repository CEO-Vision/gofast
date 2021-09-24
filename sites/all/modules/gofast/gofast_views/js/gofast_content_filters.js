(function ($, Gofast, Drupal) {
  
  Drupal.behaviors.gofast_content_filters = {
    attach: function (context, settings) {
      var isSelected = false;
      var in_filter = false;
      $('.og_contents_filter:not(.filter-processed)').each(function() {
        in_filter = true;
        if ($(this).parent().parent().attr('id') != undefined){
            var inZtree = $(this).parent().parent().attr('id');
        }else{
            var inZtree = '';
        }
        if ($(this).attr('id') == undefined){
            var $cookie = $.cookie('ids_' + $(this).attr('ids'));
            if ($cookie !== null){
                $(this).parent().parent().collapse('show');
                $(this).parent().parent().parent().find('i').removeClass('fa-chevron-right');
                $(this).parent().parent().parent().find('i').addClass('fa-chevron-down');
                isSelected = true;
                $(this).addClass('selected');
                $('.no_filter').removeClass('selected');
                if (inZtree.indexOf('collapse') != '-1'){
                    var header = $(this).parent().parent().parent().find('.panel-heading').text();
                    var filters = '<li id="' + $(this).attr('id') +  '_filter">' + header + ' >> ' + $(this).html() + '</li>';
                    $("div#activity_filters",context).prepend(filters);           
                }else{
                    var filters = '<li id="' + $(this).attr('id') +  '_filter">' + ' >> ' + $(this).html() + '</li>';
                    $("div#activity_filters",context).prepend(filters);  
                }
                }
        }else{
            var $cookie = $.cookie('id_' + $(this).attr('id'));
            if ($cookie !== null){
                $(this).parent().parent().collapse('show');
                $(this).parent().parent().parent().find('i').removeClass('fa-chevron-right');
                $(this).parent().parent().parent().find('i').addClass('fa-chevron-down');
                isSelected = true;
                $(this).addClass('selected');
                $('.no_filter').removeClass('selected');
                if (inZtree.indexOf('collapse') != '-1'){
                    var header = $(this).parent().parent().parent().find('.panel-heading').text();
                    var filters = '<li id="' + $(this).attr('id') +  '_filter">' + header + ' >> ' + $(this).html() + '</li>';
                    $("div#activity_filters",context).prepend(filters);           
                }else{
                    var filters = '<li id="' + $(this).attr('id') +  '_filter">' + ' >> ' + $(this).html() + '</li>';
                    $("div#activity_filters",context).prepend(filters);  
                }
                }
        }
        $(this).addClass('filter-processed');
        $(this).click(function(e) {
          if ($(this).hasClass('selected')) {
            if ($(this).attr('id') == undefined){
                $.cookie('ids_' + $(this).attr('ids'),null);
            }else{
                $.cookie('id_' + $(this).attr('id'),null);
            }
            $(this).removeClass('selected');
            
            if ($(this).hasClass('no_filter')) {
              $('.og_contents_filter').removeClass('selected');
              $(this).addClass('selected');
              $('#edit-gofast-filter-group-title').children().removeAttr('selected');
              $('#edit-field-state-tid').children().removeAttr('selected');
            }
            else if ($(this).hasClass('state_contents_filter')){
              var id = $(this).attr('ids');
              $('#edit-field-state-tid > option[value="' + id + '"]').removeAttr('selected');  
              var remove_filter = "#" + $(this).attr('ids')+"_filter";
              $(remove_filter).remove();           }
            else {
              var id = $(this).attr('id');
              $('#edit-gofast-filter-group-title > option[value="' + id + '"]').removeAttr('selected');              
              var remove_filter = "#" + $(this).attr('id')+"_filter";
              $(remove_filter).remove();            }
          }
          else {
            $(this).addClass('selected');
            if ($(this).attr('id') == undefined){
                $.cookie('ids_' + $(this).attr('ids'),'selected');
            }else{
                $.cookie('id_' + $(this).attr('id'),'selected');
            }
            if ($(this).hasClass('no_filter')) {
                $('.og_contents_filter').each(function() {
                if ($(this).attr('id') == undefined){
                    $.cookie('ids_' + $(this).attr('ids'),null);
                }else{
                    $.cookie('id_' + $(this).attr('id'),null);
                }
                $('#activity_filters li').each(function(){
                	$(this).remove();
                });
                $('#block-gofast-views-activity-stream-filters .panel-collapse').each(function(){
                        if ($(this).attr('aria-expanded') == "true"){
                            $(this).collapse('hide');
                            $(this).parent().find('i').removeClass('fa-chevron-down');
                            $(this).parent().find('i').addClass('fa-chevron-right');
                        }
                });
              }); 
              $('.og_contents_filter').removeClass('selected');
              $(this).addClass('selected');
              $('#edit-gofast-filter-group-title').children().removeAttr('selected');
              $('#edit-field-state-tid').children().removeAttr('selected');
              $('#edit-gofast-filter-group-title-op > option[value="empty"]').removeAttr('selected');
            }
            else if ($(this).hasClass('state_contents_filter')){
              $('.no_filter').removeClass('selected');
              var id = $(this).attr('ids');
              $('#edit-field-state-tid > option[value="' + id + '"]').attr("selected","selected");
              var filters = '<li id="' + $(this).attr('ids') +  '_filter">' + jQuery(this).html() + '</li>';
              if (inZtree.indexOf('collapse') != '-1'){
                var header = $(this).parent().parent().parent().find('.panel-heading').text();
                var filters = '<li id="' + $(this).attr('ids') +  '_filter">' + header + ' >> ' + $(this).html() + '</li>';
                $("div#activity_filters",context).prepend(filters);           
              }else{
                    var filters = '<li id="' + $(this).attr('ids') +  '_filter">' + ' >> ' + $(this).html() + '</li>';
                    $("div#activity_filters",context).prepend(filters);  
              }        
            }
            else {
              $('.no_filter').removeClass('selected');
              var id = $(this).attr('id');
              $('#edit-gofast-filter-group-title-op').children().removeAttr('selected');
              $('#edit-gofast-filter-group-title-op > option[value="or"]').attr("selected","selected");
              $('#edit-gofast-filter-group-title > option[value="' + id + '"]').attr("selected","selected");
              var filters = '<li id="' + $(this).attr('id') +  '_filter">' + jQuery(this).html() + '</li>';
                if (inZtree.indexOf('collapse') != '-1'){
                    var header = $(this).parent().parent().parent().find('.panel-heading').text();
                    var filters = '<li id="' + $(this).attr('id') +  '_filter">' + header + ' >> ' + $(this).html() + '</li>';
                    $("div#activity_filters",context).prepend(filters);           
                }else{
                    var filters = '<li id="' + $(this).attr('id') +  '_filter">' + ' >> ' + $(this).html() + '</li>';
                    $("div#activity_filters",context).prepend(filters);  
                }
            }
          }
          if (!$('.og_contents_filter').hasClass('selected')) $('.no_filter').addClass('selected');   
          $('#block-gofast-views-activity-stream-filters').trigger("filters_updated");
        });
      });
      if (in_filter == true ){
          if (isSelected == true){
              if($.cookie('display_blog') == 1){
                $(".check-display-blog").not("processed").addClass('selected');
              }else{
                $(".check-display-blog").not("processed").removeClass('selected');
              }
              $(".no_filter").removeClass("selected");
          }else{
              $(".no_filter").addClass("selected");
          }
      $('#block-gofast-views-activity-stream-filters').trigger("filters_updated");
      }
    }
  };
})(jQuery, Gofast, Drupal);