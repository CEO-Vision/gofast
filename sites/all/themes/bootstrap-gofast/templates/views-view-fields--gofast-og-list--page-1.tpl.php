<?php

/**
 * @file
 * Default simple view template to all the fields as a row.
 *
 * - $view: The view in use.
 * - $fields: an array of $field objects. Each one contains:
 *   - $field->content: The output of the field.
 *   - $field->raw: The raw data for the field, if it exists. This is NOT output safe.
 *   - $field->class: The safe class id to use.
 *   - $field->handler: The Views field handler object controlling this field. Do not use
 *     var_export to dump this object, as it can't handle the recursion.
 *   - $field->inline: Whether or not the field should be inline.
 *   - $field->inline_html: either div or span based on the above flag.
 *   - $field->wrapper_prefix: A complete wrapper containing the inline_html to use.
 *   - $field->wrapper_suffix: The closing tag for the wrapper.
 *   - $field->separator: an optional separator that may appear before a field.
 *   - $field->label: The wrap label text to use.
 *   - $field->label_html: The full HTML of the label to use including
 *     configured element type.
 * - $row: The raw result object from the query, with all data it fetched.
 *
 * @ingroup views_templates
 */
?>
<style>
  #cadre{border:solid 1px #c0c0c0;background-color:#FFFFFF;text-decoration:none;color:#636363;font-size:11px;line-height:20px;padding-left:5px;padding-right:15px;padding-top:5px;padding-bottom:3px; overflow: auto; margin: 5px 5px 5px 5px; max-width: 385px; }
  .profile-image img { width:18px; height: 20px;}
</style>
<div id="cadre" class="view-content">
  <table style="margin: inherit; min-height: 160px; min-width: 100%; max-height: 146px; margin-top: -12px;">
    <tr>
      <td><div style="margin-top: 16px;"></div></td>
    </tr>
    <tr class="profile-view" style="padding:5px;">
      <td>
        <span style="border:none; font-size: 14px; font-weight: bold; float: left;"><?php print $fields['title']->content; ?></span>
        <span style="float:right;"><?php print $fields['type']->content; ?></span>
      </td>
    </tr>
    <tr>
      <td>
        <div style="font-weight:bold; font-size: 13px; "><?php print $fields['field_description']->content; ?></div>
      </td>
    </tr>
    <tr>
      <td>
        <div>Contributions: <?php //print $fields['title_1']->content; ?></div>
      </td>
    </tr>
    <tr>
      <td>
        <div>Membres: <?php print $fields['uid']->content; ?></div>
      </td>
    </tr>
    <tr>
      <td class="quick-actions">
        <?php if(isset($fields['picture']->content)){ ?>
          <span style="margin-left: 300px;">Admin:&nbsp;</span><span class="profile-image img-rounded" style="float:right;"><?php print $fields['picture']->content; ?></span>
        <?php } else { ?>
          <span style="margin-left: 300px;">&nbsp;</span>
        <?php } ?>
      </td>
    </tr>
  </table>
    
</div>