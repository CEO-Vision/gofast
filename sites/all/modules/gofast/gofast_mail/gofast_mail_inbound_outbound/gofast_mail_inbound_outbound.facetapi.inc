<?php

/**
 * Implements hook_facetapi_facet_info()
 *
 *  Define facets provided by the module.
 */
function gofast_mail_inbound_outbound_facetapi_facet_info($searcher_info) {
  $facets = array();

  $facets['mail_object'] = array(
    'field' => 'sm_unr_mail_object',
    'label' => t("Objet du courrier", array(), array('context' => 'gofast')),
    'description' => t('Filter by', array(), array('context' => 'gofast:gofast_search')) . " " . t('Objet du courier', array(), array('context' => 'gofast')),
    'facet mincount allowed' => TRUE,
    'dependency plugins' => array('bundle', 'role'),
    'allowed operators' => array(FACETAPI_OPERATOR_AND => TRUE),
    'default sorts' => array(
      array('display', SORT_ASC)
    )

  );

  $facets['mail_rid'] = array(
    'field' => 'sm_unr_mail_rid',
    'label' => t("Reference du courrier", array(), array('context' => 'gofast')),
    'description' => t('Filter by', array(), array('context' => 'gofast:gofast_search')) . " " . t('Reference du courrier', array(), array('context' => 'gofast')),
    'facet mincount allowed' => TRUE,
    'dependency plugins' => array('bundle', 'role'),
    'allowed operators' => array(FACETAPI_OPERATOR_AND => TRUE),
    'default sorts' => array(
      array('display', SORT_ASC)
    )

  );

  $facets['arrival_departure_date'] = array(
    'field' => 'sm_unr_arrival_departure_date',
    'label' => t("Date d'arrivée/départ du courrier", array(), array('context' => 'gofast')),
    'description' => t('Filter by', array(), array('context' => 'gofast:gofast_search')) . " " . t("Date d\'arrivée/départ du courrier", array(), array('context' => 'gofast')),
    'facet mincount allowed' => TRUE,
    'dependency plugins' => array('bundle', 'role'),
    'allowed operators' => array(FACETAPI_OPERATOR_AND => TRUE),
    'default sorts' => array(
      array('display', SORT_ASC)
    )

  );

  $facets['mail_sender'] = array(
    'field' => 'sm_unr_mail_sender',
    'label' => t("Emetteur du courrier", array(), array('context' => 'gofast')),
    'description' => t('Filter by', array(), array('context' => 'gofast:gofast_search')) . " " . t('Emetteur du courier', array(), array('context' => 'gofast')),
    'facet mincount allowed' => TRUE,
    'dependency plugins' => array('bundle', 'role'),
    'allowed operators' => array(FACETAPI_OPERATOR_AND => TRUE),
    'default sorts' => array(
      array('display', SORT_ASC)
    )

  );

  $facets['mail_instruction'] = array(
    'field' => 'sm_unr_mail_instruction',
    'label' => t("Instruction du courrier", array(), array('context' => 'gofast')),
    'description' => t('Filter by', array(), array('context' => 'gofast:gofast_search')) . " " . t('Instruction du courrier', array(), array('context' => 'gofast')),
    'facet mincount allowed' => TRUE,
    'dependency plugins' => array('bundle', 'role'),
    'allowed operators' => array(FACETAPI_OPERATOR_AND => TRUE),
    'default sorts' => array(
      array('display', SORT_ASC)
    )

  );

  $facets['service_recipient'] = array(
    'field' => 'sm_unr_service_recipient',
    'label' => t("Service destinataire", array(), array('context' => 'gofast')),
    'description' => t('Filter by', array(), array('context' => 'gofast:gofast_search')) . " " . t('Service destinataire', array(), array('context' => 'gofast')),
    'facet mincount allowed' => TRUE,
    'dependency plugins' => array('bundle', 'role'),
    'allowed operators' => array(FACETAPI_OPERATOR_AND => TRUE),
    'default sorts' => array(
      array('display', SORT_ASC)
    )

  );

  $facets['user_recipient'] = array(
    'field' => 'sm_unr_user_recipient',
    'label' => t("Personne destinataire", array(), array('context' => 'gofast')),
    'description' => t('Filter by', array(), array('context' => 'gofast:gofast_search')) . " " . t('Personne destinataire', array(), array('context' => 'gofast')),
    'facet mincount allowed' => TRUE,
    'dependency plugins' => array('bundle', 'role'),
    'allowed operators' => array(FACETAPI_OPERATOR_AND => TRUE),
    'default sorts' => array(
      array('display', SORT_ASC)
    )

  );

  $facets['impute_to'] = array(
    'field' => 'sm_unr_impute_to',
    'label' => t("Imputer à", array(), array('context' => 'gofast')),
    'description' => t('Filter by', array(), array('context' => 'gofast:gofast_search')) . " " . t('Imputer à', array(), array('context' => 'gofast')),
    'facet mincount allowed' => TRUE,
    'dependency plugins' => array('bundle', 'role'),
    'allowed operators' => array(FACETAPI_OPERATOR_AND => TRUE),
    'default sorts' => array(
      array('display', SORT_ASC)
    )

  );

  $facets['mandatory_anwser'] = array(
    'field' => 'sm_unr_mandatory_anwser',
    'label' => t("Réponse obligatoire", array(), array('context' => 'gofast')),
    'description' => t('Filter by', array(), array('context' => 'gofast:gofast_search')) . " " . t('Réponse obligatoire', array(), array('context' => 'gofast')),
    'facet mincount allowed' => TRUE,
    'dependency plugins' => array('bundle', 'role'),
    'allowed operators' => array(FACETAPI_OPERATOR_AND => TRUE),
    'default sorts' => array(
      array('display', SORT_ASC)
    )

  );

  $facets['arrival_departure_link'] = array(
    'field' => 'sm_unr_arrival_departure_link',
    'label' => t("Lien entre courrier entrant/sortant:", array(), array('context' => 'gofast')),
    'description' => t('Filter by', array(), array('context' => 'gofast:gofast_search')) . " " . t('Lien entre courrier entrant/sortant', array(), array('context' => 'gofast')),
    'facet mincount allowed' => TRUE,
    'dependency plugins' => array('bundle', 'role'),
    'allowed operators' => array(FACETAPI_OPERATOR_AND => TRUE),
    'default sorts' => array(
      array('display', SORT_ASC)
    )

  );

  $facets['acknowledge_number'] = array(
    'field' => 'sm_unr_acknowledge_number',
    'label' => t("Numéro d'accusé réception", array(), array('context' => 'gofast')),
    'description' => t('Filter by', array(), array('context' => 'gofast:gofast_search')) . " " . t("Numéro d'accusé réception", array(), array('context' => 'gofast')),
    'facet mincount allowed' => TRUE,
    'dependency plugins' => array('bundle', 'role'),
    'allowed operators' => array(FACETAPI_OPERATOR_AND => TRUE),
    'default sorts' => array(
      array('display', SORT_ASC)
    )

  );

  return $facets;
}
