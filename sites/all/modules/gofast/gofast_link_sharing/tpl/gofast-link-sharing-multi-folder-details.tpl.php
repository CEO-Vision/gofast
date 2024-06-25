<?php global $user; ?>
<div class="mt-6 row d-flex justify-content-center ">
    <form id="gofast-multi-link-sharing-form" method="POST" action="<?= $_SERVER["REQUEST_URI"] ?>">
        <div class="card shadow w-100 d-flex flex-column align-items-center">
            <div class="card-header w-75 pb-0">
                <div class="card-title">
                    <h2 class="display-2 text-primary text-center"><?= t('Shared Folder', array(), array('context' => 'gofast:gofast_link_sharing')) ?>:</h2>
                </div>
            </div>
            <div class="card-body w-75 py-0">
                <?php print theme('gofast_link_sharing_share_folder_contents',
                    array('nodes_description' => [$folder_contents], 'showTitle' => false))
                ?>
                <div class="d-flex align-items-center justify-content-center my-4" style="gap: 2rem;">
                <button class=" btn-warning gofast_link_sharing_button btn" type="button" id="edit-submit" name="op" ><?= t('Download') ?></button>
                    <?php if ($user->uid == '0') { ?>
                        <span class="h3"><?php print strtoupper(t("OR", array(), array("context" => "gofast"))) ?></span>
                        <a class="btn btn-primary " href="<?php if (!empty($hash)) {
                                                                                        print "/multi_sharing/logged_in/" . $hash;
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
                        <?php
                            $start_tag = $ask_join_link ? "" : '<a class="navi-link ctools-use-modal" href="' . $ask_join_link . '">';
                            $end_tag = $ask_join_link ? "" : "</a>";
                            print html_entity_decode(t('You are logged in, but you are not a member of the space(s) where documents are shared: you can download, but also @start_tagrequest access to these spaces@end_tag to be able to easily collaborate. In this case, a notification will be sent to the administrators to validate or deny your request.', array(
                            "@start_tag" => $start_tag,
                            "@end_tag" => $end_tag,
                            ), array("context" => "gofast_link_sharing")));
                        ?>
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
<script>
    (function (jQuery, Gofast, Drupal) {
        jQuery(document).ready(function() {
            const downloadText = jQuery(".gofast_link_sharing_button").first().text();

            /** Displays a toast and resets the button text and appearance. Called when the download errors. */
            function onDownloadError() {
                Gofast.toast(Drupal.t("Download failed", {}, {context: 'gofast:gofast_link_sharing'}), "error");
                // reset button
                $(".gofast_link_sharing_button").text(downloadText);
                $(".gofast_link_sharing_button").attr("disabled", false);
                $(".gofast_link_sharing_button").removeClass("btn-success");
                $(".gofast_link_sharing_button").addClass("btn-warning");
            }

            jQuery(".gofast_link_sharing_button").on("click", function() {
                jQuery(this).html('<span class="spinner-border spinner-border-sm" role="status" aria-hidden="true"></span>&nbsp;');
                jQuery(this).append(Drupal.t("Download started...", {}, {context: 'gofast:gofast_link_sharing'}));
                //make ajax call to download the folder
                var url =  '/public/multi_sharing/dl?workspace=<?= $folder_store_id ?>&hash=<?= $hash ?>';
                jQuery.ajax({
                    url: url,
                    type: 'GET',
                    success: async function(downloadObject) {
                        // link may have been expired or invalid, in that case, we receive a redirect instead of
                        // an error response and JQuery doesn't allow us to differentiate a 200 OK from a 3XX
                        // while both count as success. hacky fix checks if returned value is an object instead of a
                        // string (redirected page's HTML)
                        if(typeof downloadObject !== 'object') {
                            onDownloadError();
                            return;
                        }

                        await Gofast.ITHit._checkDownloadStatus(downloadObject);
                        $(".gofast_link_sharing_button").removeClass("btn-warning");
                        $(".gofast_link_sharing_button").addClass("btn-success");
                        $(".gofast_link_sharing_button").attr("disabled", true);
                        // Check if the download is completed
                        var interval = setInterval(function() {
                        if (Gofast.ITHit._completedDownloads.includes(downloadObject.id)) {
                            clearInterval(interval);
                            Gofast.toast(Drupal.t("Download completed", {}, {context: 'gofast:gofast_link_sharing'}), "success");
                            $(".gofast_link_sharing_button").text(Drupal.t("Download again", {}, {context: 'gofast:gofast_link_sharing'}));
                            $(".gofast_link_sharing_button").attr("disabled", false);
                            $(".gofast_link_sharing_button").removeClass("btn-success");
                            $(".gofast_link_sharing_button").addClass("btn-warning");
                        }
                        }, 1000);
                    },
                    error: function (_jqXHR, _textStatus, _errorThrown) {
                        onDownloadError();
                    },
                });
            });
        });  
    })(jQuery, Gofast, Drupal);
</script>
