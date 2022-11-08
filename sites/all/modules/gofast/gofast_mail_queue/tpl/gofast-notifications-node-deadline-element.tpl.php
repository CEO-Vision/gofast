<!--[if mso | IE]><table role="presentation" border="0" cellpadding="0" cellspacing="0"><tr><td class="" style="vertical-align:top;width:892.8px;" ><![endif]-->
<div class="mj-column-per-90 mj-outlook-group-fix" style="font-size:0px;text-align:left;direction:ltr;display:inline-block;vertical-align:top;width:100%;">
    <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="vertical-align:top;" width="100%">
        <tbody>
            <tr>
                <td align="left" style="font-size:0px;padding:0;padding-bottom:10px;word-break:break-word;">
                    <div style="font-family:Poppins, Candara, Helvetica, Arial, sans-serif;font-size:18px;font-weight:600;line-height:1;text-align:left;color:#000000;">
                        <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="vertical-align:middle;">
                            <tbody>
                                <tr>
                                    <td>
                                        <?= str_replace(".png", ".png?cache=" . rand(1, 1000), $node_icon) ?>
                                    </td>
                                    <td>
                                        <a href="<?= $node_link ?>" style="color: #000000; font-size: 18px; font-weight: 600; text-decoration: none;">&nbsp;<?= $node_title ?></a>
                                    </td>
                                    <?php if (isset($item_label)) : ?>
                                        <td><?= theme('gofast-notifications-node-icon', array('icon' => 'flag.png', 'width' => '14')) ?></td>
                                        <td>
                                            <span style="font-size:14px;font-weight:600;"><?= $item_label ?></span>
                                        </td>
                                    <?php endif; ?>
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