function CustomGofastAutocompleteCtrl($scope, $parse, $log, widgetNameFactory, $http) {
  $scope.loading = false;
  
  this.getData = function () {
    $scope.loading = true;
    return $http.get("../../../../../../../../api/" + $scope.properties.type + "/autocomplete?str=" + $scope.properties.value + "&bundles=" + $scope.properties.bundles).then(function(r){
        var items = r.data
        var output = [];
        if($scope.properties.type == "user"){
            for(var k in items){
                var item = items[k];
                var login = item.login;
                var mail = item.mail;
                var displayname = item.displayname;
                var icon = item.icon
                
                output.push( item.icon + " "
                + item.displayname + " ("
                + item.login + " / "
                + item.mail + ")");
            }
        }else if($scope.properties.type == "node"){
            for(var k in items){
                var item = items[k];
                var nid = item.nid;
                var title = item.title;
                var icon = item.icon;
                
                output.push(item.icon + " "
                + item.title + " ( "
                + item.nid + " )");
            }
        }else if($scope.properties.type == "space"){
            
        }
        $scope.loading = false;
        return output;
    });
  };
  
  this.setData = function($item){
      if($scope.properties.type == "user"){
        $scope.properties.currentTitle=$item.substr($item.indexOf("/> ")+3, $item.lastIndexOf(" ("));  
        $item = $item.substr($item.lastIndexOf(" (")+2);
        $item = $item.substr(0, $item.lastIndexOf(" /"));
      }else if($scope.properties.type == "node"){
        $scope.properties.currentTitle=$item.substr($item.indexOf("/> ")+3, $item.lastIndexOf(" ("));  
        $item = $item.substr($item.lastIndexOf(" ( ")+2);
        $item = $item.substr(0, $item.lastIndexOf(" )"));
      }else if($scope.properties.type == "space"){
      }
      $scope.properties.value = $item;
      $scope.isReadOnly = true;
  }
  
  this.clickInput = function(){
      if(!$scope.properties.readOnly && $scope.isReadOnly){
          $scope.isReadOnly = false;
          $scope.properties.value = "";
          $scope.properties.currentTitle="";
      }
  }
  
  $scope.$watch(function(){return $scope.properties.readOnly;}, function(n, o){
      if(o !== n){
          $scope.isReadOnly = n;
      }
  });
  $scope.isReadOnly = $scope.properties.readOnly;
  this.name = widgetNameFactory.getName('customGofastAutocomplete');
}
