<div id="selection-version-container">
  <div id="selection-version-logo">
    <img alt="Logo" src="<?= theme_get_setting('logo') ?? '/sites/all/modules/gofast/img/logo_enterprise.png' ?>">
  </div>
  <div id="selection-version-choice">
    <div id="selection-version-label">
      <h3><?php print t('Collaborative Work Environment'); ?> </h3>
      <h3><?php print t('choose your user interface:') ?></h3>
    </div>
    <div id="selection-version-buttons" class="d-inline-flex">
      <div id="setVersionEssentialButton">
        <button class="btn btn-lg btn-primary large w-50"><?php print t('ESSENTIAL Interface'); ?></button>
        <div class="text-center pt-2">
          <p class="font-weight-bold"><?php print t('Beginner user'); ?></p>
          <p><?php print t('File Explorer-like access to all your shared folders and documents.'); ?></p>
        </div>
      </div>
      <div id="setVersionPlusButton">
        <button class="btn btn-lg btn-primary large w-50"><?php print t('PLUS Interface'); ?></button>
        <div class="text-center pt-2">
          <p class="font-weight-bold"><?php print t('Advanced user'); ?></p>
          <p><?php print t('Take full advantage of all document management and collaborative work tools.'); ?></p>
        </div>
      </div>
    </div>
    <div>
      <b><?= t('If you prefer to stay with the historical version, please select the "Plus" version.');?></b>
    </div>
  </div>
  <div id="selection-version-footer">
    <div class="h-100 m-auto d-flex">
      <!--begin::Aside header-->
      <a href="#" class="w-100 text-center">
        <img src="/sites/all/themes/bootstrap-keen/Logo_GoFAST de CEO-Vision_fr_blanc.png" alt="logo" class="h-100px">
      </a>
      <!--end::Aside header-->
      <!--begin::Aside title-->
      <h3 class="font-weight-bolder text-center font-size-h4 font-size-h1-lg text-white w-100 mt-5">
        TECHNOLOGY MADE SIMPLE
      </h3>
      <!--end::Aside title-->
    </div>
  </div>
</div>

<style>
  #selection-version-container {
    height: 100%;
    width: 100%;
  }

  #selection-version-logo {
    background-color: rgb(58, 121, 180) !important;
    height: 25%;
    width: 100%;
    text-align: center;
    display: flex;
    align-items: center;
    justify-content: center;
  }

  #selection-version-label {
    padding-top: 40px;
    margin-left: auto;
    margin-right: auto;
    width: 50%;
    height: 40%;
  }
  
  #selection-version-buttons {
    margin-bottom: 10px;
  }

  #setVersionEssentialButton {
    width:50%;
  }
  
  #setVersionPlusButton p,
  #setVersionEssentialButton p{
    text-align: center;
    width: 50%;
    margin: auto;
  }

  #setVersionPlusButton {
    width:50%;
  }

  img {
    max-width: 50%;
    max-height: 50%;
    height: auto;
    display: block;
    margin: auto;
  }

  #selection-version-choice {
    height: 40%;
    width: 100%;
    text-align: center;
  }

  #selection-version-footer {
    background-color: rgb(58, 121, 180) !important;
    height: 35%;
    width: 100%;
    text-align: center;
  }
  
  #selection-version-footer > div{
    align-items: center;
    flex-direction: column;
    justify-content: center;
  }

</style>
