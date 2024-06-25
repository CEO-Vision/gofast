<?php

/**
 * Implements hook_drush_command().
 */
function gofast_migrate_drush_command() {

  $items['post-migrate-operations'] = array(
    'description' => 'Execute Post-migration operations.',
    'aliases' => array('pmo'),
    'callback' => "gofast_migrate_post_migrate"
  );
  
  $items['rebuild-doc-emplacements'] = array(
    'description' => 'Rebuild the emplacement of the documents.',
    'aliases' => array('rde'),
    'callback' => "gofast_migrate_reset_doc_emplacements"
  );
  
  $items['cmis-rebuld-properties'] = array(
    'description' => 'Rebuild all Alfresco properties for each nodes.',
    'aliases' => array('crp'),
    'callback' => "gofast_migrate_rebuild_properties"
  );
  
  $items['extranet-rebuld-format'] = array(
    'description' => 'Rebuild brokens format field for extranet.',
    'aliases' => array('erf'),
    'callback' => "gofast_migrate_rebuild_extranet"
  );
  
  $items['private-spaces-rebuild'] = array(
    'description' => 'Rebuild users private spaces.',
    'aliases' => array('psr'),
    'callback' => "gofast_migrate_rebuild_private_spaces"
  );
  
  $items['private-spaces-link'] = array(
    'description' => 'Relink users private spaces.',
    'aliases' => array('psl'),
    'callback' => "gofast_migrate_relink_private_spaces"
  );
  
  $items['rebuild-ldap'] = array(
    'description' => 'Rebuild LDAP.',
    'aliases' => array('rldap'),
    'callback' => "gofast_migrate_rebuild_ldap"
  );
  
  $items['migrate'] = array(
    'description' => 'Migrate',
    'aliases' => array('mig'),
    'callback' => "gofast_migrate_migrate"
  );
  
  $items['rebuild-multifiled-documents'] = array(
    'description' => 'Rebuild the permissions and things about the multifiled documents',
    'aliases' => array('rmd'),
    'callback' => "gofast_migrate_rebuild_multifiled_documents"
  );
  
  $items['cmis-rename-folders'] = array(
    'description' => 'Rename spaces folder',
    'aliases' => array('crf'),
    'callback' => "gofast_migrate_rename_folders"
  );
  
  $items['prepare-extranet-migration'] = array(
    'description' => 'Prepare extranet content migration (membership...)',
    'aliases' => array('pem'),
    'callback' => "gofast_migrate_prepare_extranet_migration"
  );
  
  $items['relink_public_extranet'] = array(
    'description' => 'Relink publc and extranet content with theirs folders',
    'aliases' => array('rpe'),
    'callback' => "gofast_migrate_relink_public_extranet"
  );
  
  $items['rebuild_group_access'] = array(
    'description' => 'Rebuild field_data_group_access',
    'aliases' => array('rga'),
    'callback' => "gofast_migrate_rebuild_group_access"
  );
  
  $items['rebuild_memberships'] = array(
    'description' => 'Rebuild memberships',
    'aliases' => array('rmb'),
    'callback' => "gofast_migrate_rebuild_memberships"
  );
  
  $items['rebuild_taxonomy'] = array(
    'description' => 'Rebuild taxonomy',
    'aliases' => array('rtx'),
    'callback' => "gofast_migrate_rebuild_taxonomy"
  );
  
  $items['private_space_rights_update'] = array(
    'description' => 'Rebuild taxonomy',
    'aliases' => array('psru'),
    'callback' => "gofast_migrate_private_ru"
  );
  
  $items['rebuild_default_role'] = array(
    'description' => 'Rebuild default role',
    'aliases' => array('rdr'),
    'callback' => "gofast_migrate_rebuild_default_role"
  );
  
  $items['rebuild_uuid'] = array(
    'description' => 'Rebuild UUIDS',
    'aliases' => array('ruuid'),
    'callback' => "gofast_migrate_rebuild_uuids"
  );
  
  $items['rebuild_pp'] = array(
    'description' => 'Rebuild Profile Pictures',
    'aliases' => array('rpp'),
    'callback' => "gofast_migrate_rebuild_profile_pictures"
  );
  
  $items['rebuild_main_organization'] = array(
    'description' => 'Rebuild Main Organisation',
    'aliases' => array('rmo'),
    'callback' => "gofast_migrate_rebuild_main_organization"
  );
  
  $items['rebuild_body'] = array(
    'description' => 'Rebuild Body Field',
    'aliases' => array('rbd'),
    'callback' => "gofast_migrate_rebuild_body"
  );
  
  $items['rebuild_author'] = array(
    'description' => 'Rebuild Author Field',
    'aliases' => array('rauth'),
    'callback' => "gofast_migrate_rebuild_author"
  );

  $items['rebuild_revisions'] = array(
    'description' => 'Rebuild Revisions',
    'aliases' => array('rrev'),
    'callback' => "gofast_migrate_rebuild_revisions"
  );
  
  $items['migrate_aife'] = array(
    'description' => 'Migrate AIFE fields and things',
    'aliases' => array('maife'),
    'callback' => "gofast_migrate_aife"
  );
  
  $items['migrate_integrity'] = array(
    'description' => 'Integrity check',
    'aliases' => array('minteg'),
    'callback' => "gofast_migrate_integrity"
  );
  
  
  return $items;
}

function gofast_migrate_rebuild_body(){
  db_query("delete from field_data_body WHERE 1");
  db_query("delete from field_revision_body WHERE 1");
  
  //Retrieve all nodes
  $node_ids = db_select("node", 'n')
          ->fields('n', array('nid', 'vid', 'type', 'language'))
          ->execute()
          ->fetchAll();
  drush_log('Rebuilding body of '.count($node_ids).'.', 'ok');
  foreach($node_ids as $node_descr){
    $nid = $node_descr->nid;
    $type = $node_descr->type;
    $vid = $node_descr->vid;
    $lang = $node_descr->language;
    try { //We get a connection to VMCLONE, warning, static var set in code, to pass as a drush param
      $connex = new PDO('mysql:host=172.30.111.55;dbname=drupal;port=3306', 'root', '', array(PDO::MYSQL_ATTR_INIT_COMMAND => "SET NAMES utf8"));
    }catch (Exception $e){
      echo('Erreur : ' . $e->getMessage());
    }
    $body_teaser = $connex->query("select body,teaser from node_revisions where nid=".$nid)->fetch();
    $body = utf8_encode($body_teaser['body']);
    $teaser = utf8_encode($body_teaser['teaser']);
    
    try{
      db_insert("field_data_body")
              ->fields(array(
                'entity_type' => 'node',
                'bundle' => $type,
                'deleted' => 0,
                'entity_id' => $nid,
                'revision_id' => $vid,
                'language' => 'und',
                'delta' => 0,
                'body_value' => $body,
                'body_summary' => $teaser,
                'body_format' => 'full_html',
              ))->execute(); 
    db_insert("field_revision_body")
              ->fields(array(
                'entity_type' => 'node',
                'bundle' => $type,
                'deleted' => 0,
                'entity_id' => $nid,
                'revision_id' => $vid,
                'language' => 'und',
                'delta' => 0,
                'body_value' => $body,
                'body_summary' => $teaser,
                'body_format' => 'full_html',
              ))->execute(); 
    }catch(Exception $e){
      drush_log($e, 'error');
    }
    echo(".");
    usleep(100000);
  }
  drush_log('', 'ok');
  drush_log('End of rebuild', 'ok');
}

function gofast_migrate_rebuild_author(){
  db_query("delete from field_data_field_document_author WHERE 1");
  db_query("delete from field_revision_field_document_author WHERE 1");

  //Retrieve all nodes
  $node_ids = db_select("node", 'n')
          ->fields('n', array('nid', 'vid', 'type', 'language'))
          ->condition('type', 'alfresco_item', '=')
          ->execute()
          ->fetchAll();
  drush_log('Rebuilding document author of '.count($node_ids).'.', 'ok');
  foreach($node_ids as $node_descr){
    $nid = $node_descr->nid;
    $type = $node_descr->type;
    $vid = $node_descr->vid;
    $lang = $node_descr->language;
    try { //We get a connection to VMCLONE, warning, static var set in code, to pass as a drush param
      $connex = new PDO('mysql:host=10.75.194.21;dbname=drupal;port=3306', 'drupal', '', array(PDO::MYSQL_ATTR_INIT_COMMAND => "SET NAMES utf8"));
    }catch (Exception $e){
      echo('Erreur : ' . $e->getMessage());
    }
    $body_teaser = $connex->query("select field_document_author_value from content_field_document_author where nid=".$nid)->fetch();
    $value = $body_teaser['field_document_author_value'];
        if(!empty($value)){
    try{
      db_insert("field_data_field_document_author")
              ->fields(array(
                'entity_type' => 'node',
                'bundle' => $type,
                'deleted' => 0,
                'entity_id' => $nid,
                'revision_id' => $vid,
                'language' => 'und',
                'delta' => 0,
                'field_document_author_value' => $value,
                'field_document_author_format' => NULL,
              ))->execute();
       db_insert("field_revision_field_document_author")
              ->fields(array(
                'entity_type' => 'node',
                'bundle' => $type,
                'deleted' => 0,
                'entity_id' => $nid,
                'revision_id' => $vid,
                'language' => 'und',
                'delta' => 0,
                'field_document_author_value' => $value,
                'field_document_author_format' => NULL,
              ))->execute();
    }catch(Exception $e){
      drush_log($e, 'error');
    }
}
    echo(".");
    usleep(10000);
  }
  drush_log('', 'ok');
  drush_log('End of rebuild', 'ok');
}

function gofast_migrate_rebuild_main_organization(){
  drush_log('Rebuilding main organization...', 'ok');
  //We get all main organizations
  $main_organizations = db_select('field_data_ldap_user_ou', 'ou')
          ->fields('ou')
          ->execute();
  $stats = 0;
  while($main_organization = $main_organizations->fetch()){//Fetching
    $value = $main_organization->ldap_user_ou_value;
    $etid = $main_organization->entity_id;
    
    if(isset($value) && !empty($value) && !strpos($value, '_')){ //The value exists and is to rebuild
      //We search for the node and extract it's nid
      $organization = db_select('node', 'n')
              ->fields('n', array('nid', 'title'))
              ->condition('title', $value)
              ->execute()
              ->fetchAssoc();
      //We build the new value
      $title = $organization['title'];
      $nid = $organization['nid'];
      $new_value = $title . '_#' . $nid;
      //Then we reimplement it in the field
      db_update('field_data_ldap_user_ou')
              ->fields(array('ldap_user_ou_value' => $new_value))
              ->condition('entity_id', $etid)
              ->execute();
      echo('.');
      $stats++;
    }
  }
  drush_log('', 'ok');
  cache_clear_all();
  drupal_flush_all_caches();
  drush_log('Main organizations fixed for '.$stats.' elements.', 'success');
}

/*
 * Rebuild users profile picture
 * Warning: Usually, this function can only be called once, after migration process
 */
function gofast_migrate_rebuild_profile_pictures(){
  try { //We get a connection to VMCLONE, warning, static var set in code, to pass as a drush param
    $connex = new PDO('mysql:host=10.75.194.21;dbname=drupal;port=3306', 'drupal', '');
  }catch (Exception $e){
    echo('Erreur : ' . $e->getMessage());
  }
  $users = $connex->query('select uid,picture from users');
  while($user = $users->fetch()){ //Fetching into all users
    $uid = $user['uid'];
    
    $picture = $user['picture'];
    $picture_split = explode('/', $picture);
    $picture_split = array_reverse($picture_split);
    if($picture_split['0'] !== 'picture-default.jpg'){
      $pic_name = $picture_split['0'];
      $pic_id = $picture_split['1'];
      if(is_numeric($pic_id)){
        $pic_format = explode('.', $pic_name);
        $pic_format = array_reverse($pic_format);
        $pic_format = $pic_format[0];
        $pic_name = str_replace('.thumbnail-'.$pic_id.'.'.$pic_format, '', $pic_name);
        $new_name = "picture-".$pic_id."-".time().".".$pic_format;
        
        db_insert("file_managed")
              ->fields(array(
                'fid' => $pic_id,
                'uid' => $uid,
                'filename' => "picture-".$pic_id."-".time().".".$pic_format,
                'uri' => 'public://pictures/'.$new_name,
                'filemime' => 'image/'.$pic_format,
                'filesize' => '50000',
                'status' => 1,
                'uuid' => uuid_generate()                
              ))->execute(); 
        
        rename("/var/www/d7/sites/default/files/pictures/".$pic_id."/".$pic_name, "/var/www/d7/sites/default/files/pictures/".$new_name);
        db_query("update users set picture='".$pic_id."' where uid='".$uid."'");
        
      }
    }
  }
}

/*
 * Rebuild UUID to menu and base taxonomy entries
 */
function gofast_migrate_rebuild_uuids(){
  //Include UUID features
  include_once('/var/www/d7/sites/all/modules/gofast_features/gofast_features_uuid/gofast_features_uuid.features.uuid_features_menu.inc');
  include_once('/var/www/d7/sites/all/modules/gofast_features/gofast_features_taxonomy/gofast_features_taxonomy.features.uuid_term.inc');
  drush_log('Rebuilding menu UUIDs', 'ok');
  
  //We retrieve the menu UUIDs from features
  $menus = gofast_features_uuid_menu_default_uuid_features_menu();
  $stats = 0;
  
  foreach($menus as $uuid => $data){ //For each menus, we set UUID
    $link_path = $data['link_path'];
    $router_path = $data['router_path'];
    $link_title= $data['link_title'];
    db_query("UPDATE menu_links set uuid='".$uuid."' WHERE hidden=0 AND router_path='".$router_path."' AND link_path='".$link_path."' AND link_title='".$link_title."'");
    echo('.');
    $stats++;
  }
  drush_log('', 'ok');
  drush_log('UUID reset on '.$stats.' menus', 'success');
  
  //We retrieve the taxo UUIDs from features
  $taxo = gofast_features_taxonomy_uuid_features_default_terms();
  
  drush_log('Rebuilding taxonomy UUIDs', 'ok');
  $stats = 0;
  
  foreach($taxo as $uuid => $data){ //For each term, we set UUID
    $source = $data['name'];
    $uuid = $data['uuid'];
    db_query("UPDATE taxonomy_term_data set uuid='".$uuid."' WHERE name='".$source."' LIMIT 1");
    echo('.');
    $stats++;
  }
  drush_log('', 'ok');
  drush_log('UUID reset on '.$stats.' term', 'success');
}

/*
 * Rebild users default role if needed
 */
function gofast_migrate_rebuild_default_role(){
  $users_query = db_query("SELECT uid from users");
  $users = $users_query->fetchAll();
  $stats = 0;
  foreach($users as $user){ //Fetching into all users
    $uid = $user->uid;
    $rid = $uid;
    
    //$count will be 0 if the user doesn't has a default role
    $current_dr = db_query("select count(*) from field_data_field_default_role where entity_id='".$uid."'")->fetchAssoc();
    $count = $current_dr['count(*)'];
    
    if($count == 0){//The user hasn't a default role
      db_insert("field_data_field_default_role")
      ->fields(array(
        'entity_type' => 'user',
        'bundle' => 'user',
        'deleted' => 0,
        'entity_id' => $uid,
        'revision_id' => $rid,
        'language' => 'und',
        'delta' => 0,
        'field_default_role_value' => 1 //Contributor role if affected
      ))->execute();  
      echo('.');
      $stats ++;
    } 
  }
  drush_log('', 'ok');
  drush_log('Default role has been rebuilt for '.$stats.' user(s).', 'success'); 
  
  foreach($users as $user){ //Fetching into all users
    $uid = $user->uid;
    $rid = $uid;
    
    //$count will be 0 if the user doesn't has a default role
    $current_dr = db_query("select count(*) from users_roles where uid='".$uid."'")->fetchAssoc();
    $count = $current_dr['count(*)'];
    
    if($count == 0){//The user hasn't a default role
      db_insert("users_roles")
      ->fields(array(
        'uid' => $uid,
        'rid' => 4 //Standard role if affected
      ))->execute();  
      echo('.');
      $stats ++;
    } 
  }
  drush_log('', 'ok');
  drush_log('Platform role has been rebuilt for '.$stats.' user(s).', 'success'); 
}

/*
 * Update users rights in their private spaces
 */
function gofast_migrate_private_ru(){
  $private_ids = db_select("node", 'n')
          ->fields('n', array('nid'))
          ->condition('type', 'private_space', '=')
          ->execute()
          ->fetchAll();
  foreach($private_ids as $nid){ //Fething into private spaces
      $nid = $nid->nid;
      $node = node_load($nid);
      $roles_query = og_roles('node', 'private_space', $nid, FALSE, FALSE);
      foreach($roles_query as $rkey => $roles){ //We get the roles ids in this space
        if($roles == GOFAST_OG_ROLE_ADMIN){
          $admin_rid = $rkey;
        }
        if($roles == GOFAST_OG_ROLE_READ_ONLY){
          $readonly_rid = $rkey;
        }
        if($roles == GOFAST_OG_ROLE_STANDARD){
          $contributor_rid = $rkey;
        }
      }
      foreach(gofast_og_get_members($node) as $uid){ //We set admin role
        og_role_revoke('node', $nid, $uid, $readonly_rid);
        og_role_revoke('node', $nid, $uid, $contributor_rid);
        og_role_revoke('node', $nid, $uid, $admin_rid);
        og_role_grant('node', $nid, $uid, $admin_rid);
      }
  }
}

/*
 * This is a workaround function to delete when the migration module will be completed
 */
function gofast_migrate_migrate(){
  usurp(1);
  /*$forum_ids = db_select("node", 'n')
          ->fields('n', array('nid'))
          ->condition('type', 'forum', '=')
          ->execute()
          ->fetchAll();
  foreach($forum_ids as $forum_id){
    $nid = $forum_id->nid;
    $data = node_load($nid);
    db_insert("field_data_taxonomy_forums")
      ->fields(array(
        'entity_type' => 'node',
        'bundle' => $data->type,
        'deleted' => 0,
        'entity_id' => $data->nid,
        'revision_id' => $data->rid,
        'language' => 'und',
        'delta' => 0,
        'taxonomy_forums_tid' => 1
      ))->execute();    
  }*/
  /*$qi = 0;
  set_time_limit(0);
  $queries['og_membership']['fields'] = "type,etid,entity_type,gid,group_type,state,created,field_name,language";
  
  //Looking for non attached Spaces to their main spaces
    $query = db_query("SELECT nid,type from node WHERE (SELECT COUNT(*) FROM og_membership WHERE og_membership.etid=node.nid AND og_membership.field_name='og_group_ref')!=1 AND (node.type='group' OR node.type='organisation' OR node.type='extranet' OR node.type='public') AND (node.nid > 7 OR node.nid < 4)");
    $stats_inherited=0;
    while($inherited = $query->fetch()){ //Matching each inherited spaces with their spaces
      $stats_inherited++;
      switch($inherited->type){
        case 'group':
          $queries['og_membership']['values'][$qi][] = 'og_membership_type_default';
          $queries['og_membership']['values'][$qi][] = $inherited->nid;
          $queries['og_membership']['values'][$qi][] = 'node';
          $queries['og_membership']['values'][$qi][] = '4';
          $queries['og_membership']['values'][$qi][] = 'node';
          $queries['og_membership']['values'][$qi][] = '1';
          $queries['og_membership']['values'][$qi][] = time();
          $queries['og_membership']['values'][$qi][] = 'og_group_ref';
          $queries['og_membership']['values'][$qi][] = 'en';
          $qi++;
          break;
        case 'organisation':
          $queries['og_membership']['values'][$qi][] = 'og_membership_type_default';
          $queries['og_membership']['values'][$qi][] = $inherited->nid;
          $queries['og_membership']['values'][$qi][] = 'node';
          $queries['og_membership']['values'][$qi][] = '5';
          $queries['og_membership']['values'][$qi][] = 'node';
          $queries['og_membership']['values'][$qi][] = '1';
          $queries['og_membership']['values'][$qi][] = time();
          $queries['og_membership']['values'][$qi][] = 'og_group_ref';
          $queries['og_membership']['values'][$qi][] = 'en';
          $qi++;
          break;
        case 'extranet':
          $queries['og_membership']['values'][$qi][] = 'og_membership_type_default';
          $queries['og_membership']['values'][$qi][] = $inherited->nid;
          $queries['og_membership']['values'][$qi][] = 'node';
          $queries['og_membership']['values'][$qi][] = '6';
          $queries['og_membership']['values'][$qi][] = 'node';
          $queries['og_membership']['values'][$qi][] = '1';
          $queries['og_membership']['values'][$qi][] = time();
          $queries['og_membership']['values'][$qi][] = 'og_group_ref';
          $queries['og_membership']['values'][$qi][] = 'en';
          $qi++;
          break;
        case 'public':
          $queries['og_membership']['values'][$qi][] = 'og_membership_type_default';
          $queries['og_membership']['values'][$qi][] = $inherited->nid;
          $queries['og_membership']['values'][$qi][] = 'node';
          $queries['og_membership']['values'][$qi][] = '7';
          $queries['og_membership']['values'][$qi][] = 'node';
          $queries['og_membership']['values'][$qi][] = '1';
          $queries['og_membership']['values'][$qi][] = time();
          $queries['og_membership']['values'][$qi][] = 'og_group_ref';
          $queries['og_membership']['values'][$qi][] = 'en';
          $qi++;
          break;
        default:
          drush_log("node ".$inherited->nid." of type ".$inherited->type." cannot be match with a root space.", 'warning');
          break;
      }
      echo(".");
    }
    drush_log("", 'ok');
    drush_log($stats_inherited." inherited nodes has been found and set to a root space", 'success');
    
  drupal_static_reset();
  drush_log("Sending queries to database.", 'ok');
  //Send queries
  foreach ($queries as $table => $data){ //Fetching into all queries by table
    $values_global = "";
    foreach($data['values'] as $entry){ //Fetching into all line add in table's query
      $values = "";
      foreach($entry as $row){ //Fetching into all field into this line
        str_replace("'", "''", $row); //Prepare for base
        $values .= "'".$row."', "; //Formating as 'value', 'value1', ...
      }
      $values_global .= "(".substr($values, '0', '-2')."),";
    }
    $values_global = substr($values_global, '0', '-1');
    db_query("INSERT IGNORE INTO ".$table." (".$data['fields'].") VALUES ".$values_global);
    echo(".");
  }
  drush_log("", 'ok');*/
  /*$private_spaces = db_select("field_data_group_group", 'n')
          ->fields('n')
          ->condition('bundle', 'private_space')
          ->execute()
          ->fetchAll();
  foreach($private_spaces as $private){
    $nid = $private->entity_id;
    $rid = $private->revision_id;
    $uuid='none';
    db_insert("node")
      ->fields(array(
        'nid' => $nid,
        'vid' => $rid,
        'type' => 'private_space',
        'language' => 'und',
        'title' => 'My private space',
        'uid' => '1',
        'status' => '1',
        'created' => 0,
        'changed' => 0,
        'comment' => 0,
        'promote' => 0,
        'sticky' => 0,
        'tnid' => 0,
        'translate' => 0,
        'uuid' => $uuid
      ))->execute();
  }*/
  
  /*try {
    $connex = new PDO('mysql:host=80.245.17.90;dbname=drupal;port=3306', 'root', '');
  }
  catch (Exception $e)
  {
          echo('Erreur : ' . $e->getMessage());
  }
  $users = $connex->query('select uid, picture from users');
  while($user = $users->fetch()){
    $uid = $user['uid'];
    $picture = $user['picture'];
    $picture_split = explode('/', $picture);
    $picture_split = array_reverse($picture_split);
    if($picture_split['0'] !== 'picture-default.jpg'){
      $pic_name = $picture_split['0'];
      $pic_id = $picture_split['1'];
      if(is_numeric($pic_id)){
        $pic_format = explode('.', $pic_name);
        $pic_format = array_reverse($pic_format);
        $pic_format = $pic_format[0];
        $pic_name = str_replace('.thumbnail-'.$pic_id.'.'.$pic_format, '', $pic_name);
        $new_name = "picture-".$pic_id."-".time().".".$pic_format;
        
        db_insert("file_managed")
              ->fields(array(
                'fid' => $pic_id,
                'uid' => $uid,
                'filename' => "picture-".$pic_id."-".time().".".$pic_format,
                'uri' => 'public://pictures/'.$new_name,
                'filemime' => 'image/'.$pic_format,
                'filesize' => '50000',
                'status' => 1,
                'uuid' => uuid_generate()                
              ))->execute(); 
        
        rename("/var/www/d7/sites/default/files/pictures/".$pic_id."/".$pic_name, "/var/www/d7/sites/default/files/pictures/".$new_name);
        db_query("update users set picture='".$pic_id."' where uid='".$uid."'");
      }
    }
  }*/
  /*drush_log('Rebuilding node access table', 'ok');
  db_query("DELETE FROM field_data_group_access WHERE 1");
  $group_ids = db_select("node", 'n')
          ->fields('n', array('nid'))
          ->condition('type', 'group', '=')
          ->execute()
          ->fetchAll();
  $organisations_ids = db_select("node", 'n')
          ->fields('n', array('nid'))
          ->condition('type', 'organisation', '=')
          ->execute()
          ->fetchAll();
  $extranet_ids = db_select("node", 'n')
          ->fields('n', array('nid'))
          ->condition('type', 'extranet', '=')
          ->execute()
          ->fetchAll();
  $public_ids = db_select("node", 'n')
          ->fields('n', array('nid'))
          ->condition('type', 'public', '=')
          ->execute()
          ->fetchAll();
  $private_ids = db_select("node", 'n')
          ->fields('n', array('nid'))
          ->condition('type', 'private_space', '=')
          ->execute()
          ->fetchAll();
    $entity_ids = array_merge($group_ids, $organisations_ids, $extranet_ids, $public_ids, $private_ids);
  foreach($entity_ids as $space){
    $node = node_load($space->nid);
    db_insert("field_data_group_access")
              ->fields(array(
                'entity_type' => 'node',
                'bundle' => $node->type,
                'deleted' => '0',
                'entity_id' => $node->nid,
                'revision_id' => $node->rid,
                'language' => 'und',
                'delta' => 0,
                'group_access_value' => 1,
              ))->execute(); 
    echo('.');
  }
  drush_log('','ok');
  drush_log('Node access has been rebuilt in database, now rebuilding in node module tables', 'ok');
  cache_clear_all();
  drupal_flush_all_caches();
  node_access_rebuild();
  drush_log('Node access has been full rebuilt', 'success');*/
  /*drush_log('Rebuild parent table', 'ok');
  db_query("DELETE FROM taxonomy_term_hierarchy WHERE 1");
  $terms = db_query("SELECT * FROM taxonomy_term_data");
  while($term = $terms->fetch()){
    $tid = $term->tid;
    db_insert("taxonomy_term_hierarchy")
              ->fields(array(
                'tid' => $tid,
                'parent' => 0,
              ))->execute(); 
  }
  drush_log('Parent table rebuilt', 'ok');
  db_query("UPDATE taxonomy_term_data SET language='und'"); //Fix translation possible issues*/
  /*drush_log('Rebuild users format', 'ok');
  db_query("DELETE FROM field_data_field_format WHERE bundle='user'");
  $profil = taxonomy_get_term_by_name('Profil', 'format');
  $profil_tid = reset($profil)->tid;
  $users = db_select("users", 'n')
          ->fields('n', array('uid'))
          ->execute()
          ->fetchAll();
  foreach($users as $user){
    $uid = $user->uid;
    if($uid == 0){
      continue;
    }
    db_insert("field_data_field_format")
              ->fields(array(
                'entity_type' => 'user',
                'bundle' => 'user',
                'deleted' => '0',
                'entity_id' => $uid,
                'revision_id' => $uid,
                'language' => 'und',
                'delta' => 0,
                'field_format_tid' => $profil_tid,
              ))->execute();
  }*/
  /*db_query("DELETE from node_revision WHERE 1");
  $revisions = db_query("SELECT nid,vid,uid,title,comment,promote,sticky,changed,status from node");
  drush_log("Rebuilding revisions..", 'ok');
  while($revision = $revisions->fetch()){
    db_insert("node_revision")
      ->fields(array(
        'nid' => $revision->nid,
        'vid' => $revision->vid,
        'uid' => $revision->uid,
        'title' => $revision->title,
        'log' => "",
        'timestamp' => $revision->changed,
        'status' => $revision->status,
        'comment' => $revision->comment,
        'promote' => $revision->promote,
        'sticky' => $revision->sticky,
        'vuuid' => uuid_generate(),
      ))->execute();
    echo(".");
  }
  drush_log("", 'ok');
  drush_log("Drupal revisions have been rebuilt", 'success');*/
  $nodes = db_query("select * from og_membership where gid='4' AND field_name='og_group_content_ref' LIMIT 5;");

  while($node_item = $nodes->fetch()){
    $node = node_load($node_item->etid);
  $item_id = $node->field_reference['und'][0]['value'];
  /*
  * ________Location/Space update________
  */
      //Retrieve all spaces of the alfresco node
      $parents = gofast_cmis_item_get_parent($item_id, TRUE); 
  $paths = array();
      foreach($parents->objectList as $parent){
        $paths[] = $parent->properties["cmis:path"];
      }
      $field = GOFAST_CMIS_LOCATIONS_FIELD;
      print('JE SUIS UN PASSE.. OU UN PATH.. ON SAIT PAS');
  print_r($paths);
        //Prepare and send the request to gofast_xeditable
        $_POST['pk'] = $node->nid;
        $_POST['name'] = $field;
        $_POST['value'] = $paths;
        $_POST['non_xeditable'] = TRUE;
        $_POST['technically_save'] = TRUE;
          print('plop');
       gofast_update_node_field();
       usurp(1);

  }
}

/*
 * Explore the integrity report and rebuild taxonomy (tags) if needed
 */
function gofast_migrate_rebuild_taxonomy(){
  $diffs = variable_get('gofast_result_integrity_check', array());
  foreach($diffs as $nid => $diff_content){ //Fetching into all nodes in difference
    foreach($diff_content as $field=>$value){//Fetchings into all fields in difference in the node
      if($field === 'tags'){ //There is a difference in tags
        drush_log('Diff on tags on node '.$nid, 'warning');
        $value = str_replace(' / ', '/', $value); //Fix formatting issue
        $diff_value = explode('/', $value); //We get all tags as an array
        
        $before = explode(';', $diff_value[0]); //Tags as they was in GF2
        $after = explode(';', $diff_value[1]);  //Tags as they are in GF3
        
        $missings = array_diff($before, $after);
        $missings = implode(';', $missings);
        
        //TODO: Use sth like array_diff, experimentations needed
        foreach($after as $key_a => $after_item){ //Fetching into current terms
          foreach($before as $key_b => $before_item){ //Fetching into old terms
            if($before_item === $after_item){ //Match found !
              unset($after[$key_a]);
              unset($before[$key_b]);
              break;
            }
          }
        }
        $over = implode(',', $after);
        
        drush_log('Missing: '.$missings, 'ok');
        drush_log('Over: '.$over, 'ok');
        $missings = explode(';', $missings);
        foreach($missings as $missing){ //Fetching into missing terms
          if(!empty($missing)){
            //We get the missing term in GF3 database
            $taxo = db_query("select * from taxonomy_term_data WHERE name='".$missing."'")->fetch();
            if(isset($taxo) && !empty($taxo)){
              $node = node_load($nid);
              //We get the current taxo delta
              $delta = db_query("select delta from field_data_field_tags where entity_id='".$node->nid."' ORDER BY delta DESC")->fetch();
              if(isset($delta) && !empty($delta)){
                $delta = $delta->delta+1;
              }
              else{
                $delta = 0;
              }
              db_insert("field_data_field_tags") //We reimplement the term
              ->fields(array(
                'entity_type' => 'node',
                'bundle' => $node->type,
                'deleted' => '0',
                'entity_id' => $node->nid,
                'revision_id' => $node->rid,
                'language' => 'und',
                'delta' => $delta,
                'field_tags_tid' => $taxo->tid,
              ))->execute(); 
              drush_log('Fixed !', 'success');
            }
          }
        }
      }
    }
  }
  drush_log('Rebuild parent table', 'ok');
  db_query("DELETE FROM taxonomy_term_hierarchy WHERE 1");
  $terms = db_query("SELECT * FROM taxonomy_term_data");
  while($term = $terms->fetch()){
    $tid = $term->tid;
    db_insert("taxonomy_term_hierarchy")
              ->fields(array(
                'tid' => $tid,
                'parent' => 0,
              ))->execute(); 
  }
  drush_log('Parent table rebuilt', 'ok');
  db_query("UPDATE taxonomy_term_data SET language='und'"); //Fix translation possible issues
  
  drush_log('Rebuild users format', 'ok');
  //We need to rebuild users format as 'Profil'
  db_query("DELETE FROM field_data_field_format WHERE bundle='user'");
  $profil_tid = taxonomy_get_term_by_name('Profil', 'format')->tid; //We get the term id
  $users = db_select("users", 'n')
          ->fields('n', array('uid'))
          ->execute()
          ->fetchAll();
  foreach($users as $user){ //Fetching into all users
    $uid = $user->uid;
    if($uid == 0){
      continue;
    }
    db_insert("field_data_field_format") //Setting the Profil format
              ->fields(array(
                'entity_type' => 'user',
                'bundle' => 'user',
                'deleted' => '0',
                'entity_id' => $uid,
                'revision_id' => $uid,
                'language' => 'und',
                'delta' => 0,
                'field_format_tid' => $profil_tid,
              ))->execute(); 
  }
}

/**
 * Rebuild users private spaces.
 */
function gofast_migrate_rebuild_private_spaces(){
  //We act as admin
  usurp(1);
  //Retrieving all users ids
  $users = db_select("users", 'n')
          ->fields('n', array('uid'))
          ->execute()
          ->fetchAll();
  drush_log('Creating users private spaces', 'ok');
  foreach($users as $user){
    if($user->uid == 0){
      continue;
    }
    //For each user, we create his private space programatically
    $gid = gofast_og_create_private_space(user_load($user->uid));
    if ($gid) {
      gofast_og_subscribe_user($gid, user_load($user->uid), OG_STATE_ACTIVE, TRUE);
    }
    $account = user_load($user->uid, TRUE);
    $account->og_private['und'][0]['target_id'] = $gid;
    drupal_static_reset();
    echo(".");
  }  
  drush_log('', 'ok');
  drush_log('Users private spaces have been recreated', 'success');
  
  //Now we have to link the old content that was linked to the user by a contrib module in GF2
  //With his brand new private space in GF3
  $private = db_query("SELECT nid from private_bak WHERE private='1'");
  drush_log('Associating documents with their users private spaces', 'ok');
  while($data = $private->fetch()){
    //For each content that was linked to a user in GF2
    $node_infos = db_query("SELECT nid from node where nid='".$data->nid."'")->fetch();
    if(isset($node_infos->nid)){ //Check node existence and coherance
      $countSpaces = db_query("SELECT COUNT(*) FROM og_membership WHERE etid='".$data->nid."'")->fetch();
      $count_var = 'COUNT(*)';
      if($countSpaces->$count_var != 0){
        continue;
      }
      if(!gofast_og_is_space(node_load($node_infos->nid))){
        try{
          //We load the node and get back the associated user
          $node = node_load($data->nid);
          $uid = $node->uid;
          unset ($node);
          $private_space = gofast_og_get_user_private_space(user_load($uid), FALSE);
          if(isset($private_space) && !empty($private_space)){
            //We link the user's private space with the content, using og membership
            gofast_og_subscribe_node($private_space, $data->nid);
            drupal_static_reset();
            echo(".");
          }
        } catch(Exeption $e){
          drush_log("Cannot load node ".$node_infos->nid);
        }
      }
    }
  }
  drush_log('', 'ok');
  drush_log('End of work', 'success');
  
}

/*
 * Rebuild folder name in Alfresco as GF3 standards
 */
function gofast_migrate_rename_folders(){
  usurp(1);
  $group_ids = db_select("node", 'n')
          ->fields('n', array('nid'))
          ->condition('type', 'group', '=')
          ->execute()
          ->fetchAll();
  $organisations_ids = db_select("node", 'n')
          ->fields('n', array('nid'))
          ->condition('type', 'organisation', '=')
          ->execute()
          ->fetchAll();
  $extranet_ids = db_select("node", 'n')
          ->fields('n', array('nid'))
          ->condition('type', 'extranet', '=')
          ->execute()
          ->fetchAll();
  $public_ids = db_select("node", 'n')
          ->fields('n', array('nid'))
          ->condition('type', 'public', '=')
          ->execute()
          ->fetchAll();
  $entity_ids = array_merge($group_ids, $organisations_ids, $extranet_ids, $public_ids);
  drush_log("Renaming folders of ".count($entity_ids)." spaces", 'ok');
  foreach($entity_ids as $space){ //Fetching into all spaces
    $node = node_load($space->nid);
    if(!isset($node->field_folder_reference['und']['0']['value'])){
      drush_log("", "ok");
      drush_log("No folder reference for space : ".$node->nid, "warning");
      continue;
    }
    //We get the Alfresco object using CMIS
    $cmis_object = gofast_cmis_item_get($node->field_folder_reference['und']['0']['value']);
    
    //We build the path as GF3 standards
    $previous_path = $cmis_object->properties['cmis:path'];
    $path_array = explode("/", $previous_path);
    end($path_array);
    $key = key($path_array);
    
    $check = substr($path_array[$key], 0, 1);
    if($check == "_"){
      $path_array[$key] = substr($path_array[$key], 1);
    }
    
    $check = substr($path_array[$key], -1);
    if($check == "_"){
      $path_array[$key] = substr($path_array[$key], 0, -1);
    }
    
    $path_array[$key] = "_".$path_array[$key];
    
    $new_path = implode("/", $path_array);
    //We update the path and rename the item
    if($previous_path != $new_path){
      try{
        $field = GOFAST_CMIS_MAIN_LOCATION_FIELD;
        
        $re = "/" . str_replace("/", "\/", $previous_path) . "/";
        foreach ($node->{$field}[LANGUAGE_NONE] as $id => $entry) {
          $matches = preg_match($re, $entry["value"]);
          if (!empty($matches)) {
            $result = preg_replace($re, $new_path, $entry["value"]);
            $node->{$field}[LANGUAGE_NONE][$id]["value"] = $result;
            field_attach_update('node', $node);
          }
        }
      }catch(Exception $e){
        drush_log("Can't update location for node ".$node->nid." Old/new: ".$previous_path."/".$new_path, "warning");
      }
      
      try{
        gofast_cmis_node_edit_item_rename($node);
      }catch(Exception $e){
        drush_log("Can't rename item for node ".$node->nid." Old/new: ".$previous_path."/".$new_path, "warning");
      }
    }
    echo('.');
  }
}

/*
 * As privates spaces are migrated, the folder reference becomes invalid
 */
function gofast_migrate_relink_private_spaces(){
  usurp(1);
  $entity_ids = db_select("node", 'n')
          ->fields('n', array('nid'))
          ->condition('type', 'private_space', '=')
          ->execute()
          ->fetchAll();
  drush_log("Rebuilding properties of ".count($entity_ids)." elements", 'ok');
  foreach($entity_ids as $private_space){//Fetching into all private spaces
    $private_node = node_load($private_space->nid);
    $private_user = user_load($private_node->uid);
    $private_uname = $private_user->name;
    
    //We get the folder ID using CMIS
    $folder_id = 'workspace://SpacesStore/'.gofast_cmis_item_get_by_path('/Sites/_'.$private_uname)->id;
    
    //We delete and rebuild the reference
    db_query("DELETE FROM field_data_field_folder_reference WHERE entity_id='".$private_node->nid."'");
    db_insert("field_data_field_folder_reference")
      ->fields(array(
        'entity_type' => 'node',
        'bundle' => 'private_space',
        'deleted' => '0',
        'entity_id' => $private_node->nid,
        'revision_id' => $private_node->rid,
        'language' => 'und',
        'delta' => '0',
        'field_folder_reference_value' => $folder_id,
        'field_folder_reference_format' => NULL
      ))->execute();   
    echo(".");
  }
  
  drush_log("", 'ok');
  cache_clear_all();
  drupal_flush_all_caches();
  
  $stats_rebuild_error = 0;
  
  foreach($entity_ids as $entity_id){ //Fetching into private spaces
    //We rebuild aspect and properties for the folder
    $node = node_load($entity_id->nid);
    try{
      gofast_cmis_update_aspect_properties($node, "update");
      gofast_cmis_node_update_permissions($node);
      echo(".");
      //drush_log('Properties rebuilt for node '.$node->nid.'//'.$node->title, 'success');
    }catch(Exception $e){
      $stats_rebuild_error++;
      drush_log('', 'ok');
      drush_log("Cannot rebuild properties for node ".$node->nid, 'warning');
    }
    drupal_static_reset();
  }
  drush_log('', 'ok');
  drush_log("Alfresco properties set to ".(count($entity_ids)-$stats_rebuild_error)." elements. ", 'success');
  if($stats_rebuild_error>0){
      drush_log($stats_rebuild_error." errors reported !", 'warning');
  }
}
/**
 * Rebuild brokens format field for extranet.
 */
function gofast_migrate_rebuild_extranet(){
  //Looking for the tid matching to extranet
  $extranet_tid = db_query("SELECT tid from taxonomy_term_data WHERE name='Extranet'")->fetch()->tid;
  db_query("UPDATE field_data_field_format SET field_format_tid='".$extranet_tid."' WHERE bundle='extranet'");
}

/**
 * Reset emplacements from main emplacement
 */
function gofast_migrate_reset_doc_emplacements(){
  drush_log("Reseting emplacements from main emplacement.", 'ok');
  set_time_limit(0);
  $main_emplacements = db_select("field_data_field_main_emplacement", 'e')->fields('e')->execute();
  db_delete("field_data_field_emplacement")->execute();
  $stats_rebuild_emplacements = 0;
  while($data = $main_emplacements->fetch()){
    db_insert("field_data_field_emplacement")
      ->fields(array(
        'entity_type' => $data->entity_type,
        'bundle' => $data->bundle,
        'deleted' => $data->deleted,
        'entity_id' => $data->entity_id,
        'revision_id' => $data->revision_id,
        'language' => $data->language,
        'delta' => $data->delta,
        'field_emplacement_value' => $data->field_main_emplacement_value
      ))->execute();
    $stats_rebuild_emplacements++;
    echo(".");
  }
  drush_log("", 'ok');
  drush_log($stats_rebuild_emplacements." emplacements rebuilt.", 'success');
}

/*
 * Rebuild all the nodes properties and the rights into Alfresco
 */
function gofast_migrate_rebuild_properties(){
  usurp(1);
  $group_ids = db_select("node", 'n')
          ->fields('n', array('nid'))
          ->condition('type', 'group', '=')
          ->execute()
          ->fetchAll();
  $organisations_ids = db_select("node", 'n')
          ->fields('n', array('nid'))
          ->condition('type', 'organisation', '=')
          ->execute()
          ->fetchAll();
  $extranet_ids = db_select("node", 'n')
          ->fields('n', array('nid'))
          ->condition('type', 'extranet', '=')
          ->execute()
          ->fetchAll();
  $public_ids = db_select("node", 'n')
          ->fields('n', array('nid'))
          ->condition('type', 'public', '=')
          ->execute()
          ->fetchAll();
  $private_ids = db_select("node", 'n')
          ->fields('n', array('nid'))
          ->condition('type', 'private_space', '=')
          ->execute()
          ->fetchAll();
  $entity_ids = array_merge($group_ids, $organisations_ids, $extranet_ids, $public_ids, $private_ids);
  drush_log("Rebuilding properties of ".count($entity_ids)." elements", 'ok');
  $stats_rebuild_error = 0;
  foreach($entity_ids as $entity_id){ //Fetching into all spaces
    $node = node_load($entity_id->nid);
    try{ //We update aspects and properties
      gofast_cmis_node_update_permissions($node);
      echo(".");
    }catch(Exception $e){
      $stats_rebuild_error++;
      drush_log('', 'ok');
      drush_log("Cannot rebuild properties for node ".$node->nid, 'warning');
    }
    drupal_static_reset();
  }
  drush_log('', 'ok');
  drush_log("Alfresco properties set to ".(count($entity_ids)-$stats_rebuild_error)." elements. ", 'success');
  if($stats_rebuild_error>0){
      drush_log($stats_rebuild_error." errors reported !", 'warning');
  }
}

/**
 * All necessary actions after a migration process
 */
function gofast_migrate_post_migrate(){
  usurp(1);
  drush_log("Starting Post-Migration operations.", 'ok');
  $qi = 0;
  set_time_limit(0);
  $queries = array();
  $queries['field_data_group_access']['fields'] = "entity_type,bundle,deleted,entity_id,revision_id,language,delta,group_access_value";
  $queries['og_membership']['fields'] = "type,etid,entity_type,gid,group_type,state,created,field_name,language";
  $queries['og_users_roles']['fields'] = "uid,rid,gid,group_type";
  
  //Setting adm user ID in static drupal variable
  $adm = user_load_by_name("adm");
  variable_set('gofast_user_administrator_id', $adm->uid);
  
  //Rebuild node revisions
  db_query("DELETE from node_revision WHERE 1");
  $revisions = db_query("SELECT nid,vid,uid,title,comment,promote,sticky,changed,status from node");
  drush_log("Rebuilding revisions..", 'ok');
  while($revision = $revisions->fetch()){
    db_insert("node_revision")
      ->fields(array(
        'nid' => $revision->nid,
        'vid' => $revision->vid,
        'uid' => $revision->uid,
        'title' => $revision->title,
        'log' => "",
        'timestamp' => $revision->changed,
        'status' => $revision->status,
        'comment' => $revision->comment,
        'promote' => $revision->promote,
        'sticky' => $revision->sticky,
        'vuuid' => uuid_generate(),
      ))->execute();
    echo(".");
  }
  drush_log("", 'ok');
  drush_log("Drupal revisions have been rebuilt", 'success');
  //Rebuild public
  $migration_options = array(
    'parent' => '7',
    'description' => 'Content in Public foder before migration.',
    'body' => 'This public space contains all the public content in migrated old GoFast 2.'
  );
  gofast_og_create('Migration', 'public', $migration_options); //Create a public space that will contain GF2 public content
  drush_log("Sub public space created", 'success');
  $private = db_query("SELECT nid from private_bak WHERE private='0'");
  $migrate_id = db_query("SELECT nid from node WHERE type='public' and title='Migration'")->fetch()->nid;
  $stats_public_rebuild = 0;
  while($data = $private->fetch()){
    $countSpaces = db_query("SELECT COUNT(*) FROM og_membership WHERE etid='".$data->nid."'")->fetch();
    $count_var = 'COUNT(*)';
    if($countSpaces->$count_var != 0){
      continue;
    }
    $node_infos = db_query("SELECT nid from node where nid='".$data->nid."'")->fetch();
    if(isset($node_infos->nid) && !gofast_og_is_space(node_load($node_infos->nid))){ //Check node existence and coherance
      gofast_og_subscribe_node($migrate_id, $data->nid);
      $stats_public_rebuild++;
    }
  }
  drush_log($stats_public_rebuild." public elements has been rebult.", 'success');
  //Load main spaces
  $main_spaces = array();
  $main_spaces[] = node_load(4, NULL, TRUE);
  $main_spaces[] = node_load(5, NULL, TRUE);
  $main_spaces[] = node_load(6, NULL, TRUE);
  $main_spaces[] = node_load(7, NULL, TRUE);
  //Edit and save main spaces owner
  foreach($main_spaces as $main_space){
    $main_space->uid = 1; //Setting owner UID to 1/Admin
    node_save($main_space);
    drush_log($main_space->title." node has been reconfigured.", 'success');
  }
  
  unset($main_spaces); //Memory allocation management
  
  $user_admin = user_load(1, NULL, TRUE);
  user_save($user_admin);
  drush_log("Admin user has been reconfigured.", 'success');
  
  db_query("DELETE from field_data_group_access WHERE 1");
  
  $nodes_query = db_query("SELECT nid,uid,type from node");
  $nodes = $nodes_query->fetchAll();
  unset($nodes_query);
  db_query("DELETE from field_data_group_access WHERE 1");
  
  foreach($nodes as $k_node => $node){ //Fetching into all nodes
    //Deleting old private space (we will recreate some new ones later)
    if($node->type == 'private_space'){
      node_delete($node->nid); //Delete the node
      drush_log("A private space has been deleted.", 'success');
      continue;
    }
    //Looking for non existant user as node's owner
    if(user_load($node->uid, TRUE) == FALSE){
      $full_node = node_load($node->nid);
      $full_node->uid = 1;
      node_save($full_node);
      drush_log("Because user ".$node->uid." can't be found, node ".$full_node->title."/".$full_node->nid."'s owner has been set to Admin/1", 'warning');
    }
    //Rebuild access permissions
      $queries['field_data_group_access']['values'][$qi][] = 'node';
      $queries['field_data_group_access']['values'][$qi][] = $node->type;
      $queries['field_data_group_access']['values'][$qi][] = '0';
      $queries['field_data_group_access']['values'][$qi][] = $node->nid;
      $queries['field_data_group_access']['values'][$qi][] = $node->nid;
      $queries['field_data_group_access']['values'][$qi][] = 'und';
      $queries['field_data_group_access']['values'][$qi][] = '0';
      $queries['field_data_group_access']['values'][$qi][] = '1';
      $qi++;
    
    unset($nodes[$k_node]);
    echo(".");
  }
  drush_log("", 'ok');
  drush_log("Node permissions has been set.", 'success');
    
    //Looking for non attached Spaces to their main spaces
    $query = db_query("SELECT nid,type from node WHERE (SELECT COUNT(*) FROM og_membership WHERE og_membership.etid=node.nid AND og_membership.field_name='og_group_ref')!=1 AND (node.type='group' OR node.type='organisation' OR node.type='extranet' OR node.type='public') AND (node.nid > 7 OR node.nid < 4)");
    $stats_inherited=0;
    while($inherited = $query->fetch()){ //Matching each inherited spaces with their spaces
      $stats_inherited++;
      switch($inherited->type){
        case 'group':
          $queries['og_membership']['values'][$qi][] = 'og_membership_type_default';
          $queries['og_membership']['values'][$qi][] = $inherited->nid;
          $queries['og_membership']['values'][$qi][] = 'node';
          $queries['og_membership']['values'][$qi][] = '4';
          $queries['og_membership']['values'][$qi][] = 'node';
          $queries['og_membership']['values'][$qi][] = '1';
          $queries['og_membership']['values'][$qi][] = time();
          $queries['og_membership']['values'][$qi][] = 'og_group_ref';
          $queries['og_membership']['values'][$qi][] = 'en';
          $qi++;
          break;
        case 'organisation':
          $queries['og_membership']['values'][$qi][] = 'og_membership_type_default';
          $queries['og_membership']['values'][$qi][] = $inherited->nid;
          $queries['og_membership']['values'][$qi][] = 'node';
          $queries['og_membership']['values'][$qi][] = '5';
          $queries['og_membership']['values'][$qi][] = 'node';
          $queries['og_membership']['values'][$qi][] = '1';
          $queries['og_membership']['values'][$qi][] = time();
          $queries['og_membership']['values'][$qi][] = 'og_group_ref';
          $queries['og_membership']['values'][$qi][] = 'en';
          $qi++;
          break;
        case 'extranet':
          $queries['og_membership']['values'][$qi][] = 'og_membership_type_default';
          $queries['og_membership']['values'][$qi][] = $inherited->nid;
          $queries['og_membership']['values'][$qi][] = 'node';
          $queries['og_membership']['values'][$qi][] = '6';
          $queries['og_membership']['values'][$qi][] = 'node';
          $queries['og_membership']['values'][$qi][] = '1';
          $queries['og_membership']['values'][$qi][] = time();
          $queries['og_membership']['values'][$qi][] = 'og_group_ref';
          $queries['og_membership']['values'][$qi][] = 'en';
          $qi++;
          break;
        case 'public':
          $queries['og_membership']['values'][$qi][] = 'og_membership_type_default';
          $queries['og_membership']['values'][$qi][] = $inherited->nid;
          $queries['og_membership']['values'][$qi][] = 'node';
          $queries['og_membership']['values'][$qi][] = '7';
          $queries['og_membership']['values'][$qi][] = 'node';
          $queries['og_membership']['values'][$qi][] = '1';
          $queries['og_membership']['values'][$qi][] = time();
          $queries['og_membership']['values'][$qi][] = 'og_group_ref';
          $queries['og_membership']['values'][$qi][] = 'en';
          $qi++;
          break;
        default:
          drush_log("node ".$inherited->nid." of type ".$inherited->type." cannot be match with a root space.", 'warning');
          break;
      }
      echo(".");
    }
    drush_log("", 'ok');
    drush_log($stats_inherited." inherited nodes has been found and set to a root space", 'success');
  //Retrieving rids atching with 'read only' role in root spaces content types
    drush_log("Will now fetch into all users and set their membership with root spaces and roles. This may take a while...", 'ok');
  $roles = db_query("SELECT * from og_role");
  $roles_ids = array();
  while($role = $roles->fetch()){ //Fetch into all roles, filling an array with these roles
    $roles_ids[$role->group_bundle][$role->name] = $role->rid;
  }
  $users_query = db_query("SELECT uid from users");
  $users = $users_query->fetchAll();
  foreach($users as $user){ //Fetching into all users
    //Include all users in root spaces
    $uid = $user->uid;
    foreach(array('4', '5', '6', '7') as $root_space){
      $queries['og_membership']['values'][$qi][] = 'og_membership_type_default';
      $queries['og_membership']['values'][$qi][] = $uid;
      $queries['og_membership']['values'][$qi][] = 'user';
      $queries['og_membership']['values'][$qi][] = $root_space;
      $queries['og_membership']['values'][$qi][] = 'node';
      $queries['og_membership']['values'][$qi][] = '1';
      $queries['og_membership']['values'][$qi][] = time();
      $queries['og_membership']['values'][$qi][] = 'og_user_node';
      $queries['og_membership']['values'][$qi][] = 'en';
      $qi++;
    }
    
    //Register role read only or admin for all the users to the root spaces
    foreach(array('group' => '4', 'organisation' => '5', 'extranet' => '6', 'public' => '7') as $root_bundle => $root_id){
      $queries['og_users_roles']['values'][$qi][] = $uid;
      if(gofast_user_is_adm($user)){
        $queries['og_users_roles']['values'][$qi][] = $roles_ids[$root_bundle]['administrator member'];
      }
      else{
        $queries['og_users_roles']['values'][$qi][] = $roles_ids[$root_bundle]['read only member'];
      }
      $queries['og_users_roles']['values'][$qi][] = $root_id;
      $queries['og_users_roles']['values'][$qi][] = 'node';
      $qi++;
    }
    echo('.');
  }
  drush_log("Root spaces membership and users roles has been rebuilt.", 'success');
  drupal_static_reset();
  drush_log("Sending queries to database.", 'ok');
  //Send queries
  foreach ($queries as $table => $data){ //Fetching into all queries by table
    $values_global = "";
    foreach($data['values'] as $entry){ //Fetching into all line add in table's query
      $values = "";
      foreach($entry as $row){ //Fetching into all field into this line
        str_replace("'", "''", $row); //Prepare for base
        $values .= "'".$row."', "; //Formating as 'value', 'value1', ...
      }
      $values_global .= "(".substr($values, '0', '-2')."),";
    }
    $values_global = substr($values_global, '0', '-1');
    db_query("INSERT IGNORE INTO ".$table." (".$data['fields'].") VALUES ".$values_global);
    echo(".");
  }
  drush_log("", 'ok');
  drush_log("The main migration operations has been completed !", 'success');
}

function gofast_migrate_rebuild_ldap_recurse($LdapServer, $group = NULL){
    if($group == NULL){
        return;
    }
    
    foreach($group as $parent_child){
      try{
        if(isset($parent_child['node'])){ //Current node
            $dn = gofast_ldap_space_set_dn(node_load($parent_child['node']->nid), TRUE);
            drupal_static_reset();
            gofast_ldap_node_insert(node_load($parent_child['node']->nid));
            drupal_static_reset();
            //Membership process in LDAP, we create a fake OG Membership object, needed for the process
            foreach(gofast_og_get_members(node_load($parent_child['node']->nid)) as $uid){
              $membership = new OgMembership();
              $membership->entity_type = 'user';
              $membership->field_name = GOFAST_OG_USER_MEMBERSHIP_FIELD;
              $membership->gid = $parent_child['node']->nid;
              $membership->etid = $uid;
              $membership->state = 1;
              gofast_ldap_og_membership_insert($membership);
              $roles = gofast_og_get_user_roles($parent_child['node']->nid, $uid);
              $rid = array_keys($roles)[0];
              gofast_ldap_og_role_grant('node', $parent_child['node']->nid, $uid, $rid);
            }
            drupal_static_reset();
            echo(".");
        }
        if(isset($parent_child['children'])){ //Associated children(s)
            if(!empty($parent_child['children'])){ //Check existence
                gofast_migrate_rebuild_ldap_recurse($LdapServer, $parent_child['children']);
            }
        }
      }catch(Exception $e){
        drush_log($e, 'error');
      }
    }
}


function gofast_migrate_rebuild_ldap(){
  usurp(1);
  drupal_static_reset();
  //Connection (to improve)
  $base_dn = "dc=aife,dc=fr";
  $LdapServer = gofast_ldap_server_load(GOFAST_LDAP_INT_SERVER);
  $LdapServer->connect();
  $LdapServer->bind('cn=manager,'.$base_dn, 'hZ9CcL!S4R'); //Connexion to LDAP (to improve)
  //Remove base OU and their content
  $LdapServer->groupRemoveGroup("ou=group,ou=Groups,".$base_dn, FALSE, TRUE);
  $LdapServer->groupRemoveGroup("ou=organisation,ou=Groups,".$base_dn, FALSE, TRUE);
  $LdapServer->groupRemoveGroup("ou=extranet,ou=Groups,".$base_dn, FALSE, TRUE);
  $LdapServer->groupRemoveGroup("ou=public,ou=Groups,".$base_dn, FALSE, TRUE);
  $attributes = array();
  
  //Rebuild base OU
  $attributes['objectclass'] = 'organizationalUnit';
  $attributes['ou'] = 'Group';
  ldap_add($LdapServer->connection, "ou=group,ou=Groups,".$base_dn, $attributes);
  
  $attributes['ou'] = 'Organisation';
  ldap_add($LdapServer->connection, "ou=organisation,ou=Groups,".$base_dn, $attributes);
  
  $attributes['ou'] = 'Extranet';
  ldap_add($LdapServer->connection, "ou=extranet,ou=Groups,".$base_dn, $attributes);
  
  $attributes['ou'] = 'Public';
  ldap_add($LdapServer->connection, "ou=public,ou=Groups,".$base_dn, $attributes);
  drupal_static_reset();
  drush_log("LDAP spaces has been reinitialized", 'success');
  
  $groups = array();
  $groups[] = gofast_og_get_children(GOFAST_CMIS_LOCATIONS_FIELD_GROUPS_GID, TRUE, TRUE, FALSE);
  $groups[] = gofast_og_get_children(GOFAST_CMIS_LOCATIONS_FIELD_ORGANISATIONS_GID, TRUE, TRUE, FALSE);
  $groups[] = gofast_og_get_children(GOFAST_CMIS_LOCATIONS_FIELD_EXTRANET_GID, TRUE, TRUE, FALSE);
  $groups[] = gofast_og_get_children(GOFAST_CMIS_LOCATIONS_FIELD_PUBLIC_GID, TRUE, TRUE, FALSE);
  
  //Dump dn references
  db_query("DELETE FROM field_data_field_ldap_group_dn");
  drush_log("LDAP references in Drupal has been dropped... Rebuilding.", 'success');
  //Setting root spaces in LDAP
  foreach(array(node_load('4'), node_load('5'), node_load('6'), node_load('7')) as $root_space){
      
      //Add process in LDAP
      gofast_ldap_space_set_dn($root_space, TRUE);
      drupal_static_reset();
      gofast_ldap_node_insert(node_load($root_space->nid));
      drupal_static_reset();
      
      //Membership process in LDAP, we create a fake OG Membership object, needed for the process
      foreach(gofast_og_get_members(node_load($root_space->nid)) as $uid){
        $membership = new OgMembership();
        $membership->entity_type = 'user';
        $membership->field_name = GOFAST_OG_USER_MEMBERSHIP_FIELD;
        $membership->gid = $root_space->nid;
        $membership->etid = $uid;
        $membership->state = 1;
        gofast_ldap_og_membership_insert($membership);
        $roles = gofast_og_get_user_roles($root_space->nid, $uid);
        $rid = array_keys($roles)[0];
        gofast_ldap_og_role_grant('node', $root_space->nid, $uid, $rid);
      }
  }
  foreach($groups as $group){
      gofast_migrate_rebuild_ldap_recurse($LdapServer, $group);
      drush_log("", 'ok');
      drush_log("End of space rebuild...", 'ok');
  }
  drush_log("All spaces have been rebuilt", 'success');
  drupal_static_reset();
}

function gofast_migrate_rebuild_multifiled_documents(){
  $alfresco_items_ids = db_query("select node.nid from node INNER JOIN og_membership ON node.nid=og_membership.etid WHERE (SELECT COUNT(*) FROM og_membership where og_membership.etid=node.nid AND og_membership.field_name='og_group_content_ref')>1 AND node.status=1 AND node.type='alfresco_item';")->fetchAll();
  
  drush_log("Rebuilding multifiled documents... ".count($alfresco_items_ids)." items queued. This may take a while.", 'ok');
  foreach($alfresco_items_ids as $nid_query){
    try{
        $nid = $nid_query->nid;
        $node = node_load($nid);
        $wrapper = isset($node) ? entity_metadata_wrapper('node', $node) : null;
        $node_reference = $wrapper->{GOFAST_CMIS_REFERENCE_FIELD}->value();
        // Update the node permissions if the node is multifilled
        $private_space = array();
        $node_groups = $wrapper->{GOFAST_OG_CONTENT_MEMBERSHIP_FIELD}->value();
          foreach ($node_groups as $node_group) {
            $space_dn = rawurlencode(gofast_ldap_space_cn($node_group));
            if (gofast_og_is_user_private_space($node_group)) {
              $private_space[] = $space_dn;
            }
            else {
              $groups[] = $space_dn;
            }
          }
            gofast_cmis_webservice_item_assign_multifiled_permissions($node_reference, $groups, $private_space);
        unset($groups);
        unset($private_space);
        echo('.');
        drupal_static_reset();
    }catch(Exception $e){
        drush_log("Error on node ${nid} : " . $e, 'warning');
    }
  }
  drush_log("", 'ok');
  drush_log("Multifiled documents has been rebuilt !", 'success');
}

/*
 * Prepare extranet migration
 */

function gofast_migrate_prepare_extranet_migration(){
  //Rebuild extranet
  $migration_options = array(
    'parent' => '6',
    'description' => 'Content in Extranet foder before migration.',
    'body' => 'This extranet space contains all the extranet content in migrated old GoFast 2.'
  );
  gofast_og_create('Migration', 'extranet', $migration_options); //Create an extranet space that will contain GF2 public content
  
  $old_extranet = db_query("SELECT * from node where title='Extranet' AND type='extranet' AND nid !='6'")->fetch()->nid;
  $new_extranet = db_query("SELECT * from node where title='Migration' AND type='extranet'")->fetch()->nid;
  db_query("UPDATE og_membership SET gid='".$new_extranet."' WHERE gid='".$old_extranet."'");
}

/*
 * Migration Extranet/Public
 */

function gofast_migrate_relink_public_extranet(){
  
}

/*
 * Rebuild field_data_group_access field
 */
function gofast_migrate_rebuild_group_access(){
  $group_ids = db_select("node", 'n')
          ->fields('n', array('nid'))
          ->condition('type', 'group', '=')
          ->execute()
          ->fetchAll();
  $organisations_ids = db_select("node", 'n')
          ->fields('n', array('nid'))
          ->condition('type', 'organisation', '=')
          ->execute()
          ->fetchAll();
  $extranet_ids = db_select("node", 'n')
          ->fields('n', array('nid'))
          ->condition('type', 'extranet', '=')
          ->execute()
          ->fetchAll();
  $public_ids = db_select("node", 'n')
          ->fields('n', array('nid'))
          ->condition('type', 'public', '=')
          ->execute()
          ->fetchAll();
  $private_ids = db_select("node", 'n')
          ->fields('n', array('nid'))
          ->condition('type', 'private_space', '=')
          ->execute()
          ->fetchAll();
  $entity_ids = array_merge($group_ids, $organisations_ids, $extranet_ids, $public_ids, $private_ids);
  db_delete("field_data_group_access")->execute();
  foreach($entity_ids as $space_id){
    $nid = $space_id->nid;
    $node = node_load($nid);
    $bundle = $node->type;
    
    db_insert("field_data_group_access")
      ->fields(array(
        'entity_type' => 'node',
        'bundle' => $bundle,
        'deleted' => 0,
        'entity_id' => $node->nid,
        'revision_id' => $node->rid,
        'language' => LANGUAGE_NONE,
        'delta' => '0',
        'group_access_value' => 1
      ))->execute();
  }
  drupal_static_reset();
  cache_clear_all();
  drupal_flush_all_caches();
  node_access_rebuild();
}

function gofast_migrate_rebuild_memberships(){
  usurp(1);
  drush_log('Rebuilding root spaces memberships', 'ok');
  foreach(array('group', 'organisation', 'extranet', 'public') as $bundle){
    drush_log('Rebuilding: '.$bundle, 'ok');
    gofast_og_reset_memberships_by_bundle($bundle);
  }
  
  drush_log('Remotly retrieving and setting memberships for each spaces', 'ok');
  $group_ids = db_select("node", 'n')
          ->fields('n', array('nid'))
          ->condition('type', 'group', '=')
          ->execute()
          ->fetchAll();
  $organisations_ids = db_select("node", 'n')
          ->fields('n', array('nid'))
          ->condition('type', 'organisation', '=')
          ->execute()
          ->fetchAll();
  $extranet_ids = db_select("node", 'n')
          ->fields('n', array('nid'))
          ->condition('type', 'extranet', '=')
          ->execute()
          ->fetchAll();
  $entity_ids = array_merge($group_ids, $organisations_ids, $extranet_ids);
  foreach($entity_ids as $space_id){
    $nid = $space_id->nid;
    $node = node_load($nid);
    drush_log('________________ Space: ' . $node->title, 'ok');
    if(!gofast_og_is_root_space($node)){
      drush_log('________ Not a root space', 'ok');
      //Curl call to REST API
      // !! STATIC VAR IN CODE !! TODO: Pass it as a drush param
      $url = "https://10.75.194.21/check/integrity?nid=".$nid;
      drush_log('________ Calling ' . $url, 'ok');
      $ch = curl_init();
      curl_setopt($ch, CURLOPT_HEADER, 0);
      curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
      curl_setopt($ch, CURLOPT_USERPWD, "admin:" . gofast_get_admin_pwd());
      curl_setopt($ch, CURLOPT_URL, $url);
      curl_setopt($ch, CURLOPT_TIMEOUT, 5);
      curl_setopt($ch, CURLOPT_SSL_VERIFYHOST, 0);
      curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, 0);
      curl_setopt($ch, CURLOPT_PROXY, '');
      $buffer = curl_exec($ch);

      $buf = strip_tags($buffer);
      $result = json_decode($buf, TRUE);
      $admins = explode(',', $result['administrator member']);
      $contribs = explode(',', $result['group contributor']);
      $ros = explode(',', $result['read only member']);
      drush_log('________ Admins: ' . $result['administrator member'], 'ok');
      drush_log('________ Contribs: ' . $result['group contributor'], 'ok');
      drush_log('________ RO: ' . $result['read only member'], 'ok');
      
      variable_set('reset_membership_processing', '1');
      if($node == NULL){
        variable_set('reset_membership_processing', '0');
        continue;
      }
      $bundle = $node->type;

      if(!gofast_og_is_space($node)){
        variable_set('reset_membership_processing', '0');
        return false;
      }

      //Delete all space's memberships
      foreach(gofast_og_get_members($node) as $uid){
        drush_log('________ Delete: ' . $uid, 'ok');
        gofast_og_unsubscribe_user($nid, $uid);
        usleep(50000);
      }
      $roles_query = og_roles('node', $bundle, $nid, FALSE, FALSE);
      foreach($roles_query as $rkey => $roles){
        if($roles == GOFAST_OG_ROLE_ADMIN){
          $admin_rid = $rkey;
        }
        if($roles == GOFAST_OG_ROLE_READ_ONLY){
          $readonly_rid = $rkey;
        }
        if($roles == GOFAST_OG_ROLE_STANDARD){
          $contributor_rid = $rkey;
        }
      }
      foreach($admins as $uid){
        if($uid != 0 && $uid != 1 && is_object(user_load($uid))){
          gofast_og_subscribe_user($nid, $uid);
          usleep(50000);
          og_role_revoke('node', $nid, $uid, $readonly_rid);
          og_role_revoke('node', $nid, $uid, $contributor_rid);
          og_role_revoke('node', $nid, $uid, $admin_rid);
          usleep(50000);
          og_role_grant('node', $nid, $uid, $admin_rid);
          usleep(50000);
          drush_log('________ Added as admin: ' . $uid, 'ok');
        }
      }
      foreach($contribs as $uid){
        if($uid != 0 && $uid != 1 && is_object(user_load($uid))){
          gofast_og_subscribe_user($nid, $uid);
          usleep(50000);
          og_role_revoke('node', $nid, $uid, $readonly_rid);
          og_role_revoke('node', $nid, $uid, $contributor_rid);
          og_role_revoke('node', $nid, $uid, $admin_rid);
          usleep(50000);
          og_role_grant('node', $nid, $uid, $contributor_rid);
          usleep(50000);
          drush_log('________ Added as contrib: ' . $uid, 'ok');
        }
      }
      foreach($ros as $uid){
        if($uid != 0 && $uid != 1  && is_object(user_load($uid))){
          gofast_og_subscribe_user($nid, $uid);
          usleep(50000);
          og_role_revoke('node', $nid, $uid, $readonly_rid);
          og_role_revoke('node', $nid, $uid, $contributor_rid);
          og_role_revoke('node', $nid, $uid, $admin_rid);
          usleep(50000);
          og_role_grant('node', $nid, $uid, $readonly_rid);
          usleep(50000);
          drush_log('________ Added as read only: ' . $uid, 'ok');
        }
      }
    }
    drush_log('________________', 'ok');
    //drush_log('.', 'ok');
  }
}

function gofast_migrate_rebuild_revisions(){
  try { //We get a connection to VMCLONE, warning, static var set in code, to pass as a drush param
    $connex = new PDO('mysql:host=localhost;dbname=drupal;port=3306', 'root', '');
  }catch (Exception $e){
    echo('Erreur : ' . $e->getMessage());
  }
  $revisions = db_query('select nid,uid,timestamp from node_revision');
  foreach($revisions as $revision){
    $comment=false;
    $nid = $revision->nid;
    $old_revision = $connex->query('select nid,uid,timestamp from node_revisions where nid=' . $nid)->fetch();
    if(isset($old_revision['timestamp'])){
      $last_comment = db_query('select * from comment where nid=' . $nid . " ORDER BY changed DESC")->fetch();
      if(isset($last_comment->changed) && $last_comment->changed > $old_revision['timestamp']){
        drush_log('Node : ' . $revision->nid . ' with current revision timestamp ' . $revision->timestamp . ' is going to be changed to ' . $last_comment->changed, 'success');
        db_query('UPDATE node_revision SET timestamp=' . $last_comment->changed . ' WHERE nid=' . $revision->nid);
        db_query('UPDATE node SET changed=' . $last_comment->changed . ' WHERE nid=' . $revision->nid);
        $comment = true;
      }
      else{
        drush_log('Node : ' . $revision->nid . ' with current revision timestamp ' . $revision->timestamp . ' is going to be changed to ' . $old_revision['timestamp'], 'success');
        db_query('UPDATE node_revision SET timestamp=' . $old_revision['timestamp'] . ' WHERE nid=' . $revision->nid);
        db_query('UPDATE node SET changed=' . $old_revision['timestamp'] . ' WHERE nid=' . $revision->nid);
      }
    }
    if(isset($old_revision['uid']) && $old_revision['uid'] != 1){
      if($comment){
        drush_log('Node : ' . $revision->nid . ' with current revision uid ' . $revision->uid . ' is going to be changed to ' . $last_comment->uid, 'success');
        db_query('UPDATE node_revision SET uid=' . $last_comment->uid . ' WHERE nid=' . $revision->nid);
      }
      else{
        drush_log('Node : ' . $revision->nid . ' with current revision uid ' . $revision->uid . ' is going to be changed to ' . $old_revision['uid'], 'success');
        db_query('UPDATE node_revision SET uid=' . $old_revision['uid'] . ' WHERE nid=' . $revision->nid);
      }
    }
  }
}

function gofast_migrate_aife(){
  db_query("delete from field_data_field_cei");
  db_query("delete from field_revision_field_cei");
  db_query("delete from field_data_field_fdl");
  db_query("delete from field_revision_field_fdl");
  db_query("delete from field_data_field_trigger_event_owners");
  db_query("delete from field_revision_field_trigger_event_owners");
  db_query("delete from field_data_field_trigger_event_history");
  db_query("delete from field_revision_field_trigger_event_history");
  db_query("delete from field_data_field_checkout_infos");
  db_query("delete from field_revision_field_checkout_infos");
  
  $alfresco_items_ids = db_select("node", 'n')
          ->fields('n', array('nid'))
          ->condition('type', 'alfresco_item', '=')
          ->execute()
          ->fetchAll();
  $nb = 1;
  foreach($alfresco_items_ids as $nid_query){
    $nid = $nid_query->nid;
    $vid = db_query("select vid from node_revision where nid=" . $nid)->fetch()->vid;
    $url = "https://10.75.194.21/check/integrity?nid=".$nid;
    drush_log('________ Calling ' . $url . ' ' . $nb . "/" . count($alfresco_items_ids), 'ok');
    $nb++;
    $ch = curl_init();
    curl_setopt($ch, CURLOPT_HEADER, 0);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
    curl_setopt($ch, CURLOPT_USERPWD, "admin:" . gofast_get_admin_pwd());
    curl_setopt($ch, CURLOPT_URL, $url);
    curl_setopt($ch, CURLOPT_TIMEOUT, 5);
    curl_setopt($ch, CURLOPT_SSL_VERIFYHOST, 0);
    curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, 0);
    $buffer = curl_exec($ch);
    curl_close($ch);
    
    $buf = strip_tags($buffer);
    $result = json_decode($buf, TRUE);
    
    //Clear cei field
    if(is_array($result['field_cei'])){
      $delta = 0;
      foreach($result['field_cei'] as $key => $value){
        unset($result['field_cei'][$key]);
        if(!empty($value['nid'])){
          $result['field_cei'][]['target_id'] = $value['nid'];
          db_query("INSERT IGNORE INTO field_data_field_cei VALUES('node', 'alfresco_item', 0, ".$nid.", ".$vid.", 'und', ".$delta.", '".$value['nid']."')");
          db_query("INSERT IGNORE INTO field_revision_field_cei VALUES('node', 'alfresco_item', 0, ".$nid.", ".$vid.", 'und', ".$delta.", '".$value['nid']."')");
          $delta ++;
        }
      }
      $result['field_cei'] = array_values($result['field_cei']);
    }
    
    //Clear fdl field
    if(is_array($result['field_fdl'])){
      $delta = 0;
      foreach($result['field_fdl'] as $key => $value){
        unset($result['field_fdl'][$key]);
        if(!empty($value['nid'])){
          $result['field_fdl'][]['target_id'] = $value['nid'];
          db_query("INSERT IGNORE INTO field_data_field_fdl VALUES('node', 'alfresco_item', 0, ".$nid.", ".$vid.", 'und', ".$delta.", '".$value['nid']."')");
          db_query("INSERT IGNORE INTO field_revision_field_fdl VALUES('node', 'alfresco_item', 0, ".$nid.", ".$vid.", 'und', ".$delta.", '".$value['nid']."')");
          $delta ++;
        }
      }
      $result['field_fdl'] = array_values($result['field_fdl']);
    }
    
    //Clear trigger_event_owners field
    if(is_array($result['field_trigger_event_owners'])){
      $delta = 0;
      foreach($result['field_trigger_event_owners'] as $key => $value){
        unset($result['field_trigger_event_owners'][$key]);
        if(!empty($value['uid'])){
          $result['field_trigger_event_owners'][]['target_id'] = $value['uid'];
          db_query("INSERT IGNORE INTO field_data_field_trigger_event_owners VALUES('node', 'alfresco_item', 0, ".$nid.", ".$vid.", 'und', ".$delta.", '".$value['uid']."')");
          db_query("INSERT IGNORE INTO field_revision_field_trigger_event_owners VALUES('node', 'alfresco_item', 0, ".$nid.", ".$vid.", 'und', ".$delta.", '".$value['uid']."')");
          $delta ++;
        }
      }
      $result['field_trigger_event_owners'] = array_values($result['field_trigger_event_owners']);
    }
    
    //Clear trigger_event_history field
    if(is_array($result['field_trigger_event_history'])){
      $delta = 0;
      foreach($result['field_trigger_event_history'] as $key => $value){
        unset($result['field_trigger_event_history'][$key]);
        if(!empty($value)){
          $value = reset(taxonomy_get_term_by_name($value, 'trigger_event'))->tid;
          $result['field_trigger_event_history'][]['value'] = $value;
          db_query("INSERT IGNORE INTO field_data_field_trigger_event_history VALUES('node', 'alfresco_item', 0, ".$nid.", ".$vid.", 'und', ".$delta.", '".$value."', NULL)");
          db_query("INSERT IGNORE INTO field_revision_field_trigger_event_history VALUES('node', 'alfresco_item', 0, ".$nid.", ".$vid.", 'und', ".$delta.", '".$value."', NULL)");
          $delta ++;
        }
      }
      $result['field_trigger_event_history'] = array_values($result['field_trigger_event_history']);
    }
    
    //Clear checkout_infos field
    if(is_array($result['field_checkout_infos'])){
      $delta = 0;
      foreach($result['field_checkout_infos'] as $key => $value){
        unset($result['field_checkout_infos'][$key]);
        if(!empty($value['value'])){
          $result['field_checkout_infos'][]['value'] = $value['value'];
          db_query("INSERT IGNORE INTO field_data_field_checkout_infos VALUES('node', 'alfresco_item', 0, ".$nid.", ".$vid.", 'und', ".$delta.", '".str_replace("'", "\\'", $value['value'])."', NULL)");
          db_query("INSERT IGNORE INTO field_revision_field_checkout_infos VALUES('node', 'alfresco_item', 0, ".$nid.", ".$vid.", 'und', ".$delta.", '".str_replace("'", "\\'", $value['value'])."', NULL)");
          $delta ++;
        }
      }
      $result['field_checkout_infos'] = array_values($result['field_checkout_infos']);
    }
    
    
    drush_log('________ cei is : ' . json_encode($result['field_cei']), 'ok');
    drush_log('________ fdl is : ' . json_encode($result['field_fdl']), 'ok');
    drush_log('________ trigger_event_owners is : ' . json_encode($result['field_trigger_event_owners']), 'ok');
    drush_log('________ trigger_event_history is : ' . json_encode($result['field_trigger_event_history']), 'ok');
    drush_log('________ checkout_infos is : ' . json_encode($result['field_checkout_infos']), 'ok');
    
    $json_orig = $buffer;
    $json_dest = gofast_get_json_object_from_node(node_load($nid, NULL, TRUE));
    
    $diff = gofast_compare_json_objects($json_orig,$json_dest);
    
    if(!empty($diff)){
      $check_integ = variable_get("gofast_result_integrity_check", array());
      $check_integ[$nid] = $diff;
      variable_set("gofast_result_integrity_check", $check_integ);
    }
    
    drupal_static_reset();
    drush_log('________________', 'ok');
  }
  gofast_migrate_integrity(true);
}


function gofast_migrate_integrity($full = false){
  $group_ids = db_select("node", 'n')
          ->fields('n', array('nid'))
          ->condition('type', 'group', '=')
          ->execute()
          ->fetchAll();
  $organisations_ids = db_select("node", 'n')
          ->fields('n', array('nid'))
          ->condition('type', 'organisation', '=')
          ->execute()
          ->fetchAll();
  $extranet_ids = db_select("node", 'n')
          ->fields('n', array('nid'))
          ->condition('type', 'extranet', '=')
          ->execute()
          ->fetchAll();
  $public_ids = db_select("node", 'n')
          ->fields('n', array('nid'))
          ->condition('type', 'public', '=')
          ->execute()
          ->fetchAll();
  $items_ids = array_merge($group_ids, $organisations_ids, $extranet_ids, $public_ids);
  if(!$full && !empty(variable_get('gofast_result_integrity_check', array()))){
    $items_ids = array_keys(variable_get('gofast_result_integrity_check'));
    $clearing = true;
  }
  $nb = 1;
  foreach($items_ids as $nid_query){
    $nid = $nid_query->nid;
    if(empty($nid)){
      $nid = $nid_query;
    }
    $vid = db_query("select vid from node_revision where nid=" . $nid)->fetch()->vid;
    $url = "https://10.75.194.21/check/integrity?nid=".$nid;
    drush_log('________ Calling ' . $url . ' ' . $nb . "/" . count($items_ids), 'ok');
    $nb++;
    $ch = curl_init();
    curl_setopt($ch, CURLOPT_HEADER, 0);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
    curl_setopt($ch, CURLOPT_USERPWD, "admin:" . gofast_get_admin_pwd());
    curl_setopt($ch, CURLOPT_URL, $url);
    curl_setopt($ch, CURLOPT_TIMEOUT, 5);
    curl_setopt($ch, CURLOPT_SSL_VERIFYHOST, 0);
    curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, 0);
    $buffer = curl_exec($ch);
    curl_close($ch);
    
    $json_orig = $buffer;
    $json_dest = gofast_get_json_object_from_node(node_load($nid, NULL, TRUE));
    
    $diff = gofast_compare_json_objects($json_orig,$json_dest);
    
    if(!empty($diff)){
      $check_integ = variable_get("gofast_result_integrity_check", array());
      $check_integ[$nid] = $diff;
      variable_set("gofast_result_integrity_check", $check_integ);
    }
    
    else if($clearing){
      $check_integ = variable_get("gofast_result_integrity_check", array());
      unset($check_integ[$nid]);
      variable_set("gofast_result_integrity_check", $check_integ);
    }
    
    drupal_static_reset();
    drush_log('________________', 'ok');
  }
}