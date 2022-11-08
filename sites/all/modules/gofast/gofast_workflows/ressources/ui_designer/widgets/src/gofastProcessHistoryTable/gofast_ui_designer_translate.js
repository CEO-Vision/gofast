!function(){
	var app = angular.module('bonitasoft.ui');

	app.filter('gfTranslateHistory', function () {
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
					"label.process_finished" : "This process is finished",
					"label.process_title" : "Process title",
					"label.process_deadline" : "Deadline",
					"label.process_start_date" : "Start date",
					"label.process_end_date" : "End date",
					"label.process_doit" : "Execute the task",
					"label.process_history" : "Display history"
				},
				"fr" : {
					"label.process_finished" : "Ce processus est terminé",
					"label.started_by" : "Démarré par",
					"label.assigned_to" : "Assigné à",
					"label.process_soon_outdated": "Ce processus va bientôt atteindre sa date limite",
					"label.process_outdated" : "Ce processus a dépassé sa date limite",
					"label.process_title" : "Titre du processus",
					"label.process_start_date" : "Date de démarrage",
					"label.process_end_date" : "Date de fin",
					"label.process_deadline" : "Date d'échéance",
					"label.process_doit" : "Executer la tâche",
					"label.process_history" : "Afficher l'historique"
				},
				"nl" : {
					"label.process_finished" : "Dit proces is voltooid",
					"label.started_by" : "Gestart door",
					"label.assigned_to" : "toegewezen aan",
					"label.process_soon_outdated": "Dit proces bereikt binnenkort de deadline",
					"label.process_outdated" : "Dit proces is verouderd",
					"label.process_title" : "Procestitel",
					"label.process_start_date" : "Begin datum",
					"label.process_deadline" : "Deadline",
					"label.process_doit" : "Voer de taak uit",
					"label.process_history" : "Geschiedenis weergeven"
					
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