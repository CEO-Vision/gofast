<?php global $user;
global $base_url;
$can_update = node_access('update', node_load($gid));
$custom_logo = isset($custom_logo) ? file_create_url($custom_logo) : $base_url . '/sites/all/themes/bootstrap-keen/logo.png';
?>
<div class="d-flex pl-8 py-4 justify-content-between align-items-start" style="gap: 1rem;">
    <?php if ($can_update) : ?>
        <div class="image-input image-input-empty image-input-outline" id="gofast-og-home-space-logo" style="background-image: url(<?= $custom_logo ?>)">
            <div class="image-input-wrapper" style="width: 300px; height: 300px;"></div>
            <label class="btn btn-xs btn-icon btn-circle btn-white btn-hover-text-primary btn-shadow" data-action="change" data-toggle="tooltip" title="" data-original-title="<?= t('Change space picture', array(), array("context" => "gofast:gofast_og")) ?>">
                <i class="fas fa-pen icon-sm text-muted"></i>
                <input type="file" name="profile_avatar" accept=".png, .jpg, .jpeg, .webp" />
                <input type="hidden" name="profile_avatar_remove" />
            </label>
        </div>
    <?php else : ?>
        <img src="<?= $custom_logo ?>" alt="Logo" class="rounded shadow" style="width: 300px; height: 300px;">
    <?php endif; ?>
    <div class="flex-fill">
        <?= $content ?>
    </div>
</div>
<div class="mt-8 px-8 row">
    <div class="col-md-6 col-12">
        <div class="card card-custom mx-auto bg-light-primary">
            <div class="card-header border-0 px-4 py-2 min-h-40px bg-primary text-white">
                <h3 class="card-title align-items-start flex-column">
                    <span class="card-label font-weight-bolder font-size-h4 text-white"><?php echo t('Wikis / Forums', array(), array('context' => 'gofast:gofast_og')) ?></span>
                </h3>
            </div>
            <div class="card-body p-4 d-flex flex-column" style="height: 350px; overflow: scroll;">
                <ul class="nav nav-tabs nav-tabs-line nav-tabs-line-primary">
                    <li class="nav-item">
                        <a class="nav-link active" data-toggle="tab" href="#gofastOgHomeWikisTab"><?= t("Wikis") ?></a>
                    </li>
                    <li class="nav-item">
                        <a class="nav-link" data-toggle="tab" href="#gofastOgHomeForumsTab"><?= t("Forums") ?></a>
                    </li>
                </ul>
                <div id="gofastOgHomeTabContent" class="tab-content mt-5">
                    <div id="gofastOgHomeWikisTab" class="tab-pane fade show active">
                        <ul class="navi navi-accent navi-primary navi-hover navi-link-rounded" id="gofastOgHomeWikisContainer">
                            <div class="spinner spinner-track spinner-primary d-inline-flex gofast-spinner-xxl" style="left: 50%; transform: translateX(-2.5rem);"></div>
                        </ul>
                        <nav class="text-center mt-4">
                            <ul class="pagination pagination-sm justify-content-center" id="gofast-og-home-wikis-pager"></ul>
                        </nav>
                    </div>
                    <div id="gofastOgHomeForumsTab" class="tab-pane fade">
                        <ul class="navi navi-accent navi-primary navi-hover navi-link-rounded" id="gofastOgHomeForumsContainer">
                            <div class="spinner spinner-track spinner-primary d-inline-flex gofast-spinner-xxl" style="left: 50%; transform: translateX(-2.5rem);"></div>
                        </ul>
                        <nav class="text-center mt-4">
                            <ul class="pagination pagination-sm justify-content-center" id="gofast-og-home-forums-pager"></ul>
                        </nav>
                    </div>
                </div>
            </div>
        </div>
    </div>
    <div class="col-md-6 col-12">
        <div class="card card-custom mx-auto bg-light-primary">
            <div class="card-header border-0 px-4 py-2 min-h-40px bg-primary text-white">
                <h3 class="card-title align-items-start flex-column">
                    <span class="card-label font-weight-bolder font-size-h4 text-white"><?php echo t('Favorites', array(), array('context' => 'gofast:gofast_og')) ?></span>
                </h3>
            </div>
            <div class="card-body p-4 d-flex flex-column" id="gofastOgHomeFavoritesContainer" style="height: 350px; overflow: scroll;">
                <div class="spinner spinner-track spinner-primary d-inline-flex gofast-spinner-xxl" style="left: 50%; transform: translateX(-2.5rem);"></div>
            </div>
        </div>
    </div>
</div>
<script>
    jQuery(document).ready(function() {
        <?php if($can_update): ?>
            // image editable input
            let keenImageInput = new KTImageInput('gofast-og-home-space-logo');
            keenImageInput.on('change', async function(imageElement) {
                let imageFile = imageElement.input.files[0];
                if (imageFile.size > 35000000) {
                    Gofast.toast(Drupal.t("The file is too big!"), "error");
                    return;
                }
                let formData = new FormData();
                formData.set("image", imageFile);
                await fetch("/og/<?= $gid ?>/space_logo", {
                        method: "POST",
                        body: formData
                    })
                    .then(res => res.json())
                    .then(data => {
                        if (data.error) {
                            Gofast.toast(data.error, "error");
                        } else {
                            swal.fire({
                                title: Drupal.t('Image successfully changed!'),
                                type: 'success',
                                buttonsStyling: false,
                                confirmButtonText: Drupal.t('Awesome!'),
                                confirmButtonClass: 'btn btn-primary font-weight-bold'
                            });
                        }
                    });
            });
        <?php endif; ?>
        // favorites block
        jQuery.post(location.origin + "/gofast/bookmarks/favorites_contents", {
            gid: <?= $gid ?>
        }).done(function(data) {
            jQuery("#gofastOgHomeFavoritesContainer").html(data);
        });
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
                        '<span class="navi-text">' + wikiItem.title + '</span>' +
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
