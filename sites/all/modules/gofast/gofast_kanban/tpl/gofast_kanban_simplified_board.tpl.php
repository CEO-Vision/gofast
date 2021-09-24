<?php
global $user;
//$public_gid = gofast_ajax_file_browser_get_nid_from_href("/Sites/_Public");


$items = array();
foreach ($group_user_gids as $key => $gid) {
  $n = node_load($gid);
  if ($n->type !== 'public') {
    $items[gofast_kanban_get_space_kanban($gid)[0]] = strip_tags(gofast_get_space_breadcrumb_ajax($n, $user->uid, TRUE, NULL, FALSE));
  }
}
natcasesort($items);


$parent_sapce = isset($_GET['parent_sapce']) ? $_GET['parent_sapce'] : $kanban_id;
$card_to_display = isset($_GET['card_id']) ? '/card/'.$_GET['card_id'] : '';
?>


<div class="content ">
  <!-- BEGIN DROPDOWN SELECT CONTEXT-->
  <select id="select-gid-kanban" class="form-control" required="required" style="margin-bottom:10px;">
    <?php foreach ($items as $k => $v) { ?>
      <option value="<?php print $k; ?>" <?php print $parent_sapce == $k ? "selected" : '' ?>><?php print $v; ?></option>
    <?php } ?>
  </select>
  <!-- END OF DROPDOWN SELECT CONTEXT-->
  <!-- BEGIN IFRAME KANBAN-->
  <iframe src="/kanban/<?php print $parent_sapce . $card_to_display ?>" class="gf_kanban_simplfied" id="gf_kanban" style="width:100%;height:550px;border:none;"></iframe>
  <script type="text/javascript">
    (function($, Gofast, Drupal) {
      'use strict';
      Gofast.reloadKanbanFromPollingExternal = function(kanbanId) {
        $('#gf_kanban')[0].contentWindow.Gofast.reloadKanbanFromPolling(kanbanId);
      }
    })(jQuery, Gofast, Drupal);
  </script>
  <!-- END IFRAME KANBAN-->
</div>
