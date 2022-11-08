<?php 
  $field_display = "";
  switch($field){
    case 'language':
      $field_display = t("the language", array(), array('context' => 'gofast:taxonomy'));
      break;
    case 'field_state':
      $field_display = t("the state", array(), array('context' => 'gofast:taxonomy'));
      break;
    case 'field_category':
      $field_display = t("the category", array(), array('context' => 'gofast:taxonomy'));
      break;
    case 'field_tags':
      $field_display = t("the tags", array(), array('context' => 'gofast:taxonomy'));
      break;
    case 'field_date':
      $field_display = t("the deadline", array(), array('context' => 'gofast:taxonomy'));
      break;
    case 'field_criticity':
      $field_display = t("the criticity", array(), array('context' => 'gofast:taxonomy'));
      break;
  }
?>

<div class="panel panel-default manage-locations-panel">
  <div class="panel-body">
    <?php echo t('Setting', array(), array('context' => 'gofast:taxonomy')); ?> <?php echo $field_display ?> <?php echo t('of', array(), array('context' => 'gofast:taxonomy')); ?> <strong><?php echo $title; ?></strong> <?php echo t('to', array(), array('context' => 'gofast:taxonomy')); ?> : 
    <?php
      if($field == 'field_tags'){
    ?>
      <ul>
    <?php
      foreach($value as $tag){
        print "<li>";
        print taxonomy_term_load($tag['tid'])->name;
        print "</li>";
        $tags[] = $tag['tid'];
      }
    ?>
      </ul>
    <span id="value" style="display:none"><?php echo implode(",", $tags); ?></span>
    <?php
      }else if($field == 'language' || $field == 'field_date'){
        print $value;
    ?>
      <span id="value" style="display:none"><?php echo $value ?></span>
    <?php
      }else{
        print taxonomy_term_load($value)->name;
      ?>
        <span id="value" style="display:none"><?php echo $value ?></span>
      <?php
      }
    ?>
    <div class="manage-locations-info" style="position: absolute; right: 100px; margin-top: -1.5rem;"><i class='fa fa-clock-o' style='color:orange' aria-hidden='true'></i> <?php echo t('Pending...', array(), array('context' => 'gofast')) ?></div>
    <span id="nid" style="display:none"><?php echo $nid; ?></span>
    <span id="vid" style="display:none"><?php echo $vid; ?></span>
    <span id="field" style="display:none"><?php echo $field; ?></span>
  </div>
</div>