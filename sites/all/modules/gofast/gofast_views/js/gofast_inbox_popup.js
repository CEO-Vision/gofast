// jQuery for Drupal 7 [BEGIN]
(function ($, Gofast, Drupal) {
  $(window).bind("load", function() {
    if($('#gofast_inbox_popup').length != 0) $('#gofast_inbox_popup').css({'marginLeft' : $('#gofast_view-privatemsg-privatemsg_bloc').offset().left - $(".container").offset().left - parseInt($(".container").css("padding-left"))});
    
  });
  
  
  function getConfirmationDialog(msg, elClass, border){
      msg = msg == null || msg == 'undefined' || msg == '' ? Drupal.t('Delete', {}, {'context' : 'gofast'})+' ?' : msg;
      border = border || border == 'undefined' ? '<div class="confirm-border"></div>' : '' ;
      var dialog = $('\
<div id="confirm" class="'+elClass+'" style="display:none;">'+border+'\
    <span>'+msg+'</span>\
    <a id="_no_" class="btn btn-xs btn-danger">\
        <span class="glyphicon glyphicon-remove"></span> '+Drupal.t('No', {}, {'context' : 'gofast'})+'\
    </a>\
    <a class="btn btn-xs btn-success" id="_yes_">\
        <span class="glyphicon glyphicon-ok"></span> '+Drupal.t('Yes', {}, {'context' : 'gofast'})+'\
    </a>\
</div>');
      return dialog;
  }
  
  Drupal.behaviors.gofast_inbox_popup = {
    attach: function (context, settings) {
      context = $(context);
      
      var participants_menu = $("#gofast_view-privatemsg-privatemsg_bloc");
      var participants = $("#gofast_inbox_popup");
      var el = participants_menu.add(participants);
      el.hover(
        function(){
          participants.css({
            'display' : 'block',
          });
        },
        
        function(){
          participants.css('display', 'none');
        }
      ); 
      
      
      $('#gofast_inbox_popup:not(.ajax-processed)', context).addClass('ajax-processed').each(function() {
        if (Drupal.settings.gofast_pm_tree) {
          var data_tree = Drupal.settings.gofast_pm_tree.data_tree;
          $('#gofast_inbox_popup').html(data_tree);
        }
      });
      
      $('.delete_message_ajax:not(.ajax-processed)', context).addClass('ajax-processed').each(function() {
        $(this).click(function(e) {
          e.preventDefault();
          var trashIcon = $(this);
          // Drupal.t("Are you sure you want to delete this message?"),
          var confirmDialog = getConfirmationDialog(null, 'delete-msg-confirm', false);
          var thread_id = trashIcon.attr('id');
          // Other confirmation dialog could have been loaded without neither validation
          // nor cancellation so it has to be removed before showing a new one.
          //$('#confirm').remove();
          $('.delete_message_ajax').show();
          trashIcon.after(confirmDialog);
          $('#'+thread_id).hide();
          //$('#confirm').slideToggle(400, function(){$(this).remove();});
          //confirm.insertAfter($(this)).slideToggle(400);
          $('#confirm').show();
          //$('#'+mid).slideToggle(400, function(){$(this).hide();});
          confirmDialog.find('#_no_').click(function(){
              $('#'+thread_id).show();
              confirmDialog.remove();
            //$('#'+mid).slideToggle(400, function(){ $(this).show() });
            //confirm.slideToggle(400, function(){$(this).remove();});
          });

          confirmDialog.find('#_yes_').click(function(){
            $.ajax({
              type: 'POST',
              url: '/del_privatemsg',
              dataType: 'json',
              data: {
                'thread_id': thread_id
              },
              beforeSend: function(xhr) {
                $('#confirm').append('<div class="fa fa-spinner fa-spin"></div>');
                $('#confirm').find('#_yes_').attr('disabled', 'disabled');
                $('#confirm').find('#_no_').attr('disabled', 'disabled');
                Gofast.xhrPool = Gofast.xhrPool || {};
                Gofast.xhrPool.xhrDeletePrivateMsg = xhr;
              },
              complete: function() {
                delete Gofast.xhrPool.xhrDeletePrivateMsg;
              }
            }).done(function(result) {
              if (result.success === 1) {
                $('#'+thread_id).show();
                $('#unread_pm_count div').text(result.unread_count);
                confirmDialog.remove();
                trashIcon.parent().parent().remove();
                Gofast.toast(result.message, 'success');
              }
              else confirmDialog.remove();
            }).error(function(error) {
              
            });
            
          });
        });
      });
      
      $('.gofast-pm-participants:not(.extend-processed)', context).children().addClass('extend-processed').each(function() {
        if ($(this).children().hasClass('gofast-participants')) {
          $(this).children('.gofast-participants').hide();
          $(this).hover(
            function(){
              $(this).children('.participant-count').hide();
              $(this).children('.gofast-participants').show();
            },
            function(){
              $(this).children('.participant-count').show();
              $(this).children('.gofast-participants').hide();
            }
          ); 
        }
      });
      
      $('#gofast_inbox_popup:not(.btn-inbox-processed)').find(':button').addClass('btn-inbox-processed').each(function() {
        $(this).click(function(e) {
          $('#gofast_inbox_popup .view-filters, #gofast_inbox_popup .gofast_toggle_filters').appendTo("#gofast_inbox_popup .view-content");
        });
      });
      
    }
  }
 
 
}(jQuery, Gofast, Drupal));