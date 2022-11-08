<!-- FILE: mail_multi_link_sharing_source.mjml -->
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
                    <div style="font-family:Poppins, Candara, Helvetica, Arial, sans-serif;font-size:18px;font-weight:600;line-height:1;text-align:left;color:#000000;"><?= t('Hello', array(), $l) . " " . $recip_name ?></div>
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
<!-- File Sharing-->
<!--[if mso | IE]><table align="center" border="0" cellpadding="0" cellspacing="0" class="" role="presentation" style="width:992px;" width="992" bgcolor="white" ><tr><td style="line-height:0px;font-size:0px;mso-line-height-rule:exactly;"><![endif]-->
<div style="background:white;background-color:white;margin:0px auto;max-width:992px;">
  <table align="center" border="0" cellpadding="0" cellspacing="0" role="presentation" style="background:white;background-color:white;width:100%;">
    <tbody>
      <tr>
        <td style="direction:ltr;font-size:0px;padding:20px 0;padding-bottom:10px;padding-left:10px;padding-top:0px;text-align:center;">
        <?php if (!isset($is_author)) : ?>
          <!--[if mso | IE]><table role="presentation" border="0" cellpadding="0" cellspacing="0"><tr><td class="" style="width:883.8px;" ><![endif]-->
          <div class="mj-column-per-90 mj-outlook-group-fix" style="font-size:0;line-height:0;text-align:left;display:inline-block;width:100%;direction:ltr;">
            <!--[if mso | IE]><table border="0" cellpadding="0" cellspacing="0" role="presentation" ><tr><td style="vertical-align:middle;width:68px;" ><![endif]-->
            <div class="mj-column-per-10 mj-outlook-group-fix" style="font-size:0px;text-align:left;direction:ltr;display:inline-block;vertical-align:middle;width:10%;">
              <table border="0" cellpadding="0" cellspacing="0" role="presentation" width="100%">
                <tbody>
                  <tr>
                    <td style="vertical-align:middle;padding-top:10px;">
                      <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="" width="100%">
                        <tbody>
                          <tr>
                            <td align="left" style="font-size:0px;padding:0;word-break:break-word;">
                              <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="border-collapse:collapse;border-spacing:0px;">
                                <tbody>
                                  <tr>
                                    <td style="width:68px;">
                                      <?= $author_pic ?>
                                    </td>
                                  </tr>
                                </tbody>
                              </table>
                            </td>
                          </tr>
                        </tbody>
                      </table>
                    </td>
                  </tr>
                </tbody>
              </table>
            </div>
            <!--[if mso | IE]></td><td style="vertical-align:middle;width:613px;" ><![endif]-->
            <div class="mj-column-per-90 mj-outlook-group-fix" style="font-size:0px;text-align:left;direction:ltr;display:inline-block;vertical-align:middle;width:90%;">
              <table border="0" cellpadding="0" cellspacing="0" role="presentation" width="100%">
                <tbody>
                  <tr>
                    <td style="vertical-align:middle;padding-top:10px;">
                      <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="" width="100%">
                        <tbody>
                          <tr>
                            <td align="left" style="font-size:0px;padding:10px 25px;word-break:break-word;">
                              <div style="font-family:Poppins, Candara, Helvetica, Arial, sans-serif;font-size:14px;font-weight:400;line-height:1;text-align:left;color:#000000;"><?= $author_name . " " . format_plural(count($nodes_informations), "shared one file with you", "shared @count files with you") ?></div>
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
          </div>
          <?php endif; ?>
          <!--[if mso | IE]></td></tr></table><![endif]-->
        </td>
      </tr>
    </tbody>
  </table>
</div>
<!--[if mso | IE]><table align="center" border="0" cellpadding="0" cellspacing="0" class="" role="presentation" style="width:992px;" width="992" bgcolor="white" ><tr><td style="line-height:0px;font-size:0px;mso-line-height-rule:exactly;"><![endif]-->
<div style="background:white;background-color:white;margin:0px auto;max-width:992px;">
  <table align="center" border="0" cellpadding="0" cellspacing="0" role="presentation" style="background:white;background-color:white;width:100%;">
    <tbody>
      <tr>
        <td style="direction:ltr;font-size:0px;padding:20px 0;padding-bottom:10px;padding-left:10px;padding-top:0px;text-align:center;">
          <!--[if mso | IE]><table role="presentation" border="0" cellpadding="0" cellspacing="0"><tr><td class="" style="vertical-align:top;width:883.8px;" ><![endif]-->
          <div class="mj-column-per-90 mj-outlook-group-fix" style="font-size:0px;text-align:left;direction:ltr;display:inline-block;vertical-align:top;width:100%;">
            <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="background-color:#de6502;border-radius:5px;vertical-align:top;" width="100%">
              <tbody>
                <tr>
                  <td align="left" style="font-size:0px;padding:10px 25px;word-break:break-word;">
                    <div style="font-family:Poppins, Candara, Helvetica, Arial, sans-serif;font-size:18px;font-weight:600;line-height:1;text-align:left;color:white;">
                      <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="vertical-align:middle;">
                        <tbody>
                          <tr>
                            <td>
                              <img src="<?= $base_url . '/' . drupal_get_path('module', 'gofast_mail_queue') . '/icon/' . 'share-white.png' ?>" alt="<?= t("Information Icon", array(), array("context" => "gofast:gofast")) ?>" width="18" />
                            </td>
                            <td><span style="color: #FFFFFF; font-size: 18px; font-weight: 600;">&nbsp;
                                <?= t('Documents', array(), $l) ?></span></td>
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
        <td style="direction:ltr;font-size:0px;padding:0;padding-bottom:10px;padding-left:10px;padding-top:0px;text-align:center;">
          <!--[if mso | IE]><table role="presentation" border="0" cellpadding="0" cellspacing="0"><tr><td class="" style="vertical-align:middle;width:883.8px;" ><![endif]-->
          <div class="mj-column-per-90 mj-outlook-group-fix" style="font-size:0px;text-align:left;direction:ltr;display:inline-block;vertical-align:middle;width:100%;">
            <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="vertical-align:middle;" width="100%">
              <tbody>
                <?php foreach ($nodes_informations as $node_informations) : ?>
                  <tr>
                    <td align="left" style="font-size:0px;padding:10px 25px;padding-top:0;padding-bottom:5px;word-break:break-word;">
                      <div style="font-family:Poppins, Candara, Helvetica, Arial, sans-serif;font-size:14px;font-weight:400;line-height:1;text-align:left;color:#000000;">
                        <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="vertical-align:middle;">
                          <tbody>
                            <tr>
                              <td><a href="<?= $node_informations['url'] ?>" style="text-decoration: none;" color="#337ab7"><?= $node_informations['icon'] ?><?= $node_informations['title'] ?></a> <span style="font-size: 14px; font-weight: 400; color: #666666;">&nbsp;<?= t("Version", array(), array('context' => 'gofast:gofast_linksharing')) . " " . $node_informations['version'] ?></span>
                              </td>
                            </tr>
                          </tbody>
                        </table>
                      </div>
                    </td>
                  </tr>
                  <tr>
                  <?php endforeach; ?>
                  <?php if (!isset($is_author)) : ?>
                  <tr>
                    <td align="center" vertical-align="middle" style="font-size:0px;padding:10px 25px;word-break:break-word;">
                      <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="border-collapse:separate;line-height:100%;">
                        <tbody>
                          <tr>
                            <td align="center" bgcolor="#159992" role="presentation" style="border:none;border-radius:5px;cursor:auto;mso-padding-alt:10px 25px;background:#159992;" valign="middle">
                              <a href="<?= $download ?>" style="display:inline-block;background:#1BC5BD;color:white;font-family:Poppins, Candara, Helvetica, Arial, sans-serif;font-size:14px;font-weight:400;line-height:120%;margin:0;text-decoration:none;text-transform:none;padding:10px 25px;mso-padding-alt:0px;border-radius:5px;" target="_blank"><?= t('Download documents here', array(), $l) ?></a>
                            </td>
                          </tr>
                        </tbody>
                      </table>
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
<?php if (strlen($message) > 0) : ?>
  <!--[if mso | IE]></td></tr></table><table align="center" border="0" cellpadding="0" cellspacing="0" class="" role="presentation" style="width:992px;" width="992" bgcolor="white" ><tr><td style="line-height:0px;font-size:0px;mso-line-height-rule:exactly;"><![endif]-->
  <div style="background:white;background-color:white;margin:0px auto;max-width:992px;">
    <table align="center" border="0" cellpadding="0" cellspacing="0" role="presentation" style="background:white;background-color:white;width:100%;">
      <tbody>
        <tr>
          <td style="direction:ltr;font-size:0px;padding:0;padding-left:10px;padding-top:10px;text-align:center;">
            <!--[if mso | IE]><table role="presentation" border="0" cellpadding="0" cellspacing="0"><tr><td class="" style="vertical-align:top;width:883.8px;" ><![endif]-->
            <div class="mj-column-per-90 mj-outlook-group-fix" style="font-size:0px;text-align:left;direction:ltr;display:inline-block;vertical-align:top;width:100%;">
              <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="background-color:#F3F6F9;border-radius:5px;vertical-align:top;" width="100%">
                <tbody>
                  <tr>
                    <td align="left" style="font-size:0px;padding:10px 25px;word-break:break-word;">
                      <div style="font-family:Poppins, Candara, Helvetica, Arial, sans-serif;font-size:18px;font-weight:600;line-height:1;text-align:left;color:#3699ff;">
                        <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="vertical-align:middle;">
                          <tbody>
                            <tr>
                              <td>
                                <img src="<?= $base_url . '/' . drupal_get_path('module', 'gofast_mail_queue') . '/icon/' . 'scroll-solid-primary.png' ?>" alt="<?= t("Information Icon", array(), array("context" => "gofast:gofast")) ?>" width="18" />
                              </td>
                              <td><span style="color: #3699ff; font-size: 18px; font-weight: 600;">&nbsp;<?= t('Message', array(), $l) ?>
                                </span></td>
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
          <td style="direction:ltr;font-size:0px;padding:0;padding-bottom:10px;padding-left:10px;padding-top:10px;text-align:center;">
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
                              <div style="font-family:Poppins, Candara, Helvetica, Arial, sans-serif;font-size:14px;font-weight:400;line-height:1;text-align:left;color:#000000;"><?= $message ?></div>
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
<?php endif; ?>
<?php if (isset($mail_list) && count($mail_list) > 1) : ?>
  <!--[if mso | IE]></td></tr></table><table align="center" border="0" cellpadding="0" cellspacing="0" class="" role="presentation" style="width:992px;" width="992" bgcolor="white" ><tr><td style="line-height:0px;font-size:0px;mso-line-height-rule:exactly;"><![endif]-->
  <div style="background:white;background-color:white;margin:0px auto;max-width:992px;">
    <table align="center" border="0" cellpadding="0" cellspacing="0" role="presentation" style="background:white;background-color:white;width:100%;">
      <tbody>
        <tr>
          <td style="direction:ltr;font-size:0px;padding:0;padding-left:10px;padding-top:10px;text-align:center;">
            <!--[if mso | IE]><table role="presentation" border="0" cellpadding="0" cellspacing="0"><tr><td class="" style="vertical-align:top;width:883.8px;" ><![endif]-->
            <div class="mj-column-per-90 mj-outlook-group-fix" style="font-size:0px;text-align:left;direction:ltr;display:inline-block;vertical-align:top;width:100%;">
              <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="background-color:#F3F6F9;border-radius:5px;vertical-align:top;" width="100%">
                <tbody>
                  <tr>
                    <td align="left" style="font-size:0px;padding:10px 25px;word-break:break-word;">
                      <div style="font-family:Poppins, Candara, Helvetica, Arial, sans-serif;font-size:18px;font-weight:600;line-height:1;text-align:left;color:#3699ff;">
                        <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="vertical-align:middle;">
                          <tbody>
                            <tr>
                              <td>
                                <img src="<?= $base_url . '/' . drupal_get_path('module', 'gofast_mail_queue') . '/icon/' . 'scroll-solid-primary.png' ?>" alt="<?= t("Information Icon", array(), array("context" => "gofast:gofast")) ?>" width="18" />
                              </td>
                              <td><span style="color: #3699ff; font-size: 18px; font-weight: 600;">&nbsp;<?= t("Other recipients", array(), array("context" => "gofast:gofast_link_sharing")) ?></span>
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
  <!--[if mso | IE]></td></tr></table><table align="center" border="0" cellpadding="0" cellspacing="0" class="" role="presentation" style="width:992px;" width="992" bgcolor="white" ><tr><td style="line-height:0px;font-size:0px;mso-line-height-rule:exactly;"><![endif]-->
  <div style="background:white;background-color:white;margin:0px auto;max-width:992px;">
    <table align="center" border="0" cellpadding="0" cellspacing="0" role="presentation" style="background:white;background-color:white;width:100%;">
      <tbody>
        <tr>
          <td style="direction:ltr;font-size:0px;padding:0;padding-left:10px;padding-top:10px;text-align:center;">
            <!--[if mso | IE]><table role="presentation" border="0" cellpadding="0" cellspacing="0"><tr><td class="" style="vertical-align:middle;width:883.8px;" ><![endif]-->
            <div class="mj-column-per-90 mj-outlook-group-fix" style="font-size:0px;text-align:left;direction:ltr;display:inline-block;vertical-align:middle;width:100%;">
              <div class="mj-column-per-90 mj-outlook-group-fix" style="font-size:0px;text-align:left;direction:ltr;display:inline-block;vertical-align:middle;width:100%;">
                <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="vertical-align:middle;" width="100%">
                  <tbody>
                    <?php
                    $mail_loop_count = 1;
                    foreach ($mail_list as $mail) : ?>
                      <tr>
                        <td align="left" style="font-size:0px;padding:10px 25px;padding-top:0;padding-bottom:5px;word-break:break-word;">
                          <div style="font-family:Poppins, Candara, Helvetica, Arial, sans-serif;font-size:14px;font-weight:400;line-height:1;text-align:left;color:#000000;">
                            <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="vertical-align:middle;">
                              <tbody>
                                <tr>
                                  <td>
                                    <img src="<?= $base_url . '/' . drupal_get_path('module', 'gofast_mail_queue') . '/icon/' . 'arrow-right-solid-muted.png' ?>" width="14" />
                                  <td><a href="mailto:<?= $mail ?>" style="color: #337ab7; text-decoration: none;">&nbsp;<?= $mail ?></a></td>
                                </tr>
                              </tbody>
                            </table>
                          </div>
                        </td>
                      </tr>
                    <?php
                      $mail_loop_count++;
                    endforeach; ?>
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
<!--[if mso | IE]></td></tr></table><table align="center" border="0" cellpadding="0" cellspacing="0" class="" role="presentation" style="width:992px;" width="992" bgcolor="white" ><tr><td style="line-height:0px;font-size:0px;mso-line-height-rule:exactly;"><![endif]-->
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
                    <div style="font-family:Poppins, Candara, Helvetica, Arial, sans-serif;font-size:18px;font-weight:600;line-height:1;text-align:left;color:white;">
                      <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="vertical-align:middle;">
                        <tbody>
                          <tr>
                            <td>
                              <img src="<?= $base_url . '/' . drupal_get_path('module', 'gofast_mail_queue') . '/icon/' . 'info-circle-solid-white.png' ?>" alt="<?= t("Information Icon", array(), array("context" => "gofast:gofast")) ?>" width="18" style="vertical-align: middle;" />
                            </td>
                            <td><span style="color: #ffffff; font-size: 18px; font-weight: 600;">&nbsp;<?= t("Informations", array(), array("context" => "gofast")) ?></span>
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
<!--[if mso | IE]></td></tr></table><table align="center" border="0" cellpadding="0" cellspacing="0" class="" role="presentation" style="width:992px;" width="992" bgcolor="white" ><tr><td style="line-height:0px;font-size:0px;mso-line-height-rule:exactly;"><![endif]-->
<div style="background:white;background-color:white;margin:0px auto;max-width:992px;">
  <table align="center" border="0" cellpadding="0" cellspacing="0" role="presentation" style="background:white;background-color:white;width:100%;">
    <tbody>
      <tr>
        <td style="direction:ltr;font-size:0px;padding:0;padding-bottom:10px;padding-left:10px;padding-top:10px;text-align:center;">
          <!--[if mso | IE]><table role="presentation" border="0" cellpadding="0" cellspacing="0"><tr><td class="" style="vertical-align:middle;width:883.8px;" ><![endif]-->
          <div class="mj-column-per-90 mj-outlook-group-fix" style="font-size:0px;text-align:left;direction:ltr;display:inline-block;vertical-align:middle;width:100%;">
            <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="vertical-align:middle;" width="100%">
              <tbody>
                <tr>
                  <td align="left" style="font-size:0px;padding:10px 25px;word-break:break-word;">
                    <div style="font-family:Poppins, Candara, Helvetica, Arial, sans-serif;font-size:14px;font-weight:400;line-height:1;text-align:left;color:#000000;"><?= t('If you want, you can download the file and edit it.', array(), $l) ?> <?= $expiry_msg ?></div>
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