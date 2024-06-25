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
/*!*******************************************************!*\
  !*** ../demo1/src/js/pages/features/base/dropdown.js ***!
  \*******************************************************/
/* provided dependency */ var $ = __webpack_require__(/*! jquery */ "jquery");
/* provided dependency */ var jQuery = __webpack_require__(/*! jquery */ "jquery");


// Class definition

var KTDropdownDemo = function () {
    
    // Private functions

    // basic demo
    var demo1 = function () {
        var output = $('#kt_dropdown_api_output');
        var dropdown1 = new KTDropdown('kt_dropdown_api_1');
        var dropdown2 = new KTDropdown('kt_dropdown_api_2');

        dropdown1.on('afterShow', function(dropdown) {
            output.append('<p>Dropdown 1: afterShow event fired</p>');
        });
        dropdown1.on('beforeShow', function(dropdown) {
            output.append('<p>Dropdown 1: beforeShow event fired</p>');
        });
        dropdown1.on('afterHide', function(dropdown) {
            output.append('<p>Dropdown 1: afterHide event fired</p>');
        });
        dropdown1.on('beforeHide', function(dropdown) {
            output.append('<p>Dropdown 1: beforeHide event fired</p>');
        });
    
        dropdown2.on('afterShow', function(dropdown) {
            output.append('<p>Dropdown 2: afterShow event fired</p>');
        });
        dropdown2.on('beforeShow', function(dropdown) {
            output.append('<p>Dropdown 2: beforeShow event fired</p>');
        });
        dropdown2.on('afterHide', function(dropdown) {
            output.append('<p>Dropdown 2: afterHide event fired</p>');
        });
        dropdown2.on('beforeHide', function(dropdown) {
            output.append('<p>Dropdown 2: beforeHide event fired</p>');
        });    
    }

    return {
        // public functions
        init: function() {
            demo1();
        }
    };
}();

jQuery(document).ready(function() {    
    KTDropdownDemo.init();
});
})();

/******/ })()
;
//# sourceMappingURL=dropdown.js.map