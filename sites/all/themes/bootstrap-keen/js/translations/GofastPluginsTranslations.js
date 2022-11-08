// localizations for select2
$.fn.select2.amd.define("select2/i18n/fr", [], function () {
    return {
      errorLoading: function () {
        return "Les résultats ne peuvent pas être chargés.";
      },
      inputTooLong: function (e) {
        var n = e.input.length - e.maximum;
        return "Supprimez " + n + " caractère" + (n > 1 ? "s" : "");
      },
      inputTooShort: function (e) {
        var n = e.minimum - e.input.length;
        return "Saisissez au moins " + n + " caractère" + (n > 1 ? "s" : "");
      },
      loadingMore: function () {
        return "Chargement de résultats supplémentaires…";
      },
      maximumSelected: function (e) {
        return (
          "Vous pouvez seulement sélectionner " +
          e.maximum +
          " élément" +
          (e.maximum > 1 ? "s" : "")
        );
      },
      noResults: function () {
        return "Aucun résultat trouvé";
      },
      searching: function () {
        return "Recherche en cours…";
      },
      removeAllItems: function () {
        return "Supprimer tous les éléments";
      },
      removeItem: function () {
        return "Supprimer l'élément";
      },
    };
});
$.fn.select2.amd.define("select2/i18n/nl", [], function () {
    return {
      errorLoading: function () {
        return "De resultaten konden niet worden geladen.";
      },
      inputTooLong: function (e) {
        return (
          "Gelieve " + (e.input.length - e.maximum) + " karakters te verwijderen"
        );
      },
      inputTooShort: function (e) {
        return (
          "Gelieve " +
          (e.minimum - e.input.length) +
          " of meer karakters in te voeren"
        );
      },
      loadingMore: function () {
        return "Meer resultaten laden…";
      },
      maximumSelected: function (e) {
        var n = 1 == e.maximum ? "kan" : "kunnen",
          r = "Er " + n + " maar " + e.maximum + " item";
        return 1 != e.maximum && (r += "s"), (r += " worden geselecteerd");
      },
      noResults: function () {
        return "Geen resultaten gevonden…";
      },
      searching: function () {
        return "Zoeken…";
      },
      removeAllItems: function () {
        return "Verwijder alle items";
      },
    };
});

// localizations for datepicker
window.setDatepickerL18n = function() {
    $.fn.datepicker.dates["fr"] = {
        days: ["Dimanche", "Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi"],
        daysShort: ["Dim", "Lun", "Mar", "Mer", "Jeu", "Ven", "Sam"],
        daysMin: ["Di", "Lu", "Ma", "Me", "Je", "Ve", "Sa"],
        months: ["Janvier", "Février", "Mars", "Avril", "Mai", "Juin", "Juillet", "Août", "Septembre", "Octobre", "Novembre", "Décembre"],
        monthsShort: ["Jan", "Fév", "Mar", "Avr", "Mai", "Jun", "Jul", "Aoû", "Sep", "Oct", "Nov", "Déc"],
        today: "Aujourd'hui",
        clear: "Effacer",
    };
    $.fn.datepicker.dates["nl"] = {
        days: ["zondag", "maandag", "dinsdag", "woensdag", "donderdag", "vrijdag", "zaterdag"],
        daysShort: ["zo", "ma", "di", "wo", "do", "vr", "za"],
        daysMin: ["zo", "ma", "di", "wo", "do", "vr", "za"],
        months: ["januari", "februari", "maart", "april", "mei", "juni", "juli", "augustus", "september", "oktober", "november", "december"],
        monthsShort: ["jan", "feb", "mrt", "apr", "mei", "jun", "jul", "aug", "sep", "okt", "nov", "dec"],
        today: "Vandaag",
        clear: "Wissen",
    };
    // in case something goes wrong
    moment.updateLocale("fr", { invalidDate: "Date invalide" });
}

// localizations for datepicker
CKEDITOR_TRANSLATIONS.fr = {
  dictionary: {
    "%0 of %1": "%0 sur %1",
    Aquamarine: "Bleu vert",
    Black: "Noir",
    "Block quote": "Citation en bloc",
    Blue: "Bleu",
    Bold: "Gras",
    "Break text": "Casser le texte",
    "Bulleted List": "Liste à puces",
    Cancel: "Annuler",
    "Cannot upload file:": "Impossible de télécharger le fichier :",
    "Centered image": "Image centrée",
    "Change image text alternative": "Modifier l'alternative textuelle à l'image",
    "Choose heading": "Choisissez l'en-tête",
    Column: "Colonne",
    "Could not insert image at the current position.":
      "Impossible d'insérer l'image à la position actuelle.",
    "Could not obtain resized image URL.":
      "Impossible d'obtenir l'URL de l'image redimensionnée.",
    "Decrease indent": "Diminuer le retrait",
    "Delete column": "Supprimer la colonne",
    "Delete row": "Supprimer la ligne",
    "Dim grey": "Gris foncé",
    Downloadable: "Téléchargable",
    "Dropdown toolbar": "Barre d'outils déroulante",
    "Edit block": "Modifier le bloc",
    "Edit link": "Modifier le lien",
    "Editor toolbar": "Barre d'outils de l'éditeur",
    "Enter image caption": "Saisir la légende de l'image",
    "Full size image": "Image pleine taille",
    Green: "Vert",
    Grey: "Gris",
    "Header column": "Colonne d'en-tête",
    "Header row": "Ligne d'en-tête",
    Heading: "Titre",
    "Heading 1": "Titre 1",
    "Heading 2": "Titre 2",
    "Heading 3": "Titre 3",
    "Heading 4": "Titre 4",
    "Heading 5": "Titre 5",
    "Heading 6": "Titre 6",
    "Image toolbar": "Barre d'outils des images",
    "image widget": "widget d'image",
    "In line": "En ligne",
    "Increase indent": "Augmenter le retrait",
    "Insert column left": "Insérer une colonne à gauche",
    "Insert column right": "Insérer une colonne à droite",
    "Insert image": "Insérer une image",
    "Insert image or file": "Insérer une image ou un fichier",
    "Insert media": "Insérer un média",
    "Insert paragraph after block": "Insérer un paragraphe après le bloc",
    "Insert paragraph before block": "Insérer un paragraphe avant le bloc",
    "Insert row above": "Insérer une ligne au-dessus",
    "Insert row below": "Insérer une ligne en-dessous",
    "Insert table": "Insérer une table",
    "Inserting image failed": "L'insertion de l'image a échoué",
    Italic: "Italique",
    "Left aligned image": "Image alignée à gauche",
    "Light blue": "Bleu clair",
    "Light green": "Vert clair",
    "Light grey": "Gris clair",
    Link: "Lien",
    "Link URL": "URL du lien",
    "Media URL": "URL du média",
    "media widget": "widget de média",
    "Merge cell down": "Fusionner la cellule vers le bas",
    "Merge cell left": "Fusionner la cellule vers la gauche",
    "Merge cell right": "Fusionner la cellule vers la droite",
    "Merge cell up": "Fusionner la cellule vers le haut",
    "Merge cells": "Fusionner les cellules",
    Next: "Suivant",
    "Numbered List": "Liste numérotée",
    "Open in a new tab": "Ouvrir dans un nouvel onglet",
    "Open link in new tab": "Ouvrir le lien dans un nouvel onglet",
    Orange: "Orange",
    Paragraph: "Paragraphe",
    "Paste the media URL in the input.": "Coller l'URL du média dans l'entrée",
    Previous: "Précédent",
    Purple: "Violet",
    Red: "Rouge",
    Redo: "Refaire",
    "Rich Text Editor": "Éditeur de texte enrichi",
    "Rich Text Editor, %0": "Éditeur de texte enrichi, %0",
    "Right aligned image": "Image alignée à droite",
    Row: "Ligne",
    Save: "Sauvegarder",
    "Select all": "Sélectionner tout",
    "Select column": "Sélectionner la colonne",
    "Select row": "Sélectionner la ligne",
    "Selecting resized image failed":
      "Échec de la sélection de l'image redimensionnée",
    "Show more items": "Afficher plus d'éléments",
    "Side image": "Image latérale",
    "Split cell horizontally": "Fractionner la cellule horizontalement",
    "Split cell vertically": "Fractionner la cellule verticalement",
    "Table toolbar": "Barre d'outils de la table",
    "Text alternative": "Alternative textuelle",
    "The URL must not be empty.": "The URL must not be empty.",
    "This link has no URL": "L'URL ne doit pas être vide.",
    "This media URL is not supported.": "L'URL du média n'est pas supportée.",
    "Tip: Paste the URL into the content to embed faster.":
      "Conseil : collez l'URL dans le contenu pour l'intégrer plus rapidement.",
    "Toggle caption off": "Désactiver la légende",
    "Toggle caption on": "Activer la légende",
    Turquoise: "Turquoise",
    Undo: "Défaire",
    Unlink: "Dissocier",
    "Upload failed": "Le téléversement a échoué",
    "Upload in progress": "Téléversement en cours",
    White: "Blanc",
    "Widget toolbar": "Barre d'outils des widgetsr",
    "Wrap text": "Envelopper le texte",
    Yellow: "Jaune",
  },
};

CKEDITOR_TRANSLATIONS.nl = {
  dictionary: {
    "%0 of %1": "%0 van %1",
    Aquamarine: "Aquamarijn",
    Black: "Zwart",
    "Block quote": "Citaatblok",
    Blue: "Blauw",
    Bold: "Vetgedrukt",
    "Break text": "Tekst breken",
    "Bulleted List": "Lijst met opsommingstekens",
    Cancel: "Annuleren",
    "Cannot upload file:": "Kan bestand niet uploaden:",
    "Centered image": "Gecentreerde afbeelding",
    "Change image text alternative": "Alternatief voor afbeeldingstekst wijzigen",
    "Choose heading": "Kies kop",
    Column: "Kolom",
    "Could not insert image at the current position.":
      "Kan afbeelding niet invoegen op de huidige positie.",
    "Could not obtain resized image URL.":
      "Kan de verkleinde afbeeldings-URL niet verkrijgen.",
    "Decrease indent": "Inspringing verkleinen",
    "Delete column": "Kolom verwijderen",
    "Delete row": "Verwijder rij",
    "Dim grey": "Dim grijs",
    Downloadable: "Downloadbaar",
    "Dropdown toolbar": "Dropdown-werkbalk",
    "Edit block": "Blok bewerken",
    "Edit link": "Link bewerken",
    "Editor toolbar": "Editor werkbalk",
    "Enter image caption": "Voer afbeeldingsbijschrift in",
    "Full size image": "Afbeelding op volledige grootte",
    Green: "Groente",
    Grey: "Grijs",
    "Header column": "Kopkolom",
    "Header row": "Koptekstrij",
    Heading: "Rubriek",
    "Heading 1": "Koptekst 1",
    "Heading 2": "Koptekst 2",
    "Heading 3": "Koptekst 3",
    "Heading 4": "Koptekst 4",
    "Heading 5": "Koptekst 5",
    "Heading 6": "Koptekst 6",
    "Image toolbar": "Afbeeldingswerkbalks",
    "image widget": "afbeelding widget",
    "In line": "In lijn",
    "Increase indent": "Inspringing vergroten",
    "Insert column left": "Kolom links invoegen",
    "Insert column right": "Kolom rechts invoegen",
    "Insert image": "Voeg afbeelding in",
    "Insert image or file": "Afbeelding of bestand invoegen",
    "Insert media": "Media invoegen",
    "Insert paragraph after block": "Alinea na blok invoegen",
    "Insert paragraph before block": "Alinea invoegen voor blok",
    "Insert row above": "Rij hierboven invoegen",
    "Insert row below": "Rij hieronder invoegen",
    "Insert table": "Tabel invoegen",
    "Inserting image failed": "Afbeelding invoegen mislukt",
    Italic: "Cursief",
    "Left aligned image": "Links uitgelijnde afbeelding",
    "Light blue": "Lichtblauw",
    "Light green": "Licht groen",
    "Light grey": "Lichtgrijs",
    Link: "Link",
    "Link URL": "Link-URL",
    "Media URL": "Media-URL",
    "media widget": "mediawidget",
    "Merge cell down": "Cel naar beneden samenvoegen",
    "Merge cell left": "Cel links samenvoegen",
    "Merge cell right": "Cel rechts samenvoegen",
    "Merge cell up": "Cel samenvoegen",
    "Merge cells": "Cellen samenvoegen",
    Next: "Volgende",
    "Numbered List": "Genummerde lijst",
    "Open in a new tab": "Open in een nieuw tabblad",
    "Open link in new tab": "Open link in nieuw tabblad",
    Orange: "Oranje",
    Paragraph: "Paragraaf",
    "Paste the media URL in the input.": "Plak de media-URL in de invoer.",
    Previous: "Vorig",
    Purple: "Purper",
    Red: "Rood",
    Redo: "Opnieuw doen",
    "Rich Text Editor": "Rich Text-editor",
    "Rich Text Editor, %0": "Rich Text-editor, %0",
    "Right aligned image": "Rechts uitgelijnde afbeelding",
    Row: "Rij",
    Save: "Opslaan",
    "Select all": "Selecteer alles",
    "Select column": "Selecteer kolom",
    "Select row": "Selecteer rij",
    "Selecting resized image failed":
      "Het selecteren van een afbeelding met een aangepast formaat is mislukt",
    "Show more items": "Toon meer items",
    "Side image": "Zijbeeld",
    "Split cell horizontally": "Cel horizontaal splitsen",
    "Split cell vertically": "Cel verticaal splitsen",
    "Table toolbar": "Tabel werkbalk",
    "Text alternative": "Tekst alternatief",
    "The URL must not be empty.": "De URL mag niet leeg zijn.",
    "This link has no URL": "Deze link heeft geen URL.",
    "This media URL is not supported.": "Deze media-URL wordt niet ondersteund.",
    "Tip: Paste the URL into the content to embed faster.":
      "Tip: plak de URL in de inhoud om sneller in te sluiten.",
    "Toggle caption off": "Ondertiteling uitschakelen",
    "Toggle caption on": "Onderschrift aanzetten",
    Turquoise: "Turkoois",
    Undo: "Ongedaan maken",
    Unlink: "Ontkoppelen",
    "Upload failed": "Upload mislukt",
    "Upload in progress": "Bezig met uploaden",
    White: "Wit",
    "Widget toolbar": "Widget-werkbalk",
    "Wrap text": "Tekstterugloop",
    Yellow: "Geel",
  },
};
