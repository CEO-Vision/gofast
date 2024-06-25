<!--[if mso | IE]></td></tr></table><table align="center" border="0" cellpadding="0" cellspacing="0" class="" role="presentation" style="width:992px;" width="992" bgcolor="white" ><tr><td style="line-height:0px;font-size:0px;mso-line-height-rule:exactly;"><![endif]-->
<div style="background:white;background-color:white;margin:0px auto;border-radius:0 0 10px 10px;max-width:992px;">
    <table align="center" border="0" cellpadding="0" cellspacing="0" role="presentation" style="background:white;background-color:white;width:100%;border-radius:0 0 10px 10px;">
        <tbody>
            <tr>
                <td style="direction:ltr;font-size:0px;padding:0;padding-top:5px;text-align:center;">
                    <?php if (isset($responsible) || isset($item_labels)) : ?>
                        <!--[if mso | IE]><table role="presentation" border="0" cellpadding="0" cellspacing="0"><tr><td class="" style="vertical-align:top;width:496px;" ><![endif]-->
                        <div class="mj-column-per-50 mj-outlook-group-fix" style="font-size:0px;text-align:left;direction:ltr;display:inline-block;vertical-align:top;width:100%;">
                            <table border="0" cellpadding="0" cellspacing="0" role="presentation" width="100%">
                                <tbody>
                                <tr>
                                    <td style="vertical-align:top;padding-left:10px;">
                                    <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="" width="100%">
                                        <tbody>
                                        <tr>
                                            <td align="left" style="font-size:0px;padding:10px 25px;<?= $last ? "padding-bottom:0;" : "" ?>word-break:break-word;">
                                            <div style="font-family:Poppins, Helvetica, Arial, sans-serif;font-size:14px;font-weight:600;line-height:1;text-align:left;color:#000000;"><img src="<?= $base_url ?>/sites/all/modules/gofast/gofast_mail_queue/icon/trello-primary.png" style="vertical-align: bottom;" width="18">
                                                <a href="<?= $node_link ?>" style="color: #000000; font-size: 18px; font-weight: 600; text-decoration: none;">&nbsp;<?= $node_title ?></a>
                                                <?php if(isset($responsible)) : ?>
                                                    <img width="18" style="padding-left: 5px; vertical-align: bottom; border-radius: 50%;" typeof="foaf:Image" src="<?= gofast_get_url_picture_by_id($responsible->picture->fid) ?>" alt="<?= t("@user's picture", array('@user' => format_username($responsible)), array('context' => 'gofast:gofast_user')) ?>" title="<?= t("@user's picture", array('@user' => format_username($responsible)), array('context' => 'gofast:gofast_user')) ?>" />
                                                    <span style="font-weight: 400;"><?= gofast_user_display_name($responsible) ?> / <?= $parent_space ?></span>
                                                <?php endif; ?>
                                            </div>
                                            </td>
                                        </tr>
                                        </tbody>
                                    </table>
                                    </td>
                                </tr>
                                </tbody>
                            </table>
                        </div>
                        <!--[if mso | IE]></td><td class="" style="vertical-align:top;width:496px;" ><![endif]-->
                        <div class="mj-column-per-50 mj-outlook-group-fix" style="font-size:0px;text-align:left;direction:ltr;display:inline-block;vertical-align:top;width:100%;">
                            <table border="0" cellpadding="0" cellspacing="0" role="presentation" width="100%">
                                <tbody>
                                <tr>
                                    <td style="vertical-align:top;padding:0;padding-left:10px;">
                                    <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="" width="100%">
                                        <tbody>
                                        <tr>
                                            <td align="left" style="font-size:0px;padding:10px 25px;<?= $last ? "padding-bottom:0;" : "" ?>word-break:break-word;">
                                            <?php if (isset($item_labels)) : ?>
                                                <div style="font-family:Poppins, Helvetica, Arial, sans-serif;font-size:14px;line-height:1;text-align:left;color:#000000;">
                                                    <?= theme('gofast-notifications-node-icon', array('icon' => 'flag.png', 'width' => '14')) ?>
                                                    <span style="color: #000000; font-size: 14px; text-decoration: none;">&nbsp;<?= $item_labels ?></span>
                                                </div>
                                            <?php endif; ?>
                                            </td>
                                        </tr>
                                        </tbody>
                                    </table>
                                    </td>
                                </tr>
                                </tbody>
                            </table>
                        </div>
                        <!--[if mso | IE]></td></tr></table><![endif]-->
                    <?php else : ?>
                        <!--[if mso | IE]><table role="presentation" border="0" cellpadding="0" cellspacing="0"><tr><td class="" style="vertical-align:top;width:992px;" ><![endif]-->
                        <div class="mj-column-per-100 mj-outlook-group-fix" style="font-size:0px;text-align:left;direction:ltr;display:inline-block;vertical-align:top;width:100%;">
                            <table border="0" cellpadding="0" cellspacing="0" role="presentation" width="100%">
                                <tbody>
                                <tr>
                                    <td style="vertical-align:top;padding-left:10px;">
                                    <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="" width="100%">
                                        <tbody>
                                        <tr>
                                            <td align="left" style="font-size:0px;padding:10px 25px;<?= $last ? "padding-bottom:0;" : "" ?>word-break:break-word;">
                                            <div style="font-family:Poppins, Helvetica, Arial, sans-serif;font-size:14px;font-weight:600;line-height:1;text-align:left;color:#000000;">
                                                <?= str_replace(".png", ".png?cache=" . rand(1, 1000), $node_icon) ?>
                                                <a href="<?= $node_link ?>" style="color: #000000; font-size: 18px; font-weight: 600; text-decoration: none;">&nbsp;<?= $node_title ?></a>
                                            </div>
                                            </td>
                                        </tr>
                                        </tbody>
                                    </table>
                                    </td>
                                </tr>
                                </tbody>
                            </table>
                        </div>
                        <!--[if mso | IE]></td></tr></table><![endif]-->
                    <?php endif; ?>
                </td>
            </tr>
        </tbody>
    </table>
</div>
