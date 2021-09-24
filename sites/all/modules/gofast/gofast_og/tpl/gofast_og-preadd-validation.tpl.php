<?php $user_a = array(); ?>

<div class="panel panel-default preadd-validation-panel">
    <div class="panel-body">
        <span id="nid" style="display:none;"><?php echo $nid; ?></span>
        <?php echo t('Pre-add users in ', array(), array('context' => 'gofast:taxonomy')); ?> <strong><?php echo $title; ?></strong> :
        <ul>
            <?php foreach ($user_preadd_list as $user_preadd) { ?>
                <li>
                    <span class="user-preadd-span" id="<?php echo $user_preadd->id; ?>">
                        <?php
                        echo $user_preadd->name;
                        $user_a[] = $user_preadd->id;
                        ?>
                    </span>
                </li>
            <?php } ?>
        </ul>
        <div class="preadd-validation-info" style="position: absolute; right: 100px; margin-top: -5px;"><i class='fa fa-clock-o' style='color:orange' aria-hidden='true'></i> <?php echo t('Pending...', array(), array('context' => 'gofast:taxonomy')) ?></div>
        <span id="users_preadd" style="display:none"><?php echo json_encode($user_a); ?></span>
    </div>
</div>
