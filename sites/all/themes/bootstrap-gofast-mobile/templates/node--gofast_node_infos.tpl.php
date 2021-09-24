<div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>
<!--
    <\?php print render($title_prefix); ?>
    <\?php if (!$page): ?>
      <h2<\?php print $title_attributes; ?>><a href="<\?php print $node_url; ?>"><\?php print $title; ?></a></h2>
    <\?php endif; ?>
    <\?php print render($title_suffix); ?>
-->
    <?php
    // We hide the comments and links because we don't need them
    hide($content['comments']);
    hide($content['links']);
    
    /*?>
    
    <div id="tabs_node_extra" class="ui tabs">
        <ul>
            <li><a href="#info-tab"><?php print t("Info"); ?></a></li>
            <li><a href="#comments-tab"><?php print t("Comments"); ?></a></li>
        </ul>
        <div id="info-tab">
            <?php print $infoTab; ?>
        </div>
        <div id="comments-tab">
            <?php print $commentsTab; ?>
        </div>
    </div>
      
    <?php*/

    print render($content);
    
    ?>

</div>