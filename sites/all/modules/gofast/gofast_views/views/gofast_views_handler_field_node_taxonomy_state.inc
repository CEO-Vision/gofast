<?php

/**
 * @file
 * Taxonomy State
 * 
 */
class gofast_views_handler_field_node_taxonomy_state extends views_handler_field_node_link {

    function render($values) {
      
     if(isset($values->nid)){
            $node = node_load($values->nid);
            
            if($node->type !== "alfresco_item"){
                return "";
            }else{
                $wrapper = entity_metadata_wrapper("node", $node);
               // print_r("<pre>");var_dump($wrapper->{'field_state'}->value());

                if($wrapper->{'field_state'}->value() !== NULL){
                     $state = $wrapper->{'field_state'}->value();
                     $localized_term = i18n_taxonomy_localize_terms($state);
                     $output = $localized_term->name;
                }else{
                     $output = "";
                }
            }
           
       }else{
            $output = "";
       }
      
       return $output;
     
    }

}