
<table border="0" class="table profile-info-table">

  <tr>
    <td class="profile-label-cell">
      <span class="profile-label"><?php print t('Groups'); ?></span>
    </td>
    <td class="profile-groups">
      <div style="max-height:200px; overflow-y:scroll;">
        <?php
        $path = $groups['path'];
        if(empty($path)){ ?>
          <span class="text-muted mt-2 font-size-sm">
            <span><?php echo t('No groups locations') ?></span>
          </span>
        <?php }
        foreach ($path as $gid => $webdav_path) {
          print gofast_breadcrumb_display_breadcrumb($gid, ['return' => TRUE, "title_link" => TRUE, "editable" => FALSE, "show_role" => TRUE, "show_role_for_ul" => $ulid]);
        }
        ?>
      </div>
    </td>
  </tr>

  <tr>
    <td class="profile-label-cell">
      <span class="profile-label"><?php print t('Organisations'); ?></span>
    </td>
    <td class="profile-organisations">
      <div style="max-height:200px; overflow-y:scroll">
        <?php
        $path_orga = $organisations['path'];
        if(empty($path_orga)){ ?>
          <span class="text-muted mt-2 font-size-sm">
            <span><?php echo t('No organisations locations') ?></span>
          </span>
        <?php }
        foreach ($path_orga as $gid => $webdav_path) {
          print gofast_breadcrumb_display_breadcrumb($gid, ['return' => TRUE, "title_link" => TRUE, "editable" => FALSE, "show_role" => TRUE, "show_role_for_ul" => $ulid]);
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
      <div style="max-height:200px; overflow-y:scroll">
        <?php
        $path_public = $public['path'];
        if(empty($path_public)){ ?>
          <span class="text-muted mt-2 font-size-sm">
            <span><?php echo t('No public locations') ?></span>
          </span>
        <?php }
        foreach ($path_public as $gid => $webdav_path) {
          print gofast_breadcrumb_display_breadcrumb($gid, ['return' => TRUE, "title_link" => TRUE, "editable" => FALSE, "show_role" => TRUE, "show_role_for_ul" => $ulid]);
        }
        ?>
      </div>
    </td>
  </tr>

  <tr>
    <td class="profile-label-cell">
      <span class="profile-label"><?php print t('External'); ?></span>
    </td>
    <td class="profile-extranet">
      <div style="max-height:200px; overflow-y:scroll">
        <?php
        $path_extranet = $extranet['path'];
        if(empty($path_public)){ ?>
          <span class="text-muted mt-2 font-size-sm">
            <span><?php echo t('No extranet locations') ?></span>
          </span>
        <?php }
        foreach ($path_extranet as $gid => $webdav_path) {
          print gofast_breadcrumb_display_breadcrumb($gid, ['return' => TRUE, "title_link" => TRUE, "editable" => FALSE, "show_role" => TRUE, "show_role_for_ul" => $ulid]);
        }
        ?>
      </div>
    </td>
  </tr>

</table>
