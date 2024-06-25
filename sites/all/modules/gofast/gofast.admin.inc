<?php

/**
 * @file
 *  Gofast Administration.
 *
 *  Contains code related to Gofast configuration settings accessible to
 *  Gofast administrators.
 */

/**
 * Gofast configuration form
 * General vtab definitions.
 * fields are set in form_alter
 */
function gofast_admin_settings() {
  drupal_add_js(drupal_get_path('module', 'gofast') . '/js/gofast_admin.js');
  drupal_add_js(drupal_get_path('module', 'gofast') . '/js/gofast_ajax_form.js');
  $form = array();

  $form['vt'] = array(
    '#type' => 'vertical_tabs',
  );

  $form['general'] = array(
    '#title' => t('General' ,array(), array('context' => 'gofast')),
    '#type' => 'fieldset',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#group' => 'vt',
    '#attributes' => array('class' => array('edit-general')),
  );

  /*
  $form['theme'] = array(
    '#title' => t('Theme', array(), array('context' => 'gofast')),
    '#type' => 'fieldset',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#group' => 'vt'
  );
  */

  $form['smtp'] = array(
    '#title' => t('SMTP Server', array(), array('context' => 'gofast') ),
    '#type' => 'fieldset',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#group' => 'vt',
    '#attributes' => array('class' => array('edit-smtp')),
  );

  $form['rssfeeds'] = array(
    '#title' => t('RSS Feeds', array(), array('context' => 'gofast')),
    '#type' => 'fieldset',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#group' => 'vt',
    '#attributes' => array('class' => array('edit-rssfeed')),
  );

  $form['ldap'] = array(
    '#title' => t('LDAP / AD Server', array(), array('context' => 'gofast')),
    '#type' => 'fieldset',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#group' => 'vt',
    '#attributes' => array('class' => array('edit-ldap')),
  );

  $form['users'] = array(
    '#title' => t('Users', array(), array('context' => 'gofast')),
    '#type' => 'fieldset',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#group' => 'vt',
    '#attributes' => array('class' => array('edit-users')),
  );

  $form['documents'] = array(
    '#title' => t('Documents', array(), array('context' => 'gofast')),
    '#type' => 'fieldset',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#group' => 'vt',
    '#attributes' => array('class' => array('edit-documents')),
  );

  $form['spaces'] = array(
    '#title' => t('Spaces', array(), array('context' => 'gofast')),
    '#type' => 'fieldset',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#group' => 'vt',
    '#attributes' => array('class' => array('edit-spaces')),
  );

  $form['sso'] = array(
    '#title' => t('SSO', array(), array('context' => 'gofast')),
    '#type' => 'fieldset',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#group' => 'vt',
    '#attributes' => array('class' => array('edit-sso')),
  );

  $form['visibility'] = array(
    '#title' => t('Visibility', array(), array('context' => 'gofast')),
    '#type' => 'fieldset',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#group' => 'vt',
    '#attributes' => array('class' => array('edit-visibility')),
  );

  $form['indexing'] = array(
    '#title' => t('Search Index', array(), array('context' => 'gofast')),
    '#type' => 'fieldset',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#group' => 'vt',
    '#attributes' => array('class' => array('edit-indexing')),
  );

  $form['integrity'] = array(
    '#title' => t('Integrity', array(), array('context' => 'gofast:gofast_integrity')),
    '#type' => 'fieldset',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#group' => 'vt',
    '#attributes' => array('class' => array('edit-integrity')),
  );

  /*
  $form['onlyoffice'] = array(
    '#title' => t('OnlyOffice parameters', array(), array('context' => 'gofast')),
    '#type' => 'fieldset',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#group' => 'vt'
  );
   */

  $form['categories'] = array(
    '#title' => t('Categories', array(), array('context' => 'gofast')),
    '#type' => 'fieldset',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#group' => 'vt',
    '#attributes' => array('class' => array('edit-categories')),
  );

  $form['metadata'] = array(
    '#title' => t('Metadata', array(), array('context' => 'gofast')),
    '#type' => 'fieldset',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#group' => 'vt',
    '#attributes' => array('class' => array('edit-metadata')),
  );

  if(module_exists('gofast_signature')) {
      $form['signature'] = array(
        '#title' => t('Signature', array(), array('context' => 'gofast:gofast_signature')),
        '#type' => 'fieldset',
        '#collapsible' => FALSE,
        '#collapsed' => FALSE,
        '#group' => 'vt',
        '#attributes' => array('class' => array('edit-signature')),
      );
  }
  
  if(module_exists('gofast_digitalsign')) {
    $form['signature_digitalsign'] = array(
      '#title' => t('Signature Digitalsign', array(), array('context' => 'gofast:gofast_signature')),
      '#type' => 'fieldset',
      '#collapsible' => FALSE,
      '#collapsed' => FALSE,
      '#group' => 'vt',
      '#attributes' => array('class' => array('edit-signature-digitalsign')),
    );
  }

  if (module_exists('gofast_community')){
        $form['update'] = array(
        '#title' => t('Update'),
        '#type' => 'fieldset',
        '#collapsible' => FALSE,
        '#collapsed' => FALSE,
        '#group' => 'vt',
        '#attributes' => array('class' => array('edit-update')),
      );
  }

  if(module_exists('gofast_pastell')){
      $form['pastelll'] = array(
        '#title' => t('GoFAST Pastell'),
        '#type' => 'fieldset',
        '#collapsible' => FALSE,
        '#collapsed' => FALSE,
        '#group' => 'vt',
        '#attributes' => array('class' => array('edit-pastell')),
        );
  }

  if(module_exists('gofast_esup')){
      $form['esup'] = array(
        '#title' => t('GoFAST ESUP'),
        '#type' => 'fieldset',
        '#collapsible' => FALSE,
        '#collapsed' => FALSE,
        '#group' => 'vt',
        '#attributes' => array('class' => array('edit-esup')),
        );
  }

  return $form;
}



function gofast_admin_settings_tabs() {
    drupal_add_js(drupal_get_path('module', 'gofast') . '/js/gofast_admin.js');

    $tab_path = "admin/config/gofast/global/getform";
    $gofastAdminTabs = array();

   $sub_path = $tab_path."/edit-general";
    if ($router_item = menu_get_item($sub_path)) {
       if ($router_item['access']) {
            $gofastAdminTabs['general'] = array(
                'title' => t('General', array(), array('context' => 'gofast')),
                'attributes' => array('class' => 'edit-general', 'data-form-id' => str_replace('_', '-',$router_item['page_arguments'][0])),
                'icon' => 'flaticon-settings'
            );
        }
    }

    $sub_path = $tab_path."/edit-smtp";
    if ($router_item = menu_get_item($sub_path)) {
        if ($router_item['access']) {
          $gofastAdminTabs['smtp'] = array(
              'title' => t('SMTP Server', array(), array('context' => 'gofast')),
              'attributes' => array('class' => 'edit-smtp', 'data-form-id' => str_replace('_', '-',$router_item['page_arguments'][0])),
              'icon' => 'flaticon-mail'
          );
        }
    }

    $sub_path = $tab_path . "/edit-rssfeed";
    if ($router_item = menu_get_item($sub_path)) {
        if ($router_item['access']) {
            $gofastAdminTabs['rssfeeds'] = array(
                'title' => t('RSS Feeds', array(), array('context' => 'gofast')),
                'attributes' => array('class' => 'edit-rssfeed', 'data-form-id' => str_replace('_', '-',$router_item['page_arguments'][0])),
                'icon' => 'flaticon-feed'
            );
        }
    }

    $sub_path = $tab_path . "/edit-ldap";
    if ($router_item = menu_get_item($sub_path)) {
        if ($router_item['access']) {
            $gofastAdminTabs['ldap'] = array(
                'title' => t('LDAP / AD Server', array(), array('context' => 'gofast')),
                'attributes' => array('class' => 'edit-ldap', 'data-form-id' => str_replace('_', '-',$router_item['page_arguments'][0])),
                'icon' => 'flaticon-folder-1'
            );
        }
    }

    $sub_path = $tab_path . "/edit-users";
    if ($router_item = menu_get_item($sub_path)) {
        if ($router_item['access']) {
            $gofastAdminTabs['users'] = array(
                'title' => t('Users', array(), array('context' => 'gofast')),
                'attributes' => array('class' => 'edit-users', 'data-form-id' => str_replace('_', '-',$router_item['page_arguments'][0])),
                'icon' => 'flaticon-users'
            );
        }
    }

    $sub_path = $tab_path . "/edit-documents";
    if ($router_item = menu_get_item($sub_path)) {
        if ($router_item['access']) {
            $gofastAdminTabs['documents'] = array(
                'title' => t('Documents', array(), array('context' => 'gofast')),
                'attributes' => array('class' => 'edit-documents', 'data-form-id' => str_replace('_', '-',$router_item['page_arguments'][0])),
                'icon' => 'flaticon2-document'
            );
        }
    }

    $sub_path = $tab_path . "/edit-spaces";
    if ($router_item = menu_get_item($sub_path)) {
        if ($router_item['access']) {
            $gofastAdminTabs['spaces'] = array(
                'title' => t('Spaces', array(), array('context' => 'gofast')),
                'attributes' => array('class' => 'edit-spaces', 'data-form-id' => str_replace('_', '-',$router_item['page_arguments'][0])),
                'icon' => 'flaticon2-group'
            );
        }
    }

    $sub_path = $tab_path . "/edit-tags";
    if ($router_item = menu_get_item($sub_path)) {
        if ($router_item['access']) {
            $gofastAdminTabs['tags'] = array(
                'title' => t('Tags', array(), array('context' => 'gofast')),
                'attributes' => array('class' => 'edit-tags', 'data-form-id' => 'gofastTagsTable'),
                'icon' => 'fas fa-tags'
            );
        }
    }

    $sub_path = $tab_path . "/edit-sso";
    if ($router_item = menu_get_item($sub_path)) {
        if ($router_item['access']) {
            $gofastAdminTabs['sso'] = array(
                'title' => t('SSO', array(), array('context' => 'gofast')),
                'attributes' => array('class' => 'edit-sso', 'data-form-id' => str_replace('_', '-',$router_item['page_arguments'][0])),
                'icon' => 'flaticon2-user-outline-symbol'
            );
        }
    }

    $sub_path = $tab_path . "/edit-visibility";
    if ($router_item = menu_get_item($sub_path)) {
        if ($router_item['access']) {
            $gofastAdminTabs['visibility'] = array(
                'title' => t('Visibility', array(), array('context' => 'gofast')),
                'attributes' => array('class' => 'edit-visibility', 'data-form-id' => str_replace('_', '-',$router_item['page_arguments'][0])),
                'icon' => 'flaticon-visible'
            );
        }
    }

    $sub_path = $tab_path . "/edit-indexing";
    if ($router_item = menu_get_item($sub_path)) {
        if ($router_item['access']) {
            $gofastAdminTabs['indexing'] = array(
                'title' => t('Search Index', array(), array('context' => 'gofast')),
                'attributes' => array('class' => 'edit-indexing', 'data-form-id' => str_replace('_', '-',$router_item['page_arguments'][0])),
                'icon' => 'flaticon-search'
            );
        }
    }

    $sub_path = $tab_path . "/edit-integrity";
    if ($router_item = menu_get_item($sub_path)) {
        if ($router_item['access']) {
            $gofastAdminTabs['integrity'] = array(
                'title' => t('Integrity', array(), array('context' => 'gofast:gofast_integrity')),
                'attributes' => array('class' => 'edit-integrity', 'data-form-id' => str_replace('_', '-',$router_item['page_arguments'][0])),
                'icon' => 'flaticon2-graph-2'
            );
        }
    }

    $sub_path = $tab_path . "/edit-categories";
    if ($router_item = menu_get_item($sub_path)) {
        if ($router_item['access']) {
          $gofastAdminTabs['categories'] = array(
                'title' => t('Categories', array(), array('context' => 'gofast')),
                'attributes' => array('class' => 'edit-categories', 'data-form-id' => 'gofast-admin-categories-settings-form'),
                'icon' => 'flaticon2-setup'
            );
        }
    }

    if (module_exists('gofast_signature')) {
        $sub_path = $tab_path . "/edit-signature";
        if ($router_item = menu_get_item($sub_path)) {
            if ($router_item['access']) {
                $gofastAdminTabs['signature'] = array(
                    'title' => t('Signature', array(), array('context' => 'gofast:gofast_signature')),
                    'attributes' => array('class' => 'edit-signature', 'data-form-id' => str_replace('_', '-',$router_item['page_arguments'][0])),
                    'icon' => 'fas fa-file-signature'
                );
            }
        }
    }

    if (module_exists('gofast_digitalsign')) {
      $sub_path = $tab_path . "/edit-signature-digitalsign";
      if ($router_item = menu_get_item($sub_path)) {
          if ($router_item['access']) {
              $gofastAdminTabs['signature_digitalsign'] = array(
                  'title' => t('Signature Digitalsign', array(), array('context' => 'gofast:gofast_signature')),
                  'attributes' => array('class' => 'edit-signature-digitalsign', 'data-form-id' => str_replace('_', '-',$router_item['page_arguments'][0])),
                  'icon' => 'fas fa-file-signature'
              );
          }
      }
    }

    $sub_path = $tab_path . "/edit-custom-link";
    if ($router_item = menu_get_item($sub_path)) {
        if ($router_item['access']) {
            $gofastAdminTabs['custom_link'] = array(
                'title' => t('Custom Link', array(), array('context' => 'gofast:gofast_menu')),
                'attributes' => array('class' => 'edit-custom-link', 'data-form-id' => str_replace('_', '-',$router_item['page_arguments'][0])),
                'icon' => 'fas fa-archway'
            );
        }
    }
    
   if(module_exists('gofast_webhook')) {
     $sub_path = $tab_path . "/edit-webhook";
     if ($router_item = menu_get_item($sub_path)) {
       if ($router_item['access']) {
         $gofastAdminTabs['webhook'] = [
           'title' => t('Gofast Webhook', [], ['context' => 'gofast:gofast_webhook']),
           'attributes' => ['class' => 'edit-webhook', 'data-form-id' => str_replace('_', '-',$router_item['page_arguments'][0])],
           'icon' => 'fas fa-level-up',
         ];
       }
     }
   }

    if (module_exists('gofast_community')) {
        $sub_path = $tab_path . "/edit-update";
        if ($router_item = menu_get_item($sub_path)) {
            if ($router_item['access']) {
                $gofastAdminTabs['update'] = array(
                    'title' => t('Update'),
                    'attributes' => array('class' => 'edit-update', 'data-form-id' => str_replace('_', '-',$router_item['page_arguments'][0])),
                );
            }
        }
    }

    if (module_exists('gofast_pastell')) {
        $sub_path = $tab_path . "/edit-pastell";
        if ($router_item = menu_get_item($sub_path)) {
            if ($router_item['access']) {
                $gofastAdminTabs['pastelll'] = array(
                    'title' => t('GoFAST Pastell'),
                    'attributes' => array('class' => 'edit-pastell', 'data-form-id' => str_replace('_', '-',$router_item['page_arguments'][0])),
                );
            }
        }
    }

    if (module_exists('gofast_esup')) {
        $sub_path = $tab_path . "/edit-esup";
        if ($router_item = menu_get_item($sub_path)) {
            if ($router_item['access']) {
                $gofastAdminTabs['esup'] = array(
                    'title' => t('GoFAST ESUP'),
                    'attributes' => array('class' => 'edit-esup'),
                    'icon' => 'fas fa-file-signature'
                );
            }
        }
    }

  if (module_exists('gofast_bluemind')) {
    $sub_path = $tab_path . "/edit-bluemind";
    if ($router_item = menu_get_item($sub_path)) {
      if ($router_item['access']) {
        $gofastAdminTabs['gofast_bluemind'] = array(
          'title' => t('GoFAST BlueMind'),
          'attributes' => array('class' => 'edit-bluemind', 'data-form-id' => str_replace('_', '-',$router_item['page_arguments'][0])),
          'icon' => 'fas fa-calendar'
        );
      }
    }
  }
    
    return $gofastAdminTabs;
}




function gofast_admin_menu(){
  $items = array();

  $items['admin/config/gofast/global/getform/edit-general'] = array(
    'title' => t('Gofast Configuration', array(), array('context' => 'gofast')),
    'page callback' => 'drupal_get_form',
    'page arguments' => array('gofast_admin_general_settings_form'),
    'access arguments' => array('administer general configuration'),
    'delivery callback' => 'gofast_admin_deliver_page',
    'type' => MENU_NORMAL_ITEM,
    'file' => 'gofast.admin.inc'
  );

  $items['admin/config/gofast/global/getform/edit-smtp'] = array(
    'title' => t('Gofast Configuration', array(), array('context' => 'gofast')),
    'page callback' => 'drupal_get_form',
    'page arguments' => array('gofast_admin_smtp_settings_form'),
    'access arguments' => array('administer smtp configuration'),
    'delivery callback' => 'gofast_admin_deliver_page',
    'type' => MENU_NORMAL_ITEM,
    'file' => 'gofast.admin.inc'
  );

  $items['admin/config/gofast/global/getform/edit-rssfeed'] = array(
    'title' => t('Gofast Configuration', array(), array('context' => 'gofast')),
    'page callback' => 'drupal_get_form',
    'page arguments' => array('gofast_admin_rssfeed_settings_form'),
    'access arguments' => array('administer rss configuration'),
    'delivery callback' => 'gofast_admin_deliver_page',
    'type' => MENU_NORMAL_ITEM,
    'file' => 'gofast.admin.inc'
  );

  $items['admin/config/gofast/global/getform/edit-ldap'] = array(
    'title' => t('Gofast Configuration', array(), array('context' => 'gofast')),
    'page callback' => 'drupal_get_form',
    'page arguments' => array('gofast_admin_ldap_settings_form'),
    'access arguments' => array('administer ldap configuration'),
    'delivery callback' => 'gofast_admin_deliver_page',
    'type' => MENU_NORMAL_ITEM,
    'file' => 'gofast.admin.inc'
  );

  $items['admin/config/gofast/global/getform/edit-users'] = array(
    'title' => t('Gofast Configuration', array(), array('context' => 'gofast')),
    'page callback' => 'drupal_get_form',
    'page arguments' => array('gofast_admin_users_settings_form'),
    'access arguments' => array('administer users configuration'),
    'delivery callback' => 'gofast_admin_deliver_page',
    'type' => MENU_NORMAL_ITEM,
    'file' => 'gofast.admin.inc'
  );

  $items['admin/config/gofast/global/getform/edit-documents'] = array(
    'title' => t('Gofast Configuration', array(), array('context' => 'gofast')),
    'page callback' => 'drupal_get_form',
    'page arguments' => array('gofast_admin_documents_settings_form'),
    'access arguments' => array('administer documents configuration'),
    'delivery callback' => 'gofast_admin_deliver_page',
    'type' => MENU_NORMAL_ITEM,
    'file' => 'gofast.admin.inc'
  );

  $items['admin/config/gofast/global/getform/edit-spaces'] = array(
    'title' => t('Gofast Configuration', array(), array('context' => 'gofast')),
    'page callback' => 'drupal_get_form',
    'page arguments' => array('gofast_admin_spaces_settings_form'),
    'access arguments' => array('administer spaces configuration'),
    'delivery callback' => 'gofast_admin_deliver_page',
    'type' => MENU_NORMAL_ITEM,
    'file' => 'gofast.admin.inc'
  );

  $items['admin/config/gofast/global/getform/edit-sso'] = array(
    'title' => t('Gofast Configuration', array(), array('context' => 'gofast')),
    'page callback' => 'drupal_get_form',
    'page arguments' => array('gofast_admin_sso_settings_form'),
    'access arguments' => array('administer sso configuration'),
    'delivery callback' => 'gofast_admin_deliver_page',
    'type' => MENU_NORMAL_ITEM,
    'file' => 'gofast.admin.inc'
  );

  $items['admin/config/gofast/global/getform/edit-indexing'] = array(
    'title' => t('Gofast Configuration', array(), array('context' => 'gofast')),
    'page callback' => 'drupal_get_form',
    'page arguments' => array('gofast_admin_indexing_settings_form'),
    'access arguments' => array('administer index configuration'),
    'delivery callback' => 'gofast_admin_deliver_page',
    'type' => MENU_NORMAL_ITEM,
    'file' => 'gofast.admin.inc'
  );

  $items['admin/config/gofast/global/getform/edit-integrity'] = array(
    'title' => t('Gofast Configuration', array(), array('context' => 'gofast')),
    'page callback' => 'drupal_get_form',
    'page arguments' => array('gofast_admin_integrity_settings_form'),
    'access arguments' => false,
    'delivery callback' => 'gofast_admin_deliver_page',
    'type' => MENU_NORMAL_ITEM,
    'file' => 'gofast.admin.inc'
  );

  $items['admin/config/gofast/global/getform/edit-categories'] = array(
    'title' => t('Gofast Configuration', array(), array('context' => 'gofast')),
    'page callback' => array('gofast_admin_categories_settings_page'),
    'access arguments' => array('administer categories configuration'),
    'delivery callback' => 'gofast_admin_deliver_html',
    'type' => MENU_NORMAL_ITEM,
    'file' => 'gofast.admin.inc'
  );

   $items['admin/config/gofast/global/getform/edit-visibility'] = array(
    'title' => t('Gofast Configuration', array(), array('context' => 'gofast')),
    'page callback' => 'drupal_get_form',
    'page arguments' => array('gofast_admin_visibility_settings_form'),
    'access arguments' => array('administer visibility configuration'),
    'delivery callback' => 'gofast_admin_deliver_page',
    'type' => MENU_NORMAL_ITEM,
    'file' => 'gofast.admin.inc'
  );
   $items['admin/config/gofast/global/getform/edit-retention'] = array(
    'title' => t('Gofast Configuration', array(), array('context' => 'gofast')),
    'page callback' => 'drupal_get_form',
    'page arguments' => array('gofast_admin_retention_settings_form'),
    'access arguments' => array('administer retention configuration'),
    'delivery callback' => 'gofast_admin_deliver_page',
    'type' => MENU_NORMAL_ITEM,
    'file' => 'gofast.admin.inc'
  );
  $items['admin/config/gofast/global/getform/edit-custom-link'] = array(
    'title' => t('Gofast Configuration', array(), array('context' => 'gofast')),
    'page callback' => 'drupal_get_form',
    'page arguments' => array('gofast_admin_custom_link_settings_form'),
    'access arguments' => array('administer custom link configuration'),
    'delivery callback' => 'gofast_admin_deliver_page',
    'type' => MENU_NORMAL_ITEM,
    'file' => 'gofast.admin.inc'
  );
  $items['admin/config/gofast/global/getform/edit-pastell'] = array(
    'title' => t(
    'GoFAST Configuration', array(), array('context' => 'gofast')),
    'page callback' => 'drupal_get_form',
    'page arguments' => array('gofast_admin_pastell_settings_form'),
    'access arguments' => array('administer pastell configuration'),
    'delivery callback' => 'gofast_admin_deliver_page',
    'type' => MENU_NORMAL_ITEM,
    'file' => 'gofast.admin.inc'
    );
  $items['admin/config/gofast/global/getform/edit-esup'] = array(
    'title' => t('GoFAST Configuration', array(), array('context' => 'gofast')),
    'page callback' => 'drupal_get_form',
    'page arguments' => array('gofast_admin_esup_settings_form'),
    'access arguments' => array('administer esup configuration'),
    'delivery callback' => 'gofast_admin_deliver_page',
    'type' => MENU_NORMAL_ITEM,
    'file' => 'gofast.admin.inc'
    );
   $items['admin/config/gofast/global/getform/edit-signature'] = array(
    'title' => t('Gofast Configuration', array(), array('context' => 'gofast:gofast_signature')),
    'page callback' => 'drupal_get_form',
    'page arguments' => array('gofast_admin_signature_settings_form'),
    'access arguments' => array('administer signature configuration'),
    'delivery callback' => 'gofast_admin_deliver_page',
    'type' => MENU_NORMAL_ITEM,
    'file' => 'gofast.admin.inc'
  );
  $items['admin/config/gofast/global/getform/edit-signature-digitalsign'] = array(
    'title' => t('Gofast Configuration', array(), array('context' => 'gofast:gofast_signature')),
    'page callback' => 'drupal_get_form',
    'page arguments' => array('gofast_admin_signature_digitalsign_settings_form'),
    'access arguments' => array('administer signature configuration'),
    'delivery callback' => 'gofast_admin_deliver_page',
    'type' => MENU_NORMAL_ITEM,
    'file' => 'gofast.admin.inc'
  );
  $items['admin/config/gofast/global/getform/edit-tags'] = array(
    'title' => t('Gofast Configuration', array(), array('context' => 'gofast')),
    'page callback' => 'gofast_admin_tags_settings_page',
    'access arguments' => array('administer tags configuration'),
    'delivery callback' => 'gofast_admin_deliver_html',
    'type' => MENU_NORMAL_ITEM,
    'file' => 'gofast.admin.inc'
  );
  //link for the webhook
  $items['admin/config/gofast/global/getform/edit-webhook'] = array(
    'title' => t('Gofast Configuration', [], ['context' => 'gofast:gofast_webhook']),
    'page callback' => 'drupal_get_form',
    'page arguments' => ['gofast_webhook_settings_form'],
    'access arguments' => ['administer gofast webhook'],
    'delivery callback' => 'gofast_admin_deliver_page',
    'type' => MENU_NORMAL_ITEM,
    'file' => 'gofast.admin.inc',
  );
  $items['admin/action/apply_retention'] = array(
    'title' => t('Gofast Configuration', array(), array('context' => 'gofast')),
    'page callback' => array('gofast_admin_action_set_retention_rules'),
    'access arguments' => array('administer categories configuration'),
    'type' => MENU_NORMAL_ITEM,
    'file' => 'gofast.admin.inc'
  );

  $items['admin/config/gofast/global/getform/edit-bluemind'] = array(
    'title' => t('Gofast Configuration', [], ['context' => 'gofast:gofast_bluemind']),
    'page callback' => 'drupal_get_form',
    'page arguments' => ['gofast_bluemind_admin_settings_form'],
    'delivery callback' => 'gofast_admin_deliver_page',
    'access arguments' => array('administer users configuration'),
    'type' => MENU_NORMAL_ITEM,
    'file' => 'gofast.admin.inc',
  );
  
  return $items;
}

function gofast_admin_tags_settings_page() {
  $columns = [];

  $columns['links'] = t('links', [], ['context' => 'gofast:gofast']);
  $columns['name'] = t('Tag name', [], ['context' => 'gofast:gofast']);
  $columns['docs'] = t('Number of documents', [], ['context' => 'gofast:gofast']);
  $columns['actions'] = t('Actions', [], ['context' => 'gofast:gofast']);

  $jsonColumns = htmlspecialchars(json_encode($columns), ENT_QUOTES);

  $content = theme('gofast_admin_tags_table', ["columns" => $jsonColumns]);

  return $content;
}

/**
 * Admin categories page
 * @throws \Exception
 * @return string
 */
function gofast_admin_categories_settings_page(): string {

  $content = '';

  if (!module_exists('gofast_community')){
    $form = drupal_get_form('gofast_admin_categories_settings_form');
    $content .= drupal_render($form);
  }
  
  $columns = [];

  $columns['name'] = t('Category name', [], ['context' => 'gofast:gofast']);
  $columns['standard'] = t('Standard?', [], ['context' => 'gofast:gofast']);
  $columns['dua'] = t('Retention', [], ['context' => 'gofast:gofast']);
  if (module_exists("gofast_naming_rules")) {
    $columns['rules'] = t('Naming rules', [], ['context' => 'gofast:gofast']);
  }
  // $columns['criticity'] = t('Criticity', [], ['context' => 'gofast:gofast']);
  $columns['docs'] = t('Docs', [], ['context' => 'gofast']);
  $columns['in'] = t('Spaces', [], ['context' => 'gofast']);
  $columns['actions'] = t('Created by', [], ['context' => 'gofast:gofast']);

  $jsonColumns = htmlspecialchars(json_encode($columns), ENT_QUOTES);

  $content .= theme('gofast_admin_categories_table', ["columns" => $jsonColumns]);
  
  return $content;
}

/**
 * Admin categories form
 */
function gofast_admin_categories_settings_form(): array {
  $form = [];
    $form['archivists'] = [
      '#title' => t('Archivists', [], ['context' => 'gofast']),
      '#type' => 'fieldset',
      '#collapsible' => FALSE,
      '#collapsed' => FALSE,
    ];

    $recipients = [];
    if (NULL != variable_get(GOFAST_RETENTION_PERIOD_RECIPIENTS_VAR)) {
      $list_recipient = variable_get(GOFAST_RETENTION_PERIOD_RECIPIENTS_VAR);

      foreach ($list_recipient as $recipient) {
        $recipient_user = user_load($recipient->id);
        $recipients[] = gofast_ac_format_value_json('user', $recipient_user);
      }
    }

    $form['archivists']['group'] = array(
      '#type' => 'container',
      '#prefix' => '<label class="control-label" for="edit-field-tags">'.t('Current list of mail recipients', [], ['context' => 'gofast:gofast_retention']).'</label>',
      '#attributes' => array("class" => array("d-flex")),
    );
    $form['archivists']['group']['ac-list-tags-list-recipients'] = [
      '#type' => 'textfield',
      '#default_value' => json_encode($recipients),
      '#id' => 'edit-field-tags',
      '#maxlength' => 999999,
      '#attributes' => [
        'class' => ['form-control-tags js-tagify retention-archivist-users'],
        'data-user' => '', // show ac users
        ],
    ];
    
    $form['archivists']['group']['submit'] = [
      '#type' => 'submit',
      '#value' => t('Save'),
      '#attributes' => [
        'class' => ['btn btn-primary'],
      ],
    ];
    return $form;
}

  /** 
   * Submit handler for the categories form
   * @param $form 
   * @param &$form_state
   */
  function gofast_admin_categories_settings_form_submit($form, &$form_state):void {
    
    if (!module_exists("gofast_community")) {
      $recipients = $form_state['values']['ac-list-tags-list-recipients'];
      $array_dest = json_decode($recipients);
      if(count($array_dest) > 0){
        $json_list_recipients = array();
        foreach($array_dest as $dest_json){
          $account = user_load($dest_json->value);
          $account_obj = new stdClass();
          $account_obj->id = $dest_json->value;
          $account_obj->address = $account->mail;
          $account_obj->name = $account->name;
          $account_obj->type = "user";
          $json_list_recipients[] = $account_obj;
        }
        variable_set(GOFAST_RETENTION_PERIOD_RECIPIENTS_VAR, $json_list_recipients);
      }
    }
  }
  /**
   * Add search related settings to the configuration form.
 */
function gofast_admin_indexing_settings_form() {
  include_once 'gofast_search/gofast_search.admin.inc';
  $form = array();
  $form['indexing']['stats'] = array(
    '#type' => 'fieldset',
    '#title' => t('Search Index Informations', array(), array('context' => 'gofast:gofast_search')),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    'markup' => array(
      '#markup' => gofast_search_get_stats()
    )
  );

  $render_full_reindex = '';
  if (!$full_reindex_timestamp = variable_get('gofast_full_reindex', FALSE)){
    $action = t('Start full reindex', [], ['context' => 'gofast:gofast_search']);
    $render_full_reindex .= '<a href="/gofast-search/start_full_reindex" style="margin-right:20px;">';
    $render_full_reindex .= '<button title="'.$action.'" type="button" class="btn btn-default btn-sm">';
    $render_full_reindex .= $action.'</button></a>';
  }
  else {
    $start = format_date($full_reindex_timestamp, 'short');
    $msg = t('Full reindex has been started (!start).', ['!start' => $start], ['context' => 'gofast:gofast_search']);
    $action = t('Cancel full reindex', [], ['context' => 'gofast:gofast_search']);
    $render_full_reindex .= '<h6>'. $msg .'</h6>';
    $render_full_reindex .= '<a href="/gofast-search/cancel_full_reindex" style="margin-right:20px;">';
    $render_full_reindex .= '<button title="'.$action.'" type="button" class="btn btn-default btn-sm">';
    $render_full_reindex .= $action.'</button></a>';
  }

  $render_last_info = '';
  $title = t('Last full reindex :', [], ['context' => 'gofast:gofast_search']);
  $render_last_info .= '<span>'. $title .'</span>';
  $last_reindex_info = variable_get('gofast_full_reindex_last', FALSE);
  if (!$last_reindex_info) {
    $render_last_info .= '<span>n/a</span>';
  }
  else {
    $start = format_date($last_reindex_info['start'], 'short');
    $end = format_date($last_reindex_info['end'], 'short');
    $started = t('started : !start', ['!start' => ' ' . $start], ['context' => 'gofast:gofast_search']);
    $ended = t('ended : !end', ['!end' => ' ' . $end], ['context' => 'gofast:gofast_search']);
    $render_last_info .= '<span>' . array_to_html([$started, $ended]) . '</span>';
  }

  $form['indexing']['full_reindex'] = array(
    '#type' => 'fieldset',
    '#title' => t('Full Reindex Informations', array(), array('context' => 'gofast:gofast_search')),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    'markup1' => array(
      '#markup' => '<div>' . $render_full_reindex . '</div>'
    ),
    'markup2' => array(
      '#markup' => '<br><div>' . $render_last_info . '</div>'
    )
  );

  $solr_logs = array(
    'extraction' => variable_get('gofast_search_tika_node_exclude', array()),
    'index' => variable_get('gofast_search_index_node_exclude', array())
  );

  $form['indexing']['extraction'] = array(
    '#title' => t('Content Extraction', array(), array('context' => 'gofast:gofast_search')),
    '#type' => 'fieldset',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#attributes'=> array('class' => array('mt-5')),
    '#description' => t('Content extraction may sometimes fail with certain documents which, in consequence,'
      . ' are excluded from the extraction process in order not to slow down the whole indexing system.', array(), array('context' => 'gofast:gofast_search'))
      . ' ' . t('These documents are still searchable because all metadata are indexed regardless of the'
      . ' exclusion list, however users won\'t be able to match against these documents\' content.', array(), array('context' => 'gofast:gofast_search'))
      . '<br /><br />'
  );

  $form['indexing']['index'] = array(
    '#title' => t('Content Indexing', array(), array('context' => 'gofast:gofast_search')),
    '#type' => 'fieldset',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#attributes'=> array('class' => array('mt-5')),
    '#description' => t('Some documents might be excluded from the index if they are the source of critical errors.'
      . ' Gofast won\'t reattempt to index such documents until an action is taken, meaning they are not searchable.', array(), array('context' => 'gofast:gofast_search'))
      . '<br /><br />'
  );

  // Define actions.
  $actions = array(
    'clear' => array(
      'default' => array(
        'path' => 'gofast-search/manage-excluded',
        'info' => array(
          'extraction' => t('Clear the exclusion list: Gofast will automatically reattempt to extract documents\' '
                          .'content at the next indexing job (i.e. the next time a document is updated).', array(), array('context' => 'gofast:gofast_search')),
          'index' => t('Clear the exclusion list: Gofast will automatically reattempt indexing jobs the next time a document is updated.', array(), array('context' => 'gofast:gofast_search'))
        ),
        'label' => t('Clear List', array(), array('context' => 'gofast:gofast_search')),
        'args' => array('nid' => 0, 'queue' => 0),
//        'btncls' => 'btn-danger'
      ),
      'node' => array(
        'info' => t('Remove the document from the exclusion list', array(), array('context' => 'gofast:gofast_search')),
        'label' => t('Clear', array(), array('context' => 'gofast')),
        'args' => array('nid' => '%', 'queue' => 0),
      )
    ),
    'reindex' => array(
      'default' => array(
        'path' => 'gofast-search/manage-excluded',
        'info' => t('Clear the exclusion list and queue all related documents for reindexing.', array(), array('context' => 'gofast:gofast_search')),
        'label' => t('Clear & Reindex', array(), array('context' => 'gofast:gofast_search')),
        'args' => array('nid' => 0, 'queue' => 1),
//        'btncls' => 'btn-info'
      ),
      'node' => array(
        'info' => t('Remove the document from the exclusion list, and queue it for reindexing', array(), array('context' => 'gofast:gofast_search')),
        'label' => t('Reindex', array(), array('context' => 'gofast:gofast_search')),
        'args' => array('nid' => '%', 'queue' => 1),
      )
    )
  );

  foreach ($solr_logs as $type => $log) {
    if (!count($log)) {
      $form['indexing'][$type]['#description'] .= '<em>' . t('There is currently not any document in the exclusion list.', array(), array('context' => 'gofast:gofast_search')) . '</em>';
      continue;
    }

    $rows = array();

    foreach ($actions as $name => $action) {
      $default = $action['default'];
      $path = $default['path'] . '/' . implode('/', array($type) + $default['args']);
      $info = is_array($default['info'])  ? $default['info'][$type] : $default['info'];
      $cls = isset($default['btncls']) ? $default['btncls'] : '';
      $rows[] = array(
        array('data' => $info, 'class' => 'gofast-info'),
        array('data' => gofast_button($default['label'], $path, $cls, NULL), 'class' => 'gofast-action')
      );
    }

    $info = t('You can manage the list of excluded documents in the section below.', array(), array('context' => 'gofast:gofast_search'));
    $form['indexing'][$type]['#description'] .=
            t('You can manage the list of excluded documents in the section below.', array(), array('context' => 'gofast:gofast_search')) .
            '<br /><br />' . theme('table', array('rows' => $rows)) .
            t('You can also manage documents individually from the "%list" below.', array('%list' => t('Exclusion List'), array('context' => 'gofast:gofast_search')));

    $list = array();
    $ids = array_keys($log);

    // Query database to prevent entity load with problematic nodes.
    $query = db_select('node', 'n');
    $query->leftJoin('field_data_' . GOFAST_TAXONOMY_FORMAT_FIELD, 'f', 'n.nid = f.entity_id AND f.entity_type = \'node\'');
    $query->condition('n.nid', $ids, 'IN')
          ->fields('n', array('nid', 'title'))
          ->fields('f', array('bundle', 'field_format_tid'));

    $formats = $query->execute()->fetchAllAssoc('nid');

    foreach ($ids as $nid) {
      if (!isset($formats[$nid]))
        continue;

      $dummy = (object) array(
          'nid' => $nid,
          'title' => $formats[$nid]->title,
          'field_format' => array(
            LANGUAGE_NONE => array(
              array('tid' => $formats[$nid]->field_format_tid)
            )
          )
      );

      $list[$nid] = array(array(
          'data' => theme('node_title', array('node' => $dummy)),
          'class' => 'gofast-info'
        )
      );

      foreach ($actions as $name => $action) {
        $options = $action['node'] + $action['default'];
        if (isset($options['args']['nid']) && $options['args']['nid'] === '%') {
          $options['args']['nid'] = $nid;
        }
        $path = $options['path'] . '/' . implode('/', array($type) + $options['args']);
        $cls = isset($options['btncls']) ? $options['btncls'] : '';

        $list[$nid][] = array(
          'data' => gofast_button($options['label'], $path, $cls, NULL, array('title' => $options['info'])),
          'class' => 'gofast-action'
        );
      }
    }

    $form['indexing'][$type]['list'] = array(
      '#type' => 'fieldset',
      '#title' => t('Exclusion List', array(), array('context' => 'gofast')),
      '#collapsible' => FALSE,
      '#collapsed' => FALSE,
      'markup' => array(
        '#markup' => theme('table', array('rows' => $list))
      )
    );

//        $form['indexing'][$type]['logs'] = array(
//            '#type' => 'fieldset',
//            '#title' => t('log'),
//            '#collapsible' => TRUE,
//            '#collapsed' => TRUE,
//            '#description' => array_to_html($extract_logs)
//        );
  }

  return $form;
}

/**
 * Informations about platform integrity check
 */
function gofast_admin_integrity_settings_form() {
  $form = array();

  $time_range = variable_get("gofast_integrity_time_range", true) ? t("We are in an integrity check run time.", array(), array("context" => 'gofast:gofast_integrity')): t("We are not in an integrity check run time.", array(), array("context" => 'gofast:gofast_integrity'));
  $run_state = variable_get("gofast_integrity_run_state", GOFAST_INTEGRITY_RUN_STATE_OFF);
  $current_week = variable_get('gofast_integrity_week_number', "//");

  switch($run_state){
      case GOFAST_INTEGRITY_RUN_STATE_OFF:
          $run_state = t("No results availables", array(), array("context" => 'gofast:gofast_integrity'));
          break;
      case GOFAST_INTEGRITY_RUN_STATE_FOLDERS:
          $run_state = t("Running folders integrity check", array(), array("context" => 'gofast:gofast_integrity'));
          break;
      case GOFAST_INTEGRITY_RUN_STATE_SPACES:
          $run_state = t("Running spaces integrity check", array(), array("context" => 'gofast:gofast_integrity'));
          break;
      case GOFAST_INTEGRITY_RUN_STATE_DOCUMENTS:
          $run_state = t("Running documents integrity check", array(), array("context" => 'gofast:gofast_integrity'));
          break;
      case GOFAST_INTEGRITY_RUN_STATE_RESULTS:
          $run_state = t("Results of this week are ready", array(), array("context" => 'gofast:gofast_integrity'));
          break;
      default:
          break;
  }

  $status = theme('gofast_integrity_status', array(
      'run_state' => $run_state,
      'time_range' => $time_range,
      'current_week' => $current_week
  ));

  $form['status'] = array(
    '#title' => t("Status", array(), array('context' => 'gofast:gofast_integrity')),
    '#type' => 'fieldset',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE
  );

  $form['status']['content'] = array(
    '#type' => 'item',
    "#markup" => $status,
  );

    $invalid_folders = variable_get("gofast_integrity_invalid_folders", array());
    $invalid_spaces = variable_get("gofast_integrity_invalid_spaces", array());
    $invalid_documents = variable_get("gofast_integrity_invalid_documents", array());

    $results_folders = theme('gofast_integrity_results', array(
        'results' => $invalid_folders,
    ));

    $results_spaces = theme('gofast_integrity_results', array(
        'results' => $invalid_spaces,
    ));

    $results_documents = theme('gofast_integrity_results', array(
        'results' => $invalid_documents,
    ));

    $form['results'] = array(
      '#title' => t("Results", array(), array('context' => 'gofast:gofast_integrity')),
      '#type' => 'fieldset',
      '#label' => count($invalid_folders) + count($invalid_spaces) + count($invalid_documents) . "oui",
      '#collapsible' => FALSE,
      '#collapsed' => FALSE
    );

    $markup = '<i class="fa fa-search" style="color: #c0392b; margin-right: 10px;"></i> ';
    $markup .= count($invalid_folders) + count($invalid_spaces) + count($invalid_documents) . " ";
    $markup .= t("identified integrity issues", array(), array('context' => 'gofast:gofast_integrity'));

    $form['results']['count'] = array(
        '#type' => 'item',
        "#markup" => $markup,
    );

    $form['results']['folders'] = array(
      '#title' => t("Folders integrity results", array(), array('context' => 'gofast:gofast_integrity')),
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#keen-accordion' => TRUE,
    );

    $form['results']['folders']['content'] = array(
        '#type' => 'item',
        "#markup" => $results_folders,
    );

    $form['results']['spaces'] = array(
      '#title' => t("Spaces integrity results", array(), array('context' => 'gofast:gofast_integrity')),
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#keen-accordion' => TRUE,
    );

    $form['results']['spaces']['content'] = array(
        '#type' => 'item',
        "#markup" => $results_spaces,
    );

    $form['results']['documents'] = array(
      '#title' => t("Documents integrity results", array(), array('context' => 'gofast:gofast_integrity')),
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#keen-accordion' => TRUE,
    );

    $form['results']['documents']['content'] = array(
        '#type' => 'item',
        "#markup" => $results_documents,
    );

  return $form;
}

/**
 * Add LDAP settings to the configuration form.
 */
function gofast_admin_ldap_settings_form() {
  include_once 'gofast_ldap/gofast_ldap.admin.inc';
  $form = array();
  ldap_servers_module_load_include('php', 'ldap_servers', 'LdapServerAdmin.class');
  module_load_include('inc', 'gofast_ldap', 'gofast_ldap.settings');

  $form['ldap_settings'] = array(
    '#title' => t('Server settings', array(), array('context' => 'gofast:gofast_ldap')),
    '#type' => 'fieldset',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE
  );

  $sid = GOFAST_LDAP_EXT_SERVER;

  // Load configuration.
  $server = new LdapServerAdmin($sid);
  if ($server->sid !== $sid) {
    // No defaults instance found, create one on the fly. Keep the operation
    // silent for non-admin users.
    $silent = $GLOBALS['user']->uid != 1;
    gofast_ldap_server_create($sid, $silent);
    $server = new LdapServerAdmin($sid);
  }

  // Get LDAP modules settings.
  $settings = $server->drupalForm('edit');

  // Don't expose all fields if not admin.
  if ($GLOBALS['user']->uid != 1) {
    $form_fields = gofast_ldap_settings_form_fields();
    $settings = array_intersect_key($settings, $form_fields);
    foreach ($form_fields as $category => $_settings) {
      $settings[$category] = array_intersect_key($settings[$category], $form_fields[$category]);
    }

    // Server identifier is exposed to ensure form is submitted with the correct
    // value, however we don't show it to adms.
    $settings['server']['sid']['#type'] = 'hidden';

    // Display Service Account help block (string taken from LDAP Server module).
    $settings['bind_method']['binding_service_acct']['#markup'] = '<label>'.t('Service Account', array(), array('context' => 'gofast:gofast_ldap')).'</label>
          <div class="help-block">'
            .t('Some LDAP configurations prohibit or restrict
            the results of anonymous searches. These LDAPs require a DN/password
            pair for binding. For security reasons, this pair should belong to an
            LDAP account with stripped down permissions. This is also required for
            provisioning Drupal accounts!', array(), array('context' => 'gofast:gofast_ldap'))
        .'</div>'
    ;

    // Set password default value here to avoid embarrassing user that may
    // feel compelled to reset the connection password every time he would
    // reload the page, save settings or test the server conection.
    $settings['bind_method']['bindpw']['#default_value'] = $server->bindpw;

    // Values for this field should hold in 1 or 2 rows in most cases.
    $settings['users']['basedn']['#rows'] = 2;

    // Prevent use of 'default' type since we use a fallback mechanism for server
    // settings that is based on a given type with required attributes mapped.
    unset($settings['server']['ldap_type']['#options']['default']);
  }

  $form['ldap_settings'] += $settings;

  // These array will hold form keys needed to test the server connection status.
  $ldapServerPropList = array(); // hold keys for deferred & asynchronous test.
  $server_settings = array(); // hold keys & default value to test synchronously.
  _iterate_form($form['ldap_settings'], function ($element, $key) use (&$ldapServerPropList, &$server_settings) {
    $ldapServerPropList[] = $key;
    if (isset($element['#default_value'])) {
      $server_settings[$key] = $element['#default_value'];
    }
  });

  // Attempt to bind synchronously with the current saved settings, so we can
  // display server status.
  $server_status = gofast_ldap_admin_test_connection($server_settings, FALSE);
  $status_msg = $server_status ? t('Connection performed successfully.', array(), array('context' => 'gofast:gofast_ldap')) : t('Connection failed.', array(), array('context' => 'gofast:gofast_ldap'));

  // Allows connection test on the fly (without having to submit the form).
  $form['ldap_settings']['test_connection'] = array(
    '#description' => t('Attempt to bind to the server using the current configuration without having to save it.', array(), array('context' => 'gofast:gofast_ldap')),
    '#markup' => gofast_button(t('Test connection'), NULL, 'btn-info', '.glyphicon-globe', array('id' => 'ldap-connection-test')),
    '#suffix' => '<span id="ldap-connection-status" style="float:right;">'. $status_msg .'</span>',
    '#attached' => array(
      'js' => array(
        array(
          'data' => array('gofast_ldap' => array('ldapServerPropList' => $ldapServerPropList)),
          'type' => 'setting'
        ),
        array(
          'data' => drupal_get_path('module', 'gofast_ldap') . '/gofast_ldap.js',
          'type' => 'file',
          'scope' => 'footer',
          'weight' => 5
        )
      )
    )
  );

  // SASL delegated Authentication. Connection to the company's directory is
  // required for this field to be enabled, except if already enabled : in this
  // case if server binding fails, set a message to let adm consider disabling
  // SASL authentication.
  if (!$server_status && $sasl = variable_get('gofast_sasl_auth', 0)) {
    $msg = t('SASL Authentication is enabled but your company\' LDAP server can\'t be reach.'
    . ' You should consider deactivating the feature until the server is up again or users won\'t be able to authenticate.', array(), array('context' => 'gofast:gofast_ldap'));
    drupal_set_message($msg, 'error');
  }
  if(!variable_get("gofast_sasl_switching", FALSE)){
      $form['sasl_delegation'] = array(
        '#title' => t('SASL Authentication', array(), array('context' => 'gofast:gofast_ldap')),
        '#type' => 'fieldset',
        '#collapsible' => FALSE,
        '#collapsed' => FALSE,
        'sasl_auth' => array(
          '#type' => 'checkbox',
          '#title' => t('Delegate authentication to LDAP server.', array(), array('context' => 'gofast:gofast_ldap')),
          '#default_value' => $sasl = variable_get('gofast_sasl_auth', 0),
          '#disabled' => !($server_status || $sasl),
          '#description' => t('Activating SASL delegated Authentication permit users to log into GoFast using their company\'s directory credentials (Active Directory, OpenLDAP...).'
            . ' Notice that SASL authentication only works with users that are registered into the company\'s directory.'
            . ' As an administrator, you can also switch delegated authentication on/off for a specific user directly from the account edit form.'
            . ' Make sure that LDAP parameters are suitable so that this functionality can be turned on.'
          , array(), array('context' => 'gofast:gofast_ldap'))
        ) /** @todo : validate the set of users returned by gofast_ldap_sasl_get_users() & add details here. */
      );
  }else{
      $form['sasl_delegation'] = array(
        '#title' => t('SASL Authentication', array(), array('context' => 'gofast:gofast_ldap')),
        '#type' => 'fieldset',
        '#collapsible' => FALSE,
        '#collapsed' => FALSE,
        'sasl_auth' => array(
          '#type' => 'checkbox',
          '#title' => t('Delegate authentication to LDAP server.', array(), array('context' => 'gofast:gofast_ldap')),
          '#default_value' => TRUE,
          '#disabled' => TRUE,
          '#description' => t("SASL switching operation is in progress, this operation may take a while.", array(), array('gofast:gofast_ldap'))
        ) /** @todo : validate the set of users returned by gofast_ldap_sasl_get_users() & add details here. */
      );
  }
  if(!($server_status || $sasl)){
    $form['sasl_delegation']["#attributes"] = array('class' => array('gofast_display_none'));
  }
  $form['sasl_delegation']['#attributes']['class'][] = 'mt-5';
  $sync_settings = variable_get('gofast_directory_sync_config', array());
  $sync = variable_get('gofast_directory_sync', FALSE);

  $form['ldap_sync'] = array(
    '#title' => t('Directory synchronization', array(), array('context' => 'gofast:gofast_ldap')),
    '#type' => 'fieldset',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );

  if(!(($sasl&&$server_status) || $sync)){
    $form['ldap_sync']["#attributes"] = array('class' => array('gofast_display_none'));
  }

  $form['ldap_sync']['enable_sync'] = array(
    '#type' => 'checkbox',
    '#title' => t('Synchronize @site_name with the configured directory.', array('@site_name' => variable_get('site_name', 'GoFAST')), array('context' => 'gofast:gofast_ldap')),
    '#default_value' => $sync = variable_get('gofast_directory_sync', 0),
    '#disabled' => !(($server_status&&$sasl) || $sync),
    '#description' => t("Activating directory synchronization will synchronize the accounts of this platform with the remote directory.<br /><br /><strong>Please note</strong> that the non authentication delegated accounts won't be automatically blocked or unblock from this platform.", array(), array('context' => 'gofast:gofast_ldap'))
  );

  $form['ldap_sync']['configuration'] = array(
    '#title' => t('Configuration', array(), array('context' => 'gofast:gofast_ldap')),
    '#type' => 'fieldset',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );

  $form['ldap_sync']['configuration']['interval'] = array(
    '#title' => t('Synchronization interval', array(), array('context' => 'gofast:gofast_ldap')),
    '#type' => 'select',
    '#default_value' => !empty($sync_settings['interval']) ? $sync_settings['interval']:'dayly',
    '#disabled' => !(($server_status&&$sasl) || $sync),
    '#description' => t('The frequency of the synchronization', array(), array('context' => 'gofast:gofast_ldap')),
    '#options' => array(
      'twiceaday' => t('Twice a day', array(), array('context' => 'gofast:gofast_ldap')),
      'dayly' => t('Every day', array(), array('context' => 'gofast:gofast_ldap')),
      'weekly' => t('Every week', array(), array('context' => 'gofast:gofast_ldap')),
      'monthly' => t('Every month', array(), array('context' => 'gofast:gofast_ldap')),
    ),
    '#required' => TRUE,
  );

  $form['ldap_sync']['fields_mapping'] = array(
    '#title' => t('Fields mapping', array(), array('context' => 'gofast:gofast_ldap')),
    '#type' => 'fieldset',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );

  $form['ldap_sync']['fields_mapping']['uid'] = array(
    '#title' => t('Username *', array(), array('context' => 'gofast:gofast_ldap')),
    '#type' => 'textfield',
    '#default_value' => $sync_settings['mapping']['uid'],
    '#disabled' => !(($server_status&&$sasl) || $sync),
    '#description' => t('The unique identifier of the user, usually associated to samAccountName for an Active Directory.', array(), array('context' => 'gofast:gofast_ldap')),
  );

  $form['ldap_sync']['fields_mapping']['firstname'] = array(
    '#title' => t('First name', array(), array('context' => 'gofast:gofast_ldap')),
    '#type' => 'textfield',
    '#default_value' => $sync_settings['mapping']['firstname'],
    '#disabled' => !($server_status || $sync),
  );

  $form['ldap_sync']['fields_mapping']['lastname'] = array(
    '#title' => t('Last name', array(), array('context' => 'gofast:gofast_ldap')),
    '#type' => 'textfield',
    '#default_value' => $sync_settings['mapping']['lastname'],
    '#disabled' => !($server_status || $sync),

  );
  $form['ldap_sync']['fields_mapping']['fullname'] = array(
    '#title' => t('Full name', array(), array('context' => 'gofast:gofast_ldap')),
    '#type' => 'textfield',
    '#default_value' => $sync_settings['mapping']['fullname'],
    '#disabled' => !($server_status || $sync),
    '#description' => t("If this field is mapped, first name and last name fields won't be used.", array(), array('context' => 'gofast:gofast_ldap')),

  );
  $form['ldap_sync']['fields_mapping']['email'] = array(
    '#title' => t('E-mail address *', array(), array('context' => 'gofast:gofast_ldap')),
    '#type' => 'textfield',
    '#default_value' => $sync_settings['mapping']['email'],
    '#disabled' => !($server_status || $sync),
  );
  $form['ldap_sync']['fields_mapping']['main_orga'] = array(
    '#title' => t('Main organisation', array(), array('context' => 'gofast:gofast_ldap')),
    '#type' => 'textfield',
    '#default_value' => $sync_settings['mapping']['main_orga'],
    '#disabled' => !($server_status || $sync),
    '#description' => t("If an organisation in the platform matches exactly this field, the user will be added in this organisation as it's main organisation.", array(), array('context' => 'gofast:gofast_ldap')),

  );
  $form['ldap_sync']['fields_mapping']['title'] = array(
    '#title' => t('Function', array(), array('context' => 'gofast:gofast_ldap')),
    '#type' => 'textfield',
    '#default_value' => $sync_settings['mapping']['title'],
    '#disabled' => !($server_status || $sync),

  );
  $form['ldap_sync']['fields_mapping']['company'] = array(
    '#title' => t('Entity', array(), array('context' => 'gofast:gofast_ldap')),
    '#type' => 'textfield',
    '#default_value' => $sync_settings['mapping']['company'],
    '#disabled' => !($server_status || $sync),

  );
  $form['ldap_sync']['fields_mapping']['phone'] = array(
    '#title' => t('Phone number', array(), array('context' => 'gofast:gofast_ldap')),
    '#type' => 'textfield',
    '#default_value' => $sync_settings['mapping']['phone'],
    '#disabled' => !($server_status || $sync),

  );
  $form['ldap_sync']['fields_mapping']['mobile_phone'] = array(
    '#title' => t('Mobile phone number', array(), array('context' => 'gofast:gofast_ldap')),
    '#type' => 'textfield',
    '#default_value' => $sync_settings['mapping']['mobile_phone'],
    '#disabled' => !($server_status || $sync),

  );

  //Filters
  $form['ldap_sync']['filters'] = array(
    '#title' => t('Filters', array(), array('context' => 'gofast:gofast_ldap')),
    '#type' => 'fieldset',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );

  $filters = "";
  foreach($sync_settings['filters'] as $filter){
      $filters .= "$filter[0]=$filter[1]\n";
  }
  $form['ldap_sync']['filters']['filters'] = array(
    '#title' => t('Filters list', array(), array('context' => 'gofast:gofast_ldap')),
    '#type' => 'textarea',
    '#default_value' => $filters,
    '#disabled' => !(($server_status&&$sasl) || $sync),
    '#description' => t('A list of filters separated by newlines with possible combination of conditions.', array(), array('context' => 'gofast:gofast_ldap')) . "<br />" . t('Example :', array(), array('context' => 'gofast:gofast_ldap')) . "<br /><br />employeetype=active<br />o=CEO-Vision|o=GoFAST<br />ou!=SI",
  );

  if($sync){
    //Gathering stats
    $sync_progress = variable_get('gofast_ldap_processing_sync', 0);
    $last_sync = variable_get('gofast_ldap_last_sync', null);

    switch($sync_settings['interval']){
      case 'monthly':
        $next_sync = (intval($last_sync)+2628000);
        break;
      case 'weekly':
        $next_sync = (intval($last_sync)+604800);
        break;
      case 'dayly':
        $next_sync = (intval($last_sync)+86400);
        break;
      case 'twiceaday':
        $next_sync = (intval($last_sync)+43200);
        break;
    }
    $stats = theme('gofast_sync_status', array(
      'sync_progress' => $sync_progress,
      'last_sync' => $last_sync,
      'next_sync' => $next_sync,
    ));
    $form['ldap_sync']['sync_stats'] = array(
      '#title' => t('Synchronization status', array(), array('context' => 'gofast:gofast_ldap')),
      '#type' => 'fieldset',
      '#collapsible' => FALSE,
      '#collapsed' => FALSE,
    );
    $form['ldap_sync']['sync_stats']['content'] = array(
      '#type' => 'item',
      "#markup" => $stats,
    );

    if(!$sync_progress){
      $form['ldap_sync']['force_sync'] = array(
      '#type' => 'markup',
      '#markup' => '<button type="button" id="edit-force-sync" name="op" value="'.t('Synchronization', array(), array('context' => 'gofast:gofast_ldap')).'" class="btn btn-sm btn-default">Synchronization</button>'
      );
    }
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save', array(), array('context' => 'gofast')),
  );
  return $form;
}

/**
 * LDAP settings (from Gofast admin form) validate callback
 */
function gofast_admin_ldap_settings_form_validate($form, &$form_state) {
  include_once 'gofast_ldap/gofast_ldap.admin.inc';
  // Server port.
  if (!preg_match('/^[0-9]+$/', trim($form_state['values']['port']))) {
    form_set_error('port', t('The LDAP port number must be an integer.', array(), array('context' => 'gofast:gofast_ldap')));
  }

  // SASL Authentication.
  $old_state = variable_get('gofast_sasl_auth', FALSE);
  $state = $form_state['values']['sasl_auth'];
  if ($state && !$old_state && !variable_get("gofast_sasl_switching", FALSE)) {
    // Collect server settings & check server connection.
    $form_fields = array_flatten(gofast_ldap_settings_form_fields());
    $settings = array_intersect_key($form_state['values'], $form_fields);
    $status = gofast_ldap_admin_test_connection($settings, FALSE);
    if (!$status) {
      form_set_error('sasl_auth', t('SASL delegated Authentication : please make sure your LDAP settings are suitable '
                      .' before activating this functionality, otherwise you should consider disabling it.',
                      array(), array('context' => 'gofast:gofast_ldap')));
      form_set_error('general', t('LDAP Server : The current configuration is not compatible with the SASL Authentication functionality.',
                      array(), array('context' => 'gofast:gofast_ldap')));
    }
  }

  //Synchronisation parameters check
  if($form_state['values']['enable_sync'] == 1){
    //Check mendatory fields
    if(empty($form_state['values']['uid'])){
      form_set_error('uid', t("Username is a mandatory field", array(), array('context' => 'gofast:gofast_ldap')));
      return;
    }
    if(empty($form_state['values']['email'])){
      form_set_error('email', t("E-mail address is a mandatory field", array(), array('context' => 'gofast:gofast_ldap')));
      return;
    }
  }
}

/**
 * LDAP settings (from Gofast admin form) submit callback
 */
function gofast_admin_ldap_settings_form_submit(&$form, &$form_state) {
  include_once 'gofast_ldap/gofast_ldap.admin.inc';
  $form_fields = array_flatten(gofast_ldap_settings_form_fields());
  $settings = array_intersect_key($form_state['values'], $form_fields);

  // Merge in defaults settings (given server type).
  $defaults = gofast_ldap_server_defaults($settings['ldap_type']);
  $settings += $defaults;

  // Submit the form using the server method.
  $server = new LdapServerAdmin($settings['sid']);
  $server->drupalFormSubmit('edit', $settings);

  // SASL Authentication
  $old_state = variable_get('gofast_sasl_auth', FALSE);
  $state = $form_state['values']['sasl_auth'];
  if (!!$state === !$old_state && !variable_get("gofast_sasl_switching", FALSE)) {
    // Switch SASL Authentication ON/OFF. If an error occurs during the process,
    // state might be reverted if no user were affected, log are always updated.
    variable_set("gofast_sasl_switching", TRUE);

    //Unable to drupal_get_form the ldap settings form here so here is a workaround
    $sasl_switching_info = t("SASL switching operation is in progress, this operation may take a while.", array(), array('gofast:gofast_ldap'));
    $output = array(
        "error" => null,
        "html" => '<div class="loader-replicate"></div> <span id="ldap-sasl-switching">' . $sasl_switching_info . "</span>"
    );
    print json_encode($output);

    gofast_ldap_sasl_auth_switch_async($state);
  }else{
  }

  //Synchronisation parameters save
  if($form_state['values']['enable_sync']){
    variable_set('gofast_directory_sync', 1);

    $sync_config = array();
    $sync_config['interval'] = $form_state['values']['interval'];
    $sync_config['mapping']['uid'] = $form_state['values']['uid'];
    $sync_config['mapping']['firstname'] = $form_state['values']['firstname'];
    $sync_config['mapping']['lastname'] = $form_state['values']['lastname'];
    $sync_config['mapping']['fullname'] = $form_state['values']['fullname'];
    $sync_config['mapping']['email'] = $form_state['values']['email'];
    $sync_config['mapping']['main_orga'] = $form_state['values']['main_orga'];
    $sync_config['mapping']['title'] = $form_state['values']['title'];
    $sync_config['mapping']['company'] = $form_state['values']['company'];
    $sync_config['mapping']['phone'] = $form_state['values']['phone'];
    $sync_config['mapping']['mobile_phone'] = $form_state['values']['mobile_phone'];

    $filters = $form_state['values']['filters'];
    $filters = explode("\n", $filters);
    $saved_filters = array();
    //Parse selected filters
    foreach($filters as &$filter){
        if(!empty($filter)){
            $filter = str_replace("\n", "", $filter);
            $filter = str_replace("\r", "", $filter);
            $filter = str_replace("\t", "", $filter);
            $filter = explode("=", $filter);
            if(count($filter) > 1){
                $filter[0] = strtolower($filter[0]);
                $saved_filters[] = array(
                    array_shift($filter),
                    implode("=", $filter)
                );
            }
        }
    }

    $sync_config['filters'] = $saved_filters;

    variable_set('gofast_directory_sync_config', $sync_config);
  }else{
    variable_set('gofast_directory_sync', 0);
  }
}

/**
 * Add Users settings to the configuration form.
 */
function gofast_admin_users_settings_form() {
  $form = array();
  
  $form['user_standby'] = array(
    '#title' => t('Enable standby mode for new users', array(), array('context' => 'gofast')),
    '#type' => 'fieldset',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE
  );

  $form['user_standby']['standby_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t("Enable 'User-support' Profile Validation for User creation", array(), array('context' => 'gofast')),
    '#default_value' => variable_get("gofast_standby_enabled", false),
    '#description' => t("If checked, users will be create in standby, and a 'User-support' validation will be necessarly for activating this new accounts.", array(), array('context' => 'gofast'))
  );

  $form['user_form'] = array(
    '#title' => t('Default configuration of the user form', array(), array('context' => 'gofast')),
    '#type' => 'fieldset',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE
  );

  //Retrieve saved user form configuration
  $default_user_form_configuration = array(
      'sasl_auth' => variable_get('gofast_sasl_auth', 0),
      'extranet' => FALSE,
      'broadcaster' => FALSE,
      'comment_restricted' => FALSE,
      'default_role' => "1",
      'notify' => 1
  );
  $user_form_defaults = variable_get("user_form_defaults", $default_user_form_configuration);

  $form['user_form']['sasl_auth'] = array(
    '#type' => 'checkbox',
    '#title' => t("SASL Authentication", array(), array('context' => 'gofast')),
    '#default_value' => $user_form_defaults['sasl_auth'],
    '#description' => t("When activated, users authentication is delegated to the configured LDAP server.", array(), array('context' => 'gofast'))
  );

  $form['user_form']['extranet'] = array(
    '#type' => 'checkbox',
    '#title' => t("External user", array(), array('context' => 'gofast')),
    '#default_value' => $user_form_defaults['extranet'],
    '#description' => t("Depending on global settings, administrators can revoke permissions to external users so they can't access non-external spaces regardless of their profiles.", array(), array('context' => 'gofast'))
  );

  $form['user_form']['broadcaster'] = array(
    '#type' => 'checkbox',
    '#title' => t("Broadcaster", array(), array('context' => 'gofast')),
    '#default_value' => $user_form_defaults['broadcaster'],
    '#description' => t("Broadcaster are allowed to broadcast any content they can access in any spaces including spaces in which they are not a member, regardless of their profiles and permissions.", array(), array('context' => 'gofast'))
  );

  $form['user_form']['comment_restricted'] = array(
    '#type' => 'checkbox',
    '#title' => t("Restricted comments", array(), array('context' => 'gofast')),
    '#default_value' => $user_form_defaults['comment_restricted'],
    '#description' => t("Restricted users won't be able to post public comments and make public annotations if they haven't administrative rights on a content.", array(), array('context' => 'gofast'))
  );

  $form['user_form']['default_role'] = array(
    '#type' => 'radios',
    '#options' => array(
        //Removing the possibility to be default admin in collaborative spaces
        //'0' => t("Administrator", array(), array('gofast:gofast_user')),
        '1' => t("Contributor", array(), array('gofast:gofast_user')),
        '2' => t("Read Only", array(), array('gofast:gofast_user'))
    ),
    '#title' => t("Default role in collaborative spaces", array(), array('context' => 'gofast')),
    '#default_value' => $user_form_defaults['default_role'],
    '#description' => t("Default role in collaborative spaces when creating a user and when a user in a sub-space is automatically added to the upper space.", array(), array('context' => 'gofast'))
  );

  $form['user_form']['notify'] = array(
    '#type' => 'checkbox',
    '#title' => t("New account notification", array(), array('context' => 'gofast')),
    '#default_value' => $user_form_defaults['notify'],
    '#description' => t("Notify a user when creating it's account.", array(), array('context' => 'gofast'))
  );

  $password_policy_settings = gofast_ldap_get_password_policy_settings();

  $min_password_lifetime_days = (int) $password_policy_settings["min_password_lifetime"]/60/60/24;
  $max_password_lifetime_days = (int) $password_policy_settings["max_password_lifetime"]/60/60/24;

   $form["password_policy"] = array(
        '#title' => t('Password policy', array(), array('context' => 'gofast:gofast_ldap')),
        '#type' => 'fieldset',
        '#collapsible' => FALSE,
        '#collapsed' => FALSE,
        'password_policy_history_limit' => array(
            '#type' => 'textfield',
            '#title' => t("Number of passwords stored into history", array(), array('context' => 'gofast:gofast_ldap')),
            '#default_value' => $password_policy_settings["history_limit"],
            '#description' => t("Users can't use again a password stored into this history", array(), array('context' => 'gofast:gofast_ldap'))
        ),
       'password_policy_min_password_length' => array(
            '#type' => 'textfield',
            '#attributes' => array(
                ' type' => 'number',
            ),
            '#title' => t("Minimum password length", array(), array('context' => 'gofast:gofast_ldap')),
            '#default_value' => $password_policy_settings["min_password_length"],
            '#description' => t("Minimum password length", array(), array('context' => 'gofast:gofast_ldap'))
        ),
       'password_policy_min_password_lifetime' => array(
            '#type' => 'textfield',
            '#attributes' => array(
                ' type' => 'number',
            ),
            '#title' => t("Minimum password lifetime", array(), array('context' => 'gofast:gofast_ldap')),
            '#default_value' => $min_password_lifetime_days,
            '#description' => t("Minium password lifetime ( in days )", array(), array('context' => 'gofast:gofast_ldap'))
        ),
       'password_policy_max_password_lifetime' => array(
            '#type' => 'textfield',
            /*'#attributes' => array(
                ' type' => 'number',
            ),*/
            '#title' => t("Maximum password lifetime", array(), array('context' => 'gofast:gofast_ldap')),
            '#default_value' => $max_password_lifetime_days,
            '#description' => t("Maximum password lifetime ( in days )", array(), array('context' => 'gofast:gofast_ldap'))
        ),
    );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save', array(), array('context' => 'gofast')),
  );
  return $form;
}

/**
 * Users settings (from Gofast admin form) validate callback
 */
function gofast_admin_users_settings_form_validate($form, &$form_state) {
     //validate password settings
    $min_password_lifetime = $form_state['values']["password_policy_min_password_lifetime"];
    $max_password_lifetime = $form_state['values']["password_policy_max_password_lifetime"];

    if(!is_numeric( $min_password_lifetime)){
                 form_set_error('password_policy_min_password_lifetime', t('Minimum password lifetime must be an integer', array(), array('context' => 'gofast:gofast_ldap')));
    }

    if(!is_numeric($max_password_lifetime)){
                 form_set_error('password_policy_max_password_lifetime', t('Maximum password lifetime must be an integer', array(), array('context' => 'gofast:gofast_ldap')));
    }
    if($min_password_lifetime > $max_password_lifetime){
         form_set_error('password_policy_min_password_lifetime', t('Minimum password lifetime must be smaller than Maximum password lifetime', array(), array('context' => 'gofast:gofast_ldap')));
    }

    return;
}

/**
 * Users settings (from Gofast admin form) submit callback
 */
function gofast_admin_users_settings_form_submit(&$form, &$form_state) {
    $user_form_defaults = $form_state['values'];
    $user_form_defaults["notify"] = TRUE;

    unset($user_form_defaults['submit']);
    unset($user_form_defaults['form_build_id']);
    unset($user_form_defaults['form_token']);
    unset($user_form_defaults['form_id']);
    unset($user_form_defaults['op']);

    //unset password policy settings before save
    $min_password_lifetime_seconds = $user_form_defaults["password_policy_min_password_lifetime"]*60*60*24;
    $max_password_lifetime_seconds = $user_form_defaults["password_policy_max_password_lifetime"]*60*60*24;

    $ldap_policy_settings = array("history_limit" => $user_form_defaults['password_policy_history_limit'], "min_password_length" => $user_form_defaults['password_policy_min_password_length'],
                                  "min_password_lifetime" => $min_password_lifetime_seconds, "max_password_lifetime" => $max_password_lifetime_seconds);

    gofast_ldap_set_password_policy_settings($ldap_policy_settings);
    unset($user_form_defaults['password_policy_history_limit']);
    unset($user_form_defaults['password_policy_min_password_length']);
    unset($user_form_defaults['password_policy_min_password_lifetime']);
    unset($user_form_defaults['password_policy_max_password_lifetime']);

    variable_set("user_form_defaults", $user_form_defaults);
    variable_set("gofast_standby_enabled", $form_state['values']['standby_enabled']);
}

/**
 * Add Documents settings to the configuration form.
 */
function gofast_admin_documents_settings_form() {
  $form = array();

  //Retrieve saved documents form configuration
  $default_documents_form_configuration = array(
      'ticket' => 1,
      'ticket_path_length' => 200,
      'gofast_onlyoffice_ro_preview' => FALSE,
      'edit_libreoffice_documents' => FALSE,
      'xss_whitelist' => [],
  );
  $documents_form_defaults = variable_get("documents_form_defaults", $default_documents_form_configuration);

  $form['documents_edition_form'] = array(
    '#title' => t('Document edition', array(), array('context' => 'gofast')),
    '#type' => 'fieldset',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE
  );

  $form['documents_edition_form']['ticket'] = array(
    '#type' => 'checkbox',
    '#title' => t("Use GoFAST session ticket", array(), array('context' => 'gofast')),
    '#default_value' => $documents_form_defaults['ticket'],
    '#description' => t("Using GoFAST session ticket allows the users to don't have to enter their credentials to edit a document locally. This may cause issue with Windows path length limitations.", array(), array('context' => 'gofast'))
  );

  $form['documents_edition_form']['ticket_path_length'] = array(
    '#type' => 'textfield',
    '#attributes' => array(
        ' type' => 'number',
    ),
    '#title' => t("Maximum path length to use the GoFAST session ticket", array(), array('context' => 'gofast')),
    '#default_value' => $documents_form_defaults['ticket_path_length'],
    '#description' => t("If GoFAST session ticket is enabled, adapt this setting to fix the Windows path length limitations.", array(), array('context' => 'gofast'))
  );

  $form['documents_edition_form']['edit_libreoffice_documents'] = array(
    '#type' => 'checkbox',
    '#title' => t("Use LibreOffice protocol to open documents", array(), array('context' => 'gofast')),
    '#default_value' => $documents_form_defaults['edit_libreoffice_documents'],
    '#description' => t("Check this if Microsoft Office has never been installed so ms protocols are not available to open documents", array(), array('context' => 'gofast'))
  );

  $form['documents_preview_form'] = array(
    '#title' => t('Document preview', array(), array('context' => 'gofast')),
    '#type' => 'fieldset',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE
  );

  $form['documents_preview_form']['gofast_onlyoffice_ro_preview'] = array(
    '#type' => 'checkbox',
    '#title' => t("Preview documents using OnlyOffice in read only mode", array(), array('context' => 'gofast')),
    '#default_value' => $documents_form_defaults['gofast_onlyoffice_ro_preview'],
  );

  $form['document_custom_date_field'] = array(
    '#title' => t('Custom date', array(), array('context' => 'gofast')),
    '#type' => 'fieldset',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE
  );

  $form['document_custom_date_field']['gofast_metadata_custom_date_label'] = array(
    '#type' => 'textfield',
    '#title' => t("Name of the custom date field", array(), array('context' => 'gofast')),
    '#default_value' => GOFAST_METADATA_CUSTOM_DATE_LABEL,
  );

  $form['documents_security'] = array(
    '#title' => t('Document security', array(), array('context' => 'gofast')),
    '#type' => 'fieldset',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE
  );

  foreach($documents_form_defaults['xss_whitelist'] as $nid){
    $node = node_load($nid);
    $xss_whitelist[] = gofast_ac_format_value_json('node', $node);
  }

  $form['documents_security']['xss'] = array(
    '#title' => t("XSS filtering whitelist", array(), array('context' => 'gofast')),
    '#type' => 'textfield',
    '#maxlength' => 999999,
    '#default_value' => json_encode($xss_whitelist),
    '#attributes' => array(
      // spaces and conferences descriptions may have xss bypassed as well
      'id' => 'edit-bundles-alfresco_item-article-conference',
      'class' => ['form-control-tags js-tagify'],
      'data-node' => '',
      'data-get-spaces' => '',
    ),
    '#name' => 'ac-list-tags-xss',
    '#description' => t("By default and for security reasons, a large amount of HTML tags are filtered in space's home pages, articles, document's summaries... For complex usages, you may want to have some pages to bypass this filter, you can add them here by typing the page's title.", array(), array('context' => 'gofast'))
  );

  if (!module_exists("gofast_community")) {
    $form['retention'] = array(
      '#title' => t('Retention', array(), array('context' => 'gofast')),
      '#type' => 'fieldset',
      '#collapsible' => FALSE,
      '#collapsed' => FALSE
    );
  
    $list_recipient = array();
    $recipients = array();
    if ( NULL != variable_get(GOFAST_RETENTION_PERIOD_RECIPIENTS_VAR) ) {
      $list_recipient = variable_get(GOFAST_RETENTION_PERIOD_RECIPIENTS_VAR);
  
      foreach($list_recipient as $recipient){
        $recipient_user =  user_load($recipient->id);
        $recipients[] = gofast_ac_format_value_json('user', $recipient_user);
      }
    }
  
    $form['retention']['ac-list-tags-list-recipients'] = array(
      '#type' => 'textfield',
      '#title' => t('Current list of mail recipients', array(), array('context' => 'gofast:gofast_retention')),
      '#default_value' => json_encode($recipients),
      '#id' => 'edit-field-tags',
      '#maxlength' => 999999,
      '#attributes' => [
        'class' => ['form-control-tags js-tagify'],
        'data-user' => '', // show ac users
      ],
    );
    $form['documents_external_links'] = array(
      '#title' => t('External links', array(), array('context' => 'gofast')),
      '#type' => 'fieldset',
      '#collapsible' => FALSE,
      '#collapsed' => FALSE
    );
    $form['documents_external_links']['enable_automatic_renaming'] = array(
      '#title' => t('Enable automatic renaming', array(), array('context' => 'gofast')),
      '#description' => t("If this option is enabled, http requests will be made from the server to retrieve the page title.", array(), array("context" => "gofast")),
      '#type' => 'checkbox',
      '#default_value' => variable_get("enable_automatic_external_link_title", true),
    );
    $form['documents_external_links']['allow_http'] = array(
      '#title' => t('Allow external links to redirect to http urls', array(), array('context' => 'gofast')),
      '#type' => 'checkbox',
      '#default_value' => variable_get("use_http_link", false),
    );
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save', array(), array('context' => 'gofast')),
  );

  return $form;
}

/**
 * Documents settings (from Gofast admin form) validate callback
 */
function gofast_admin_documents_settings_form_validate($form, &$form_state) {
    return;
}

/**
 * Documents settings (from Gofast admin form) submit callback
 */
function gofast_admin_documents_settings_form_submit(&$form, &$form_state) {
    $documents_form_defaults = $form_state['values'];

    unset($documents_form_defaults['submit']);
    unset($documents_form_defaults['form_build_id']);
    unset($documents_form_defaults['form_token']);
    unset($documents_form_defaults['form_id']);
    unset($documents_form_defaults['op']);

    //Custom fields
    variable_set("gofast_metadata_custom_date_label", $documents_form_defaults["gofast_metadata_custom_date_label"]);
    unset($documents_form_defaults['gofast_metadata_custom_date_label']);

    //XSS Filtering
    $input_xss = json_decode($form_state['input']['ac-list-tags-xss']);

    foreach($input_xss as $ac_content){
      $documents_form_defaults['xss_whitelist'][] = $ac_content->value;
    }

    variable_set("documents_form_defaults", $documents_form_defaults);

    if (!module_exists("gofast_commmunity")) {
      $recipients = $form_state['values']['ac-list-tags-list-recipients'];
      $array_dest = json_decode($recipients);
      if(count($array_dest) > 0){
        $json_list_recipients = array();
        foreach($array_dest as $dest_json){
          $account = user_load($dest_json->value);
          $account_obj = new stdClass();
          $account_obj->id = $dest_json->value;
          $account_obj->address = $account->mail;
          $account_obj->name = $account->name;
          $account_obj->type = "user";
          $json_list_recipients[] = $account_obj;
        }
        variable_set(GOFAST_RETENTION_PERIOD_RECIPIENTS_VAR, $json_list_recipients);
      }
    }
    variable_set("enable_automatic_external_link_title", $form_state['values']['enable_automatic_renaming']);
    variable_set("use_http_link", $form_state['values']['allow_http']);
}

/**
 * Add spaces settings to the configuration form.
 */
function gofast_admin_spaces_settings_form() {
  $form = array();

  $form['spaces_permissions'] = array(
    '#title' => t('Permissions', array(), array('context' => 'gofast')),
    '#type' => 'fieldset',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE
  );

  $spaces_defaults = gofast_admin_get_space_defaults();

  $public_count = db_select("node", 'n')
          ->fields('n', array('nid'))
          ->condition('type', 'public', '=')
          ->execute()
          ->fetchAll();
  $public_count = count($public_count);
  $form['spaces_permissions']['public_contrib'] = array(
    '#title' => t(' Contribute to public content', array(), array('context' => 'gofast')),
    '#type' => 'checkbox',
    '#default_value' => $spaces_defaults['public_contrib'],
    '#description' => t('If checked, users can contribute to public content. This operation is estimated to @time minutes.', array('@time' => intval($public_count/GOFAST_OG_MEMBERSHIP_QUEUE_MAX_VALUE)+1), array('context' => 'gofast'))
  );

  if(variable_get('block_membership_queue', '0')){
    $form['spaces_permissions']['public_contrib']['#attributes'] = array('disabled' => TRUE);
    $form['spaces_permissions']['public_contrib']['#description'] = t('If checked, users can contribute to public content. This operation is in progress, please wait to revert.', array(), array('context' => 'gofast'));
  }

  //Temporary disabled GOFAST-6081
  $form['spaces_permissions']['public_contrib']['#attributes'] = array('disabled' => TRUE);
  $form['spaces_permissions']['public_contrib']['#description'] = t('This feature is temporarily disabled and will be back soon.', array(), array('context' => 'gofast'));

  $form['spaces_permissions']['create_sub_space'] = array(
    '#title' => t(' Allow non administrator members to create 2nd level sub spaces', array(), array('context' => 'gofast')),
    '#type' => 'checkbox',
    '#default_value' => $spaces_defaults['create_sub_space'],
    '#description' => t('If checked, users are allowed to create their own group or extranet spaces under any 1st level spaces. <br />Example: "Groups/Project_ABC/<strong>My own space</strong>"', array(), array('context' => 'gofast'))
  );

  $form['spaces_permissions']['group_add_external_user'] = array(
    '#title' => t(' Disable adding external users to groups', array(), array('context' => 'gofast')),
    '#type' => 'checkbox',
    '#default_value' => $spaces_defaults['group_add_external_user'],
    '#description' => t('If checked, administrator will not be allowed to add external users to groups.', array(), array('context' => 'gofast'))
  );

  $form['spaces_permissions']['organization_add_external_user'] = array(
    '#title' => t(' Disable adding external users to organizations', array(), array('context' => 'gofast')),
    '#type' => 'checkbox',
    '#default_value' => $spaces_defaults['organization_add_external_user'],
    '#description' => t('If checked, administrator will not be allowed to add external users to organizations.', array(), array('context' => 'gofast'))
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save', array(), array('context' => 'gofast')),
  );
  return $form;
}

/**
 * Spaces settings (from Gofast admin form) validate callback
 */
function gofast_admin_spaces_settings_form_validate($form, &$form_state) {
    return;
}

/**
 * Spaces settings (from Gofast admin form) submit callback
 */
function gofast_admin_spaces_settings_form_submit(&$form, &$form_state) {
    //Retrieve saved spaces configuration
    $spaces_defaults_old = gofast_admin_get_space_defaults();

    $spaces_defaults = $form_state['values'];

    unset($user_form_defaults['submit']);
    unset($user_form_defaults['form_build_id']);
    unset($user_form_defaults['form_token']);
    unset($user_form_defaults['form_id']);
    unset($user_form_defaults['op']);

    if($spaces_defaults['public_contrib'] != $spaces_defaults_old['public_contrib'] && !variable_get('block_membership_queue', 1)){
    //Acquire membership_waiting_build lock
    lock_wait("membership_waiting_build", 10);
    if(!lock_acquire("membership_waiting_build", 10)){
        form_set_error("Lock unabailable", "Unable to lock membership_waiting_build variable");
        return;
    }

    //We will now queue all the public space to rebuild their memberships
    $membership_queue = variable_get('membership_waiting_build', "");
    $membership_queue = json_decode($membership_queue, TRUE);

    foreach(gofast_og_get_root_spaces(TRUE, TRUE) as $root){
      if($root->type == 'public'){
        if($membership_queue == ""){
          $membership_queue = array();
        }
        $membership_queue[] = $root->nid;
        $public_ids = gofast_og_get_children($root->nid, TRUE, FALSE, TRUE);
      }
    }

    foreach($public_ids as $public){
      $membership_queue[] = $public;
    }

    $membership_queue = json_encode($membership_queue);
    variable_set('membership_waiting_build', $membership_queue);
    variable_set('block_membership_queue', 1);

    //Release membership_waiting_build lock
    lock_release("membership_waiting_build");
  }

    variable_set("spaces_defaults", $spaces_defaults);
}

/**
 * Add LDAP settings to the configuration form.
 */
function gofast_admin_sso_settings_form() {
    global $base_url;

    //Login page configuration
    $form['login'] = array(
        '#title' => t('Login page configuration', array(), array('context' => 'gofast:gofast_sso')),
        '#type' => 'fieldset',
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
        '#keen-accordion' => TRUE,
    );

    $form['login']['disable_login'] = array(
        '#title' => t(' Disable login form', array(), array('context' => 'gofast:gofast_sso')),
        '#type' => 'checkbox',
        '#default_value' => variable_get("gofast_disable_login_form", FALSE),
        '#description' => t('If this setting is enabled, the login form will be disabled. Make sure that another authentication mechanism is enabled and working before.', array(), array('context' => 'gofast:gofast_sso'))
    );

    $form['login']['disable_password_reset'] = array(
      '#title' => t(' Disable password reset', array(), array('context' => 'gofast:gofast_sso')),
      '#type' => 'checkbox',
      '#default_value' => variable_get("gofast_disable_password_reset", FALSE),
      '#description' => t('If this setting is enabled, users will no be able to reset their password on their own. Make sure that another authentication mechanism is enabled and working before.', array(), array('context' => 'gofast:gofast_sso'))
  );

    //Keycloak configuration
    if(module_exists("gofast_keycloak")){
        $form['keycloak_settings'] = array(
          '#title' => t('Identity server settings (Keycloak)', array(), array('context' => 'gofast:gofast_keycloak')),
          '#type' => 'fieldset',
          '#collapsible' => TRUE,
          '#collapsed' => TRUE
        );

        $client = gofast_keycloak_get_client();
        $certificates = gofast_keycloak_get_idp_certificates($client);

        $form['keycloak_settings']['cert'] = array(
            '#type' => 'textarea',
            '#title' => t('Identity Provider certificate', array(), array('context' => 'gofast:gofast_keycloak')),
            '#description' => t('This key must be uploaded in the certificate part of the identity provider section.', array(), array('context' => 'gofast:gofast_sso')),
            "#value" => $certificates['certificate'],
        );

        $form['keycloak_settings']['pub'] = array(
            '#type' => 'textarea',
            '#title' => t('Signing public key', array(), array('context' => 'gofast:gofast_keycloak')),
            '#description' => t('This key can be uploaded in the security part of the service provider section to enforce security settings.', array(), array('context' => 'gofast:gofast_sso')),
            "#value" => $certificates['sign_pub'],
        );

        $form['keycloak_settings']['ppk'] = array(
            '#type' => 'textarea',
            '#title' => t('Signing private key', array(), array('context' => 'gofast:gofast_keycloak')),
            '#description' => t('This key can be uploaded in the security part of the service provider section to enforce security settings.', array(), array('context' => 'gofast:gofast_sso')),
            "#value" => $certificates['sign_ppk'],
        );

        $form['keycloak_settings']['help-text'] = array(
            '#type' => 'markup',
            "#markup" => "<strong>" . t("Entity ID", array()) . "</strong>: local <br />"
            . "<strong>" . t("App name", array(), array('context' => 'gofast:gofast_sso')) . ":</strong> local <br />"
            . "<strong>" . t("IDP Login URL", array(), array('context' => 'gofast:gofast_sso')) . ":</strong> $base_url/keycloak/realms/master/protocol/saml <br />"
            . "<strong>" . t("IDP Logout URL", array(), array('context' => 'gofast:gofast_sso')) . ":</strong> $base_url/keycloak/realms/master/protocol/saml <br />",
        );
    }

    //Declare IDP fieldset
    $form['idp'] = array(
        '#title' => t('Identity provider', array(), array('context' => 'gofast:gofast_sso')),
        '#type' => 'fieldset',
        '#collapsible' => TRUE,
        '#collapsed' => FALSE,
        '#keen-accordion' => TRUE,
    );

    //Retrieve eventual already existing IDP
    $idp = saml_sp__load_all_idps();
    if (count($idp) > 0) {
        $idp = reset($idp);
    } else {
        $idp = null;
    }

    //Retrieve IDP configuration_form
    include_once drupal_get_path("module", "saml_sp") . "/saml_sp.admin.inc";
    $idp_form = saml_sp__configure_idp_form($form['idp'], $form, $idp);

    //Merge and format IDP form into IDP fieldset
    $form['idp'] = array_merge($form['idp'], $idp_form);
    $form['idp'] = gofast_admin_sso_format_idp_form($form['idp']);

    //Declare SP fieldset
    $form['sp'] = array(
        '#title' => t('Service provider', array(), array('context' => 'gofast:gofast_sso')),
        '#type' => 'fieldset',
        '#collapsible' => TRUE,
        '#collapsed' => FALSE,
        '#keen-accordion' => TRUE,
    );

    if ($idp !== null) {
        //Collapse IDP fieldset
        $form['idp']['#collapsed'] = true;
    } else {
        //Collapse SP fieldset
        $form['sp']['#collapsed'] = true;
    }
    //Retrieve SP configuration_form
    include_once drupal_get_path("module", "saml_sp") . "/saml_sp.admin.inc";
    $sp_form = saml_sp__admin_config($form['sp'], $form);

    //Merge and format IDP form into IDP fieldset
    $form['sp'] = array_merge($form['sp'], $sp_form);
    $form['sp'] = gofast_admin_sso_format_sp_form($form['sp']);

    $form['delete_request'] = array(
        '#type' => 'checkbox',
        '#attributes' => array('class' => array('gofast_display_none'))
    );

    $form['actions']['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Save', array(), array('context' => 'gofast')),
        '#attributes' => array('onclick' => array('jQuery("#edit-delete-request").prop("checked", false);'))
    );

    if ($idp !== null) {
        $form['actions']['disable_sso'] = array(
            '#type' => 'submit',
            '#value' => t('Disable SSO', array(), array('context' => 'gofast:gofast_sso')),
            '#attributes' => array('onclick' => array('jQuery("#edit-delete-request").prop("checked", true);'))
        );
    }
    return $form;
}

/*
 * Format default IDP form for our own purpose
 */
function gofast_admin_sso_format_idp_form($idp_form){
    //Remove or hide some unwanted fields
    unset($idp_form['#destination']);
    $idp_form['export_type']['#type'] = "hidden";
    $idp_form['machine_name']['#access'] = false;
    $idp_form['nameid_field']["#type"] = "hidden";
    $idp_form['nameid_field']["#value"] = "mail";

    //Get items out of an unwanted fieldset level
    unset($idp_form['idp']['#type']);
    unset($idp_form['idp']['#title']);
    unset($idp_form['idp']['#description']);
    unset($idp_form['idp']['#collapsible']);
    unset($idp_form['idp']['#collapsed']);
    $idp_form = array_merge($idp_form, $idp_form['idp']);
    unset($idp_form['idp']);
    unset($idp_form['submit']);

    //Hide and preset authentication method
    $idp_form['authn_context_class_ref']['#access'] = false;
    $idp_form['authn_context_class_ref']['#default_value'] = array(
       "P" => "P",
       "PPT" => 0,
       "TLS" => 0,
       "x509" => "x509",
       "IWA" => 0,
       "K" => 0
    );

    //Manage mandatory fields
    //print_r($idp_form);exit;
    $idp_form["entity_id"]["#required"] = TRUE;
    $idp_form["app_name"]["#required"] = TRUE;

    //Add a global description
    $idp_form['#description'] = t("The identity provider is the authority that will allow users to connect to this platform. This provider will interact with the users or with your company directory to authentify these users.", array(), array('context' => "gofast:gofast_sso"));

    //Translate all untranslated fields
    $idp_form["name"]["#description"] = t($idp_form["name"]["#description"], array(), array('context' => 'gofast:gofast_sso'));
    $idp_form["entity_id"]["#description"] = t($idp_form["entity_id"]["#description"], array(), array('context' => 'gofast:gofast_sso'));
    $idp_form["app_name"]["#description"] = t($idp_form["app_name"]["#description"], array(), array('context' => 'gofast:gofast_sso'));
    $idp_form["idp_login_url"]["#description"] = t($idp_form["idp_login_url"]["#description"], array(), array('context' => 'gofast:gofast_sso'));
    $idp_form["idp_login_url"]["#maxlength"] = NULL; // "no" maxlength
    $idp_form["idp_logout_url"]["#description"] = t($idp_form["idp_logout_url"]["#description"], array(), array('context' => 'gofast:gofast_sso'));
    $idp_form["idp_logout_url"]["#maxlength"] = NULL; // "no" maxlength
    $idp_form["idp_x509_certs"]["#description"] = t($idp_form["idp_x509_certs"]["#description"], array(), array('context' => 'gofast:gofast_sso'));

    foreach($idp_form["idp_x509_certs"] as $k => &$field){
        if(is_numeric($field)){
            $field['cert']["#title"] = t($field['cert']["#title"], array(), array('context' => 'gofast:gofast_sso'));
            $field['cert']["#description"] = t($field['cert']["#description"], array(), array('context' => 'gofast:gofast_sso'));
        }
    }

    $idp_form["app_name"]["#title"] = t($idp_form["app_name"]["#title"], array(), array('context' => 'gofast:gofast_sso'));
    $idp_form["idp_login_url"]["#title"] = t($idp_form["idp_login_url"]["#title"], array(), array('context' => 'gofast:gofast_sso'));
    $idp_form["idp_logout_url"]["#title"] = t($idp_form["idp_logout_url"]["#title"], array(), array('context' => 'gofast:gofast_sso'));
    $idp_form["idp_x509_certs"]["#title"] = t($idp_form["idp_x509_certs"]["#title"], array(), array('context' => 'gofast:gofast_sso'));

    foreach($idp_form["idp_x509_certs"] as $k => &$field){
        if(is_numeric($k) && !empty($field['cert']['#description'])){
            $field['cert']['#description'] = t($field['cert']['#description'], array(), array('context' => 'gofast:gofast_sso'));
        }
    }

    return $idp_form;
}

/*
 * Format default SP form for our own purpose
 */
function gofast_admin_sso_format_sp_form($sp_form){
    //Hide unwanted fields
    unset($sp_form['saml_sp__strict']);
    $sp_form['saml_sp__cert_location']['#access'] = false;
    $sp_form['saml_sp__key_location']['#access'] = false;
    $sp_form['saml_sp__new_cert_location']['#access'] = false;
    unset($sp_form['saml_sp__debug']);
    $sp_form['metadata']['data']['#disabled'] = false;
    unset($sp_form['actions']);
    unset($sp_form['#submit']);
    unset($sp_form['#theme']);

    //Make security field collapsible and collapse it
    $sp_form['saml_sp__security']['#collapsible'] = TRUE;
    $sp_form['saml_sp__security']['#collapsed'] = TRUE;

    //Translate fields
    $sp_form['saml_sp__contact']['#title'] = t($sp_form['saml_sp__contact']['#title'], array(), array('context' => 'gofast:gofast_sso'));
    $sp_form['saml_sp__organization']['#title'] = t($sp_form['saml_sp__organization']['#title'], array(), array('context' => 'gofast:gofast_sso'));
    $sp_form['saml_sp__security']['#title'] = t($sp_form['saml_sp__security']['#title'], array(), array('context' => 'gofast:gofast_sso'));
    $sp_form['metadata']['#title'] = t($sp_form['metadata']['#title'], array(), array('context' => 'gofast:gofast_sso'));
    $sp_form['saml_sp__contact']['#description'] = t($sp_form['saml_sp__contact']['#description'], array(), array('context' => 'gofast:gofast_sso'));
    $sp_form['saml_sp__organization']['#description'] = t($sp_form['saml_sp__organization']['#description'], array(), array('context' => 'gofast:gofast_sso'));
    //$sp_form['saml_sp__security']['#description'] = t($sp_form['saml_sp__security']['#description'], array(), array('context' => 'gofast:gofast_sso'));
    $sp_form['metadata']['#description'] = t($sp_form['metadata']['#description'], array(), array('context' => 'gofast:gofast_sso'));

    $sp_form['saml_sp__contact']['technical']['#title'] = t($sp_form['saml_sp__contact']['technical']['#title'], array(), array('context' => 'gofast:gofast_sso'));
    $sp_form['saml_sp__contact']['technical']['name']['#title'] = t($sp_form['saml_sp__contact']['technical']['name']['#title'], array(), array('context' => 'gofast:gofast_sso'));
    $sp_form['saml_sp__contact']['technical']['email']['#title'] = t($sp_form['saml_sp__contact']['technical']['email']['#title'], array(), array('context' => 'gofast:gofast_sso'));
    $sp_form['saml_sp__contact']['support']['#title'] = t($sp_form['saml_sp__contact']['support']['#title'], array(), array('context' => 'gofast:gofast_sso'));
    $sp_form['saml_sp__contact']['support']['name']['#title'] = t($sp_form['saml_sp__contact']['support']['name']['#title'], array(), array('context' => 'gofast:gofast_sso'));
    $sp_form['saml_sp__contact']['support']['email']['#title'] = t($sp_form['saml_sp__contact']['support']['email']['#title'], array(), array('context' => 'gofast:gofast_sso'));

    $sp_form['saml_sp__organization']['name']['#title'] = t($sp_form['saml_sp__organization']['name']['#title'], array(), array('context' => 'gofast:gofast_sso'));
    $sp_form['saml_sp__organization']['name']['#description'] = t($sp_form['saml_sp__organization']['name']['#description'], array(), array('context' => 'gofast:gofast_sso'));

    $sp_form['saml_sp__organization']['display_name']['#title'] = t($sp_form['saml_sp__organization']['display_name']['#title'], array(), array('context' => 'gofast:gofast_sso'));
    $sp_form['saml_sp__organization']['display_name']['#description'] = t($sp_form['saml_sp__organization']['display_name']['#description'], array(), array('context' => 'gofast:gofast_sso'));

    $sp_form['saml_sp__organization']['url']['#title'] = t($sp_form['saml_sp__organization']['url']['#title'], array(), array('context' => 'gofast:gofast_sso'));
    $sp_form['saml_sp__organization']['url']['#description'] = t($sp_form['saml_sp__organization']['url']['#description'], array(), array('context' => 'gofast:gofast_sso'));

    $sp_form['metadata']['data']["#description"] = str_replace("This metadata for gofast_sso can also be accessed", t("This metadata for gofast_sso can also be accessed", array(), array('context' => 'gofast:gofast_sso')), $sp_form['metadata']['data']["#description"]);

    foreach($sp_form['saml_sp__security'] as $ename => &$element){
        if(substr($ename, 0, 1) != "#" && is_string($element["#title"])){
            $element["#title"] = t($element["#title"], array(), array('context' => 'gofast:gofast_sso'));
        }
    }

    $sp_form['saml_sp__security']['offered']["#markup"] = t($sp_form['saml_sp__security']['offered']["#markup"], array(), array('context' => 'gofast:gofast_sso'));
    $sp_form['saml_sp__security']['required']["#markup"] = t($sp_form['saml_sp__security']['required']["#markup"], array(), array('context' => 'gofast:gofast_sso'));
    $sp_form['saml_sp__security']['metadata']["#markup"] = t($sp_form['saml_sp__security']['metadata']["#markup"], array(), array('context' => 'gofast:gofast_sso'));

    $sp_form['saml_sp__security']['security_pub'] = array(
        '#type' => "textarea",
        '#default_value' => file_get_contents("/var/www/d7/sites/default/files/gofastx509.crt"),
        '#title' => t('Signing public key', array(), array('context' => 'gofast:gofast_keycloak')),
    );

    $sp_form['saml_sp__security']['security_ppk'] = array(
        '#type' => "textarea",
        '#default_value' => file_get_contents("/var/www/d7/sites/default/files/gofastx509.key"),
        '#title' => t('Signing private key', array(), array('context' => 'gofast:gofast_keycloak')),
    );


    //[GOFAST-6837]
    $sp_form['saml_sp__security']['#keen-accordion'] = TRUE;
    $sp_form['metadata']['#keen-accordion'] = TRUE;

    return $sp_form;
}

/**
 * SSO settings (from Gofast admin form) validate callback
 */
function gofast_admin_sso_settings_form_validate($form, &$form_state) {
  $values = &$form_state['values'];

  // check if values are inconsistently empty or filled
  // list of fields to check if all filled or all empty
  $fields = [
    'name',
    'entity_id',
    'app_name',
    'idp_login_url',
    'idp_logout_url',
  ];
  $fields = array_map(
    fn ($name) => [
      'name' => $name,
      'value' => $values[$name],
      'title' => $form['idp'][$name]['#title']
    ],
    $fields
  );

    $max_url_length = 255; // Max length for URL fields 
    $idp_login_url_length = strlen($values['idp_login_url']);
    $idp_logout_url_length = strlen($values['idp_logout_url']);
  
    if ($idp_login_url_length > $max_url_length) {
      form_set_error(
          'idp_login_url',
          t('!name cannot be longer than %max characters but is currently %length characters long.', [
              '!name' => $form['idp']['idp_login_url']['#title'],
              '%max' => $max_url_length,
              '%length' => $idp_login_url_length
          ])
      );
  }
  
  if ($idp_logout_url_length > $max_url_length) {
      form_set_error(
          'idp_logout_url',
          t('!name cannot be longer than %max characters but is currently %length characters long.', [
              '!name' => $form['idp']['idp_logout_url']['#title'],
              '%max' => $max_url_length,
              '%length' => $idp_logout_url_length
          ])
      );
  }
}

/**
 * SSO settings (from Gofast admin form) submit callback
 */
function gofast_admin_sso_settings_form_submit(&$form, &$form_state) {
  variable_set("gofast_disable_login_form", $form_state['values']['disable_login']);
  if ((bool) $form_state['values']['disable_login'] === FALSE) {
    variable_set("gofast_disable_password_reset", FALSE);
  } else {
    variable_set("gofast_disable_password_reset", $form_state['values']['disable_password_reset']);
  }

  //Set IDP machine_name field
  $form_state['values']['machine_name'] = "gofast_sso";
  //Format IDP auth field, removing false values
  foreach($form_state['values']['authn_context_class_ref'] as $k => $value){
      if($value == false){
          unset($form_state['values']['authn_context_class_ref'][$k]);
      }
  }

  //Send keys to file
  file_put_contents("/var/www/d7/sites/default/files/gofastx509.crt", $form_state['values']['saml_sp__security']['security_pub']);
  file_put_contents("/var/www/d7/sites/default/files/gofastx509.key", $form_state['values']['saml_sp__security']['security_ppk']);

  if($form_state['values']['delete_request']){
      variable_set("gofast_disable_login_form", FALSE);

      //This is a "Disable SSO" request, to delete the IDP
      include_once drupal_get_path("module", "saml_sp") . "/saml_sp.admin.inc";
      saml_sp__delete_idp_form_submit(null, $form_state);
  }else{
      //Send IDP configuration_form
      include_once drupal_get_path("module", "saml_sp") . "/saml_sp.admin.inc";
      saml_sp__configure_idp_form_submit(null, $form_state);
      //Set login page to use this IDP
      variable_set('saml_sp_drupal_login__idp', 'gofast_sso');
      //Exploit SAML SP security field as the default handler can't manage it
      variable_set('saml_sp__security', $form_state['values']['saml_sp__security']);
      $form_state['values']['saml_sp__security'] = array();

      //Send SP informations
      drupal_form_submit("saml_sp__admin_config", $form_state);
  }
}

function gofast_admin_deliver_page($form){
  $content = drupal_render($form);
  $output = array(
    'html' => $content,
    'error' => form_get_errors(),
  );
  print json_encode($output);
}

function gofast_admin_deliver_html($content){
  $output = array(
    'html' => $content,
    'error' => null,
  );
  print json_encode($output, JSON_INVALID_UTF8_IGNORE);
}

function gofast_admin_visibility_settings_form() {
  $form = array();

    // Adds user partitioning setting.
  $form['visibility']['user_partitioning'] = array(
    '#type' => 'select',
    '#title' => t('User Visibility', array(), array('context' => 'gofast')),
    '#options' => gofast_user_partitioning_options(),
    '#default_value' => variable_get('gofast_user_partitioning', GOFAST_USER_PARTITIONING_DEFAULT),
    '#description' => t('Choose whether or not to let users view each others if they don\'t share at least one space in common.', array(), array('context' => 'gofast:gofast_user'))
  );
  // Adds space partitioning config to the form.
  $form['visibility']['space_partitioning'] = array(
    '#type' => 'select',
    '#title' => t('Space Visibility', array(), array('context' => 'gofast')),
    '#options' => gofast_og_partitioning_options(),
    '#default_value' => variable_get('gofast_og_partitioning', GOFAST_OG_PARTITIONING_DEFAULT),
    '#description' => t('Choose whether or not to let users view spaces they are not member of.', array(), array('context' => 'gofast:gofast_og'))
  );

  // Adds checkbox admin config to the form.
 /* $form['visibility']['checkbox_admin'] = array(
    '#type' => 'checkbox',
    '#title' => t('Platform administrators can see all users and spaces', array(), array('context' => 'gofast')),
    '#default_value' => variable_get('gofast_admin_visibility', GOFAST_ADMIN_VISIBILITY_DEFAULT),
    '#description' => t('Platform administrators can’t access contents if they are not members of spaces but can see what spaces exists and can access all users profiles', array(), array('context' => 'gofast:gofast_og'))
  );*/

  $form['visibility']['checkbox_conference_check'] = array(
    '#type' => 'checkbox',
    '#title' => t('Conferences must be created from', array(), array('context' => 'gofast')) . " " . variable_get('site_name', 'GoFAST'),
    '#default_value' => variable_get("gofast_conference_check_room", FALSE),
    '#description' => t('Users will be able to join a conference room only if it has been created before in', array(), array('context' => 'gofast:gofast_og')) . " " . variable_get('site_name', 'GoFAST')
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save', array(), array('context' => 'gofast'))
  );
  return $form;
}

function gofast_admin_general_settings_form() {
  $form = array();

  $form['site_name'] = array(
    '#title' => t('Title', array(), array('context' => 'gofast')),
    '#type' => 'textfield',
    '#default_value' => variable_get('site_name', 'GoFast'),
    '#description' => t('Set your site name', array(), array('context' => 'gofast')) . '.<br /><br />',
    '#attributes' => array('class' => array('form-control'))
  );

  $form['welcome_message'] = array(
    '#title' => t('The default welcome message', array(), array('context' => 'gofast')),
    '#type' => 'textfield',
    '#default_value' => variable_get('welcome_message', 'Welcome to' . variable_get('site_name', 'GoFast')),
    '#description' => t('Set your sentence for the welcome message', array(), array('context' => 'gofast')) . '.<br /><br />'
  );

  $theme_settings = variable_get('theme_bootstrap_gofast_settings', array('toggle_logo' => 0, 'toggle_name' => 1));
  $form['logo'] = array(
    '#title' => t(' Activate Logo', array(), array('context' => 'gofast')),
    '#type' => 'checkbox',
    '#default_value' => $theme_settings['toggle_logo'],
    '#description' => t('Note : If activated, the logo will replace the title.', array(), array('context' => 'gofast'))
  );

  $form['logo_upload_gofast'] = array(
    '#type' => 'file',
    '#title' => t('Upload logo image', array(), array('context' => 'gofast')),
    '#maxlength' => 40,
    '#description' => t("Use this field to upload your logo.")
  );
  $form['position'] = array(
    '#type' => 'select',
    '#title' => t('Logo on login page',array(), array('context' => 'gofast')),
    '#default_value' => isset($theme_settings['position'])? intval($theme_settings['position']):0,
    '#options' => [
      0 => t('Not shown', [], ['context' => 'gofast']),
      1 => t('Above the login form (Pos.1)', [], ['context' => 'gofast']),
      2 => t('In the top right corner (Pos.2)', [], ['context' => 'gofast']),
      3 => t('At the center of the left block (Pos.3)', [], ['context' => 'gofast']),
    ],
    '#description' => '<a href="/custom/modal/'.base64_encode("/sites/all/themes/bootstrap-gofast4/Logo_position.png").'" class="nav-link active ctools-use-modal pl-0"> '. t("Show available positions", array(), array("context" =>  "gofast")).'</a>'
  );

  $form['default_gofast_version'] = array(
    '#type' => 'radios',
    '#options' => array(
      '1' => t("GoFAST Plus", array(), array('gofast')),
      '2' => t("GoFAST Essential", array(), array('gofast'))
    ),
    '#title' => t("Default GoFast user interface", array(), array('context' => 'gofast')),
    '#default_value' =>   variable_get('gofast_admin_interface', GOFAST_COMPLETE_VERSION),
    '#description' => t("Default interface suggested at the first login (each user can make his own choice when connecting).", array(), array('context' => 'gofast'))
  );

  $form['email'] = array(
    '#title' => t('email', array(), array('context' => 'gofast')),
    '#type' => 'textfield',
    '#default_value' => variable_get('site_mail', ini_get('sendmail_from')),
    '#description' => t('Set the site email.', array(), array('context' => 'gofast')),
    '#required' => true
  );

  $form['email_sender'] = array(
    '#title' => t('Email sender', array(), array('context' => 'gofast')),
    '#type' => 'textfield',
    '#default_value' => variable_get('site_mail_sender', 'Postmaster ' . variable_get('site_name', 'GoFast')),
    '#description' => t('Set the site email sender name.', array(), array('context' => 'gofast')),
    '#required' => true
  );

  $form['welcome_mail'] = array(
    '#title' => t('Message in welcome mail', array(), array('context' => 'gofast')),
    '#type' => 'textarea',
    '#default_value' => variable_get('message_welcome_mail', t('Welcome to the GoFAST')),
    '#description' => t('Define the default message sent to the newly created user', array(), array('context' => 'gofast')),
    '#required' => true
  );

  $dropdown_frequency = gofast_subscriptions_ui_get_frequency_dropdown();
  $form['notifications_frequency'] =  array(
    '#title' => t('Default notification frequency', array(), array('context' => 'gofast')),
    '#type'     => 'select',
    '#options'  => $dropdown_frequency,
    '#key_type' => 'associative',
    '#description' => t('Set the default notification frequency for activity notifications.', array(), array('context' => 'gofast')),
    '#default_value' => variable_get("notification_frequency_configuration", 0),
  );
  $form['comments_notifications_frequency'] =  array(
    '#title' => t('Default comments notification frequency', array(), array('context' => 'gofast')),
    '#type'     => 'select',
    '#options'  => $dropdown_frequency,
    '#key_type' => 'associative',
    '#description' => t('Set the default notification frequency for comments notifications.', array(), array('context' => 'gofast')),
    '#default_value' => variable_get("comments_notification_frequency_configuration", 0),
  );

  $home_page = variable_get('site_frontpage', 'node');
  $form['home_node'] = array(
    '#title' => t('Content / Node', array(), array('context' => 'gofast')),
    '#type' => 'textfield',
    '#default_value' => $home_page === 'node' ? '' : $home_page,
    '#description' => t('Enter keywords related to the content you want to display in the home page, then select the appropriate content title apearing in the filtered list (content must be public). Leave blank to set default Home Page.', array(), array('context' => 'gofast')),
    //'#autocomplete_path' => 'gofast-search/node-autocomplete',
  );

  $form['document_reference_label'] = array(
    '#title' => t('Document reference field label', array(), array('context' => 'gofast')),
    '#type' => 'textfield',
    '#default_value' => variable_get('document_reference_label'),
    '#description' => t('Assign a customized label to the document reference field. The default value is "Document reference"', array(), array('context' => 'gofast'))
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save', array(), array('context' => 'gofast'))
  );

  return $form;
}

function gofast_admin_theme_settings(&$form, &$form_state) {

  $form['theme']['background_color'] = array(
    '#markup' => /*TO BE DONE*/'',
  );
    //we list all the css files corresponding to specific domains url
   /* $list_all_css = gofast_admin_get_domains_specific_css();

    $form['theme']['domains_css'] = array(
    '#title' => t('Domain\'s specific css', array(), array('context' => 'gofast')),
    '#type' => 'radios',
    '#options' => $list_all_css,
    '#description' => t('CSS specifics to each domains configured to GoFast'),
  );*/

    /*$form['general']['logo_upload_gofast'] = array(
    '#type' => 'file',
    '#title' => t('Upload logo image'),
    '#maxlength' => 40,
    '#description' => t("Use this field to upload your logo.")
  );*/

  $form['#validate'][] = 'gofast_form_gofast_admin_theme_validate';
  $form['#submit'][] = 'gofast_form_gofast_admin_theme_submit';
}

function gofast_admin_smtp_settings_form() {
  $form = array();

  $form['smtp_server'] = array(
    '#title' => t('SMTP Server', array(), array('context' => 'gofast')),
    '#type' => 'textfield',
    '#default_value' => variable_get('smtp_host', ''),
    '#description' => t('SMTP server url.', array(), array('context' => 'gofast')),
    '#required' => true
  );
  $form['smtp_authentication'] = array(
    '#title' => t(' SMTP Authentication', array(), array('context' => 'gofast')),
    '#type' => 'fieldset',
    '#description' => t('Leave blank if your SMTP server does not require authentication.', array(), array('context' => 'gofast'))
  );
  $form['smtp_authentication']['smtp_username'] = array(
    '#title' => t('Username', array(), array('context' => 'gofast')),
    '#type' => 'textfield',
    '#default_value' => variable_get('smtp_username', ''),
//        '#description' => t('SMTP username.'),
  );
  $form['smtp_authentication']['smtp_password'] = array(
    '#title' => t('Password', array(), array('context' => 'gofast')),
    '#type' => 'password',
    '#default_value' => variable_get('smtp_password', ''),
    //'#description' => t('Leave empty if you do not intend to change the current password.')
//        '#description' => t('SMTP Password.'),
  );
  $form['smtp_authentication']['smtp_security'] = array(
    '#title' => t('Security', array(), array('context' => 'gofast')),
    '#type' => 'radios',
    '#options' => array(
        '' => t('None', array(), array('context' => 'gofast')),
        'tls' => t('TLS', array(), array('context' => 'gofast')),
        'ssl' => t('SSL', array(), array('context' => 'gofast'))
     ),
    '#default_value' => variable_get('smtp_protocol', ''),
    '#description' => t('What security, if any, to use for this SMTP connection.', array(), array('context' => 'gofast')),
  );
  $form['smtp_authentication']['smtp_port'] = array(
    '#title' => t('SMTP Port', array(), array('context' => 'gofast')),
    '#type' => 'textfield',
    '#default_value' => variable_get('smtp_port', ''),
    '#description' => t('What port to use for the connection.', array(), array('context' => 'gofast')),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save', array(), array('context' => 'gofast'))
  );

  return $form;
}

function gofast_admin_onlyoffice_settings(&$form, &$form_state) {
  if (!module_exists('gofast_community')){
    $form['onlyoffice']['settings'] = array(
    '#markup' => /*TO BE DONE*/'',
  );

  $form['#validate'][] = 'gofast_form_gofast_admin_onlyoffice_validate';
  $form['#submit'][] = 'gofast_form_gofast_admin_onlyoffice_submit';
  }
}

/**
 * Implements hook_form()
 */
function gofast_admin_custom_link_settings_form(){
  $form = array();

  $form['add_edit'] = array(
    '#type' => 'fieldset',
    '#title' => t('Activate/Modify a custom link', array(), array('context' => 'gofast')),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    'markup' => array(
      '#markup' => t('You can activate or edit a menu link on the top menu bar', array(), array('context' => 'gofast'))
    )
  );

  $form['has_custom_link'] = array(
    '#title' => t('Display a custom link', array(), array('context' => 'gofast')),
    '#type' => 'checkbox',
    '#default_value' => variable_get('gofast_has_custom_menu_link', false),
    '#description' => t('Determine whether a custom link will be displayed on the top menu bar or not', array(), array('context' => 'gofast'))
  );

  $form['custom_link_label'] = array(
    '#type' => 'textfield',
    '#title' => t('Label of the custom link', array(), array('context' => 'gofast')),
    '#default_value' => variable_get("gofast_custom_menu_link_label", t("Custom Link", [], ["context" => "gofast:gofast_menu"]))
  );

  $form['custom_link_link'] = array(
    '#type' => 'textfield',
    '#title' => t('Link of the custom link', array(), array('context' => 'gofast')),
    '#default_value' => variable_get("gofast_custom_menu_link_href", "https://community.ceo-vision.com")
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save', array(), array('context' => 'gofast'))
  );

  return $form;
}

/**
 * Implements hook_form_validate()
 */
function gofast_admin_custom_link_settings_form_validate(&$form, &$form_state) {
  if (strlen($form_state['values']['custom_link_label']) < 5) {
    form_set_error('custom_link_label', t('The label of the custom link must be at least 4 characters long', array(), array('context' => 'gofast')));
  }
  if (!valid_url($form_state['values']['custom_link_link'])) {
    form_set_error('custom_link_link', t('The url of the custom link is not valid', array(), array('context' => 'gofast')));
  }
}

/**
 * Implements hook_form_validate()
 */
function gofast_admin_custom_link_settings_form_submit(&$form, &$form_state) {
  variable_set("gofast_has_custom_menu_link", (bool) $form_state['values']['has_custom_link']);
  if((bool) $form_state['values']['has_custom_link']) {
    variable_set("gofast_custom_menu_link_label", $form_state['values']['custom_link_label']);
    variable_set("gofast_custom_menu_link_href", $form_state['values']['custom_link_link']);
  }
}

function gofast_admin_visibility_settings_form_submit(&$form, &$form_state){
  variable_set("gofast_user_partitioning", $form_state["values"]["user_partitioning"]);
  variable_set("gofast_og_partitioning", $form_state["values"]["space_partitioning"]);
  variable_set("gofast_conference_check_room", $form_state["values"]["checkbox_conference_check"]);
}

function gofast_admin_general_settings_form_validate(&$form, &$form_state) {
    $form_state['values']['site_name'] = trim($form_state['values']['site_name']);
    if (empty($form_state['values']['site_name']) && $form_state['values']['logo'] == 0) {
        form_set_error('site_name', t('The site name field cannot be empty.', array(), array('context' => 'gofast')));
    }

    //There is no limit on the size of the site name
//    if (strlen($form_state['values']['site_name']) > 28) {
//        form_set_error('site_name', t('The site name is too long, it should be less than 12 characters.', array(), array('context' => 'gofast')));
//    }

    if ($form_state['values']['logo'] && !$form['logo']['#default_value'] && empty($_FILES['files']['name']['logo_upload_gofast'])) {
        form_set_error('logo_upload_gofast', t('Logo path is unset. Please upload a file or uncheck \'Activate Logo\' box.', array(), array('context' => 'gofast')));
    }

    $form_state['values']['home_node'] = trim($form_state['values']['home_node']);
    if (!empty($form_state['values']['home_node'])) {
    //if (!ceo_vision_admin_valid_home_page($form_state['values']['home_node'])) {
    //form_set_error('home_node', t('The content of the node you specified is not public or doesn\'t exist.'));
    //}
    }

    if (!valid_email_address($form_state['values']['email'])) {
        form_set_error('email', t('Please enter a valid email address in the field below.', array(), array('context' => 'gofast')));
    }
}

function gofast_admin_general_settings_form_submit(&$form, &$form_state) {
    if (!empty($form_state['values']['site_name']) && $form_state['values']['site_name'] != variable_get('site_name', 'GoFast')) {
        variable_set('site_name', $form_state['values']['site_name']);
    }
    if (!empty($form_state['values']['welcome_message'])){
        variable_set('welcome_message', $form_state['values']['welcome_message']);
    }
    if (!empty($form_state['values']['welcome_mail'])){
        variable_set('message_welcome_mail', $form_state['values']['welcome_mail']);
    }

  // Update interface setting.
  variable_set('gofast_admin_interface', (int) $form_state['values']['default_gofast_version']);

  $theme_settings = variable_get('theme_bootstrap_gofast_settings', array());
  $theme_settings['toggle_logo'] = $form_state['values']['logo'];

  // si logo inactif :
  // on efface le 'logo_path' sinon l'eventuel ancien logo resterait affiché
  // on réactive le titre
  if (!$theme_settings['toggle_logo']) {
    $theme_settings['logo_path'] = '';
    $theme_settings['toggle_name'] = 1;
    variable_set('theme_bootstrap_gofast_settings', $theme_settings);
  }
  else {
    // logo actif -> on désactive le titre (nom du site) pour ne pas surcharger:
    $theme_settings['toggle_name'] = 0;
    if ($form_state['values']['position'] != $theme_settings['position']) {
      $theme_settings['position'] = intval( $form_state['values']['position']);
     }
     variable_set('theme_bootstrap_gofast_settings', $theme_settings);
    // Upload :
    if (!empty($_FILES['files']['name']['logo_upload_gofast'])) {
      $directory_path = variable_get('file_public_path', conf_path() . '/files');
      file_prepare_directory($directory_path, FILE_CREATE_DIRECTORY);
      $key = 'bootstrap gofast';

      if ($file = file_save_upload('logo_upload_gofast', array('file_validate_is_image' => array()), 'public://')) {
        $parts = pathinfo($file->filename);
        $filename = 'logo.' . $parts['extension'];
        $file->status = FILE_STATUS_PERMANENT;
        $file->filename = $filename;
        file_save($file);

        $_POST['default_logo'] = 0;
        $theme_settings['logo_path'] = $file->uri;
        $theme_settings['default_logo'] = 0;
        variable_set('theme_bootstrap_gofast_settings', $theme_settings);
        variable_set('theme_bootstrap_gofast_mobile_settings', $theme_settings);
        variable_set('theme_bootstrap_keen_settings', $theme_settings);
        $_POST['toggle_logo'] = 1;
      }
      else {
        form_set_error('logo_upload_gofast', t('Logo path is unset. Please upload a file or uncheck \'Activate Logo\' box.', array(), array('context' => 'gofast')));
        return;
      }
    }
  }

  $path = $form_state['values']['home_node'];
  if (empty($path)) {
    $path = 'node';
  }
  if ($path != variable_get('site_frontpage', 'node')) {
    // Apply changes in 'Home' menu item
    /*$ml = menu_link_load(15355);
    $ml['path'] = $ml['tab_root'] = $ml['link_path'] = $ml['href'] = $path;
    menu_link_save($ml);*/
    variable_set('site_frontpage', $path);
  }

  if ($form_state['values']['email'] != variable_get('site_mail', ini_get('sendmail_from'))) {
    variable_set('site_mail', $form_state['values']['email']);
  }
  if ($form_state['values']['email_sender'] != variable_get('site_mail_sender', 'Postmaster ' . variable_get('site_name', 'GoFast'))) {
    variable_set('site_mail_sender', $form_state['values']['email_sender']);
  }

  variable_set('notification_frequency_configuration', $form_state['values']['notifications_frequency']);
  variable_set('comments_notification_frequency_configuration', $form_state['values']['comments_notifications_frequency']);

  $instance = field_read_instance('flagging', 'field_frequency_term', 'subscribe_term');
  $instance['default_value'][0]['value'] = $form_state['values']['notifications_frequency'];
  field_update_instance($instance);

  $instance = field_read_instance('flagging', 'field_frequency_node', 'subscribe_node');
  $instance['default_value'][0]['value'] = $form_state['values']['notifications_frequency'];
  field_update_instance($instance);

  $instance = field_read_instance('flagging', 'field_frequency_og', 'subscribe_og');
  $instance['default_value'][0]['value'] = $form_state['values']['notifications_frequency'];
  field_update_instance($instance);

  $instance = field_read_instance('flagging', 'field_frequency_user', 'subscribe_user');
  $instance['default_value'][0]['value'] = $form_state['values']['notifications_frequency'];
  field_update_instance($instance);

  foreach(['subscribe_term', 'subscribe_node', 'subscribe_og', 'subscribe_user'] as $bundle) {
    $instance = field_read_instance('flagging', 'field_frequency_comment', $bundle);
    if ($instance) {
      $instance['default_value'][0]['value'] = $form_state['values']['comments_notifications_frequency'];
      field_update_instance($instance);
    }
  }

  if(!empty($form_state['values']['document_reference_label'])){
      variable_set("document_reference_label", $form_state['values']['document_reference_label']);
  }else{
      variable_del("document_reference_label");
  }

  cache_clear_all('*', "cache", TRUE);
}

function gofast_form_gofast_admin_onlyoffice_validate(&$form, &$form_state) {

}

function gofast_form_gofast_admin_onlyoffice_submit(&$form, &$form_state) {

}

function gofast_admin_smtp_settings_form_validate(&$form, &$form_state) {
  if (!valid_url($form_state['values']['smtp_server'], false)) {
    form_set_error('smtp_server', t('SMTP Server adress is not valid.', array(), array('context' => 'gofast')));
  }
}

function gofast_admin_smtp_settings_form_submit(&$form, &$form_state) {
  variable_set('smtp_host', $form_state['values']['smtp_server']);
  variable_set('smtp_username', $form_state['values']['smtp_username']);
  if(isset($form_state['values']['smtp_password']) && $form_state['values']['smtp_password'] !== ''){
    variable_set('smtp_password', $form_state['values']['smtp_password']);
  }
  variable_set('smtp_protocol', $form_state['values']['smtp_security']);
  variable_set('smtp_port', $form_state['values']['smtp_port']);
}

function gofast_form_gofast_admin_theme_validate(&$form, &$form_state) {

}

function gofast_form_gofast_admin_theme_submit(&$form, &$form_state) {

}

function gofast_admin_signature_settings_form(&$form, &$form_state) {
    $form = array();

    $form['signature_form'] = array(
        '#title' => t('Default configuration of the signature feature', array(), array('gofast:gofast_signature')),
        '#type' => 'fieldset',
        '#collapsible' => FALSE,
        '#collapsed' => FALSE
    );

    $form['signature_form']['api_url'] = array(
        '#type' => 'textfield',
        '#title' => t('Yousign API URL', array(), array('gofast:gofast_signature')),
        '#default_value' => GOFAST_YOUSIGN_API_URL,
        '#description' => ''
    );

    $form['signature_form']['api_key'] = array(
        '#type' => 'textfield',
        '#title' => t('Yousign API key', array(), array('gofast:gofast_signature')),
        '#default_value' => GOFAST_YOUSIGN_API_KEY,
        '#description' => ''
    );

    $form['signature_form']['app_url'] = array(
        '#type' => 'textfield',
        '#title' => t('Server URL', array(), array('gofast:gofast_signature')),
        '#default_value' => GOFAST_YOUSIGN_APP_URL,
        '#description' => ''
    );

    $form['signature_form']['proof_folder'] = array(
        '#type' => 'textfield',
        '#title' => t('Proof folder', array(), array('gofast:gofast_signature')),
        '#default_value' => GOFAST_YOUSIGN_PROOF_FOLDER,
        '#description' => t('Folder where signature proofs will be stored. Leave empty to store them at the same location than the signed document', array(), array('gofast:gofast_signature'))
    );

    $form['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Save', array(), array('context' => 'gofast')),
    );

    return $form;
}

function gofast_admin_signature_settings_form_validate(&$form, &$form_state) {

}

function gofast_admin_signature_settings_form_submit(&$form, &$form_state) {

  variable_set('gofast_yousign_api_url', $form_state['values']['api_url']);
  variable_set('gofast_yousign_app_url', $form_state['values']['app_url']);
  variable_set('gofast_yousign_api_key', $form_state['values']['api_key']);

  if($form_state['values']['proof_folder'] == ""){
       variable_del('gofast_yousign_proof_folder');
  }else{
       variable_set('gofast_yousign_proof_folder', $form_state['values']['proof_folder']);
  }
}

function gofast_admin_signature_digitalsign_settings_form(&$form, &$form_state) {
  $form = array();

  $form['signature_digitalsign_form'] = array(
    '#title' => t('Default configuration of the signature feature', array(), array('gofast:gofast_signature')),
    '#type' => 'fieldset',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE
  );

  $form['signature_digitalsign_form']['api_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Digitalsign API URL', array(), array('gofast:gofast_signature')),
    '#default_value' => GOFAST_DIGITALSIGN_API_URL,
    '#description' => ''
  );

  $form['signature_digitalsign_form']['portal_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Digitalsign portal URL', array(), array('gofast:gofast_signature')),
    '#default_value' => GOFAST_DIGITALSIGN_PORTAL_URL,
    '#description' => ''
  );

  $form['signature_digitalsign_form']['api_cert'] = array(
    '#type' => 'textarea',
    '#title' => t('Digitalsign API certificate', array(), array('gofast:gofast_signature')),
    '#default_value' => GOFAST_DIGITALSIGN_API_CERT,
    '#description' => t("You have to copy the whole certificate", array(), array('gofast:gofast_signature')),
  );

  $form['signature_digitalsign_form']['api_private_key'] = array(
    '#type' => 'textarea',
    '#title' => t('Digitalsign API private key', array(), array('gofast:gofast_signature')),
    '#default_value' => GOFAST_DIGITALSIGN_API_PRIVATEKEY,
    '#description' => t("You have to copy the whole certificate", array(), array('gofast:gofast_signature')),
  );

  $form['signature_digitalsign_form']['has_signature_background'] = array(
    '#type' => 'checkbox',
    '#title' => t("Enable custom background on DigitalSign signature display", array(), array('context' => 'gofast:gofast_signature')),
    '#default_value' => GOFAST_DIGITALSIGN_HAS_BACKGROUND,
  );

  $form['signature_digitalsign_form']['signature_background'] = array(
    '#type' => 'file',
    '#title' => t('Upload signature background', array(), array('context' => 'gofast:gofast_signature')),
    '#maxlength' => 40,
    '#description' => t("Use this field to upload your signature background. The file must be in .pdf format."),
    "#attributes" => array("data-allowed" => "application/pdf", "data-preview" => "form-item-signature-background-preview")
  );
  
  if (GOFAST_DIGITALSIGN_HAS_BACKGROUND) {
    $form['signature_digitalsign_form']['signature_background']["#suffix"] = '<div id="form-item-signature-background-preview" class="mb-2"><iframe style="width: 100%; height: 100%;" src="'. file_create_url(GOFAST_DIGITALSIGN_BACKGROUND) .'"></iframe></div>';
  }

  $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save', array(), array('context' => 'gofast')),
  );

  return $form;
}

function gofast_admin_signature_digitalsign_settings_form_validate(&$form, &$form_state) {
  if ($form_state['values']['has_signature_background'] && !$form['signature_digitalsign_form']['has_signature_background']['#default_value'] && empty($_FILES['files']['name']['signature_background'])) {
    form_set_error("signature", t("If you enable a signature custom background, you must upload a background for that purpose", [], ["gofast:gofast_signature"]));
  }
}

function gofast_admin_signature_digitalsign_settings_form_submit(&$form, &$form_state) {
  if ($form_state['values']['has_signature_background'] && !empty($_FILES['files']['name']['signature_background'])) {
    $destination = 'public://signature_logos/';
    file_prepare_directory($destination, FILE_CREATE_DIRECTORY);  
    // actual upload
    if ($file = file_save_upload('signature_background', array('file_validate_extensions' => array('pdf')), $destination, FILE_EXISTS_REPLACE)) {
      $file->status = FILE_STATUS_PERMANENT;
      file_save($file);
      drupal_unlink(drupal_realpath(GOFAST_DIGITALSIGN_BACKGROUND));
      variable_set('gofast_digitalsign_background', $file->uri);
    }
  }
  variable_set('gofast_digitalsign_has_background', (bool) $form_state['values']['has_signature_background']);
  variable_set('gofast_digitalsign_api_url', $form_state['values']['api_url']);
  variable_set('gofast_digitalsign_portal_url', $form_state['values']['portal_url']);
  variable_set('gofast_digitalsign_api_cert', $form_state['values']['api_cert']);
  variable_set('gofast_digitalsign_api_privatekey', $form_state['values']['api_private_key']);
}

/**
 * Implements hook_taxonomy_term_delete
 */
function gofast_taxonomy_term_delete($term) {
  if ($term->vid == GOFAST_VID_CATEGORY) {
    // will unset retention only if it has been set on that term
    gofast_retention_unset_category_retention($term);
  }
}

/**
 * Ajax endpoint to set retention rules on a category.
 */
function gofast_admin_action_set_retention_rules() {
  extract($_POST, EXTR_PREFIX_SAME, '_');
  $current_matrix = variable_get(GOFAST_RETENTION_PERIOD_MATRICE_VAR);
  $tid = gofast_xss_clean($tid);
  $term = taxonomy_term_load($etid);
  if (isset($clear)) {
    unset($current_matrix[$term->uuid]);
    variable_set(GOFAST_RETENTION_PERIOD_MATRICE_VAR, $current_matrix);
    drupal_json_output(["data" => ["placeholder" => theme("gofast_ac_placeholder")], "message" => ["success" => t('The retention clear was successful', [], ["context" => "gofast:gofast_retention"])]]);
    exit();
  }
  if ($action != "-None-" && !$period) {
    drupal_json_output(["data" => [], "message" => ["error" => t("You must fill all mandatory fields")]]);
    exit;
  }
  if ($action == "-None-") {
    gofast_retention_unset_category_retention($term);
    $data = [];
  } else {
    $current_matrix[$term->uuid] = array(
      'uuid' => $term->uuid,
      'tid' => $term->tid,
      'period' => gofast_xss_clean($period),
      'period_unit' => gofast_xss_clean($period_unit),
      'action' => gofast_xss_clean($action),
    );
    variable_set(GOFAST_RETENTION_PERIOD_MATRICE_VAR, $current_matrix);
    $multiselect_actions = ["-None-" => t("None"), "Archive" => t("Archive"), "Sort" => t("For sorting"), "Destroy" => t("For disposal")];
    $multiselect_period_units =  ["d" => t("day(s)"), "m" => t("month(s)"), "y" => t("year(s)")];
    $data = ["placeholder" => $multiselect_actions[$action] . " " . t("after") . " " . $period . " " . $multiselect_period_units[$period_unit]];
  }

  drupal_json_output(["data" => $data, "message" => ["success" => t('The retention apply was successful', [], ["context" => "gofast:gofast_retention"])]]);
}

/**
 * This form is intended to apply retention rules retroactively.
 */
function gofast_admin_categories_multiple_apply_retention_form($form, &$form_state, $terms) {
  if (module_exists("gofast_community")) {
    return;
  }
  $terms = array_unique($terms);
  $form['terms'] = [
    '#type' => 'hidden',
    '#value' => $terms,
  ];

  $retention_matrix = variable_get(GOFAST_RETENTION_PERIOD_MATRICE_VAR);
  $retention_matrix_uuids = array_keys($retention_matrix);

  $units = array('d' => 'day(s)', 'm' => 'month(s)', 'y' => 'year(s)');
  $units_trad = array();
  foreach($units as $key => $unit){
    $units_trad[$key] = t($unit);
  }

  $has_retention = FALSE;
  if (!empty($terms)) {
      $value = "<h3>" . t('List of selected categories', [], ['context' => 'gofast:gofast_taxonomy']) . "</h3>";
      $value .= '<ul>';
      foreach ($terms as $key => $term) {
          $full_cat = taxonomy_term_load($term);
          $cat_name = i18n_taxonomy_localize_terms($full_cat)->name;
          if (in_array($full_cat->uuid, $retention_matrix_uuids)) {
            $has_retention = TRUE;
            $value .= '<li><strong>' . $cat_name . '</strong> (';
            $retention_item = $retention_matrix[$full_cat->uuid];
            $translated_actions = ["-None-" => t("None"), "Archive" => t("Archive"), "Sort" => t("For sorting"), "Destroy" => t("For disposal")];
            $translated_action = $translated_actions[$retention_item["action"]];
            $period = $retention_item["period"] . " " . $units_trad[$retention_item['period_unit']];
            $retention_string = t("@action after @period", ["@action" => $translated_action, "@period" => $period], ["context" => "gofast:gofast_retention"]);
            $value .= $retention_string . ")</li>";
          }
      }
      $value .= '</ul>';
  }
  if (!$has_retention) {
    $value = "<h3>" . t("No category with retention set has been selected", array(), array("context" => "gofast:gofast_retention")) . "</h3>";
  }

  $form ['warning'] = [
    '#type' => 'markup',
    '#markup' => "<div class='alert alert-custom alert-notice alert-light-warning fade show' role='alert'><div class='alert-icon'><i class='flaticon-warning'></i></div><div class='alert-text m-0'><span class='font-weight-bold'>" . format_plural(count($terms), "You are going to apply this retention to all documents with the associated category. These documents won't be editable anymore as long as they have this category. Are you sure ?", "You are going to apply this retention to all documents with the associated categories. These documents won't be editable anymore as long as they have those categories. Are you sure ?", array(), array('context' => 'gofast:gofast_retention')) . "</span></div></div>"
  ];

  $form['terms_names'] = [
    '#type' => 'markup',
    '#markup' => $value,
  ];

  $confirm_form = confirm_form(
    $form,
    format_plural(count($terms), 'Are you sure you want to apply retention on the selected category?', 'Are you sure you want to apply retention on the selected categories?', [], ["context" => "gofast:gofast_retention"]),
    'admin/config/gofast/global#edit-categories',
    ''
  );
  if (!$has_retention) {
    $confirm_form['actions']['submit']['#attributes']['disabled'] = TRUE;
    $confirm_form['actions']['submit']['#attributes']['style'] = "cursor: not-allowed;";
  }
  unset($confirm_form['actions']['cancel']);

  return $confirm_form;
}

function gofast_admin_categories_multiple_apply_retention_form_submit($form, &$form_state) {
  $terms = $form_state['values']['terms'];
  $current_matrix = variable_get(GOFAST_RETENTION_PERIOD_MATRICE_VAR);
  $form_state['redirect'] = 'admin/config/gofast/global#edit-categories';
  // The operation will return prematurely to be able to finish without server timeout, so we set the response message now
  $commands[] = gofast_command_toast_message(t('The retention apply was successful', [], ["context" => "gofast:gofast_retention"], 'success'));
  $commands[] = ctools_modal_command_dismiss();
  $commands[] = gofast_command_processAjax("/admin/config/gofast/global#edit-categories");
  print ajax_render($commands);
  // Release the client session and process
  set_time_limit(0);
  fastcgi_finish_request();
  foreach ($terms as $term) {
      $term = taxonomy_term_load($term);
      $term_uuid = $term->uuid;
      if (!isset($current_matrix[$term_uuid])) {
        continue;
      }
      // select nodes with associated category to apply retention to them
      $nids = db_select("field_data_field_category", "cat")
        ->fields("cat", array("entity_id"))
        ->condition('field_category_tid', $term->tid)
        ->execute()->fetchCol();

    foreach ($nids as $nid) {
      $node = node_load($nid);
      $node = gofast_retention_set_node_retention_end_date($term->name, $node, true);
      node_save($node);
    }
  }
}

/**
 * This form is not used anymore. But it may be used in the future if the bulk action to set retention rules is reintroduced.
 */
function gofast_admin_categories_multiple_retention_form($form, &$form_state, $terms) {
  if (module_exists("gofast_community")) {
    return;
  }
  $terms = array_unique($terms);
  $form['terms'] = [
    '#type' => 'hidden',
    '#value' => $terms,
  ];

  $retention_matrix = variable_get(GOFAST_RETENTION_PERIOD_MATRICE_VAR);
  $retention_matrix_uuids = array_keys($retention_matrix);
  
  $units = array('d' => 'Day', 'm' => 'Month', 'y' => 'Year');
  $units_trad = array();
  foreach($units as $key => $unit){
    $units_trad[$key] = t($unit, array(), array('context' => 'gofast:gofast_retention'));
  }

  if (!empty($terms)) {
    $value = "<h3>" . t('List of selected categories', [], ['context' => 'gofast:gofast_taxonomy']) . "</h3>";
    $value .= '<ul>';
    foreach ($terms as $term) {
        $full_cat = taxonomy_term_load($term);
        $cat_name = i18n_taxonomy_localize_terms($full_cat)->name;
        $id_string = "checkbox-item-" . $term;
        $checkbox = '<label class="checkbox checkbox-single kt-checkbox--solid mr-1"><input id="' . $id_string . '" class="checkbox-item" type="checkbox" checked>&nbsp;<span></span></label>';
        $value .= '<li class="list-unstyled d-flex">' . $checkbox . '<strong>' . $cat_name . '</strong>';
        if (in_array($full_cat->uuid, $retention_matrix_uuids)) {
          $value .= " (";
          $retention_item = $retention_matrix[$full_cat->uuid];
          $action = t($retention_item["action"], array(), array('context' => 'gofast:gofast_retention'));
          $period = $retention_item["period"] . " " . $units_trad[$retention_item['period_unit']];
          $retention_string = t("@action after @period", ["@action" => $action, "@period" => $period], ["context" => "gofast:gofast_retention"]);
          $value .= $retention_string . ")";
        } else {
          $value .= " (" . t("No associated retention", [], ["context" => "gofast:gofast_retention"]) . ")";
        }
        $value .= '</li>';
    }
    $value .= '</ul>';
  }

  $form['terms_names'] = [
    '#type' => 'markup',
    '#markup' => $value,
  ];

  $form['unset_all_bs_switch'] = array(
    '#type' => 'checkbox',
    '#title' => t("Check this if you want to unset the retention for all selected categories", [], ["context" => "gofast:gofast_retention"]),
    '#default_value' => 1,
  );

  $form['retention'] = [
    '#type' => 'fieldset'
  ];

  $form['retention']['duration'] = array(
    '#title' => t('Retention duration', array(), array('context' => 'gofast:gofast_retention')),
    '#type' => 'textfield',
    '#description' => "<p class='text-muted'>" . t("If a selected category has a retention duration, it will be replaced by this duration", [], ["context" => "gofast:gofast_retention"]),
  );

  $form['retention']['unit'] = array(
    '#title' => t('Unit', array(), array('context' => 'gofast:gofast_retention')),
    '#type' => 'select',
    '#options' => $units_trad,
  );

  $actions = array('-None-', 'Archive', 'For sorting', 'For disposal');
  $actions_trad =array();
  foreach($actions as $action){
    $actions_trad[$action] = t($action, array(), array('context' => 'gofast:gofast_retention'));
    }
  $form['retention']['action'] = array(
    '#title' => t('Final fate', array(), array('context' => 'gofast:gofast_retention')),
    '#type' => 'select',
    '#options' => $actions_trad,
    '#description' => "<p class='text-muted'>" . "<i class=\"fa fa-warning text-warning\"></i>" .  t("The action will not be triggered automatically, it's an information for the archivists who will decide in the end what to do", [], ["context" => "gofast:gofast_retention"])
  );

  // runs hook (letting modules such as gofast_archive_sorting_room altering the forum)
  foreach(module_implements('alter_admin_retention_settings_form') as $module){
    $function = $module . '_alter_admin_retention_settings_form';
    $form = call_user_func( $function, $form, $units_trad );
  }

  $confirm_form = confirm_form(
    $form,
    format_plural(count($terms), 'Are you sure you want to update the category retention?', 'Are you sure you want to update the categories retention?', [], ["context" => "gofast:gofast_retention"]),
    'admin/config/gofast/global#edit-categories',
    ''
  );
  unset($confirm_form['actions']['cancel']);

  return $confirm_form;
}

function gofast_admin_categories_multiple_retention_form_validate($form, &$form_state) {
  $unset_all = $form_state['values']['unset_all_bs_switch'];
  $duration = $form_state['values']['duration'];
  if ($unset_all == 0 && (strlen($duration) == 0 || !is_numeric($duration))) {
      form_set_error("taxonomy", t("You must input a numeric retention duration", [], ["context" => "gofast:gofast_retention"]));
  }
}

function gofast_admin_categories_multiple_retention_form_submit($form, &$form_state) {
  $terms = explode(" ", $form_state['input']['terms']);
  $current_matrix = variable_get(GOFAST_RETENTION_PERIOD_MATRICE_VAR);

  // first we remove everything
  foreach ($terms as $key => $term) {
    $terms[$key] = taxonomy_term_load($term);
    $term_uuid = $terms[$key]->uuid;
    unset($current_matrix[$term_uuid]);
  }
  $unset_all = $form_state['values']['unset_all_bs_switch'];
  // case the user just wants to unset retention
  if ($unset_all != 0) {
    variable_set(GOFAST_RETENTION_PERIOD_MATRICE_VAR, $current_matrix);
    return;
  }

  foreach ($terms as $term) {
    $current_matrix[$term_uuid] = array(
      'uuid' => $term->uuid,
      'tid' => $term->tid,
      'period' => $form_state['values']['duration'] ,
      'period_unit' => $form_state['values']['unit'],
      'action' => $form_state['values']['action']
    );
  }
  variable_set(GOFAST_RETENTION_PERIOD_MATRICE_VAR, $current_matrix);

  if(isset($form_state['values']['frequence_sorting']['duration'])){
    gofast_archive_sorting_room_settings_frequence_notification($form, $form_state);
  }

  $form_state['redirect'] = 'admin/config/gofast/global#edit-categories';
  drupal_set_message(t('The retention setting was successful', [], ["context" => "gofast:gofast_retention"]));
  return;
}

function gofast_admin_categories_multiple_manage_criticities_form($form, &$form_state, $terms) {
  $terms = array_unique($terms);
  $standard_terms = [];
  gofast_admin_categories_set_categories_list_form_markup($form, $terms, $standard_terms, FALSE);

  $options = [];
  $options[0] = t("None", array(), array("context" => "gofast"));

  $allowed_taxonomy_state = taxonomy_allowed_values(field_info_field('field_criticity'));
  foreach ($allowed_taxonomy_state as $tid => $term){
    $localized_term = i18n_taxonomy_localize_terms(taxonomy_term_load($tid));
    $options[$localized_term->tid] = $localized_term->name;
  }

  // criticity select
  $form['criticity'] = array(
      '#title' => t("Input here the target criticity", [], ["gofast:gofast_taxonomy"]),
      '#type' => 'select',
      '#description' => format_plural(count($terms), 'The criticity will be applied to the selected category. If "None" is selected, the previously applied criticity will be removed from the selected category.', 'The criticity will be applied to all selected categories. If "None" is selected, all previously applied criticities will be removed from the selected categories.', array(), array('context' => 'gofast:gofast_taxonomy')),
      '#options' => $options,
  );

  $form['#suffix'] = "<p class='text-muted'>" . "<i class=\"fa fa-warning text-warning\"></i>" .  t("The target criticity will be applied automatically to all documents having the selected categories", [], ["context" => "gofast:gofast_taxonomy"]);

  $confirm_form = confirm_form(
      $form,
      format_plural(count($terms), 'Are you sure you want to update the category criticity?', 'Are you sure you want to update the categories criticity?', [], ["context" => "gofast:gofast_taxonomy"]),
      'admin/config/gofast/global#edit-categories',
      ''
  );
  unset($confirm_form['actions']['cancel']);
  if (empty($terms)) {
      $confirm_form['actions']['submit']['#attributes']['disabled'] = TRUE;
      $confirm_form['actions']['submit']['#attributes']['style'] = "cursor: not-allowed;";
  }
  return $confirm_form;
}

function gofast_admin_categories_multiple_manage_criticities_form_submit($form, &$form_state) {
  $terms = explode(" ", $form_state['input']['terms']);
  $target_criticity = $form_state['input']['criticity'];

  foreach ($terms as $tid) {
    $term = taxonomy_term_load($tid);
    if ($target_criticity > 0) {
      $term->field_category_criticity[LANGUAGE_NONE][0]["tid"] = $target_criticity;
      // apply the new criticity to all nodes having the matching category
      $nids = db_select("field_data_field_category", "cat")
        ->fields("cat", array("entity_id"))
        ->condition('field_category_tid', $tid)
        ->execute()->fetchCol();
      foreach ($nids as $nid) {
        $node = node_load($nid);
        $node->field_criticity[LANGUAGE_NONE][0]["tid"] = $target_criticity;
        field_attach_update('node', $node);
      }
    } else {
      $term->field_category_criticity = [];
    }  
    taxonomy_term_save($term);
  }

  $form_state['redirect'] = 'admin/config/gofast/global#edit-categories';
  drupal_set_message(format_plural(count($terms), 'You have successfully updated the criticity of the selected category', 'You have successfully updated the criticity of the selected categories', [], ["context" => "gofast:gofast_taxonomy"]));
  return;
}

function gofast_admin_categories_multiple_merge_form($form, &$form_state, $terms) {
  if (module_exists("gofast_naming_rules")) {
    $message = html_entity_decode(t(htmlentities("The selected category has the following naming rule <rule></rule>. Please be sure to know what you are doing before applying it."), [], ["context" => "gofast:gofast_naming_rules"]));
    $callback = "Gofast.namingRules.events.toggleWarningOnInput";
    $form["gofast_naming_rules_warning"] = array(
      "#type" => "markup",
      "#markup" => theme("gofast_naming_rules_warning", ["message" => $message, "callback" => $callback, "selector" => ".modal input#edit-categories"]),
    );
  }
  $terms = array_unique($terms);
  $standard_terms = [];
  gofast_admin_categories_set_categories_list_form_markup($form, $terms, $standard_terms);
  $form['categories'] = array(
    '#title' => t("Input here the category you want to merge to", [], ["gofast:gofast_taxonomy"]),
    '#type' => 'textfield',
    '#name' => 'ac-list-tags-list-cats',
    '#maxlength' => '', // no maxlength
    '#prefix' => "<div style='clear:both;'>",
    '#suffix' => "</div>",
    '#description' => "<p class='text-muted'>" . t("Merged categories will not exist anymore but target category will be applied to all documents on which they were applied", [], ["context" => "gofast:gofast_taxonomy"]),
    '#placeholder' => "<p class='text-muted'>" . t("Start typing the name of a category"),
    '#attributes' => [
      'class' => ['form-control-tags js-tagify'],
      'data-taxonomy_term' => '',
      'data-ac-max-tags' => 1,
      'data-vid' => GOFAST_VID_CATEGORY,
      'data-translate' => '',
    ]
  );

  $confirm_form = confirm_form(
    $form,
    format_plural(count($terms), 'Are you sure you want to merge the category?', 'Are you sure you want to merge the categories?', [], ["context" => "gofast:gofast_taxonomy"]),
    'admin/config/gofast/global#edit-categories',
    ''
  );
  unset($confirm_form['actions']['cancel']);
  if (empty($terms)) {
      $confirm_form['actions']['submit']['#attributes']['disabled'] = TRUE;
      $confirm_form['actions']['submit']['#attributes']['style'] = "cursor: not-allowed;";
  }
  return $confirm_form;
}

function gofast_admin_categories_multiple_merge_form_validate($form, &$form_state) {
  $target_cat = json_decode($form_state['input']['ac-list-tags-list-cats']);
  if (count($target_cat) != 1) {
    form_set_error("taxonomy", t("You have to select one target category, no less, no more", [], ["gofast:gofast_taxonomy"]));
  }
}

function gofast_admin_categories_multiple_merge_form_submit($form, &$form_state) {
  $terms = $form_state['values']['terms'];
  $merge_into = json_decode($form_state['input']['ac-list-tags-list-cats']);
  $term_id = $merge_into[0]->value;

  $cats_to_remove = array_values(array_diff($terms, [$term_id]));
  gofast_admin_tags_set_nodes_tag($term_id, $terms, GOFAST_VID_CATEGORY);

  // cleanup
  foreach($cats_to_remove as $tid) {
    taxonomy_term_delete($tid);
  }

  $form_state['redirect'] = 'admin/config/gofast/global#edit-categories';
  drupal_set_message(t('The category merge was successful', [], ["context" => "gofast:gofast_taxonomy"]));
  return;
}

function gofast_admin_categories_multiple_delete_confirm_form_submit($form, &$form_state) {
  $terms = $form_state['values']['terms'];
  foreach ($terms as $term) {
      taxonomy_term_delete($term);
  }
  $form_state['redirect'] = 'admin/config/gofast/global#edit-categories';
  drupal_set_message(t('You have successfully deleted selected categories', [], ["context" => "gofast:gofast_taxonomy"]));
  return;
}

function gofast_admin_categories_multiple_manage_spaces_form($form, &$form_state, $terms) {
  $terms = array_unique($terms);
  $standard_terms = [];
  $all_gids = gofast_admin_categories_set_categories_list_form_markup($form, $terms, $standard_terms);

  $default_spaces = [];
  foreach($all_gids as $gid) {
      $autocompleted_spaces = gofast_ac_format_value_json('node', node_load($gid), null, []);
      $autocompleted_spaces["nid"] = $gid;
      $default_spaces[] = $autocompleted_spaces;
  }

  $form['allow_all_bs_switch'] = array(
    '#type' => 'checkbox',
    '#title' => t("Check this if you want to allow the selected categories in all spaces", [], ["context" => "gofast:gofast_taxonomy"]),
    '#default_value' => empty($all_gids) ? 1 : 0,
  );

  // ac input
  $form['spaces'] = array(
      '#title' => t("Input here the spaces you want to restrict the category to", [], ["gofast:gofast_taxonomy"]),
      '#type' => 'textfield',
      '#name' => 'ac-list-tags-spaces',
      '#maxlength' => '', // no maxlength
      '#value' => empty($default_spaces) ? "" : json_encode($default_spaces, JSON_HEX_APOS),
      '#prefix' => "<div style='clear:both;'>",
      '#suffix' => "</div>",
      '#description' => "<p class='text-muted'>" . t("Subspaces of selected spaces will inherit their parents' available categories", [], ["context" => "gofast:gofast_taxonomy"]),
      '#placeholder' => "<p class='text-muted'>" . t("Start typing the name of a space"),
      '#attributes' => [
          'data-get-spaces' => ''
      ]
  );

  $confirm_form = confirm_form(
      $form,
      format_plural(count($terms), 'Are you sure you want to update the category spaces?', 'Are you sure you want to update the categories spaces?', [], ["context" => "gofast:gofast_taxonomy"]),
      'admin/config/gofast/global#edit-categories',
      ''
  );
  unset($confirm_form['actions']['cancel']);
  if (empty($terms)) {
      $confirm_form['actions']['submit']['#attributes']['disabled'] = TRUE;
      $confirm_form['actions']['submit']['#attributes']['style'] = "cursor: not-allowed;";
  }
  return $confirm_form;
}

function gofast_admin_categories_multiple_manage_spaces_form_validate($form, &$form_state) {
  $allow_all = $form_state['values']['allow_all_bs_switch'];
  $spaces = json_decode($form_state['input']['ac-list-tags-spaces']);
  if ($allow_all == 0 && empty($spaces)) {
      form_set_error("taxonomy", t("If the category is not authorized in all spaces, you must target at least one authorized space", [], ["context" => "gofast:gofast_taxonomy"]));
  }
}

function gofast_admin_categories_multiple_manage_spaces_form_submit($form, &$form_state) {
  $terms = explode(" ", $form_state['input']['terms']);

  $allow_all = $form_state['values']['allow_all_bs_switch'];
  $spaces = json_decode($form_state['input']['ac-list-tags-spaces']);

  if ($allow_all > 0) {
      gofast_taxonomy_categories_delete_all_spaces_memberships($terms);
  } else {
      $gids = array_map(fn($el) => $el->value, $spaces);
      gofast_taxonomy_categories_restrict_categories_to_spaces($terms, $gids);
  }

  $form_state['redirect'] = 'admin/config/gofast/global#edit-categories';
  drupal_set_message(t('You have successfully updated spaces for selected categories', [], ["context" => "gofast:gofast_taxonomy"]));
  return;
}

function gofast_admin_categories_add_form($form, &$form_state) {
  $form['title'] = array(
      '#title' => t("Input here the technical name of the new category. If needed, you will be able to translate it afterwards.", [], ["gofast:gofast_taxonomy"]),
      '#type' => 'textfield',
  );
  
  $form['allow_all_bs_switch'] = array(
    '#type' => 'checkbox',
    '#title' => t("Check this if you want to allow the new category in all spaces", [], ["context" => "gofast:gofast_taxonomy"]),
    '#default_value' => 1,
  );

  // ac input
  $form['spaces'] = array(
      '#title' => t("Input here the spaces you want to restrict the category to", [], ["gofast:gofast_taxonomy"]),
      '#type' => 'textfield',
      '#name' => 'ac-list-tags-spaces',
      '#maxlength' => '', // no maxlength
      '#value' => empty($default_spaces) ? "" : json_encode($default_spaces, JSON_HEX_APOS),
      '#prefix' => "<div style='clear:both;'>",
      '#suffix' => "</div>",
      '#description' => "<p class='text-muted'>" . t("Subspaces of selected spaces will inherit their parents' available categories", [], ["context" => "gofast:gofast_taxonomy"]),
      '#placeholder' => "<p class='text-muted'>" . t("Start typing the name of a space"),
      '#attributes' => [
          'data-get-spaces' => ''
      ]
  );

  $confirm_form = confirm_form(
      $form,
      t('Are you sure you want to create a new category?', [], ["context" => "gofast:gofast_taxonomy"]),
      'admin/config/gofast/global#edit-categories',
      ''
  );
  unset($confirm_form['actions']['cancel']);
  return $confirm_form;
}

function gofast_admin_categories_add_form_validate($form, &$form_state) {
  $cat_title = trim(gofast_xss_clean($form_state['input']['title']));
  $existing_term = taxonomy_get_term_by_name($cat_title, "category");
  if (!empty($existing_term)) {
      form_set_error("taxonomy", t("A category with the same name already exists", [], ["context" => "gofast:gofast_taxonomy"]));
  }
  if (strlen($cat_title) == 0) {
      form_set_error("taxonomy", t("A category name can't be empty", [], ["context" => "gofast:gofast_taxonomy"]));
  }
  $allow_all = $form_state['values']['allow_all_bs_switch'];
  $spaces = json_decode($form_state['input']['ac-list-tags-spaces']);
  if ($allow_all == 0 && empty($spaces)) {
      form_set_error("taxonomy", t("If the category is not authorized in all spaces, you must target at least one authorized space", [], ["context" => "gofast:gofast_taxonomy"]));
  }
}

function gofast_admin_categories_add_form_submit($form, &$form_state) {
  $cat_title = trim(gofast_xss_clean($form_state['input']['title']));
  $allow_all = $form_state['values']['allow_all_bs_switch'];
  $spaces = json_decode($form_state['input']['ac-list-tags-spaces']);
  gofast_taxonomy_vocabulary_add_term(GOFAST_VID_CATEGORY, $cat_title);
  $term = taxonomy_get_term_by_name($cat_title, "category");
  if (is_array($term)) {
    $term = array_shift($term);
  }

  if ($allow_all > 0) {
      gofast_taxonomy_categories_delete_all_spaces_memberships([$term->tid]);
  } else {
      $gids = array_map(fn($el) => $el->value, $spaces);
      gofast_taxonomy_categories_restrict_categories_to_spaces([$term->tid], $gids);
  }

  $form_state['redirect'] = 'admin/config/gofast/global#edit-categories';
  drupal_set_message(t('You have successfully created a new category', [], ["context" => "gofast:gofast_taxonomy"]));
  return;
}

function gofast_admin_categories_rename_translate_form($form, &$form_state) {
  global $user;
  $category = $form_state["build_info"]["args"][0];

  $form['title'] = array(
      '#title' => t("Input here the technical name of the category", [], ["gofast:gofast_taxonomy"]),
      '#type' => 'textfield',
      '#default_value' => $category->name,
  );

  $language_list = gofast_clean_language_list();
  foreach ($language_list as $key => $available_language) {
    if($available_language->enabled == 0){
      unset($language_list[$key]);
    }
  }
  usort($language_list, function($a, $b) use ($user) {
    if ($a->language == $user->language) {
      return -1;
    }
    if ($b->language == $user->language) {
      return 1;
    }
    return strcmp($a->language, $b->language);
  });
  foreach ($language_list as $language) {
      $default_value = i18n_object('taxonomy_term', $category)->localize($language->language)->name;
      $form['translations_' . $language->language] = array(
          '#title' => t("Input here the category translation for @language", ["@language" => t($language->name)], ["gofast:gofast_taxonomy"]),
          '#type' => 'textfield',
          '#default_value' => $default_value,
      );
  }

  $confirm_form = confirm_form(
      $form,
      t('Are you sure you want to update the category?', [], ["context" => "gofast:gofast_taxonomy"]),
      'admin/config/gofast/global#edit-categories',
      ''
  );
  unset($confirm_form['actions']['cancel']);
  return $confirm_form;
}

function gofast_admin_categories_rename_translate_form_validate($form, &$form_state) {
  $cat_title = trim(gofast_xss_clean($form_state['input']['title']));
  if (strlen($cat_title) == 0) {
      form_set_error("taxonomy", t("A category technical name can't be empty", [], ["context" => "gofast:gofast_taxonomy"]));
  }
  foreach($form_state['input'] as $input_name => $input) {
      if($input_name == "title" || substr($input_name, 0, strlen("translations_")) == "translations_") {
          if (!locale_string_is_safe($input)) {
              form_set_error('translations', t('The submitted string contains disallowed HTML: %string', array('%string' => $input)));
          }
      }
  }
}

function gofast_admin_categories_rename_translate_form_submit($form, &$form_state) {
  $cat_title = trim(gofast_xss_clean($form_state['input']['title']));
  $category = $form_state["build_info"]["args"][0];
  // just in case
  $full_term = taxonomy_term_load($category->tid);
  if ($full_term->name != $cat_title) {
      $full_term->name = $cat_title;
      taxonomy_term_save($full_term);
  }
  foreach($form_state['input'] as $input_name => $input) {
      if(substr($input_name, 0, strlen("translations_")) == "translations_") {
          $langcode = substr($input_name, strlen("translations_"));
          $langstring = i18n_string_object_translate('taxonomy_term', $full_term, ["langcode" => $langcode])->name;
          $langinput = trim(gofast_xss_clean($input));
          if ($langstring == $langinput) {
              continue;
          }
          gofast_taxonomy_add_translation_by_term_name($category->tid, $langcode, $langinput);
      }
  }
  $form_state['redirect'] = 'admin/config/gofast/global#edit-categories';
  drupal_set_message(t('You have successfully updated the category', [], ["context" => "gofast:gofast_taxonomy"]));
  return;
}

function gofast_admin_tags_merge_form($form, &$form_state, $terms) {
  $form['#id'] = 'gofast_admin_tags_merge_form';
  $form['#submit'] = ['gofast_admin_tags_merge_form_submit'];

  $form['terms'] = [
    '#type' => 'hidden',
    '#value' => $terms,
  ];


  $terms_markup = "<h3> ". t("The following tags will be merged:", array(), array("context" => "gofast:gofast_modal")) . "</h3>";
  $terms_markup .= "<ul>";
  foreach ($terms as $term) {
    $term = taxonomy_term_load($term);
    $terms_markup .= "<li>" . $term->name . "</li>";
  }
  $terms_markup .= "</ul>";

  $form['summary'] = [
    '#type' => 'markup',
    '#markup' => $terms_markup
  ];

  $ac_prefix = "<h3> ". t("Please select the target tag the selected tags will be merged into:", array(), array("context" => "gofast:gofast_modal")) . "</h3>";
  $form['ac-list-tags-list-tags'] = [
    '#prefix' => $ac_prefix,
    '#type' => 'textfield',
    '#id' => 'edit-field-tags',
    '#maxlength' => 512,
    '#attributes' => [
      'class' => [' form-control-tags js-tagify'],
      'data-taxonomy_term' => '',
      'data-ac-max-tags' => 1,
      'data-vid' => GOFAST_VID_TAGS,
    ],
  ];
  
  $form['#validate'][] = 'gofast_admin_tags_merge_form_validate';

  $count = count($terms);
  $confirm_form = confirm_form($form, t('Merge @count selected tag(s) into?', ['@count' => $count]), 'admin/config/gofast/global#edit-tags');
  unset($confirm_form['actions']['cancel']);

  return $confirm_form;
}

function gofast_admin_tags_merge_form_validate($form, &$form_state){
  $merge_into = json_decode($form_state['values']['ac-list-tags-list-tags']);
  $term_id = $merge_into[0]->value;
  
  if(!$term_id || !is_numeric($term_id)){
    form_set_error('taxonomy', t("Please select a target tag to merge into.", [], ['context' => 'gofast:gofast_taxonomy']));
    return;
  }
}

function gofast_admin_tags_merge_form_submit($form, &$form_state) {
  $terms = $form_state['values']['terms'];
  $merge_into = json_decode($form_state['values']['ac-list-tags-list-tags']);
  $name = $merge_into[0]->name;
  $term_id = $merge_into[0]->value;

  // contains tags that are in the source tags but not in the target tag: those tags will not be used by any document anymore and should be removed
  $emptied_tags_tids = array_values(array_diff($terms, [$term_id]));

  // update tags
  gofast_admin_tags_set_nodes_tag($term_id, $terms);

  // cleanup
  foreach($emptied_tags_tids as $tid) {
      taxonomy_term_delete($tid);
  }

  $form_state['redirect'] = 'admin/config/gofast/global#edit-tags';
  drupal_set_message(t('You have successfully merged terms into <b>%term</b>', ['%term' => $name]));
  return;
}

function gofast_admin_tags_set_nodes_tag($target_tid, $source_tids, $vid = GOFAST_VID_TAGS) {
  $target = "tags";
  if ($vid == GOFAST_VID_CATEGORY) {
    $target = "category";
  }
  db_update("field_data_field_" . $target)
      ->fields(["field_" . $target . "_tid" => $target_tid])
      ->condition("field_" . $target . "_tid", $source_tids, 'IN')
      ->execute();
  // get all documents whom metadata have been modified
  $query = db_select("node", "n");
  $query->fields("n", ["nid"]);
  $query->innerJoin("field_data_field_" . $target, "t", "t.entity_id = n.nid AND n.status = 1");
  $query->condition("t.field_" . $target . "_tid", $source_tids, 'IN');
  $nids = $query->execute()->fetchCol();
  // and reindex them
  gofast_search_reindex_entities($nids, "node");
}

function gofast_admin_get_nodes_with_tags($terms = [], $vid = GOFAST_VID_TAGS) {
  $target = "tags";
  if ($vid == GOFAST_VID_CATEGORY) {
    $target = "category";
  }

  if (!empty($terms) && is_array($terms)) {
      $query = db_select("field_data_field_" . $target, 'tax');
      $query->addfield('tax', 'entity_id');
      $query->condition("field_" . $target . "_tid", $terms, "IN");
      return $query->execute()->fetchCol();
  }
  return [];
}

function gofast_admin_tags_multiple_delete_confirm_form($form, &$form_state, $terms) {
  $form['terms'] = [
      '#type' => 'hidden',
      '#value' => $terms,
  ];

  $value = t('List of choose terms');
  $value .= '<ul>';
  foreach ($terms as $term) {
      $term_load = taxonomy_term_load($term);
      $name = $term_load->name;
      $value .= '<li>' . $name . '</li>';
  }
  $value .= '</ul>';
  $form['terms_names'] = [
      '#type' => 'markup',
      '#markup' => $value,
  ];

  $confirm_form = confirm_form($form, t('Are you sure you want to delete the term(s)?'), 'admin/config/gofast/global#edit-tags');
  unset($confirm_form['actions']['cancel']);
  return $confirm_form;
}

function gofast_admin_tags_multiple_delete_confirm_form_submit($form, &$form_state) {
  $terms = $form_state['values']['terms'];
  $names = [];
  foreach ($terms as $term) {
      $load_term = taxonomy_term_load($term);
      $names[] = $load_term->name;
      taxonomy_term_delete($term);
  }

  // Clean values in nodes
  $nodes = gofast_admin_get_nodes_with_tags($terms);
  if (!empty($nodes)) {
      foreach ($nodes as $node) {
          $node_load = node_load($node);
          $wrapper = entity_metadata_wrapper('node', $node_load);
          $tags = $wrapper->field_tags->value();
          foreach ($tags as $tag) {
              $tids[] = $tag->tid;
          }
          $tids = array_unique($tids);
          $new_tids = [];
          foreach ($tids as $tid) {
              if (in_array($tid, $terms)) {
              continue;
              }
              $new_tids[] = $tid;
          }
          $wrapper->field_tags->set($new_tids);
          $wrapper->save();
      }
  }
  drupal_set_message(t('Deleted terms %name.', ['%name' => implode(', ', $names)]));
  watchdog('gofast_directory', t('Deleted terms %name.', ['%name' => implode(', ', $names)]), array(), WATCHDOG_NOTICE);
  $form_state['redirect'] = 'admin/config/gofast/global#edit-tags';
  cache_clear_all();
  return;
}

function gofast_admin_categories_get_category_item_form_markup($tid, $term_name, $disabled = FALSE) {
  $all_gids = [];
  $spaces_query = db_select("og_membership", "ogm")
      ->fields("ogm", array("gid"))
      ->condition("ogm.field_name", GOFAST_TAXONOMY_CATEGORY_MEMBERSHIP_FIELD)
      ->condition("ogm.entity_type", "taxonomy_term")
      ->condition("ogm.etid", $tid)
      ->execute()->fetchCol();

  $spaces = "(" . t('Allowed in all spaces', [], ['context' => 'gofast:gofast_taxonomy']) . ")";
  if (!empty($spaces_query)) {
      $spaces = "(";
      foreach($spaces_query as $space) {
          $all_gids[] = $space;
          $crumbs = gofast_breadcrumb_get_breadcrumb($space)[0];
          foreach ($crumbs as $crumb) {
              $spaces .= strip_tags($crumb["name"]) . "/";
          }
          $spaces = substr($spaces, 0, -1);
          $spaces .= ", ";
      }
      $spaces = trim($spaces, ", ");
      $spaces .= ")";
  }
  $label_disabled_string = $disabled ? " checkbox-disabled" : "";
  $disabled_string = $disabled ? " disabled" : " checked";
  $id_string = "checkbox-item-" . $tid;
  $value = '<li class="d-flex">';
  $value .= '<label class="checkbox checkbox-single kt-checkbox--solid mr-1' . $label_disabled_string . '"><input id="' . $id_string . '" class="checkbox-item" type="checkbox"' . $disabled_string . '>&nbsp;<span></span></label>';
  $value .= '<strong>' . $term_name . '</strong> ' . $spaces;
  $value .= '</li>';

  return [$value, $all_gids];
}

function gofast_admin_categories_set_categories_list_form_markup(&$form, &$terms, &$standard_terms, $skip_standard = TRUE) {
  $all_gids = [];
  foreach ($terms as $i => $term) {
      if (gofast_taxonomy_categories_is_category_standard($term)) {
          $standard_terms[] = $term;
          unset($terms[$i]);
      }
  }

  // If wanted, list standard terms along with the other terms
  if (!$skip_standard) {
    $terms = [...$terms, ...$standard_terms];
    $standard_terms = [];
  }

  $form['terms'] = [
      '#type' => 'hidden',
      '#value' => $terms,
  ];

  if (!empty($terms)) {
      $value = "<h3>" . t('List of selected categories', [], ['context' => 'gofast:gofast_taxonomy']) . "</h3>";
      $value .= '<ul class="list-unstyled">';
      foreach ($terms as $term) {
          $full_cat = taxonomy_term_load($term);
          $cat_name = i18n_taxonomy_localize_terms($full_cat)->name;
          [$value_item, $gids_item] = gofast_admin_categories_get_category_item_form_markup($term, $cat_name);
          $value .= $value_item;
          $all_gids = [...$all_gids, ...$gids_item];
      }
      $value .= '</ul>';
  }

  if (!empty($standard_terms)) {
      $value .= "<h3>" . t('The following categories are standard and will not be modified', [], ['context' => 'gofast:gofast_taxonomy']) . "</h3>";
      $value .= '<ul class="list-unstyled">';
      foreach ($standard_terms as $standard_term) {
          $full_cat = taxonomy_term_load($standard_term);
          $cat_name = i18n_taxonomy_localize_terms($full_cat)->name;
          [$value_item, $gids_item] = gofast_admin_categories_get_category_item_form_markup($standard_term, $cat_name, TRUE);
          $value .= $value_item;
      }
      $value .= '</ul>';
  }

  $form['terms_names'] = [
      '#type' => 'markup',
      '#markup' => $value,
  ];
  return $all_gids;
}

function gofast_admin_categories_multiple_delete_confirm_form($form, &$form_state, $terms) {
  $terms = array_unique($terms);
  $standard_terms = [];
  gofast_admin_categories_set_categories_list_form_markup($form, $terms, $standard_terms);

  $confirm_form = confirm_form(
      $form,
      format_plural(count($terms), 'Are you sure you want to delete the category?', 'Are you sure you want to delete the categories', [], ["context" => "gofast:gofast_taxonomy"]),
      'admin/config/gofast/global#edit-categories'
  );
  unset($confirm_form['actions']['cancel']);
  if (empty($terms)) {
      $confirm_form['actions']['submit']['#attributes']['disabled'] = TRUE;
      $confirm_form['actions']['submit']['#attributes']['style'] = "cursor: not-allowed;";
  }
  return $confirm_form;
}