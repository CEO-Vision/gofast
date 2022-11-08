<?php

/**
 * @file
 * Default theme implementation to display a Bootstrap panel component.
 *
 * @todo Fill out list of available variables.
 *
 * @ingroup templates
 */
?>
<?php if (strpos($attributes, 'accordion-solid')): ?>
    <!-- accordion-solid -> class : Accordions Style Keen https://preview.keenthemes.com/keen/demo1/features/custom/accordions.html# -->
    <div <?php print $attributes ?> id="accordion_gofast_<?php $uniq = uniqid();
    print $uniq;
    ?>">
        <div class="card">
            <div class="card-header">
                <div class="card-title<?php print ($collapsed ? ' collapsed' : ''); ?>" data-toggle="collapse" data-target="#collapse_gofast_<?php print $uniq; ?>">
    <?php print $title ?>
                </div>
            </div>
            <div id="collapse_gofast_<?php print $uniq; ?>" class="collapse<?php print (!$collapsed ? ' show' : ''); ?> " data-parent="#accordion_gofast_<?php print $uniq; ?>">
                <div class="card-body">
                    <?php print $description; ?><br />
    <?php print $content; ?>
                </div>
            </div>
        </div>
    </div>
    
    <?php else: ?>
    <div <?php print $attributes; ?>>
        <?php if ($title): ?>
        <?php if ($collapsible): ?>
                <legend class="panel-heading">
                    <a href="<?php print $target; ?>" class="panel-title fieldset-legend<?php print ($collapsed ? ' collapsed' : ''); ?>" data-toggle="collapse"><?php print $title; ?></a>
                </legend>
        <?php else: ?>
                <legend class="panel-heading">
                    <span class="panel-title fieldset-legend"><?php print $title; ?></span>
                </legend>
            <?php endif; ?>
            <?php endif; ?>
        <div<?php print $body_attributes; ?>>
            <?php if ($description): ?><div class="help-block"><?php print $description; ?></div><?php endif;
            ?>
    <?php print $content; ?>
        </div>
    </div>
<?php endif;