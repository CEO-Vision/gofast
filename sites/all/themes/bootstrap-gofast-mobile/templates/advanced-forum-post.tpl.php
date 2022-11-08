<?php
/**
  This file overrides forum-post of advanced-forum module (3rd module)
 */

    //Check if comment is private to apply the proper class
    if($comment->field_comment_is_private[LANGUAGE_NONE][0]['value']){
        $classes .= " gofast-comment-is-private";
    }

?>

<?php if($top_post): ?>

  <div id = "fullscreen-node">
<?php endif; ?>

<div id="<?php print $post_id; ?>" class="panel panel-default <?php print $classes; ?>" <?php print $attributes; ?>>
  <?php
    if($comment->field_comment_is_private[LANGUAGE_NONE][0]['value']){    
  ?>
        <span style="position: absolute;right: 120px;font-size: 1em;margin-top: 7px;color: #AAA;font-weight: bold;"><i class="fa fa-lock" style="color: red;"></i> <?php echo t("Private comment"); ?></span>
  <?php
    }
  ?>
        
  <div class="panel-heading">
    <div class="forum-posted-on">
      <?php print $date ?>

      <?php
      // This whole section is for printing the "new" marker. With core comment
      // we just need to check a variable. With Node Comment, we need to do
      // extra work to keep the views caching used for Node Comment from
      // caching the new markers.
      ?>
      <?php if (!$top_post): ?>
        <?php if (!empty($new)): ?>
          <a id="new"><span class="new">(<?php print $new ?>)</span></a>
        <?php endif; ?>

        <?php if (!empty($first_new)): ?>
          <?php print $first_new; ?>
        <?php endif; ?>

        <?php if (!empty($new_output)): ?>
          <?php print $new_output; ?>
        <?php endif; ?>
      <?php endif; ?>

      <?php /* End of posted on div. */ ?>

      <?php if (!empty($in_reply_to)): ?>
        <span class="forum-in-reply-to"><?php print $in_reply_to; ?></span>
      <?php endif; ?>

      <?php /* Add a note when a post is unpublished so it doesn't rely on theming. */ ?>
      <?php if (!$node->status): ?>
        <span class="unpublished-post-note"><?php print t("Unpublished post") ?></span>
      <?php endif; ?>

      <span class="forum-post-number"><?php print $permalink; ?></span>
    </div>

  </div> <?php /* End of post info div. */ ?>

  <div class="forum-post-wrapper row" style="margin-left: 0px; margin-right: 0px;">
    <div class="forum-post-panel-sub col-xs-4 col-sm-4">

      <?php
        if (!empty($author_pane)){
          print $author_pane;
        }
        ?>

    </div>

    <div class="forum-post-panel-main col-xs-8 col-sm-8">
      
     
      <?php
        if (($comment instanceof stdClass) && isset($comment->vud_comment_widget)) {
          $vud_widget = $comment->vud_comment_widget;
          print $vud_widget;
        } elseif (isset($content['vud_node_widget_display'])) {
          print $content['vud_node_widget_display']['#value'];
        }
      ?>
      
      
      <?php if (!empty($title)): ?>
        <div class="forum-post-title">
          <?php
            print $title;

          ?>
        </div>
      <?php endif; ?>

      <div class="forum-post-content">
        <?php
        hide($content['links']['print_html']);
        hide($content['links']['print_mail']);
        if (isset($content['body']) && isset($content['body']['#bundle']) && $content['body']['#bundle'] == "forum") {
          echo $content['body']['#items'][0]['value'];
        }
        elseif (isset($content['comment_body']) && isset($content['comment_body']['#bundle']) && $content['comment_body']['#bundle'] == "comment_node_forum") {
          echo $content['comment_body']['#items'][0]['value'];
        }
        ?>
      </div>

      <?php if (!empty($post_edited)): ?>
        <div class="post-edited">
          <?php print $post_edited ?>
        </div>
      <?php endif; ?>

      <?php if (!empty($signature)): ?>
        <div class="author-signature">
          <?php print $signature ?>
        </div>
      <?php endif; ?>
        
      
      
    </div>
    
  </div>
  <?php /* End of post wrapper div. */ ?>

  <div class="panel-footer">
    <div style="text-align:right;">
      <?php print render($content['links']); ?>
    </div>


  </div>
  <?php /* End of footer div. */ ?>
</div>
<?php /* End of main wrapping div. */ ?>
    
    
<div id="comments-container">
<div>
<?php //print render($content['comments']); 
    
    if (isset($content['comments']) && count($content['comments']) === 0) :
      print '<div id="forum-comments" class="comment-wrapper">';
    endif;

    print render($content['comments']);

    if (isset($content['comments']) && count($content['comments']) === 0) {
      print '</div>';
    }
    
    if(isset($must_load_remaining_comments)){       
        print "<script>jQuery(document).ready(function(){  setTimeout(function(){                                                
                                               Gofast.loadcomments(".$node->nid.");
                                              }, 2000);});</script>";
    }
    else{
          print "<script>jQuery(document).ready(function(){
                Gofast.checkReply();  });</script>";
        }
?>
    
</div>
</div>

<?php if ($top_post): ?>
  </div>
<?php endif; ?>
