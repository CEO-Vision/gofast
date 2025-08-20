<?php

namespace Drupal\gofast_og\EventSubscriber;

use Drupal\Core\Routing\RouteSubscriberBase;
use Symfony\Component\Routing\RouteCollection;

/**
 * Add OG-related D7 access check to canonical node route.
 */
class RouteSubscriber extends RouteSubscriberBase {

  /**
   * {@inheritdoc}
   */
  public function alterRoutes(RouteCollection $collection) {
    // Add gofast_og access check to node routes.
    if ($route = $collection->get('entity.node.canonical')) {
      $route->setRequirement('_gofast_og_access_check', 'TRUE');
    }
  }

}
