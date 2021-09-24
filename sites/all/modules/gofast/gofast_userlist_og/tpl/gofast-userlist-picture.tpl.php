<?php

/**
 * @file
 * Gofast theme implementation to present a picture configured for the
 * userlist.
 *
 * @see template_preprocess_member_picture()
 *
 * @ingroup themeable
 */
?>
<?php //if (!$userlist_picture) $userlist_picture = "<img alt='{$userlist->name}' />"; ?>
<div class="<?php echo implode(' ', $classes_array); ?>" id="<?php echo "{$member->etid}-" . rand(0, 10000); ?>">
  <div class="profile-popup-wrapper">
    <div class="profile-popup">
      <!-- ajax load profile popup -->
    </div>
  </div>
  <span class="fa fa-users userlist fa-3x"></span>
</div>
