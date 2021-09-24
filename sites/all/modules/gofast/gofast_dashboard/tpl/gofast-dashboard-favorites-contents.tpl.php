<?php
/**
 * @file
 * Displays list of Group shortcut of a user
 *
 * Available variables:
 *
 * @see template_preprocess_gofast_cdel_dashboard_shortcut_group()
 *
 * @ingroup themeable
 */
?>
  <div class="panel panel-dashboard panel-dashboard-big panel-default">
    <div class="panel-heading">
      <div class="row">
        <div class="col-sm-11" style="font-weight: bold">
          <?php print t('My favorite contents', array(), array('context' => 'gofast_dashboard'))?>
        </div>

        <div class="col-sm-1">
          <a href="/modal/nojs/dashboard_add_content_to_dashboard" class="ctools-use-modal" data-toggle="tooltip" title="<?php echo t('Pin new contents', array(), array('context' => 'gofast_cd74')); ?>">
            <span class="fa fa-plus"></span>
          </a>
        </div>
      </div>
    </div>
    <div id="dashboard-favorite-contents" class="panel-body">
       <?php echo views_embed_view('gofast_flag_bookmarks', "page_1") ?>
    </div>
  </div>

<script>
    jQuery("document").ready(function(){
        //Load menu asyncly
        jQuery(".dropdown-placeholder").not(".dropdown-processed").addClass("dropdown-processed").click(function(){
          if(! jQuery(this).hasClass("dropdown-processing")){
            var nid = this.id.substring(21);
	    if(jQuery(this).parents('#gofast-node-actions-microblogging').length > 0){
		var microblogging = true;
	    }
            var div = jQuery(this).parent();
            var container = div.parent();

            //Animation
            jQuery(this).addClass("dropdown-processing");
            jQuery("#dropdownactive-placeholder-" + nid).show();
	    if(microblogging === true){
		jQuery.post(location.origin+"/activity/ajax/microblogging/menu/"+nid, function(data){
		    var newdiv = div.replaceWith(data);
		    Drupal.attachBehaviors();
		    container.find(".gofast-node-actions").addClass("open");

		    //Align menu
		    console.log(Gofast.last_menu_align);
		    if(Gofast.last_menu_align === "up"){
			jQuery(".gofast-dropdown-menu:not(.dropdown-menu-right)").css("top", "100%").css("bottom", "inherit");
			jQuery(".gofast-dropdown-menu.dropdown-menu-right").css("top", "inherit").css("bottom", "0px");
		    }else{
			jQuery(".gofast-dropdown-menu:not(.dropdown-menu-right)").css("bottom", "100%").css("top", "inherit");
			jQuery(".gofast-dropdown-menu.dropdown-menu-right").css("top", "inherit").css("bottom", "0px");
		    }
		});
	    }else{
		//Load menu
		jQuery.post(location.origin+"/activity/ajax/menu/"+nid, function(data){
		  var newdiv = div.replaceWith(data);
		  Drupal.attachBehaviors();
		  container.find(".gofast-node-actions").addClass("open");

		  //Align menu
		  console.log(Gofast.last_menu_align);
		  if(Gofast.last_menu_align === "up"){
		    jQuery(".gofast-dropdown-menu:not(.dropdown-menu-right)").css("top", "100%").css("bottom", "inherit");
		    jQuery(".gofast-dropdown-menu.dropdown-menu-right").css("top", "inherit").css("bottom", "0px");
		  }else{
		    jQuery(".gofast-dropdown-menu:not(.dropdown-menu-right)").css("bottom", "100%").css("top", "inherit");
		    jQuery(".gofast-dropdown-menu.dropdown-menu-right").css("top", "inherit").css("bottom", "0px");
		  }
		});
	    }
          }
        });
    });
</script>
