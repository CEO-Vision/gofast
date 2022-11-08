<div id="gofast-node-info-basic">
  <div class="row font-size-sm gofast_metadata_infotab" id="document__infotab">
    <?php foreach ($extra_infos as $key => $info) { ?>
      <div class=" gofast_metadata_field col-12 d-flex justify-content-between align-items-center document__editable order-<?php echo $info['order'] ?>">

        <div class="font-weight-bolder flex-shrink-0 my-auto">
          <span><?php print $info["title"] ?> :</span>
        </div>

        <div class="document__editable--field d-flex w-100 justify-content-end pl-2 text-truncate">
          <div class="spinner document__editable--spinner d-none"></div>
          
          <?php if ($info['type'] == 'input') : ?>
            <!-- Begin input type  -->
            <a class="btn btn-hover-light btn-sm p-2 document__editable--label text-truncate" id="" title="<?php print $info['info'] ?>"><?php echo $info['info']; ?></a>
            <div class="document__editable--divfiel d-none">
              <input type="text" class="form-control form-control-sm document__editable--input document__editable--processe <?php echo $info['class'] ?>" value="<?php print $info["value"] ?>" name="<?php print $info["name"] ?>" data-id="<?php print $info["node_pk"]  ?>">
            </div>
            <!-- End input type  -->
          <?php endif; ?>
            
            
          <?php if ($info['type'] == 'select') : ?>
              <a class="btn btn-hover-light btn-sm p-2 document__editable--label text-truncate" id="" title="<?php print $info['info'] ?>"><?php echo $info['info']; ?></a>
              <div class="document__editable--divfiel document__editable--select w-100 d-none">
                <select class="form-control form-control-sm document__editable--processe" name="<?php print $info["name"] ?>" data-id="<?php print $info["node_pk"]  ?>">
                  <?php foreach ($info['fields'] as $value) : ?>
                    <?php $select = $info['value'] == $value["text"] ? 'selected' : ''; ?>
                    <option id="<?php print $value["id"] ?>" value="<?php echo $value["text"] ?>" <?php if ($select != '') : ?> selected="selected" <?php endif ?>><?php print $value["text"] == "" ? t('None') : $value["text"]  ?></option>
                  <?php endforeach  ?>
                </select>
              </div>
          <?php endif; ?>

        </div>
      </div>
    <?php } ?>
  </div>
</div>
