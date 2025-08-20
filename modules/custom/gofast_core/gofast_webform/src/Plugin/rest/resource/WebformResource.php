<?php

namespace Drupal\gofast_webform\Plugin\rest\resource;

use Drupal\gofast_webform\Service\SurveyServiceD7;
use Drupal\rest\ModifiedResourceResponse;
use Drupal\rest\Plugin\ResourceBase;
use Symfony\Component\DependencyInjection\ContainerInterface;
use Symfony\Component\HttpFoundation\Request;

/**
 * Provides a Webform Resource.
 *
 * @RestResource(
 *   id = "webform",
 *   label = "Webform",
 *   uri_paths = {
 *     "canonical" = "/api/webform/webform",
 *     "create" = "/api/webform/webform"
 *   }
 * )
 */
class WebformResource extends ResourceBase {
  /**
   * The Survey API service.
   *
   * @var \Drupal\gofast_webform\SurveyServiceD7
   */
  protected $surveyService;

  /**
   * Constructs a new WebformResource object.
   *
   * @param array $configuration
   *   A configuration array containing information about the plugin instance.
   * @param string $plugin_id
   *   The plugin_id for the plugin instance.
   * @param mixed $plugin_definition
   *   The plugin implementation definition.
   * @param \Psr\Log\LoggerInterface $logger
   *   A logger instance.
   * @param \Drupal\gofast_webform\Service\SurveyServiceD7 $surveyServiceD7
   *   The survey service.
   */

  /**
   * Constructs a new WebformResource object.
   *
   * @param array $configuration
   *   A configuration array containing information about the plugin instance.
   * @param string $plugin_id
   *   The plugin_id for the plugin instance.
   * @param mixed $plugin_definition
   *   The plugin implementation definition.
   * @param \Drupal\gofast_webform\Service\SurveyServiceD7 $surveyServiceD7
   *   The survey service.
   * @param \Psr\Log\LoggerInterface $logger
   *   A logger instance.
   */
  public function __construct(
    array $configuration,
    $plugin_id,
    $plugin_definition,
    SurveyServiceD7 $surveyServiceD7,
    $logger,
  ) {
    parent::__construct($configuration, $plugin_id, $plugin_definition, [], $logger);
    $this->surveyService = $surveyServiceD7;
  }

  /**
   * Represents a WebformResource.
   */
  public static function create(ContainerInterface $container, array $configuration, $plugin_id, $plugin_definition) {
    return new static(
          $configuration,
          $plugin_id,
          $plugin_definition,
          $container->get('gofast_webform.survey_service_d7'),
          $container->get('logger.factory')->get('webform_resource')
      );
  }

  /**
   * Retrieves the webform information.
   */
  public function get() {

    // Get node id from the request.
    $request = \Drupal::request();
    $nid = $request->query->get('nid');
    $webform = $this->surveyService->getSurveyValues($nid);
    $webform["node_access"] = $request->attributes->get("node_access");
    $response = new ModifiedResourceResponse($webform);
    return $response;
  }

  /**
   * Update a webform.
   */
  public function post(Request $request) {

    // Get the request content and decode the JSON.
    $data = json_decode($request->getContent(), TRUE);
    if (!$data) {
      return new ModifiedResourceResponse(['error' => 'Invalid JSON'], 400);
    }

    // Extract the nid and submission data from the request.
    $nid = $data['nid'] ?? NULL;
    $survey_array = $data['survey_json'] ?? NULL;

    // Validate mandatory parameters.
    if (empty($nid)) {
      return new ModifiedResourceResponse(['error' => 'Missing mandatory parameters: nid'], 400);
    }

    if (empty($survey_array)) {
      return new ModifiedResourceResponse(['error' => 'Missing mandatory parameters: survey_array'], 400);
    }

    // Transform SurveyJS JSON to Webform elements.
    $this->surveyService->setWebformValues($nid, $survey_array);

    return new ModifiedResourceResponse("Webform elements changed successfully.");

  }

}
