<?php

namespace Drupal\symfony_error_pages;

use Symfony\Component\ErrorHandler\ErrorRenderer\HtmlErrorRenderer;
use Symfony\Component\HttpFoundation\Response;

class GlobalErrorHandler {

  protected $htmlErrorRenderer;

  public function __construct() {
    $this->htmlErrorRenderer = new HtmlErrorRenderer(true);
  }

  public function handle(\Throwable $exception) {
    // Pass the original exception directly to HtmlErrorRenderer
    $errorContent = $this->htmlErrorRenderer->render($exception)->getAsString();

    $response = new Response($errorContent, Response::HTTP_INTERNAL_SERVER_ERROR);
    $response->send();
  }
}
