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

<script>
    jQuery('.view-gofast-userlist-creator-contributor table').css('width', '100%');
</script>

<style>

    .view-gofast-userlist-creator-contributor>div>table>tbody>tr {
        display: inline-block;
        margin-bottom: 25px;
    }

    .view-gofast-userlist-creator-contributor>div>table>tbody>tr>td {
        width: 160.5px !important;
        display: inline-block;
        text-align: center;
    }

    @media (max-width: 1400px) {
        .view-gofast-userlist-creator-contributor>div>table>tbody>tr>td {
            width: 130.5px !important;
        }
    }

    .view-display-id-gofast_userlist_creator .user_admin_message{
        font-size: 16px;
        padding: 10px;
        font-weight: 500;
        text-align: start;
    }
    .view-display-id-gofast_userlist_creator>div>table>tbody>tr, .view-display-id-gofast_userlist_creator>div>table>tbody>tr>td{
        width: 100% !important;
    }
</style>
