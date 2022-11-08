function CustomGofastPdfViewer($scope, $sce, $http, $timeout) {
    this.getLink = function(){
        if(Number.isNaN(parseInt($scope.properties.nid))){
            $(".loader-pdf").hide();
            return false;
        }
        $(".loader-pdf").show();
        return $http.get("../../../../../../../../api/node/preview_link?nid=" + $scope.properties.nid + "&zoom=" + $scope.properties.zoom).then(function(r){
             $(".loader-pdf").hide();
             $scope.urlRetrieved = $sce.trustAsResourceUrl(r.data.link);
             return true;
        });
    }
    
    $scope.$watch("properties.nid", function(){
        $scope.ctrl.getLink();
    })
    
    $scope.displayFrame = false;
    $scope.rand = Math.floor(Math.random() * 1000000);
    
    $scope.$watch(function(){
        setTimeout(function(){
                if($scope.displayFrame != jQuery("#pdf-" + $scope.rand).is(":visible")){
                    $scope.displayFrame = jQuery("#pdf-" + $scope.rand).is(":visible");
                    $scope.$apply();
                }
        }, 50);
    });
}
