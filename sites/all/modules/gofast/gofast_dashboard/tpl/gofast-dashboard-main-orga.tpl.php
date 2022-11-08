<?php
/**
 * @file
 * Displays Main Orga block for dashboard
 *
 * Available variables:
 * - $og_nid : Main Organisation (OG node) ID
 * - $og_name : Main Organisation (OG node) name
 *
 * @see template_preprocess_gofast_cdel_dashboard_main_orga()
 *
 * @ingroup themeable
 */
?>

<?php if(FALSE): ?>
<div class="col-xxl-4 col-lg-6">
    <div class="card card-custom card-stretch gutter-b">
        <div class="card-header">
            <div class="card-title">
                <h3 class="card-label">
                    <span class="font-weight-bolder font-size-h4 text-dark-75">
                        <?php
                            if(!empty($og_nid)){
                                print $og_name;
                            }else{
                                print t('Your main space', array(), array('context' => 'gofast'));
                            }
                        ?>
                    </span>
                </h3>
            </div>
        </div>
        <div class="card-body">
            <?php
                if(!empty($og_nid)){
            ?>
            <ul class="list-group dashboard cdel">
                <li class="list-group-item">
                    <a class="btn btn-link" href="/node/<?php echo $og_nid ?>#ogdocuments">
                        <span class="fa fa-sitemap"></span>
                        <?php  print t('Go to documents of @main_orga', array('@main_orga' => $og_name), array('context' => 'gofast_cdel'))?>
                    </a>
                </li>
                <li class="list-group-item">
                        <a class="btn btn-link" href="<?php echo $og_calendar_link ?>">
                            <span class="fa fa-calendar"></span>
                            <?php print t('Show calendar of @main_orga', array('@main_orga' => $og_name), array('context' => 'gofast_cdel'))?>                           
                        </a>
                </li>
            </ul>
            <?php
                }else{
                    print t("You have no main space yet.", array(), array('context' => 'gofast'));
                }
            ?>
        </div>
    </div>
</div>
<?php endif ?>

<div class="card card-stretch gutter-b card-custom ">
    <!--begin::Header-->
    <div class="card-header min-h-30px px-4">
        <h3 class="card-title my-4">
            <span class="card-label font-weight-bolder text-dark-75 ">
                <?php
                    if(!empty($og_nid)){
                        print $og_name;
                    }else{
                        print t('Your main space', array(), array('context' => 'gofast'));
                    }
                ?>
            </span>
        </h3>
    </div>
    <!--end::Header-->
    <!--begin::Body-->
    <div class="card-body h-100 p-4">
        <?php if(!empty($og_nid)): ?>
            <ul class="list-group dashboard cdel">
                <li class="list-group-item">
                    <a class="btn btn-link" href="/node/<?php echo $og_nid ?>#ogdocuments">
                        <span class="fa fa-sitemap"></span>
                        <?php  print t('Go to documents of @main_orga', array('@main_orga' => $og_name), array('context' => 'gofast_cdel'))?>
                    </a>
                </li>
                <li class="list-group-item">
                        <a class="btn btn-link" href="<?php echo $og_calendar_link ?>">
                            <span class="fa fa-calendar"></span>
                            <?php print t('Show calendar of @main_orga', array('@main_orga' => $og_name), array('context' => 'gofast_cdel'))?>                           
                        </a>
                </li>
            </ul>
        <?php else: ?>
            <?php print t("You have no main space yet.", array(), array('context' => 'gofast')); ?>
        <?php endif ?>
    </div>
    <!--end::Body-->
</div>

