<script>
  //We have a Riot token in our browser, logout this session
  if(typeof localStorage.mx_access_token == "string" && localStorage.mx_access_token.length){
    jQuery.ajax({
        url: "https://" + Drupal.settings.GOFAST_COMM + "/_matrix/client/r0/logout",
        headers: {
          "Authorization": "Bearer " + localStorage.mx_access_token
        },
        type: 'POST',
        dataType: 'json',
        complete: function(){
          //Delete local storage to finalize the clear
          localStorage.clear();
          indexedDB.deleteDatabase('matrix-js-sdk:riot-web-sync');
          indexedDB.deleteDatabase('matrix-js-sdk:crypto');
          indexedDB.deleteDatabase('matrix-react-sdk');
          indexedDB.deleteDatabase('logs');
        },
      });
  }else{
    //Delete local storage to finalize the clear
    localStorage.clear();
    indexedDB.deleteDatabase('matrix-js-sdk:riot-web-sync');
    indexedDB.deleteDatabase('matrix-js-sdk:crypto');
    indexedDB.deleteDatabase('matrix-react-sdk');
    indexedDB.deleteDatabase('logs');
  }
</script>
