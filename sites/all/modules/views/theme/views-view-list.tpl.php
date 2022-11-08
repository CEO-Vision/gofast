<?php

/**
 * @file
 * Default simple view template to display a list of rows.
 *
 * - $title : The title of this group of rows.  May be empty.
 * - $options['type'] will either be ul or ol.
 *
 * @ingroup views_templates
 */
?>
<?php if(FALSE): ?>
<?php print $wrapper_prefix; ?>
  <?php if (!empty($title)) : ?>
    <h3><?php print $title; ?></h3>
  <?php endif; ?>
  <?php print $list_type_prefix; ?>
    <?php foreach ($rows as $id => $row): ?>
      <li class="<?php print $classes_array[$id]; ?>"><?php print $row; ?></li>
    <?php endforeach; ?>
    <?php print $list_type_suffix; ?>
    <?php print $wrapper_suffix; ?>
<?php endif; ?>
    

  
<ul class="navi GofastList mb-4 text-truncate">
  <?php foreach ($rows as $id => $row): ?>
    <li class="navi-item">
      <div class="navi-link py-1">
        <span class="navi-bullet">
            <i class="bullet bullet-dot"></i>
        </span>
        <?php print $row; ?>
      </div>
    </li>
  <?php endforeach; ?>
</ul>