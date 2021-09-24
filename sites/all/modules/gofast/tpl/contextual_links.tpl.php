<div id="<?php print $btn_group_id; ?>" class="contextual-actions btn-group btn-group-xs" role="group" aria-label="contextual actions">
  <?php
  foreach ($buttons as $button) {
    if (isset($button['children'])) {
      // Dropdown button, children may already be themed items (see views)
      $buttonText = isset($button['button-text']) ? $button['button-text'] : '';
      $classes = isset($button['classes']) ? implode(" ", $button['classes']) : '';
      print '<button '
              . 'class="btn btn-default dropdown-toggle ' . $classes . '" '
              . 'type="button" '
              . 'id="dropdown-' . $button['id'] . '" '
              . 'data-toggle="dropdown" '
              . 'aria-haspopup="true" '
              . 'aria-expanded="true" '
              . 'title="' . t($button['title'], array(), array('context' => 'gofast:gofast_workflows')) . '">
            <i class="' . $button['icon-class'] . '" aria-hidden="true"></i>
              ' . $buttonText . '
            </button>';
      print '<ul class="dropdown-menu dropdown-menu-right gofast-dropdown-menu" aria-labelledby="dropdown-' . $button['id'] . '">';
      foreach ($button['children'] as $menu_entry) {
 
          if($menu_entry['children']){
              print '<li class="collapsed dropdown-submenu">'.$menu_entry['themed'];
              if(count($menu_entry['children']) < 15){
                  print '<ul class="dropdown-menu dropdown-menu-right gofast-dropdown-menu" aria-labelledby="dropdown-' . $button['id'] . '" style ="bottom:-100px;top:inherit;min-width:200px;">';
              }else{
                  print '<ul class="dropdown-menu dropdown-menu-right gofast-dropdown-menu" aria-labelledby="dropdown-' . $button['id'] . '" style ="bottom:-150px;top:inherit;min-width:200px;">';
              }
              foreach ($menu_entry['children'] as $child) {
                print '<li>'.$child['themed'].'</li>'; 
              }
              print '</ul>';
              print '</li>';
          }else{
            print '<li>'.$menu_entry['themed'].'</li>';
          }
      }
      print '</ul>';
    }
    else {
      // Simple button
      $buttonText = isset($button['button-text']) ? $button['button-text'] : '';
      $classes = isset($button['classes']) ? implode(" ", $button['classes']) : '';
      
      if(isset($button['href'])){
        print '<a ';
      } else {
        print '<button ';
      }
      
      print 'class="btn btn-default ' . $classes . '" '
              . 'type="button" '
              . 'id="' . $button['id'] . '" '
              . (isset($button['href']) ? 'href="' . $button['href'] . '" ' : '')
              . (isset($button['disabled']) ? 'disabled="disabled" ' : '')
              . (isset($button['onClick']) ? 'onClick="' . $button['onClick'] . '" ' : '')
              . (isset($button['alt']) ? 'alt="' . $button['alt'] . '" ' : '')
            . (isset($button['target']) ? 'target="' . $button['target'] . '" ' : '')
              . 'title="' . t($button['title'], array(), array('context' => 'gofast:gofast_workflows')) . '">
              ' . (isset($button['avatar']) ?  $button['avatar'] : '') . '
              <i class="' . $button['icon-class'] . '" aria-hidden="true"></i>
              ' . $buttonText;
      if(isset($button['href'])){
        print '</a>';
      } else {
        print '</button>';
    }
  }
  }
  ?>
</div>