<?php

//Check if comment is private to apply the proper class
if ($item['is_private']) {
    $classes .= " gofast-comment-is-private";
}
?>

<div class="timeline-item pl-8" id="<?php echo "comment-". $item['comment_id'] ?>">
    <div class="timeline-media border-0">
        <?php print theme('user_picture', array('account' => user_load($item['creator_id']),'popup' => TRUE, 'dimensions' => 40)); ?>
    </div>
    <div class="timeline-label d-flex justify-content-between align-items-center px-0">
        <span class="text-muted "><?= format_date(strtotime(($item['edited_date'] != $item['creation_date']) ? $item['edited_date'] : $item['creation_date'] ), "medium") ?></span>
    </div>
    <div class="timeline-content d-flex flex-column">
        <div class="w-100 d-flex justify-content-between">
            <!-- BEGIN LOCK PRIVATE--->
            <?php if ($item['is_private']) {  ?>
            <div class="p-2">
                    <span class="text-muted mr-3"> <i class="fa fa-lock" style="color: red;"></i> <?php echo t("Private comment"); ?> </span>
            </div>
            <?php  } ?>
            <!-- END LOCK PRIVATE --->

            <!-- BEGIN EDITED BY --->
            <?php if (isset($item['edit_user'])) { ?>
                <div class="p-2">
                    <span class="text-muted mr-3"><?php print t("Edited by") ?> :</span>
                    <div class="symbol symbol-20 mr-3">
                        <img title="<?php echo $item['edit_user']["name"] ?>" alt="Pic" src="<?php print $item['edit_user']['picture'] ?>" />
                    </div>
                    <a href="<?php print $item['edit_user']["link"] ?>" class="text-dark text-hover-primary"><?php print $item['edit_user']["name"] ?></a>
                </div>
            <?php  }  ?>
            <!-- END EDITED BY --->
        </div>

        <!-- BEGIN TITLE --->
        <?php if (!empty($item['title'])) : ?>
            <div class="timeline-content__header w-100 mt-2">
                <span class="font-size-h4">
                    <?php print $item['title']; ?>
                </span>
            </div>
        <?php endif; ?>
        <!-- END TITLE --->

        <!-- BEGIN TEXT BODY --->
        <div class="timeline-content__body mt-2">
            <?php
            print $item['text'];
            ?>
        </div>
        <!-- END TEXT BODY --->

    </div>
    <div class="timeline-toolbar d-flex justify-content-between pt-2">

        <!-- BEGIN LIKE/DISLIKE --->
        <div class="comment__likes d-flex">
            <?php
            if (isset($item['vud_comment_widget'])) {
                print $item['vud_comment_widget'];
            }
            ?>
        </div>
        <!-- END LIKE/DISLIKE --->

        <!-- BEGIN LINKS --->
        <div class="comment__actions align-self-center">
        <?php print render($item['links']); ?>
        </div>
        <!-- END TEXT LINKS --->
    </div>

    <?php if ($item['child_comments']) : ?>
        <?php echo theme('gofast_comment_container', ['comments' => $item['child_comments'], 'first_level_comments' => FALSE]) ?>
    <?php endif ?>

</div>
