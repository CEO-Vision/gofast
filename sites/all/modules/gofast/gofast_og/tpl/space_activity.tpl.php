 <?php
    //make sure the Views js files had been added to the page
           $views_path = drupal_get_path('module', 'views');
           drupal_add_js(
               $views_path . '/js/base.js',
               array(
                   'type' => 'file',
                   'scope' => 'footer',
                   'group' => JS_DEFAULT,
               )
           );
           drupal_add_js(
               $views_path . '/js/ajax_view.js',
               array(
                   'type' => 'file',
                   'scope' => 'footer',
                   'group' => JS_DEFAULT,
               )
           );
            ?>

            <div class="row">
              <div class="col-md-6">
                <div class="panel panel-default" style="height:350px; overflow:auto;">
                  <div class="panel-heading">
                    <h3 class="panel-title"><?php print t("Forums"); ?></h3>
                  </div>
                  <div class="panel-body">
                      <script type='text/javascript'>                      
                         jQuery.ajax({
                                    url: '/views/ajax',
                                    type: 'post',
                                    data: {
                                      view_name: 'gofast_activity_feed',
                                      view_display_id: 'block_4', //your display id
                                      view_args: '<?php echo $nid; ?>', // your views argument(s)
                                    },
                                    dataType: 'json',
                                    success: function (response) {
                                      if (response[2] !== undefined) {
                                            jQuery("#gofast_activity_feed_block_4").html(response[2].data);
                                            // Set views key based on response data. 
                                            Drupal.settings.views = response[0].settings.views;
                                            Drupal.attachBehaviors();

                                      }
                                    }
                                  });
                      </script>
                      <div id="gofast_activity_feed_block_4"></div>                  
                  </div>
                </div>
              </div>
              <div class="col-md-6">
                <div class="panel panel-default" style="height:350px; overflow:auto;">
                  <div class="panel-heading">
                    <h3 class="panel-title"><?php print t("Internal pages"); ?></h3>
                  </div>
                  <div class="panel-body">
                     <script type='text/javascript'>                      
                         jQuery.ajax({
                                    url: '/views/ajax',
                                    type: 'post',
                                    data: {
                                      view_name: 'gofast_group_article',
                                      view_display_id: 'block', //your display id
                                      view_args: '<?php echo $nid; ?>', // your views argument(s)
                                    },
                                    dataType: 'json',
                                    success: function (response) {
                                      if (response[2] !== undefined) {
                                            jQuery("#gofast_group_article_block").html(response[2].data);
                                            // Set views key based on response data. 
                                            Drupal.settings.views = response[0].settings.views;
                                            Drupal.attachBehaviors();

                                      }
                                    }
                                  });
                      </script>
                      <div id="gofast_group_article_block"></div>                 
                  </div>
                </div>
              </div>
            </div>
            
           <div class="row">
              <div class="col-md-6">
                <div class="panel panel-default" style="height:350px; overflow:auto;">
                  <div class="panel-heading">
                    <h3 class="panel-title"><?php print t("Popular contents"); ?></h3>
                  </div>
                  <div class="panel-body">
                        <script type='text/javascript'>                      
                         jQuery.ajax({
                                    url: '/views/ajax',
                                    type: 'post',
                                    data: {
                                      view_name: 'gofast_group_content',
                                      view_display_id: 'block_1', //your display id
                                      view_args: '<?php echo $nid; ?>', // your views argument(s)
                                    },
                                    dataType: 'json',
                                    success: function (response) {
                                      if (response[2] !== undefined) {
                                            jQuery("#gofast_group_content_block_1").html(response[2].data);
                                            // Set views key based on response data. 
                                            Drupal.settings.views = response[0].settings.views;
                                            Drupal.attachBehaviors();

                                      }
                                    }
                                  });
                      </script>
                      <div id="gofast_group_content_block_1"></div>                   
                  </div>
                </div>
              </div>
              <div class="col-md-6">
                <div class="panel panel-default" style="height:350px; overflow:auto;">
                  <div class="panel-heading">
                    <h3 class="panel-title"><?php print t("Space bookmarks"); ?></h3>
                  </div>
                  <div class="panel-body">
                    <script type='text/javascript'>                      
                         jQuery.ajax({
                                    url: '/views/ajax',
                                    type: 'post',
                                    data: {
                                      view_name: 'gofast_group_content',
                                      view_display_id: 'block', //your display id
                                      view_args: '<?php echo $nid; ?>', // your views argument(s)
                                    },
                                    dataType: 'json',
                                    success: function (response) {
                                      if (response[2] !== undefined) {
                                            jQuery("#gofast_group_content_block").html(response[2].data);
                                            // Set views key based on response data. 
                                            Drupal.settings.views = response[0].settings.views;
                                            Drupal.attachBehaviors();

                                      }
                                    }
                                  });
                      </script>
                      <div id="gofast_group_content_block"></div>                  
                  </div>
                </div>
              </div>
            </div>
<!--            <div style="clear:both;margin:10px;"></div>-->
            <div class="row">
              <div class="col-md-6">
                <div class="panel panel-default" style="height:350px; overflow:auto;">
                  <div class="panel-heading">
                    <h3 class="panel-title"><?php print t("Books in this group"); ?></h3>
                  </div>
                  <div class="panel-body">
                    <?php
                        $block = module_invoke('gofast_book', 'block_view', 'gofast_book_group');
                        print $block['content'];
                    ?>
                  </div>
                </div>
              </div>         
            </div>