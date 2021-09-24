<?php

$detect = new Mobile_Detect;

print '<span class="xeditable_field_wrapper field-' . $xeditable_vars['name'] . ' ' . implode(' ', $xeditable_vars['wrapper_class']) . '" >';
print '<a class="xeditable-field" href="#" ';
foreach ($xeditable_vars as $key => $value) {
    if ($key === 'wrapper_class' || $key === 'default' || count($value) === 0 || $key === 'link_value') {
        continue;
    }
    if(is_array($value) ) {
        $value = htmlspecialchars(json_encode($value), ENT_QUOTES);
    }

    if ($xeditable_vars['type'] == 'textarea'){
      $value = htmlspecialchars($value, ENT_QUOTES);
    }

    print 'data-' . $key . '="' . $value . '" ';
}
$link_default_value = isset($xeditable_vars['link_value']) ? $xeditable_vars['link_value'] : '';
print '>'.$link_default_value.'</a>';
if($xeditable_vars['delegated'] == 'true') {
  print '<span class="xeditable-values"></span>';
  if($xeditable_vars['name'] !='body' && !in_array('manual_ckeditor' ,$xeditable_vars['wrapper_class']) ){
    if(gofast_mobile_is_mobile_domain() && ($detect->isMobile() || $detect->isTablet())){
      print '<span class="xeditable-trigger btn btn-xs btn-default" alt="' . t('Edit', array(), array('context' => 'gofast')) . '"><span class="fa fa-pencil" ></span></span>';
    }else{
      print '<span class="xeditable-trigger btn btn-xs btn-primary" alt="' . t('Edit', array(), array('context' => 'gofast')) . '"><span class="fa fa-pencil"></span> ' . t('Edit', array(), array('context' => 'gofast')) . '</span>';
    }
  }
}
print '</span>';
