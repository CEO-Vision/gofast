<?php

include_once 'MobileDetect.php';
$detect = new Mobile_Detect;
$desktop = TRUE;
if ($detect->isMobile() || $detect->isTablet()) {
  $desktop = FALSE;
}
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
if ($desktop) {
  $groups = $variables['result'][$entity_type]->{'sm_' . GOFAST_OG_CONTENT_MEMBERSHIP_FIELD};
} else {
  $groups = '';
}
$string_groups = t('Spaces') . ': ';
if (!empty($groups)) {
  if ($desktop) {
    foreach ($groups as $group) {
      $nid = explode(':', $group)[1];
      $string_groups .= ' ' . gofast_get_node_title($nid, array_keys(gofast_og_node_types()));
    }
  } else {
    $string_groups .= implode(' ', $groups);
  }
}

?>
<?php if($desktop) : ?>
  <div class="search-result <?php print $zebra;?>">
<?php else : ?>
  <div class="search-result <?php //print $zebra;?>">
<?php endif; ?>

  <dt class="title">
    <!-- Title + fast-actions buttons -->
    <span class="title">
      <?php print $title; ?>
    </span>
    <?php if ($desktop): ?>
      <?php if($entity_type == "node" && $bundle != 'task' ): ?>
        <span class="fast-actions">
          <?php print $fast_actions; ?>
        </span>
      <?php endif; ?>
      <?php if($entity_type == "node" && $bundle == "alfresco_item"): ?>
        <a class="btn btn-sm" id="Preview" href="" onclick="Drupal.gofast_cmis.showPreviewModal(event , '<?php echo $entity_id; ?>', '#preview_modal_global');">
            <span class="fa fa-image"></span> <?php echo t("Preview", array(), array('context' => 'gofast')); ?>
        </a>
      <?php endif; ?>
    <?php else : ?>
      <?php if ($entity_type == "node") : ?>
        <span class="fast-actions">
          <?php print $fast_actions; ?>
        </span>
      <?php endif; ?>
    <?php endif; ?>
  </dt>

  <dd>

    <?php if ($snippet) echo $snippet; ?>
    <?php if ($snippet || $tags) : ?>
      <div class="snippet-pager-wrapper">
        <div class="snippet-pager pager<?php print $entity_id; ?>">
          <a href="#" alt="Previous" class="prevPage gofast-button blue-hover"></a>
          <span class="pager-info"><span class="currentPage"></span> - <span class="totalPages"></span></span>
          <a href="#" alt="Next" class="nextPage gofast-button blue-hover"></a>
        </div>
        <!-- Highlighted Tags -->
        <?php if ($tags) : ?>
          <div class="hl-tags">
            <?php print $tags; ?>
          </div>
        <?php endif; ?>
        <div style="clear:both;"></div>
      </div>
    <?php endif; ?>

    <?php if ($info_split) : ?>

      <div class="search-info">
        <?php $info_separator = ' - '; ?>

        <span class="search-info-user"><?php print $author ?></span>
        <?php if($desktop) : ?>
          <span class="search-info-date"><?php print t('Creat.', array(), array('context' => 'gofast')).': ' ?><?php print format_date($result[$entity_type]->created); ?></span>
          <span class="search-info-date"><?php print $info_separator .t('Upd.', array(), array('context' => 'gofast')).': ' ?><?php print format_date($result[$entity_type]->changed); ?></span>
        <?php else : ?>
          <span class="search-info-date"><?php print format_date($result[$entity_type]->created); ?></span>
        <?php endif; ?>

        <?php if (isset($info_split['comment'])) : ?>
          <span class="search-info-comment"><?php print $info_separator . t($info_split['comment']); ?></span>
        <?php endif; ?>

        <?php if (isset($string_groups)) : ?>
          <span class="search-info-upload"><?php print $info_separator . ucfirst($string_groups); ?></span>
        <?php endif; ?>

        <?php if (isset($popularity)) : ?>
          <span class="search-info-date"><?php print $info_separator . t('Popularity') . ': ' . $popularity; ?></span>
        <?php endif; ?>

        <?php if (isset($result['score'])) : ?>
          <?php print "<span class='solr-result-score'> - SCORE: {$result['score']} </span>"; ?>
        <?php endif; ?>
      </div>

    <?php endif; ?>

    <?php if (isset($result['fivestar'])) : ?>
      <div class="search-info-fivestar" style="padding-top: 3px; float: left;">
        <?php print $result['fivestar']; ?>
      </div>
    <?php endif; ?>
    <div style="clear:both;"></div>
  </dd>
</div> <!-- /search-result -->
