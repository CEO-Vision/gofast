(function ($, Gofast, Drupal) {

  /*
  * GoFAST Essential main library
  */
  Gofast.Essential = {
      /*
      * Handle a solr search in Essential version
      */
      solrSearch: function(terms){
          
          $("#search-block-form").addClass("processed");
          if(terms == ""){
            terms = "all";
          }
          // GOFAST-10214 - prevent search query if query contains a slash
          let termsWithoutQuery = terms.split("?")[0];
          let hasSlash = !!termsWithoutQuery.match(new RegExp(/\/|%2F/g))
          if (hasSlash) {
            Gofast.toast(Drupal.t("It is forbidden to make a search query with slashes"), "error");
            return;
          }
          if(Gofast._settings.isEssential && !Gofast._settings.isMobileDevice){
            Gofast.Essential.closeFullPageLayer()
            if($('#mobile_file_browser_full_tree_container').length == 0){
              Gofast.Essential.getHiddenFileBrowserContent().then((fileBrowserContent)=>{
                $('.mainContent.fullScreen').html("")
                $('.mainContent.fullScreen').html(fileBrowserContent)

                $('#essentialFileBrowserHistory').attr('style', 'display:none!important;')
              
                Gofast.ITHit.tree.cancelSelectedNode()
                Gofast.Essential.showSearchLayer(terms)
              })
            } else {
              Gofast.Essential.showSearchLayer(terms)
            }
          }
      },
      //Get the content of the filebrowser page
      // Get the content of the file browser page
      getFileBrowserContent: async function() {
        try {
          // Make the GET request to fetch file browser content
          const content = await $.get('/essential/get_node_content_part/filebrowser/0');
          return content;
        } catch (error) {
          // Handle the error here
          console.error('Error fetching file browser content:', error);
          throw error;
        }
      },
      getHiddenFileBrowserContent: function(){
        return new Promise((resolve) => {
          $.get('/essential/get_node_content_part/hidden_filebrowser/0').done((content)=>{
            resolve(content);
          })
        })
      },
      /**
       * Close full page layer (e.g: alfresco_item, webform)
       */
      closeFullPageLayer: function(e){
        var backgroundContent = $("#gofastContainer > div:not('#nodeContainer')")
        var fullPageNode = $("#nodeContainer[data-isfullpage='true']")
        var nid = fullPageNode.data("nid");
        if(fullPageNode.length == 0){
          return;
        }
        fullPageNode.remove()
        backgroundContent.find("[id=document__infotab_disabled]").attr("id", "document__infotab")
        backgroundContent.removeClass("d-none").addClass("d-flex")
        Gofast.ITHit.reset_full_browser_size()
        // Highlight and scroll to the node in the file browser
        let nodeItem = $(`.item-nid:contains('${nid}')`).parent();
        if(nodeItem.length){
          nodeItem.trigger("mousedown")
          $("#file_browser_full_files_table").mCustomScrollbar("scrollTo", nodeItem)
        }
        $(window).trigger("resize", ["fromResize"]) // second argument prevent retrigger of reset_full_browser_size
        if(Gofast.ITHit){
          Gofast.ITHit.reload();
        }
        if (Gofast.isTablet()) {
          Gofast.tabletOrientationHandler({}, true);
        }
      },
      /*
      * Handle essential navigation, replacing processAjax in ajaxification
      */
      processEssentialAjax: function(href){
        const isValidUrl = (urlString) => {
          try { 
            return Boolean(new URL(urlString)); 
          }
          catch(e){ 
            return false; 
          }
        }
        if(isValidUrl(href)){
          href = new URL(href);
          } else {
          href = window.location.origin + href
          href = new URL(href);
          }
        let hrefWithoutOrigin = href.pathname + href.search + href.hash
        if (href.pathname.startsWith("/node/") && Number(href.pathname.split("/")[2].replace(/\D/g, "")) !== 0 && Number.isInteger(Number(href.pathname.split("/")[2].replace(/\D/g, "")))){
          let action = href.pathname.split("/")[3]
          if (action) {
            Gofast.processAjax(hrefWithoutOrigin);
            return;
          }
          let nid = href.pathname.split("/")[2]
          let type = href.pathname.split("/")[1]
          let urlParam = new URLSearchParams(href.search)

            let isFolder = false;
            
            if(href.search.includes("path=")){
              urlParam = urlParam.get("path");
              if(urlParam != null){
                let pathArray = urlParam.split("/");
                if(!pathArray[pathArray.length-1].startsWith("_")){
                let pathArrayReverse = urlParam.split("/").reverse()
                //iterate until the first space parent is find
                pathArrayReverse.forEach((e,i)=>{
                  if(isFolder){
                    return;
                  }
                  //if the node is a space, stop the loop and go to this space node
                  if(e.startsWith("_")){
                    isFolder = true;
                    let parentSpace = urlParam.slice(0,urlParam.indexOf(pathArray[pathArray.length-i]))
                    $.get(location.origin+"/ajax/getnidfromhref?href="+parentSpace).done((result)=>{
                      if(result != ""){
                        nid = result
                        history.pushState({}, "", "/node/"+nid+"?path="+urlParam+"#ogdocuments")
                        Gofast.Essential.goToNode(nid, "folder", false, urlParam);
                        isFolder = true;
                      }
                    });
                  }
                })
              }
            }
            }
            if(isFolder){
              return;
            }
            Gofast.Essential.goToNode(nid, type, false, "", href.search);
        } else {
          $('.essentialHeader a.btn-clean').removeClass('selected')
          if(href.pathname == "/activity"){
            Gofast.Essential.showActivityFeed();
          }else if(href.pathname.startsWith("/search/solr")){
            let terms = href.pathname.split("/")[3]+href.search;
            Gofast.Essential.solrSearch(terms);
          } else {
            Gofast.processAjax(hrefWithoutOrigin, true);
          }
        }
      },
    /*
    * Handle essential navigation to a node
    */
    processEssentialNodeAjax: function(href){
      let nid = "";
      let hash = "";
      if(href.includes("#")){
        nid = href.substring(0, href.indexOf("#"))
        hash = href.substring(href.indexOf("#")+1)
      }
      nid = nid.split("/")[2]
      
      //get the nid of the node we come from
      var oldNid = location.pathname.split("/")[2]

      //update the Gofast.get("node") variable
      Gofast.Essential.setNodeObject(nid, true);
      
      //If there is a gfb tab hash in the href, go to the space with the selected tab
      if(hash == "oghome" || hash == "ogdocuments" || hash == "ogcalendar" || hash == "ogkanban" || hash == "gofastSpaceMembers"){
        history.pushState({}, "", href)
        $('.essentialHeader a.btn-clean').removeClass('selected')
        Gofast.Essential.removeAllNodeLayers(true);
        
        if($("#gofast_file_browser_side_content").length == 0){
          $.get('/essential/get_node_content_part/pageContent/0').done(async (content)=>{
            $("#gofast_over_content").remove()
            $("#content-main-container").prepend(content)
            await Gofast.Essential.showFileBrowserLayer({nid : nid, hash : '#'+hash});

          })
        } else {
          Gofast.Essential.showFileBrowserLayer({nid : nid, hash : "#"+hash, showOnly : true});
          Gofast.Essential.navigateFileBrowser(nid, "#"+hash)
        }
      } else if(hash == "comment-init"){ //If the href redirect to a forum
        if (oldNid == nid) return; // If the forum is already diplayed don't to anything
        Gofast.Essential.showForumLayer(nid)
        history.pushState({}, "", "/node/" + nid + "#comment-init");
      } else if(hash.startsWith("comment-") && hash != "comment-init"){ //If the href redirect to the comment of a forum, show the forum and scroll to the comment
        history.pushState({}, "", href)
        //scroll to comment
        const goToComment = function(hash){
          $("#"+hash).find(".timeline-content").addClass("comment-new");
          $("#"+hash).find(".timeline-content").addClass("comment-new");
          
          setTimeout(function(){
            $("#"+hash).find(".timeline-content").removeClass("comment-new");
            $("#"+hash).find(".timeline-content").removeClass("comment-new");
          }, 2000);
          
          $("#"+hash)[0].scrollIntoView({ behavior: 'smooth' });
        }
        
        //show the forum page if it's not already loaded or if the forum clicked is different
        if(!$("#forumPageLayer").length || nid != oldNid){
          Gofast.Essential.showForumLayer(nid)
          const loadCommentInterval = setInterval(()=>{
            if($("#"+hash).length > 0){
              clearInterval(loadCommentInterval);
              goToComment(hash)
            }
          },20)
        } else {
          goToComment(hash)
        }
      } else {
        
        Gofast.processAjax(href)
      }
    },
    /*
    * Handle layers and pages at click on top bar items in Essential
    */
    topBarNavigationHandlers: function(){
        let topBarNavButtons = $('#gf-topbar-menu > .menu-nav > .menu-item > a').slice(0,4)
        if(!topBarNavButtons.first().hasClass("processed")){
          if(topBarNavButtons.length > 0){
            topBarNavButtons.each((i,el)=>{
              if(!$(el).hasClass('processed')){
                $(el).addClass('processed')
                $(el).on('click', function(e){
                  if(!$(el).hasClass("selected")){
                    Gofast.addLoading();
                  }
                $('.essentialHeader a.btn-clean').removeClass('selected')

                  if($(el).attr('id') == "topbarNavFileBrowserButton" || $(el).attr("id") == "topbarNavLogoButton"){
                    
                    if(Gofast.ITHit.currentPath == "/alfresco/webdav/Sites"){
                      Gofast.ITHit.currentPath += "/_"+Gofast.get("user").name
                    }

                    var splittedPath = Gofast.ITHit.currentPath.split("/")
                    var lastLocation = splittedPath[splittedPath.length-1]
                    var isFolder = false;
                    if(!lastLocation.startsWith("_")){
                      isFolder = true;
                    }
                    var currentSpacePath = Gofast.ITHit.getSpacePath(Gofast.ITHit.currentPath)
                    $.get(location.origin + "/ajax/getnidfromhref?href="+currentSpacePath).done((nid)=>{
                      if(nid == ""){
                        nid = Gofast._settings.gofast_ajax_file_browser.private_space_nid;
                      }
                      let path = Gofast.ITHit.currentPath;
                      if(path.substr(0, 16) === "/alfresco/webdav"){
                        path = path.substring(16, path.length);
                      }
                      history.pushState({}, "", "/node/"+nid+"?path="+path+"#ogdocuments");
                      if(isFolder){
                        nid = Gofast.ITHit.currentPath;
                      }
                    if($('.mainContent.fullScreen').length == 0){
                      $.get('/essential/get_node_content_part/pageContent/0').done((content)=>{
                          $("#gofast_over_content").remove()
                          $("#content-main-container").prepend(content)
                          $(el).addClass('selected')
                          Gofast.Essential.showFileBrowserLayer({nid: nid,hash: "#ogdocuments",isFolder: isFolder,showOnlyLayer: true})
                        })
                      } else {
                        $(el).addClass('selected')
                        Gofast.Essential.showFileBrowserLayer({nid: nid,hash: "#ogdocuments",isFolder: isFolder, showOnlyLayer : true})
                      }
                    })

                  } else if ($(el).attr('id') == "topbarNavActivityFeedButton" && !$("#topbarNavActivityFeedButton").hasClass("selected")){                   
                    if($('.mainContent.fullScreen').length == 0){
                      $.get('/essential/get_node_content_part/pageContent/0').done((content)=>{
                        $("#gofast_over_content").remove()
                        $("#content-main-container").prepend(content)
                        $(el).addClass('selected')
                        Gofast.Essential.showActivityFeedLayer()
                      })
                    } else {
                      $(el).addClass('selected')
                      Gofast.Essential.showActivityFeedLayer()
                    }

                  } else if ($(el).attr('id') == "topbarNavDashboardButton"){
                    if($('.mainContent.fullScreen').length == 0){
                      $.get('/essential/get_node_content_part/pageContent/0').done((content)=>{
                        $("#gofast_over_content").remove()
                        $("#content-main-container").prepend(content)
                        $(el).addClass('selected')
                        Gofast.Essential.showDashboardLayer()
                      })
                    } else {
                      $(el).addClass('selected')
                      Gofast.Essential.showDashboardLayer()
                    }
                  }
                  Gofast.removeLoading();
                })
              }
            })
          }
          
          //Handle click on logo in Essential
          $("#topbarNavLogoButton").click(function(e){
            e.preventDefault();
            e.stopPropagation();
            
            $("#topbarNavFileBrowserButton").click();
          });
        }
    },
    /*
    *  Display the search results in the layer
    */
    displaySearch: function(el){
      // Get the value of the href to execute the request
      let href = $(el).attr("href");
      // Execute the request
      $.get(href).done((content)=>{
        if($('#searchPageLayer').length == 0){
          if($('#activityFeedLayer').length > 0){
            $('#activityFeedLayer').remove()
          }
          $('#fileBrowserLayer').clone().appendTo($('#fileBrowserLayer').parent()).html(content).attr('id','searchPageLayer')
        } else {
          $('#searchPageLayer').hide();
          $("#searchPageLayer").html(content)
        }
        $('#fileBrowserLayer').removeClass('d-flex').addClass('d-none')
        $('#searchPageLayer > #kt_content .gofast-content').removeClass('gofast-content')
        $('#searchPageLayer').removeClass('d-none').addClass('d-flex')
        $('#searchPageLayer > #kt_content').addClass('px-0')
        $('#searchPageLayer > #kt_content .mainContent').addClass('px-0 py-0')
        Gofast.ITHit.tree.cancelSelectedNode()
        Drupal.attachBehaviors();
        $('#searchPageLayer').show();
      })
    },
    /*
    * Handle search pagination
    */
    searchHandlerPaginate: function(){
      if(!$('#gofastSearchResultsContent').hasClass('processed')){
        $('#gofastSearchResultsContent').addClass('processed');
        // When trigger pager, change only the layer
        $('#gofastSearchResultsContent .card-footer .align-items-center ul li a.btn').click(function(event){
          event.preventDefault();
          event.stopPropagation();
          
          Gofast.Essential.displaySearch(this);
        });
        
        $('#block-apachesolr-search-sort ul .btn-group li a').click(function(event){
          event.preventDefault();
          event.stopPropagation();
          
          Gofast.Essential.displaySearch(this);
        });
      }
    },
    showActivityFeedLayer: async function(){
      history.pushState({}, "", "/activity");
      Gofast.Essential.removeAllNodeLayers(true)
      await Gofast.Essential.showFileBrowserLayer({onlyLoad : true});
      if($('#activityFeedLayer').length){
        return;
      }

      $.post(location.origin+"/activity", {ajax: true}).done((content)=>{
        $('.GofastNodeOg__container > .card-body').first().removeClass('d-flex').addClass('d-none')
        if ($("#activityFeedLayer").length) {
          $("#activityFeedLayer").html(content);
        } else {
          $("<div id='activityFeedLayer' class='card-body h-100'>").html(content).appendTo(".GofastNodeOg__container")
        }
        if (Gofast.ITHit.tree) {
          Gofast.ITHit.tree.cancelSelectedNode()
        }
        // document.title = Drupal.settings.site_name || "GoFAST";
      })
    },
    showDashboardLayer: function(){
      if($('.gofastDashboard').length){
        return;
      }
      $.get('/essential/get_node_content_part/dashboard/0').done((content)=>{
        let parentEl = $("#kt_content").parent()
        $("#kt_content").remove();
        parentEl.prepend(content)
        if (Gofast.ITHit.tree) {
          Gofast.ITHit.tree.cancelSelectedNode()
        }
        // document.title = Drupal.settings.site_name || "GoFAST";
        history.pushState({}, "", "/dashboard");
        Gofast.removeLoading()
      })
    },
    showArticleLayer: function(nid = false){
      const articleNid = nid || Gofast.get("node").id;
      $.get('/essential/get_node_page/'+articleNid+"/true").done((result)=>{
        if($("#wikiPageLayer").length == 0){
          Gofast.Essential.removeAllNodeLayers(true)
          $('#fileBrowserLayer').clone().attr('id','wikiPageLayer').appendTo($('#fileBrowserLayer').parent())
        }
        $("#wikiPageLayer").html(result)
        // document.title = Gofast.get("node").title;
        Gofast.removeLoading();
        
        $('#fileBrowserLayer').first().removeClass('d-flex').addClass('d-none')
        $('#wikiPageLayer > #kt_content .gofast-content').removeClass('gofast-content')
        $('#wikiPageLayer').removeClass('d-none').addClass('d-flex')
        Drupal.attachBehaviors()
        
        $("#nav_mobile_file_browser_wiki_container").click();

        Drupal.settings.gofast_selected_book = Gofast.get("node").id;
        Gofast.selectCurrentWikiArticle();
      })
    },
    showForumLayer: function(nid){
      $('.essentialHeader a.btn-clean').removeClass('selected')
      $("#topbarNavFileBrowserButton").addClass("selected")

      Gofast.Essential.removeAllNodeLayers(true);
      if($("#forumPageLayer").length > 0){
        $("#forumPageLayer").remove()
      }
      $.get('/essential/get_node/'+nid).done((result)=>{
        var node = Gofast.get("node")
        let jsonData = JSON.parse(result)
        if (node == false || node.id != jsonData.id){
          Gofast.set("node", jsonData);
        }
        $.get('/essential/get_node_content_part/forum/'+nid).done((result)=>{
          if($("#forumPageLayer").length == 0){
            $('#fileBrowserLayer').clone().attr('id','forumPageLayer').appendTo($('#fileBrowserLayer').parent())
          }
          $("#forumPageLayer").html(result)
          // document.title = Gofast.get("node").title;
          Gofast.removeLoading();
          
          $('#fileBrowserLayer').first().removeClass('d-flex').addClass('d-none')
          $('#forumPageLayer > #kt_content .gofast-content').removeClass('gofast-content')
          $('#forumPageLayer').removeClass('d-none').addClass('d-flex')
          Drupal.attachBehaviors()
          Gofast.loadcomments(nid)
          Gofast.selectCurrentForum(nid)

          $("#nav_mobile_file_browser_forum_container").click();
          const loadForumListInterval = setInterval(() => {
            var forumListArrow = $("a[href*='"+nid+"#comment-init']").parent().siblings(".forum-explorer-element-seechild").find("i");
            if(forumListArrow.length > 0){
              clearInterval(loadForumListInterval)
              if(forumListArrow.hasClass("ki-bold-arrow-next")){
                forumListArrow.click()
              }
            }
          }, 20)
        })
      })
    },
    removeAllNodeLayers: function(alsoRemovePages = false) {
      const excludedLayers = ["#fileBrowserLayer"];
      if (!alsoRemovePages) {
        excludedLayers.push(...["#activityFeedLayer", "#searchPageLayer", ".gofastDashboard", "#wikiPageLayer", "#forumPageLayer"]);
      }
      $('#kt_content .GofastNodeOg__container > div:not(' +  excludedLayers.join(", ") + ')').remove();
      if($(".gofastHighlightedForum").length){
        $(".gofastHighlightedForum").removeClass("gofastHighlightedForum bg-primary text-white rounded");
      }
      Gofast.unselectWikiArticle()
    },
    showFileBrowserLayer: async function({nid = false, onlyLoad = false, hash = "#ogdocuments", isFolder = false, showOnlyLayer =  false} = {}){
      Gofast.Essential.closeFullPageLayer()
      // If the file browser is already loaded, don't load it again
      if($('.mainContent.GofastNodeOg').length == 0){
        // Make the file browser load but hidden to prevent having wrong layer displayed
        await Gofast.Essential.getHiddenFileBrowserContent().then((fileBrowserContent) => {
            $('.mainContent.fullScreen').html("")
            $('.mainContent.fullScreen').html(fileBrowserContent)
          
            $('#essentialFileBrowserHistory').attr('style', 'display:none!important;')
            Gofast.removeLoading()
        
        });
      }
      if (onlyLoad) {
        return;
      }
      Gofast.Essential.unHideFileBrowserLayerChildren();
      /**
       * If the only action required is to show the layer without any other 
       *operation unhide the hidden elements of the file browser and return
      */
      if($('.mainContent.GofastNodeOg').length >  0 && showOnlyLayer){
        return;
      }

      // normally all layers have been erased by the load, this call is in case something still remains
      Gofast.Essential.removeAllNodeLayers(true);
      $('#fileBrowserLayer').addClass('d-flex').removeClass('d-none');
      Gofast.ITHit.reset_full_browser_size()

      // document.title = Drupal.settings.site_name || "GoFAST";

      if (nid) {
        if(isFolder){
          Gofast.ITHit.navigate(encodeURI(nid))
          if($("#gofastBrowserNavTabs a[href="+hash+"]").length){
            $("#gofastBrowserNavTabs a[href="+hash+"]").click()
          }
        } else {
          Gofast.Essential.navigateFileBrowser(nid, hash);
        }
      } else {
        Gofast.ITHit.tree.selectNode(Gofast.ITHit.tree.getNodeByParam("path", decodeURIComponent(Gofast.ITHit.currentPath)));
        Gofast.ITHit.navigate(decodeURIComponent(Gofast.ITHit.currentPath))
      }
      setTimeout(()=>{
        Gofast.removeLoading()
      },10)
    },
    /**
     * The unHideFileBrowserLayerChildren function is responsible for showing a hidden file browser layer.
     * This method first checks if the fileBrowserLayer is present in the DOM, and if so, it performs the following steps:
     * 
     * 1. Removes all other visible node layers by calling Gofast.Essential.removeAllNodeLayers(true).
     * 2. Removes the "d-none" class from the fileBrowserLayer and its child elements with the "d-none" class, making them visible.
     * 3. Modifies the style of "#essentialFileBrowserHistory" to show it by removing the "style" attribute and adding the "d-flex" class.
     * 
     * Additionally, the method utilizes the MutationObserver API to monitor changes in the visibility or class of the fileBrowserLayer.
     * The checkFileBrowserLayer function is used to remove other children of the ".GofastNodeOg__container" element, except the "#fileBrowserLayer" (e.g., search layers).
     * 
     * Note: This method should be called when there is a need to display the hidden file browser layer, and it ensures proper synchronization of the DOM.
     * 
   */
    unHideFileBrowserLayerChildren: function() {
      var fileBrowserLayer = $("#fileBrowserLayer");
      
      if (fileBrowserLayer.length > 0) {
        Gofast.Essential.removeAllNodeLayers(true);
        fileBrowserLayer.removeClass("d-none").addClass("d-flex").children(".d-none").removeClass("d-none");
        $("#essentialFileBrowserHistory").removeAttr('style').addClass('d-flex');
        Gofast.ITHit.reset_full_browser_size()
      }

      // Check if the child element with ID "fileBrowserLayer" is visible or doesn't have the "d-none" class
      function checkFileBrowserLayer() {
        if (!fileBrowserLayer.hasClass("d-none") || fileBrowserLayer.is(":visible")) {
          // Remove other children of "GofastNodeOg__container" eg:search layers
          $(".GofastNodeOg__container > :not(#fileBrowserLayer)").remove();
        }
        Gofast.removeLoading()
      }
      
      $(document).ready(function() {
        // Call the checkFileBrowserLayer function initially
        checkFileBrowserLayer();

        // Use MutationObserver to detect changes in the visibility or class of the child element
        var observer = new MutationObserver(function(mutations) {
          //:element change detected
          mutations.forEach(function(mutation) {
            if (mutation.target.id === "fileBrowserLayer") {
              checkFileBrowserLayer();
            }
          });
        });

        // Observe class changes in the file browser layer("#fileBrowserLayer")
        observer.observe(document.getElementById("fileBrowserLayer"), {
          attributes: true,
          attributeFilter: ["class"],
          attributeOldValue: true
        });
      });
    },
    setNodeObject: async function (nid, forceSet = false) {
      var node = Gofast.get("node");
      if (typeof node == "undefined" || forceSet) {
        await $.get('/essential/get_node/'+nid).done((result) => {
          let jsonData = JSON.parse(result)
          Gofast.set("node", jsonData);
        });
      }
    },
    // this space object is intended for spaces and folders and must be workable platform-scope (independently of ITHit)
    setSpaceObject: async function (path, forceSet = false) {
      var space = Gofast.get("space");
      if (typeof space != "string" || forceSet) {
        Gofast.set("space", path);
      }
    },
    navigateFileBrowser: function(nid, hash = "#ogdocuments", loadType = "backgroundNavigation"){
      // we force set the current node context to the target node
      Gofast.Essential.setNodeObject(nid, true);
      $.get("/essential/get_href_from_nid/"+nid).done((href) => {
        var fullHref = href;
        if (!href.startsWith("/alfresco/webdav")) {
          fullHref = "/alfresco/webdav" + href;
        }
        // the "backgroundNavigation" param will prevent navigation handler to force set the node context to the parent group
        // If loadType = "load" -> prevent history bar to duplicate the last location 
        Gofast.ITHit.navigate(fullHref, false, false, null, null, null, loadType)
      });
    },
    showSearchLayer: function(terms){
      if($(".essentialFileBrowser").length){ // Prevent navigating error if file browser is not loaded
        Gofast.ITHit.tree.cancelSelectedNode() // Make ztree appear without selecting a space
      }
      Gofast.addLoading();
      var requestParam = terms;
      //if the search string is empty make a filtered search on all
      if(terms.startsWith("?")){
        requestParam = "all"+requestParam
      }
      $.get('/essential/get_node_content_part/search/'+requestParam).done((content)=>{
        if($('#searchPageLayer').length == 0){
          Gofast.Essential.removeAllNodeLayers(true);
          $('.GofastNodeOg__container > .card-body').clone().appendTo($('.GofastNodeOg__container > .card-body').parent()).html(content).attr('id','searchPageLayer')
        } else {
          $("#searchPageLayer").html(content)
        }
        Gofast.removeLoading();
        // document.title = Drupal.settings.site_name || "GoFAST";
        $('.GofastNodeOg__container > .card-body').first().removeClass('d-flex').addClass('d-none')
        $('#searchPageLayer > #kt_content .gofast-content').removeClass('gofast-content')
        $('#searchPageLayer').removeClass('d-none').addClass('d-flex')
        $('#searchPageLayer > #kt_content').addClass('px-0')
        $('#searchPageLayer > #kt_content .mainContent').addClass('px-0 py-0')
        history.pushState({}, "", "/search/solr/"+terms)
        if (Gofast.ITHit.tree) {
          Gofast.ITHit.tree.cancelSelectedNode()
        }
        Drupal.attachBehaviors();
      })
    },
    goToNode: function(nid, type = "node", context = false, folderPath = "", search = ""){
      if (type != "node" && type != "folder") {
        // other entities e.g. user
        Gofast.processAjax("/" + type + "/" + nid);
        return;
      }
      if(type == "folder"){
        
        $('.essentialHeader a.btn-clean').removeClass('selected')
        $("#topbarNavFileBrowserButton").addClass("selected")
        Gofast.Essential.showFileBrowserLayer({nid: folderPath,onlyLoad: false,hash: "#ogdocuments",isFolder: true});
        return;
      }
      $.get('/essential/get_node/'+nid).done(async (node)=>{
        let jsonData = JSON.parse(node)
        Gofast.set("node", jsonData);
        const nodeType = Gofast.get("node").type;
        const fullNodeTypes = ["alfresco_item", "webform"];
        const layeredNodeTypes = ["article", "forum"];
        const supportedGroupTypes = ["private_space", "public", "extranet", "organisation", "group"];
        Gofast.Essential.removeAllNodeLayers();
        if(fullNodeTypes.includes(nodeType)){
          Gofast.addLoading();
          history.pushState({}, "", "/node/" + nid + search);
          if(folderPath == ""){
            // Don't navigate if we are in a case where we don't want to go to the file browser (e.g. opening a file from the dashboard)
            if($(".essentialFileBrowser").length && context){
              $.get("/essential/get_node_first_location/" +  nid).done((path)=>{
                let searchQueryString = Gofast.ITHit.buildSearchQueryStringWithPath(path)
                history.pushState({}, "", "/node/" + nid + searchQueryString + "#ogdocuments")
                Gofast.ITHit.navigate(path, false, false, null, null, null, "backgroundNavigation");
              })
            }
          } else {
            Gofast.ITHit.navigate(folderPath, false, false, null, null, null, "backgroundNavigation");
          }
          $.get('/essential/get_node_page/'+nid+"/"+context).done((result) => {
            var $backgroundContent = $("#gofastContainer > div:not('#nodeContainer')")
            $backgroundContent.removeClass("d-flex").addClass("d-none");
            $backgroundContent.find("[id=document__infotab]").attr("id", "document__infotab_disabled");
            var gofastContainerEl = $("#gofastContainer");
            // The #gofastContainer can be inside the .essentialFileBrowser (e.g. articleLayer), so be sure to take the good element
            if($(".essentialFileBrowser").length){
              gofastContainerEl = $("[id=gofastContainer]").filter(function(index){
                                      return $(this).find(".essentialFileBrowser").length
                                  })
            }
            if(gofastContainerEl.find("> #nodeContainer").length){
              gofastContainerEl.find("> #nodeContainer").remove()
            }
            gofastContainerEl.append(result);
            // document.title = Gofast.get("node").title;
            Gofast.removeLoading();
          });
        } else if (layeredNodeTypes.includes(nodeType)) {
          // Put nid in the url before showing file browser
          history.pushState({}, "", "/node/" + nid + search);
          Gofast.addLoading();
          Gofast.Essential.closeFullPageLayer()
          if($("#gofast_file_browser_side_content").length == 0){
            await Gofast.Essential.showFileBrowserLayer({nid : nid});
          }
          const layerHandler = Gofast.Essential["show" + nodeType.charAt(0).toUpperCase() + nodeType.slice(1) + "Layer"];
          if (typeof layerHandler == "function") {
            layerHandler(nid);
          }
        } else if (supportedGroupTypes.includes(Gofast.get("node").type)) {
          // Put nid in the url before showing file browser
          history.pushState({}, "", "/node/" + nid + search);
          $('.essentialHeader a.btn-clean').removeClass('selected')
          await Gofast.Essential.showFileBrowserLayer({nid:nid, showOnlyLayer: false});
        } else {
          // other node types e.g. kanban
          Gofast.processAjax("/node/" + nid);
        }
      })
    },
    /*
    * Load file browser essential
    * TODO : Call to this function may be moved (In document template ?). Currently called in a behavior
    */
    loadFileBrowser: function(){
      if($(".essentialFileBrowser").length) {
        return;
      }
      let action = window.location.pathname.split("/")[3];
      if (action) {
        // we're navigating to a full page form: cancel
        return;
      }
      if(window.location.pathname.startsWith("/node/") && Gofast.get("node") != undefined && !$('#topbarNavFileBrowserButton').hasClass('selected') && !$("#topbarNavActivityFeedButton").hasClass("selected") && !$("#topbarNavDashboardButton").hasClass("selected")){ 
        if(Gofast.get("node").type != "alfresco_item" && Gofast.get("node").type != "webform" && Gofast.get("node").type != "article" && Gofast.get("node").type != "forum"){ 
          $('#topbarNavFileBrowserButton').addClass('selected') 
        } else if($(".gofastDashboard").length == 0 && (Gofast.get("node").type == "alfresco_item" || Gofast.get("node").type != "webform")){ 
          $('#topbarNavFileBrowserButton').addClass('selected') 
          if($("#mobile_file_browser_full_tree_container").length == 0){
            /**
             * This block represents a conditional check and a subsequent action to load file browser content into the DOM.
             * 
             * Condition:
             * This block is executed when the following conditions are met:
             * - The element with ID "fileBrowserLayer" does not have the class "processed".
             * - There is no element with the class "fileBrowserLayerContainer".
             * 
             * Action:
             * Depending on the condition and the current URL's search parameter, the following steps are performed:
             * 
             * 1. If the current window's URL search is empty:
             *    - A GET request is made to retrieve the initial location/path of the node using "/essential/get_node_first_location/" API.
             *    - The retrieved path is used to set a space object using Gofast.Essential.setSpaceObject().
             *    - The path is modified to remove the "/alfresco/webdav" prefix and added to the URL as a query parameter.
             *    - The browser history is updated with the new URL, reflecting the changes in the address bar.
             *    - If the "fileBrowserLayer" is still unprocessed and there is no "fileBrowserLayerContainer":
             *      - Gofast.Essential.getFileBrowserContent() is called to fetch file browser content.
             *      - The content is cloned to "#kt_content_space" and its mainContent.fullScreen is populated with the fetched file browser content.
             *      - "#kt_content_space" is then hidden by adding the "d-none" class.
             * 
             * 2. If the current window's URL search is not empty:
             *    - Gofast.Essential.getFileBrowserContent() is called to fetch file browser content.
             *    - The content is cloned to "#kt_content_space" and its mainContent.fullScreen is populated with the fetched file browser content.
             *    - "#kt_content_space" is then hidden by adding the "d-none" class.
             * 
             * Overall, this code block handles the dynamic loading of file browser content into the DOM based on certain conditions, ensuring the correct state of the file browser layer for the user interface.
             * 
             */
            if (!$('#fileBrowserLayer').hasClass('processed') && !$('.fileBrowserLayerContainer').length) {
              if(window.location.search == ""){
                $.get("/essential/get_node_first_location/" + Gofast.get("node").id).done((path)=>{
                  Gofast.Essential.setSpaceObject(path, true);
                  path = path.replace("/alfresco/webdav", "");
                  history.pushState({}, "", "/node/" + Gofast.get("node").id + "?path=" + encodeURI(path) + window.location.hash)
                    if (!$('#fileBrowserLayer').hasClass('processed') && !$('.fileBrowserLayerContainer').length) {
                      Gofast.Essential.getFileBrowserContent().then((fileBrowserContent) => {
                      $("#gofastContainer").prepend(fileBrowserContent)
                      $(".essentialFileBrowser").removeClass("d-flex").addClass("d-none")
                      })
                    }
                  })
              } else {
                Gofast.Essential.getFileBrowserContent().then((fileBrowserContent)=>{
                  $("#gofastContainer").prepend(fileBrowserContent)
                  $(".essentialFileBrowser").removeClass("d-flex").addClass("d-none")
                })
              }
            }
          }
        }
      }
    },
    /*
     * Reduce Essential SideBar
    */
    reduceSideBar: function(el){
      let sideBarEl = $(".side-content-container-essential").has(el);
      // Selects the child element .card inside of the parent element #id > .sideContent and changes its left property to 98%
      if(sideBarEl.length){
        sideBarEl.find('.card-header').css('overflow', 'hidden');
        sideBarEl.animate({width: 68 + 'px'});
        // Remove margin-right
        sideBarEl.css('margin-right', '0px');
      }
      el.find(".fa-chevron-right").removeClass("fa-chevron-right").addClass("fa-chevron-left")
      // Remove the class 'expand' from the element with the given id
      el.removeClass('expand')
    },
    /*
     * Expand Essential SideBar
    */
    expandSideBar: function(el){
      let sideBarEl = $(".side-content-container-essential").has(el);
      // Selects the child element card inside of the parent element #id > .sideContent and changes its left property to 0
      if(sideBarEl.length){
        sideBarEl.find('.card-header').css('overflow', "");
        // Make search filter side panel smaller
        if(el.attr("id") == "filterSideButton"){
          if(Gofast.isTablet() && !Gofast.isMobile()){
            sideBarEl.animate({width: 320 + 'px'});
            sideBarEl.css('margin-right', '0px'); 
          }else{
            sideBarEl.animate({width: 320 + 'px'});
            sideBarEl.css('margin-right', '68px');
          }
        } else {
          // Add margin-right
          if(Gofast.isTablet() && !Gofast.isMobile()){
            sideBarEl.animate({width: 400 + 'px'});
            sideBarEl.css('margin-right', '0px'); 
          }else{
            sideBarEl.animate({width: 568 + 'px'});
            sideBarEl.css('margin-right', '68px');
          }
        }
      }
      el.find(".fa-chevron-left").removeClass("fa-chevron-left").addClass("fa-chevron-right")
      // Add the class 'expand' to the element with the given id
      el.addClass('expand')
    },
    /*
    * Setup essential sidebar
    */
    setupSideBar: function(){
      // Interval to check for the existence of the fullscreen toggle button
      const fullscreenButtonInterval = setInterval(()=>{
          // If the fullscreen toggle button exists, clear the interval
          if($('#toggle-fitscreen').length > 0){
              clearInterval(fullscreenButtonInterval)
          }
      }, 50)

      $("[id=metadataSideButton]").each((i,e)=>{
        // Check if the metadata side button has not been processed yet
        if(!$(e).hasClass('processed')){
            // Add the class 'processed' to the metadata side button to prevent multiple event listeners from being added
            $(e).addClass('processed')
          // Add a click event listener to the metadata side button
          $(e).on('click', function(){
            // Check if the metadata side button has the class 'expand'
            if($(e).hasClass('expand')) {
                // If it does, call the reduceSidebar function and pass in the id "metadataSideButton"
                Gofast.Essential.reduceSideBar($(e));
            } else {
                // If it does not, call the expandSidebar function and pass in the id "metadataSideButton"
                Gofast.Essential.expandSideBar($(e));
            }
          })
        }
      })
      // Check if the search filter side button has not been processed yet
      if(!$('#filterSideButton').hasClass('processed')){
        // Add the class 'processed' to the search filter side button to prevent multiple event listeners from being added
        $('#filterSideButton').addClass('processed')
        
        // Set the default state of the filter side panel
        if($("#filterSideButton").hasClass('expand')) {
          Gofast.Essential.expandSideBar($("#filterSideButton"));
          $("#gofastSearchResultsFilter > .card-custom").removeClass("d-none");
        } else {
          Gofast.Essential.reduceSideBar($("#filterSideButton"));
          $("#gofastSearchResultsFilter > .card-custom").addClass("d-none");
        }
      }
    },
    /*
     * Expand / Reduce search filter side menu
     */
    toggleSearchFilterTab: function() {
      // Check if the metadata side button has the class 'expand'
      if($('#filterSideButton').hasClass('expand')) {
          // If it does, call the reduceSidebar function and pass in the id "metadataSideButton"
          Gofast.Essential.reduceSideBar($("#filterSideButton"));
          
          //Hide the block content
          $("#gofastSearchResultsFilter > .card-custom").addClass("d-none");
      } else {
          // If it does not, call the expandSidebar function and pass in the id "metadataSideButton"
          Gofast.Essential.expandSideBar($("#filterSideButton"));
          
          //Display the block content
          $("#gofastSearchResultsFilter > .card-custom").removeClass("d-none");
      }
    },
    /*
     *  Show Wiki layer from URL navigation
    */
    showWikiLayer: function(){
      if(!$('.essentialHeader a.btn-clean').hasClass("selected") && !$("#topbarNavFileBrowserButton").hasClass("selected") && Gofast.get("node") != undefined && Gofast.get("node").type == "article" && location.pathname.startsWith("/node/")){
        $('.essentialHeader a.btn-clean').removeClass('selected')
        $("#topbarNavFileBrowserButton").addClass("selected")
        if($("#gofast_file_browser_side_content").length == 0){
          $.get('/essential/get_node_content_part/pageContent/0').done((content)=>{
            $("#gofast_over_content").remove()
            $("#content-main-container").prepend(content)
            /**
             * This block conditionally loads file browser content into the DOM based on 
             * specific conditions in the absence of the "processed" class in "fileBrowserLayer"
             * and the non-existence of "fileBrowserLayerContainer." and unhides the fileBrowser as this
             * shows that the filebrowser chil elements have not yet been rendered.
             */
            if (!$('#fileBrowserLayer').hasClass('processed') && !$('.fileBrowserLayerContainer').length) {
              Gofast.Essential.getFileBrowserContent().then((fileBrowserContent) => {
                $('.mainContent.fullScreen').html("")
                $('.mainContent.fullScreen').html(fileBrowserContent)
                Gofast.Essential.unHideFileBrowserLayerChildren()
                Gofast.Essential.showArticleLayer()
              })
            }
          })
        } else {
          Gofast.Essential.showArticleLayer()
        }
      }
    },
    /*
     *  Show Forum page from URL navigation
    */
    showForumPage: function(){
      if(!$('.essentialHeader a.btn-clean').hasClass("selected") && !$("#topbarNavFileBrowserButton").hasClass("selected") && Gofast.get("node") != undefined && Gofast.get("node").type == "forum" && location.pathname.startsWith("/node/")){
        $('.essentialHeader a.btn-clean').removeClass('selected')
        $("#topbarNavFileBrowserButton").addClass("selected")

        if($("#gofast_file_browser_side_content").length == 0){
          $.get('/essential/get_node_content_part/pageContent/0').done((content)=>{
            $("#gofast_over_content").remove()
            $("#content-main-container").prepend(content)
             /**
             * This block conditionally loads file browser content into the DOM based on 
             * specific conditions in the absence of the "processed" class in "fileBrowserLayer"
             * and the non-existence of "fileBrowserLayerContainer." and unhides the fileBrowser as this
             * shows that the filebrowser chil elements have not yet been rendered.
             */
            if (!$('#fileBrowserLayer').hasClass('processed') && !$('.fileBrowserLayerContainer').length) {
              Gofast.Essential.getFileBrowserContent().then((fileBrowserContent)=>{
                $('.mainContent.fullScreen').html("")
                $('.mainContent.fullScreen').html(fileBrowserContent)
                Gofast.Essential.showForumLayer(Gofast.get("node").id)
                Gofast.Essential.unHideFileBrowserLayerChildren()
              })
            }
          })
        } else {
          Gofast.Essential.showForumLayer(Gofast.get("node").id)
        }
      }
    },
    /*
     *  Show Activity feed from URL navigation
    */
    showActivityFeed: function(){
      if(window.location.pathname == "/activity"){
        $('.essentialHeader a.btn-clean').removeClass('selected')
        $("#topbarNavActivityFeedButton").addClass("selected")
        
        if($('.mainContent.fullScreen').length == 0){
          $.get('/essential/get_node_content_part/pageContent/0').done((content)=>{
            $("#gofast_over_content").remove()
            $("#content-main-container").prepend(content)
            Gofast.Essential.showActivityFeedLayer()
          })
        } else {
          Gofast.Essential.showActivityFeedLayer()
        }
      }
    },
    /*
     *  Show Dashboard from URL navigation
    */
    showDashboard: function(){
      if(window.location.pathname == "/dashboard"){

        $('.essentialHeader a.btn-clean').removeClass('selected')
        $("#topbarNavDashboardButton").addClass("selected")

        if($('.mainContent.fullScreen').length == 0){
          $.get('/essential/get_node_content_part/pageContent/0').done((content)=>{
            $("#gofast_over_content").remove()
            $("#content-main-container").prepend(content)
            Gofast.Essential.showDashboardLayer()
          })
        } else {
          Gofast.Essential.showDashboardLayer()
        }
      }
    },
    /*
     *  Show Search page from URL navigation
    */
    showSearchPage: function(){
      if(window.location.pathname.startsWith("/search/solr")){
        $("#search-block-form").addClass("processed");
        $('.essentialHeader a.btn-clean').removeClass('selected')
        $("#topbarNavFileBrowserButton").addClass("selected");

        var term = window.location.pathname.split("/")[3];
        var params = window.location.search;
        var requestParam = term + params;
        
        if(term == ""){
          requestParam = "all"+requestParam;
        }
        $.get('/essential/get_node_content_part/pageContent/0').done((content)=>{
          $("#gofast_over_content").remove()
          $("#content-main-container").prepend(content)
          Gofast.addLoading();
          /**
           * Fetches and displays hidden file browser content as search results.
           * 
           * This following block fetches hidden file browser content using Gofast.Essential.getHiddenFileBrowserContent(),
           * and then populates the ".mainContent.fullScreen" element with the fetched content. It hides the "#essentialFileBrowserHistory"
           * element by adding an inline style to set its display to "none".
           * 
           * After that, it initiates a search request using $.get('/essential/get_node_content_part/search/'+requestParam),
           * where 'requestParam' is the search parameter. Upon receiving the search results, it performs the following actions:
           * 
           * 1. Clones the "#fileBrowserLayer" element, appends it to its parent, and assigns the fetched search content to the cloned element.
           * 2. Modifies the cloned element to create a new element with ID "searchPageLayer" and sets it as the new file browser layer.
           * 3. Hides the original "#fileBrowserLayer" by removing the "d-flex" class and adding the "d-none" class.
           * 4. Hides the original "#essentialFileBrowserHistory" element in a similar manner.
           * 5. Performs specific modifications to the "searchPageLayer" and its child elements, adjusting classes and styling.
           * 6. Cancels the selected node in the file browser tree using Gofast.ITHit.tree.cancelSelectedNode().
           * 7. Removes loading indicators using Gofast.removeLoading().
           * 
           * This block handles the display of search results in the file browser layer and ensures proper synchronization of the DOM.
           * Note: The variable "requestParam" should be set with the appropriate search parameter before calling this function.
           */
           Gofast.Essential.getHiddenFileBrowserContent().then((fileBrowserContent)=>{
            $('.mainContent.fullScreen').html("")
            $('.mainContent.fullScreen').html(fileBrowserContent)
            Gofast.ITHit.navigate("/alfresco/webdav/Sites",false, false, null, null, null, "backgroundNavigation"); // Make ztree appear without selecting a space
            $('#essentialFileBrowserHistory').attr('style', 'display:none!important;')
            Gofast.ITHit.tree.cancelSelectedNode()
            $.get('/essential/get_node_content_part/search/'+requestParam).done((content)=>{
              $('#fileBrowserLayer').clone().appendTo($('#fileBrowserLayer').parent()).html(content).attr('id','searchPageLayer')
              $('#fileBrowserLayer').first().removeClass('d-flex').addClass('d-none')
              $('#essentialFileBrowserHistory').first().removeClass('d-flex').addClass('d-none')
              $('#searchPageLayer > #kt_content .gofast-content').removeClass('gofast-content')
              $('#searchPageLayer').removeClass('d-none').addClass('d-flex')
              $('#searchPageLayer > #kt_content').addClass('px-0')
              $('#searchPageLayer > #kt_content .mainContent').addClass('px-0 py-0')
              Gofast.ITHit.tree.cancelSelectedNode()
              Gofast.removeLoading()
            })
          })
        })
      }
    },
    /*
    * If needed, trigger the document tab to show the explorer to the user
    */
    triggerDocumentTab: function(){
      if($('.essentialNavTab.active:visible').length == 0 && $('.essentialNavTab:visible').length > 0) {
        $("#ogtab_documents:visible").click()
      }
    },
    /*
     *  Process all the logic in a document layer
    */
    handleDocumentPage: function(type, status){
      $('#node-previous-content-button:not(.noContext):not(.processed)').addClass('processed').on('click', () => {
        // let newTitle = window.sessionStorage.getItem('previousNodeTitle_' + Gofast.get('user').uid);
        // document.title = newTitle;
        
        Gofast.Essential.changeDocumentContent('previous', type, status)
      })
      

      $('#node-next-content-button:not(.noContext):not(.processed)').addClass('processed').on('click', () => {
          // let newTitle = window.sessionStorage.getItem('nextNodeTitle_' + Gofast.get('user').uid);
          // document.title = newTitle;
          
          Gofast.Essential.changeDocumentContent('next', type, status)
      })

      $('#node-exit-button:not(.processed)').addClass('processed').on('click', function(e) {
        //Gofast.Essential.unHideFileBrowserLayerChildren()
        Gofast.Essential.closeFullPageLayer()
          if(e.originalEvent != undefined && e.originalEvent.isTrusted){
              if($(".gofastDashboard").length > 0){
                  history.pushState({}, "", "/dashboard");
              } else if($("#activity-feed").length > 0) {
                  history.pushState({}, "", "/activity");
              } else {
                  const urlParam = new URLSearchParams(window.location.search);
                  var pathParam = urlParam.get("path");
                  if(pathParam != null){
                      $.get(location.origin + '/ajax/getnidfromhref', { href: pathParam, essential_close:true }, function (nid) {
                          history.pushState({}, "", "/node/" + nid + "?path=" + pathParam + location.hash);
                          $.get('/essential/get_node/' + nid).done((result) => {
                              
                              var node = Gofast.get('node');
                              let jsonData = JSON.parse(result)
                              if (typeof node !== 'undefined') {
                                  node.id = jsonData.id
                                  node.title = jsonData.title
                                  node.type = jsonData.type
                              } else {
                                Gofast.set("node", jsonData);
                              }
                        //  Gofast.ITHit.navigate(pathParam);
                        })
                      })
                    } else if(typeof Gofast.get("space") == "string"){
                      $.get(location.origin + '/ajax/getnidfromhref', { href: Gofast.get("space") }).done((nid) => {
                        history.pushState({}, "", "/node/" + nid + "?path=" + Gofast.get("space").replace("/alfresco/webdav", "") + location.hash);
                      })
                    }
              }
          }
      })
      $("#node-full-screen-button:not(.processed)").addClass('processed').on('click', function(){
        $('#node-normal-screen-button').parents("#fullscreenNavigationButtons").css("display", "flex");
        $("#gofastContainer").addClass("active");
        $("#nodeContainer").css("height", "100%");
        $("#nodeContainer").children("div.mainContent").css("padding-bottom", "0");
        $('div.side-content-container-essential').css("display", "none");
        $('#kt_content > div.gofast-content.h-100 > div > div > div.mainContent > div.card.card-custom.card-stretch.isStackedLayer > div.card-header.min-h-50px.flex-nowrap.px-3').css("display", "none");
        $('span#block-gofast-cmis-gofast-cmis-fast-upload-file').css("display", "none");
      });
      $('a[id="node-normal-screen-button"]:not(.processed)').addClass('processed').on('click', function(){
        $("#gofastContainer").removeClass("active");
        $("#nodeContainer").css("height", "inherit");
        $("#nodeContainer").children("div.mainContent").css("padding-bottom", "1rem");
        $('div.side-content-container-essential').css("display", "block");
        $('#kt_content > div.gofast-content.h-100 > div > div > div.mainContent > div.card.card-custom.card-stretch.isStackedLayer > div.card-header.min-h-50px.flex-nowrap.px-3').css("display", "flex");
        $("#node-normal-screen-button").parents("#fullscreenNavigationButtons").css("display", "none");
        $('span#block-gofast-cmis-gofast-cmis-fast-upload-file').css("display", "block");
        return false;
      });
    },
    /*
     * Load the essential breadcrumb in a document layer
    */
    loadBreadcrumb: function(nid){
      //Locations are successfully checked, process the breadcrumb, the right block and the menu
      var options = {"show_title": true};
      options.alt_theme = "gofast_document_breadcrumb";
      $.get(location.origin + "/gofast/node-breadcrumb/" + nid + "?options=" + JSON.stringify(options), function(breadcrumb) {
          
          Gofast.breadcrumb_gid = nid;
          //update the breadcrumb
          $("#gofastMenuHeaderSubheader > .breadcrumb-gofast").replaceWith(breadcrumb);
          $("#gofastMenuHeaderSubheader > .breadcrumb-gofast:not('.breadcrumb-gofast-full')").addClass("processed");
      });
    },
    /*
     * Change document content when navigating in the document layer
     * @todo refactor this: 1. storeNodeTitle should be external to this, 2. we can already have the nids insead of the path in the storage item which make it possible to
     * 3. avoid a lot of getnidfromhref calls
    */
    changeDocumentContent(event, type, status){
      var allContentsObj = {}
      
      if (window.sessionStorage.getItem("allContents" + Gofast.get('user').uid)) {
        allContentsObj = window.sessionStorage.getItem("allContents" + Gofast.get('user').uid);
        allContentsObj = JSON.parse(allContentsObj)
        allContentsHref = Object.keys(allContentsObj)

        var nodeTitle = decodeURIComponent(Gofast.get("node").title);

        const storeNodeTitle = (nodeHref, side, nid) => {
          if(nid != null){
            fetchNodeTitle(nid, side)
            
          } else {
            $.get(`${location.origin}/ajax/getnidfromhref?href=${nodeHref}`).done((nid) => {
              fetchNodeTitle(nid, side)
            });
          }
        };
        const fetchNodeTitle = (nid, side) => {
          $.get(`/essential/get_node/${nid}`).done((result) => {
              const jsonData = JSON.parse(result);
              const nodeTitle = jsonData.title.slice(0, jsonData.title.lastIndexOf("."))
              window.sessionStorage.setItem(`${side}NodeTitle_${Gofast.get('user').uid}`, nodeTitle);
          });
        }

        Object.entries(allContentsObj).forEach((entry, i) => {
          const [href, nodeId] = entry;
            if (decodeURIComponent(href.split('/').last()) == nodeTitle) {
              if(i == 0){
                $("a[id=node-previous-content-button]").removeClass("btn-primary").addClass("noContext") 
              }
              if(i == allContentsHref.length-1){
                $("a[id=node-next-content-button]").removeClass("btn-primary").addClass("noContext") 

              }
                let href = ""

                let previousNodeHref = "";
                let nextNodeHref = "";

                if (event == "previous") {
                  if($("a[id=node-next-content-button]").hasClass("noContext")){ 
                    $("a[id=node-next-content-button]").removeClass("noContext").addClass("btn-primary") 
                  }
                    nextNodeHref = allContentsHref[i];
                    if (i == 0) {
                        href = allContentsHref[allContentsHref.length - 1]
                        previousNodeHref = allContentsHref[allContentsHref.length - 2]
                    } else if (i == 1) {
                      //Remove this line to be able to navigate in a loop in the space
                      $("a[id=node-previous-content-button]").removeClass("btn-primary").addClass("noContext") 

                        previousNodeHref = allContentsHref[allContentsHref.length - 1]
                        href = allContentsHref[i - 1]
                    } else {
                        href = allContentsHref[i - 1]
                        previousNodeHref = allContentsHref[i - 2]
                    }

                } else if (event == "next") {

                  if($("a[id=node-previous-content-button]").hasClass("noContext")){ 
                    $("a[id=node-previous-content-button]").removeClass("noContext").addClass("btn-primary") 
                  }

                    previousNodeHref = allContentsHref[i];

                    if (i == allContentsHref.length - 1) {
                        href = allContentsHref[0]
                        nextNodeHref = allContentsHref[1]
                    } else if (i == allContentsHref.length - 2) {
                      //Remove this line to be able to navigate in a loop in the space
                      $("a[id=node-next-content-button]").removeClass("btn-primary").addClass("noContext") 
                      
                        nextNodeHref = allContentsHref[0]
                        href = allContentsHref[allContentsHref.length-1]
                    } else {
                        href = allContentsHref[i + 1]
                        nextNodeHref = allContentsHref[i + 2]
                    }

                } else if (event == "load") {
                   if (Gofast._settings.isEssential && !Gofast._settings.isMobileDevice){
                      // document.title = decodeURIComponent(Gofast.get("node")?.title);
                   }
                    if (i == allContentsHref.length - 1) {
                        nextNodeHref = allContentsHref[0]
                    } else {
                        nextNodeHref = allContentsHref[i + 1]
                    }
                    if (i == 0) {
                        previousNodeHref = allContentsHref[allContentsHref.length - 1]
                    } else {
                        previousNodeHref = allContentsHref[i - 1]
                    }
                }

                storeNodeTitle(previousNodeHref, "previous", allContentsObj[previousNodeHref]);
                // Set title hover for the previous document
                let newTitlePrevious = window.sessionStorage.getItem('previousNodeTitle_' + Gofast.get('user').uid);
                $("#node-previous-content-button").attr('title', newTitlePrevious);
                
                storeNodeTitle(nextNodeHref, "next", allContentsObj[nextNodeHref]);
                // Set title hover for the next document
                let newTitleNext = window.sessionStorage.getItem('nextNodeTitle_' + Gofast.get('user').uid);
                $("#node-next-content-button").attr('title', newTitleNext);

                if (event != "load") {
                
                    
                    $.get(location.origin + '/ajax/getnidfromhref?href=' + href).done((nid) => {
                        
                        Gofast.Essential.loadBreadcrumb(nid)
                        $.get('/essential/get_node/' + nid).done((result) => {
                            
                            if($(".GofastNode").length > 0){

                                var node = Gofast.get('node');
                                let jsonData = JSON.parse(result)
                                if (typeof node !== 'undefined') {
                                    node.id = jsonData.id
                                    node.title = jsonData.title
                                    node.type = jsonData.type
                                }
                                
                                //Get space path insteads of document path to put in URL
                                var spacePath = href;
                                spacePath = spacePath.split("/")
                                spacePath.pop()
                                spacePath = spacePath.join("/")
                                history.pushState({}, "", "/node/" + nid + "?path=" + spacePath + location.hash);
                                $.get('/essential/get_node_content_part/sideContent/' + nid).done((result) => {
                                    if($(".GofastNode").length > 0){
                                        $('#side-content-container > .sideContent').html(result)
                                    }
                                })

                                $.get('/essential/get_node_content_part/content/' + nid).done((result) => {
                                    if (!$(".GofastNode").length){
                                        return;
                                    }
                                    $('#nodeContainer > .mainContent > .card > .card-body').remove()
                                    $('#nodeContainer > .mainContent > .card').append(result)
                                    $('#nodeContainer').attr("data-nid", allContentsObj[href])
                                });
                            }
                        })
                        // Only execute this request if contextual-actions exist
                        if ($("#refresh_actions_button").parent().find('.contextual-actions').length > 0) {
                            
                            // Empty all content of contextual actions (We empty the elements to not lose the size of the block)
                            $("#refresh_actions_button").parent().find('> :not(#refresh_actions_button)').html('');
                            
                            // Get new contextual actions with the new node
                            $.get('/essential/get_contextual_actions/' + nid).done((result) => {
                                result.forEach((el, i) => {
                                    $("#refresh_actions_button").parent().find('> :not(#refresh_actions_button)').remove();
                                    
                                    // Remove useless comment into bloc
                                    $("#refresh_actions_button").parent().contents().filter(function() {
                                        return this.nodeType === 8;
                                    }).remove();
                                    
                                    // Append new contextual actions
                                    $("#refresh_actions_button").parent().append(el);
                                })
                                
                                // Replace contextual actions loading by the contextual menu (if necessary)
                                if (jQuery("#contextual-actions-loading").length !== 0 && jQuery("#contextual-actions-loading").hasClass('not-processed')) {
                                    jQuery("#contextual-actions-loading").removeClass('not-processed');
                                    jQuery.get(location.origin + "/gofast/node-actions/" + nid, function(data) {
                                        jQuery("#contextual-actions-loading").replaceWith(data);
                                        Drupal.attachBehaviors();
                                        if (jQuery('#unlock_document_span').length) {
                                            jQuery("li>a.on-node-lock-disable").addClass('disabled');
                                        }
                                    });
                                }
                            })
                        }
                    })
                }
                return;
            }
        })
      }
    },
    /*
     * Handle Wiki and Forum elements in document layer
    */
    handleWikiForumInDocumentLayer: function(type, status, isBook){
      $(document).ready(() => {
        if(Gofast.get("node") != undefined && Gofast.get("node").type == "forum"){
            Gofast.Essential.loadBreadcrumb(Gofast.get("node").id)
        } else {
            Gofast.Essential.changeDocumentContent('load', type, status);
        }
      })
   },
  };

  /*
   * Implements behaviors and events
  */
  let loaded = false;
  Drupal.behaviors.essentialHandlers = {
    attach: function(){
      Gofast.Essential.topBarNavigationHandlers();
      Gofast.Essential.searchHandlerPaginate();
      Gofast.Essential.setupSideBar();
      Gofast.Essential.showWikiLayer();
      Gofast.Essential.showForumPage();
      if(loaded == false){
        loaded = true
        Gofast.Essential.loadFileBrowser();
        Gofast.Essential.showActivityFeed();
        Gofast.Essential.showDashboard();
        Gofast.Essential.showSearchPage();
      }
      Gofast.Essential.triggerDocumentTab();
    }
  }
})(jQuery, Gofast, Drupal);
