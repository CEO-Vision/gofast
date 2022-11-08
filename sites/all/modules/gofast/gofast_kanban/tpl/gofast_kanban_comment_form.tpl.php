 <h6>
      <?php echo t('Comment(s)', array(), array('context' => 'gofast_kanban')); ?>
</h6>
<div class="publisher gf-card-comment-body-form <?php echo drupal_html_id($form['comment_body'][LANGUAGE_NONE][0]['value']['#name']) ?>" class="form-control <?php foreach($form['comment_body']['#attributes']['class'] as $key=> $class){ echo $class.' '; }; ?>">
 
  <!--<label for="publisherInput1" class="publisher-label"><?php print t('Add a new comment', array(), array('context' => 'gofast_kanban')); ?> </label> --> 
  <div class="publisher-input task-new-comment">
    <textarea id="<?php echo $form['comment_body'][LANGUAGE_NONE][0]['value']['#id'] ?>" name="<?php echo $form['comment_body'][LANGUAGE_NONE][0]['value']['#name'] ?>" class="form-control <?php foreach($form['comment_body'][LANGUAGE_NONE][0]['#attributes']['class'] as $key=> $class){ echo $class.' '; }; ?>" placeholder="<?php echo t('Enter your comment', array(), array('context' => 'gofast_kanban')); ?>"></textarea>
  </div>
  
  <?php //print_r ($form['comment_body']); ?>
  
  
  <div class="publisher-actions">

    <div class="publisher-tools mr-auto">
      <!--                  <div class="btn btn-light btn-icon fileinput-button">
                          <i class="fa fa-paperclip"></i> <input type="file" id="attachment1" name="attachment1[]" multiple="">
                        </div>
                        <button type="button" class="btn btn-light btn-icon"><i class="far fa-smile"></i></button>-->
    </div>
    <button type="button" class="btn btn-success btn-add-task-comment" onmousedown="KanbanBoard.addNewComment()"><?php echo t('Publish', array(), array('context' => 'gofast_kanban')); ?></button>
  </div>
</div>
<?php print drupal_render_children($form, array('author', 'form_build_id', 'form_token', 'form_id')); ?> 