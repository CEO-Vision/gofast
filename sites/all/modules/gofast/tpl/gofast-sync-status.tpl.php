<?php
  if($sync_progress){
    print "<div class='loader-sync-status'></div><p>". t('Synchronization in progress', array(), array('context' => 'gofast:gofast_ldap')) ."</p>";
  }else if($next_sync <= time()){
    print "<div class='loader-sync-status'></div><p>". t('A synchronization is about to start', array(), array('context' => 'gofast:gofast_ldap')) ."</p>";
  }else{
    ?>
<table>
  <tr>
    <td style="width: 30px;">
      <i class="fa fa-check" style='color: #5cb85c;' aria-hidden="true"></i>
    </td>
    
    <td>
      <?php echo t('The directories are synchronized', array(), array('context' => 'gofast:gofast_ldap')); ?>
    </td>
  </tr>
  <tr>
    <td style="width: 30px;">
      <i class="fa fa-clock-o" style='color: #337ab7;' aria-hidden="true"></i>
    </td>
    
    <td>
      <?php echo t('Last synchronization: ', array(), array('context' => 'gofast:gofast_ldap')) . format_date($last_sync, "custom", "m-d-Y H:i"); ?>
    </td>
  </tr>
  <tr>
    <td style="width: 30px;">
      <i class="fa fa-arrow-right" style='color: #337ab7;' aria-hidden="true"></i>
    </td>
    
    <td>
      <?php echo t('Next synchronization: ', array(), array('context' => 'gofast:gofast_ldap')) . format_date($next_sync, "custom", "m-d-Y H:i"); ?>
    </td>
  </tr>
</table>
    <?php
  }