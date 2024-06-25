  <div class="d-flex h-100 w-100 flex-column">
    <div class="d-flex py-6">
      <div class="input-icon w-100">
        <input type="text" class="form-control " placeholder="<?php echo t('Search...', array(), array('context' => 'gofast')); ?>" id="kt_datatable_search_query" />
        <span>
          <i class="flaticon2-search-1 text-muted"></i>
        </span>
      </div>
      <div class="d-flex align-items-center ml-4">
        <label class="mr-3 mb-0 d-none d-md-block"><?php echo t('Role', array(), array('context' => 'gofast:gofast_userlist')) ?></label>
        <select class="form-control w-200px" id="kt_datatable_search_role">
          <option value="all"><?php echo t('All'); ?></option>
          <option value="admins"><?php echo t('Administrators', array(), array('context' => 'gofast:gofast_userlist')); ?></option>
          <option value="members"><?php echo t('Members', array(), array('context' => 'gofast:gofast_userlist')); ?></option>
          <option value="pending"><?php echo t('Pending members', array(), array('context' => 'gofast:gofast_userlist')); ?></option>
        </select>
      </div>
    </div>
    <div class="h-100 w-100">
      <div id="gofastUserlistMembersTable" class="datatable datatable-bordered datatable-head-custom" data-id="<?php print $node->nid; ?>"></div>
    </div>
  </div>
