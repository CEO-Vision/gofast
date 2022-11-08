<?php

/**
 * Set context for menu's blocks
 * @param $element
 *  The element in the block.
 * @param $key
 *  The key for the block's element
 * @param $value
 *  The value to assign
 *
 * Without params, it will set context for all blocks
 */
function gofast_menu_set_context($element = FALSE, $key = NULL, $value = NULL)
{
  if (!$element) { //Initialize all values
    $block_context = array(
      'block_menu' => array(
        'private_message' => array(
          'unread_count' => json_decode(gofast_menu_get_unread_messages())->count
        )
      )
    );
  } else { //Set a value for a given association of element and key
    $block_context = array(
      'block_menu' => array(
        $element => array(
          $key => $value
        )
      )
    );
  }

  gofast_set_context($block_context);
}


/**
 * This method adds custom data to loaded blocks based on delta
 * @param type $display_id the delta we load.
 * @return string
 */
function appendCustomData($display_id)
{
  $output = '';
  $path = drupal_get_path('module', 'gofast_views');
  switch ($display_id) {
      //Disabled until this is finished
      /*case 'gofast_notifications':
            $output .= '<script src="/' . $path . '/js/gofast_notifications_popup.js"></script>';
            break;*/
    case 'gofast_inbox':
      $output .= '<a href="/gofast/nojs/messages/new" class="btn btn-info ctools-use-modal btn-sm ctools-modal-center" style=" top: 37px; left: 10px;" title="' . t('Compose') . '"><span class="glyphicon glyphicon-send" style="margin: 1px 8px 0 0;"></span>' . t('Compose', array(), array('context' => 'gofast')) . '</a>';
      $output .= '<script src="/' . $path . '/js/gofast_inbox_popup.js"></script>';
      break;
    case 'bookmarks':
      $output .= '<script src="/' . $path . '/js/gofast_mybookmarks_popup.js"></script>';
      break;
    case 'gofast_aggregator':
      $output .= '<script src="/' . $path . '/js/gofast_headlines_popup.js"></script>';
      break;
  }
  return $output;
}

function gofast_get_block_menu_async() {
    if(gofast_request_is_ajax()) {
        $is_block = $_POST['isBloc'];
        $block_delta = $_POST['isBlockDelta'];
        $view_name = $_POST['viewName'];
        $display_id = $_POST['displayID'] ? $_POST['displayID'] : 'default';
        $subject = $_POST['subject'] ? t($_POST['subject']) : $view_name;
        $path = $_POST['original_path'];
        $query = isset($path['query']) && parse_url($path)['query'] ? '?' . parse_url($path)['query'] : '';
        $_GET['q'] = '/' . $view_name . '/' . $display_id . $query;
        $_REQUEST = $_POST = array();
        
        return gofast_get_block_menu($is_block, $block_delta, $view_name, $display_id, $subject, $path, $query);
    } 
}

/**
 * This method renders the menu blocks from view or block depending the case
 */
function gofast_get_block_menu($is_block = 0, $block_delta = 0, $view_name = "", $display_id = "", $subject = "", $path = "", $query = "")
{
    $view = views_get_view($view_name, true);
    $view_data = array();
    if (!is_null($view)) {
      $preview = $view->preview($display_id);
      $view_data = array(
        'view_dom_id:' . $view->dom_id => array(
          'view_base_path' => $view->display[$display_id]->display_options['path'],
          'view_display_id' => $display_id,
          'view_dom_id' => $view->dom_id,
          'view_name' => $view->name,
          'view_path' => $view->display[$display_id]->display_options['path']
        )
      );
    }


    // This is for a block of a view
    if ($is_block && $view_name && !$block_delta) {
      $block = block_load('views', $view_name . '-' . $display_id);
      //$block = block_load('views', $view_name);
      $blockLoaded = _block_render_blocks(array($block));
      $blockObject = $blockLoaded['views_' . $view_name . '-' . $display_id];
      //$blockObject = $blockLoaded['views_' . $view_name];
      // We add custom data to the blocks depending of delta
      $blockObject->content['#markup'] .= appendCustomData($view_name);
    } // A standard view as a page
    elseif ($view_name && !$block_delta) {
      $blockObject = new stdClass();

      $blockObject->subject = $subject;
      $blockObject->content['#markup'] = $preview;
      // We add custom data to the blocks depending of delta
      $blockObject->content['#markup'] .= appendCustomData($display_id);
    } // A block
    elseif ($is_block && $block_delta) {
      $block = block_load($display_id, $view_name);
      $blockLoaded = _block_render_blocks(array($block));
      $blockObject = $blockLoaded[$display_id . "_" . $view_name];
      // We add custom data to the blocks depending of delta
      $blockObject->content['#markup'] .= appendCustomData($view_name);
    }

    $blockObject->module = 'gofast';
    $blockObject->region = '';
    $blockObject->delta = '';

    $arrayBlock = _block_get_renderable_array(array($blockObject));
    $output = drupal_render($arrayBlock);

    return json_encode(array(
      'output' => $output,
      'view' => $view_data
    ));
  
}



function gofast_menu_rebuild_og_menu($node_type = null)
{
  usurp(1);
  //todo take care of $node_type param

  //first, remove all menu item corresponding to nodes
  $main_menu_links = menu_load_links("main-menu");

  foreach ($main_menu_links as $key => $item) {
    if ($item["router_path"] == "node/%") {
      menu_link_delete($item["mlid"]);
    }
  }


  //get all group's nodes, from parents to children
  module_load_include('inc', 'gofast_og', 'gofast_og.admin');
  $roots = gofast_og_get_root_spaces(FALSE, TRUE);
  foreach ($roots as $gid) {
    $node = node_load($gid);
    if (!isset($node->nid)) {
      continue;
    }
    $root_plid =  gofast_get_mlid_by_uuid('5af2180e-ccd8-4953-8d32-8e2ecd7bb78b');
    if (!isset($root_plid) || $root_plid == FALSE) {
      $root_plid =  gofast_get_mlid_by_title('Spaces');
    }

    $options = array(
      "node_type" => "group",
      "alter" => 1,
      "attributes" => array("title" => "")
    );

    $item = array(
      'link_title' => $node->title,
      'link_path' => 'node/' . $node->nid,
      'menu_name' => 'main-menu',
      'weight' => 0,
      'plid' => $root_plid,
      'has_children' => 1,
      'expanded' => 1,
      'options' => $options
    );
    menu_link_save($item);
  }

  //we add a fake item that represent the private space
  $options = array(
    "node_type" => "group",
    "alter" => 1,
    "attributes" => array("title" => "")
  );

  $item = array(
    'link_title' => t("My Personal Space"),
    'link_path' => 'node/' . array_shift(array_values($roots)),
    'menu_name' => 'main-menu',
    'weight' => 0,
    'plid' => $root_plid,
    'has_children' => 1,
    'expanded' => 1,
    'options' => $options
  );
  menu_link_save($item);
}
