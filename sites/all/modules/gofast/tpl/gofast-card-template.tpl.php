<!--
  Note :
  Any modification on this template will modifie all card where this tempalte is used

  Param :
  $class
  $title
  $content
-->
<?php if(isset($child_content) && $child_content == true) : ?>
<div class='card card-custom  <?php print $class  ?>'>
    <div class='px-3'>
        <div class='card-label text-white font-size-h5 text-center text-decoration-underline'>
            <?php print $title  ?>
        </div>
        <div class='card-label text-white font-size-h5'>
            <?php print $content ?>
        </div>
    </div>
</div>
<?php else : ?>
<div class='card card-custom  <?php print $class  ?>'>
    <div class='card-header border-0 max-h-50px min-h-50px h-50px'>
        <div class='card-title'>
            <h5 class='card-label text-white'>
                <?php print $title  ?>
            </h5>
        </div>
    </div>
    <div class='separator separator-solid separator-white opacity-20'></div>
    <div class='card-body bg-white rounded-bottom'>
        <div class="body">
          <?php print $content ?>
        </div>
    </div>
</div>
<?php endif; ?>

