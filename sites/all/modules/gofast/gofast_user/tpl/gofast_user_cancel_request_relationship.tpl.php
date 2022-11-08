<?php
?>

<!-- Title div. Title of the body -->
<table width="95%" cellpadding="0" cellspacing="0" style="margin-bottom: 20px;">
  <tr style="margin-bottom: 20px;">
    <td>
      <table width="100%" cellpadding="0" cellspacing="0">
        <tr>
          <td style="font-size:14px; color: #515151;">
            <center><?php print t('Hello ', array(), $l); print_r ($recipName.","); ?></center>
          </td>
        </tr>
      </table>        
    </td>
  </tr>
  <tr>
    <td>
      <table width="98%" cellpadding="0" cellspacing="0" style="padding-left:10px; padding-right: 10px; margin-top:20px;">
        <tr>
          <td valign="bottom" style="padding-left:10px; width: 50px;">
            <?php print $author_pic; ?>
          </td>
          <td valign="middle" style="text-align: left; font-size:14px; color: #515151;">
              <?php print t('%relationshipSeeker cancelled his relationship request on %siteName.', array('%relationshipSeeker' => $relationshipSeeker, '%siteName' => $siteName), $l); ?>
          </td>
        </tr>
      </table>
    </td>
  </tr>
</table>
<!-- Table spacer -->
<table><div></div></table>
<table><div></div></table>                                     

