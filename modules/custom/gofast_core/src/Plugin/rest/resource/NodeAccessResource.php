<?php

namespace Drupal\gofast_core\Plugin\rest\resource;

use Drupal\rest\ModifiedResourceResponse;
use Drupal\rest\Plugin\ResourceBase;
use Symfony\Component\DependencyInjection\ContainerInterface;

/**
 * Provides a Node access Resource.
 *
 * @RestResource(
 *   id = "node_access",
 *   label = "node_access",
 *   uri_paths = {
 *     "canonical" = "/api/node/access",
 *     "create" = "/api/node/access"
 *   }
 * )
 */
class NodeAccessResource extends ResourceBase {

  /**
   * Constructs a new NodeAccessResource object.
   *
   * @param array $configuration
   *   A configuration array containing information about the plugin instance.
   * @param string $plugin_id
   *   The plugin_id for the plugin instance.
   * @param mixed $plugin_definition
   *   The plugin implementation definition.
   * @param \Psr\Log\LoggerInterface $logger
   *   A logger instance.
   */
  public function __construct(
    array $configuration,
    $plugin_id,
    $plugin_definition,
    $logger,
  ) {
    parent::__construct($configuration, $plugin_id, $plugin_definition, [], $logger);
  }

  /**
   * Represents a NodeAccessResource.
   */
  public static function create(ContainerInterface $container, array $configuration, $plugin_id, $plugin_definition) {
    return new static(
          $configuration,
          $plugin_id,
          $plugin_definition,
          $container->get('logger.factory')->get('webform_resource')
      );
  }

  /**
   * Retrieves the node access information.
   */
  public function get() {

    // Get node id from the request.
    $request = \Drupal::request();
    $op = $request->attributes->get('node_access');
    $response = new ModifiedResourceResponse($op);
    return $response;
  }

  /**
   * Creates a new node access.
   */
  public function post() {
    // @todo .
  }

}
