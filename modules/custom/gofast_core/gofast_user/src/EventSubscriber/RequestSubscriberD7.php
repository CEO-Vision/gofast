<?php

namespace Drupal\gofast_user\EventSubscriber;

use Psr\Log\LoggerInterface;
use Drupal\Core\Logger\RfcLogLevel;
use Drupal\Core\Routing\RouteMatchInterface;
use Drupal\Core\Session\AccountProxyInterface;
use Drupal\gofast_core\Utils\RequestUtils;
use Psr\Http\Message\ResponseInterface;
use Symfony\Component\EventDispatcher\EventSubscriberInterface;
use Symfony\Component\HttpFoundation\RedirectResponse;
use Symfony\Component\HttpFoundation\RequestStack;
use Symfony\Component\HttpKernel\Event\ControllerEvent;
use Symfony\Component\HttpKernel\Event\ResponseEvent;
use Symfony\Component\HttpKernel\KernelEvents;

/**
 * Class RequestSubscriber.
 *
 * @package Drupal\gofast_user\EventSubscriber
 */
class RequestSubscriberD7 implements EventSubscriberInterface {
  /**
   * Routes to auth with API.
   *
   * @var string[]
   */
  protected $authGuarded = ["entity.node.canonical"];

  /**
   * Routes to node_access with API.
   *
   * @var string[]
   */
  protected $nodeGuarded = ["rest.node_access.GET", "rest.webform.GET"];

  /**
   * The route match.
   *
   * @var \Drupal\Core\Routing\RouteMatchInterface
   */
  protected $routeMatch;

  /**
   * The account proxy.
   *
   * @var \Drupal\Core\Session\AccountProxyInterface
   */
  protected $accountProxy;

  /**
   * The logger.
   *
   * @var \Drupal::logger
   */
  protected $logger;

  /**
   * The current request.
   *
   * @var \Symfony\Component\HttpFoundation\Request
   */
  protected $request;

  /**
   * The full request stack.
   *
   * @var \Symfony\Component\HttpFoundation\RequestStack
   */
  protected $requestStack;

  /**
   * The current event.
   *
   * @var \Symfony\Component\HttpKernel\Event\ControllerEvent
   */
  protected $event;

  /**
   * Route name from current request.
   *
   * @var string
   */
  protected $routeName;

  /**
   * D7 user ID of current user if any.
   *
   * @var int
   */
  public $uid;

  /**
   * D7 node ID of current request if any.
   *
   * @var int
   */
  public $nid;

  /**
   * Constructs a new RequestSubscriber object.
   *
   * @param \Drupal\Core\Session\AccountProxyInterface $account_proxy
   *   The current user.
   * @param \Drupal\Core\Routing\RouteMatchInterface $route_match
   *   The route match.
   * @param \Symfony\Component\HttpFoundation\RequestStack $request_stack
   *   The request stack.
   * @param \Psr\Log\LoggerInterface $logger
   *   The logger.
   */
  public function __construct(AccountProxyInterface $account_proxy, RouteMatchInterface $route_match, RequestStack $request_stack, LoggerInterface $logger) {
    $this->routeMatch = $route_match;
    $this->accountProxy = $account_proxy;
    $this->requestStack = $request_stack;
    $this->logger = $logger;
  }

  /**
   * {@inheritdoc}
   *
   * @return array
   *   The event names to listen for, and the methods that should be executed.
   */
  public static function getSubscribedEvents() {
    return [
    // The route is resolved but the controller not called yet.
      KernelEvents::CONTROLLER => ['onKernelController', 0],
    // Handle response flags set at earlier stages.
      KernelEvents::RESPONSE => ['onKernelResponse', 0],
    ];
  }

  /**
   * Handler called when an API request fails.
   *
   * @return false
   *   Since it's an error callback, it will always return false.
   *   So the caller knows something went wrong.
   */
  public function onErrorCallback($response, $context) {
    RequestUtils::redirect($context->event, "system.403");
    return FALSE;
  }

  /**
   * Handler called when an auth API request succeeds.
   *
   * @return Psr\Http\Message\ResponseInterface|false
   *   The plain request response if authentication was successful.
   *   False otherwise.
   */
  public function onAuthAgainstDrupalSuccess(ResponseInterface $response, $context) {
    $body = json_decode($response->getBody()->getContents());

    // User is authenticated in D7: we do not have to prevent anything.
    if ($body && $body->uid && $body->uid > 0) {
      $context->uid = (int) $body->uid;
      $current_uri = $context->request->getUri();
      $this->logger->log(RfcLogLevel::INFO, "Authorize D7 user $context->uid to access $current_uri");

      return $response;
    }
    return FALSE;
  }

  /**
   * Check for authentication against D7.
   *
   * @return bool
   *   False if auth failed, true otherwise.
   */
  private function authAgainstDrupal() {
    // If we're not navigating to an auth guarded route,
    // we do not have to do anything.
    if (!in_array($this->routeName, $this->authGuarded)) {
      return TRUE;
    }

    $hostname = $this->request->getHost();
    $endpoint = "https://$hostname/gofast/user/whoami";

    // Make the API request with the cookies.
    $response = RequestUtils::request(
          $endpoint,
          "GET",
          [],
          [],
          [$this, "onAuthAgainstDrupalSuccess"],
          [$this, "errorCallback"],
          $this
      );

    // Falsy response may come from faulty request
    // or from error callback: in both cases auth has failed.
    if (!$response) {
      RequestUtils::redirect($this->request, "system.403");
      return FALSE;
    }
    return TRUE;
  }

  /**
   * Handler called when an auth API request succeeds.
   *
   * @return string|false
   *   False if no access, otherwise highest authorized operation
   */
  public function onNodeAccessAgainstDrupalSuccess($response, $context) {
    $body = json_decode($response->getBody()->getContents());
    $access_string = json_encode($body->access);
    $this->logger->log(RfcLogLevel::INFO, "Got authorization $access_string for D7 user $context->uid on D7 node $context->nid");
    return $body->access;
  }

  /**
   * Check for node access permission against D7.
   *
   * @return bool
   *   False if no access, true otherwise
   */
  private function nodeAccessAgainstDrupal() {
    // If we're not navigating to a node_access guarded route,
    // we do not have to do anything.
    if (!in_array($this->routeName, $this->nodeGuarded)) {
      return TRUE;
    }

    // Route parameter.
    $this->nid = $this->routeMatch->getParameter('nid');

    // Else query parameter.
    if ($this->nid === NULL) {
      $this->nid = $this->requestStack->getCurrentRequest()->query->get('nid');
    }

    $hostname = $this->request->getHost();
    $endpoint = "https://$hostname/api/node/access?nid=$this->nid";

    if ($this->routeName === "rest.webform.GET") {
      $hash = $this->requestStack->getCurrentRequest()->query->get('hash');
      if ($hash) {
        $endpoint .= "&hash=$hash";
      }
    }

    // Make the API request with the cookies.
    $response = RequestUtils::request(
          $endpoint,
          "GET",
          [],
          [],
          [$this, "onNodeAccessAgainstDrupalSuccess"],
          [$this, "errorCallback"],
          $this
      );

    // Put the check result in the request, so it can be read in the controller.
    $this->request->attributes->set("node_access", $response);

    if (!$response) {
      RequestUtils::redirect($this->request, "system.403");
      return FALSE;
    }

    return TRUE;
  }

  /**
   * General handler to trigger all D7-related checks.
   */
  private function triggerAllChecks() {
    $checks = [
      [$this, 'authAgainstDrupal'],
      [$this, 'nodeAccessAgainstDrupal'],
    ];
    foreach ($checks as $check) {
      $auth = call_user_func($check);
      // Check has failed: no need to go further.
      if (!$auth) {
        break;
      }
    }
  }

  /**
   * React to requests being made.
   *
   * @param \Symfony\Component\HttpKernel\Event\ControllerEvent $event
   *   The controller event.
   */
  public function onKernelController(ControllerEvent $event) {
    // Set values.
    $this->event = $event;
    $this->request = $event->getRequest();

    // Set cookies.
    $cookies = $this->request->cookies->all();

    $hostname = $this->request->getHost();
    RequestUtils::updateCookies($cookies, $hostname);
    $this->routeName = $this->routeMatch->getRouteName();

    $this->triggerAllChecks();
  }

  /**
   * If we flagged the request for redirection, do the actual redirection.
   *
   * @param \Symfony\Component\HttpKernel\Event\ResponseEvent $event
   *   The response event.
   */
  public function onKernelResponse(ResponseEvent $event) {
    $request = $event->getRequest();
    $redirect = $request->attributes->get('redirect');

    // Check if the redirect flag is set.
    if ($redirect) {
      $event->setResponse(new RedirectResponse($redirect));
    }
  }

}
