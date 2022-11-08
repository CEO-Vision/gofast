<div class="card card-custom">
  <div class="card-body">
    <div id="kt_calendar">
    </div>
  </div>
</div>

<?php $events = [];
$view_args = $_GET['view_args'];
$date = explode('/', $view_args)[0];
$nid = explode('/', $view_args)[1];
$prev_date = $view->date_info->prev_date->format('Y-m-d');
$next_date = $view->date_info->next_date->format('YYYY');
foreach ($view->result as $key => $result) {
  $entity = $result->_field_data['nid']['entity'];
  $entity_title = $entity->title;
  $entity_start_date = $entity->field_date[LANGUAGE_NONE][0]['value'];
  $entity_end_date = $entity->field_end_date[LANGUAGE_NONE][0]['value'];
  $entity_body = $entity->field_body[LANGUAGE_NONE][0]['value'];
  $events[$key]['title'] = $entity_title;
  $events[$key]['start'] = $entity_start_date;
  $events[$key]['end'] = $entity_end_date;
  $events[$key]['description'] = $entity_body;
  $events[$key]['className'] = "fc-event-primary";
}

$init_ktcalendar_script = "jQuery(document).ready(function () {
  var events = '" . print json_encode($events) . "';
  Gofast.KTCalendarBasic.init(events);
});";
drupal_add_js($init_ktcalendar_script, 'inline');
?>