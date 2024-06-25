<table class="table table-striped gy-7 gs-7">
    <thead>
        <tr>
            <?php foreach ($columns as $column) : ?>
                <th class="min-w-100px"><?= $column ?></th>
            <?php endforeach; ?>
        </tr>
    </thead>
    <tbody>
        <?php if (!empty($contents)) : ?>
            <?php foreach ($contents as $content) : ?>
                <?= theme($theme, ["content" => $content]) ?>

            <?php endforeach; ?>
        <?php else : ?>
            </br>
            <p> <b><?= $placeholder ?></p> </b></br>
        <?php endif; ?>
    </tbody>
</table>