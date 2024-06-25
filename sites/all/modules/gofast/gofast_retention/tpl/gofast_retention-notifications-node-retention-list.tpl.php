<div class="mj-column-per-90 mj-outlook-group-fix" style="font-size:0px;text-align:left;direction:ltr;display:inline-block;vertical-align:top;width:100%;">
  <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="vertical-align:top;" width="100%">
    <tbody>
    <tr>
      <td align="left" style="font-size:0px;padding:10px 25px;word-break:break-word;">
        <div style="font-family: Poppins, Helvetica, Arial, sans-serif;font-size:13px;line-height:1;text-align:left;color:#000000;">
          <table border="0" cellpadding="0" cellspacing="0" role="presentation" style="vertical-align:middle;">
            <tbody>
            <?php foreach ($nodes as $node): ?>
              <tr>
                <td style="color:#505050; font-family:Arial; font-size:14px; line-height:150%; text-align:left;">
                  <?php 
                    $node_icon = str_replace('<span>', '<span style="display:none;">', theme('node_title', array('node' => node_load($node['nid']), 'link' => FALSE)));
                    echo gofast_mail_queue_fa_png($node_icon);
                  ?>
                  <a href='<?php print $node['link']; ?>' >
                    <span style="font-size:15px; font-weight:normal; overflow:auto; margin-left: 5px; font-weight: bold; color: #0074A6">
                      <?php print $node['title']; ?>
                    </span>
                  </a>
                </td>
              </tr>
              <br/>
            <?php endforeach; ?>
            </tbody>
          </table>
        </div>
      </td>
    </tr>
    </tbody>
  </table>
</div>
