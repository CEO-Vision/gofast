<?php

/**
 * @file
 * Default theme implementation to present a picture configured for the
 * user's account.
 *
 * Available variables:
 * - $user_picture: Image set by the user or the site's default. Will be linked
 *   depending on the viewer's permission to view the user's profile page.
 * - $account: Array of account information. Potentially unsafe. Be sure to
 *   check_plain() before use.
 *
 * @see template_preprocess_user_picture()
 *
 * @ingroup themeable
 */
?>
<?php if (!$user_picture) $user_picture = "<img alt='{$account->name}' />"; ?>
<div class="<?php echo implode(' ', $classes_array); ?>" id="<?php echo "{$account->uid}-" . rand(0, 10000); ?>">
  <div class="profile-popup-wrapper">
    <div class="profile-popup"><!-- ajax load profile popup --></div>
  </div>
  <?php print $user_picture; ?>
</div>