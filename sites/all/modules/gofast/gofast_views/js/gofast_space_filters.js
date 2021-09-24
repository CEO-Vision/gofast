(function ($, Gofast, Drupal) {

  Drupal.behaviors.gofast_space_filters = {
    attach: function (context, settings) {
      context = $(context);
//      var form = $('#views-exposed-form-gofast-og-list-page-1:not(.filter-processed)').addClass('filter-processed');
//      $('#edit-submit-gofast-og-list:not(.filter-processed)').addClass('filter-processed').click(function(e) {
//        // Serializing form & put the form state in a cookie
//        var formState = form.serialize(),
//         id = Drupal.settings.drupalchat.uid || '',
//         cookieName = 'space_filters' + id;
//        Gofast.setCookie(cookieName, formState);
//      });

      $('.gofast_space_filters:not(.filter-processed)', context).addClass('filter-processed').each(function () {

        $("#gofast_search_input").on("keyup", function () {
          $(".gofast_search_submit").attr("value", $(this).val());
        });
        $(this).click(function (e) {
          if ($(this).hasClass('selected')) {
            $(this).removeClass('selected');
            $('.form-select > option[value="All"]').attr("selected", "selected");
          }
          else {
            $(this).addClass('selected');
            if ($(this).hasClass('gofast_all_filter')) {
              $('.gofast_space_filters').removeClass('selected');
              $(this).addClass('selected');
              $('.form-select > option[value="All"]').attr("selected", "selected");
            }
            else if ($(this).hasClass('gofast_orga_filter')) {
              $('.gofast_space_filters').removeClass('selected');
              $(this).addClass('selected');
              $('.form-select > option[value="organisation"]').attr("selected", "selected");
            }
            else if ($(this).hasClass('gofast_group_filter')) {
              $('.gofast_space_filters').removeClass('selected');
              $(this).addClass('selected');
              $('.form-select > option[value="group"]').attr("selected", "selected");
            }
            else if ($(this).hasClass('gofast_public_filter')) {
              $('.gofast_space_filters').removeClass('selected');
              $(this).addClass('selected');
              $('.form-select > option[value="public"]').attr("selected", "selected");
            }
            else if ($(this).hasClass('gofast_extranet_filter')) {
              $('.gofast_space_filters').removeClass('selected');
              $(this).addClass('selected');
              $('.form-select > option[value="extranet"]').attr("selected", "selected");
            }
//            else {
//              $('.gofast_all_filter').removeClass('selected');
//              $('.public_contents_filter').removeClass('selected');
//              var id = $(this).attr('id');
//              $('#edit-gofast-filter-group-title-op').children().removeAttr('selected');
//              $('#edit-gofast-filter-group-title-op > option[value="or"]').attr("selected","selected");
//              $('#edit-gofast-filter-group-title > option[value="' + id + '"]').attr("selected","selected");
//            }

          }
          if (!$('.gofast_space_filters').hasClass('selected')) {
            $('.gofast_all_filter').addClass('selected');
          }
          if ($(this).hasClass('gofast_search_submit')) {
            $('#edit-title').val($('#gofast_search_input').val());
            $('.gofast-og-list .views-exposed-form .form-submit').click();
          }
        });
      });

      // no filter click : $('#edit-gofast-filter-group-title').children().removeAttr('selected');
    }
  }
})(jQuery, Gofast, Drupal);