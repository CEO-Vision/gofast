<!-- FILE: mail_header_source.mjml -->
<?php global $base_url; ?>
<!doctype html>
<html xmlns="http://www.w3.org/1999/xhtml" xmlns:v="urn:schemas-microsoft-com:vml" xmlns:o="urn:schemas-microsoft-com:office:office">

<head>
  <title>
  </title>
  <!--[if !mso]><!-->
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <!--<![endif]-->
  <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <!-- GoFAST -->
  <!-- Facebook sharing information tags -->
  <meta property="og:title" content="GoFast Notifications">
  <title><?php echo (variable_get('site_name')); ?></title>
  <style type="text/css">
    /** GoFAST */
    #edits-metadatas tr td th {
      border: 1px solid grey;
    }

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
      .mj-column-per-20 {
        width: 20% !important;
        max-width: 20%;
      }

      .mj-column-per-80 {
        width: 80% !important;
        max-width: 80%;
      }
    }
  </style>
  <style media="screen and (min-width:480px)">
    .moz-text-html .mj-column-per-20 {
      width: 20% !important;
      max-width: 20%;
    }

    .moz-text-html .mj-column-per-80 {
      width: 80% !important;
      max-width: 80%;
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
      font-weight: 100;
      src: url("<?= $base_url ?>/sites/all/themes/bootstrap-keen/fonts/poppins/Poppins-Thin.otf") format("opentype");
    }

    @font-face {
      font-family: 'Poppins';
      font-style: normal;
      font-weight: 200;
      src: url("<?= $base_url ?>/sites/all/themes/bootstrap-keen/fonts/poppins/Poppins-ExtraLight.otf") format("opentype");
    }

    @font-face {
      font-family: 'Poppins';
      font-style: normal;
      font-weight: 300;
      src: url("<?= $base_url ?>/sites/all/themes/bootstrap-keen/fonts/poppins/Poppins-Light.otf") format("opentype");
    }

    @font-face {
      font-family: 'Poppins';
      font-style: normal;
      font-weight: 400;
      src: url("<?= $base_url ?>/sites/all/themes/bootstrap-keen/fonts/poppins/Poppins-Regular.otf") format("opentype");
    }

    @font-face {
      font-family: 'Poppins';
      font-style: normal;
      font-weight: 500;
      src: url("<?= $base_url ?>/sites/all/themes/bootstrap-keen/fonts/poppins/Poppins-Medium.otf") format("opentype");
    }

    @font-face {
      font-family: 'Poppins';
      font-style: normal;
      font-weight: 600;
      src: url("<?= $base_url ?>/sites/all/themes/bootstrap-keen/fonts/poppins/Poppins-SemiBold.otf") format("opentype");
    }

    @font-face {
      font-family: 'Poppins';
      font-style: bold;
      font-weight: 700;
      src: url("<?= $base_url ?>/sites/all/themes/bootstrap-keen/fonts/poppins/Poppins-Bold.otf") format("opentype");
    }

    @font-face {
      font-family: 'Poppins';
      font-style: normal;
      font-weight: 800;
      src: url("<?= $base_url ?>/sites/all/themes/bootstrap-keen/fonts/poppins/Poppins-ExtraBold.otf") format("opentype");
    }

    @font-face {
      font-family: 'Poppins';
      font-style: normal;
      font-weight: 900;
      src: url("<?= $base_url ?>/sites/all/themes/bootstrap-keen/fonts/poppins/Poppins-Black.otf") format("opentype");
    }

    .separate>table {
      border-collapse: separate;
    }

    /** GoFAST */
    body {
      font-family: Poppins, Candara, Helvetica, Arial, sans-serif;
    }
  </style>
</head>

<body style="word-spacing:normal;background-color:#EAF1F7;">
  <div style="background-color:#EAF1F7;">
    <!-- Header -->
    <!--[if mso | IE]><table align="center" border="0" cellpadding="0" cellspacing="0" class="" role="presentation" style="width:992px;" width="992" bgcolor="#242939" ><tr><td style="line-height:0px;font-size:0px;mso-line-height-rule:exactly;"><![endif]-->
    <div style="background:#242939;background-color:#242939;margin:0px auto;max-width:992px;">
      <table align="center" border="0" cellpadding="0" cellspacing="0" role="presentation" style="background:#242939;background-color:#242939;width:100%;">
        <tbody>
          <tr>
            <td style="direction:ltr;font-size:0px;padding:20px 0;padding-bottom:5px;padding-top:5px;text-align:center;">
              <!--[if mso | IE]><table role="presentation" border="0" cellpadding="0" cellspacing="0"><tr><td class="" style="vertical-align:middle;width:198.4px;" ><![endif]-->
              <div class="mj-column-per-20 mj-outlook-group-fix" style="font-size:0px;text-align:left;direction:ltr;display:inline-block;vertical-align:middle;width:100%;">
                <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="vertical-align:middle;" width="100%">
                  <tbody>
                    <tr>
                      <td align="left" style="font-size:0px;padding:0;padding-left:20px;word-break:break-word;">
                        <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="border-collapse:collapse;border-spacing:0px;">
                          <tbody>
                            <tr>
                              <td style="width:100px;">
                                <a href="<?= $base_url ?>">
                                  <img height="auto" src="<?= $logo ?>" style="border:0;display:block;outline:none;text-decoration:none;height:auto;width:100%;font-size:13px;" width="100" /></a>
                              </td>
                            </tr>
                          </tbody>
                        </table>
                      </td>
                    </tr>
                  </tbody>
                </table>
              </div>
              <!--[if mso | IE]></td><td class="" style="vertical-align:middle;width:793.6px;" ><![endif]-->
              <div class="mj-column-per-80 mj-outlook-group-fix" style="font-size:0px;text-align:left;direction:ltr;display:inline-block;vertical-align:middle;width:100%;">
                <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="vertical-align:middle;" width="100%">
                  <tbody>
                    <tr>
                      <td align="left" style="font-size:0px;padding:10px 25px;word-break:break-word;">
                        <div style="font-family:Poppins, Candara, Helvetica, Arial, sans-serif;font-size:22px;font-weight:600;line-height:1;text-align:left;color:white;"><?= $title ?></div>
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