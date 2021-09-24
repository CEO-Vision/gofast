// jQuery for Drupal 7 [BEGIN]
(function ($, Gofast, Drupal) {
  Drupal.behaviors.gofast_users_filters = {
    attach: function (context, settings) {
      context = $(context);
      /*
      var form = $('#views-exposed-form-gofast-user-directory-page:not(.filter-processed)').addClass('filter-processed');
      $('#edit-submit-gofast-user-directory:not(.filter-processed)').addClass('filter-processed').click(function(e) {
        // Serializing form & put the form state in a cookie
        var formState = form.serialize(),
        id = Gofast.get('user').uid || '',
        cookieName = 'users_filters' + id;
        Gofast.setCookie(cookieName, formState);
      });
      */

      $('.gofast_user_filters:not(.filter-processed)[data-parent!="#accordion"]', context).addClass('filter-processed').each(function() {

        $(this).click(function(e) {

          if ($(this).hasClass('selected')) {
            $(this).removeClass('selected');

            if ($(this).hasClass('gofast_all_filter')) {
              $(this).addClass('selected');
            }
            else if ($(this).hasClass('gofast_my_relation')){
//              $('.gofast_all_filter').addClass('selected');
              $('.form-item-gofast-user-relationships > select > option[value="0"]').attr("selected","selected");
            }
            else if ($(this).hasClass('gofast_names_filter')){
              $(this).removeClass('selected');
              $('.form-item-ldap-user-sn-value-1 > input').first().val('');
              $('.form-item-ldap-user-sn-value > input').first().val('');
            }
            else if ($(this).hasClass('gofast_skills_filter')){
              var id = $(this).attr('ids');
              $('.form-item-field-skills-tid > select > option[value="' + id + '"]').removeAttr('selected');
            }
            else {
              var id = $(this).attr('id');
              $('.form-item-gofast-filter-group-title > select > option[value="' + id + '"]').removeAttr('selected');
            }

          }
          else {
            $(this).addClass('selected');
            if ($(this).hasClass('gofast_all_filter')) {
              $('.gofast_user_filters').removeClass('selected');
              $('.form-item-gofast-user-relationships > select > option[value="0"]').attr("selected","selected");
              $('.form-item-ldap-user-sn-value > input').first().val("");
              $('.form-item-ldap-user-sn-value-1 > input').first().val("");
              $('.form-item-field-skills-tid > select').children().removeAttr('selected');
              $('.form-item-gofast-filter-group-title > select').children().removeAttr('selected');
            }
            else if ($(this).hasClass('gofast_my_relation')){
              $('.gofast_all_filter').removeClass('selected');
              $('.form-item-gofast-user-relationships > select > option[value="1"]').attr("selected","selected");
            }
            else if ($(this).hasClass('gofast_names_filter')){
              $('.gofast_all_filter').removeClass('selected');
              $('.gofast_names_filter').removeClass('selected');
              $(this).addClass('selected');
              $('.form-item-ldap-user-sn-value > input').first().val($(this).attr("val1"));
              $('.form-item-ldap-user-sn-value-1 > input').first().val($(this).attr("val2"));
            }
            else if ($(this).hasClass('gofast_skills_filter')){
              $('.gofast_all_filter').removeClass('selected');
              var id = $(this).attr('ids');
              $('.form-item-field-skills-tid > select > option[value="' + id + '"]').attr("selected","selected");
            }
            else {
              $('.gofast_all_filter').removeClass('selected');
              var id = $(this).attr('id');
              $('#edit-gofast-filter-group-title > option[value="' + id + '"]').attr("selected","selected");
            }

          }

          if (!$('.gofast_user_filters').hasClass('selected')) $('.gofast_all_filter').addClass('selected');

            $('.form-submit[id^=edit-submit-gofast-user-directory]').click();

        });

      });

      $('#user-last-login-date-filter, #user-created-date-filter').each(function(){
        $(this).datepicker({
          format: 'yyyy-mm-dd',
          orientation: "bottom auto",
          autoclose: true,
          clearBtn: true,
        });

      })

      $('#edit-ldap-user-sn-value-sidebar, #edit-ldap-user-givenname-value-sidebar').each(function(){
        $(this).change(function(){

          switch ($(this).attr('id')) {
            case 'edit-ldap-user-sn-value-sidebar':
              var regex = new RegExp("[A-Za-z0-9_.]{2,20}");
              var input = $(this).val();

              if(regex.test(input) || input === "") {
                $('#edit-ldap-user-sn-value').val(input);
                $(this).css('border-color', '#cccccc');
              }else {
                $(this).css('border-color', 'red');
                $('#edit-ldap-user-sn-value').val("");
              }
              break;
              
            case 'edit-ldap-user-givenname-value-sidebar':
              var regex = new RegExp("[A-Za-z0-9_.]{2,20}");
              var input = $(this).val();

              if(regex.test(input) || input === "") {
                $('#edit-ldap-user-givenname-value').val(input);
                $(this).css('border-color', '#cccccc');
              }else {
                $(this).css('border-color', 'red');
                $('#edit-ldap-user-givenname-value').val('');
              }
              break;
            

            default:
              break;
          }
          
          
        })
      })

      $('#edit-submit-user-filters-sidebar').click(function(){

        
        // Get all value from filters
        Gofast.addLoading();

        var lastlogin_min = $('#edit-login-sidebar').val();
        var lastlogin_max = $('#edit-login-end-sidebar').val();
        var created_min = $('#edit-created-sidebar').val();
        var created_max = $('#edit-created-end-sidebar').val();
        var activeUser = $('#edit-status-sidebar').children("option:selected").val();

        
        
        $('#edit-login-min').val(lastlogin_min);
        $('#edit-login-max').val(lastlogin_max);
        $('#edit-created-min').val(created_min);
        $('#edit-created-max').val(created_max);
        $('#edit-status').val(activeUser);
        $('#gofast_mobile_arrow').remove();
        $('#gofast_mobile_panel').remove();
        $('#views-exposed-form-gofast-user-directory-user-directory #edit-submit-gofast-user-directory').click();
        Gofast.removeLoading();
      });
      $('#edit-reset-user-filters-sidebar').click(function(){
        $('#views-exposed-form-gofast-user-directory-user-directory #edit-reset').click();
      });
      $('#edit-submit-user-active-filters-sidebar').click(function(){
        // Get all value from filters
        Gofast.addLoading();
        var lastname = $('#edit-ldap-user-sn-value-sidebar').val();
        var firstname = $('#edit-ldap-user-givenname-value-sidebar').val();
        var lastlogin = $('#edit-login-sidebar').val();
        var created = $('#edit-created-sidebar').val();

        $('#edit-ldap-user-sn-value').val(lastname);
        $('#edit-ldap-user-givenname-value').val(firstname);
        $('#edit-login').val(lastlogin);
        $('#edit-created').val(created);

        $('#views-exposed-form-gofast-user-directory-page-2 #edit-submit-gofast-user-directory').click();
        Gofast.removeLoading();
      });
      $('#edit-reset-user-active-filters-sidebar').click(function () {
        $('#views-exposed-form-gofast-user-directory-page-2 #edit-reset').click();
      });
      $('#edit-submit-user-inactive-filters-sidebar').click(function(){
        // Get all value from filters
        Gofast.addLoading();
        var lastname = $('#edit-ldap-user-sn-value-sidebar').val();
        var firstname = $('#edit-ldap-user-givenname-value-sidebar').val();
        var lastlogin = $('#edit-login-sidebar').val();
        var created = $('#edit-created-sidebar').val();

     
        $('#edit-ldap-user-sn-value').val(lastname);
        $('#edit-ldap-user-givenname-value').val(firstname);
        $('#edit-login').val(lastlogin);
        $('#edit-created').val(created);

        $('#views-exposed-form-gofast-user-directory-page-1 #edit-submit-gofast-user-directory').click();
        Gofast.removeLoading();
      });
      $('#edit-reset-user-inactive-filters-sidebar').click(function () {
        $('#views-exposed-form-gofast-user-directory-page-1 #edit-reset').click();
      });
    }
  }
}(jQuery, Gofast, Drupal));
