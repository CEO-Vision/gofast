/******/ (() => { // webpackBootstrap
/******/ 	var __webpack_modules__ = ({

/***/ "jquery":
/*!*************************!*\
  !*** external "jQuery" ***!
  \*************************/
/***/ ((module) => {

"use strict";
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
/*!************************************************************************!*\
  !*** ../demo1/src/js/pages/features/forms/widgets/google-recaptcha.js ***!
  \************************************************************************/
/* provided dependency */ var jQuery = __webpack_require__(/*! jquery */ "jquery");
// Class definition

var KTRecaptcha = function () {
    
    // Private functions
    var demos = function () {
        // minimum setup
        //$('#kt_timepicker_1, #kt_timepicker_1_modal').timepicker();
    }

    return {
        // public functions
        init: function() {
            demos(); 
        }
    };
}();

jQuery(document).ready(function() {
    KTRecaptcha.init();
});
})();

/******/ })()
;
//# sourceMappingURL=google-recaptcha.js.map