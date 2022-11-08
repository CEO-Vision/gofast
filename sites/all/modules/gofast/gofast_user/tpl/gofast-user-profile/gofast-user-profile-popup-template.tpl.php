<div id="gofastUserPopup" class="card card-custom ml-2 border shadow min-w-400px " style="left:45px;">
    <div class="card-header p-5 min-h-60px">
        <div class="card-title">
            <h4 class="card-label">
                <?php print $user_name; ?>
                <small>
                    <?php print $user_orga; ?>
                    <?php print $user_role; ?>
                </small>
            </h4>
        </div>
    </div>
    <div class="card-body d-flex p-5 pb-0">
        <div class="gofastProfilePopupLeft min-w-150px px-4">
            <div class="picture img-rounded">
                <?php print $user_picture; ?>
            </div>
            <span class="card-text last-login d-block mt-2 pt-3">
                <?php print $user_points; ?>
            </span>
            <span class="card-text points d-block pt-1 mt-4" title="<?php print t('Last login', array(), array('context' => 'gofast:user')); ?>">
                <?php print $user_lastlogin; ?>
            </span>
        </div>
        <div class="goFastCardIcons gofastProfilePopupRight">
            <ul class="navi navi-hover navi-link-rounded">
                <?php foreach($user_actions as $actions): ?>
                <li class="navi-item"><?php print $actions; ?></li>
                <?php endforeach; ?>
            </ul>
        </div>
    </div>

</div>
