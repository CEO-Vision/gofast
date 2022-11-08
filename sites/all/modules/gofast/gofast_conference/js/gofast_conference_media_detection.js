(function ($, Drupal, Gofast, DetectRTC) {
  'use trict';
  Drupal.behaviors.createMediaReport = {
    attach: function(context, settings) {
		
		$('#report_detection_media:not(.processed)').addClass('processed').each(function(){
			
		
			function checkMedia(selector, result) {
			  if (result) {
				$(selector + ' .result_icon').addClass('fas fa-check text-success');
			  } else {
				$(selector + ' .result_icon').addClass('fas fa-exclamation-triangle text-warning');
			  }
			}
			
			function summariseMedia(name) {
			  if ($('#' + name + ' .non_supported').length > 0) {
				$('#heading_' + name).addClass('heading_device non_supported');
				$('#heading_' + name + ' a').append('<span class="glyphicon glyphicon-alert result_icon"></span>');
			  } else {
				$('#heading_' + name).addClass('heading_device supported');
				$('#heading_' + name + ' a').append('<span class="glyphicon glyphicon-ok result_icon"></span>');
			  }
			}
			
			function summariseOthers() {
			  $('#report_result_others ul').append("<li>" + Drupal.t("Display resolution : !resolution", { "!resolution": DetectRTC.displayResolution }, { context: "gofast:gofast_conference" }) + "</li>");
			  $('#report_result_others ul').append("<li>" + Drupal.t("Browser : !browser", { "!browser": DetectRTC.browser.name }, { context: "gofast:gofast_conference" }) + "</li>");
			  $('#report_result_others ul').append("<li>" + Drupal.t("Browser's version : !version", { "!version": DetectRTC.browser.fullVersion }, { context: "gofast:gofast_conference" }) + "</li>");
			}
			
			//$('#report_detection_media').html('');
			$('#report_detection_media').addClass('text-center');
			$('#report_detection_media').append('<div class="fa fa-spinner fa-spin" style="font-size: 24px;"></div>');  
			setTimeout(function () {
			  $('#report_detection_media > .fa-spinner').remove();
			  $('#report_detection_media').removeClass('text-center');
			  $('#report_result').fadeIn(1000);
			  

			  checkMedia('#camera', DetectRTC.hasWebcam);
			  checkMedia('#audio', DetectRTC.hasSpeakers);
			  checkMedia('#microphone', DetectRTC.hasMicrophone);
			  
			  checkMedia('#webrtc', DetectRTC.isWebRTCSupported);
			  checkMedia('#websocket', DetectRTC.isWebSocketsSupported);
			  
			  
			  
			  summariseMedia('main_devices');
			  summariseMedia('protocols');
			  
			  summariseOthers();
              
              $(document).ready(function(){
                //Resize user pictures
                $('.gofast-participant').find('img').width(15).height(15);
                $('.gofast-participant').css('min-height', 0);
                $('.gofast-participant').css('line-height', 0);
                $('.gofast-participant').css('float', 'none');  
                $('.gofast-participant').css('border', 'none');
                $('.gofast-participant').css('font-size', '1em');
                
                //Click on display link
                $("#conference-pc-link-display").click(function(){
                  $("#conference-pc-link").show();
                });
				$("#conference-pc-link").click(function(){
				  $("#conference-pc-link").hide();
				})
              });
			  
			  setTimeout(function () {
				$('#heading_main_devices a').trigger('click');
			  }, 500);
			  setTimeout(function () {
				$('#heading_protocols a').trigger('click');
			  }, 1000);
			  setTimeout(function () {
				$('#heading_others a').trigger('click');
			  }, 1500);
			  if (!DetectRTC.isWebRTCSupported || !DetectRTC.isWebSocketsSupported) {
				$('#panel_conference_url').remove();
				$('#report_result').prepend('<div class="alert alert-danger" role="alert">'+Drupal.t("Your browser can't use Jitsi-meet conference due to the lack of protocol's support", {}, {'context' : 'gofast:gofast_conference'})+'</div>');
			  } else {
				setTimeout(function() {
				  $('#panel_conference_url').slideDown();
				}, 2000);
			  }
			  
			  
			}, 500);
		});
	}
	
  };
  
})(jQuery, Drupal, Gofast, DetectRTC);

