<style>
@import url(http://fonts.googleapis.com/css?family=Roboto);
.panel {
  margin-bottom: 20px;
  background-color: #fff;
  border: 1px solid transparent;
  border-radius: 4px;
  -webkit-box-shadow: 0 1px 1px rgba(0,0,0,.05);
  box-shadow: 0 1px 1px rgba(0,0,0,.05);
  margin-left: 10px;
  margin-right: 10px;
}
.panel-default {
  border-color: #ddd;
}
.panel-default>.panel-heading {
  color: #333;
  background-color: #f5f5f5;
  border-color: #ddd;
}
.panel-body {
  padding: 15px;
}
.panel-primary {
  border-color: #337ab7;
}
.panel-info {
  border-color: #bce8f1;
}
.panel-primary > .panel-heading {
  color: #ffffff;
  background-color: #337ab7;
  border-color: #337ab7;
}
.panel-info > .panel-heading {
    color: #31708f;
    background-color: #d9edf7;
    border-color: #bce8f1;
}
.panel-heading {
  display: block;
  padding: 10px 15px;
  border-bottom: 1px solid transparent;
  border-top-right-radius: 3px;
  border-top-left-radius: 3px;
}

.panel-title {
  margin-top: 0;
  margin-bottom: 0;
  font-size: 16px;
  color: inherit;
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
img{
  width: 20px;
  height: 20px;
}
.list-group{
  padding-left: 0;
}
body{
  font-family: Roboto, Arial, sans-serif;
} 
</style>

<div class="panel panel-info">
    <div class="panel-heading">
      <h3 class="panel-title"><b><?php print t('Security action', array(), $l) ;?></b></h3>
    </div>
    <div class="panel-body">
      <table width="100%">
        <tr>
          <td>
            <div  style="margin-top:10px; color: #666666; font-family: Arial; font-size: 13px; font-weight: normal; line-height: 150%;">
                <?php print t('The user !userBlocked has been blocked from @site_name due to successive failed login attempts.', array('!userBlocked' => $userBlocked, '@site_name' => $site_name), $l); ?>
                <?php print t("You can unblock this user in it's profile.", array(), $l); ?>
              </a>                
            </div>               
          </td>
        </tr>
      </table>
    </div>
  </div>