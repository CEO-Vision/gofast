<?php
    $first_breadcrumb = array_shift($breadcrumb) ?? array();
    $last_crumb = array_pop($first_breadcrumb);
    $toggler = "";
    if ((count($breadcrumb)) && ($options["show_all_items"] !== true) && ($options["only_first"] !== true)) {
        $toggler = "<i class='fas fa-chevron-right text-muted ml-1' data-icons='fa-chevron-right/fa-chevron-down' id='gofast_breadcrumb_more' style='cursor:pointer;color:black;'></i>";
    }
?>
<div class="h-100 overflow-auto <?= $options["no_padding"] ? "mt-0" : "mt-2" ?> breadcrumb-gofast <?php if($options["only_title"]){ print "breadcrumb-gofast-only-title"; } elseif($options["only_first"]){ print "breadcrumb-gofast-only-first"; }  elseif($options["show_title"]){ print "breadcrumb-gofast-show-title"; } else{ print "breadcrumb-gofast-full"; } ?>">
    <ul fullpath="<?php echo $last_crumb["location"]; ?>" class="d-flex flex-column align-items-start breadcrumb breadcrumb-transparent font-weight-bold p-0 m-0 font-size-md">
        <li class="d-flex w-100" id="title-reference">
        <?php if ($type =="article" && isset($node->weight)) : ?>
            <span><strong id="gofast-wiki-weight-indicator" style="font-weight: 700;">W<?= str_pad($node->weight, 3, "0", STR_PAD_LEFT) ?></strong>&nbsp;-</span>
        <?php endif; ?>
            <div class="breadcrumb-item align-items-center" data-title="<?= $last_crumb["title"] ?: "" ?>" data-animation="true" data-trigger="hover" data-placement="bottom" data-boundary="window" data-toggle="tooltip"><?= $last_crumb["name"] ?>
            <i class='fas fa-chevron-right text-muted ml-1' data-icons='fa-chevron-right/fa-chevron-down' id='gofast_title_metadata_more' style='cursor:pointer;color:black;'></i>
</div>
        </li>
        <div class="gofast-node-title-row d-none">
            <div class="d-flex">
                <b class="mr-2"><?= t('Title')?> : </b>
                <div id="gofast-node-title-editable-input" class="gofast-node-title-value breadcrumb-item d-flex w-100" title="<?= t("Click here to change the title metadata", array(), array('context' => 'gofast')) ?>">
                    <div class="w-100">
                        <?= $node->field_title[LANGUAGE_NONE][0]["value"] ?? "" ?>
                    </div>
                </div>
            </div>
        </div>
        <div class="font-size-sm d-flex align-items-center"><?= theme("gofast_crumbs", array("crumbs" => $first_breadcrumb, "options" => $options, "size" =>
        "sm")) . $toggler ?></div>
    </ul>
    <div class="breadcrumbAnimator d-none">
    <?php
        foreach ($breadcrumb as $k => $crumbs) :
            array_pop($crumbs);
    ?>
        <ul fullpath="<?= end($crumbs)["location"]; ?>" class="breadcrumb breadcrumb-transparent font-weight-bold p-0 <?= $options["no_padding"] ? "my-0" : "my-2" ?> font-size-sm gofast_breadcrumb_hidden_origine">
            <?= theme("gofast_crumbs", array("crumbs" => $crumbs, "options" => $options, "size" =>
        "sm")) ?>
        </ul>
    <?php endforeach; ?>
    </div>
    <script type="text/javascript">
      jQuery(document).ready(function() {
          <?php if ($options["editable"] === TRUE): ?> window.initBreadCrumb(); <?php endif; ?>
          window.initTitleInput();
          $('[data-toggle="tooltip"]').tooltip();
      });
  </script>
</div>
