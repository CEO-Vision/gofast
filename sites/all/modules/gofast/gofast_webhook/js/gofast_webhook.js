(function ($, Gofast) {
  Gofast.gofastWebhookPopulateServiceContainer = function () {
    $.ajax({
      url: '/gofast-webhook/api/get-service-container',
      method: 'GET',
      success: function (data) {
        $('#webhookServicesLoader').remove();
        $('#gofastWebhookServicesTableBody').html(data);
      },
      error: function (error) {
        //console.error('Error fetching data: ', error);
      },
    });
  };
})(jQuery, Gofast);

