<style>
@import url(http://fonts.googleapis.com/css?family=Roboto);
body{
  font-family: Roboto, Arial, sans-serif;
} 
</style>

<!-- GoFast Notifications - Node Deadline template -->
<table width="100%" cellpadding="0" cellspacing="0" style="margin-bottom: 20px;">
  <tr style="margin-bottom: 20px;">
    <td>
      <table width="100%" cellpadding="0" cellspacing="0">
        <tr>
          <td style="color:#505050; font-family:Arial; font-size:14px; line-height:150%; text-align:left;">
            <center><?php print t('Hello ',array(), $l) . $user_name . "," ; ?></center> <br />
          </td>
        </tr>
      </table>        
    </td>
  </tr>
  <tr>
    <td>
      <table width="98%" cellpadding="0" cellspacing="0" style="border: 1px solid; border-color: #bce8f1;   margin-left: 10px; margin-right: 10px; border-radius: 4px;  -webkit-box-shadow: 0 1px 1px rgba(0,0,0,.05); box-shadow: 0 1px 1px rgba(0,0,0,.05); margin-bottom: 10px;">
        <tr>
          <td>
            <table width="100%" cellpadding="0" cellspacing="0" bgcolor="#d9edf7" style=" background-color: #d9edf7; border-bottom: 1px solid;  border-color: #bce8f1;">
              <tr>
                <td style="padding-left:15px;">
                  <h4 style="margin-top: 10px; margin-bottom: 10px; color: #31708f;"><?php print t('Deadline', array(), $l) ;?></h4>
                </td>
              </tr>
          </table>
          </td>
        </tr>
        <tr>
          <td>
            <table width="100%" cellpadding="0" cellspacing="0">
            <tr>
              <td valign="middle" style="color:#505050; font-family:Arial; font-size:14px; line-height:150%; text-align:left; padding: 10px 15px;">
                <?php print t('The deadline of', array(), $l); ?>
                <?php print $node_icon; ?>
                <a href='<?php print $node_link; ?>' >
                  <span style="  font-size:15px;   font-weight:normal;   overflow:auto;   margin-left: 5px;   font-weight: bold; text-decoration: underline; text-decoration-color: #0074A6;  color: #0074A6">
                    <?php print $node_title; ?>
                  </span>
                </a>
                <?php
                  print t('is set for tomorrow.', array(), $l);
                ?>
              </td>
            </tr>
          </table>
          </td>
        </tr>
      </table> 
    </td>
  </tr>
</table>
<!-- Table spacer -->
<table><div></div></table>
<table><div></div></table>
