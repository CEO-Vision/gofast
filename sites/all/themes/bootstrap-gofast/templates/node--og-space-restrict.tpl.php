<div id="fullscreen-node">
   <?php
   if(gofast_group_is_archive($node)){ ?>
    <div class="alert alert-warning">
        <h4 style="font-size: 12px "><?php print t('This space is archived', array(), array('context' => 'gofast')) ?></h4>
    </div>
   <?php } ?>
  <div id="node-<?php print $node->nid; ?>" class="gofast-og-page <?php print $classes; ?> clearfix"<?php print $attributes; ?>>
    
    <div class="alert alert-warning" style="min-height: 50px;" role="alert">
    <?php if(!$isMember){?>
      <span id="textmembership_<?php echo $node->nid; ?>" style="font-size: 13px; color: red; "><?php print t("You are not member of this space !", array(), array("context" => "gofast")); ?></span>
      <span class="btn-group" role="group" style="float:right; margin-right: 5px; margin-bottom: 10px; margin-top: -10px;">
        <?php if($groupCanBeJoin){ ?>
          <button type="button" class="btn btn-default joinbtn" id="join_<?php echo $nid; ?>"><span id="iconjoin_<?php echo $nid; ?>" class="glyphicon glyphicon-ok" style="margin-right:7px;"></span><span id="textjoin_<?php echo $nid; ?>"><?php echo(t("Join", array(), array('context' => 'gofast:og'))); ?></span></button>
        <?php } ?>
      </span>
    <?php }else{ ?>
      <span id="textmembership_<?php echo $node->nid; ?>" style="font-size: 13px; color: blue;"><?php print t("You are not yet a member of this space : your join request is still pending !", array(), array("context" => "gofast")); ?></span>
      <span class="btn-group" role="group" style="float:right; margin-right: 5px; margin-bottom: 10px; margin-top: -10px;">
        <?php if($groupCanBeJoin){ ?>
          <button type="button" class="btn btn-default cancelbtn" id="cancel_<?php echo $nid; ?>"><span id="iconcancel_<?php echo $nid; ?>" class="glyphicon glyphicon-remove" style="margin-right:7px;"></span><span id="textcancel_<?php echo $nid; ?>"><?php echo(t("Cancel", array(), array('context' => 'gofast:og'))); ?></span></button>
        <?php } ?>
      </span>
    <?php } ?>
    </div>
    
    <div class="content"<?php print $content_attributes; ?>>
      <div>
        <ul class="nav nav-tabs nav-justified" role="tablist">
          <li role="presentation" class="active"><a href="#oghome" aria-controls="oghome" role="tab" data-toggle="tab"><?php print t("Home"); ?></a></li>
          <li role="presentation" class="disabled"><a><?php print t("Activity"); ?></a></li>
          <li class="disabled"><a target="#" ><?php print t("Documents"); ?></a></li>
          <li class="disabled"><a target="#" ><?php print t('Tasks', array(), array('context' => 'gofast_kanban')); ?></a></li>
          <li role="presentation" class="disabled"><a><?php print t("Calendar"); ?></a></li>
          <?php if(!gofast_og_is_entity_hide_members_tab($node)): ?>
          <li role="presentation" class="disabled"><a><?php print t("Members"); ?></a></li>
          <?php endif; ?>
        </ul>

        <div class="tab-content content well well-sm">
          <div role="tabpanel" class="tab-pane active" id="oghome">
            <?php
            print $node_body;
            ?>
          </div>
        </div>        
      </div>
    </div>
  </div>
</div>
