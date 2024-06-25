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
    if(typeof $.fn.datepicker.dates == "undefined") {
      return;
    }
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
    moment.updateLocale("en", { invalidDate: "Please input a date" });
    moment.updateLocale("fr", { invalidDate: "Veuillez saisir une date" });
}
