<?php
/**
 * @file
 * gofast_features_global.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function gofast_features_global_default_rules_configuration() {
  $items = array();
  $items['og_gofast_og_member_subscribe_active_'] = entity_import('rules_config', '{ "og_gofast_og_member_subscribe_active_" : {
      "LABEL" : "GoFast OG member subscribe (Active)",
      "PLUGIN" : "reaction rule",
      "ACTIVE" : false,
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "php", "og" ],
      "ON" : { "og_user_insert" : [] },
      "IF" : [
        { "data_is" : { "data" : [ "og-membership:state" ], "value" : "1" } },
        { "entity_is_of_type" : { "entity" : [ "og-membership:group" ], "type" : "node" } }
      ],
      "DO" : [
        { "php_eval" : { "code" : "\\/\\/gofast_og_sendmail_user_added_group($og_membership);" } }
      ]
    }
  }');
  $items['rules_log_edit_userlist_clon_'] = entity_import('rules_config', '{ "rules_log_edit_userlist_clon_" : {
      "LABEL" : "Log edit Userlist",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules" ],
      "ON" : { "node_update--userlist" : { "bundle" : "userlist" } },
      "DO" : [
        { "entity_create" : {
            "USING" : {
              "type" : "message",
              "param_type" : "message_log",
              "param_user" : [ "site:current-user" ]
            },
            "PROVIDE" : { "entity_created" : { "entity_created" : "Created entity" } }
          }
        },
        { "data_set" : {
            "data" : [ "entity-created:field-target-id" ],
            "value" : [ "node:nid" ]
          }
        },
        { "data_set" : { "data" : [ "entity-created:field-message-log" ], "value" : "EUSL|" } }
      ]
    }
  }');
  $items['rules_log_edited_comment'] = entity_import('rules_config', '{ "rules_log_edited_comment" : {
      "LABEL" : "Log Edited Comment",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "comment" ],
      "ON" : { "comment_update" : [] },
      "DO" : [
        { "entity_create" : {
            "USING" : {
              "type" : "message",
              "param_type" : "message_log",
              "param_user" : [ "comment:author" ]
            },
            "PROVIDE" : { "entity_created" : { "entity_created" : "Created entity" } }
          }
        },
        { "data_set" : { "data" : [ "entity-created:field-message-log" ], "value" : "ECOM|" } },
        { "data_set" : {
            "data" : [ "entity-created:field-target-id" ],
            "value" : [ "comment:cid" ]
          }
        },
        { "data_set" : {
            "data" : [ "entity-created:field-node-id" ],
            "value" : [ "comment:node:nid" ]
          }
        }
      ]
    }
  }');
  $items['rules_log_edited_content'] = entity_import('rules_config', '{ "rules_log_edited_content" : {
      "LABEL" : "Log Edited Content",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules" ],
      "ON" : { "node_update" : [] },
      "IF" : [
        { "NOT node_is_of_type" : {
            "node" : [ "node" ],
            "type" : { "value" : { "userlist" : "userlist" } }
          }
        }
      ],
      "DO" : [
        { "entity_create" : {
            "USING" : {
              "type" : "message",
              "param_type" : "message_log",
              "param_user" : [ "node:author" ]
            },
            "PROVIDE" : { "entity_created" : { "entity_created" : "Created entity" } }
          }
        },
        { "data_set" : { "data" : [ "entity-created:field-message-log" ], "value" : "ECON|" } },
        { "data_set" : {
            "data" : [ "entity-created:field-target-id" ],
            "value" : [ "node:nid" ]
          }
        }
      ]
    }
  }');
  $items['rules_log_new_comment'] = entity_import('rules_config', '{ "rules_log_new_comment" : {
      "LABEL" : "Log New Comment",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "comment" ],
      "ON" : { "comment_insert" : [] },
      "DO" : [
        { "entity_create" : {
            "USING" : {
              "type" : "message",
              "param_type" : "message_log",
              "param_user" : [ "comment:author" ]
            },
            "PROVIDE" : { "entity_created" : { "entity_created" : "Created entity" } }
          }
        },
        { "data_set" : { "data" : [ "entity-created:field-message-log" ], "value" : "NCOM|" } },
        { "data_set" : {
            "data" : [ "entity-created:field-target-id" ],
            "value" : [ "comment:cid" ]
          }
        },
        { "data_set" : {
            "data" : [ "entity-created:field-node-id" ],
            "value" : [ "comment:node:nid" ]
          }
        }
      ]
    }
  }');
  $items['rules_log_new_content'] = entity_import('rules_config', '{ "rules_log_new_content" : {
      "LABEL" : "Log New Content",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules" ],
      "ON" : { "node_insert" : [] },
      "IF" : [
        { "NOT node_is_of_type" : {
            "node" : [ "node" ],
            "type" : { "value" : { "userlist" : "userlist" } }
          }
        }
      ],
      "DO" : [
        { "entity_create" : {
            "USING" : {
              "type" : "message",
              "param_type" : "message_log",
              "param_user" : [ "node:author" ]
            },
            "PROVIDE" : { "entity_created" : { "entity_created" : "Created entity" } }
          }
        },
        { "data_set" : { "data" : [ "entity-created:field-message-log" ], "value" : "NCON|" } },
        { "data_set" : {
            "data" : [ "entity-created:field-target-id" ],
            "value" : [ "node:nid" ]
          }
        }
      ]
    }
  }');
  $items['rules_log_new_userlist'] = entity_import('rules_config', '{ "rules_log_new_userlist" : {
      "LABEL" : "Log new Userlist",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules" ],
      "ON" : { "node_insert--userlist" : { "bundle" : "userlist" } },
      "DO" : [
        { "entity_create" : {
            "USING" : {
              "type" : "message",
              "param_type" : "message_log",
              "param_user" : [ "node:author" ]
            },
            "PROVIDE" : { "entity_created" : { "entity_created" : "Created entity" } }
          }
        },
        { "data_set" : {
            "data" : [ "entity-created:field-target-id" ],
            "value" : [ "node:nid" ]
          }
        },
        { "data_set" : { "data" : [ "entity-created:field-message-log" ], "value" : "NUSL|" } }
      ]
    }
  }');
  return $items;
}
