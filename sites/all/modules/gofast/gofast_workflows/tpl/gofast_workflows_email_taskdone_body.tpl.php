<!-- FILE: mail_workflows_notif_source.mjml -->
<?php
global $base_url;
$short_format = system_date_format_locale($assignee_language, "short");
$message = "";
switch ($step) {
    case "task_done":
        $done_task = $history[0];
        $message .= $done_task->actor_displayname;
        $post_message = t("with the following comment:", array(), array("langcode" => $assignee_language, "context" => "gofast:gofast_workflows"));
        $task_comment = $done_task->comment;
        // Drupal will not accept importation of translatable strings with HTML tags inside, so we encode the translatable string html entities
        $done_task_description =  html_entity_decode(t(htmlentities($done_task->description), array(), array("langcode" => $assignee_language, "context" => "gofast:gofast_workflows")));
        break;
    case "task_assigned":
    case "remind_task_assigned":
        $message .= t("Please review your pending tasks below", array(), array("langcode" => $assignee_language, "context" => "gofast:gofast_workflows"));
        break;
    case "end_process":
        $message .= t("The process has been entirely completed", array(), array("langcode" => $assignee_language, "context" => "gofast:gofast_workflows"));
        break;
    default:
        $message .= t("A user has completed a task", array(), array("langcode" => $assignee_language, "context" => "gofast:gofast_workflows"));
}
?>
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

        .mj-column-per-20 {
            width: 20% !important;
            max-width: 20%;
        }

        .mj-column-per-30 {
            width: 30% !important;
            max-width: 30%;
        }
    }
</style>
<style media="screen and (min-width:480px)">
    .moz-text-html .mj-column-per-90 {
        width: 90% !important;
        max-width: 90%;
    }

    .moz-text-html .mj-column-per-20 {
        width: 20% !important;
        max-width: 20%;
    }

    .moz-text-html .mj-column-per-30 {
        width: 30% !important;
        max-width: 30%;
    }
</style>
<style type="text/css">
</style>

<!-- SubHeader -->
<!--[if mso | IE]><table align="center" border="0" cellpadding="0" cellspacing="0" class="" role="presentation" style="width:992px;" width="992" bgcolor="white" ><tr><td style="line-height:0px;font-size:0px;mso-line-height-rule:exactly;"><![endif]-->
<div style="background:white;background-color:white;margin:0px auto;max-width:992px;">
    <table align="center" border="0" cellpadding="0" cellspacing="0" role="presentation" style="background:white;background-color:white;width:100%;">
        <tbody>
            <tr>
                <td style="direction:ltr;font-size:0px;padding:0;padding-left:10px;padding-top:10px;text-align:center;">
                    <!--[if mso | IE]><table role="presentation" border="0" cellpadding="0" cellspacing="0"><tr><td class="" style="vertical-align:top;width:883.8px;" ><![endif]-->
                    <div class="mj-column-per-90 mj-outlook-group-fix" style="font-size:0px;text-align:left;direction:ltr;display:inline-block;vertical-align:top;width:100%;">
                        <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="vertical-align:top;" width="100%">
                            <tbody>
                                <tr>
                                    <td align="left" style="font-size:0px;padding:10px 25px;padding-left:0;word-break:break-word;">
                                        <div style="font-family:Poppins;font-size:18px;font-weight:600;line-height:1;text-align:left;color:#000000;"><?= t("Hello", array(), array("langcode" => $assignee_language, "context" => "gofast:gofast_workflows")) . " " . $assignee_firstname ?>,</div>
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
                    <!--[if mso | IE]><table role="presentation" border="0" cellpadding="0" cellspacing="0"><tr><td class="" style="vertical-align:top;width:883.8px;" ><![endif]-->
                    <div class="mj-column-per-90 mj-outlook-group-fix" style="font-size:0px;text-align:left;direction:ltr;display:inline-block;vertical-align:top;width:100%;">
                        <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="vertical-align:top;" width="100%">
                            <tbody>
                                <tr>
                                    <td align="left" style="font-size:0px;padding:10px 25px;padding-left:0;word-break:break-word;">
                                        <div style="font-family:Poppins;font-size:14px;font-weight:600;line-height:1;text-align:left;color:#000000;"><?= $message ?>
                                        <?php if ($step == "task_done") : ?>
                                            &nbsp;<?= $done_task_description ?>
                                        <?php endif; ?>
                                        </div>
                                        <?php if (isset($post_message) && isset($task_comment) && strlen($task_comment) > 0) : ?>
                                            <div style="font-family:Poppins;font-size:14px;font-weight:400;line-height:1.5;text-align:left;color:#000000;margin-top:10px;">
                                                <?= $post_message ?>
                                            </div>
                                            &nbsp;<div style="color: #000000; font-size: 14px; font-weight: 400; background-color: #F3F6F9; border: 1px solid #666666; padding: 2px;"><?= $task_comment?></div>
                                        <?php endif; ?>
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
<!-- Workflows -->
<?php if (!empty($list_tasks_assigned_user)) : ?>
    <!--[if mso | IE]><table align="center" border="0" cellpadding="0" cellspacing="0" class="" role="presentation" style="width:992px;" width="992" bgcolor="white" ><tr><td style="line-height:0px;font-size:0px;mso-line-height-rule:exactly;"><![endif]-->
    <div style="background:white;background-color:white;margin:0px auto;max-width:992px;">
        <table align="center" border="0" cellpadding="0" cellspacing="0" role="presentation" style="background:white;background-color:white;width:100%;">
            <tbody>
                <tr>
                    <td style="direction:ltr;font-size:0px;padding:0;padding-left:10px;padding-top:10px;text-align:center;">

                        <!--[if mso | IE]><table role="presentation" border="0" cellpadding="0" cellspacing="0"><tr><td class="" style="vertical-align:top;width:883.8px;" ><![endif]-->
                        <div class="mj-column-per-90 mj-outlook-group-fix" style="font-size:0px;text-align:left;direction:ltr;display:inline-block;vertical-align:top;width:100%;">
                            <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="background-color:#de6502;border-radius:10px 10px 0 10px;vertical-align:top;" width="100%">
                                <tbody>
                                    <tr>
                                        <td align="left" style="font-size:0px;padding:10px 25px;word-break:break-word;">
                                            <div style="font-family:Poppins;font-size:18px;font-weight:600;line-height:1;text-align:left;color:white;">
                                                <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="vertical-align:middle;">
                                                    <tbody>
                                                        <tr>
                                                            <td>
                                                                <img src="<?= $base_url . '/' . drupal_get_path('module', 'gofast_mail_queue') . '/icon/' . 'cogs-solid-white.png' ?>" alt="<?= t("Information Icon", array(), array("context" => "gofast:gofast_workflows")) ?>" width="18" />
                                                            </td>
                                                            <td><span style="color: #FFFFFF; font-size: 18px; font-weight: 600;"> &nbsp;
                                                                    <?= t("Tasks to do", array(), array("langcode" => $assignee_language, "context" => "gofast:gofast_workflows")) ?>
                                                                </span>
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
<?php endif; ?>
<?php foreach ($list_tasks_assigned_user as $assigned_user_task) : ?>
    <!--[if mso | IE]></td></tr></table><table align="center" border="0" cellpadding="0" cellspacing="0" class="" role="presentation" style="width:992px;" width="992" bgcolor="white" ><tr><td style="line-height:0px;font-size:0px;mso-line-height-rule:exactly;"><![endif]-->
    <div style="background:white;background-color:white;margin:0px auto;max-width:992px;">
        <table align="center" border="0" cellpadding="0" cellspacing="0" role="presentation" style="background:white;background-color:white;width:100%;">
            <tbody>
                <tr>
                    <td style="direction:ltr;font-size:0px;padding:0;padding-left:10px;text-align:center;">
                        <!--[if mso | IE]><table role="presentation" border="0" cellpadding="0" cellspacing="0"><tr><td class="" style="width:883.8px;" ><![endif]-->
                        <div class="mj-column-per-90 mj-outlook-group-fix" style="font-size:0px;text-align:left;direction:ltr;display:inline-block;vertical-align:top;width:100%;">
                            <!--[if mso | IE]><table border="0" cellpadding="0" cellspacing="0" role="presentation" ><tr><td style="vertical-align:top;width:176px;" ><![endif]-->
                            <div class="mj-column-per-20 mj-outlook-group-fix" style="font-size:0px;text-align:left;direction:ltr;display:inline-block;vertical-align:top;width:20%;">
                                <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="vertical-align:top;" width="100%">
                                    <tbody>
                                        <tr>
                                            <td align="left" style="font-size:0px;padding:10px;word-break:break-word;">
                                                <div style="font-family:Poppins;font-size:14px;font-weight:400;line-height:1;text-align:left;color:#000000;"><?= format_date(strtotime($assigned_user_task["dueDate"]), "custom", $short_format, NULL, $assignee_language) ?></div>
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
                                                <div style="font-family:Poppins;font-size:14px;font-weight:600;line-height:1;text-align:left;color:#000000;"><?= $assignee_fullname ?></div>
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
                                                <div style="font-family:Poppins;font-size:14px;font-weight:400;line-height:1;text-align:left;color:#000000;"><?= t($assigned_user_task["displayName"], array(), array("langcode" => $assignee_language, "context" => "gofast:gofast_workflows")) ?></div>
                                            </td>
                                        </tr>
                                    </tbody>
                                </table>
                            </div>
                            <?php if ($step !== "end_process") : ?>
                                <!--[if mso | IE]></td><td style="vertical-align:top;width:265px;" ><![endif]-->
                                <div class="mj-column-per-30 mj-outlook-group-fix" style="font-size:0px;text-align:left;direction:ltr;display:inline-block;vertical-align:top;width:30%;">
                                    <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="background-color:#159992;vertical-align:top;" width="100%">
                                        <tbody>
                                            <tr>
                                                <td align="left" style="font-size:0px;padding:10px;word-break:break-word;">
                                                    <div style="font-family:Poppins;font-size:14px;font-weight:600;line-height:1;text-align:left;color:white;">
                                                        <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="vertical-align:middle;">
                                                            <tbody>
                                                                <tr>
                                                                    <td><img src="<?= $base_url . '/' . drupal_get_path('module', 'gofast_mail_queue') . '/icon/' . 'play-solid-white.png' ?>" alt="" width="14">
                                                                    </td>
                                                                    <td>
                                                                        <a href="<?= isset($documents_info[0]) ? $base_url . "/node/" . $documents_info[0] : $base_url . "/workflow/dashboard" ?>" style="color: #FFFFFF; font-size: 14px; font-weight: 600; text-decoration: none;">&nbsp;<?= t("Execute Task", array(), array("langcode" => $assignee_language, "context" => "gofast:gofast_workflows")) ?></a>
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
                            <?php endif; ?>
                        </div>
                        <!--[if mso | IE]></td></tr></table><![endif]-->
                    </td>
                </tr>
            </tbody>
        </table>
    </div>
<?php endforeach; ?>
<?php if (!empty($documents_info)) : ?>
    <!--[if mso | IE]></td></tr></table><table align="center" border="0" cellpadding="0" cellspacing="0" class="" role="presentation" style="width:992px;" width="992" bgcolor="white" ><tr><td style="line-height:0px;font-size:0px;mso-line-height-rule:exactly;"><![endif]-->
    <div style="background:white;background-color:white;margin:0px auto;max-width:992px;">
        <table align="center" border="0" cellpadding="0" cellspacing="0" role="presentation" style="background:white;background-color:white;width:100%;">
            <tbody>
                <tr>
                    <td style="direction:ltr;font-size:0px;padding:0;padding-left:10px;padding-top:10px;text-align:center;">
                        <!--[if mso | IE]><table role="presentation" border="0" cellpadding="0" cellspacing="0"><tr><td class="" style="vertical-align:top;width:883.8px;" ><![endif]-->
                        <div class="mj-column-per-90 mj-outlook-group-fix" style="font-size:0px;text-align:left;direction:ltr;display:inline-block;vertical-align:top;width:100%;">
                            <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="background-color:#337ab7;border-radius:10px;vertical-align:top;" width="100%">
                                <tbody>
                                    <tr>
                                        <td align="left" style="font-size:0px;padding:10px 25px;word-break:break-word;">
                                            <div style="font-family:Poppins;font-size:18px;font-weight:600;line-height:1;text-align:left;color:white;"><span>
                                                    <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="vertical-align:middle;">
                                                        <tbody>
                                                            <tr>
                                                                <td>
                                                                    <img src="<?= $base_url . '/' . drupal_get_path('module', 'gofast_mail_queue') . '/icon/' . 'other-white.png' ?>" alt="<?= t("Information Icon", array(), array("context" => "gofast:gofast_workflows")) ?>" width="18" />
                                                                </td>
                                                                <td>
                                                                    <span style="color: #FFFFFF; font-size: 18px; font-weight: 600;">&nbsp;<?= t("Documents", array(), array("langcode" => $assignee_language, "context" => "gofast:gofast_workflows")) ?></span>
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
<?php endif; ?>
<!--[if mso | IE]></td></tr></table><table align="center" border="0" cellpadding="0" cellspacing="0" class="" role="presentation" style="width:992px;" width="992" bgcolor="white" ><tr><td style="line-height:0px;font-size:0px;mso-line-height-rule:exactly;"><![endif]-->
<div style="background:white;background-color:white;margin:0px auto;max-width:992px;">
    <table align="center" border="0" cellpadding="0" cellspacing="0" role="presentation" style="background:white;background-color:white;width:100%;">
        <tbody>
            <tr>
                <td style="direction:ltr;font-size:0px;padding:0;padding-left:10px;padding-bottom:10px;text-align:center;">
                    <!--[if mso | IE]><table role="presentation" border="0" cellpadding="0" cellspacing="0"><tr><td class="" style="vertical-align:middle;width:883.8px;" ><![endif]-->
                    <div class="mj-column-per-90 mj-outlook-group-fix" style="font-size:0px;text-align:left;direction:ltr;display:inline-block;vertical-align:top;width:100%;">
                        <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="vertical-align:middle;" width="100%">
                            <tbody>
                                <?php foreach ($documents_info as $nid) :
                                    $document_node = node_load($nid);
                                    $node_icon = theme("gofast_node_icon_format", array("node" => $node));
                                    $node_icon = gofast_mail_queue_fa_png($node_icon, "14", "primary"); ?>
                                    <tr>
                                        <td align="left" style="font-size:0px;padding:0;padding-top:10px;padding-left:10px;word-break:break-word;">
                                            <div style="font-family:Poppins;font-size:14px;font-weight:400;line-height:1;text-align:left;color:#000000;">
                                                <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="vertical-align:middle;">
                                                    <tbody>
                                                        <tr>
                                                            <td><?= $node_icon ?></td>
                                                            <td>
                                                                <a href="<?= $base_url . "/node/" . $nid ?>" style="color: #337ab7; font-size: 14px; font-weight: 400; text-decoration: none;">&nbsp;<?= $document_node->title ?></a>
                                                            </td>
                                                        </tr>
                                                    </tbody>
                                                </table>
                                            </div>
                                        </td>
                                    </tr>
                                <?php endforeach; ?>
                            </tbody>
                        </table>
                    </div>
                </td>
            </tr>
        </tbody>
    </table>
</div>
<?php if (!empty($list_tasks)) : ?>
    <!--[if mso | IE]></td></tr></table><table align="center" border="0" cellpadding="0" cellspacing="0" class="" role="presentation" style="width:992px;" width="992" bgcolor="white" ><tr><td style="line-height:0px;font-size:0px;mso-line-height-rule:exactly;"><![endif]-->
    <div style="background:white;background-color:white;margin:0px auto;max-width:992px;">
        <table align="center" border="0" cellpadding="0" cellspacing="0" role="presentation" style="background:white;background-color:white;width:100%;">
            <tbody>
                <tr>
                    <td style="direction:ltr;font-size:0px;padding:0;padding-left:10px;padding-top:10px;text-align:center;">
                        <!--[if mso | IE]><table role="presentation" border="0" cellpadding="0" cellspacing="0"><tr><td class="" style="vertical-align:top;width:883.8px;" ><![endif]-->
                        <div class="mj-column-per-90 mj-outlook-group-fix" style="font-size:0px;text-align:left;direction:ltr;display:inline-block;vertical-align:top;width:100%;">
                            <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="background-color:#337ab7;border-radius:10px 10px 0 0;vertical-align:top;" width="100%">
                                <tbody>
                                    <tr>
                                        <td align="left" style="font-size:0px;padding:10px 25px;word-break:break-word;">
                                            <div style="font-family:Poppins;font-size:18px;font-weight:600;line-height:1;text-align:left;color:white;">
                                                <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="vertical-align:middle;">
                                                    <tbody>
                                                        <tr>
                                                            <td>
                                                                <img src="<?= $base_url . '/' . drupal_get_path('module', 'gofast_mail_queue') . '/icon/' . 'play-solid-white.png' ?>" alt="<?= t("Information Icon", array(), array("context" => "gofast:gofast_workflows")) ?>" width="18" />
                                                            </td>
                                                            <td>
                                                                <span style="color: #FFFFFF; font-size: 18px; font-weight: 600;">&nbsp;<?= t("Other ongoing tasks", array(), array("langcode" => $assignee_language, "context" => "gofast:gofast_workflows")) ?></span>
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
                    <td style="direction:ltr;font-size:0px;padding:0;padding-left:10px;text-align:center;">
                        <!--[if mso | IE]><table role="presentation" border="0" cellpadding="0" cellspacing="0"><tr><td class="" style="width:883.8px;" ><![endif]-->
                        <div class="mj-column-per-90 mj-outlook-group-fix" style="font-size:0;line-height:0;text-align:left;display:inline-block;width:100%;direction:ltr;background-color:#666666;">
                            <!--[if mso | IE]><table bgcolor="#666666" border="0" cellpadding="0" cellspacing="0" role="presentation" ><tr><td style="vertical-align:top;width:176px;" ><![endif]-->
                            <div class="mj-column-per-20 mj-outlook-group-fix" style="font-size:0px;text-align:left;direction:ltr;display:inline-block;vertical-align:top;width:20%;">
                                <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="vertical-align:top;" width="100%">
                                    <tbody>
                                        <tr>
                                            <td align="left" style="font-size:0px;padding:10px;word-break:break-word;">
                                                <div style="font-family:Poppins;font-size:14px;font-weight:600;line-height:1;text-align:left;color:white;"><?= t("Date", array(), array("langcode" => $assignee_language, "context" => "gofast:gofast_workflows")) ?></div>
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
                                                <div style="font-family:Poppins;font-size:14px;font-weight:600;line-height:1;text-align:left;color:white;"><?= t("Author", array(), array("langcode" => $assignee_language, "context" => "gofast:gofast_workflows")) ?></div>
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
                                                <div style="font-family:Poppins;font-size:14px;font-weight:600;line-height:1;text-align:left;color:white;"><?= t("Action", array(), array("langcode" => $assignee_language, "context" => "gofast:gofast_workflows")) ?></div>
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
                                                <div style="font-family:Poppins;font-size:14px;font-weight:600;line-height:1;text-align:left;color:white;"><?= t("Comment", array(), array("langcode" => $assignee_language, "context" => "gofast:gofast_workflows")) ?></div>
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
<?php endif; ?>
<?php foreach ($list_tasks as $task) : ?>
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
                                                <div style="font-family:Poppins;font-size:14px;font-weight:400;line-height:1;text-align:left;color:#000000;"><?= format_date(strtotime($task["dueDate"]), "custom", $short_format, NULL, $assignee_language) ?></div>
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
                                                <div style="font-family:Poppins;font-size:14px;font-weight:600;line-height:1;text-align:left;color:#000000;"><?= $task["assignedDisplayName"] ?></div>
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
                                                <div style="font-family:Poppins;font-size:14px;font-weight:400;line-height:1;text-align:left;color:#000000;"><?= strpos($task["displayName"], "|") === false ? t($task["displayName"], array(), array("langcode" => $assignee_language, "context" => "gofast:gofast_workflows")) : t(explode("|", $task["displayName"])[0] . " " . explode("|", $task["displayName"])[1], array(), array("langcode" => $assignee_language, "context" => "gofast:gofast_workflows")) ?></div>
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
                                                <div style="font-family:Poppins;font-size:14px;line-height:1;text-align:left;color:#000000;"><?= $task["description"] ?></div>
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
<?php if (!empty($history)) : ?>
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
                                                                <img src="<?= $base_url . '/' . drupal_get_path('module', 'gofast_mail_queue') . '/icon/' . 'history-solid-white.png' ?>" alt="<?= t("Information Icon", array(), array("context" => "gofast:gofast_workflows")) ?>" width="18" style="vertical-align: bottom;" />
                                                            </td>
                                                            <td><span style="color: #FFFFFF; font-size: 18px; font-weight: 600;">&nbsp;<?= t("History", array(), array("langcode" => $assignee_language, "context" => "gofast:gofast_workflows")) ?></td>
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
                                                <div style="font-family:Poppins;font-size:14px;font-weight:600;line-height:1;text-align:left;color:white;"><?= t("Action", array(), array("langcode" => $assignee_language, "context" => "gofast:gofast_workflows")) ?></div>
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
                                                <div style="font-family:Poppins;font-size:14px;font-weight:600;line-height:1;text-align:left;color:white;"><?= t("Author", array(), array("langcode" => $assignee_language, "context" => "gofast:gofast_workflows")) ?></div>
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
                                                <div style="font-family:Poppins;font-size:14px;font-weight:600;line-height:1;text-align:left;color:white;"><?= t("Action", array(), array("langcode" => $assignee_language, "context" => "gofast:gofast_workflows")) ?></div>
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
                                                <div style="font-family:Poppins;font-size:14px;font-weight:600;line-height:1;text-align:left;color:white;"><?= t("Comment", array(), array("langcode" => $assignee_language, "context" => "gofast:gofast_workflows")) ?></div>
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
<?php endif; ?>
<?php
    foreach ($history as $history_item) :
        if (strpos($history_item->actor_login, "__CUSTOM_STEP__") != FALSE) {
            $history_item->actor_login = explode("__CUSTOM_STEP__", $history_item->actor_login)[0];
        }
?>
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
                                                <div style="font-family:Poppins;font-size:14px;font-weight:400;line-height:1;text-align:left;color:#000000;"><?= format_date(substr($history_item->date, 0, -3), "custom", $short_format, NULL, $assignee_language) ?></div>
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
                                                <div style="font-family:Poppins;font-size:14px;font-weight:600;line-height:1;text-align:left;color:#000000;"><?= gofast_user_display_name(user_load_by_name($history_item->actor_login)) ?></div>
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
                                                <div style="font-family:Poppins;font-size:14px;font-weight:400;line-height:1;text-align:left;color:#000000;"><?= html_entity_decode(t(htmlentities($history_item->description), array(), array("langcode" => $assignee_language, "context" => "gofast:gofast_workflows"))) ?></div>
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
                                                <div style="font-family:Poppins;font-size:14px;line-height:1;text-align:left;color:#000000;"><?= $history_item->comment ?></div>
                                                <div style="font-family:Poppins;font-size:14px;font-weight:400;line-height:1;text-align:left;color:#000000;"></div>
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
<!--[if mso | IE]></td></tr></table><![endif]-->
