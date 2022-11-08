<ul class="navi navi-hover navi-link-rounded" id="">
    <?php foreach($recently_read as $node) : ?>
    <li class="navi-item" id="">
        <a class="navi-link" href="/node/<?php echo $node->nid; ?>">
            <span class="navi-icon">
                <?php echo theme("gofast_node_icon_format", array('node' => node_load($node->nid)));  ?>
            </span>
            <span class="navi-text"><?php echo $node->title; ?></span>
        </a>
    </li>
    <?php endforeach; ?>  
</ul> 
