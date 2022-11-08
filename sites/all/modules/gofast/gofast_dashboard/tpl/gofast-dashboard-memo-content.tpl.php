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
<?php global $language ?>
<table id="table_memo" class="table table-hover table-striped" style="margin-bottom: -8px;" >
    <thead></thead>
    <tbody>
          <?php if(count($user_memos) > 0): ?>
            <?php foreach ($user_memos as $memo): ?>
        <tr>
            <td>              
                <span class="">                   
                    <?php echo theme('user_picture', array('account' => user_load($memo->uid), 'dimensions' => 15)) ?>
                </span>            
            </td>
            <td>              
                <span class="dashboard-block-ellipses ellipses-large">                   
                    <?php echo $memo->body[LANGUAGE_NONE][0]["value"] ?>
                </span>            
            </td>
        </tr>
            <?php endforeach; ?>
          <?php else: ?>
        <tr>
            <td><?php echo t('No memo.', array(), array('context' => 'gofast_dashboard')) ?></td>
        </tr> 
          <?php endif; ?>
    </tbody>
</table>

<nav class="text-center mt-4">
    <ul class="pagination pagination-sm justify-content-center" id="memo_pager"></ul>
</nav>
<script>
    jQuery("document").ready(function() {
        jQuery('.dashboard-block-ellipses > p').addClass('m-0');
    })
</script>
