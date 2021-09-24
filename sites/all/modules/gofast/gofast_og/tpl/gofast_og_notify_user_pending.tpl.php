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
            <center><?php print t('Hello', array(), $l);?>, </center>
          </td>
        </tr>
      </table>
    </td>
  </tr>
  <tr>
    <td>
      <table width="98%" cellpadding="0" cellspacing="0" style="padding-left:10px; padding-right: 10px; margin-top:20px;">
        <tr>
          <td valign="bottom" style="padding-left:10px; width: 50px;">
            <?php print $author_pic; ?>
          </td>
          <td valign="middle" style="text-align: left; font-size:14px; color: #515151;">
            <?php
            print_r($author_name . " ");
              print t('You asked to join the space ', array(), $l);
            ?>
            <a href='<?php print $node_link; ?>' >
              <span style="  font-size:15px;   font-weight:normal;   overflow:auto;   margin-left: 5px;   font-weight: bold; text-decoration: underline; text-decoration-color: #0074A6;  color: #0074A6">
                <?php print $node_title; ?>
              </span>
            </a>
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
                  <h4 style="margin-top: 10px; margin-bottom: 10px; color: #31708f;"><?php print t('Action', array(), $l); ?></h4>
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
              print t("Your request is pending. You will be notified when an Administrator of this space accepts/rejects it.", array(), $l);
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