<?php if(!$ajax){ 
    print theme('gofast_dashboard_dashboard_breadcrumb', array("activity" => TRUE));
?>
<div id="activity-feed-container" class="panel panel-default">
  <div id="gofast-blog-container"></div>
<?php } ?>
  <div id="activity-feed" class="panel-body">
    <table id="activity-feed-table" class="table">
      <tr>
        <th></th>
        <th><?php echo t('Last event', array(), array('context' => 'gofast')); ?></th>
        <th><?php echo t('Title', array(), array('context' => 'gofast')); ?></th>
        <th><?php echo t('Spaces', array(), array('context' => 'gofast')); ?></th>
        <th><?php echo t('Popularity', array(), array('context' => 'gofast')); ?></th>
        <th><?php echo t('State', array(), array('context' => 'gofast')); ?></th>
      </tr>
      <!-- Fill the table -->
      <?php echo $table_content; ?>
    </table>
    <hr />
    <?php if(!empty($table_content) || !$ajax){ ?>
    <div class="loader-activity-feed"></div>
    <?php }else{
        print "<center>" . t("The activity feed is empty with these filters", array(), array('context' => "gofast")) . "<center><br />";
    } ?>
    <ul id="activity-feed-pagination" class="pagination" style="display: none; margin: 0 auto; display: table;">
    </ul>
  </div>
</div>
<span id="activity-feed-page" style="display: none;"><?php echo $page; ?></span>


<?php if(gofast_mobile_is_mobile_domain()){ ?>
<style>
    @media (min-width: 768px){
        .col-sm-9 {
            width: 100%;
        }
    }
</style>

<?php } ?>