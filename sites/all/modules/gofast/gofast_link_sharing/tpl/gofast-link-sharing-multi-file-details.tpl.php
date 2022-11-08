<?php global $user; ?>
<div class="mt-6 row d-flex justify-content-center ">
    <form id="gofast-multi-link-sharing-form" method="POST" action="<?= $_SERVER["REQUEST_URI"] ?>">
        <div class="card shadow w-100 d-flex flex-column align-items-center">
            <div class="card-header w-75 pb-0">
                <div class="card-title">
                    <h2 class="display-2 text-primary text-center"><?= t('Shared Documents : ', array(), array('context' => 'gofast:gofast_link_sharing')) ?></h2>
                </div>
                <div class="card-toolbar d-flex align-items-start justify-content-center">
                    <div class="w-30px form-item form-type-checkbox align-items-start d-flex flex-column mb-5"><label class="checkbox checkbox-outline checkbox-outline-2x checkbox-primary mr-3" for="edit-check-all"><input type="checkbox" id="edit-check-all" class="form-checkbox"><span class="mr-2"></span></label>
                    </div>
                    <div class="w-50"><label class="h3 w-100 text-center"><?php print t('Title', array(), array('context' => 'gofast:gofast_link_sharing')) ?></label></div>
                    <div class="w-25"><label class="h3 w-100 text-center"><?php print t('Version', array(), array('context' => 'gofast')) ?></label></div>
                </div>
            </div>
            <div class="card-body w-75 py-0">
                <?php foreach ($form["shares"]["#options"] as $nid => $link) : ?>
                    <div class="gofast_link_sharing_checkbox w-100 d-flex align-items-center justify-content-center pt-4">
                        <div class="w-30px"><?php
                                            unset($form["shares"][$nid]["#title"]);
                                            echo drupal_render($form["shares"][$nid]);
                                            ?></div>
                        <div class="w-50 d-flex flex-column align-items-center">
                            <span class="d-flex align-items-center" style="gap: .5rem;">
                                <?= theme("gofast_node_icon_format", array("node" => node_load($nid))) ?>
                                <p id="link_sharing_title_<?= $nid ?>" class="mb-0 h4 font-weight-light"><a class="text-decoration-none" href="<?= $base_url . "/node/" . $nid ?>"><?php print $link["title"] ?></a></p>
                            </span>
                        </div>
                        <div class="w-25 d-flex flex-column align-items-center">
                            <p id="link_sharing_version_<?= $nid ?>" class="h4 font-weight-light"><?php print $link["version"] ?></p>
                        </div>
                    </div>
                    <div class="separator separator-solid separator-border-2 w-100"></div>
                <?php endforeach; ?>
                <div class="d-flex align-items-center justify-content-center my-4" style="gap: 2rem;">
                    <?php echo render($form['actions']); ?>
                    <?php if ($user->uid == '0') { ?>
                        <span class="h3"><?php print strtoupper(t("OR", array(), array("context" => "gofast"))) ?></span>
                        <a class="btn btn-primary gofast_link_sharing_button" href="<?php if (!empty($nid)) {
                                                                                        print "/?node=" . $nid;
                                                                                    } ?>" role="button"><?php print t('Login', array(), array("context" => 'gofast')) ?></a>
                    <?php } ?>
                </div>
            </div>
            <div class="separator separator-solid separator-border-2 w-100"></div>
            <div class="lead text-center py-4">
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
        <?php drupal_process_attached($form); ?>
        <div class="d-none"><?php echo drupal_render_children($form); ?></div>
    </form>
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
</style>
