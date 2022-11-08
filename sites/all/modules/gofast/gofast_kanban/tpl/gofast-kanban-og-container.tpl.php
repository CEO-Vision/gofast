<?php 
if ($node->type != 'kanban'){
  $kanban_id = gofast_kanban_get_space_kanban($node->nid)[0];
}else{
  $kanban_id = $node->nid;
}

 ?>
<div class="mx-4 mb-4 mt-0">
    <div  class="container">
        <div class="row">
            <div class="col">
                <div class="input-icon">
                    <input type="text" class="form-control" placeholder="<?php echo t('Search...', array(), array('context' => 'gofast_kanban')); ?>" id="gofastKanbanSearchQuery">
                    <span>
                        <i class="fas fa-search text-muted"></i>
                    </span>
                </div>
            </div>
            <?php $detect = new Mobile_Detect;?>
            <?php if( ! $detect->isMobile()) : ?>
            <div class="col col-5">
                <div class="gofastKanban__newColumn">
                    <div>
                        <form class="newColumn__form">
                            <div class="form-group mb-0">
                                <div class="input-group">
                                    <input type="text" class="form-control newColumn__input" name="title"  placeholder="<?php echo t('Enter new column title', array(), array('context' => 'gofast_kanban')) ?>"/>

                                    <div class="newColumn__actions input-group-append">
                                        <button type="submit" class="btn btn-primary mr-2">
                                            <?php echo t('Add Column', array(), array('context' => 'gofast_kanban')) ?>
                                        </button>
                                    </div>
                                </div>
                                <span class="form-text text-danger newColumn__message"></span>
                            </div>
                        </form>
                    </div>
                </div>
            </div>
            <?php endif; ?>
        </div>
    </div>
</div> 


<div class="w-100 position-relative" id="gofastKanban" data-kid="<?php echo $kanban_id ?>" style="height: calc(100vh - 250px) /*!important;*/">
    <div class="spinner gofastSpinner spinner-primary spinner-lg position-absolute fade show " style="top: 50%; left: 50%;"></div>
    <div id="goKanban" class="gofastKanban__kanban fade overflow-auto h-100"></div>
</div>


<!-- Modal-->
<div class="modal fade" id="gofastKanbanModal" role="dialog" aria-labelledby="exampleModalLabel" aria-hidden="true">
    <div class="modal-dialog modal-xl modal-dialog-scrollable kanban-modal" >
        <div class="modal-content">
            <div class="modal-header">
                <div class="modal-title font-size-h5 text-white" id="exampleModalLabel"><?php echo t("Task Detail", array(), array('context'=>'gofast_kanban')); ?></div>
                <button type="button" class="close" data-dismiss="modal" aria-label="Close">
                    <i aria-hidden="true" class="ki ki-close"></i>
                </button>
            </div>
            <div class="modal-taskDetail overflow-auto modal-body"></div>
            <div class="modal-footer"></div>
        </div>
    </div>
</div>

<?php drupal_add_js(drupal_get_path('module', 'gofast_kanban') . "/js/gofastTodoList.js"); ?>
<?php drupal_add_js(drupal_get_path('module', 'gofast_kanban') . "/js/gofastKanbanCardDetail.js"); ?>
<?php drupal_add_js(drupal_get_path('module', 'gofast_kanban') . "/js/gofastKanban.js"); ?>
