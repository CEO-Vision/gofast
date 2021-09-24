<?php

/**
 * @file
 * Display the body of the mail sent for user creation
 *
 * Available variables:
 * - $author_pict: Link to author picture
 * - $author_name : Author Name (FirstName LastName)
 * - $user_login : Le login of newly created user
 * - $user_password : password of newly created user
 * - $site_name : name of site
 * - $url : URL of site sending this email
 * - $url_change_password : url to change password on the first connection
 * - $l : array containing technical info for t() function
 * @ingroup themeable
 */
?>
<tr>
  <td align="center" valign="top" style="border-collapse: collapse;">
    <!-- // Begin Template Body \ -->
    <table width="95%" cellspacing="0" cellpadding="0" border="0" style="border-bottom:solid 20px #fff;">
    <tr>
        <td>
            <table width="100%" cellspacing="0" cellpadding="10" border="0" style="border-collapse:separate !important; border:1px solid #d9d9d9; border-radius:4px; background-color:#fafafa; ">
                <tr>
                    <td style="padding:10px;">
                        <table width="100%" cellspacing="0" cellpadding="0" border="0">
                            <tr>
                                <td width="40" height="40" valign="top" style="width:40px; max-width:40px; height:40px; max-height:40px;">
                                    <table width="40" height="40" cellspacing="0" cellpadding="0" border="0" style="background:#fff; border:0;">
                                        <tr>
                                            <td width="40" height="40" valign="middle" style="width:40px; height:40px; border-collapse:collapse; line-height:100%; padding:0;">
                                                <?php print $author_pic; ?>
                                            </td>
                                        </tr>
                                    </table>
                                </td>
                                <td width="10" valign="top" style="font-size:1px"></td>
                                <td valign="middle">
                                    <table width="100%" cellspacing="0" cellpadding="0" border="0" align="left" style="font-size:12px;">
                                        <tr>
                                            <td valign="top" style="color: #666666; font-family: Arial; font-size: 13px; font-weight: normal; line-height: 150%;">
                                                <?php 
                                                    print t('!author has created an account for you on ', array('!author' => $author_name), $l);
                                                ?>
                                                <a href='<?php print $url; ?>' >
                                                  <span style="font-size:15px; font-weight:normal; overflow:auto; margin-left: 5px; font-weight: bold; color: #0074A6">
                                                    <?php print $site_name ?>
                                                  </span>
                                                </a>                                              
                                            </td>
                                        </tr>
                                    </table>
                                </td>
                            </tr>
                        </table>
                        <table width="97%" cellspacing="0" cellpadding="0" border="0" align="center">
                            <!-- comment section -->
                            <tr>
                                <td valign="top">
                                    <table width="100%" cellspacing="0" cellpadding="0" border="0" align="left" style="border-collapse:separate !important;">
                                        <tr>
                                            <td height="10">
                                                <!-- margin -->
                                            </td>
                                        </tr>                               
                                        <tr>
                                            <td style="background-color: #F9F9F9; border:1px solid #dddddd; border-radius:5px;">
                                                <table width="100%" cellspacing="0" cellpadding="10" border="0" align="center">
                                                    <tr>
                                                        <td width="5" valign="top" style="padding:10px; font-size:1px"></td>
                                                        <td style="width: 100%;max-height: 300px; overflow: auto; padding:10px; color:#666666; font-family:Arial; font-size:14px; font-weight:normal; line-height:150%; display:inline-block; word-wrap:break-word; word-break:break-word;" >
                                                          <div>
                                                            <?php
                                                                print t('You can connect using the login and password configured into your company directory', array(), $l); 
                                                            ?>
                                                           </div>
                                                            
                                                        </td>
                                                        <td width="5" valign="top" style="padding:10px; font-size:1px"></td>
                                                    </tr>
                                                </table>
                                            </td>
                                        </tr>
                                    </table>
                                    <table width="100%" cellspacing="0" cellpadding="0" border="0" align="center" style="font-size:12px;">
                                        <tr>
                                            <td height="10" style="height:10px; max-height:10px; font-size:10px; line-height:100%">
                                                &nbsp; <!-- margin -->
                                            </td>
                                        </tr>
                                    </table>
                                </td> <!-- comment section end -->
                            </tr>
                  <tr>
                    <td style="color: #666666; font-family: Arial; font-size: 13px; font-weight: normal; line-height: 150%;" >
                      <span><?php //print $expiry_msg; ?></span>
                    </td>
                  </tr>
                        </table>
                    </td>
                </tr>
            </table>
        </td>
    </tr>
</table>
  </td>
</tr>
