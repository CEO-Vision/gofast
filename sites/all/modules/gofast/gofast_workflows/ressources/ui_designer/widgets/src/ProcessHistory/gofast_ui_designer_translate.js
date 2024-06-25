!function(){
	var app = angular.module('bonitasoft.ui');

	app.filter('gfdTranslate', ['$sce', function ($sce) {
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
					
				},
				"fr" : {
					"The workflow has started" : "Le processus a démarré",
					"The document broadcast workflow has started. The users have been assigned to their tasks." : "Le processus de diffusion de documents a démarré. Les utilisateurs ont été assignés à leurs tâches.",
					
					"A task for contribution is finished" : "Une tâche pour contribution est terminée",
					"A task for comment is finished" : "Une tâche pour commentaire est terminée",
					"A task for information is finished" : "Une tâche pour information est terminée",
					"A task for validation is finished" : "Une tâche pour validation est terminée",
					"A task for signature is finished" : "Une tâche pour signature est terminée",
					
					"has finished his task for contribution" : "a clos sa tâche de contribution",
					"has finished his task for comment" : "a clos sa tâche pour commentaire",
					"has finished his task for information" : "a clos sa tâche pour information",
					"has finished his task for validation and has <strong style='color:#2ecc71'>accepted</strong> the validation" : "a <strong style='color:#2ecc71'>accepté</strong> la validation",
					"has finished his task for validation and has <strong style='color:#c0392b'>refused</strong> the validation" : "a <strong style='color:#c0392b'>refusé</strong> la validation",
					"has finished his task for validation and has <strong style='color:#f0ad4e'>Refused</strong> the validation and return the process to the validators" : "a <strong style='color:#f0ad4e'>Refusé</strong> la validation et renvoyé le processus aux validateurs",
					"has finished his task for validation and has <strong style='color:#f0ad4e'>Refused</strong> the validation and return the process to the contributors" : "a <strong style='color:#f0ad4e'>Refusé</strong> la validation et renvoyé le processus aux contributeurs",
					"has finished his task for signature" : "a clos sa tâche pour signature",
					
					"Starting workflow" : "Démarrage du processus",
					"Comment" : "Commentaire",
					"Actor(s)" : "Acteur(s)",
					"Document(s)" : "Document(s)",
					"A task for " : "La tâche ",
					" is finished" : " est terminée",
					"has finished his task for " : "a terminé sa tâche ",
					
					"For contribution" : "Pour contribution",
					"For Comment" : "Pour commentaire",
					"For Validation" : "Pour validation",
					"For Signature" : "Pour signature",
                                        "For Signature ( Yousign" : "Pour signature ( Yousign",
                                        "For Advanced Signature ( Yousign" : "Pour signature avancée ( Yousign",
                                        "For Signature (Pastell" : "Pour signature (Pastell",
					"For Information" : "Pour information",
					"A task has been reassigned" : "Une tâche a été réassignée",
				},
				"nl" : {
					"The workflow has started" : "De workflow is gestart",
					"The document broadcast workflow has started. The users have been assigned to their tasks." : "De workflow voor documentuitzending is gestart. De gebruikers zijn toegewezen aan hun taken.",
					
					"A task for contribution is finished" : "Een taak voor bijdrage is voltooid",
					"A task for comment is finished" : "Een taak voor commentaar is voltooid",
					"A task for information is finished" : "Een taak voor informatie is voltooid",
					"A task for validation is finished" : "Een validatietaak is voltooid",
					"A task for signature is finished" : "A task for signature is finished",
					
					"has finished his task for contribution" : "is klaar met zijn bijdrage",
					"has finished his task for comment" : "heeft zijn taak voor commentaar beëindigd",
					"has finished his task for information" : "heeft zijn taak ter informatie beëindigd",
					"has finished his task for validation and has <strong style='color:#2ecc71'>accepted</strong> the validation" : "heeft zijn validatietaak voltooid en heeft <strong style='color: #2ecc71'>geaccepteerd</strong> de validatie",
					"has finished his task for validation and has <strong style='color:#c0392b'>refused</strong> the validation" : "heeft zijn validatietaak voltooid en heeft <strong style='color: #c0392b'>de validatie geweigerd</strong>",
					"has finished his task for signature" : "is klaar met zijn handtekening",
					
					"Starting workflow" : "Werkstroom starten",
					"Comment" : "Commentaar",
					"Actor(s)" : "Acteur (s)",
					"Document(s)" : "Document(s)",
					"A task for " : "Een taak voor ",
					" is finished" : " is klaar",
					"has finished his task for " : "heeft zijn taak volbracht ",
					
					"For contribution" : "Voor bijdrage",
					"For Comment" : "Voor commentaar",
					"For Validation" : "Ter validatien",
					"For Signature" : "Voor handtekening",
                                        "For Signature ( Yousign" : "Voor handtekening ( Yousign",
                                        "For Advanced Signature ( Yousign" : "Voor geavanceerde handtekening ( Yousign",
                                        "For Signature (Pastell" : "Voor handtekening ( Pastell",
					"For Information" : "Ter informatie",
					"A task has been reassigned" : "Een taak is opnieuw toegewezen",
				},
			};
			//Return the translated content
			if(typeof item !== "string"){
			    item = $sce.valueOf(item);
			}
			
			if(typeof item == "string" && item.indexOf("|||") > -1){
				//There is parts we don't want to translate in there
				var parts = item.split("|||");
				var output = "";
				
				if(typeof localizations[langcode][parts[0]] !== "undefined"){
					output += localizations[langcode][parts[0]];
				}else if(typeof localizations[langcode]["en"] !== "undefined"){
					output += localizations[langcode]["en"];
				}else{
					output += parts[0];
				}
				
				output += parts[1];
				
				if(typeof(parts[2]) == "string" && parts[2] !== ""){
					if(typeof localizations[langcode][parts[2]] !== "undefined"){
						output += localizations[langcode][parts[2]];
					}else if(typeof localizations[langcode]["en"] !== "undefined"){
						output += localizations[langcode]["en"];
					}else{
						output += parts[2];
					}
				}
				
				return output;
				
			}else{
				if(typeof localizations[langcode][item] !== "undefined"){
					return $sce.trustAsHtml($sce.valueOf(localizations[langcode][item]));
				}else if(typeof localizations[langcode]["en"] !== "undefined"){
					return $sce.trustAsHtml($sce.valueOf(localizations[langcode]["en"]));
				}else{
					return $sce.trustAsHtml($sce.valueOf(item));
				}
			}
		};
	}]);
}();