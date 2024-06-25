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
              
              output.push( item.icon + " "
              + item.displayname + " ("
              + item.login + " / "
              + item.mail + ")");
          }
        }else if($scope.properties.type == "node" || $scope.properties.type == "space"){
            for(var k in items){
                var item = items[k];
                
                output.push(item.icon + " "
                + item.title + " ( "
                + item.nid + " )");
            }
        }
        $scope.loading = false;
        return output;
    });
  };
  
  this.setData = function($item){
      // To be able to parse the content easily, create a temporary container and set its innerHTML
      const container = document.createElement('div');
      container.innerHTML = $item;
      let targetSpan = null;
      if($scope.properties.type == "user"){
        if (targetSpan = container.querySelector('span[data-type="userlist"]')) {
            // Userlist case
            let userlistId = "ul_" + targetSpan.textContent;
            // Value of the input is the name of the Bonita group matching the userlist
            $item = userlistId;
            // And displayed content of the input is userlist name and members
            let titleSpan = container.querySelector('span[data-type="userlist-title"]').textContent;
            $scope.properties.currentTitle = titleSpan;
        } else {
            // User case
            $scope.properties.currentTitle=$item.substr($item.indexOf("/> ")+3, $item.lastIndexOf(" ("));
            $item = $item.substr($item.lastIndexOf(" (")+2);
            $item = $item.substr(0, $item.lastIndexOf(" /"));
        }
        container.remove();
      }else if($scope.properties.type == "node" || $scope.properties.type == "space"){
        targetSpan = container.querySelector('span[data-type="node"]');
        let nodeId = targetSpan.textContent;
        $item = nodeId;
        let titleSpan = container.querySelector('span[data-type="node-title"]').textContent;
        $scope.properties.currentTitle = titleSpan;
      }
      $scope.properties.value = $item;
      $scope.isReadOnly = true;
  }
  
  this.clickInput = function(){
    if(!$scope.properties.readOnly){
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