<!-- Global style, including our fonts -->
<?php global $base_url; ?>
<style>
    @font-face {
      font-family: 'Poppins';
      font-style: normal;
      font-weight: 100;
      src: url("<?= $base_url ?>/sites/all/themes/bootstrap-keen/fonts/poppins/Poppins-Thin.otf") format("opentype");
    }

    @font-face {
      font-family: 'Poppins';
      font-style: normal;
      font-weight: 200;
      src: url("<?= $base_url ?>/sites/all/themes/bootstrap-keen/fonts/poppins/Poppins-ExtraLight.otf") format("opentype");
    }

    @font-face {
      font-family: 'Poppins';
      font-style: normal;
      font-weight: 300;
      src: url("<?= $base_url ?>/sites/all/themes/bootstrap-keen/fonts/poppins/Poppins-Light.otf") format("opentype");
    }

    @font-face {
      font-family: 'Poppins';
      font-style: normal;
      font-weight: 400;
      src: url("<?= $base_url ?>/sites/all/themes/bootstrap-keen/fonts/poppins/Poppins-Regular.otf") format("opentype");
    }

    @font-face {
      font-family: 'Poppins';
      font-style: normal;
      font-weight: 500;
      src: url("<?= $base_url ?>/sites/all/themes/bootstrap-keen/fonts/poppins/Poppins-Medium.otf") format("opentype");
    }

    @font-face {
      font-family: 'Poppins';
      font-style: normal;
      font-weight: 600;
      src: url("<?= $base_url ?>/sites/all/themes/bootstrap-keen/fonts/poppins/Poppins-SemiBold.otf") format("opentype");
    }

    @font-face {
      font-family: 'Poppins';
      font-style: bold;
      font-weight: 700;
      src: url("<?= $base_url ?>/sites/all/themes/bootstrap-keen/fonts/poppins/Poppins-Bold.otf") format("opentype");
    }

    @font-face {
      font-family: 'Poppins';
      font-style: normal;
      font-weight: 800;
      src: url("<?= $base_url ?>/sites/all/themes/bootstrap-keen/fonts/poppins/Poppins-ExtraBold.otf") format("opentype");
    }

    @font-face {
      font-family: 'Poppins';
      font-style: normal;
      font-weight: 900;
      src: url("<?= $base_url ?>/sites/all/themes/bootstrap-keen/fonts/poppins/Poppins-Black.otf") format("opentype");
    }

    h1,h2,h3,p,center {
      font-family: Poppins, Candara, Helvetica, Arial, sans-serif;
      color: #3f4254;
      font-weight:500;
    }

    .bootstrap-button-primary{
      color: #fff;
      background-color: #187de4;
      border-color: #187de4;
      transition: color .15s ease,background-color .15s ease,border-color .15s ease,box-shadow .15s ease;
      box-shadow: none;
      cursor: pointer;
      outline: none !important;
      vertical-align: middle;
      display: inline-block;
      font-weight: 400;
      text-align: center;
      user-select: none;
      border: 1px solid transparent;
      padding: 0.6rem 0.4rem;
      font-size: 0.9rem;
      line-height: 1.5;
      border-radius: 0.42rem;
    }
</style>


<!-- GENERATION : Theme for preview generation (Generation in progress) -->
<?php if($generating){ ?>
  <h2>
    <center>
      <?php echo t("This document preview generation in progress", [], ['context' => 'gofast:gofast_cmis']); ?>
    </center>
  </h2>
  
  <h3>
    <center>
      <?php echo t("This might take a while before the preview is available, please reload this page after a few minutes", [], ['context' => 'gofast:gofast_cmis']); ?>
    </center>
  </h3>
  
  <script>
    //Show our preview element to display generation information
    parent.window.jQuery("#previewEmbedElement").show();
  </script>

<!-- HEADER : Theme for preview header, before file content -->
<?php }else if($header){ ?>
  
  <script src="/sites/all/libraries/svg-pan-zoom/svg-pan-zoom.min.js"></script>
  <style>
    svg {
      width: 100% !important; 
      height:100% !important
    }
  </style>
  
  <progress id="progress" style="position: absolute;"></progress>
  
  <script>
    //Our preview is loading and ready to be shown
    parent.window.jQuery("#previewEmbedElement").show();
  </script>

<!-- FOOTER : Theme for preview footer, after file content -->
<?php } else if($footer){ ?>
  
  <script>
    //SVG fully loaded, trigger controls
    svgPanZoom(document.querySelectorAll("svg")[0], {zoomEnabled: true, controlIconsEnabled: true, minZoom: 0.0000001, maxZoom: 100000}).resize().fit().center();
    document.getElementById("progress").remove();
  </script>
<?php } ?>