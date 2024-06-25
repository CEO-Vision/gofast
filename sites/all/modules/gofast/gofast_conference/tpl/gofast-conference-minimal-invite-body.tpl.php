<?php global $base_url; ?>
<!-- FILE: mail_conference_minimal_invite_source.mjml -->
<style type="text/css">
    #outlook a {
        padding: 0;
    }

    body {
        margin: 0;
        padding: 0;
        -webkit-text-size-adjust: 100%;
        -ms-text-size-adjust: 100%;
    }

    table,
    td {
        border-collapse: collapse;
        mso-table-lspace: 0pt;
        mso-table-rspace: 0pt;
    }

    img {
        border: 0;
        height: auto;
        line-height: 100%;
        outline: none;
        text-decoration: none;
        -ms-interpolation-mode: bicubic;
    }

    p {
        display: block;
        margin: 13px 0;
    }
</style>
<!--[if mso]>
    <noscript>
    <xml>
    <o:OfficeDocumentSettings>
      <o:AllowPNG/>
      <o:PixelsPerInch>96</o:PixelsPerInch>
    </o:OfficeDocumentSettings>
    </xml>
    </noscript>
    <![endif]-->
<!--[if lte mso 11]>
    <style type="text/css">
      .mj-outlook-group-fix { width:100% !important; }
    </style>
    <![endif]-->
<style type="text/css">
    @media only screen and (min-width:480px) {
        .mj-column-per-90 {
            width: 90% !important;
            max-width: 90%;
        }
    }
</style>
<style media="screen and (min-width:480px)">
    .moz-text-html .mj-column-per-90 {
        width: 90% !important;
        max-width: 90%;
    }
</style>
<style type="text/css">
    @font-face {
        font-family: 'Poppins';
        font-style: normal;
        font-weight: 400;
        src: url("<?= $base_url ?>/sites/all/themes/bootstrap-keen/fonts/poppins/Poppins-Regular.otf") format("opentype");
    }

    @font-face {
        font-family: 'Poppins';
        font-style: normal;
        font-weight: 600;
        src: url("<?= $base_url ?>/sites/all/themes/bootstrap-keen/fonts/poppins/Poppins-SemiBold.otf") format("opentype");
    }
</style>
<!-- SubHeader -->
<!--[if mso | IE]><table align="center" border="0" cellpadding="0" cellspacing="0" class="" role="presentation" style="width:992px;" width="992" bgcolor="white" ><tr><td style="line-height:0px;font-size:0px;mso-line-height-rule:exactly;"><![endif]-->
<div style="background:white;background-color:white;margin:0px auto;max-width:992px;">
    <table align="center" border="0" cellpadding="0" cellspacing="0" role="presentation" style="background:white;background-color:white;width:100%;">
        <tbody>
            <tr>
                <td style="direction:ltr;font-size:0px;padding:20px 0;padding-bottom:10px;padding-left:10px;padding-top:10px;text-align:center;">
                    <!--[if mso | IE]><table role="presentation" border="0" cellpadding="0" cellspacing="0"><tr><td class="" style="vertical-align:top;width:883.8px;" ><![endif]-->
                    <div class="mj-column-per-90 mj-outlook-group-fix" style="font-size:0px;text-align:left;direction:ltr;display:inline-block;vertical-align:top;width:100%;">
                        <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="vertical-align:top;" width="100%">
                            <tbody>
                                <tr>
                                    <td align="left" style="font-size:0px;padding:10px 25px;padding-left:0;word-break:break-word;">
                                        <div style="font-family:Poppins, Helvetica, Arial, sans-serif;font-size:18px;font-weight:600;line-height:1;text-align:left;color:#000000;"><?= t('Hello', array(), $l) . " " . $recip_name ?></div>
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
<!-- Pass Reset -->
<!--[if mso | IE]><table align="center" border="0" cellpadding="0" cellspacing="0" class="" role="presentation" style="width:992px;" width="992" bgcolor="white" ><tr><td style="line-height:0px;font-size:0px;mso-line-height-rule:exactly;"><![endif]-->
<div style="background:white;background-color:white;margin:0px auto;max-width:992px;">
    <table align="center" border="0" cellpadding="0" cellspacing="0" role="presentation" style="background:white;background-color:white;width:100%;">
        <tbody>
            <tr>
                <td style="direction:ltr;font-size:0px;padding:0;padding-left:10px;padding-top:10px;text-align:center;">
                    <!--[if mso | IE]><table role="presentation" border="0" cellpadding="0" cellspacing="0"><tr><td class="" style="vertical-align:top;width:883.8px;" ><![endif]-->
                    <div class="mj-column-per-90 mj-outlook-group-fix" style="font-size:0px;text-align:left;direction:ltr;display:inline-block;vertical-align:top;width:100%;">
                        <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="background-color:#337ab7;border-radius:5px;vertical-align:top;" width="100%">
                            <tbody>
                                <tr>
                                    <td align="left" style="font-size:0px;padding:10px 25px;word-break:break-word;">
                                        <div style="font-family:Poppins, Helvetica, Arial, sans-serif;font-size:18px;font-weight:600;line-height:1;text-align:left;color:white;">
                                            <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="vertical-align:middle;">
                                                <tbody>
                                                    <tr>
                                                        <td>
                                                            <img src="<?= $base_url ?>/sites/all/modules/gofast/gofast_mail_queue/icon/video-white.png" alt="Information Icon" width="18" />
                                                        </td>
                                                        <td><span style="color: #ffffff; font-size: 18px; font-weight: 600;">&nbsp;<?= t("Meeting", [], $l) ?></span></td>
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
<!--[if mso | IE]></td></tr></table><table align="center" border="0" cellpadding="0" cellspacing="0" class="" role="presentation" style="width:992px;" width="992" bgcolor="white" ><tr><td style="line-height:0px;font-size:0px;mso-line-height-rule:exactly;"><![endif]-->
<div style="background:white;background-color:white;margin:0px auto;max-width:992px;">
    <table align="center" border="0" cellpadding="0" cellspacing="0" role="presentation" style="background:white;background-color:white;width:100%;">
        <tbody>
            <tr>
                <td style="direction:ltr;font-size:0px;padding:0;padding-bottom:10px;padding-left:10px;padding-top:0;text-align:center;">
                    <!--[if mso | IE]><table role="presentation" border="0" cellpadding="0" cellspacing="0"><tr><td class="" style="vertical-align:middle;width:883.8px;" ><![endif]-->
                    <div class="mj-column-per-90 mj-outlook-group-fix" style="font-size:0px;text-align:left;direction:ltr;display:inline-block;vertical-align:middle;width:100%;">
                        <table border="0" cellpadding="0" cellspacing="0" role="presentation" width="100%">
                            <tbody>
                                <tr>
                                    <td style="vertical-align:middle;padding-top:10px;">
                                        <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="" width="100%">
                                            <tbody>
                                                <tr>
                                                    <td align="left" style="font-size:0px;padding:10px 25px;word-break:break-word;">
                                                        <div style="font-family:Poppins, Helvetica, Arial, sans-serif;font-size:14px;font-weight:400;line-height:1;text-align:left;color:#000000;"><?= $message ?></div>
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
                </td>
            </tr>
        </tbody>
    </table>
</div>
<!--[if mso | IE]></td></tr></table><table align="center" border="0" cellpadding="0" cellspacing="0" class="" role="presentation" style="width:992px;" width="992" bgcolor="white" ><tr><td style="line-height:0px;font-size:0px;mso-line-height-rule:exactly;"><![endif]-->
<div style="background:white;background-color:white;margin:0px auto;max-width:992px;">
    <table align="center" border="0" cellpadding="0" cellspacing="0" role="presentation" style="background:white;background-color:white;width:100%;">
        <tbody>
            <tr>
                <td style="direction:ltr;font-size:0px;padding:20px 0;padding-bottom:10px;padding-left:10px;padding-top:10px;text-align:center;">
                    <!--[if mso | IE]><table role="presentation" border="0" cellpadding="0" cellspacing="0"><tr><td class="" style="vertical-align:top;width:883.8px;" ><![endif]-->
                    <div class="mj-column-per-90 mj-outlook-group-fix" style="font-size:0px;text-align:left;direction:ltr;display:inline-block;vertical-align:top;width:100%;">
                        <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="background-color:#de6502;border-radius:5px;vertical-align:top;" width="100%">
                            <tbody>
                                <tr>
                                    <td align="left" style="font-size:0px;padding:10px 25px;word-break:break-word;">
                                        <div style="font-family:Poppins, Helvetica, Arial, sans-serif;font-size:18px;font-weight:600;line-height:1;text-align:left;color:white;">
                                            <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="vertical-align:middle;">
                                                <tbody>
                                                    <tr>
                                                        <td>
                                                            <img src="<?= $base_url ?>/sites/all/modules/gofast/gofast_mail_queue/icon/exclamation-triangle-solid-white.png" alt="Information Icon" width="18" />
                                                        </td>
                                                        <td><span style="color: #FFFFFF; font-size: 18px; font-weight: 600;">&nbsp;<?= t("Warning", [], $l) ?></span></td>
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
<!--[if mso | IE]></td></tr></table><table align="center" border="0" cellpadding="0" cellspacing="0" class="" role="presentation" style="width:992px;" width="992" bgcolor="white" ><tr><td style="line-height:0px;font-size:0px;mso-line-height-rule:exactly;"><![endif]-->
<div style="background:white;background-color:white;margin:0px auto;max-width:992px;">
    <table align="center" border="0" cellpadding="0" cellspacing="0" role="presentation" style="background:white;background-color:white;width:100%;">
        <tbody>
            <tr>
                <td style="direction:ltr;font-size:0px;padding:20px 0;padding-left:10px;padding-top:0;text-align:center;">
                    <!--[if mso | IE]><table role="presentation" border="0" cellpadding="0" cellspacing="0"><tr><td class="" style="vertical-align:middle;width:883.8px;" ><![endif]-->
                    <div class="mj-column-per-90 mj-outlook-group-fix" style="font-size:0px;text-align:left;direction:ltr;display:inline-block;vertical-align:middle;width:100%;">
                        <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="vertical-align:middle;" width="100%">
                            <tbody>
                                <tr>
                                    <td align="left" style="font-size:0px;padding:10px 25px;word-break:break-word;">
                                        <div style="font-family:Poppins, Helvetica, Arial, sans-serif;font-size:14px;font-weight:400;line-height:1;text-align:left;color:#000000;"><?= t("If you use this link several hours after having received this notification, the meeting might have ended.", [], $l) ?>.</div>
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