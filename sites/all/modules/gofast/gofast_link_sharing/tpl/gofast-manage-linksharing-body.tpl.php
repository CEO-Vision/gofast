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
          <td valign="bottom" style="padding-left:10px; width: 50px;">
            <?php print $author_pic; ?>
          </td>
          <td valign="middle" style="text-align: left; font-size:14px; color: #515151;">
            <?php
              print_r($author_name);
              print t(' shared with you :', array(), $l);
              print $document_pic;          
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

<!-- Subject Panel -->
<table width="98%" cellpadding="0" cellspacing="0" style=" border: 1px solid; border-color: #ddd; margin-left: 10px; margin-right: 10px; border-radius: 4px;  -webkit-box-shadow: 0 1px 1px rgba(0,0,0,.05); box-shadow: 0 1px 1px rgba(0,0,0,.05); margin-bottom: 10px;">
  <tr>
    <td>
      <table width="100%" cellpadding="0" cellspacing="0" bgcolor="#f5f5f5" style=" background-color: #f5f5f5; border-bottom: 1px solid;  border-color: #bce8f1;">
              <tr>
                <td style="padding-left:15px;">
                  <h4 style="margin-top: 10px; margin-bottom: 10px; color: #31708f;"><?php print t('Documents', array(), $l); ?></h4>
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
                            <span style=" font-size:15px;   font-weight:normal;   overflow:auto;   margin-left: 5px;   font-weight: bold; text-decoration: underline; text-decoration-color: #0074A6;  color: #0074A6">
                                <?php print $node_information['title']; ?>
                            </span>
                         </a>
                        <code>
                            <strong>   <?php print t("Version :  ", array(),array('context'=>'gofast:gofast_linksharing')) . $node_information['version']; ?>  </strong>
                        </code>
                      <?php
                      }
                    }
                  ?>
            
                </li>
                <table width="100%" cellspacing="0" cellpadding="0" border="0" align="center" style="font-size:12px;">
                    <tr>
                        <td height="20" style="height:20px; max-height:20px; font-size:10px; line-height:100%">
                            &nbsp; <!-- margin -->
                        </td>
                    </tr>
                    <tr>
                        <td width="200">
                            <table width="100%" border="0" cellpadding="6" cellspacing="0" style="color:#FFFFFF; font-family:Arial; font-size:12px; font-weight:bold; line-height:100%; text-align:center; text-decoration:none; -moz-border-radius:2px; -webkit-border-radius:2px; background-color:#2DA1EC; border:1px solid #0082C3; border-collapse:separate !important; border-radius:2px;">
                                <tr>
                                    <td valign="middle" style="padding:6px; border-collapse: collapse;">
                                      <?php global $base_url ?>
                                      <a href="<?php print $download ?>"style='color:white;text-decoration:none;'><?php print t('Download documents here',array(),$l); ?> </a>  
                                    </td>
                                </tr>
                            </table>
                        </td>
                        <td style="border:none; text-decoration:none; font-family:'Helvetica Neue',Helvetica,Arial,sans-serif; color:#999999; text-align:right;">
                        </td>
                    </tr>
                </table>                
   
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
        <table width="100%" cellpadding="0" cellspacing="0" bgcolor="#d9edf7" style=" background-color: #d9edf7; border-bottom: 1px solid;  border-color: #bce8f1;">
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




