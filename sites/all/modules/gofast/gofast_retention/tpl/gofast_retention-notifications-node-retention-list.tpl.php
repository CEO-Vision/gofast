<table style="margin:16px" align="left" border="0" cellpadding="0" cellspacing="0" width="540">
  <tbody>
    <?php foreach($nodes as $node): ?>
    <tr>
      <td style="color:#505050; font-family:Arial; font-size:14px; line-height:150%; text-align:left;">
        <span><?php print $node['icon']; ?></span>
        <a href='<?php print $node['link']; ?>' >
          <span style="font-size:15px; font-weight:normal; overflow:auto; margin-left: 5px; font-weight: bold; color: #0074A6">
            <?php print $node['title']; ?>
          </span>
        </a>
      </td>
    </tr>
    <?php endforeach; ?>
  </tbody>
</table>
