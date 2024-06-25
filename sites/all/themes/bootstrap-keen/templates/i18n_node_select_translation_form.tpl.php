<?php $node = $form['#node']['#value']; ?>
<div id="edit-translations">
    <legend class="panel-heading">
        <span class="panel-title fieldset-legend"><?= t('Select translations for %title', array('%title' => $node->title)) ?></span>
    </legend>
    <div role="application">
        <div class="help-block"><?= t("Alternatively, you can select existing nodes as translations of this one or remove nodes from this translation set. Only nodes that have the right language and don't belong to other translation set will be available here.") ?></div>
        <table class="table table-hover table-striped">
            <tbody>
                <?php
                foreach ($form['translations']['language'] as $langcode => $lang) :
                    if (!isset($lang["#value"]) || !isset($form['translations']['node'][$langcode])) {
                        continue;
                    }
                ?>
                    <tr>
                        <td><?= $lang["#value"] ?></td>
                        <td style="width: 80%;">
                            <?= render($form['translations']['node'][$langcode]); ?>
                        </td>
                        <td>
                            <?=  render($form['translations']['action_add'][$langcode]); ?>
                        </td>
                    </tr>
                <?php endforeach; ?>
            </tbody>
        </table>
    </div>
    <?= render($form['actions']) ?>
    <?php drupal_process_attached($form); ?>
    <div class="d-none"><?php echo drupal_render_children($form); ?></div>
</div>