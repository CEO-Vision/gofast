<div class="w-100 h-100 overflow-hidden <?php if($hidden_filebrowser){ print
  'd-none'; } ?>" >
    <div class="tab-content h-100 w-100" id="gofastBrowserContentPanel">
      <?php foreach ($links as $link) : ?>
        <?php if($link['dropdown']) : ?>
          <?php foreach ($link['dropdown-menu'] as $dropdown_link) : ?>
            <?php if (isset($dropdown_link['prefix'])) : ?>
              <?php print $dropdown_link['prefix']; ?>
            <?php endif; ?>
                  <div class="tab-pane px-2 pt-4 fade h-100 w-100 overflow-hidden" id="<?php print $dropdown_link['href']; ?>" role="tabpanel" aria-labelledby="<?php print $dropdown_link['id']; ?>">
                    <?php print $dropdown_link['content']; ?>
                  </div>
          <?php endforeach; ?>
        <?php else : ?>
              <div class="tab-pane px-2 pt-4 fade h-100 w-100 overflow-hidden" id="<?php print $link['href']; ?>" role="tabpanel" aria-labelledby="<?php print $link['id']; ?>">
                <?php print $link['content']; ?>
              </div>
        <?php endif; ?>
      <?php endforeach; ?>
    </div>
</div>