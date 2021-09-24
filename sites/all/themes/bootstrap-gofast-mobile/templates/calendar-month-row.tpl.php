<?php
/**
 * @file
 * Template to display a row
 * 
 * - $inner: The rendered string of the row's contents.
 */
$attrs = ($class) ? 'class="' . $class . ' calendar-week row"': 'calendar-week row';
$attrs .= ($iehint > 0) ? ' iehint="' . $iehint . '"' : '';
?>
  <?php if ($attrs != ''):?>
  <div <?php print $attrs?>>
  <?php else:?>
  <div>
  <?php endif;?>
      <?php print $inner ?>
  </div>
