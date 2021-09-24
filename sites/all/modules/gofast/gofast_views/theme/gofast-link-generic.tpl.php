<?php
print '<a ';

print 'class="center-block sidebar-items ' . $link_class . '" '
  . 'id="' . $link_id . '" '
  . (isset($href) ? 'href="' . $href . '" ' : '')
  . (isset($disabled) ? 'disabled="disabled" ' : '')
  . (isset($onClick) ? 'onClick="' . $onClick . '" ' : '')
  . (isset($alt) ? 'alt="' . $alt . '" ' : '')
  . (isset($target) ? 'target="' . $target . '" ' : '')
  . (isset($title) ? 'title="' . $title . '" ' : '')
  . '>';

print '<div class="list-items-icons"><i class="' . $icon_class . '"></i></div>'
  . '<p style="text-overflow: ellipsis; overflow: hidden;">' . (isset($text) ? $text : '') . '</p>';
print '</a>';
