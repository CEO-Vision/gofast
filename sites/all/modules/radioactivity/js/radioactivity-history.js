(function ($, Gofast) {

  Gofast.radioactivityGenerateGraph = function () {
    if ($.fn.sparkline) {
      $('.radioactivity-history').each(function (match) {
        var dataset = $.parseJSON($(this).text());
        if (dataset) {
          $(this).sparkline(dataset.values, {
            type: 'bar',
            height: '150%',
            width: '150%',
            chartRangeMin: dataset.cutoff,
            tooltipFormat: dataset.tooltipFormat,
            tooltipValueLookups: {
              tooltips: dataset.tooltips
            }
          });
        }
      });
    }
  };

})(jQuery, Gofast);
