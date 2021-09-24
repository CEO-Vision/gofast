<div class="panel panel-dashboard panel-default">
  <div class="panel-heading">
    <div class="row">
      <div class="col-sm-11" style="font-weight: bold">
        <?php print t('Memos', array(), array('context' => 'gofast_dashboard')) ?>
      </div>
      <div class="col-sm-1">
       <!-- <a href="/node/add/conference" data-toggle="tooltip" title="<?php //echo t('Create new meeting', array(), array('context' => 'gofast_cdel')); ?>" >
          <?php //if (gofast_mobile_is_mobile_domain() == FALSE){ ?>
              <span class="fa fa-plus"></span>
          <?php //} ?>
        </a>-->
      </div>
    </div>
  </div>
  <div class="panel-body dashboard-memo-placeholder">
    <div class="loader-dashboard-block"></div>
  </div>
</div>

  <script type='text/javascript'>
   jQuery(document).ready(function(){
      jQuery.post(location.origin+"/dashboard/ajax/memo", function(data){
        jQuery(".dashboard-memo-placeholder").find(".loader-dashboard-block").remove();
        jQuery(".dashboard-memo-placeholder").prepend(data);
        jQuery('#table_memo > tbody').pager({pagerSelector : '#memo_pager', perPage: 4, numPageToDisplay : 5});
      });
    });
    
  </script>