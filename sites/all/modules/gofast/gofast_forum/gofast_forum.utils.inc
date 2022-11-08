<?php

function gofast_forum_get_space_content($gid) {
    $query_forums = db_query("SELECT nid, title, uid FROM node LEFT JOIN og_membership ON og_membership.entity_type = 'node' AND og_membership.etid = node.nid WHERE og_membership.gid = :gid AND node.type = 'forum'", array(":gid" => $gid));
    $forums = [];
    foreach($query_forums as $result) {
        $user_props = gofast_get_properties_user_by_uid_or_u_name($result->uid, NULL, ["picture"]);
        $result->url_picture = gofast_get_url_picture_by_id($user_props->picture);
        $forums[] = $result;
    }
    drupal_json_output($forums);
    drupal_exit();
}
