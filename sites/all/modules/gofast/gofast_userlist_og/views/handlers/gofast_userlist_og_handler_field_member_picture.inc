<?php

/**
 * @file
 * Definition of gofast_userlist_og_handler_field_userlist_picture.
 */

/**
 * Field handler to provide simple renderer that allows using a themed user link.
 *
 * @ingroup views_field_handlers
 */
class gofast_userlist_og_handler_field_member_picture extends views_handler_field_node_link {

  function option_definition() {
    $options = parent::option_definition();

    $options['picture_only'] = array('default' => TRUE, 'bool' => TRUE);
    $options['popup'] = array('default' => FALSE, 'bool' => FALSE);
    $options['dimensions'] = array('default' => 40, 'translatable' => FALSE);
    $options['link'] = array('default' => TRUE, 'bool' => TRUE);

    return $options;
  }

  function options_form(&$form, &$form_state) {
    
    $form['picture_only'] = array(
      '#title' => t('Show picture only', array(), array('context' => 'gofast')),
      '#type' => 'checkbox',
      '#default_value' => !empty($this->options['picture_only']),
      '#description' => t('If unchecked, it will show member (or custom text).', array(), array('context' => 'gofast')),
      '#fieldset' => 'more',
    );
    
    $form['popup'] = array(
      '#title' => t('Show popup profile', array(), array('context' => 'gofast')),
      '#type' => 'checkbox',
      '#default_value' => !empty($this->options['popup']),
      '#description' => t('This allow the popup to show the profile popup on mouse over.', array(), array('context' => 'gofast')),
      '#fieldset' => 'more',
    );

    $form['dimensions'] = array(
      '#title' => t('The size of the picture (squared)', array(), array('context' => 'gofast')),
      '#type' => 'textfield',
      '#default_value' => $this->options['dimensions'],
      '#description' => t('Change this settings to update picture dimensions.', array(), array('context' => 'gofast')),
      '#fieldset' => 'more',
    );
    $form['link'] = array(
      '#title' => t('Link to member', array(), array('context' => 'gofast')),
      '#type' => 'checkbox',
      '#default_value' => !empty($this->options['link']),
      '#description' => t('If checked, the link will redirrect to member.', array(), array('context' => 'gofast')),
      '#dependency' => array(
        'edit-options-picture-only' => array(0),
      ),
      '#fieldset' => 'more',
    );
     $form['override_name'] = array(
      '#title' => t('Override the username', array(), array('context' => 'gofast')),
      '#type' => 'checkbox',
      '#default_value' => !empty($this->options['override_name']),
      '#description' => t('Default is username. Check to display another value.', array(), array('context' => 'gofast')),
      '#fieldset' => 'more',
      '#dependency' => array(
        'edit-options-picture-only' => array(0),
      ),
    );
    $form['override_name_text'] = array(
      '#title' => t('Override the user name by another text', array(), array('context' => 'gofast')),
      '#type' => 'textfield',
      '#default_value' => $this->options['override_name_text'],
      '#description' => t('Specify the user name overriden. Use <b>&lt;NONE&gt</b> to use Firstname and Lastname', array(), array('context' => 'gofast')),
      '#dependency' => array(
        'edit-options-picture-only' => array(0),
      ),
      '#fieldset' => 'more',
    );
    
    
    parent::options_form($form, $form_state);
  }

  function render($values) {
    $member = $this->get_value($values);
    
    if ($this->options['picture_only']) {
      
      if ($this->query->view->current_display == 'gofast_single_profile') {
        $this->options['dimensions'] = 100;
      }

      if ($member->entity_type == 'user') {
        $account = user_load($member->etid);
         return theme("user_picture", array('account' => $account, 'popup' => !!$this->options['popup'], 'dimensions' => $this->options['dimensions'], 'style' => 'thumbnail'));
      }
      else if ($member->entity_type == 'userlist') {
        return theme("gofast_userlist_picture", array('member' => $member, 'popup' => !!$this->options['popup'], 'dimensions' => $this->options['dimensions'], 'style' => 'thumbnail'));
      }
    }
    else {
      $options = array('userlist' => $userlist,
        'picture' => TRUE,
        'popup' => $this->options['popup'],
        'link' => $this->options['link'],
        'dimensions' => $this->options['dimensions']);
      
      if ((!!$this->options['override_name']) === TRUE) {
        $options['override_name'] = $this->options['override_name_text'] !== "<NONE>" ? $this->options['override_name_text'] : TRUE;
      } else {
        $options['override_name'] = FALSE;
      }

      return theme('userlist_name', $options);
    }
  }

}
