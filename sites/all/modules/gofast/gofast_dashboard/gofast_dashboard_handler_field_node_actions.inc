<?php
/**
 * @file
 *
 */

/**
 * Field handler to display date on modifications from audit table
 *
 * @ingroup views_field_handlers
 */
class gofast_dashboard_handler_field_node_actions extends views_handler_field {
  function construct() {
    parent::construct();
    //$this->additional_fields['nid'] = array('table' => 'node', 'field' => 'nid');
  }

  function option_definition() {
    $options = parent::option_definition();

//    $options['use_title'] = array('default' => FALSE);
//    $options['display_as_link'] = array('default' => TRUE);

    return $options;
  }
  
  /**
   * {@inheritdoc}
   *
   * Perform any database or cache data retrieval here. In this example there is
   * none.
   */
  function query() {
 
  }

  /**
   * Provide link to the page being visited.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
//    $form['use_title'] = array(
//      '#title' => t('Use node title as filename'),
//      '#type' => 'checkbox',
//      '#default_value' => !empty($this->options['use_title']),
//    );
//
//    $form['display_as_link'] = array(
//      '#title' => t('Display as download link'),
//      '#type' => 'checkbox',
//      '#default_value' => !empty($this->options['display_as_link']),
//    );
  }

 function render($values) {
    $nid = $values->nid;
    
    $output = '<div><a class="btn btn-default btn-xs dropdown-toggle dropdown-placeholder" type="button" id="dropdown-placeholder-' . $nid . '" data-toggle="dropdown">'
              . '<span class="fa fa-bars" style="color:#777;"></span>'
              . '<ul class="dropdown-menu gofast-dropdown-menu" role="menu" id="dropdownactive-placeholder-' . $nid . '">'
                . '<li><div class="loader-activity-menu-active"></div></li>'
              . '</ul>'
            . '</a></div>';
    
    return $output;
  }
}