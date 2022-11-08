          <?php $kanban_id = gofast_kanban_get_space_kanban($node->nid)[0];  ?>
          <?php $card_to_display = isset($_GET['card_id']) ? '/card/' . $_GET['card_id'] : ''; ?>
          <iframe src="/kanban/<?php echo $kanban_id . $card_to_display; ?>" id="gf_kanban" style="width:100%;height: calc(100vh - 180px);border:none;"></iframe>
