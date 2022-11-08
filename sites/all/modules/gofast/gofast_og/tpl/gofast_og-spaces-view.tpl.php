<?php
/*
 * Display the spaces and their childrens.
 *
 */
?>
<div id="og_level_container" class="container_<?php echo $nid; ?>">
  <div class="cadre_og_grid view-content">
    <table style="min-height: 160px; max-height: 146px; margin-top: -12px; width: 100%">
      <tbody>
        <tr>
          <td>
            <div style="margin-top: 16px;"></div>
          </td>
        </tr>
        <tr class="profile-view" style="padding-bottom:5px;">
          <td style="text-align: center;">
            <?php if ($isMember && !$isPending) { ?>
              <span style="border:none; font-size: 17px; font-weight: bold; margin-top: 10px;"><span class="field-content"><a href="/node/<?php echo $nid; ?>"><?php echo $title; ?></a></span></span>
            <?php } else { ?>
              <span style="border:none; font-size: 17px; font-weight: bold; margin-top: 10px;"><span class="field-content"><?php echo $title; ?></span></span>
            <?php } ?>
            <span style="float:right; margin-top: 0; margin-right: 5px;"><span class="field-content"><?php echo t($type, array(), array('context' => 'gofast:og')); ?></span></span>
          </td>
        </tr>
        <tr style="border-top: 1px solid grey;">
          <td style="padding-top:15px;">
            <span class='glyphicon glyphicon-pencil'></span>
            <span style="font-weight:bold; font-size: 13px; "><span class="field-content" style="text-align: left"><?php echo $description; ?></span></span>
          </td>
        </tr>
        <tr>
          <td style="padding-top:15px;">
            <span class='glyphicon glyphicon-flash'></span>
            <span><?php echo t("Contributions", array(), array('context' => 'gofast:og')); ?>: <span class="field-content"><?php echo $contributions_count; ?></span></span>
          </td>
        </tr>
        <tr>
          <td>
            <span class='glyphicon glyphicon-user'></span>
            <span><?php echo t("Members", array(), array('context' => 'gofast:og')); ?>: <span class="field-content"><?php echo $members_count; ?></span></span>
          </td>
        </tr>
        <?php if (!$isMember) { ?>
          <tr>
            <td style="padding-top:20px;">
              <span id="textmembership_<?php echo $nid; ?>" style="font-size: 13px; color: red;"><?php echo (t("You are not member of this space.", array(), array('context' => 'gofast:og'))); ?></span>
              <?php $node = node_load($nid);
              if ($node->type != "public") { ?>
                <span class="btn-group" role="group" style="float:right; margin-right: 5px; margin-bottom: 10px; margin-top: -10px;">
                  <button type="button" class="btn btn-default joinbtn" id="join_<?php echo $nid; ?>"><span id="iconjoin_<?php echo $nid; ?>" class="glyphicon glyphicon-ok" style="margin-right:7px;"></span><span id="textjoin_<?php echo $nid; ?>"><?php echo (t("Join", array(), array('context' => 'gofast:og'))); ?></span></button>
                </span>
              <?php } ?>
            </td>
          </tr>
          <?php } else {
          foreach ($roles as $role) {
          ?>
            <tr>
              <td style="padding-top:20px;">
                <?php $role = t($role); ?>
                <span style="font-size: 13px; color: green;"><?php echo (t("You are @role in this space.", array('@role' => t($role)), array('context' => 'gofast:og'))); ?></span>
              </td>
            </tr>
        <?php }
        } ?>
        <?php if ($isPending) { ?>
          <tr>
            <td style="padding-top:20px;">
              <span id="textmembership_<?php echo $nid; ?>" style="font-size: 13px; color: blue;"><?php echo (t("You are a pending requester of this space.", array(), array('context' => 'gofast:og'))); ?></span>
              <span class="btn-group" role="group" style="float:right; margin-right: 5px; margin-bottom: 10px; margin-top: -10px;">
                <?php if ($isJoinable) { ?>
                  <button type="button" class="btn btn-default cancelbtn" id="cancel_<?php echo $nid; ?>"><span id="iconcancel_<?php echo $nid; ?>" class="glyphicon glyphicon-remove" style="margin-right:7px;"></span><span id="textcancel_<?php echo $nid; ?>"><?php echo (t("Cancel", array(), array('context' => 'gofast:og'))); ?></span></button>
                <?php } ?>
              </span>
            </td>
          </tr>
        <?php } ?>
        <?php if ($haveChilds) { ?>
          <tr style="padding-top: 10px;" class="caller_fill" id="caller_<?php echo $nid; ?>">
            <td style="text-align: center; border-top: solid 1px #c0c0c0; padding-top:7px; padding-bottom: 7px;">
              <span class="glyphicon glyphicon-arrow-down arrow_<?php echo $nid; ?>"></span>
              <span class='noselect' style="font-size: 17px; font-weight: bold;"><?php echo t("Sub spaces", array(), array('context' => 'gofast:og')); ?></span>
              <span class="glyphicon glyphicon-arrow-down arrow_<?php echo $nid; ?>"></span>
            </td>
          </tr>
        <?php } ?>

        <!----------------------------------- BEGIN AC pre-add member/userlist ----------------->
        <!-- Button to Open the Modal -->
        <?php
        $isAdmin = !empty($user->roles['3']);
        if ($isAdmin) {
          print theme('gofast_space_preadd_members', array('nid' => $nid));
        }
        ?>
        <!----------------------------------- END AC pre-add member/userlist ----------------->


      </tbody>
    </table>
    <span class='crumb_path' style='display:none;'><?php echo $path; ?></span>
  </div>
  <table style="margin-top: -12px; width: 100%">
    <tr style="padding-top: 10px;">
      <td id="placeholder_<?php echo $nid;  ?>" style='display:block;'></td>
    </tr>
  </table>
</div>
