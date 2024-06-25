<?php if (!empty($title) && !empty($description)) : ?>
<!--[if mso | IE]></td></tr></table><![endif]-->
<!-- Notif details -->
<!--[if mso | IE]><table align="center" border="0" cellpadding="0" cellspacing="0" class="" role="presentation" style="width:992px;" width="992" bgcolor="white" ><tr><td style="line-height:0px;font-size:0px;mso-line-height-rule:exactly;"><![endif]-->
<div style="background:white;background-color:white;margin:0px auto;max-width:992px;">
  <table align="center" border="0" cellpadding="0" cellspacing="0" role="presentation" style="background:white;background-color:white;width:100%;">
    <tbody>
      <tr>
        <td style="direction:ltr;font-size:0px;padding:20px 0;padding-bottom:10px;padding-left:10px;padding-top:0px;text-align:center;">
          <!--[if mso | IE]><table role="presentation" border="0" cellpadding="0" cellspacing="0"><tr><td class="" style="vertical-align:top;width:883.8px;" ><![endif]-->
          <div class="mj-column-per-90 mj-outlook-group-fix" style="font-size:0px;text-align:left;direction:ltr;display:inline-block;vertical-align:top;width:100%;">
            <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="background-color:#337ab7;border-radius:5px;vertical-align:top;" width="100%">
              <tbody>
                <tr>
                  <td align="left" style="font-size:0px;padding:10px 25px;word-break:break-word;">
                    <div style="font-family: Poppins, Candara, Helvetica, Arial, sans-serif;font-size:18px;font-weight:600;line-height:1;text-align:left;color:white;">
                      <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="vertical-align:middle;">
                        <tbody>
                          <tr>
                            <td>
                              <img src="<?= $base_url ?>/sites/all/modules/gofast/gofast_mail_queue/icon/info-circle-solid-white.png" alt="Information Icon" width="18" />
                            </td>
                            <td>
                              <span style="color: #FFFFFF; font-size: 18px; font-weight: 600;">&nbsp;<?= $title ?></span>
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
        <td style="direction:ltr;font-size:0px;padding:20px 0;padding-bottom:10px;padding-left:10px;padding-top:0px;text-align:center;">
          <!--[if mso | IE]><table role="presentation" border="0" cellpadding="0" cellspacing="0"><tr><td class="" style="vertical-align:middle;width:883.8px;" ><![endif]-->
          <div class="mj-column-per-90 mj-outlook-group-fix" style="font-size:0px;text-align:left;direction:ltr;display:inline-block;vertical-align:middle;width:100%;">
            <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="vertical-align:middle;" width="100%">
              <tbody>
                <tr>
                  <td align="left" style="font-size:0px;padding:10px 25px;word-break:break-word;">
                    <div style="font-family: Poppins, Candara, Helvetica, Arial, sans-serif;font-size:14px;font-weight:400;line-height:1;text-align:left;color:#000000;"><?= $description ?></a></div>
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