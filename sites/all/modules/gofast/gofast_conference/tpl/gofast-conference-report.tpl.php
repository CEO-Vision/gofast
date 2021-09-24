<div id="report_result">
  <div class="panel panel-default">
    <div class="panel-heading" role="tab" id="heading_main_devices">
      <h4 class="panel-title">
        <a role="button" data-toggle="collapse" data-target="#main_devices" aria-expanded="true" aria-controls="main_devices">
          <?php print t('Main devices', array(), array('context' => 'gofast:gofast_conference')) ?>
        </a>

      </h4>
    </div>
    <div id="main_devices" class="panel-collapse fade collapse" role="tabpanel" aria-labelledby="heading_main_devices">
      <div class="panel-body container-fluid">
        <div class="row" id="camera">
          <div class="col-md-10">
            <div><span class="glyphicon glyphicon-camera"></span> <?php print t('Camera', array(), array('context' => 'gofast:gofast_conference')) ?></div>
          </div>
          <div class="col-md-2">
            <span class="result_icon"></span>
          </div>
        </div>

        <div class="row" id="microphone">
          <div class="col-md-10">
            <div><span class="glyphicon glyphicon-bullhorn"></span> <?php print t('Microphone', array(), array('context' => 'gofast:gofast_conference')) ?></div>
          </div>
          <div class="col-md-2">
            <span class="result_icon"></span>
          </div>
        </div>

        <div class="row" id="audio">
          <div class="col-md-10">
            <div><span class="glyphicon glyphicon-headphones"></span> <?php print t('Loudspeakers', array(), array('context' => 'gofast:gofast_conference')) ?></div>
          </div>
          <div class="col-md-2">
            <span class="result_icon"></span>
          </div>
        </div>
      </div>
    </div>
  </div>

<!--  <fieldset class="form-group collapsible panel panel-default form-wrapper collapse-processed" id="edit-group-profile-data">
    <legend class="panel-heading">
      <a href="#" class="panel-title fieldset-legend" data-toggle="collapse" data-target="#edit-group-profile-data > .collapse" aria-expanded="true"><span class="fieldset-legend-prefix element-invisible">Masquer</span>Profile data</a>
    </legend>
    <div class="panel-collapse fade collapse in" aria-expanded="true">
      <div class="panel-body">
        <div class="field-type-list-text field-name-ldap-user-ou field-widget-options-select form-wrapper form-group" id="edit-ldap-user-ou--2"><div class="form-item form-item-ldap-user-ou-und form-type-select form-group"> <label class="control-label" for="edit-ldap-user-ou-und--2">Main organisation </label>

          </div>
          <span class="summary"></span>
  </fieldset>-->

          <div class="panel panel-default">
            <div class="panel-heading" role="tab" id="heading_protocols">
              <h4 class="panel-title">
                <a role="button" data-toggle="collapse" data-target="#protocols" aria-expanded="true" aria-controls="protocols">
                  <?php print t('Protocols', array(), array('context' => 'gofast:gofast_conference')) ?>
                </a>
              </h4>
            </div>
            <div id="protocols" class="panel-collapse fade collapse" role="tabpanel" aria-labelledby="heading_protocols">
              <div class="panel-body container-fluid">
                <div class="row" id="webrtc">
                  <div class="col-md-10">
                    <?php print t('WebRTC', array(), array('context' => 'gofast:gofast_conference')) ?>
                  </div>
                  <div class="col-md-2">
                    <span class="result_icon"></span>
                  </div>
                </div>

                <div class="row" id="websocket">
                  <div class="col-md-10">
                    <?php print t('WebSocket', array(), array('context' => 'gofast:gofast_conference')) ?>
                  </div>
                  <div class="col-md-2">
                    <span class="result_icon"></span>
                  </div>
                </div>
              </div>
            </div>
          </div>


          <div class="panel panel-default">
            <div class="panel-heading" role="tab" id="heading_others">
              <h4 class="panel-title">
                <a role="button" data-toggle="collapse" data-target="#others" aria-expanded="true" aria-controls="others">
                  <?php print t('Others', array(), array('context' => 'gofast:gofast_conference')) ?>
                </a>
              </h4>
            </div>
            <div id="others" class="panel-collapse fade collapse" role="tabpanel" aria-labelledby="heading_others">
              <div class="panel-body container-fluid">

              </div>
            </div>
          </div>
        </div>

