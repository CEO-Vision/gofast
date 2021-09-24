
<table border="0" class="table profile-info-table">

  <?php //if ($self || $is_adm): ?>
    <tr>
      <td class="profile-label-cell">
        <span class="profile-label"><?php print t('Userlists'); ?></span>
      </td>
      <td class="profile-userlists">
        <div style="max-height:200px; overflow-y:scroll">
          <ul style="margin-left: 0;padding-left:0;list-style: none;">
            <?php foreach ($userlists as $ulid => $title_userlists) { ?>
              <li>
                <a href="/userlist/<?php echo $ulid ?>"><?php print $title_userlists; ?></a>
              </li>
            <?php } ?>
          </ul>
        </div>
      </td>
    </tr>
  <?php //endif; ?>

  <?php if ($self || $is_adm || !empty($groups)): ?>
    <tr>
      <td class="profile-label-cell">
        <span class="profile-label"><?php print t('Groups'); ?></span>
      </td>
      <td class="profile-groups">
        <div style="max-height:200px; overflow-y:scroll;">
          <?php
          $path = $groups['path'];

          foreach ($path as $gid => $webdav_path) {
            gofast_get_node_space_breadcrumb_async($gid, $account->uid); //Get breadcrumbs for all groups
          }
          ?>
        </div>
      </td>
    </tr>
  <?php endif; ?>

  <?php if ($self || $is_adm || !empty($requested_groups)) : ?>
    <tr>
      <td class="profile-label-cell" style="border-top:0;">
        <span class="profile-label"><?php print t('Requested groups'); ?></span>
      </td>
      <td class="profile-groups_requested" style="border-top:0;"> <?php print $requested_groups; ?> </td>
    </tr>
  <?php endif; ?>

  <?php if ($self || $is_adm || !empty($organisations)) : ?>
    <tr>
      <td class="profile-label-cell">
        <span class="profile-label"><?php print t('Organisations'); ?></span>
      </td>
      <td class="profile-organisations">
        <div style="max-height:200px; overflow-y:scroll">
          <?php
          $path_orga = $organisations['path'];
          foreach ($path_orga as $gid => $webdav_path) {
            gofast_get_node_space_breadcrumb_async($gid, $account->uid); //Get breadcrumbs for all groups
          }
          ?>
        </div>
      </td>
    </tr>
  <?php endif; ?>

  <?php if ($self || $is_adm || !empty($public)) : ?>
    <tr>
      <td class="profile-label-cell">
        <span class="profile-label"><?php print t('Public'); ?></span>
      </td>
      <td class="profile-public">
        <div style="max-height:200px; overflow-y:scroll">
          <?php
          $path_public = $public['path'];
          foreach ($path_public as $gid => $webdav_path) {
            gofast_get_node_space_breadcrumb_async($gid, $account->uid); //Get breadcrumbs for all groups
          }
          ?>
        </div>
      </td>
    </tr>
  <?php endif; ?>

  <?php if ($self || $is_adm || !empty($extranet)) : ?>
    <tr>
      <td class="profile-label-cell">
        <span class="profile-label"><?php print t('Extranet'); ?></span>
      </td>
      <td class="profile-extranet">
        <div style="max-height:200px; overflow-y:scroll">
          <?php
          $path_extranet = $extranet['path'];
          foreach ($path_extranet as $gid => $webdav_path) {
            gofast_get_node_space_breadcrumb_async($gid, $account->uid); //Get breadcrumbs for all groups
          }
          ?>
        </div>
      </td>
    </tr>
  <?php endif; ?>

</table>
