<?php
global $base_url;
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
<div class="row d-flex justify-content-center ">
  <div class="<?php if($user->uid != 0){echo "w-75 ml-auto mr-auto mt-8";}?> p-6 rounded shadow d-flex flex-column align-items-center" style="gap: 3rem;">
    <h2 class="display-2 text-primary"><?php print t('Shared Document', array(), array('context' => 'gofast:gofast_link_sharing')) ?></h2>
    <div class="d-flex flex-column align-items-center">
      <label class="h3" for="link_sharing_title"><?php print t('Title', array(), array('context' => 'gofast:gofast_link_sharing')) ?></label>
      <span class="d-flex align-items-center" style="gap: .5rem;">
        <?= theme("gofast_node_icon_format", array("node" => node_load($nid))) ?>
        <p id="link_sharing_title_<?= $nid ?>" class="mb-0 h4 font-weight-light"><span class="text-decoration-none"><?php print $title ?></span></p>
      </span>
    </div>
    <div class="d-flex flex-column align-items-center">
      <label class="h3" for="link_sharing_version"><?php print t('Version', array(), array('context' => 'gofast')) ?></label>
      <p id="link_sharing_version" class="h4 font-weight-light"><?php print $version ?></p>
    </div>
    <div class="separator separator-solid separator-border-2 w-100"></div>
    <div class="d-flex align-items-center" style="gap: 2rem;">
      <?php if ($user->uid == '0') { ?>
        <div class="row d-block m-2">
          <div class="mb-5">Pas de compte?</div>
          <div class="">
            <a class="btn btn-warning gofast_search_link gofast_link_sharing_button" role="button"><?php print t('Download', array(), array("context" => 'gofast')) ?></a>
          </div>
        </div>
        <div class="row d-block m-2">
          <div class="">
            <span class="h3"><?php print strtoupper(t("OR", array(), array("context" => "gofast"))) ?></span>
          </div>
        </div>
        <div class="row d-block m-2">
          <div class="mb-5">J’ai un compte</div>
          <div class="">
            <a class="btn btn-primary gofast_link_sharing_button" href="<?php if (!empty($nid)) {
                                                                          print "/?node=" . $nid;
                                                                        } ?>" role="button"><?php print t('Login', array(), array("context" => 'gofast')) ?></a>
          </div>
        </div>
      <?php } else { ?>
        <a class="btn btn-warning gofast_search_link gofast_link_sharing_button" role="button"><?php print t('Download', array(), array("context" => 'gofast')) ?></a>
      <?php } ?>
    </div>
    <div class="d-none">
      <p id="hash_link"><?php print $hash ?></p>
    </div>
    <div class="separator separator-solid separator-border-2 w-100"></div>
    <div class="lead text-center">
      <?php if ($user->uid == '0') { ?>
        <p>
          <?php print t('GoFAST Digital Workplace GED offers a unified work environment to manage documents from model to e-signature, office and remote work.', array(), array("context" => "gofast_link_sharing")); ?>
        </p>
        <p>
        <?php print t('The sovereign and Open Source alternative to "GAFAM" exists well and truly: an efficient and available Collaborative EDM OnPremise, in dedicated SaaS or in SecNumCloud to be compliant with the circular !cloud_center. Click !here to discover GoFAST', array("!cloud_center" => '<a target="_blank" href="https://www.legifrance.gouv.fr/circulaire/id/45205">« Cloud au centre »</a>', '!here' => '<a target="_blank" href="https://www.ceo-vision.com/fr/content/fonctionnalites-gofast-digital-workplace-plateforme-ged-open-source?utm_source=gofast&utm_medium=referral&utm_campaign=lien-telechargement-gofast&utm_content=page-de-telechargement">' . t('here',array(), array('context' => 'gofast')) . '</a>'), array("context" => "gofast_link_sharing")) ?>
        </p>
      <?php } else { ?>
        <p class="w-75 m-auto">
          <?php print t('You are logged in, but you are not a member of the space(s) where documents are shared: you can download, but also request access to these spaces to be able to easily collaborate. In this case, a notification will be sent to the administrators to validate or deny your request.', array(), array("context" => "gofast_link_sharing")) ?>
        </p>
      <?php } ?>
    </div>

  </div>
</div>
<style>
  .gofast_link_sharing_button {
    /** preloading the shadow to avoid performance hit */
    box-shadow: transparent 0px 50px 100px -20px, transparent 0px 30px 60px -30px, transparent 0px -2px 6px 0px inset;
    transition: all 0.3s ease-in-out !important;
  }

  .gofast_link_sharing_button:hover {
    transform: scale(1.1) translateY(-3px);
    box-shadow: rgba(50, 50, 93, 0.25) 0px 50px 100px -20px, rgba(0, 0, 0, 0.3) 0px 30px 60px -30px, rgba(10, 37, 64, 0.35) 0px -2px 6px 0px inset;
  }
  
  #content-main-container{
    background-color: white;
  }
</style>
