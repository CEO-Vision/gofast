<?php $locations_a = array(); ?>

<div class="panel panel-default manage-folders-locations-panel">
  <div class="panel-body">
    <span id="folder" style="display:none;"><?php echo $folder; ?></span>
    <?php echo t('Setting locations of', array(), array('context' => 'gofast:taxonomy')); ?> <strong><?php echo $title; ?></strong> :
    <ul>
      <?php foreach ($locations as $location) { ?>
        <?php if($location != "/Sites"){ ?>
          <li>
            <?php
            if (is_numeric($location)) {
            echo gofast_cmis_space_get_webdav_path($location);
            $locations_a[] = gofast_cmis_space_get_webdav_path($location);
          } else {
            echo $location;
            $locations_a[] = $location;
          }
              ?>
          </li>
        <?php } ?>
      <?php } ?>
    </ul>
    <div class="manage-folders-locations-info" style="position: absolute; right: 100px; margin-top: -5px;"><i class='fa fa-clock-o' style='color:orange' aria-hidden='true'></i> <?php echo t('Pending...', array(), array('context' => 'gofast:taxonomy')) ?></div>
    <span id="locations" style="display:none"><?php echo json_encode($locations_a); ?></span>
    <span id="is_broadcast" style="display:none"><?php echo (bool)$is_broadcast; ?></span>
  </div>
</div>
