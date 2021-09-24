<style>
body{
  font-family: Roboto, Arial, sans-serif;
}
</style>
    <?php if ($role_member == 'MEM'){ ?>
    <table width='98%' cellpadding='0' cellspacing='0' style=' border: 1px solid; border-color: #ddd; margin-left: 10px; margin-right: 10px; border-radius: 4px;  -webkit-box-shadow: 0 1px 1px rgba(0,0,0,.05); box-shadow: 0 1px 1px rgba(0,0,0,.05); margin-bottom: 10px;'>    
       <tr><td>    
          <table width='100%' cellpadding='0' cellspacing='0' bgcolor='#f5f5f5' style=' background-color: #f5f5f5; border-bottom: 1px solid;  border-color: #ddd;'>
              <tr>    
              <td style='padding-left:15px;'> <h4 style='margin-top: 10px; margin-bottom: 10px; color: #31708f;'> <?php print t('Spaces',array(), $l); ?> </h4></td>    
              </tr>
          </table>    
       </td></tr>    
       <tr><td>    
           <table width='100%' cellpadding='0' cellspacing='0'>
               <tr>    
                  <td style='color: #333; padding-left:10px; padding-top:10px; font-size: 14px; padding-right: 10px; padding-bottom: 10px;'> 
                      <?php print t('You have been removed from the following spaces :',array(), $l) ; 
                            print $grps; ?>
                  </td>    
               </tr>
           </table>    
       </td></tr>    
    </table >   
     <?php } ?>
    
    <table width='98%' cellpadding='0' cellspacing='0' style=' border: 1px solid; border-color: #ddd; margin-left: 10px; margin-right: 10px; border-radius: 4px;  -webkit-box-shadow: 0 1px 1px rgba(0,0,0,.05); box-shadow: 0 1px 1px rgba(0,0,0,.05); margin-bottom: 10px;'>    
       <tr><td>    
          <table width='100%' cellpadding='0' cellspacing='0' bgcolor='#f5f5f5' style=' background-color: #f5f5f5; border-bottom: 1px solid;  border-color: #ddd;'>
              <tr>    
                 <td style='padding-left:15px;'> <h4 style='margin-top: 10px; margin-bottom: 10px; color: #31708f;'><?php print t('Message',array(), $l); ?></h4></td>    
              </tr>
          </table>    
       </td></tr>    
       <tr><td>    
           <table width='100%' cellpadding='0' cellspacing='0'>
               <tr>    
                 <td style='color: #333; padding-left:10px; padding-top:10px; font-size: 14px; padding-right: 10px; padding-bottom: 10px;'> <?php print $mess ?></td>    
               </tr>
           </table>    
       </td></tr>    
    
     <?php if ($role_member == 'MEM'){ ?>
     <table width='98%' cellpadding='0' cellspacing='0' style=' border: 1px solid; border-color: #ddd; margin-left: 10px; margin-right: 10px; border-radius: 4px;  -webkit-box-shadow: 0 1px 1px rgba(0,0,0,.05); box-shadow: 0 1px 1px rgba(0,0,0,.05); margin-bottom: 10px;'>    
       <tr><td>    
           <table width='100%' cellpadding='0' cellspacing='0' bgcolor='#d9edf7' style=' background-color: #d9edf7; border-bottom: 1px solid;  border-color: #bce8f1;'>
               <tr>    
                 <td style='padding-left:15px;'> <h4 style='margin-top: 10px; margin-bottom: 10px; color: #31708f;'><?php print t('Notes',array(), $l); ?> </h4></td>    
               </tr>
           </table>    
       </td></tr> 
       
       <tr><td>    
            <table width='100%' cellpadding='0' cellspacing='0'>
                <tr>    
                  <td style='padding-left:10px; font-size: 14px; color: #333; padding-top:10px; padding-right: 10px; padding-bottom: 10px; display: inline-block;'><?php
                    print t("You've been automatically unSubscribed from this spaces.", array(), $l);?></td>    
                </tr>
            </table>    
       </td></tr> 
       
     </table > 
     <?php } ?>