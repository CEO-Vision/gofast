function CustomGofastTree($scope, $parse, widgetNameFactory, $log, $http) {
    var rand_id = Math.floor(Math.random() * Math.floor(10000));
    $scope.tree_rand_id = "tree"+rand_id;

    this.addWebfontIcon = function(treeId, treeNode){
        var aObj = $("#" + treeNode.tId + "_ico");
        //retreive taxo icone
        style = aObj.css('background-image');
        var cleanup = /\"|\'|\)/g;
        icon = style.split('/').pop().replace('%20', ' ').replace(cleanup, '');

        if ($("#webfont_icon_"+treeNode.tId).length>0) return;
        var editStr = " <span id='webfont_icon_" +treeNode.tId+ "' class='fa "+icon+"'> </span>";
        aObj.prepend(editStr);
        aObj.css('background', 'transparent');
    }
    
    this.selectClicked = function(e, tid, tnode){
        $scope.zTree.checkNode(tnode, !tnode.checked, false, false);
		$scope.properties.selectedData = JSON.stringify($scope.zTree.getCheckedNodes().map(node => node.ename));
        $scope.$apply();
    }
	
	this.selectCheck = function(tid, tnode){
		$scope.zTree.checkNode(tnode, !tnode.checked, false, false);
		$scope.properties.selectedData = JSON.stringify($scope.zTree.getCheckedNodes().map(node => node.ename));
        $scope.$apply();
		return false;
    }
    
    this.decodeTreeData = function(tid, pnode, r){
        return JSON.parse(r.tree);
    }
	
	this.otherParam = function(tid, pnode, r){
        if(pnode == null && $scope.properties.origin !== null){
			return {ename: $scope.properties.origin};
		}
		return [];
    }
    
    this.beforeAsync = function(){
        $(".loader-tree").show();
    }
    
    this.onAsyncSuccess = function(){
        $(".loader-tree").hide();
    }
    
    this.onAsyncSuccess = function(){
        $(".loader-tree").hide();
    }
        
    var callbacks = {
        onClick: $scope.ctrl.selectClicked,
		beforeCheck: $scope.ctrl.selectCheck,
        beforeAsync: $scope.ctrl.beforeAsync,
        onAsyncSuccess: $scope.ctrl.onAsyncSuccess,
        onAsyncError: $scope.ctrl.onAsyncError,
    }
    
    $scope.setting = {
      check: {
          enable: true,
          chkStyle: $scope.properties.chkStyle
      },
      view: {
        showLine: true,
        selectedMulti: true,
        addDiyDom: $scope.ctrl.addWebfontIcon
      },
      data: {
        keep: {
            parent: true
        }
      },
      async: {
          enable: true,
          url: "../../../../../../../../api/locations/tree",
          autoParam: ["ename"],
		  otherParam: $scope.ctrl.otherParam,
          contentType: "application/json",
          dataFilter: $scope.ctrl.decodeTreeData,
          type: 'POST'
      },
      callback: callbacks
    };
     
        
 $scope.$watch(
    function () { return jQuery("#"+$scope.tree_rand_id).length > 0 ;},
    function (newValue, oldValue) {
        if(newValue === true){
            $scope.t = jQuery("#"+$scope.tree_rand_id);
            $scope.t = jQuery.fn.zTree.init($scope.t, $scope.setting);
            $scope.zTree = jQuery.fn.zTree.getZTreeObj($scope.tree_rand_id);
        }
    }
 )  ;      
   
}
