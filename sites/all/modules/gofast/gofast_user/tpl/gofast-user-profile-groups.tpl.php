<table border="0" class="table profile-info-table">

  <tr>
    <td class="profile-label-cell">
      <span class="profile-label"><?php print t('Userlists'); ?></span>
    </td>
    <td class="profile-userlists">
      <div style="min-height: 30px; max-height:200px; overflow-y:scroll">
        <ul style="margin-left: 0;padding-left:0;list-style: none;">
          <div class="spinner spinner-track spinner-primary mr-15 mt-4"></div>
        </ul>
      </div>
    </td>
  </tr>

  <tr>
    <td class="profile-label-cell">
      <span class="profile-label"><?php print t('Groups'); ?></span>
    </td>
    <td class="profile-groups">
      <div style="min-height: 30px; max-height:200px; overflow-y:scroll">
        <div class="spinner spinner-track spinner-primary mr-15 mt-4"></div>
      </div>
    </td>
  </tr>

  <tr>
    <td class="profile-label-cell" style="border-top:0;">
      <span class="profile-label"><?php print t('Requested groups'); ?></span>
    </td>

    <td class="profile-groups_requested" style="border-top:0;">
      <div class="spinner spinner-track spinner-primary mr-15 mt-4"></div>
    </td>
  </tr>

  <tr>
    <td class="profile-label-cell">
      <span class="profile-label"><?php print t('Organisations'); ?></span>
    </td>
    <td class="profile-organisations">
      <div style="min-height: 30px; max-height:200px; overflow-y:scroll">
        <div class="spinner spinner-track spinner-primary mr-15 mt-4"></div>
        <?php
        $path_orga = $organisations['path'];
        foreach ($path_orga as $gid => $webdav_path) {
          print gofast_breadcrumb_display_breadcrumb($gid, ['return' => TRUE, "title_link" => TRUE, "editable" => FALSE, "show_role" => TRUE, "show_role_for" => $account->uid]);
        }
        ?>
      </div>
    </td>
  </tr>

  <tr>
    <td class="profile-label-cell">
      <span class="profile-label"><?php print t('Public'); ?></span>
    </td>
    <td class="profile-public">
      <div class="spinner spinner-track spinner-primary mr-15 mt-4"></div>
      <div style="min-height: 30px; max-height:200px; overflow-y:scroll">
        <?php
        $path_public = $public['path'];
        foreach ($path_public as $gid => $webdav_path) {
          print gofast_breadcrumb_display_breadcrumb($gid, ['return' => TRUE, "title_link" => TRUE, "editable" => FALSE, "show_role" => TRUE, "show_role_for" => $account->uid]);
        }
        ?>
      </div>
    </td>
  </tr>

  <tr>
    <td class="profile-label-cell">
      <span class="profile-label"><?php print t('Extranet'); ?></span>
    </td>
    <td class="profile-extranet">
      <div style="min-height: 30px; max-height:200px; overflow-y:scroll">
        <div class="spinner spinner-track spinner-primary mr-15 mt-4"></div>
        <?php
        $path_extranet = $extranet['path'];
        foreach ($path_extranet as $gid => $webdav_path) {
          print gofast_breadcrumb_display_breadcrumb($gid, ['return' => TRUE, "title_link" => TRUE, "editable" => FALSE, "show_role" => TRUE, "show_role_for" => $account->uid]);
        }
        ?>
      </div>
    </td>
  </tr>

</table>
