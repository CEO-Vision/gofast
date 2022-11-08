<?php
print '<a ';

print 'class="' . $link_class . '" '
  . 'id="' . $link_id . '" '
  . (isset($href) ? 'href="' . $href . '" ' : '')
  . (isset($disabled) ? 'disabled="disabled" ' : '')
  . (isset($onClick) ? 'onClick="' . $onClick . '" ' : '')
  . (isset($alt) ? 'alt="' . $alt . '" ' : '')
  . (isset($target) ? 'target="' . $target . '" ' : '')
  . (isset($title) ? 'title="' . $title . '" ' : '')
  . 'data-toggle="modal"'
  . (isset($datatarget) ? 'data-target="' . $datatarget .'" ' : '')
  . '>';

print '<div class="list-items-icons"><i class="' . $icon_class . '"></i></div>'
  . '<p>' . (isset($text) ? $text : '') . '</p>';

print '</a>';
