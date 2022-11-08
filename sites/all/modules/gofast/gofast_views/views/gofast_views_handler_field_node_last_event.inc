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
    $edit = NULL;
    if(module_exists('gofast_message_ext')){ //Log event enabled
      $nid = $values->nid;
      //$output_prepare = gofast_message_ext_api_get_last_event($nid);
      $output_prepare = gofast_message_ext_api_get_last_event2($nid, $values->_field_data['nid']['entity']->changed);
      if($output_prepare['message']){ //Return dated event message from gofast_message_ext
           $output =  gofast_message_ext_api_render_event($output_prepare);
      }
      else{ // No event recorded by gofast_message_ext, return 'changed' field in node
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
 