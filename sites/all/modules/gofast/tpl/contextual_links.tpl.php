<div class="w-100 d-flex justify-content-center" id="<?php print $btn_group_id; ?>">
    <div class="contextual-actions btn-group btn-group-xs" role="group" aria-label="contextual actions">
        <?php foreach ($buttons as $btn) : ?>
            <?php
            $classes = isset($btn['classes']) ? implode(" ", $btn['classes']) : '';
            $buttonText = isset($btn['button-text']) ? $btn['button-text'] : '';
            ?>
            <?php if (isset($btn['children'])) : ?>
                <?php $contextual_menu = $btn; ?>
            <?php else : ?>
                <a type="button" class="btn btn-outline-secondary btn-icon btn-sm position-relative <?php echo $classes ?>" <?php if (isset($btn['id'])) : ?> id="<?php echo $btn['id'] ?>" <?php endif ?> <?php if (isset($btn['href'])) : ?> href="<?php echo $btn['href'] ?>" <?php endif ?> <?php if (isset($btn['disabled'])) : ?> disabled <?php endif ?> <?php if (isset($btn['onClick'])) : ?> onClick=<?php echo $btn['onClick'] ?> <?php endif ?> <?php if (isset($btn['alt'])) : ?> alt="<?php echo $btn['alt'] ?>" <?php endif ?> <?php if (isset($btn['target'])) : ?> target="<?php echo $btn['target'] ?>" <?php endif ?> <?php if (isset($btn['title'])) : ?> title="<?php echo t($btn['title'], array(), array('context' => 'gofast:gofast_workflows')) ?>" <?php endif ?>>
                      <?php if (isset($btn['avatar'])) : ?>
                          <?php echo $btn['avatar'] ?>
                      <?php endif ?>
                    <i class="<?php echo $btn['icon-class'] ?> icon-nm">
                    </i>
                    <?php if (isset($btn['title'])) : ?>
                        <?php if ($buttonText != 0) : ?>
                            <span class="label label-danger position-absolute" style="top: -10px; right: -5px; z-index: 2;"><?php echo $buttonText ?></span>
                        <?php endif ?>
                    <?php endif ?>
                </a>
            <?php endif ?>
        <?php endforeach ?>
    </div>

    <?php if (!empty($contextual_menu)) : ?>
        <div class="dropdown ml-3 <?= $fromBrowser ? "dropleft" : "" ?>">
            <div class="dropdown-menu dropdown-menu-md py-5" aria-labelledby="dropdown-<?php echo $contextual_menu['id'] ?>">
                <ul class="navi navi-hover navi-link-rounded-lg px-1">
                    <?php foreach ($contextual_menu['children'] as $item) : ?>
                        <?php if ($item['divider'] == TRUE) : ?>
                         <li class='navi-separator my-3'></li>
                        <?php elseif ($item['children'] && !empty($item['children'])) : ?>
                            <li class="collapsed dropdown-submenu navi-item">
                                <div class="dropdown gofastDropdown">
                                    <a class="dropdown-toogle">
                                    <?php echo $item['themed'] ?>
                                </a>
                                <div class="dropdown-menu dropdown-menu-md py-5 <?= $fromBrowser || $_POST['dropleft'] ? "dropleft" : "" ?>" aria-labelledby="dropdown-<?php echo $contextual_menu['id'] ?>">
                                    <ul class="navi navi-hover navi-link-rounded-lg px-1">
                                        <?php foreach ($item['children'] as $item) : ?>
                                            <li class="navi-item"><?php echo $item['themed']; ?></li>
                                        <?php endforeach ?>
                                    </ul>
                                </div>
                            </div>
                        </li>
                    <?php else : ?>
                        <li class="navi-item" <?php if (isset($item['title'])) : ?> data-toggle="tooltip" data-theme="dark" data-trigger="hover" data-html="true" title="<?php print $item['title']; ?>" <?php endif ?>><?php echo $item['themed'] ?></li>
                    <?php endif ?>
                <?php endforeach ?>
            </ul>
        </div>
        <a type="button" class="btn btn-primary btn-icon btn-sm position-relative" <?php if (isset($contextual_menu['id'])) : ?> id="dropdown-<?php echo $contextual_menu['id'] ?>" <?php endif ?> <?php if (isset($contextual_menu['title'])) : ?> title="<?php echo t($contextual_menu['title'], array(), array('context' => 'gofast:gofast_workflows')) ?>" <?php endif ?> data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
            <i class="<?php echo $contextual_menu['icon-class'] ?> icon-nm"></i>
            <?php if (isset($contextual_menu['title'])) : ?>
                <?php if ($contextual_menu['title'] != 0) : ?>
                    <span class="label label-danger position-absolute" style="top: -10px; right: -5px; z-index: 2;"><?php echo $contextual_menu['title'] ?></span>
                <?php endif ?>
            <?php endif ?>
        </a>
    </div>
    <?php endif; ?>
</div>

<script>
    jQuery("#refresh_actions_button").removeClass("d-none");
</script>
