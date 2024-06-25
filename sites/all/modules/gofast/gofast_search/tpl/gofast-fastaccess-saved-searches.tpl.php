<div class="dropdown-menu dropdown-menu-right">
    <h4 class="dropdown-header font-weight-bolder font-size-lg"><?= t("Saved Searches", array(), array("context" => "gofast:search")) ?></h4>
    <?php if(!empty($searches)): ?>
        <?php foreach($searches as $search):?>
           <?php echo $search->href; ?>
        <?php endforeach ?>
    <?php else: ?>
        <div class="p-4 max-w-300px">
            <p class="text-muted  font-size-lg text-truncate">
                <?php echo t("You do not have any saved searches yet!", array(), array('context' => 'gofast:search'))?>
            </p>
        </div>
    <?php endif ?>
</div>
<button type="button" class="btn-icon input-group-text" onClick="$('#search-block-form').submit();">
    <i class="fas fa-search"></i>
</button>
<button type="button" class="btn-icon input-group-text" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
    <i class="fas fa-arrow-down"></i>
</button>
