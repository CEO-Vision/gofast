<!-- FILE: mail_conference_source.mjml -->
<?php global $base_url; ?>
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
    .mj-column-per-100 {
      width: 100% !important;
      max-width: 100%;
    }

    .mj-column-per-25 {
      width: 25% !important;
      max-width: 25%;
    }

    .mj-column-per-50 {
      width: 50% !important;
      max-width: 50%;
    }
  }
</style>
<style media="screen and (min-width:480px)">
  .moz-text-html .mj-column-per-100 {
    width: 100% !important;
    max-width: 100%;
  }

  .moz-text-html .mj-column-per-25 {
    width: 25% !important;
    max-width: 25%;
  }

  .moz-text-html .mj-column-per-50 {
    width: 50% !important;
    max-width: 50%;
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

<!-- SubHeader -->
<!--[if mso | IE]><table align="center" border="0" cellpadding="0" cellspacing="0" class="" role="presentation" style="width:992px;" width="992" bgcolor="white" ><tr><td style="line-height:0px;font-size:0px;mso-line-height-rule:exactly;"><![endif]-->
<div style="background:white;background-color:white;margin:0px auto;max-width:992px;">
  <table align="center" border="0" cellpadding="0" cellspacing="0" role="presentation" style="background:white;background-color:white;width:100%;">
    <tbody>
      <tr>
        <td style="direction:ltr;font-size:0px;padding:0;padding-top:10px;text-align:center;">
          <!--[if mso | IE]><table role="presentation" border="0" cellpadding="0" cellspacing="0"><tr><td class="" style="vertical-align:top;width:992px;" ><![endif]-->
          <div class="mj-column-per-100 mj-outlook-group-fix" style="font-size:0px;text-align:left;direction:ltr;display:inline-block;vertical-align:top;width:100%;">
            <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="vertical-align:top;" width="100%">
              <tbody>
                <tr>
                  <td align="left" style="font-size:0px;padding:10px 25px;word-break:break-word;">
                    <div style="font-family:Poppins, Candara, Helvetica, Arial, sans-serif;font-size:18px;font-weight:600;line-height:1;text-align:left;color:#337ab7;"><?= t("Hello", array(), $l) ?> <?= $recipient_name ?></div>
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
        <td style="direction:ltr;font-size:0px;padding:0;text-align:center;">
          <!--[if mso | IE]><table role="presentation" border="0" cellpadding="0" cellspacing="0"><tr><td class="" style="vertical-align:middle;width:992px;" ><![endif]-->
          <div class="mj-column-per-100 mj-outlook-group-fix" style="font-size:0px;text-align:left;direction:ltr;display:inline-block;vertical-align:middle;width:100%;">
            <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="vertical-align:middle;" width="100%">
              <tbody>
                <tr>
                  <td align="left" style="font-size:0px;padding:10px 25px;word-break:break-word;">
                    <div style="font-family:Poppins, Candara, Helvetica, Arial, sans-serif;font-size:14px;font-weight:400;line-height:1;text-align:left;color:#000000;">
                      <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="vertical-align:middle;">
                        <tbody>
                          <tr>
                            <td>
                              <img src="<?= $base_url . '/' . drupal_get_path('module', 'gofast_mail_queue') . '/icon/' . 'user-solid.png' ?>" alt="<?= t("User Icon", array(), $l) ?>" width="18" />
                            </td>
                            <td>
                              <span style="font-family:Poppins, Candara, Helvetica, Arial, sans-serif; font-size: 14px; font-weight: 400;">&nbsp;<?= t("You are invited to a new @sitename conference", array("@sitename" => variable_get("site_name", "GoFAST")), $l) ?></span>
                            </td>
                          <tr>
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
        <td style="direction:ltr;font-size:0px;padding:0;padding-bottom:10px;text-align:center;">
          <!--[if mso | IE]><table role="presentation" border="0" cellpadding="0" cellspacing="0"><tr><td class="" style="vertical-align:top;width:992px;" ><![endif]-->
          <div class="mj-column-per-100 mj-outlook-group-fix" style="font-size:0px;text-align:left;direction:ltr;display:inline-block;vertical-align:top;width:100%;">
            <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="vertical-align:top;" width="100%">
              <tbody>
                <tr>
                  <td align="center" style="font-size:0px;padding:10px 25px;word-break:break-word;">
                    <p style="border-top:solid 1px #666666;font-size:1px;margin:0px auto;width:100%;">
                    </p>
                    <!--[if mso | IE]><table align="center" border="0" cellpadding="0" cellspacing="0" style="border-top:solid 1px #666666;font-size:1px;margin:0px auto;width:718px;" role="presentation" width="718px" ><tr><td style="height:0;line-height:0;"> &nbsp;
</td></tr></table><![endif]-->
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
<!-- Body -->
<!--[if mso | IE]><table align="center" border="0" cellpadding="0" cellspacing="0" class="" role="presentation" style="width:992px;" width="992" bgcolor="white" ><tr><td style="line-height:0px;font-size:0px;mso-line-height-rule:exactly;"><![endif]-->
<div style="background:white;background-color:white;margin:0px auto;max-width:992px;">
  <table align="center" border="0" cellpadding="0" cellspacing="0" role="presentation" style="background:white;background-color:white;width:100%;">
    <tbody>
      <tr>
        <td style="direction:ltr;font-size:0px;padding:0;text-align:center;">
          <!--[if mso | IE]><table role="presentation" border="0" cellpadding="0" cellspacing="0"><tr><td class="" style="vertical-align:top;width:992px;" ><![endif]-->
          <div class="mj-column-per-100 mj-outlook-group-fix" style="font-size:0px;text-align:left;direction:ltr;display:inline-block;vertical-align:top;width:100%;">
            <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="vertical-align:top;" width="100%">
              <tbody>
                <tr>
                  <td align="left" style="font-size:0px;padding:10px 25px;word-break:break-word;">
                    <div style="font-family:Poppins, Candara, Helvetica, Arial, sans-serif;font-size:18px;font-weight:600;line-height:1;text-align:left;color:#000000;"><?= $conference_title ?></div>
                  </td>
                </tr>
                <?php if (isset($conference_content["subject"])) : ?>
                  <tr>
                    <td align="left" style="font-size:0px;padding:10px 25px;word-break:break-word;">
                      <div style="font-family:Poppins, Candara, Helvetica, Arial, sans-serif;font-size:14px;font-weight:400;line-height:1;text-align:left;color:#000000;"><?= $conference_content["subject"] ?></div>
                    </td>
                  </tr>
                <?php endif; ?>
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
        <td style="direction:ltr;font-size:0px;padding:0;text-align:center;">
          <!--[if mso | IE]><table role="presentation" border="0" cellpadding="0" cellspacing="0"><tr><td class="" style="vertical-align:middle;width:248px;" ><![endif]-->
          <div class="mj-column-per-25 mj-outlook-group-fix" style="font-size:0px;text-align:left;direction:ltr;display:inline-block;vertical-align:middle;width:100%;">
            <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="vertical-align:middle;" width="100%">
              <tbody>
                <tr>
                  <td align="center" style="font-size:0px;padding:0;word-break:break-word;">
                    <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="border-collapse:collapse;border-spacing:0px;">
                      <tbody>
                        <tr>
                          <td style="width:18px;">
                            <img alt="<?= t("Calendar Icon", array(), $l) ?>" height="auto" src="<?= $base_url . '/' . drupal_get_path('module', 'gofast_mail_queue') . '/icon/' . 'calendar-alt-solid.png' ?>" style="border:0;display:block;outline:none;text-decoration:none;height:auto;width:100%;font-size:13px;" width="18" />
                          </td>
                        </tr>
                      </tbody>
                    </table>
                  </td>
                </tr>
                <tr>
                  <td align="center" style="font-size:0px;padding:3px;word-break:break-word;">
                    <div style="font-family:Poppins, Candara, Helvetica, Arial, sans-serif;font-size:14px;line-height:1;text-align:center;color:#000000;"><?= t("Meeting Start", array(), $l) ?></div>
                  </td>
                </tr>
                <tr>
                  <td align="center" style="font-size:0px;padding:3px;word-break:break-word;">
                    <div style="font-family:Poppins, Candara, Helvetica, Arial, sans-serif;font-size:14px;line-height:1;text-align:center;color:#666666;"><?= $conference_datetime ?></div>
                  </td>
                </tr>
              </tbody>
            </table>
          </div>
          <!--[if mso | IE]></td><td class="" style="vertical-align:middle;width:248px;" ><![endif]-->
          <div class="mj-column-per-25 mj-outlook-group-fix" style="font-size:0px;text-align:left;direction:ltr;display:inline-block;vertical-align:middle;width:100%;">
            <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="vertical-align:middle;" width="100%">
              <tbody>
                <tr>
                  <td align="center" style="font-size:0px;padding:0;word-break:break-word;">
                    <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="border-collapse:collapse;border-spacing:0px;">
                      <tbody>
                        <tr>
                          <td style="width:18px;">
                            <img alt="<?= t("Calendar Icon", array(), $l) ?>" height="auto" src="<?= $base_url . '/' . drupal_get_path('module', 'gofast_mail_queue') . '/icon/' . 'calendar-alt-solid.png' ?>" style="border:0;display:block;outline:none;text-decoration:none;height:auto;width:100%;font-size:13px;" width="18" />
                          </td>
                        </tr>
                      </tbody>
                    </table>
                  </td>
                </tr>
                <tr>
                  <td align="center" style="font-size:0px;padding:3px;word-break:break-word;">
                    <div style="font-family:Poppins, Candara, Helvetica, Arial, sans-serif;font-size:14px;line-height:1;text-align:center;color:#000000;"><?= t("Meeting End", array(), $l) ?></div>
                  </td>
                </tr>
                <tr>
                  <td align="center" style="font-size:0px;padding:3px;word-break:break-word;">
                    <div style="font-family:Poppins, Candara, Helvetica, Arial, sans-serif;font-size:14px;line-height:1;text-align:center;color:#666666;"><?= $conference_end_datetime ?></div>
                  </td>
                </tr>
              </tbody>
            </table>
          </div>
          <!--[if mso | IE]></td><td class="" style="vertical-align:middle;width:248px;" ><![endif]-->
          <div class="mj-column-per-25 mj-outlook-group-fix" style="font-size:0px;text-align:left;direction:ltr;display:inline-block;vertical-align:middle;width:100%;">
            <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="vertical-align:middle;" width="100%">
              <tbody>
                <tr>
                  <td align="center" style="font-size:0px;padding:0;word-break:break-word;">
                    <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="border-collapse:collapse;border-spacing:0px;">
                      <tbody>
                        <tr>
                          <td style="width:18px;">
                            <img alt="<?= t("Clock Icon", array(), $l) ?>" height="auto" src="<?= $base_url . '/' . drupal_get_path('module', 'gofast_mail_queue') . '/icon/' . 'clock-regular.png' ?>" style="border:0;display:block;outline:none;text-decoration:none;height:auto;width:100%;font-size:13px;" width="18" />
                          </td>
                        </tr>
                      </tbody>
                    </table>
                  </td>
                </tr>
                <tr>
                  <td align="center" style="font-size:0px;padding:3px;word-break:break-word;">
                    <div style="font-family:Poppins, Candara, Helvetica, Arial, sans-serif;font-size:14px;line-height:1;text-align:center;color:#000000;"><?= t("Duration", array(), $l) ?></div>
                  </td>
                </tr>
                <tr>
                  <td align="center" style="font-size:0px;padding:3px;word-break:break-word;">
                    <div style="font-family:Poppins, Candara, Helvetica, Arial, sans-serif;font-size:14px;line-height:1;text-align:center;color:#666666;"><?= $duration ?></div>
                  </td>
                </tr>
              </tbody>
            </table>
          </div>
          <!--[if mso | IE]></td><td style="vertical-align:middle;width:173px;" ><![endif]-->
          <div class="mj-column-per-25 mj-outlook-group-fix" style="font-size:0px;text-align:left;direction:ltr;display:inline-block;vertical-align:middle;width:25%;">
            <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="vertical-align:middle;" width="100%">
              <tbody>
                <tr>
                  <td align="center" style="font-size:0px;padding:0;word-break:break-word;">
                    <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="border-collapse:collapse;border-spacing:0px;">
                      <tbody>
                        <tr>
                          <td style="width:18px;">
                            <img alt="<?= t("Map Icon", array(), $l) ?>" height="auto" src="<?= $base_url . '/' . drupal_get_path('module', 'gofast_mail_queue') . '/icon/' . 'map-marker-alt-solid.png' ?>" style="border:0;display:block;outline:none;text-decoration:none;height:auto;width:100%;font-size:13px;" width="18" />
                          </td>
                        </tr>
                      </tbody>
                    </table>
                  </td>
                </tr>
                <tr>
                  <td align="center" style="font-size:0px;padding:3px;word-break:break-word;">
                    <div style="font-family:Poppins, Candara, Helvetica, Arial, sans-serif;font-size:14px;line-height:1;text-align:center;color:#000000;"><?= t("Place", [], $l) ?></div>
                  </td>
                </tr>
                <tr>
                  <td align="center" style="font-size:0px;padding:3px;word-break:break-word;">
                    <div style="font-family:Poppins, Candara, Helvetica, Arial, sans-serif;font-size:14px;line-height:1;text-align:center;color:#666666;"><?= $conference_content["place"] ?: t("Online", array(), $l) ?></div>
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
        <td style="direction:ltr;font-size:0px;padding:0;text-align:center;">
          <!--[if mso | IE]><table role="presentation" border="0" cellpadding="0" cellspacing="0"><tr><td class="" style="vertical-align:top;width:992px;" ><![endif]-->
          <div class="mj-column-per-100 mj-outlook-group-fix" style="font-size:0px;text-align:left;direction:ltr;display:inline-block;vertical-align:top;width:100%;">
            <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="vertical-align:top;" width="100%">
              <tbody>
                <tr>
                  <td align="center" style="font-size:0px;padding:10px 25px;word-break:break-word;">
                    <p style="border-top:solid 1px #666666;font-size:1px;margin:0px auto;width:100%;">
                    </p>
                    <!--[if mso | IE]><table align="center" border="0" cellpadding="0" cellspacing="0" style="border-top:solid 1px #666666;font-size:1px;margin:0px auto;width:942px;" role="presentation" width="942px" ><tr><td style="height:0;line-height:0;"> &nbsp;
</td></tr></table><![endif]-->
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
        <td style="direction:ltr;font-size:0px;padding:0;text-align:center;">
          <!--[if mso | IE]><table role="presentation" border="0" cellpadding="0" cellspacing="0"><tr><td class="" style="vertical-align:top;width:496px;" ><![endif]-->
          <div class="mj-column-per-50 mj-outlook-group-fix" style="font-size:0px;text-align:left;direction:ltr;display:inline-block;vertical-align:top;width:100%;">
            <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="vertical-align:top;" width="100%">
              <tbody>
                <tr>
                  <td align="left" style="font-size:0px;padding:10px 25px;word-break:break-word;">
                    <div style="font-family:Poppins, Candara, Helvetica, Arial, sans-serif;font-size:18px;font-weight:600;line-height:1;text-align:left;color:#de6502;"><?= t('Organisator', array(), $l) ?></div>
                  </td>
                </tr>
                <tr>
                  <td align="left" style="font-size:0px;padding:10px 25px;word-break:break-word;">
                    <div style="font-family:Poppins;font-size:14px;line-height:1;text-align:left;color:#000000;">
                      <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="vertical-align:middle;">
                        <tbody>
                          <tr>
                            <td>
                              <img alt="<?= t("Organisator Avatar", array(), $l) ?>" src="<?= $conference_owner->picture ?>" width="40" />
                            </td>
                            <td>
                              <span style="font-family: Poppins; font-size: 14px;">&nbsp;<?= $conference_owner->fullname ?></span>
                            </td>
                          </tr>
                        </tbody>
                      </table>
                      <div style="padding-top: 5px;"><a style="color: #666666;; font-family: Poppins; font-size: 14px; text-decoration: none;" href="mailto:<?= $conference_owner->mail ?>"><?= $conference_owner->mail ?></a></div>
                    </div>
                  </td>
                </tr>
              </tbody>
            </table>
          </div>
          <?php
          $count_all_participants = count($gofast_participants);
          $participants = $gofast_participants;
          // normalize informations for non-GoFAST participants
          if (!empty($other_participants)) {
            $count_all_participants += count($other_participants);
            $participants = array_merge($participants, $other_participants);
          }
          ?>

          <!--[if mso | IE]></td><td class="" style="vertical-align:top;width:496px;" ><![endif]-->
          <div class="mj-column-per-50 mj-outlook-group-fix" style="font-size:0px;text-align:left;direction:ltr;display:inline-block;vertical-align:top;width:100%;">
            <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="vertical-align:top;" width="100%">
              <tbody>
                <tr>
                  <td align="left" style="font-size:0px;padding:10px 25px;word-break:break-word;">
                    <div style="font-family:Poppins, Candara, Helvetica, Arial, sans-serif;font-size:18px;font-weight:600;line-height:1;text-align:left;color:#de6502;"><?= format_plural($count_all_participants, "Participant", "Participants") ?> (<?= $count_all_participants ?>)</div>
                  </td>
                </tr>
                <?php foreach ($participants as $participant) : ?>
                  <tr>
                    <td align="left" style="font-size:0px;padding:10px 25px;word-break:break-word;">
                      <div style="font-family:Poppins, Candara, Arial, sans-serif;font-size:14px;line-height:1;text-align:left;color:#000000;">
                        <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="vertical-align:middle;">
                          <tbody>
                            <tr>
                              <td>
                                <img alt="<?= t("User Avatar", array(), $l) ?>" src="<?= $participant->picture ?>" width="40" />
                              </td>
                              <td>
                                &nbsp;<?= $participant->fullname ?>
                              </td>
                            </tr>
                          </tbody>
                        </table>
                        <div style="padding-top: 5px;"><a style="color: #666666;; font-family:Poppins, Candara, Helvetica, Arial, sans-serif; font-size: 14p; text-decoration: none;" href="<?= $participant->mail ?>"><?= $participant->mail ?></a></div>
                    </td>
                  </tr>
                <?php endforeach; ?>
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
        <td style="direction:ltr;font-size:0px;padding:0;text-align:center;">
          <!--[if mso | IE]><table role="presentation" border="0" cellpadding="0" cellspacing="0"><tr><td class="" style="vertical-align:top;width:992px;" ><![endif]-->
          <div class="mj-column-per-100 mj-outlook-group-fix" style="font-size:0px;text-align:left;direction:ltr;display:inline-block;vertical-align:top;width:100%;">
            <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="vertical-align:top;" width="100%">
              <tbody>
                <tr>
                  <td align="center" style="font-size:0px;padding:10px 25px;word-break:break-word;">
                  <div style="font-family:Poppins;font-size:12px;line-height:1;text-align:center;">
                    <?php if (isset($conference_password)) : ?>
                        <span style="color: #f64e60;">
                            <?php echo t("Conference password : ", array(), $l) ?>
                            <strong style="font-weight:900"><?php echo $conference_password; ?></strong>
                        </span>
                    <?php else: ?>
                        <span><?php echo t("This conference is not locked with a password", array(), $l) ?></span>
                    <?php endif; ?>
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
        <td style="direction:ltr;font-size:0px;padding:0;text-align:center;">
          <!--[if mso | IE]><table role="presentation" border="0" cellpadding="0" cellspacing="0"><tr><td class="" style="vertical-align:top;width:992px;" ><![endif]-->
          <div class="mj-column-per-100 mj-outlook-group-fix" style="font-size:0px;text-align:left;direction:ltr;display:inline-block;vertical-align:top;width:100%;">
            <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="vertical-align:top;" width="100%">
              <tbody>
                <tr>
                  <td align="center" vertical-align="middle" style="font-size:0px;padding:10px 25px;word-break:break-word;">
                    <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="border-collapse:separate;line-height:100%;">
                      <tbody>
                        <tr>
                          <td align="center" bgcolor="#159992" role="presentation" style="border:none;border-radius:5px;cursor:auto;mso-padding-alt:10px 25px;background:#159992;" valign="middle">
                            <a href="<?= $conference_url_external ?>" style="display:inline-block;background:#159992;color:#ffffff;font-family:Poppins, Candara, Helvetica, Arial, sans-serif;font-size:14px;font-weight:600;line-height:120%;margin:0;text-decoration:none;text-transform:none;padding:10px 25px;mso-padding-alt:0px;border-radius:5px;" target="_blank"><?= t('Go to the conference', array(), $l) ?></a>
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
        <td style="direction:ltr;font-size:0px;padding:0;text-align:center;">
          <!--[if mso | IE]><table role="presentation" border="0" cellpadding="0" cellspacing="0"><tr><td class="" style="vertical-align:top;width:992px;" ><![endif]-->
          <div class="mj-column-per-100 mj-outlook-group-fix" style="font-size:0px;text-align:left;direction:ltr;display:inline-block;vertical-align:top;width:100%;">
            <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="vertical-align:top;" width="100%">
              <tbody>
                <tr>
                  <td align="center" style="font-size:0px;padding:10px 25px;word-break:break-word;">
                    <div style="font-family:Poppins;font-size:12px;font-weight:300;line-height:1;text-align:center;color:#666666;">
                      <a href="<?= str_replace(CONFERENCE_URL, "https://meet.jit.si", $conference_url_external); ?>" style="color: #666666; text-decoration: none;"><?= t("If you find any problems, all participants can try to use this link (shared Jitsi SaaS)", array(), $l); ?></a>
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
<?php if (strlen($conference_documents > 0) || strlen($conference_folders) > 0) : ?>
  <!--[if mso | IE]></td></tr></table><table align="center" border="0" cellpadding="0" cellspacing="0" class="" role="presentation" style="width:992px;" width="992" bgcolor="white" ><tr><td style="line-height:0px;font-size:0px;mso-line-height-rule:exactly;"><![endif]-->
  <div style="background:white;background-color:white;margin:0px auto;max-width:992px;">
    <table align="center" border="0" cellpadding="0" cellspacing="0" role="presentation" style="background:white;background-color:white;width:100%;">
      <tbody>
        <tr>
          <td style="direction:ltr;font-size:0px;padding:0;text-align:center;">
            <!--[if mso | IE]><table role="presentation" border="0" cellpadding="0" cellspacing="0"><tr><td class="" style="vertical-align:top;width:992px;" ><![endif]-->
            <div class="mj-column-per-100 mj-outlook-group-fix" style="font-size:0px;text-align:left;direction:ltr;display:inline-block;vertical-align:top;width:100%;">
              <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="vertical-align:top;" width="100%">
                <tbody>
                  <tr>
                    <td align="center" style="font-size:0px;padding:10px 25px;word-break:break-word;">
                      <p style="border-top:solid 1px #666666;font-size:1px;margin:0px auto;width:100%;">
                      </p>
                      <!--[if mso | IE]><table align="center" border="0" cellpadding="0" cellspacing="0" style="border-top:solid 1px #666666;font-size:1px;margin:0px auto;width:942px;" role="presentation" width="942px" ><tr><td style="height:0;line-height:0;"> &nbsp;
</td></tr></table><![endif]-->
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
<?php endif; ?>
<?php if (strlen($conference_documents) > 0) : ?>
  <!--[if mso | IE]></td></tr></table><table align="center" border="0" cellpadding="0" cellspacing="0" class="" role="presentation" style="width:992px;" width="992" bgcolor="white" ><tr><td style="line-height:0px;font-size:0px;mso-line-height-rule:exactly;"><![endif]-->
  <div style="background:white;background-color:white;margin:0px auto;max-width:992px;">
    <table align="center" border="0" cellpadding="0" cellspacing="0" role="presentation" style="background:white;background-color:white;width:100%;">
      <tbody>
        <tr>
          <td style="direction:ltr;font-size:0px;padding:0;text-align:center;">
            <!--[if mso | IE]><table role="presentation" border="0" cellpadding="0" cellspacing="0"><tr><td class="" style="vertical-align:top;width:992px;" ><![endif]-->
            <div class="mj-column-per-100 mj-outlook-group-fix" style="font-size:0px;text-align:left;direction:ltr;display:inline-block;vertical-align:top;width:100%;">
              <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="vertical-align:top;" width="100%">
                <tbody>
                  <tr>
                    <td align="left" style="font-size:0px;padding:10px 25px;word-break:break-word;">
                      <div style="font-family:Poppins, Candara, Helvetica, Arial, sans-serif;font-size:18px;font-weight:600;line-height:1;text-align:left;color:#000000;"><?= t("Documents: ", array(), $l) ?></div>
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
          <td style="direction:ltr;font-size:0px;padding:0;text-align:center;">
            <!--[if mso | IE]><table role="presentation" border="0" cellpadding="0" cellspacing="0"><tr><td class="" style="vertical-align:top;width:992px;" ><![endif]-->
            <div class="mj-column-per-100 mj-outlook-group-fix" style="font-size:0px;text-align:left;direction:ltr;display:inline-block;vertical-align:top;width:100%;">
              <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="vertical-align:top;" width="100%">
                <tbody>
                  <tr>
                    <td align="left" style="font-size:0px;padding:10px 25px;word-break:break-word;">
                      <div style="font-family:Poppins, Candara, Helvetica, Arial, sans-serif;font-size:14px;line-height:1;text-align:left;color:#000000;"><?= $conference_documents ?></div>
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
<?php endif; ?>
<?php if (strlen($conference_folders) > 0) : ?>
  <!--[if mso | IE]></td></tr></table><table align="center" border="0" cellpadding="0" cellspacing="0" class="" role="presentation" style="width:992px;" width="992" bgcolor="white" ><tr><td style="line-height:0px;font-size:0px;mso-line-height-rule:exactly;"><![endif]-->
  <div style="background:white;background-color:white;margin:0px auto;max-width:992px;">
    <table align="center" border="0" cellpadding="0" cellspacing="0" role="presentation" style="background:white;background-color:white;width:100%;">
      <tbody>
        <tr>
          <td style="direction:ltr;font-size:0px;padding:0;text-align:center;">
            <!--[if mso | IE]><table role="presentation" border="0" cellpadding="0" cellspacing="0"><tr><td class="" style="vertical-align:top;width:992px;" ><![endif]-->
            <div class="mj-column-per-100 mj-outlook-group-fix" style="font-size:0px;text-align:left;direction:ltr;display:inline-block;vertical-align:top;width:100%;">
              <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="vertical-align:top;" width="100%">
                <tbody>
                  <tr>
                    <td align="left" style="font-size:0px;padding:10px 25px;word-break:break-word;">
                      <div style="font-family:Poppins, Candara, Helvetica, Arial, sans-serif;font-size:18px;font-weight:600;line-height:1;text-align:left;color:#000000;"><?= t("Folders: ", array(), $l) ?></div>
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
          <td style="direction:ltr;font-size:0px;padding:0;text-align:center;">
            <!--[if mso | IE]><table role="presentation" border="0" cellpadding="0" cellspacing="0"><tr><td class="" style="vertical-align:top;width:992px;" ><![endif]-->
            <div class="mj-column-per-100 mj-outlook-group-fix" style="font-size:0px;text-align:left;direction:ltr;display:inline-block;vertical-align:top;width:100%;">
              <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="vertical-align:top;" width="100%">
                <tbody>
                  <tr>
                    <td align="left" style="font-size:0px;padding:10px 25px;word-break:break-word;">
                      <div style="font-family:Poppins, Candara, Helvetica, Arial, sans-serif;font-size:14px;line-height:1;text-align:left;color:#000000;"><?= $conference_folders ?></div>
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
<?php endif; ?>
<!--[if mso | IE]></td></tr></table><![endif]-->