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
/*!***********************************************************************!*\
  !*** ../demo1/src/js/pages/features/forms/validation/form-widgets.js ***!
  \***********************************************************************/
/* provided dependency */ var $ = __webpack_require__(/*! jquery */ "jquery");
/* provided dependency */ var jQuery = __webpack_require__(/*! jquery */ "jquery");
// Class definition

var KTFormWidgetsValidation = function () {
    // Private functions
    var validator;

    var _initWidgets = function() {
        // Initialize Plugins
        // Datepicker
        $('#kt_datepicker').datepicker({
            todayHighlight: true,
            templates: {
                leftArrow: '<i class=\"la la-angle-left\"></i>',
                rightArrow: '<i class=\"la la-angle-right\"></i>'
            }
        }).on('changeDate', function(e) {
            // Revalidate field
            validator.revalidateField('date');
        });

        // Datetimepicker
        $('#kt_datetimepicker').datetimepicker({
            pickerPosition: 'bottom-left',
            todayHighlight: true,
            autoclose: true,
            format: 'yyyy.mm.dd hh:ii'
        });

        $('#kt_datetimepicker').change(function() {
            // Revalidate field
            validator.revalidateField('datetime');
        });

        // Timepicker
        $('#kt_timepicker').timepicker({
            minuteStep: 1,
            showSeconds: true,
            showMeridian: true
        });

        $('#kt_timepicker').change(function() {
            // Revalidate field
            validator.revalidateField('time');
        });

        // Daterangepicker
        $('#kt_daterangepicker').daterangepicker({
            buttonClasses: ' btn',
            applyClass: 'btn-primary',
            cancelClass: 'btn-light-primary'
        }, function(start, end, label) {
            var input = $('#kt_daterangepicker').find('.form-control');
            input.val( start.format('YYYY/MM/DD') + ' / ' + end.format('YYYY/MM/DD'));

            // Revalidate field
            validator.revalidateField('daterangepicker');
        });

        // Bootstrap Switch
        $('[data-switch=true]').bootstrapSwitch();
        $('[data-switch=true]').on('switchChange.bootstrapSwitch', function() {
            // Revalidate field
            validator.revalidateField('switch');
        });

        // Bootstrap Select
        $('#kt_bootstrap_select').selectpicker();
        $('#kt_bootstrap_select').on('changed.bs.select', function() {
            // Revalidate field
            validator.revalidateField('select');
        });

        // Select2
        $('#kt_select2').select2({
            placeholder: "Select a state",
        });

        $('#kt_select2').on('change', function(){
            // Revalidate field
            validator.revalidateField('select2');
        });

        // Typeahead
        var countries = new Bloodhound({
            datumTokenizer: Bloodhound.tokenizers.whitespace,
            queryTokenizer: Bloodhound.tokenizers.whitespace,
            prefetch: HOST_URL + '/api/?file=typeahead/countries.json'
        });

        $('#kt_typeahead').typeahead(null, {
            name: 'countries',
            source: countries
        });

        $('#kt_typeahead').bind('typeahead:select', function(ev, suggestion) {
            // Revalidate field
            validator.revalidateField('typeahead');
        });
    }

    var _initValidation = function () {
        // Validation Rules
        validator = FormValidation.formValidation(
            document.getElementById('kt_form'),
            {
                fields: {
                    date: {
                        validators: {
                            notEmpty: {
                                message: 'Date is required'
                            }
                        }
                    },
                    daterangepicker: {
                        validators: {
                            notEmpty: {
                                message: 'Daterange is required'
                            }
                        }
                    },
                    datetime: {
                        validators: {
                            notEmpty: {
                                message: 'Datetime is required'
                            }
                        }
                    },
                    time: {
                        validators: {
                            notEmpty: {
                                message: 'Time is required'
                            }
                        }
                    },
                    select: {
                        validators: {
                            notEmpty: {
                                message: 'Select is required'
                            }
                        }
                    },
                    select2: {
                        validators: {
                            notEmpty: {
                                message: 'Select2 is required'
                            }
                        }
                    },
                    typeahead: {
                        validators: {
                            notEmpty: {
                                message: 'Typeahead is required'
                            }
                        }
                    },
                    switch: {
                        validators: {
                            notEmpty: {
                                message: 'Typeahead is required'
                            }
                        }
                    },
                    markdown: {
                        validators: {
                            notEmpty: {
                                message: 'Typeahead is required'
                            }
                        }
                    },
                },

                plugins: {
                    trigger: new FormValidation.plugins.Trigger(),
					// Validate fields when clicking the Submit button
					submitButton: new FormValidation.plugins.SubmitButton(),
            		// Submit the form when all fields are valid
            		defaultSubmit: new FormValidation.plugins.DefaultSubmit(),
                    // Bootstrap Framework Integration
                    bootstrap: new FormValidation.plugins.Bootstrap({
                        eleInvalidClass: '',
                        eleValidClass: '',
                    })
                }
            }
        );
    }

    return {
        // public functions
        init: function() {
            _initWidgets();
            _initValidation();
        }
    };
}();

jQuery(document).ready(function() {
    KTFormWidgetsValidation.init();
});

})();

/******/ })()
;
//# sourceMappingURL=form-widgets.js.map