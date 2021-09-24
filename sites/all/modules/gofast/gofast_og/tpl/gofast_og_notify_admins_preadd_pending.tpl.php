<?php

?>

<style>
body{
  font-family: Roboto, Arial, sans-serif;
}
code{
    padding: 2px 4px;
    font-size: 90%;
    color: #c7254e;
    background-color: #f9f2f4;
    border-radius: 4px;
}
</style>
<!--[if mso]><!-- -->
<style>
</style>
<!--<![endif]-->


<!-- Title div. Title of the body -->
<table width="100%" cellpadding="0" cellspacing="0" style="margin-bottom: 20px;">
  <tr>
    <td>
      <table width="98%" cellpadding="0" cellspacing="0" style="padding-left:10px; padding-right: 10px; margin-top:20px;">
        <tr>
            <?php print t('The administrator of the platform @siteName, @adminName asks you to add the following user(s) in the space ', ["@siteName" => $site_name, "@adminName" => $admin_name], $l); ?>
            <a href='<?php print $node_link; ?>'>
              <span style=" font-size:15px; font-weight:normal; overflow:auto; margin-left: 5px; font-weight: bold; text-decoration: underline; text-decoration-color: #0074A6; color: #0074A6">
                <?php print $node_title ?>
              </span>
            </a>
            :
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
                  <h4 style="margin-top: 10px; margin-bottom: 10px; color: #31708f;"><?php print t('Users', array(), $l); ?></h4>
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

              <table width="98%" cellpadding="0" cellspacing="0" style="padding-left:10px; padding-right: 10px; margin-top:20px;">
              <tr>
                <?php print $users_preadd; ?>
              </tr>
              </table>
<!--
                  <?php
                    /* if (empty($nodes_informations)){
                    }
                    else{
                      foreach($nodes_informations as $node_information){ */?>
                <li style="list-style: none;margin-bottom: 5px;">
                         <?php /* print $node_information['icon']; */?>
                         <a href='<?php /* print $node_information['url'];  */?>' >
                            <span style=" font-size:15px;   font-weight:normal;   overflow:auto;   margin-left: 5px;   font-weight: bold; text-decoration: underline; text-decoration-color: #0074A6;  color: #0074A6">
                                <?php /* print $node_information['title']; */ ?>
                            </span>
                         </a>
                        <code>
                            <strong>   <?php print t("Version :  ", array(),array('context'=>'gofast:gofast_linksharing')) ?>  </strong>
                        </code>
                      <?php
                     /*  }
                    } */
                  ?>
                </li> -->
          </td>
        </tr>
      </table>
    </td>
  </tr>
</table>

<!-- Note Panel -->
<table width="98%" cellpadding="0" cellspacing="0" style="border: 1px solid; border-color: #bce8f1;   margin-left: 10px; margin-right: 10px; border-radius: 4px;  -webkit-box-shadow: 0 1px 1px rgba(0,0,0,.05); box-shadow: 0 1px 1px rgba(0,0,0,.05); margin-bottom: 10px;">
  <tr>
    <td>
        <table width="100%" cellpadding="0" cellspacing="0" bgcolor="#d9edf7" style=" background-color: #d9edf7; border-bottom: 1px solid;  border-color: #bce8f1;">
              <tr>
                <td style="padding-left:15px;">
                  <h4 style="margin-top: 10px; margin-bottom: 10px; color: #31708f;"><?php print t('Action', array(), $l) ?></h4>
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
              print t("You are the administrator of this space, please go to the members tab of the space to accept / decline ", array(), $l);
              ?>
              <a href='<?php print $node_link; ?>'>
                <span style="  font-size:15px;   font-weight:normal;   overflow:auto;   margin-left: 5px;   font-weight: bold; text-decoration: underline; text-decoration-color: #0074A6;  color: #0074A6">
                  <?php print t("space's page", array(), $l) . "."; ?>
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




