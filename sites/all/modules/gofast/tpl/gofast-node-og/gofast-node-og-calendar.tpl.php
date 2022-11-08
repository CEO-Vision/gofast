<div class="h-100 w-100 d-flex flex-column">
  <div class="mb-4 text-right d-none">
    <a href="#" class="btn btn-light-primary font-weight-bold btn-sm">
      <i class="ki ki-plus icon-md mr-2"></i>
      <?php print t('Add event', [], []); ?>
    </a>
  </div>
  <div class="h-100 ktCalendarParentContainer">  
    <div class="gofastCalendar" id="kt_calendar" data-id="<?php print $node->nid; ?>"></div>
  </div>

</div>

