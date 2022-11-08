<?php if (user_is_logged_in()) {
global $user;    
?>
    <style>
        .GofastNotFound .card {
            transition: all .5s ease-in-out;
            box-shadow: transparent 0px 54px 55px, rgba(0, 0, 0, 0.12) 0px -12px 30px, transparent 0px 4px 6px, transparent 0px 12px 13px, transparent 0px -3px 5px;
        }

        .GofastNotFound .card:hover {
            box-shadow: rgba(0, 0, 0, 0.25) 0px 54px 55px, rgba(0, 0, 0, 0.12) 0px -12px 30px, rgba(0, 0, 0, 0.12) 0px 4px 6px, rgba(0, 0, 0, 0.17) 0px 12px 13px, rgba(0, 0, 0, 0.09) 0px -3px 5px;
            transform: translateY(-.5rem);
        }

        .GofastNotFound .card-toolbar {
            transition: all .3s ease-in-out;
        }

        .GofastNotFound .card-toolbar:hover {
            transform: scale(1.1);
        }
    </style>
    <div id="kt_content" class="container-fluid h-100 py-0">
        <div id="kt_subheader" class="subheader mt-4 pt-6 pt-lg-8 subheader-transparent d-flex flex-column align-items-start">
            <div class="block-title font-size-h1 font-weight-bold mb-4">
                <?php print t("Page not found", array(), array('context' => 'gofast_error')); ?>
            </div>
            <div class="block-title font-size-h3 font-weight-bold mb-4">
                <?php print t("Return to :", array(), array('context' => 'gofast_error')); ?>
            </div>
        </div>
        <div class="d-flex flex-column-fluid">
            <div class="container GofastNotFound">
                <div class="row mb-10 d-flex justify-content-between">
                    <div class="col-lg-5 col-sm-12 mb-sm-10">
                        <a href="<?php print url('dashboard', array()); ?>" target="_blank">
                            <div class="card card-custom card-stretch">
                                <div class="card-header border-0 px-10 py-2 d-flex">
                                    <div class="card-title align-items-center d-flex">
                                        <div class="font-size-h2 font-weight-bold">
                                            <?php print t("Dashboard", array(), array('context' => 'gofast_error')); ?>
                                        </div>
                                    </div>
                                    <div class="card-toolbar">
                                        <i class="flaticon-dashboard icon-10x" aria-hidden="true"></i>
                                    </div>
                                </div>
                            </div>
                        </a>
                    </div>
                    <div class="col-lg-5 col-sm-12 mb-sm-10">
                        <a href="<?php print url('activity', array()); ?>" target="_blank">
                            <div class="card card-custom card-stretch">
                                <div class="card-header border-0 px-10 py-2">
                                    <div class="card-title align-items-center d-flex">
                                        <div class="font-size-h2 font-weight-bold">
                                            <?php print t("Activity feed", array(), array('context' => 'gofast_error')); ?>
                                        </div>
                                    </div>
                                    <div class="card-toolbar">
                                        <i class="flaticon-list icon-10x" aria-hidden="true"></i>
                                    </div>
                                </div>
                            </div>
                        </a>
                    </div>
                </div>
                <div class="row d-flex justify-content-between">
                    <div class="col-lg-5 col-sm-12 mb-sm-10">
                        <a href="https://gofast-docs.readthedocs.io/<?= $user->language  ?>/4.0/" target="_blank">
                            <div class="card card-custom card-stretch">
                                <div class="card-header border-0 px-10 py-2 d-flex">
                                    <div class="card-title align-items-center d-flex">
                                        <div class="font-size-h2 font-weight-bold">
                                            <?php print t("Doc online", array(), array('context' => 'gofast_error')); ?>
                                        </div>
                                    </div>
                                    <div class="card-toolbar">
                                        <i class="flaticon-book icon-10x" aria-hidden="true"></i>
                                    </div>
                                </div>
                            </div>
                        </a>
                    </div>
                    <div class="col-lg-5 col-sm-12 mb-sm-10">
                        <a href="https://community.ceo-vision.com/categories/" target="_blank">
                            <div class="card card-custom card-stretch">
                                <div class="card-header border-0 px-10 py-2">
                                    <div class="card-title align-items-center d-flex">
                                        <div class="font-size-h2 font-weight-bold">
                                            <?php print t("Forums", array(), array('context' => 'gofast_error')); ?>
                                        </div>
                                    </div>
                                    <div class="card-toolbar">
                                        <i class="flaticon-comment icon-10x" aria-hidden="true"></i>
                                    </div>
                                </div>
                            </div>
                        </a>
                    </div>
                </div>
            </div>
        </div>
    </div>
<?php } ?>

<?php if (FALSE) : ?>
    <div class="panel-heading">
        <h3 class="panel-title"><b><?php print t("Page not found", array(), array('context' => 'gofast_error')); ?></b></h3>
    </div>
    <div class="panel-body">
        <p class="p_error_center"><b><?php print t("This page does not exist ...", array(), array('context' => 'gofast_error')); ?></b></p>
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
    </div>
<?php endif; ?>