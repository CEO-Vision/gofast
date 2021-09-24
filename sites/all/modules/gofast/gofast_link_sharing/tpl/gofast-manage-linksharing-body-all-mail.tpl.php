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
<!-- Table spacer -->
<table><div></div></table>
<table><div></div></table>

<!-- Subject Panel -->
<table width="98%" cellpadding="0" cellspacing="0" style=" border: 1px solid; border-color: #ddd; margin-left: 10px; margin-right: 10px; border-radius: 4px;  -webkit-box-shadow: 0 1px 1px rgba(0,0,0,.05); box-shadow: 0 1px 1px rgba(0,0,0,.05); margin-bottom: 10px;">
  <tr>
    <td>
      <table width="100%" cellpadding="0" cellspacing="0" bgcolor="#f5f5f5" style=" background-color: #d9edf7; border-bottom: 1px solid;  border-color: #bce8f1;">
              <tr>
                <td style="padding-left:15px;">
                  <h4 style="margin-top: 10px; margin-bottom: 10px; color: #31708f;"><?php print t('Sent to', array(), $l); ?></h4>
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
                    if (empty($mail_list)){
                    }
                    else{
                      print $mail_list;
                    }
                  ?>
          </td>
        </tr>
      </table>
    </td>
  </tr>            
</table>


<!-- Subject Panel -->
<table width="98%" cellpadding="0" cellspacing="0" style=" border: 1px solid; border-color: #ddd; margin-left: 10px; margin-right: 10px; border-radius: 4px;  -webkit-box-shadow: 0 1px 1px rgba(0,0,0,.05); box-shadow: 0 1px 1px rgba(0,0,0,.05); margin-bottom: 10px;">
  <tr>
    <td>
      <table width="100%" cellpadding="0" cellspacing="0" bgcolor="#f5f5f5" style=" background-color: #d9edf7; border-bottom: 1px solid;  border-color: #bce8f1;">
              <tr>
                <td style="padding-left:15px;">
                  <h4 style="margin-top: 10px; margin-bottom: 10px; color: #31708f;"><?php print t('Documents sent', array(), $l); ?></h4>
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
                if (empty($nodes_informations)){
                }
                else{
                  foreach($nodes_informations as $node_information){?>
            <li style="list-style: none;margin-bottom: 5px;">
                     <?php print $node_information['icon'];?> 
                     <a href='<?php print $node_information['url']; ?>' >
                        <span style="  font-size:15px;   font-weight:normal;   overflow:auto;   margin-left: 5px;   font-weight: bold; text-decoration: underline; text-decoration-color: #0074A6;  color: #0074A6">
                            <?php print $node_information['title']; ?>
                        </span>
                     </a> <?php
                  }
                }
              ?>
          </td>
        </tr>
      </table>
    </td>
  </tr>            
</table>

<!-- Subject Panel -->
<table width="98%" cellpadding="0" cellspacing="0" style=" border: 1px solid; border-color: #ddd; margin-left: 10px; margin-right: 10px; border-radius: 4px;  -webkit-box-shadow: 0 1px 1px rgba(0,0,0,.05); box-shadow: 0 1px 1px rgba(0,0,0,.05); margin-bottom: 10px;">
  <tr>
    <td>
      <table width="100%" cellpadding="0" cellspacing="0" bgcolor="#f5f5f5" style=" background-color: #f5f5f5; border-bottom: 1px solid;  border-color: #bce8f1;">
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
          <td style=" color: #333; padding-left:10px; padding-top:10px; font-size: 14px; padding-right: 10px; padding-bottom: 10px;">
                  <?php 
                    if (empty($message)){
                    }
                    else{
                      print '<span style=font-style:italic;>' . $message . '</span>';
                    }
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
        <table width="100%" cellpadding="0" cellspacing="0" bgcolor="#d9edf7" style=" background-color: #fcf8e3; border-bottom: 1px solid;  border-color: #bce8f1;">
              <tr>
                <td style="padding-left:15px;">
                  <h4 style="margin-top: 10px; margin-bottom: 10px; color: #31708f;"><?php print t('Information', array(), $l) ?></h4>
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
            print t('If you want, you can download the file and edit it.', array(), $l);
            print " ";
            print $expiry_msg;
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

