<?php foreach ($crumbs as $kc => $crumb) : ?>
    <?php if ($kc == 0 && !$options["only_title"]) : ?>
    <li <?php if (!$options['from_tooltip']): ?> data-toggle="tooltip" data-placement="right" data-trigger="hover" <?php endif; ?> title="<?= t($crumb['name'], array(), array("context" => "gofast")) ?>" class="breadcrumb-item position-relative">
        <?php if ($crumb['text']) : ?>
        <i class="<?php echo $crumb['icon'] ?>"></i>
        <?php else : ?>
        <a class="text-hover-bold" href="<?php echo $crumb['href'] ?>" <?php if($options['in_modal']){print "data-dismiss='modal'";} ?> class="ajax-navigate" nid="<?php echo $crumb['gid'] ?>">
            <i class="<?php echo $crumb['icon'] . (isset($size) ? " font-size-" . $size : "") ?>"></i>
        </a>
        <?php endif; ?>
    </li>
    <?php else : ?>
    <li class="breadcrumb-item position-relative ariane-path-item" id="ariane-path-item" data-title="<?= $crumb["title"] ?: "" ?>" data-animation="true" data-trigger="hover" data-placement="bottom" data-boundary="window" data-toggle="tooltip">
        <?php if ($crumb['text']) : ?>
        <?php echo $crumb['name'] ?>
        &nbsp;<?php echo $crumb['role']; ?>
        <?php else : ?>
        <a class="text-hover-bold <?php if($crumb['is_mirror']){echo 'text-danger';} ?>" href="<?php echo $crumb['href']; if($crumb['folder']) { echo '?path=/Sites/' . rawurlencode($crumb['location']); } ?>" <?php if($options['in_modal']){print 'data-dismiss="modal"';} ?> class="ajax-navigate" nid="<?php echo $crumb['gid'] ?>"><?php echo $crumb['name'] ?></a>
        <?php if($crumb['is_mirror']){ ?>
            <i class="fas fa-exchange-alt ml-2" data-placement="top" data-toggle="tooltip" title="<?php echo t('The location in red means that this location is a mirror location (the contents are available in the different locations)'); ?>"></i>
        <?php } ?>
        &nbsp;<?php echo $crumb['role']; ?>
        <?php endif; ?>
    </li>
    <?php endif; ?>
<?php endforeach; ?>