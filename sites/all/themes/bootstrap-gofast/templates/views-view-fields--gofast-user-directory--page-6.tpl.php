<?php

/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
?>
<div id="cadre" class="view-content" style="border-color:#777;">
  <table class="gofast-simple-profile" style="margin:inherit; min-height:160px; min-width:270px;">
    <tr>
      <td class="pic-view" style="width:70px;padding:10px;float:left;margin-right:10px;vertical-align:top;">
        <div class="picture img-rounded">          
          <?php print $fields['gofast_views_handler_field_user_picture']->content; ?>
        </div>
        <div class="last-login" style="font-size:12px;"><?php print $fields['login']->content; ?></div>
      </td>
      <td style="float:right;padding:5px;width:200px;vertical-align:top;" >
        <div class="name-wrapper" style="color:#777;"><?php print $fields['ldap_user_givenname']->content . ' ' . $fields['ldap_user_sn']->content;?></div>
        <div style="font-weight:bold; font-size: 13px; "><?php print $fields['ldap_user_o']->content; ?></div>
        <div><?php print $fields['ldap_user_title']->content; ?></div>
        <div><?php print $fields['ldap_user_departmentnumber_1']->content; ?></div>
      </td>
    </tr>
    <tr>
      <td class="profile-view" style="padding:5px;width:200px;vertical-align:top;">
        <div style="margin-left:-5px;">
          <?php global $user;
            if (gofast_user_is_adm($user)){ ?>
              <a class="btn btn-xs ctools-modal-center ctools-use-modal-processed">
                      <button 
                      style="margin: 0; padding: 0; background: none; border:0;" 
                      onmouseout='this.style.textDecoration="none"' onmouseover='this.style.textDecoration="underline"' 
                      type="button" id="btn-unblock" 
                      onclick="Gofast.Unblock_user(<?php print_r($fields['uid']->content); ?>)">
                        <div class="fa fa fa-unlock"></div>  <?php print t('Unblock this user.',array(),array('context' => 'gofast'));?>
                      </button>
              </a>
          <?php }?>
        </div>
      </td>
    </tr>
  </table>  
</div>
