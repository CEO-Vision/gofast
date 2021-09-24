<?php 

    $node=node_load($nid); 
    
    $spaces_defaults = gofast_admin_get_space_defaults();
    $first_level_spaces = array();
          
    if($spaces_defaults['create_sub_space']){
        $first_level_spaces = array_merge(
            gofast_og_get_children(4, FALSE, FALSE, TRUE),
            gofast_og_get_children(6, FALSE, FALSE, TRUE)
        );
    }
    
    if(in_array($nid, $first_level_spaces)){
        $create_sub_space_ro = TRUE;
    }
?>
<?php
 //make sure the Views js files had been added to the page
           $views_path = drupal_get_path('module', 'views');
           drupal_add_js(
               $views_path . '/js/base.js',
               array(
                   'type' => 'file',
                   'scope' => 'footer',
                   'group' => JS_DEFAULT,
               )
           );
           drupal_add_js(
               $views_path . '/js/ajax_view.js',
               array(
                   'type' => 'file',
                   'scope' => 'footer',
                   'group' => JS_DEFAULT,
               )
           );
?>


<?php $members_filter_form = drupal_get_form( 'gofast_og_member_filter_form'); print drupal_render($members_filter_form); ?>

<h4>
    <span class="fa-stack fa-md">
        <i class="fa fa-shield fa-stack-2x" style="color: gray;"></i>
        <i class="fa fa-stack-1x" style="font-weight: bolder;">A</i>
    </span>
    <?php print t('Space administrators', array(), array('context' => 'gofast:gofast_og')); ?>
    <i class="fa fa-question-circle" style="color:#525252" onmouseover="displayPanelTip(this)" onmouseout="hidePanelTip(this)"></i>
    <div class="panel panel-primary" style="width: 500px; position: absolute; z-index: 10; display: none;">
        <div class="panel-heading" style="font-weight: normal; font-size: 14px;"><?php print t('Permissions of a space administrator', array(), array('context' => 'gofast:gofast_og')); ?></div>
        <div class="panel-body" style="font-size: 12px; color:#525252; font-weight: normal;">
            <strong><?php print t('Can :', array(), array('context' => 'gofast:gofast_og')); ?></strong><br />
            <ul>
                <li><?php print t('Add / Remove members in this space and set their roles', array(), array('context' => 'gofast:gofast_og')); ?></li>
                <li><?php print t("Edit the space's home page and rename / Delete the space", array(), array('context' => 'gofast:gofast_og')); ?></li>
                <li><?php print t('Create a sub space', array(), array('context' => 'gofast:gofast_og')); ?></li>
                <li><?php print t('Create a user in the space', array(), array('context' => 'gofast:gofast_og')); ?></li>
                <li><?php print t('Create / Edit / Comment / Annotate / Publish / Move and Delete contents of this space', array(), array('context' => 'gofast:gofast_og')); ?></li>
                <li><?php print t('Start a standard document broadcast workflow', array(), array('context' => 'gofast:gofast_og')); ?></li>
            </ul>
        </div>
    </div>
  </h4>
    <script type='text/javascript'>                      
                         jQuery.ajax({
                                    url: '/views/ajax',
                                    type: 'post',
                                    data: {
                                      view_name: 'gofast_og_members_page',
                                      view_display_id: 'gofast_og_members_role_admin_page', //your display id
                                      view_args: '<?php echo $node->nid; ?>', // your views argument(s)
                                    },
                                    dataType: 'json',
                                    success: function (response) {
                                      if (response[2] !== undefined) {
                                            jQuery("#gofast_og_members_page_gofast_og_members_role_admin_page").html(response[2].data);
                                            // Set views key based on response data. 
                                            Drupal.settings.views = response[0].settings.views;
                                            Drupal.attachBehaviors();

                                      }
                                    }
                                  });
   </script>
   <div id="gofast_og_members_page_gofast_og_members_role_admin_page"></div>                  

<h4>
    <span class="fa-stack fa-md">
        <i class="fa fa-shield fa-stack-2x" style="color: gray;"></i>
        <i class="fa fa-stack-1x" style="font-weight: bolder;">C</i>
    </span>
    <?php print t('Space contributors', array(), array('context' => 'gofast:gofast_og')); ?>
    <i class="fa fa-question-circle" style="color:#525252" onmouseover="displayPanelTip(this)" onmouseout="hidePanelTip(this)"></i>
    <div class="panel panel-primary" style="width: 500px; position: absolute; z-index: 10; display: none;">
        <div class="panel-heading" style="font-weight: normal; font-size: 14px;"><?php print t('Permissions of a space contributor', array(), array('context' => 'gofast:gofast_og')); ?></div>
        <div class="panel-body" style="font-size: 12px; color:#525252; font-weight: normal;">
            <strong><?php print t('Can :', array(), array('context' => 'gofast:gofast_og')); ?></strong><br />
            <ul>
                <?php if($create_sub_space_ro){print "<li>" . t('Create a sub space', array(), array('context' => 'gofast:gofast_og')) . "</li>";} ?>
                <li><?php print t('Create / Edit / Comment / Annotate / Publish contents of this space', array(), array('context' => 'gofast:gofast_og')); ?></li>
                <li><?php print t("Move / Delete their own contents", array(), array('context' => 'gofast:gofast_og')); ?></li>
                <li><?php print t('Start a standard document broadcast workflow', array(), array('context' => 'gofast:gofast_og')); ?></li>
            </ul>
            <strong><?php print t('Cannot :', array(), array('context' => 'gofast:gofast_og')); ?></strong><br />
            <ul>
                <li><?php print t("Move / Delete other's contents", array(), array('context' => 'gofast:gofast_og')); ?></li>
                <li><?php print t("Manage the space", array(), array('context' => 'gofast:gofast_og')); ?></li>
            </ul>
        </div>
    </div>
 </h4>
   <script type='text/javascript'>                      
                         jQuery.ajax({
                                    url: '/views/ajax',
                                    type: 'post',
                                    data: {
                                      view_name: 'gofast_og_members_page',
                                      view_display_id: 'gofast_og_members_role_contrib_page', //your display id
                                      view_args: '<?php echo $node->nid; ?>', // your views argument(s)
                                    },
                                    dataType: 'json',
                                    success: function (response) {
                                      if (response[2] !== undefined) {
                                            jQuery("#gofast_og_members_page_gofast_og_members_role_contrib_page").html(response[2].data);
                                            // Set views key based on response data. 
                                            Drupal.settings.views = response[0].settings.views;
                                            Drupal.attachBehaviors();

                                      }
                                    }
                                  });
   </script>
   <div id="gofast_og_members_page_gofast_og_members_role_contrib_page"></div>   

<h4>
    <span class="fa-stack fa-md">
        <i class="fa fa-shield fa-stack-2x" style="color: gray;"></i>
        <i class="fa fa-stack-1x" style="font-weight: bolder;"></i>
      </span>
    <?php print t('Read only members', array(), array('context' => 'gofast:gofast_og')); ?>
    <i class="fa fa-question-circle" style="color:#525252" onmouseover="displayPanelTip(this)" onmouseout="hidePanelTip(this)"></i>
    <div class="panel panel-primary" style="width: 500px; position: absolute; z-index: 10; display: none;">
        <div class="panel-heading" style="font-weight: normal; font-size: 14px;"><?php print t('Permissions of a read only member', array(), array('context' => 'gofast:gofast_og')); ?></div>
        <div class="panel-body" style="font-size: 12px; color:#525252; font-weight: normal;">
            <strong><?php print t('Can :', array(), array('context' => 'gofast:gofast_og')); ?></strong><br />
            <ul>
                <?php if($create_sub_space_ro){print "<li>" . t('Create a sub space', array(), array('context' => 'gofast:gofast_og')) . "</li>";} ?>
                <li><?php print t('View / Comment / Annotate contents of this space', array(), array('context' => 'gofast:gofast_og')); ?></li>
                <li><?php print t('Start a standard document broadcast workflow', array(), array('context' => 'gofast:gofast_og')); ?></li>
            </ul>
            <strong><?php print t('Cannot :', array(), array('context' => 'gofast:gofast_og')); ?></strong><br />
            <ul>
                <li><?php print t("Create / Publish / Move / Delete contents of this space", array(), array('context' => 'gofast:gofast_og')); ?></li>
                <li><?php print t("Manage the space", array(), array('context' => 'gofast:gofast_og')); ?></li>
            </ul>
        </div>
    </div>
  </h4>
   <script type='text/javascript'>                      
                         jQuery.ajax({
                                    url: '/views/ajax',
                                    type: 'post',
                                    data: {
                                      view_name: 'gofast_og_members_page',
                                      view_display_id: 'gofast_og_members_role_member_page', //your display id
                                      view_args: '<?php echo $node->nid; ?>', // your views argument(s)
                                    },
                                    dataType: 'json',
                                    success: function (response) {
                                      if (response[2] !== undefined) {
                                            jQuery("#gofast_og_members_page_gofast_og_members_role_member_page").html(response[2].data);
                                            // Set views key based on response data. 
                                            Drupal.settings.views = response[0].settings.views;
                                            Drupal.attachBehaviors();

                                      }
                                    }
                                  });
   </script>
   <div id="gofast_og_members_page_gofast_og_members_role_member_page"></div>  

<h4>
    <span class="fa-stack fa-md">
        <i class="fa fa-shield fa-stack-2x" style="color: gray;"></i>
        <i class="fa fa-stack-1x" style="font-weight: bolder;">R</i>
    </span>
    <?php print t('Requesters', array(), array('context' => 'gofast:gofast_og')); ?>
</h4>
   <script type='text/javascript'>                      
                         jQuery.ajax({
                                    url: '/views/ajax',
                                    type: 'post',
                                    data: {
                                      view_name: 'gofast_og_members_page',
                                      view_display_id: 'gofast_og_members_pending_request_page', //your display id
                                      view_args: '<?php echo $node->nid; ?>', // your views argument(s)
                                    },
                                    dataType: 'json',
                                    success: function (response) {
                                      if (response[2] !== undefined) {
                                            jQuery("#gofast_og_members_page_gofast_og_members_pending_request_page").html(response[2].data);
                                            // Set views key based on response data. 
                                            Drupal.settings.views = response[0].settings.views;
                                            Drupal.attachBehaviors();

                                      }
                                    }
                                  });
   </script>
   <div id="gofast_og_members_page_gofast_og_members_pending_request_page"></div> 

<h4>
    <span class="fa-stack fa-md">
        <i class="fa fa-shield fa-stack-2x" style="color: gray;"></i>
        <i class="fa fa-ban fa-stack-1x" style="font-weight: bolder;"></i>
    </span>
    <?php print t('Blocked users', array(), array('context' => 'gofast:gofast_og')); ?>
</h4>
      <script type='text/javascript'>                      
                         jQuery.ajax({
                                    url: '/views/ajax',
                                    type: 'post',
                                    data: {
                                      view_name: 'gofast_og_members_page',
                                      view_display_id: 'gofast_og_banned_members', //your display id
                                      view_args: '<?php echo $node->nid; ?>', // your views argument(s)
                                    },
                                    dataType: 'json',
                                    success: function (response) {
                                      if (response[2] !== undefined) {
                                            jQuery("#gofast_og_members_page_gofast_og_banned_members").html(response[2].data);
                                            // Set views key based on response data. 
                                            Drupal.settings.views = response[0].settings.views;
                                            Drupal.attachBehaviors();

                                      }
                                    }
                                  });
   </script>
   <div id="gofast_og_members_page_gofast_og_banned_members"></div> 

   <script>
        function displayPanelTip(elem){
            var tip = jQuery(elem).parent().find("div.panel");
            tip.show();
        }   
    
        function hidePanelTip(elem){
           var tip = jQuery(elem).parent().find("div.panel");
            tip.hide();
        }
   </script>
