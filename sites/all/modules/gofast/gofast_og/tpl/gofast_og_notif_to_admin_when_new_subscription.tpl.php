<?php
?>

<style>
body{
  font-family: Roboto, Arial, sans-serif;
}
</style>

<!-- Information Panel -->
<table width="98%" cellpadding="0" cellspacing="0" style="border: 1px solid; border-color: #ddd; margin-left: 10px; margin-right: 10px; border-radius: 4px;  -webkit-box-shadow: 0 1px 1px rgba(0,0,0,.05); box-shadow: 0 1px 1px rgba(0,0,0,.05); margin-bottom: 10px;">
  <tr>
    <td>
      <table width="100%" cellpadding="0" cellspacing="0" bgcolor="#f5f5f5" style=" background-color: #f5f5f5; border-bottom: 1px solid;  border-color: #ddd;">
        <tr>  
          <td style="padding-left:15px;">
            <h4 style="margin-top: 10px; margin-bottom: 10px; color: #31708f;"><?php print t('Action',array(), $l); ?></h4>
          </td>
        </tr>
    </table>
    </td>
  </tr>
  <tr>
    <td>
      <table width="100%" cellpadding="0" cellspacing="0">
        <tr>
          <td style="padding-left:10px; font-size: 14px; color: #333; padding-top:10px; padding-right: 10px; display: inline-block;">
            <?php 
              print "<p style='padding-bottom: 10px;' >" . t("%AuthorName added a user in %nameSpace", array("%AuthorName" => $AuthorName, '%nameSpace' => $nameSpace), $l) . "</p>"; 
            ?>
          </td>
        </tr>
      </table>
    </td>
  </tr>
</table>

<!-- Table spacer -->
<table><div></div></table>
<table><div></div></table

<!-- Information Panel -->
<table width="98%" cellpadding="0" cellspacing="0" style="border: 1px solid; border-color: #ddd; margin-left: 10px; margin-right: 10px; border-radius: 4px;  -webkit-box-shadow: 0 1px 1px rgba(0,0,0,.05); box-shadow: 0 1px 1px rgba(0,0,0,.05); margin-bottom: 10px;">
  <tr>
    <td>
      <table width="100%" cellpadding="0" cellspacing="0" bgcolor="#f5f5f5" style=" background-color: #f5f5f5; border-bottom: 1px solid;  border-color: #ddd;">
        <tr>  
          <td style="padding-left:15px;">
            <h4 style="margin-top: 10px; margin-bottom: 10px; color: #31708f;"><?php print t('Added user',array(), $l); ?></h4>
          </td>
        </tr>
    </table>
    </td>
  </tr>
  <tr>
    <td>
      <table width="100%" cellpadding="0" cellspacing="0">
        <tr>
          <td style="padding-left:10px; font-size: 14px; color: #333; padding-top:10px; padding-right: 10px; display: inline-block;">
            <ul>
              <?php 
                foreach ($members['users'] as $uid){
                  $user = user_load($uid);
                  print "<li>" . gofast_user_display_name($user). print "</li>";
                }
                 foreach ($members['userlists'] as $ulid){
                  $userlist = entity_load_single('userlist', $ulid);
                  print "<li>" . $userlist->name." ".t("(userlist)", array(), $l)."</li>";
                }
              ?>
            </ul>
          </td>
        </tr>
      </table>
    </td>
  </tr>
</table>
<!-- Table spacer -->
<table><div></div></table>
<table><div></div></table>
