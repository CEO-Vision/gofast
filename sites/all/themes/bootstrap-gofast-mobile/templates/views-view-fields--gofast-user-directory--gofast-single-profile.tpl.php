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
<div id="cadre" class="view-content panel" style="border-color:#777;">
  <table class="gofast-simple-profile" style="margin:inherit; min-height:160px; min-width:270px; text-align: left;">
    <tr>
      <td class="pic-view" style="width:120px;padding:10px;float:left;margin-right:10px;vertical-align:top;">
        <div class="picture img-rounded">          
          <?php print $fields['gofast_views_handler_field_user_picture']->content; ?>
        </div>
        <div class="last-login" style="font-size:10px; margin-bottom: -5px;"><?php print $fields['login']->content; ?></div>
        <div class="points" style="font-size:10px;"><?php print $fields['points']->content; ?> pts</div>
      </td>
      <td class="profile-view" style="padding:5px;width:200px;vertical-align:top;" >
        <div class="name-wrapper" style="color:#777;"><?php print $fields['ldap_user_givenname']->content . ' ' . $fields['ldap_user_sn']->content;?></div>
        <div style="border-bottom: 1px solid #777;"></div>
        <div style="font-weight:bold; font-size: 12px; "><?php print $fields['ldap_user_o']->content; ?></div>
        <div><?php print $fields['ldap_user_title']->content; ?></div>
        <div><?php print $fields['ldap_user_departmentnumber_1']->content; ?></div>
        <div style="margin-left:-5px;"><?php print $fields['gofast_views_handler_field_subscribe_user']->content; ?></div>
        <div style="margin-left:-5px; margin-bottom: -5px;"><?php print $fields['gofast_link_add_relationship_1']->content; ?></div>
        <div style="margin-left:-5px;"><?php print $fields['gofast_views_handler_field_user_quick_actions']->content; ?></div>
      </td>
    </tr>
  </table>
</div>
