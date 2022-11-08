<script type="text/javascript">atatus.setTags(['content']);</script >
<div class="gofast-content__node GofastNode">
    <div class="mainContent">
      <?php print $content; ?>
    </div>

  <?php if (gofast_mobile_is_mobile_domain()) : ?>
      <div id="side-content-container">
          <div class="sideContent">
            <?php print $side_content; ?>
          </div>
      </div>
  <?php else : ?>
      <div class="sideContent">
        <?php print $side_content; ?>
      </div>
  <?php endif; ?>

  <?php if (gofast_mobile_is_mobile_domain()) : ?>
          <div id="side-content-toggle" class=""><i class="fas fa-chevron-left"></i></div>
  <?php endif; ?>
</div>


