<!-- Begin switch type  -->
<span class="document__editable--processe document__editable--switch switch switch-sm switch-icon gofast-switch-icon">
    <label>
        <input type="checkbox" name="<?php print $info["name"] ?>" data-id="<?php print $info["node_pk"]  ?>" <?= $info["value"] == 1 ? " checked" : "" ?>>
        <span></span>
    </label>
</span>
<!-- End switch type  -->