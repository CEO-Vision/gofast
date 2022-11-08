<?php

/**
 * @file Deferred incident storage class
 */

class RadioactivityDeferredIncidentStorage extends RadioactivityIncidentStorage {

  /**
   * Constructor
   */
  public function __construct() {}

  /**
   * add incident to the deferred storage
   * @entity_energy energy by entity id
   */
  public function addIncident(RadioactivityIncident $incident) {

    db_insert('radioactivity_deferred_incidents')->fields(array('data' => serialize($incident)))->execute();
  }

  /**
   * Process incidents in the deferred queue
   */
  public function processIncidents() {

    // grab rows from table and push them to fields

    $query = db_select("radioactivity_deferred_incidents", "rds")->fields("rds", array("data"));

    $result = $query->execute();

    while ($row = $result->fetch()) {
      $incident = unserialize($row->data);
      //Patch CEO-vision GOFast
      $exist=true;
      if($incident->entityType=='node'){
         $exist = db_query('SELECT nid FROM {node} WHERE nid = :nid', array(':nid'=> $incident->entityId))->fetchField();
      }
      elseif($incident->entityType=='user'){
          $exist = db_query('SELECT uid FROM {user} WHERE uid = :uid', array(':uid'=> $incident->entityId))->fetchField();
      }
      if ($exist && $incident->floodCheck()) {
        $incident->updateEnergy();
      }
    }

    // Flush the processed entries from the db
    db_delete("radioactivity_deferred_incidents")->execute();
  }
}
