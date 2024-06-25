<?php global $base_url; ?>
<tr>
    <td style="line-height: inherit;">
        <i class="fas <?= $content->field_icone_value ?>"></i>
        <a href="<?= $base_url . '/node/' . $content->etid; ?>" class=""><?= $content->title; ?></a>
    </td>
    <td style="line-height: inherit;">
        <?= format_date(strtotime($content->field_date_value), "short") ?>
    </td>
</tr>