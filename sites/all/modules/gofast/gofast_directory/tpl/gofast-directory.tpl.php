<div class="card card-custom card-stretch">
    <div class="card-body pb-4 pt-0 px-1 d-flex flex-column">
        <div class="w-100 p-2">
          <ul class="nav nav-tabs nav-fill gofastTab w-100 mb-0 justify-content-end flex-nowrap" id="gofastDirectoryrNavTabs" role="tablist">
            <?php foreach ($lists as $list) : ?>
              <li class="nav-item">
                <a class="nav-link px-2 d-flex justify-content-center <?php print $list['selected'] ? 'active': '' ?>" 
                        role="tab" 
                        id="<?php print $list['id']; ?>Tab" 
                        href="#<?php print $list['id']; ?> "  
                        data-toggle="tab"
                        data-type ="<?php echo $list['type'];?>"
                        aria-selected="true"
                        aria-controls="<?php print $list['id']; ?>"
                        >
                    <span class="nav-icon">
                        <i class="<?php print $list['icon'] ?>"></i>
                    </span>
                    <span class="nav-text"><?php print $list['label']; ?></span>
                </a>
              </li>
            <?php endforeach; ?>
          </ul>
        </div>
        <div class="h-100 w-100 pt-4 pl-6 overflow-hidden" >
          <div class="tab-content h-100 w-100 scroll scroll-pull" data-scroll="true" data-wheel-propagation="true" >
            <?php foreach ($lists as $list) : ?>
                <div class="tab-pane fade h-100 w-100 pr-2 <?php print $list['selected'] ? 'show active': '' ?>" 
                        id="<?php print $list['id']; ?>" 
                        role="tabpanel" 
                        aria-labelledby="<?php print $list['id']; ?>Tab"
                        >
                    <?php print theme($list['template']) ?>
                </div>
            <?php endforeach; ?>
          </div>
        </div>
    </div>
</div>