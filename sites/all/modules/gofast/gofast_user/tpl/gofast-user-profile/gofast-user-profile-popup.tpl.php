<div id="gofastUserPopup" class="card card-custom" style="border-color:#777; z-index:1001; left:55px; margin-left: 0.5em;">
    <div class="card-header">
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
    <div class="card-body">
        <span class="picture img-rounded">
                <?php print $user_picture; ?>
        </span>
        <span class="card-text last-login">
            <?php print $user_points; ?>
        </span>
        <span class="card-text points">
            <?php print $user_lastlogin; ?>
        </span>
    </div>
    <div class="card-footer">
        <?php print $user_actions; ?>
    </div>
</div>