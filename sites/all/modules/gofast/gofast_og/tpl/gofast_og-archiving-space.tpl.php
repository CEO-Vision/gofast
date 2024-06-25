<div id="archive_space_modal_process_container" class="process_container">
  <div class="panel panel-default">
    <div class="panel-body">
      <div id="archive_step_1_1" class="archive_step_1" data-nid="<?= $nid?>">
          <?php echo '<h3>' . t("Archiving space: @space", array('@space' => is_object($space_node) ? $space_node->title : $space_node['title']),
              array('context' => 'gofast:og')). '</h3>';
          ?>
          <?php echo t("Step 1: Setting read only permissions on all the space's documents (this operation might take a while)", array(), array('context' => 'gofast:og')); ?> 
          <span class="icon step_process_icon fa"></span>
          <div class="loader-deleting"></div>
      </div>
    </div>
  </div>
  
  <div class="panel panel-default">
    <div class="panel-body">
      <div id="archive_step_2_1" class="archive_step_2" data-nid="<?= $nid?>">
          <?php echo t("Step 2: Setting read only permissions on this space", array(), array('context' => 'gofast:og')); ?> 
          <span class="icon step_process_icon fa"></span>
          <div class="loader-deleting gofast_display_none"></div>
      </div>
    </div>
  </div>
</div>
<br/>

<?php if ($is_last): ?>
  <script id="archive_space_script">
    
    var completedContainers = new Set(); // Keep track of completed containers

    async function checkState() {
      const processContainers = document.querySelectorAll('.process_container');

      for (const element of processContainers) {
        if (completedContainers.has(element)) {
          // Skip this container if it's already completed
          continue;
        }

        const step1Element = element.querySelector('.archive_step_1');
        const step2Element = element.querySelector('.archive_step_2');
        const nid = step1Element.dataset.nid;

        try {
          // Query the server to retrieve the current state
          const response = await fetch(`/space/${nid}/archive/status`);
          const data = await response.text();
          
          switch (data) {
            case 'error':
              // The process was rolled back
              window.location.href =  window.location.origin+"/node/<?= $nid ?>";
              break;
            case '':
              // The process is finished
              stateChecked('2_1', step2Element);
              stateChecked('1_1', step1Element);
              <?php if(!$is_bulk):?>
                window.location.href = window.location.origin+"/node/<?= $nid ?>";
              <?php endif;?>
              // Mark this container as completed
              completedContainers.add(element);
              break;
            case '2_1':
              stateLoading('2_1', step2Element);
              stateChecked('1_1', step1Element);
              break;
            case '1_1':
              stateLoading('1_1', step1Element);
              break;
            default:
              console.log('State not found');
              break;
          }
        } catch (error) {
          console.error('Error fetching data:', error);
        }
      }

      // Check if all containers are completed, then stop polling
      if (completedContainers.size === processContainers.length) {
        clearInterval(pollingInterval);
        document.getElementById('archive_space_script').remove();
        <?php if($is_bulk): ?>
           Gofast.toast('<?= t('The spaces have been archived successfully', array(), array('context' => 'gofast:space_archive')); ?>', 'success');
        <?php endif; ?>
      }
    }

    function stateChecked(state, element) {
      const icon = element.querySelector('.step_process_icon');
      const loader = element.querySelector('.loader-deleting');
      icon.classList.add('fa-check');
      loader.classList.add('gofast_display_none');
    }

    function stateLoading(state, element) {
      const loader = element.querySelector('.loader-deleting');
      loader.classList.remove('gofast_display_none');
    }
    
    // Start the initial check after a 2-second delay
    setTimeout(checkState, 3000);

    // Poll for status updates every 2 seconds
    var pollingInterval = setInterval(checkState, 3000);
  </script>
<?php endif; ?>
