<?php
  $locations_a = array();
  $locations_gids = array();
?>

<div class="panel panel-default manage-locations-panel">
  <div class="panel-body">
    <span id="nid" style="display:none;"><?php echo $nid; ?></span>
    <?php echo t('Setting locations of', array(), array('context' => 'gofast:taxonomy')); ?> <strong><?php echo $title; ?></strong> : 
    <ul>
      <?php foreach($locations as $location){ ?>
        <li>
          <?php
            $is_article = isset($type) && $type == "article";
            if(is_numeric($location)){
              echo gofast_cmis_space_get_webdav_path($location);
              $locations_a[] = gofast_cmis_space_get_webdav_path($location);
              $locations_gids[] = $location;
            }else{
              echo $location;
              $locations_a[] = $location;
              $locations_gids[] = gofast_og_get_group_id_from_title($location, TRUE);
            }
            if ($is_article) {
              echo "/Wikis";
            }
          ?>
        </li>
      <?php } ?>
    </ul>
    <div class="manage-locations-info" style="position: absolute; right: 100px; margin-top: -5px;"><i class='fa fa-clock-o' style='color:orange' aria-hidden='true'></i> <?php echo t('Pending...', array(), array('context' => 'gofast:taxonomy')) ?></div>
    <span id="locations" style="display:none"><?php echo json_encode($locations_a); ?></span>
    <span id="locations-gids" style="display:none"><?php echo json_encode($locations_gids); ?></span>
    <span id="is_broadcast" style="display:none"><?php echo (bool)$is_broadcast; ?></span>
  </div>
</div>