<!-- Table to Display API Services -->
<table id="gofastWebhookServicesTable" class="table table-bordered">
  <thead>
  <tr>
    <th><?= t('Service Name',[],['context' => 'gofast:gofast_webhook']); ?></th>
    <th><?= t('API Endpoint',[],['context' => 'gofast:gofast_webhook']); ?></th>
    <th><?= t('Events',      [],['context' => 'gofast:gofast_webhook']); ?></th>
    <th><?= t('Status',      [],['context' => 'gofast:gofast_webhook']); ?></th>
    <th><?= t('Actions',     [],['context' => 'gofast:gofast_webhook']); ?></th>
  </tr>
  </thead>
  <tbody id="gofastWebhookServicesTableBody">
    <div id="webhookServicesLoader" class="spinner gofast-spinner-xxl"></div>
    <!-- Table rows will be populated by Gofast.gofastWebhookPopulateServiceContainer() -->
  </tbody>
</table>

<script>
  jQuery(document).ready(function () {
    Gofast.gofastWebhookPopulateServiceContainer();
  });
</script>
