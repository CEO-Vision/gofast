<div class="timeline timeline-justified timeline-3">
    <div class="timeline-bar"></div>
    <div class="timeline-items">
        <?php if ($first_level_comments === TRUE): ?>
        <div class="d-flex w-100 mb-4 gofastAddComment">
            <a href="/gofast/nojs/comment/reply/<?php echo $nid; ?>" class="w-100 text-muted ctools-use-modal"> <?php echo t('Click here to add a new comment ...', array(), array('context' =>  'gofast')) ?></a>
        </div>
        <?php endif; ?>
        <?php if (empty($comments)) : ?>
            <div class="alert alert-custom alert-notice alert-light-info fade show" role="alert">
                <div class="alert-icon"><i class="flaticon-information"></i></div>
                <div class="alert-text"><?= t("No comment was found for this document") ?></div>
            </div>
        <?php else : ?>
            <?php foreach ($comments as $comment) : ?>
                <?php echo theme('gofast_comment_item', ['item' => $comment]) ?>
            <?php endforeach ?>
        <?php endif ?>
    </div>
</div>
