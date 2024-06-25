<?php global $base_url; ?>
<tr>
    <td style="line-height: inherit;">
        <i class="fas fa-video"></i>
        <a href="<?= $base_url . '/node/' . $content["nid"] ?>" class=""><?= $content["title"] ?></a>
    </td>
    <td style="line-height: inherit;">
        <?= format_date(strtotime($content["start"]), "short") ?>
    </td>
    <td style="line-height: inherit;">
        <?= format_date(strtotime($content["end"]),"short") ?>
    </td>
</tr>