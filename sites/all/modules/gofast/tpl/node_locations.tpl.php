<?php
print '<span id="' . $node_locations_options['container_id'] . '" class="' . $node_locations_options['container_class'] . '">';
    // empty div to display the "Edit" button
    print '<div '
          .  'class = "xeditable-trigger-1">'
     . ' </div>';
    print '<span class="xeditable-values">'.$node_locations_options['link_text'].'</span>';
    print '<a class="xeditable-trigger btn btn-xs btn-primary ctools-use-modal" id="manage-locations" alt="' . t('Edit', array(), array('context' => 'gofast')) . '"  href="' . $node_locations_options['href'] . '" style="top:150px;"><span class="glyphicon glyphicon-pencil" ></span> ' . t('Edit', array(), array('context' => 'gofast')) . '</a>';
print '</span>';
