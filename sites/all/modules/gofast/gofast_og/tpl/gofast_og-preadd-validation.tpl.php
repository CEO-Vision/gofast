<?php $user_a = array(); ?>

<div class="panel panel-default preadd-validation-panel">
    <div class="panel-body">
    <div style='margin-bottom:10px;'><b><?php echo t("Message", array(), array("context" => "gofast")). "</b> :    <span id='message'>".$message; ?></span> <span id='role_id'> <?php echo $rid; ?></span></div>
        <span id="nid" style="display:none;"><?php echo $nid; ?></span>
        <span id="type" style="display:none;"><?php echo $type; ?></span>
        <?php echo t('Pre-add members in ', array(), array('context' => 'gofast:taxonomy')); ?> <strong><?php echo $title; ?></strong> :
        <ul>
            <?php foreach ($user_preadd_list as $user_preadd) { ?>
                <?php
                    $entity_id = "";
                    if($user_preadd->type == "userlist"){
                        $user_a[] = array(
                            "id" => $user_preadd->ulvalue,
                            "type" => "userlist"
                        );
                        $entity_id = $user_preadd->ulvalue;
                    } else if($user_preadd->type == "user"){
                        $user_a[] = array(
                            "id" => $user_preadd->value,
                            "type" => "user"
                        );
                        $entity_id = $user_preadd->value;
                    }
                ?>
                <li>
                    <span class="user-preadd-span" id="<?php echo $entity_id; ?>" data-type="<?= $user_preadd->type ?>">
                        <?= $user_preadd->name;?>
                    </span>
                </li>
            <?php } ?>
        </ul>       
        <div class="preadd-validation-info" style="position: absolute; right: 100px; margin-top: -5px;"><i class='fa fa-clock-o' style='color:orange' aria-hidden='true'></i> <?php echo t('Pending...', array(), array('context' => 'gofast:taxonomy')) ?></div>
        <span id="users_preadd" style="display:none"><?php echo json_encode($user_a); ?></span>
    </div>
</div>
