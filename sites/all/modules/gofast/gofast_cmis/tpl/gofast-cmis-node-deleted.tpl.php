<h2>
  <center>
    <span class='fa fa-trash-o'></span>
      <?php echo t('This content is deleted'); ?>
  </center>
</h2>
<h4>
  <center>
  <?php if(gofast_contextual_menu_user_can_delete_node($node, NULL, NULL, NULL)
            && gofast_contextual_menu_node_not_locked($node, NULL, NULL, NULL)
            && gofast_contextual_menu_node_not_archived($node, NULL, NULL, NULL)
            && gofast_contextual_menu_is_not_multifiled($node, NULL, NULL, NULL)) {
            echo t('To restore, go through the contextual menu', array(), array("context" => "gofast:gofast_cmis"));
    } else {
      echo t('To restore, please contact a space administrator', array(), array("context" => "gofast:gofast_cmis"));
    } ?>
  </center>
</h4>
