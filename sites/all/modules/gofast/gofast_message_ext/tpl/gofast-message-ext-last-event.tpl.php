  <span><?php print $output_prepare; ?></span>
<?php if(isset($edit)){ ?>
  <div class="glyphicon glyphicon-search" onmouseover="displayLastEvent(this)" onmouseout="hideLastEvent(this)"></div>

<div style='position: relative; z-index:100; margin-top:2px; display:none;' onmouseover="display(this)" onmouseout="hide(this)">
  <div style='top: -5px; left:0; background-color: #F8F8F8; position: absolute; min-width: 500px;'>
    <?php print $edit; ?>
  </div>
</div>
<?php }else{ ?>
</div>
<?php }