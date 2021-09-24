<div id="unarchive_space_modal_process_container">
  <div class="panel panel-default">
    <div class="panel-body">
      <div id="unarchive_step_1_1">
          <?php echo t("Step 1: Reset normal permissions on all the space's documents (this operation might take a while)", array(), array('context' => 'gofast:og')); ?> 
          <span class="icon fa"></span>
          <div class="loader-deleting"></div>
      </div>
    </div>
  </div>
  
  <div class="panel panel-default">
    <div class="panel-body">
      <div id="unarchive_step_2_1">
          <?php echo t("Step 2: Reset normal permissions on this space", array(), array('context' => 'gofast:og')); ?> 
          <span class="icon fa"></span>
          <div class="loader-deleting gofast_display_none"></div>
      </div>
    </div>
  </div>
</div>

<script>
  var $ = jQuery;
function checkState(){
    //Query the server to retrieve the current state
    $.get(window.location.origin + "/space/<?php echo $space_node->nid; ?>/unarchive/status", function(response){
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
                    stateChecked("1_1");
                    location.href = location.origin + "/node/<?php echo $space_node->nid; ?>";
                }
                return;
            case "2_1":
                stateLoading("2_1");
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
    var icon = $("#unarchive_step_" + state).find(".icon");
    var loader = $("#unarchive_step_" + state).find(".loader-deleting");
    
    icon.addClass("fa-check");
    loader.addClass("gofast_display_none");
}

function stateLoading(state){
    var loader = $("#unarchive_step_" + state).find(".loader-deleting");
    
    loader.removeClass("gofast_display_none");
}

checkState();
modalContentResize();
</script>