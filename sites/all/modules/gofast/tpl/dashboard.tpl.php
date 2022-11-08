<div class="panel panel-default">
  <div class="panel-heading"><?php echo t('Services', array(), array('context' => 'gofast:dashboard')); ?></div>
  <div class="panel-body">
    <div id='gofast_dashboard_container' >
      <table style="table-layout: fixed;width:100%">
        <tr>
          <td><?php echo $alfresco_status; ?></td>
          <td><?php echo $bonita_status; ?></td>
          <td><?php echo $solr_status; ?></td>
        </tr>
        <tr>
          <td><?php echo $soffice_status; ?></td>
          <td><?php echo $cron_status; ?></td>
        </tr>
      </table>
    </div>
  </div>
</div>

<div class="panel panel-default">
  <div class="panel-heading"><?php echo t('Configurations', array(), array('context' => 'gofast:dashboard')); ?></div>
  <div class="panel-body">
    <div id='gofast_dashboard_config_container' >
      <div class="panel panel-default">
        <div class="panel-heading">my.cnf</div>
        <div class="panel-body">
          <div id='gofast_dashboard_config_mycnf_container' >
            <?php 
              if(file_exists("/var/www/d7/sites/default/files/my.cnf")){
                print t("Applying configuration...") . " <div class='loader-actions'></div>";
              }else{
                print drupal_render(drupal_get_form("gofast_configure_mycnf_form"));
              }
            ?>
          </div>
        </div>
      </div>
    </div>
  </div>
</div>