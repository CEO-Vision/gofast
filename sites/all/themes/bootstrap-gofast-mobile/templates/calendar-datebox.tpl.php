<?php
/**
 * @file 
 * Template to display the date box in a calendar.
 *
 * - $view: The view.
 * - $granularity: The type of calendar this box is in -- year, month, day, or week.
 * - $mini: Whether or not this is a mini calendar.
 * - $class: The class for this box -- mini-on, mini-off, or day.
 * - $day:  The day of the month.
 * - $date: The current date, in the form YYYY-MM-DD.
 * - $link: A formatted link to the calendar day view for this day.
 * - $url:  The url to the calendar day view for this day.
 * - $selected: Whether or not this day has any items.
 * - $items: An array of items for this day.
 */
  $timeStamp = strtotime($date); 
  $reformated_date = format_date($timeStamp, 'custom', 'm/d/Y');
  global $user;
?>
<div class="<?php print $granularity ?> <?php print $class; ?>"> <?php print !empty($selected) ? $link : $day; ?> </div>
<?php if (is_numeric(arg(1)) && user_access('administer spaces', $user) && !gofast_og_is_root_space(node_load(arg(1)))) : ?>
<div style="margin-left:2px;float:left;background-color:white;">
  <a href="/node/add/conference?deadline=<?php print $reformated_date ?>&gid=<?php print arg(1) ?>" style="background-color:white;">+</a>
</div>
<?php endif; ?>