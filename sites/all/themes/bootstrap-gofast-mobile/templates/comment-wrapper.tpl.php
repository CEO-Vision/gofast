<?php

/**
 This file overrides comment-wrapper of comment module (core module)
 */
?>
<div id="forum-comments" class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <?php 
    print render($content['comments']); 
  ?>
  <?php if ($content['comment_form']): ?>
    <h2 class="title comment-form"><?php print t('Add new comment'); ?></h2>
    <?php print render($content['comment_form']); ?>
  <?php endif; ?>
</div>
