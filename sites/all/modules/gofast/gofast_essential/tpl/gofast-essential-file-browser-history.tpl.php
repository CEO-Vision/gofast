<div id="essentialFileBrowserHistory" class="d-flex mt-3">
  <div id="backHistory" role="button" class="d-flex 
         justify-content-center btn-icon btn-light btn-sm mr-1 align-self-center ml-2">
    <i class="fas fa-arrow-left align-self-center"></i>
  </div>
  <div id="nextHistory" role="button" class="d-flex 
         justify-content-center btn-icon btn-light btn-sm mr-1 align-self-center">
    <i class="fas fa-arrow-right align-self-center"></i>
  </div>
  <div id="parentHistory" role="button" class="d-flex 
         justify-content-center btn-icon btn-light btn-sm mr-2 align-self-center">
    <i class="fas fa-arrow-up align-self-center"></i>
  </div>
  <?php $selectedPath = substr($_GET['path'], strpos($_GET['path'],
    "/_")); ?>
  <select name="fileBrowserHistory" id="fileBrowserSelect">
    <option value="" data-path="<?= $selectedPath ?>" style="width: 
         100%;"><?= $selectedPath ?></option>
  </select>
  <div id="essential-actions" class="ml-2">
    <?php print $hasEssentialSpaceActions; ?>
  </div>
</div>