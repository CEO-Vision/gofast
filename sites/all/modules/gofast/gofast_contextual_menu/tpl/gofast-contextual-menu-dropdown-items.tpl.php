<div class="dropdown-menu dropdown-menu-md py-5" aria-labelledby="dropdown-">
  <ul class="navi navi-hover navi-link-rounded-lg px-1">
    <?php foreach ($node_actions as $item) : ?>
      <?php if ($item['divider'] == TRUE) : ?>
        <li class='navi-separator my-3'></li>
      <?php elseif ($item['children'] && !empty($item['children'])) : ?>
        <li class="collapsed dropdown-submenu navi-item">
          <div class="dropdown gofastDropdown">
            <a class="dropdown-toogle">
              <?php echo $item['themed'] ?>
            </a>
            <div class="dropdown-menu dropdown-menu-md py-5" aria-labelledby="dropdown-">
              <ul class="navi navi-hover navi-link-rounded-lg px-1">
                <?php foreach ($item['children'] as $item) : ?>
                  <li class="navi-item"><?php echo $item['themed']; ?></li>
                  <?php endforeach ?>
              </ul>
            </div>
          </div>
        </li>
      <?php else : ?>
        <li class="navi-item"><?php echo $item['themed'] ?></li>
      <?php endif; ?>
      <?php endforeach; ?>
  </ul>
</div>
