<?php if($is_confidential): ?>
  <div class="alert alert-custom alert-light-warning fade show mb-5" role="alert">
    <div class="alert-text"><?= t("This document is confidential: you can't download and share it", array(), array('context' => 'gofast:gofast_cmis')); ?></div>
  </div>
<?php endif; ?>
<?php if($async){ ?> <div class="tab-pane" id="document__historytab" role="tabpanel" aria-labelledby="nav-info-tab"> <?php } ?>
  <div class="historytab__revision mt-4">
    <div class="font-weight-bolder font-size-sm mb-4 mr-4"><?php print  t('Revision by', array(), array('context' => 'gofast:gofast_cmis')) ?> : </div>
    <div class="navbar navbar-light bg-faded">
      <ul class="nav nav-pills">
        <li class="nav-item" title="<?php print  t('Show only current version', array(), array('context' => 'gofast:gofast_cmis')) ?>">
          <a class="nav-link active py-1" data-toggle="tab" href="#current_version"><?php print  t('Current', array(), array('context' => 'gofast:gofast_cmis')) ?></a>
        </li>

        <li class="nav-item" title="<?php print t('Show only major versions', array(), array('context' => 'gofast:gofast_cmis')) ?>">
          <a class="nav-link py-1" data-toggle="tab" href="#major_version"><?php print  t('Major', array(), array('context' => 'gofast:gofast_cmis')) ?></a>
        </li>

        <li class="nav-item" title="<?php print t('Show all versions of the document', array(), array('context' => 'gofast:gofast_cmis')) ?>">
          <a class="nav-link py-1" data-toggle="tab" href="#all_version"><?php print t('All', array(), array('context' => 'gofast:gofast_cmis')) ?></a>
        </li>
      </ul>
    </div>

    <div class="tab-content">

      <?php foreach ($version as $name_version => $version_html) : ?>
        <div id="<?php print $name_version ?>" class="tab-pane <?php print $name_version == 'current_version' ? "active" : "" ?>">
          <div class="w-100 d-flex flex-wrap p-3 border border-1 mt-4 rounded gf-version-tag pre-scrollable align-items-center max-h-100px">
            <?php echo $version_html ?>
          </div>


          <?php if (isset($content_version[$name_version])) : ?>
            <div id="<?php print $name_version ?>" class="tab-pane <?php print $name_version == 'current_version' ? "active" : "" ?>">
              <?php foreach ($content_version[$name_version] as $user) : ?>
                <div class="historytab__cell d-flex w-100 justify-content-between">
                  <div class="py-4 d-flex align-items-center">
                    <?php print $user['avatar']; ?>
                    <div class="cell__info font-size-md ml-2">
                      <div>
                        <?php echo $user['auth'] ?>
                        <?php echo $user['date'] ?>
                      </div>
                      <span class="text-muted">
                        <?php echo "(" . $user['type'] . ")" ?>
                      </span>
                    </div>
                  </div>
                  <div class="font-weight-bolder my-auto">
                    <?php if (isset($user['href'])) { ?>
                      <a href="<?php echo $user['href'] ?>" class="font-size-lg"><?php echo $user['version'] ?></a>
                    <?php } else { ?>
                      <span class="text-muted"><?php echo $user['version'] ?></span>
                    <?php } ?>
                  </div>
                </div>
              <?php endforeach ?>
            </div>
          <?php endif ?>


        </div>
      <?php endforeach ?>
    </div>
  </div>
  <?php if($async){ ?> </div> <?php } ?>
