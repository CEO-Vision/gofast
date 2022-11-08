<div class="btn-group" role="group" aria-label="Button group with nested dropdown">
  <div class="btn-group dropdown" role="group">
    <button id="dropdown-rapid" type="button" class="btn btn-sm btn-info text-primary dropdown-toggle" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false" style="background-color:transparent">
      <?php echo t('Meetings', array(), array('context' => 'gofast_cdel')); ?> <span></span>
    </button>

    <div class="dropdown-menu">
      <a class="dropdown-item" id="dashboard-calendar-selection-meetings">
        <?php echo t('Meetings', array(), array('context' => 'gofast')); ?>
      </a>
      <a class="dropdown-item" id="dashboard-calendar-selection-deadlines">
        <?php echo t('Documents deadlines', array(), array('context' => 'gofast_cdel')); ?>
      </a>
    </div>
  </div>
</div>
<a href="/node/add/conference" style='margin-left:5px;' data-toggle="tooltip" data-html="true" title="<?php echo t('New meeting', array(), array('context' => 'gofast')); ?>">
  <span class="fa fa-plus"></span>
</a>
