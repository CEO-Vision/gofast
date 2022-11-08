    <!--begin::Body-->
    <div class="dashboard-folders-placeholder">
        <?php global $language; ?>
        <table id="table_favorite_path" class="table table-hover table-striped">
            <thead></thead>
            <tbody>
                <?php if (count($favorite_folders) > 0) : ?>
                    <?php foreach ($favorite_folders as $folder) : ?>
                        <tr>
                            <td>
                                <span class="">
                                    <?php echo $folder["icon"]; ?>
                                    <?php echo $folder["link"]; ?>
                                </span>
                            </td>
                            <td class="pr-8 text-right">
                                <a href="<?php echo $folder["unthemed_link"]; ?>" title="<?php echo t('Go to file browser', array(), array('context' => 'gofast:gofast_dashboard')); ?>" style="margin-right: 8px;">
                                    <span class="fa fa-arrow-right"></span>
                                </a>
                                <a href="#" onClick="Gofast.ITHit.unbookmarkFolder('/alfresco/webdav<?php echo $folder['unthemed_path']; ?>'); $(this).parent().parent().remove(); jQuery('#table_favorite_path > tbody').pager({pagerSelector : '#path_pager', perPage: 9, numPageToDisplay : 5, showPrevNext: false});">
                                    <span class="fa fa-trash" title="<?php echo t('Remove from bookmarks', array(), array('context' => 'gofast:gofast_dashboard')); ?>"></span>
                                </a>
                            </td>
                        </tr>
                    <?php endforeach; ?>
                <?php else : ?>
                    <tr>
                        <td><?php echo t('No favorite path.', array(), array('context' => 'gofast_dashboard')) ?></td>
                    </tr>
                <?php endif; ?>
            </tbody>
        </table>

        <nav class="text-center mt-6 dashboard-pagination-bottom">
            <ul class="pagination pagination-sm justify-content-center" id="path_pager"></ul>
        </nav>
    </div>
    <!--end::Body-->


    <script type='text/javascript'>
        jQuery(document).ready(function() {
            jQuery('#table_favorite_path > tbody').pager({
                pagerSelector: '#path_pager',
                perPage: 7,
                numPageToDisplay: 5,
                showPrevNext: false
            });
        });
    </script>
