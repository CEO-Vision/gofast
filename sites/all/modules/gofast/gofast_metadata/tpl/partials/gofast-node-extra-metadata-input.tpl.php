<!-- Begin input type  -->
<a class="btn btn-hover-light btn-sm p-2 document__editable--label text-wrap text-right" id="" title="<?php print $info['info'] ?>"><?php echo $info['info']; ?></a>
<div class="document__editable--divfiel d-none">
    <input type="text" class="form-control form-control-sm document__editable--input document__editable--processe <?php echo $info['class'] ?>" value="<?php print $info["value"] ?>" name="<?php print $info["name"] ?>" data-id="<?php print $info["node_pk"]  ?>">
</div>
<!-- End input type  -->