<?php

?>


<style>
  @import url(http://fonts.googleapis.com/css?family=Roboto);

  body {
    font-family: Roboto, Arial, sans-serif;
  }

  .help_notes td {
    text-align: center !important;
    padding-left: 10px;
    font-size: 14px;
    color: #333;
    padding-top: 10px;
    padding-right: 10px;
    padding-bottom: 10px;
  }

  p {
    padding-left: 10px;
    font-size: 14px;
    color: #333;
    padding-top: 10px;
    padding-right: 10px;
    padding-bottom: 10px;
  }
</style>

<!--[if mso]><!-- -->
<style>
</style>
<!--<![endif]-->

<!-- Title div. Title of the body -->
<div>
  <center>
    <h3>
      <?php print t("Hello ", array(), $l) . $full_name; ?>
    </h3>
  </center>
</div>

<!-- Subject Panel -->
<table width="98%" cellpadding="0" cellspacing="0" style=" border: 1px solid; border-color: #ddd; margin-left: 10px; margin-right: 10px; border-radius: 4px;  -webkit-box-shadow: 0 1px 1px rgba(0,0,0,.05); box-shadow: 0 1px 1px rgba(0,0,0,.05); margin-bottom: 10px;">
  <tr>
    <td>
      <table width="100%" cellpadding="0" cellspacing="0" bgcolor="#f5f5f5" style=" background-color: #f5f5f5; border-bottom: 1px solid;  border-color: #ddd;">
        <tr>
          <td style="padding-left:15px;">
            <h4 style="margin-top: 10px; margin-bottom: 10px; color: #31708f;"><?php print t('Information', array(), $l); ?></h4>
          </td>
        </tr>
      </table>
    </td>
  </tr>
  <tr>
    <td>
      <table width="100%" cellpadding="0" cellspacing="0">
        <tr>
          <td style=" color: #333; padding-left:10px; padding-top:10px; font-size: 14px; padding-right: 10px; padding-bottom: 10px;">
            <span style="display:inline-block;"><?php print $author_pic; ?></span>
            <?php print "   " . $author_name; ?>
            <?php print t('has created you an account on', array(), $l) . " "; ?>
            <a href="<?php print $url ?>" style="  font-size:15px;   font-weight:normal;   overflow:auto;   margin-left: 5px;   font-weight: bold; text-decoration: underline; text-decoration-color: #0074A6;  color: #0074A6" class="link"> <?php print $site_name; ?> </a>
          </td>
        </tr>
      </table>
    </td>
  </tr>
</table>
<!-- Table spacer -->
<table>
  <div></div>
</table>
<table>
  <div></div>
</table>


<!-- Information Panel -->
<table width="98%" cellpadding="0" cellspacing="0" style="border: 1px solid; border-color: #ddd;   margin-left: 10px; margin-right: 10px; border-radius: 4px;  -webkit-box-shadow: 0 1px 1px rgba(0,0,0,.05); box-shadow: 0 1px 1px rgba(0,0,0,.05); margin-bottom: 10px;">
  <tr>
    <td>
      <table width="100%" cellpadding="0" cellspacing="0" bgcolor="#f5f5f5" style=" background-color: #f5f5f5; border-bottom: 1px solid;  border-color: #ddd;">
        <tr>
          <td style="padding-left:15px;">
            <h4 style="margin-top: 10px; margin-bottom: 10px; color: #31708f;"><?php print t('Your new account', array(), $l); ?></h4>
          </td>
        </tr>
      </table>
    </td>
  </tr>
  <tr>
    <td>
      <table width="100%" cellpadding="0" cellspacing="0">
        <tr>
          <td style="padding-left:10px; font-size: 14px; color: #333; padding-top:10px; padding-right: 10px; padding-bottom: 10px; display: inline-block;">
            <div>
              <?php print t('Here are your connection informations: ', array(), $l); ?>
            </div> <br />
            <div>
              <?php print "<b>" . t("Login", array(), $l) . " : </b>";
              print $user_login; ?>
            </div>
            <?php if(!empty($user_password)){ ?>
              <div>
                <?php print "<b>" . t("Password", array(), $l) . " : </b>";
                print $user_password; ?>
              </div>
            <?php } ?>
          </td>
        </tr>
      </table>
    </td>
  </tr>
</table>
<!-- Table spacer -->
<table>
  <div></div>
</table>
<table>
  <div></div>
</table>

<!-- Information Panel -->
<table width="98%" cellpadding="0" cellspacing="0" style="border: 1px solid; border-color: #ddd;   margin-left: 10px; margin-right: 10px; border-radius: 4px;  -webkit-box-shadow: 0 1px 1px rgba(0,0,0,.05); box-shadow: 0 1px 1px rgba(0,0,0,.05); margin-bottom: 10px;">
  <tr>
    <td>
      <table width="100%" cellpadding="0" cellspacing="0" bgcolor="#f5f5f5" style=" background-color: #f5f5f5; border-bottom: 1px solid;  border-color: #ddd;">
        <tr>
          <td style="padding-left:15px;">
            <h4 style="margin-top: 10px; margin-bottom: 10px; color: #31708f;"><?php print t('Message', array(), $l); ?></h4>
          </td>
        </tr>
      </table>
    </td>
  </tr>
  <tr>
    <td>
      <table width="100%" cellpadding="0" cellspacing="0">
        <tr>
          <td style="padding-left:10px; font-size: 14px; color: #333; padding-top:10px; padding-right: 10px; padding-bottom: 10px; display: inline-block;">
            <div>
              <?php print $author_message ?>
            </div> <br />
          </td>
        </tr>
      </table>
    </td>
  </tr>
</table>
<!-- Table spacer -->
<table>
  <div></div>
</table>
<table>
  <div></div>
</table>

<!-- Note Panel -->
<table width="98%" cellpadding="0" cellspacing="0" style="border: 1px solid; border-color: #bce8f1;   margin-left: 10px; margin-right: 10px; border-radius: 4px;  -webkit-box-shadow: 0 1px 1px rgba(0,0,0,.05); box-shadow: 0 1px 1px rgba(0,0,0,.05); margin-bottom: 10px;">
  <tr>
    <td>
      <table width="100%" cellpadding="0" cellspacing="0" bgcolor="#bce8f1" style=" background-color: #bce8f1; border-bottom: 1px solid;  border-color: #bce8f1;">
        <tr>
          <td style="padding-left:15px;">
            <h4 style="margin-top: 10px; margin-bottom: 10px; color: #31708f;"><?php print t('Last step', array(), $l); ?></h4>
          </td>
        </tr>
      </table>
    </td>
  </tr>
  <tr>
    <td>
      <table width="100%" cellpadding="0" cellspacing="0">
        <tr>
          <td style="padding-left:10px; font-size: 14px; color: #333; padding-top:10px; padding-right: 10px; padding-bottom: 10px; display: inline-block;">
            <div>
              <?php print t("Please change your account password immediately using ", array(), $l); ?>
              <a href="<?php print $url_change_password ?>" style="font-size:15px; text-decoration: underline; text-decoration-color: #0074A6; font-weight:normal;   overflow:auto;   margin-left: 5px;   font-weight: bold;   color: #0074A6" class="link"><?php print t("this link", array(), $l); ?> </a>
            </div>
          </td>
        </tr>
      </table>
    </td>
  </tr>
</table>
<!-- Table spacer -->
<table>
  <div></div>
</table>
<table>
  <div></div>
</table>

<!-- Information Panel -->
<table width="98%" cellpadding="0" cellspacing="0" style="border: 1px solid; border-color: #ddd;   margin-left: 10px; margin-right: 10px; border-radius: 4px;  -webkit-box-shadow: 0 1px 1px rgba(0,0,0,.05); box-shadow: 0 1px 1px rgba(0,0,0,.05); margin-bottom: 10px;">
  <tr>
    <td>
      <table width="100%" cellpadding="0" cellspacing="0" bgcolor="#f5f5f5" style=" background-color: #f5f5f5; border-bottom: 1px solid;  border-color: #ddd;">
        <tr>
          <td style="padding-left:15px;">
            <h4 style="margin-top: 10px; margin-bottom: 10px; color: #31708f;"><?php print t('Notes', array(), $l) ?></h4>
          </td>
        </tr>
      </table>
    </td>
  </tr>
  <tr>
    <td>
      <table class='help_notes' cellspacing="15" style="border-spacing: 15px; border-collapse: inherit; margin:auto; margin-top:30px; margin-bottom:30px;">
        <p>
          <?php print t('To help you get started, here is a list of important things to know about the online documentation of our platform.', array(), $l); ?>
        </p>
        <tr>
          <td style="text-align: center;"><?php print t('Profile', array(), $l); ?></td>
          <td style="text-align: center;"><?php print t('Collaborative spaces', array(), $l); ?></td>
          <td style="text-align: center;"><?php print t('Content creation', array(), $l); ?></td>
          <td style="text-align: center;"><?php print t('Subscriptions', array(), $l); ?></td>
          <td style="text-align: center;"><?php print t('Simplified Version', array(), $l); ?></td>
        </tr>
        <tr>
          <td style="text-align: center;"> <a href="https://gofast-docs.readthedocs.io/fr/latest/docs-gofast-users/doc-gofast-guide-utilisateurs.html#mon-profil"><img src="<?php global $base_url;
                                                                                                                                                                            print $base_url ?>/sites/default/files/user.png" /></a></td>
          <td style="text-align: center;"> <a href="https://gofast-docs.readthedocs.io/fr/latest/docs-gofast-users/doc-gofast-guide-utilisateurs.html#les-espaces-collaboratifs"><img src="<?php global $base_url;
                                                                                                                                                                                            print $base_url ?>/sites/default/files/collaborative.png" /></a></td>
          <td style="text-align: center;"> <a href="https://gofast-docs.readthedocs.io/fr/latest/docs-gofast-users/doc-gofast-guide-utilisateurs.html#creation-de-contenus"><img src="<?php global $base_url;
                                                                                                                                                                                      print $base_url ?>/sites/default/files/create_content.png" /></a></td>
          <td style="text-align: center;"> <a href="https://gofast-docs.readthedocs.io/fr/latest/docs-gofast-users/doc-gofast-guide-utilisateurs.html#vos-abonnements"><img src="<?php global $base_url;
                                                                                                                                                                                  print $base_url ?>/sites/default/files/abonnement.png" /></a></td>
          <td style="text-align: center;"> <a href="https://gofast-docs.readthedocs.io/fr/latest/docs-gofast-users/doc-gofast-guide-utilisateurs.html#version-mobile"><img src="<?php global $base_url;
                                                                                                                                                                                print $base_url ?>/sites/default/files/mobile.png" /></a></td>
        </tr>
      </table>
      <p><?php print t('If you want information on something else, here is ', array(), $l); ?><a href="https://gofast-docs.readthedocs.io/fr/latest/docs-gofast-users/doc-gofast-guide-utilisateurs.html" style="font-size:15px; text-decoration: underline; text-decoration-color: #0074A6; font-weight:normal;   overflow:auto;   margin-left: 5px;   font-weight: bold;   color: #0074A6;"><?php print t('the link', array(), $l); ?></a>
        <?php print t('to the online documentation.', array(), $l); ?></p>
      <p style="margin-top: 20px; font-size:18px; line-height: 1.5em;"><?php print t('If you have more questions about GoFAST features, please post them on the ', array(), $l); ?><a href="https://community.ceo-vision.com/" style="text-decoration: underline; text-decoration-color: #0074A6; font-weight:normal;   overflow:auto;   margin-left: 5px;   font-weight: bold;   color: #0074A6;"><?php print t('GOFAST community forum', array(), $l); ?></a></p>
    </td>
  </tr>
</table>
<!-- Table spacer -->
<table>
  <div></div>
</table>
<table>
  <div></div>
</table>
