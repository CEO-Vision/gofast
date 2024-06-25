<?php

/**
 * Extending the Entity for the BookmarkCollection entity.
 */
class BookmarkCollectionEntity extends Entity {

  /**
   * Change the default URI from default/id to bookmark_collection/id
   */
  protected function defaultUri() {
    return array('path' => 'bookmark_collection/' . $this->identifier());
  }

}

class BookmarkCollectionEntityController extends EntityAPIController {
  public function delete($ids, \DatabaseTransaction $transaction = NULL){
    global $user;

    $entities = $ids ? $this->load($ids) : FALSE;
    if (!$entities) {
      // Do nothing, in case invalid or no ids have been passed.
      return;
    }
    
    foreach ($entities as $bcid => $entity) {
      if($entity->uid == $user->uid){
        db_delete("gofast_bookmark_collections")
          ->condition("uid", $user->uid, "=")
          ->condition("bcid", $bcid, "=")
          ->execute();
        $this->resetCache(array($bcid));
      } else {
        drupal_set_message('You do not have the permission to delete this entity.', 'error');
      }
    }
    
  }
}