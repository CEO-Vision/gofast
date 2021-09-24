<!-- GoFast Notifications - Header Template -->
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN" "http://www.w3.org/TR/REC-html40/loose.dtd">
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <!-- Facebook sharing information tags -->
        <meta property="og:title" content="GoFast Notifications">
        <title><?php echo(variable_get('site_name')); ?></title>
        <style type="text/css">
          #edits-metadatas tr td th{
            border: 1px solid grey;
          }
          </style>          
    </head>
    <body leftmargin="0" marginwidth="0" topmargin="0" marginheight="0" offset="0" style="background-color: #E6E6E6; width: 100% !important; -webkit-text-size-adjust: none; margin: 0; padding: 0;">
    	<center>
            <!-- Mail Client Background -->
            <table id="top" border="0" cellpadding="0" cellspacing="0" height="95%" width="60%" min-width="640px" style="height: 95% !important; margin: 0; padding: 0; width:70%; min-width:640px; background-color: #E6E6E6;">
                <tr>
                    <td width="95%" align="center" valign="top" style="padding-top: 0px; border-collapse: collapse;">
                        <!-- Mail Content -->
                        <table align="center" border="0" cellpadding="0" cellspacing="0" width="100%" style="border: 1px solid #DDDDDD; background-color: #EFEFEF; width:100%;">
                          <!-- Header row --> 
                            <tr>
                                <td align="center" valign="top" style="border-collapse: collapse;">
                                    <table align="center" border="0" cellpadding="0" cellspacing="0" width="100%" style="background-color: #FFFFFF; border: 0;  text-align:left;">
                                        <tr class="gofast-notification-header">
                                            <td align="left" width="100%" style="border-collapse: collapse; color: #202020; line-height: 100%; padding: 0; text-align: left; vertical-align: middle; width:100%;">
                                                <table align="left" border="0" cellpadding="0" cellspacing="0" width=100%" height="40" style="background-color: #2B2B2B; border: 0;">
                                                    <tr>
                                                        <td width="20%"style="width:10%; border-collapse: collapse; color: #202020;font-size: 30px;   line-height: 100%; padding: 0; text-align: left; vertical-align: middle;">
                                                            <!-- margin -->
                                                        </td>
                                                        <td width="100" height="40" valign="middle" style="width:100px; height:40px; border-collapse: collapse; color: #202020; line-height: 100%; padding: 0; text-align: left;">
                                                            <a href="<?php global $base_url; print $base_url; ?>">
                                                              <img src="<?php print($logo); ?>" height="33" style="max-height:33px; margin-right: 15px; border: 0; line-height: 100%; outline: none; text-decoration: none; bot: 0;">
                                                            </a>
                                                        </td>
                                                        <td width="10%"style="width:10%; border-collapse: collapse; color: #202020;font-size: 30px;   line-height: 100%; padding: 0; text-align: left; vertical-align: middle;">
                                                            <!-- margin -->
                                                        </td>
                                                        <td style="background-color: #2B2B2B; color: #9d9d9d; border-collapse: collapse; font-size: 24px;   line-height: 100%; text-align:left; vertical-align: middle;">
                                                            <?php echo($title);?>
                                                        </td>
                                                        <td>
                                                          <!-- Prevents clients like gmail to trim cell -->
                                                          &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                                                          &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                                                          &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                                                        </td>
                                                    </tr>
                                                </table>
                                            </td>
                                        </tr>
                                        <tr>
                                            <td height="20">
                                                <!-- margin -->
                                            </td>
                                        </tr>
                                    </table>
                                    <!-- // End Template Header \ -->
                                </td>
                            </tr>