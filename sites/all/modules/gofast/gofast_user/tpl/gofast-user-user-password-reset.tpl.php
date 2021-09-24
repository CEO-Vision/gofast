<?php

?>

<style>
body{
  font-family: Roboto, Arial, sans-serif;
}
</style>
<!--[if mso]><!-- -->
<style>
</style>
<!--<![endif]-->


<!-- Title div. Title of the body -->
<table width="100%" cellpadding="0" cellspacing="0" style="margin-bottom: 20px;">
  <tr style="margin-bottom: 20px;">
    <td>
      <table width="100%" cellpadding="0" cellspacing="0">
        <tr>
          <td style="font-size:14px; color: #515151;">
            <center><?php print t('Hello', array(), $l) . " " . $name; ?>,</center>
          </td>
        </tr>
      </table>
    </td>
  </tr>
</table>
<!-- Table spacer -->
<table><div></div></table>
<table><div></div></table>

<!-- Subject Panel -->
<table width="98%" cellpadding="0" cellspacing="0" style=" border: 1px solid; border-color: #ddd; margin-left: 10px; margin-right: 10px; border-radius: 4px;  -webkit-box-shadow: 0 1px 1px rgba(0,0,0,.05); box-shadow: 0 1px 1px rgba(0,0,0,.05); margin-bottom: 10px;">
  <tr>
    <td>
      <table width="100%" cellpadding="0" cellspacing="0" bgcolor="#f5f5f5" style=" background-color: #f5f5f5; border-bottom: 1px solid;  border-color: #bce8f1;">
              <tr>
                <td style="padding-left:15px;">
                  <h4 style="margin-top: 10px; margin-bottom: 10px; color: #31708f;"><?php print t('Reset your password', array(), $l); ?></h4>
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
                  <?php
                    print t("A new password request has been done for your account. If this action doesn't comes from you, please ignore this message.", array(), $l);
                  ?>
                  <br /><br />
                  <?php
                    $link = "<a href='".$new_password_link."'>".t("password reset form", array(), $l)."</a>";
                    print t("You can reset your password using this", array(), $l) . " " . $link . ".";
                  ?>
          </td>
        </tr>
      </table>
    </td>
  </tr>
</table>
<!-- Table spacer -->
<table><div></div></table>
<table><div></div></table>

<!-- Note Panel -->
<table width="98%" cellpadding="0" cellspacing="0" style="border: 1px solid; border-color: #bce8f1;   margin-left: 10px; margin-right: 10px; border-radius: 4px;  -webkit-box-shadow: 0 1px 1px rgba(0,0,0,.05); box-shadow: 0 1px 1px rgba(0,0,0,.05); margin-bottom: 10px;">
  <tr>
    <td>
        <table width="100%" cellpadding="0" cellspacing="0" bgcolor="#d9edf7" style=" background-color: #d9edf7; border-bottom: 1px solid;  border-color: #bce8f1;">
              <tr>
                <td style="padding-left:15px;">
                  <h4 style="margin-top: 10px; margin-bottom: 10px; color: #31708f;"><?php print t('Usage', array(), $l) ?></h4>
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
          <?php
            print t('This link will be active for the next day and can only be used to reset your password once.', array(), $l);
          ?>
        </td>
      </tr>
    </table>
    </td>
  </tr>
</table>
<!-- Table spacer -->
<table><div></div></table>
<table><div></div></table>

