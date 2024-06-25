<?php foreach ($paths as $path) :
    $path = str_replace(["/Sites/", "/_"], "/", $path);
?>
    <div class='gofast_template_widget_path mb-2'><?= implode("</span>/<span>", explode("/", $path)) ?></div>
<?php endforeach; ?>