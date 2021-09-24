<?php if (user_is_logged_in()) { ?>
    <div class="panel panel-info">
        <div class="panel-heading">
            <h3 class="panel-title"><b><?php print t("Access denied", array(), array('context' => 'gofast_error')); ?></b></h3>
        </div>
        <div class="panel-body">
            <p class="p_error_center"><b><?php print t("Unfortunately, you do not have access to this page.", array(), array('context' => 'gofast_error')); ?></b></p>
            <p class="p_error_center"><b><?php print t("Return to :", array(), array('context' => 'gofast_error')); ?></b></p>
            <div class="td_error_center">
                <table class="table_error">
                    <tr>
                        <td class="td_error_center"><a class="btn btn-sm <?php print $class; ?> a_error" href="<?php print url('dashboard', array()); ?>"><i class="fa fa-th fa-fw" aria-hidden="true"></i></a></td>
                        <td class="td_error_center"><a class="btn btn-sm <?php print $class; ?> a_error" href="<?php print url('activity', array()); ?>"><i class="fa fa-bars fa-fw" aria-hidden="true"></i></a></td>
                        <td class="td_error_center"><a class="btn btn-sm <?php print $class; ?> a_error" href="<?php print url('user', array()); ?>"><i class="fa fa-user fa-fw" aria-hidden="true"></i></a></td>
                    </tr>
                    <tr>
                        <td class="td_error_center"><?php print t("Dashboard", array(), array('context' => 'gofast_error')); ?></td>
                        <td class="td_error_center"><?php print t("Activity feed", array(), array('context' => 'gofast_error')); ?></td>
                        <td class="td_error_center"><?php print t("My profile", array(), array('context' => 'gofast_error')); ?></td>
                    </tr>
                </table>
            </div>
            <div class="td_error_center">
                <table class="table_error">
                    <tr>
                        <td class="td_error_center"><a class="btn btn-sm <?php print $class; ?> a_error" href="https://gofast-docs.readthedocs.io/fr/latest/" target="_blank"><i class="fa fa-book fa-fw" aria-hidden="true"></i></a></td>
                        <td class="td_error_center"><a class="btn btn-sm <?php print $class; ?> a_error" href="https://community.ceo-vision.com/categories/" target="_blank"><i class="fa fa-comments fa-fw" aria-hidden="true"></i></a></td>
                    </tr>
                    <tr>
                        <td class="td_error_center"><?php print t("Doc online", array(), array('context' => 'gofast_error')); ?></td>
                        <td class="td_error_center"><?php print t("Forums", array(), array('context' => 'gofast_error')); ?></td>
                    </tr>
                </table>
            </div>
        </div>
    </div>
<?php } ?>

<style>
    .breadcrumb-gofast {
        display: none;
    }
</style>
