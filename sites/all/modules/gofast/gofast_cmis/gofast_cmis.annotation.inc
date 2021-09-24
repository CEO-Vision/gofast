<?php

function gofast_cmis_get_annotations($nid) {
  global $user;
  $at_last_one_too_old = false;
  $annotations = variable_get("gofast_annotations", array());
  if (isset($annotations[$nid])) {
    //$annotation_object = '[{"text":"coucou","ranges":[{"start":"/div/div/div[2]/div","startOffset":10,"end":"/div/div/div[2]/div","endOffset":33}],"quote":"ots clés séparation cor","uri":"https://dev.ceo-vision.com/fr/node/6656"}]';
    $annotation_object = "[";
    $i = 0;
    //on charge le noeud
    $node = node_load($nid);
    $node_reference = gofast_cmis_node_get_item_id($node);
    $infos = gofast_cmis_webservice_item_get_versions($node_reference);
    $timestamp_document =  strtotime($infos[0]->createdDate);
    foreach ($annotations[$nid] as $id => $annotation) {
      $annotation_php_object = json_decode($annotation);
      $uid = db_query("select uid from comment where cid=" . $annotation_php_object->cid)->fetchAll()[0]->uid;
      $annotation_php_object->permissions->admin = array($annotation_php_object->user);
      $annotation = json_encode($annotation_php_object);

      if(!is_object($annotation_php_object->private) && $annotation_php_object->private == 1){
          //This annotation is private, we have to check if we have the visibility on it
          if($uid != $user->uid){
              $i++;
              continue;
          }
      }

      $annotation_object .= $annotation;
      //on verifie si l'annotation est plus récente que la date de derniere modif du doc
      // si non, on la supprime
      $timestamp_annotation = $annotation_php_object->timestamp;
      if ($timestamp_annotation < $timestamp_document && isset($annotation_php_object->timestamp)) {
        unset($annotations[$nid][$annotation_php_object->id]);
        variable_set("gofast_annotations", $annotations);
        watchdog("debug delete annotation too old", $nid);
        $annotation_object = "[]";
        $at_last_one_too_old = true;
      }
      else {
        if (count($annotations[$nid]) !== 1 && $i < count($annotations[$nid]) - 1) {
          $annotation_object .= ",";
        }
      }
      $i++;
    }
    if(substr($annotation_object, -1) === ","){
        $annotation_object = substr($annotation_object, 0, -1);
    }
    $annotation_object .= "]";
  }
  else {
    $annotation_object = "[]";
  }
  if ($at_last_one_too_old == true) {
    $annotation_object = "[]";
  }
  print $annotation_object;
}

function gofast_cmis_create_annotations($nid) {
  //on utilise cette methode car étrangement la variable $_POST est vide...
  $data_json_annotation = file_get_contents('php://input');
  $data_json_annotation_decoded = json_decode($data_json_annotation);
  if(gofast_user_is_comment_restricted()){
      $data_json_annotation_decoded->private = TRUE;
  }

  $annotations = variable_get("gofast_annotations", array());
  //$annotation_object = '[{"text":"coucou","ranges":[{"start":"/div/div/div[2]/div","startOffset":10,"end":"/div/div/div[2]/div","endOffset":33}],"quote":"ots clés séparation cor","uri":"https://dev.ceo-vision.com/fr/node/6656"}]';
  $random = substr(md5(rand()), 0, 15);
  $data_json_annotation_decoded->id = $random;
  $data_json_annotation_decoded->timestamp = time();

  if(isset($data_json_annotation_decoded->ranges[0]->start)){
    $correctPage = substr($data_json_annotation_decoded->ranges[0]->start, 5, 1);
    if($correctPage){
      $data_json_annotation_decoded->currentPage = $correctPage;
    }
  }

  //on créer un commentaire qui contient l'annotation
  $cid_comment_annotation = gofast_cmis_create_comment_annotation($nid, $data_json_annotation_decoded);
  $data_json_annotation_decoded->cid = $cid_comment_annotation;

  $annotations[$nid][$random] = json_encode($data_json_annotation_decoded);

  variable_set("gofast_annotations", $annotations);

  print json_encode($data_json_annotation_decoded);
}

function gofast_cmis_create_comment_annotation($nid, $data_json_annotation_decoded) {
  global $user;
  $node = node_load($nid);

  //on recupere l'objet cmis pour avoir sa derniere version
  $infos_document = gofast_cmis_alfresco_get_infos($node);

  $subject = t("Annotation on the version !version", array("!version" => $infos_document["current_version"]));

  //on genere le body du commentaire. Celui-ci est composé du texte que l'on annote, suivi de l'annotation en elle même
  $page_text = t("Page %page", array('%page' => $data_json_annotation_decoded->currentPage));
  $body = $page_text . " - '<i>" . $data_json_annotation_decoded->quote . "</i>'<br /> => " . $data_json_annotation_decoded->text;
  $isPrivate = $data_json_annotation_decoded->private ? "1" : "0";
  $isPrivate = gofast_user_is_comment_restricted() ? "1" : $isPrivate;

  $comment = new stdClass();
  $comment->nid = $node->nid;
  $comment->cid = 0;
  $comment->pid = 0;
  $comment->uid = $user->uid;
  $comment->is_anonymous = 0;
  $comment->status = COMMENT_PUBLISHED;
  $comment->language = $node->language;
  $comment->subject = $subject;
  $comment->field_is_annotation[LANGUAGE_NONE][0]['value'] = intval(TRUE);
  $comment->field_comment_is_private[LANGUAGE_NONE][0]['value'] = $isPrivate;
  $comment->comment_body[LANGUAGE_NONE][0]['value'] = nl2br($body);
  $comment->comment_body[LANGUAGE_NONE][0]['format'] = 'full_html';

  comment_submit($comment);
  comment_save($comment);
  $cid = $comment->cid;

  return $cid;
}

function gofast_cmis_update_annotation($nid) {
  $data_json_annotation = file_get_contents('php://input');
  $data_json_annotation_decoded = json_decode($data_json_annotation);
  if(gofast_user_is_comment_restricted()){
      $data_json_annotation_decoded->private = TRUE;
  }

  $id_annotation = $data_json_annotation_decoded->id;

  $annotations = variable_get("gofast_annotations", array());
  if (isset($annotations[$nid][$id_annotation])) {
    $annotations[$nid][$id_annotation] = json_encode($data_json_annotation_decoded);
    variable_set("gofast_annotations", $annotations);
    //on modifie le commentaire associé
    $body = "' <i>" . $data_json_annotation_decoded->quote . "</i>'<br /> => " . $data_json_annotation_decoded->text;
    $isPrivate = $data_json_annotation_decoded->private ? "1" : "0";
    $isPrivate = gofast_user_is_comment_restricted() ? "1" : $isPrivate;
    $original_comment = comment_load($data_json_annotation_decoded->cid);

    global $user;
    $original_comment->uid = $user->uid;
    $original_comment->comment_body[LANGUAGE_NONE][0]['value'] = nl2br($body);
    $original_comment->timestamp = time();
    $original_comment->field_comment_is_private[LANGUAGE_NONE][0]['value'] = $isPrivate;

    comment_save($original_comment);
  }
  print $data_json_annotation;
}

function gofast_cmis_delete_annotation($nid, $id_annotation) {
  $annotations = variable_get("gofast_annotations", array());
  if (isset($annotations[$nid][$id_annotation])) {
    $annotation_decoded = json_decode($annotations[$nid][$id_annotation]);
    $cid = $annotation_decoded->cid;
    require_once(drupal_get_path('module', 'comment') . '/comment.pages.inc');
    require_once(drupal_get_path('module', 'comment') . '/comment.admin.inc');

    $comment = comment_load($cid);
    comment_delete($cid);
    _comment_update_node_statistics($comment->nid);

    unset($annotations[$nid][$id_annotation]);
    variable_set("gofast_annotations", $annotations);
  }

  print "[]";
}
