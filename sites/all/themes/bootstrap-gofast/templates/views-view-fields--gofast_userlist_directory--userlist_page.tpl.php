<?php

/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
$ulid = $fields['field_userlist_ulid']->content;

$visible = gofast_userlist_is_visible($ulid);

if($visible){
?>
    <div id="cadre" class="view-content" style="height:200px; position:relative; border-color:#777;">
        <div style="font-weight: bold; padding:5px;position:absolute;right: 0;"><?php echo t('Members count: ',array(),array('context'=>'gofast:gofast_userlist')) . count(gofast_userlist_get_members($ulid)); ?></div>
        <div style="font-weight: bold; padding:5px;position:absolute;right: 0;padding-top: 25px;"><?php echo t('Administrators count: ',array(),array('context'=>'gofast:gofast_userlist')) . (count(gofast_userlist_get_administrators($ulid)) + 1); ?></div>
        <div class="name-wrapper" style="font-size:18px !important;padding:5px;width:200px;vertical-align:top;"><?php print $fields['title']->content?></div>
        <div style="font-weight: bold; padding:5px;"><?php echo t('Description',array(),array('context'=>'gofast:gofast_userlist'));?></div>
        <div style="width: 150px;  border: 0; height: 1px; background-image: -webkit-linear-gradient(left, #f0f0f0, #8c8b8b, #f0f0f0); background-image: -moz-linear-gradient(left, #f0f0f0, #8c8b8b, #f0f0f0); background-image: -ms-linear-gradient(left, #f0f0f0, #8c8b8b, #f0f0f0); background-image: -o-linear-gradient(left, #f0f0f0, #8c8b8b, #f0f0f0); "></div>
        <div id ="userlist-description-id" style="padding:8px;max-height: 100px;"><?php print $fields['field_description']->content?></div>
        <div style="font-weight: bold;padding:5px;position: absolute; bottom: 0;"><?php print t('Created by ',array(),array('context'=>'gofast:gofast_userlist')) . theme('user_picture', array('account' => user_load($fields['uid']->raw), 'dimensions' => 20));?> </div>
    </div>
<?php
}else{
?>
    <div id="cadre" class="view-content" style="height:200px; position:relative; border-color:#777;">
        <div style="font-weight: bold; padding:5px;position:absolute;right: 0;"><?php echo t('Members count: ',array(),array('context'=>'gofast:gofast_userlist'))?> N/A</div>
        <div style="font-weight: bold; padding:5px;position:absolute;right: 0;padding-top: 25px;"><?php echo t('Administrators count: ',array(),array('context'=>'gofast:gofast_userlist')); ?> N/A</div>
        <div class="name-wrapper" style="font-size:18px !important;padding:5px;width:200px;vertical-align:top;"><?php echo t('Hidden list',array(),array('context:gofast_userlist'=>'gofast')); ?></div>
        <div style="font-weight: bold; padding:5px;"><?php echo t('Description',array(),array('context'=>'gofast:gofast_userlist'));?></div>
        <div style="width: 150px;  border: 0; height: 1px; background-image: -webkit-linear-gradient(left, #f0f0f0, #8c8b8b, #f0f0f0); background-image: -moz-linear-gradient(left, #f0f0f0, #8c8b8b, #f0f0f0); background-image: -ms-linear-gradient(left, #f0f0f0, #8c8b8b, #f0f0f0); background-image: -o-linear-gradient(left, #f0f0f0, #8c8b8b, #f0f0f0); "></div>
        <div id ="userlist-description-id" style="padding:8px;max-height: 100px;"><?php echo t("You can't view this userlist because you are not member of it.",array(),array('context:gofast_userlist'=>'gofast')); ?></div>
        <div style="font-weight: bold;padding:5px;position: absolute; bottom: 0;"><?php print t('Created by ',array(),array('context'=>'gofast:gofast_userlist'));?> N/A</div>
    </div>
<?php
}