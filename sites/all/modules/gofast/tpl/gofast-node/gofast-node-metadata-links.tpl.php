  <div id="gofast-node-metatadata-links" class="row d-flex flex-wrap font-size-sm">

    <!-- BEGIN Filed publication source-->
    <?php if (!empty($node_infos['node_publication_source']['value'])): ?>
      <div class="col-12 mt-4">
        <div class="font-weight-bolder my-auto"><?php echo $node_infos['node_publication_source']['title'] ?> :</div>
        <div class="d-flex">
          <?php echo $node_infos['node_publication_source']['value'] ?>
        </div>
      </div>
      <?php endif; ?>
    <!-- END Filed publication source  -->

    <!-- BEGIN Filed publication -->
    <?php if (!empty($node_infos['node_publication']['value'])): ?>
      <div class="col-12 mt-4">
        <div class="font-weight-bolder my-auto"><?php echo $node_infos['node_publication']['title'] ?> :</div>
        <div class="d-flex text-truncate">
          <?php echo $node_infos['node_publication']['value'] ?>
        </div>
      </div>
      <?php endif; ?>
    <!-- END Filed publication   -->

    <!-- BEGIN Filed target_links  -->
    <div class="col-12 col-xxl-6 mt-4">
      <span class="font-weight-bolder mb-4"><?php print $node_infos['node_target_links']['title'] ?> :</span>
      <?php if (isset($node_infos['node_target_links']["node_pk"])) { ?>
        <div class="go-lien-listgroup bg-hover-light rounded document__editable--processe" style="list-style:none;" id="tags-list-ac">

          <?php if (empty(json_decode($node_infos['node_target_links']["json_target_links_tags"], TRUE))) { ?>
            <a class="btn btn-hover-light btn-sm p-2 document__editable--label" id=""><?php echo t('None') ?></a>
          <?php  } ?>

          <div class="document__editable--select">
            <input class="gofast_display_none" type="text" id="edit-actagify-ac-list-tags-target-links" name="gofast_tagify_ac" value='<?php print $node_infos['node_target_links']['json_target_links_tags'] ?>' size="60" maxlength="128">
            <input class="js-tagify metadata-node border-0 " data-node="" data-pk="<?php print $node_infos['node_target_links']['node_pk'] ?>" type="text" id="edit-field-taget-link" data-name="<?php print $node_infos['node_target_links']['name'] ?>" name="ac-list-tags-target-links" value="" size="60" maxlength="">
          </div>

        </div>
      <?php } else { ?>
        <?php if (!empty($node_infos['node_target_links']['existe_link_tpl']) && $node_infos['node_target_links']['existe_link_tpl'] != null) {
          print $node_infos['node_target_links']['existe_link_tpl'];
        } else { ?>
          <div class="p-2"><?php echo t('None') ?></div>
        <?php } ?>
      <?php } ?>
    </div>
    <!-- END Filed target_links  -->

    <!-- BEGIN Filed source_links  -->
    <div class="col-12 col-xxl-6 mt-4">
      <span class="font-weight-bolder mb-4"><?php print t('Links from') ?> :</span>
      <div>
        <?php //print "<pre>"; print_r($node_infos['node_source_links']);
        ?>
        <ul class="p-0 m-0 list-unstyled">
          <?php if (isset($node_infos['node_source_links']) && !empty($node_infos['node_source_links'])) { ?>
            <?php
              foreach ($node_infos['node_source_links'] as $node) {
                $node_icon = gofast_node_get_icon($node);
                $node_link = '/node/'.$node->nid;
                $node_title = $node->title;
                $node_theme = theme('gofast_metadata_node_link', array('icon' => $node_icon, 'link' => $node_link,'title' => $node_title));
                print $node_theme;
              }
            ?>
          <?php } else { ?>
            <div class="p-2"><?php echo t('None') ?></div>
          <?php } ?>
        </ul>
      </div>
    </div>
    <!-- END Filed source_links  -->

    <!-- BEGIN Filed external link  -->
    <div class="col-12 col-xxl-6 mt-4">
      <div class="font-weight-bolder my-auto"><?php print $node_infos['node_external_page_url']['title'] ?> :</div>
      <div class="document__editable--field d-flex w-100 h-100">
        <div class="spinner document__editable--spinner d-none" style="margin: auto;"></div>
        <?php if (isset($node_infos['node_external_page_url']["node_pk"])) : ?>
          <?= theme("gofast_metadata_external_links",array("node_infos" => $node_infos)); ?>
        <?php else : ?>
          <div class="p-2 overflow-hidden d-flex" id=""><?php echo $node_infos['node_external_page_url']['span_value'] ?></div>
        <?php endif ?>
      </div>
    </div>
    <!-- END Filed external link  -->


    <!-- Begin language type  -->
    <div class="col-12 col-xxl-6 mt-4">
      <span class="font-weight-bolder mb-4"><?php print t('Language') ?> :</span>
      <div class="d-flex mt-1">
        <?php if (isset($node_infos['node_language']["node_pk"])) : ?>
          <div class="d-flex w-60px">
            <div class="spinner document__editable--spinner d-none" style="z-index: 1000;"></div>
            <div class="btn btn-sm symbol symbol-20 document__editable--label position-relative py-2">
              <img class="metadata-language-flag" alt="Pic" src="<?php print $node_infos['node_language']['flag'] ?>" />
            </div>
            <div class="document__editable--divfield document__editable--select select-langue d-none w-100">
            <select class="form-control form-control-sm document__editable--processe" name="<?php print $node_infos['node_language']["name"] ?>" data-id="<?php print $node_infos['node_language']["node_pk"]  ?>">
              <?php foreach ($node_infos['node_language']['fields'] as $language) {
              $select = $node_infos['node_language']['value'] == $language["id"] ? 'selected' : '';
              $disabled = isset($language['disabled']) && $language['disabled'] == true ? 'disabled' : '';
            ?>
              <option value="<?php print $language["id"] ?>" data-flag="<?php print $language["icon"] ?>" <?php print $disabled ?> <?php print $select ?>>
                <?php print $language["text"]  ?>
              </option>
              <?php }  ?>
            </select>
          </div>
          </div>
          <div class="d-flex p-2">
            <?php if (isset($node_infos['node_language']['have_translate'])) : ?>
              <div class="d-flex mr-4">/</div>
              <?php foreach ($node_infos['node_language']['have_translate']['translations'] as $langue) : ?>
                <div class="d-flex w-40px">
                  <a class="symbol symbol-20" href="<?php print $langue['href'] ?>" title="<?php print $langue['title'] ?>">
                    <img class="h-20px w-20px rounded-sm" src="<?php print $langue['icon'] ?>" alt="flag_<?php print $langue['key'] ?>">
                  </a>
                </div>
              <?php endforeach ?>
            <?php endif ?>
          </div>

        <?php else : ?>
          <div class="symbol symbol-20 p-2">
            <img alt="Pic" src="<?php print $node_infos['node_language']['flag'] ?>" />
        </div>
      <?php endif ?>
      </div>
    </div>
    <!-- End language type  -->
       <div class="col-12 col-xxl-12 mt-4">
            <?php if ($node_infos['node_target_lien'] !== "" || $node_infos['node_source_lien'] !== "") : ?>
            <span class="font-weight-bolder mb-4"><?php print t('Proof of signature') ?> :</span>
             <div class="d-flex">
                  <?php if ($node_infos['node_target_lien'] !== "") : ?>
                   <div class="p-2" id="" ><?php echo $node_infos['node_target_lien']; ?></div>  
                    <?php else: ?>
                   <div class="p-2" id="" ><?php echo $node_infos['node_source_lien']; ?></div>
                    <?php endif; ?>
             </div>
            <?php endif ?>
       </div>
  </div>