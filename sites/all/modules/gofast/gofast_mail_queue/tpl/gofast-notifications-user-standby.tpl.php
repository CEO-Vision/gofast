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
<style type="text/css">
  @media only screen and (min-width:480px) {
    .mj-column-per-90 {
      width: 90% !important;
      max-width: 90%;
    }

    .mj-column-per-10 {
      width: 10% !important;
      max-width: 10%;
    }
  }
</style>
<style media="screen and (min-width:480px)">
  .moz-text-html .mj-column-per-90 {
    width: 90% !important;
    max-width: 90%;
  }

  .moz-text-html .mj-column-per-10 {
    width: 10% !important;
    max-width: 10%;
  }
</style>
<style type="text/css">
  @media only screen and (max-width:480px) {
    table.mj-full-width-mobile {
      width: 100% !important;
    }

    td.mj-full-width-mobile {
      width: auto !important;
    }
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

<?php global $base_url; ?>
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
                    <div style="font-family:Poppins, Candara, Helvetica, Arial, sans-serif;font-size:18px;font-weight:600;line-height:1;text-align:left;color:#000000;"><?= t("Hello @name,", array("@name" => $user_name), array("context" => "gofast:gofast_user")); ?></div>
                  </td>
                </tr>
                <tr align="left" style="font-size:0px;padding:10px 25px;word-break:break-word;">
                  <td>
                    <div style="font-family:Poppins, Candara, Helvetica, Arial, sans-serif;font-size:14px;font-weight:400;line-height:1;text-align:left;color:#000000;"><?= $sub_title ?>.</div>
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
                <td style="direction:ltr;font-size:0px;padding:0;padding-left:10px;text-align:center;">
                    <!--[if mso | IE]><table role="presentation" border="0" cellpadding="0" cellspacing="0"><tr><td class="" style="vertical-align:top;width:883.8px;" ><![endif]-->
                    <div class="mj-column-per-90 mj-outlook-group-fix" style="font-size:0px;text-align:left;direction:ltr;display:inline-block;vertical-align:top;width:100%;">
                        <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="background-color:#337ab7;border-radius:10px 10px 0 0;vertical-align:top;" width="100%">
                            <tbody>
                                <tr>
                                    <td align="left" style="font-size:0px;padding:10px 25px;word-break:break-word;">
                                        <div style="font-family:Poppins, Candara, Helvetica, Arial, sans-serif;font-size:18px;font-weight:600;line-height:1;text-align:left;color:white;">
                                            <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="vertical-align:middle;">
                                                <tbody>
                                                    <tr>
                                                        <td>
                                                            <img src="<?= $base_url . '/' . drupal_get_path('module', 'gofast_mail_queue') . '/icon/' . 'info-circle-solid-white.png' ?>" alt="<?= t("Information Icon", array(), array("langcode" => $recpt->language, "context" => "gofast:gofast_user")) ?>" width="18" style="vertical-align: bottom;" />
                                                        </td>
                                                        <td><span style="color: #FFFFFF; font-size: 18px; font-weight: 600;">&nbsp;<?= t("Standby user(s) :", array(), array("langcode" => $recpt->language, "context" => "gofast:gofast_user")) ?></td>
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
                <td style="direction:ltr;font-size:0px;padding:0;padding-left:10px;text-align:center;">
                    <!--[if mso | IE]><table role="presentation" border="0" cellpadding="0" cellspacing="0"><tr><td class="" style="width:883.8px;" ><![endif]-->
                    <div class="mj-column-per-90 mj-outlook-group-fix" style="font-size:0;line-height:0;text-align:left;display:inline-block;width:100%;direction:ltr;background-color:#666666;">
                        <!--[if mso | IE]><table bgcolor="#666666" border="0" cellpadding="0" cellspacing="0" role="presentation" ><tr><td style="vertical-align:top;width:176px;" ><![endif]-->
                        <div class="mj-column-per-20 mj-outlook-group-fix" style="font-size:0px;text-align:left;direction:ltr;display:inline-block;vertical-align:top;width:20%;">
                            <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="vertical-align:top;" width="100%">
                                <tbody>
                                    <tr>
                                        <td align="left" style="font-size:0px;padding:10px;word-break:break-word;">
                                            <div style="font-family:Poppins;font-size:14px;font-weight:600;line-height:1;text-align:left;color:white;"><?= t("First Name", array(), array("langcode" => $recpt->language, "context" => "gofast:gofast_user")) ?></div>
                                        </td>
                                    </tr>
                                </tbody>
                            </table>
                        </div>
                        <!--[if mso | IE]></td><td style="vertical-align:top;width:176px;" ><![endif]-->
                        <div class="mj-column-per-20 mj-outlook-group-fix" style="font-size:0px;text-align:left;direction:ltr;display:inline-block;vertical-align:top;width:20%;">
                            <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="vertical-align:top;" width="100%">
                                <tbody>
                                    <tr>
                                        <td align="left" style="font-size:0px;padding:10px;word-break:break-word;">
                                            <div style="font-family:Poppins;font-size:14px;font-weight:600;line-height:1;text-align:left;color:white;"><?= t("Last Name", array(), array("langcode" => $recpt->language, "context" => "gofast:gofast_user")) ?></div>
                                        </td>
                                    </tr>
                                </tbody>
                            </table>
                        </div>
                        <!--[if mso | IE]></td><td style="vertical-align:top;width:265px;" ><![endif]-->
                        <div class="mj-column-per-30 mj-outlook-group-fix" style="font-size:0px;text-align:left;direction:ltr;display:inline-block;vertical-align:top;width:30%;">
                            <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="vertical-align:top;" width="100%">
                                <tbody>
                                    <tr>
                                        <td align="left" style="font-size:0px;padding:10px;word-break:break-word;">
                                            <div style="font-family:Poppins;font-size:14px;font-weight:600;line-height:1;text-align:left;color:white;"><?= t("Username", array(), array("langcode" => $recpt->language, "context" => "gofast:gofast_user")) ?></div>
                                        </td>
                                    </tr>
                                </tbody>
                            </table>
                        </div>
                        <!--[if mso | IE]></td><td style="vertical-align:top;width:265px;" ><![endif]-->
                        <div class="mj-column-per-30 mj-outlook-group-fix" style="font-size:0px;text-align:left;direction:ltr;display:inline-block;vertical-align:top;width:30%;">
                            <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="vertical-align:top;" width="100%">
                                <tbody>
                                    <tr>
                                        <td align="left" style="font-size:0px;padding:10px;word-break:break-word;">
                                            <div style="font-family:Poppins;font-size:14px;font-weight:600;line-height:1;text-align:left;color:white;"><?= t("Email", array(), array("langcode" => $recpt->language, "context" => "gofast:gofast_user")) ?></div>
                                        </td>
                                    </tr>
                                </tbody>
                            </table>
                        </div>
                        <!--[if mso | IE]></td></tr></table><![endif]-->
                    </div>
                    <!--[if mso | IE]></td></tr></table><![endif]-->
                </td>
            </tr>
        </tbody>
    </table>
</div>
<?php foreach ($users as $user) : ?>
    <!--[if mso | IE]></td></tr></table><table align="center" border="0" cellpadding="0" cellspacing="0" class="" role="presentation" style="width:992px;" width="992" bgcolor="white" ><tr><td style="line-height:0px;font-size:0px;mso-line-height-rule:exactly;"><![endif]-->
    <div style="background:white;background-color:white;margin:0px auto;max-width:992px;">
        <table align="center" border="0" cellpadding="0" cellspacing="0" role="presentation" style="background:white;background-color:white;width:100%;">
            <tbody>
                <tr>
                    <td style="direction:ltr;font-size:0px;padding:0;padding-left:10px;text-align:center;">
                        <!--[if mso | IE]><table role="presentation" border="0" cellpadding="0" cellspacing="0"><tr><td class="" style="width:883.8px;" ><![endif]-->
                        <div class="mj-column-per-90 mj-outlook-group-fix" style="font-size:0;line-height:0;text-align:left;display:inline-block;width:100%;direction:ltr;">
                            <!--[if mso | IE]><table border="0" cellpadding="0" cellspacing="0" role="presentation" ><tr><td style="vertical-align:top;width:176px;" ><![endif]-->
                            <div class="mj-column-per-20 mj-outlook-group-fix" style="font-size:0px;text-align:left;direction:ltr;display:inline-block;vertical-align:top;width:20%;">
                                <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="vertical-align:top;" width="100%">
                                    <tbody>
                                        <tr>
                                            <td align="left" style="font-size:0px;padding:10px;word-break:break-word;">
                                                <div style="font-family:Poppins;font-size:14px;font-weight:400;line-height:1;text-align:left;color:#000000;"><?= $user->ldap_user_givenname[LANGUAGE_NONE][0]['value']; ?></div>
                                            </td>
                                        </tr>
                                    </tbody>
                                </table>
                            </div>
                            <!--[if mso | IE]></td><td style="vertical-align:top;width:176px;" ><![endif]-->
                            <div class="mj-column-per-20 mj-outlook-group-fix" style="font-size:0px;text-align:left;direction:ltr;display:inline-block;vertical-align:top;width:20%;">
                                <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="vertical-align:top;" width="100%">
                                    <tbody>
                                        <tr>
                                            <td align="left" style="font-size:0px;padding:10px;word-break:break-word;">
                                                <div style="font-family:Poppins;font-size:14px;font-weight:600;line-height:1;text-align:left;color:#000000;"><?= $user->ldap_user_sn[LANGUAGE_NONE][0]['value']; ?></div>
                                            </td>
                                        </tr>
                                    </tbody>
                                </table>
                            </div>
                            <!--[if mso | IE]></td><td style="vertical-align:top;width:265px;" ><![endif]-->
                            <div class="mj-column-per-30 mj-outlook-group-fix" style="font-size:0px;text-align:left;direction:ltr;display:inline-block;vertical-align:top;width:30%;">
                                <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="vertical-align:top;" width="100%">
                                    <tbody>
                                        <tr>
                                            <td align="left" style="font-size:0px;padding:10px;word-break:break-word;">
                                                <div style="font-family:Poppins;font-size:14px;font-weight:400;line-height:1;text-align:left;color:#000000;"><?= $user->name ?></div>
                                            </td>
                                        </tr>
                                    </tbody>
                                </table>
                            </div>
                            <!--[if mso | IE]></td><td style="vertical-align:top;width:265px;" ><![endif]-->
                            <div class="mj-column-per-30 mj-outlook-group-fix" style="font-size:0px;text-align:left;direction:ltr;display:inline-block;vertical-align:top;width:30%;">
                                <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="vertical-align:top;" width="100%">
                                    <tbody>
                                        <tr>
                                            <td align="left" style="font-size:0px;padding:10px;word-break:break-word;">
                                                <div style="font-family:Poppins;font-size:14px;line-height:1;text-align:left;color:#000000;"><?= $user->mail ?></div>
                                            </td>
                                        </tr>
                                    </tbody>
                                </table>
                            </div>
                            <!--[if mso | IE]></td></tr></table><![endif]-->
                        </div>
                        <!--[if mso | IE]></td></tr></table><![endif]-->
                    </td>
                </tr>
            </tbody>
        </table>
    </div>
<?php endforeach; ?>