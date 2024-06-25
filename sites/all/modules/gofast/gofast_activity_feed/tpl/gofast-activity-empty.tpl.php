<?php
    $detect = new Mobile_Detect();
    $is_mobile = $detect->isMobile();
?>

<div class="alert alert-info d-flex align-items-center" role="alert">
    <i class="fas fa-warning text-white"></i> <!-- Font Awesome Warning Icon -->
    <strong class="ml-2"><?= t("The activity feed is empty", array(), array("context" => "gofast:gofast_activity_feed")) ?></strong>
</div>
<div class="text-center">
    <p><?= gofast_essential_is_essential() || $is_mobile ? t("The activity feed may be empty because of the lack of activity in your content over the last two weeks.", array(), array("context" => "gofast:gofast_activity_feed")) : t("The activity feed may be empty because of the lack of activity in your content over the last two weeks or because of the filters on the right.", array(), array("context" => "gofast:gofast_activity_feed")) ?></p>
</div>