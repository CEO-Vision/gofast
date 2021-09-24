<!-- .publisher -->
  <div class="publisher todolist-form <?php foreach($form['label']['#attributes']['class'] as $key=> $class){ echo $class.' '; }; ?>"  class="<?php echo drupal_html_id($form['label']['#name']) ?>">
      <!-- .publisher-input -->
      <div class="publisher-input pr-0"> 
        <input id="<?php echo $form['label']['#id'] ?>"  name="<?php echo $form['label']['#name'] ?>" 
               class="form-control form-control-reflow <?php foreach($form['label']['#attributes']['class'] as $key=> $class){ echo $class.' '; }; ?>" 
               placeholder="<?php echo t('Add an item', array(), array('context' => 'gofast_kanban')); ?>" autocomplete="off">
        
      </div>
      
     
      <!-- /.publisher-input -->
    <!-- .publisher-actions -->
    <div class="publisher-actions">
      <!-- .publisher-tools -->
      <div class="publisher-tools pb-0">
<!--        <div class="row">
          <div class="col-6">
             <?php print drupal_render_children($form, array( 'assignee'));  ?>
          </div>
          <div class="col-6">
             <?php print drupal_render_children($form, array( 'deadline'));  ?>
          </div>
        </div>-->
        <button type="button" class="btn btn-success add-todo" onclick="KanbanBoard.addTodo($(this));"><?php echo t('Add', array(), array('context' => 'gofast_kanban')); ?></button>
        <button type="button" class="btn btn-secondary cancel-add-todo" onclick="KanbanBoard.cancelAddTodo($(this));"><i class="fa fa-times"></i>&nbsp;<?php echo t('Cancel', array(), array('context' => 'gofast_kanban')); ?></button>
      </div>
      <!-- /.publisher-tools -->
    </div>
    <!-- /.publisher-actions -->
  </div>
  
   <?php print drupal_render_children($form, array( 'form_build_id', 'form_token', 'form_id', 'cid'));  ?>
  <!-- /.publisher -->
  
  <script type="text/javascript">
    
    $(document).ready(function() {
      $('#gofast-kanban-checklistitem-form').keydown(function(event) {
        var key = event.which;
        if(key == 13){
          event.preventDefault();
          KanbanBoard.addTodo($('.btn.btn-success.add-todo'));
          return false;
          }
      });
    });
    
  </script>