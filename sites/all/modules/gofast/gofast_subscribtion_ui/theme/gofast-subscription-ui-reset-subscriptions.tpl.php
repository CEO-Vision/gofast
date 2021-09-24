


<span>
  <p><?php echo $info; ?></p>
  <?php if(isset($continue)){ ?>
    <div class="btn-group" role="group" aria-label="...">
      <button type="button" class="btn btn-primary" onclick="window.location.href='process-reset'"><?php echo t('Continue', array(), array('context' => 'gofast:subscription_ui')); ?></button>
    </div>
  <?php } ?>
</span>