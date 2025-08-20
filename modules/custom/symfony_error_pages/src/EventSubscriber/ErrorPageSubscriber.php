<?php

namespace Drupal\symfony_error_pages\EventSubscriber;

use Symfony\Component\HttpKernel\Event\ExceptionEvent;
use Symfony\Component\HttpKernel\EventListener\ErrorListener;
use Symfony\Component\HttpKernel\KernelEvents;
use Symfony\Component\EventDispatcher\EventSubscriberInterface;
use Twig\Environment;
use Symfony\Component\HttpFoundation\Response;

class ErrorPageSubscriber implements EventSubscriberInterface {

  protected $twig;
  protected $kernel;
  protected $requestStack;

  public function __construct(Environment $twig, $kernel, $requestStack) {
    $this->twig = $twig;
    $this->kernel = $kernel;
    $this->requestStack = $requestStack;
  }

  public static function getSubscribedEvents() {
    return [
      KernelEvents::EXCEPTION => 'onException',
    ];
  }

  public function onException(ExceptionEvent $event) {
    $exception = $event->getThrowable();
    $request = $this->requestStack->getCurrentRequest();

    // Use Symfony's HTML error renderer.
    $htmlRenderer = new \Symfony\Component\ErrorHandler\ErrorRenderer\HtmlErrorRenderer(true);
    $errorContent = $htmlRenderer->render($exception)->getAsString();

    $response = new Response($errorContent, Response::HTTP_INTERNAL_SERVER_ERROR);
    $event->setResponse($response);
  }
}
