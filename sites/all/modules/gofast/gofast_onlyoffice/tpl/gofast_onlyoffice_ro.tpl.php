    <script type="text/javascript" src="<?php print DOC_SERV_API_URL ?>"></script>

    <script type="text/javascript">
      //Wait for DocsAPI to be available
      Gofast.process_onlyoffice_editor = function(){
              var docEditor;

              var fileName = "<?php echo $filename ?>";
              var fileType = "<?php echo $extension ?>";
              var documentType = "<?php echo getDocumentType(array_key_exists('extension', pathinfo($filename)) ? $filename : $filename . '.' . $extension) ?>";
              var fileUri = "<?php echo $fileuri ?>";
              var key = "<?php echo $key ?>";
              var author = "<?php echo $author['ldap_user_givenname']['value'] . ' ' . $author['ldap_user_sn']['value']; ?>";
              var created = "<?php echo date('d.m.y', $timestamp) ?>";
              var sharingPermission = "<?php echo $permission; ?>";
              var sharingUser = "<?php echo $user['ldap_user_givenname']['value'] . ' ' . $user['ldap_user_sn']['value']; ?>";
              var editPermission = <?php  var_export($edit_permission) ?>;
              var callbackUrl = "<?php echo $callbackUrl; ?>";
              var userId = "<?php echo $user['name']; ?>";
              var userFirstname = "<?php echo $user['ldap_user_givenname']['value'] ?>";
              var userLastname = "<?php echo $user['ldap_user_sn']['value'] ?>";
              var editorMode = "<?php echo $editor_mode ?>";
              var lang = "<?php print $user['user-language'] ?>";

              //Set a cookie to inform onlyoffice plugins about the current key
              var current_date = new Date();
              current_date.setMonth(current_date.getMonth() + 12);

              var domain_parse = location.origin.split(".");
              var domain_base = domain_parse[domain_parse.length-2] + "." + domain_parse[domain_parse.length-1];

              document.cookie = "gen_id=" + key + ";expires=" + current_date 
                          + ";domain=." + domain_base + ";path=/";

              Gofast.docEditor = new DocsAPI.DocEditor("iframeEditor",
                        {
                          width: "100%",
                          height: "800",
                          type: "desktop",
                          documentType: documentType,
                          document: {
                            title: fileName,
                            url: fileUri,
                            fileType: fileType,
                            info: {
                              author: author,
                              created: created,
                              sharingSettings: [
                                {
                                  permissions: "Read Only",
                                  user: sharingUser,
                                }
                              ]
                            },
                            permissions: {
                              edit: false,
                              print: false,
                              download: false,
                              comment: false,
                            }
                          },
                          editorConfig: {
                            mode: "view",
                            lang: lang,
                            callbackUrl: callbackUrl,
                            user: {
                              id: userId,
                              name: userFirstname + " " + userLastname
                            },
                            embedded: {
                              saveUrl: fileUri,
                              embedUrl: fileUri,
                              shareUrl: fileUri,
                              toolbarDocked: "top"
                            },
                            customization: { // not support to customize logo
                              logUrl : 'https://gofast.ceo-vision.com/sites/default/files/pictures/162/3070-logo-gofast.png.thumbnail-162.png',
                              logUrlEmbedded : 'https://gofast.ceo-vision.com/sites/default/files/pictures/162/3070-logo-gofast.png.thumbnail-162.png',
                              about: false,
                              feedback: false,
                              chat: false,
                              comments: false,
                              hideRightMenu: true,
                              plugins: false,
                            }
                          }
                    });
      }
      
      Gofast.onlyoffice_preview_interval = setInterval(function(){
            if(typeof DocsAPI == "undefined"){
                return;
            }
            Gofast.process_onlyoffice_editor();
            clearInterval(Gofast.onlyoffice_preview_interval);
            
      }, 500);
    </script>
    
    <form id="form1">
      <div id="iframeEditor">
      </div>
    </form>