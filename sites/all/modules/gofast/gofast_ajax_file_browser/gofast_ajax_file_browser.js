(function ($, Gofast, Drupal) {

  /*
   * Functions used to implement ITHit Ajax Library
   */
  Gofast.ITHit = {
    /*
     * To truely stop propagation
     */
    prop: false,
    /*
     * Tells if we are ready to process data
     */
    ready: false,
    /*
     * Contains the File Browser tree object
     */
    tree: false,
    /*
     * Contains the current path
     */
    currentPath: "/alfresco/webdav/Sites",
    /*
     * Number of downloads in progress (used tu set 2s interval between downloads start)
     */
    downloadTimeout: 1,
    /*
     * Load the bredcrumb after 1 second to avoid multiple calls
     */
    refreshBreadcrumbTimeout: 1,
    /*
     * Load the bredcrumb after 1 second to avoid multiple calls
     */
    locationChanged: false,
    /*
     * Contains the todo queue (move and delete actions)
     */
    queue: [],
    /*
     * Tells if the queue refreshing is active
     */
    activeQueue: false,
    /*
     * Tells if the queue processing loop is running
     */
    processingQueue: false,
    /*
     * Tells if we are already processing items or not to prevent multiple items processing
     */
    processingItems: false,
    /*
     * Set the drop path, used to queue events in another folder than the initial
     */
    dropPath: false,
    /*
     * Store copied items from CTRL+C or CTRL+X
     */
    itemsCopied: [],
    /*
     * CTRL+C or CTRL+X
     */
    copyType: 'C',
    /*
     * Contains a timeout for the search processing (prevent overload)
     */
    searchProcess: null,
    /*
     * Define display (default : details)
     */
    display: 'details',
    /*
     * Define by what are sorted the items (default : name)
     */
    sortType: 'DisplayName.toLowerCase()',
    /*
     * Defines the sort order (default asc);
     */
    sortOrder: 'asc',
    /*
     * Refresh the breadcrumb
     */
    refreshBreadcrumb: function (usedPath, refreshPage) {
      var baseUrl = window.location.protocol + "//" + window.location.host;
      var folderPath = "";
      //formatting path to match the next call
      var index = usedPath.indexOf('/', usedPath.lastIndexOf('/_') + 1);
      //case where the user clicked on a folder
      if (index !== -1) {
        folderPath = usedPath.substring(index, usedPath.lenngth);
        usedPath = usedPath.substring(0, index);
      }
      //getting node
      $.post(baseUrl + '/ajax/getnidfromhref', { href: usedPath.replace(/\&/g, "%26").replace(/\+/g, "%2B") }, function (data) {
        //to avoid calling if we already are on the node
        if (Gofast.get("node")["id"] !== data || Gofast.ITHit.locationChanged) {
          if (Gofast.get("node")["id"] === data) Gofast.ITHit.locationChanged = false;
          else Gofast.ITHit.locationChanged = true;
          if (refreshPage && Gofast.get("node")["id"] !== data) {
            if (typeof Gofast.processAjax !== "undefined") {
              Gofast.processAjax("/node/" + data + "?&path=" + usedPath + folderPath + location.hash);
            } else {
              window.location.href = window.location.origin + "/node/" + data + "?&path=" + usedPath + folderPath + location.hash;
            }

          }
          else {
            //getting breadcrumb
            $.post(baseUrl + '/gofast/node-breadcrumb/' + data, function (breadcrumb) {
              //update the breadcrumb
              $("div.breadcrumb.gofast.breadcrumb-gofast").replaceWith(breadcrumb);
              Drupal.attachBehaviors();

              //Toggle members button
              if ($(breadcrumb).find("div").text().indexOf("»") == "-1" || $(breadcrumb).find("div").text().split("»")[0] == "Public ") {
                //Disable members button
                $('a[href="#ogmembers"]').attr("id", "tab_ogmembers_disabled");
                $('a[href="#ogmembers"]').css("pointer-events", "none");
                $('a[href="#ogmembers"]').addClass("disabled");
                $('a[href="#ogmembers"]').parent().addClass("disabled");
              } else {
                //Enable members button
                $('a[href="#ogmembers"]').attr("id", "");
                $('a[href="#ogmembers"]').css("pointer-events", "initial");
                $('a[href="#ogmembers"]').removeClass("disabled");
                $('a[href="#ogmembers"]').parent().removeClass("disabled");
              }

              $.post(baseUrl + '/gofast/node-breadcrumb/' + data + "?only_actions=true", function (breadcrumb) {
                $("#breadcrumb-alt-actions").replaceWith(breadcrumb);
                Drupal.attachBehaviors();
              });
            });
          }
        }
      });
    },
    /*
     * Init component
     * Will wait and call itself while the ITHit object isn't instanciated
     */
    init: function () {
      if (typeof Drupal.settings.pass_reset != "undefined") {
        return;
      }

      //Check if ITHit object is here
      if (typeof ITHit === "undefined") { //Object is not here
        //Try later
        setTimeout(Gofast.ITHit.init, 1000);
      } else { //Object is here
        //Check if the user is logged in
        if (Gofast.get('user').uid === 0) {
          //Not logged in
          return;
        }

        //Create a new ITHit session
        Gofast.ITHit.Client = ITHit.WebDAV.Client;
        Gofast.ITHit.Session = new Gofast.ITHit.Client.WebDavSession();

        //Authentify to Alfresco
        Gofast.ITHit._authentify();

        //Instenciate uploaders (Warning, mobile uploader is also instanciated here)
        Gofast.ITHit.Uploader = new ITHit.WebDAV.Client.Upload.Uploader();
        Gofast.ITHit.Uploader.UploadFolders = true;
        Gofast.ITHit.Uploader.FilesMultiselect = true;

        Gofast.ITHit.UploaderMobile = new ITHit.WebDAV.Client.Upload.Uploader();
        Gofast.ITHit.UploaderMobile.UploadFolders = true;
        Gofast.ITHit.UploaderMobile.FilesMultiselect = true;

        //Init the queue processing
        if (!Gofast.ITHit.processingQueue) {
          Gofast.ITHit.processQueue();
        }

        //Init the files loader
        NProgress.configure({ parent: '#file_browser_full_toolbar' });
        NProgress.configure({ showSpinner: false });
      }
    },
    /*
     * Authentify to Alfresco
     * Called in init process
     */
    _authentify: function () {
      if (!Gofast.ITHit.ready) {

        Gofast.sendXHR('OPTIONS', '/alfresco/webdav/Sites?ticket=' + Drupal.settings.ticket, '', false, null, function (xhr) {
          Gofast.sendXHR('GET', '/alfresco/webdav/Sites?ticket=' + Drupal.settings.ticket, '', false, null, function (xhr) {
            //Ready to retrieve data
            Gofast.ITHit.ready = true;
          });
        });

        setInterval(function () {
          Gofast.sendXHR('OPTIONS', '/alfresco/webdav/Sites?ticket=' + Drupal.settings.ticket, '', true, null, function (xhr) {
            Gofast.sendXHR('GET', '/alfresco/webdav/Sites?ticket=' + Drupal.settings.ticket, '', true, null, function (xhr) {
              //Ready to retrieve data
              Gofast.ITHit.ready = true;
            });
          });
        }, 900000);
      }
    },
    /*
     * Navigate to a path
     * If no params are provided or if the path is not accessible, will back to
     * Sites folder
     * If onlyTree is set to true, we just update the zTree
     * If noRecursion is set to true, we only update the zTree for the wanted location
     */
    navigate: function (path, onlyTree, noRecursion, noPush, selectItem, deleteTree) {
      clearInterval(Gofast.ITHit.refreshBreadcrumbTimeout);
      NProgress.start();
      path = path.replace(/%2F/g, '/');
      if (path.indexOf('/alfresco/webdav') !== 0) {
        path = "/alfresco/webdav" + path;
      }
      var fullPath = path;
      if (typeof ITHit === "undefined" || typeof Gofast.ITHit.Session === "undefined") { //Not ready to navigate
        //Try later
        setTimeout(Gofast.ITHit.navigate, 1000, path);
      } else { //Ready to navigate
        Gofast.ITHit.Session.OpenFolderAsync(path, null,
          function (asyncResult) {

            if (!asyncResult.IsSuccess) {
              NProgress.done();
              Gofast.toast(Drupal.t("Unable to access to", {}, { context: 'gofast:ajax_file_browser' }) + " " + path, "warning");

              //Remove slash at the end if needed
              if (path.substr(-1, 1) === "/") {
                path = path.substring(0, path.length - 1);
              }

              //Try to get the parent folder
              path = path.split('/');
              path.pop();

              //Prevent infinite loop and go
              if (path.length !== 2) {
                path = path.join('/') + "/";
                Gofast.ITHit.navigate(path);
              } else {
                $('#file_browser_full_container').replaceWith('<div style="text-align: center;font-size: 25px;"><i style="color: #dc3545;" class="fa fa-exclamation" aria-hidden="true"></i> ' + Drupal.t("Sorry, we are not able to load the file browser", {}, { context: 'gofast:ajax_file_browser' }) + "</div>");
              }
              return;
            }

            NProgress.set(0.4);

            var folder = asyncResult.Result;
            folder.GetChildrenAsync(false, null,
              function (asyncResult) {
                if (!asyncResult.IsSuccess) {
                  NProgress.done();
                  Gofast.toast(Drupal.t("Unable to get elements of", {}, { context: 'gofast:ajax_file_browser' }) + " " + path, "warning");

                  //Try to get the parent folder
                  path = path.split('/');
                  path.pop();
                  path.pop();

                  //Prevent infinite loop and go
                  if (path.length !== 0) {
                    path = path.join('/') + "/";
                    Gofast.ITHit.navigate(path);
                  }
                  return;
                }
                var error_new_document_browser = ['/alfresco/webdav/Sites', '/alfresco/webdav/Sites/_Public/', '/alfresco/webdav/Sites/_Extranet/', '/alfresco/webdav/Sites/_Groups/', '/alfresco/webdav/Sites/_Organisations/'];
                var error_new_document_ztree = ['/alfresco/webdav/Sites/_Public', '/alfresco/webdav/Sites/_Extranet', '/alfresco/webdav/Sites/_Groups', '/alfresco/webdav/Sites/_Organisations'];
                var folder_template_path = '/alfresco/webdav/Sites/FOLDERS TEMPLATES';
                if (jQuery.inArray(path, error_new_document_browser) !== -1 || jQuery.inArray(path, error_new_document_ztree) !== -1 || Gofast._settings.gofast_ajax_file_browser.archived_spaces.indexOf(decodeURI(path).substring(0, decodeURI(path).length - 1)) !== -1 || Gofast._settings.gofast_ajax_file_browser.archived_spaces.indexOf(decodeURI(path).substring(0, decodeURI(path).length)) !== -1) {
                  $('#file_browser_tooolbar_new_item').prop('disabled', true);
                } else {
                  $('#file_browser_tooolbar_new_item').prop('disabled', false);
                }
                if (decodeURI(path).indexOf(folder_template_path) !== -1) {
                  $('.add-folder-template').addClass('gofast_display_none');
                  $('#file_browser_tooolbar_new_alfresco_item').addClass('gofast_display_none');
                } else {
                  $('.add-folder-template').removeClass('gofast_display_none');
                  $('#file_browser_tooolbar_new_alfresco_item').removeClass('gofast_display_none');
                }
                NProgress.set(0.6);

                var items = asyncResult.Result;
                if (!onlyTree) {
                  Gofast.ITHit._processItems(items, fullPath);

                  fullPath = decodeURIComponent(fullPath);
                  //Remove slash at the end if needed
                  if (fullPath.substr(-1, 1) === "/") {
                    fullPath = fullPath.substring(0, fullPath.length - 1);
                  }

                  Gofast.ITHit.currentPath = fullPath;
                  Gofast.ITHit.Uploader.SetUploadUrl(location.origin + fullPath);

                  if (!noPush) {
                    Gofast.ITHit.updatePathParam(fullPath);
                  }

                  //Select the wanted item
                  if (typeof selectItem !== "undefined") {
                    Gofast.ITHit.selectItem(selectItem);
                  }

                  //Disable copy and cut buttons
                  $('#file_browser_tooolbar_copy').prop('disabled', true);
                  $('#file_browser_tooolbar_cut').prop('disabled', true);
                  //Disable manage button
                  $('#file_browser_tooolbar_manage').prop('disabled', true);
                  //Disable cart button
                  $('#file_browser_tooolbar_cart_button').prop('disabled', true);
                  //Disable contextual actions
                  $('#file_browser_tooolbar_contextual_actions').prop('disabled', true);

                  if (location.hash === "#ogdocuments") {
                    //setting an interval to avoid multiple useless calls
                    Gofast.ITHit.refreshBreadcrumbTimeout = setTimeout(function () {
                      Gofast.ITHit.refreshBreadcrumb(path.substring(16, path.length), false);
                    }, 1000);
                  }
                }

                Gofast.ITHit._processTree(path, noRecursion, deleteTree);
                if (onlyTree) {
                  NProgress.done();
                }
                Gofast.ITHit.searchProcess = setTimeout(function () {
                  $('#name_header').trigger('resize');
                  $('#size_header').trigger('resize');
                  $('#type_header').trigger('resize');
                }, 250);

              }
            );
          }
        );
      }
    },
    /*
     * Select an item by path and scroll to it
     */
    selectItem: function (path, keepothers) {
      var item = $('#file_browser_full_files_table').find('.item-path:contains("' + path + '")').parent();
      if (keepothers) {
        var event = $.Event("mousedown");
        event.ctrlKey = true;
        item.trigger(event);
      } else {
        item.trigger('mousedown');
        $("#file_browser_full_files_table").mCustomScrollbar("scrollTo", item);
      }
    },
    /*
     * Push a new state in history containing the path param
     * Occures at navigation
     */
    updatePathParam: function (path) {
      //Get params
      var params = {};

      if (location.search) {
        var parts = location.search.substring(1).split('&');

        for (var i = 0; i < parts.length; i++) {
          var nv = parts[i].split('=');
          if (!nv[0]) continue;
          params[nv[0]] = nv[1] || true;
        }
      }

      var replace = false;
      if (typeof params.path === "undefined") {
        replace = true;
      }

      //Change path param
      params.path = path.replace('/alfresco/webdav', '');
      params.path = params.path.replace(/&/g, '%26');

      //Prepare params to push
      var pushParams = '?';
      for (var key in params) {
        pushParams += "&" + key + "=" + params[key];
      }

      //Prepare hash to push
      var pushHash = "";
      if (location.hash !== "") {
        pushHash = location.hash;
      }

      //Prepare URL to push
      var pushUrl = location.origin + location.pathname + pushParams + pushHash;

      if (replace) {
        history.replaceState(null, "Gofast", pushUrl);
      } else {
        history.pushState(null, "Gofast", pushUrl);
      }
    },
    /*
     * Usually called when loading a space node (in the tpl)
     */
    attachBrowserEvents: function () {
      $('#file_browser_full_files_table').on('keydown', function (e) {
        if (e.keyCode == 65 && e.ctrlKey == true && document.activeElement.id !== "rename-form") { //CTRL+A pressed
          Gofast.ITHit.selectAll();
          return false;
        }
      });
      $("#file_browser_full_files_table").on('keyup', function (e) {
        if (e.keyCode == 46) { //Suppr pressed
          if ($("#rename-form").length !== 0) {
            return;
          }
          //Retrieve all selected items
          var data = [];
          var selected = $('#file_browser_full_files_table').find('.selected').find('.item-path');
          var noDelete = false;
          $.each(selected, function (k, elem) {
            var path = elem.innerText;

            //Remove slash at the end if needed
            if (path.substr(-1, 1) === "/") {
              path = path.substring(0, path.length - 1);
            }

            //Check if this is a space
            var name = path.split('/');
            name = name.pop();

            if (name.substr(0, 1) !== '_') {
              if (decodeURI(name) === "FOLDERS TEMPLATES") {
                Gofast.toast(Drupal.t("You can't delete FOLDERS TEMPLATES.", {}, { context: 'gofast:ajax_file_browser' }), "warning");
                noDelete = true;
              } else {
                data.push(elem.innerText);
              }
            } else {
              noDelete = true;
              Gofast.addLoading();
              $.get(location.origin + "/ajax/getnidfromhref?href=" + path)
                .done(function (result) {
                  $.ajax({
                    url: location.origin + "/modal/nojs/gofast_og/delete_space/" + result,
                  }).done(function (commands) {
                    var jsonCommands = JSON.parse(commands);

                    jsonCommands.forEach(function (k, v) {
                      if (k.command == "modal_display") {
                        Gofast.removeLoading();
                        Gofast.modal(k.output, k.title);
                      }
                    })
                  })
                    .fail(function () {
                      Gofast.removeLoading();
                      Gofast.toast(Drupal.t("You don't have permission to delete this space", {}, { context: 'gofast:ajax_file_browser' }), "warning");
                    })
                })
            }
          });
          data = JSON.stringify(data);

          if (!noDelete) {
            //process delete
            Gofast.ITHit.delete(data);
          }
        } if (e.keyCode == 67 && e.ctrlKey == true && document.activeElement.id !== "rename-form") { //CTRL+C pressed
          Gofast.ITHit.copySelected();
        } if (e.keyCode == 88 && e.ctrlKey == true & document.activeElement.id !== "rename-form") { //CTRL+X pressed
          Gofast.ITHit.cutSelected();
        } if (e.keyCode == 86 && e.ctrlKey == true && document.activeElement.id !== "rename-form") { //CTRL+V pressed
          Gofast.ITHit.paste();
        }
      });

      $("#file_browser_full_tree_container").on('keyup', function (e) {
        if (e.keyCode == 67 && e.ctrlKey == true && document.activeElement.id !== "rename-form") { //CTRL+C pressed
          Gofast.ITHit.copySelected();
        } if (e.keyCode == 88 && e.ctrlKey == true && document.activeElement.id !== "rename-form") { //CTRL+X pressed
          Gofast.ITHit.cutSelected();
        } if (e.keyCode == 86 && e.ctrlKey == true && document.activeElement.id !== "rename-form") { //CTRL+V pressed
          Gofast.ITHit.paste();
        }
      });

      $("#file_browser_full_toolbar_search_input").on('keyup', function (e) {
        //We set timeout to prevent JS engine overload (and we clear the timeout each time a key is pressed)
        clearTimeout(Gofast.ITHit.searchProcess);
        Gofast.ITHit.searchProcess = setTimeout(function () {
          Gofast.ITHit.search($('#file_browser_full_toolbar_search_input').val());
        }, 300);
      });

      //Toolbar
      $('#file_browser_tooolbar_new_folder').on('click', function (e) {
        e.preventDefault();
        Gofast.ITHit.createFolder(Gofast.ITHit.currentPath);
      });
      $('#file_browser_tooolbar_display_details').on('click', function (e) {
        e.preventDefault();
        Gofast.ITHit.setDisplay('details');
      });
      $('#file_browser_tooolbar_display_icons').on('click', function (e) {
        e.preventDefault();
        Gofast.ITHit.setDisplay('icons');
      });
      $('#file_browser_tooolbar_refresh').on('click', function (e) {
        e.preventDefault();
        Gofast.ITHit.reload();
      });
      $('#file_browser_tooolbar_copy').on('click', function (e) {
        e.preventDefault();
        Gofast.ITHit.copySelected();
      });
      $('#file_browser_tooolbar_cut').on('click', function (e) {
        e.preventDefault();
        Gofast.ITHit.cutSelected();
      });
      $('#file_browser_tooolbar_paste').on('click', function (e) {
        e.preventDefault();
        Gofast.ITHit.paste();
      });
      $('#file_browser_tooolbar_cart_button').on('click', function (e) {
        Gofast.ITHit.bulkSelected(e);
      });
      $('#file_browser_tooolbar_contextual_actions').on('click', function (e) {
        $('#file_browser_full_files_table').find('.selected').trigger('contextmenu');
      });

      //Sorting
      $('.file_table_header').on('click', function (e) {
        var target = $(e.target);
        if (target.hasClass('ui-resizable-resizing')) {
          return;
        }
        if (target.find('.order_indicator').not('.gofast_display_none').length !== 0) { //Just need to switch the order
          if (target.find('.order_indicator').not('.gofast_display_none').hasClass('fa-caret-up')) {
            //Switch to asc order
            target.find('.fa-caret-down').removeClass('gofast_display_none');
            target.find('.fa-caret-up').addClass('gofast_display_none');

            Gofast.ITHit.sortOrder = 'asc';
          } else {
            //Switch to desc order
            target.find('.fa-caret-up').removeClass('gofast_display_none');
            target.find('.fa-caret-down').addClass('gofast_display_none');

            Gofast.ITHit.sortOrder = 'desc';
          }
        } else { //Set order to asc and change ordering type
          target.parent().find('.order_indicator').addClass('gofast_display_none');
          target.find('.fa-caret-down').removeClass('gofast_display_none');

          Gofast.ITHit.sortOrder = 'asc';

          if (target.attr('id') === 'name_header') {
            Gofast.ITHit.sortType = 'DisplayName.toLowerCase()';
          } else if (target.attr('id') === 'size_header') {
            Gofast.ITHit.sortType = 'ContentLength';
          } else if (target.attr('id') === 'type_header') {
            Gofast.ITHit.sortType = 'type';
          } else if (target.attr('id') === 'modified_header') {
            Gofast.ITHit.sortType = 'LastModified.getTime()';
          }
        }

        Gofast.ITHit.reload();
      });

      //Makes the columns resizable
      $('#file_browser_full_files_table').find('th:not(:first):not(:last)').resizable({
        handles: 'e',
        minWidth: 10,
      }).css('border-right', '1px solid black');

      //Bind the resize events
      $('#name_header').resize(function (e) {
        e.stopPropagation();
        if (!$("#ogtab_documents").parent().hasClass('active') && window.location.pathname.indexOf("/gofast/browser") === -1) {
          return;
        }
        var icon_width = $('#file_browser_full_files_header').find('th:first').innerWidth();
        var header_width = $("#file_browser_full_files_header").innerWidth();
        var name_width = $('#name_header').innerWidth();
        var size_width = $('#size_header').innerWidth();
        var type_width = $('#type_header').innerWidth();
        var modified_width = $('#modified_header').innerWidth();
        var info_width = $('#info_header').innerWidth();

        //Edit elements width
        $('#file_browser_full_files_table').find('tr').find('.item-name').innerWidth(name_width);

        //Search what width we have to correct
        var correction_width = (icon_width + name_width + size_width + type_width + modified_width + info_width) - header_width + 10;

        //We need to have a repartition of this correction between headers. A header
        //cannot be smaller than 80px

        //Alter size header
        var alter_size_width_max = -(10 - size_width);
        if (alter_size_width_max < correction_width) {
          correction_width -= alter_size_width_max;
          $('#size_header').innerWidth(10);
          $('#file_browser_full_files_table').find('tr').find('.item-size').innerWidth(10);
        } else {
          $('#size_header').innerWidth(size_width - correction_width);
          $('#file_browser_full_files_table').find('tr').find('.item-size').innerWidth(size_width - correction_width);
          return;
        }

        //Alter type header
        var alter_type_width_max = -(10 - type_width);
        if (alter_type_width_max < correction_width) {
          correction_width -= alter_type_width_max;
          $('#type_header').innerWidth(10);
          $('#file_browser_full_files_table').find('tr').find('.item-type').innerWidth(10);
        } else {
          $('#type_header').innerWidth(type_width - correction_width);
          $('#file_browser_full_files_table').find('tr').find('.item-type').innerWidth(type_width - correction_width);
          return;
        }

        //Alter modified header
        var alter_modified_width_max = -(10 - modified_width);
        if (alter_modified_width_max < correction_width) {
          correction_width -= alter_modified_width_max;
          $('#modified_header').innerWidth(10);
          $('#file_browser_full_files_table').find('tr').find('.item-date').innerWidth(10);

          //We need to revert the resizing as we can't resize anymore
          $('#name_header').innerWidth(name_width - correction_width);
          $('#file_browser_full_files_table').find('tr').find('.item-name').innerWidth(name_width - correction_width);
        } else {
          $('#modified_header').innerWidth(modified_width - correction_width);
          $('#file_browser_full_files_table').find('tr').find('.item-date').innerWidth(modified_width - correction_width);
          return;
        }
      });
      $('#size_header').resize(function (e) {
        e.stopPropagation();
        if (!$("#ogtab_documents").parent().hasClass('active') && window.location.pathname.indexOf("/gofast/browser") === -1) {
          return;
        }
        var icon_width = $('#file_browser_full_files_header').find('th:first').innerWidth();
        var header_width = $("#file_browser_full_files_header").innerWidth();
        var name_width = $('#name_header').innerWidth();
        var size_width = $('#size_header').innerWidth();
        var type_width = $('#type_header').innerWidth();
        var modified_width = $('#modified_header').innerWidth();
        var info_width = $('#info_header').innerWidth();

        $('#file_browser_full_files_table').find('tr').find('.item-size').innerWidth(size_width);

        //Search what width we have to correct
        var correction_width = (icon_width + name_width + size_width + type_width + modified_width + info_width) - header_width + 10;

        //We need to have a repartition of this correction between headers. A header
        //cannot be smaller than 80px

        //Alter type header
        var alter_type_width_max = -(10 - type_width);
        if (alter_type_width_max < correction_width) {
          correction_width -= alter_type_width_max;
          $('#type_header').innerWidth(10);
          $('#file_browser_full_files_table').find('tr').find('.item-type').innerWidth(10);
        } else {
          $('#type_header').innerWidth(type_width - correction_width);
          $('#file_browser_full_files_table').find('tr').find('.item-type').innerWidth(type_width - correction_width);
          return;
        }

        //Alter modified header
        var alter_modified_width_max = -(10 - modified_width);
        if (alter_modified_width_max < correction_width) {
          correction_width -= alter_modified_width_max;
          $('#modified_header').innerWidth(10);
          $('#file_browser_full_files_table').find('tr').find('.item-date').innerWidth(10);

          //We need to revert the resizing as we can't resize anymore
          $('#size_header').innerWidth(size_width - correction_width);
          $('#file_browser_full_files_table').find('tr').find('.item-size').innerWidth(size_width - correction_width);
        } else {
          $('#modified_header').innerWidth(modified_width - correction_width);
          $('#file_browser_full_files_table').find('tr').find('.item-date').innerWidth(modified_width - correction_width);
          return;
        }
      });
      $('#type_header').resize(function (e) {
        e.stopPropagation();
        if (!$("#ogtab_documents").parent().hasClass('active') && window.location.pathname.indexOf("/gofast/browser") === -1) {
          return;
        }
        var icon_width = $('#file_browser_full_files_header').find('th:first').innerWidth();
        var header_width = $("#file_browser_full_files_header").innerWidth();
        var name_width = $('#name_header').innerWidth();
        var size_width = $('#size_header').innerWidth();
        var type_width = $('#type_header').innerWidth();
        var modified_width = $('#modified_header').innerWidth();
        var info_width = $('#info_header').innerWidth();

        $('#file_browser_full_files_table').find('tr').find('.item-type').innerWidth(type_width);


        //Search what width we have to correct
        var correction_width = (icon_width + name_width + size_width + type_width + modified_width + info_width) - header_width + 10;

        //We need to have a repartition of this correction between headers. A header
        //cannot be smaller than 80px

        //Alter modified header
        var alter_modified_width_max = -(10 - modified_width);
        if (alter_modified_width_max < correction_width) {
          correction_width -= alter_modified_width_max;
          $('#modified_header').innerWidth(10);
          $('#file_browser_full_files_table').find('tr').find('.item-date').innerWidth(10);

          //We need to revert the resizing as we can't resize anymore
          $('#type_header').innerWidth(type_width - correction_width);
          $('#file_browser_full_files_table').find('tr').find('.item-type').innerWidth(type_width - correction_width);
        } else {
          $('#modified_header').innerWidth(modified_width - correction_width);
          $('#file_browser_full_files_table').find('tr').find('.item-date').innerWidth(modified_width - correction_width);
          return;
        }
      });
    },
    /*
     * Select all items
     */
    selectAll: function () {
      $('.file_browser_full_files_element').not('#file_browser_back_button').addClass('selected');
    },
    /*
     * Set the display type of the browser
     */
    setDisplay: function (type) {
      Gofast.ITHit.display = type;
      Gofast.ITHit.reload();

      if (type === 'details') {
        //Display the header
        $('#file_browser_full_files_header').show();
        $('#file_browser_tooolbar_display_icon').removeClass('fa-picture-o').addClass('fa-list');
      } else {
        //Hide the header
        $('#file_browser_full_files_header').hide();
        $('#file_browser_tooolbar_display_icon').removeClass('fa-list').addClass('fa-picture-o');
      }

    },
    /*
     * Reload the current path
     */
    reload: function () {
      Gofast.ITHit.navigate(Gofast.ITHit.currentPath);
    },
    /*
     * Create a folder (form)
     */
    createFolder: function (path) {
      //Remove slash at the end
      if (path.substr(-1, 1) === "/") {
        path = path.substring(0, path.length - 1);
      }

      //Create a fake item to process it in the table
      var item = {
        ResourceType: 'Folder',
        DisplayName: Drupal.t('New folder', {}, { context: 'gofast:ajax_file_browser' }),
        Href: path + '/' + this.DisplayName,
      };

      //Format the fake item
      var itemHTML = Gofast.ITHit._formatItem(item);

      //Add a new line to the table at the bottom containing the new potential folder
      var processedItem = $('#file_browser_full_files_table').find('tbody:last-child').append(itemHTML);
      processedItem = processedItem.find('tr').last();
      var name_element = processedItem.find('.item-name');

      //We are secure to edit
      name_element.html('<input id="new-folder-form" class="form-control form-text" value="' + name_element.text() + '" style="height:20px;width:80%;float:left"><div class="btn-group" role="group"><button style="height:20px;padding-left:5px;padding-right:5px;padding-top:0px;padding-bottom:0px;" type="button" class="btn btn-success"><i class="fa fa-check"></i></button><button type="button" style="height:20px;padding-left:5px;padding-right:5px;padding-top:0px;padding-bottom:0px;" class="btn btn-danger"><i class="fa fa-times"></i></button>');

      //Scroll to the bottom of the table
      $("#file_browser_full_files_table").mCustomScrollbar("scrollTo", "bottom", { scrollInertia: 0 });
      name_element.find('input:text').select();

      //Bind the enter event to the input
      name_element.find('input').on('keyup', function (e) {
        if (e.keyCode == 13) { //Enter pressed
          var new_name = name_element.find('input').val();

          //Delete spaces at the beginning and end of the name
          new_name = new_name.trim();
          //Prevent users to create folders starting with '_'
          if (new_name.substr(0, 1) === "_") {
            Gofast.toast(Drupal.t("You can't create a folder with a name starting with '_'"), "warning");
            return;
          }

          //Trigger the animation
          name_element.html('<div class="loader-filebrowser"></div>' + new_name);

          //Process creation
          Gofast.ITHit._processCreateFolder(path, new_name, processedItem, name_element);
        }
      });
      //Bind the validate button event
      name_element.find('.btn-success').on('click', function (e) {
        var new_name = name_element.find('input').val();

        //Delete spaces at the beginning and end of the name
        new_name = new_name.trim();

        //Prevent users to create folders starting with '_'
        if (new_name.substr(0, 1) === "_") {
          Gofast.toast(Drupal.t("You can't create a folder with a name starting with '_'"), "warning");
          return;
        }

        //Trigger the animation
        name_element.html('<div class="loader-filebrowser"></div>' + new_name);

        //Process creation
        Gofast.ITHit._processCreateFolder(path, new_name, processedItem, name_element);
      });
      //Bind the cancel button event
      name_element.find('.btn-danger').on('click', function (e) {
        processedItem.remove();
      });
    },
    /*
     * Process the creation of a folder
     */
    _processCreateFolder: function (path, name, element, name_element) {
      Gofast.ITHit.Session.OpenFolderAsync(path, null, function (asyncResult) {
        if (!asyncResult.IsSuccess) {
          Gofast.toast(Drupal.t("Unable to find", {}, { context: 'gofast:ajax_file_browser' }) + " " + path, "warning");
          element.remove();
          return;
        }

        var folder = asyncResult.Result;

        //Process creation
        folder.CreateFolderAsync(name, null, null, function (asyncFResult) {
          if (asyncFResult.IsSuccess) {
            //Reload and go to folder position
            Gofast.ITHit.navigate(path, null, null, null, asyncFResult.Result.Href);
          } else if (asyncFResult.Error instanceof ITHit.WebDAV.Client.Exceptions.MethodNotAllowedException) {
            Gofast.toast(name + " " + Drupal.t("already exists in this folder", {}, { context: 'gofast:ajax_file_browser' }), "warning");
            element.remove();
            return;
          } else {
            Gofast.toast(Drupal.t("You are not the administrator of this space and therefore cannot create a template inside.", {}, { context: 'gofast:ajax_file_browser' }), "warning", Drupal.t("Your folder cannot be created", {}, { context: 'gofast:ajax_file_browser' }));
            element.remove();
            return;
          }
        });
      });
    },
    /*
     * Search a string in displayed items
     */
    search: function (pattern) {
      if ($("#rename-form").length !== 0) {
        return;
      }
      var elements = $(".file_browser_full_files_element").not('#file_browser_back_button');

      if (pattern === "") {
        elements.removeClass('search-hidden');
        elements.css('display', 'block');

        //Remove bold
        $.each(elements.find('.item-name'), function (k, elem) {
          $(elem).text($(elem).text());
        });
      } else {
        $.each(elements, function (k, element) {
          if ($(element).find('.item-name').text().toLowerCase().indexOf(pattern.toLowerCase()) === -1) {
            $(element).addClass('search-hidden');
            setTimeout(function () {
              $(element).css('display', 'none');
            }, 300);

            $(element).find('.item-name').text($(element).find('.item-name').text());
          } else {
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
    },
    /*
     * Copy selected content to ITHit variable
     */
    copySelected: function () {
      //Get selected items
      var selected = $('#file_browser_full_files_table').find('.selected').find('.item-path');

      if (selected.length == 0) {
        return;
      }
      //Store them
      Gofast.ITHit.itemsCopied = [];
      $.each(selected, function (k, path) {
        Gofast.ITHit.itemsCopied.push(path.innerText);
      });

      //Set copy type
      Gofast.ITHit.copyType = 'C';

      //Display toast
      Gofast.toast(Drupal.t("Copied", {}, { context: 'gofast:ajax_file_browser' }), "info");

      //Enable paste button
      $('#file_browser_tooolbar_paste').prop('disabled', false);
    },
    /*
     * Cut selected content to ITHit variable
     */
    cutSelected: function () {
      //Get selected items
      var selected = $('#file_browser_full_files_table').find('.selected').find('.item-path');

      if (selected.length == 0) {
        return;
      }
      //Store them
      Gofast.ITHit.itemsCopied = [];
      $.each(selected, function (k, path) {
        Gofast.ITHit.itemsCopied.push(path.innerText);
      });

      //Set copy type
      Gofast.ITHit.copyType = 'X';

      //Display toast
      Gofast.toast(Drupal.t("Cut", {}, { context: 'gofast:ajax_file_browser' }), "info");

      //Enable paste button
      $('#file_browser_tooolbar_paste').prop('disabled', false);
    },
    /*
     * Paste content from ITHit variable
     */
    paste: function () {
      if (Gofast.ITHit.copyType === 'C') { //Copy
        //Queue items to be copied
        $.each(Gofast.ITHit.itemsCopied, function (k, path) {
          //Get the name of the element from the path
          var fileName = path;
          if (path.substr(-1, 1) === "/") {
            fileName = path.substring(0, path.length - 1);
          }
          fileName = fileName.split('/');
          fileName = decodeURIComponent(fileName.pop());

          Gofast.ITHit.queue.push({
            uuid: Gofast.ITHit.generate_uuid(),
            path: path,
            destination: Gofast.ITHit.currentPath,
            displayNamePath: fileName + ' (' + path + ')',
            fileName: fileName,
            operation: 'copy',
            displayOperation: Drupal.t('Copy', {}, { context: 'gofast:ajax_file_browser' }),
            progression: 0,
            status: 0
          });
        });
      } else { //Move (cut)
        //Queue items to be moved
        $.each(Gofast.ITHit.itemsCopied, function (k, path) {
          //Get the name of the element from the path
          var fileName = path;
          if (path.substr(-1, 1) === "/") {
            fileName = path.substring(0, path.length - 1);
          }
          fileName = fileName.split('/');
          fileName = decodeURIComponent(fileName.pop());

          Gofast.ITHit.queue.push({
            uuid: Gofast.ITHit.generate_uuid(),
            path: path,
            destination: Gofast.ITHit.currentPath,
            displayNamePath: fileName + ' (' + path + ')',
            fileName: fileName,
            operation: 'move',
            displayOperation: Drupal.t('Move', {}, { context: 'gofast:ajax_file_browser' }),
            progression: 0,
            status: 0
          });
        });
        Gofast.ITHit.itemsCopied = [];

        //Disable paste button
        $('#file_browser_tooolbar_paste').prop('disabled', true);
      }
      //Display toast
      Gofast.toast(Drupal.t("Pasted", {}, { context: 'gofast:ajax_file_browser' }), "info");
    },
    /*
     * Attach events when ITHit upload queue is updated
     */
    attachUploadEvents: function () {
      Gofast.ITHit.Uploader.Queue.AddListener('OnQueueChanged', '_UploadQueueChanged', this);

      //Callback that happens when a drag and drop occur to filter the uploaded content
      Gofast.ITHit.Uploader.Queue.OnUploadItemsCreatedCallback = function (oUploadItemsCreated) {
        items = [];

        for (i = 0; i < oUploadItemsCreated.Items.length; i++) {
          items[i] = oUploadItemsCreated.Items[i];
        }
        var item_delete = false;
        items.forEach(function (item, id) {
          if (item_delete === true) {
            indice = items.length - oUploadItemsCreated.Items.length;
            id = id - indice;
            item_delete = false;
          }
          var file = item.GetFile();
          var relativePath = item.GetRelativePath();
          relativepath = relativePath.split("/");

          if (file === null) {
            //This might be a folder and it will not be created
            oUploadItemsCreated.Items.splice(id, 1);
            item_delete = true;
          }
          relativepath.forEach(function (part) {
            if (part.substr(0, 1) === "_") {
              Gofast.toast(Drupal.t("You can't create the following document because a part of it's path is starting with '_' : ") + "<strong>" + item.GetRelativePath() + "</strong>", "warning");
              oUploadItemsCreated.Items.splice(id, 1);
              item_delete = true;
            }
          });
          if (item_delete === false) {
            var path = item._UploadProvider.Url._BaseUrl;
            if (path.indexOf('/alfresco/webdav/Sites/FOLDERS TEMPLATES') !== -1) {
              Gofast.toast(Drupal.t("You can't create documents in folders templates"), "warning");
              oUploadItemsCreated.Items.splice(id, 1);
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
    _UploadQueueChanged: function (changes) {
      if (typeof changes.AddedItems !== "undefined" && changes.AddedItems.length > 0) {
        //Close any opened modal
        Drupal.CTools.Modal.dismiss();
      }
      $.each(changes.AddedItems, function (index, uploadItem) {
        Gofast.ITHit.queue.push({
          uuid: Gofast.ITHit.generate_uuid(),
          path: uploadItem._UploadProvider.Url._OriginalUrl,
          displayNamePath: "(" + uploadItem._UploadProvider.FSEntry._File.name + ") " + decodeURIComponent(uploadItem._UploadProvider.Url._OriginalUrl.replace('/alfresco/webdav/Sites/', '')),
          fileName: uploadItem._UploadProvider.FSEntry._File.name,
          operation: "upload",
          displayOperation: Drupal.t("Upload", {}, { context: 'gofast:ajax_file_browser' }),
          progression: 0,
          status: 0,
          uploadItem: uploadItem
        });
        uploadItem.AddListener('OnProgressChanged', '_UploadItemQueueChanged', this);
        uploadItem.AddListener('OnStateChanged', '_UploadItemQueueChanged', this);
        if (Gofast.ITHit.dropPath) {
          Gofast.ITHit.dropPath = false;
          Gofast.ITHit.Uploader.SetUploadUrl(location.origin + Gofast.ITHit.currentPath);
        }
      }.bind(this));

      $.each(changes.RemovedItems, function (index, uploadItem) {
        console.log('removed');
      }.bind(this));
    },
    /*
     * Upload item queue changed
     */
    _UploadItemQueueChanged: function (change) {
      //Get queue item by path
      var index = Gofast.ITHit.queue.findIndex(function (e) {
        return e !== null && e.operation === "upload" && e.path === change.Sender._UploadProvider.Url._OriginalUrl;
      });

      if (!$.isNumeric(index)) {
        return;
      }

      //Update state
      var state = 0;
      switch (change.NewState) {
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
      if (typeof change.NewProgress !== "undefined" && typeof change.NewProgress.NewProgress !== "undefined" && state !== 4) {
        Gofast.ITHit.queue[index].progression = change.NewProgress.NewProgress.Completed;
      }

      //Update completed, clear the queue and process the item
      if (state === 4) {
        if (location.origin + Gofast.ITHit.currentPath === change.Sender._UploadProvider.Url._BaseUrl) {
          //Get uploaded file and URl informations
          var file = change.Sender._UploadProvider._UploadItem.GetFile();
          var fullPath = change.Sender._UploadProvider._UploadItem.GetUrl();

          var folderPath = fullPath.split("/");
          folderPath.pop();
          folderPath = folderPath.join("/");

          if (folderPath !== change.Sender._UploadProvider.Url._BaseUrl) {
            var type = "Folder";

            //Prevent depth to alter wanted the behavior
            while (folderPath.split("/").length + 1 > change.Sender._UploadProvider.Url._BaseUrl.split("/").length + 2) {
              folderPath = folderPath.split("/");
              folderPath.pop();
              folderPath = folderPath.join("/");
            }

            //Build a folder item object
            var item = {
              DisplayName: folderPath.split("/").pop(),
              Href: folderPath.substr(window.location.origin.length),
              ResourceType: type,
              LastModified: new Date()
            };
          } else {
            var type = "Resource";

            //Build a ressource item object
            var item = {
              DisplayName: file.name,
              Href: fullPath.substr(window.location.origin.length),
              ContentLength: file.size,
              ResourceType: type,
              LastModified: new Date()
            };
          }

          //Check if the item is already present in the file browser
          var browser_item = $('#file_browser_full_files_table').find('td:contains("' + item.Href + '")');
          if (browser_item.length > 0) {
            if (item.ResourceType === "Resource") {
              Gofast.ITHit.selectItem(item.Href, true);
            }
          } else {
            //Format the new item
            var itemHTML = Gofast.ITHit._formatItem(item);

            //Add the item to the list
            var processedItem = $('#file_browser_full_files_table').find('tbody:last-child').append(itemHTML);
            processedItem = processedItem.find('tr').last();

            //Attach event handlers to the processed item
            Gofast.ITHit._attachEvents(item, processedItem);

            if (type === "Folder") {
              //Make this folder dropable
              processedItem.attr('ondragover', "Gofast.ITHit.insideDragOver(event)");
              processedItem.attr('ondragleave', "Gofast.ITHit.insideDragLeave(event)");
              processedItem.attr('ondrop', "Gofast.ITHit.insideDrop(event)");
              processedItem[0].addEventListener("drop", Gofast.ITHit.insideDrop);
            }

            //Trigger resize on columns and select item
            $('#name_header').trigger('resize');
            $('#size_header').trigger('resize');
            $('#type_header').trigger('resize');
            Gofast.ITHit.selectItem(item.Href, true);
          }

          //Removed : GOFAST-5364
          //Gofast.ITHit.reload();
        }
        Gofast.ITHit.queue[index].progression = 100;
        setTimeout(function () {
          Gofast.ITHit.queue[index] = null;
        }, 1000);
      }

      //Update failed, clear the queue and process the item
      if (state === 3) {
        var baseurl = change.Sender._UploadProvider.Url._BaseUrl;
        if (baseurl == window.location.origin + "/alfresco/webdav/Sites" || baseurl == window.location.origin + "/alfresco/webdav/Sites/_Groups" || baseurl == window.location.origin + "/alfresco/webdav/Sites/_Organisations" || baseurl == window.location.origin + "/alfresco/webdav/Sites/_Public" || baseurl == window.location.origin + "/alfresco/webdav/Sites/_Extranet") {
          Gofast.ITHit.queue[index].progression = 0;
          Gofast.toast(Drupal.t("You can not upload files in root spaces (Groups, Organizations, Public, Extranet). Please, upload your files in sub-spaces or create them. ", {}, { context: 'gofast:ajax_file_browser' }), 'warning');
          setTimeout(function () {
            Gofast.ITHit.queue[index] = null;
          }, 1500);
        } else {
          Gofast.ITHit.queue[index].progression = 0;
          if (baseurl.indexOf('/TEMPLATES/') !== -1) {
              Gofast.toast("<u>" + change.Sender._UploadProvider.FSEntry._File.name + "</u><br /><br />" + Drupal.t("You are not the administrator of this space, you cannot create a model there.", {}, { context: 'gofast:ajax_file_browser' }), "warning", Drupal.t("Your document cannot be uploaded", {}, { context: 'gofast:ajax_file_browser' }));
          }
          else{
            Gofast.toast("<u>" + change.Sender._UploadProvider.FSEntry._File.name + "</u><br /><br />" + Drupal.t("Please verify that you are allowed to do that.  If you think this is an error, please contact your administrator.", {}, { context: 'gofast:ajax_file_browser' }), "warning", Drupal.t("Your document cannot be uploaded", {}, { context: 'gofast:ajax_file_browser' }));
          }
          setTimeout(function () {
            Gofast.ITHit.queue[index] = null;
          }, 1500);
        }
      }
    },
    /*
     *
     * @param {type} uuid
     * @returns {undefined}
     * Cancel a waiting or processing upload in the queue
     */
    cancelUpload: function (uuid) {
      Gofast.ITHit.queue.forEach(function (item, i) {
        if (item !== null && item.uuid == uuid && item.uploadItem !== null) {
          //Cancel the upload
          if (typeof item.uploadItem.CancelAsync == "function") {
            item.uploadItem.SetDeleteOnCancel(false);
            item.uploadItem.CancelAsync(5, 500, function () {
              //Upload cancelled, remove line in queue
              Gofast.ITHit.queue[i] = null;
            });
          }
        }
      });
    },
    /*
     *
     * @returns {undefined}
     * Cancel all waiting or processing uploads in the queue
     */
    cancelAllUpload: function () {
      Gofast.ITHit.queue.forEach(function (item, i) {
        if (item !== null && item.uploadItem !== null) {
          //Cancel the upload
          if (typeof item.uploadItem.CancelAsync == "function") {
            item.uploadItem.SetDeleteOnCancel(false);
            item.uploadItem.CancelAsync(5, 500, function () {
              //Upload cancelled, remove line in queue
              Gofast.ITHit.queue[i] = null;
            });
          }
        }
      });
    },
    /*
     * Load the tree of the File Browser
     * Uses a ztree basic implementation
     */
    loadTree: function () {
      //Configure zTree parameters
      var settings = {
        view: {
          dblClickExpand: false,
          showLine: true,
          selectedMulti: false,
        },
        data: {
          simpleData: {
            enable: true,
            idKey: "id",
            pIdKey: "pId",
            rootPId: null,
          }
        },
        callback: {
          onClick: function (event, treeId, treeNode, clickFlag) {
            Gofast.ITHit.navigate(treeNode.path, false, true);
          },
          onExpand: function (event, treeId, treeNode, clickFlag) {
            Gofast.ITHit.navigate(treeNode.path, true, true);
          },
          onRightClick: Gofast.ITHit._contextMenuHandler,
        }
      }

      //Configure zTree elements
      var treeNodes = [
        { id: 1, pId: null, name: "Sites", open: true, path: "/alfresco/webdav/Sites" },
      ];

      Gofast.additionalGFBNodes.forEach(function (item, index) {
        var new_node = { id: index + 1, pId: null, name: item.split("/").reverse()[0], open: true, path: item }
        treeNodes.push(new_node);
      });

      //Instenciate zTree
      var tree = $("#file_browser_full_tree_element");
      Gofast.ITHit.tree = $.fn.zTree.init(tree, settings, treeNodes);

    },
    /*
     *
     * Fully reload the tree to the given path
     * Call when navigating
     * If noRecursion is set to true, we only update the zTree for the wanted location
     */
    _processTree: function (path, noRecursion, deleteTree) {
      //DEBUG TC
      var currentPath = ["/alfresco/webdav/Sites"];
      Gofast.additionalGFBNodes.forEach(function (item, index) {
        currentPath.push(item);
      });

      //Remove not needed /alfresco/webdav/Sites and other currentPath
      currentPath.forEach(function (item, index, array) {
        if (path.indexOf(item) === 0) {
          path = path.substr(item.size() + 1);
        }
      });

      //Get elements
      var splitPath = path.split('/');
      var nodes = Gofast.ITHit.tree.getSelectedNodes();
      if (deleteTree === true) {
        Gofast.ITHit.tree.removeNode(nodes[0]);
      }

      //Call for recursion if needed
      if (noRecursion) {
        currentPath.forEach(function (item, index, array) {
          Gofast.ITHit._processTreePart(item + '/' + path, []);
        })
      } else {
        currentPath.forEach(function (item, index, array) {
          Gofast.ITHit._processTreePart(item, splitPath);
        })
      }
    },
    /*
     * Called in zTree processing for each opened folder
     */
    _processTreePart: function (path, split) {
      Gofast.ITHit.Session.OpenFolderAsync(path, null,
        function (asyncResult) {

          if (!asyncResult.IsSuccess) {
            console.log("Error ITHit async");
            return;
          }

          var folder = asyncResult.Result;
          folder.GetChildrenAsync(false, null,
            function (asyncResult) {

              if (!asyncResult.IsSuccess) {
                console.log("Error ITHit async");
                return;
              }

              var items = asyncResult.Result;
              var nodes_to_add = []

              //Decode HTML entities
              path = decodeURIComponent(path);

              //Search where to put the elements in zTree
              var node_parent = Gofast.ITHit.tree.getNodeByParam("path", path);

              //Order nodes before processing them, regarding their names
              items.sort(function (a, b) {
                var comp_a = eval('a.DisplayName.toLowerCase()');
                var comp_b = eval('b.DisplayName.toLowerCase()');
                return (comp_a > comp_b) ? 1 : ((comp_b > comp_a) ? -1 : 0);
              });

              //Process items in zTree
              for (var i = 0; i < items.length; i++) {
                var item = items[i];
                //If it's not a folder, continue
                if (item.ResourceType !== "Folder") {
                  continue;
                }

                //Decode HTML entities
                item.Href = decodeURIComponent(item.Href);
                //Remove slash at the end if needed
                if (item.Href.substr(-1, 1) === "/") {
                  item.Href = item.Href.substring(0, item.Href.length - 1);
                }

                //Search if our wanted node exists
                if (Gofast.ITHit.tree.getNodeByParam("path", item.Href) === null) {
                  //Need to add the node to the tree
                  var name = item.Href.split('/');
                  name = name.pop();

                  //Get icon path
                  var icon = Gofast.ITHit._getIconPath(name, item.Href, "image");
                  for (var j = 0; j < Gofast._settings.gofast_ajax_file_browser.archived_spaces.length; j++) {
                    if (decodeURIComponent(item.Href) == Gofast._settings.gofast_ajax_file_browser.archived_spaces[j]) {
                      icon = '/sites/all/modules/gofast/gofast_ajax_file_browser/img/archive_space.png';
                    }
                  }

                  //Set open status to open or close, regarding the full path and the actual item path
                  if (path.indexOf(item.Href) !== -1) {
                    var open = true;
                  } else {
                    var open = false;
                  }

                  var type = item.ResourceType;

                  //Push the node to the array
                  nodes_to_add.push({ id: Math.floor(Math.random() * 999999), pId: node_parent.id, name: name, open: open, path: item.Href, icon: icon, isParent: true, type: type });
                }
              }

              //Add nodes to the tree if needed
              if (nodes_to_add.length > 0) {
                Gofast.ITHit.tree.addNodes(node_parent, nodes_to_add);
                //Configure custom scrollbar to replace the legacy
                var pathname = window.location.pathname; // Returns path
                var excludeScrolbarTheme = pathname.indexOf("home_page_navigation"); // path exist only on mobile domain
                if (excludeScrolbarTheme == -1) {
                  $("#file_browser_full_tree_element").mCustomScrollbar({
                    axis: "xy",
                    theme: "dark-thin"
                  });
                }

                $('.mCSB_container_wrapper .mCSB_container').css('left', '0px');
                //Add drop events
                var nodes = $("#file_browser_full_tree").find("a");
                nodes.attr("ondragover", "Gofast.ITHit.moveDragOver(event)");
                nodes.attr("ondragleave", "Gofast.ITHit.moveDragLeave(event)");


                //Set drag and drop zone for upload
                nodes.each(function (k, elem) {
                  elem.addEventListener("drop", Gofast.ITHit.moveDrop);
                  Gofast.ITHit.Uploader.DropZones.AddById(elem.id);
                });
              }

              //Iterate again if needed
              if (split.length > 0) {
                Gofast.ITHit._processTreePart(path + "/" + split.shift(), split);
              } else {
                //All is done, we can select the item in the zTree if needed
                if (typeof Gofast.ITHit.tree.getSelectedNodes()[0] !== "object" || Gofast.ITHit.tree.getSelectedNodes()[0].path !== Gofast.ITHit.currentPath) {
                  Gofast.ITHit.tree.selectNode(Gofast.ITHit.tree.getNodeByParam("path", decodeURIComponent(Gofast.ITHit.currentPath)));
                }
              }
            }
          );
        }
      );
    },
    /*
     * Check the path and the name passed in params and return the corresponding icon path
     */
    _getIconPath: function (name, path, type) {
      if (type == "image") {
        if (name.substr(0, 1) === '_') { //This is a space
          //Now, we get the type of the space, regarding the path
          var pathSplit = path.split('/');
          var space = pathSplit[4];
          //Then, set the icon
          if (space === "_Groups") {
            var icon = "/sites/all/modules/gofast/gofast_ajax_file_browser/img/users.png";
          } else if (space === "_Organisations") {
            var icon = "/sites/all/modules/gofast/gofast_ajax_file_browser/img/sitemap.png";
          } else if (space === "_Extranet") {
            var icon = "/sites/all/modules/gofast/gofast_ajax_file_browser/img/globe.png";
          } else if (space === "_Public") {
            var icon = "/sites/all/modules/gofast/gofast_ajax_file_browser/img/share.png";
          } else {
            var icon = "/sites/all/modules/gofast/gofast_ajax_file_browser/img/home.png";
          }
        } else if (name == "TEMPLATES") { //This is a templates folder
          var icon = "/sites/all/modules/gofast/gofast_ajax_file_browser/img/folder_template.png";
        } else { //This is a folder
          var icon = "/sites/all/modules/gofast/gofast_ajax_file_browser/img/folder.png";
        }
      }
      if (type == "fa") {
        if (name.substr(0, 1) === '_') { //This is a space
          //Now, we get the type of the space, regarding the path
          var pathSplit = path.split('/');
          var space = pathSplit[4];
          //Then, set the icon
          if (space === "_Groups") {
            var icon = "fa-users";
          } else if (space === "_Organisations") {
            var icon = "fa-sitemap";
          } else if (space === "_Extranet") {
            var icon = "fa-globe";
          } else if (space === "_Public") {
            var icon = "fa-share-alt";
          } else {
            var icon = "fa-home";
          }
        } else if (name === "TEMPLATES") {
          var icon = "TEMPLATE";
        } else { //This is a folder
          var icon = "fa-folder";
        }
      }
      return icon;
    },
    /*
     * Process items into the file browser when it's loaded
     * Called when navigation occures
     */
    _processItems: function (items, fullPath) {
      if (Gofast.ITHit.processingItems) {
        //We are already processing items, wait for lock release
        setTimeout(function () {
          Gofast.ITHit._processItems(items, fullPath);
        }, 100);
        return;
      }
      NProgress.set(0.7);

      Gofast.ITHit.processingItems = true;
      var itemHTML = "";
      $(".file_browser_full_files_element").remove();

      //First, if we are not localized at the root path '/alfresco/webdav/Sites'

      //Get parent path from given path
      var path = fullPath;
      if (path.substr(-1, 1) === "/") {
        path = path.substring(0, path.length - 1);
      }
      path = path.split('/');
      path.pop();
      var name = decodeURIComponent(path.last());
      path = path.join('/');

      //Get the 'Back' button at the top of the list
      itemHTML += Gofast.ITHit._getBackButton(name);

      if (path !== "/alfresco/webdav") {
        //Add the item to the list
        var processedItem = $('#file_browser_full_files_table').find('tbody:last-child').append(itemHTML);
        processedItem = processedItem.find('tr').last();

        //Attach event handlers to the processed item
        Gofast.ITHit._attachEvents(null, processedItem, path);
      }

      //Replace items last modified dates with last version date
      //Split folders and files
      var folders = items.filter(function (e) { return e.ResourceType === 'Folder'; });
      var resources = items.filter(function (e) { return e.ResourceType === 'Resource'; });

      if (resources.length < 300 && folders.length < 300) {
        //Get the documents paths
        var Hrefs_files = resources.map(function (item) { return item.Href.replace("/alfresco/webdav/", ""); });
        var Hrefs_folders = folders.map(function (item) { return item.Href.replace("/alfresco/webdav/", ""); });
        //Send a request to Alfresco to map versionning dates
        $.ajax({
          url: location.origin + '/alfresco/service/post/file_browser_extra_informations?alf_ticket=' + Drupal.settings.ticket,
          type: "POST",
          timeout: 2000,
          data: { files: JSON.stringify(Hrefs_files), folders: JSON.stringify(Hrefs_folders), current_folder: fullPath.replace("/alfresco/webdav/", "") },
          contentType: "application/json; charset=utf-8",
          dataType: "json",
          indexValue: { folders: folders, resources: resources }
        }).always(function (response) {
          Gofast.ITHit._processItemsAfterAsync(this.indexValue.folders, this.indexValue.resources, response);
          Gofast.ITHit.processingItems = false;
        });
      } else {
        Gofast.ITHit._processItemsAfterAsync(folders, resources, null);
        Gofast.ITHit.processingItems = false;
      }
    },
    /*
     * Process items into the file browser when it's loaded
     * Called when navigation occures
     */
    _processItemsAfterAsync: function (folders, resources, response) {
      NProgress.set(0.9);
      if (response !== null && typeof response !== "undefined" && typeof response.status === "undefined") {

        if (response.files && response.files.dates && response.files.dates.length > 0) {
          for (var j = 0; j < resources.length; j++) {
            if (response.files.dates[j]) {
              resources[j].LastModified = new Date(response.files.dates[j]);
            }
          }
        }

        if (response.files && response.files.permissions && response.files.permissions.length > 0) {
          for (var j = 0; j < resources.length; j++) {
            if (response.files.permissions[j]) {
              resources[j].Permission = response.files.permissions[j];
            }
          }
        }

        if (response.files && response.files.visibility && response.files.visibility.length > 0) {
          for (var j = 0; j < resources.length; j++) {
            if (response.files.visibility[j]) {
              resources[j].Visibility = response.files.visibility[j];
            }
          }
        }

        if (response.folders && response.folders.permissions && response.folders.permissions.length > 0) {
          for (var j = 0; j < folders.length; j++) {
            if (response.folders.permissions[j]) {
              folders[j].Permission = response.folders.permissions[j];
            }
          }
        }

        if (response.current_folder && response.current_folder.permissions && response.current_folder.permissions.length > 0) {
          ; var permission = response.current_folder.permissions[0];
          Gofast.ITHit._setCurrentInfo(permission);
        } else {
          Gofast.ITHit._setCurrentInfo();
        }

      } else {
        console.log("timeout");
        for (var j = 0; j < folders.length; j++) {
          folders[j].Timeout = true;
        }

        for (var j = 0; j < resources.length; j++) {
          resources[j].Timeout = true;
        }
      }

      //Merge the arrays
      items = folders.concat(resources);

      //Sort items
      items = Gofast.ITHit.sort(items);

      for (var i = 0; i < items.length; i++) {
        //Format the item
        itemHTML = "";
        var item = items[i];
        var itemHTML = Gofast.ITHit._formatItem(item);

        //Add the item to the list
        var processedItem = $('#file_browser_full_files_table').find('tbody:last-child').append(itemHTML);
        processedItem = processedItem.find('tr').last();

        //Attach event handlers to the processed item
        Gofast.ITHit._attachEvents(item, processedItem);

        //Configure custom scrollbar to replace the legacy
        $("#file_browser_full_files_table").mCustomScrollbar({
          theme: "dark-thin",
          callbacks: {
            onInit: function () {
              //Trigger the auto sizing of columns
              $('#name_header').trigger('resize');
              $('#size_header').trigger('resize');
              $('#type_header').trigger('resize');
            }
          },
        });
      }

      //Trigger the auto sizing of columns
      $('#name_header').trigger('resize');
      $('#size_header').trigger('resize');
      $('#type_header').trigger('resize');

      //Make the folders dropable
      var folders = $(".file_browser_full_files_element").find('.item-real-type:contains("Folder")').parent();
      folders.attr('ondragover', "Gofast.ITHit.insideDragOver(event)");
      folders.attr('ondragleave', "Gofast.ITHit.insideDragLeave(event)");
      folders.attr('ondrop', "Gofast.ITHit.insideDrop(event)");
      folders.each(function (k, elem) {
        elem.addEventListener("drop", Gofast.ITHit.insideDrop);
      });
      NProgress.done();
    },
    /*
     * Set info icon for the current path
     */
    _setCurrentInfo: function (permission) {
      //Remove this for now
      return;
      var icon_container = $("#file_browser_full_toolbar_info_icons");
      infoHTML = "";

      if (!permission) {
        var title = Drupal.t("Unable to retrieve the informations because there are to many elements or the request took too long", {}, { context: "gofast:gofast_ajax_file_browser" });
        infoHTML += "<i title=\"" + title + "\" class='fa fa-question' style='margin-right: 3px; color: #777;'></i>";
      } else {
        infoHTML = Gofast.ITHit._formatInfo(permission, null, "Folder");
      }

      icon_container.html(infoHTML);
    },
    /*
     * Sort items
     */
    sort: function (items, forceName) {
      //Split folders and files
      var folders = items.filter(function (e) { return e.ResourceType === 'Folder'; });
      var resources = items.filter(function (e) { return e.ResourceType === 'Resource'; });

      //Process the sort
      if (Gofast.ITHit.sortOrder === 'asc' || forceName) {
        folders.sort(function (a, b) {
          if (forceName) {
            var comp_a = eval('a.DisplayName.toLowerCase()');
            var comp_b = eval('b.DisplayName.toLowerCase()');
          }
          else if (Gofast.ITHit.sortType === 'type') {
            var comp_a = Gofast.ITHit._getTypeFromRessourceType(a.DisplayName, a.Href, a.ResourceType);
            var comp_b = Gofast.ITHit._getTypeFromRessourceType(b.DisplayName, b.Href, b.ResourceType);
          } else {
            var comp_a = eval('a.' + Gofast.ITHit.sortType);
            var comp_b = eval('b.' + Gofast.ITHit.sortType);
          }
          return (comp_a > comp_b) ? 1 : ((comp_b > comp_a) ? -1 : 0);
        });
        resources.sort(function (a, b) {
          if (forceName) {
            var comp_a = eval('a.DisplayName.toLowerCase()');
            var comp_b = eval('b.DisplayName.toLowerCase()');
          }
          else if (Gofast.ITHit.sortType === 'type') {
            var comp_a = Gofast.ITHit._getTypeFromRessourceType(a.DisplayName, a.Href, a.ResourceType);
            var comp_b = Gofast.ITHit._getTypeFromRessourceType(b.DisplayName, b.Href, b.ResourceType);
          } else {
            var comp_a = eval('a.' + Gofast.ITHit.sortType);
            var comp_b = eval('b.' + Gofast.ITHit.sortType);
          }
          return (comp_a > comp_b) ? 1 : ((comp_b > comp_a) ? -1 : 0);
        });
      } else {
        folders.sort(function (a, b) {
          if (forceName) {
            var comp_a = eval('a.DisplayName.toLowerCase()');
            var comp_b = eval('b.DisplayName.toLowerCase()');
          }
          else if (Gofast.ITHit.sortType === 'type') {
            var comp_a = Gofast.ITHit._getTypeFromRessourceType(a.DisplayName, a.Href, a.ResourceType);
            var comp_b = Gofast.ITHit._getTypeFromRessourceType(b.DisplayName, b.Href, b.ResourceType);
          } else {
            var comp_a = eval('a.' + Gofast.ITHit.sortType);
            var comp_b = eval('b.' + Gofast.ITHit.sortType);
          }
          return (comp_a < comp_b) ? 1 : ((comp_b < comp_a) ? -1 : 0);
        });
        resources.sort(function (a, b) {
          if (forceName) {
            var comp_a = eval('a.DisplayName.toLowerCase()');
            var comp_b = eval('b.DisplayName.toLowerCase()');
          }
          else if (Gofast.ITHit.sortType === 'type') {
            var comp_a = Gofast.ITHit._getTypeFromRessourceType(a.DisplayName, a.Href, a.ResourceType);
            var comp_b = Gofast.ITHit._getTypeFromRessourceType(b.DisplayName, b.Href, b.ResourceType);
          } else {
            var comp_a = eval('a.' + Gofast.ITHit.sortType);
            var comp_b = eval('b.' + Gofast.ITHit.sortType);
          }
          return (comp_a < comp_b) ? 1 : ((comp_b < comp_a) ? -1 : 0);
        });
      }

      //Merge the arrays
      items = folders.concat(resources);

      return items;
    },
    /*
     * Return HTML formatted back button
     */
    _getBackButton: function (name) {
      var itemHTML = "";

      itemHTML += "<tr id='file_browser_back_button' class='file_browser_full_files_element' style='width:100%; display: inline-block;'>";
      //Icon
      itemHTML += "<td style='width:10%;'>";
      itemHTML += "<span class='fa fa-arrow-left' style='color:#3498db'></span>";
      itemHTML += "</td>";

      //Name
      itemHTML += "<td style='width:35%;'>";
      itemHTML += Drupal.t("Back to ", {}, { context: "gofast:ajax_file_browser" }) + name;
      itemHTML += "</td>";

      //Size
      itemHTML += "<td style='width:15%;'>";
      itemHTML += "</td>";

      //Type
      itemHTML += "<td style='width:15%;'>";
      itemHTML += "</td>";

      //Modification date
      itemHTML += "<td style='width:15%;'>";
      itemHTML += "</td>";

      //Infos
      itemHTML += "<td style='width:10%;'>";
      itemHTML += "</td>";
      itemHTML += "</tr>";

      return itemHTML;
    },
    /*
     * Get an Item and return the corresponding HTML
     * Called when items are processed
     */
    _formatItem: function (item) {
      var itemHTML = "";
      var HTMLClass = "";
      var trStyle = "";
      var float = 0;
      var tdIconSize = "";
      var tdNameSize = "";

      //Display type is icons
      if (Gofast.ITHit.display === 'icons') {
        HTMLClass = 'display-icons';
        trStyle = 'width:25%;height: 155px;';
        tdIconSize = "100%;text-align: center;font-size:80px;";
        tdNameSize = "100%;text-align: center;height:40px;white-space: normal;";
        if (float < 4) {
          trStyle += "float: left;";
          float++;
        } else {
          float = 0;
        }
      } else { //Display type is details
        trStyle = 'width:100%;';
        tdIconSize = "5%;";
        tdNameSize = "35%;";
      }
      itemHTML += "<tr draggable='true' ondragstart='Gofast.ITHit.moveDragStart(event)' class='file_browser_full_files_element " + HTMLClass + "' style='" + trStyle + " display: block;white-space: nowrap;'>";
      //checkbox to select multiple
      itemHTML += "<td style='width:5%'><input id='cbxSelect' type='checkbox'></td>"
      //Icon
      itemHTML += "<td title='" + item.DisplayName + "' style='width:" + tdIconSize + "; height:75px;' class='item-icon'>";
      if (item.ResourceType == "Folder") { //It's a folder
        var icon = Gofast.ITHit._getIconPath(item.DisplayName, item.Href, "fa");
        for (var i = 0; i < Gofast._settings.gofast_ajax_file_browser.archived_spaces.length; i++) {
          if (decodeURIComponent(item.Href) == Gofast._settings.gofast_ajax_file_browser.archived_spaces[i] + '/') {
            icon = 'fa-archive';
          }
        }
        if (icon === "TEMPLATE") {
          icon = "fa-folder";
          var color = "#f0685a";
        } else {
          color = "#3498db";
        }
        itemHTML += "<span class='fa " + icon + "' style='color:" + color + "'></span>";
      } else { //It's a document, use mapping to find the proper icon
        //Get extension
        var ext = item.DisplayName.split('.').pop().toLowerCase();
        //toLowerCase extension GOFAST-4662

        //Get font
        var font = Drupal.settings.ext_map[ext];

        if (typeof font !== "undefined") { //Known
          if (font === "fa-file-image-o" && Gofast.ITHit.display == "icons") {
            //Load image
            itemHTML += "<img height=\"75px\" src='" + location.origin + item.Href + "' />";
          } else {
            itemHTML += "<span class='fa " + font + "'></span>";
          }
        } else { //Unknown
          itemHTML += "<span class='fa fa-file-o file-other'></span>";
        }
      }

      if (typeof item.ActiveLocks !== "undefined" && item.ActiveLocks.length !== 0) {
        if (Gofast.ITHit.display === 'icons') {
          itemHTML += "<span class='fa fa-lock' style='color:red;font-size: 0.3em;float: right;position: relative;margin-left: -13px;top: 54px;left: -40px;'></span>";
        } else {
          itemHTML += "<span class='fa fa-lock' style='color:red;font-size: 0.7em;float: right;position: relative;top: -9px;'></span>";
        }
      }
      itemHTML += "</td>";

      //Name
      itemHTML += "<td class='item-name' title='" + item.DisplayName + "' style='width:" + tdNameSize + "'>";
      itemHTML += item.DisplayName;
      itemHTML += "</td>";

      //Size
      itemHTML += "<td class='item-size' style='width:15%;'>";
      if (typeof item.ContentLength !== "undefined" && item.ContentLength !== 0) {
        itemHTML += Gofast.ITHit._octetToString(item.ContentLength);
      }
      itemHTML += "</td>";

      //Type
      itemHTML += "<td class='item-type' style='width:15%;'>";
      itemHTML += Gofast.ITHit._getTypeFromRessourceType(item.DisplayName, item.Href, item.ResourceType);
      itemHTML += "</td>";

      //Type
      itemHTML += "<td class='item-real-type' style='display:none;'>";
      itemHTML += item.ResourceType;
      itemHTML += "</td>";

      //Modification date
      itemHTML += "<td class='item-date' style='width:15%;'>";
      if (typeof item.LastModified !== "undefined") {
        var date = item.LastModified;
        //Display date, regarding the user language
        if (Gofast.get('user').language === "en") {
          var displayedDate = ("0" + (date.getMonth() + 1)).slice(-2) + "/" + ("0" + (date.getDate())).slice(-2) + "/" + date.getFullYear().toString().slice(-2) + " " + ("0" + (date.getHours())).slice(-2) + ":" + ("0" + (date.getMinutes())).slice(-2);
        } else {
          var displayedDate = ("0" + (date.getDate())).slice(-2) + "/" + ("0" + (date.getMonth() + 1)).slice(-2) + "/" + date.getFullYear().toString().slice(-2) + " " + ("0" + (date.getHours())).slice(-2) + ":" + ("0" + (date.getMinutes())).slice(-2);
        }
        itemHTML += displayedDate;
      }
      itemHTML += "</td>";

      //Prepare the info header
      itemHTML += "<td class='item-info' style='width:10%;'>";
      if (!item.Timeout) {
        itemHTML += Gofast.ITHit._formatInfo(item.Permission, item.Visibility, item.ResourceType);
      } else {
        var title = Drupal.t("Unable to retrieve the informations because there are to many elements or the request took too long", {}, { context: "gofast:gofast_ajax_file_browser" });
        itemHTML += "<i title=\"" + title + "\" class='fa fa-question' style='margin-right: 3px; color: #777;'></i>";
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
     *
     * @param {string} Access permission
     * @returns {string} HTML formated INFO column
     */
    _formatInfo: function (permission, visibility, type) {
      var output = "";

      //Permissions
      if (typeof permission !== "undefined") {
        if (type == "Resource") {
          switch (permission) {
            case "owner":
              var title = Drupal.t("You can manage this content (edition, deletion...) because you have owner rights on it.", {}, { context: "gofast:gofast_ajax_file_browser" });
              output += "<i title=\"" + title + "\" class='fa fa-user-circle-o' style='margin-right: 3px; color: #777;'></i>";
              break;
            case "administrator":
              var title = Drupal.t("You can manage this content (edition, deletion...) because you administer one of it's spaces.", {}, { context: "gofast:gofast_ajax_file_browser" });
              output += "<i title=\"" + title + "\" class='fa fa-shield' style='margin-right: 3px; color: #777;'></i>";
              break;
            case "contributor":
              var title = Drupal.t("You can collaborate on this content (edition, commenting) but you won't be able to delete or move it.", {}, { context: "gofast:gofast_ajax_file_browser" });
              output += "<i title=\"" + title + "\" class='fa fa-user' style='margin-right: 3px; color: #777;'></i>";
              break;
            case "readonly":
              var title = Drupal.t("You are only able to consult this content and comment it because you are read only on all of it's spaces.", {}, { context: "gofast:gofast_ajax_file_browser" });
              output += "<i title=\"" + title + "\" class='fa fa-user-o' style='margin-right: 3px; color: #777;'></i>";
              break;
            case "onlyreadonly":
              var title = Drupal.t("You are only able to consult this content and comment it because it have special permissions (archived, DUA...).", {}, { context: "gofast:gofast_ajax_file_browser" });
              output += "<i title=\"" + title + "\" class='fa fa-archive' style='margin-right: 3px; color: #777;'></i>";
              break;
          }
        } else {
          switch (permission) {
            case "owner":
              var title = Drupal.t("You have owner permissions on this folder/space but you won't have extra permissions on the content in this folder/space because you are read only in this space.", {}, { context: "gofast:gofast_ajax_file_browser" });
              output += "<i title=\"" + title + "\" class='fa fa-user-circle-o' style='margin-right: 3px; color: #777;'></i>";
              break;
            case "administrator":
              var title = Drupal.t("You have administration permissions, you will be able to manage all content inside this folder/space.", {}, { context: "gofast:gofast_ajax_file_browser" });
              output += "<i title=\"" + title + "\" class='fa fa-shield' style='margin-right: 3px; color: #777;'></i>";
              break;
            case "contributor":
              var title = Drupal.t("You have contribution permissions, you will be able to collaborate on all content inside this folder/space.", {}, { context: "gofast:gofast_ajax_file_browser" });
              output += "<i title=\"" + title + "\" class='fa fa-user' style='margin-right: 3px; color: #777;'></i>";
              break;
            case "readonly":
              var title = Drupal.t("You have read only permissions, you can see all the content in this folder/space but you won't get extra permissions.", {}, { context: "gofast:gofast_ajax_file_browser" });
              output += "<i title=\"" + title + "\" class='fa fa-user-o' style='margin-right: 3px; color: #777;'></i>";
              break;
            case "onlyreadonly":
              var title = Drupal.t("This is a special folder/space with read only permissions.", {}, { context: "gofast:gofast_ajax_file_browser" });
              output += "<i title=\"" + title + "\" class='fa fa-user-o' style='margin-right: 3px; color: #777;'></i>";
              break;
          }
        }
      }

      //Visibility
      if (type === "Resource") {
        if (visibility && visibility.length === 1) {
          output += "";
        } else if (visibility && visibility.length > 1) {
          var title = Drupal.t("This content is in multiple locations : ", {}, { context: "gofast:gofast_ajax_file_browser" }) + decodeURIComponent(visibility.join(", ")).replace(/\/webdav\/Sites/g, "");
          output += "<i title=\"" + title + "\" class='fa fa-share-alt' style='margin-right: 3px; color: #777;'></i>";
        } else if (typeof permission !== "undefined") {
          var title = Drupal.t("This content is in multiple locations but you don't have access to all these locations.", {}, { context: "gofast:gofast_ajax_file_browser" });
          output += "<i title=\"" + title + "\" class='fa fa-share-alt' style='margin-right: 3px; color: #777;'></i>";
        }
      }

      return output;
    },
    /*
     *
     */
    _getTypeFromRessourceType: function (name, path, type) {
      if (type === "Resource") {
        return name.split('.').pop().toUpperCase()
      } else {
        if (name.substr(0, 1) === '_') { //This is a space
          //Now, we get the type of the space, regarding the path
          var pathSplit = path.split('/');
          var space = pathSplit[4];
          //Then, set the type
          if (space === "_Groups") {
            return Drupal.t('Group', {}, { context: 'gofast:ajax_file_browser' });
          } else if (space === "_Organisations") {
            return Drupal.t('Organisation', {}, { context: 'gofast:ajax_file_browser' });
          } else if (space === "_Extranet") {
            return Drupal.t('Extranet', {}, { context: 'gofast:ajax_file_browser' });
          } else if (space === "_Public") {
            return Drupal.t('Public space', {}, { context: 'gofast:ajax_file_browser' });
          } else {
            return Drupal.t('Private space', {}, { context: 'gofast:ajax_file_browser' });
          }
        } else if (name == "TEMPLATES") {
          return Drupal.t('Templates folder', {}, { context: 'gofast:ajax_file_browser' });
        } else { //This is a folder
          return Drupal.t('Folder', {}, { context: 'gofast:ajax_file_browser' });
        }
      }
    },
    /*
     * Get an Queued Item and return the corresponding HTML
     * Called when queue items are processed
     */
    _formatQueueItem: function (item) {
      var cancellable = false;
      var itemHTML = "";
      itemHTML += "<tr class='file_browser_full_upload_element' style='width:100%; display: inline-block;'>";
      //Icon
      //Set icon regarding the status
      var fa_icon = "";
      var color = "#3498db";
      if (item.status === 0) {
        fa_icon = "fa-clock-o";
        color = "#3498db";
        cancellable = true;
      } else if (item.status === 1) {
        fa_icon = "fa-play";
        color = '#3498db';
        cancellable = true;
      } else if (item.status === 3) {
        fa_icon = "fa-times";
        color = '#d9534f';
      } else if (item.status === 4) {
        fa_icon = "fa-check";
        color = '#5cb85c';
      }
      itemHTML += "<td style='width:5%;'>";
      itemHTML += "<span class='fa " + fa_icon + "' style='color:" + color + "'></span>";
      itemHTML += "</td>";

      //Name + Path
      itemHTML += "<td style='width:65%;'>";
      itemHTML += item.displayNamePath;
      itemHTML += "</td>";

      //Operation
      itemHTML += "<td style='width:10%;'>";
      itemHTML += item.displayOperation;
      itemHTML += "</td>";

      //Progression
      itemHTML += "<td style='width:18%;height:22px;'>";
      itemHTML += '<div class="progress" style="display:block; width:70%;">';
      itemHTML += '<div class="progress-bar bg-success" role="progressbar" style="width: ' + item.progression + '%" aria-valuenow="' + item.progression + '" aria-valuemin="0" aria-valuemax="100">' + item.progression + '%</div>';
      itemHTML += '</div>';
      if (cancellable && item.operation === "upload") { //Waiting or in progress uploads are cancellable
        itemHTML += '<button type="button" style="height:20px;padding-left:5px;padding-right:5px;padding-top:0px;padding-bottom:0px;float:right;margin-top:-35px;" onClick="Gofast.ITHit.cancelUpload(\'' + item.uuid + '\')" class="btn btn-danger"><i class="fa fa-times"></i></button>';
      }
      itemHTML += "</td>";

      itemHTML += "</tr>";
      return itemHTML;
    },
    /*
     * Get a value in octet and return it in the appropriate size value
     */
    _octetToString: function (aSize) {
      aSize = Math.abs(parseInt(aSize, 10));
      var def = [[1, 'octets'], [1024, 'ko'], [1024 * 1024, 'Mo'], [1024 * 1024 * 1024, 'Go'], [1024 * 1024 * 1024 * 1024, 'To']];
      for (var i = 0; i < def.length; i++) {
        if (aSize < def[i][0])
          return (aSize / def[i - 1][0]).toFixed(2) + ' ' + def[i - 1][1];
      }
    },
    /*
     * Attach event handlers to the processed item passed in param
     * Called in the item processing phase
     */
    _attachEvents: function (item, processedItem, path) {
      if (typeof item !== "undefined" && item !== null) {
        if (Gofast._settings.isMobile) {
          //Disable resize on double tap
          processedItem.on('touchend', function (e) {
            e.preventDefault();
            //Propagate a click event
            $(this).click();
          });

          //Double click detection on mobile version
          var touchtime = 0;
          processedItem.on("click", function () {
            if (((new Date().getTime()) - touchtime) < 500) {
              processedItem.trigger('dblclick');
            }
            touchtime = new Date().getTime();
          });
        }
        //Folder navigation triggering at double click
        if (item.ResourceType === "Folder") {
          processedItem.dblclick(function () {
            var rename_form = $("#rename-form");
            if (processedItem.find(rename_form).length === 0) {
              Gofast.ITHit.navigate(item.Href);
            }
          });
        }
        if (item.ResourceType === "Resource") {
          //Go to node in ajax triggering at double click
          processedItem.dblclick(function () {
            var rename_form = $("#rename-form");
            if (processedItem.find(rename_form).length === 0) {
              if (!Gofast._settings.isMobile) {
                Gofast.addLoading();
              }
              Gofast.ITHit.goToNode(item.Href, false, item.DisplayName);
              clearTimeout(Gofast.willRenameElement);
            }
          });
          processedItem.on('mousedown', function (e) {
            if (e.which == 2) {
              Gofast.ITHit.goToNode(item.Href, true, item.DisplayName);
              clearTimeout(Gofast.willRenameElement);
            }
          });
        }

        //Allow to select items
        processedItem.find("td>input[type=checkbox]").on('mousedown touchstart', function (e) {
          e.stopPropagation();
          e.stopImmediatePropagation();
          e.preventDefault();
          Gofast.ITHit.prop = true;
          if (processedItem.hasClass('selected')) {
            processedItem.removeClass('selected');
            if ($(".selected").length == 0) {
              //add class disabled on copy and cut options
              $('#file_browser_tooolbar_copy').prop('disabled', true);
              $('#file_browser_tooolbar_cut').prop('disabled', true);
              //disable manage button
              $('#file_browser_tooolbar_manage').prop('disabled', true);
              //disable contextual actions
              $('#file_browser_tooolbar_contextual_actions').prop('disabled', true);
            }

          } else {
            processedItem.addClass('selected');
            //Remove class disabled on copy and cut options
            $('#file_browser_tooolbar_copy').prop('disabled', false);
            $('#file_browser_tooolbar_cut').prop('disabled', false);
            //Enable manage button
            var path = $(processedItem[0]).find('td.item-path').text();
            var type = $(processedItem[0]).find('td.item-type').text();

            if (path === '/alfresco/webdav/Sites/_Groups/' || path === '/alfresco/webdav/Sites/_Extranet/' || path === '/alfresco/webdav/Sites/_Organisations/' || path === '/alfresco/webdav/Sites/_Public/'
              || Gofast._settings.gofast_ajax_file_browser.archived_spaces.indexOf(path.substring(0, path.length - 1)) !== -1 || type === "Folder" || type === "Group" || type === "Organisation") {
              $('#file_browser_tooolbar_manage').prop('disabled', true);

            } else {
              if ($('.file_browser_full_files_element.selected').length > 0) {
                $('.file_browser_full_files_element.selected').each(function () {
                  if ($(this).find('.item-real-type').text() === "Folder" || $(this).find('.item-real-type').text() === "Group" || $(this).find('.item-real-type').text() === "Organisations" || $(this).find('.item-real-type').text() === "Templates folder" || $(this).find('.item-real-type').text() === "Extranet" || $(this).find('.item-real-type').text() === "Public space") {
                    $('#file_browser_tooolbar_manage').prop('disabled', true);
                    return false;
                  } else {
                    $('#file_browser_tooolbar_manage').prop('disabled', false);
                  }
                });
              } else {
                $('#file_browser_tooolbar_manage').prop('disabled', false);
              }
            }
            //Enable contextual actions
            $('#file_browser_tooolbar_contextual_actions').prop('disabled', false);

            if (Drupal.settings.isMobile) {
              //Check the box
              $(this).prop("checked", true);
            }
          }
        });
        processedItem.find("td>input[type=checkbox]").on('mouseup touchend', function (e) {
          if ($('.file_browser_full_files_element.selected').length > 0) {
            $('.file_browser_full_files_element.selected').each(function () {
              if ($(this).find('.item-real-type').text() === "Folder" || $(this).find('.item-real-type').text() === "Group" || $(this).find('.item-real-type').text() === "Organisations" || $(this).find('.item-real-type').text() === "Templates folder" || $(this).find('.item-real-type').text() === "Extranet" || $(this).find('.item-real-type').text() === "Public space") {
                $('#file_browser_tooolbar_manage').prop('disabled', true);
                return false;
              } else {
                $('#file_browser_tooolbar_manage').prop('disabled', false);
              }
            });
          } else {
            $('#file_browser_tooolbar_manage').prop('disabled', true);
          }
        });
        processedItem.on('mousedown touchstart', function (e) {
          //Remove class disabled on copy and cut options
          $('#file_browser_tooolbar_copy').prop('disabled', false);
          $('#file_browser_tooolbar_cut').prop('disabled', false);
          //Enable manage button
          var path = $(processedItem[0]).find('td.item-path').text();
          var type = $(processedItem[0]).find('td.item-type').text();
          if (path === '/alfresco/webdav/Sites/_Groups/' || path === '/alfresco/webdav/Sites/_Extranet/' || path === '/alfresco/webdav/Sites/_Organisations/' || path === '/alfresco/webdav/Sites/_Public/'
            || Gofast._settings.gofast_ajax_file_browser.archived_spaces.indexOf(path.substring(0, path.length - 1)) !== -1 || type === "Folder" || type === "Group" || type === "Organisation" || type === "Templates folder") {
            $('#file_browser_tooolbar_manage').prop('disabled', true);

          } else {
            $('#file_browser_tooolbar_manage').prop('disabled', false);
          }
          //Enable contextual actions
          $('#file_browser_tooolbar_contextual_actions').prop('disabled', false);

          if (e.shiftKey) {
            if ($(".selected").length > 0) {
              if (processedItem.hasClass('selected')) {

              } else if ($(".selected").first().position().top > processedItem.position().top || $(".selected").first().position().left > processedItem.position().left) {
                processedItem.nextUntil($(".selected").first(), "tr").not('.search-hidden').find("td>input[type=checkbox]").prop('checked', true);
                processedItem.nextUntil($(".selected").first(), "tr").not('.search-hidden').addClass('selected');
              } else {
                $(".selected").not('.search-hidden').last().nextUntil(processedItem, "tr").find("td>input[type=checkbox]").prop('checked', true);
                $(".selected").last().nextUntil(processedItem, "tr").not('.search-hidden').addClass('selected');
              }
              processedItem.addClass('selected');
              processedItem.find("td>input[type=checkbox]").prop('checked', true);
            } else {
              $(".selected").removeClass("selected");
              processedItem.addClass('selected');
            }
          } else if (e.ctrlKey) {
            if (processedItem.hasClass('selected')) {
              processedItem.removeClass('selected');
              processedItem.find("td>input[type=checkbox]").prop('checked', false);
            } else {
              processedItem.addClass('selected');
              processedItem.find("td>input[type=checkbox]").prop('checked', true);
            }
          } else {
            if (!processedItem.hasClass('selected')) {
              $(".selected").removeClass("selected");
              processedItem.addClass('selected');
              $("td>input[type=checkbox]:checked").prop('checked', false);
              processedItem.find("td>input[type=checkbox]").prop('checked', true);
            } else if (processedItem.find("#rename-form").length === 0 && $(".selected").length === 1 && e.which === 1) {
              /*if (((new Date().getTime()) - touchtimerename) > 500) {
                  clearTimeout(Gofast.willRenameElement);
                  Gofast.willRenameElement = setTimeout(function(){ //Prevent dbl click to trigger this
                      Gofast.ITHit.rename(item.Href);
                  }, 500);
              }*/
            }
            //touchtimerename = new Date().getTime();
          }
          //Enable cart button if no folder are selected, else disable it
          if ($('.selected').filter(function (k, i) { return $(i).find('.item-real-type').text() === "Folder"; }).length === 0) {
            $('#file_browser_tooolbar_cart_button').prop('disabled', false);
          } else {
            $('#file_browser_tooolbar_cart_button').prop('disabled', true);
          }
        });
        processedItem.on('mouseup touchend', function (e) {
          if (Gofast.ITHit.prop) {
            Gofast.ITHit.prop = false;
            return;
          }
          if ($('.ui-resizable-resizing').length !== 0) {
            return;
          }
          if (!e.shiftKey && !e.ctrlKey && e.button === 0) {
            $(".selected").removeClass("selected");
            processedItem.addClass('selected');
            $("td>input[type=checkbox]:checked").prop('checked', false);
            processedItem.find("td>input[type=checkbox]").prop('checked', true);
          }

          //Enable cart button if no folder are selected, else disable it
          if ($('.selected').filter(function (k, i) { return $(i).find('.item-real-type').text() === "Folder"; }).length === 0) {
            $('#file_browser_tooolbar_cart_button').prop('disabled', false);
          } else {
            $('#file_browser_tooolbar_cart_button').prop('disabled', true);
          }
          if ($('.file_browser_full_files_element.selected').length > 0) {
            $('.file_browser_full_files_element.selected').each(function () {
              if ($(this).find('.item-real-type').text() === "Folder" || $(this).find('.item-real-type').text() === "Group" || $(this).find('.item-real-type').text() === "Organisations" || $(this).find('.item-real-type').text() === "Templates folder" || $(this).find('.item-real-type').text() === "Extranet" || $(this).find('.item-real-type').text() === "Public space") {
                $('#file_browser_tooolbar_manage').prop('disabled', true);
                return false;
              } else {
                $('#file_browser_tooolbar_manage').prop('disabled', false);
              }
            });
          } else {
            $('#file_browser_tooolbar_manage').prop('disabled', true);
          }
        });

        //Display menu at right click event, select the item if it's not already selected
        processedItem.contextmenu(function (e) {
          if (!processedItem.hasClass('selected')) {
            processedItem.click();
          } else {
            // If you don't edit input field rename doc, dispaly ContextMenu
            if (e.target.id !== "rename-form") {
              Gofast.ITHit._contextMenuHandler(e);
            }//Else not think to do
          }
        });
      };

      //Navigation triggering at single click
      if (typeof path !== "undefined") {
        processedItem.click(function () {
          Gofast.ITHit.navigate(path);
        });
      }
    },
    /*
     * Attach again click events to an item
     * Usually called after a rename operation
     */
    _attachEventsAgain: function (item, processedItem) {
      processedItem.off('mousedown');
      processedItem.off('dblclick');
      //Folder navigation triggering at double click
      if (item.ResourceType === "Folder") {
        processedItem.dblclick(function () {
          var rename_form = $("#rename-form");
          if (processedItem.find(rename_form).length === 0) {
            Gofast.ITHit.navigate(item.Href);
          }
        });
      }
      if (item.ResourceType === "Resource") {
        //Go to node in ajax triggering at double click
        processedItem.dblclick(function () {
          var rename_form = $("#rename-form");
          if (processedItem.find(rename_form).length === 0) {
            if (!Gofast._settings.isMobile) {
              Gofast.addLoading();
            }
            Gofast.ITHit.goToNode(item.Href, false, item.DisplayName);
          }
        });
        processedItem.on('mousedown', function (e) {
          if (e.which == 2) {
            Gofast.ITHit.goToNode(item.Href, true, item.DisplayName);
          }
        });
      }
    },
    /*
     * Attach event handlers to the processed queue item passed in param
     * Called in the queue item processing phase
     */
    _attachQueueEvents: function (item, processedItem) {
      if (typeof item !== "undefined" && item !== null) {
      }
    },
    /*
     * Triggered by right clicking an item
     * Display the corresponding menu
     */
    _contextMenuHandler: function (e, tId, node) {
      //Prevent any default browser action, we are going to manage all actions
      e.preventDefault();

      //Prevent click on nothing
      if (node == null && typeof node == 'object') {
        return;
      }
      //If another menu is open, destroy it
      if ($("#file_browser_full_files").find('.gofast-node-actions').is('.open') !== false) {
        $("#file_browser_full_files").find('.gofast-node-actions').remove();
      }

      //Display the loader, waiting the ajax request to get the menu and positioning
      //dynamically the menu
      var menu = $('<div class="gofast-node-actions"><ul class="dropdown-menu gofast-dropdown-menu" role="menu"><li><div class="loader-activity-menu-active"></div></li></ul></div>').appendTo("#file_browser_full_files");

      //Show the menu and position it
      menu.addClass('open');
      menu.css('position', 'fixed');
      if (typeof e.clientX == "undefined" && typeof e.clientY == "undefined") {
        e.clientX = $("#file_browser_tooolbar_contextual_actions").offset().left;
        e.clientY = $("#file_browser_tooolbar_contextual_actions").offset().top - window.scrollY;
      }
      menu.css('left', e.clientX);
      menu.css('top', e.clientY);

      //Add event to destroy the menu when clicking outside
      $('body').click(function (e) {
        if ($(e.target).hasClass("fa-bars") || $(e.target).attr('id') === "file_browser_tooolbar_contextual_actions") {
          return;
        }
        //Destroy the listner for performances
        $(this).off(e);

        //Remove the item
        menu.remove();
      });

      //Get the selected elements
      var data = [];
      var fromTree = 0;
      if (typeof node === "undefined") { //From files
        var selected = $('#file_browser_full_files_table').find('.selected').find('.item-path');
        $.each(selected, function (k, elem) {
          data.push(elem.innerText);
        });
      } else { //From tree
        data.push(node.path);
        fromTree = 1;
      }

      //AJAX request to get the menu
      $.post(location.origin + "/gofast/node-actions/filebrowser", { selected: data, fromTree: fromTree }, function (data) {
        if ($(data).find('ul').length == 0) { //Empty menu
          menu.remove();
          return;
        }

        $(menu).find("ul").html($(data).find('ul').html());
        Drupal.attachBehaviors();

        // Submenu is always out of the window, then reposition it
        var submenu = menu.children().children('.dropdown-submenu').children('.dropdown-menu');
        $(submenu).css('bottom', '0');

        //Check if the menu is out of the window, reposition it if needed
        var bottom = menu[0].getBoundingClientRect().top + menu[0].scrollHeight;
        if (window.innerHeight < bottom) {
          var diff = bottom - window.innerHeight;
          $(menu).css('top', parseInt($(menu).css("top")) - diff);
        }
      });
    },
    /*
     * Implements an little input form to rename the document/folder
     */
    rename: function (href) {
      //Search and get the line we are editing

      var element = $('#file_browser_full_files_table').find('td:contains("' + href + '")');
      var name_element = element.parent().find('.item-name');

      //Check if we got an element
      if (name_element.length == 0) {
        Gofast.toast(Drupal.t("Unable to rename this item", {}, { context: 'gofast:ajax_file_browser' }), "warning");
      } else {
        //Save old name
        var old_name = name_element.text();

        //We are secure to edit
        var input_group = name_element.html('<input id="rename-form" class="form-control form-text"  value="' + name_element.text() + '" style="line-height:0px;height:20px;width:80%;float:left" ><div class="btn-group" role="group"><button style="height:20px;padding-left:5px;padding-right:5px;padding-top:0px;padding-bottom:0px;" type="button" class="btn btn-success"><i class="fa fa-check"></i></button><button type="button" style="height:20px;padding-left:5px;padding-right:5px;padding-top:0px;padding-bottom:0px;" class="btn btn-danger"><i class="fa fa-times"></i></button>');

        //GOFAST-6757 - Couldn't d&d a file after going out of a rename in the gfb (caused because no refresh when we don't submit a new name)
        $('.file_browser_full_files_element').attr('draggable', 'false'); //sets the attribute to false

        //Select text without the extension
        if (input_group.parent().find(".item-real-type").text() === "Resource") {
          Gofast.selectPartOfInput(input_group.find('input:text')[0], 0, input_group.find('input:text').val().lastIndexOf("."));
        } else {
          input_group.find('input:text').select();
        }

        //Bind the enter event to the input
        name_element.find('input').on('keyup', function (e) {
          if (e.keyCode == 13) { //Enter pressed
            var new_name = name_element.find('input').val();

            //Prevent users to rename contents with a name starting with '_'
            if (new_name.substr(0, 1) === "_") {
              Gofast.toast(Drupal.t("You can't rename a content with a name starting with '_'"), "warning");
              return;
            }

            //Trigger the animation
            name_element.html('<div class="loader-filebrowser"></div>' + new_name);

            //Process rename
            Gofast.ITHit._processRename(href, old_name, new_name, name_element, "ressource");
          }
        });
        //Bind the validate button event
        name_element.find('.btn-success').on('click', function (e) {
          var new_name = name_element.find('input').val();

          //delete spaces at the beginning and end of the name
          new_name = new_name.trim();

          //Prevent users to rename contents with a name starting with '_'
          if (new_name.substr(0, 1) === "_") {
            Gofast.toast(Drupal.t("You can't rename a content with a name starting with '_'"), "warning");
            return;
          }

          //Trigger the animation
          name_element.html('<div class="loader-filebrowser"></div>' + new_name);

          //Process rename
          Gofast.ITHit._processRename(href, old_name, new_name, name_element, "ressource");
        });
        //Bind the cancel button event
        name_element.find('.btn-danger').on('click', function (e) {
          name_element.text(old_name);
          $('.file_browser_full_files_element').attr('draggable', 'true'); //sets the attribute to true
        });
      }
    },
    /*
     * Implements an little input form to rename the document/folder
     */
    renameTree: function (href) {
      //Search and get the ztree element we are editing
      var zElement = Gofast.ITHit.tree.getNodeByParam("path", href);

      //Check if we got an element
      if (zElement === null) {
        Gofast.toast(Drupal.t("Unable to rename this item", {}, { context: 'gofast:ajax_file_browser' }), "warning");
      } else {
        var name = zElement.name;

        //Display the input field
        $("#rename-popup").remove();
        var input_group = $('#file_browser_full_tree').prepend('<div id="rename-popup"><input id="rename-form" class="form-control form-text" value="' + name + '" style="line-height:0px;height:20px;width:80%;float:left"><div class="btn-group" role="group"><button style="height:20px;padding-left:5px;padding-right:5px;padding-top:0px;padding-bottom:0px;" type="button" class="btn btn-success"><i class="fa fa-check"></i></button><button type="button" style="height:20px;padding-left:5px;padding-right:5px;padding-top:0px;padding-bottom:0px;" class="btn btn-danger"><i class="fa fa-times"></i></button></div>');
        var name_element = $("#rename-popup");

        name_element.css('width', $("#file_browser_full_tree_element").width());

        //Select text
        name_element.find('input:text').select();

        //Bind the enter event to the input
        name_element.find('input').on('keyup', function (e) {
          if (e.keyCode == 13) { //Enter pressed
            var new_name = name_element.find('input').val();

            //delete spaces at the beginning and end of the name
            new_name = new_name.trim();

            //Prevent users to rename contents with a name starting with '_'
            if (new_name.substr(0, 1) === "_") {
              Gofast.toast(Drupal.t("You can't rename a content with a name starting with '_'"), "warning");
              return;
            }

            //Process rename
            $("#rename-popup").remove();
            Gofast.ITHit._processRename(href, name, new_name, name_element, "ressource", zElement);
          }
        });
        //Bind the validate button event
        name_element.find('.btn-success').on('click', function (e) {
          var new_name = name_element.find('input').val();

          //delete spaces at the beginning and end of the name
          new_name = new_name.trim();

          //Process rename
          $("#rename-popup").remove();
          Gofast.ITHit._processRename(href, name, new_name, name_element, "ressource", zElement);
        });
        //Bind the cancel button event
        name_element.find('.btn-danger').on('click', function (e) {
          $("#rename-popup").remove();
        });
      }
    },
    /*
     * Process the rename of an element. Usually called in renaming process
     * path : The full path of the element
     * old_name : The old name of the element
     * new_name : The new name of the element
     * name_element : the jQuery graphic container
     * type : folder or ressource
     * zElement : Ztree element if the rename comes from ztree
     */
    _processRename: function (path, old_name, new_name, name_element, type, zElement) {
      //Remove slash at the end if needed
      if (path.substr(-1, 1) === "/") {
        path = path.substring(0, path.length - 1);
      }

      //Prevent move of a space
      if (old_name.substr(0, 1) === "_") {
        Gofast.toast(Drupal.t("You can only rename a space from it's page.", {}, { context: 'gofast:ajax_file_browser' }), "warning");
        name_element.text(old_name);
        return;
      }

      //If the rename comes from ztree, change icon
      if (typeof zElement !== "undefined") {
        var saveIcon = zElement.icon;
        var selectedNode = Gofast.ITHit.tree.getSelectedNodes()[0];
        zElement.icon = "/sites/all/modules/gofast/gofast_ajax_file_browser/img/load.gif";
        Gofast.ITHit.tree.refresh();
        Gofast.ITHit.tree.selectNode(selectedNode);
      }
      if (type == "ressource") { //We are renaming a document
        //First, we open the item
        Gofast.ITHit.Session.OpenItemAsync(path, null, function (asyncResult) {

          if (!asyncResult.IsSuccess) {
            Gofast.toast(Drupal.t("Unable to find", {}, { context: 'gofast:ajax_file_browser' }) + " " + old_name, "warning");
            if (typeof zElement === "undefined") {
              name_element.text(old_name);
            } else {
              var selectedNode = Gofast.ITHit.tree.getSelectedNodes()[0];
              zElement.icon = saveIcon;
              Gofast.ITHit.tree.refresh();
              Gofast.ITHit.tree.selectNode(selectedNode);
            }
            return;
          }

          var item = asyncResult.Result;

          //We got the item, we try to get the parent folder
          var pathSplit = path.split('/');
          pathSplit.pop();
          var folderPath = pathSplit.join('/');
          Gofast.ITHit.Session.OpenFolderAsync(folderPath, null, function (asyncResult) {

            if (!asyncResult.IsSuccess) {
              Gofast.toast(Drupal.t("Unable to open the parent folder of", {}, { context: 'gofast:ajax_file_browser' }) + " " + old_name, "warning");
              if (typeof zElement === "undefined") {
                name_element.text(old_name);
              } else {
                var selectedNode = Gofast.ITHit.tree.getSelectedNodes()[0];
                zElement.icon = saveIcon;
                Gofast.ITHit.tree.refresh();
                Gofast.ITHit.tree.selectNode(selectedNode);
              }
              return;
            }

            var folder = asyncResult.Result;

            //We got the folder, we can process the rename action
            item.MoveToAsync(folder, new_name, false, null, function (asyncResult) {
              if (asyncResult.Error instanceof ITHit.WebDAV.Client.Exceptions.PreconditionFailedException) {
                Gofast.toast(new_name + " " + Drupal.t("already exists in this folder", {}, { context: 'gofast:ajax_file_browser' }), "warning");
                var selectedNode = Gofast.ITHit.tree.getSelectedNodes()[0];
                if (typeof zElement === "undefined") {
                  name_element.text(old_name);
                } else {
                  zElement.icon = saveIcon;
                  Gofast.ITHit.tree.refresh();
                  Gofast.ITHit.tree.selectNode(selectedNode);
                }
                return;
              }
              if (!asyncResult.IsSuccess) {
                Gofast.toast(Drupal.t("Unable to rename", {}, { context: 'gofast:ajax_file_browser' }) + " " + old_name, "warning");
                if (typeof zElement === "undefined") {
                  name_element.text(old_name);
                } else {
                  var selectedNode = Gofast.ITHit.tree.getSelectedNodes()[0];
                  zElement.icon = saveIcon;
                  Gofast.ITHit.tree.refresh();
                  Gofast.ITHit.tree.selectNode(selectedNode);
                }
                return;
              } else {
                if (typeof zElement === "undefined") {
                  name_element.text(new_name);

                  //Check if we find the element int the tree
                  var zElement = Gofast.ITHit.tree.getNodeByParam("path", decodeURIComponent(folder.Href + old_name));

                  if (zElement !== null) {
                    //That's a folder and we found it in thz zTree, rename it !
                    zElement.name = new_name;
                    zElement.path = decodeURIComponent(folder.Href + new_name);
                    Gofast.ITHit.tree.editName(zElement);
                    Gofast.ITHit.tree.removeChildNodes(zElement);
                    zElement.isParent = true;
                    zElement.icon = saveIcon;
                    Gofast.ITHit.tree.refresh();
                    Gofast.ITHit.tree.selectNode(selectedNode);
                  }

                  Gofast.ITHit.reload();
                } else {
                  var selectedNode = Gofast.ITHit.tree.getSelectedNodes()[0];
                  zElement.name = new_name;
                  zElement.path = decodeURIComponent(folder.Href + new_name);
                  Gofast.ITHit.tree.editName(zElement);
                  zElement.icon = saveIcon;
                  Gofast.ITHit.tree.removeChildNodes(zElement);
                  zElement.isParent = true;
                  Gofast.ITHit.tree.refresh();
                  Gofast.ITHit.tree.selectNode(selectedNode);
                }
                //Attach again click evennt with the proper path
                var rtype_items = items.filter(function (i) {
                  return i.Href === folder.Href + encodeURIComponent(old_name).replace(/[!'()*]/g, escape);
                });
                var rtype = "";
                if (rtype_items.length) {
                  rtype = "Resource";
                } else {
                  rtype = "Folder";
                }
                var fakeItem = {
                  ResourceType: rtype,
                  DisplayName: new_name,
                  Href: folder.Href + encodeURIComponent(new_name).replace(/[!'()*]/g, escape)
                };
                console.log(fakeItem.Href);
                Gofast.ITHit._attachEventsAgain(fakeItem, name_element.parent());
                //We also need to edit the item-path hidden attribute for technical reasons
                var item_path = folder.Href + encodeURIComponent(new_name).replace(/[!'()*]/g, escape);
                name_element.parent().find('.item-path').text(item_path);
                return;
              }
            });
          });
        });
      }
    },
    /*
     * Display confirmation modal to process a deletion
     */
    delete: function (data, process) {
      if (process) {
        Gofast.closeModal();
        var items = JSON.parse(data);

        //Queue items for deletion
        items.forEach(function (path) {
          //Get the name of the element from the path
          var fileName = path;
          if (path.substr(-1, 1) === "/") {
            fileName = path.substring(0, path.length - 1);
          }
          fileName = fileName.split('/');
          fileName = decodeURIComponent(fileName.pop());
          $.post(location.origin + "/gofast/audit/delete/folder", { folder: path }, function (data) {
            console.log('Delete folder successfull');
          });
          $.post(location.origin + "/gofast/browser/check_favorite_folders", { folder: path }, function (data) {
            if (data == 1) {
              console.log('Favorites was remove');
            } else {
              console.log('There was no favorites');
            }
          });
          var displayNamePath = fileName + ' (' + decodeURIComponent(path).replace('/alfresco/webdav/Sites/', '') + ')';

          var operation = "delete";
          var displayOperation = Drupal.t('Deletion', {}, { context: 'gofast:ajax_file_browser' });
          Gofast.ITHit.queue.push({
            uuid: Gofast.ITHit.generate_uuid(),
            path: path,
            displayNamePath: displayNamePath,
            fileName: fileName,
            operation: operation,
            displayOperation: displayOperation,
            progression: 0,
            status: 0
          });
        });
        //Disable copy and cut buttons
        $('#file_browser_tooolbar_copy').prop('disabled', true);
        $('#file_browser_tooolbar_cut').prop('disabled', true);
        //Disable manage button
        $('#file_browser_tooolbar_manage').prop('disabled', true);
        //Disable cart button
        $('#file_browser_tooolbar_cart_button').prop('disabled', true);
        //Disable contextual actions
        $('#file_browser_tooolbar_contextual_actions').prop('disabled', true);

      } else {
        //Retrieve back items
        var items = JSON.parse(data);

        var title = Drupal.t("Delete files", {}, { context: "gofast:ajax_file_browser" });

        var html = "<h4>" + Drupal.t("Are you sure you want to delete?", {}, { context: "gofast:ajax_file_browser" }) + "</h4>";
        html += "<br /><ul style='max-height: 320px;overflow-y: scroll;'>";
        var int = 0;
        items.forEach(function (path) {
          path = decodeURIComponent(path);
          var drupalPath = path.replace('/alfresco/webdav', '');
          path = path.replace('/alfresco/webdav/Sites/', '');
          $.get(location.origin + "/ajax_file_browser/folder/get_documents", { folder_path: drupalPath, int: int },
            function (data) {
              var result = JSON.parse(data);
              var data = result.theme_list_documents;
              var int = result.int;
              $('.delete-loader-actions-' + int).replaceWith(data);
              $("body").tooltip({ selector: '[data-toggle=tooltip]' });
            }
          );
          $.get(location.origin + "/ajax_file_browser/get_icon", { folder_path: drupalPath, int: int },
            function (data) {
              var result = JSON.parse(data);
              var data = result.icon;
              var locations = result.locations
              var int = result.int;
              $('.delete-locations-' + int + ' span').replaceWith(data);
              $('.delete-locations-' + int + ' i').replaceWith(locations);
            }
          );
          html += '<li class="delete-locations-' + int + '">';
          html += '<span></span>';
          html += path;
          html += '<i></i>';
          html += '</li>';
          html += "<div id='delete-loader-actions' class='delete-loader-actions-" + int + " loader-actions' style='width:50px;height:50px;'></div>"
          int += 1;
        });
        html += "</ul>";
        html += '<i class="fa fa-exclamation-triangle" style="color:red;"></i> ' + Drupal.t("These files will also be removed from all their locations.", {}, { context: 'gofast' });
        html += "<br />";
        html += '<i class="fa fa-exclamation-triangle" style="color:red;"></i> ' + Drupal.t("Files with ", {}, { context: 'gofast' }) + '<i class="fa fa-question-circle"></i>' + Drupal.t(" have more than one emplacements", {}, { context: 'gofast' });
        html += "<br /><br />";
        data = data.replace(/"/g, '&quot;');
        html += '<button id="deleteButton" class="btn btn-danger btn-sm icon-before" type="submit" onClick="Gofast.ITHit.delete(\'' + data + '\', true)"><span class="icon glyphicon glyphicon-trash"></span>' + ' ' + Drupal.t('Delete') + '</button>';

        Gofast.modal(html, title);
        $("#deleteButton").focus();
      }
    },
    /*
     * Delete selected items
     */
    deleteSelected: function (e, selection) {
      if (typeof selection === "undefined") {
        var supprEvent = $.Event('keyup');
        supprEvent.keyCode = 46;
        //Full browser
        $("#file_browser_full_files_table").trigger(supprEvent);
      } else {
        var data = JSON.stringify([selection]);
        Gofast.ITHit.delete(data);
      }
      e.preventDefault();
      e.stopPropagation();
    },
    /*
     * Move selected items
     */
    moveSelected: function (destination) {
      //Get selected items
      var selected = $('#file_browser_full_files_table').find('.selected');

      //Push them to queue
      $.each(selected, function (k, elem) {
        var path = $(elem).find('.item-path').text();
        var fileName = $(elem).find('.item-name').text();
        Gofast.ITHit.queue.push({
          uuid: Gofast.ITHit.generate_uuid(),
          path: path,
          destination: destination,
          displayNamePath: fileName + ' (' + path + ')',
          fileName: fileName,
          operation: 'move',
          displayOperation: Drupal.t('Move', {}, { context: 'gofast:ajax_file_browser' }),
          progression: 0,
          status: 0
        });
      });
      //Disable copy and cut buttons
      $('#file_browser_tooolbar_copy').prop('disabled', true);
      $('#file_browser_tooolbar_cut').prop('disabled', true);
      //Disable manage button
      $('#file_browser_tooolbar_manage').prop('disabled', true);
      //Disable cart button
      $('#file_browser_tooolbar_cart_button').prop('disabled', true);
      //Disable contextual actions
      $('#file_browser_tooolbar_contextual_actions').prop('disabled', true);

    },
    /*
     * Download selected items
     */
    downloadSelected: function () {
      //Get selected items
      var selected = $('#file_browser_full_files_table').find('.selected');

      //Push them to queue
      $.each(selected, function (k, elem) {
        var path = $(elem).find('.item-path').text();
        var fileName = $(elem).find('.item-name').text();

        if ($(elem).find('.item-real-type').text() !== 'Resource') {
          Gofast.toast(Drupal.t("Can't download ", {}, { context: 'gofast:ajax_file_browser' }) + " " + fileName, "warning");
        } else {
          Gofast.ITHit.queue.push({
            uuid: Gofast.ITHit.generate_uuid(),
            path: path,
            displayNamePath: fileName + ' (' + decodeURIComponent(path).replace('/alfresco/webdav/Sites/', '') + ')',
            fileName: fileName,
            operation: 'download',
            displayOperation: Drupal.t('Download', {}, { context: 'gofast:ajax_file_browser' }),
            progression: 0,
            status: 0
          });
        }
      });
    },
    /*
     * Process a delete operation on a item in the queue
     */
    _processDelete: function (index) {
      var path = Gofast.ITHit.queue[index].path;
      var fileName = Gofast.ITHit.queue[index].fileName;
      //Remove slash at the end if needed
      if (path.substr(-1, 1) === "/") {
        path = path.substring(0, path.length - 1);
      }

      //First, we try to open the item
      Gofast.ITHit.Session.OpenItemAsync(path, null, function (asyncResult) {
        if (!asyncResult.IsSuccess) {
          Gofast.toast(Drupal.t("Unable to find", {}, { context: 'gofast:ajax_file_browser' }) + " " + fileName, "warning");
          Gofast.ITHit.queue[index] = null;
          return;
        }

        var item = asyncResult.Result;
        Gofast.ITHit.queue[index].progression = 50;
        //We got the item, ask delete authorization to Drupal
        Gofast.ITHit.authorizeDelete(path, function (auth) {
          Gofast.ITHit.queue[index].progression = 75;
          if (auth) {
            //We do have the autorization, now try to delete it
            item.DeleteAsync(null, function (oAsyncResult) {
              if (oAsyncResult.IsSuccess) {
                //Check if the file was successfully removed as Alfresco can send false
                //positives
                Gofast.ITHit.queue[index] = null;

                //Remove line in file browser
                var element = $('td:contains("' + path + '")');
                if (element.length !== 0) {
                  element.parent().remove();
                  var elementLeft = $('a[title|="' + fileName + '"]');
                  elementLeft.parent().remove();
                }
              } else {
                Gofast.toast("<u>" + fileName + "</u><br /><br />" + Drupal.t("Please verify that you are allowed to do that.  If you think this is an error, please contact your administrator.", {}, { context: 'gofast:ajax_file_browser' }), "warning", Drupal.t("This element cannot be deleted", {}, { context: 'gofast:ajax_file_browser' }));
                Gofast.ITHit.queue[index] = null;
                return;
              }
            });
          } else {
            Gofast.toast(Drupal.t("You are not authorized to delete", {}, { context: 'gofast:ajax_file_browser' }) + " " + fileName, "warning");
            Gofast.ITHit.queue[index] = null;
            return;
          }
        })
      });
    },
    /*
     * Process a move operation on a item in the queue
     */
    _processMove: function (index) {
      var path = Gofast.ITHit.queue[index].path;
      var destination = Gofast.ITHit.queue[index].destination;
      var fileName = Gofast.ITHit.queue[index].fileName;
      //Remove slash at the end if needed
      if (path.substr(-1, 1) === "/") {
        path = path.substring(0, path.length - 1);
      }

      //Prevent move of a space
      if (fileName.substr(0, 1) === "_") {
        Gofast.toast(Drupal.t("You can only move a space from it's page.", {}, { context: 'gofast:ajax_file_browser' }), "warning");
        Gofast.ITHit.queue[index] = null;
        return;
      }

      //First, we try to open the item
      Gofast.ITHit.Session.OpenItemAsync(path, null, function (asyncResult) {
        if (!asyncResult.IsSuccess) {
          Gofast.toast(Drupal.t("Unable to find", {}, { context: 'gofast:ajax_file_browser' }) + " " + fileName, "warning");
          Gofast.ITHit.queue[index] = null;
          return;
        }

        var item = asyncResult.Result;
        Gofast.ITHit.queue[index].progression = 30;

        //Then, we try to open the destination folder
        Gofast.ITHit.Session.OpenFolderAsync(destination, null, function (dasyncResult) {
          if (!dasyncResult.IsSuccess) {
            Gofast.toast(Drupal.t("Unable to find", {}, { context: 'gofast:ajax_file_browser' }) + " " + destination, "warning");
            Gofast.ITHit.queue[index] = null;
            return;
          }

          var destinationItem = dasyncResult.Result;
          Gofast.ITHit.queue[index].progression = 40;

          item.MoveToAsync(destinationItem, item.DisplayName, false, null, function (oAsyncResult) {
            if (oAsyncResult.IsSuccess) {
              Gofast.ITHit.queue[index] = null;

              //Remove line in file browser
              var element = $('td:contains("' + path + '")');
              if (element.length !== 0) {
                element.parent().remove();
              }
              //If we are in the destination path, reload
              if (destination === Gofast.ITHit.currentPath) {
                Gofast.ITHit.reload();
              }
            } else if (oAsyncResult.Error instanceof ITHit.WebDAV.Client.Exceptions.PreconditionFailedException) {
              Gofast.toast(Drupal.t("Can't move", {}, { context: 'gofast:ajax_file_browser' }) + " " + fileName + " " + Drupal.t("because this item already exists in the destination folder.", {}, { context: 'gofast:ajax_file_browser' }), "warning");
              Gofast.ITHit.queue[index] = null;
              return;
            } else if (destination == '/alfresco/webdav/Sites/_Groups' || destination == '/alfresco/webdav/Sites/_Organisations' || destination == '/alfresco/webdav/Sites/_Public' || destination == '/alfresco/webdav/Sites/_Extranet') {
              Gofast.toast(Drupal.t("You can not upload files in root spaces (Groups, Organizations, Public, Extranet). Please, upload your files in sub-spaces or create them. ", {}, { context: 'gofast:ajax_file_browser' }), 'warning');
              Gofast.ITHit.queue[index] = null;
              return;
            } else if (item.ResourceType === "Folder") {
              Gofast.toast(Drupal.t("You are not the creator of the directory or the creator of some files in the directory.", {}, { context: 'gofast:ajax_file_browser' }), "warning", Drupal.t("Your folder cannot be moved", {}, { context: 'gofast:ajax_file_browser' }));
              Gofast.ITHit.queue[index] = null;
              return;
            } else {
              Gofast.toast(Drupal.t("You are not the creator of the file.", {}, { context: 'gofast:ajax_file_browser' }), "warning", Drupal.t("Your file cannot be moved", {}, { context: 'gofast:ajax_file_browser' }));
              Gofast.ITHit.queue[index] = null;
              return;
            }
          });
        });
      });
    },
    /*
     * Process a copy operation on a item in the queue
     */
    _processCopy: function (index) {
      var path = Gofast.ITHit.queue[index].path;
      var destination = Gofast.ITHit.queue[index].destination;
      var fileName = Gofast.ITHit.queue[index].fileName;
      //Remove slash at the end if needed
      if (path.substr(-1, 1) === "/") {
        path = path.substring(0, path.length - 1);
      }

      //Prevent copy of a space
      if (fileName.substr(0, 1) === "_") {
        Gofast.toast(Drupal.t("You can't copy/paste a space.", {}, { context: 'gofast:ajax_file_browser' }), "warning");
        Gofast.ITHit.queue[index] = null;
        return;
      }

      //First, we try to open the item
      Gofast.ITHit.Session.OpenItemAsync(path, null, function (asyncResult) {
        if (!asyncResult.IsSuccess) {
          Gofast.toast(Drupal.t("Unable to find", {}, { context: 'gofast:ajax_file_browser' }) + " " + fileName, "warning");
          Gofast.ITHit.queue[index] = null;
          return;
        }

        var item = asyncResult.Result;
        Gofast.ITHit.queue[index].progression = 30;

        //Then, we try to open the destination folder
        Gofast.ITHit.Session.OpenFolderAsync(destination, null, function (dasyncResult) {
          if (!dasyncResult.IsSuccess) {
            Gofast.toast(Drupal.t("Unable to find", {}, { context: 'gofast:ajax_file_browser' }) + " " + destination, "warning");
            Gofast.ITHit.queue[index] = null;
            return;
          }

          var destinationItem = dasyncResult.Result;
          Gofast.ITHit.queue[index].progression = 40;

          item.CopyToAsync(destinationItem, item.DisplayName, true, false, null, function (oAsyncResult) {
            if (oAsyncResult.IsSuccess) {
              Gofast.ITHit.queue[index] = null;

              //Reload file browser
              Gofast.ITHit.reload();
            } else if (oAsyncResult.Error instanceof ITHit.WebDAV.Client.Exceptions.PreconditionFailedException) {
              Gofast.toast(Drupal.t("Can't copy/paste", {}, { context: 'gofast:ajax_file_browser' }) + " " + fileName + " " + Drupal.t("because this item already exists in the destination folder.", {}, { context: 'gofast:ajax_file_browser' }), "warning");
              Gofast.ITHit.queue[index] = null;
              return;
            } else {
              Gofast.toast(Drupal.t("Please verify that you are allowed to do that. If you think this is an error, please contact your administrator.", {}, { context: 'gofast:ajax_file_browser' }), "warning", Drupal.t("This copy / paste operation cannot be completed", {}, { context: 'gofast:ajax_file_browser' }));
              Gofast.ITHit.queue[index] = null;
              return;
            }
          });
        });
      });
    },
    /*
     * Process a download operation on a item in the queue
     */
    _processDownload: function (index, process) {

      //Prevent overload
      if (!process) {
        setTimeout(function () {
          Gofast.ITHit.downloadTimeout--;
          Gofast.ITHit._processDownload(index, true);
        }, (2000 * Gofast.ITHit.downloadTimeout));
        Gofast.ITHit.downloadTimeout++;
      } else {
        var path = Gofast.ITHit.queue[index].path;
        var fileName = Gofast.ITHit.queue[index].fileName;
        var is_confidential;
        var is_internal;

        //Remove slash at the end if needed
        if (path.substr(-1, 1) === "/") {
          path = path.substring(0, path.length - 1);
        }

        //Ask Drupal for the alfresco reference of the item we try to download
        Gofast.ITHit.getReference(path, function (reference) {
          if (reference.indexOf('workspace') === -1) {
            Gofast.toast(Drupal.t("Can't download", {}, { context: 'gofast:ajax_file_browser' }) + " " + fileName, "warning");
            Gofast.ITHit.queue[index] = null;
            return;
          }

          //Check if the document is confidential
          is_confidential = Gofast.ITHit.getIsConfidential(reference);
          //Check if the document is Internal Distribution
          is_internal = Gofast.ITHit.getIsInternalDocument(reference);

          if (is_confidential) {
            is_confidential_data = true;
            Gofast.toast(fileName + " " + Drupal.t("can't be downloaded because it's a confidential document", {}, { context: 'gofast:ajax_file_browser' }), "warning");
            Gofast.ITHit.queue[index] = null;
          } else if (is_internal) {
            is_internal_data = true;
            Gofast.toast(fileName + " " + Drupal.t("Can't be downloaded because it's an Internal Distribution document", {}, { context: 'gofast:ajax_file_browser' }), "warning");
            Gofast.ITHit.queue[index] = null;
          } else {
            //Download
            $('<form><input type="hidden" name="id" value="' + reference + '"></form>')
              .attr('action', '/cmis/browser')
              .attr('method', 'get')
              .appendTo('body').submit().remove();
          }
        });
        Gofast.ITHit.queue[index] = null;
      }
    },
    /*
     * Ask Drupal for an Alfresco reference
     */
    getReference: function (path, callback) {
      $.post(location.origin + "/ajax_file_browser/get_reference", { path: path }, function (data) {
        callback(data);
      });
    },
    /*
     * Ask Drupal to know if the document is confidential
     */
    getIsConfidential: function (reference) {
      var response = $.ajax({
        url: location.origin + "/ajax_file_browser/is_confidential",
        type: 'POST',
        data: { reference: reference },
        dataType: 'json',
        async: false
      });
      if (typeof (response.responseJSON) != "undefined" && response.responseJSON !== null && response.responseJSON == 1) {
        return true;
      } else {
        return false;
      }
    },
    /*
     * Ask Drupal to know if the document is internal
     */
    getIsInternalDocument: function (reference) {
      var response = $.ajax({
        url: location.origin + "/ajax_file_browser/is_internal",
        type: 'POST',
        data: { reference: reference },
        dataType: 'json',
        async: false
      });
      if (typeof (response.responseJSON) != "undefined" && response.responseJSON !== null && response.responseJSON == 1) {
        return true;
      } else {
        return false;
      }
    },
    /*
     * Go to a node from File Browser
     * /!\ Legacy ITHit function /!\
     */
    goToNode: function (href, newtab, name) {
      var baseUrl = window.location.protocol + "//" + window.location.host;
      // Retrieve the document's nid.
      $.post(baseUrl + '/ajax/getnidfromhref', { href: href.replace(/\&/g, "%26").replace(/\+/g, "%2B") }, function (data) {
        if (data === false || isNaN(data) || data === "false" || data === "") {
          Gofast.removeLoading();
          Gofast.modal('<div class="panel panel-default">\n\
                            <div class="panel-body" id="uploading_progress_panel">\n\
                              <div id="uploading_error_messages" class="alert alert-danger" style="display:none;">\n\
                                <ul></ul>\n\
                              </div>\n\
                              <div id="uploading_buttons_actions_all"></div>\n\
                                <div style="clear:both;" id="uploading_0" file-name="logo gofast détouré_eng.png" xhr-id="0" file-id="0">\n\
\n\                               <div class="loader-replicate"></div>\n\
                                  <span id="uploading_replicating" style="font-weight: bold;">' + Drupal.t('You will be redirected to @path  in a few seconds...', { '@path': window.decodeURI(href.split('/').pop()) }, { 'context': 'gofast:gofast_ajax_file_browser' }) + '</span>\n\
                                </div>\n\
                              </div>\n\
                          </div>', Drupal.t('Almost ready', {}, { 'context': 'gofast' }), {
            'modalSize': {
              'type': 'scale',
              'width': .5,
              'height': .5
            },
            'modalTheme': 'uploading_dragdrop'
          });
          //Start replication as it seems to be needed
          $.ajax({
            url: baseUrl + '/cmis/replicate',
            data: 'href=' + href.replace(/\&/g, "%26").replace(/\+/g, "%2B"),
            dataType: 'json'
          }).done(function (data) {
            $(".ctools-close-modal").trigger("click");
            if (newtab) {
              var win = window.open("/node/" + data, '_blank');
            } else {
              if (typeof Gofast.processAjax !== "undefined") {
                Gofast.processAjax('/node/' + data);
              } else {
                window.location.href = window.location.origin + "/node/" + data;
              }
            }
          });
        } else {
          if (newtab) {
            var win = window.open("/node/" + data, '_blank');
          } else {
            Drupal.settings.title = name;
            if (typeof Gofast.processAjax !== "undefined") {
              Gofast.processAjax('/node/' + data);
            } else {
              window.location.href = window.location.origin + "/node/" + data;
            }
          }
        }
      });
      return false;
    },
    /*
     * loop to refresh the current queue
     */
    refreshQueue: function () {
      var queueLoop = setInterval(function () {
        //Check if we need to stop the queue loop
        if ($("#file_browser_full_container").length === 0) {
          Gofast.ITHit.activeQueue = false;
          clearInterval(queueLoop);
          return;
        }
        Gofast.ITHit.activeQueue = true;
        var items = Gofast.ITHit.queue.filter(function (e) {
          return e !== null;
        });

        if (items.length === 0) {
          //Clear index as there is no item in the queue
          Gofast.ITHit.queue = [];
        }

        //Prevent graphic overload
        var more = 0;
        var itemsLength = items.length;
        if (items.length > 15) {
          itemsLength = 15;
          more = items.length - 15;
        }

        //Configure custom scrollbar to replace the legacy
        $("#file_browser_full_upload_table").mCustomScrollbar({
          theme: "dark-thin"
        });

        $(".file_browser_full_upload_element").remove();
        for (var i = 0; i < itemsLength; i++) {
          //Format the item
          itemHTML = "";
          var item = items[i];
          var itemHTML = Gofast.ITHit._formatQueueItem(item);

          //Add the item to the list after removing the current items of the list
          var processedItem = $('#file_browser_full_upload_table').find('tbody:last-child').append(itemHTML);
          processedItem = processedItem.find('tr').last();

          //Attach event handlers to the processed item
          Gofast.ITHit._attachQueueEvents(item, processedItem);
        }
        if (more !== 0) {
          itemHTML = "<tr class='file_browser_full_upload_element' style='width:100%; display: inline-block;'><td style='width:5%;'></td><td style='width:75%;'>" + more + " " + Drupal.t('more items in the queue', {}, { context: 'gofast:ajax_file_browser' }) + "</td></tr>";
          $('#file_browser_full_upload_table').find('tbody:last-child').append(itemHTML);
        }
      }, 700);
    },
    /*
     * loop to process the current queue
     * This function is not part of graphic implementation, it will process the
     * queued items in background
     */
    processQueue: function () {
      Gofast.ITHit.processingQueue = true;
      var items = Gofast.ITHit.queue.filter(function (e) {

        //!! debug TC !!
        if (e !== null) {
          if (e.operation == "upload") {
            Gofast.additionalGFBNodes.forEach(function (item, index) {
              if (e.path.includes(item)) {
                console.log("cancel upload " + e.uuid);
                Gofast.ITHit.cancelUpload(e.uuid);
              }
            });

          }
        }
        return e !== null && e.operation !== "upload";
      });

      //Get the number of queued elements
      var queued_count = items.length;

      //Get the number of processing elements
      var active_count = items.filter(function (e) {
        return e.status === 1;
      }).length;

      //Check if we have something to do this processing
      if (queued_count !== 0 && active_count < 3 && queued_count > active_count) {
        //Get the pending items
        var pending_items = items.filter(function (e) {
          return e.status === 0;
        });
        if (queued_count < 3) {
          var max_count = queued_count;
        } else {
          var max_count = 3
        }
        while (active_count < max_count) { //Stop the processing when we reached this limit
          var item = pending_items.shift();

          //Before anything, we update the status and progression of this item
          //so we need to find the item index using integrated uuid
          var item_uuid = item.uuid;
          var item_index = Gofast.ITHit.queue.findIndex(function (e) {
            return e !== null && e.uuid === item_uuid;
          });
          Gofast.ITHit.queue[item_index].status = 1;
          Gofast.ITHit.queue[item_index].progression = 25;

          //Now, we can send the item to the proper processing function
          switch (Gofast.ITHit.queue[item_index].operation) {
            case 'delete':
              Gofast.ITHit._processDelete(item_index);
              break;
            case 'move':
              Gofast.ITHit._processMove(item_index);
              break;
            case 'download':
              Gofast.ITHit._processDownload(item_index);
              break;
            case 'copy':
              Gofast.ITHit._processCopy(item_index);
              break;
          }
          active_count++;
        }
      }

      setTimeout(function () { //Run again in 500ms
        Gofast.ITHit.processQueue();
      }, 500);
    },
    generate_uuid: function () {
      return 'xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx'.replace(/[xy]/g, function (c) {
        var r = Math.random() * 16 | 0, v = c == 'x' ? r : (r & 0x3 | 0x8);
        return v.toString(16);
      });
    },
    /*
     * Ask Drupal (OG) if we have the right to delete an item
     * Call the passed callback with true or false
     */
    authorizeDelete: function (path, callback) {
      $.post(location.origin + "/ajax_file_browser/right/delete", { path: path }, function (data) {
        if (data.trim() === "GRANTED") {
          callback(true);
        } else {
          callback(false);
        }
      });
    },
    /*
     * Handle drag start event
     */
    moveDragStart: function (e) {
      if ($("#rename-form").length !== 0 || $("#new-folder-form").length !== 0) {
        e.preventDefault();
        return false;
      }
      var selected = $('#file_browser_full_files_table').find('.selected');
      var selectedDom = selected.get();

      var ua = window.navigator.userAgent;
      var msie = ua.indexOf("MSIE ");

      if (msie > 0 || !!navigator.userAgent.match(/Trident.*rv\:11\./)) {  // Internet Explorer
      } else {
        //Clear Drag and drop elements
        $('#dragndrop_file_browser').remove();

        //Replace ghost of the drag by a file(s)/folder(s)/files+folders icon
        //regarding what was selected
        if (selected.length === 1) { //One item selected
          if (selected.find(".item-real-type").text() === "Resource") {
            var ghost = $('<i id="dragndrop_file_browser" class="fa fa-file-o" aria-hidden="true"></i>');
          } else {
            var ghost = $('<i id="dragndrop_file_browser" class="fa fa-folder-open-o" aria-hidden="true"></i>');
          }
        } else { //Multiple items selected
          var ghost = $('<i id="dragndrop_file_browser" class="fa fa-files-o" aria-hidden="true"></i>');
        }
        $('body').append(ghost);
        ghost.css('position', 'absolute');
        ghost.css('font-size', '60px');
        ghost.css('top', '0px');
        ghost.css('left', '-100px');
        var ghostDom = ghost.get(0);
        e.dataTransfer.setDragImage(ghostDom, 0, 0);
        e.dataTransfer.setData('text', 'anything');
      }
    },
    /*
     * Handle drag over event
     */
    moveDragOver: function (e) {
      e.preventDefault();
      e.dataTransfer.dropEffect = "move";
      var item = $(e.currentTarget);
      var itemTitle = item.find('.node_name').text();
      if (itemTitle == '_Groups' || itemTitle == '_Public' || itemTitle == '_Organisations' || itemTitle == '_Extranet') {
        item.css('border-color', '#ebccd1');
        item.css('background-color', '#f2dede');
        item.css('color', '#a94442');
        item.css("border", "dashed 1px #a94442");
      } else {
        item.find('.node_name').css("font-weight", "bold");
        item.css("color", "#428bca");
        item.css("border", "dashed 1px #337ab7");
      }
    },
    /*
     * Handle drag leave event
     */
    moveDragLeave: function (e) {
      var item = $(e.currentTarget);
      item.find('.node_name').removeAttr('style');
      item.removeAttr('style');
    },
    /*
     * Handle drop event
     */
    moveDrop: function (e) {
      var item = $(e.currentTarget);

      item.find('.node_name').removeAttr('style');
      item.removeAttr('style');

      var node = item.parent();
      var znode = Gofast.ITHit.tree.getNodeByParam("tId", node[0].id);
      var data = e.dataTransfer.getData("text");
      if ((typeof e.dataTransfer.items !== "undefined" && e.dataTransfer.items !== null && e.dataTransfer.items.length == 1 && e.dataTransfer.items[0].kind === "string") || (typeof e.dataTransfer.files !== "undefined" && e.dataTransfer.files !== null && e.dataTransfer.files.length == 0) || (data == "anything")) { //Internal d&d
        Gofast.ITHit.moveSelected(znode.path);
        e.stopPropagation();
        e.preventDefault();
      } else { //External d&d
        Gofast.ITHit.dropPath = true;
        var fullPath = znode.path;

        //Remove slash at the end if needed
        if (fullPath.substr(-1, 1) === "/") {
          fullPath = fullPath.substring(0, fullPath.length - 1);
        }

        Gofast.ITHit.Uploader.SetUploadUrl(location.origin + znode.path);
      }
    },

    /*
     * Handle Drag over event (inside the browser)
     */
    insideDragOver: function (e) {
      e.preventDefault();
      var target = e.currentTarget;
      var path = $(target).find('.item-path').text();
      if (path == '/alfresco/webdav/Sites/_Groups/' || path == '/alfresco/webdav/Sites/_Extranet/' || path == '/alfresco/webdav/Sites/_Organisations/' || path == '/alfresco/webdav/Sites/_Public/') {
        $(target).css('background-color', '#f2dede');
        $(target).css('border-color', '#ebccd1');
        $(target).css('color', '#a94442');
      } else {
        $(target).css('border', '2px dashed #a3a3a3');
      }
    },

    /*
     * Handle Drag leave event (inside the browser)
     */
    insideDragLeave: function (e) {
      var target = e.currentTarget;
      $(target).css('background-color', 'white');
      $(target).css('color', '#777');
      $(target).css('border', 'none');
    },

    /*
     * Handle Drop event (inside the browser)
     */
    insideDrop: function (e) {
      var target = e.currentTarget;
      $(target).css('background-color', 'white');
      $(target).css('color', '#777');
      $(target).css('border', 'none');

      var path = $(target).find('.item-path').text();
      var data = e.dataTransfer.getData("text");

      if ((typeof e.dataTransfer.items !== "undefined" && e.dataTransfer.items !== null && e.dataTransfer.items.length == 1 && e.dataTransfer.items[0].kind === "string") || (typeof e.dataTransfer.files !== "undefined" && e.dataTransfer.files !== null && e.dataTransfer.files.length == 0) || (data == "anything")) { //Internal d&d
        Gofast.ITHit.moveSelected(path);
        e.stopImmediatePropagation();
        e.preventDefault();
      } else { //External d&d
        Gofast.ITHit.dropPath = true;
        var fullPath = path;

        //Remove slash at the end if needed
        if (fullPath.substr(-1, 1) === "/") {
          fullPath = fullPath.substring(0, fullPath.length - 1);
        }

        Gofast.ITHit.Uploader.SetUploadUrl(location.origin + decodeURIComponent(decodeURIComponent(path)));
      }
    },
    /*
     * Set Drupal variable to contain the selected items and call back itelfs to
     * do an action with this bulk (taxonomy, location mass management..)
     */
    bulkSelected: function (e, path) {
      var element = $(e.target);
      //Stop propagation of the click event
      e.preventDefault();
      e.stopImmediatePropagation();
      var data = [];

      if (path) {
        data.push({ url: path, type: "Folder" });
      } else {
        //Get selected elements
        var selected = $('#file_browser_full_files_table').find('.selected').find('.item-path');
        if (selected.length == 0) {
          var selected = $('#file_browser_mobile_files_table').find('.selected').find('.item-path');
        }
        $.each(selected, function (k, elem) {
          var path = elem.innerText;

          //Remove slash at the end if needed
          if (path.substr(-1, 1) === "/") {
            path = path.substring(0, path.length - 1);
          }

          var type = $(elem).parent().find('.item-real-type').text();
          data.push({ url: path, type: type });
        });
      }
      data = JSON.stringify(data);

      //Send selected elements to Drupal
      var user_id = Gofast.get("user").uid;
      $.post("/gofast/variable/set", { name: "ithit_bulk_" + user_id, value: data }).done(function (data) {
        if ($(element[0]).hasClass('manage-taxonomy') || $(element[0]).parentsUntil('ul').hasClass('manage-taxonomy')) {
          $('.bulk_taxonomy').click();
        } else if ($(element[0]).hasClass('add-locations') || $(element[0]).parentsUntil('ul').hasClass('add-locations')) {
          $('.bulk_add_locations').click();
        } else if ($(element[0]).hasClass('manage-publications') || $(element[0]).parentsUntil('ul').hasClass('manage-publications')) {
          $('.bulk_publications').click();
        } else if ($(element[0]).hasClass('manage-mail-sharing') || $(element[0]).parentsUntil('ul').hasClass('manage-mail-sharing')) {
          $('.bulk_mail_sharing').click();
        } else if ($(element[0]).hasClass('bulk-archive') || $(element[0]).parentsUntil('ul').hasClass('bulk-archive')) {
          $('.bulk_archive').click();
        } else {
          $('.bulk_add_to_cart').click();
        }
      });
    },
    linkToFolder: function (path) {
      var url = "";

      if (path.indexOf('/alfresco/webdav') !== -1) {
        //This is a folder
        Gofast.copyToClipboard(Gofast.get('baseUrl') + "/gofast/browser?path=" + path);
      } else {
        //This is a space
        Gofast.copyToClipboard(Gofast.get('baseUrl') + path);
      }
    },
    /*
     * Wait for the upload modal to be processed and then, tells to ITHit lib to
     * listen the input
     */
    attachInputEvents: function () {
      var waitProcess = setInterval(function () {
        if ($("#gofast_file_browser_upload_input").length) {
          Gofast.ITHit.Uploader.Inputs.AddById('gofast_file_browser_upload_input');
          clearInterval(waitProcess);
        }
      }, 200);
    },
    /*
     * Add a folder to bookmarks
     */
    bookmarkFolder: function (path) {
      $.post(location.origin + "/ajax_file_browser/bookmark_folder", { href: path }, function () {
        Gofast.toast(Drupal.t("Folder added to bookmarks"), "success");
        $(".block-bookmarks").data('forceRefresh', true);
        Gofast.block.loadIfNeeded($(".gofast-block"));
      });
    },

    /*
     * Remove a folder from bookmarks
     */
    unbookmarkFolder: function (path) {
      $.post(location.origin + "/ajax_file_browser/unbookmark_folder", { href: path }, function () {
        Gofast.toast(Drupal.t("Folder removed from bookmarks"), "success");
        $(".block-bookmarks").data('forceRefresh', true);
        Gofast.block.loadIfNeeded($(".gofast-block"));
      });
    },

    /*
     * Add new alfresco_item
     */
    addAlfrescoItem: function (event) {
      event.preventDefault();
      event.stopPropagation();
      Gofast.addLoading();
      var browser_location = window.location.href;
      var browser_path = Gofast.getAllUrlParams(browser_location).path;
      $.post(location.origin + '/gofast/browser/path/get_rules', { href: browser_path }, function (data) {
        if (data == 2) {
          Gofast.removeLoading();
          Gofast.toast(Drupal.t('You don\'t have write permission in this group'), "warning");
        } else if (data == 1) {
          Gofast.removeLoading();
          Gofast.toast(Drupal.t('You can\'t write to this group because it is archived'), "warning");
        } else {
          var browser_href = '/node/add/alfresco-item?path=' + browser_path;
          Gofast.processAjax(browser_href);
        }
      });
    },
    /*
     * Resize the browser in the full browser page
     */
    resize_full_browser: function () {
      var size = window.innerHeight - 100;
      $(file_browser_full_container).height(size);
    }
  };
  $(document).ready(function () {
    //Init File Browser
    Gofast.ITHit.init();

    //Handle path changes in URL when clicking on back/forward button
    $(document).on('urlChanged', function (e, oldLocation) {
      var params = {};
      if (location.search) {
        var parts = location.search.substring(1).split('&');

        for (var i = 0; i < parts.length; i++) {
          var nv = parts[i].split('=');
          if (!nv[0]) continue;
          params[nv[0]] = nv[1] || true;
        }
      }

      if (typeof params.path !== "undefined" && params.path !== "") {
        Gofast.ITHit.navigate('/alfresco/webdav' + params.path, null, null, true);
      }
    });
  });

  function linkToThisFolder(aContextMenuHierarchyItems) {
    if (aContextMenuHierarchyItems[0].ResourceType == "Folder") {
      var href = aContextMenuHierarchyItems[0].Href.replace("/alfresco/webdav", "");
    } else if (aContextMenuHierarchyItems[0].ResourceType == "Resource") {
      var href = aContextMenuHierarchyItems[0].Href.replace("/alfresco/webdav", "").replace(encodeURI(aContextMenuHierarchyItems[0].DisplayName), "");
    }
    Gofast.copyToClipboard(Gofast.get('baseUrl') + "/gofast/browser?path=" + encodeURI(href));
  }

  if (!Array.prototype.findIndex) {
    Object.defineProperty(Array.prototype, 'findIndex', {
      value: function (predicate) {
        // 1. Let O be ? ToObject(this value).
        if (this == null) {
          throw new TypeError('"this" is null or not defined');
        }

        var o = Object(this);

        // 2. Let len be ? ToLength(? Get(O, "length")).
        var len = o.length >>> 0;

        // 3. If IsCallable(predicate) is false, throw a TypeError exception.
        if (typeof predicate !== 'function') {
          throw new TypeError('predicate must be a function');
        }

        // 4. If thisArg was supplied, let T be thisArg; else let T be undefined.
        var thisArg = arguments[1];

        // 5. Let k be 0.
        var k = 0;

        // 6. Repeat, while k < len
        while (k < len) {
          // a. Let Pk be ! ToString(k).
          // b. Let kValue be ? Get(O, Pk).
          // c. Let testResult be ToBoolean(? Call(predicate, T, « kValue, k, O »)).
          // d. If testResult is true, return k.
          var kValue = o[k];
          if (predicate.call(thisArg, kValue, k, o)) {
            return k;
          }
          // e. Increase k by 1.
          k++;
        }

        // 7. Return -1.
        return -1;
      },
      configurable: true,
      writable: true
    });
  }


  $(document).on("click", ".switch.bottom_close", function () {
    $('.mCSB_container_wrapper .mCSB_container').css('left', '0px');
  });

  $(document).on("click", ".switch.center_close", function () {
    $('.mCSB_container_wrapper .mCSB_container').css('left', '0px');
  });

  $(document).ready(function () {
    //Resize browser if we are on the full browser page
    if (location.pathname === "/gofast/browser") {
      Gofast.ITHit.resize_full_browser();
    }

    $(window).resize(function () {
      $('#name_header').trigger('resize');
      $('#size_header').trigger('resize');
      $('#type_header').trigger('resize');

      //Resize browser if we are on the full browser page
      if (location.pathname === "/gofast/browser") {
        Gofast.ITHit.resize_full_browser();
      }
    });

    Drupal.behaviors.resize_full_browser = {
      attach: function (context) {
        if (location.pathname === "/gofast/browser" && $("#file_browser_full_container").length !== 0) {
          Gofast.ITHit.resize_full_browser();
        }
      }
    }

    //Implements translations
    Drupal.t("Unable to find this space's folder", {}, { context: 'gofast:ajax_file_browser' });
  });
})(jQuery, Gofast, Drupal);
