  <?php if ($flag == TRUE) : ?>
    <span class="flag-wrapper">
  <?php endif; ?>
  <?php if(!empty($text)):  ?> 
    <?php
    print '<a ';

    print 'class="navi-link ' . $link_class .' '. (!empty($disabled) ? "disabled" : "").'" '
      . 'id="' . $link_id . '" '
      . (isset($href) ? 'href="' . $href . '" ' : '')
      . (isset($onClick) ? 'onClick="' . $onClick . '" ' : '')
      . (isset($alt) ? 'alt="' . $alt . '" ' : '')
      . (isset($target) ? 'target="' . $target . '" ' : '')
      . (isset($title) ? 'title="' . $title . '" ' : '')
      . '>';
    
    if($svg){
      print '<span class="navi-icon"><img class="' . $icon_class . '" src="' . $svg . '" /></span>' . '<span class="navi-text">' . (isset($text) ? $text : '') . '</span>';
    }else{
      print '<span class="navi-icon"><i class="' . $icon_class . '"></i></span>' . '<span class="navi-text">' . (isset($text) ? $text : '') . '</span>';
    }
    
    print '</a>';
    ?>
    <?php endif; ?>
  <?php if ($flag == TRUE) : ?>
    </span>
  <?php endif; ?>
  <?php if($divider): ?>
    <li class='navi-separator my-3'></li>
  <?php endif; ?>
