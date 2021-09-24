
(function ($, Gofast, Drupal) {
  
  function addWebfontIcon(treeId, treeNode){
    
    var aObj = $("#" + treeNode.tId + "_ico");
    //retreive taxo icone
    style = aObj.css('background-image');
    var cleanup = /\"|\'|\)/g;
    
    if(treeNode.parentTId == null){
      icon = "fa-book";
    }else{
      icon = "fa-newspaper-o";
    }

    if ($("#webfont_icon_"+treeNode.tId).length>0) return;
    var editStr = " <span id='webfont_icon_" +treeNode.tId+ "' class='fa "+icon+"'> </span>";
    aObj.prepend(editStr);
    aObj.css('background', 'transparent');
  };
  
  Drupal.behaviors.gofast_book_block = {
    attach: function (context, settings) {
      context = $(context);
    
      $('#ztree_book:not(.ztree-processed)', context).addClass('ztree-processed').each(function() {
        var data_tree = {};
   
        if (Drupal.settings.gofast_book_tree) {
          data_tree = $.parseJSON(Drupal.settings.gofast_book_tree.data_tree);   
        }

        //var settings = { edit: { drag: { prev: dropPrev, inner: dropInner, next: dropNext }, enable: false, showRemoveBtn: false, showRenameBtn: false}, data: {simpleData: {enable: true, rootPId: 0}}, callback: {beforeExpand: beforeExpand, beforeDrag: beforeDrag }, view: {showIcon: true, fontCss: {color:"#428bca"}} };

        var settings = {  data: {
                            simpleData: {
                              enable: true
                            }
                          }, 
                          view: {
                            showIcon: true,
                            fontCss: {color:"#428bca"},
                            txtSelectedEnable: false,
                            addDiyDom : addWebfontIcon
                          },
                         callback: {				
                          onClick: gofast_book_click
                        }
                     };                                      
        var zTreeObj = $.fn.zTree.init($("#ztree_book"), settings, data_tree);
       
      });
    } 
     
  };
  
  function gofast_book_click(event, treeId, treeNode, clickFlag){
    Gofast.addLoading();
    var GofastSettings = Drupal.settings.gofast;
    var href = "/node/"+treeNode.nId;
    window.location.href = window.location.origin + href;
   }
}(jQuery, Gofast, Drupal));