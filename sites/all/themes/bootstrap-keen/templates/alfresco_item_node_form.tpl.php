<div class="card card-custom GofastForm__CardContainer">
  <?php if (isset($_GET["field_target_link"])) : ?>
    <?php $target_node = node_load($_GET["field_target_link"]); ?>
    <div class="alert alert-custom alert-notice alert-light-warning fade show m-4" role="alert">
      <div class="alert-icon"><i class="flaticon-warning"></i></div>
      <div class="alert-text"><?php echo t("You are currently creating a response to the mail '@title'", array('@title' => $target_node->title), array('context' => 'gofast')); ?></div>
      <div class="alert-close">
        <button type="button" class="close" data-dismiss="alert" aria-label="Close">
          <span aria-hidden="true"><i class="ki ki-close"></i></span>
        </button>
      </div>
    </div>
  <?php endif; ?>
  <?php if (isset($_GET["translation"])) { $target_node = node_load($_GET["translation"]); } ?>
  <div class="card-body <?= $_POST["from_modal"] ? "p-0" : "" ?>">
    <div class="GofastForm__Field GofastForm__Field--title">
      <?php echo render($form['wrapper']['title']); ?>
    </div>
    <div class="GofastForm__Field GofastForm__Field--extension">
      <?php echo render($form['wrapper']['extension']); ?>
    </div>
    <div class="GofastForm__Field GofastForm__Field--language">
      <?php echo render($form['wrapper']['language']); ?>
    </div>
    <div class="GofastForm__Field GofastForm__Field--file">
      <?php if (isset($form['group_vertical_tab_input_file']['group_remote_url']['remote_url'])) : ?>
        <label for="createFromURL"><?php echo t('Create from URL *', array('context' => 'gofast:gofast_cmis')); ?></label>
        <?php echo render($form['group_vertical_tab_input_file']['group_remote_url']['remote_url']); ?>
      <?php else : ?>
        <?php
          $activeTab = "downloadFile";
          if(isset($_GET["hash"])){
           $activeTab = gofast_xss_clean($_GET["hash"]);
          }
        ?>
        <ul class="nav nav-tabs" id="alfresco_item_tab" role="tablist">
          <li class="nav-item">
            <a class="nav-link <?= $activeTab == "downloadFile" ? "active" : "" ?>" id="download_file" data-toggle="tab" href="#downloadFile" aria-controls="downloadFile">
              <span class="nav-text"><?php echo t('Upload a file', array('context' => 'gofast:gofast_cmis')); ?></span>
            </a>
          </li>
          <li class="nav-item">
            <a class="nav-link <?= $activeTab == "createFromTemplate" ? "active" : "" ?>" id="create_from_template" data-toggle="tab" href="#createFromTemplate" aria-controls="createFromTemplate">
              <span class="nav-text"><?php echo t('Create from template', array('context' => 'gofast:gofast_cmis')); ?></span>
            </a>
          </li>
          <li class="nav-item">
            <a class="nav-link <?= $activeTab == "createAnEmptyFile" ? "active" : "" ?>" id="create_an_empty_file" data-toggle="tab" href="#createAnEmptyFile" aria-controls="createAnEmptyFile">
              <span class="nav-text"><?php echo t('Create an empty file', array('context' => 'gofast:gofast_cmis')); ?></span>
            </a>
          </li>
        </ul>
        <div class="tab-content p-4" id="alfresco_item_tabContent">
          <div class="tab-pane fade <?= $activeTab == "downloadFile" ? "active show" : "" ?>" id="downloadFile" role="tabpanel" aria-labelledby="download_file"><?php echo render($form['group_vertical_tab_input_file']['group_upload_file']['reference']); ?></div>
          <div class="tab-pane fade <?= $activeTab == "createFromTemplate" ? "active show" : "" ?>" id="createFromTemplate" role="tabpanel" aria-labelledby="create_from_template">
            <?= theme("gofast_cmis_template_widget", array("available_templates" => $form["#templates_infos"])) ?>
            <?= render($form['group_vertical_tab_input_file']['group_template_file']['templates']) ?>
          </div>
          <div class="tab-pane fade <?= $activeTab == "createAnEmptyFile" ? "active show" : "" ?>" id="createAnEmptyFile" role="tabpanel" aria-labelledby="create_an_empty_file"><?php echo render($form['group_vertical_tab_input_file']['group_empty_file']['empty_template']); ?></div>
        </div>
      <?php endif ?>
    </div>
    <div class="GofastForm__Field GofastForm__Field--broadcast">
      <?php echo render($form['og_group_content_ref']); ?>
      <?php if (isset($form['fieldset_broadcast_og'])) : ?>
        <div>
          <?php echo render($form['fieldset_broadcast_og']); ?>
        </div>
      <?php endif ?>
    </div>
    <div class="spinner d-none"></div>
  </div>
  <div class='card-footer pb-0 pt-3 d-flex w-100 GofastAddForms__buttons'>
    <?php echo render($form['actions']); ?>
    <?php drupal_process_attached($form); ?>
    <div class="d-none"><?php echo drupal_render_children($form); ?></div>
  </div>
</div>

<style>
  /* Applied only when the form is displayed in a modal */
  #modal-content {
    overflow: hidden !important;
  }
</style>

<script>
  if (window.location.hash == '#createFromTemplate') {
    jQuery('#create_from_template').click();
  }

  jQuery(document).ready(function() {
    window.initFileInput();

    const interval = setInterval(function() {
      if (!jQuery("#ztree_component_content > li").length) {
        return;
      }
      clearInterval(interval);

      let node = <?= json_encode($target_node); ?>;
      if (!node) {
        return;
      }
      Gofast.expandTargetLinkNode(node.field_main_emplacement.und[0].value, true);
    }, 100);
  });
</script>