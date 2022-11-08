<div class="breadcrumb-gofast <?php if($options["only_title"]){ print "breadcrumb-gofast-only-title"; } elseif($options["only_first"]){ print "breadcrumb-gofast-only-first"; }  elseif($options["show_title"]){ print "breadcrumb-gofast-show-title"; } else{ print "breadcrumb-gofast-full"; } ?>">
  <?php if($webdav_path && !$options['from_tooltip']){ ?>
    <div id="webdav-path" style="display: none;"><?php echo $webdav_path; ?></div>
  <?php } ?>
  <!--begin::Breadcrumb-->
  <?php foreach ($breadcrumb as $k => $crumbs) : ?>
  <ul fullpath="<?php echo end($crumbs)["location"]; ?>" class="breadcrumb breadcrumb-transparent font-weight-bold p-0 <?= $options["no_padding"] ? "my-0" : "my-2" ?> font-size-sm <?php if($k != 0 && $options["show_all_items"] !== true){ echo "gofast_breadcrumb_hidden_origine d-none";} ?>">
        <?php foreach ($crumbs as $kc => $crumb) : ?>
          <?php if ($kc == 0 && !$options["only_title"]) : ?>
            <li <?php if (!$options['from_tooltip']): ?> data-toggle="tooltip" data-placement="top" data-trigger="hover" <?php endif; ?> title="<?= t($crumb['name'], array(), array("context" => "gofast")) ?>"class="breadcrumb-item position-relative">
              <?php if ($crumb['text']) : ?>
                <i class="<?php echo $crumb['icon'] ?>"></i>
              <?php else : ?>
                <a class="text-hover-bold" href="<?php echo $crumb['href'] ?>" <?php if($options['in_modal']){print "data-dismiss='modal'";} ?> class="ajax-navigate" nid="<?php echo $crumb['gid'] ?>">
                  <i class="<?php echo $crumb['icon'] ?>"></i>
                </a>
              <?php endif; ?>
            </li>
          <?php else : ?>
            <li class="breadcrumb-item position-relative">
              <?php if ($crumb['text']) : ?>
                <?php echo $crumb['name'] ?>
                &nbsp;<?php echo $crumb['role']; ?>
              <?php else : ?>
                  <a class="text-hover-bold <?php if($crumb['is_mirror']){echo 'text-danger';} ?>" href="<?php echo $crumb['href']; if($crumb['folder'] && !gofast_mobile_is_mobile_domain()) { echo '?path=/Sites/' . rawurlencode($crumb['location']); } ?>" <?php if($options['in_modal']){print 'data-dismiss="modal"';} ?> class="ajax-navigate" nid="<?php echo $crumb['gid'] ?>"><?php echo $crumb['name'] ?></a>               
                <?php if($crumb['is_mirror']){ ?>
                  <i class="fas fa-exchange-alt ml-2" data-placement="top" data-toggle="tooltip" title="<?php echo t('The location in red means that this location is a mirror location (the contents are available in the different locations)'); ?>"></i>
                <?php } ?>
                &nbsp;<?php echo $crumb['role']; ?>
              <?php endif; ?>
            </li>
          <?php endif; ?>
        <?php endforeach; ?>
      <?php if ((count($breadcrumb) > 1 && $k == 0) && ($options["show_all_items"] !== true) &&  ($options["only_first"] !== true)) : ?>
        <i class='fas fa-plus-circle ml-1' id='gofast_breadcrumb_more' style='cursor:pointer;color:black;' title=""></i>
      <?php endif; ?>
    </ul>
    <?php if ($options["only_first"]) {
      break;
    } ?>
  <?php endforeach; ?>
  <!--end::Breadcrumb-->

  <script type="text/javascript">
    jQuery(document).ready(function() {
      window.initBreadCrumb();
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

