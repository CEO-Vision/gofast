(function ($, Gofast, Drupal) {
  /*
   * Functions used to implement ITHit Ajax Library in the mobile module
   */

  Gofast.ITHitMobile = {
    /*
     * Contains the current path
     */
    currentPath: "/alfresco/webdav/Sites",
    /*
     * Tells if the queue is refreshing in the Mobile browser
     */
    queueProcessing: false,
    /*
     * Contains a timeout for the search processing (prevent overload)
     */
    searchProcess: null,
    /*
     * It's mobile version
     */
    mobileVersion: false,
    /*
     * When switching in full mode, set this to true if the browser is hidden
     */
    notShow: false,
    /*
     * Global var to recover unfloadpath value
     */
     reservedPath : null,
    /*
     * @param {type} unfloadPath
     * @ {unresolved}
     */
    memorizedPath : null,
    
    getPathIfUnfload : function (unfloadPath){
      reservedPath = encodeURI(decodeURIComponent(unfloadPath));
    },

    selectedTitle : "",
    
    gofast_book_refresh_file_browser : function() {
      //Ajax query possible changes in the explorer for forums and books views
      setTimeout(function(){
        if($("#explorer-wiki").hasClass("active") && $("#explorer-toggle").hasClass("open")){ 
            $.get(window.origin + "/gofast/book/explorer")
            .done(function(data){
                $("#wiki").html(data);
                Gofast.selectCurrentWikiArticle();
            });
            }
        }, 5000);
    },

    gofast_forum_refresh_file_browser : function() {
      //Ajax query possible changes in the explorer for forums and books views
      setTimeout(function(){
          const urlParam = window.location.pathname.split('/')[2] || "-1";
         if($("#expl-forum").hasClass("active") && $("#explorer-toggle").hasClass("open")){
            $.get(window.origin + "/gofast/forum/explorer/" + urlParam)
            .done(function(data){
                $("#expl-forum").html(data);
            });
          }else{            
              Gofast.lastUrlForumTab =  urlParam;
          }
        }, 5000);
    },
    
    /*
     * Navigate to a path
     * If no params are provided or if the path is not accessible, will back to
     * Sites folder
     */
    navigate: function (path) {
          if(( !$("#explorer-file-browser").hasClass("active") || !$("#explorer-toggle").hasClass("open") ) && !$("#gofastMobileHomeContentPanel").length){
               Gofast.ITHitMobile.memorizedPath = path;
               return;
          }
      //Make sure the path is well encoded
      path = encodeURI(decodeURIComponent(path));
      Gofast.ITHitMobile.gofast_forum_refresh_file_browser();

      if(path.indexOf('/alfresco/webdav') !== 0){
        path = "/alfresco/webdav" + path;
      }
      var fullPath = path;

      if(Gofast.ITHitMobile.mobileVersion == true){
        Gofast.ITHit.updatePathParam(fullPath);
      }

      if (typeof ITHit === "undefined" || typeof Gofast.ITHit === "undefined" || Gofast.ITHit.ready === false) { //Not ready to navigate
        //Try later
        setTimeout(Gofast.ITHitMobile.navigate, 1000, path);
      } else { //Ready to navigate
          //A tab refresh triggers refresh for all, so all will have the laoding icon
        $('#file_browser_mobile_tooolbar_refresh').html("<div class='loader-mobile-filebrowser'></div>");
        $('#file_browser_books_mobile_tooolbar_refresh').html("<div class='loader-mobile-filebrowser'></div>");
        $('#file_browser_forums_mobile_tooolbar_refresh').html("<div class='loader-mobile-filebrowser'></div>");
        //Start the graphic processing of the queue at the 1st navigation
        if(!Gofast.ITHitMobile.queueProcessing){
          Gofast.ITHitMobile.queueProcessing = true;
          Gofast.ITHitMobile.refreshQueue();
        }

        Gofast.ITHit.Session.OpenFolderAsync(path, null,
                function (asyncResult) {

                  if (!asyncResult.IsSuccess) {
                    //Gofast.toast(Drupal.t("Unable to access to", {}, {context: 'gofast:ajax_file_browser'}) + " " + path, "warning");

                    //Remove slash at the end if needed
                    if(path.substr(-1, 1) === "/"){
                      path = path.substring(0, path.length - 1);
                    }

                    //Try to get the parent folder
                    path = path.split('/');
                    path.pop();

                    //Prevent infinite loop and go
                    if(path.length !== 2){
                      path = path.join('/') + "/";
                      Gofast.ITHitMobile.navigate(path);
                    }else{
                      $('#file_browser_mobile_container').replaceWith('<div style="text-align: center;font-size: 25px;"><i style="color: #dc3545;" class="fa fa-exclamation" aria-hidden="true"></i> ' + Drupal.t("Sorry, we are not able to load the file browser", {}, {context:'gofast:ajax_file_browser'}) + "</div>");
                    }
                    $('#file_browser_mobile_tooolbar_refresh').html('<i class="fa fa-refresh" aria-hidden="true"></i>');
                    $('#file_browser_books_mobile_tooolbar_refresh').html('<i class="fa fa-refresh" aria-hidden="true"></i>');
                    $('#file_browser_forums_mobile_tooolbar_refresh').html('<i class="fa fa-refresh" aria-hidden="true"></i>');
                    return;
                  }
                  var folder = asyncResult.Result;
                  folder.GetChildrenAsync(false, null,
                      function (asyncResult) {

                        if (!asyncResult.IsSuccess) {
                          Gofast.toast(Drupal.t("Unable to get elements of", {}, {context: 'gofast:ajax_file_browser'}) + " " + path, "warning");

                          //Try to get the parent folder
                          path = path.split('/');
                          path.pop();
                          path.pop();

                          //Prevent infinite loop and go
                          if(path.length !== 0){
                            path = path.join('/') + "/";
                            Gofast.ITHitMobile.navigate(path);
                          }
                            $('#file_browser_mobile_tooolbar_refresh').html('<i class="fa fa-refresh" aria-hidden="true"></i>');
                            $('#file_browser_books_mobile_tooolbar_refresh').html('<i class="fa fa-refresh" aria-hidden="true"></i>');
                            $('#file_browser_forums_mobile_tooolbar_refresh').html('<i class="fa fa-refresh" aria-hidden="true"></i>');
                          return;
                        }

                        var items = asyncResult.Result;
                        Gofast.ITHitMobile._processItems(items, fullPath, Gofast.ITHitMobile.mobileVersion);

                        fullPath = decodeURIComponent(fullPath);
                        //Remove slash at the end if needed
                        if(fullPath.substr(-1, 1) === "/"){
                          fullPath = fullPath.substring(0, fullPath.length - 1);
                        }

                        Gofast.ITHitMobile.currentPath = fullPath;
                        Gofast.ITHit.UploaderMobile.SetUploadUrl(location.origin + fullPath);

                        //Update breadcrumb
                        Gofast.ITHitMobile.updateBreadcrumb(fullPath);

                        if(Gofast.ITHitMobile.selectedTitle !== ""){
                          $('#file_browser_mobile_files .file_browser_mobile_files_element').each(function(){
                            if($(this).find('.item-name').attr('title') == Gofast.ITHitMobile.selectedTitle){
                              $(this).addClass('selected');
                            }
                          });
                          Gofast.ITHitMobile.selectedTitle = "";
                        }
                        $('#file_browser_mobile_tooolbar_refresh').html('<i class="fa fa-refresh" aria-hidden="true"></i>');
                        $('#file_browser_books_mobile_tooolbar_refresh').html('<i class="fa fa-refresh" aria-hidden="true"></i>');
                        $('#file_browser_forums_mobile_tooolbar_refresh').html('<i class="fa fa-refresh" aria-hidden="true"></i>');
                      }
                  );
                }
        );
      }
    },
    /*
     * Reload the current path
     */
    reload: function(){
      Gofast.ITHitMobile.navigate(Gofast.ITHitMobile.currentPath);
    },
    /*
     * Attach events when ITHit upload queue is updated
     */
    attachUploadEvents: function(){
     Gofast.ITHit.UploaderMobile.Queue.AddListener('OnQueueChanged', '_UploadQueueChanged', this);

      //Callback that happens when a drag and drop occur to filter the uploaded content
      Gofast.ITHit.UploaderMobile.Queue.OnUploadItemsCreatedCallback = function(oUploadItemsCreated) {
	    items = [];

	    for (i = 0; i < oUploadItemsCreated.Items.length; i++) {
	      items[i] = oUploadItemsCreated.Items[i];
	    }
	    var item_delete = false;
            items.forEach(function(item, id){
		console.log(id);
		    if (item_delete === true){
			indice = items.length - oUploadItemsCreated.Items.length ;
			id = id - indice;
			item_delete = false;
		    }
                var file = item.GetFile();
                var relativePath = item.GetRelativePath();
                relativepath = relativePath.split("/");

                if(file === null){
                    //This might be a folder and it will not be created
		    oUploadItemsCreated.Items.splice(id, 1);
		    item_delete = true;
                }
                relativepath.forEach(function(part){
                    if(part.substr(0,1) === "_"){
                        Gofast.toast(Drupal.t("You can't create the following document because a part of it's path is starting with '_' : ") + "<strong>" + item.GetRelativePath() + "</strong>", "warning");
			oUploadItemsCreated.Items.splice(id,1);
			item_delete = true;
                    }
                });
		if (item_delete === false){
		    var path = item._UploadProvider.Url._BaseUrl;
		    if(path.indexOf('/alfresco/webdav/Sites/FOLDERS TEMPLATES') !== -1){
			    Gofast.toast(Drupal.t("You can't create documents in folders templates"), "warning");
			    oUploadItemsCreated.Items.splice(id,1);
			    item_delete = true;
		    }
		}
            });
            oUploadItemsCreated.Upload(oUploadItemsCreated.Items);
      };
    },
    /*
     * Upload queue changed
     */
    _UploadQueueChanged : function(changes){
      $.each(changes.AddedItems, function (index, uploadItem) {
        Gofast.ITHit.queue.push({
            uuid: Gofast.ITHit.generate_uuid(),
            path : uploadItem._UploadProvider.Url._OriginalUrl,
            displayNamePath: "(" + uploadItem._UploadProvider.FSEntry._File.name + ") " + decodeURIComponent(uploadItem._UploadProvider.Url._OriginalUrl.replace('/alfresco/webdav/Sites/', '')),
            fileName: uploadItem._UploadProvider.FSEntry._File.name,
            operation: "upload",
            displayOperation: Drupal.t("Upload", {}, {context: 'gofast:ajax_file_browser'}),
            progression: 0,
            status: 0
        });
        uploadItem.AddListener('OnProgressChanged', '_UploadItemQueueChanged', this);
        uploadItem.AddListener('OnStateChanged', '_UploadItemQueueChanged', this);
        if(Gofast.ITHitMobile.dropPath){
          Gofast.ITHitMobile.dropPath = false;
          Gofast.ITHitMobile.Uploader.SetUploadUrl(location.origin + Gofast.ITHitMobile.currentPath);
        }
      }.bind(this));

      $.each(changes.RemovedItems, function (index, uploadItem) {
        console.log('removed');
      }.bind(this));
    },
    /*
     * Upload item queue changed
     */
    _UploadItemQueueChanged : function(change){
      //Get queue item by path
      var index = Gofast.ITHit.queue.findIndex(function(e){
        return e !== null && e.operation === "upload" && e.path === change.Sender._UploadProvider.Url._OriginalUrl;
      });

      if(!$.isNumeric(index)){
        return;
      }

      //Update state
      var state = 0;
      switch(change.NewState){
        case "Queued":
          state = 0;
          break;
        case "Uploading":
          state = 1;
          break;
        case "Failed":
          state = 3;
          break;
        case "Completed":
          state = 4;
          break;
      }
      Gofast.ITHit.queue[index].status = state;

      //Update progression
      if(typeof change.NewProgress !== "undefined" && typeof change.NewProgress.NewProgress !== "undefined" && state !== 4){
        Gofast.ITHit.queue[index].progression = change.NewProgress.NewProgress.Completed;
      }

      //Update completed, clear the queue and process the item
      if(state === 4){
        if(location.origin + Gofast.ITHitMobile.currentPath === change.Sender._UploadProvider.Url._BaseUrl){
          Gofast.ITHitMobile.reload();
        }
        Gofast.ITHit.queue[index].progression = 100;
        setTimeout(function(){
          Gofast.ITHit.queue[index] = null;
        }, 1000);
      }

      //Update failed, clear the queue and process the item
      if(state === 3){
          var baseUrl = change.Sender._UploadProvider.Url._BaseUrl;
        if(baseUrl == window.location.origin + "/alfresco/webdav/Sites"|| baseUrl == window.location.origin +"/alfresco/webdav/Sites/_Groups"|| baseUrl == window.location.origin +"/alfresco/webdav/Sites/_Organisations"|| baseUrl == window.location.origin +"/alfresco/webdav/Sites/_Extranet"|| baseUrl == window.location.origin +"/alfresco/webdav/Sites/_Public"){
            Gofast.ITHit.queue[index].progression = 0;
            Gofast.toast(Drupal.t("You can not upload files in root spaces (Groups, Organizations, Public, Extranet). Please, upload your files in sub-spaces or create them. ", {}, {context: 'gofast:ajax_file_browser'}),'warning');
            setTimeout(function(){
              Gofast.ITHit.queue[index] = null;
            }, 1500);
        }else{
            Gofast.ITHit.queue[index].progression = 0;
            Gofast.toast(Drupal.t("You are not authorized to upload ", {}, {context: 'gofast:ajax_file_browser'}) + " " + change.Sender._UploadProvider.FSEntry._File.name, "warning");
            setTimeout(function(){
              Gofast.ITHit.queue[index] = null;
            }, 1500);
        }
      }
    },
    /*
     * Refresh graphically the state of the queue
     */
    refreshQueue: function(){
      setInterval(function(){
        var queue = Gofast.ITHit.queue;
        var html = "";

        //Get uploadings elements
        var uploading = queue.filter(function(e){return e !== null && e.operation === 'upload';}).length;

        //Get copying elements
        var copying = queue.filter(function(e){return e !== null && e.operation === 'copy';}).length;

        //Get downloadings elements
        var downloading = queue.filter(function(e){return e !== null && e.operation === 'download';}).length;

        //Get moving elements
        var moving = queue.filter(function(e){return e !== null && e.operation === 'move';}).length;

        //Get deleting elements
        var deleting = queue.filter(function(e){return e !== null && e.operation === 'delete';}).length;

        //Get back HTML from retrieved data
        html += Gofast.ITHitMobile._formatQueue(uploading, copying, downloading, moving, deleting);

        //Insert HTML into the queue
        $("#file_browser_mobile_queue").html(html);
      }, 700);
    },
    /*
     * Format the queue regarding the data passed in param
     */
    _formatQueue: function(uploading, copying, downloading, moving, deleting){
      var html = "";

      //Format uploadings
      if(uploading > 0){
        html += '<span class="file_browser_mobile_queue_element"><i class="fa fa-cloud-upload" aria-hidden="true"></i> ' + uploading + "</span>";
      }

      //Format copyings
      if(copying > 0){
        html += '<span class="file_browser_mobile_queue_element"><i class="fa fa-files-o" aria-hidden="true"></i> ' + copying + "</span>";
      }

      //Format downloadings
      if(downloading > 0){
        html += '<span class="file_browser_mobile_queue_element"><i class="fa fa-cloud-download" aria-hidden="true"></i> ' + downloading + "</span>";
      }

      //Format movings
      if(moving > 0){
        html += '<span class="file_browser_mobile_queue_element"><i class="fa fa-arrow-right" aria-hidden="true"></i> ' + moving + "</span>";
      }

      //Format deletings
      if(deleting > 0){
        html += '<span class="file_browser_mobile_queue_element"><i class="fa fa-trash-o" aria-hidden="true"></i> ' + deleting + "</span>";
      }

      return html;
    },
    /*
     * Update Breadcrumb
     */
    updateBreadcrumb: function(path){
      //Remove breadcrumb
      const breadcrumbEl = $('#file_browser_mobile_header_breadcrumb').find('ul');
      breadcrumbEl.html("");
      //First, remove '/alfresco/webdav/' from path and remove / at the end
      if(path.substr(0, 17) === "/alfresco/webdav/"){
        path = path.substring(17, path.length);
      }
      if(path.substr(-1, 1) === "/"){
        path = path.substring(0, path.length - 1);
      }

      //Split path by /
      path = path.split('/');

      //Foreach path elements, build breadcrumb
      $.each(path, function(k, element){
        var domItem = $('#file_browser_mobile_header_breadcrumb').find('ul').append('<li>'+decodeURIComponent(element)+'</li>');

        if(k === path.length -1){ //Active item
          domItem.find('li').last().addClass('active');
        }else{ //Clickable item
          $('#file_browser_mobile_header_breadcrumb').find('ul').append(' » ');
          domItem.find('li').last().click(function(){
            Gofast.ITHitMobile.navigate("/alfresco/webdav/" + path.slice(0, k+1).join('/'));
          });
          domItem.find('li').last().attr('title', path.slice(0, k+1).join('/'));
        }
      });
      let scrollableWidth = 0;
      breadcrumbEl.find('li').each((i, e) => scrollableWidth += e.clientWidth);
      if (breadcrumbEl.width() < scrollableWidth){
        breadcrumbEl.css({position: 'relative', overflowX: 'scroll'});
        const breadcrumbStr = breadcrumbEl.find('li:nth-last-of-type(2)').attr('title');
        breadcrumbEl.find('li:last-of-type')[0].scrollIntoView();
        breadcrumbEl.tooltip({title: breadcrumbStr, placement: "bottom"});
      }
    },
    /*
     * Process items into the file browser when it's loaded
     * Called when navigation occures
     */
    _processItems: function (items, fullPath, mobile) {
      var itemHTML = "";
      $(".file_browser_mobile_files_element").remove();

      //First, if we are not localized at the root path '/alfresco/webdav/Sites'

      //Get parent path from given path
      var path = fullPath;
      if(path.substr(-1, 1) === "/"){
        path = path.substring(0, path.length - 1);
      }
      path = path.split('/');
      path.pop();
      var name = decodeURIComponent(path.last());
      path = path.join('/');

      //Get the 'Back' button at the top of the list
      itemHTML += Gofast.ITHitMobile._getBackButton(name);

      if(path !== "/alfresco/webdav"){
        //Add the item to the list
        var lastItem = $('#file_browser_mobile_files_table').find('tr:last()').parent();
        if(lastItem.length !== 0){//Append
          var processedItem = lastItem.append(itemHTML)
        }else{ //Replace
            if($('#file_browser_mobile_files_table').find('#mCSB_2_container').length){
                var processedItem = $('#file_browser_mobile_files_table').find('#mCSB_2_container').html(itemHTML);
            }else{
                var processedItem = $('#file_browser_mobile_files_table').html(itemHTML);
            }
        }
        processedItem = processedItem.find('tr').last();

        //Attach event handlers to the processed item
        Gofast.ITHitMobile._attachEvents(null, processedItem, path, mobile);
      }

      //Sort items
      items = Gofast.ITHit.sort(items, true);


      for (var i = 0; i < items.length; i++) {
        //Format the item
        itemHTML = "";
        var item = items[i];

        
        var itemHTML = Gofast.ITHitMobile._formatItem(item);

        //Add the item to the list
        var lastItem = $('#file_browser_mobile_files_table').find('tr:last()').parent();
        if(lastItem.length !== 0){//Append
          var processedItem = lastItem.append(itemHTML)
        }else{ //Replace
            if($('#file_browser_mobile_files_table').find('#mCSB_2_container').length){
                var processedItem = $('#file_browser_mobile_files_table').find('#mCSB_2_container').html(itemHTML);
            }else{
                var processedItem = $('#file_browser_mobile_files_table').html(itemHTML);
            }
        }

        processedItem = processedItem.find('tr').last();

        //Attach event handlers to the processed item
        Gofast.ITHitMobile._attachEvents(item, processedItem, null, mobile);

      }
    },
    /*
     * Return HTML formatted back button
     */
    _getBackButton : function(name){
      var itemHTML = "";

      itemHTML += "<tr id='file_browser_mobile_back_button' class='file_browser_mobile_files_element' style='height: 36px;'>";
        //Icon
        itemHTML += "<td style='width:14%; padding-left:7px;'>";
          itemHTML += "<span class='fa fa-arrow-left' style='color:#3498db; font-size: 17px;'></span>";
        itemHTML += "</td>";

        //Name
        itemHTML += "<td style='width:86%;'>";
          itemHTML += Drupal.t("Back to ", {}, {context: "gofast:ajax_file_browser"}) + name;
        itemHTML += "</td>";

        //Modification date
        itemHTML += "<td style='width:0%;'>";
        itemHTML += "</td>";
      itemHTML += "</tr>";

      return itemHTML;
    },
    /*
     * Attach event handlers to the processed item passed in param
     * Called in the item processing phase
     */
    _attachEvents: function(item, processedItem, path, mobile){
      if(typeof item !== "undefined" && item !== null){
        if(!mobile){
          //Folder navigation triggering at double click
          if(item.ResourceType === "Folder"){
            processedItem.dblclick(function(){
              Gofast.ITHitMobile.navigate(item.Href);
            });
          }
          if(item.ResourceType === "Resource"){
            //Go to node in ajax triggering at double click
            processedItem.dblclick(function(){
              // if(!Gofast._settings.isMobile){
                Gofast.addLoading();
              // }
              Gofast.ITHit.goToNode(item.Href);
            });
            processedItem.on('mousedown', function(e){
              if(e.which == 2){
                Gofast.ITHit.goToNode(item.Href, true);
              }
            });
          }

          //Allow to select items
          processedItem.on('mousedown', function(e){
              if(e.shiftKey){
                if($(".selected").length > 0){
                  if(processedItem.hasClass('selected')){

                  }else if($(".selected").first().position().top > processedItem.position().top || $(".selected").first().position().left > processedItem.position().left){
                    processedItem.nextUntil($(".selected").first(), "tr").not('.search-hidden').addClass('selected');
                  }else{
                    $(".selected").last().nextUntil(processedItem, "tr").not('.search-hidden').addClass('selected');
                  }
                  processedItem.addClass('selected');
                }else{
                  $(".selected").removeClass("selected");
                  processedItem.addClass('selected');
                }
              }else if(e.ctrlKey){
                if(processedItem.hasClass('selected')){
                  processedItem.removeClass('selected');
                }else{
                  processedItem.addClass('selected');
                }
              }else{
                if(!processedItem.hasClass('selected')){
                  $(".selected").removeClass("selected");
                  processedItem.addClass('selected');
                }
              }
          });
          processedItem.on('mouseup', function(e){
              if(!e.shiftKey && !e.ctrlKey && e.button === 0){
                $(".selected").removeClass("selected");
                processedItem.addClass('selected');
              }
          });

          //Display menu at right click event, select the item if it's not already selected
          processedItem.contextmenu(function(e){
            if(!processedItem.hasClass('selected')){
              processedItem.click();
            }
            Gofast.ITHitMobile._contextMenuHandler(e);
          });
        }else{
            //Folder navigation triggering at single click
            if(item.ResourceType === "Folder"){
              processedItem.click(function(){
                Gofast.ITHitMobile.navigate(item.Href);
              });
            }
            if(item.ResourceType === "Resource"){
              //Go to node in ajax triggering at single click
              processedItem.click(function(){
                if(Gofast.ITHitMobile.mobileVersion !== true){
                  // if(!Gofast._settings.isMobile){
                    Gofast.addLoading();
                  // }
                  }
                Gofast.ITHit.goToNode(item.Href);
              });
            }

             //Display menu at right click event, select the item if it's not already selected
            processedItem.contextmenu(function(e){
                $(".selected").removeClass("selected");
                if(!processedItem.hasClass('selected')){
                  processedItem.addClass('selected');
                }
                Gofast.ITHitMobile._contextMenuHandler(e);
            });
        }
      }

      //Navigation triggering at single click
      if(typeof path !== "undefined" && path !== null){
        processedItem.click(function(){
          Gofast.ITHitMobile.navigate(path);
        });
      }
    },
    /*
     * Triggered by right clicking an item
     * Display the corresponding menu
     */
    _contextMenuHandler : function(e){

      //Prevent any default browser action, we are going to manage all actions
      e.preventDefault();

      //If another menu is open, destroy it
      if($(".mobile-browser-node-actions").is('.open') !== false){
        $(".mobile-browser-node-actions").remove();
      }

      //Display the loader, waiting the ajax request to get the menu and positioning
      //dynamically the menu
      var menu = $('<div class="gofast-node-actions"><ul class="dropdown-menu gofast-dropdown-menu" role="menu"><li><div class="loader-activity-menu-active"></div></li></ul></div>').insertAfter("#ithit-toggle");

      if(!$(menu).length) {
        menu = $('<div class="dropdown-menu dropdown-menu-md py-5"><ul class="navi navi-hover navi-link-rounded-lg px-1" role="menu"><li><div class="loader-activity-menu-active"></div></li></ul></div>').insertAfter("#main-ajax-file-browser");
      }

      //Show the menu and position it
      menu.addClass('open, show');
      menu.css('position', 'fixed');
      menu.css('left', e.clientX);
      menu.css('top', e.clientY);
      menu.css('z-index', "99999");
      menu.addClass('mobile-browser-node-actions');

      //Add event to destroy the menu when clicking outside
      $('body').click(function(e){
        //Destroy the listner for performances
        $(this).off(e);

        //Remove the item
        menu.remove();

      });

      //Get the selected elements
      var data = [];
      var selected = $('#file_browser_mobile_files_table').find('.selected').find('.item-path');
      $.each(selected, function(k, elem){
        data.push(elem.innerText);
      });

      //AJAX request to get the menu
      $.post(location.origin + "/gofast/node-actions/filebrowser", {selected: data}, function( data ) {
        if($(data).find('ul').length == 0){ //Empty menu
          menu.remove();
          return;
        }

        //Replace functions in menu with mobile version
        data = data.replace(/Gofast.ITHit.rename/g, 'Gofast.ITHitMobile.rename');
        data = data.replace(/Gofast.ITHit.downloadSelected/g, 'Gofast.ITHitMobile.downloadSelected');
        data = data.replace(/Gofast.ITHit.deleteSelected/g, 'Gofast.ITHitMobile.deleteSelected');
        data = data.replace(/Gofast.ITHit.bulkSelected/g, 'Gofast.ITHitMobile.bulkSelected');
        
        $(menu).find("ul").html($(data).find('ul').html());
        
        var duplicate_link = $(menu).find('a.gf-filebrowser-full-only').parent();
        $(duplicate_link).next().remove();
        $(duplicate_link).remove();
              
        Drupal.attachBehaviors();

        //Check if the menu is out of the window, reposition it if needed
        var bottom = $(menu)[0].getBoundingClientRect().top + menu[0].scrollHeight;
        if(window.innerHeight < bottom){
          var diff = bottom - window.innerHeight;
          $(menu).css('top', parseInt($(menu).css("top")) - diff);
        }
      });
    },
    /*
     * Delete selected items
     */
    deleteSelected: function(e, selection){
      if(typeof selection === "undefined"){
        var supprEvent = $.Event('keyup');
        supprEvent.keyCode = 46;
          //Mobile browser
          $("#file_browser_mobile_files_table").trigger(supprEvent);
      }else{
        var data = JSON.stringify([selection]);
        Gofast.ITHit.delete(data);
      }
      e.preventDefault();
      e.stopPropagation();
    },
    /*
     * Set Drupal variable to contain the selected items and call back itelfs to
     * do an action with this bulk (taxonomy, location mass management..)
     */
    bulkSelected: function(e, path){
        var element = $(e.target);
        //Stop propagation of the click event
        e.preventDefault();
        e.stopImmediatePropagation();
        var data = [];

        if(path){
          data.push({url: path, type: "Folder"});
        }else{
          //Get selected elements
          var selected = $('#file_browser_full_files_table').find('.selected').find('.item-path');
          if (selected.length == 0){
            var selected = $('#file_browser_mobile_files_table').find('.selected').find('.item-path');
          }
          $.each(selected, function(k, elem){
            var path = elem.innerText;

            //Remove slash at the end if needed
            if(path.substr(-1, 1) === "/"){
              path = path.substring(0, path.length - 1);
            }

            var type = $(elem).parent().find('.item-real-type').text();
            data.push({url: path, type: type});
          });
        }
        data = JSON.stringify(data);

        //Send selected elements to Drupal
        var user_id = Gofast.get("user").uid;
          $.post( "/gofast/variable/set", { name: "ithit_bulk_"+user_id, value: data }).done(function( data ) {
            if($(element[0]).hasClass('manage-taxonomy') || $(element[0]).parentsUntil('ul').hasClass('manage-taxonomy')){
              $('.bulk_taxonomy').click();
            }else if($(element[0]).hasClass('add-locations') || $(element[0]).parentsUntil('ul').hasClass('add-locations')){
              $('.bulk_add_locations').click();
            }else if($(element[0]).hasClass('manage-publications') || $(element[0]).parentsUntil('ul').hasClass('manage-publications')){
              $('.bulk_publications').click();
            }else if($(element[0]).hasClass('manage-mail-sharing') || $(element[0]).parentsUntil('ul').hasClass('manage-mail-sharing')){
              $('.bulk_mail_sharing').click();
            }else if($(element[0]).hasClass('bulk-archive') || $(element[0]).parentsUntil('ul').hasClass('bulk-archive')){
              $('.bulk_archive').click();
	          }else{
              $('.bulk_add_to_cart').click();
            }
          });
    },
    /*
     * Download selected items
     */
    downloadSelected: function(){
      //Get selected items
      var selected = $('#file_browser_mobile_files_table').find('.selected');

      //Push them to queue
      $.each(selected, function(k, elem){
        var path = $(elem).find('.item-path').text();
        var fileName = $(elem).find('.item-name').text();

        if($(elem).find('.item-real-type').text() !== 'Resource'){
          Gofast.toast(Drupal.t("Can't download ", {}, {context: 'gofast:ajax_file_browser'}) + " " + fileName, "warning");
        }else{
          Gofast.ITHit.queue.push({
            uuid: Gofast.ITHit.generate_uuid(),
            path : path,
            displayNamePath: fileName + ' (' + decodeURIComponent(path).replace('/alfresco/webdav/Sites/', '') + ')',
            fileName: fileName,
            operation: 'download',
            displayOperation: Drupal.t('Download', {}, {context: 'gofast:ajax_file_browser'}),
            progression: 0,
            status: 0
          });
        }
      });
    },
    /*
     * Get an Item and return the corresponding HTML
     * Called when items are processed
     */
    _formatItem: function(item){
      var itemHTML = "";

      itemHTML += "<tr class='file_browser_mobile_files_element'>";
      //Icon
      itemHTML += "<td title='"+item.DisplayName+"' style='width:14%' class='item-icon'>";
        if(item.ResourceType == "Folder"){ //It's a folder
          var icon = Gofast.ITHit._getIconPath(item.DisplayName, item.Href, "fa");
          for(var i= 0; i <  Gofast._settings.gofast_ajax_file_browser.archived_spaces.length; i++)
          {
              if (decodeURIComponent(item.Href) == Gofast._settings.gofast_ajax_file_browser.archived_spaces[i] + '/' ){
                  icon = 'fa-archive';
              }
          }
          if(icon === "TEMPLATE"){
            icon = "fa-folder";
            var color = "#f0685a";
          }else{
            var color="#3498db";
          }
          itemHTML += "<span class='fas "+icon+"' style='color:"+color+"'></span>";
        }else{ //It's a document, use mapping to find the proper icon
          //Get extension
          var ext = item.DisplayName.split('.').pop();

          //Get font
          var font = Drupal.settings.ext_map[ext];
          var typeForArticle = Gofast.ITHit._getTypeFromRessourceType(item.DisplayName, item.Href, item.ResourceType, item.ContentType);
          if(typeForArticle === "Article") { //Article icon
              itemHTML += "<span class='far fa-ballot'></span>";
          }else if(typeof font !== "undefined"){ //Known
                itemHTML += "<span class='fa " + font + "'></span>";
          }else {
              itemHTML += "<span class='fa fa-file-o file-other'></span>";
          }
        }
      itemHTML += "</td>";

      //Name
      itemHTML += "<td class='item-name' title='"+item.DisplayName+"' style='width:51%; height:30px;'>";
        itemHTML += item.DisplayName;
      itemHTML += "</td>";

      //Type
      itemHTML += "<td class='item-real-type' style='display:none;'>";
        itemHTML += item.ResourceType;
      itemHTML += "</td>";

      //Modification date
      itemHTML += "<td class='item-date' style='width:35%;'>";
        if(typeof item.LastModified !== "undefined"){
          var date = item.LastModified;
          //Display date, regarding the user language
          if(Gofast.get('user').language === "en"){
            var displayedDate = ("0" + (date.getMonth() + 1)).slice(-2) + "/" + ("0" + (date.getDate())).slice(-2) + "/" + date.getFullYear().toString().slice(-2) + " " + ("0" + (date.getHours())).slice(-2) + ":" + ("0" + (date.getMinutes())).slice(-2);
          }else{
            var displayedDate = ("0" + (date.getDate())).slice(-2) + "/" + ("0" + (date.getMonth() + 1)).slice(-2) + "/" + date.getFullYear().toString().slice(-2) + " " + ("0" + (date.getHours())).slice(-2) + ":" + ("0" + (date.getMinutes())).slice(-2);
          }
          itemHTML += displayedDate;
        }
      itemHTML += "</td>";

      //Stock the path to the item
      itemHTML += "<td class='item-path' style='display:none;'>";
        itemHTML += item.Href;
      itemHTML += "</td>";

      itemHTML += "</tr>";
      return itemHTML;
    },
    /*
     * Implements an little input form to rename the document/folder
     */
    rename : function(href){
      //Search and get the line we are editing
      var element = $('#file_browser_mobile_files_table').find('td:contains("'+href+'")');
      var name_element = element.parent().find('.item-name');

      //Check if we got an element
      if(name_element.length == 0){
        Gofast.toast(Drupal.t("Unable to rename this item", {}, {context: 'gofast:ajax_file_browser'}), "warning");
      }else{
        //Save old name
        var old_name = name_element.text();

        //We are secure to edit
        var input_group = name_element.html('<input id="rename-form" class="form-control form-text" value="' + name_element.text() + '" style="line-height:0px;height:20px;width:80%;float:left"><div class="btn-group" role="group"><button style="height:18px;padding-left:5px;padding-right:5px;padding-top:0px;padding-bottom:0px;" type="button" class="btn btn-success"><i class="fa fa-check"></i></button><button type="button" style="height:18px;padding-left:5px;padding-right:5px;padding-top:0px;padding-bottom:0px;" class="btn btn-danger"><i class="fa fa-times"></i></button>');

        //Select text
        input_group.find('input:text').select();

        //Set element height
        name_element.css("width", "82%");

        //Bind the enter event to the input
        name_element.find('input').on('keyup', function(e){
          if(e.keyCode == 13){ //Enter pressed
            var new_name = name_element.find('input').val();

            //Prevent users to rename contents with a name starting with '_'
            if(new_name.substr(0,1) === "_"){
                Gofast.toast(Drupal.t("You can't rename a content with a name starting with '_'"), "warning");
                return;
            }

            //Trigger the animation
            name_element.html('<div class="loader-filebrowser"></div>'+new_name);

            //Process rename
            Gofast.ITHit._processRename(href, old_name, new_name, name_element, "ressource");

            //Reset element height
            name_element.css("width", "51%");
          }
        });
        //Bind the validate button event
        name_element.find('.btn-success').on('click', function(e){
          var new_name = name_element.find('input').val();

          //Prevent users to rename contents with a name starting with '_'
          if(new_name.substr(0,1) === "_"){
              Gofast.toast(Drupal.t("You can't rename a content with a name starting with '_'"), "warning");
              return;
          }

          //Trigger the animation
          name_element.html('<div class="loader-filebrowser"></div>'+new_name);

          //Process rename
          Gofast.ITHit._processRename(href, old_name, new_name, name_element, "ressource");

          //Reset element height
          name_element.css("width", "51%");
        });
        //Bind the cancel button event
        name_element.find('.btn-danger').on('click', function(e){
          name_element.text(old_name);
          //Reset element height
          name_element.css("width", "51%");
        });
      }
    },
    /*
     * Attach mobile browser events
     */
    attachBrowserEvents: function(mobile){
      $('html').on('click', '#file_browser_mobile_tooolbar_refresh', function(){
        Gofast.ITHitMobile.reload();
      });
      $('html').on('click', '#file_browser_books_mobile_tooolbar_refresh', function(){
        // GOFAST-8125 - empty wiki filter input before reload
        $("#file_browser_mobile_toolbar_search_input").val("");
        Gofast.ITHitMobile.reload();
      });
      $('html').on('click', '#file_browser_forums_mobile_tooolbar_refresh', function(){
        Gofast.ITHitMobile.reload();
      });


      $('#ithit-toggle').click(function(){

        Gofast.ITHitMobile.toggle();
        getCurrentUrl = window.location.href;

        if( getCurrentUrl.indexOf('node')== -1){

            reservedPath = null;
            if($("#ithit-toggle").hasClass('shown')){
                Gofast.ITHitMobile.navigate( "/Sites" );
             }

        }else{
            if( reservedPath !== null && $("#ithit-toggle").hasClass('shown')){
                Gofast.ITHitMobile.navigate( reservedPath );
          }
        }
    });

    $(document).ready(function () {
        //Handle path changes in URL when clicking on back/forward button
        $(document).on('urlChanged', function(e, oldLocation){
          var params = {};
            if (location.search) {
              var parts = location.search.substring(1).split('&');

              for (var i = 0; i < parts.length; i++) {
              var nv = parts[i].split('=');
              if (!nv[0]) continue;
              params[nv[0]] = nv[1] || true;
            }
          }

          if(typeof params.path !== "undefined" && params.path !== ""){
             //trigger the navigation only if the 2 hashes are the same. If not it means that we just change bootstrap tab  
             var new_param_path = location.search.replace("?&path=", "");
             var old_param_path = oldLocation.params.path;
           // if(location.hash == oldLocation.hash && new_param_path != old_param_path){
            if(location.hash == oldLocation.hash){
                 Gofast.ITHit.navigate('/alfresco/webdav' + params.path, null, null, true);
            }
          }
        });
     });

      $(document).on('click', '#toggle-fitscreen', function(e) {
        $('#name_header').trigger('resize');
        $('#size_header').trigger('resize');
        $('#type_header').trigger('resize');
        if ($('#toggle-fitscreen').find('i').hasClass('fa-compress')) {
          if($("#ithit-toggle").hasClass('hiddenithit')){
            Gofast.ITHitMobile.notShow = true;
          }
          Gofast.ITHitMobile.toggle('hide');
        } else {
          if(Gofast.ITHitMobile.notShow){
            Gofast.ITHitMobile.notShow = false;
          }else{
            Gofast.ITHitMobile.toggle('show');
          }
        }
      });

      $("#file_browser_mobile_toolbar_search_input").on('keyup', function(e){
        //We set timeout to prevent JS engine overload (and we clear the timeout each time a key is pressed)
        clearTimeout(Gofast.ITHitMobile.searchProcess);
        Gofast.ITHitMobile.searchProcess = setTimeout(function(){
          Gofast.ITHitMobile.search($('#file_browser_mobile_toolbar_search_input').val());
        }, 300);
      });
      
      //Same block but we filter forums in the explorer tab
      $("html").on('keyup', '#forum_explorer_toolbar_search_input', function(e){
        //We set timeout to prevent JS engine overload (and we clear the timeout each time a key is pressed)
        clearTimeout(Gofast.ITHitMobile.searchProcess);
        Gofast.ITHitMobile.searchProcess = setTimeout(function(){
          Gofast.ITHitMobile.search($('#forum_explorer_toolbar_search_input').val(), true);
        }, 300);
      });

      //Same block but we filter books in the explorer tab
      $("html").on('keyup', '#book_explorer_toolbar_search_input', function(e){
        //We set timeout to prevent JS engine overload (and we clear the timeout each time a key is pressed)
        clearTimeout(Gofast.ITHitMobile.searchProcess);
        Gofast.ITHitMobile.searchProcess = setTimeout(function(){
          Gofast.ITHitMobile.search($('#book_explorer_toolbar_search_input').val(), false, true);
        }, 300);
      });

      $("#file_browser_mobile_files_table").on('keyup', function(e){
            if(e.keyCode == 46){ //Suppr pressed
              if($("#rename-form").length !== 0){
                return;
              }
              //Retrieve all selected items
              var data = [];
              var selected = $('#file_browser_mobile_files_table').find('.selected').find('.item-path');
              var noDelete = false;
              $.each(selected, function(k, elem){
                var path = elem.innerText;

                //Remove slash at the end if needed
                if(path.substr(-1, 1) === "/"){
                  path = path.substring(0, path.length - 1);
                }

                //Check if this is a space
                var name = path.split('/');
                name = name.pop();

                if(name.substr(0,1) !== '_'){
                    if(decodeURI(name) === "FOLDERS TEMPLATES"){
                        Gofast.toast(Drupal.t("You can't delete FOLDERS TEMPLATES.", {}, {context: 'gofast:ajax_file_browser'}), "warning");
                        noDelete = true;
                    }else{
                        data.push(elem.innerText);
                    }
                }else{
                    noDelete = true;
                    Gofast.addLoading();
                    $.get(location.origin + "/ajax/getnidfromhref?href=" + path)
                    .done(function(result) {
                        $.ajax({
                            url: location.origin + "/modal/nojs/gofast_og/delete_space/"+ result,
                        }).done(function(commands){
                            var jsonCommands = JSON.parse(commands);

                            jsonCommands.forEach(function(k,v){
                                if(k.command == "modal_display"){
                                    Gofast.removeLoading();
                                    Gofast.modal(k.output, k.title);
                                }
                            })
                        })
                        .fail(function () {
                        Gofast.removeLoading();
                        Gofast.toast(Drupal.t("You don't have permission to delete this space", {}, {context: 'gofast:ajax_file_browser'}), "warning");
                    })
                    })
                }
              });
              data = JSON.stringify(data);

              if(!noDelete){
                //process delete
                Gofast.ITHit.delete(data);
              }
            }
          });
    },
    /*
     * Search a string in displayed items
     */
    search: function(pattern, for_forums=false, for_books=false){
      if($("#rename-form").length !== 0){
        return;
      }
      var elements = (for_forums) ? $(".forum-explorer-element") : (for_books) ? $('.book-explorer-element') : $(".file_browser_mobile_files_element").not('#file_browser_mobile_back_button');
      
        if(pattern === ""){
            elements.removeClass('search-hidden');
            elements.css('display', 'block');

            //Remove bold
            $.each(elements.find('.item-name'), function(k, elem){
             $(elem).text($(elem).text());
            });
        }else{
            $.each(elements, function(k, element){
            if($(element).find('.item-name').text().toLowerCase().indexOf(pattern.toLowerCase()) === -1){
                $(element).addClass('search-hidden');
                setTimeout(function(){
                $(element).css('display', 'none');
             }, 300);
             
              $(element).find('.item-name').text($(element).find('.item-name').text());
            }else{
             $(element).removeClass('search-hidden');
             $(element).css('display', 'block');

             //Add bold
             $(element).find('.item-name').text($(element).find('.item-name').text());
              var name = $(element).find('.item-name').text()
              var indexStart = $(element).find('.item-name').text().toLowerCase().indexOf(pattern.toLowerCase());
              var indexEnd = indexStart + pattern.toLowerCase().length;

              var newHtml = name.substring(0, indexStart) + "<span class='search-bold'>" + name.substring(indexStart, indexEnd) + "</span>" + name.substring(indexEnd);
             $(element).find('.item-name').html(newHtml);
             }
            });
         }
         if(for_forums) Gofast.ITHitMobile.display_forums();
    },
    display_forums: function() {
        var elements = $(".forum-explorer-element-table");
        $.each(elements, function(k, elem) {
            setTimeout(function() {
                var s = $(elem).children().children().length > 0 ? "block" : "none";
                $(elem).css('display', s);
            },300)
        });
    },
    toggle: function(state){
      if(state === "show" && $("#ithit-toggle").hasClass('shown')){
          return;
      }
      if(state === "hide" && $("#ithit-toggle").hasClass('hiddenithit')){
        return;
      }
      if($("#file_browser_mobile_container").css('left') === "0px" || $("#file_browser_mobile_container").css('left') === "auto"){
        $("#ithit-toggle").removeClass('shown');
        $("#ithit-toggle").addClass('hiddenithit');
        $("#file_browser_mobile_container").animate({
          left: "-250px",
        }, 500);
        $("#ithit-toggle").animate({
          left: "0px",
        }, 500);
        $(".main-container").css('margin-left', 'auto');
      }
      if($("#file_browser_mobile_container").css('left') === "-250px"){
        $("#ithit-toggle").addClass('shown');
        $("#ithit-toggle").removeClass('hiddenithit');
        $("#file_browser_mobile_container").animate({
          left: "0px",
        }, 500);
        $("#ithit-toggle").animate({
          left: "250px",
        }, 500);
        if(parseInt(jQuery('.main-container').css('margin-left')) <= 250 && parseInt(jQuery('.main-container').position().left) <= 250){
          $(".main-container").css('margin-left', '250px');
        }
      }
    }
  }

  Gofast.ITHitMobile.gofast_book_refresh_file_browser();

   Drupal.behaviors.marginContainer = {
    attach: function(context, settings) {
      if (window.innerWidth < 1600){
          if ($('#file_browser_mobile_container', context).css('left') == '0px'){
              $('.main-container',context).css('margin-left','250px');
          }
          if ($('#file_browser_mobile_container', context).css('left') == '-250px'){
              $('.main-container',context).css('margin-left','auto');
          }

          $('#ithit-toggle',context).click(function(){
              if ($('#file_browser_mobile_container', context).css('left') == '0px'){
                  $('.main-container',context).css('margin-left','auto');
              }else if ($('#file_browser_mobile_container', context).css('left') == '-250px'){
                  $('.main-container',context).css('margin-left','250px');
              }
          });
      }

    }
  };

  Drupal.behaviors.marginContainer = {
    attach: function (context, settings) {
    // $(document).ready(function(){
    $(window).resize(function(){
      //Handle resize event to resize the mobile file browser
      $('#file_browser_mobile_files_table').height(jQuery("#content-main-container").outerHeight()-180-jQuery("#file_browser_mobile_queue").outerHeight());
      $('#forum_explorer_body').height(jQuery("#content-main-container").outerHeight()-180);
      $('#book_explorer_body').height(jQuery("#content-main-container").outerHeight()-180);
    });
    $('#file_browser_mobile_files_table').height(jQuery("#content-main-container").outerHeight()-180-jQuery("#file_browser_mobile_queue").outerHeight());
    $('#forum_explorer_body').height(jQuery("#content-main-container").outerHeight()-180);
    $('#book_explorer_body').height(jQuery("#content-main-container").outerHeight()-180);
    }
  };
  
})(jQuery, Gofast, Drupal);
