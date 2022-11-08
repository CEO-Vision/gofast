<?php unset($field->options['label']); ?>

<?php $creator_id = isset($row->node_uid) ? $row->node_uid : $row->og_membership_node_1_etid; ?>
<div>
    <?php if (user_load($creator_id)->name == "admin") : ?>
        <?php if ($view->current_display = "gofast_userlist_creator") : ?>
            <div class="user_admin_message" data-toggle="tooltip" data-placement="top" title="" data-original-title="Tooltip on top">
                <?php print t('Userlist created natively by GoFAST'); ?>
            </div>
        <?php endif; ?>
    <?php else : ?>
        <div class="user_member_picture">
            <?php print  theme('user_picture', array('account' => user_load($creator_id), 'dimensions' => 40)); ?>
        </div>
        <a href="/user/<?php print $creator_id ?>"><?php print gofast_user_display_name(user_load($creator_id)); ?></a>
    <?php endif; ?>
</div>

<?php
$view_creator_contributor_table_script = "jQuery(document).ready(function () {
    jQuery('.view-gofast-userlist-creator-contributor table').css('width', '100%');
});";
drupal_add_js($view_creator_contributor_table_script, 'inline');
drupal_add_css(drupal_get_path('theme', 'bootstrap_keen') . '/css/userlist.css');
?>