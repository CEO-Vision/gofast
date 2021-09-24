<?php

/**
 * @file
 * Gofast theme implementation to present a picture configured for the
 * user's account.
 *
 * @see template_preprocess_user_picture()
 *
 * @ingroup themeable
 */
?>
<?php if (!$user_picture) $user_picture = "<img alt='{$account->name}' />"; ?>
<div class="<?php echo implode(' ', $classes_array); ?>" id="<?php echo "{$account->uid}-" . rand(0, 10000); ?>">
  <div class="profile-popup-wrapper">
    <div class="profile-popup">
      <!-- ajax load profile popup -->
    </div>
  </div>
  <?php print $user_picture; ?>
</div>
