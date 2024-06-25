!function(){
	var app = angular.module('bonitasoft.ui');

    app.filter('safeHtml', ['$sce', function ($sce) { 
        return function (text) {
            return $sce.trustAsHtml(text);
        };    
    }])
}();