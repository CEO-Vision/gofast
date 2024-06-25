  <span><?php print $output_prepare; ?></span>
  <?php if (isset($edit)) : ?>
    <a class="btn gofast__popover btn-link-success ml-1" role="button" tabindex="0" data-toggle="popover" data-trigger="<?php gofast_essential_is_essential() ? print 'click' : print 'hover' ;?>" title="" data-html="true" data-content="<?php print str_replace('"', '\'', $edit) ?>">
      <i class="fas fa-search icon-nm text-muted"></i>
    </a>
  <?php endif; ?>
