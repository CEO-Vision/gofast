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
  !*** ../demo1/src/js/pages/features/miscellaneous/sweetalert2.js ***!
  \*******************************************************************/
/* provided dependency */ var $ = __webpack_require__(/*! jquery */ "jquery");
/* provided dependency */ var jQuery = __webpack_require__(/*! jquery */ "jquery");


// Class definition
var KTSweetAlert2Demo = function () {
	var _init = function () {
		// Sweetalert Demo 1
		$('#kt_sweetalert_demo_1').click(function (e) {
			Swal.fire('Good job!');
		});

		// Sweetalert Demo 2
		$('#kt_sweetalert_demo_2').click(function (e) {
			Swal.fire("Here's the title!", "...and here's the text!");
		});

		// Sweetalert Demo 3
		$('#kt_sweetalert_demo_3_1').click(function (e) {
			Swal.fire("Good job!", "You clicked the button!", "warning");
		});

		$('#kt_sweetalert_demo_3_2').click(function (e) {
			Swal.fire("Good job!", "You clicked the button!", "error");
		});

		$('#kt_sweetalert_demo_3_3').click(function (e) {
			Swal.fire("Good job!", "You clicked the button!", "success");
		});

		$('#kt_sweetalert_demo_3_4').click(function (e) {
			Swal.fire("Good job!", "You clicked the button!", "info");
		});

		$('#kt_sweetalert_demo_3_5').click(function (e) {
			Swal.fire("Good job!", "You clicked the button!", "question");
		});

		// Sweetalert Demo 4
		$("#kt_sweetalert_demo_4").click(function (e) {
			Swal.fire({
				title: "Good job!",
				text: "You clicked the button!",
				icon: "success",
				buttonsStyling: false,
				confirmButtonText: "Confirm me!",
				customClass: {
					confirmButton: "btn btn-primary"
				}
			});
		});

		// Sweetalert Demo 5
		$("#kt_sweetalert_demo_5").click(function (e) {
			Swal.fire({
				title: "Good job!",
				text: "You clicked the button!",
				icon: "success",
				buttonsStyling: false,
				confirmButtonText: "<i class='la la-headphones'></i> I am game!",
				showCancelButton: true,
				cancelButtonText: "<i class='la la-thumbs-down'></i> No, thanks",
				customClass: {
					confirmButton: "btn btn-danger",
					cancelButton: "btn btn-default"
				}
			});
		});

		$('#kt_sweetalert_demo_6').click(function (e) {
			Swal.fire({
				position: 'top-right',
				icon: 'success',
				title: 'Your work has been saved',
				showConfirmButton: false,
				timer: 1500
			});
		});

		$('#kt_sweetalert_demo_7').click(function (e) {
			Swal.fire({
				title: 'jQuery HTML example',
				showClass: {
			    	popup: 'animate__animated animate__wobble'
			  	},
			  	hideClass: {
			    	popup: 'animate__animated animate__swing'
			  	}
		  	});
		});

		$('#kt_sweetalert_demo_8').click(function (e) {
			Swal.fire({
				title: 'Are you sure?',
				text: "You won't be able to revert this!",
				icon: 'warning',
				showCancelButton: true,
				confirmButtonText: 'Yes, delete it!'
			}).then(function (result) {
				if (result.value) {
					Swal.fire(
						'Deleted!',
						'Your file has been deleted.',
						'success'
					)
				}
			});
		});

		$('#kt_sweetalert_demo_9').click(function (e) {
			Swal.fire({
				title: 'Are you sure?',
				text: "You won't be able to revert this!",
				icon: 'warning',
				showCancelButton: true,
				confirmButtonText: 'Yes, delete it!',
				cancelButtonText: 'No, cancel!',
				reverseButtons: true
			}).then(function (result) {
				if (result.value) {
					Swal.fire(
						'Deleted!',
						'Your file has been deleted.',
						'success'
					)
					// result.dismiss can be 'cancel', 'overlay',
					// 'close', and 'timer'
				} else if (result.dismiss === 'cancel') {
					Swal.fire(
						'Cancelled',
						'Your imaginary file is safe :)',
						'error'
					)
				}
			});
		});

		$('#kt_sweetalert_demo_10').click(function (e) {
			Swal.fire({
				title: 'Sweet!',
				text: 'Modal with a custom image.',
				imageUrl: 'https://unsplash.it/400/200',
				imageWidth: 400,
				imageHeight: 200,
				imageAlt: 'Custom image',
				animation: false
			});
		});

		$('#kt_sweetalert_demo_11').click(function (e) {
			Swal.fire({
				title: 'Auto close alert!',
				text: 'I will close in 5 seconds.',
				timer: 5000,
				onOpen: function () {
					Swal.showLoading()
				}
			}).then(function (result) {
				if (result.dismiss === 'timer') {
					console.log('I was closed by the timer')
				}
			})
		});
	};

	return {
		// Init
		init: function () {
			_init();
		},
	};
}();

// Class Initialization
jQuery(document).ready(function () {
	KTSweetAlert2Demo.init();
});

})();

/******/ })()
;
//# sourceMappingURL=sweetalert2.js.map