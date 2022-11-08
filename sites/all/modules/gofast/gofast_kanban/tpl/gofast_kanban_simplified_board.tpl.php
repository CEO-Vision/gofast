<?php
global $user;
//$public_gid = gofast_ajax_file_browser_get_nid_from_href("/Sites/_Public");


$items = array();
foreach ($group_user_gids as $key => $gid) {
  $n = node_load($gid);
  if ($n->type !== 'public') {
    $items[gofast_kanban_get_space_kanban($gid)[0]] = gofast_cmis_space_get_drupal_path($gid); //gofast_breadcrumb_display_breadcrumb($gid, array());
  }
}
natcasesort($items);

//default kanban_id = personal space;
if( ! isset($kanban_id) && ! isset($_GET['parent_space']) ) {
  $private_space_gid = gofast_og_get_user_private_space($user, FALSE);
  $kanban_id = $private_space_gid;
}

$parent_space = isset($_GET['parent_space']) ? $_GET['parent_space'] : $kanban_id;
$card_to_display = isset($_GET['card_id']) ? '/card/'.$_GET['card_id'] : '';

?>


<div class="h-100">
  <!-- BEGIN DROPDOWN SELECT CONTEXT-->
  <select id="select-gid-kanban" class="form-control" required="required" style="margin-bottom:10px;">
    <?php foreach ($items as $k => $v) { ?>
      <option value="<?php print $k; ?>" <?php print $parent_space == $k ? "selected" : '' ?>><?php print $v; ?></option>
    <?php } ?>
  </select>
  <!-- END OF DROPDOWN SELECT CONTEXT-->
  
  
  <div id="gofastKanbanContainer" class="gf_kanban_simplified h-100">
      <?php echo theme('gofast_kanban_og_container', array('node' => node_load($parent_space))); ?>
  </div>
  

</div>
