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
/*!*********************************************************************!*\
  !*** ../demo1/src/js/pages/features/forms/widgets/form-repeater.js ***!
  \*********************************************************************/
/* provided dependency */ var $ = __webpack_require__(/*! jquery */ "jquery");
/* provided dependency */ var jQuery = __webpack_require__(/*! jquery */ "jquery");
// Class definition
var KTFormRepeater = function() {

    // Private functions
    var demo1 = function() {
        $('#kt_repeater_1').repeater({
            initEmpty: false,
           
            defaultValues: {
                'text-input': 'foo'
            },
             
            show: function () {
                $(this).slideDown();
            },

            hide: function (deleteElement) {                
                $(this).slideUp(deleteElement);                 
            }   
        });
    }

    var demo2 = function() {
        $('#kt_repeater_2').repeater({
            initEmpty: false,
           
            defaultValues: {
                'text-input': 'foo'
            },
             
            show: function() {
                $(this).slideDown();                               
            },

            hide: function(deleteElement) {                 
                if(confirm('Are you sure you want to delete this element?')) {
                    $(this).slideUp(deleteElement);
                }                                
            }      
        });
    }


    var demo3 = function() {
        $('#kt_repeater_3').repeater({
            initEmpty: false,
           
            defaultValues: {
                'text-input': 'foo'
            },
             
            show: function() {
                $(this).slideDown();                               
            },

            hide: function(deleteElement) {                 
                if(confirm('Are you sure you want to delete this element?')) {
                    $(this).slideUp(deleteElement);
                }                                  
            }      
        });
    }

    var demo4 = function() {
        $('#kt_repeater_4').repeater({
            initEmpty: false,
           
            defaultValues: {
                'text-input': 'foo'
            },
             
            show: function() {
                $(this).slideDown();                               
            },

            hide: function(deleteElement) {              
                $(this).slideUp(deleteElement);                                               
            }      
        });
    }

    var demo5 = function() {
        $('#kt_repeater_5').repeater({
            initEmpty: false,
           
            defaultValues: {
                'text-input': 'foo'
            },
             
            show: function() {
                $(this).slideDown();                               
            },

            hide: function(deleteElement) {              
                $(this).slideUp(deleteElement);                                               
            }      
        });
    }

    var demo6 = function() {
        $('#kt_repeater_6').repeater({
            initEmpty: false,
           
            defaultValues: {
                'text-input': 'foo'
            },
             
            show: function() {
                $(this).slideDown();                               
            },

            hide: function(deleteElement) {                  
                $(this).slideUp(deleteElement);                                                
            }      
        });
    }
    return {
        // public functions
        init: function() {
            demo1();
            demo2();
            demo3();
            demo4();
            demo5();
            demo6();
        }
    };
}();

jQuery(document).ready(function() {
    KTFormRepeater.init();
});

    
})();

/******/ })()
;
//# sourceMappingURL=form-repeater.js.map