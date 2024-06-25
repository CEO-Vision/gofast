function CustomGofastPdfViewer($scope, $sce, $http) {
    this.getLink = function(){
        if(Number.isNaN(parseInt($scope.properties.nid))){
            $(".loader-pdf").hide();
            return false;
        }
        $(".loader-pdf").show();
        let link = "../../../../../../../../api/node/preview_link?nid=" + $scope.properties.nid;
        if ($scope.properties.caseId > 0) {
            link += "&caseId=" + $scope.properties.caseId;
        }
        return $http.get(link).then(function(r){
             $(".loader-pdf").hide();
             $scope.urlRetrieved = $sce.trustAsResourceUrl(r.data.link);
             return true;
        });
    }
    
    $scope.$watch("properties.nid", function(){
        $scope.ctrl.getLink();
    })
}