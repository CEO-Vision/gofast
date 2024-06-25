<?php global $base_url; ?>
<?php
$event_string = "";
$event_post_string = "";
$is_comment_event = false;
if (isset($event["type"])) {
    $is_comment_event = true;
    if ($event["type"] == "ECOM") {
        if (strlen($event["comment_title"]) > 0) {
            $event_string = t('!author edited the comment "!title"', array('!author' => $event["author_name"], '!title' => $event["comment_title"]), $l) . ".";
        } else {
            $event_string = t('!author edited a comment', array('!author' => $event["author_name"]), $l) . ".";
        }
    }
    if ($event["type"] == "NCOM") {
        if (strlen($event["comment_title"]) > 0) {
            $event_string = t('!author added the comment "!title"', array('!author' => $event["author_name"], '!title' => $event["comment_title"]), $l) . ".";
        } else {
            $event_string = t('!author added a comment', array('!author' => $event["author_name"]), $l) . ".";
        }
    }
// In case we only have body modification
} else if(count($event["actions"]) == 1 && $event["actions"][0]["update"]["field"] == "body"){
    $event_string = t("!author has made changes to the content.", array("!author" => $event["author_name"]), $l);
} else {
    $event_string = t('!author made the following changes:', array('!author' => $event["author_name"]), $l);
}
?>
<!-- Single comment -->
<!--[if mso | IE]><table align="center" border="0" cellpadding="0" cellspacing="0" class="" role="presentation" style="width:992px;" width="992" bgcolor="white" ><tr><td style="line-height:0px;font-size:0px;mso-line-height-rule:exactly;"><![endif]-->
<?php // in non-comment notifications, we don't display the "Answer" button so the bottom radius must be rendered here 
?>
<div style="background:white;background-color:white;margin:0px auto;max-width:992px;">
    <table align="center" border="0" cellpadding="0" cellspacing="0" role="presentation" style="background:white;background-color:white;width:100%;">
        <tbody>
            <tr>
                <td style="direction:ltr;font-size:0px;padding:0;padding-top:10px;text-align:center;">
                    <!--[if mso | IE]><table role="presentation" border="0" cellpadding="0" cellspacing="0"><tr><td class="" style="width:892.8px;" ><![endif]-->
                    <div class="mj-column-per-90 mj-outlook-group-fix" style="font-size:0;line-height:0;text-align:left;display:inline-block;width:100%;direction:ltr;">
                        <?php if ($is_comment_event) : ?>
                            <!--[if mso | IE]><table border="0" cellpadding="0" cellspacing="0" role="presentation" ><tr><td style="vertical-align:middle;width:714px;" ><![endif]-->
                            <div class="mj-column-per-80 mj-outlook-group-fix" style="font-size:0px;text-align:left;direction:ltr;display:inline-block;vertical-align:middle;width:80%;">
                            <?php else : ?>
                                <!--[if mso | IE]><table border="0" cellpadding="0" cellspacing="0" role="presentation" ><tr><td style="vertical-align:middle;width:892px;" ><![endif]-->
                                <div class="mj-column-per-100 mj-outlook-group-fix" style="font-size:0px;text-align:left;direction:ltr;display:inline-block;vertical-align:middle;width:100%;">
                                <?php endif; ?>
                                <table border="0" cellpadding="0" cellspacing="0" role="presentation" width="100%">
                                    <tbody>
                                        <tr>
                                            <td style="vertical-align:middle;padding-top:10px;">
                                                <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="" width="100%">
                                                    <tbody>
                                                        <tr>
                                                            <td align="left" style="font-size:0px;padding:0;padding-left:10px;word-break:break-word;">
                                                                <div style="font-family:Poppins, Candara, Helvetica, Arial, sans-serif;font-size:14px;font-weight:400;line-height:1;text-align:left;color:#000000;">
                                                                    <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="vertical-align:middle;">
                                                                        <tbody>
                                                                            <tr>
                                                                                <td><?= $event["author_pic"] ?>
                                                                                </td>
                                                                                <td><span style="font-size: 14px; font-weight: 400;">&nbsp;<?= $event_string ?></span>
                                                                                </td>
                                                                            </tr>
                                                                        </tbody>
                                                                    </table>
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
                                <?php if ($is_comment_event) : ?>
                                    <!--[if mso | IE]></td><td style="vertical-align:middle;width:178px;" ><![endif]-->
                                    <div class="mj-column-per-20 mj-outlook-group-fix" style="font-size:0px;text-align:left;direction:ltr;display:inline-block;vertical-align:middle;width:20%;">
                                        <table border="0" cellpadding="0" cellspacing="0" role="presentation" width="100%">
                                            <tbody>
                                                <tr>
                                                    <td style="vertical-align:middle;padding-top:10px;">
                                                        <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="" width="100%">
                                                            <tbody>
                                                                <tr>
                                                                    <td align="left" style="font-size:0px;padding:0;padding-left:10px;word-break:break-word;">
                                                                        <div style="font-family:Poppins, Candara, Helvetica, Arial, sans-serif;font-size:14px;font-weight:400;line-height:1;text-align:left;color:#666666;"><?= format_date($event["timestamp"], "custom", $short_format, NULL, $l["langcode"]) ?></div>
                                                                    </td>
                                                                </tr>
                                                            </tbody>
                                                        </table>
                                                    </td>
                                                </tr>
                                            </tbody>
                                        </table>
                                    </div>
                                <?php endif; ?>
                                <!--[if mso | IE]></td></tr></table><![endif]-->
                            </div>
                            <!--[if mso | IE]></td></tr></table><![endif]-->
                </td>
            </tr>
        </tbody>
    </table>
</div>
<?php if (isset($event["body"])) : ?>
    <!--[if mso | IE]></td></tr></table><table align="center" border="0" cellpadding="0" cellspacing="0" class="" role="presentation" style="width:992px;" width="992" bgcolor="white" ><tr><td style="line-height:0px;font-size:0px;mso-line-height-rule:exactly;"><![endif]-->
    <div style="background:white;background-color:white;margin:0px auto;max-width:992px;">
        <table align="center" border="0" cellpadding="0" cellspacing="0" role="presentation" style="background:white;background-color:white;width:100%;">
            <tbody>
                <tr>
                    <td style="direction:ltr;font-size:0px;padding:0;padding-top:10px;text-align:center;">

                        <!--[if mso | IE]><table role="presentation" border="0" cellpadding="0" cellspacing="0"><tr><td class="separate-outlook" style="vertical-align:top;width:892.8px;" ><![endif]-->
                        <div class="mj-column-per-90 mj-outlook-group-fix separate" style="font-size:0px;text-align:left;direction:ltr;display:inline-block;vertical-align:top;width:100%;">
                            <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="border:1px solid #666666;border-radius:10px;vertical-align:top;" width="100%">
                                <tbody>
                                    <tr>
                                        <td align="left" style="font-size:0px;padding:10px 25px;word-break:break-word;">
                                            <div style="font-family:Poppins, Candara, Helvetica, Arial, sans-serif;font-size:14px;font-weight:400;line-height:1;text-align:left;color:#000000;"><?= $event["body"] ?></div>
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
<?php if ($is_comment_event) : ?>
    <!--[if mso | IE]></td></tr></table><table align="center" border="0" cellpadding="0" cellspacing="0" class="" role="presentation" style="width:992px;" width="992" bgcolor="white" ><tr><td style="line-height:0px;font-size:0px;mso-line-height-rule:exactly;"><![endif]-->
    <div style="background:white;background-color:white;margin:0px auto;max-width:992px;<?= $mail_loop_count == count($item["events"]) ? "border-radius:0 0 10px 10px;" : "" ?>">
        <table align="center" border="0" cellpadding="0" cellspacing="0" role="presentation" style="background:white;background-color:white;width:100%;<?= $mail_loop_count == count($item["events"]) ? "border-radius:0 0 10px 10px;" : "" ?>">
            <tbody>
                <tr>
                    <td style="direction:ltr;font-size:0px;padding:0;text-align:center;">
                        <!--[if mso | IE]><table role="presentation" border="0" cellpadding="0" cellspacing="0"><tr><td class="" style="vertical-align:top;width:892.8px;" ><![endif]-->
                        <div class="mj-column-per-90 mj-outlook-group-fix" style="font-size:0px;text-align:left;direction:ltr;display:inline-block;vertical-align:top;width:100%;">
                            <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="vertical-align:top;" width="100%">
                                <tbody>
                                    <tr>
                                        <td align="left" vertical-align="middle" style="font-size:0px;padding:10px 25px;padding-left:0;word-break:break-word;">
                                            <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="border-collapse:separate;line-height:100%;">
                                                <tbody>
                                                    <tr>
                                                        <td align="center" bgcolor="#337ab7" role="presentation" style="border:none;border-radius:5px;cursor:auto;mso-padding-alt:10px 25px;background:#337ab7;" valign="middle">
                                                            <a href="<?= $base_url . "/node/" . $event["nid"] . "#comment-" . $event["vid"] ?>" style="display:inline-block;background:#337ab7;color:#ffffff;font-family:Poppins, Candara, Helvetica, Arial, sans-serif;font-size:14px;font-weight:600;line-height:120%;margin:0;text-decoration:none;text-transform:none;padding:10px 25px;mso-padding-alt:0px;border-radius:5px;" target="_blank"><?= t("Answer", array(), $l) ?> </a>
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
    <?php
else :
    foreach ($event["actions"] as $index => $action) :
        // Don't show the diff of the body
        if($action["update"]["field"] == "body"){
            continue;
        }
    ?>
        <!--[if mso | IE]></td></tr></table><table align="center" border="0" cellpadding="0" cellspacing="0" class="" role="presentation" style="width:992px;" width="992" bgcolor="white" ><tr><td style="line-height:0px;font-size:0px;mso-line-height-rule:exactly;"><![endif]-->
        <div style="background:white;background-color:white;margin:0px auto;max-width:992px;<?= $index + 1 == count($event["actions"]) ? "border-radius:0 0 10px 10px;" : "" ?>">
            <table align="center" border="0" cellpadding="0" cellspacing="0" role="presentation" style="background:white;background-color:white;width:100%;<?= $index + 1 == count($event["actions"]) ? "border-radius:0 0 10px 10px;" : "" ?>">
                <tbody>
                    <tr>
                        <td style="direction:ltr;font-size:0px;padding:0;padding-top:10px;text-align:center;">
                            <!--[if mso | IE]><table role="presentation" border="0" cellpadding="0" cellspacing="0"><tr><td class="" style="vertical-align:top;width:892.8px;" ><![endif]-->
                            <div class="mj-column-per-90 mj-outlook-group-fix" style="font-size:0;line-height:0;text-align:left;display:inline-block;width:100%;direction:ltr;<?= $index + 1 == count($event["actions"]) ? "padding-bottom:20px;" : "" ?>">
                                <!--[if mso | IE]><table border="0" cellpadding="0" cellspacing="0" role="presentation" ><tr><td style="vertical-align:top;width:133px;" ><![endif]-->
                                <div class="mj-column-per-15 mj-outlook-group-fix" style="font-size:0px;text-align:left;direction:ltr;display:inline-block;vertical-align:top;width:15%;">
                                    <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="vertical-align:top;" width="100%">
                                        <tbody>
                                            <tr>
                                                <td align="left" style="font-size:0px;padding:0;padding-left:10px;word-break:break-word;">
                                                    <div style="font-family:Poppins, Candara, Helvetica, Arial, sans-serif;font-size:14px;font-weight:400;line-height:1;text-align:left;color:#666666;">
                                                        <?php
                                                        $action_date = explode(" - ", format_date($action["timestamp"], "custom", $extra_short_format, NULL, $l["langcode"]));
                                                        echo "<div>" . $action_date[1] . "</div>";
                                                        echo "<div style='font-size: 10px;'>" . $action_date[0] . "</div>";
                                                        ?>
                                                    </div>
                                                </td>
                                            </tr>
                                        </tbody>
                                    </table>
                                </div>
                                <!--[if mso | IE]></td><td style="vertical-align:top;width:178px;" ><![endif]-->
                                <div class="mj-column-per-20 mj-outlook-group-fix" style="font-size:0px;text-align:left;direction:ltr;display:inline-block;vertical-align:top;width:20%;">
                                    <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="vertical-align:top;" width="100%">
                                        <tbody>
                                            <tr>
                                                <td align="left" style="font-size:0px;padding:0;padding-left:10px;word-break:break-word;">
                                                    <div style="font-family:Poppins, Candara, Helvetica, Arial, sans-serif;font-size:14px;font-weight:400;line-height:1;text-align:left;color:#000000;">
                                                        <?php
                                                        switch ($action["type"]) {
                                                            case "NCON":
                                                                echo t("Added a document", array(), $l);
                                                                break;
                                                            case "ECON":
                                                                if ($action["update"]["field"] == "deadline") {
                                                                    $action["update"]["from"] = format_date(strtotime($action["update"]["from"]), 'custom', $short_without_hours_format, NULL, $l["langcode"]);
                                                                    $action["update"]["to"] = format_date(strtotime($action["update"]["to"]), 'custom', $short_without_hours_format, NULL, $l["langcode"]);
                                                                }
                                                                if ($action["update"]["field"] == "locations") {
                                                                    $action["update"]["from"] = str_replace("/_", "/", str_replace("/Sites", "", $action["update"]["from"]));
                                                                    $action["update"]["to"] = str_replace("/_", "/", str_replace("/Sites", "", $action["update"]["to"]));
                                                                }
                                                                echo t('!field', array('!field' => t(ucfirst($action["update"]["field"]), array(), $l)), $l);
                                                                break;
                                                            case "NDEL":
                                                                echo t("Deleted a document", array(), $l);
                                                                break;
                                                            case "NREV":
                                                                echo t("Updated a document", array(), $l);
                                                                break;
                                                        }
                                                        ?>
                                                    </div>
                                                </td>
                                            </tr>
                                        </tbody>
                                    </table>
                                </div>
                                <?php if ($action["type"] == "ECON") : ?>
                                    <!--[if mso | IE]></td><td style="vertical-align:top;width:290px;" ><![endif]-->
                                    <div class="mj-column-per-32-5 mj-outlook-group-fix" style="font-size:0px;text-align:left;direction:ltr;display:inline-block;vertical-align:top;width:32.5%;">
                                        <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="vertical-align:top;" width="100%">
                                            <tbody>
                                                <tr>
                                                    <td align="left" style="font-size:0px;padding:0;padding-left:10px;word-break:break-word;">
                                                        <div style="font-family:Poppins, Candara, Helvetica, Arial, sans-serif;font-size:14px;font-weight:600;line-height:1;text-align:left;color:#000000;"><?= strlen($action["update"]["from"]) > 0 ? t($action["update"]["from"], array(), $l) : t("Blank", array(), $l) ?></div>
                                                    </td>
                                                </tr>
                                            </tbody>
                                        </table>
                                    </div>
                                <?php endif; ?>
                                <?php if ($action["type"] == "ECON" || $action["type"] == "NREV") : ?>
                                    <!--[if mso | IE]></td><td style="vertical-align:top;width:290px;" ><![endif]-->
                                    <div class="mj-column-per-32-5 mj-outlook-group-fix" style="font-size:0px;text-align:left;direction:ltr;display:inline-block;vertical-align:top;width:32.5%;">
                                        <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="vertical-align:top;" width="100%">
                                            <tbody>
                                                <tr>
                                                    <td align="left" style="font-size:0px;padding:0;padding-left:10px;word-break:break-word;">
                                                        <div style="font-family:Poppins, Candara, Helvetica, Arial, sans-serif;font-size:14px;font-weight:600;line-height:1;text-align:left;color:#FD7E14;">
                                                            <?php
                                                            if ($action["type"] == "ECON") {
                                                                echo strlen($action["update"]["to"]) > 0 ? t($action["update"]["to"], array(), $l) : t("Blank", array(), $l);
                                                            }
                                                            if ($action["type"] == "NREV") {
                                                                echo $event["revision"]["to"];
                                                            }
                                                            ?>
                                                        </div>
                                                    </td>
                                                </tr>
                                            </tbody>
                                        </table>
                                    </div>
                                <?php endif; ?>
                                <!--[if mso | IE]></td></tr></table><![endif]-->
                        </td>
                    </tr>
                </tbody>
            </table>
        </div>
<?php
    endforeach;
endif;
?>
<?php if ($mail_loop_count != count($item["events"])) : ?>
    <!--[if mso | IE]></td></tr></table><table align="center" border="0" cellpadding="0" cellspacing="0" class="" role="presentation" style="width:992px;" width="992" bgcolor="white" ><tr><td style="line-height:0px;font-size:0px;mso-line-height-rule:exactly;"><![endif]-->
    <div style="background:white;background-color:white;margin:0px auto;max-width:992px;">
        <table align="center" border="0" cellpadding="0" cellspacing="0" role="presentation" style="background:white;background-color:white;width:100%;">
            <tbody>
                <tr>
                    <td style="direction:ltr;font-size:0px;padding:0;padding-top:10px;text-align:center;">
                        <!--[if mso | IE]><table role="presentation" border="0" cellpadding="0" cellspacing="0"><tr><td class="" style="vertical-align:top;width:992px;" ><![endif]-->
                        <div class="mj-column-per-100 mj-outlook-group-fix" style="font-size:0px;text-align:left;direction:ltr;display:inline-block;vertical-align:top;width:100%;">
                            <table border="0" cellpadding="0" cellspacing="0" role="presentation" width="100%">
                                <tbody>
                                    <tr>
                                        <td style="vertical-align:top;padding-right:10px;">
                                            <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="" width="100%">
                                                <tbody>
                                                    <tr>
                                                        <td align="center" style="font-size:0px;padding:10px 25px;word-break:break-word;">
                                                            <p style="border-top:solid 1px #666666;font-size:1px;margin:0px auto;width:100%;">
                                                            </p>
                                                            <!--[if mso | IE]><table align="center" border="0" cellpadding="0" cellspacing="0" style="border-top:solid 1px #666666;font-size:1px;margin:0px auto;width:932px;" role="presentation" width="932px" ><tr><td style="height:0;line-height:0;"> &nbsp;
</td></tr></table><![endif]-->
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
<!--[if mso | IE]></td></tr></table><![endif]-->