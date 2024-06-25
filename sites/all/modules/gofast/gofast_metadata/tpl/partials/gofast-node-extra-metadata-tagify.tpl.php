<!-- Begin tagify type  -->
<div class="pl-4 w-100">
    <tags></tags>
    <div class="go-lien-listgroup bg-hover-light rounded" id="tags-list-ac">
        <input class="js-tagify metadata-node border-0" placeholder="Essayez d'ajouter des étiquettes depuis la liste" data-taxonomy_term="" data-enforce="" data-vid="<?php print $info['vid'] ?>" data-pk="<?php print $info['node_pk'] ?>" type="text" id="edit-field-custom-keywords" data-name="<?php print $info['name'] ?>" name="ac-list-tags-custom-keywords" size="60" maxlength="" data-oninput="<?php print $info["oninput"]; ?>">
        <input class="gofast_display_none" type="text" id="edit-actagify-ac-list-tags-custom-keywords" name="gofast_tagify_ac" value="<?php print htmlspecialchars($info['value']) ?>" size="60" maxlength="128">
    </div>
</div>
<!-- End tagify type  -->
