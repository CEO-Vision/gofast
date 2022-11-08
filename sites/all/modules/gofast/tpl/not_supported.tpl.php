<?php 
  preg_match('/MSIE (.*?);/', $_SERVER['HTTP_USER_AGENT'], $matches);
  if (count($matches) < 2) {
    preg_match('/Trident\/\d{1,2}.\d{1,2}; rv:([0-9]*)/', $_SERVER['HTTP_USER_AGENT'], $matches);
  }
  if (count($matches) > 1 && strpos($_SERVER['HTTP_USER_AGENT'], "ms-office") === FALSE) {
      $ie = true;
  }
?>

<div class="row" style="display: flex;justify-content: center;text-align: center;<?php if($ie){ print 'width: 500px!important;';} ?>">
  <div class="col-md-6">
    <h2><?php print t("Ce navigateur n'est plus supporté", [], ['context' => 'gofast']); ?></h2>
    <p><?php print t("Veuillez utiliser un autre navigateur", [], ['context' => 'gofast']); ?></p>
    <div>
      <img style="width:40px; height:40px;" src="/sites/default/files/chrome.png" alt="">
      <img style="width:40px; height:40px;" src="/sites/default/files/firefox.png" alt="">
      <img style="width:40px; height:40px;" src="/sites/default/files/opera.png" alt="">
      <img style="width:40px; height:40px;" src="/sites/default/files/edge.png" alt="">
      <img style="width:40px; height:40px;" src="/sites/default/files/safari.png" alt="">
    </div>
  </div>
</div>
