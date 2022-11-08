<div class="card card-custom GofastForm__CardContainer">
  <div class="card-body Conference__Form">
    <div class="Conference__Field GofastForm__Field GofastForm__Field--title">
      <?php echo render($form['title']); ?>
    </div>
    <div class="Conference__Field GofastForm__Field GofastForm__Field--datestart">
      <?php echo render($form['field_date']); ?>
    </div>
    <div class="Conference__Field GofastForm__Field GofastForm__Field--dateend">
      <?php echo render($form['field_end_date']); ?>
    </div>
    <div class="Conference__Field GofastForm__Field GofastForm__Field--place">
      <?php echo render($form['field_place']); ?>
    </div>
    <div class="Conference__Field GofastForm__Field GofastForm__Field--content">
      <?php echo render($form['body']); ?>
    </div>
    <div class="Conference__Field GofastForm__Field GofastForm__Field--documents">
      <?php echo render($form['list_documents']); ?>
    </div>
    <div class="Conference__Field GofastForm__Field GofastForm__Field--members">
      <?php echo render($form['list_participants']); ?>
    </div>
    <div class="Conference__Field GofastForm__Field GofastForm__Field--folders">
      <?php echo render($form['folders']); ?>
    </div>
  </div>
  
  <div>
    <?php
     foreach($form as $field_name=>$field){
        if(is_array($form[$field_name])){
            if(isset($form[$field_name]["#gofast_specific_field"])){              
              echo render($form[$field_name]);
            }
        }        
      }
    ?>
  </div>
  
  <div class='card-footer pb-0 pt-3 d-flex GofastAddForms__buttons'>
    <?php echo render($form['actions']); ?>
    <?php drupal_process_attached($form); ?>
  </div>
</div>

<div class="d-none"><?php echo drupal_render_children($form); ?></div>

  
<script>
  jQuery(document).ready(function() {
    jQuery('#edit-field-date-und-0-value .gofastDatetimepicker').on("change.datetimepicker", (e) => {
      jQuery('#edit-field-end-date-und-0-value .gofastDatetimepicker').datetimepicker("date", moment(e.date).add(1, "hours"));
    });
  });
</script>
