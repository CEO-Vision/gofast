<table width="100%" cellspacing="0" cellpadding="0" border="0" style="border-bottom:solid 20px #fff;">
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
                                                    print $is_digest ? $author_name : t('!author updated', array('!author' => $author_name), $l);
                                                ?>
                                              <span style="font-size:15px; font-weight:normal; overflow:auto; margin-left: 5px; font-weight: bold; color: #0074A6"><?php print $node_title; ?></span>
                                            </td>
                                        </tr>
                                        <?php if ($is_digest) : ?>
                                            <tr>
                                                <td valign="bottom" style="color: #666666; font-family: Arial; font-size: 12px; font-weight: normal; line-height: 150%; padding-top:1px;">
                                                    <?php print t('updated this content', array(), $l); ?>
                                                </td>
                                            </tr>                     
                                        <?php endif; ?>
                                    </table>
                                </td>
                            </tr>
                        </table>
                        <table width="100%" cellspacing="0" cellpadding="0" border="0" align="center">
                            <!-- comment section -->
                            <tr>
                                <td valign="top">
                                    <table width="100%" cellspacing="0" cellpadding="0" border="0" align="left" style="border-collapse:separate !important;">
                                        <tr>
                                            <td height="10">
                                                <!-- margin -->
                                            </td>
                                        </tr>   
                                        <?php if (isset($modifications)) : ?>
                                        <tr>
                                            <td style="background-color: #F9F9F9;">
                                                <table width="100%" cellspacing="0" cellpadding="10" border="0" align="center">
                                                    <tr>
                                                        <td style=" color:#666666; font-family:Arial; font-size:14px; font-weight:normal; line-height:150%; word-wrap:break-word; word-break:break-word;" >
                                                            <?php print $modifications; ?>
                                                        </td>
                                                    </tr>
                                                </table>
                                            </td>
                                        </tr>
                                        <?php endif; ?>
                                    </table>
                                    <table width="100%" cellspacing="0" cellpadding="0" border="0" align="center" style="font-size:12px;">
                                        <tr>
                                            <td height="10" style="height:10px; max-height:10px; font-size:10px; line-height:100%">
                                                &nbsp; <!-- margin -->
                                            </td>
                                        </tr>
                                        <tr>
                                            <td width="75">
                                            </td>
                                            <td style="border:none; text-decoration:none; font-family:'Helvetica Neue',Helvetica,Arial,sans-serif; color:#999999; text-align:right;">
                                                <?php print $date; ?>
                                            </td>
                                        </tr>
                                    </table>
                                </td> <!-- comment section end -->
                            </tr>
                        </table>
                    </td>
                </tr>
            </table>
        </td>
    </tr>
</table>