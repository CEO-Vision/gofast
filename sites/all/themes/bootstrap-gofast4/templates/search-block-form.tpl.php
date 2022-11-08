<?php

/**
 * @file
 * Displays the search form block.
 *
 * Available variables:
 * - $search_form: The complete search form ready for print.
 * - $search: Associative array of search elements. Can be used to print each
 *   form element separately.
 *
 * Default elements within $search:
 * - $search['search_block_form']: Text input area wrapped in a div.
 * - $search['actions']: Rendered form buttons.
 * - $search['hidden']: Hidden form elements. Used to validate forms when
 *   submitted.
 *
 * Modules can add to the search form, so it is recommended to check for their
 * existence before printing. The default keys will always exist. To check for
 * a module-provided field, use code like this:
 * @code
 *   <?php if (isset($search['extra_field'])): ?>
 *     <div class="extra-field">
 *       <?php print $search['extra_field']; ?>
 *     </div>
 *   <?php endif; ?>
 * @endcode
 *
 * @see template_preprocess_search_block_form()
 *
 * @ingroup templates
 */
?>
<!-- START search-block-form.tpl.php -->
<?php $block = module_invoke('gofast_search', 'block_view', 'gofast_saved_searches_fastaccess');?>

<div class="input-group input-group-sm">
  <div class="input-group-search">
    <?php print $search['search_block_form']; ?>
  </div>
  <div class="input-group-append">
    <?php print $block['content']; ?>
  </div>
</div>
<!-- END search-block-form.tpl.php -->

