(function ($, Gofast, Drupal) {
  'use strict';

  var node;
  Drupal.gofast_cmis = Drupal.gofast_cmis || {};

  Drupal.gofast_cmis.get_remote_file = function (node_ref, modal, direct_url,type) {
   if(modal == null){
       modal = false;
    }
    if(typeof direct_url !== "undefined"){
        var url = direct_url;
    }else{
        var ticket = Gofast.get('ticket');
        var reference = node_ref.replace("workspace://SpacesStore/", "");
        var url = "/alfresco/service/api/node/workspace/SpacesStore/" + reference + "/content/thumbnails/pdf?c=force&alf_ticket=" + ticket;
    }
    $.ajax({
      url: url,
      type: "get",
      'beforeSend': function(xhr) {
        Gofast.xhrPool = Gofast.xhrPool || {};
        Gofast.xhrPool.xhrGetRemoteFile = xhr;  // before jQuery send the request we will add it into our object
      },
      'complete': function() {
        delete Gofast.xhrPool.xhrGetRemoteFile;
      },
    }).done(function (data) {
      Drupal.gofast_cmis.replace_content(url, modal,type);
    }).fail(function (error) {
      Drupal.gofast_cmis.replace_content(error, modal);
    });
  };

  Drupal.gofast_cmis.get_pdf_viewer = function (url) {
    var viewer = "/sites/all/libraries/pdf/web/viewer_gofast.html?v=238&file=";
    var hash = window.location.hash.substr(1);

    var myurl = new URL(window.location);
    var search = null;
    if(myurl.searchParams !== undefined && myurl.searchParam !== null){
      search = myurl.searchParams.get("search");
    }
    if(search == null){
         var complete_url = viewer + encodeURIComponent(url);
    }else{
         var complete_url = viewer + encodeURIComponent(url)+"#search="+search;
    }

    return complete_url;
  };

  Drupal.gofast_cmis.replace_content = function (data, modal , type) {
    if(modal == null){
       modal = false;
    }
    if(type == null && typeof data !== "undefined" && data !== null && typeof data.type !== "undefined" && data.type !== null){
        type = data.type;
    }
    var frame = "";
    var framed_content = '';
    if (data.status === 500) {
      frame = Drupal.t("Error while generating the preview of this file.", {}, {'context' : 'gofast:gofast_cmis'});
      frame += "<br />";
      var reason = Drupal.t("The document preview cannot be generated for this format.", {}, {'context' : 'gofast:gofast_cmis'});
      reason += " "+Drupal.t("Or maybe the preview process is temporarily out of service", {}, {'context' : 'gofast:gofast_cmis'});
      frame += reason;
      Gofast.toast(Drupal.t("Error while generating the preview of this file.", {}, {'context' : 'gofast:gofast_cmis'}) + '<br />' + reason, "warning", Drupal.t("Preview generation failed", {}, {'context' : 'gofast:gofast_cmis'}));
    } else {
      if(type !== undefined) {
        if(type === 'PDF') {
          if(typeof data == "string"){
              framed_content = Drupal.gofast_cmis.get_pdf_viewer(data);
          }else{
              framed_content = Drupal.gofast_cmis.get_pdf_viewer(data.link);
          }
        } else {
          framed_content = data;
        }
      } else {
        // Replace the document viewer frame with document
        framed_content = Drupal.gofast_cmis.get_pdf_viewer(data);
      }
      //var height = $(window).height();
      //var new_height = height - 150;
      //if(new_height > 800){
          var new_height = 800;
      //}
      if (type == 'other'){
          frame = '<div id="alfresco_content" class="alfresco_content_processed"><img width="100%" name="pdf-frame" style="border:none; z-index:0;" src="' + framed_content + '" ></div>';
      }else{
          frame = '<div id="alfresco_content" class="alfresco_content_processed"><iframe id="pdf_frame" width="100%" height="'+new_height+'" name="pdf-frame" style="border:none; z-index:0;" src="' + framed_content + '" target="_parent"><base target="_parent" /></iframe></div>';
      }
    }
    if(modal == true){
        $("#alfresco_content_modal").html(frame);
    }else{
        $("#alfresco_content").html(frame);
    }
    if (data.status === 500) {
        Drupal.gofast_cmis.show_generation_error_message();
     }
  };

  Drupal.gofast_cmis.show_loading = function () {
    var loading_content = '<div class="loader"><div class="loader-blog fa fa-3x"></div></div>';
    $("#alfresco_content").html(loading_content);
  };

  Drupal.gofast_cmis.show_generation_error_message = function () {
    var error_content = '<div class="document_transformation_error">';
    error_content += Drupal.t("Document transformation has failed last time, you can click to the following button to try another generation", {}, {'context' : 'gofast:gofast_cmis'}) + '<br />';
    error_content += '<button id="document_transformation_button" type="submit" class="btn btn-primary btn-sm">'
            + '<i class="glyphicon glyphicon-repeat"></i>'
            + "&nbsp;" + Drupal.t("Try another transformation", {}, {'context' : 'gofast:gofast_cmis'}) + "&nbsp;"
            + '</button>';
    error_content += '</div>';
    $("#alfresco_content").addClass('failed').html(error_content);
    $('#document_transformation_button').on('click', function () {
      Drupal.gofast_cmis.generate_node_preview(Gofast.get('node').id);
    });
  };
  Drupal.gofast_cmis.correct_generate_node_preview = function(node_id){
    $(".loader").html("");
    $(".loader").prepend('<p style="text-align: center;font-size: 2em; position: absolute; margin-left: 20px;">' + Drupal.t('Available in a few seconds...') + '</p><div class="loader-blog"></div>');
    //Change mimetype
        var url = "/gofast/correct_mimetype/" + node_id;
        $.ajax({
          url: url,
          type: "GET",
          dataType: "text"
        }).done(function (data) {
	  var url = "/gofast/ajax/generate_onlyoffice_preview/" + node_id;
          $.ajax({
            url: url,
            type: "POST",
            dataType: "json",
            'beforeSend': function(xhr) {
              Gofast.xhrPool = Gofast.xhrPool || {};
              Gofast.xhrPool.xhrGenerateNodePreview = xhr;  // before jQuery send the request we will add it into our object
            },
            'complete': function() {
              delete Gofast.xhrPool.xhrGenerateNodePreview;
            }
          }).done(function (data) {
            // Replace the div content with the PDFJS widget
	    if(data.status !== 'FALLBACK' && typeof(data.FileUrl) !== "undefined"){
		if (data.FileUrl.length > 0 &&  data.EndConvert === "True") {
		    Drupal.gofast_cmis.replace_content(data.FileUrl);
		}
	    }else{
		var url = "/gofast/ajax/generate_preview/" + node_id;
		$.ajax({
		url: url,
		type: "GET",
		dataType: "json",
		'beforeSend': function(xhr) {
		  Gofast.xhrPool = Gofast.xhrPool || {};
		  Gofast.xhrPool.xhrGenerateNodePreview = xhr;  // before jQuery send the request we will add it into our object
		},
		'complete': function() {
		  delete Gofast.xhrPool.xhrGenerateNodePreview;
		}
		}).done(function (data) {
		// Replace the div content with the PDFJS widget
		if (data.status === "OK") {
		  if(data.type !== undefined && data.type === 'PDF') {
		    Drupal.gofast_cmis.replace_content(data);
		  } else {
		    Drupal.gofast_cmis.get_remote_file(data.reference);
		  }
		} else {
		  if (data.ex && data.ex.indexOf("Transformation failed to obey timeout limit")) {
		    Gofast.toast(Drupal.t("The document took too much time to generate preview.", {}, {'context' : 'gofast:gofast_cmis'}), "warning", Drupal.t("Preview generation failed", {}, {'context' : 'gofast:gofast_cmis'}));
		  } else {
		    Gofast.toast(Drupal.t("Error while generating the preview of this file.", {}, {'context' : 'gofast:gofast_cmis'}), "warning", Drupal.t("Preview generation unavailable", {}, {'context' : 'gofast:gofast_cmis'}));
		  }
		  // Show the generate button
		  Drupal.gofast_cmis.show_generation_error_message();
		}
		}).fail(function (err) {
		console.log("Error with request");
		});
	    }
          }).fail(function (err) {
            console.log("Error with request generate onlyoffice preview");
          });
        });
  }
  Drupal.gofast_cmis.generate_node_preview = function (node_id) {
    Drupal.gofast_cmis.show_loading();
    $(".loader").prepend('<p style="text-align: center;font-size: 2em; position: absolute; margin-left: 20px;margin-top:50px;">' + Drupal.t('Preview is being generated') + '</p>');

    //Check mimetype
    var url = "/gofast/check_mimetype/" + node_id;
    $.ajax({
      url: url,
      type: "GET",
      dataType: "text"
    }).done(function (data) {
      if(data != "true"){ //Need mimetype modification
          if(data == "reload"){
              document.location.reload();
          }
        $(".loader").prepend('<p style="font-size: 1.7em; float:left;">' + Drupal.t('We need to correct this document. This will generate a minor version.') + '</p><button class="btn btn-default" onclick="Drupal.gofast_cmis.correct_generate_node_preview(' + node_id + ')"><i class="fa fa-wrench" aria-hidden="true"></i> ' + Drupal.t('Correct') + '</button>');
        $(".loader").find(".loader-blog").remove();
      }else{ //We can generate the preview
	var url = "/gofast/ajax/generate_onlyoffice_preview/" + node_id;
	$.ajax({
	url: url,
	type: "GET",
	dataType: "json",
	'beforeSend': function(xhr) {
	  Gofast.xhrPool = Gofast.xhrPool || {};
	  Gofast.xhrPool.xhrGenerateNodePreview = xhr;  // before jQuery send the request we will add it into our object
	},
	'complete': function() {
	  delete Gofast.xhrPool.xhrGenerateNodePreview;
	}
	}).done(function (data) {
            // Replace the div content with the PDFJS widget
	    if(data.status !== 'FALLBACK' && typeof(data.FileUrl) !== "undefined"){
		if (data.FileUrl.length > 0 &&  data.EndConvert === "True") {
		    Drupal.gofast_cmis.replace_content(data.FileUrl);
		}
	    }else{
		var url = "/gofast/ajax/generate_preview/" + node_id;
		$.ajax({
		  url: url,
		  type: "GET",
		  dataType: "json",
		  'beforeSend': function(xhr) {
		    Gofast.xhrPool = Gofast.xhrPool || {};
		    Gofast.xhrPool.xhrGenerateNodePreview = xhr;  // before jQuery send the request we will add it into our object
		  },
		  'complete': function() {
		    delete Gofast.xhrPool.xhrGenerateNodePreview;
		  }
		}).done(function (data) {
		  // Replace the div content with the PDFJS widget
		  if (data.status === "OK") {

		    if(data.value === "soffice_down"){
		       Gofast.toast(Drupal.t("The preview component is down", {}, {'context' : 'gofast:gofast_cmis'}) + '<br />' , "error", Drupal.t("Preview component error", {}, {'context' : 'gofast:gofast_cmis'}));
		    }

		    if(data.type !== undefined && data.type === 'PDF') {
		      Drupal.gofast_cmis.replace_content(data);
		    } else {
		      Drupal.gofast_cmis.get_remote_file(data.reference);
		    }
		  } else {
		    if (data.ex && data.ex.indexOf("Transformation failed to obey timeout limit")) {
		      Gofast.toast(Drupal.t("The document took too much time to generate preview.", {}, {'context' : 'gofast:gofast_cmis'}), "warning", Drupal.t("Preview generation failed", {}, {'context' : 'gofast:gofast_cmis'}));
		    } else {
		      Gofast.toast(Drupal.t("Error while generating the preview of this file.", {}, {'context' : 'gofast:gofast_cmis'}), "warning", Drupal.t("Preview generation unavailable", {}, {'context' : 'gofast:gofast_cmis'}));
		    }
		    // Show the generate button
		    Drupal.gofast_cmis.show_generation_error_message();
		  }
		}).fail(function (err) {
		  console.log("Error with request");
		});

	    }
	}).fail(function (err) {
	console.log("Error with request");
	});
      }
    }).fail(function (err) {
      console.log("Error with request");
    });
  };

  Drupal.gofast_cmis.reloadPreview = function() {
    $('#refresh-preview').prop('disabled', true);
    $('#alfresco_content').removeClass('alfresco_content_processed');
    Drupal.attachBehaviors('#alfresco_content');
    if(jQuery('iframe[name="frameEditor"]').length > 0){
        Gofast.docEditor.destroyEditor();
        Gofast.process_onlyoffice_editor();
    }
  };

  Drupal.behaviors.nodeRetrievePreview = {
    attach: function (context, settings) {
      $("#alfresco_content:not(.alfresco_content_processed)").addClass("alfresco_content_processed").each(function () {
        if ($("#alfresco_content").length > 0) {
          if (!$("#alfresco_content").hasClass('failed')) {
            var node = Gofast.get('node');
            Drupal.gofast_cmis.generate_node_preview(node.id);
          } else {
            Drupal.gofast_cmis.show_generation_error_message();
          }
        }
      });
    }
  };

   Drupal.behaviors.checkInternalOrConfidentialHideButton = {
    attach: function (context, settings) {
      Gofast.HidePrintButton();
    }
  };

})(jQuery, Gofast, Drupal);
