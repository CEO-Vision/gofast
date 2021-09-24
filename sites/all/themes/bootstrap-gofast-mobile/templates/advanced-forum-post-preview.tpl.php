<?php

/**
 This file overrides post-review of advanced-forum module (3rd module)
 */
?>

<?php if ($top_post): ?>
  <a id="forum-topic-top"></a>
<?php else: ?>
  <a id="forum-reply-preview"></a>
<?php endif; ?>

<div id="<?php print $post_id; ?>" class="panel panel-default <?php print $classes; ?>" <?php print $attributes; ?>>
  <div class="panel-heading">
    <div class="forum-posted-on">
      <?php print $date ?>

      <?php if (!$top_post): ?>
        <?php if (!empty($first_new)): ?>
          <?php print $first_new; ?>
        <?php endif; ?>
        <?php if  (!empty($new_output)): ?>
          <?php print $new_output; ?>
        <?php endif; ?>
      <?php endif; ?>
      
      <?php if (!$top_post && !empty($comment_link) && !empty($page_link)): ?>
        <span class="forum-post-number"><?php print $comment_link . ' ' . $page_link; ?></span>
      <?php endif; ?>
    </div>

    
  </div>

  <div class="forum-post-wrapper">
    <div class="forum-post-panel-sub">
      <?php print $author_pane; ?>
    </div>

    <div class="forum-post-panel-main clearfix">
      <?php if ($title): ?>
        <div class="forum-post-title">
          <?php print $title ?>
        </div>
      <?php endif; ?>

      <div class="forum-post-content">
       <?php
          hide($content['links']['print_html']);
          hide($content['links']['print_mail']);

 
          if ($content['body']['#bundle'] == "forum") {
            echo $content['body']['#items'][0]['summary']; 
          } elseif ($content['body']['#bundle'] == "comment_node_forum") {
            echo $content['body']['#items'][0]['value']; 
          }
          
        ?>
      </div>

      <?php if (!empty($signature)): ?>
        <div class="author-signature">
          <?php print $signature ?>
        </div>
      <?php endif; ?>
    </div>
  </div>

	<div class="forum-post-footer clear-block">
    <?php /* Purposely empty on preview just to keep the structure intact. */ ?>
  </div>
</div>
