<?php

namespace Drupal\gofast_webform\Controller;

use Drupal\Core\Controller\ControllerBase;
use Symfony\Component\HttpFoundation\Request;

/**
 * Controller for displaying webform pages.
 *
 * @package Drupal\gofast_webform\Controller
 */
class WebformPageController extends ControllerBase {

  /**
   * Get webform content.
   *
   * @param \Symfony\Component\HttpFoundation\Request $request
   *   The request object.
   * @param int $nid
   *   The node ID.
   *
   * @return array
   *   The webform content.
   */
  public function index(Request $request, $nid) {
    return [
      '#theme' => 'gofast_webform.page_content',
      '#nid' => $nid,
      '#hash' => $request->query->get("hash"),
    ];
  }

}
