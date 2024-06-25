<div class="card card-custom GofastForm__CardContainer">
    <div class="card-body">
        <div class="GofastForm__Field GofastForm__Field--title">
            <?php echo render($form['wrapper']['title']); ?>
        </div>
        <div class="GofastForm__Field GofastForm__Field--language">
            <?php echo render($form['wrapper']['language']); ?>
        </div>
        <div class="GofastForm__Field GofastForm__Field--content">
            <?php echo render($form['body']); ?>
        </div>
        <div class="GofastForm__Field GofastForm__Field--book">
            <?php echo render($form['page_selector']); ?>
        </div>
        <div class="GofastForm__Field GofastForm__Field--broadcast">
            <?php echo theme("gofast_book_tree_widget") ?>
            <?php if (isset($form['fieldset_broadcast_og'])) : ?>
                <?php echo render($form['fieldset_broadcast_og']); ?>
            <?php endif ?>
        </div>
    </div>
    <div class='card-footer pb-0 pt-3 d-flex GofastAddForms__buttons'>
        <?php echo render($form['actions']); ?>
        <?php drupal_process_attached($form); ?>
        <div class="d-none"><?php echo drupal_render_children($form); ?></div>
    </div>
</div>

<script>
    // we make 100% sure the ckeditor is correctly triggered
    Drupal.attachBehaviors();

    jQuery(document).ready(function() {
        <?php
            $target = FALSE;
            if(isset($form[GOFAST_CMIS_LOCATIONS_FIELD][LANGUAGE_NONE]['#value']) && !empty($form[GOFAST_CMIS_LOCATIONS_FIELD][LANGUAGE_NONE]['#value'])) {
                $target = $form[GOFAST_CMIS_LOCATIONS_FIELD][LANGUAGE_NONE]['#value'];
            }
            if (isset($_GET['target_location']) && !empty($_GET['target_location'])) {
                $target = gofast_xss_clean($_GET['target_location']);
            }
            if ($target) :
        ?>
            const fakeEvent = {};
            fakeEvent.preventDefault = () => {};
            fakeEvent.currentTarget = "tr[data-nid='" + <?= $target ?> + "']";
            Gofast.book.treeWidgetItemCallback(fakeEvent);
        <?php endif; ?>
    });
</script>