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
/*!***********************************************************************!*\
  !*** ../demo1/src/js/pages/features/miscellaneous/session-timeout.js ***!
  \***********************************************************************/
/* provided dependency */ var $ = __webpack_require__(/*! jquery */ "jquery");
/* provided dependency */ var jQuery = __webpack_require__(/*! jquery */ "jquery");


var KTSessionTimeoutDemo = function () {
    var initDemo = function () {
        $.sessionTimeout({
            title: 'Session Timeout Notification',
            message: 'Your session is about to expire.',
            keepAliveUrl: HOST_URL + '/api/session-timeout/keepalive.php',
            redirUrl: '?p=page_user_lock_1',
            logoutUrl: '?p=page_user_login_1',
            warnAfter: 5000, //warn after 5 seconds
            redirAfter: 15000, //redirect after 15 secons,
            ignoreUserActivity: true,
            countdownMessage: 'Redirecting in {timer} seconds.',
            countdownBar: true
        });
    }

    return {
        //main function to initiate the module
        init: function () {
            initDemo();
        }
    };
}();

jQuery(document).ready(function() {
    KTSessionTimeoutDemo.init();
});

})();

/******/ })()
;
//# sourceMappingURL=session-timeout.js.map