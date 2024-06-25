<?php if (isset($node_infos['node_external_page_url']["span_value"]) && $node_infos['node_external_page_url']["span_value"] != t('None')) : ?>
<div class="w-100 btn btn-hover-light btn-sm px-3 pb-4 document__editable--label justify-content-start external-links-list-container">
  <ul class="p-0 m-0 list-unstyled external-links-list">
    <?php foreach ($node_infos['node_external_page_url']['linksValues'] as $link) : ?>
      <?= theme("gofast_metadata_external_links_tag", array("link" => $link)); ?>
    <?php endforeach ?>
  </ul>
</div>
<?php else : ?>
<div class="w-100 btn btn-hover-light btn-sm p-2 document__editable--label text-truncate external-links-list-container"><?php echo $node_infos['node_external_page_url']['span_value'] ?></div>
<?php endif ?>
<div class="document__editable--divfiel document__editable--tags w-100 document__editable--select document__editable--selectExternalLink d-none">
  <select class="form-control form-control-sm document__editable--processe external-links" multiple="multiple" name="<?php print $node_infos['node_external_page_url']["name"] ?>" data-id="<?php print $node_infos['node_external_page_url']["node_pk"]  ?>">
    <?php foreach ($node_infos['node_external_page_url']['linksValues'] as $external_link) : ?>
      <option value="<?php echo $external_link["url"] ?>" selected="selected"><?php echo $external_link["url"] ?></option>
    <?php endforeach ?>
  </select>
</div>