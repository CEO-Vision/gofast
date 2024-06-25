<?php

/**
 * @file
 * Main view template.
 *
 * Variables available:
 * - $classes_array: An array of classes determined in
 *   template_preprocess_views_view(). Default classes are:
 *     .view
 *     .view-[css_name]
 *     .view-id-[view_name]
 *     .view-display-id-[display_name]
 *     .view-dom-id-[dom_id]
 * - $classes: A string version of $classes_array for use in the class attribute
 * - $css_name: A css-safe version of the view name.
 * - $css_class: The user-specified classes names, if any
 * - $header: The view header
 * - $footer: The view footer
 * - $rows: The results of the view query, if any
 * - $empty: The empty text to display if the view is empty
 * - $pager: The pager next/prev links to display, if any
 * - $exposed: Exposed widget form/info to display
 * - $feed_icon: Feed icon to display, if any
 * - $more: A link to view more, if any.
 *
 * @ingroup views_templates
 */
?>


<div class="card card-custom <?php print $classes; ?>">
  <?php print render($title_prefix); ?>
  <?php if ($title) : ?>
    <?php print $title; ?>
  <?php endif; ?>
  <?php print render($title_suffix); ?>
  <?php if ($header) : ?>
    <div class="view-header">
      <?php print $header; ?>
    </div>
  <?php endif; ?>

  <?php if ($exposed) : ?>
    <div class="view-filters">
      <?php print $exposed; ?>
    </div>
  <?php endif; ?>

  <?php if ($attachment_before) : ?>
    <div class="attachment attachment-before">
      <?php print $attachment_before; ?>
    </div>
  <?php endif; ?>

  <?php if ($rows) : ?>
    <div class="view-content">
      <?php print $rows;
      ?>


    </div>
  <?php elseif ($empty) : ?>
    <div class="view-empty">
      <?php print $empty; ?>
    </div>
  <?php endif; ?>

  <?php if ($pager) : ?>
    <!--begin::Pagination-->
    <div class="d-flex justify-content-between align-items-center flex-wrap">
      <div class="d-flex flex-wrap py-2 mr-3">
        <?php print $pager; ?>

        <?php if ($footer) : ?>
          <span class="text-muted mt-5">
            <?php print $footer; ?>
          </span>
      </div>
    </div>
    <?php if ($feed_icon) : ?>
      <span class="text-muted">
        <?php print t('Export : The export is limited to a maximum 50 000 results', array(), array("context" => "gofast")); ?>
      </span>
      <div class="d-flex flex-wrap py-2 mr-3">
        <span class="text-muted">
          <?php print t('Click for export ', array(), array("context" => "gofast"));
            print "<span id='audit_export_xls_button' style='display:none;'>".$feed_icon."</span>"; 
            print '<button style="margin-right: 10px; margin-left:18px;" onclick="Gofast.download_audit_export()" id="audit_export_btn_group_xlsx" type="button" class="btn btn-default"><span class="fa fa-file-excel-o"></span></button>'?>
        </span>
      </div>
    <?php endif; ?>
  <?php endif; ?>
<?php endif; ?>

<?php if ($attachment_after) : ?>
  <div class="attachment attachment-after">
    <?php print $attachment_after; ?>
  </div>
<?php endif; ?>

<?php if ($more) : ?>
  <?php print $more; ?>
<?php endif; ?>

</div><?php /* class view */ ?>
