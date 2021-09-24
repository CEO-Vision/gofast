  <!--[if lt IE 8]>
    <p class="browserupgrade">You are using an <strong>outdated</strong> browser. Please <a href="http://browsehappy.com/">upgrade your browser</a> to improve your experience.</p>
  <![endif]-->

  
  <!-- Content -->
  <div class="container" id="gofast_crop_avatar">
     <div class="row">
      <div class="col-md-9 docs-buttons">
        <div class="btn-group">
          <button type="button" class="btn btn-primary" data-method="rotate" data-option="-45" title="<?php print t('Rotate Left', array(), array('context' => 'gofast:gofast_user')); ?>">
            <span class="docs-tooltip" data-toggle="tooltip" title="$().cropper(&quot;rotate&quot;, -45)">
              <span class="fa fa-rotate-left"></span>
            </span>
          </button>
          <button type="button" class="btn btn-primary" data-method="rotate" data-option="45" title="<?php print t('Rotate Right', array(), array('context' => 'gofast:gofast_user')); ?>">
            <span class="docs-tooltip" data-toggle="tooltip" title="$().cropper(&quot;rotate&quot;, 45)">
              <span class="fa fa-rotate-right"></span>
            </span>
          </button>
        </div>
        

        <div class="btn-group">
          <button type="button" class="btn btn-primary" data-method="reset" title="<?php print t('Reset', array(), array('context' => 'gofast')); ?>" id="reset">
            <span class="docs-tooltip" data-toggle="tooltip" title="$().cropper(&quot;reset&quot;)">
              <span class="fa fa-refresh"></span> <?php print t('Reset', array(), array('context' => 'gofast')); ?>
            </span>
          </button>
          <label class="btn btn-primary btn-upload" for="inputImage" title="<?php print t('Upload image file', array(), array('context' => 'gofast')); ?>">
            <input type="file" class="sr-only" id="inputImage" name="file" accept="image/*">
            <span class="docs-tooltip" data-toggle="tooltip" title="<?php print t('Import image with Blob URLs', array(), array('context' => 'gofast')); ?>">
              <span class="fa fa-upload"></span> <?php print t('Upload', array(), array('context' => 'gofast')); ?>
            </span>
          </label>
         
        </div>

        <div class="btn-group btn-group-crop">
          <a class="btn btn-success" uid="<?php print $uid ?>" id="save"><?php print t('Save', array(), array('context' => 'gofast')); ?></a>

         
        </div>
      </div><!-- /.docs-buttons -->
    </div>
    <div class="row">
      <div class="col-md-12">
        <!-- <h3 class="page-header">Demo:</h3> -->
        <div class="img-container-current">
          <img id="current_image" src="<?php print $avatar ?>" />
        </div>
      </div>
    </div> 
    <div class="row">
      <div class="col-md-12">
        <!-- <h3 class="page-header">Demo:</h3> -->
        <div class="img-container">
          <img id="image" src="<?php print $avatar ?>" />
        </div>
      </div>
    </div> 
   
  </div>