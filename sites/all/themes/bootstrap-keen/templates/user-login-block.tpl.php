<?php if((bool)variable_get("gofast_disable_login_form", false) === true){$hidden_class = "d-none";}  ?>
    <div class="d-block">
      <?php if(isset($form['saml_sp_drupal_login_links'])): ?>
        <div class="GofastLoginField">
          <?php print render($form['saml_sp_drupal_login_links']); ?>
        </div>
      <?php endif; ?>
      <div class="GofastLoginField <?php echo $hidden_class; ?>">
        <label class="font-size-h6 font-weight-bolder text-dark"><?php print t('Username'); ?> *</label>
        <span class ="badge badge-pill badge-light-info"
          title="<?= t("Please use your actual username, an email will not work.", array(), array("context" => "gofast: gofast_user")) ?>"
          data-toggle="tooltip"
          data-placement="right"
          style="cursor: initial;"
        ><i class="fas fa-question"></i></span>
        <?php print render($form['name']); ?>
      </div>
      <div class="GofastLoginField">
        <div class="d-flex justify-content-between mt-n5">
          <label class="font-size-h6 font-weight-bolder text-dark pt-5 <?php echo $hidden_class; ?>"><?php print t('Password'); ?> *</label>
          <?php if((bool) variable_get("gofast_disable_password_reset") === FALSE): ?>
            <span class="password-link text-primary font-size-h6 font-weight-bolder text-hover-primary pt-5"><a href="/user/password"><?php echo t('Forgot your password?'); ?></a></span>
          <?php endif; ?>
        </div>
        <span class="<?php echo $hidden_class; ?>"><?php print render($form['pass']); ?></span>
      </div>
        <div class="pb-lg-0 pb-5 font-weight-bolder <?php if((bool)variable_get("gofast_disable_login_form", false) === true){echo "d-none";}else{echo "d-flex";}  ?> justify-content-center">
          <?php echo render($form['actions']); ?>
        </div>
      <div class="d-none"><?php echo drupal_render_children($form); ?></div>
    </div>
<?php if (!gofast_ldap_is_directory_reachable()) : ?>
<script>
  jQuery(document).ready(function() {
    Gofast.toast(Drupal.t("Unable to reach the company directory. If the problem persists, please contact your IT department.", {}, {context: 'gofast:gofast_ldap'}), "warning");
    jQuery("#edit-submit").attr("disabled", true).css("cursor", "not-allowed");
  });
</script>
<?php endif; ?>