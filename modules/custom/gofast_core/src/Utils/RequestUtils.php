<?php

namespace Drupal\gofast_core\Utils;

use Drupal\Core\Url;
use GuzzleHttp\Client;
use GuzzleHttp\Cookie\CookieJar;
use GuzzleHttp\Cookie\SetCookie;
use GuzzleHttp\HandlerStack;
use Symfony\Component\HttpFoundation\Request;

/**
 * Core reusable logic for Drupal requests.
 *
 * @package Drupal\gofast_core\Utils
 */
class RequestUtils {
  /**
   * The HTTP client.
   *
   * @var \GuzzleHttp\Client
   */
  private static $client;

  /**
   * The cookie jar for the HTTP client.
   *
   * @var \GuzzleHttp\Cookie\CookieJar
   */
  private static $cookieJar;

  /**
   * The logger.
   *
   * @var \Drupal::logger
   */
  private static $logger;

  /**
   * Initialize static properties.
   */
  private static function initialize() {
    if (!isset(self::$logger)) {
      self::$logger = \Drupal::logger('gofast_core');
    }

    if (!isset(self::$cookieJar)) {
      self::$cookieJar = new CookieJar();
    }

    if (!isset(self::$client)) {
      $stack = HandlerStack::create();
      self::$client = new Client([
        'handler' => $stack,
        'cookies' => self::$cookieJar,
      ]);
    }
  }

  /**
   * Set a redirect flag to request being made.
   *
   * @param \Symfony\Component\HttpFoundation\Request $request
   *   The request object.
   * @param string $route_name
   *   The route name.
   */
  public static function redirect(Request $request, string $route_name) {
    $url = Url::fromRoute($route_name)->toString();
    $request->attributes->set('redirect', $url);
  }

  /**
   * Force update cookies in the cookie jar.
   *
   * @param array $cookies
   *   Cookies set up as name => value pairs.
   * @param string $hostname
   *   Hostname which will be set in the cookies.
   */
  public static function updateCookies(array $cookies, string $hostname) {
    self::initialize();

    foreach ($cookies as $name => $value) {
      $setCookie = new SetCookie([
        'Name' => $name,
        'Value' => $value,
        'Domain' => $hostname,
        'Path' => '/',
        'Max-Age' => 3600,
        'Secure' => TRUE,
        'HttpOnly' => TRUE,
      ]);
      self::$cookieJar->setCookie($setCookie);
    }
  }

  /**
   * Make a request with callbacks for success and failure.
   *
   * @param string $endpoint
   *   Target endpoint for the request.
   * @param string $verb
   *   HTTP verb which will be used for the request.
   * @param array $headers
   *   Headers for the request.
   * @param array $body
   *   Body for the request.
   * @param callable|null $success_callback
   *   If set, will be called on request success
   *   with the response and the context.
   * @param callable|null $error_callback
   *   If set, will be called on request error
   *   with the response and the context.
   * @param object|null $context
   *   If set, callbacks will be called with this context object.
   *   Useful when needed to use some attributes of this context
   *   within the callbacks.
   *
   * @return mixed
   *   If no callback is set, will return the plain request response.
   *   Otherwise the callback response.
   */
  public static function request($endpoint, $verb = "GET", $headers = [], $body = [], $success_callback = NULL, $error_callback = NULL, $context = NULL) {
    self::initialize();

    $headers["Cache-Control"] = "no-cache";

    $response = self::$client->request($verb, $endpoint, [
      'json' => $body,
      'headers' => $headers,
    ]);

    $return = $response;
    if ($response->getStatusCode() === 200) {
      if (is_callable($success_callback)) {
        $return = call_user_func($success_callback, $response, $context);
      }
    }
    else {
      if (is_callable($error_callback)) {
        $return = call_user_func($error_callback, $response, $context);
      }
    }
    return $return;
  }

}
