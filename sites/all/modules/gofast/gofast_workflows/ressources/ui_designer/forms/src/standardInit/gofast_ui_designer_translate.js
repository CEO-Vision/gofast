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
					"header.work_task" : "Work tasks",
					"header.validation_task" : "Validation tasks",
					"header.sign_task" : "Signature tasks",
					
					"label.processTitle" : "Title of your process",
					"label.deadline" : "Deadline",
					"label.comment" : "Comment",
					"label.customStepTitle" : "Custom step name",
					"label.for" : "For",
					"label.isValidationTask" : "Validation task",
					"label.isSequentialSign" : "Sequential signature",
					"label.isSequentialValidation" : "Sequential validation",
					"label.externalSigner" : "External signer",
					"label.user" : "User",
					"label.signaturePosition" : "Signature position",
					"label.lastname" : "Lastname",
					"label.firstname" : "Firstname",
                    "label.mail" : "Mail",
                    "label.phone" : "Mobile Phone",
                    "label.typeSigner" : "Signer type",
                    "label.name_profil" : "Model name",
					"label.space_profil" : "Restrict model availability to users in the following spaces:",
					
					"placeholder.deadline" : "Enter a date (mm/dd/yyyy)",
					"placeholder.documents" : "Document title or identifier",
					"placeholder.attributions" : "User firstname, lastname or identifier",
					"placeholder.customStep" : "Type the name of your custom step",
					"placeholder.yousignDisabled" : "Yousign signature module is disabled on this server, several signature options are not available",
					"placeholder.pastellDisabled" : "Pastell signature module is disabled on this server, several signature options are not available",
					"placeholder.sequential" :"Sent one at a time, in the order of the lines below",
					"placeholder.parallel" : "All tasks will be sent at the same time",
					"placeholder.transform" : "Transform the documents",
					"placeholder.space_profil" : "Leave empty to not restrict",
					"placeholder.task_end_date" : "Task expiration date",
					
					
					"button.add.documents" : "Add a document",
					"button.remove.documents" : "Remove",
					"button.add.attributions" : "Add an attribution",
					"button.remove.attributions" : "Remove",
					"button.submit" : "Submit",
					"button.edit_profil" : "Edit workflow model",
				    "button.new_profil" : "Create workflow model",
					
					
					"placeholder.list.attributions" : "Attribution type",
					
					"customStepWarning" : "Your custom steps will be assigned one by one, after validation steps and before signature steps, in the order you declared them.",
					
					"duplicateSignPosition" : "You can't choose same signature position multiple time",
					
					
				},
				"fr" : {
					"header.informations" : "Informations",
					"header.documents" : "Document(s)",
					"header.attributions" : "Assignation(s)",
					"header.work_task" : "Etapes de travail",
					"header.validation_task" : "Etapes de validation",
					"header.sign_task" : "Etapes de signature",
					
					"label.processTitle" : "Titre de votre processus",
					"label.deadline" : "Date d'échéance",
					"label.comment" : "Commentaire",
					"label.customStepTitle" : "Nom de l'étape suplémentaire",
					"label.for" : "Pour",
					"label.isValidationTask" : "Tâche de validation",
					"label.isSequentialSign" : "Signature séquentielle",
					"label.isSequentialValidation" : "Validation séquentielle",
					"label.externalSigner" : "Signataire externe",
					"label.user" : "Utilisateur",
					"label.signaturePosition" : "Position de la signature",
					"label.lastname" : "Nom",
					"label.firstname" : "Prénom",
                    "label.mail" : "Mail",
                    "label.phone" : "Portable",
                    "label.typeSigner" : "Type de signataire",
                    "label.name_profil" : "Nom du modèle",
					"label.space_profil" : "Restreindre la disponibilité du modèle aux utilisateurs des espaces suivants",
					
					"placeholder.deadline" : "Saisissez une date (mm/dd/yyyy)",
					"placeholder.documents" : "Titre ou identifiant du document",
					"placeholder.attributions" : "Nom, prénom ou identifiant de l'utilisateur",
					"placeholder.customStep" : "Saissisez le nom de votre étape supplémentaire",
					"placeholder.yousignDisabled" : "Le module de signature Yousign n'est pas activé sur ce serveur, certaines options de signature ne sont donc pas disponibles",
					"placeholder.pastellDisabled" : "Le module Pastell n'est pas activé sur ce serveur, certaines options de signature ne sont donc pas disponibles",
					"placeholder.sequential" :"Envoyées l’une après l’autre, dans l’ordre des lignes ci-dessous",
					"placeholder.parallel" : "Toutes les tâches seront envoyées en même temps",
					"placeholder.transform" : "Transformer les documents",
					"placeholder.space_profil" : "Laisser vide pour ne pas restreindre",
					"placeholder.task_end_date" : "Date d'expiration de la tâche",
					
					"button.add.documents" : "Ajouter un document",
					"button.remove.documents" : "Retirer",
					"button.add.attributions" : "Ajouter une assignation",
					"button.remove.attributions" : "Retirer",
					"button.submit" : "Envoyer",
					"button.edit_profil" : "Modifier le modèle de processus",
				    "button.new_profil" : "Créer le modèle de processus",
					
					"placeholder.list.attributions" : "Type d'attribution",
					
					"Today" : "Aujourd'hui",
					
					"customStepWarning" : "Vos étapes supplémentaires seront assignés unes par unes, après les étapes de validation et avant les étapes de signature, dans l'ordre ou vous les avez déclarés.",
					
					"duplicateSignPosition" : "Vous ne pouvez pas choisir la même position de signature plusieurs fois",
				},
				"nl" : {
					"header.informations" : "Informations",
					"header.documents" : "Documenten",
					"header.attributions" : "Bevoegdheden",
					"header.work_task" : "Werk taken",
					"header.validation_task" : "Validatietaken",
					"header.sign_task" : "Handtekeningstaken",
					
					"label.processTitle" : "Titel van uw proces",
					"label.deadline" : "Deadline",
					"label.comment" : "Commentaar",
					"label.customStepTitle" : "Custom step name",
					"label.for" : "For",
					"label.isValidationTask" : "Is a validation task ?",
					"label.isSequentialSign" : "Is a sequential signature ?",
					"label.isSequentialValidation" : "Is a sequential validation ?",
					"label.externalSigner" : "External signer",
					"label.user" : "User",
					"label.signaturePosition" : "Signature position",
					"label.lastname" : "Lastname",
					"label.firstname" : "Firstname",
                    "label.mail" : "Mail",
                    "label.phone" : "Mobile Phone",
                    "label.name_profil" : "Model name",
					"label.space_profil" : "Beperk de beschikbaarheid van het model tot gebruikers in de volgende ruimtes",
					
					"placeholder.deadline" : "Voer een datum in (mm/dd/yyyy)",
					"placeholder.documents" : "Documenttitel of identificatie",
					"placeholder.attributions" : "Voornaam gebruiker, achternaam of identificatie",
					"placeholder.customStep" : "Type the name of your custom step",
					"placeholder.yousignDisabled" : "De handtekeningmodule van Yousign is uitgeschakeld op deze server, verschillende ondertekeningsopties zijn niet beschikbaar",
					"placeholder.pastellDisabled" : "De handtekeningmodule van Pastell is uitgeschakeld op deze server, verschillende ondertekeningsopties zijn niet beschikbaar",
					"placeholder.sequential" :"Een voor een verzonden, in de volgorde van de onderstaande regels",
					"placeholder.parallel" : "Alle taken worden tegelijkertijd verzonden",
					"placeholder.transform" : "Transformeer documenten",
					"placeholder.space_profil" : "Leeg laten om niet te beperken",
					"placeholder.task_end_date" : "Taak vervaldatum",
					
					"button.add.documents" : "Voeg een document toe",
					"button.remove.documents" : "Verwijderen",
					"button.add.attributions" : "Voeg een toeschrijving toe",
					"button.remove.attributions" : "Verwijderen",
					"button.submit" : "Voorleggen",
					"button.edit_profil" : "Workflow-model bewerken",
				    "button.new_profil" : "Creëer een werkstroommodel",
					
					"placeholder.list.attributions" : "Toeschrijvingstype",
					
					"Today" : "Vandaag",
					
					"customStepWarning" : "Your custom steps will be triggered one by one, after validation steps and before signature steps, in the order you declared them.",
					
					"duplicateSignPosition" : "You can't choose same signature position multiple time",
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
	
	app.filter('uiTranslate', function () {
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
					
					"Today" : "Aujourd'hui"
				},
				"nl" : {
					
					"Today" : "Vandaag"
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