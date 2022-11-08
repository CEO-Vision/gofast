<?php ?>
<html lang="en" style='font-size:12px;'>
  <head>
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
    <?php
    define('LOOPER_THEME_DIR_CSS', '/ressources/looper-v1.2.1/assets/stylesheets/');
    define('LOOPER_THEME_DIR_JS', '/ressources/looper-v1.2.1/assets/javascript/');
    define('LOOPER_THEME_DIR_VENDOR', '/ressources/looper-v1.2.1/assets/vendor/');
    ?>
<!--
     BEGIN THEME STYLES 
    <link rel="stylesheet" href="../<?php echo drupal_get_path('module', 'gofast_kanban') . LOOPER_THEME_DIR_CSS . 'theme.css' ?>" data-skin="default">

     BEGIN OTHER STYLES 
    <link rel="stylesheet" href="../<?php echo drupal_get_path('module', 'gofast') . '/css/font-awesome.css' ?>" data-skin="default">
    <link rel="stylesheet" href="../<?php echo drupal_get_path('module', 'gofast_kanban') . LOOPER_THEME_DIR_VENDOR . 'open-iconic/css/open-iconic-bootstrap.min.css' ?>" >
    <link rel="stylesheet" href="../<?php echo drupal_get_path('module', 'gofast_kanban') . LOOPER_THEME_DIR_VENDOR . 'tributejs/tribute.css' ?>" >
    <link rel="stylesheet" href="../<?php echo drupal_get_path('module', 'gofast_kanban') . LOOPER_THEME_DIR_VENDOR . 'simplemde/simplemde.min.css' ?>" >
    <link rel="stylesheet" href="../<?php echo drupal_get_path('module', 'gofast_kanban') . LOOPER_THEME_DIR_VENDOR . 'flatpickr/flatpickr.min.css' ?>" >-->

  </head>
  <body>
     
    <?php
      $detect = new Mobile_Detect;
      //detect if the user_agent correspond to an old IE
      $IE_version = $detect->version('IE');
      
      $title = t("Unsupported browser detected", array(), array("context" => "gofast")); 
      $details = t('The feature "Tasks" in not compatible with your current browser. <br/> Please use one of the followings : ', array(), array("context" => "gofast_kanban"));
      
      if ($IE_version == "7.0" || $IE_version == "8.0" || $IE_version == "9.0" || $IE_version == "10.0" || $IE_version == "11.0"): 
    ?>
    
    <div class="alert alert-warning" role="alert">
        <h4 class="alert-heading"><?php print_r($title); ?></h4>
        <p><?php print_r($details); ?></p>
        <br >
        <div  class="container-fluid mb-0">
          <div class='row'>
            <div class="col-2">
              <div class="tile tile-circle tile-lg bg-warning">
                <span class="fa fa-chrome"></span>
              </div>
              Chrome
            </div>
            <div class="col-2">
              <div class="tile tile-circle tile-lg bg-warning">
                <span class="fa fa-firefox"></span>
              </div>
              Firefox
            </div>
            <div class="col-2">
              <div class="tile tile-circle tile-lg bg-warning">
                <span class="fa fa-edge"></span>
              </div>
              Edge
            </div>
            <div class="col-2">
              <div class="tile tile-circle tile-lg bg-warning">
                <span class="fa fa-opera"></span>
              </div>
              Opera
            </div>
            <div class="col-2">
              <div class="tile tile-circle tile-lg bg-warning">
                <span class="fa fa-safari"></span>
              </div>
              Safari
            </div>
          </div>
        </div>
      </div>
    <?php else : ?>
      <?php print render($page['content']); ?>
    <?php endif; ?>
    
  </body>
</html>