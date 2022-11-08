<ul class="navi navi-hover navi-link-rounded" id="gofastRssContent">
    <?php foreach ($items as $item) : ?>
        <li class="d-flex navi-item" id="">
            <a class="navi-link min-w-100" style="padding-right: 0 !important" title="<?php echo $item["title"]; ?>" href="<?= $item["link"] ?>">
                <span class="navi-icon">
                    <i class="fas fa-rss-square" title="<?php echo $node->title; ?>"></i>
                </span>
                <span class="navi-text text-truncate"><?php echo $item["title"]; ?></span>
            </a>
        </li>
    <?php endforeach; ?>
</ul>

<nav class="text-center mt-4">
    <ul class="pagination pagination-sm justify-content-center" id="gofast-rss-content-pager"></ul>
</nav>
