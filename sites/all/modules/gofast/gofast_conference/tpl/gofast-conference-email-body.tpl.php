<style>
@import url(http://fonts.googleapis.com/css?family=Roboto);
td {
  font-size: 13px;
}

#conference-links{
  margin: 0 auto;
  display: table;
}
.btn-group, .btn-group-vertical {
    position: relative;
    display: inline-block;
    vertical-align: middle;
}
.btn-group > .btn:first-child:not(:last-child):not(.dropdown-toggle) {
    border-bottom-right-radius: 0;
    border-top-right-radius: 0;
}
.btn-group > .btn:first-child {
    margin-left: 0;
}
.btn-group > .btn, .btn-group-vertical > .btn {
    position: relative;
    float: left;
}
a:link, a:visited, a:hover, a:active, a:focus {
    outline: none;
    text-decoration: none;
}
.btn-success {
    color: #ffffff;
    background-color: #5cb85c;
    border-color: #4cae4c;
}
.btn {
    display: inline-block;
    margin-bottom: 0;
    font-weight: normal;
    text-align: center;
    vertical-align: middle;
    touch-action: manipulation;
    cursor: pointer;
    background-image: none;
    border: 1px solid transparent;
    white-space: nowrap;
    padding: 6px 12px;
    font-size: 14px;
    line-height: 1.42857143;
    border-radius: 4px;
    -webkit-user-select: none;
    -moz-user-select: none;
    -ms-user-select: none;
    user-select: none;
}

.btn-group > .btn:not(:first-child):not(:last-child):not(.dropdown-toggle) {
    border-radius: 0;
}
.btn-group .btn + .btn, .btn-group .btn + .btn-group, .btn-group .btn-group + .btn, .btn-group .btn-group + .btn-group {
    margin-left: -1px;
}
.btn-group > .btn, .btn-group-vertical > .btn {
    position: relative;
    float: left;
}
.btn-default {
    color: #333333;
    background-color: #ffffff;
    border-color: #cccccc;
}
.list-group-item:last-child {
    margin-bottom: 0;
    border-bottom-right-radius: 4px;
    border-bottom-left-radius: 4px;
}
.list-group-item:first-child {
    border-top-right-radius: 4px;
    border-top-left-radius: 4px;
}
.list-group-item {
    position: relative;
    display: block;
    padding: 10px 15px;
    margin-bottom: -1px;
    background-color: #ffffff;
    border: 1px solid #dddddd;
}
.user-picture {
    display: inline-block;
}
.profile-popup-wrapper {
    position: absolute;
    z-index: 999;
}
img.little{
  width: 10px;
  height: 10px;
}
.list-group{
  padding-left: 0;
}
body{
  font-family: Roboto, Arial, sans-serif;
}
</style>

  <?php
    if(!$delete){
  ?>
   <table width="98%" cellpadding="0" cellspacing="0" style="margin-left: 10px; margin-right: 10px; border-radius: 4px;  -webkit-box-shadow: 0 1px 1px rgba(0,0,0,.05); box-shadow: 0 1px 1px rgba(0,0,0,.05); margin-bottom: 10px;">
        <tr>
          <td width="42%"></td>
          <td width="16%">
            <table width="100%" cellpadding="5" cellspacing="0" bgcolor="#5cb85c" style="border-radius: 4px; padding: 5px; background-color: #5cb85c; border-bottom: 1px solid;  border-color: #4cae4c;">
              <tr>
                <td style="text-align: center;">
                   <a target="_blank" href="<?php print $conference_url_external ?>" style="text-decoration: none; color: #fff;"><?php print t('Go to the conference') ?></a>
                </td>               
              </tr>
          </table>
          </td>
          <td width="42%"></td>
        </tr>
      </table>
  <div style='margin-top:10px;text-align:center;'><a href="<?php print str_replace(CONFERENCE_URL, "https://meet.jit.si", $conference_url_external); ?>" target="_blank"><?php print t("If you find any problems, all participants can try to use this link (shared Jitsi SaaS)"); ?></a></div>
    <?php } ?>

  <?php if(isset ($conference_content) && $conference_content !== ""){ ?>
    <table width="98%" cellpadding="0" cellspacing="0" style="border: 1px solid; border-color: #bce8f1;   margin-left: 10px; margin-right: 10px; border-radius: 4px;  -webkit-box-shadow: 0 1px 1px rgba(0,0,0,.05); box-shadow: 0 1px 1px rgba(0,0,0,.05); margin-bottom: 10px;">
        <tr>
          <td>
            <table width="100%" cellpadding="0" cellspacing="0" bgcolor="#d9edf7" style=" background-color: #d9edf7; border-bottom: 1px solid;  border-color: #bce8f1;">
              <tr>
                <td style="padding-left:15px;">
                  <h4 style="margin-top: 10px; margin-bottom: 10px; color: #31708f;"><?php print t('Informations') ?></h4>
                </td>
              </tr>
          </table>
          </td>
        </tr>
        <tr>
          <td>
            <table width="100%" cellpadding="0" cellspacing="0">
            <tr>
              <td valign="middle" style="color:#505050; font-family:Arial; font-size:14px; line-height:150%; text-align:left; padding: 10px 15px;">
                <?php print $conference_content; ?>
              </td>
            </tr>
          </table>
          </td>
        </tr>
      </table> 
<!-- Table spacer -->
<table><div></div></table>
<table><div></div></table>
  <?php } ?>

  <?php if(isset ($conference_documents) && $conference_documents !== ""){ ?>
      <table width="98%" cellpadding="0" cellspacing="0" style="border: 1px solid; border-color: #bce8f1;   margin-left: 10px; margin-right: 10px; border-radius: 4px;  -webkit-box-shadow: 0 1px 1px rgba(0,0,0,.05); box-shadow: 0 1px 1px rgba(0,0,0,.05); margin-bottom: 10px;">
        <tr>
          <td>
            <table width="100%" cellpadding="0" cellspacing="0" bgcolor="#d9edf7" style=" background-color: #d9edf7; border-bottom: 1px solid;  border-color: #bce8f1;">
              <tr>
                <td style="padding-left:15px;">
                  <h4 style="margin-top: 10px; margin-bottom: 10px; color: #31708f;"><?php print t('Documents') ?></h4>
                </td>
              </tr>
          </table>
          </td>
        </tr>
        <tr>
          <td>
            <table width="100%" cellpadding="0" cellspacing="0">
            <tr>
              <td valign="middle" style="color:#505050; font-family:Arial; font-size:14px; line-height:150%; text-align:left; padding: 10px 15px;">
                <?php print $conference_documents ?>
              </td>
            </tr>
          </table>
          </td>
        </tr>
      </table> 
<!-- Table spacer -->
<table><div></div></table>
<table><div></div></table>
  <?php } ?>

  <?php if(isset ($conference_folders) && $conference_folders !== ""){ ?>
      <table width="98%" cellpadding="0" cellspacing="0" style="border: 1px solid; border-color: #bce8f1;   margin-left: 10px; margin-right: 10px; border-radius: 4px;  -webkit-box-shadow: 0 1px 1px rgba(0,0,0,.05); box-shadow: 0 1px 1px rgba(0,0,0,.05); margin-bottom: 10px;">
        <tr>
          <td>
            <table width="100%" cellpadding="0" cellspacing="0" bgcolor="#d9edf7" style=" background-color: #d9edf7; border-bottom: 1px solid;  border-color: #bce8f1;">
              <tr>
                <td style="padding-left:15px;">
                  <h4 style="margin-top: 10px; margin-bottom: 10px; color: #31708f;"><?php print t('Linked folders') ?></h4>
                </td>
              </tr>
          </table>
          </td>
        </tr>
        <tr>
          <td>
            <table width="100%" cellpadding="0" cellspacing="0">
            <tr>
              <td valign="middle" style="color:#505050; font-family:Arial; font-size:14px; line-height:150%; text-align:left; padding: 10px 15px;">
                <?php print $conference_folders ?>
              </td>
            </tr>
          </table>
          </td>
        </tr>
      </table> 
<!-- Table spacer -->
<table><div></div></table>
<table><div></div></table>
  <?php } ?>

      <table width="98%" cellpadding="0" cellspacing="0" style="border: 1px solid; border-color: #bce8f1;   margin-left: 10px; margin-right: 10px; border-radius: 4px;  -webkit-box-shadow: 0 1px 1px rgba(0,0,0,.05); box-shadow: 0 1px 1px rgba(0,0,0,.05); margin-bottom: 10px;">
        <tr>
          <td>
            <table width="100%" cellpadding="0" cellspacing="0" bgcolor="#d9edf7" style=" background-color: #d9edf7; border-bottom: 1px solid;  border-color: #bce8f1;">
              <tr>
                <td style="padding-left:15px;">
                  <h4 style="margin-top: 10px; margin-bottom: 10px; color: #31708f;"><?php print t('Participants') ?></h4>
                </td>
              </tr>
          </table>
          </td>
        </tr>
        <tr>
          <td>
            <table width="100%">
              <tr>
                <td width="50%">
                  <div><strong><?php print t('%site_name participants', array('%site_name' => variable_get('site_name', 'GoFAST'))) ?></strong></div>
                </td>
                <td width="50%">
                  <div><strong><?php print t('Other participants') ?></strong></div>
                </td>
              </tr>
              <tr>
                <td width="50%">
                  <div>         
                      <?php print $gofast_participants; ?>
                      <div style='clear:both;'></div>
                  </div>
                </td>
                <td width="50%">
                  <div>
                    <ul class="list-group">
                      <?php print $other_participants; ?>
                    </ul>
                    <div style='clear:both;'></div>
                  </div>
                </td>
              </tr>
              <tr>
                <td width="50%">
                  <div><strong><?php print t('Meeting Owner'); ?></strong></div>
                </td>
                <td width="50%">
                  <div><strong><?php print t('Meeting Date');  ?></strong></div>
                </td>
              </tr>
              <tr>
                <td width="50%">
                  <div>
                    <?php print $conference_owner; ?>
                    <div style='clear:both;'></div>
                  </div>
                </td>
                <td width="50%">
                  <div>
                    <?php print $conference_datetime; ?><br /><?php print $conference_end_datetime; ?>
                    <div style='clear:both;'></div>
                  </div>
                </td>
              </tr>
            </table>
          </td>
        </tr>
      </table>
       <!-- Table spacer -->
    <table><div></div></table>
    <table><div></div></table>
    <table width="98%" cellpadding="0" cellspacing="0" style="border: 1px solid; border-color: #bce8f1;   margin-left: 10px; margin-right: 10px; border-radius: 4px;  -webkit-box-shadow: 0 1px 1px rgba(0,0,0,.05); box-shadow: 0 1px 1px rgba(0,0,0,.05); margin-bottom: 10px;">
        <tr>
          <td>
            <table width="100%" cellpadding="0" cellspacing="0" bgcolor="#d9edf7" style=" background-color: #d9edf7; border-bottom: 1px solid;  border-color: #bce8f1;">
              <tr>
                <td style="padding-left:15px;">
                  <h4 style="margin-top: 10px; margin-bottom: 10px; color: #31708f;"><?php print t('Advices') ?></h4>
                </td>
              </tr>
          </table>
          </td>
        </tr>
        <tr>
          <td>
            <table width="100%">
              <tr>
                <td width="50%">
                  <div><strong><?php print t('Recommended browsers') ?></strong></div>
                </td>
                <td width="20%">
                  <div><a style="text-decoration:none" href='https://gofast-docs.readthedocs.io/fr/latest/docs-gofast-users/doc-gofast-guide-utilisateurs.html#pre-requis-necessaires-pour-lutilisation-de-gofast'><?php print t("Usage tips")?></a></div>
                </td>
                <td width="30%">
                    <div></div>
                </td>
              </tr>
              <tr>
                <td width="50%">
                  <div>         
                      Firefox 76+<br/>
                      Firefox ESR 78+<br/>
                      Google Chrome<br/>
                      Safari<br/>
                      Chromium Edge
                  </div>
                </td>
                <td width="20%">
                  <div>
                    <!-- <a style="text-decoration:none" href="<?php // print $conference_url_test ?>">Test</a> -->
                  </div>
                </td>
                <td width="30%">
                    <div></div>
                </td>
              </tr>
            </table>
          </td>
          <tr>
          <td>
            <table width="100%" cellpadding="0" cellspacing="0">
              <tr>
                <td style="padding-left:15px;">
                    <div><?php t('We recommend you to use the same browser as the other members of the conference.')?></div>
                </td>
              </tr>
          </table>
          </td>
        </tr>
        </tr>
      </table>
    