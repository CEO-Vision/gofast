<?php global $user;
global $base_url;
$node = node_load($gid);
$article_homepage = gofast_og_get_article_homepage_from_og($gid);
$can_update = node_access('update', $node);
$custom_logo = isset($custom_logo) ? file_create_url($custom_logo) . '?rand='. rand(1, 1000) : $base_url . '/sites/all/themes/bootstrap-keen/logo.png';
?>
<div class="d-flex h-100 overflow-scroll" data-parent-tab="oghome" data-gid="<?= $gid ?>" id="gofastHomePage">
    <div class="d-flex mt-4 pl-8 pr-8 align-items-center flex-column" style="gap: 1rem;">
        <?php if ($can_update) : ?>
            <div class="image-input image-input-empty image-input-outline" id="gofast-og-home-space-logo" style="background-image: url(<?= $custom_logo ?>); background-position: center; background-size: contain;">
                <div class="image-input-wrapper" style="width: 300px; height: 300px;"></div>
                <a href="/modal/nojs/og/edit-space-logo/<?= $gid ?>" class="ctools-use-modal">
                <label id="gofastSpaceLogoButton" class="btn btn-xs btn-icon btn-circle btn-white btn-hover-text-primary btn-shadow" data-action="change" data-toggle="tooltip" title="" data-original-title="<?= t('Change space picture', array(), array("context" => "gofast:gofast_og")) ?>">
                    <i class="fas fa-edit icon-sm text-muted"></i>
                    <input type="file" name="profile_avatar" accept=".png, .jpg, .jpeg, .webp" />
                    <input type="hidden" name="profile_avatar_remove" />
                </label>
                </a>
            </div>
        <?php else : ?>
            <img src="<?= $custom_logo ?>" alt="Logo" class="rounded shadow" style="width: 300px; height: 300px;">
        <?php endif; ?>
        <div class="h-100" style="width: 300px;">
            <div class="card card-custom mx-auto bg-light-primary h-100">
                <div class="card-header border-0 px-4 py-2 min-h-40px bg-primary text-white">
                    <h3 class="card-title align-items-start flex-column">
                        <span class="card-label font-weight-bolder font-size-h4 text-white"><?php echo t('Favorites', array(), array('context' => 'gofast:gofast_og')) ?></span>
                    </h3>
                </div>
                <div class="card-body p-4 d-flex flex-column" style="height: 350px; overflow: scroll;">
                    <ul class="navi navi-accent navi-primary navi-hover navi-link-rounded" id="gofastOgHomeFavoritesContainer">
                        <div class="spinner spinner-track spinner-primary d-inline-flex gofast-spinner-xxl" style="left: 50%; transform: translateX(-2.5rem);"></div>
                    </ul>
                    <nav class="text-center mt-4">
                        <ul class="pagination pagination-sm justify-content-center" id="gofast-og-home-favorites-pager"></ul>
                    </nav>
                </div>
            </div>
        </div>
    </div>
    <div class="flex-fill">
        <div class="<?php print !$only_article ? "p-4": "" ?>">
            <div class="ogSpaceTitleContainer">
                <h3 class="ogSpaceTitle"><?= $node->title ?></h3>
            </div>
            <?php if (isset($description) && !empty($description)) : ?>
                <div class="card card-custom mx-auto bg-white h-100 mb-4">
                    <div class="card-header border-0 px-4 py-2 min-h-40px bg-primary text-white">
                        <h3 class="card-title align-items-start flex-column">
                            <span class="card-label font-weight-bolder font-size-h4 text-white"><?php echo t('Description', array(), array('context' => 'gofast:gofast_og')) ?></span>
                        </h3>
                    </div>
                    <div class="homeDescriptionContainer image-input w-100">
                        <?php if ($can_update) : ?>
                        <label class="btn btn-xs btn-icon btn-circle btn-white btn-hover-text-primary btn-shadow" data-action="change" onClick="Gofast.triggerEditableInput('.gofastArticleDescription.homeDescription > div')">
                            <i class="fas fa-edit icon-sm text-muted"></i>
                        </label>
                        <?php endif; ?>
                        <div data-gid="<?= $gid ?>" class="gofastArticleDescription homeDescription border mb-2 p-2 rounded shadow-sm font-weight-bold">
                            <?= $description ?>
                        </div>           
                    </div>
                </div>
            <?php endif; ?>
            <?= $content ?>
        </div>
    </div>
</div>
<script>
    jQuery(document).ready(function() {
        <?php if($can_update && $node->type != "private_space") : ?>
            const spaceTitleElement = $(".ogSpaceTitle");
            spaceTitleElement.text("");
            GofastEditableInput(spaceTitleElement[0], "<?= $node->title ?>", "text", {
                save: async (newContent) => {
                    // disable input while saving
                    spaceTitleElement.css("pointer-events", "none");
                    spaceTitleElement.parent().css("cursor", "not-allowed");
                    $(".ogSpaceTitleContainer").prepend($("<div class='spinner mr-5 mb-2'>"));
                    await _gofastPostSimulator({
                        pk: "<?= $node->nid ?>",
                        name: "title",
                        value: newContent,
                    });
                    // re-enable it after
                    spaceTitleElement.css("pointer-events", "auto");
                    spaceTitleElement.parent().css("cursor", "auto");
                    $(".ogSpaceTitleContainer .spinner").remove();
                    // reload browser in the background to refresh the browser and the history as well
                    Gofast.ITHit.reload();
                },
                isEditable: true,
                showConfirmationButtons: true
            });
        <?php endif; ?>
        $('#ogtab_home').on('click',function(){
            // favorites block: refresh on click in case favorites have been updated on the documents tab in the meantime
            if(!$("#ogtab_home").hasClass("active")){
                Gofast.og.getSpaceBookmarks("<?= $gid ?>");
            }
        });
        Drupal.attachBehaviors();
        // unwrap left menu: we try to do it only if a homepage actually exists
        <?php if ($article_homepage) : ?>
            // but we target the gid since it's the gid which is referred in the "book" element in the left menu
            Drupal.settings.gofast_selected_book = <?= $gid ?>;
            Gofast.selectCurrentWikiArticle(false);
        <?php endif; ?>
        // favorites block
        Gofast.og.getSpaceBookmarks("<?= $gid ?>");
        // we don't load wikis neither forums tabs for now
        return;
        // wikis tab
        jQuery.post(location.origin + "/space/book/<?= $gid ?>")
            .done(function(data) {
                jQuery("#gofastOgHomeWikisContainer").html("");
                for (const wikiItem of data) {
                    $("#gofastOgHomeWikisContainer").append(
                        '<li class="navi-item">' +
                        '<a href="' + location.origin + '/node/' + wikiItem.nid + '" class="navi-link w-100">' +
                        '<span class="navi-icon mr-2">' +
                        '<i class="fas fa-book-open"></i>' +
                        '</span>' +
                        '<span class="navi-text">' + wikiItem.name + '</span>' +
                        '</a>' +
                        '</li>'
                    );
                }
                jQuery('#gofastOgHomeWikisContainer').pager({
                    pagerSelector: '#gofast-og-home-wikis-pager',
                    perPage: 10,
                    numPageToDisplay: 5,
                    isFlex: true
                });
            });
        // forums tabs
        jQuery.post(location.origin + "/space/forum/<?= $gid ?>")
            .done(function(data) {
                jQuery("#gofastOgHomeForumsContainer").html("");
                for (const forumItem of data) {
                    $("#gofastOgHomeForumsContainer").append(
                        '<li class="navi-item">' +
                        '<a href="' + location.origin + '/node/' + forumItem.nid + '" class="navi-link w-100">' +
                        '<span class="navi-icon mr-2">' +
                        '<img width="40" style="border-radius: 5px;" src="' + forumItem.url_picture + '">' +
                        '</span>' +
                        '<span class="navi-text">' + forumItem.title + '</span>' +
                        '</a>' +
                        '</li>'
                    );
                }
                jQuery('#gofastOgHomeForumsContainer').pager({
                    pagerSelector: '#gofast-og-home-forums-pager',
                    perPage: 10,
                    numPageToDisplay: 5,
                    isFlex: true
                });
            });
    });
</script>
