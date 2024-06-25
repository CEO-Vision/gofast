<?php
/**
 * @file
 * Displays Dashboard Page
 *
 * Available variables:
 *
 * @see template_preprocess_gofast_cdel_dashboard_main()
 *
 * @ingroup themeable
 */
?>

<div class="gofastDashboard py-4 h-100">
    <div class="d-flex flex-wrap h-100 w-100 min-h-50" style="gap: .5rem 0;">
    <?php foreach ($dashboard_blocks as $pos => $block) : ?>
        <div class="col-12 col-md-6 col-xl-4 pb-2">
            <?php echo theme('gofast_dashboard_card', array('label' => $block['label'], 'toolbar' => $block['toolbar'], 'block_id' => $block['id'])); ?>
        </div>
    <?php endforeach; ?>
    </div>
</div>

<script type='text/javascript'>
    jQuery(document).ready(function(){
        jQuery('.gofastDashboard .card .card-body > div:not(.processed)').each(function (index, element) {
            jQuery(this).addClass('processed');

            var blockId = jQuery(this).attr('id');
            jQuery.ajax({
                type: "GET",
                url: "/gofast/dashboard/get/block",
                data: {
                    id: blockId
                },
                dataType: 'json',
            }).done(function (data) {
                var blockId = data.id;
                var content = data.content
                jQuery('#' + blockId + " .spinner").remove();
                jQuery('#' + blockId).html(content);
                Drupal.attachBehaviors();
            });
        });
        if (jQuery("#dashboard-block-last-commented").length > 0){
            jQuery.post(location.origin+"/dashboard/ajax/last_commented", function(data){
                jQuery("#dashboard-block-last-commented").replaceWith(data);
            });
        }

        if (jQuery("#dashboard-block-mail").length > 0){
            jQuery.post(location.origin+"/dashboard/ajax/mail", function(data){
                jQuery("#dashboard-block-mail").replaceWith(data);
            });
        }
    });
</script>
