
<div id="conference-links" class="btn-group" role="group" style="margin-bottom: 20px;">
  <a target="_blank" href="<?php print $conference_url_external ?>" id="conference-pc-link-start" type="button" class="btn btn-success"><?php print t('Go to the conference') ?></a>
</div>

<?php if(isset ($conference_content) && $conference_content !== ""){ ?>
  <div class="panel panel-info">
    <div class="panel-heading">
      <h3 class="panel-title"><?php print t('Informations', array(), array('context' => 'gofast:gofast_conference')) ?></h3>
    </div>
    <div class="panel-body">
      <?php print $conference_content ?>
    </div>
  </div>
<?php } ?>

<?php if(isset ($conference_place) && $conference_place !== ""){ ?>
  <div class="panel panel-default">
    <div class="panel-heading">
      <h3 class="panel-title"><?php print t('Place', array(), array('context' => 'gofast:gofast_conference')) ?></h3>
    </div>
    <div class="panel-body">
      <?php print $conference_place ?>
    </div>
  </div>
<?php } ?>

<div class="panel panel-info">
  <div class="panel-heading">
    <h3 class="panel-title"><?php print t('Participants') ?></h3>
  </div>
  <div class="panel-body">
    <div class="container">
      <div class="row">
        <div class="col-xs-12 col-md-6">
          <strong><?php print t('User participants') ?></strong>
          <br />
          <?php print $gofast_participants; ?>
          <div style='clear:both;'></div>
        </div>
        <div class="col-xs-12 col-md-6">
          <strong><?php print t('Non user participants') ?></strong>
          <br />
          <div>
            <ul class="list-group">
              <?php print $other_participants; ?>
            </ul>
          </div>
           <div style='clear:both;'></div>
        </div>
      </div>

      <div class="row">
        <div class="col-xs-12 col-md-6" style="padding-bottom:20px;">
          <strong><?php print t('Meeting Owner'); ?></strong>
          <br />
          <?php print $conference_owner; ?>
          <div style='clear:both;'></div>
        </div>
        <div class="col-xs-12 col-md-6">
          <strong><?php print t('Meeting Date'); ?></strong>
          <br />
          <?php print $conference_datetime; ?><br /><?php print $conference_end_datetime; ?>
          <div style='clear:both;'></div>
        </div>  
      </div>

    </div>
  </div>
</div>

<?php if(isset ($conference_documents) && $conference_documents !== ""){ ?>
  <div class="panel panel-info">
    <div class="panel-heading">
      <h3 class="panel-title"><?php print t('Documents') ?></h3>
    </div>
    <div class="panel-body">
      <?php $even = 0; ?>
      
      <?php foreach($conference_documents as $document): ?>
        <?php if($even == 0): ?>
          <div class="container" style="padding-left: 0px;padding-right: 0px;">
        <?php endif; ?>
      
      <?php 
        $value = $document['value'];
        $valueSplit = explode('/', $value);
        $node = node_load($valueSplit[0]);
        $date = format_date($valueSplit[1], 'long', '', date_default_timezone_get());

        $node_icon = theme("node_title", array("link" => TRUE, "node" => $node));
      ?>
      <div class="row col-xs-12 col-md-6">
        <div class="col-xs-6" style=";white-space: nowrap;text-overflow: ellipsis;overflow: hidden;word-break: break-all;"><?php print $node_icon ?></div>
        <div class="col-xs-6"><?php print $date; ?></div>
      </div>
      <?php if($even == 0): ?>
        <?php $even = 1 ?>
      <?php else: ?>
        </div>
        <?php $even = 0 ?>
      <?php endif; ?>    
          
     <?php endforeach; ?>
    </div>
  </div>
<?php } ?>
