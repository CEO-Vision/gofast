<div class="breadcrumb-gofast <?php if($options["only_title"]){ print "breadcrumb-gofast-only-title"; } elseif($options["only_first"]){ print "breadcrumb-gofast-only-first"; }  elseif($options["show_title"]){ print "breadcrumb-gofast-show-title"; } else{ print "breadcrumb-gofast-full"; } ?>">
  <?php if($webdav_path && !$options['from_tooltip']){ ?>
    <div id="webdav-path" style="display: none;"><?php echo $webdav_path; ?></div>
  <?php } ?>
  <!--begin::Breadcrumb-->
  <?php foreach ($breadcrumb as $k => $crumbs) : ?>
    <ul fullpath="<?php echo end($crumbs)["location"]; ?>" class="breadcrumb breadcrumb-transparent font-weight-bold p-0 <?= $options["no_padding"] ? "my-0" : "my-2" ?> font-size-sm <?php if($k != 0 && $options["show_all_items"] !== true){ echo "gofast_breadcrumb_hidden_origine d-none";} ?>">
      <?php echo theme("gofast_crumbs", array("crumbs" => $crumbs, "options" => $options)) ?>
      <?php if ((count($breadcrumb) > 1 && $k == 0) && ($options["show_all_items"] !== true) && ($options["only_first"] !== true)) : ?>
        <i class='fas fa-chevron-right text-muted ml-1' data-icons='fa-chevron-right/fa-chevron-down' id='gofast_breadcrumb_more' style='cursor:pointer;color:black;' title=""></i>
      <?php endif; ?>
    </ul>
    <?php if ($options["only_first"]) {
      break;
    } ?>
  <?php endforeach; ?>
  <!--end::Breadcrumb-->

  <script type="text/javascript">
    jQuery(document).ready(function() {
      <?php if ($options["editable"] === TRUE): ?> window.initBreadCrumb(); <?php endif; ?>
      <?php if (!$options['from_tooltip']): ?> $('[data-toggle="tooltip"]').tooltip(); <?php endif; ?>
    });
  </script>
</div>
<?php if($options["manage_locations"]) {
    $pop_over_option = [
      'href' => '/modal/nojs/node/' . $nid . '/manage-locations',
      'container_id' => 'popup_block_' . $nid,
      'container_class' => NULL,
      'relative_positioning' => TRUE,
    ];
    echo theme('node_locations', $pop_over_option);
} ?>

