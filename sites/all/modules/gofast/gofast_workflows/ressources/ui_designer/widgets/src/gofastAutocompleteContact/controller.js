function CustomGofastAutocompleteCtrl($scope, $parse, $log, widgetNameFactory, $http) {
  $scope.loading = false;
  
  this.getData = function ($field) {
    $scope.loading = true;
    if($field == "firstname"){
        $str = $scope.properties.valueFirstname;
    }else{
        $str = $scope.properties.value;
    }
    return $http.get("../../../../../../../../api/contact/autocomplete?str=" + $str).then(function(r){
        var items = r.data
        var output = [];
            for(var k in items){
                var item = items[k];
                var lastname = item.name;
                var firstname = item.firstname;
                var phone = item.mobile;
                var mail = item.email;
                var entity = item.entity;
                var address = item.address;
                output.push( item.name + " , " + item.firstname + " , " +item.email + " , " + item.mobile + " , " + item.entity);
            }
        $scope.loading = false;
        return output;
    });
  };
  
  this.setData = function($item){
       var array_item = $item.split(' , ');
      $scope.properties.currentTitle=array_item[0];
      $scope.properties.currentTitleFirstname=array_item[1];  
      $scope.properties.currentTitleEmail=array_item[2];
      $scope.properties.currentTitleMobile=array_item[3]; 
      $scope.properties.currentTitleEntity=array_item[4];

      $scope.properties.value = array_item[0];
      $scope.properties.valueFirstname = array_item[1];
      $scope.properties.valueEmail = array_item[2];
      $scope.properties.valueMobile = array_item[3];
      $scope.properties.valueEntity = array_item[4];
  }
  
  this.clickInput = function($element){
      if($element == 'email'){
        $scope.properties.currentTitleEmail = "";
        $scope.properties.currentTitleEmail = "";
      }else if($element == 'firstname'){
        $scope.properties.valueFirstname = "";
        $scope.properties.currentTitleFirstname = "";
      }else if($element == 'lastname'){
        $scope.properties.value = "";
        $scope.properties.currentTitle = "";
      }else if($element == 'mobile'){
        $scope.properties.valueMobile = "";
        $scope.properties.currentTitleMobile="";
      }else if($element == 'entity'){
        $scope.properties.valueEntity = "";
        $scope.properties.currentTitleEntity="";
      }
     
  }
  
  this.name = widgetNameFactory.getName('customGofastAutocomplete');
}
