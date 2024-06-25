<!-- Begin text type  -->
<span class="p-2 text-wrap text-right" id="" title="<?php print $info['info'] ?>"><?php echo $info['value']; ?></span>
<div class="document__editable--divfiel d-none">
    <input type="text" class="form-control form-control-sm <?php echo $info['class'] ?>" value="<?php print $info["value"] ?>" name="<?php print $info["name"] ?>" data-id="<?php print $info["node_pk"]  ?>">
</div>
<!-- End text type  -->
