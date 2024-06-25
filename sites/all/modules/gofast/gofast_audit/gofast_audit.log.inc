<?php

/**
 * Function intended to write logs in other files than Drupal's main one, when needed (e.g. audit log)
 */
function gofast_audit_write_alternate_log($message, $prefix = "drupal_audit", $severity = WATCHDOG_INFO) {
    openlog($prefix, LOG_NDELAY, LOG_LOCAL1);
    syslog($severity, $message);
    closelog();
    $default_facility = defined('LOG_LOCAL0') ? LOG_LOCAL0 : LOG_USER;
    openlog(variable_get('syslog_identity', 'drupal'), LOG_NDELAY, variable_get('syslog_facility', $default_facility));
}

function gofast_audit_insert_line_audit($nid, $event_type, $last_event_serialized, $last_event_unserialized)
{
    $table_name = GOFAST_AUDIT_TABLE_NAME;
    // we insert this event in the audit table
    db_query("INSERT INTO {" . $table_name . "} (nid,timestamp,uid,details,event_type) VALUES ('" . $nid . "', '" . $last_event_unserialized["mod_timestamp"] . "'"
        . ", '" . $last_event_unserialized["mod_author"] . "', '" . $last_event_serialized . "', '" . $event_type . "')");
    // also write in a dedicated log file
    gofast_audit_write_alternate_log("Event $event_type audited on node $nid. Details: " . json_encode($last_event_unserialized));
}
