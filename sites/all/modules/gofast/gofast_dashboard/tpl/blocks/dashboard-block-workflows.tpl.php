    <!--begin::Body-->
    <div class="dashboard-workflows-placeholder">
    </div>
    <!--end::Body-->

    <script type='text/javascript'>
        //Load my in progress processes
        var bonita_uid = "<?php global $user;
                            echo gofast_workflows_get_bonitaids_from_uids(array($user->uid))[0]; ?>";
        var params = "p=0&c=50&users=%5B%22" + bonita_uid + "%22%5D&documents=%5B%5D&state=progress";

        //Pre
        jQuery("document").ready(function() {
            Drupal.gofast_workflows.ceo_vision_js_check_login(function() {
                var iframe = jQuery('<iframe src="/bonita/portal/resource/app/GoFAST/blockDashboard/content/?app=GoFAST&amp;locale='+ Gofast.get("user").language +'" id="bonita_form_process" style="width:100%;height:100%;min-height:280px;border:none;"></iframe>');
                //jQuery("#loader_process_in_progress").replaceWith(iframe);
                jQuery(".dashboard-workflows-placeholder").find(".loader-dashboard-block").remove();
                jQuery(".dashboard-workflows-placeholder").prepend(iframe);
            });
        });
    </script>
