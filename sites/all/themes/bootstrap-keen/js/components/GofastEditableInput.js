// user-defined locale, then navigator language, then english
window.GofastLocale = Drupal.settings.gofast.language || navigator.language || "en";

window.GofastDrupalDateConversionTables = {
    // for the datepicker
    bootstrapDate: {
        d: "dd",
        m: "mm",
        Y: "yyyy",
        H: "hh",
        i: "mm",
    },
    // for the datetimepicker
    bootstrap: {
        d: "DD",
        m: "MM",
        Y: "YYYY",
        H: "HH",
        i: "mm",
        g: "h",
    },
    moment: {
        D: "ddd",
        F: "MMMM",
        Y: "YYYY",
        d: "DD",
        m: "MM",
        H: "HH",
        i: "mm",
        l: "dddd",
        j: "Do",
    },
};

/**
 * @desc helper to convert a Drupal date_format pattern into another date pattern
 * @param {string} patternType: in case we need to convert to different date patterns
 * @param {string} pattern: works with short, medium and long Drupal date_format pattern
 * @param {boolean} isDate: if set to true, the function will return a date pattern without time
 * @return {string}
 */
window.GofastConvertDrupalDatePattern = (patternType = "moment", pattern = Drupal.settings.date_format_short, isDate = true) => {
    const patternConversionTable = GofastDrupalDateConversionTables[patternType];
    for (const patternKey in patternConversionTable) {
        pattern = pattern.replace(patternKey, patternConversionTable[patternKey]);
    }
    return isDate ? pattern.split(" -")[0] : pattern;
}

/**
 * @desc helper to convert a datetime into a Drupal date_format pattern
 * @param {datetime|string} datetime: works with a timestamp, a SQL datetime or a JS Date object
 * @return {string} a formatted localized datetime string
 */
window.GofastFormatAsDrupalDate = (datetime, pattern = Drupal.settings.date_format_short, isDate = true) => {
    const convertibleDate = new Date(datetime);
    pattern = window.GofastConvertDrupalDatePattern("moment", pattern, isDate);
    // using moment.js not to reinvent the wheel
    moment.locale(GofastLocale);
    return moment(convertibleDate).format(pattern);
}

window.GofastWidgetsCallbacks = {
    datePickerCallback(date) {
        if (date > new Date()) {
            return { classes : "font-weight-bold text-dark" };
        }
        return true;
    },
    dateTimePickerCallback() {
        const momentPattern = GofastConvertDrupalDatePattern();
        const currentDate = new Date();
        // datetimepicker marks days before current *week* as old days, we want to mark days before current *day* as old days in order to apply related CSS
        $(".datepicker-days td:not(.old)").each(function (index, elem) {
          const cellDate = moment($(elem).attr("data-day"), momentPattern);
          if (cellDate < currentDate) {
            $(elem).addClass("old-month-day");
          }
        });
    }
};

window.GofastEditableInput = (element, initialData, type, props = {}) => {
    // this is an abstract blueprint for the various input types
    var _editableInput = {
        data: null,
        wishlist: null,
        DOM: {
          element: null,
          input: null,
          customInput: null,
          inputContent: null,
          valueContent: null,
          loader: null,
          setInputWidth: function() {
            if(typeof props.widenInput != "undefined" && props.widenInput == true) {
                customIn.DOM.input.style.maxWidth = "100%";
                customIn.DOM.input.style.width = "100%";
                return;
            }
            // default case: input size adapts to value size
            if(customIn.DOM.input.value.length < 15) {
                customIn.DOM.input.style.width = "15ch";
            } else {
                customIn.DOM.input.style.width = customIn.DOM.input.value.length + "ch";
            }
          },
          setInputFontSize: function() {
            if(typeof props.fontSize != "undefined") {
                customIn.DOM.input.style.fontSize = props.fontSize;
            }
          },
          setTextAreaHeight: function() {
            if(props.useTextarea){
                if(customIn.DOM.input.scrollHeight >= customIn.DOM.input.offsetHeight){
                    customIn.DOM.input.style.height = (customIn.DOM.input.scrollHeight + 4) + "px";
                }
            }
          }
        },
        isEditable: true,
        isLoading: false,
        templates: {
          input: function(){
            return "<input type=\"text\" class=\"input-control form-control\" />";
          },
          value: function(data){
            if(data){
              return  "<div>" + data + "</div>";
            }
            return '<div class="text-muted">' + (props.placeholder ? Drupal.t(props.placeholder) : Drupal.t('Empty value')) + '</div>';
          },
        },
        getData: () => false,
        setData: function(data){
            if(data !== this.data){
                this.data = data
                this.setValueContent(data)
            }
        },
        setLoading: function(isLoading){
          isLoading ?
            this.DOM.loader.classList.add("loading") :
            this.DOM.loader.classList.remove("loading")
        },
        setValueContent: function(data){
          if(this.DOM.valueContent) {
            this.DOM.valueContent.innerHTML = this.templates.value(data)

            let popupItems = this.DOM.valueContent.querySelectorAll('[data-toggle="popover"]')

            if(popupItems && popupItems.length > 0){
                popupItems.forEach(item => {
                    item.onclick = (e) => {
                        e.stopPropagation()
                    }
                    $(item).popover({
                        template: "<div class=\"popover GofastKanbanPopover\" role=\"tooltip\"> <div class=\"arrow\"></div> <div class=\"popover-body\"></div></div>"
                    })
                })
            }
          }
        },
        saveData: async function(data){
            this.setLoading(true)
            try {
              const res = this.save(data)
              this.setData(data)

            } catch(error) {
                console.log(error.message)
            }

            this.setLoading(false)

        },
        save: function(){return true},
        events: {
          onclickValue: function(e, the){
            // if we don't want the input to be toggled on click, but on our own trigger
            if(typeof props.programmaticTrigger != "undefined" && props.programmaticTrigger == true){
                // we do nothing if our trigger is not found
                if(!e.data || !e.data.programmaticTriggered) {
                    return;
                }
            }
            if(e.target.nodeName != "A"){
              the.events.toogleInput(the, true)
              if(the.customDisplayHandler) the.customDisplayHandler()
            } else {
                e.stopPropagation()
            }
          },
          toogleInput: function(the, isEditing){
            if(isEditing) {
              
              // Decode the data
              the.data = Gofast.htmlDecode(the.data)
              
              // abort poll
              Gofast.incrementMetadataEditCounter();
              the.DOM.element.removeChild(the.DOM.valueContent)
              the.DOM.element.appendChild(the.DOM.inputContent)

              if(the.events.showInputCustom){
                the.events.showInputCustom()    
                if(typeof props.showConfirmationButtons != "undefined" && props.showConfirmationButtons) {
                    // showConfirmationButtons may be a boolean or a selector which targets the confirmation buttons container
                    customIn.hooksHelpers.renderConfirmationButtons(true, props.showConfirmationButtons);
                }
              }

            } else {
              // run poll if no other fields are being edited
              Gofast.decrementMetadataEditCounter();
              if(the.events.hideInputCustom){
                the.events.hideInputCustom()
              }
              var index = Array.prototype.indexOf.call(the.DOM.element.children, the.DOM.inputContent);
              if(index > -1) the.DOM.element.removeChild(the.DOM.inputContent)
              the.DOM.element.appendChild(the.DOM.valueContent)

            }
          },
          showInputCustom: null,
          hideInputCustom: null,
        },
        hooksHelpers: {
            hasPendingConfirmation: false,
            promises: {},
            // tool to render confirmation buttons
            renderConfirmationButtons(textInput = false, selector = false){
                // If another editable input is open with confirmation buttons, cancel them
                if ($(".editableInputConfirmationButtons").length) {
                    $(".editable-input-cancel-button").trigger("mousedown")
                }
                const $confirmButton = $("<button class=\"btn btn-icon btn-sm editable-input-confirm-button\"><i class=\"fas fa-check text-success\"></i></button>");
                const $cancelButton = $("<button class=\"btn btn-icon btn-sm editable-input-cancel-button\"><i class=\"fas fa-times text-danger\"></i></button>");
                if (textInput) {
                    const $buttons = $("<span class=\"editableInputConfirmationButtons d-flex justify-content-center\"></span>").append($confirmButton, $cancelButton);
                    const buttonsContainerInterval = setInterval(function() {
                        let $buttonsContainer = [];
                        if (selector === true || selector === false) {
                            $buttonsContainer = $(".EditableInput__input").parent().parent();
                        } else {
                            $buttonsContainer = $(selector);
                        }
                        if (!$buttonsContainer.length) {
                            return;
                        }
                        $buttons.insertAfter($buttonsContainer);
                        $buttons.parent().addClass("hasConfirmationButtons");
                        $confirmButton.on("mousedown", (e) => {
                            customIn.saveData(customIn.getData() || customIn.DOM.input.value);
                            $(".editableInputConfirmationButtons").remove();
                            customIn.events.toogleInput(customIn, false);
                            window.dispatchEvent(new Event("tagifyHookConfirm"));
                        });
                        $cancelButton.on("mousedown", (e) => {
                            // in a text input, buttons are displayed before any save event or promise callback has been triggered
                            $(".editableInputConfirmationButtons").remove();
                            customIn.preventSave = true;
                            customIn.events.toogleInput(customIn, false);
                            window.dispatchEvent(new Event("tagifyHookCancel"));
                        });
                        clearInterval(buttonsContainerInterval);
                    }, 100);
                } else {
                    const $buttonsContainer = $("<span class=\"editableInputConfirmationButtons d-flex align-items-center justify-content-center\" style=\"margin-left: auto; margin-block: auto;\"></span>");
                    $buttonsContainer.append($confirmButton).append($cancelButton);
                    $buttonsContainer.insertAfter($(customIn.DOM.inputContent));
                    $confirmButton.on("mousedown", (e) => window.dispatchEvent(new Event("tagifyHookConfirm")));
                    $cancelButton.on("mousedown", (e) => window.dispatchEvent(new Event("tagifyHookCancel")));
                }
            },
            // promise to render confirm buttons from a hook
            confirmationHookPromise(params = false) {
                // if the input is not a vanilla editable input, confirmation buttons are not rendered upfront
                if (params.target || Array.isArray(params)) {
                    customIn.hooksHelpers.renderConfirmationButtons();
                }
                $(".tagify__dropdown").remove();
                // cleanup previous confirmation promise
                window.dispatchEvent(new Event("tagifyHookClean"));
                customIn.hooksHelpers.hasPendingConfirmation = true;
                customIn.hooksHelpers.promises.confirmationPromise = new Promise((resolve, reject) => {
                    const cleanPromiseListeners = () => {
                        window.removeEventListener("tagifyHookConfirm", resolveCallback);
                        window.removeEventListener("tagifyHookCancel", rejectCallback);
                        window.removeEventListener("tagifyHookClean", cleanCallback);
                    };
                    const resolveCallback = (e) => {
                        // avoid overcrowding listeners
                        cleanPromiseListeners();
                        $("#editableInputPendingConfirmationLabel").remove();
                        $(".editableInputConfirmationButtons").remove();
                        $(".EditableInput__loader").hide();
                        customIn.hooksHelpers.hasPendingConfirmation = false;
                        sessionStorage.clear();
                        resolve(params);
                    };
                    const rejectCallback = (e) => {
                        //Replace the content of the textbox with the current data to reset it when the edit is cancelled
                        if(customIn.DOM.customInput){
                            customIn.DOM.customInput.setData(customIn.data)
                        } else {
                            customIn.DOM.input.value = customIn.data;
                        }
                        // avoid overcrowding listeners
                        cleanPromiseListeners();
                        $("#editableInputPendingConfirmationLabel").remove();
                        $(".editableInputConfirmationButtons").remove();
                        $(".EditableInput__loader").hide();
                        customIn.hooksHelpers.hasPendingConfirmation = false;
                        sessionStorage.clear();
                        reject(params);
                    };
                    const cleanCallback = (e) => {
                        cleanPromiseListeners();
                        reject(params);
                    }
                    window.addEventListener("tagifyHookConfirm", resolveCallback);
                    window.addEventListener("tagifyHookCancel", rejectCallback);
                    window.addEventListener("tagifyHookClean", cleanCallback);
                });
                return customIn.hooksHelpers.promises.confirmationPromise;
            },
            // set events for draft mode in tagify input
            setTagifyDraftMode(tagify) {
                tagify.on("dropdown:select remove", function() {
                    customIn.hooksHelpers.renderConfirmationButtons();
                });
                tagify.on("change", function() {
                    const tid = $(".KanbanCard__documents .KanbanCard__InputEditable").attr("data-tid");
                    sessionStorage.setItem("gofastEditableValue_" + Gofast.get("user").uid + "_" + tid, tagify.DOM.originalInput.value);
                });
                tagify.on("remove", function() {
                    // prevent blur bug occurring with FF
                    tagify.DOM.input.focus();
                });
                tagify.on("blur", function() {
                    // cleanup
                    $("#editableInputPendingConfirmationLabel").remove();
                    $(".editableInputConfirmationButtons").remove();
                    const tid = $(customIn.DOM.element).attr("data-tid");
                    if(customIn.hooksHelpers.hasPendingConfirmation) {
                        // display a label if there are unsaved changes
                        $('<div id="editableInputPendingConfirmationLabel" class="label label-xl label-light-warning label-inline font-weight-bolder d-flex m-auto" style="width: max-content;">' + Drupal.t("You have unsaved pending changes, please go back to edition mode to confirm or discard them.", {}, {context: "gofast"}) + '</div>').insertAfter($(customIn.DOM.element.parentElement));
                        // we don't want to display unsaved change if the user is not editing anymore (after blur)
                        const draftOriginalValue = sessionStorage.getItem("gofastEditableOriginalValue_" + Gofast.get("user").uid + "_" + tid);
                        customIn.setValueContent(JSON.parse(draftOriginalValue));
                        return;
                    }
                    sessionStorage.removeItem("gofastEditableValue_" + Gofast.get("user").uid + "_" + tid);
                    sessionStorage.removeItem("gofastEditableOriginalValue_" + Gofast.get("user").uid + "_" + tid);
                });
                tagify.on("focus", function() {
                    // cleanup
                    $("#editableInputPendingConfirmationLabel").remove();
                    $(".editableInputConfirmationButtons").remove();
                    const tid = $(customIn.DOM.element).attr("data-tid");
                    const draftValue = sessionStorage.getItem("gofastEditableValue_" + Gofast.get("user").uid + "_" + tid);
                    const draftOriginalValue = sessionStorage.getItem("gofastEditableOriginalValue_" + Gofast.get("user").uid + "_" + tid);
                    if (!customIn.hooksHelpers.hasPendingConfirmation && !draftValue) {
                        // keep track of unsaved changes for this card and user for the whole browsing session
                        sessionStorage.setItem("gofastEditableOriginalValue_" + Gofast.get("user").uid + "_" + tid, JSON.stringify(tagify.value));
                    }
                    if (draftValue && draftValue != draftOriginalValue) {
                        customIn.hooksHelpers.renderConfirmationButtons();
                        $('<div id="editableInputPendingConfirmationLabel" class="label label-xl label-light-warning label-inline font-weight-bolder">' + Drupal.t("You are editing previously unsaved changes.", {}, {context: "gofast"}) + '</div>').insertAfter($(customIn.DOM.element.parentElement));
                        tagify.settings.whitelist = JSON.parse(draftValue);
                        tagify.removeAllTags();
                        tagify.addTags(JSON.parse(draftValue), true);
                    }
                });
                const tid = $(customIn.DOM.element).attr("data-tid");
                const draftValueOnInit = sessionStorage.getItem("gofastEditableValue_" + Gofast.get("user").uid + "_" + tid);
                const draftOriginalValueOnInit = sessionStorage.getItem("gofastEditableOriginalValue_" + Gofast.get("user").uid + "_" + tid);
                if (draftValueOnInit && draftValueOnInit != draftOriginalValueOnInit) {
                    $('<div id="editableInputPendingConfirmationLabel" class="label label-xl label-light-warning label-inline font-weight-bolder">' + Drupal.t("You have unsaved pending changes, please go back to edition mode to confirm or discard them.", {}, {context: "gofast"}) + '</div>').insertAfter($(customIn.DOM.element.parentElement));
                }
                return tagify;
            }
        },
        hooks: {
            preSave: null,
        },
        initCustomInput: null,
        init: function(element, initialData){

            this.DOM.element = element
            this.setData(initialData)

            let valueContent = document.createElement('div')
            valueContent.classList.add("EditableInput__value")

            this.DOM.valueContent = valueContent
            this.DOM.element.appendChild(this.DOM.valueContent)

            this.setValueContent(this.data)

            if(this.isEditable){
                if(!props.programmaticTrigger){
                    this.DOM.valueContent.classList.add("editable")
                }
                this.DOM.valueContent.onclick = (e, d) => {
                    // if custom data is passed on the event, we keep it
                    if (typeof d != "undefined") {
                        e.data = d;
                    }
                    this.events.onclickValue(e, this)
                    e.stopPropagation()
                }

                let inputContent = document.createElement('div')
                inputContent.classList.add('EditableInput__input')
                this.DOM.inputContent = inputContent



                this.DOM.inputContent.innerHTML = this.templates.input()
                let input = this.DOM.inputContent.querySelector('.input-control')
                this.DOM.input = input

                let loader = document.createElement('div')
                loader.className = 'EditableInput__loader'
                loader.innerHTML = "<div class=\"spinner\"></div>";

                this.DOM.loader = loader
                this.DOM.element.appendChild(this.DOM.loader)
                if(this.initCustomInput) {
                    this.initCustomInput()
                }
                if (this.hooks.preSave != null) {
                    const saveCallback = this.save;
                    this.save = (params) => this.hooks.preSave(params).then((params) => saveCallback(params));
                }
            }

        }
    }

    // this is the copy of the blueprint we'll effectively initialize
    let customIn = {..._editableInput}

    // this is where we alter customIn according to its type before initializing it
    if(type){
        switch (type) {

            case 'text':

                customIn.save = () => new Promise(resolve => setTimeout(resolve, 1000))
                if(typeof props.showConfirmationButtons != "undefined" && props.showConfirmationButtons == true) {
                    customIn.hooks.preSave = (params) => customIn.hooksHelpers.confirmationHookPromise(params);
                }
                customIn.events.showInputCustom = () => {
                    if (customIn.DOM.input.closest(".breadcrumb-item") != null) {
                        customIn.DOM.input.closest(".breadcrumb-item").classList.add("breadcrumb-item-editable");
                    }
                    customIn.DOM.input.value = customIn.data;
                    customIn.DOM.setInputWidth();
                    customIn.DOM.setInputFontSize();
                    customIn.DOM.setTextAreaHeight();
                    customIn.DOM.input.focus();
                }
                customIn.events.hideInputCustom = () => {
                    if (customIn.DOM.input.closest(".breadcrumb-item") != null) {
                        customIn.DOM.input.closest(".breadcrumb-item").classList.remove("breadcrumb-item-editable");
                    }
                }

                customIn.initCustomInput = () => {
                    // add custom properties
                    if (customIn.pattern) {
                        customIn.DOM.input.setAttribute("pattern", customIn.pattern);
                    }

                    const inputFontSize = getComputedStyle(customIn.DOM.element).fontSize;
                    if (inputFontSize) {
                        props.fontSize = inputFontSize;
                    }

                    customIn.DOM.input.onblur = (e) => {
                        if(typeof props.showConfirmationButtons != "undefined" && props.showConfirmationButtons) {
                            e.preventDefault();
                            return;
                        }
                        customIn.events.toogleInput(customIn, false)
                    }
                    customIn.DOM.input.onchange = (e) => {
                        if(!customIn.preventSave){
                            customIn.saveData(e.target.value);
                        }
                        delete(customIn.preventSave);
                    }
                    customIn.DOM.input.onkeydown = (e) => {
                        // if widenInput is not set, we'll use the default behaviour in which we adapt the input width to the content
                        if(typeof props.widenInput == "undefined") {
                            customIn.DOM.setInputWidth();
                        }
                        // Put a setTimeout to resize after the text is added
                        setTimeout(() => {
                            customIn.DOM.setTextAreaHeight();
                        }, 0)
                        let hasConfirmationButtons = false;
                        if(typeof props.showConfirmationButtons != "undefined" && props.showConfirmationButtons == true) {
                            hasConfirmationButtons = true;
                        }
                        // if user presses Enter
                        if (e.keyCode === 13 && !props.useTextarea) {
                            customIn.saveData(customIn.getData() || customIn.DOM.input.value);
                            customIn.preventSave = true;
                            customIn.events.toogleInput(customIn, false)
                        }
                        if (e.keyCode === 13 && hasConfirmationButtons && !props.useTextarea) {
                            window.dispatchEvent(new Event("tagifyHookConfirm"));
                        }
                        // if user presses Esc
                        if (e.keyCode === 27) {
                            customIn.events.toogleInput(customIn, false)
                        }
                        if (e.keyCode === 27 && hasConfirmationButtons) {
                            $(".editableInputConfirmationButtons").remove();
                        }
                    }
                    customIn.DOM.input.onpaste = (e) => {
                        // Resize text area after text is pasted
                        setTimeout(() => {
                            customIn.DOM.setTextAreaHeight();
                        }, 0)
                    }
                }
                customIn.templates.input = function() {
                    // @warning line jumps are interpreted as new commands here, but not elsewhere in this script
                    if(props.useTextarea == true){
                        return '<textarea class="input-control form-control"/>';
                    } else {
                        return '<input type="text" class="input-control form-control"/>';
                    }
                }
                break;

            case 'date':
                // datepicker l18n: we have to declare l18n here juste before it gets initialized since there are other datepickers around that would overwrite this setting
                setDatepickerL18n();

                customIn.rawData = customIn.data,
                customIn.setData = function(data) {
                     if(data == null || data == 0){
                         data = null; //Math.floor(Date.now());
                         formattedData = null;
                     }else{
                        // if the date comes from the datepicker plugin, a x1000 compensation is expected
                        if (String(data).length < 12){
                            data = data * 1000;
                        }
                        formattedData = GofastFormatAsDrupalDate(data);
                    }

                    if (formattedData !== this.data) {
                        this.data = formattedData || data;
                        this.setValueContent( formattedData || data);
                        this.rawData = data;
                    }
                }

                customIn.templates.input = function() {
                    // @warning line jumps are interpreted as new commands here, but not elsewhere in this script
                    return '<div class="input-group date"><input type="text" class="input-control datetime form-control form-control-sm gofastDatepicker" data-toggle="datepicker" data-date-autoclose="true" placeholder="' + (props.placeholder ? Drupal.t(props.placeholder) : Drupal.t('Select date')) + '"/></div>';
                }

                customIn.initCustomInput = () => {
                    if(customIn.data) {
                        let currentDate = new Date(customIn.rawData);
                        let datepicker = $(customIn.DOM.input).datepicker({
                            language: window.GofastLocale,
                            locale : window.GofastLocale,
                            autoclose: true,
                            todayHighlight: true,
                            clearBtn: true,
                            format: window.GofastConvertDrupalDatePattern("bootstrapDate"),
                            beforeShowDay: GofastWidgetsCallbacks.datePickerCallback,
                        }).datepicker("setDate", currentDate);
                    }else{
                         $(customIn.DOM.input).datepicker({
                            language: window.GofastLocale,
                            locale : window.GofastLocale,
                            autoclose: true,
                            todayHighlight: true,
                            clearBtn: true,
                            beforeShowDay: GofastWidgetsCallbacks.datePickerCallback,
                            format: window.GofastConvertDrupalDatePattern("bootstrapDate")
                        });
                    }
                                   
                    $(customIn.DOM.input).on('hide', (e) => {
                        let newDate = new Date($(customIn.DOM.input).datepicker('getDate')).getTime()
                        customIn.saveData(newDate)
                        customIn.events.toogleInput(customIn, false)
                    })
                }

                customIn.events.showInputCustom = () => {
                    $(customIn.DOM.input).datepicker('show')
                }

                break;
            case 'expiration_date':
                
                customIn.rawData = customIn.data,
                customIn.setData = function(data) {
                    if(data != ""){
                        this.data = moment.unix(data).format(window.GofastConvertDrupalDatePattern("bootstrapDate").toUpperCase());
                        this.timestamp = data;
                        this.setValueContent(this.data);
                    }
                }

                customIn.templates.input = function() {
                    // @warning line jumps are interpreted as new commands here, but not elsewhere in this script
                    return '<div class="input-group date"><input type="text" class="input-control gofastProfileDatetimepickerExpirationDate form-control form-control-sm" data-toggle="datetimepicker"/></div>';
                }

                customIn.initCustomInput = () => {
                    Gofast.user.setDateTimePickerExpirationDate($(customIn.DOM.input), customIn.data);
                    
                    // When the datetimepicker is hidden, save the last selected date
                    $(customIn.DOM.input).on('hide.datetimepicker', (e) => {
                        let newDate = moment($(customIn.DOM.input).val(), window.GofastConvertDrupalDatePattern("bootstrapDate").toUpperCase()).unix()
                        customIn.saveData(newDate)
                        customIn.events.toogleInput(customIn, false)
                    })
                }
                // When the editable input is focused, show the datetimepicker
                customIn.events.showInputCustom = () => {
                    $(customIn.DOM.input).datetimepicker('show')
                }
                break;
            case 'select':

                customIn.templates.input = function(){

                    let options = []

                    if(customIn.wishlist){

                        customIn.wishlist.forEach(option => {
                            let otemp = "<option value=\"" + option.value + "\">" + option.label + "</option>";
                            options.push(otemp)
                        });
                    }

                    return "<select class=\"input-control form-control\"><option value=\"\">" + (props.placeholder ? Drupal.t(props.placeholder) : Drupal.t('Empty value')) + ("</option>" + options.join("") + "</select>");

                }

                customIn.templates.value = function(data){
                    if(data && (data.label || data.text) != null) {
                      return "<div>" + (data.label || data.text) + "</div>";
                    }
                      return "<div class=\"text-muted\" >" + (props.placeholder ? Drupal.t(props.placeholder) : Drupal.t('Empty value')) + "</div>";
                }

                customIn.events.showInputCustom = () => {

                    $(customIn.DOM.input).select2('open')

                }
                customIn.initCustomInput = () => {

                    $(customIn.DOM.input).select2({
                        minimumResultsForSearch: Infinity,
                    });

                    $(customIn.DOM.input).on('select2:close', (e) => {
                        var data = $(customIn.DOM.input).select2('data')[0]
                        customIn.saveData(data)
                        customIn.events.toogleInput(customIn, false)
                    })
                }

                break;

            case 'userselect':

                customIn.templates.value = function(data){
                    if(!data || data.uid == 0) {
                        return "<div class=\"text-muted\">" + (props.placeholder ? Drupal.t(props.placeholder) : Drupal.t('No members selected', {}, {context: "gofast"})) + "</div>";
                    }
                    return "<div class=\"select2__suggestionItem d-flex align-items-center\">" + (data.picture ? "<div class=\"suggestion__avatar symbol symbol-25 mr-4\"> <img alt=\"Gofast user avatar\" loading=\"lazy\" src=\"" + data.picture + "\"> </div>" : "") + "<div class=\"suggestion__label font-size-lg\">" + data.firstname + " " + data.lastname + "</div></div>";
                }
                customIn.templates.input = function(){
                    if (customIn.data && customIn.data.uid) {
                        return "<select class=\"input-control form-control select2 select2__users\"><option value=\"" + customIn.data.uid + "\" selected></option></select>";
                    }
                    return "<select class=\"input-control form-control select2 select2__users\"></select>";

                }
                customIn.events.showInputCustom = () => {

                    $(customIn.DOM.input).select2('open')

                }
                customIn.initCustomInput = () => {

                    $(customIn.DOM.input).select2({
                        language: GofastLocale,
                        ajax: {
                            url: function(params){
                                return window.origin + "/directory/directory_async/user?nopopup=true";
                            },
                            dataType: 'json',
                            data: function (params) {
                                return {
                                  query: {name: params.term}, // search term
                                };
                            },
                            delay: 250,
                            processResults: function (results) {
                                // data may be a sub-object along with "meta" because of server-side pagination
                                let data = Array.isArray(results) ? results : results.data;
                                let newData  = data.map(user => {
                                    user.text = user.firstname+' '+user.lastname;
                                    user.id = user.uid;
                                    return user;
                                })
                                return {
                                  results: newData
                                };
                            }
                        },
                        placeholder: Drupal.t('Search User'),
                        minimumInputLength: 3,
                        // minimumResultsForSearch: Infinity,
                        templateResult: customIn.templates.selectionItemTemplate,
                        templateSelection: customIn.templates.suggestionItemTemplate
                    });

                    // Fix data not correctly set in .select2("data") causing "undefined undefined" on blur
                    if(customIn.data != null){
                        Object.entries(customIn.data).forEach(([key, value]) => {
                            $(customIn.DOM.input).select2("data")[0][key] = value
                        })
                    }

                    $(customIn.DOM.input).on('select2:close', (e) => {
                        var data = $(customIn.DOM.input).select2('data')[0] || {uid: 0};
                        customIn.saveData(data)
                        customIn.events.toogleInput(customIn, false)
                    })
                }
                customIn.templates.selectionItemTemplate = function(user){
                    let template = "<div class=\"d-flex align-items-center\"> <div class=\" font-size-lg\">" + (props.placeholder ? Drupal.t(props.placeholder) : Drupal.t('Nobody selected', {}, {context: "gofast"})) + "</div></div>";

                    if(user){
                        template = "<div class=\"select2__suggestionItem d-flex align-items-center\">" + (user.picture ? "<div class=\"suggestion__avatar symbol symbol-25 mr-4\"> <img alt=\"Gofast user avatar\" loading=\"lazy\" src=\"" + user.picture + "\"> </div>" : "") + " <div class=\"suggestion__label font-size-lg\">" + user.text + "</div></div>";
                    }

                    return $(template)

                }
                
                customIn.templates.suggestionItemTemplate = function(data) {
                    if (!data.uid && customIn.data && customIn.data.uid && data.id != "") {
                        data = customIn.data;
                        data.text = data.firstname+' '+data.lastname;
                        data.id = data.uid;
                    }
                    let picture = data.picture ? `<div class="suggestion__avatar symbol symbol-25 mr-4"> <img alt="Gofast user avatar" loading="lazy" src="${data.picture}"></div>` : "";
                    let text = `<div class="suggestion__label font-size-lg text-truncate" id="itemTextContainer">${data.text}</div>`;
                    let removeButton = `<button class="close remove-current-selection" ><i class="fa fa-close"></i></button>`;
                    let $template = $(`<div class="select2__suggestionItem d-flex align-items-center w-100"> ${picture} ${text} &nbsp;&nbsp;${removeButton}</div>`);
                    if (!$(customIn.DOM.input).val()) {
                        $template.find(".remove-current-selection").css("display", "none");
                    }
                    $template.find(".remove-current-selection").mousedown(() => $(customIn.DOM.input).val(null).trigger("change"));
                    return $template;
                }

                break;

            case 'userstags':
                customIn.searchUrl = function(search){

                    let encodeSearch = encodeURIComponent("query[name]") + "=" + search;
                    return '/directory/directory_async/user?'+encodeSearch ;
                },
                customIn.templates.value = function(data){
                    if (data && data.length > 0) {

                        let members;
                        let othersMembers;
                        let popOverOthers;

                        if(data.length < 6){
                            members = data
                            othersMembers = 0
                        } else {
                            //TODO: members.join('') for print string array
                            members = data.slice(0,5)
                            othersMembers = data.slice(5)
                            popOverOthers = othersMembers.map(mem => {

                                return "<li class='navi-item text-truncate'><span class='navi-bullet mr-1'><i class='bullet bullet-dot'></i></span><span class='navi-text'>" + mem.firstname + " " + mem.lastname + "</span></li>";
                            })
                        }

                        let membersGroup = []
                        members.forEach(mem => {
                            let template = " <div class=\"symbol symbol-circle symbol-40\" data-toggle=\"popover\" data-trigger=\"hover\" data-placement=\"top\" data-content=\"" + mem.firstname + " " + mem.lastname + ("\"> <img alt=\"Gofast user avatar\" loading=\"lazy\" src=\"" + mem.picture + "\"> </div> ");
                            membersGroup.push(template)
                        })
                        return "<div class=\"symbol-group symbol-hover\">" + membersGroup.join("") + " " + (othersMembers.length > 0 ? " <div class=\"symbol symbol-circle symbol-35 symbol-light-primary\" data-toggle=\"popover\" data-html=\"true\" data-trigger=\"hover\" data-placement=\"top\" data-content=\"<ul class='navi'>" + popOverOthers.join("") + "</ul>\"> <span class=\"symbol-label font-weight-bolder\">+" + othersMembers.length + "</span> </div>" : "") + "</div>";
                    } else {
                        return ('<div class="text-muted">' + (props.placeholder ? Drupal.t(props.placeholder) : Drupal.t('No members selected', {}, {context: "gofast"})) + '</div>');
                    }
                }

                customIn.events.showInputCustom = () => {

                    $(customIn.DOM.customInput.DOM.input).trigger('focus');

                }

                customIn.formatData = (data) => {
                    return data.map(user => {
                                user.value = Number.parseInt(user.uid)
                                return user
                            });

                },
                customIn.initCustomInput = () => {
                    var tagify = new Tagify(customIn.DOM.input, {
                        delimiters : null,
                        // tagTextProp: 'name', // very important since a custom template is used with this property as text. allows typing a "value" or a "name" to match input with whitelist
                        enforceWhitelist: false,
                        skipInvalid: true, // do not temporarily add invalid tags
                        templates : {
                            tag : function(tagData){
                                try{
                                return "<tag title='" + tagData.value + "' contenteditable='false' spellcheck=\"false\" class='tagify__tag " + (tagData.class ? tagData.class : "") + "' " +  this.getAttributes(tagData) + "> <x title='remove tag' class='tagify__tag__removeBtn'></x> <div> <div class=\"tagify__tag__avatar-wrap\"> <img onerror=\"this.style.visibility='hidden'\" loading=\"lazy\" src=\"" + tagData.picture + "\"> </div> <span class='tagify__tag-text'>" + tagData.firstname + " " + tagData.lastname + "</span> </div> </tag>";
                                }
                                catch(err){}
                            },

                            dropdownItem : function(tagData){

                                try{
                                    return "<div class='tagify__dropdown__item " + (tagData.class ? tagData.class : "") + "' tabindex=\"0\" role=\"option\">" + (tagData.picture ? " <div class='tagify__dropdown__item__avatar-wrap'> <img onerror=\"this.style.visibility='hidden'\" loading=\"lazy\" src=\"" + tagData.picture + "\"> </div>" : "") + "<strong>" + tagData.firstname + " " + tagData.lastname + "</strong><span>" + tagData.mail + "</span></div>";
                                }
                                catch(err){}
                            }
                        },
                        dropdown : {
                            enabled: 3, // suggest tags after a single character input
                            classname : 'users-list', // custom class for the suggestions dropdown
                            closeOnSelect: true,
                            searchKeys: ['firstname', 'lastname']  // very important to set by which keys to search for suggesttions when typing
                        }, // map tags' values to this property name, so this property will be the actual value and not the printed value on the screen
                        whitelist : [],
                    })

                    if(customIn.data && customIn.data.length > 0){
                        tagify.addTags(customIn.data)
                    }

                    let onTagifyInput =  async function(e){

                        let search = e.detail.value

                        // clear current whitelist
                        tagify.settings.whitelist.length = 0; // reset current whitelist

                        if(search.length > 2) {

                            // show loader & hide suggestions dropdown (if opened)
                            tagify.loading(true).dropdown.hide.call(tagify)

                            let encodeSearch = customIn.searchUrl(search);

                            var res = await fetch(encodeSearch);
                            var data = await res.json();

                            let newWhitelist = await customIn.formatData(data);

                            // replace tagify "whitelist" array values with new values
                            // and add back the ones already choses as Tags
                            tagify.settings.whitelist.push(...newWhitelist, ...tagify.value)

                            // render the suggestions dropdown
                            tagify.loading(false).dropdown.show.call(tagify, e.detail.value);
                        }

                    }

                    // listen to any keystrokes which modify tagify's input
                    let timeout = null
                    tagify.on('input', function(e){
                        clearTimeout(timeout)
                        timeout = setTimeout(function(){
                            onTagifyInput(e)
                        }, 500)
                    })

                    tagify.on('blur', e => {
                        customIn.events.toogleInput(customIn, false)
                    })

                    tagify.on('change', (e) => {
                        let newValues = []
                        try {
                            newValues = JSON.parse(e.detail.value)

                        } catch (error) {
                            console.log(error.message)
                        }
                        customIn.saveData(newValues)
                    })

                    customIn.DOM.customInput = tagify
                }

                break;

            case 'ckeditor-classic':
                customIn.templates.input = function(){
                    return "<textarea class=\"input-control form-control CEditor\">" + (props.placeholder ? Drupal.t(props.placeholder) : Drupal.t('No content')) + "</textarea>";
                }

                if(typeof props.showConfirmationButtons != "undefined" && props.showConfirmationButtons == true) {
                    customIn.hooks.preSave = (params) => customIn.hooksHelpers.confirmationHookPromise(params);
                }

                customIn.events.showInputCustom = function(){
                    customIn.DOM.customInput.focus()
                }

                customIn.initCustomInput = async function(){
                    try {
                        let ckeditor = await ClassicEditor.create(customIn.DOM.input, Gofast.parseCKEditorProfile(Drupal.settings.ckeditor.profiles["ckeditor-classic"]));
                        customIn.getData = () => ckeditor.getData();
                        if(customIn.data && customIn.data.trim().length){
                            ckeditor.setData(customIn.data);
                        } else if (customIn.data) {
                            (props.placeholder ? Drupal.t(props.placeholder) : Drupal.t('No content'));
                        }
                        if(typeof props.showConfirmationButtons != "undefined" && props.showConfirmationButtons == true) {
                            $(".editableInputConfirmationButtons .text-success").on("click", async (e) => {
                                e.stopPropagation();
                                $(".editableInputConfirmationButtons").remove();
                                let data = ckeditor.getData();
                                console.log(data);
                                await customIn.saveData(ckeditor.getData());
                                customIn.events.toogleInput(customIn, false);
                            });
                            $(".editableInputConfirmationButtons .text-danger").on("click", () => {
                                e.stopPropagation();
                                $(".editableInputConfirmationButtons").remove();
                                customIn.events.toogleInput(customIn, false);
                            });
                        }
                        ckeditor.editing.view.document.on( 'change:isFocused', ( evt, data, isFocused ) => {
                            if(typeof props.showConfirmationButtons != "undefined" && props.showConfirmationButtons == true) {
                                return;
                            }
                            if(!isFocused){
                                let data = ckeditor.getData()
                                customIn.saveData(data)
                                customIn.events.toogleInput(customIn, false)
                            }
                        } );
                        // override the paste event to avoid view/model mapping errors due to pasting misformatted HTML
                        ckeditor.editing.view.document.on('clipboardInput', (evt, data) => {
                            const dataTransfer = data.dataTransfer;
                            let content = dataTransfer.getData('text/plain');
                            data.content = ckeditor.data.htmlProcessor.toView(content);
                        });

                        customIn.DOM.customInput = ckeditor


                    } catch (error) {
                        console.log(error)
                    }
                }

                break;
             case 'ckeditor-full':
                customIn.templates.input = function(){
                    return "<textarea class=\"input-control form-control CEditor\">" + (props.placeholder ? Drupal.t(props.placeholder) : Drupal.t('No content')) + "</textarea>";
                }

                if(typeof props.showConfirmationButtons != "undefined" && props.showConfirmationButtons == true) {
                    customIn.hooks.preSave = (params) => customIn.hooksHelpers.confirmationHookPromise(params);
                }

                customIn.events.showInputCustom = function(){
                    customIn.DOM.customInput.focus()
                }

                customIn.initCustomInput = async function(){
                    try {
                        let ckeditor = await ClassicEditor.create(customIn.DOM.input, Gofast.parseCKEditorProfile(Drupal.settings.ckeditor.profiles["ckeditor-full"]));
                        customIn.getData = () => ckeditor.getData();
                        if(customIn.data && customIn.data.trim().length){
                            ckeditor.setData(customIn.data);
                        } else if (customIn.data) {
                            (props.placeholder ? Drupal.t(props.placeholder) : Drupal.t('No content'));
                        }
                        if(typeof props.showConfirmationButtons != "undefined" && props.showConfirmationButtons == true) {
                            $(".editableInputConfirmationButtons .text-success").on("click", async (e) => {
                                e.stopPropagation();
                                $(".editableInputConfirmationButtons").remove();
                                let data = ckeditor.getData();
                                await customIn.saveData(ckeditor.getData());
                                customIn.events.toogleInput(customIn, false);
                            });
                            $(".editableInputConfirmationButtons .text-danger").on("click", () => {
                                e.stopPropagation();
                                $(".editableInputConfirmationButtons").remove();
                                customIn.events.toogleInput(customIn, false);
                            });
                        }
                        ckeditor.editing.view.document.on( 'change:isFocused', ( evt, data, isFocused ) => {
                            if(typeof props.showConfirmationButtons != "undefined" && props.showConfirmationButtons == true) {
                                return;
                            }
                            if(!isFocused){
                                let data = ckeditor.getData()
                                customIn.saveData(data)
                                customIn.events.toogleInput(customIn, false)
                            }
                        } );

                        customIn.DOM.customInput = ckeditor


                    } catch (error) {
                        console.log(error)
                    }
                }

                break;
                
             case 'ckeditor-classic-enrich':

                customIn.templates.input = function(){
                    return "<textarea class=\"input-control form-control CEditor\">" + (props.placeholder ? Drupal.t(props.placeholder) : Drupal.t('No content')) + "</textarea>";
                }

                customIn.events.showInputCustom = function(){
                    customIn.DOM.customInput.focus()
                }

                customIn.initCustomInput = async function(){
                    try {
                        let ckeditor = await ClassicEditor.create(customIn.DOM.input, Gofast.parseCKEditorProfile(Drupal.settings.ckeditor.profiles["ckeditor-classic-enrich"]));
                        if(customIn.data){
                            ckeditor.setData(customIn.data);
                        }
                        customIn.DOM.customInput = ckeditor


                    } catch (error) {
                        console.log(error)
                    }
                }

                break;;

            case 'ckeditor-comment':

                customIn.templates.input = function(){                 
                        return "<textarea class=\"input-control form-control CEditor\"></textarea><button type=\"submit\" name=\"op\" value=\"" + Drupal.t("Save") + "\" class=\"btn btn-sm btn-success form-submit icon-before save-cke\"> <span class=\"icon glyphicon glyphicon-ok\" aria-hidden=\"true\"></span> " + Drupal.t("Save") + "</button>&nbsp;<button type=\"submit\"  name=\"op\" value=\"" + Drupal.t("Cancel") + "\" class=\"btn btn-sm btn-bg-secondary icon-before cancel-cke\"> <span class=\"icon glyphicon glyphicon-cross\" aria-hidden=\"true\"></span> " + Drupal.t("Cancel") + "</button>";
                    
                }

                customIn.initCustomInput = async function(){
                    try {
                        let ckeditor = await ClassicEditor.create(customIn.DOM.input, Gofast.parseCKEditorProfile(Drupal.settings.ckeditor.profiles["ckeditor-comment"]));
                        if(customIn.data){
                            ckeditor.setData(customIn.data);
                        }


                        customIn.DOM.customInput = ckeditor

                        // Prevent edition by clicking on comment
                        customIn.DOM.valueContent.onclick = function(e){
                            e.stopPropagation()
                        };

                        // Instead enable start edition from button
                        $(customIn.DOM.valueContent).on('editFromButton', (e) => {
                            customIn.events.toogleInput(customIn, true);
                        });


                    } catch (error) {
                        console.log(error)
                    }
                }

                break;

            case 'docstags':

                customIn.templates.value = function(data){
                    if (data && data.length > 0) {

                        let docsEls = []

                        docsEls = data.map(doc => {
                            return "<div class=\"d-flex documentsList__item\" title=\"" + doc.name + "\"><i class=\"" + doc.icon + " icon-md mr-2\"></i><a class=\"overflow-hidden text-nowrap text-truncate\" style=\"max-width: 30ch;\" href=\"/node/" + encodeURIComponent(doc.value) + "\">" + doc.name + "</a></div>";

                        });
                        return "<div class=\"documentsList\">" + docsEls.join("") + "</div>";

                    } else {
                        return ('<div class="text-muted">' + Drupal.t("No documents selected", {}, {context: "gofast"}) + '</div>');
                    }
                }
                
                customIn.events.showInputCustom = () => {
                    $(customIn.DOM.customInput.DOM.input).trigger('focus');
                    $(".gofastKanbanCardDetail .separator:last-of-type").css("visibility", "hidden");
                }
                customIn.events.hideInputCustom = () => {
                    $(".gofastKanbanCardDetail .separator:last-of-type").css("visibility", "visible");
                }
                
                var originalDataList = [];
                
                customIn.initCustomInput = () => {
                    var dataList = null;
                    dataList = originalDataList = customIn.data;

                    var tagify = new Tagify(customIn.DOM.input, {
                        delimiters: null,
                        tagTextProp: 'name', // very important since a custom template is used with this property as text. allows typing a "value" or a "name" to match input with whitelist
                        enforceWhitelist: true,
                        skipInvalid: false, // do not temporarily add invalid tags
                        templates : {
                            tag : function(tagData){
                                try{
                                    return "<tag title='" + tagData.value + "' contenteditable='false' spellcheck=\"false\" class='tagify__tag " + (tagData.class ? tagData.class : "") + "' " +  this.getAttributes(tagData) + "><x title='remove tag' class='tagify__tag__removeBtn'></x><div> <i class=\"" + tagData.icon + " mr-2\"></i> <span class='tagify__tag-text'>" + tagData.name + "</span></div></tag>";

                                }
                                catch(err){
                                    console.log(err.message)
                                }
                            },

                            dropdownItem : function(tagData){
                                try{
                                    return "<div class='d-flex align-items-center tagify__dropdown__item " + (tagData.class ? tagData.class : "") + "' tagifySuggestionIdx=\"" + tagData.tagifySuggestionIdx + "\"><i class=\"" + tagData.icon + " mr-2\"></i><span>" + tagData.name + "</span></div>";
                                }
                                catch(err){
                                    console.log(err.message)
                                }
                            }
                        },
                        dropdown : {
                            enabled: 3, // suggest tags after a single character input
                            classname : 'docs-list', // custom class for the suggestions dropdown
                            closeOnSelect: true,
                            searchKeys: ['name']  // very important to set by which keys to search for suggestions when typing
                        }, // map tags' values to this property name, so this property will be the actual value and not the printed value on the screen
                        whitelist : dataList != null ? dataList : [],
                    })

                    if(customIn.data && customIn.data.length > 0){
                        tagify.addTags(customIn.data)
                    }

                    let onTagifyInput =  async function(e){
                        if (e.type == "invalid" && e.detail.message == "already exists") {
                            return;
                        }
                        //number of ms we wait before sending the ac request
                        await new Promise(resolve => setTimeout(() => resolve(), 200));
                        let search = e.type === "invalid" ?  e.detail.data.name : e.detail.tagify.DOM.input.innerText;
                        // clear current whitelist
                        tagify.settings.whitelist.length = 0; // reset current whitelist

                        if(search.length > 2) {

                            // show loader & hide suggestions dropdown (if opened)
                            tagify.loading(true).dropdown.hide.call(tagify)

                            let formData = new FormData()

                            formData.append('str', search)
                            formData.append('get_user', false)
                            formData.append('get_node', true)
                            formData.append('get_userlist', false)
                            formData.append('get_taxonomy_term', false)
                            formData.append('input_id', 'edit-list-documents')


                            let url = window.origin + "/gofast/gofast_ac_config";

                            const res = await fetch(url, {
                                method: 'POST',
                                body: formData
                            })

                            const data = await res.json()

                            let newWhitelist = await data

                            if (newWhitelist.length) {
                                // replace tagify "whitelist" array values with new values
                                // and add back the ones already choses as Tags
                                tagify.settings.whitelist.push(...newWhitelist, ...tagify.value)

                                // render the suggestions dropdown
                                tagify.loading(false).dropdown.show.call(tagify, e.detail.value);
                            } else {
                                tagify.settings.whitelist.length = 0;
                                tagify.loading(false).dropdown.hide.call(tagify);
                                const nodeURLRegex = /^(https?:\/\/?)?(www\.)?[A-Za-z0-9\W_]+\/node\/([0-9]+).*/;
                                if (!search.match(nodeURLRegex)) {
                                  return;
                                }
                                const nodeIDURLMatch = search.match(nodeURLRegex)[3];
                                if (nodeIDURLMatch) {
                                  fetch(Drupal.settings.gofast.baseUrl + '/gofast/metadata/node/' + nodeIDURLMatch + '/load?icon=true')
                                    .then(response => response.json())
                                    .then(data => {
                                      if (data.title) {
                                        let formattedData = [
                                          {
                                            node_type: "alfresco_item",
                                            type: "node",
                                            icon: data.icon,
                                            name: data.title,
                                            value: data.nid,
                                          }
                                        ];
                                        tagify.settings.whitelist.push(...formattedData, ...tagify.value);
                                        tagify.addTags(formattedData);
                                        e.detail.inputElm.innerHTML = "";
                                      }
                                    });
                                }
                            }
                        }
                    }

                    // align cursor with tags
                    $(customIn.DOM.inputContent).find("tags").addClass("d-flex align-items-center");

                    // listen to any keystrokes which modify tagify's input
                    let timeout = null
                    tagify.on('keydown', function(e){
                        clearTimeout(timeout)
                        timeout = setTimeout(function(){
                            onTagifyInput(e)
                        }, 500)
                    })

                    tagify.on('invalid', function(e){
                        clearTimeout(timeout)
                        timeout = setTimeout(function(){
                            onTagifyInput(e)
                        }, 500)
                    })

                    const tagifyBlurCallback = e => customIn.events.toogleInput(customIn, false);
                    tagify.on('blur', tagifyBlurCallback);

                    tagify.on('change', (e) => {
                        clearTimeout(timeout)
                        timeout = setTimeout(function(){
                            onTagifyInput(e)
                            let newValues = []
                            try {
                                newValues = JSON.parse(e.detail.value == "" ? "[]" : e.detail.value)
                            } catch (error) {
                                console.log(error.message)
                            }
                            customIn.saveData(newValues)
                        }, 500);
                    })

                    // condition for confirmation buttons and draft mode
                    if(typeof props.draftMode != "undefined" && props.draftMode == true) {
                        customIn.hooks.preSave = (params) => customIn.hooksHelpers.confirmationHookPromise(params);
                        tagify = customIn.hooksHelpers.setTagifyDraftMode(tagify);
                    }

                    customIn.DOM.customInput = tagify
                }

                break;
            case 'tags':
                customIn.templates.value = function(data){
                    if (data && data.length > 0) {

                        let tagsEls = [];
                        const dataLen = data.length;
                        tagsEls = data.map((tag, i) => {
                            if (tag.tid) {
                                return "<div class=\"tagsList__item mr-2\"><span id=\"tagList__item_" + tag.tid + "\">" + tag.name + "</span></div>";

                            } else {
                                return "<div class=\"tagsList__item mr-2\"><span id=\"tagList__item_" + tag.name + "\">" + tag.name + "</span></div>";
                            }
                        })
                        return "<div class=\"tagsList\">" + tagsEls.join("") + "</div>";

                    } else {
                        return "<div class=\"text-muted\">" + (props.placeholder ? Drupal.t(props.placeholder) : Drupal.t('No element')) + "</div>";
                    }
                }

                customIn.events.showInputCustom = () => {

                    $(customIn.DOM.customInput.DOM.input).trigger('focus');

                }



                customIn.initCustomInput = () => {

                    var tagify = new Tagify(customIn.DOM.input, {
                        delimiters : null,
                        // tagTextProp: 'name', // very important since a custom template is used with this property as text. allows typing a "value" or a "name" to match input with whitelist
                        enforceWhitelist: false,
                        skipInvalid: true, // do not remporarily add invalid tags
                        templates : {
                            tag : function(tagData){
                                try{
                                    return "<tag title='" + tagData.value + "' contenteditable='false' spellcheck=\"false\" class='tagify__tag " + (tagData.class ? tagData.class : "") + "' " +  this.getAttributes(tagData) + "><x title='remove tag' class='tagify__tag__removeBtn'></x><div> <span class='tagify__tag-text'>" + tagData.name + "</span></div></tag>";
                                }
                                catch(err){
                                    console.log(err.message)
                                }
                            },
                            dropdownItem : function(tagData){
                                try{
                                    return "<div class='tagify__dropdown__item " + (tagData.class ? tagData.class : "") + "' tagifySuggestionIdx=\"" + tagData.tagifySuggestionIdx + "\"><span>" + tagData.name + "</span></div>";
                                }
                                catch(err){
                                    console.log(err.message)
                                }
                            }
                        },
                        dropdown : {
                            enabled: 3, // suggest tags after a single character input
                            classname : 'tags-list', // custom class for the suggestions dropdown
                            closeOnSelect: true,
                            searchKeys: ['name']  // very important to set by which keys to search for suggesttions when typing
                        }, // map tags' values to this property name, so this property will be the actual value and not the printed value on the screen
                        whitelist : [],
                    })

                    if(customIn.data && customIn.data.length > 0){
                        tagify.addTags(customIn.data)
                    }

                    let onTagifyInput =  async function(e){

                        let search = e.detail.value

                        // clear current whitelist
                        tagify.settings.whitelist.length = 0; // reset current whitelist

                        if(search.length > 2) {

                            // show loader & hide suggestions dropdown (if opened)
                            tagify.loading(true).dropdown.hide.call(tagify)

                            let formData = new FormData()

                            formData.append('str', search)
                            formData.append('input_id', 'edit-list-tags')
                            formData.append('get_taxonomy_term', true)
                            var dataVid = $(e.detail.inputElm).parents('.gutter-b').find('.text-uppercase').attr('data-vid');
                            var dataEnforce = $(e.detail.inputElm).parents('.gutter-b').find('.text-uppercase').attr('data-enforce');
                            formData.append('vid', dataVid);
                            formData.append('enforce', dataEnforce);

                            let url = window.origin + "/gofast/gofast_ac_config";

                            const res = await fetch(url, {
                                method: 'POST',
                                body: formData
                            })

                            const data = await res.json()

                            // let newWhitelist = await data.map(user => {
                            //     user.value = Number.parseInt(user.uid)
                            //     return user
                            // })

                            let newWhitelist = await data

                            // replace tagify "whitelist" array values with new values
                            // and add back the ones already choses as Tags
                            tagify.settings.whitelist.push(...newWhitelist, ...tagify.value)

                            // render the suggestions dropdown
                            tagify.loading(false).dropdown.show.call(tagify, e.detail.value);
                        }

                    }

                    // listen to any keystrokes which modify tagify's input
                    let timeout = null
                    tagify.on('input', function(e){
                        clearTimeout(timeout)
                        timeout = setTimeout(function(){
                            onTagifyInput(e)
                        }, 500)
                    })

                    tagify.on('blur', e => {
                        customIn.events.toogleInput(customIn, false)
                    })

                    tagify.on('change', (e) => {
                        let newValues = []
                        try {
                            newValues = JSON.parse(e.detail.value)

                        } catch (error) {
                            console.log(error.message)
                        }
                        customIn.saveData(newValues)
                    })

                    customIn.DOM.customInput = tagify
                }
                break;
            default:
                break;
        }
    }

    if(props){

        for(const property in props) {

            if(typeof(props[property]) == "object" && !Array.isArray(props[property])) {
               customIn[property] = {...customIn[property], ...props[property]}
            }
            else {
               customIn[property] = props[property]
            }


        }
    }

    customIn.init(element, initialData)

    return customIn

}

window.ckeditorPluginMentionCustomization =  function(editor) {
    editor.conversion.for('upcast').elementToAttribute({
        view: {
            name: 'a',
            classes: 'gofast__comment-tag'
        },
        model: {
            key: "mention",
            value: viewItem => {
                const style = viewItem.getAttribute('style');
                const imageUrlMatch = style && style.match(/url\('([^']+)'\)/);
                const image = imageUrlMatch && imageUrlMatch[1];
                return editor.plugins.get('Mention').toMentionAttribute(viewItem, {
                    id: viewItem.getAttribute('data-mention'),
                    link: viewItem.getAttribute('href'),
                    userId: viewItem.getAttribute('data-user-id'),
                    image: image
                });
            }
        }
    });

    editor.conversion.for('downcast').attributeToElement({
        model: 'mention',
        view: (modelAttributeValue, { writer }) => {
            // Do not convert empty attributes (lack of value means no mention).
            if (!modelAttributeValue) {
                return;
            }
            // Create the 'img' element.
            return writer.createAttributeElement('a', {
                id: `user-autocomplete-${modelAttributeValue.userId}`,
                class: 'gofast__comment-tag',
                'data-mention': modelAttributeValue.id,
                'data-user-id': modelAttributeValue.userId,
                href: modelAttributeValue.link,
                style: "--bg-image: url('"+ modelAttributeValue.image +"')",
                contenteditable: false, 
            }, {
                // Make mention attribute to be wrapped by other attribute elements.
                priority: 20,
                // Prevent merging mentions together.
                id: modelAttributeValue.uid,
            });
        },
        converterPriority: 'high',
    })
};

window.ckeditorPluginMentionFeeds = function(queryText = '') {
    return new Promise((resolve, reject) => {
        if (!queryText) {
            reject();
        }
        var nid = Drupal.settings.gofast.node.id;
        clearTimeout(window.ckeditorPluginMentionFeedsTimeout);
        window.ckeditorPluginMentionFeedsTimeout = setTimeout(() => {
            $.ajax({
                type: "GET",
                url: location.origin+'/gofast_og/'+nid+'/get_visible_node_users',
                success: function (users) {
                    itemsArray= [];
                    users = JSON.parse(users)
                    users.map((user) => {
                        itemsArray.push({
                            id: '@' + user.name,// the ID will be automatically displayed on the dropdown list
                            name: user.display_name,
                            link:  window.location.origin + '/user/' + user.value,
                            email: user.email,
                            userId: user.value,
                            image: user.avatar,
                        })
                    })
                    const itemsToDisplay = itemsArray
                        .filter(isItemMatching)
                        .slice(0, 10);
                    resolve(itemsToDisplay);
                }
            })
        }, 500); // delay in ms

        function isItemMatching(item) {
            // Make the search case-insensitive.
            const searchString = queryText.toLowerCase();
            // Include an item in the search results if the name or username includes the current user input.
            return (
                item.name.toLowerCase().includes(searchString) ||
                item.id.toLowerCase().includes(searchString) ||
                item.email.toLowerCase().includes(searchString)
            );
        }
    });
}

window.ckeditorPluginMentionFeedItemRenderer =  function(item) {
    const itemElement = document.createElement('span');
    itemElement.classList.add('gofast__comment-tag');
    itemElement.style.background = "transparent";
    itemElement.style.width= "fit-content";
    itemElement.id = `user-autocomplete-${item.value}`;
    const imageElement = document.createElement('img');
    imageElement.classList.add('gofast__comment-tag-icon');
    imageElement.style.width = '20px';
    imageElement.style.height = '20px';
    imageElement.style.objectFit = 'cover';
    imageElement.style.borderRadius = '50%';
    imageElement.setAttribute('data-image', item.image)
    imageElement.setAttribute('src', item.image)
    itemElement.appendChild(imageElement);
    const textElement = document.createElement('a');
    textElement.classList.add('gofast__comment-tag-text');
    textElement.textContent = item.name;
    textElement.style.marginLeft = '10px';
    textElement.style.fontWeight = '600';
    itemElement.appendChild(textElement);
    $('.ck-mentions > li:nth-child(1)').css('background', 'rgba(239,240,239,0.63)')
    return itemElement;
};

