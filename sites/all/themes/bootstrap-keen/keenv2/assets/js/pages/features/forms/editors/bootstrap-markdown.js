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
/******/ 		if(__webpack_module_cache__[moduleId]) {
/******/ 			return __webpack_module_cache__[moduleId].exports;
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
(() => {
/*!**************************************************************************!*\
  !*** ../demo1/src/js/pages/features/forms/editors/bootstrap-markdown.js ***!
  \**************************************************************************/
/* provided dependency */ var jQuery = __webpack_require__(/*! jquery */ "jquery");

// Class definition

var KTBootstrapMarkdown = function () {    
    // Private functions
    var demos = function () {
        
    }

    return {
        // public functions
        init: function() {
            demos(); 
        }
    };
}();

// Initialization
jQuery(document).ready(function() {
    KTBootstrapMarkdown.init();
});
})();

/******/ })()
;
//# sourceMappingURL=bootstrap-markdown.js.map