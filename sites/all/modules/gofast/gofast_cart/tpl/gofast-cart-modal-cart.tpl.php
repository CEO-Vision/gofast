<div id="gofast-cart" class="table-responsive GofastCart">
    <div class="GofastCart__table">
        <table id="gofast-cart-table" class="table table-vertical-center table-head-custom">
            <thead>
                <tr>
                    <th class="min-w-200px max-w-300px w-300px text-truncate"><?php print t('Title', array(), array('context' => 'gofast:cart')); ?></th>
                    <th class="max-w-400px min-w-200px w-400px"><?php print t('Location', array(), array('context' => 'gofast:cart')); ?></th>
                    <th class="w-175px"><?php print t('Cart addition date', array(), array('context' => 'gofast:cart')); ?></th>
                    <th class="w-50px min-w-50px"></th>
                </tr>
            </thead>
            <tbody class="GofastCart__tBody">
                <?php if($table_content !== ""): ?>
                    <?php print $table_content; ?>
                <?php endif; ?>
            </tbody>
        </table>
        <nav class="text-center mt-4">
            <ul class="pagination pagination-sm justify-content-center" id="gofast-cart-pager"></ul>
        </nav>
        <div class="GofastCart__emptyPlaceholder">
        <?php if($table_content === ""): ?>
            <div class="align-content-center d-flex justify-content-center p-5 pt-10">
                <span class="font-size-h3 font-weight-bolder text-muted text-uppercase" style="letter-spacing: 0.05rem;"><?php print(t('You have no content into your cart', array(), array('context' => 'gofast:cart'))); ?></span>
            </div>
        <?php endif; ?>
        </div>
    </div>
</div>

<script type="text/javascript">
    jQuery(document).ready(function() {
        jQuery('#gofast-cart-table > tbody').pager({pagerSelector : '#gofast-cart-pager', perPage: 10, numPageToDisplay : 5});
    })
</script>
