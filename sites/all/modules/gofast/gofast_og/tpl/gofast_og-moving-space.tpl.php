<div id="move_space_modal_process_container">
  <div class="panel panel-default">
    <div class="panel-body">
        <div id="move_step_1"><?php echo t("Step 1: Moving", array(), array('context' => 'gofast:og')); ?> <strong><?php print $space_node->title ?></strong></div>
      
      <ul>
          <li id="move_step_1_1">
              <?php echo t("Move the space folder from", array(), array('context' => 'gofast:og')) . " <strong>" . $old_parent_node->title. "</strong> " . t("to", array(), array('context' => 'gofast:gofast_og')) . " <strong>" . $new_parent_node->title . "</strong>"; ?> 
              <span class="icon fa"></span>
              <div class="loader-deleting gofast_display_none"></div>
          </li>
        <li id="move_step_1_2">
            <?php echo t("Move the space permissions", array(), array('context' => 'gofast:og')); ?> 
            <span class="icon fa"></span>
            <div class="loader-deleting gofast_display_none"></div>
        </li>
      </ul>
    </div>
  </div>
  
  <div class="panel panel-default">
    <div class="panel-body">
      <div id="move_step_2_1">
          <?php echo t("Step 2: Synchronize the documents paths", array(), array('context' => 'gofast:og')); ?> 
          <span class="icon fa"></span>
          <div class="loader-deleting gofast_display_none"></div>
      </div>
    </div>
  </div>
</div>

<script>

function checkState(){
    var $ = jQuery;
    //Query the server to retrieve the current state
    $.get(window.location.origin + "/space/<?php echo $space_node->nid; ?>/move/status", function(response){
	switch(response){ //The missing breaks are intentional
            case "error":
                var error = true;
            case "":
                if(error){
                    //The process was rollbacked
                    location.href = location.origin + "/node/<?php echo $space_node->nid; ?>";
                }else{
                    //The process is finished
                    stateChecked("2_1");
                    stateChecked("1_2");
                    stateChecked("1_1");
                    location.href = location.origin + "/node/<?php echo $space_node->nid; ?>";
                }
                return;
            case "2_1":
                stateLoading("2_1");
                stateChecked("1_2");
                stateChecked("1_1");
                break;
            case "1_2":
                stateLoading("1_2");
                stateChecked("1_1");
                break;
            case "1_1":
                stateLoading("1_1");
                break;
            break;
            default:
                console.log("State not found");
                return;
        }
        
        setTimeout(checkState, 1000);
    });
}

function stateChecked(state){
    var $ = jQuery;
    var icon = $("#move_step_" + state).find(".icon");
    var loader = $("#move_step_" + state).find(".loader-deleting");
    
    icon.addClass("fa-check");
    loader.addClass("gofast_display_none");
}

function stateLoading(state){
    var $ = jQuery;
    var loader = $("#move_step_" + state).find(".loader-deleting");
    
    loader.removeClass("gofast_display_none");
}

checkState();
</script>