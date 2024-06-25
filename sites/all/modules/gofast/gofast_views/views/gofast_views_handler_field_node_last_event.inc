<?php

/**
 * @file
 * 
 * Gofast Field Handler. 
 *  Last Event
 * 
 * Return a string about the last event on the node
 */
class gofast_views_handler_field_node_last_event extends views_handler_field_node_link {

  function render($values) {
    $output = NULL;
    if(module_exists('gofast_message_ext')){ //Log event enabled
      $nid = $values->nid;
      //$output_prepare = gofast_message_ext_api_get_last_event($nid);
      $output_prepare = gofast_message_ext_api_get_last_event2($nid, $values->_field_data['nid']['entity']->changed);
      if(!$output_prepare['event_last_modifier']){
        $node = node_load($nid);
        $last_modifier = user_load($node->revision_uid);
        if($last_modifier){
          $output_prepare['event_last_modifier'] = $last_modifier;
          $output_prepare['user_uid'] = $last_modifier->uid;
          $output_prepare['message'] = $last_modifier->name .' '.$output_prepare['message'];
        }
      }
      if($output_prepare['message']){ //Return dated event message from gofast_message_ext
           $output =  gofast_message_ext_api_render_event($output_prepare);
      }
      if ($output_prepare['message'] && $output_prepare['event_last_modifier']) {
        $output .= "<div class='d-none event-last-modifier'>"
          . theme('user_picture', array('account' => $output_prepare['event_last_modifier'], 'dimensions' => 40))
          . "</div>";
      }
      if(!$output_prepare['message']){ // No event recorded by gofast_message_ext, return 'changed' field in node
        if(isset($values->_field_data['nid']['entity']->changed)){
          $timestamp_last_edit = $values->_field_data['nid']['entity']->changed;
          if($timestamp_last_edit < (time()-86400)){
            $output = format_date($timestamp_last_edit, 'long');
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
          $revision_uid = db_select("node_revision", "nr")->fields("nr", array("uid"))->condition("nr.nid", $nid)->execute()->fetchCol()[0];
          $output .= "<div class='d-none event-last-modifier'>"
            . theme('user_picture', array('account' => user_load($revision_uid), 'dimensions' => 40))
            . "</div>";
          }
      }
    }
    else{ //Log event disables, return 'changed' field in node
      if(isset($values->_field_data['nid']['entity']->changed)){
        $timestamp_last_edit = $values->_field_data['nid']['entity']->changed;
        if($timestamp_last_edit < (time()-86400)){
          $output = format_date($timestamp_last_edit, 'long');
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
    
    //Format text
    $output = "<span>".$output."</span>";
        if ($output_prepare['event'] == 'linksharing'){
          $output_bis = array ();
          $output_bis['last_event']= $output;
          $output_bis['user_uid']= $output_prepare['user_uid'];
          $output_bis['event']= $output_prepare['event'];
          return $output_bis;
        }
        return $output;
    }
  }
 