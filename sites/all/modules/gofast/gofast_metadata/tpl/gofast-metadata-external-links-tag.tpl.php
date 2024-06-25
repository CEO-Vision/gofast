<li class="text-left">
  <div class="btn link-badge w-100 d-flex">
    <div class="text-truncate ml-auto">
      <a class="text-truncate" target="_blank" href="<?php echo $link['url'] ?>" title="<?php echo $link['title'] ?>"><?= $link['icon'] ?><span class="external-link-name"><?= $link['title'] ?></span></a>
    </div>
    <a type="button" class="ml-auto pl-1 d-flex" onclick="Gofast.metadata.updateExternalLink(event, '<?= $link['url'] ?>')">
      <i class="fas fa-edit fa-sm pr-0"></i>
    </a>
  </div>
</li>