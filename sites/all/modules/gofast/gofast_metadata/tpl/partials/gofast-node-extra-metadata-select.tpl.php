<!-- Begin select type  -->
<a class="btn btn-hover-light btn-sm p-2 document__editable--label text-truncate" id="" title="<?php print $info['info'] ?>"><?php echo $info['info']; ?></a>
<div class="document__editable--divfiel document__editable--select w-100 d-none">
    <select class="form-control form-control-sm document__editable--processe" name="<?php print $info["name"] ?>" data-vid="<?php print $info["vid"]  ?>" data-id="<?php print $info["node_pk"]  ?>">
        <?php foreach ($info['fields'] as $value) : ?>
            <?php $select = $info['value'] == $value["text"] ? 'selected' : ''; ?>
            <option value="<?php echo $value["text"] ?>" <?php if ($select != '') : ?> selected="selected" <?php endif ?>><?php print $value["text"] == "" ? t('None') : $value["text"]  ?></option>
        <?php endforeach  ?>
    </select>
</div>
<!-- End select type  -->
