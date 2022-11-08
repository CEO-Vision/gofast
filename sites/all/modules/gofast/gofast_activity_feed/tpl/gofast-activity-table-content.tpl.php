<!-- Begin: gofast-activity-table-content -->
<?php $user_is_admin = array_intersect([
  'administrator',
  'business administrator',
], $user->roles); ?>
<?php if(empty($items) && !$ajax):?>
    <div class="loader-activity-items" hidden></div>
<?php else: ?>
    <?php foreach($items as $item):?>
        <?php if($item['type'] !== 'blog' && $item['spaces_list'] != "<ul></ul>"):?>
            <tr>
                <td class="pl-0 d-flex" style="position: relative;">
                    <?php if($item['sticky']): ?>
                        <i class="fa fa-thumb-tack" aria-hidden="true" style="position: absolute;left: 40px;color: #337ab7;"></i>
                    <?php endif ?>
                    <?php echo $item['last_modifier']; ?>
                </td>
                <td class="max-w-500px">
                    <?php print theme('gofast_activity_table_content_event', ['item' => $item]); ?>
                </td>
                <td class="">
                        <?php echo $item['spaces_list']; ?>
                </td>
            </tr>
        <?php else: ?>
            <tr>
                <td class="pl-0 d-flex" style="position: relative;">
                    <?php if($item['sticky']): ?>
                        <i class="fa fa-thumb-tack" aria-hidden="true" style="position: absolute;left: 40px;color: #337ab7;"></i>
                    <?php endif ?>
                    <?php echo $item['last_modifier']; ?>
                </td>
                <td class="max-w-500px" colspan="2">
                    <?php  if($user->uid == node_load($item['nid'])->uid || $user_is_admin): ?>
                        <div id="ckeditor_microblogging_edit_<?php echo $item['nid'] ?>" style="display:none;">
                            <textarea id="blog_<?php echo $item['nid'] ?>" name="blog_name_<?php echo $item['nid'] ?>">
                                <?php  echo $item['body']; ?>
                            </textarea>
                            <div id="ckeditor_microblogging_buttons" style="padding:8px;">
                                <a id="blog-update-<?php echo $item['nid']; ?>" class="btn btn-sm btn-success" style="margin-right:10px;"><?php echo t('Valider') ?></a>
                                <a id="blog-cancel-<?php echo $item['nid']; ?>" class="btn btn-sm btn-danger"><?php echo t('Annuler') ?></a>
                            </div>
                        </div>
                    <?php endif ?>
                    <div id="block_blog_body w-100" >
                        <?php  echo $item['body']; ?>
                    </div>
                    <div class="d-flex align-items-center">
                        <div class="mt-2">
                            <span class="text-muted mt-2 font-size-sm"><?php echo $item['last_event']; ?> <span class="text-<?php //echo $colors[0]?> font-weight-bolder"><?php //echo $actions[rand(0,6)]?></span> <?php //echo $date ?></span>
                        </div>
                      <?php if (($user->uid == node_load($item['nid'])->uid) || $user_is_admin) : ?>
                          <div class="gofast-microblogging-actionss mt-2 pl-2"
                               id="gofast-node-actions-microblogging">
                              <div class="gofast-node-actions btn-group dropdown ">
                                  <a class="btn btn-light btn-xs btn-icon mr-2 dropdown-placeholder"
                                     type="button"
                                     id="dropdown-placeholder-<?php echo $item['nid']; ?>"
                                     data-toggle="dropdown">
                                      <span class="fa fa-bars"></span>
                                      <ul class="dropdown-menu gofast-dropdown-menu"
                                          role="menu"
                                          id="dropdownactive-placeholder-<?php echo $item['nid']; ?>">
                                          <li>
                                              <div class="loader-activity-menu-active"></div>
                                          </li>
                                      </ul>
                                  </a>
                              </div>
                          </div>
                      <?php endif ?>
                    </div>
                </td>
            </tr>
        <?php endif ?>
    <?php endforeach?>
<?php endif ?>
<!-- End: gofast-activity-table-content -->
