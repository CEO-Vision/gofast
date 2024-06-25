<!-- gofast-conference-report.tpl.php -->
<div id="node-<?php print $node->nid; ?>" class="conferenceContainer col-12 pt-4 h-100">
    <div class="card card-custom card-stretch gofastConferenceDetail">
        <div class="card-body overflow-auto">
            <div class="row h-100">
                <div class="gofastConferenceDetail__principalInfo col-lg-9">
                    <div class="conference__title d-flex justify-content-between">
                        <div class="h1 font-weight-bolder"><?php echo $node->title ?></div>
                    </div>
                    <div class="conference__subject my-10">
                        <div class="font-size-lg"><?php echo $conferenceDetails['subject'] ?></div>
                    </div>
                    <div class="row conference_about">
                        <div class="col ">
                            <div class="conferace__label h6 font-weight-bolder text-center"><?= t("Meeting Start", [], ["context" => "gofast:gofast_conference"]) ?></div>
                            <div class="text-center d-flex flex-column">
                                <span id="gofastConferenceToggleStartTimezone" title="<?= t("Click to see the timezone", array(), array("context" => "gofast:gofast_conference")) ?>" class="cursor-pointer">
                                    <?php echo $conferenceDetails['startDate'] . " - " . $conferenceDetails['startTime']; ?>
                                </span>
                                <span id="gofastConferenceStartTimezone" class="d-none font-weight-bold"><?php echo $conferenceDetails['timezone']; ?></span>
                            </div>
                        </div>
                        <div class="col border-left ">
                            <div class="conferace__label h6 font-weight-bolder text-center"><?= t("Meeting End", [], ["context" => "gofast:gofast_conference"]) ?></div>
                            <div class="text-center d-flex flex-column">
                                <span id="gofastConferenceToggleEndTimezone" title="<?= t("Click to see the timezone", array(), array("context" => "gofast:gofast_conference")) ?>" class="cursor-pointer">
                                    <?php echo $conferenceDetails['endDate'] . " - " . $conferenceDetails['endTime']; ?>
                                </span>
                                <span id="gofastConferenceEndTimezone" class="d-none font-weight-bold"><?php echo $conferenceDetails['timezone']; ?></span>
                            </div>
                        </div>
                        <div class="col border-left">
                            <div class="conferace__label h6 font-weight-bolder text-center"><?= t("Duration", [], ["context" => "gofast:gofast_conference"]) ?></div>
                            <div class=" text-center"><?php echo $conferenceDetails['duration'] ?></div>
                        </div>
                        <div class="col border-left ">
                            <div class="conferace__label h6 font-weight-bolder text-center"><?= t("Place", [], ["context" => "gofast:gofast_conference"]) ?></div>
                            <div class=" text-center"><?php echo $conferenceDetails['place'] ?></div>
                        </div>
                    </div>
                    <div class="separator separator-solid my-5"></div>
                    <div class="row">
                        <div class="conference__actions mx-auto">
                            <?php if ($conferenceDetails['actions']['startConference']) : ?>
                                <a href="<?php echo $conferenceDetails['actions']['startConference']['href'] ?>" id="<?php echo $conferenceDetails['actions']['startConference']['id'] ?>" class="btn btn-sm btn-success"><?php echo $conferenceDetails['actions']['startConference']['label'] ?></a>
                            <?php endif; ?>
                            <div class="dropdown dropdown-inline mr-4">
                                <button type="button" class="btn btn-sm btn-icon btn-info " data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
                                    <i class="fa fa-bars icon-nm"></i>
                                </button>
                                <div class="dropdown-menu">
                                    <a class="dropdown-item" href="<?php echo $conferenceDetails['actions']['displayPCLink']['href'] ?>" id="<?php echo $conferenceDetails['actions']['displayPCLink']['id'] ?>"><?php echo $conferenceDetails['actions']['displayPCLink']['label'] ?></a>
                                    <a class="dropdown-item clipboard" data-clipboard-text="<?php echo $conferenceDetails['actions']['copyLinkToClipboard']['url'] ?>" href="<?php echo $conferenceDetails['actions']['copyLinkToClipboard']['href'] ?>" id="<?php echo $conferenceDetails['actions']['copyLinkToClipboard']['id'] ?>"><?php echo $conferenceDetails['actions']['copyLinkToClipboard']['label'] ?></a>
                                    <?php if (isset($conferenceDetails['actions']['editConference'])) : ?>
                                        <a class="dropdown-item" href="<?php echo $conferenceDetails['actions']['editConference']['href'] ?>" id="<?php echo $conferenceDetails['actions']['editConference']['id'] ?>"><?php echo $conferenceDetails['actions']['editConference']['label'] ?></a>
                                        <a href="<?= $base_url ?>/modal/nojs/node/<?= $node->nid ?>/manage"" class="ctools-use-modal dropdown-item"><?= t('Delete', array(), array('context' => 'gofast')) ?></a>
                                    <?php endif; ?>
                                </div>
                            </div>
                        </div>
                    </div>
                    <div class="row">
                        <div class="conference__password mx-auto mt-5">
                            <?php if (isset($conferenceDetails['password'])) : ?>
                                <span class="navi-icon"><i class="fa fa-lock text-danger mr-2"></i></span>
                                <span>
                                    <?php echo t("Conference password : ") ?>
                                    <strong><?php echo $conferenceDetails['password']; ?></strong>
                                </span>
                            <?php else: ?>
                                <span class="navi-icon"><i class="fa fa-unlock text-success mr-2"></i></span>
                                <span><?php echo t("This conference is not locked with a password") ?></span>
                            <?php endif; ?>
                        </div>
                    </div>
                    <div class="separator separator-solid my-5"></div>
                    <div class="row">
                        <div class="col">
                            <div class="h2 font-weight-bolder text-center"><?= t("Linked Files", [], ["context" => "gofast:gofast_conference"]) ?></div>
                            <div class="p-4">
                                <div class="conference__documents ">
                                    <div class="conference_lable h6 font-weight-bolder"><?= t("Documents: ", [], ["context" => "gofast:gofast_conference"]) ?></div>
                                    <div class="d-flex flex-column my-4">
                                        <?php foreach ($conferenceDetails["listsDocuments"] as $doc) : ?>
                                            <div class="d-flex documetnsList__item mb-1 ">
                                                <div class="mr-2 font-size-md"><?php echo $doc["node_icon"] ?></div>
                                                <a href="<?php echo $doc["href"] ?>"><?php echo $doc["title"] ?></a>
                                            </div>
                                        <?php endforeach; ?>
                                    </div>
                                </div>
                                <div class="conference__folders ">
                                    <div class="conference_lable h6 font-weight-bolder"><?= t("Folders: ", [], ["context" => "gofast:gofast_conference"]) ?></div>
                                    <div class="d-flex flex-column my-4">
                                        <?php foreach ($conferenceDetails["listsFolders"] as $folder) : ?>
                                            <div class="d-flex folderList__item mb-1 ">
                                                <a href="/node/<?= $folder["gid"] ?>/?path=<?= $folder["value"] ?>"><?php echo $folder["value"] ?></a>
                                            </div>
                                        <?php endforeach; ?>
                                    </div>
                                </div>
                            </div>
                        </div>
                        <div class="border-right mx-4"></div>
                        <div class="col">
                            <div class="h2 font-weight-bolder text-center"><?= t("Extra Information", [], ["context" => "gofast:gofast_conference"]) ?></div>
                            <div class="p-4">
                                <ul class="navi">
                                    <li id="hasLobbyRoom" class="navi-item d-flex align-items-center mb-1">
                                        <div class="w-30px">
                                            <span class="navi-icon"><i class="<?= $conferenceDetails['hasLobbyRoom']['preIcon'] ?>"></i></span>
                                        </div>
                                        <span class="navi-text mr-1"><?= $conferenceDetails['hasLobbyRoom']['label'] ?></span>
                                        <span class="navi-icon"><i class="<?= $conferenceDetails['hasLobbyRoom']['postIcon'] ?>"></i></span>
                                    </li>
                                </ul>
                                <?php echo theme("gofast_conference_report") ?>
                            </div>
                        </div>
                    </div>

                </div>
                <div class="border-right mx-4"></div>
                <div class="gofastConferenceDetail__moreInfo col max-h-100" style="overflow-y: scroll; overflow-x: hidden;">
                    <div class="conference__owner mb-10">
                        <div class="conference_lable h6 font-weight-bolder"><?php print t('Organisator'); ?>:</div>
                        <div class="d-flex align-items-center my-4">
                            <div class="symbol symbol-35 ">
                                <img alt="Pic" src="<?php echo $conferenceDetails['owner']->picture ?>" />
                            </div>
                            <div class="px-4">
                                <div>
                                    <a href="/<?php echo $conferenceDetails['owner']->url_user ?>" class="btn btn-link-primary font-weight-bold "><?php echo $conferenceDetails['owner']->fullname ?></a>
                                </div>
                                <div class="font-size-sm text-muted"><?php echo $conferenceDetails['owner']->mail ?></div>
                            </div>
                        </div>
                    </div>
                    <?php if(count((array) $conferenceDetails["spaces_participants"]) > 0): ?>
                    <div class="conference__gofastPartisipantsSpaces my-10">
                        <div class="conference_lable h6 font-weight-bolder"><?=  t("Spaces", array(), array("context" => "gofast:gofast_conference")) ?></div>
                        <div class="my-4">
                            <?php foreach ($conferenceDetails["spaces_participants"] as $participant) : ?>
                                <div class="d-flex align-items-center my-4">
                                    <div class="symbol symbol-35 ">
                                       <?php echo theme('gofast_node_icon_format', array('node' => $participant)); ?>
                                    </div>
                                    <div class="px-4">
                                        <div>
                                            <a href="/node/<?= $participant->nid ?>" class="btn btn-link-primary font-weight-bold "><?php echo $participant->title ?></a>
                                        </div>
                                       
                                    </div>
                                </div>
                            <?php endforeach; ?>
                      
                        </div>
                    </div>
                    <?php  endif; ?>
                    <?php
                       $count_all_participants = count((array) $conferenceDetails["participants"]);
                       if(is_array($conferenceDetails["othersParticipants"])){
                           $count_all_participants = $count_all_participants + count($conferenceDetails["othersParticipants"]);
                       }
                    ?>
                    <div class="conference__gofastPartisipants my-10">
                        <div class="conference_lable h6 font-weight-bolder"><?= format_plural($count_all_participants, "Participant", "Participants") ?> (<?php echo $count_all_participants; ?>):</div>
                        <div class="my-4">
                            <?php foreach ($conferenceDetails["participants"] as $participant) : ?>
                                <div class="d-flex align-items-center my-4">
                                    <div class="symbol symbol-35 ">
                                        <img alt="Pic" src="<?php echo $participant->picture ?>" />
                                    </div>
                                    <div class="px-4">
                                        <div>
                                            <a href="/user/<?= $participant->uid["target_id"]
                                                        ?>" class="btn btn-link-primary font-weight-bold "><?php echo $participant->fullname ?></a>
                                        </div>
                                        <div class="font-size-sm text-muted"><?php echo $participant->mail ?></div>
                                    </div>
                                </div>
                            <?php endforeach; ?>
                            <?php foreach ($conferenceDetails["othersParticipants"] as $participant) : ?>
                                <div class="d-flex align-items-center my-4">
                                    <div class="symbol symbol-35 ">
                                        <img alt="Pic" src="/sites/all/themes/bootstrap-keen/keenv2/assets/media/users/blank.png" />
                                    </div>
                                    <div class="px-4">
                                        <div class="text-primary font-weight-bold"><?php echo $participant; ?></div>
                                    </div>
                                </div>
                            <?php endforeach; ?>
                        </div>
                    </div>
                </div>
            </div>
        </div>
    </div>
</div>
<div id="conference-pc-link" class="mx-auto">
    <div class="card">
        <div class="card-body">
            <span id="clipboard-pc-url">
                <?php print $conferenceDetails['actions']['copyLinkToClipboard']['url'] ?>
            </span>
        </div>
        <span class="position-absolute text-muted" style="top: 1rem; right: 1rem; font-size: 2rem;">&times;</span>
    </div>
</div>
<style>
    #conference-pc-link {
        display: none;
        position: fixed;
        top: 55px;
        z-index: 10000;
        cursor: pointer;
    }
</style>
<script defer>
    jQuery("#gofastConferenceToggleStartTimezone").on("click", () => jQuery("#gofastConferenceStartTimezone").toggleClass("d-none"));
    jQuery("#gofastConferenceToggleEndTimezone").on("click", () => jQuery("#gofastConferenceEndTimezone").toggleClass("d-none"));
</script>
