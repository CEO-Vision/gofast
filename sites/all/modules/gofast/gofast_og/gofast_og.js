(function ($, Gofast, Drupal) {
  'use strict';

  Drupal.gofast_og = Drupal.gofast_og || {};

  var fromTree = false;

  $(document).ready(function () {
    var $ = jQuery;
    //Switch tab when hash change in url at navigation (back/fwd button)
    $(window).bind('hashchange', function(e){
      if($(".gofast-og-page").length < 1){
          //Prevent doing these actions outside of a space page
          return;
      }
     // if(e.oldURL !== e.newURL){
        if(location.hash === ""){
          history.replaceState(null, "Gofast", location.href + "#oghome");
        }

        if(location.hash !== "#ogdocuments"){
            clearInterval(Gofast.ITHit.refreshBreadcrumbTimeout);
            //Get params
            var params = {};
            if (location.search) {
                var parts = location.search.substring(1).split('&');

                for (var i = 0; i < parts.length; i++) {
                    var nv = parts[i].split('=');
                    if (!nv[0]) continue;
                    params[nv[0]] = nv[1] || true;
                }
            }
            Gofast.ITHit.refreshBreadcrumb(params.path, true);
        }
        $('.gofast-og-page a[href="' + location.hash + '"]').tab('show');
        $(window).scrollTop(0);
        if($("#file_browser_full_tree_element").length > 0){
            $("#file_browser_full_tree_element").mCustomScrollbar('scrollTo', 'left');
            $('.mCSB_scrollTools_vertical').css('visibility', 'visible');
            $('.mCSB_scrollTools_horizontal').css('visibility', 'visible');
        }
    //  }
    });
    $('#tabs_og_group').tabs();
    $('#panel_ztree_og').css('max-height', $(window).height()*0.7);
    window.onresize = function(){
      $('#panel_ztree_og').css('max-height', $(window).height()*0.7);
    };
    $(document).scroll(function(){
      $('#panel_ztree_og').css('top', $(this).scrollTop()+97);
    });

    Drupal.deleteSpace = function(gid){
      var modal_form = $('#delete_space_modal_container');
      var modal_process = $('#delete_space_modal_process_container');

      modal_form.hide();
      modal_process.css('display', 'block');
      modalContentResize();

      //Step 1 : Delete the documents
      $("#delete_step_1").append("<div class='loader-deleting'></div>");

      //Step 1-1 : Remove multifiling
      $("#delete_step_1_1").append("<div class='loader-deleting'></div><span id='delete_remaining_items'></span>");
      Drupal.removeMultifiling(gid);

    };

    Drupal.removeMultifiling = function(gid){
      $.get(location.origin + "/gofast_og/delete_space/" + gid + "/unmultifile_documents").done(function(data){
        if(data === "OK"){
          $("#delete_step_1_1").find(".loader-deleting").remove();
          $("#delete_remaining_items").remove();
          $("#delete_step_1_1").append(' <i class="fa fa-check" style="color:green;"></i>');
          Drupal.deleteDocuments(gid);
        }else if(!isNaN(data)){
          $("#delete_remaining_items").html(" " + data + " " + Drupal.t("items remaining..."));
          Drupal.deleteDocuments(gid);
        }else{
          $("#delete_step_1_1").find(".loader-deleting").remove();
          $("#delete_step_1").find(".loader-deleting").remove();
          $("#delete_remaining_items").remove();
          $("#delete_step_1_1").append(' <i class="fa fa-times" style="color:red;"></i> <span>' + data + "</span>");
          $("#delete_step_1").append(' <i class="fa fa-times" style="color:red;"></i>');
        }
      });
    };

    Drupal.deleteDocuments = function(gid){
      //Step 1-2 : Delete all the documents
      $("#delete_step_1_2").append("<div class='loader-deleting'></div><span id='delete_remaining_items'></span>");
      Drupal.deleteDocumentsProcess(gid);
    };

    Drupal.deleteDocumentsProcess = function(gid){
      $.get(location.origin + "/gofast_og/delete_space/" + gid + "/delete_documents").done(function(data){
        if(data === "OK"){
          $("#delete_step_1_2").find(".loader-deleting").remove();
          $("#delete_step_1").find(".loader-deleting").remove();
          $("#delete_remaining_items").remove();
          $("#delete_step_1_2").append(' <i class="fa fa-check" style="color:green;"></i>');
          $("#delete_step_1").append(' <i class="fa fa-check" style="color:green;"></i>');
          Drupal.deleteSpaceFolder(gid);
        }else if(!isNaN(data)){
          $("#delete_remaining_items").html(" " + data + " " + Drupal.t("items remaining..."));
          Drupal.deleteDocumentsProcess(gid);
        }else{
          $("#delete_step_1_2").find(".loader-deleting").remove();
          $("#delete_step_1").find(".loader-deleting").remove();
          $("#delete_remaining_items").remove();
          $("#delete_step_1_2").append(' <i class="fa fa-times" style="color:red;"></i> <span>' + data + "</span>");
          $("#delete_step_1").append(' <i class="fa fa-times" style="color:red;"></i>');
        }
      });
    };

    Drupal.deleteSpaceFolder = function(gid){
      //Step 2 : Delete the folders
      $("#delete_step_2").append("<div class='loader-deleting'></div>");
      $.get(location.origin + "/gofast_og/delete_space/" + gid + "/delete_folder").done(function(data){
        if(data === "OK"){
          $("#delete_step_2").find(".loader-deleting").remove();
          $("#delete_step_2").append(' <i class="fa fa-check" style="color:green;"></i>');
          //[GOFAST-6199] get parent space path
          $.post("/gofast_og/" + gid + "/get_parent_space_path/").done(function(parent_path){
              Drupal.deleteSpaceDrupal(gid, parent_path);
          },"text");
        }else{
          $("#delete_step_2").find(".loader-deleting").remove();
          $("#delete_step_2").append(' <i class="fa fa-times" style="color:red;"></i> <span>' + data + "</span>");
        }
      });
    };

    Drupal.deleteSpaceDrupal = function(gid, parent_path){
      //Step 2 : Delete the drupal space
      $("#delete_step_3").append("<div class='loader-deleting'></div>");
      $.get(location.origin + "/gofast_og/delete_space/" + gid + "/delete_drupal").done(function(data){
        setTimeout(Drupal.deleteSpaceDrupalProgress, 5000, gid, parent_path);
      });
    };

    Drupal.deleteSpaceDrupalProgress = function(gid, parent_path){
      $.get(location.origin + "/gofast_og/delete_space/" + gid + "/delete_drupal_progression").done(function(data){
        if(data === "OK"){
          $("#delete_step_3").find(".loader-deleting").remove();
          $("#delete_step_3").append(' <i class="fa fa-check" style="color:green;"></i>');
        }else{
          setTimeout(Drupal.deleteSpaceDrupalProgress, 5000, gid);
        }
      });

      //[GOFAST-6199]
      var str = parent_path.split("*");
      var url = str[0];
      url += "?&path=/Sites" + str[1] + "#ogdocuments";
      Gofast.processAjax(url);
      Gofast.toast(Drupal.t("Your space has been deleted", {}, {context : 'gofast:og'}));
      Drupal.CTools.Modal.dismiss();
    };
  });

  Drupal.gofast_og.transform_tabs = function (tab_id) {
    $(document).ready(function ($) {
      //on remplit automatiquement le champs titre avec le nom du fichier choisit
      $('#fragment-' + tab_id).tabs();
    });
  };

  /**
   * OG/User membership edition forms. Process states for roles checkboxes so
   * that only 1 non-technical role can be assigned to a user (radios would not
   * do the job for technical roles values).
   */
  Drupal.behaviors.gofastOGAdminRolesStates = {
    attach: function (context, settings) {
      var $roles = $('.og-roles-force-single input[type=checkbox]', context);
      $roles.once('single-role', function () {
        $(this).on('change', function () {
          if (this.checked) {
            $roles.not(this).not(':disabled').prop('checked', false);
          }
        });
      });
    }
  };

  Drupal.behaviors.gofastOGMembersFilters = {
    attach: function (context, settings) {
      $('[id^=gofast-og-member-filter-form]:not(.gofast-og-member-filter-form_processed)').addClass('gofast-og-member-filter-form_processed').each(function () {
        $('[id^=gofast-og-member-filter-form]').submit(function (e) {
          e.preventDefault();
        });

        $('[id^=gofast-og-member-filter-form] [id^=edit-reset-filters]').on('click', function () {
          $('[id^=edit-member-search]').val('');
          $('[id^=gofast-og-member-filter-form] [id^=edit-apply-filters]').click();
        });

        $('[id^=gofast-og-member-filter-form] [id^=edit-apply-filters]').on('click', function () {
          var text_value = $('[id^=edit-member-search]').val();
          $('[id^=edit-administrators-filter-input]').val(text_value);
          $('[id^=edit-contributors-filter-input]').val(text_value);
          $('[id^=edit-members-filter-input]').val(text_value);
          $('[id^=edit-requesters-filter-input]').val(text_value);
          $('[id^=edit-administrators-filter-input-]').siblings('div .views-submit-button').children('button').click();
          $('[id^=edit-contributors-filter-input-]').siblings('div .views-submit-button').children('button').click();
          $('[id^=edit-members-filter-input-]').siblings('div .views-submit-button').children('button').click();
          $('[id^=edit-requesters-filter-input-]').siblings('div .views-submit-button').children('button').click();
        });
      });
    }
  };

  Drupal.behaviors.og_grid = {
     attach: function() {
       if(($('.joinbtn')[0]) || ($('.cancelbtn')[0])){
            $('#contextual-actions-loading').hide();
       }else{
            $('#contextual-actions-loading').show();
       }
       $(document).trigger("scroll");
       $('#panel_ztree_og').css('max-height', $(window).height()*0.7);
       //In case of non-membership
       $('.joinbtn').not(".processed").on('click', function(caller){ //Click on join button
         if($(caller.target).hasClass("clicked")){ // Check if the button was already clicked
           return;
         }
         var caller_id = caller.currentTarget.id;
         var gid = caller_id.replace("join_", ""); //Get back the id of the caller div
         $(caller.target).addClass("clicked"); //Prevent from multiclicking

         $('#iconjoin_'+gid).removeClass("glyphicon-ok").addClass("glyphicon glyphicon-time"); //Change icon on the button
         $('#textjoin_'+gid).html(Drupal.t("Joining", {}, {'context' : 'gofast:og'})); //Change text on the button
         $('#textmembership_'+gid).html("");//Unset "you are not member" text

         $.ajax({ //Call to join the group
                url : Drupal.settings.gofast.baseUrl+'/og/list_grid/ajax/'+gid+'/join',
                type : 'GET',
                dataType: 'html',
                success : function(content, status){ //We edit the display (button + membership sentence)
                  $('#join_'+gid).replaceWith("<button type='button' class='btn btn-default cancelbtn' id='cancel_"+gid+"'><span id='iconcancel_"+gid+"' class='glyphicon glyphicon-remove' style='margin-right:7px;'></span><span id='textcancel_"+gid+"'>"+Drupal.t('Cancel', {}, {'context' : 'gofast:og'})+"</span></button>");
                  $('#textmembership_'+gid).html(Drupal.t('You are a pending requester of this space.', {}, {'context' : 'gofast:og'})).css("color", "blue");
                  Drupal.attachBehaviors('#cancel_'+gid);
                }
            });

       }).addClass("processed"); //Prevent multi attach to this listner on the same div

       //In case of pending membership
       $('.cancelbtn').not(".processed").on('click', function(caller){ //Click on the cancel button
         if($(caller.target).hasClass("clicked")){// Check if the button was already clicked
           return;
         }
         var caller_id = caller.currentTarget.id;
         var gid = caller_id.replace("cancel_", "");//Get back the id of the caller div
         $(caller.target).addClass("clicked"); //Prevent from multiclicking

         $('#iconcancel_'+gid).removeClass("glyphicon-ok").addClass("glyphicon glyphicon-time"); //Change icon on the button
         $('#textcancel_'+gid).html(Drupal.t("Canceling", {}, {'context' : 'gofast:og'})); //Change text on the button
         $('#textmembership_'+gid).html("");

         $.ajax({ //Call to cancel the membership request
                url : Drupal.settings.gofast.baseUrl+'/og/list_grid/ajax/'+gid+'/cancel',
                type : 'GET',
                dataType: 'html',
                success : function(content, status){ //We edit the display (button + membership sentence)
                  $('#cancel_'+gid).replaceWith("<button type='button' class='btn btn-default joinbtn' id='join_"+gid+"'><span id='iconjoin_"+gid+"' class='glyphicon glyphicon-ok' style='margin-right:7px;'></span><span id='textjoin_"+gid+"'>"+Drupal.t('Join', {}, {'context' : 'gofast:og'})+"</span></button>");
                  $('#textmembership_'+gid).html(Drupal.t('You are not member of this space.', {}, {'context' : 'gofast:og'})).css("color", "red");
                  Drupal.attachBehaviors('#join_'+gid);
                }
            });

       }).addClass("processed"); //Prevent multi attach to this listner on the same div


       $('.caller_fill').not(".processed").on('click', function(caller){
          var caller_id = caller.currentTarget.id;
          var gid = caller_id.replace("caller_", "");
          var placeholder_id = caller_id.replace("caller_", "#placeholder_");
          if($(placeholder_id).css('display') === 'none'){
            $(".arrow_"+gid).removeClass("glyphicon-arrow-down").addClass("glyphicon-arrow-up");
            $(placeholder_id).css('display', 'block').css('height', '100%');
            var height_ph = $(placeholder_id).height();

            //Expend ztree object
            var treeId = "ztree_og_grid";
            var zTreeObj = $.fn.zTree.getZTreeObj(treeId);
            var node = zTreeObj.getNodeByParam('nId', gid);
            if(!fromTree){
              zTreeObj.expandNode(node, true, false, false, false);
            }

            $(placeholder_id).css('height', '0px').css('display', 'block').css('opacity', '0').animate({
              height: height_ph,
              opacity: "1"
            }, 500, "swing", function(){
              $(placeholder_id).css('height', '100%');
            });
          }
          else if($(placeholder_id).html() !== ""){
            $(".arrow_"+gid).removeClass("glyphicon-arrow-up").addClass("glyphicon-arrow-down");

            //Collpse ztree object
            var treeId = "ztree_og_grid";
            var zTreeObj = $.fn.zTree.getZTreeObj(treeId);
            var node = zTreeObj.getNodeByParam('nId', gid);
            if(!fromTree){
              zTreeObj.expandNode(node, false, false, false, false);
            }

            $(placeholder_id).animate({
              height: "0px",
              opacity: "0"
            }, 500, "swing", function(){
              $(placeholder_id).css('display', 'none');
            });
          }
          else{
            $(".arrow_"+gid).removeClass("glyphicon-arrow-down").addClass("glyphicon-arrow-up");
            $(placeholder_id).css("display", "block").css("opacity", "0").animate({
              height: '100px'
              },200);
            $.ajax({
                url : Drupal.settings.gofast.baseUrl+'/og/list_grid/ajax/'+gid,
                type : 'GET',
                dataType: 'html',
                success : function(content, status){
                  //Expend ztree object
                  var treeId = "ztree_og_grid";
                  var zTreeObj = $.fn.zTree.getZTreeObj(treeId);
                  var node = zTreeObj.getNodeByParam('nId', gid);
                  if(!fromTree){
                    zTreeObj.expandNode(node, true, false, false, false);
                  }

                  $(placeholder_id).html(content);
                  $(placeholder_id).children(".og_grid_level").children("#og_level_container").css("width", '100%');
                  Drupal.attachBehaviors(placeholder_id);
                  $(placeholder_id).css('display', 'block').css('height', '100%');
                  var height_ph = $(placeholder_id).height();
                  $(placeholder_id).css('height', '100px').css('display', 'block').css('opacity', '0').animate({
                    height: height_ph,
                    opacity: 1
                  }, 500, "swing", function(){
                    $(placeholder_id).css('height', '100%');
                  });
                }
            });
          }
        }).addClass("processed"); //Prevent multi attach to this listner on the same div

        $(".cadre_og_grid").not(".processed-enter").mousemove(function(e){
            var target = $(e.target);
            var path = target.children(".crumb_path").html();
            while (path === undefined){
              var target = target.parent();
              path = target.children(".crumb_path").html();
            }
            $("#float_crumbs").css("display", "block");
            $("#float_crumbs").html(path);
        }).addClass("processed-enter"); //Prevent multi attach to this listner on the same div

       $(".cadre_og_grid").not(".processed-move").mousemove(function(e){
          if($("#float_crumbs").css("display") === "none"){
            var target = $(e.target);
            var path = target.children(".crumb_path").html();
            while (path === undefined){
              var target = target.parent();
              path = target.children(".crumb_path").html();
            }
            $("#float_crumbs").css("display", "block");
            $("#float_crumbs").html(path);
          }
        }).addClass("processed-move"); //Prevent multi attach to this listner on the same div

        $(".cadre_og_grid").not(".processed-leave").mouseleave(function(e){
          $("#float_crumbs").css("display", "none");
        }).addClass("processed-leave"); //Prevent multi attach to this listner on the same div
     }
}

Drupal.behaviors.gofast_og_grid_ztree = {
    attach: function (context, settings) {
      context = $(context);

      $('#ztree_og_grid:not(.ztree-processed)', context).addClass('ztree-processed').each(function() {
        var data_tree = {};

        if (Drupal.settings.gofast_og_tree) {
          data_tree = $.parseJSON(Drupal.settings.gofast_og_tree.data_tree);
        }

        var settings = {  data: {
                                simpleData: {
                                    enable: true,
                                    }
                          },
                          view: {
                                showIcon: false,
                                selectedMulti: false,
                                fontCss: {color:"#428bca"},
                                txtSelectedEnable: false,
                                dblClickExpand: false,
                          },
                         callback: {
                           onClick: gofast_og_ztree_click,
                           beforeExpand: gofast_og_ztree_expand,
                           beforeCollapse: gofast_og_ztree_collapse
                          }
                       };
        var zTreeObj = $.fn.zTree.init($("#ztree_og_grid"), settings, data_tree);
        var topNode = zTreeObj.getNodeByParam('nId', -1);
        zTreeObj.expandNode(topNode, true, false, false, false);
      });
    }
  }

  Drupal.behaviors.gofast_og_grid_ztree_af = {
    attach: function (context, settings) {
      context = $(context);

      $('#ztree_og_grid_af_filter:not(.ztree-processed)', context).addClass('ztree-processed').each(function() {
        var data_tree = {};
        if (Drupal.settings.gofast_og_tree_af_filter) {
          data_tree = $.parseJSON(Drupal.settings.gofast_og_tree_af_filter.data_tree);
        }

        var settings = {  data: {
                                simpleData: {
                                    enable: true,
                                    }
                          },
                          view: {
                                showIcon: false,
                                selectedMulti: false,
                                fontCss: {color:"#428bca"},
                                txtSelectedEnable: false,
                                dblClickExpand: false,
                          },
                         callback: {
                           onClick: gofast_og_ztree_af_click,
                           beforeExpand: gofast_og_ztree_expand,
                           beforeCollapse: gofast_og_ztree_collapse
                          }
                       };
        var zTreeObj = $.fn.zTree.init($("#ztree_og_grid_af_filter"), settings, data_tree);
        var topNode = zTreeObj.getNodeByParam('nId', -1);
        zTreeObj.expandNode(topNode, true, false, false, false);
      });
    }
  }

  Drupal.behaviors.gofast_og_grid_ztree_af_orga = {
    attach: function (context, settings) {
      context = $(context);

      $('#ztree_og_grid_af_filter_orga:not(.ztree-processed)', context).addClass('ztree-processed').each(function() {
        var data_tree = {};
        if (Drupal.settings.gofast_og_tree_af_filter_orga) {
          data_tree = $.parseJSON(Drupal.settings.gofast_og_tree_af_filter_orga.data_tree);
        }

        var settings = {  data: {
                                simpleData: {
                                    enable: true,
                                    }
                          },
                          view: {
                                showIcon: false,
                                selectedMulti: false,
                                fontCss: {color:"#428bca"},
                                txtSelectedEnable: false,
                                dblClickExpand: false,
                          },
                         callback: {
                           onClick: gofast_og_ztree_af_click,
                           beforeExpand: gofast_og_ztree_expand,
                           beforeCollapse: gofast_og_ztree_collapse
                          }
                       };
        var zTreeObj = $.fn.zTree.init($("#ztree_og_grid_af_filter_orga"), settings, data_tree);
        var topNode = zTreeObj.getNodeByParam('nId', -1);
        zTreeObj.expandNode(topNode, true, false, false, false);
      });
    }
  }

    Drupal.behaviors.gofast_og_grid_ztree_af_extranet = {
    attach: function (context, settings) {
      context = $(context);

      $('#ztree_og_grid_af_filter_extranet:not(.ztree-processed)', context).addClass('ztree-processed').each(function() {
        var data_tree = {};
        if (Drupal.settings.gofast_og_tree_af_filter_extranet) {
          data_tree = $.parseJSON(Drupal.settings.gofast_og_tree_af_filter_extranet.data_tree);
        }

        var settings = {  data: {
                                simpleData: {
                                    enable: true,
                                    }
                          },
                          view: {
                                showIcon: false,
                                selectedMulti: false,
                                fontCss: {color:"#428bca"},
                                txtSelectedEnable: false,
                                dblClickExpand: false,
                          },
                         callback: {
                           onClick: gofast_og_ztree_af_click,
                           beforeExpand: gofast_og_ztree_expand,
                           beforeCollapse: gofast_og_ztree_collapse
                          }
                       };
        var zTreeObj = $.fn.zTree.init($("#ztree_og_grid_af_filter_extranet"), settings, data_tree);
        var topNode = zTreeObj.getNodeByParam('nId', -1);
        zTreeObj.expandNode(topNode, true, false, false, false);
      });
    }
  }

    Drupal.behaviors.gofast_og_grid_ztree_af_public = {
    attach: function (context, settings) {
      context = $(context);

      $('#ztree_og_grid_af_filter_public:not(.ztree-processed)', context).addClass('ztree-processed').each(function() {
        var data_tree = {};
        if (Drupal.settings.gofast_og_tree_af_filter_public) {
          data_tree = $.parseJSON(Drupal.settings.gofast_og_tree_af_filter_public.data_tree);
        }

        var settings = {  data: {
                                simpleData: {
                                    enable: true,
                                    }
                          },
                          view: {
                                showIcon: false,
                                selectedMulti: false,
                                fontCss: {color:"#428bca"},
                                txtSelectedEnable: false,
                                dblClickExpand: false,
                          },
                         callback: {
                           onClick: gofast_og_ztree_af_click,
                           beforeExpand: gofast_og_ztree_expand,
                           beforeCollapse: gofast_og_ztree_collapse
                          }
                       };
        var zTreeObj = $.fn.zTree.init($("#ztree_og_grid_af_filter_public"), settings, data_tree);
        var topNode = zTreeObj.getNodeByParam('nId', -1);
        zTreeObj.expandNode(topNode, true, false, false, false);
      });
    }
  }

   function gofast_og_ztree_af_click(event, treeId, treeNode, clickFlag){
    var zTreeObj = $.fn.zTree.getZTreeObj(treeId);
    var gid = treeNode.nId;
    //simulate click to the non indented element into the space filter
    $("#"+gid).click();

  }

  function gofast_og_ztree_click(event, treeId, treeNode, clickFlag){
    var zTreeObj = $.fn.zTree.getZTreeObj(treeId);
    var gid = treeNode.nId;
    $("html, body").animate({ scrollTop: $('.container_'+gid).offset().top-60}, 500, function(){
      $('.container_'+gid).children('.cadre_og_grid').animate({ backgroundColor: "#CCC"}, 50, function(){
        $('.container_'+gid).children('.cadre_og_grid').animate({ backgroundColor: "#FFF"}, 500, function(){
          $('.container_'+gid).children('.cadre_og_grid').removeProperty('background-color');
        });
      });
    });

    //zTreeObj.expandNode(treeNode, false, false, false, true);
    //zTreeObj.expandNode(treeNode, true, false, false, true);
  }

  function gofast_og_ztree_expand(treeId, treeNode){
    fromTree = true;
    var zTreeObj = $.fn.zTree.getZTreeObj(treeId);
    var gid = treeNode.nId;
    $('#caller_'+gid).trigger('click');
    fromTree = false;
  }

  function gofast_og_ztree_collapse(treeId, treeNode){
    fromTree = true;
    var zTreeObj = $.fn.zTree.getZTreeObj(treeId);
    var gid = treeNode.nId;
    $('#caller_'+gid).trigger('click');
    fromTree = false;
  }

    Drupal.behaviors.gofast_members_space_async = {
        attach: function (context, settings) {
            if($('#tab_ogmembers_disabled').length == 0){
                if($('#tab_ogmembers:not(.members_processed)').parent().hasClass('active')){
                    $("#tab_ogmembers:not(.members_processed)").addClass("members_processed");
                    var nid = $(".gofast-og-page").attr("id").replace("node-", "");
                     $("#ogmembers").load( "/gofast_og/space_members_async/" + nid, function (response, status, xhr){
                         if(status == "success"){
                             Drupal.attachBehaviors();
                         }
                     });
                }
                $("#tab_ogmembers:not(.members_processed)").addClass("members_processed").click(function(){
                    var nid = $(".gofast-og-page").attr("id").replace("node-", "");
                     $("#ogmembers").load( "/gofast_og/space_members_async/" + nid, function (response, status, xhr){
                         if(status == "success"){
                             Drupal.attachBehaviors();
                         }
                     });
                });
            }else{
                $('#tab_ogmembers_disabled').css('pointer-events','none');
                $("#tab_ogmembers:not(.members_processed)").addClass("members_processed").click(function(e){
                    e.preventDefault();
                    return false;
                });
            }
        }
    };

    Drupal.behaviors.gofast_activity_space_async = {
        attach: function (context, settings) {
                if($('#tab_ogactivity:not(.activity_processed)').parent().hasClass('active')){
                    $("#tab_ogactivity:not(.activity_processed)").addClass("activity_processed");
                    var nid = $(".gofast-og-page").attr("id").replace("node-", "");
                     $("#ogactivity").load( "/gofast_og/space_activity_async/" + nid, function (response, status, xhr){
                         if(status == "success"){
                             Drupal.attachBehaviors();
                         }
                     });
                }
            $("#tab_ogactivity:not(.activity_processed)").addClass("activity_processed").click(function(){
                        var nid = $(".gofast-og-page").attr("id").replace("node-", "");
                         $("#ogactivity").load( "/gofast_og/space_activity_async/" + nid, function (response, status, xhr){
                             if(status == "success"){
                                 Drupal.attachBehaviors();
                             }
                         });
            });
        }
    };

        Drupal.behaviors.gofast_home_page_async = {
        attach: function (context, settings) {
              setTimeout(function(){
                if($('#ogtab_home:not(.activity_processed)').parent().hasClass('active')){
                    $("#ogtab_home:not(.activity_processed)").addClass("activity_processed");
                    var nid = $(".gofast-og-page").attr("id").replace("node-", "");
                     $("#oghome").load( "/gofast_og/home_async/" + nid, function (response, status, xhr){
                         if(status == "success"){
                             Drupal.attachBehaviors();
                         }
                     });
                }
            }, 2000 );
            $("#ogtab_home:not(.activity_processed)").click(function(){
                       $(this).addClass("activity_processed");
                        var nid = $(".gofast-og-page").attr("id").replace("node-", "");
                        if($("#oghome").html().trim() == "<span></span>"){
                            $("#oghome").load( "/gofast_og/home_async/" + nid, function (response, status, xhr){
                                if(status == "success"){
                                    Drupal.attachBehaviors();
                                }
                            });
                        }
            });
        }
    };

  Gofast.og_preadd_validation_process = function () {
    var panel = $(".preadd-validation-panel");

    //For each panel, process the request and check the result
        //Retrieve nid
        var nid = $(panel).find('#nid').text();
        if (nid > 0) { } else {
          $(panel).find('.panel-body').find(".preadd-validation-info").html("<i class='fa fa-times' style='color:red' aria-hidden='true'></i> " + Drupal.t("This modification cannot be done currently. Please try again later.", {}, { context: 'gofast:taxonomy' }));
          return true;
        }
        //Retrieve locations
        var usersPreAdd = JSON.parse($(panel).find('#users_preadd').text());
        $(panel).find('.panel-body').find(".preadd-validation-info").html("<i class='fa fa-arrow-right' style='color:#3498db' aria-hidden='true'></i> " + Drupal.t("Processing...", {}, { context: 'gofast:taxonomy' }));

        var barWidth = usersPreAdd.length;
        var count = 0;
        var actionPost;
        var timeoutPreadd;

        usersPreAdd.forEach(function (userPreaAdd) {
          count++
          if (count == usersPreAdd.length) {
            actionPost = "join_preadd_send";
            timeoutPreadd = 3000;
          } else {
            actionPost = "join_preadd"
            timeoutPreadd = 0;
          }

            $.ajax({
              type: "POST",
              async: false,
              url: location.origin + "/og/preadd/process",
              data: {nid: nid, action: actionPost, user_to_add: userPreaAdd },
              timeout: timeoutPreadd,
              success: function (data) {
                var returnData = jQuery.parseJSON(data);
                if (returnData.success == false) {
                  $("span.user-preadd-span#" + returnData.uid).append(" - " + returnData.message + " <i class='fa fa-info' style='color:red' aria-hidden='true'></i>");
                } else {
                  $("span.user-preadd-span#" + returnData.uid).append("<i class='fa fa-check' style='color:green' aria-hidden='true'></i>");
                }

                var barProgressValue = 100 / barWidth;
                $('#modal-content .progress-bar').width(barProgressValue * 10);
                $('#modal-content .progress-bar').html(Math.floor(barProgressValue) + "%");
                if (Math.floor(barProgressValue) === 100) {
                  $('.progress-bar').removeClass('progress-bar-striped');
                  $('.progress-bar').addClass('progress-bar-success');
                  $('.progress-bar').html(Drupal.t('Completed', {}, { 'context': "gofast:gofast_taxonomy" }));
                  $(panel).find('.panel-body').find(".preadd-validation-info").html("<i class='fa fa-check' style='color:green' aria-hidden='true'></i> " + Drupal.t("Processed !", {}, { context: 'gofast:taxonomy' }));
                }
                barWidth--;
              }
            });
        });
  };

})(jQuery, Gofast, Drupal);
