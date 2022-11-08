(function ($, Gofast, Drupal) {
  'use strict';

  Drupal.gofast_cmis = Drupal.gofast_cmis || {};

  $(document).ready(function () {

    $(document).on('change', '#gofast-cmis-alfresco-file-form #edit-reference', function(e) {
      Gofast.toast(Drupal.t("Please make sure you upload the right file, pay attention to the file's name", {}, {'context' : 'gofast:gofast_cmis'}), 'info');
    });

    $(document).on('click', '[data-toggle="btns"] .btn', function (e) {
      var $this = $(this);
      $this.parent().find('.active').removeClass('active');
      $this.addClass('active');
    });

    $(document).on('click', '.alfresco_download_edit_url', function (e) {
      e.preventDefault();
      var link = $(this);
      $.ajax({
        'url': '/gofast/document/onlineedit',
        'type': 'POST',
        'dataType': 'json',
        'data': {
          'nid': $(this).attr("class").split('-').last()
        },
        'beforeSend': function(xhr) {
          Gofast.xhrPool = Gofast.xhrPool || {};
          Gofast.xhrPool.xhrCheckOnlineEdit = xhr;  // before jQuery send the request we will add it into our object
        },
        'complete': function() {
          delete Gofast.xhrPool.xhrCheckOnlineEdit;
        },
        'async': true
      }).done(function (result) {
        if (result.isEditable != 1) {
          Gofast.toast(Drupal.t('This document is being opened by OnlyOffice', {}, {'context' : 'gofast:gofast_cmis'}), 'warning');
        } else {
            var href = $.trim(link.attr("href"));
            var extension = href.substring(href.lastIndexOf('.')+1, href.length) || href;
            var documents_settings = Gofast._settings.gofast_cmis.documents_form_defaults;
           if(documents_settings.ticket && href.length < documents_settings.ticket_path_length){
                href = href.replace("alfresco/webdav", Drupal.settings.ticket + "/alfresco/webdav");
            }

            var libreoffice_extensions = [
                "odt", "ods", "odp",
                "docx", "doc", "xlsx", "xls", "pptx", "ppt",
                "docm", "xlsm", "doct", "xlst",
                "csv", "rtf"
            ];

            if(Drupal.settings.gofast_cmis.documents_form_defaults.edit_libreoffice_documents == true && libreoffice_extensions.includes(extension)){
                window.open("vnd.libreoffice.command:ofe|u|" + href, 'Document');
            }else{
                Gofast.ITHit.Client.DocManager.EditDocument(href, null, gofastMissingProtocol);
            }
        }
      });
    });

  });
  
  /**
   * helper to override a drop event issued from an iframe by passing the dropped file to the classic gofast .drop-area
   * @param {HTMLElement} iframeContent 
   */
  Drupal.gofast_cmis.init_iframe_proxy_dropzone = function (iframeContent) {
    iframeContent.addEventListener("drop", (e) => {
      e.preventDefault();
      e.stopPropagation();
      e.stopImmediatePropagation();
      const canEdit = $.get("/gofast/user/cani/update/" + Gofast.get("node").id);
      if (!canEdit) {
        Gofast.toast(Drupal.t('You are not allowed to edit this document', {}, {'context' : 'gofast:gofast_cmis'}), 'warning');
        return;
      }

      function FakeDataTransfer(file) {
        this.types = ['Files'];
        this.getData = function() {
          return file;
        };
        this.files = [file];
      };

      const droppedFile = e.dataTransfer.files[0];
      const dropArea = document.querySelector(".drop-area");

      const dropAreaFakeEvent = new DragEvent("drop");
      // defineProperty lets us override readonly attributes such as dataTransfer
      Object.defineProperty(dropAreaFakeEvent, "dataTransfer", {
        value: new FakeDataTransfer(droppedFile),
      });
      dropArea.dispatchEvent(dropAreaFakeEvent);
    });
  }

  Drupal.gofast_cmis.tagmajorversion = function () {
    $("#popup-version #major_version_valid_span").html("'.$img_html_wait.'");
    var url = Gofast.js_get_url("gofast/ajax/tag/majorversion");
    var comment = $("#popup-version #major_version_comment").val();
    var nid = "'.$node->nid.'";
    $.ajax({
      url: url,
      type: "POST",
      data: 'comment=' + comment + '&nid=' + nid,
      'beforeSend': function(xhr) {
        Gofast.xhrPool = Gofast.xhrPool || {};
        Gofast.xhrPool.xhrTagMajorVersion = xhr;  // before jQuery send the request we will add it into our object
      },
      'complete': function() {
        delete Gofast.xhrPool.xhrTagMajorVersion;
      },
      success: function (data) {
        $("#versions_span").html(data);
        Drupal.CTools.Modal.dismiss();
      }
    });
  };

  Drupal.gofast_cmis.preUnlockDocument = function(noderef, lock_owner) {
    const document_title = document.getElementsByTagName("title")[0].innerHTML;
    const modal_title = Drupal.t("Document unlock confirmation", {}, {"context": "gofast:gofast_cmis"});
    let html = "<div class='h-100 mt-8'>";
    html += "<p class='font-weight-bold'>" + Drupal.t("Are you really sure you want to unlock the document?", {}, {"context": "gofast:gofast_cmis"}) + "</p>"
    html += "<p class='font-weight-bold'>" + Drupal.t("You may inadvertently erase an ongoing work on this document.", {}, {"context": "gofast:gofast_cmis"}) + "</p>";
    html += "<button class='btn btn-danger' onClick='Drupal.gofast_cmis.unlockDocument(\"" + noderef + "\", \"" + lock_owner +"\"); Drupal.CTools.Modal.dismiss();'>" + Drupal.t("I want to unlock", {}, {"context": "gofast:gofast_cmis"}) + " " + document_title + "</button>";
    html += "</div>";
    Gofast.modal(html, modal_title);
  }

  Drupal.gofast_cmis.unlockDocument = function (noderef, lock_owner) {
    var url = Gofast.js_get_url("gofast/ajax/unlock_document");

    $.ajax({
      url: url,
      data: 'noderef=' + noderef + '&lock_owner=' + lock_owner,
      dataType: 'html',
      'beforeSend': function(xhr) {
        Gofast.xhrPool = Gofast.xhrPool || {};
        Gofast.xhrPool.xhrUnlockDocument = xhr;  // before jQuery send the request we will add it into our object
      },
      'complete': function() {
        delete Gofast.xhrPool.xhrUnlockDocument;
      },
      success: function (data) {
        //location.reload();
        Gofast.processAjax(window.location.pathname, true);
      }
    });
  };

  Drupal.gofast_cmis.unlockDocumentTodoAuto = function (noderef) {
    var url = Gofast.js_get_url("gofast/ajax/unlock_document_todo");


    $.ajax({
      url: url,
      data: 'noderef=' + noderef,
      dataType: 'html',
      'beforeSend': function(xhr) {
        Gofast.xhrPool = Gofast.xhrPool || {};
        Gofast.xhrPool.xhrUnlockDocumentToDo = xhr;  // before jQuery send the request we will add it into our object
      },
      'complete': function() {
        delete Gofast.xhrPool.xhrUnlockDocumentToDo;
      },
      success: function (data) {
        Gofast.processAjax(window.location.pathname, true);
      }
    });
  };

  Drupal.formatSizeUnits = function (aSize) {
    aSize = Math.abs(parseInt(aSize, 10));
    var def = [[1, 'octets'], [1024, 'ko'], [1024 * 1024, 'Mo'], [1024 * 1024 * 1024, 'Go'], [1024 * 1024 * 1024 * 1024, 'To']];
    for (var i = 0; i < def.length; i++) {
      if (aSize < def[i][0])
        return (aSize / def[i - 1][0]).toFixed(2) + ' ' + def[i - 1][1];
    }
  };


//fonction d'initialisation du drag&drop. le parametre "version" qui vaut true ou false indique si c'est un upload dans le cadre d'un ajout de doc
// ou d'un upload de nouvelle version. si version == true, c'est un upload de nouvelle version, si version == false c'est un ajout de document.
// cela modifie la redirection que l'on fait après l'upload du fichier
  Drupal.gofast_cmis.init_dragdrop = function (version) {
    var progress_bar = $("#progress");
    var drop_zone = $(".drop-area");
    var time_drag;

    function uploadFile(file) {
      //Escape unwanted char in the title
      var filename = file.name;
      filename = encodeURIComponent(filename).replace("'", "%27").replace("!", "%21").replace("(", "%28").replace(")", "%29");
      
      var upload = new tus.Upload(file, {
        endpoint: "/gofast/dragdrop/upload",
        retryDelays: [0, 3000, 5000, 10000, 20000],
        metadata: {
          name: filename,
          type: file.type
        },
        chunkSize: 500000,
        // Callback for errors which cannot be fixed using retries
        onError: function(error) {
            console.log("Failed because: " + error);
            //TOAST
            progress_bar.css("display", "none");
        },
        // Callback for reporting upload progress
        onProgress: function(bytesUploaded, bytesTotal) {
            var percentage = (bytesUploaded / bytesTotal * 100).toFixed(2);
            progress_bar.attr("value", percentage);
            progress_bar.attr("max", 100);
        },
        // Callback for once the upload is completed
        onSuccess: function() {
            console.log("Download %s from %s", upload.file.name, upload.url);
            progress_bar.css("display", "none");

            if (version === false) {
              //location.href = "/node/add/alfresco-item?dragdrop=1";
              Gofast.processAjax('/node/add/alfresco-item?dragdrop=1', true);
            } else {
                $("#alfresco_item_upload_new_version").click();
            }
        }
      });

      // Start the upload
      upload.start();
      progress_bar.css("display", "block");
    }

    function traverseFiles(files) {
      if (typeof files !== "undefined") {
        for (var i = 0, l = files.length; i < l; i++) {
          var maxsize = 36700160;
          if (files[i].size < maxsize) {
            var current_ajax_request = $.ajax();
            if (current_ajax_request !== null && current_ajax_request.readyState > 0 && current_ajax_request.readyState < 4) {
              current_ajax_request.abort();
            }
            uploadFile(files[i]);
          } else {
            var message = '<u>' + files[i].name + '</u><br />' + Drupal.t("The file size (%filesize) exeed the limit (%units)", {'%filesize': Drupal.formatSizeUnits(files[i].size), '%units': Drupal.formatSizeUnits(maxsize)},{'context' : 'gofast:gofast_cmis'}) + ". <br /> <br />" + Drupal.t("Please use the file browser to upload your document.");
            Gofast.toast(message, "error", Drupal.t("File upload failed", {}, {'context' : 'gofast:gofast_cmis'}));
          }
        }
      } else {
        drop_zone.html(Drupal.t("Your browser does not support this functionality", {}, {'context' : 'gofast:gofast_cmis'}));
      }
    }

    function updateDropZone(dragging) {      
      if (dragging) {      
        if (drop_zone.css('line-height') !== '75px') {
          drop_zone.animate({
            'line-height': '75px'
          }, 150);
        }
      } else {
        if (drop_zone.css('line-height') !== '20px') {
          drop_zone.animate({
            'line-height': '20px'
          }, 150);
        }
      }
    }
    ;


    $(document).bind('drop dragover', function (e) {
      e.preventDefault();
    });


    $(".drop-area:not(.drop-area-processed)").addClass("drop-area-processed").each(function () {
      $(this).on('drag dragstart dragend dragover dragenter dragleave drop', function (e) {
        e.preventDefault();
        e.stopPropagation();
      }).on('dragleave', function (e) {       
            clearTimeout(Drupal.gofast_cmis.dropzoneleave);       
            Drupal.gofast_cmis.dropzoneleave = setTimeout(function () {          
                //$("#container_pdf_iframe").css("visibility" , "visible");
                 $(".drop-area").animate({height:35},600);
            }, 500);
       
        var target = e.target;
        if (target && target.id === $(this).attr("id")) {
          if (new Date().getTime() - time_drag > 1) {
            $(this).removeClass("over");
          }
        }
      }).on('dragenter', function (e) {      
        clearTimeout(Drupal.gofast_cmis.dropzoneleave);
        $(this).animate({height:500},600);      
        var drag_date = new Date();
        $(this).addClass("over");
        time_drag = drag_date.getTime();
      }).on('drop', function (e) {
       // $("#container_pdf_iframe").css("visibility" , "visible");
        $(".drop-area").animate({height:35},600);
        traverseFiles(e.originalEvent.dataTransfer.files);
        $(this).removeClass("over");
        updateDropZone(false);
      });
    });


  };

  Drupal.gofast_cmis.async_show_all_versions = function (nid) {
      $("#gofast_cmis_container_versions_button").hide();
      $("#gofast_cmis_container_versions").load("/gofast/api/getversions/"+nid);
  }


  Drupal.gofast_cmis.init_show_all_versions = function (nid) {
  //fct qui fait apparaitre la liste de toutes les versions
    $("#all_list_versions_open_span").each(function () {
      if ($(this).hasClass("list_versions_processed")) {
        return;
      }
      $(this).click(function () {
        var url = Gofast.js_get_url("gofast/ajax/get/revisions");

        $.ajax({
          url: url,
          data: 'all=true&nid=' + nid,
          'beforeSend': function(xhr) {
            Gofast.xhrPool = Gofast.xhrPool || {};
            Gofast.xhrPool.xhrShowAllVersions = xhr;  // before jQuery send the request we will add it into our object
          },
          'complete': function() {
            delete Gofast.xhrPool.xhrShowAllVersions;
          },
          success: function (data) {
            $("#versions_span").html(data);
            Drupal.gofast_cmis.init_show_major_versions(nid);
          }
        });
      });

      $(this).addClass("list_versions_processed");
    });
  };

  /** commented for now for reference, will be removed if no regression is found */
  // Drupal.gofast_cmis.showPreviewModal = function (e, nid, selector){
  // e.preventDefault();
  // e.stopPropagation();

  // // Hide contexctuel menu
  // $("#file_browser_full_container .gofast-node-actions").css("display","none");

  // if(selector == null){
  //     selector = "#preview_modal";
  // }
  // var url = "/gofast/ajax/generate_onlyoffice_preview/" + nid;
  // var loading_content = '<div class="loader-preview"></div>';
  // $(selector).html(loading_content);
  // $.ajax({
  //   url: url,
  //   type: "POST",
  //   dataType: "json",
  //   'beforeSend': function(xhr) {
  //     Gofast.xhrPool = Gofast.xhrPool || {};
  //     Gofast.xhrPool.xhrGenerateNodePreview = xhr;  // before jQuery send the request we will add it into our object
  //   },
  //   'complete': function() {
  //     delete Gofast.xhrPool.xhrGenerateNodePreview;
  //   }
  // }).done(function (data) {
  //   // Replace the div content with the PDFJS widget
  //   if(data.status !== 'FALLBACK' && typeof(data.FileUrl) !== "undefined"){
  //     if (data.FileUrl.length > 0 &&  data.EndConvert === "True") {
  //       $("#alfresco_content_modal").remove();
  //       var container ="<div class='modal-header' id='modal-header-preview'><button type='button' class='close ctools-close-modal' aria-hidden='true' onClick='jQuery(\"#alfresco_content_modal\").remove();jQuery(\"#modal-header-preview\").remove();jQuery(\"#modal-content-preview\").remove();''>×</button><span class='modal-title' ></span></div><div class='modal-content' id='modal-content-preview'><div id='alfresco_content_modal' style='height: 75vh;'></div></div>";
  //       $(selector).html("");
  //       $(selector).append(container);
  //       Drupal.gofast_cmis.replace_content(data.FileUrl,true);
  //       $(selector).draggable({handle: '.modal-header'});
  //     }
  //   }else{
  //     var url = "/gofast/ajax/generate_preview/" + nid;
  //     $.get(url, function (data) {
  //       data = JSON.parse(data);
  //       $("#alfresco_content_modal").remove();
  //       var container ="<div class='modal-header' id='modal-header-preview'><button type='button' class='close ctools-close-modal' aria-hidden='true' onClick='jQuery(\"#alfresco_content_modal\").remove();jQuery(\"#modal-header-preview\").remove();jQuery(\"#modal-content-preview\").remove();''>×</button><span class='modal-title' >"+(data.title ?? '')+"</span></div><div class='modal-content' id='modal-content-preview'><div id='alfresco_content_modal' style='height: 75vh;'></div></div>";
  //       $(selector).html("");
  //       $(selector).append(container);
  //       if(data.hasOwnProperty('reference')){
  //         Drupal.gofast_cmis.get_remote_file(data.reference, true);
  //       }else{
  //         Drupal.gofast_cmis.get_remote_file("", true, data.link,data.type);
  //       }
  //       $(selector).draggable({handle: '.modal-header'});
  //     });
  //   }
  // }).fail(function (err) {
  //   console.log("Error with request generate onlyoffice preview");
  // });

  //   // Hide contexctuel menu
  //   $("#file_browser_full_container .gofast-node-actions").css(
  //     "display",
  //     "none"
  //   );

  // if (selector == null) {
  //   selector = "#preview_modal";
  // }
  // var url = "/gofast/ajax/generate_onlyoffice_preview/" + nid;
  // var loading_content = '<div class="loader-preview"></div>';
  // $(selector).html(loading_content);
  // $.ajax({
  //   url: url,
  //   type: "POST",
  //   dataType: "json",
  //   beforeSend: function (xhr) {
  //     Gofast.xhrPool = Gofast.xhrPool || {};
  //     Gofast.xhrPool.xhrGenerateNodePreview = xhr; // before jQuery send the request we will add it into our object
  //   },
  //   complete: function () {
  //     delete Gofast.xhrPool.xhrGenerateNodePreview;
  //   },
  // })
  //   .done(function (data) {
  //     // Replace the div content with the PDFJS widget
  //     if (
  //       data.status !== "FALLBACK" &&
  //       typeof data.FileUrl !== "undefined"
  //     ) {
  //       if (data.FileUrl.length > 0 && data.EndConvert === "True") {
  //         $("#alfresco_content_modal").remove();
  //         var container =
  //           "<div class='modal-header' id='modal-header-preview'><button type='button' class='close ctools-close-modal' aria-hidden='true' onClick='jQuery(\"#alfresco_content_modal\").remove();jQuery(\"#modal-header-preview\").remove();jQuery(\"#modal-content-preview\").remove();''>×</button><span class='modal-title' ></span></div><div class='modal-content' id='modal-content-preview'><div id='alfresco_content_modal' style='height: 75vh;'></div></div>";
  //         $(selector).html("");
  //         $(selector).append(container);
  //         Drupal.gofast_cmis.replace_content(data.FileUrl, true);
  //         $(selector).draggable({ handle: ".modal-header" });
  //       }
  //     } else {
  //       var url = "/gofast/ajax/generate_preview/" + nid;
  //       $.get(url, function (data) {
  //         data = JSON.parse(data);
  //         $("#alfresco_content_modal").remove();
  //         var container =
  //           "<div class='modal-header' id='modal-header-preview'><button type='button' class='close ctools-close-modal' aria-hidden='true' onClick='jQuery(\"#alfresco_content_modal\").remove();jQuery(\"#modal-header-preview\").remove();jQuery(\"#modal-content-preview\").remove();''>×</button><span class='modal-title' >" +
  //           (data.title ?? '') +
  //           "</span></div><div class='modal-content' id='modal-content-preview'><div id='alfresco_content_modal' style='height: 75vh;'></div></div>";
  //         $(selector).html("");
  //         $(selector).append(container);
  //         if (data.hasOwnProperty("reference")) {
  //           Drupal.gofast_cmis.get_remote_file(data.reference, true);
  //         } else {
  //           Drupal.gofast_cmis.get_remote_file(
  //             "",
  //             true,
  //             data.link,
  //             data.type
  //           );
  //         }
  //         $(selector).draggable({ handle: ".modal-header" });
  //       });
  //     }
  //   })
  //   .fail(function (err) {
  //     console.log("Error with request generate onlyoffice preview");
  //   });
  // };

  Drupal.gofast_cmis.init_show_major_versions = function (nid) {
    //fct qui fait apparaitre la liste de toutes les versions majeurs
    $(".list_versions_open_span").each(function () {
      if ($(this).hasClass("list_versions_processed")) {
        return;
      }
      $(this).click(function () {

        var url = Gofast.js_get_url("gofast/ajax/get/revisions");

        $.ajax({
          url: url,
          data: 'nid=' + nid,
          'beforeSend': function(xhr) {
            Gofast.xhrPool = Gofast.xhrPool || {};
            Gofast.xhrPool.xhrShowMajorVersions = xhr;  // before jQuery send the request we will add it into our object
          },
          'complete': function() {
            delete Gofast.xhrPool.xhrShowMajorVersions;
          },
          success: function (data) {
            $("#versions_span").html(data);
            Drupal.gofast_cmis.init_show_all_versions(nid);
          }
        });
      });
      $(this).addClass("list_versions_processed");
    });
  };

//  Drupal.behaviors.urlmodifiy = {
//    attach: function (context) {
//
//      $(".alfresco_download_edit_url:not(.urlmodify_processed)").addClass("urlmodify_processed").each(function () {
//
//        $(this).click(function (event) {
//          event.preventDefault();
//
//        });
//      });
//    }
//  };

Drupal.behaviors.loadTemplate = {
  attach: function (context) {

    //Fold node templates
    function foldZtreeNodes(ztree){
       var nodes = ztree.getNodesByParam("name", "TEMPLATES");
       nodes.forEach(function(node){
         ztree.expandNode(node, false, true);
       });
    }

    //Fold node folder templates
    function foldZtreeFolderNodes(ztree){
       var nodes = ztree.getNodesByParam("name", "FOLDERS TEMPLATES")[0].children;
       nodes.forEach(function(node){
         ztree.expandNode(node, false, true);
       });
    }

    //Load templates async if needed
    var templates_params = $("#async_ztree_templates").not(".processed").addClass('processed');
    if(templates_params.length > 0){
      var arr_values_combine = templates_params.find("#arr_values_combine").text();
      var ztree_options = templates_params.find("#ztree_options").text();
      var paths_options = templates_params.find("#paths_options").text();
      var selected_item = templates_params.find("#selected_item").text();

   $.post( "/ztree/templates/async", { arr_values_combine: arr_values_combine, ztree_options: ztree_options, paths_options: paths_options })
      .done(function( ztree ) {
        templates_params.replaceWith(ztree);
        $('#ztree_component_content_templates').append('<div class="spinner"></div>');
        Drupal.behaviors.gofast_ztree.attach();

        //close all "TEMPLATE" ztree nodes
        var ztree = $.fn.zTree.getZTreeObj("ztree_component_content_templates");
        //GOFAST-5146 Revert closing of template folders
        //foldZtreeNodes(ztree);

        if(selected_item !== ""){
          //Select template if we are creating a document from template
          var node = ztree.getCheckedNodes(true);
          var current_node = node[0];
          var parents = new Array();
          while(null !== current_node.getParentNode()){
            current_node = current_node.getParentNode();
            parents.push(current_node);
          }
          parents.reverse();
          parents.forEach(function(parent){
            ztree.expandNode(parent, true, false);
          });
        }
      });

    }

    //Load templates_folder async if needed
    var templates_folder_params = $("#async_ztree_templates_folder").not(".processed").addClass('processed');
    if(templates_folder_params.length > 0){
      var arr_values_combine = templates_folder_params.find("#arr_values_combine").text();
      var ztree_options = templates_folder_params.find("#ztree_options").text();
      var paths_options = templates_folder_params.find("#paths_options").text();
      var selected_item = templates_folder_params.find("#selected_item").text();

      $.post( "/ztree/templates/async", { arr_values_combine: arr_values_combine, ztree_options: ztree_options, paths_options: paths_options })
      .done(function( ztree ) {
        templates_folder_params.replaceWith(ztree);
        Drupal.behaviors.gofast_ztree.attach();

        //close all "FOLDER TEMPLATES" ztree nodes
        var ztree = $.fn.zTree.getZTreeObj("ztree_component_content_templates_folders");
        foldZtreeFolderNodes(ztree);

        if(selected_item !== ""){
          //Select template if we are creating a document from template
          var node = ztree.getCheckedNodes(true);
          var current_node = node[0];
          var parents = new Array();
          while(null !== current_node.getParentNode()){
            current_node = current_node.getParentNode();
            parents.push(current_node);
          }
          parents.reverse();
          parents.forEach(function(parent){
            ztree.expandNode(parent, true, false);
          });
        }
        $('#gofast-ajax-file-browser-add-template-folder-form #ztree_component_content_templates_folders').css('float','unset');
      });
    }
  }
};

  function GetMsOfficeSchemaByExtension(sExt) {
    sExt = sExt.toLowerCase();
    switch (sExt) {
      case "docx":
      case "doc":
      case "docm":
      case "dot":
      case "dotm":
      case "dotx":
      case "odt":
        return "ms-word";
      case "xltx":
      case "xltm":
      case "xlt":
      case "xlsx":
      case "xlsm":
      case "xlsb":
      case "xls":
      case "xll":
      case "xlam":
      case "xla":
      case "ods":
        return "ms-excel";
      case "pptx":
      case "pptm":
      case "ppt":
      case "ppsx":
      case "ppsm":
      case "pps":
      case "ppam":
      case "ppa":
      case "potx":
      case "potm":
      case "pot":
      case "odp":
        return "ms-powerpoint";
      case "accdb":
      case "mdb":
        return "ms-access";
      case "xsn":
      case "xsf":
        return "ms-infopath";
      case "pub":
        return "ms-publisher";
      case "vstx":
      case "vstm":
      case "vst":
      case "vssx":
      case "vssm":
      case "vssm":
      case "vss":
      case "vsl":
      case "vsdx":
      case "vsdm":
      case "vsd":
      case "vdw":
        return "ms-visio";
      case "mpp":
      case "mpt":
        return "ms-project";
    }
  }

  function gofastMissingProtocol(){
    //OS Detection
    var extension="msi";
    if (navigator.userAgent.indexOf("Win")!=-1) extension="msi";
    if (navigator.userAgent.indexOf("Mac")!=-1) extension="pkg";
    if (navigator.userAgent.indexOf("X11")!=-1) extension="deb";
    if (navigator.userAgent.indexOf("Linux")!=-1) extension="deb";
    var title = Drupal.t("Open a non Office document", {}, {context : 'gofast'});
    var html = "<span style='display:inline-block;padding-top:10px;'>" + '<strong>' + Drupal.t("Step 1: Please download and install this software to open this document from your PC.", {}, {context: 'gofast'}) + '</strong>' + '</span><br><a class="mt-2 btn btn-info no-footer" onClick="window.open(\'' + location.origin + "/sites/all/libraries/ajax_file_browser/Plugins/ITHitEditDocumentOpener."+extension+"'" + ', \'_blank\')"><i class="fa fa-download" aria-hidden="true"></i> ITHitEditDocumentOpener.'+extension+'</button></a>';
    html += "<span style='display:inline-block;padding-top:10px;'>";
    html += '<strong>' + Drupal.t('Step 2: Install the extension in your browser:',{}, {context: 'gofast-ithit-help'}) + '</strong>';
    html += "<ul style='list-style-type: none;'>";
    html += "<li>";
    html += "<span style='display:inline-block;padding-top:10px;'>"+'<a href="https://chrome.google.com/webstore/detail/it-hit-edit-doc-opener-5/nakgflbblpkdafokdokmjdfglijajhlp" target="_blank">' + '<img src="/sites/default/files/logos_web/google_chrome.png" height="3%" width="3%" style="margin-right: 1rem;">',{}, {context: 'gofast-ithit-help'} + '</a>';
    html += '<strong>'+ Drupal.t(' Link for Chrome Extension',{}, {context: 'gofast-ithit-help'}) + '</strong> </a>';
    html += "</li>";
    html += "<li>";
    html += "<span style='display:inline-block;padding-top:10px;'>"+'<a href="https://addons.mozilla.org/fr/firefox/addon/it-hit-edit-doc-opener-5/" target="_blank">' + '<img src="/sites/default/files/logos_web/firefox.png" height="3%" width="3%" style="margin-right: 1rem;">',{}, {context: 'gofast-ithit-help'} + '</a>';
    html += '<strong>'+ Drupal.t(' Link for FireFox Extension',{}, {context: 'gofast-ithit-help'}) + '</strong> </a>';
    html += "</li>";
    html += "<li>";
    html += "<span style='display:inline-block;padding-top:10px;'>"+'<a href="https://microsoftedge.microsoft.com/addons/detail/it-hit-edit-doc-opener-5/mdfaonmaoigngflemfmkboffllkopopm?hl=fr" target="_blank">' + '<img src="/sites/default/files/logos_web/edge.png" height="3%" width="3%" style="margin-right: 1rem;">',{}, {context: 'gofast-ithit-help' }  + '</a>';
    html += '<strong>'+ Drupal.t(' Link for Edge Extension',{}, {context: 'gofast-ithit-help'}) + '</strong> </a>';
    html += "</li>";
    html += "</ul>";
    html += Drupal.t('For help: consult the ',{}, {context: 'gofast-ithit-help'}) + '<a href="https://gofast-docs.readthedocs.io/' + Drupal.settings.gofast.language + '/4.0/docs-gofast-users/doc-gofast-guide-utilisateurs.html" target="_blank"><strong>' + Drupal.t('documentation',{}, {context: 'gofast-ithit-help'}) + '</strong> </a>' + Drupal.t('or our ',{}, {context: 'gofast-ithit-help'}) + '<a href="https://community.ceo-vision.com/" target="_blank"><strong>' + Drupal.t('forum',{}, {context: 'gofast-ithit-help'}) + '</strong> </a>';
    html += "</span>";
    Gofast.modal(html, title);
  }

})(jQuery, Gofast, Drupal);
