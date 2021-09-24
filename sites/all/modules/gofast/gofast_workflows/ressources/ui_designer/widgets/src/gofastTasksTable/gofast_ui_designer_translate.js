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
					"label.process_finished" : "This process is finished",
					"label.started_by" : "Started by",
					"label.assigned_to" : "Assigned to",
					"label.process_soon_outdated": "This process will soon reach it deadline",
					"label.process_outdated" : "This process has outdated it deadline",
					"label.process_title" : "Title",
					"label.process_start_date" : "Start date",
					"label.process_deadline" : "Deadline",
					"label.process_doit" : "Execute the task",
					"label.process_delete" : "Delete the process",
					"label.process_history" : "Display history",
					"label.completed_at" : "Completed at",
					"label.responsible" : "Responsible"
					
				},
				"fr" : {
					"label.process_finished" : "Ce processus est terminé",
					"label.started_by" : "Démarré par",
					"label.assigned_to" : "Assigné à",
					"label.process_soon_outdated": "Ce processus va bientôt atteindre sa date limite",
					"label.process_outdated" : "Ce processus a dépassé sa date limite",
					"label.process_title" : "Titre",
					"label.process_start_date" : "Date de démarrage",
					"label.process_deadline" : "Date d'échéance",
					"label.process_doit" : "Executer la tâche",
					"label.process_delete" : "Supprimer le processus",
					"label.process_history" : "Afficher l'historique",
					"For contribution" : "Pour contribution",
					"For Comment" : "Pour commentaire",
					"For Validation" : "Pour validation",
					"For Signature" : "Pour signature",
					"For Information" : "Pour information",
					"label.completed_at" : "Complété à",
					"label.responsible" : "Responsable"
				},
				"nl" : {
					"label.process_finished" : "Dit proces is voltooid",
					"label.started_by" : "Gestart door",
					"label.assigned_to" : "toegewezen aan",
					"label.process_soon_outdated": "Dit proces bereikt binnenkort de deadline",
					"label.process_outdated" : "Dit proces is verouderd",
					"label.process_title" : "Titel",
					"label.process_start_date" : "Begin datum",
					"label.process_deadline" : "Deadline",
					"label.process_doit" : "Voer de taak uit",
					"label.process_delete" : "Verwijder het proces",
					"label.process_history" : "Geschiedenis weergeven",
					"For contribution" : "Voor bijdrage",
					"For Comment" : "Voor commentaar",
					"For Validation" : "Ter validatien",
					"For Signature" : "Voor handtekening",
					"For Information" : "Ter informatie",
					"label.completed_at" : "Voltooid om",
					"label.responsible" : "Verantwoordelijk"
				},
			};
			
			//Return the translated content
			if(typeof localizations[langcode][item] !== "undefined"){
				return localizations[langcode][item];
			}else if(typeof localizations[langcode]["en"] !== "undefined"){
				return localizations[langcode]["en"];
			}else{
				return item;
			}
		};
	});
}();