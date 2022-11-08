
(function ($, Gofast, Drupal) {         
        $("#explorer-wiki").on('click', function(){         
            if($("#wiki .gofast-spinner-xxl").length == 1){                   
              setTimeout(function(){          
                   $.get(window.origin + "/gofast/book/explorer")
                    .done(function(data){
                        $("#wiki").html(data);
                        Gofast.selectCurrentWikiArticle();
                    });
              }, 500); 
            }
       })
    
    
}(jQuery, Gofast, Drupal));