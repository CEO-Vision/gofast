function PbDatePickerCtrl(
  $scope,
  $log,
  widgetNameFactory,
  $element,
  $locale,
  $bsDatepicker
) {
  "use strict";

  this.name = widgetNameFactory.getName("pbDatepicker");
  this.firstDayOfWeek =
    ($locale &&
      $locale.DATETIME_FORMATS &&
      $locale.DATETIME_FORMATS.FIRSTDAYOFWEEK) ||
    0;

  $bsDatepicker.defaults.keyboard = false;

  this.setDateToToday = function () {
    var today = new Date();
    if (today.getDay() !== today.getUTCDay()) {
      //we need to add this offset for the displayed date to be correct
      if (today.getTimezoneOffset() > 0) {
        today.setTime(today.getTime() - 1440 * 60 * 1000);
      } else if (today.getTimezoneOffset() < 0) {
        today.setTime(today.getTime() + 1440 * 60 * 1000);
      }
    }
    today.setUTCHours(0);
    today.setUTCMinutes(0);
    today.setUTCSeconds(0);
    today.setUTCMilliseconds(0);
    $scope.properties.value = today;
  };

  this.openDatePicker = function () {
    $element.find("input")[0].focus();
  };

  if (!$scope.properties.isBound("value")) {
    $log.error(
      'the pbDatepicker property named "value" need to be bound to a variable'
    );
  }

  $scope.setAllDatepickersTo = function (date) {
    // Check if the collection exists and has more than one item
    if (
      $scope.properties.collection &&
      $scope.properties.collection.length > 1
    ) {
      // Iterate through the collection starting from the second item
      for (var i = 1; i < $scope.properties.collection.length; i++) {
        // Update the "end_date" value for each item
        $scope.properties.collection[i].end_date = date;
      }
    }
  };
  // Reset value of all datepicker (exept the first two) to make them follow the interval
  $scope.setAllDatepickersWithInterval = function(interval) {
    if($scope.properties.collection && $scope.properties.collection.length > 2){
      // Iterate through the collection starting from the third item
      for(var i = 2; i < $scope.properties.collection.length; i++) {
        // Calculates the new date value from the last item date and the interval
        let previous_timestamp = new Date($scope.properties.collection[i-1].end_date).getTime();
        let new_date = new Date(previous_timestamp + interval);
        $scope.properties.collection[i].end_date = new_date;
      }
    }
  }

  $scope.$watchCollection("properties.collection", function (newVal, oldVal) {
    // To calculates if a new item is added, check if there is a difference between the old and new value
    // This is not triggered when the datepicker value is changed

    // Case sequential: if this datepicker is the newest one, its date is not set and the dates of the first and second items are set
    // then set this datepicker's date after same interval as the first and second date
    if($scope.properties.isSequential){
      if($scope.properties.collection.length > 2
        && $scope.properties.index > 1
        && $scope.properties.collection[0].end_date
        && $scope.properties.collection[1].end_date
        && (newVal[$scope.properties.index] != oldVal[$scope.properties.index])){
          let time_interval = $scope.getSequentialTimeInterval()
          let first_date_timestamp = new Date($scope.properties.collection[0].end_date).getTime();
          // Calutates the new date from the interval and the index to not rely on the previous date if modified
          newVal[$scope.properties.index].end_date = new Date(first_date_timestamp + (time_interval * $scope.properties.index));
        }
    // Case not sequential: if this datepicker is the newest one, its date is not set and the date of the first item is set
    // then set this datepicker's date after the value of the first item
    } else {
      if($scope.properties.index != 0 
        && newVal[$scope.properties.index] != oldVal[$scope.properties.index]
        && $scope.properties.collection[0].end_date) {
          newVal[$scope.properties.index].end_date = $scope.properties.collection[0].end_date;
        }
    }
  })
  // Get timestamp interval of the two first datepicker if they are set
  $scope.getSequentialTimeInterval = function() {
    let interval = 0;
    if($scope.properties.collection[0].end_date && $scope.properties.collection[1].end_date){
      let first_date = new Date($scope.properties.collection[0].end_date);
      let second_date = new Date($scope.properties.collection[1].end_date);
      interval = second_date.getTime() - first_date.getTime();
    }
    return interval;
  }
  // Listen to datepicker changes
  $scope.$watch("properties.value", function (newVal, oldVal) {
    
    // Case not sequential: nothing fancy
    if (!$scope.properties.isSequential && $scope.properties.index == 0) {
      $scope.setAllDatepickersTo(newVal);
    }
    // Case sequential: if there are at least three datepickers and the two first ones are set
    if ($scope.properties.isSequential
        && $scope.properties.collection.length > 2 
        && $scope.properties.collection[0].end_date && $scope.properties.collection[1].end_date
        && ($scope.properties.index == 0 || $scope.properties.index == 1)) {
          let interval = $scope.getSequentialTimeInterval()
          if(interval >= 0){
            $scope.setAllDatepickersWithInterval(interval);
          }
    }
  });
}
