<div class="d-flex align-items-center">
    <div class="d-flex justify-content-center align-items-center">  
        <?php echo $item['format']; ?>      
    </div>
    <i class="fas fa-file-pdf d-none mr-2 text-<?php //echo $colors[rand(0,3)]?> icon-nm"></i>
    <a href="#" class="gofast_activity_feed_title text-dark text-hover-primary font-weight-bolder font-size-lg text-truncate mr-2"><?php echo $item['title']; ?></a>
    <div class="gofast-node-actions btn-group dropdown ">
        <a class="btn btn-light btn-xs btn-icon mr-2 dropdown-placeholder" type="button" id="dropdown-placeholder-<?php echo $item['nid']; ?>" data-toggle="dropdown">
            <span class="fa fa-bars"></span>
            <ul class="dropdown-menu gofast-dropdown-menu" role="menu" id="dropdownactive-placeholder-<?php echo $item['nid']; ?>">
                <li><div class="loader-activity-menu-active"></div></li>
            </ul>
        </a>
    </div>
    <div class="d-flex align-items-center">
        <span class="label label-inline mx-1 d-none"><?php //echo rand(0,15)?></span>
        <?php if($item['state']): ?>
            <span class="label label-sm text-truncate label-inline mx-1"><?php echo $item['state']; ?></span>
        <?php endif ?>
    </div>
    <div class="d-flex align-items-center">
        <span class="label label-inline mx-1 d-none"><?php //echo rand(0,15)?></span>
        <?php if($item['criticity']): ?>
            <span class="label label-sm text-truncate label-inline mx-1"><?php echo $item['criticity']; ?></span>
        <?php endif ?>
    </div>
</div>
<div class="mt-2">
    <span class="text-muted mt-2 font-size-sm"><?php echo $item['last_event']; ?> <span class="text-<?php //echo $colors[0]?> font-weight-bolder"><?php //echo $actions[rand(0,6)]?></span> <?php //echo $date ?></span>
</div>