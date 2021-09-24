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
					"header.informations" : "Informations",
					"header.documents" : "Document(s)",
					"header.attributions" : "Attributions",
					
					"label.processTitle" : "Title of your process",
					"label.deadline" : "Deadline",
					"label.comment" : "Comment",
					
					"placeholder.deadline" : "Enter a date (mm/dd/yyyy)",
					"placeholder.documents" : "Document title or identifier",
					"placeholder.attributions" : "User firstname, lastname or identifier",
					
					"button.add.documents" : "Add a document",
					"button.remove.documents" : "Remove",
					"button.add.attributions" : "Add an attribution",
					"button.remove.attributions" : "Remove",
					"button.submit" : "Submit",
					
					"placeholder.list.attributions" : "Attribution type",
				},
				"fr" : {
					"header.informations" : "Informations",
					"header.documents" : "Document(s)",
					"header.attributions" : "Assignation(s)",
					
					"label.processTitle" : "Titre de votre processus",
					"label.deadline" : "Date d'échéance",
					"label.comment" : "Commentaire",
					
					"placeholder.deadline" : "Saisissez une date (mm/dd/yyyy)",
					"placeholder.documents" : "Titre ou identifiant du document",
					"placeholder.attributions" : "Nom, prénom ou identifiant de l'utilisateur",
					
					"button.add.documents" : "Ajouter un document",
					"button.remove.documents" : "Retirer",
					"button.add.attributions" : "Ajouter une assignation",
					"button.remove.attributions" : "Retirer",
					"button.submit" : "Envoyer",
					
					"placeholder.list.attributions" : "Type d'attribution",
				},
				"nl" : {
					"header.informations" : "Informations",
					"header.documents" : "Documenten",
					"header.attributions" : "Bevoegdheden",
					
					"label.processTitle" : "Titel van uw proces",
					"label.deadline" : "Deadline",
					"label.comment" : "Commentaar",
					
					"placeholder.deadline" : "Voer een datum in (mm/dd/yyyy)",
					"placeholder.documents" : "Documenttitel of identificatie",
					"placeholder.attributions" : "Voornaam gebruiker, achternaam of identificatie",
					
					"button.add.documents" : "Voeg een document toe",
					"button.remove.documents" : "Verwijderen",
					"button.add.attributions" : "Voeg een toeschrijving toe",
					"button.remove.attributions" : "Verwijderen",
					"button.submit" : "Voorleggen",
					
					"placeholder.list.attributions" : "Toeschrijvingstype",
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