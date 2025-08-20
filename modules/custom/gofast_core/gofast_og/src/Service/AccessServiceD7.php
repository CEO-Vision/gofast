<?php

namespace Drupal\gofast_og\Service;

use Psr\Log\LoggerInterface;
use Drupal\Core\Access\AccessResult;
use Drupal\Core\Routing\Access\AccessInterface;
use Drupal\Core\Session\AccountInterface;
use Drupal\Core\Entity\EntityTypeManagerInterface;
use Drupal\gofast_core\Utils\RequestUtils;
use Symfony\Component\HttpFoundation\Request;

/**
 * Access interface to handle OG-related D7 access.
 */
class AccessServiceD7 implements AccessInterface {
  /**
   * The entity type manager service.
   *
   * @var \Drupal\Core\Entity\EntityTypeManagerInterface
   */
  protected $entityTypeManager;

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
   * Constructs a new AccessServiceD7 object.
   *
   * @param \Drupal\Core\Entity\EntityTypeManagerInterface $entityTypeManager
   *   The entity type manager service.
   * @param \Psr\Log\LoggerInterface $logger
   *   The logger.
   */
  public function __construct(EntityTypeManagerInterface $entityTypeManager, LoggerInterface $logger) {
    $this->logger = $logger;
    $this->entityTypeManager = $entityTypeManager;
  }

  /**
   * Checks access to groups for a given node.
   *
   * @param object $account
   *   The user account object.
   *
   * @return \Drupal\Core\Access\AccessResult
   *   The access result.
   */
  protected function checkNodeGroupAccess($account) {
    $node = $this->request->attributes->get('node');
    if (!$node) {
      return AccessResult::forbidden();
    }

    $bundle = $node->bundle();
    $group_relationships = $this->getGroupRelationships($node->id(), $bundle);

    foreach ($group_relationships as $relationship) {
      /** @var \Drupal\group\Entity\GroupRelationship $relationship */
      $group = $relationship->getGroup();
      if ($group) {
        // Group exists on D10, no D7 checks needed.
        continue;
      }

      $gid = $relationship->get("gid")->target_id;
      $access_result = $this->checkGroupAccess($gid, $account->uid);
      if ($access_result->isForbidden()) {
        return $access_result;
      }
    }

    return AccessResult::allowed();
  }

  /**
   * Gets group relationships for a given entity ID and bundle.
   *
   * @param int $entity_id
   *   The entity ID.
   * @param string $bundle
   *   The entity bundle.
   *
   * @return \Drupal\group\Entity\GroupRelationship[]
   *   An array of group relationship entities.
   */
  protected function getGroupRelationships($entity_id, $bundle) {
    $storage = $this->entityTypeManager->getStorage('group_relationship');
    return $storage->loadByProperties([
      'entity_id' => $entity_id,
      'plugin_id' => "group_node:$bundle",
    ]);
  }

  /**
   * Checks access to a group using an external API.
   *
   * @param int $gid
   *   The group ID.
   * @param int $user_id
   *   The user ID.
   *
   * @return \Drupal\Core\Access\AccessResult
   *   The access result.
   */
  protected function checkGroupAccess($gid, $user_id) {
    $hostname = $this->request->getHost();
    $endpoint = "https://$hostname/api/node/access?nid=$gid";

    try {
      $response = RequestUtils::request($endpoint, "GET");
      if ($response->getStatusCode() !== 200) {
        $this->logger->error("Error while requesting D7 node_access API for D10 user $user_id on D7 space $gid");
        return AccessResult::forbidden();
      }

      $body = json_decode($response->getBody()->getContents());
      $access_string = json_encode($body->access);
      if (!$access_string) {
        return AccessResult::forbidden();
      }

      $this->logger->info("Got authorization $access_string for D10 user $user_id on D7 space $gid");
      return AccessResult::allowed();
    }
    catch (\Exception $e) {
      $this->logger->error("HTTP request failed: " . $e->getMessage());
      return AccessResult::forbidden();
    }
  }

  /**
   * Trigger the access check.
   */
  public function access(Request $request, AccountInterface $account) {

    $this->request = $request;
    $cookies = $this->request->cookies->all();
    $hostname = $this->request->getHost();
    if (isset($cookies['gofast_user'])) {
      RequestUtils::updateCookies($cookies, $hostname);
    }
    return $this->checkNodeGroupAccess($account);
  }

}
