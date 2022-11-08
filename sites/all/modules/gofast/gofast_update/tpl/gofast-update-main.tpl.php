<div id="gofastUpdateMainContainer">
  <?php if($done || $updating){?>
    <div class="mt-4 mx-auto card w-75">
      <div class="card-header py-2 bg-light-success">
        <h2><?php print t('Updating', array(), array('context' => 'gofast')); ?>
        </h2>
      </div>
      <div class="card-body">
        <?php print t("We are updating your platform. The platform should be set in maintenance mode in less than a minute. Once the update is done, the platform will be up again !", array(), array('context' => 'gofast')); ?>
        <pre id="log_output_update"></div>
        <div class="form-check" style="margin-left:15px;">
          <label class="form-check-label">
            <input id="scroll_check" class="form-check-input" type="checkbox" value="">
            Stop scroll
          </label>
        </div>
      </div>
    </div>

    <script>
      //URL replacement
      var url_replace = window.location.href.split("/");
      var pop = url_replace.pop();
      if(pop === "perform" || pop === "hperform"){
        history.pushState({}, null, url_replace.join("/"));
      }
      
      //Log
      function loadLogs(){
        jQuery.get(window.location.origin + "/sites/default/files/logs/update_report.gflog?v=" + Math.floor((Math.random() * 999999) + 1), function(data) {
          jQuery( "#log_output_update" ).html(data.split("\n").slice(-300).join("\n"));
          if(!jQuery("#scroll_check").is(":checked")){
            jQuery("#log_output_update").scrollTop(jQuery("#log_output_update")[0].scrollHeight);
          }
        });
        setTimeout(loadLogs, 2000);
      }
      
      loadLogs();
    </script>
  <?php }else if($error){?>
    <div class="mt-4 mx-auto card w-75">
      <div class="card-header py-2 bg-light-danger">
        <h2><?php print t('Error', array(), array('context' => 'gofast')); ?></h2>
      </div>
      <div class="card-body">
        <?php print t("Can't retrieve data. Please make sure this server is allowed to perform extenal requests.", array(), array('context' => 'gofast')); ?>
      </div>
    </div>
  <?php } ?>
    <div class="mt-4 mx-auto card w-75">
      <div class="card-header py-2 bg-light-info">
        <h2><?php print t('Your GoFAST installation', array(), array('context' => 'gofast')); ?></h2>
      </div>
      <div class="card-body">
        <table>
          
          <tr class="gofast-update-tab-item">
            <td c>
              <i class="fa fa-check" aria-hidden="true"></i>
            </td>
            <td class="gofast-update-icon-category">
              Version
            </td>
            <td class="gofast-update-icon-data">
              <?php print $gofast_version['infos']['versionDisplay']; ?>
            </td>
          </tr>
          <?php 
            if(!empty($gofast_version['infos']['releaseDate'])){
          ?>
              <tr class="gofast-update-tab-item">
                <td class="gofast-update-icon-tab">
                  <i class="fa fa-calendar" aria-hidden="true"></i>
                </td>
                <td class="gofast-update-icon-category">
                  Release Date
                </td>
                <td class="gofast-update-icon-data">
                  <?php
                      print $gofast_version['infos']['releaseDate']; 
                  ?>
                </td>
              </tr>
            <?php } ?>  
          
          <?php 
            if(!empty($gofast_version['files']['releaseNote'])){
          ?>
            <tr class="gofast-update-tab-item">
              <td class="gofast-update-icon-tab">
                <i class="fa fa-pencil" aria-hidden="true"></i>
              </td>
              <td class="gofast-update-icon-category">
                Release Note
              </td>
              <td class="gofast-update-icon-data">
                <?php
                    $release_note_path = $repository_server . $repository_path . $gofast_version['files']['root'] . $gofast_version['files']['releaseNote'];
                    print '<a href="' . $release_note_path . '">' . $gofast_version['files']['releaseNote'] . "</a>"; 
                ?>
              </td>
            </tr>     
          <?php } ?>
          
          <?php 
            if(!empty($gofast_hotfix_version)){
          ?>
            <tr class="gofast-update-tab-item">
              <td class="gofast-update-icon-tab">
                <i class="fa fa-code-fork" aria-hidden="true"></i>
              </td>
              <td class="gofast-update-icon-category">
                Hotfix
              </td>
              <td class="gofast-update-icon-data">
                <?php
                    print $gofast_hotfix_version['infos']['versionDisplay'];
                ?>
              </td>
            </tr>     
          <?php } ?>
        
        </table>
      </div>
    </div>
    
    <div class="mt-4 mx-auto card w-75">
      <div class="card-header py-2 bg-light-success">
        <h2><?php print t('Available updates', array(), array('context' => 'gofast')); ?></h2>
      </div>
      <div class="card-body">
        <?php
          if(!empty($available_version)){
        ?>
        <table>
          
          <tr class="gofast-update-tab-item">
            <td c>
              <i class="fa fa-check" aria-hidden="true"></i>
            </td>
            <td class="gofast-update-icon-category">
              Version
            </td>
            <td class="gofast-update-icon-data">
              <?php print $available_version['infos']['versionDisplay']; ?>
            </td>
          </tr>
          
          <tr class="gofast-update-tab-item">
            <td class="gofast-update-icon-tab">
              <i class="fa fa-calendar" aria-hidden="true"></i>
            </td>
            <td class="gofast-update-icon-category">
              Release Date
            </td>
            <td class="gofast-update-icon-data">
              <?php 
                if(!empty($available_version['infos']['releaseDate'])){
                  print $available_version['infos']['releaseDate']; 
                }
              ?>
            </td>
          </tr>
          
          <tr class="gofast-update-tab-item">
            <td class="gofast-update-icon-tab">
              <i class="fa fa-pencil" aria-hidden="true"></i>
            </td>
            <td class="gofast-update-icon-category">
              Release Note
            </td>
            <td class="gofast-update-icon-data">
              <?php 
                if(!empty($available_version['files']['releaseNote'])){
                  $release_note_path = $repository_server . $repository_path . $available_version['files']['root'] . $available_version['files']['releaseNote'];
                  print '<a href="' . $release_note_path . '">' . $available_version['files']['releaseNote'] . "</a>"; 
                }
              ?>
            </td>
          </tr>        
        
        </table>
        <div style='margin-top: 10px;'>
          <span style='color:red;'>
            <?php
              if($updating){
            ?>
              <button type="button" class="btn btn-success" disabled>Update</button>
            <?php
              }else{
            ?>
              <a href="/admin/config/gofast/update/perform">
                <?php if(!empty($available_hotfix_version) && module_exists('gofast_community')){?>
                  <button type="button" class="btn btn-success" disabled>Update</button>
                <?php }else{?>
                  <button type="button" class="btn btn-success">Update</button>
                <?php } ?>
              </a>
            <?php } ?>
            <i class="fa fa-exclamation-circle" aria-hidden="true" style='margin-left: 15px;'></i>
            <?php if(!empty($available_hotfix_version) && module_exists('gofast_community')){ ?>
            <?php print t('Please pass the hotfix before any major release!', array(), array('context' => 'gofast')); ?>
            <?php }else{ ?>
            <?php print t('The platform will be set in maintenance mode and unsaved work will be lost. Please be sure you are ready to update !', array(), array('context' => 'gofast')); ?>
            <?php } ?>
          </span>
        </div>
        <?php
          }
          else{
            echo t('Your installation is up to date !', array(), array('context' => 'gofast'));
          }
        ?>
      </div>
    </div>

  <div class="mt-4 mx-auto card w-75">
      <div class="card-header py-2 bg-light-warning">
        <h2><?php print t('Available hotfix', array(), array('context' => 'gofast')); ?></h2>
      </div>
      <div class="card-body">
        <?php
          if(!empty($available_hotfix_version)){
        ?>
        <table>
          
          <tr class="gofast-update-tab-item">
            <td c>
              <i class="fa fa-check" aria-hidden="true"></i>
            </td>
            <td class="gofast-update-icon-category">
              Version
            </td>
            <td class="gofast-update-icon-data">
              <?php print $available_hotfix_version['infos']['versionDisplay']; ?>
            </td>
          </tr>
          
          <tr class="gofast-update-tab-item">
            <td class="gofast-update-icon-tab">
              <i class="fa fa-calendar" aria-hidden="true"></i>
            </td>
            <td class="gofast-update-icon-category">
              Release Date
            </td>
            <td class="gofast-update-icon-data">
              <?php 
                if(!empty($available_hotfix_version['infos']['releaseDate'])){
                  print $available_hotfix_version['infos']['releaseDate']; 
                }
              ?>
            </td>
          </tr>
          
          <tr class="gofast-update-tab-item">
            <td class="gofast-update-icon-tab">
              <i class="fa fa-pencil" aria-hidden="true"></i>
            </td>
            <td class="gofast-update-icon-category">
              Description
            </td>
            <td class="gofast-update-icon-data">
              <?php 
                if(!empty($available_hotfix_version['infos']['description'])){
                  print $available_hotfix_version['infos']['description']; 
                }
              ?>
            </td>
          </tr>        
        
        </table>
        <div style='margin-top: 10px;'>
          <span style='color:red;'>
            <?php
              if($updating){
            ?>
              <button type="button" class="btn btn-success" disabled>Update</button>
            <?php
              }else{
            ?>
              <a href="/admin/config/gofast/update/hperform">
                <button type="button" class="btn btn-success">Update</button>
              </a>
            <?php } ?>
            <i class="fa fa-exclamation-circle" aria-hidden="true" style='margin-left: 15px;'></i>
            <?php print t('The platform will be set in maintenance mode and unsaved work will be lost. Please be sure you are ready to update !', array(), array('context' => 'gofast')); ?>
          </span>
        </div>
        <?php
          }
          else{
            echo t('Your installation is up to date !', array(), array('context' => 'gofast'));
          }
        ?>
      </div>
    </div>
  </div>
</div>