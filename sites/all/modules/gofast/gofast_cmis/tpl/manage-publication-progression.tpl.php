<?php $locations_a = array(); ?>

<div class="panel panel-default manage-publications-panel">
  <div class="panel-body">
    <span id="nid" style="display:none;"><?php echo $nid; ?></span>
    <?php echo t('Publication of', array(), array('context' => 'gofast:cmis')); ?> <strong id="title"><?php echo $title; ?></strong> : 
    <ul>
      <?php foreach($locations as $location){ ?>
        <li>
          <?php
            if(is_numeric($location)){
              echo gofast_cmis_space_get_webdav_path($location);
              $locations_a[] = gofast_cmis_space_get_webdav_path($location);
            }else{
              echo $location;
              $locations_a[] = $location;
            }
          ?>
        </li>
      <?php } ?>
    </ul>
    <div class="manage-publications-info" style="position: absolute; right: 100px; margin-top: -5px;"><i class='fa fa-clock-o' style='color:orange' aria-hidden='true'></i> <?php echo t('Pending...', array(), array('context' => 'gofast:cmis')) ?></div>
    <span id="locations" style="display:none"><?php echo json_encode($locations_a); ?></span>
    <span id="locations_nid" style="display:none"><?php echo json_encode($locations_nid); ?></span>
    <span id="transformation" style="display:none"><?php echo $transformation ?></span>
    <span id="is_broadcast" style="display:none"><?php echo (bool)$is_broadcast; ?></span>
  </div>
</div>