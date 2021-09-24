!function(){
	var app = angular.module('bonitasoft.ui');

	app.filter('gfTranslate', function () {
		return function (item) {
			//Retrieve URL parameters
			var params = {};

			if (location.search) {
				var parts = location.search.substring(1).split('&');

				for (var i = 0; i < parts.length; i++) {
					var nv = parts[i].split('=');
					if (!nv[0]) continue;
					params[nv[0]] = nv[1] || true;
				}
			}
			
			//Get the langcode from the URL
			var langcode = params.locale;
			if(typeof langcode == "undefined"){
				langcode = "en";
			}
			//Declare localizations
			var localizations = {
				"en" : {
					"header.comment" : "Comment",
					"header.comment_initiator" : "Initiator comment",
					"header.history" : "History",
					
					"button.submit" : "Submit",
				},
				"fr" : {
					"header.comment" : "Commentaire",
					"header.comment_initiator" : "Commentaire de l'initiateur",
					"header.history" : "Historique",
					
					"button.submit" : "Envoyer",
				},
				"nl" : {
					"header.comment" : "Commentaar",
					"header.comment_initiator" : "Reactie van initiator",
					"header.history" : "Geschiedenis",
					
					"button.submit" : "Voorleggen",
				},
			};
			
			//Return the translated content
			if(typeof localizations[langcode][item] !== "undefined"){
				return localizations[langcode][item];
			}else if(typeof localizations[langcode]["en"] !== "undefined"){
				return localizations[langcode]["en"];
			}else{
				return "Translation not found for key : " + item;
			}
		};
	});
}();