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
<?php
// Workaround 
$parts_uri = arg();
$nid = '';
if ($parts_uri[0] === 'node') {
  $nid = $parts_uri[1];
} else $nid = $parts_uri[3];
global $user;
if ((in_array('administrator member', gofast_og_get_user_final_roles_for_space('node', $nid, $user->uid, FALSE, TRUE), true) || in_array('group contributor', gofast_og_get_user_final_roles_for_space('node', $nid, $user->uid, FALSE, TRUE), true)) && !gofast_og_is_root_space(node_load($nid)) || gofast_og_is_user_private_space(node_load($nid))) : 
?>
<div style="margin-left:2px;float:left;background-color:white;">
  <a href="/node/add/conference?deadline=<?php print $reformated_date ?>&gid=<?php print $nid ?>" style="background-color:white;">+</a>
</div>
<?php endif; ?>