<style>
  pre.gf-kanban-card-desc, pre.gf-kanban-comment {
	font-family: inherit; 
	font-size: 14px;
	border: none;
	background-color: transparent;
	padding: 0px;
	color: #666666;
	white-space: -moz-pre-wrap;
	white-space: -pre-wrap;
	white-space: -o-pre-wrap;
	white-space: pre-wrap;
	word-wrap: break-word;
}
</style>


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
                                                    $comment_title = "<strong>".$comment_title."</strong>";
                                                    print $is_digest ? $author_name : t('!author edited the comment "!title" on', array('!author' => $author_name, '!title' => $comment_title), $l);
                                                ?>
                                            <span style="font-size:15px; font-weight:normal; overflow:auto; margin-left: 5px; font-weight: bold; color: #0074A6"><?php print $node_title; ?></span>
                                            </td>
                                            <td style="border:none; text-decoration:none; font-family:'Helvetica Neue',Helvetica,Arial,sans-serif; color:#999999; text-align:right;">
                                                <?php print $date; ?>
                                            </td>
                                        </tr>
                                        <?php if ($is_digest) : ?>
                                            <tr>
                                                <td valign="bottom" style="color: #666666; font-family: Arial; font-size: 12px; font-weight: normal; line-height: 150%; padding-top:1px;">
                                                    <?php print t('edited his comment', array(), $l); ?>
                                                </td>
                                            </tr>                     
                                        <?php endif; ?>
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
                                                          <?php print $comment_body; ?>
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
                                        <tr>
                                            <td width="75">
                                                <table width="100%" border="0" cellpadding="6" cellspacing="0" style="color:#FFFFFF; font-family:Arial; font-size:12px; font-weight:bold; line-height:100%; text-align:center; text-decoration:none; -moz-border-radius:2px; -webkit-border-radius:2px; background-color:#2DA1EC; border:1px solid #0082C3; border-collapse:separate !important; border-radius:2px;">
                                                    <tr>
                                                        <td valign="middle" style="padding:6px; border-collapse: collapse;">
                                                          <?php global $base_url ?>
                                                          <a href="<?php print $base_url."/node/".$nid."/replytocomment/".$cid;?>" style='color:white;text-decoration:none;'> <?php print $comment_reply; ?></a>
                                                        </td>
                                                    </tr>
                                                </table>
                                            </td>
                                            <td style="border:none; text-decoration:none; font-family:'Helvetica Neue',Helvetica,Arial,sans-serif; color:#999999; text-align:right;">
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