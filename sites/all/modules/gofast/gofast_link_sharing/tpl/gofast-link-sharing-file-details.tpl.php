<?php
global $user;
/**
 * @file
 * Display the body of the document access' page for gofast_link_sharing module
 *
 * Available variables:
 * - $title : name of the shared document
 * - $version : version of the shared document
 * - $link : cmis(Alfresco) URL to access the shared document
 *
 * @see template_preprocess_block()
 *
 * @ingroup themeable
 */
?>
<!-- GoFast link Sharing - File-Details Template -->
<div class="row">
  <div class="col-sm-9">
    <h4><?php print t('Shared Document', array(), array('context' => 'gofast:gofast_link_sharing')) ?></h4>
    <div class="form-group">
      <div class="col-sm-2">
        <label for="title"><?php print t('Title', array(), array('context' => 'gofast:gofast_link_sharing')) ?></label>
      </div>
      <div class="col-sm-10">
        <p class="form-control-static"><?php print $title ?></p>
      </div>
    </div>
    <div class="form-group">
      <div class="col-sm-2">
        <label for="version"><?php print t('Version', array(), array('context' => 'gofast')) ?></label>
      </div>
      <div class="col-sm-10">
        <p class="form-control-static"><?php print $version ?></p>
      </div>
    </div>
    <div class="form-group">
      <div class="text-right">
          <a class="btn btn-primary gofast_search_link" role="button"><?php print t('Download', array(), array("context" => 'gofast')) ?></a>
          <!--<a class="btn btn-primary gofast_search_link" href="<?php //print $link ?>" role="button"><?php //print t('Download', array(), array("context" => 'gofast')) ?></a>-->
      </div>
    </div>
    <?php if ($user->uid == '0'){ ?>
    <center>
    <div><hr><h3 class="login-or">OU</h3></div>
    <a class="btn btn-primary" href="<?php if(!empty($nid)){ print "/?node=" . $nid;} ?>" role="button"><?php print t('Login', array(), array("context" => 'gofast')) ?></a>
    </center>
    <?php } ?>
    <div class="hidden">
        <p id="hash_link"><?php print $hash ?></p>
    </div>
  </div>
</div>
  