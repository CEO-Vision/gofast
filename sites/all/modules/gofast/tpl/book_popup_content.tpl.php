<!-- 
Popup content
-->

<?php
$callback = isset($popup_variables['js_callback']) && $popup_variables['js_callback'] !== NULL ? 'data-jscallback="' . $popup_variables['js_callback'] . '" ' : '';
print '<span id="' . $popup_variables['container_id'] . '" class="' . $popup_variables['container_class'] . '">';
if (isset($popup_variables['delegated']) && $popup_variables['delegated'] == 'true') {
  print '<div '
          .  'class = "xeditable-trigger-1" '
          . 'data-trigger="manual" '
          . 'data-container="body" '
          . 'data-html="true" '
          . 'data-toggle="popover" '
          . 'data-context="' . $popup_variables['context'] . '" '
          . 'data-placement="' . $popup_variables['placement'] . '" '
          . $callback
          . 'title="' . $popup_variables['title'] . '" '
          . 'data-content="' . $popup_variables['content'] . '">
      </div>';
  print '<span class="xeditable-values">'.$popup_variables['link_text'].'</span>';
  print '<span class="xeditable-trigger btn btn-xs btn-primary" alt="' . t('Edit', array(), array('context' => 'gofast')) . '"><span class="glyphicon glyphicon-pencil" ></span> ' . t('Edit', array(), array('context' => 'gofast')) . '</span>';
} else {
  if ($popup_variables['type'] === 'button') {
    print '<button '
            . 'type="button" '
            . 'class="btn btn-default ' . $popup_variables['link_class'] . '" '
            . 'data-container="body" '
            . 'data-html="true" '
            . 'data-toggle="popover" '
            . 'data-context="' . $popup_variables['context'] . '" '
            . 'data-placement="' . $popup_variables['placement'] . '" '
            . $callback
            . 'title="' . $popup_variables['title'] . '" '
            . 'data-content="' . $popup_variables['content'] . '">
    ' . $popup_variables['link_text'] . '
  </button>';
  } else {
    print '<a href="#"'
            . 'class="' . $popup_variables['link_class'] . '" '
            . 'data-container="body" '
            . 'data-html="true" '
            . 'data-toggle="popover" '
            . 'data-context="' . $popup_variables['context'] . '" '
            . 'data-placement="' . $popup_variables['placement'] . '" '
            . $callback
            . 'title="' . $popup_variables['title'] . '" '
            . 'data-content="' . $popup_variables['content'] . '">
    ' . $popup_variables['link_text'] . '
  </a>';
  }
}
print '</span>';
