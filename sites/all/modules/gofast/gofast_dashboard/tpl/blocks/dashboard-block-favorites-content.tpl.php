<?php

/*
 * Template file for flag bookmarks
 * Used in dashboard cards for the group shortcuts and favorite contents
 * We print the icon, link that we retrieved before calling the hook_theme(), and the node actions
 * 
 * Implemented pagination is the same as the memo one
 */
$all_flags = gofast_dashboard_get_all_flags('content');
$type = 'content';
?>
<table class="table table-hover table-striped" id="table_bookmarks_<?php echo $type; ?>" style="table-layout:fixed">
    <thead>
        
    </thead>
    <tbody>
        <?php foreach($all_flags['content'] as $el) : ?>
        <tr>
            <td class="dashboard-favorite-content-wrap w-75">
                <?php print $el['icon']; ?>
                <span title="<?php if(!empty($el['title'])) : echo $el['title']; endif; ?>"><?php print $el['link']; ?></span>
            </td>
            <?php if(!empty($el['node_actions'])): ?>
                <td class="w-25" style="text-right">
                    <?php print $el['node_actions']; ?>
                </td>
            <?php endif; ?>
        </tr>
        <?php endforeach; ?>
    </tbody> 
</table>
<nav class="text-center mt-6 dashboard-pagination-bottom">
    <ul class="pagination pagination-sm justify-content-center" id="bookmark_pager_<?php echo $type; ?>"></ul>
</nav>
<script type='text/javascript'>
    jQuery(document).ready(function(){
        jQuery(".gofast-node-actions > a").addClass('p-0');
        jQuery('#table_bookmarks_<?php echo $type; ?> > tbody').pager({pagerSelector : '#bookmark_pager_<?php echo $type; ?>', perPage: 7, numPageToDisplay : 5});
    });   
</script>

<style>
.w-25 > .gofast-node-actions{
   text-align: right !important;
   display:block !important;
}
</style>
