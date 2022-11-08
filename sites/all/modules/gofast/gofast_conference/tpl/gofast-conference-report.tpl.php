<div id="report_detection_media" class="conference__media ">
    <div class="conference_lable h6 font-weight-bolder"><?php print t('Main devices', array(), array('context' => 'gofast:gofast_conference')) ?>:</div>
    <div class="my-4">
        <ul class="navi">
            <li id="camera" class="navi-item d-flex align-items-center mb-1">
                <div class="w-30px">
                    <span class="navi-icon"><i class="fas fa-camera mr-2"></i></span>
                </div>
                <span class="navi-text mr-1"><?php print t('Camera', array(), array('context' => 'gofast:gofast_conference')) ?></span>
                <span class="result_icon"></span>
            </li>
            <li id="microphone" class="navi-item d-flex align-items-center mb-1">
                <div class="w-30px">
                    <span class="navi-icon"><i class="fas fa-microphone mr-2"></i></i></span>
                </div>
                <span class="navi-text mr-1"><?php print t('Microphone', array(), array('context' => 'gofast:gofast_conference')) ?></span>
                <span class="result_icon"></span>
            </li>
            <li id="audio" class="navi-item d-flex align-items-center mb-1">
                <div class="w-30px">
                    <span class="navi-icon"><i class="fas fa-volume-up mr-2"></i></i></span>
                </div>
                <span class="navi-text mr-1"><?php print t('Loudspeakers', array(), array('context' => 'gofast:gofast_conference')) ?></span>
                <span class="result_icon"></span>
            </li>
        </ul>
    </div>
</div>
<div id="conference_report_more_details_title" class="my-2 h4 font-weight-bolder cursor-pointer d-flex align-items-center" style="gap: 1rem;" data-toggle="collapse" data-target="#conference_report_more_details">
    <span><?= t("More details") ?></span>
    <i class="fas fa-cog"></i>
</div>
<div id="conference_report_more_details" class="collapse hide" data-parent="#conference_report_more_details_title">
    <div id="report_result_protocols" class="conference__protocol ">
        <div class="conference_lable h6 font-weight-bolder"><?php print t('Protocols', array(), array('context' => 'gofast:gofast_conference')) ?>:</div>
        <div class="my-4">
            <ul class="navi">
                <li id="webrtc" class="navi-item d-flex align-items-center mb-1">
                    <div class="w-30px">
                        <span class="navi-icon"><i class="fas fa-angle-double-right"></i></span>
                    </div>
                    <span class="navi-text mr-1"><?php print t('WebRTC', array(), array('context' => 'gofast:gofast_conference')) ?></span>
                    <span class="result_icon"></span>
                </li>
                <li id="websocket" class="navi-item d-flex align-items-center mb-1">
                    <div class="w-30px">
                        <span class="navi-icon"><i class="fas fa-angle-double-right"></i></span>
                    </div>
                    <span class="navi-text mr-1"><?php print t('WebSocket', array(), array('context' => 'gofast:gofast_conference')) ?></span>
                    <span class="result_icon"></span>
                </li>
            </ul>
        </div>
    </div>
    <div id="report_result_others" class="conference__more">
        <div class="conference_lable h6 font-weight-bolder"><?php print t('Others', array(), array('context' => 'gofast:gofast_conference')) ?>:</div>
        <div class="my-4">
            <ul class="pl-5">
            </ul>
        </div>
    </div>
</div>
<style>
    .conference__title>.h1 {
        overflow: hidden;
        text-overflow: ellipsis;
        white-space: nowrap;
    }

    .conference__actions {
        display: flex;
        gap: 1rem;
        align-items: center;
    }

    .conference__actions>a {
        white-space: nowrap;
    }
</style>