<div class="d-flex flex-wrap">
  <div class="d-flex font-size-sm">
    <span class="font-weight-bolder mb-4 pt-2"><?php echo t('Tags') ?>:</span>
    <div class="pl-4 w-100">
      <?php if (isset($node_infos['node_keywords_info']["node_keywords_pk"])): ?>
        <div class="go-lien-listgroup bg-hover-light rounded"id="tags-list-ac">
          <input class="js-tagify metadata-node border-0" placeholder="<?= t("Try to add tags from the list", array(), array("context" => "gofast;gofast_metadata")) ?>"  data-taxonomy_term="" data-enforce="" data-vid="<?php print $node_infos['node_keywords_info']['node_keywords_vid'] ?>" data-pk="<?php print $node_infos['node_keywords_info']['node_keywords_pk'] ?>" type="text" id="edit-field-keywords" data-name="field_tags" name="ac-list-tags-keywords"  size="60" maxlength="">
          <input class="gofast_display_none" type="text" id="edit-actagify-ac-list-tags-keywords" name="gofast_tagify_ac" value='<?php print str_replace("'", "`", $node_infos['node_keywords_info']['json_tags']) ?>' size="60" maxlength="128">
        </div>
      <?php else: ?>
        <tags class="tagify metadata-node-disable w-100 border-0" tabindex="-1">
          <?php if (!empty($node_infos['node_keywords_info']['array_tags']) && $node_infos['node_keywords_info']['array_tags'] != null): ?>
            <?php foreach ($node_infos['node_keywords_info']['array_tags'] as $array_tag) : ?>
              <tag title="<?php echo $array_tag['name'] ?>" class="tagify__tag undefined tagify--noAnim" editable="false">
                <div>
                  <span class="tagify__tag-text"><?php echo $array_tag['name'] ?></span>
                  <?php print $array_tag['flag_html'] ?>
                </div>
              </tag>
            <?php endforeach ?>
          <?php  else: ?>
            <div class="p-2" id=""><?php echo t('None') ?></div>
          <?php endif ?>
        </tags>
      <?php endif ?>
    </div>
  </div>
</div>
