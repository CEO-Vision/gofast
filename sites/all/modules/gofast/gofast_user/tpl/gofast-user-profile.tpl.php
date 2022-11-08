<?php //

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
 *   - $usrs are strongly encouraged to use these
 *     variables. Otherwise they will have to explicitly specify the desired
 *     field language, e.g. $account->field_example['en'], thus overriding any
 *     language negotiation rule thaer_profile: An array of profile items. Use render() to print them.
 *   - Field variables: for each field instance attached to the user a
 *     corresponding variable is defined; e.g., $account->field_example has a
 *     variable $field_example defined. When needing to access a field's raw
 *     values, developers/themet was previously applied.
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

<?php //echo json_encode($userDetails, JSON_PRETTY_PRINT); ?>

<?php //print theme('gofast_user_profile', array('account' => $account)); ?>

<?php if (FALSE): ?>

  <div class="user-profile-menu" style="display:inline-flex; float: right; padding: 10px 10px 0 0;">
    <?php if ($self || isset($profile_account_settings)) : ?>
      <div class="profile-settings">
        <div class="profile-account-settings">
          <?php print $profile_account_settings; ?>
        </div>
        <!--
          <div class="profile-uprofile-settings">
            <?php //print $profile_uprofile_settings;
            ?>
          </div> -->
      </div>
    <?php endif; ?>
    <?php if (!empty($contextual_actions)) : ?>
      <?php print render($contextual_actions); ?>
    <?php endif; ?>
  </div>

  <div id="gofast-profile-view" class="profile-panel<?php if ($self) print ' self';
                                                    if ($is_adm) print ' is_adm' ?>" uid="<?php print $account->uid ?>">

    <div class="profile-row profile-row-1">


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
            <?php if (!empty($account_blocked)) {
              print '<p style="color:#B82010;">(' . $account_blocked . ')</p>';
            } ?>
            <br />
            <span id="profile-displayname">
              <?php print $ldap['ldap_user_displayname']['value']; ?>
            </span>
            <!--<span class="profile-pseudo" style="float:right;">
              <?php //print $profile_pseudo;
              ?>
            </span> -->
          </div>

          <div class="profile-title_orga">
            <?php if ($a = $self || $is_adm || !empty($ldap['ldap_user_title']['value'])) : ?>
              <span id="profile-title"><span id="editable-ldap_user_title"><?php print $ldap['ldap_user_title']['value']; ?></span></span>
            <?php endif; ?>
            <?php if ($b = $self || $is_adm || !empty($ldap['ldap_user_o']['value'])) : ?>
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
            <?php //print $profile_status_box;
            ?>
          </div> -->

          <!--
          <div class="profile-status">
            <?php //print $profile_status;
            ?>
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

      <div id='gf_user_groups' data-profileUid="<?php echo $account->uid ?>">
        <!-- Placeholder : Load groups templates ! -->
        <div class="loader-blog"></div>
        <?php
          $script = "var wait_gofast_profile_spaces = setInterval(function() {
            if (typeof Gofast === 'object' && typeof Gofast.load_user_profile_spaces === 'function' && jQuery('#gf_user_groups').length === 1) {
              Gofast.load_user_profile_spaces();
              clearInterval(wait_gofast_profile_spaces);
            }
          }, 500);";

          drupal_add_js($script, "inline");
        ?>
      </div>

    </div><!-- profile-row row-2 -->


    <div class="profile-row profile-row-4">
      <table border="0" class="table profile-info-table">
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
        <tr>
          <td class="profile-label-cell">
            <span class="profile-label"><?php print t('Interests'); ?></span>
          </td>
          <td class="profile-interests edit-cell">
            <?php print $taxonomy['interests']; ?>
          </td>
        </tr>
        <tr>
          <td class="profile-label-cell">
            <span class="profile-label"><?php print t('Passions'); ?></span>
          </td>
          <td class="profile-passions edit-cell">
            <?php if ($self) {
              print $taxonomy['passions'];
            } else {
              print $taxonomy['hobbies'];
            } ?>
          </td>
        </tr>
        <?php if ($self || !empty($profile_birthdate)) : ?>
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

  <!-- Load "My team" block -->
  <?php
    $script = "var wait_gofast_profile_teams = setInterval(function() {
      if (typeof Gofast === 'object' && typeof Gofast.load_user_profile_teams === 'function' && jQuery('#gf_user_groups').length === 1) {
        Gofast.load_user_profile_teams();
        clearInterval(wait_gofast_profile_teams);
      }
    }, 500);";
    drupal_add_js($script, "inline");
  ?>

<?php else: ?>

  <div class="GofastUserProfile mainContent">
    <div class="GofastUserProfile__info">
      <?php echo theme("gofast_user_profile_personal_info", [
        "profile_picture" => $profile_picture,
        "ldap" => $ldap,
        "account_blocked" => $account_blocked,
        "is_adm" => $is_adm,
        "self" => $self,
        "account" => $account,
        "profile_roles" => $profile_roles,
        "profile_score" => $profile_score,
        "profile_primary_phone" => $profile_primary_phone,
        "profile_birthdate" => $profile_birthdate,
        "manager_default" => $manager_default,
        "taxonomy" => $taxonomy,
        "profile_account_settings" => $profile_account_settings,
        "contextual_actions" => $contextual_actions
  
      ]); ?>
    </div>
    <div class="GofastUserProfile__detail">
      <?php echo theme("gofast_user_profile_detail_info", ["account" => $account, "account_blocked" => $account_blocked, "account_left" => $account_left]); ?>
    </div>
  </div>

<?php endif ?>
