<?php $detect = new Mobile_Detect(); 
  $isFull = "false";
  if(isset($node)){
    if($node->type == "alfresco_item" || $node->type == "webform"){
      $isFull = "true";
    }
  }
?>
<div id="nodeContainer" <?= "data-nid='{$node->nid}'" ?> class="gofast-content__node GofastNode <?= (isset($node) && $node->type == 'article') && gofast_essential_is_essential() ? 'articleContent' : '' ?> <?= gofast_essential_is_essential() && !gofast_mobile_is_phone() ? 'gofast-content__node__essential essential' : '' ?>" <?= gofast_essential_is_essential() ? 'data-isfullpage="'. $isFull .'"' : '' ?>>
    <?php if($user->field_atatus_tracking[LANGUAGE_NONE]['0']['value'] == 2) : ?>
        <script type="text/javascript">atatus.setTags(['content']);</script>
    <?php endif; ?>
    <div class="mainContent">
      <?php print $content; ?>
    </div>

  <?php if (gofast_essential_is_essential()) : ?>
    <div id="side-content-container" <?= !gofast_mobile_is_phone() ? "class='side-content-container-essential'" : ""; ?>>
        <div class="sideContent">
          <?php print $side_content; ?>
        </div>
    </div>
  <?php else : ?>
      <div class="sideContent">
        <?php print $side_content; ?>
      </div>
  <?php endif; ?>

  <?php if (gofast_mobile_is_phone()) : ?>
          <div id="side-content-toggle" class=""><i class="fas fa-chevron-left"></i></div>
  <?php endif; ?>
</div>