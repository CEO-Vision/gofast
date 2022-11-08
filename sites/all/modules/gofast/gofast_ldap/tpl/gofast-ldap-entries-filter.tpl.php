<div class="card card-custom gutter-b GofastAdminLDAPFilter">
    <!--begin::Body-->
    <div class="card-body">
        <form class="form" id="LDAPAdminEntriesFilterForm">
            <div class="form-group">
                <label class="col-form-label text-right"><?php echo t('Filter', array(), array('context' => 'gofast:gofast_ldap')); ?></label>
                <div class="input-icon">
                    <input type="text" class="form-control" placeholder="<?php echo t('Search...', array(), array('context' => 'gofast:gofast_ldap')); ?>" id="LDAPAdminEntriesText">
                    <span>
                        <i class="fa fa-search text-muted"></i>
                    </span>
                </div>
                <div class="mt-5">
                    <select class="form-control" id="LDAPAdminEntriesSelect" datasize="4">
                        <?php foreach($filters as $key => $f) : ?>
                            <option value="<?php echo $key; ?>"><?php echo $f; ?></option>
                        <?php endforeach; ?>
                    </select>
                </div>
            </div>            
            
            <button type="submit" id="LDAPAdminEntriesSubmit" class="btn btn-light btn-sm"><?php echo t('Search...', array(), array('context' => 'gofast:gofast_ldap')); ?></button>
            <button type="reset" id="LDAPAdminEntriesReset" class="btn btn-light btn-sm"><?php echo t('Reset', array(), array('context' => 'gofast:gofast_ldap')); ?></button>
        </form>
    </div>
    
    <!--end::Body-->
</div>
<div class="card card-custom gutter-b GofastAdminLDAPImport">
    <div class="card-body">
        <span class="" id="gofast_adminLdap_importRowsLength"></span>
        <button type="button" class="btn btn-light font-weight-bold" id="gofast_adminLdap_importRows"><?php echo t('Import Selection', array(), array('context' => 'gofast')); ?></button>  
    </div>
</div>