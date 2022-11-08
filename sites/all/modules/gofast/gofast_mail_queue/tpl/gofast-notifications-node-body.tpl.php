<style>
    /** GoFAST */
    pre.gf-kanban-card-desc,
    pre.gf-kanban-comment {
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

    /** GoFAST */
    img:not(.gofast_png_icon) {
        width: 40px;
    }

    img.gofast__comment-tag-icon {
        display: none;
    }
</style>

<!-- Comments -->
<?php global $base_url; ?>
<?php foreach ($content as $group) : ?>
    <?php foreach ($group["items"] as $item) : ?>
        <!--[if mso | IE]><table align="center" border="0" cellpadding="0" cellspacing="0" class="" role="presentation" style="width:992px;" width="992" bgcolor="transparent" ><tr><td style="line-height:0px;font-size:0px;mso-line-height-rule:exactly;"><![endif]-->
        <div style="background:transparent;background-color:transparent;margin:0px auto;max-width:992px;">
            <table align="center" border="0" cellpadding="0" cellspacing="0" role="presentation" style="background:transparent;background-color:transparent;width:100%;">
                <tbody>
                    <tr>
                        <td style="direction:ltr;font-size:0px;padding:20px 0;padding-bottom:10px;padding-top:10px;text-align:center;">
                            <!--[if mso | IE]><table role="presentation" border="0" cellpadding="0" cellspacing="0"><tr></tr></table><![endif]-->
                        </td>
                    </tr>
                </tbody>
            </table>
        </div>
        <!--[if mso | IE]></td></tr></table><table align="center" border="0" cellpadding="0" cellspacing="0" class="" role="presentation" style="width:992px;" width="992" bgcolor="white" ><tr><td style="line-height:0px;font-size:0px;mso-line-height-rule:exactly;"><![endif]-->
        <div style="background:white;background-color:white;margin:0px auto;border-radius:10px 10px 0 0;max-width:992px;">
            <table align="center" border="0" cellpadding="0" cellspacing="0" role="presentation" style="background:white;background-color:white;width:100%;border-radius:10px 10px 0 0;">
                <tbody>
                    <tr>
                        <td style="direction:ltr;font-size:0px;padding:0;text-align:center;">
                            <!--[if mso | IE]><table role="presentation" border="0" cellpadding="0" cellspacing="0"><tr><td class="" style="vertical-align:top;width:992px;" ><![endif]-->
                            <div class="mj-column-per-100 mj-outlook-group-fix" style="font-size:0px;text-align:left;direction:ltr;display:inline-block;vertical-align:top;width:100%;">
                                <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="background-color:#337ab7;border-radius:10px 10px 0 0;vertical-align:top;" width="100%">
                                    <tbody>
                                        <tr>
                                            <td align="left" style="font-size:0px;padding:10px 25px;padding-left:10px;word-break:break-word;">
                                                <div id="<?= $item["node"]->nid ?>" style="font-family:Poppins, Candara, Helvetica, Arial, sans-serif;font-size:18px;font-weight:600;line-height:1;text-align:left;color:white;">
                                                    <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="vertical-align:middle;">
                                                        <tbody>
                                                            <tr>
                                                                <td>
                                                                    <?= $item["icon_white"] ?>
                                                                </td>
                                                                <td><span style="color: #FFFFFF; font-size: 18px; font-weight: 600;">&nbsp;<?= $item["node"]->title ?></span><?= isset($item["flag"]) ? " <span style='font-weight: 300; color: #FD7E14;'> <b>(" . t($item["flag"], array(), $l) . ")</b></span>" : "" ?>
                                                                </td>
                                                            </tr>
                                                        </tbody>
                                                    </table>
                                                </div>
                                            </td>
                                        </tr>
                                    </tbody>
                                </table>
                            </div>
                            <!--[if mso | IE]></td></tr></table><![endif]-->
                        </td>
                    </tr>
                </tbody>
            </table>
        </div>
        <!--[if mso | IE]></td></tr></table><![endif]-->
        <?php
        $mail_loop_count = 1;
        foreach ($item["events"] as $event) {
            echo theme("gofast-notifications-node-event", array(
                "event" => $event,
                "item" => $item,
                "l" => $l,
                "short_format" => $short_format,
                "short_without_hours_format" => $short_without_hours_format,
                "extra_short_format" => $extra_short_format,
                "mail_loop_count" => $mail_loop_count,
            ));
            $mail_loop_count++;
        } ?>
    <?php endforeach; ?>
<?php endforeach; ?>
<!--[if mso | IE]><table align="center" border="0" cellpadding="0" cellspacing="0" class="" role="presentation" style="width:992px;" width="992" bgcolor="transparent" ><tr><td style="line-height:0px;font-size:0px;mso-line-height-rule:exactly;"><![endif]-->
<div style="background:transparent;background-color:transparent;margin:0px auto;max-width:992px;">
    <table align="center" border="0" cellpadding="0" cellspacing="0" role="presentation" style="background:transparent;background-color:transparent;width:100%;">
        <tbody>
            <tr>
                <td style="direction:ltr;font-size:0px;padding:20px 0;padding-bottom:10px;padding-top:10px;text-align:center;">
                    <!--[if mso | IE]><table role="presentation" border="0" cellpadding="0" cellspacing="0"><tr></tr></table><![endif]-->
                </td>
            </tr>
        </tbody>
    </table>
</div>
<!--[if mso | IE]></td></tr></table><![endif]-->