<div class='alert alert-custom alert-notice alert-light-warning' role='alert'>
    <div class='alert-icon'><i class='flaticon-warning'></i></div>
    <div class='alert-text m-0'>
        <span><?= t("Are you sure you want to delete this bookmark collection :", array(), array("context" => "gofast:gofast_bookmark_collection")) ?> <span><i class="fa <?= $tree[0]["iconSkin"] ?> fa-lg"></i> <?= $tree[0]["name"] ?> ?</span>
    </div>
</div>
<div>
    <p><?= t("All theses items are going to be deleted :", array(), array("context" => "gofast:gofast_bookmark_collection")) ?></p>
    <ul>
    <?php foreach($tree as $items): ?>
        <li>
            <span><i class="fa <?= $items["iconSkin"] ?> fa-lg"></i> <?= $items["name"] ?> (<?= $items["itemPath"] ?>)</span>
        </li>
    <?php endforeach; ?>
    </ul>
</div>
<div class="btn btn-danger btn-sm" value="Delete" onclick="Gofast.Bookmark_Collection.removeBookmarkCollection('<?= $treeId ?>', <?= $tree[0]['bcid'] ?>)"><?= t("Delete") ?></div>
<div class="btn btn-secondary btn-sm" value="Cancel" onclick="Drupal.CTools.Modal.dismiss()"><?= t("Cancel") ?></div>