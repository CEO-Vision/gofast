    <select class="form-control form-select" id="wf-process-<?php print $variables['process_id'] ?>" style="max-width: 80%;">
        <option value="0"> <?php print t("Default"); ?> </option>
        <?php foreach ($variables['profils']  as $profil) : ?>
            <option value="<?php print $profil->id ?>"><?php print $profil->name ?></option>
        <?php endforeach ?>
    </select>


    <div class="gofast_wf_actions">
        <?php echo $actions; ?>
    </div>
