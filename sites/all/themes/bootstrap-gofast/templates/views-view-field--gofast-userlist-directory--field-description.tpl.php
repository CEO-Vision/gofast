<?php

/**
 * @file
 * This template is used to print a single field in a view.
 *
 * It is not actually used in default Views, as this is registered as a theme
 * function which has better performance. For single overrides, the template is
 * perfectly okay.
 *
 * Variables available:
 * - $view: The view object
 * - $field: The field handler object that can process the input
 * - $row: The raw SQL result that can be used
 * - $output: The processed output that will normally be used.
 *
 * When fetching output from the $row, this construct should be used:
 * $data = $row->{$field->field_alias}
 *
 * The above will guarantee that you'll always get the correct data,
 * regardless of any changes in the aliasing that might happen if
 * the view is modified.
 */
$ulid = $row->_field_data['nid']['entity']->field_userlist_ulid[LANGUAGE_NONE][0]['value'];
$visible = gofast_userlist_is_visible($ulid);
?>


<?php if ($visible) : ?>
  <?php print $output; ?>
<?php else : ?>
  <span><em><?php echo t("You can't view this userlist because you are not member of it.", array(), array('context:gofast_userlist' => 'gofast')); ?><em></span>
<?php endif; ?>
