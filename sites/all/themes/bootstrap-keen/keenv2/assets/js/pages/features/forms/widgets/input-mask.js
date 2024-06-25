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
/*!******************************************************************!*\
  !*** ../demo1/src/js/pages/features/forms/widgets/input-mask.js ***!
  \******************************************************************/
/* provided dependency */ var $ = __webpack_require__(/*! jquery */ "jquery");
/* provided dependency */ var jQuery = __webpack_require__(/*! jquery */ "jquery");
// Class definition

var KTInputmask = function () {
    
    // Private functions
    var demos = function () {
        // date format
        $("#kt_inputmask_1").inputmask("99/99/9999", {
            "placeholder": "mm/dd/yyyy",
            autoUnmask: true
        });

        // custom placeholder        
        $("#kt_inputmask_2").inputmask("99/99/9999", {
            "placeholder": "mm/dd/yyyy",
        });
        
        // phone number format
        $("#kt_inputmask_3").inputmask("mask", {
            "mask": "(999) 999-9999"
        }); 

        // empty placeholder
        $("#kt_inputmask_4").inputmask({
            "mask": "99-9999999",
            placeholder: "" // remove underscores from the input mask
        });

        // repeating mask
        $("#kt_inputmask_5").inputmask({
            "mask": "9",
            "repeat": 10,
            "greedy": false
        }); // ~ mask "9" or mask "99" or ... mask "9999999999"
        
        // decimal format
        $("#kt_inputmask_6").inputmask('decimal', {
            rightAlignNumerics: false
        }); 
        
        // currency format
        $("#kt_inputmask_7").inputmask('€ 999.999.999,99', {
            numericInput: true
        }); //123456  =>  € ___.__1.234,56

        //ip address
        $("#kt_inputmask_8").inputmask({
            "mask": "999.999.999.999"
        });  

        //email address
        $("#kt_inputmask_9").inputmask({
            mask: "*{1,20}[.*{1,20}][.*{1,20}][.*{1,20}]@*{1,20}[.*{2,6}][.*{1,2}]",
            greedy: false,
            onBeforePaste: function (pastedValue, opts) {
                pastedValue = pastedValue.toLowerCase();
                return pastedValue.replace("mailto:", "");
            },
            definitions: {
                '*': {
                    validator: "[0-9A-Za-z!#$%&'*+/=?^_`{|}~\-]",
                    cardinality: 1,
                    casing: "lower"
                }
            }
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
    KTInputmask.init();
});
})();

/******/ })()
;
//# sourceMappingURL=input-mask.js.map