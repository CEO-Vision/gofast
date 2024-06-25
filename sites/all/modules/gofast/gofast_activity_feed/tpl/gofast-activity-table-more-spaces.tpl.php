  <?php if (isset($popover_content)) : ?>
    <a class="btn gofast__popover btn-link-success text-muted " role="button" tabindex="0" data-toggle="popover" data-trigger="focus" title="" data-html="true" data-content="<?php print '<ul class=\'navi navi-hover navi-link-rounded\'>' . $popover_content . '</ul>'; ?>">
      <i class="fas fa-search icon-nm text-muted"></i>
      <?php print $button_text; ?>
    </a>
  <?php endif; ?>