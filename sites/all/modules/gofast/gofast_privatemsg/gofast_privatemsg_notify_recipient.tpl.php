
<style>
body{
  font-family: Roboto, Arial, sans-serif;
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

</style>                                                
<!--[if mso]><!-- -->
<style>
</style>
<!--<![endif]-->


<!-- Title div. Title of the body -->
<table width="100%" cellpadding="0" cellspacing="0" style="margin-bottom: 20px;">
  <tr style="margin-bottom: 20px;">
    <td>
      <table width="100%" cellpadding="0" cellspacing="0">
        <tr>
        
        </tr>
      </table>        
    </td>
  </tr>
  <tr>
    <td>
      <table width="98%" cellpadding="0" cellspacing="0" style="padding-left:10px; padding-right: 10px; margin-top:20px;">
        <tr>
          <td valign="bottom" style="padding-left:10px; width: 50px;">
            <?php print $sender_picture; ?>
          </td>
          <td valign="middle" style="text-align: left; font-size:14px; color: #515151;">
            <?php
              print $sender;
              print t(' sent you a private message ', array(), $l);         
            ?>
              <a href='<?php echo $response_link; ?>'><button type="button" class="btn btn-success">
                <i class="fa fa-trash"></i> <?php echo $response_icon; ?>
              </button><a/>
          </td>
        </tr>
      </table>
    </td>
  </tr>
</table>
<!-- Table spacer -->
<table><div></div></table>
<table><div></div></table>

<!-- Subject Panel -->
<table width="98%" cellpadding="0" cellspacing="0" style=" border: 1px solid; border-color: #ddd; margin-left: 10px; margin-right: 10px; border-radius: 4px;  -webkit-box-shadow: 0 1px 1px rgba(0,0,0,.05); box-shadow: 0 1px 1px rgba(0,0,0,.05); margin-bottom: 10px;">
  <tr>
    <td>
      <table width="100%" cellpadding="0" cellspacing="0" bgcolor="#f5f5f5" style=" background-color: #f5f5f5; border-bottom: 1px solid;  border-color: #bce8f1;">
              <tr>
                <td style="padding-left:15px;">
                  <h4 style="margin-top: 10px; margin-bottom: 10px; color: #31708f;"><?php print $subject; ?></h4>
                </td>
              </tr>
      </table>
    </td>
  </tr>
  <tr>
    <td>
      <table width="100%" cellpadding="0" cellspacing="0">
        <tr>
          <td style=" color: #333; padding-left:10px; padding-top:10px; font-size: 14px; padding-right: 10px; padding-bottom: 10px;">
                  <?php 
                    if (empty($message)){
                    }
                    else{
                      print $message;
                    }
                  ?>
          </td>
        </tr>
      </table>
    </td>
  </tr>            
</table>
<!-- Table spacer -->
<table><div></div></table>
<table><div></div></table>

<!-- Table spacer -->
<table><div></div></table>
<table><div></div></table>                 
