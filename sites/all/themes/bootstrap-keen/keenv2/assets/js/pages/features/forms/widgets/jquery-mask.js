/******/ (() => { // webpackBootstrap
/******/ 	"use strict";
/******/ 	var __webpack_modules__ = ({

/***/ "jquery":
/*!*************************!*\
  !*** external "jQuery" ***!
  \*************************/
/***/ ((module) => {

module.exports = jQuery;

/***/ })

/******/ 	});
/************************************************************************/
/******/ 	// The module cache
/******/ 	var __webpack_module_cache__ = {};
/******/ 	
/******/ 	// The require function
/******/ 	function __webpack_require__(moduleId) {
/******/ 		// Check if module is in cache
/******/ 		var cachedModule = __webpack_module_cache__[moduleId];
/******/ 		if (cachedModule !== undefined) {
/******/ 			return cachedModule.exports;
/******/ 		}
/******/ 		// Create a new module (and put it into the cache)
/******/ 		var module = __webpack_module_cache__[moduleId] = {
/******/ 			// no module.id needed
/******/ 			// no module.loaded needed
/******/ 			exports: {}
/******/ 		};
/******/ 	
/******/ 		// Execute the module function
/******/ 		__webpack_modules__[moduleId](module, module.exports, __webpack_require__);
/******/ 	
/******/ 		// Return the exports of the module
/******/ 		return module.exports;
/******/ 	}
/******/ 	
/************************************************************************/
var __webpack_exports__ = {};
// This entry need to be wrapped in an IIFE because it need to be isolated against other modules in the chunk.
(() => {
/*!*******************************************************************!*\
  !*** ../demo1/src/js/pages/features/forms/widgets/jquery-mask.js ***!
  \*******************************************************************/
/* provided dependency */ var $ = __webpack_require__(/*! jquery */ "jquery");
/* provided dependency */ var jQuery = __webpack_require__(/*! jquery */ "jquery");

// Class definition

var KTMaskDemo = function () {

    // private functions
    var demos = function () {
        $('#kt_date_input').mask('00/00/0000', {
            placeholder: "dd/mm/yyyy"
        });

        $('#kt_time_input').mask('00:00:00', {
            placeholder: "hh:mm:ss"
        });

        $('#kt_date_time_input').mask('00/00/0000 00:00:00', {
            placeholder: "dd/mm/yyyy hh:mm:ss"
        });

        $('#kt_cep_input').mask('00000-000', {
            placeholder: "99999-999"
        });

        $('#kt_phone_input').mask('0000-0000', {
            placeholder: "9999-9999"
        });

        $('#kt_phone_with_ddd_input').mask('(00) 0000-0000', {
            placeholder: "(99) 9999-9999"
        });

        $('#kt_cpf_input').mask('000.000.000-00', {
            reverse: true
        });

        $('#kt_cnpj_input').mask('00.000.000/0000-00', {
            reverse: true
        });

        $('#kt_money_input').mask('000.000.000.000.000,00', {
            reverse: true
        });

        $('#kt_money2_input').mask("#.##0,00", {
            reverse: true
        });

        $('#kt_percent_input').mask('##0,00%', {
            reverse: true
        });

        $('#kt_clear_if_not_match_input').mask("00/00/0000", {
            clearIfNotMatch: true
        });
    }

    return {
        // public functions
        init: function() {
            demos();
        }
    };
}();

jQuery(document).ready(function() {
    KTMaskDemo.init();
});

})();

/******/ })()
;
//# sourceMappingURL=jquery-mask.js.map