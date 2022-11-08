<?php if (!gofast_og_is_entity_hide_members_tab($node)) : ?>
  <?php //print $space_members; ?>
  <div class="d-flex h-100 w-100 flex-column">
    <div class="d-flex py-6">
      <div class="input-icon w-100">
        <input type="text" class="form-control " placeholder="<?php print t('Search...', array(), array('context' => 'gofast')) ?>" id="kt_datatable_search_query" />
        <span>
          <i class="flaticon2-search-1 text-muted"></i>
        </span>
      </div>
      <div class="d-flex align-items-center ml-4">
        <label class="mr-3 mb-0 d-none d-md-block">Status:</label>
        <select class="form-control w-200px" id="kt_datatable_search_status">
          <option value=""><?php echo t("All", array(), array("context" => "gofast")); ?></option>
          <option value="1"><?php echo t('Active', array(), array('context' => 'gofast:gofast_directory')) ?></option>
          <option value="0"><?php echo t('Blocked') ?></option>
        </select>
      </div>
      <div class="d-flex align-items-center ml-4">
        <label class="mr-3 mb-0 d-none d-md-block">Type:</label>
        <select class="form-control w-200px" id="kt_datatable_search_type">
          <option value=""><?php echo t("All", array(), array("context" => "gofast")); ?></option>
          <option value="user"><?php echo t("User"); ?></option>
          <option value="userlist"><?php echo t("Userlist", array(), array("context" => "gofast")); ?></option>
        </select>
      </div>
        <?php
            $roles_query = og_roles('node',gofast_get_node_type($node->nid), $node->nid, FALSE, FALSE);
              foreach($roles_query as $rkey => $roles){
                if($roles == GOFAST_OG_ROLE_ADMIN){
                  $admin_rid = $rkey;
                }
                if($roles == GOFAST_OG_ROLE_READ_ONLY){
                  $readonly_rid = $rkey;
                }
                if($roles == GOFAST_OG_ROLE_STANDARD){
                  $contributor_rid = $rkey;
                }
              }   
        ?>
      <div class="d-flex align-items-center ml-4">
        <label class="mr-3 mb-0 d-none d-md-block">Role:</label>
        <select class="form-control w-200px" id="kt_datatable_search_role">
          <option value=""><?php echo t("All", array(), array("context" => "gofast")); ?></option>
          <option value="<?php echo $admin_rid; ?>"><?php echo t("Administrator", array(), array("context" => "gofast:gofast_user")); ?></option>
          <option value="<?php echo $contributor_rid; ?>"><?php echo t("Contributor", array(), array("context" => "gofast:gofast_user")); ?></option>
          <option value="<?php echo $readonly_rid; ?>"><?php echo t("Read Only", array(), array("context" => "gofast:gofast_user")); ?></option>
          <option value="0"><?php echo t("Pending members", array(), array("context" => "gofast:gofast_user")); ?></option>
        </select>
      </div>
    </div>
    <div class="h-100 w-100">
      <div id="gofastSpaceMembersTable" class="gofastSpaceMembersTable datatable datatable-bordered datatable-head-custom" data-id="<?php print $node->nid; ?>"></div>
    </div>
  </div>
<?php endif ?>
