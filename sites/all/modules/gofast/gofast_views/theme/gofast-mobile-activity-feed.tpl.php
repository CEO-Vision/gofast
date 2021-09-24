<div class="container">
  <div class="row">
<!--    <div class="gofast_animation_width gofast_mobile_field_action_activity_feed">
      <a href="#" class="btn btn-warning">Download</a> <br />
      <a href="#" class="btn btn-warning">New comment</a> <br />
      <a href="#" class="btn btn-warning">Upload new version</a> <br />
      <a href="#" class="btn btn-warning">Delete</a> <br />
    </div>-->
    <div class="col-xs-12 col-sm-12 gofast_animation_width">
      <div class="clearfix">
        <div class="pull-left">
          <span class="last_node_modifier"><?php print $user_picture ?></span>
        </div>
        <div class="row col-xs-offset-2 col-sm-offset-1" >
          <div class="title_location row col-xs-12 col-sm-12" >
            <div class="col-xs-9  col-sm-10" style="white-space: nowrap; overflow:hidden; text-overflow: ellipsis;">
              <span class="node_format" style="margin-right: 5px; margin-left: 2px;" ><?php print $icon_format ?></span>
              <a class="gofast_activity_feed_title" href="/node/<?php print $node->nid ?>" title="" ><?php print $trimmed_title ?></a>
            </div>
            <div class="col-xs-3 col-sm-2">
              <?php if(strlen($state) > 0 ): ?>
                <span style="font-size: 10px; background-color:#337ab7; border-radius:5px; white-space:nowrap; color:#fff; padding:2px; float:right; margin-right: -15px;" ><?php print $state ?></span>
              <?php endif; ?>
            </div>
          </div>
          <div class="row col-xs-12 col-sm-12">
            <div class="col-xs-12 col-sm-12" >
              <span style="font-size: 12px; padding:2px;"><?php print $last_updated ?></span>
              <!-- <span style="font-size: 12px; p:0px 5px;"><?php //print $spaces ?></span> -->
            </div>
          </div>
        </div>
      </div>
      <div>  
        <?php //print $download_action ?>
      </div>
    </div>
  </div>
</div>

