<!-- Content -->
  <div class="row">
    <div class="col-lg-9" style="background-color: #f7f7f7;">
      <div class="img-container card-body" id="img-cropper" style="max-width: 95%;">
        <img id="image" src="<?php print isset($logo) ? file_create_url($logo) . '?rand='. rand(1, 1000)  : $base_url . '/sites/all/themes/bootstrap-keen/logo.png' ?>" />
      </div>
      <?= theme("gofast_cropper_buttons", array("id_attribute" => "gid='$gid'")) ?>
    </div>
    <div class="col-lg-3" id="gofast_crop_og_logo">
      <h5 class="text-muted mb-3"><?= t("Cropped image") ?></h5>
      <div class="cropper-preview clearfix mb-3">
        <div id="cropper-preview-lg" class="symbol symbol-100 img-preview preview-lg img-fluid mb-3" style="width: 100px; height: 100px; overflow: hidden; background-color: #f7f7f7;"><canvas width="100" height="100"></canvas></div>
      </div>
    </div>
  </div>
