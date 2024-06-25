<div id="gofast-node-info-basic">
  <div class="row font-size-sm gofast_metadata_infotab" id="document__infotab">
    <?php
      $extra_metadata_types = gofast_metadata_get_extra_metadata_types();
      foreach ($extra_infos as $key => $info) {
        $type = $info["type"];
        if (in_array($type, array_keys($extra_metadata_types))) {
          $has_wrapper = $extra_metadata_types[$type]["has_wrapper"];
          if ($has_wrapper) {
            echo theme("gofast_node_extra_metadata_wrapper", ["before" => TRUE, "info" => $info]);
          }
          echo theme("gofast_node_extra_metadata_{$type}", ["info" => $info]);
          if ($has_wrapper) {
            echo theme("gofast_node_extra_metadata_wrapper", ["after" => TRUE, "info" => $info]);
          }
        } else { ?>
          <div class="alert alert-custom alert-light-warning fade show mb-5" role="alert">
            <div class="alert-text"><?= t("The %theme theme was not found.", ["%theme" => "gofast_node_extra_metadata_{$info["type"]}"]) ?></div>
          </div>
        <?php }
    } ?>
  </div>
</div>
