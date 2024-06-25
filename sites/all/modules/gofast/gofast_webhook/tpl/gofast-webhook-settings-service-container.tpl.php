<?php foreach ($services as $service): ?>
  <tr style="<?= $service->service_status === "DEFAULT" ? 'background: #80808012;':''?>">
    <td><?php echo $service->service_name; ?></td>
    <td style="width:45%;">
      <?php if ($service->is_secure): ?>
        <i class="text-success fas fa-lock"></i>
      <?php else: ?>
        <i class="text-danger fas fa-unlock"></i>
      <?php endif ?>
      <span style="padding-left:0.5rem;">
        <?php echo $service->api_endpoint; ?>
      </span>
    </td>
    <td><?php echo implode(', ', $service->events); ?></td>
    <td id="gofastWebhookServicesTableStatusTD">
      <?php if ($service->service_status === t("ACTIVE", [], ['context'=>'gofast_webhook'])): ?>
        <span class="badge badge-success"><?php echo $service->service_status; ?></span>
      <?php else: ?>
        <span class="badge <?= $service->service_status === t("INACTIVE", [], ['context'=>'gofast_webhook']) ? 'badge-danger' : 'badge-warning'?>"><?php echo $service->service_status; ?></span>
      <?php endif; ?>
    </td>
    <td id="gofastWebhookServicesTableActionsTD">
      <!-- Action Buttons with Bootstrap Icons -->
      <a class="ctools-use-modal" href="<?= '/'.GOFAST_WEBHOOK_ACTIONS_BASE_URL.'/view-service/'.$service->service_id ?>">
        <i class="fas fa-eye" style="font-size: 15px"></i> <!-- View Icon -->
      </a>
      <?php if ($service->service_status !== "DEFAULT") :?>
      <a class="<?= $service->service_status === t("ACTIVE", [], ['context'=>'gofast_webhook']) ? 'ctools-use-modal': '' ?>" 
          href="<?= '/'.GOFAST_WEBHOOK_ACTIONS_BASE_URL.'/edit-service/'.$service->service_id ?>">
        <i class="fa fa-pencil" style="font-size: 15px"></i> <!-- Edit Icon -->
      </a>
      <a class="ctools-use-modal" href="<?= '/'.GOFAST_WEBHOOK_ACTIONS_BASE_URL.'/delete-service/'.$service->service_id ?>">
        <i class="fa fas fa-trash" style="font-size: 15px"></i> <!-- Delete Icon -->
      </a>
      <?php endif; ?>
    </td>
  </tr>
<?php endforeach; ?>
  
<script>
  (function ($, Gofast, Drupal) {
    Drupal.behaviors.ZZCToolsModal.attach();
  })(jQuery, Gofast, Drupal)
</script>

