<!-- START gofast-menu-langue.tpl.php -->
<li class="nav-item nav-item-language dropdown no-arrow" id="gofast-flag-lang-switch">
  <a type="button" class="nav-link dropdown-toggle p-1" id="gofast-menu-language-dropdown" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false" data-offset="0,10">
    <span class="<?php print t($selected_language['icon'])?>"></span>
  </a>
  <div class="dropdown-menu dropdown-menu-right shadow" aria-labelledby="gofast-menu-language-dropdown">
    <?php foreach ($languages as $language ) : ?>
        <a class="dropdown-item" type="button" href="<?php print $language['href'];?>"><span class="dropdown-item-icon <?php print t($language['icon'])?>"></span> <?php print t($language['name']);?></a>
    <?php endforeach; ?>
  </div>
</li>
<!-- END gofast-menu-langue.tpl.php -->
