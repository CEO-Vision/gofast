<?php foreach ($docs as $doc) : ?>
    <div class="d-flex align-items-center p-2"> <i class="<?= $doc->icon ?>"></i>
        &nbsp;<a href="/node/<?= $doc->nid ?>" class="font-size-lg"><?= str_replace(["'", "\""], " ", $doc->title) ?></a>
    </div>
<?php endforeach; ?>