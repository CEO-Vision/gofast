<?php
/**
 * @file
 * Displays list of incoming meetings (conference) for logged user
 *
 * Available variables:
 * - $user_meetings: List of meetings. It contains :
 *  - $meeting : Conference object (only field selected from the query in preprocess). it contains:
 *    - $meeting->title : conference name
 *    - $meeting->field_date_value : conference starting date
 *    - $meeting->gf_participants : comma separated name of conference participant (user gofast)
 *    - $meeting->ext_participants : comma separated email of conference participant (not gofast user)
 * - $language : plateforme current language (used for translation)
 *
 * @see template_preprocess_gofast_cdel_dashboard_meetings()
 *
 * @ingroup themeable
 */

?>

<div class="panel panel-dashboard panel-dashboard-big panel-default">
  <div class="panel-heading">
    <div class="row">
    </div>
  </div>
  <div class="panel-body dashboard-folders-placeholder">
   <?php global $language ?>
    <table id="table_favorite_path" class="table table-hover table-striped" style="margin-bottom: -8px;" >
        <thead></thead>
        <tbody>
          <?php if(count($favorite_folders) > 0): ?>
            <?php foreach ($favorite_folders as $folder): ?>
            <tr>
              <td>              
                  <span class="">                   
                    <?php echo $folder["icon"]; ?>
                    <?php echo $folder["link"]; ?>                   
                  </span>            
              </td>            
            </tr>
            <?php endforeach; ?>
          <?php else: ?>
              <tr>
                <td><?php echo t('No favorite path.', array(), array('context' => 'gofast_dashboard')) ?></td>
              </tr> 
          <?php endif; ?>
        </tbody>
    </table>
    
    <nav class="text-center" style="margin-top:15px;">
        <ul class="pagination" style="margin-top:25px;margin-bottom:5px;" id="path_pager"></ul>
    </nav>
  </div>
</div>

  <script type='text/javascript'>
   jQuery(document).ready(function(){
         jQuery('#table_favorite_path > tbody').pager({pagerSelector : '#path_pager', perPage: 9, numPageToDisplay : 5, showPrevNext: true});
    });
    
  </script>