<?php

namespace Drupal\gofast_webform\Plugin\rest\resource;

use Drupal\gofast_webform\Service\SurveyService;
use Drupal\rest\ModifiedResourceResponse;
use Drupal\rest\Plugin\ResourceBase;
use Symfony\Component\DependencyInjection\ContainerInterface;
use Symfony\Component\HttpFoundation\Request;

/**
 * Provides a Webform submissions Resource.
 *
 * @RestResource(
 *   id = "webform_submissions",
 *   label = "Webform submissions",
 *   uri_paths = {
 *     "canonical" = "/api/webform/submissions",
 *     "create" = "/api/webform/submissions"
 *   }
 * )
 */
class WebformSubmissionsResource extends ResourceBase {
  /**
   * The Survey API service.
   *
   * @var \Drupal\gofast_webform\SurveyService
   */
  protected $surveyService;

  /**
   * Constructs a new WebformSubmissionsResource object.
   *
   * @param array $configuration
   *   A configuration array containing information about the plugin instance.
   * @param string $plugin_id
   *   The plugin_id for the plugin instance.
   * @param mixed $plugin_definition
   *   The plugin implementation definition.
   * @param \Drupal\gofast_webform\Service\SurveyService $surveyService
   *   The survey service.
   * @param \Psr\Log\LoggerInterface $logger
   *   A logger instance.
   */
  public function __construct(
    array $configuration,
    $plugin_id,
    $plugin_definition,
    SurveyService $surveyService,
    $logger,
  ) {
    parent::__construct($configuration, $plugin_id, $plugin_definition, [], $logger);
    $this->surveyService = $surveyService;
  }

  /**
   * Represents a WebformSubmissionsResource.
   */
  public static function create(ContainerInterface $container, array $configuration, $plugin_id, $plugin_definition) {
    return new static(
          $configuration,
          $plugin_id,
          $plugin_definition,
          $container->get('gofast_webform.survey_service'),
          $container->get('logger.factory')->get('webform_submissions_resource')
      );
  }

  /**
   * Responds to GET requests.
   *
   * Returns the webform submissions.
   *
   * @return \Drupal\rest\ResourceResponse
   *   The response containing the webform submissions.
   */
  public function get() {
    // Get node id from the request.
    $request = \Drupal::request();
    $nid = $request->query->get('nid');

    // Validate mandatory parameters.
    if (empty($nid)) {
      return new ModifiedResourceResponse(['error' => 'Missing mandatory parameters: nid'], 400);
    }

    // Get webform submissions.
    $submissions = $this->surveyService->getWebformSubmissions($nid);
    if ($submissions === NULL) {
      return new ModifiedResourceResponse(['error' => 'Webform not found or no submissions'], 404);
    }

    return new ModifiedResourceResponse($submissions);
  }

  /**
   * Responds to POST requests.
   */
  public function post(Request $request) {

    // Get all parameters.
    $parameters = $request->getContent();
    $parameters = json_decode($parameters, TRUE);
    $nid = $parameters['nid'];
    $results = $parameters['results'];

    $webform_submission = $this->surveyService->setWebformSubmissions($nid, $results);

    return new ModifiedResourceResponse($webform_submission);
  }

}
