<?php
/**
 * @file
 * Template to display a column
 * 
 * - $item: The item to render within a td element.
 */

$id = (isset($item['id'])) ? 'id="' . $item['id'] . '" ' : '';
$date = (isset($item['date'])) ? ' data-date="' . $item['date'] . '" ' : '';
$day = (isset($item['day_of_month'])) ? ' data-day-of-month="' . $item['day_of_month'] . '" ' : '';
$headers = (isset($item['header_id'])) ? ' headers="' . $item['header_id'] . '" ' : '';


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
$timeStamp = strtotime($item['date']);
$reformated_date = format_date($timeStamp, 'custom', 'm/d/Y');

global $user;


// Workaround 
$parts_uri = arg();
$month = strtotime($parts_uri[2].'-01');
$month_first_day = strtotime(date("Y-m-d", $month));
$month_last_day = strtotime(date("Y-m-t", $month));

$is_previous_or_next_month_day = FALSE;
if($month_first_day > $timeStamp || $month_last_day < $timeStamp ){
  $is_previous_or_next_month_day = TRUE;
}

?>

<?php if( ! $is_previous_or_next_month_day) : ?>
<div class="panel panel-default">
  <div class="panel-heading">
    <div <?php print $id ?> class="col-md-12 col-xs-12 calendar-day <?php print $item['class'] ?>" <?php print $date . $headers . $day; ?> >
      <div class="row">
        <div class="col-xs-1 col-md-1 day-nb "><?php print($item['day_of_month'])?></div>
        <div class="col-xs-1 col-md-1 day-of-week hidden-xs "><?php print($item['header_id'])?></div>
        <div class="col-xs-1 col-md-1 day-of-week hidden-sm hidden-md hidden-lg"><?php print( substr($item['header_id'], 0, 3).'.')?></div>
        <div class="col-xs-9 col-md-9 day-events">
          <div>
            <?php print $item['entry'] ?>
          </div>
        </div>
        <div class="col-xs-1 col-md-1 day-add-event">
    <?php  
      $parts_uri = arg();
    $nid = '';
    if ($parts_uri[0] === 'node') {
      $nid = $parts_uri[1];
    } else $nid = $parts_uri[3];
    global $user;
    if(empty($nid)){
      $nid = gofast_og_get_user_private_space($user, FALSE);
    }
      if ((in_array('administrator member', gofast_og_get_user_final_roles_for_space('node', $nid, $user->uid, FALSE, TRUE), true) || in_array('group contributor', gofast_og_get_user_final_roles_for_space('node', $nid, $user->uid, FALSE, TRUE), true)) && !gofast_og_is_root_space(node_load($nid)) || gofast_og_is_user_private_space(node_load($nid))) :
      ?>
          <div style="margin-left:2px;">
            <a href="/node/add/conference?deadline=<?php print $reformated_date ?>&gid=<?php print $nid ?>" class="fa fa-plus"></a>
          </div>
    <?php endif; ?>
        </div>
      </div>
    </div>
  </div>
</div>
<?php endif; ?>