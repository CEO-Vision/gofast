<?php
$items_count = count($nodes_description);
?>


<h3> <?= format_plural($items_count, t("Are you sure you want to extract the following item?", [], ["context" => "gofast:ajax_file_browser"]), t("Are you sure you want to extract the following items?", [], ["context" => "gofast:ajax_file_browser"]), [], ["context" => "gofast:ajax_file_browser"]) ?></h3>

<?php if ($items_count) : ?>
    <div class="alert alert-custom alert-notice alert-light-info fade show mb-5"
         role="alert">
        <div class="alert-icon"><i class="flaticon-information"></i></div>
        <div class="alert-text">
          <?= t("Please note that a new folder will be created with the name of the zip file and the files will be extracted in it.", [], ["context" => "gofast:ajax_file_browser"]) ?>
        </div>
    </div>
<?php endif; ?>

<?php foreach ($nodes_description as $index => $node_description) :
  $locations_string = implode("", array_map(function ($loc) {
    return "<ul class='list-group'>" . str_replace("/Sites", "", $loc) . "</ul>";
  }, $node_description->locations));
  $is_templates = $node_description->title == "TEMPLATES";
  ?>
    <div style="width: max-content;" class="my-2"
         <?php if (count($node_description->locations) > 1) : ?>data-toggle="tooltip"
         data-html="true" data-trigger="hover" data-placement="bottom"
         title="<li class='border-0 list-group-item'><?= $locations_string ?></li>" <?php endif; ?> <?php if (!empty($node_description->children)) : ?> type="button" data-toggle="collapse" data-target="#removableContent<?= $index ?>" <?php endif; ?>>
        <div class="d-flex align-items-center">
            <i class="fa-2x <?= $node_description->icon ?>" <?= $is_templates ? "style=\"color: #F0685A !important;\"" : "" ?>></i>
            &nbsp;<span
                    class="font-size-lg"><?= $node_description->title ?></span>
          <?php if (count($node_description->locations) > 1) : ?>&nbsp;<i
                  class="fa fa-question-circle"></i><?php endif; ?>
        </div>
      <?php if (!empty($node_description->children)) : ?>
          <div class="collapse" id="removableContent<?= $index ?>">
              <div class="font-weight-bold">
                <?= t("The folder above has the following content:", [], ["context" => "gofast:ajax_file_browser"]) ?>
              </div>
            <?php foreach ($node_description->children as $child) :
              $is_templates = $child->title == "TEMPLATES";
              ?>
                <div>
                    <i class="<?= $child->icon ?>" <?= $is_templates ? "style=\"color: #F0685A !important;\"" : "" ?>></i>
                    &nbsp;<span><?= $child->title ?></span>
                </div>
            <?php endforeach; ?>
          </div>
      <?php endif; ?>
    </div>
<?php endforeach; ?>

<script>
  jQuery(document).ready(function () {
    setTimeout(function () {
      jQuery("body").tooltip({selector: '[data-toggle=tooltip]'});
    }, 1000);
  });
</script>