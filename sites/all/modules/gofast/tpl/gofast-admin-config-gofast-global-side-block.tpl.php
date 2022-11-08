<div class="card card-custom gutter-b">
  <div class="card-body" id="gofastSettingsTabs">
      <ul class="nav flex-column nav-pills">
          <?php foreach($settingsTabs as $tab): ?>
          <li class="nav-item mb-2">
            <a class="nav-link" id="tab-<?php echo $tab['attributes']['class'];?>" data-toggle="tab" href="#<?php echo $tab['attributes']['class'];?>">
                  <span class="nav-icon">
                      <i class="<?php echo $tab['icon'];?>"></i>
                  </span>
                  <span class="nav-text"><?php echo $tab['title']; ?></span>
              </a>
          </li>
          <?php endforeach; ?>
      </ul>
  </div>
</div>