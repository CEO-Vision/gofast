<?php

/**
 * @file
 * Displays list of Group shortcut of a user
 *
 * Available variables:
 *
 * @see template_preprocess_gofast_cdel_dashboard_shortcut_group()
 *
 * @ingroup themeable
 */
?>
<style>
    button#dropdown-rapid::after {
        visibility: hidden;
    }
    /* set caret color */
    button#dropdown-rapid span {
        position: relative;
    }

    button#dropdown-rapid span::after {
        position: absolute;
        left: 1ch;
        font-family: 'Font Awesome\ 5 Free';
        font-weight: 900;
        content: "\f0d7";
        color: var(--tagify-dd-color-primary);
    }
</style>
<!-- <div class="card-header min-h-30px px-4">
    <h3 class="card-title my-4">
        <span class="card-label font-weight-bolder text-dark-75 "><?php print t('My calendar', array(), array('context' => 'gofast_dashboard')) ?></span>
    </h3>
    <div class="card-toolbar">

    </div>
</div> -->

<div id="dashboard-calendar" class="panel-body">
    <div id="dashboard-calendar-meetings">
    </div>
    <div id="dashboard-calendar-deadlines" style="display: none;">
    </div>
</div>

<script>
    //Load my in progress processes
    var bonita_uid = "<?php global $user;
                        echo gofast_workflows_get_bonitaids_from_uids(array($user->uid))[0]; ?>";
    var params = "p=0&c=50&users=%5B%22" + bonita_uid + "%22%5D&documents=%5B%5D&state=progress";

    //Pre
    jQuery("document").ready(function() {

        $.ajax({
            type: "POST",
            url: "/gofast/dashboard/get_upcomings",
            success: function(response) {
                var data = JSON.parse(response);
                jQuery('#dashboard-calendar-deadlines').html(data.files);
                jQuery('#dashboard-calendar-meetings').html(data.meetings);
            }
        });

        jQuery("#dashboard-calendar-selection-meetings").click(function() {
            jQuery("#dashboard-calendar-meetings").show();
            jQuery("#dashboard-calendar-deadlines").hide();
            jQuery("#dashboard-calendar-tasks").hide();
            jQuery("#dashboard-calendar-dropdown-selected").html(Drupal.t("Meetings", {}, {
                context: 'gofast_cdel'
            }));
            jQuery("button#dropdown-rapid").html(Drupal.t("Meetings", {}, {
                context: 'gofast_cdel'
            }) + '<span class="caret"></span>');
        });

        jQuery("#dashboard-calendar-selection-deadlines").click(function() {
            jQuery("#dashboard-calendar-meetings").hide();
            jQuery("#dashboard-calendar-deadlines").show();
            jQuery("#dashboard-calendar-tasks").hide();
            jQuery("#dashboard-calendar-dropdown-selected").html(Drupal.t("Documents deadlines", {}, {
                context: 'gofast_cdel'
            }));
            jQuery("button#dropdown-rapid").html(Drupal.t("Documents deadlines", {}, {
                context: 'gofast_cdel'
            }) + '<span class="caret"></span>');
        });

        jQuery("#dashboard-calendar-selection-tasks").click(function() {
            jQuery("#dashboard-calendar-meetings").hide();
            jQuery("#dashboard-calendar-deadlines").hide();
            jQuery("#dashboard-calendar-tasks").show();
            jQuery("#dashboard-calendar-dropdown-selected").html(Drupal.t("Tasks", {}, {
                context: 'gofast_cdel'
            }));
        });
    });
</script>
