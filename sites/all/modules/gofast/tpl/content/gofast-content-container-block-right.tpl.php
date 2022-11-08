<!--begin::Row-->
<div class="gofast-content--right mainContent">
  <?php echo $content; ?>
</div>

<?php if (gofast_mobile_is_mobile_domain()) : ?>
    <div id="side-content-container">
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

<?php if (gofast_mobile_is_mobile_domain()) : ?>
    <div id="side-content-toggle-top-30" class=""><i class="fas fa-chevron-left"></i>
    </div>
<?php endif; ?>
<!--end::Row-->
