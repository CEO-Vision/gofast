<div class="card card-custom gutter-b">
    <!--begin::Body-->
    <div class="card-body">
        <?php if (($self || $is_adm) && !empty($groups)): ?>
            <?php print $og_button_join; ?>
        <?php endif?>
        <?php if ((gofast_user_is_adm() || user_access('gofast administer user')) && (!empty($account_blocked) && !$account_left)) : ?>
            <div class="alert alert-custom alert-outline-2x alert-outline-warning fade show mb-5" role="alert">
                <div class="alert-icon"><i class="flaticon-warning"></i></div>
                <div class="alert-text"><?= str_replace("{Click here}", "<a class='ctools-use-modal text-warning font-weight-bolder' href='/modal/nojs/user/$account->uid/unblock'>" . t("Click here") . "</a>", t("This user is blocked. {Click here} to unblock the account", array(), array("context" => "gofast:gofast_user"))) ?></div>
                <div class="alert-close">
                    <button type="button" class="close" data-dismiss="alert" aria-label="Close">
                        <span aria-hidden="true"><i class="ki ki-close"></i></span>
                    </button>
                </div>
            </div>
        <?php endif; ?>
        <div id='gf_user_groups' data-profileUid="<?php echo $account->uid ?>">
            <!-- Placeholder : Load groups templates ! -->
            <div>
                <?php print theme('gofast_user_profile_groups'); ?>
            </div>
        </div>

    </div>
    <!--end::Body-->
</div>
