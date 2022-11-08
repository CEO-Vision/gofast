<?php if (isset($title)): ?>
<div class="field field-label-inline clearfix field-<?php print strtolower(str_replace("_", "-", $title)); ?>">
      <div class="field-label"><?php print $title !== '' ? t($title, array(), array('context' => 'gofast')) . ':&nbsp;' : ''; ?></div>
      <div class="field-item even">
          <?php
          if (null !== $values) {
            if (is_array($values)) {
              print '<div class="field-items">';
              print isset($title_suffix_html) ? $title_suffix_html : ''; 
              foreach ($values as $value) {
                print '<div class="field-item even">' . $value . '</div>';
              }
              print '</div>';
            }
            else {
              $multiline_class = isset($multiline) ? ' multiline' : '';
              print '<div class="field-item'.$multiline_class.'">';
               print isset($title_suffix_html) ? $title_suffix_html : ''; 
              if($seemore){
                $rand = rand(0, 999999);
                print '<button id="mobile-see-more" type="button" class="btn btn-default mobile-see-more-'.$rand.'" onclick="showMore(\''.$rand.'\')"><i class="fa fa-search-plus" aria-hidden="true"></i></button>';
              }
              if(isset($multiline)) {
                print '<br />';
              }
              if($seemore){
                print '<div id="value-'.$rand.'" class="mobile-hidden gofast_display_none">';
              }
              print $values;
              if($seemore){
                print '</div>';
              }
              print '</div>';
            }
          }
          else {
            print '<div class="field-item">'.t('None', array(), array('context' => 'gofast')) . '</div>';
          }
          ?>
      </div>
  </div>
<?php endif;
$script = "function showMore(rand){
  if(jQuery('#value-' + rand).hasClass('gofast_display_none')){
    jQuery('#value-' + rand).removeClass('gofast_display_none');
    jQuery('.mobile-see-more-' + rand).find('i').removeClass('fa-search-plus').addClass('fa-search-minus');
  }else{
    jQuery('#value-' + rand).addClass('gofast_display_none');
    jQuery('.mobile-see-more-' + rand).find('i').removeClass('fa-search-minus').addClass('fa-search-plus');
  }
}";
drupal_add_js($script, "inline");
?>