<?php

class gofast_views_handler_field_node_gofast_mobile_activity_feed extends views_handler_field {

    private function get_node_last_modifier($node) {
      $updated = $node->revision_timestamp;
      $commented = $node->last_comment_timestamp;
      $uid = $node->uid;
      if ($commented && $commented > $updated) {
        $uid = $node->last_comment_uid;
      }
      elseif ($node->revision_uid) {
        $uid = $node->revision_uid;
      }
      else {
        $uid = $node->uid;
      }

      $account = user_load($uid);
      return $account;
    }

    private function get_last_updated_time($last_comment_timestamp) {
      
      $second_format = 'short';
      $second_custom_format = 'm/d/y H:m';
      $timezone = drupal_get_user_timezone();
      $time_diff = REQUEST_TIME - $last_comment_timestamp;
      $custom_format = 'm/d/y H:m'; 

      $last_updated = '';

      if (format_date(REQUEST_TIME, 'custom', 'Y-m-d', $timezone) == format_date($last_comment_timestamp, 'custom', 'Y-m-d', $timezone)) {
        $last_updated = t('%time ago', array('%time' => format_interval($time_diff, is_numeric($custom_format) ? $custom_format : 2)), array('context' => 'gofast'));
      }
      elseif ($second_format == 'custom') {
        /*
        if ($second_custom_format == 'r') {
          $last_updated = format_date($last_comment_timestamp, $second_format, $second_custom_format, $timezone, 'en');
        }
         */
        $last_updated = format_date($last_comment_timestamp, $second_format, $second_custom_format, $timezone);
      }
      else {
        $last_updated = format_date($last_comment_timestamp, $second_format, '', $timezone);
      }
      return $last_updated;
    }

    
    private function get_node_spaces($node) {
      $id_spaces = gofast_og_get_parent($node);
      $spaces = node_load_multiple($id_spaces);

//      $renamed_spaces = array_map(function($space) {
//        return gofast_og_node_types()[$space->type] . '/' . $space->title;
//      }, $spaces);
//       
//      return implode(' - ', $renamed_spaces);

     
    
    //Format spaces
      $spaces_list='';
      foreach($spaces as $space){
  //   $spaces_list = array_map(function($space) {
        $gid = $space->nid;
        global $user;
        //Access is bypassed for user 1/Admin
        $node_access = (og_get_membership('node', $gid, 'user', $user->uid) != FALSE) || $user->uid === 1;
        
        if($node_access){
          if(strlen($spaces_list) > 1 ) $spaces_list .= ' - ';
          //$spaces_list .= "<a href=/node/" . $gid . ">" . gofast_get_node_title($gid) . "</a> ";
          $spaces_list .= gofast_get_node_title($gid);
        }
      }
     return $spaces_list;
    }
 
    function query() {
      // do nothing -- to override the parent query.
    }

   function render($values) {
     
     
    $node = isset($values->_field_data['nid']['entity']) ? 
            $values->_field_data['nid']['entity'] : node_load($values->nid);
    
    //ellipse node_title
    if(strlen($values->node_title) > 35){
      $trimmed_title = substr($values->node_title, 0, 35).'...';
    }else{
      $trimmed_title = $values->node_title;
    }
    
    $account = $this->get_node_last_modifier($node);
    
    $output_prepare = gofast_message_ext_api_get_last_event($node->nid);
      
    if($output_prepare['message']){ //Return dated event message from gofast_message_ext
        //print_r("<pre>");print_r($output_prepare);exit;
         $output =  gofast_message_ext_api_render_event($output_prepare);
    }else{
      if(isset($values->_field_data['nid']['entity']->changed)){
        $timestamp_last_edit = $values->_field_data['nid']['entity']->changed;
        if($timestamp_last_edit < (time()-86400)){
          $output = format_date($timestamp_last_edit, 'short');
        }
        else{
          $relative_timestamp = (time()-$timestamp_last_edit);
          $hours = floor($relative_timestamp / 3600);
          $minutes = floor(($relative_timestamp / 60) % 60);
          if($hours == 0){
            $output = t("@min min ago", array('@min' => $minutes), array('context' => 'gofast'));
          }
          else{
            $output = t("@hour hour(s) and @min min ago", array('@hour' => $hours, '@min' => $minutes), array('context' => 'gofast'));
          }
        }
      }
    }
    $last_updated = $output;
    
    $spaces = $this->get_node_spaces($node);   
    $state = '';
    
    //Use directly the $values variable to avoid retrieving the state from taxonomy_load_term (perfoamance problem)
    if (!empty($values->field_field_state)) {
      $state = i18n_taxonomy_localize_terms(taxonomy_term_load($node->field_state[LANGUAGE_NONE][0]['tid']))->name;
    }
    
    // Render your content.
    return theme('gofast_mobile_activity_feed', array(
      'user_picture' => theme('user_picture', array('account' => $account)),
      'node' => $node,
      'trimmed_title' => $trimmed_title, 
      'icon_format' => theme('gofast_node_icon_format', array('node' => $node)),
      'last_updated' => $last_updated,
      'spaces' => $spaces,
      'state' => $state,
      'download_action' => $node->type === 'alfresco_item' ? theme('gofast_download_link', array('node' => $node)) : NULL
    ));      
   }
  
}