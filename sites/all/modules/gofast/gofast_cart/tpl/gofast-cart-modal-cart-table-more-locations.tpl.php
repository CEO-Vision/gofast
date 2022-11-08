  <?php if (isset($popover_content)) : ?>
    <a class="btn gofast__popover btn-link-success " role="button" tabindex="0" data-toggle="popover" data-trigger="click" title="" data-html="true" data-content="<?php print '<ul class=\'navi navi-hover navi-link-rounded\'>' . $popover_content . '</ul>'; ?>">
      <i class="fas fa-info-circle icon-nm text-success"></i>
      <?php print $button_text; ?>
    </a>
  <?php endif; ?>