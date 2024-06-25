<?php
foreach ($items as $item) {
  if ($item['type'] !== 'blog' && $item['spaces_list'] != "<ul></ul>") {
?>
    <tr class="d-flex flex-row w-75">
        <td class="pl-0 d-flex" style="position: relative;">
          <?php
          if ($item['sticky']) {
            echo '<i class="fa fa-thumb-tack" aria-hidden="true" style="position: absolute;left: 40px;color: #337ab7;"></i>';
          }
          echo $item['last_modifier'];
          ?>
        </td>
        <td style="max-width: 75vw">
          <?php print theme('gofast_activity_table_content_event', ['item' => $item]); ?>
        </td>
    </tr>
  <?php
  } else {
  ?>
    <tr class="d-flex flex-row w-75">
      <td>
        <?php
        if ($item['sticky']) {
          echo '<i class="fa fa-thumb-tack" aria-hidden="true" style="position: absolute;left: 25px;color: #337ab7;"></i>';
        }
        echo $item['last_modifier'];
        ?>
      </td>
      <td colspan="5" class="gofast-activity-blog-field-mobil">

        <div id="block_blog_body">
          <?php echo $item['body']; ?>

          <?php if ($user->uid == node_load($item['nid'])->uid) { ?>
          <div class="gofast-microblogging-actions">
            <div class="gofast-node-actions btn-group" id="gofast-node-actions-microblogging">
              <a class="btn btn-default btn-xs dropdown-toggle dropdown-placeholder" type="button" id="dropdown-placeholder-<?php echo $item['nid']; ?>" data-toggle="dropdown">
                <span class="fa fa-bars" style="color:#777;"></span>
                <ul class="dropdown-menu gofast-dropdown-menu" role="menu" id="dropdownactive-placeholder-<?php echo $item['nid']; ?>" style="left:-190px;">
                  <li>
                    <div class="loader-activity-menu-active"></div>
                  </li>
                </ul>
              </a>
            </div>
          </div>
          <div id="ckeditor_microblogging_edit_<?php echo $item['nid'] ?>" style="display:none;">
            <textarea id="blog_<?php echo $item['nid'] ?>" name="blog_name_<?php echo $item['nid'] ?>">
		          <?php echo $item['body']; ?>
		        </textarea>
            <div style="padding:8px;">
              <a class="btn btn-sm btn-success" onclick="Gofast.microBlogging.update('<?php echo $item['nid'] ?>')" style="margin-right:10px;"><?php echo t('Valider') ?></a>
              <a class="btn btn-sm btn-danger" onclick="Gofast.microBlogging.closeCke('<?php echo $item['nid'] ?>')"><?php echo t('Annuler') ?></a>
            </div>
          </div>
        <?php } ?>
        </div>
        <br />
        <div style="text-align: left; clear: both;">
          <?php echo $item['last_event']; ?>
        </div>
      </td>
    </tr>
  <?php
  }
}
if (empty($items) && !$ajax) {
  ?>
  <div class="loader-activity-items"></div>
<?php
}
