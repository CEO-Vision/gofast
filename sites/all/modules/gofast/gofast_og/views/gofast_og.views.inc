<?php



/**
 * Implements hook_views_data_alter()
 *  
 *  Alter table structure.
 */
function gofast_og_views_data_alter(&$data) {
  // Override field handlers that defines OG membership links for 'delete' & 
  // 'edit' operation.
  if (isset($data['og_membership']['delete_membership']['field']['handler'])) {
    $data['og_membership']['delete_membership']['field']['handler'] = 'gofast_og_handler_field_og_membership_link_delete';
  }
  if (isset($data['og_membership']['edit_membership']['field']['handler'])) {
    $data['og_membership']['edit_membership']['field']['handler'] = 'gofast_og_handler_field_og_membership_link_edit';
  }
}
