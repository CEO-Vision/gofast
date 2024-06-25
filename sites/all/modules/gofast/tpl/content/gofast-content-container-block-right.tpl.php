<?php $detect = new Mobile_Detect(); ?>
<!--begin::Row-->
<div class="<?= gofast_essential_is_essential() ? "" : "gofast-content--right ";?>mainContent" <?= gofast_essential_is_essential() ? "style='grid-column-end: 4;'" : ""; ?>>
  <?php echo $content; ?>
</div>

<?php if (gofast_essential_is_essential()) : ?>
    <div id="side-content-container" <?= !gofast_mobile_is_phone() ? "class='side-content-container-essential'" : ""; ?>>
        <div class="gofast-content--right sideContent">
            <!--begin::Stats Side Content-->
          <?php echo $sideContent; ?>
            <!--end::Stats Side Content-->
        </div>
    </div>
<?php else : ?>
    <div class="gofast-content--right sideContent">
        <!--begin::Stats Side Content-->
      <?php echo $sideContent; ?>
        <!--end::Stats Side Content-->
    </div>
<?php endif; ?>

<?php if (gofast_mobile_is_phone()) : ?>
  <div id="side-content-toggle-top-30" class=""><i class="fas fa-chevron-left"></i>
  </div> 
<?php endif; ?>
<!--end::Row-->
