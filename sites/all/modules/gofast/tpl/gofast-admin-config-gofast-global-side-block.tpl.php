<div class="card card-custom card-stretch overflow-scroll" style=" width: 320px;">
  <div class="card-body" id="gofastSettingsTabs">
      <ul class="nav flex-column nav-pills">
          <?php foreach($settingsTabs as $tab): ?>
          <li class="nav-item mb-2">
              <a class="nav-link <?php echo $tab['attributes']['class'] ?>" id="<?php echo $tab['attributes']['id'];?>" data-toggle="tab" href="#<?php echo $tab['attributes']['class'];?>" data-form-id="<?php echo $tab['attributes']['data-form-id'];?>">
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
<script>
    jQuery(document).ready(function() {
        if (window.location.hash.length && jQuery("[href='" + window.location.hash + "']").length) {
            jQuery("[href='" + window.location.hash + "']").click();
        }
        $("#gofastSettingsTabs .nav-link").on("click", function() {
            window.location.hash = $(this).attr("href");
        });
    });
</script>