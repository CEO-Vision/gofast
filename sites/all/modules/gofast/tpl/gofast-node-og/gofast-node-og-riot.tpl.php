    <?php if ($node->field_riot_identifier[LANGUAGE_NONE][0]['value'] != '') : ?>
      <div id="DivRiot"></div>
      <!--<iframe src="/sites/all/libraries/riot/index.html#/room/<?php echo $node->field_riot_identifier[LANGUAGE_NONE][0]['value']; ?>" id="gf_conversation" style="width:100%;height: calc(100vh - 180px);border:none;"></iframe> -->
    <?php else : ?>
      <span class="RiotMessageRoom"> <?php print t('This collaboratif space does not have any chatroom yet.'); ?>
        <?php global $user;
        if (in_array('administrator member', gofast_og_get_user_final_roles_for_space('node', $node->nid, $user->uid), true) || $user->uid == 1) : ?>
          <?php print t('The administrator of this space can create a chatroom via the context actions menu.'); ?>
          ( <i class="fa fa-bars" aria-hidden="true"></i> )
      </span>
    <?php else : ?>
      <?php print t('Please contact a space administrator (“Members” tab) to ask for the creation of a linked chatroom.'); ?></span>
    <?php endif; ?>

    <?php endif; ?>
