<?php

/**
 * @file
 * Default theme implementation for displaying a single search result.
 *
 * This template renders a single search result and is collected into
 * search-results.tpl.php. This and the parent template are
 * dependent to one another sharing the markup for definition lists.
 *
 * Available variables:
 * - $url: URL of the result.
 * - $title: Title of the result.
 * - $snippet: A small preview of the result. Does not apply to user searches.
 * - $info: String of all the meta information ready for print. Does not apply
 *   to user searches.
 * - $info_split: Contains same data as $info, split into a keyed array.
 * - $module: The machine-readable name of the module (tab) being searched, such
 *   as "node" or "user".
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 *
 * Default keys within $info_split:
 * - $info_split['module']: The module that implemented the search query.
 * - $info_split['user']: Author of the node linked to users profile. Depends
 *   on permission.
 * - $info_split['date']: Last update of the node. Short formatted.
 * - $info_split['comment']: Number of comments output as "% comments", %
 *   being the count. Depends on comment.module.
 *
 * Other variables:
 * - $classes_array: Array of HTML class attribute values. It is flattened
 *   into a string within the variable $classes.
 * - $title_attributes_array: Array of HTML attributes for the title. It is
 *   flattened into a string within the variable $title_attributes.
 * - $content_attributes_array: Array of HTML attributes for the content. It is
 *   flattened into a string within the variable $content_attributes.
 *
 * Since $info_split is keyed, a direct print of the item is possible.
 * This array does not apply to user searches so it is recommended to check
 * for its existence before printing. The default keys of 'type', 'user' and
 * 'date' always exist for node searches. Modules may provide other data.
 * @code
 *   <?php if (isset($info_split['comment'])): ?>
 *     <span class="info-comment">
 *       <?php print $info_split['comment']; ?>
 *     </span>
 *   <?php endif; ?>
 * @endcode
 *
 * To check for all available data within $info_split, use the code below.
 * @code
 *   <?php print '<pre>'. check_plain(print_r($info_split, 1)) .'</pre>'; ?>
 * @endcode
 *
 * @see template_preprocess()
 * @see template_preprocess_search_result()
 * @see template_process()
 *
 * @ingroup themeable
 */
  $result = $variables['result'];  
  $string_groups = t('Spaces') . ': ';
  $tooltip_preview = t('Preview');
  $formatedGroupes = $result["formatedGroupes"];
?>
<?php if (is_array($result)): ?>
<div class="mt-5">
    <div class="recherche-title d-flex justify-content-between">
        <div class="d-flex align-items-center">
            <label class="checkbox mr-4">
                <input type="checkbox" class="selected_for_basket" onclick="Gofast.search.toggleDisplayButtonForAddToCart(this)" name="Add to cart" />
                <span></span>
            </label>
            <div class="text-dark-75 text-hover-dark font-weight-bolder font-size-lg text-truncate mr-2" style="font-style: normal;"><?php print $title; ?></div>
            <?php if($entity_type == "node" && $bundle != 'task' ): ?>
              <div class="fast-actions" id="gofastFastActions">
                <?php //print $fast_actions; ?>
                <div class="gofast-node-actions dropdown dropdown-inline">
                  <a class="btn btn-light btn-xs btn-icon mr-2 dropdown-placeholder" type="button" id="dropdown-placeholder-<?php echo $entity_id ?>" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
                    <i class="fa fa-bars"></i>
                    <ul class="dropdown-menu gofast-dropdown-menu" role="menu" id="dropdownactive-placeholder-<?php echo $entity_id ?>">
                      <li><div class="loader-activity-menu-active"></div></li>
                    </ul>
                  </a>
                </div>
              </div>
            <?php endif; ?>
            <?php if($entity_type == "node" && $bundle == "alfresco_item"): ?>
                <?php
                  // load node status
                  $query = db_select('node', 'n');
                  $query->fields('n', ['status'])->condition('n.nid', $entity_id);
                  $node_status = $query->execute()->fetchField();
                  $is_trashed = $node_status == 0;
                ?>
                <a
                  class="btn btn-sm btn-hover-light p-0 ctools-use-modal<?= $is_trashed ? " disabled" : "" ?>"
                  id="Preview"
                  title="<?php echo $tooltip_preview ?>"
                  href="/modal/nojs/preview/show/<?= $entity_id ?>"
                >
                  <i class="fa <?= $is_trashed ? 'fa-eye-slash' : 'fa-eye' ?> p-0"></i>
                </a>
            <?php endif; ?>
        </div>
        <div class="recherche-pagination">
              <div class="snippet-pager-wrapper">
                <div class="snippet-pager pager<?php print $entity_id; ?>" >
                  <a href="#" alt="Previous" class="prevPage gofast-button blue-hover" style="border:none;"><<</a>
                    <span class="pager-info"><span class="currentPage"></span> - <span class="totalPages"></span></span>
                  <a href="#" alt="Next" class="nextPage gofast-button blue-hover" style="border:none;">>></a>
                </div>
              </div>
              </div> 
    </div>
    <div class="recherche-detail">

        <div class="recherche-info py-2">
            <?php if ($snippet) echo $snippet; ?>
                      </div>

        <?php
        // we don't need the snippet pager anymore since we now have a preview button
        if ($tags) : ?>
          <div class="recherche-footer d-flex flex-row-reverse justify-content-end">            
              <div class="recherche-tags d-flex flex-wrap py-1 hl-tags">
                <?php print $tags; ?>
              </div>
          </div>
        <?php endif; ?>


    </div>
    <div class="mt-4 d-flex align-items-center">
        <div class="flex-shrink-0 mr-3 ">
          <?php print $author ?>
        </div>
        <div>
            <div class="font-size-xs">
                <?php if (!empty($formatedGroupes)) : ?>
                  <span class="font-weight-bolder mr-1"><?php echo t('Spaces');?>:</span>
                  <?php foreach($formatedGroupes as $group): ?>
                    <a href="/node/<?= $group["nid"] ?>" data-nid="<?php echo $group["nid"]; ?>" data-toggle="search-tooltip" class=""><span class="label label-sm label-warning label-inline font-weight-bold mr-1 text-hover-white bg-hover-dark"><?php echo $group["title"] ?></span></a>
                  <?php endforeach; ?>
                <?php endif; ?>
            </div>
            <div class="font-size-xs">
                <span class="font-weight-bolder mr-1"><?php print t('Creat.', array(), array('context' => 'gofast'));?>:</span>
                <?php print format_date($result[$entity_type]->created); ?> -

                <span class="font-weight-bolder mr-1"><?php print t('Upd.', array(), array('context' => 'gofast'))?>:</span>
                <?php print format_date($result[$entity_type]->changed); ?> - 

                <?php if (isset($info_split['comment'])) : ?>
                  <span class="mr-1"><?php print t($info_split['comment']); ?></span> -
                <?php endif; ?>
                <?php if (isset($popularity) && $bundle !== "task") : ?>
                  <span class="font-weight-bolder mr-1"><?php print t('Popularity'); ?>:</span>
                  <?php echo $popularity; ?> -
                <?php endif; ?>

                <?php if (isset($result['score'])) : ?>
                  <span class="font-weight-bolder mr-1">SCORE:</span>
                  <?php echo $result['score'] ?>
                <?php endif; ?>

            </div>
        </div>
        
       
    </div>
</div>
<div class="separator separator-solid separator-border-1 mt-4"></div>
<script>
  jQuery(document).ready(function() {
    jQuery('.selected_for_basket').each(function() {
      if(jQuery(this).is(':checked')) Gofast.search.toggleDisplayButtonForAddToCart(this);
    });
  });
</script>
<?php endif; ?>