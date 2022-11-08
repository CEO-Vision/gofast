<?php

/**
 This file overrides comment layout of comment module (core module)
 */

//Check if comment is private to apply the proper class
if ($comment->field_comment_is_private[LANGUAGE_NONE][0]['value']) {
  $classes .= " gofast-comment-is-private";
}
?>

<div class="timeline timeline-justified timeline-3 mt-4">
  <div class="timeline-bar"> </div>
  <div class="timeline-items">
    <div class="timeline-item pl-10">
      <div class="timeline-media border-0">
        <img class="w-35px" alt="Pic" src="<?php echo $content['comment_body']['#user_picture'] ?>">
      </div>
      <div class="timeline-label d-flex justify-content-between align-items-center px-0">
        <span class="text-muted "><?php print $date; ?></span>
      </div>
      <div class="timeline-content d-flex flex-column">
        <div class="w-100 d-flex justify-content-between">
          <!-- BEGIN LOCK PRIVATE--->
          <div class="p-2">
            <?php if ($comment->field_comment_is_private[LANGUAGE_NONE][0]['value']) {  ?>
              <span class="text-muted mr-3"> <i class="fa fa-lock" style="color: red;"></i> <?php echo t("Private comment"); ?> </span>
            <?php  } ?>
          </div>
          <!-- END LOCK PRIVATE --->

          <!-- BEGIN EDITED BY --->
          <?php if (isset($comment->edit_user)) { ?>
            <div class="p-2">
              <span class="text-muted mr-3"><?php print t("Edited by") ?> :</span>
              <div class="symbol symbol-20 mr-3">
                <img alt="Pic" src="<?php print $comment->edit_user->user_picture ?>" />
              </div>
              <a href="<?php print '/user/' . $comment->edit_user->uid ?>" class="text-dark text-hover-primary"><?php print gofast_user_display_name($comment->edit_user) ?></a>
            </div>
          <?php  }  ?>
          <!-- END EDITED BY --->
        </div>

        <!-- BEGIN TITLE --->
        <?php if (!empty($title)) : ?>
          <div class="timeline-content__header w-100 mt-2">
            <span class="font-size-h4">
              <?php print $title; ?>
            </span>
          </div>
        <?php endif; ?>
        <!-- END TITLE --->

        <!-- BEGIN TEXT BODY --->
        <div class="timeline-content__body mt-4">
          <?php
          hide($content['links']['print_html']);
          hide($content['links']['print_mail']);
          print $content['comment_body']['#items'][0]['value'];
          ?>
        </div>
        <!-- END TEXT BODY --->

      </div>
      <div class="timeline-toolbar d-flex justify-content-between pt-2">

        <!-- BEGIN LIKE/DISLIKE --->
        <div class="comment__likes d-flex">
          <?php
          if (($comment instanceof stdClass) && isset($comment->vud_comment_widget)) {
            $vud_widget = $comment->vud_comment_widget;
            print $vud_widget;
          }
          ?>
        </div>
        <!-- END LIKE/DISLIKE --->

        <!-- BEGIN LINKS --->
        <div class="comment__actions">
          <?php print render($content['links']); ?>
        </div>
        <!-- END TEXT LINKS --->
      </div>
    </div>
  </div>
</div>
</div>
<?php /* End of main wrapping div. */ ?>
<div class="timeline timeline-justified timeline-3 mt-4">
  <div class="timeline-bar"></div>
  <div class="timeline-items">
    <?php
    if (isset($content['child_comments'])) {
      foreach ($content['child_comments'] as $child) {
        print render($child);
      }
    }
    ?>
  </div>
</div>
</div>
