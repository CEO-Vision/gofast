<?php
/**
 * @file
 * Features integration hooks.
 */

/**
 * Features export callback.
 */
function uuid_features_menu_features_export($data, &$export, $module_name) {
  // Default hooks are provided by the feature module so we need to add
  // it as a dependency.
  $export['dependencies']['features'] = 'features';
  $export['dependencies']['menu'] = 'menu';
  $export['dependencies']['uuid'] = 'uuid';
  $export['dependencies']['uuid_features_menu'] = 'uuid_features_menu';

  // Collect a link to module map.
  $pipe = array();
  $map = features_get_default_map('uuid_features_menu', 'uuid');
  foreach ($data as $identifier) {
    if ($link = uuid_features_menu_link_load($identifier)) {
      // If this link is provided by a different module, add it as a dependency.
      if (isset($map[$identifier]) && $map[$identifier] != $module_name) {
        $export['dependencies'][$map[$identifier]] = $map[$identifier];
      }
      else {
        $export['features']['uuid_features_menu'][$identifier] = $identifier;
      }

      // If this module has a parent add that too.
      if ($link['plid'] != 0 && $parent = menu_link_load($link['plid'])) {
        $pipe['uuid_features_menu'][] = uuid_features_menu_link_uuid($parent);
      }

      // For now, exclude a variety of common menus from automatic export.
      // They may still be explicitly included in a Feature if the builder
      // chooses to do so.
      if (!in_array($link['menu_name'], array(
          'features',
          'primary-links',
          'secondary-links',
          'navigation',
          'admin',
          'devel',
        ))) {
        $pipe['menu_custom'][] = $link['menu_name'];
      }
    }
  }
  return $pipe;
}

/**
 * Build a list of menu links to export.
 */
function uuid_features_menu_features_export_options() {
  // Generate UUIDs for the menu links.
  uuid_generate();

  // Get a list of all the menu links.
  return _uuid_features_menu_get_links();
}

/**
 * Implements hook_features_export_render().
 */
function uuid_features_menu_features_export_render($module, $data) {
  $code = array();
  $code[] = '  $menu_uuid_links = array();';
  $code[] = '';

  $translatables = array();
  foreach ($data as $identifier) {
    if ($link = uuid_features_menu_link_load($identifier)) {
      // Replace plid with a parent uuid.
      if (!empty($link['plid']) && $parent = menu_link_load($link['plid'])) {
        $link['parent_uuid'] = $parent['uuid'];
      }
      unset($link['plid']);
      unset($link['mlid']);

      // If the menu path links to something that has a UUID use that instead.
      if ($uuid_path = uuid_features_menu_encode_path($link['link_path'])) {
        $link['uuid_path'] = $uuid_path;
        unset($link['link_path']);
      }

      $code[] = "  // Exported menu link: {$identifier}";
      $code[] = "  \$menu_uuid_links['{$identifier}'] = " . features_var_export($link, '  ') . ";";
      $translatables[] = $link['link_title'];
    }
  }
  if (!empty($translatables)) {
    $code[] = '';
    $code[] = features_translatables_export($translatables, '  ');
  }

  $code[] = '  return $menu_uuid_links;';
  $code = implode("\n", $code);
  return array('menu_default_uuid_features_menu' => $code);
}

/**
 * Implements hook_features_export_revert().
 */
function uuid_features_menu_features_revert($module) {
  uuid_features_menu_features_rebuild($module);
}

/**
 * Implements hook_features_export_rebuild().
 */
function uuid_features_menu_features_rebuild($module) {
  if ($menu_links = features_get_default('uuid_features_menu', $module)) {
    uuid_features_menu_features_rebuild_ordered($menu_links);
  }
}

/**
 * Generate a depth tree of all menu links.
 */
function uuid_features_menu_features_rebuild_ordered($menu_links, $reset = FALSE) {
  static $ordered;
  static $all_links;
  if (!isset($ordered) || $reset) {
    $ordered = array();
    $unordered = features_get_default('uuid_features_menu');

    // Order all links by depth.
    if ($unordered) {
      do {
        $current = count($unordered);
        foreach ($unordered as $key => $link) {
          $identifier = uuid_features_menu_link_uuid($link);
          $parent = '';
          if (!empty($link['parent_uuid'])) {
            $parent = $link['parent_uuid'];
          }
          if (empty($parent)) {
            $ordered[$identifier] = 0;
            $all_links[$identifier] = $link;
            unset($unordered[$key]);
          }
          elseif (isset($ordered[$parent])) {
            $ordered[$identifier] = $ordered[$parent] + 1;
            $all_links[$identifier] = $link;
            unset($unordered[$key]);
          }
        }
      } while (count($unordered) < $current);
    }
    asort($ordered);
  }

  // Ensure any default menu items that do not exist are created.
  foreach (array_keys($ordered) as $identifier) {
    $link = $all_links[$identifier];
    $existing = uuid_features_menu_link_load($identifier);
    if (!$existing || in_array($link, $menu_links)) {
      // Retrieve the mlid if this is an existing item.
      if ($existing) {
        $link['mlid'] = $existing['mlid'];
      }
      // Retrieve the plid for a parent link.
      if (!empty($link['parent_uuid']) && $parent = uuid_features_menu_link_load($link['parent_uuid'])) {
        $link['plid'] = $parent['mlid'];
      }
      else {
        $link['plid'] = 0;
      }
      // Convert uuid paths to node paths.
      if (!empty($link['uuid_path'])) {
        if (!$link['link_path'] = uuid_features_menu_resolve_path($link['uuid_path'])) {
          drupal_set_message("Couldn't restore {$link['uuid']} as the uuid it points to does not exist on this site.");
          continue;
        }
        unset($link['uuid_path']);
      }
      $mlid = menu_link_save($link);
      if (!$existing) {
        uuid_features_menu_link_set_uuid($mlid, $identifier);
      }
    }
  }
}
