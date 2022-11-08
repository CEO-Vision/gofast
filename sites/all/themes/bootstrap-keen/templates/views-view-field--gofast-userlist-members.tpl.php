<?php

/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
?>


<?php
$userlist_members = $row->field_field_userlist_members; 
$int = 0;
?>

<?php foreach($userlist_members as $key=>$member){
        if($int%5 == 0 ){?>
        <tr>  
        <?php } ?>
        <?php $user_id = $member['raw']['value']; ?>
            <td style="width: 19%;display: inline-block;padding-top: 10px;"> 
                <div class="user_member_picture" style="text-align: center;display: block;">
                    <?php print  theme('user_picture', array('account' => user_load($user_id), 'dimensions' => 40)); ?>
                </div>
                <a href="/user/<?php print $user_id ?>" style="text-align: center;display: block;">
                    <?php print gofast_user_display_name(user_load($user_id));?>
                </a>   
            </td>
<?php $int = $int + 1 ; ?>    
<?php }
drupal_add_js(drupal_get_path('theme', 'bootstrap_keen') . '/js/components/userlist.js');
?>