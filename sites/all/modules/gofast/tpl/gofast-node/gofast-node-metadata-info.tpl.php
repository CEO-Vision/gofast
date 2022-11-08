<?php /** @todo rework popularity history modal */ $node_infos["node_popularity"]["info"] = explode("<a", $node_infos["node_popularity"]["info"])[0] . "/ " . $node_infos["node_view_count"]; ?>
  <?php if ($node_infos['message'] != ""):?>
    <div class="alert alert-custom alert-light-warning fade show mb-5" role="alert">
      <div class="alert-text"><?php print $node_infos['message']; ?></div>
    </div>
  <?php endif; ?>

  <div class="row font-size-sm gofast_metadata_infotab" id="document__infotab">
    <?php foreach ($node_infos as $node) : ?>
      <?php if (!empty($node['title'])) : ?>
        <?php if ($node['order'] != '') : ?>
        <div class=" gofast_metadata_field col-xxl-6 d-flex justify-content-between align-items-center document__editable order-<?php echo $node['order'] ?>">
          <div class="font-weight-bolder flex-shrink-0 my-auto">
            <span><?php print $node["title"] ?> :</span>
          </div>
          <?php if (isset($node["node_pk"])) : ?>
            <div class="document__editable--field d-flex w-100 justify-content-end pl-2 text-truncate">
              <div class="spinner document__editable--spinner d-none"></div>
              <?php if ($node['type'] == 'rating') : ?>
                <a class=" p-2 document__editable--label text-truncate" id="" title="<?php print $node['info'] ?>"><?php echo $node['info']; ?></a>
              <?php elseif ($node['type'] != 'language') : ?>
                <a class="btn btn-hover-light btn-sm p-2 document__editable--label text-truncate" id="" title="<?php print $node['info'] ?>"><?php echo $node['info']; ?></a>
              <?php endif ?>
              <?php if ($node['type'] == 'select') : ?>
                <!-- Begin select type  -->
                <div class="document__editable--divfiel document__editable--select w-100 d-none">
                  <select class="form-control form-control-sm document__editable--processe" name="<?php print $node["name"] ?>" data-id="<?php print $node["node_pk"]  ?>" data-vid="<?php print $node["vid"]  ?>">
                    <?php foreach ($node['fields'] as $value) : ?>
                      <?php if (!empty($value['children'])) : ?>
                        <optgroup label="<?php print $value["text"]  ?>">
                          <?php foreach ($value['children'] as $groupe) : ?>
                            <?php $select = $node['value'] == $groupe["text"] ? 'selected' : ''; ?>
                            <option id="<?php print $groupe["id"] ?>" value="<?php echo $groupe["database_name"] ?>" <?php if ($select != '') : ?> selected="selected" <?php endif ?>><?php print $groupe["text"] == "" ? t('None') : $groupe["text"]  ?></option>
                          <?php endforeach ?>
                        </optgroup>
                      <?php else : ?>
                        <?php $select = $node['value'] == $value["text"] ? 'selected' : ''; ?>
                        <option id="<?php print $value["id"] ?>" value="<?php echo $value["database_name"] ?>" <?php if ($select != '') : ?> selected="selected" <?php endif ?>><?php print $value["text"] == "" ? t('None') : $value["text"]  ?></option>
                      <?php endif ?>
                    <?php endforeach  ?>
                  </select>
                </div>
                <!-- End select type  -->
              <?php endif ?>
              <?php if ($node['type'] == 'rating') : ?>
                <!-- Begin ranking type  -->
                <div class="p-2">
                  <div class="d-flex">
                    <?php print $node_infos['rating']['rating'] ?>
                  </div>
                </div>
                <!-- End ranking type  -->
              <?php endif ?>
              <?php if ($node['type'] == 'input') : ?>
                <!-- Begin input type  -->
                <div class="document__editable--divfiel d-none ">
                  <input type="text" class="form-control form-control-sm document__editable--input document__editable--processe <?php echo $node['class'] ?>" value="<?php print $node["value"] ?>" name="<?php print $node["name"] ?>" data-id="<?php print $node["node_pk"]  ?>">
                </div>
                <!-- End input type  -->
              <?php endif ?>
              <?php if ($node['type'] == 'auth') : ?>
                <!-- Begin auth type  -->
                <div class="document__editable--divfiel d-none document__editable--select document__editable--selectAcAuthor w-100 pl-2">
                  <select class="form-control form-control-sm document__editable--processe" name="<?php print $node["name"] ?>" data-id="<?php print $node["node_pk"]  ?>">
                  </select>
                </div>
                <!-- End auth type  -->
              <?php endif ?>
            </div>
          <?php else : ?>
            <div class="p-2 d-flex flex-row-fluid justify-content-end align-items-center text-truncate" id="">
              <?php if ($node['type'] == 'image') : ?>
                <span class="text-truncate" <?= isset($node['more']) ? 'data-toggle="tooltip" data-placement="top"' : ''?>  title="<?php print $node['more'] ?? $node['title'] ?>"><?php print $node['info'] ?></span>
                <div class="symbol symbol-20 ml-1">
                  <?php print $node['picture'] ?>
                </div>
              <?php else : ?>
                <span class="text-truncate" <?= isset($node['more']) ? 'data-toggle="tooltip" data-placement="top"' : ''?> title="<?php print $node['more'] ?? $node['title'] ?>"><?php echo $node['info'] ?></span>
              <?php endif ?>
            </div>
          <?php endif ?>
        </div>
      <?php endif ?>
    <?php endif ?>
  <?php endforeach ?>
</div>
<style>
  .datepicker {
    transform: translateX(-100%);
  }
</style>
