<?php $detect = new Mobile_Detect; ?>

<?php if ($detect->isMobile() || $detect->isTablet()) : ?>
  <div id="gofast_mobile_panel" class="gofast_animation_right Document Document__Mobile region-sidebar-second">
    <?php else : ?>
      <div class="region-sidebar-second">
        <aside role="complementary" class="Document Document__Simple">
        <?php endif ?>
        <?php if (gofast_essential_is_essential() && !$detect->isMobile() && !$detect->isTablet()) { ?>
          <section id="block-gofast-cmis-gofast-cmis-fast-upload-file" class="block block-gofast-cmis contextual-links-region clearfix">
            <?php $block_cmis_upload = module_invoke('gofast_cmis', 'block_view', 'gofast_cmis_fast_upload_file');
            print $block_cmis_upload['content'];
            ?>
          </section>
        <?php } ?>

        <?php if ($context === 'node') : ?>
          <div class="panel panel-info">
            <?php if (gofast_essential_is_essential() && $detect->isMobile()) : ?>
              <div id="panel-heading-title" class="panel-heading">
                <?php
                if (node_access('update', $node)) {
                  echo '<i class="fa fa-pencil mobile-rename-node col-xs-1" aria-hidden="true"></i>';
                  $title = pathinfo($title)['filename'];
                }
                ?><h3 class="panel-title"><?php print $title ?></h3>
                <?php if (module_exists('gofast_workflows') && $node->type == 'alfresco_item' && ($detect->isMobile() || $detect->isTablet())) {
                  echo gofast_mobile_get_node_workflow($node);
                } ?>
              </div>
              <div id="panel-heading-title-edit" class="panel-heading" style="display: none;">
                <div class="form-group" style="margin-bottom: 0px;">
                  <input type="text" class="panel-title-edit form-control" value="<?php print $title; ?>">
                  <button type="button" class="btn btn-success">
                    <i class="fa fa-check"></i>
                  </button>
                  <button type="button" class="btn btn-danger">
                    <i class="fa fa-times"></i>
                  </button>
                </div>

              </div>
            <?php endif; ?>
            <div class="panel-body">
              <?php print $info ?>
            </div>
            <?php if ($detect->isMobile() || $detect->isTablet()) : ?>
              <div class="panel-footer">
                <?php print $actions ?>
              </div>
            <?php endif ?>
          </div>
        <?php elseif ($context === 'search') : ?>
          <div class="panel panel-default">
            <?php print $info ?>
          </div>
        <?php elseif ($context === 'directories') : ?>
          <div class="panel panel-default">
            <div class="panel-body">
              <?php print $info ?>
            </div>
          </div>
        <?php endif; ?>

        <?php if ($detect->isMobile() || $detect->isTablet()) : ?>
      </div>
      <div id="gofast_mobile_arrow" class="gofast_animation_right">
        <span class="glyphicon glyphicon-menu-right center-block" aria-hidden="true"></span>
      </div>
  <?php else : ?>
    </aside>
  </div>
<?php endif ?>
