<?php

/**
 * @file
 * Default theme implementation to present all user profile data.
 *
 * This template is used when viewing a registered member's profile page,
 * e.g., example.com/user/123. 123 being the users ID.
 *
 * Use render($user_profile) to print all profile items, or print a subset
 * such as render($user_profile['user_picture']). Always call
 * render($user_profile) at the end in order to print all remaining items. If
 * the item is a category, it will contain all its profile items. By default,
 * $user_profile['summary'] is provided, which contains data on the user's
 * history. Other data can be included by modules. $user_profile['user_picture']
 * is available for showing the account picture.
 *
 * Available variables:
 *   - $user_profile: An array of profile items. Use render() to print them.
 *   - Field variables: for each field instance attached to the user a
 *     corresponding variable is defined; e.g., $account->field_example has a
 *     variable $field_example defined. When needing to access a field's raw
 *     values, developers/themers are strongly encouraged to use these
 *     variables. Otherwise they will have to explicitly specify the desired
 *     field language, e.g. $account->field_example['en'], thus overriding any
 *     language negotiation rule that was previously applied.
 *
 * @see user-profile-category.tpl.php
 *   Where the html is handled for the group.
 * @see user-profile-item.tpl.php
 *   Where the html is handled for each item in the group.
 * @see template_preprocess_user_profile()
 *
 * @ingroup themeable
 */
?>

<div class="profile"<?php print $attributes; ?>>
  <?php //print render($user_profile); ?>
</div>
<?php //  print_r('<pre>'); print_r($account); print_r('</pre>'); ?>


<div  class="user-profile-menu" style="display:inline-flex; float: right; padding: 10px 10px 0 0;">
   <?php if ($self || isset($profile_account_settings)) : ?>
    <div class="profile-settings">
        <div class="profile-account-settings">
          <?php print $profile_account_settings; ?>
        </div><!--
         <div class="profile-uprofile-settings">
          <?php //print $profile_uprofile_settings; ?>
        </div> -->
    </div>
  <?php endif; ?>
  <?php if (!empty($contextual_actions)): ?>
    <?php print render($contextual_actions); ?>
  <?php endif; ?>
</div>

<div id="gofast-profile-view" class="profile-panel<?php if ($self) print ' self'; if ($is_adm) print ' is_adm' ?>" uid="<?php print $account->uid ?>" >
    
  <div class="profile-row profile-row-1" id="gofast-profile-info-box">
      
      
    <div class="profile-box-left">
      <div class="profile-avatar">
        <?php print $profile_picture; ?>
      </div>
    </div>
      
    <div class="profile-box-right">
        
      <div class="profile-primary-info">
        <div class="profile-name_firstname">
          <span id="profile-firstname"><span id="editable-ldap_user_givenname gofast-tooltip" class="edit"><?php print $ldap['ldap_user_givenname']['value']; ?></span></span>
          <span id="profile-lastname"><span id="editable-ldap_user_sn gofast-tooltip" class="edit"><?php print $ldap['ldap_user_sn']['value']; ?></span></span>
          <?php if (!empty($account_blocked)){ print '<p style="color:#B82010;">(' . $account_blocked . ')</p>';} ?>
          <br />
          <span id="profile-displayname">
            <?php print $ldap['ldap_user_displayname']['value']; ?>
          </span>
          <!--<span class="profile-pseudo" style="float:right;">
            <?php //print $profile_pseudo; ?>
          </span> -->
        </div>

        <div class="profile-title_orga">
          <?php if ($a = $self || $is_adm || !empty($ldap['ldap_user_title']['value'])): ?>
            <span id="profile-title"><span id="editable-ldap_user_title"><?php print $ldap['ldap_user_title']['value']; ?></span></span>
          <?php endif; ?>
          <?php if ($b = $self || $is_adm || !empty($ldap['ldap_user_o']['value'])): ?>
            <span id="profile-department"> 
            <span> <?php print $a && $b ? ' @ ' : ''; ?> </span>
            <span id="editable-ldap_user_o" class="edit"><?php print $ldap['ldap_user_o']['value']; ?></span></span>
          <?php endif; ?>
        </div>
        <div class="profile-organisation-unit">
          <?php print gofast_ldap_ou_title($account); ?>
        </div>
      </div>
        
        
      <div class="profile-secondary-info">
        <div class="profile-roles-score">
          <?php print "$profile_roles ($profile_score)"; ?>
        </div>
        <div class="profile-phone-info">
          <?php print $profile_primary_phone; ?>
        </div>
        <div class="profile-mail editable" id="profile-mail">
          <span id="editable-mail" class="edit"><?php print $account->mail; ?></span>
        </div>
        
<!--
        <div class="profile-status-box">
          <?php //print $profile_status_box; ?>
        </div> -->      
          
        <!--  
        <div class="profile-status">
          <?php //print $profile_status; ?>
        </div>
        -->
      </div>

    </div> <!-- profile-box-right -->

  </div> <!-- profile-row row-1 -->
   
  
  <div class="profile-row profile-row-4">
    <?php 
    if (($self || $is_adm) && !empty($groups)) {
      print $og_button_join;
    }
    ?>
    <table border="0" class="table profile-info-table">
        
      <?php if ($self || $is_adm || !empty($userlists)): ?>
        <tr> 
          <td class="profile-label-cell">
            <span class="profile-label"><?php print t('Userlists'); ?></span>
          </td>
          <td class="profile-userlists">
            <div style="max-height:200px; overflow-y:scroll">
                <ul style="margin-left: 0;padding-left:0;list-style: none;">
                    <?php
                    $userlists = array();
                    $userlists_ids = gofast_userlist_get_userlists_by_user($account);
                    foreach($userlists_ids as $key=>$ulid){
                        $entity_userlist = entity_load_single('userlist',$key);
                        $nid = $entity_userlist->nid;
                        $node = node_load($nid);
                        $title = $node->title;
                        if(!empty($title)){
                            $userlists[$key]=$title;
                        }
                    }
                    asort($userlists);
                    foreach($userlists as $ulid=>$title_userlists){ ?>
                    <li>
                        <a href="/userlist/<?php echo $ulid ?>"><?php print $title_userlists; ?></a>
                    </li>
                    <?php } ?>
                </ul>
            </div>
          </td>
        </tr>
      <?php endif; ?>
        
      <?php if ($self || $is_adm || !empty($groups)): ?>
        <tr> 
          <td class="profile-label-cell">
            <span class="profile-label"><?php print t('Groups'); ?></span>
          </td>
          <td class="profile-groups">
            <div style="max-height:200px; overflow-y:scroll">
                <?php
                $groups_user = gofast_og_get_spaces_by_user($account);
                foreach($groups_user as $gid){
                    if(node_load($gid)->type == 'group' && node_access('view',node_load($gid))){
                        $path[$gid] = gofast_cmis_space_get_drupal_path($gid);
                    }
                }
                asort($path);
                foreach($path as $gid=>$webdav_path){
                        gofast_get_node_space_breadcrumb_async($gid,$account->uid); //Get breadcrumbs for all groups
                }
                ?>
            </div>
          </td>
        </tr>
      <?php endif; ?>
        
      <?php if ($self || $is_adm || !empty($requested_groups)) : ?>
        <tr> 
          <td class="profile-label-cell" style="border-top:0;">
            <span class="profile-label"><?php print t('Requested groups'); ?></span>
          </td>
          <td class="profile-groups_requested" style="border-top:0;"> <?php print $requested_groups; ?> </td>
        </tr>
      <?php endif; ?>
        
      <?php if ($self || $is_adm || !empty($organisations)) : ?>
        <tr> 
          <td class="profile-label-cell">
            <span class="profile-label"><?php print t('Organisations'); ?></span>
          </td>
          <td class="profile-organisations">
            <div style="max-height:200px; overflow-y:scroll">
                <?php
                foreach($groups_user as $gid){
                    if(node_load($gid)->type == 'organisation' && node_access('view',node_load($gid))){
                        $path_orga[$gid] = gofast_cmis_space_get_drupal_path($gid);
                    }
                }
                asort($path_orga);
                foreach($path_orga as $gid=>$webdav_path){ 
                        gofast_get_node_space_breadcrumb_async($gid,$account->uid); //Get breadcrumbs for all groups
                }
                ?>
            </div>           
          </td>
        </tr>
      <?php endif; ?>
        
      <?php if ($self || $is_adm || !empty($public)) : ?>
        <tr> 
          <td class="profile-label-cell">
            <span class="profile-label"><?php print t('Public'); ?></span>
          </td>
          <td class="profile-public">
            <div style="max-height:200px; overflow-y:scroll">
                <?php
                foreach($groups_user as $gid){
                    if(node_load($gid)->type == 'public' && node_access('view',node_load($gid))){
                        $path_public[$gid] = gofast_cmis_space_get_drupal_path($gid);
                    }
                }
                asort($path_public);
                foreach($path_public as $gid=>$webdav_path){ 
                        gofast_get_node_space_breadcrumb_async($gid,$account->uid); //Get breadcrumbs for all groups
                }
                ?>
            </div>             
          </td>
        </tr>
      <?php endif; ?>
        
      <?php if ($self || $is_adm || !empty($extranet)) : ?>
        <tr> 
          <td class="profile-label-cell">
            <span class="profile-label"><?php print t('Extranet'); ?></span>
          </td>
          <td class="profile-extranet">
            <div style="max-height:200px; overflow-y:scroll">
                <?php
                foreach($groups_user as $gid){
                    if(node_load($gid)->type == 'extranet' && node_access('view',node_load($gid))){
                        $path_extranet[$gid] = gofast_cmis_space_get_drupal_path($gid);
                    }
                }
                asort($path_extranet);
                foreach($path_extranet as $gid=>$webdav_path){ 
                        gofast_get_node_space_breadcrumb_async($gid,$account->uid); //Get breadcrumbs for all groups
                }
                ?>
            </div>            
          </td>
        </tr>
      <?php endif; ?>
      
    </table>
  </div><!-- profile-row row-2 -->
  
  
  <div class="profile-row profile-row-4">
    <table border="0" class="table profile-info-table">
      <?php if($self || !empty($profile_skills)): ?>
        <tr>
          <td class="profile-label-cell">
            <span class="profile-label"><?php print t('Manager'); ?></span>
          </td>
          <td class="profile-manager edit-cell">
            <span id="editable-ldap_user_manager" class="edit edit-select click-to-submit"> <?php print $manager_default; ?> </span>
          </td>
        <tr>
          <td class="profile-label-cell">
            <span class="profile-label"><?php print t('Skills'); ?></span>
          </td>
          <td class="profile-skills edit-cell">
              <?php print $taxonomy['skills']; ?>
          </td>
        </tr>
      <?php endif; ?>
      <?php if($self || !empty($profile_interests)): ?>
        <tr> 
          <td class="profile-label-cell">
            <span class="profile-label"><?php print t('Interests'); ?></span>
          </td>
          <td class="profile-interests edit-cell">
              <?php print $taxonomy['interests']; ?>
          </td>
        </tr>
      <?php endif; ?>
      <?php if($self || !empty($profile_passions)): ?>
        <tr> 
          <td class="profile-label-cell">
            <span class="profile-label"><?php print t('Passions'); ?></span>
          </td>
          <td class="profile-passions edit-cell">
              <?php print $taxonomy['passions']; ?>
          </td>
        </tr>
      <?php endif; ?>
      <?php if($self || !empty($profile_birthdate)): ?>
        <tr> 
          <td class="profile-label-cell">
            <span class="profile-label"><?php print t('Birthdate'); ?></span>
          </td>
          <td class="profile-birthdate edit-cell" id="profile-birthdate">
            <?php print $profile_birthdate; ?>
          </td>
        </tr>
      <?php endif; ?>      
      <tr></tr>
    </table>
  </div><!-- profile-row row-3 -->
  
</div> <!-- profile-panel -->

<script type="text/javascript">
ua = navigator.userAgent;
/* MSIE used to detect old browsers and Trident used to newer ones*/
var is_ie = ua.indexOf("MSIE ") > -1 || ua.indexOf("Trident/") > -1;
if(is_ie != true){
    if(screen.width > 700){
	jQuery('.profile-groups div').mCustomScrollbar({theme: 'dark-thin'});
	jQuery('.profile-organisations div').mCustomScrollbar({theme: 'dark-thin'});
	jQuery('.profile-public div').mCustomScrollbar({theme: 'dark-thin'});
	jQuery('.profile-extranet div').mCustomScrollbar({theme: 'dark-thin'});
	jQuery('.profile-userlists div').mCustomScrollbar({theme: 'dark-thin'});
	jQuery('.mCustomScrollbar').css('overflow-y','hidden');
    }
}
</script>