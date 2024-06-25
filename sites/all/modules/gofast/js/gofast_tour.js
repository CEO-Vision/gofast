/**
 * Describe content of contextual helps.
 */
//function executed at every page load
(function ($, Gofast, Drupal) {
    const LOG_DATA_REQUESTS = false; //enables/disables the logging when fetching/storing data on server
    let BRAND;

    /**
     * Generates a regular expression from a simplified route declaration (see routes object)
     * @param {String|RegExp} path The path of the route
     * @returns {RegExp} The regex to check whether you are currently in the correct route
     */
    function pathReg(path) {
        let reg = "";
        if (path instanceof String || typeof path === "string") {
            reg += "^";
            reg += path.substring(0, path.length - 1).replace("*", "[^\/]+");
            let end = path.substring(path.length - 1);
            if (end !== "*") {
                reg += end + "$";
            }
        } else {
            reg = path;
        }
        return new RegExp(reg);
    }
    /**
     * Returns true if on mobile version, false on the standard version or simplified
     * @returns {boolean}
     */
    function isMobile() { return Gofast.isMobileResolution() }
    /**
     * Returns true if on simplifed version, false otherwise.
     * @returns {boolean}
     */
    function isSimplified() { return Gofast._settings.isEssential }
    /**
     * Returns a string representing the current version
     * @returns {"standard"|"simplified"|"mobile"}
     */
    function getVersion() { return ["standard", "mobile", "simplified"][isSimplified() ? 2 : isMobile() ? 1 : 0] }
    /**
     * Defers execution of other code based on visibility of a necessary HTML element.
     * Returns a Promise for use with ShepherdJS beforeShowPromise
     * @param {String} selector The selector of the element to check. passing a string can check if an element is not present initially on the page
     * @param {number} interval check interval, defaults to 100.
     */
    function waitForElementVisibility(selector, interval = 500) {
        return new Promise(async (resolve) => {
            const waitForElementInterval = setInterval(() => {
                if (!$(selector).length) {
                    return;
                }
                clearInterval(waitForElementInterval);
                resolve();
            }, interval);
        });
    }
    /**
     * Adds a step indicator (ex: - 2/6) for all steps of a tour. Applies a pattern which may be translated if needed.
     * @param {Object[]} steps The step array for
     * @param {{stepCount:number,start:number}} args Additional arguments
     * @returns {Object[]}
     */
    function autoStepIndicator(steps, args = {}) {
        let i = +(args.start !== 0) && (args.start || 1); // lets i be args.start even if args.start is 0
        let stepCount = args.stepCount || steps.length;

        for (let s of steps) {
            if (s.title) {
                s.title = Drupal.t(
                    "@title - @index/@stepCount",
                    { "@title": s.title, "@index": i, "@stepCount": stepCount },
                    { context: "gofast_tour" }
                );
            }
            i++;
        }
        return steps;
    }
    Gofast.tour = {
        data: {
            configuration: {},
            pages: {
                done: {},
                notified: {},
            },
            fragments: {},
            enabled: -1,
            cancelActionsToAwait: [],
        },
        boilerplates: {
            newTour() {
                return new Shepherd.Tour({
                    useModalOverlay: true,
                    defaultStepOptions: {
                        classes: 'shadow-md bg-dark gofast-shepherd-tour',
                        scrollTo: true,
                        cancelIcon: {
                            enabled: true
                        },
                    },
                })
            },
            baseButtons() {
                return [
                    {
                        text: "<i class=\"fas fa-step-backward\"></i>",
                        action() {
                            Gofast.tour.data.cancelActionsToAwait[Gofast.tour.currentInstance.getCurrentStep().id] = true;
                            Gofast.tour.currentInstance.back();
                        },
                    },
                    {
                        text: "<i class=\"fas fa-step-forward\"></i>",
                        action(){
                            Gofast.tour.data.cancelActionsToAwait[Gofast.tour.currentInstance.getCurrentStep().id] = true;
                            Gofast.tour.currentInstance.next();
                        } 
                    }
                ]
            },
            baseCancel() {
                Gofast.tour.data.cancelActionsToAwait[Gofast.tour.currentInstance.getCurrentStep().id] = true;
                $("#gofast_over_content").removeClass('tour-processed');
                Gofast.tour.components.fakeCursor.destroy();
            },
            essentialTourLastStepOnCancel() {
                Gofast.tour.boilerplates.baseCancel();
                Gofast.tour.currentInstance = Gofast.tour.boilerplates.newTour();
                let targetStep = [Gofast.tour.descriptions.simplifiedEssentialTourLastStep];
                Gofast.tour.currentInstance.addSteps(targetStep);
                Gofast.tour.currentInstance.start();
            }
        },
        sequences: {
            _actionToAwait(actionHandler, timeout) {
                return new Promise((resolve, reject) => {
                    var stepId = Gofast.tour.currentInstance.getCurrentStep().id
                    setTimeout(async () => {
                        if(Gofast.tour.data.cancelActionsToAwait[stepId]){
                            Gofast.tour.data.cancelActionsToAwait[stepId] = false;
                            resolve("cancel");
                        }else{
                            await actionHandler();
                            resolve();
                        }
                    }, timeout);
                });
            },
            // custom sequence: array of actions to be executed in array order with given timeout as a time gap
            actionsToAwait(actionsHandlers, timeout) {
                Gofast.tour.data.cancelActionsToAwait[Gofast.tour.currentInstance.getCurrentStep().id] = false;
                return new Promise(async (resolve, reject) => {
                    for (const actionHandler of actionsHandlers) {
                        const isCancelled = (await this._actionToAwait(actionHandler, timeout) == "cancel");
                        if(isCancelled){
                            resolve()
                            break;
                        }
                    }
                    resolve();
                })

            },
            // menu sequence: simulate hover events over all items of given unordered list
            showMenuItems($menuList) {
                let itemsCount = $menuList.find("> li").length;
                let itemsCounter = 1;
                const showMenuItemsInterval = setInterval(async function() {
                    if(Gofast.tour.currentInstance.getCurrentStep().id != "gofast-tour-home-menu-step" || Gofast.tour.currentInstance.isActive() == false){    
                        clearInterval(showMenuItemsInterval);
                        return;
                    }
                    if (itemsCounter > itemsCount) {
                        $menuList.find("> li:nth-of-type(" + (itemsCounter - 1) + ")").first().removeClass("menu-item-hover");
                        clearInterval(showMenuItemsInterval);
                        return;
                    }
                    const $currentTarget = $menuList.find("> li:nth-of-type(" + itemsCounter + ") a").first();
                    await Gofast.tour.sequences._actionToAwait(() => Gofast.tour.components.fakeCursor.moveTo($currentTarget[0], 500), 500);
                    $menuList.find("> li:nth-of-type(" + (itemsCounter - 1) + ")").first().removeClass("menu-item-hover");
                    $menuList.find("> li:nth-of-type(" + itemsCounter + ")").first().addClass("menu-item-hover");
                    itemsCounter++;
                }, 1000);
            },
            showSpacesMenuItems($menuList) {
                let itemsCount = $menuList.find("> li").length;
                let itemsCounter = 0;
                let submenuId = '';
                const showSpacesMenuItemsInterval = setInterval(async function() {
                    //cancel animation if tour step is changed or canceled
                    if(Gofast.tour.currentInstance.getCurrentStep().id != "gofast-tour-home-spaces-menu-step" || Gofast.tour.currentInstance.isActive() == false){
                        clearInterval(showSpacesMenuItemsInterval);
                        return;
                    }
                    if (itemsCounter >= itemsCount) {
                        $menuList.find("> li").eq(itemsCounter - 1).removeClass("menu-item-hover");
                        if(itemsCounter > 0) {
                            if($menuList.find("> li").eq(itemsCounter - 1).hasClass("menu-item-submenu")){
                                submenuId = $("#gf-spaces-menu > .menu-submenu > .menu-subnav > .menu-content > .menu-item > .menu-inner > li").eq(itemsCounter - 1).attr('id')
                                Gofast.spacesMenu.cleanSubMenus($('#'+submenuId));
                            }
                        }
                        clearInterval(showSpacesMenuItemsInterval);
                        return;
                    }
                    const $currentTarget = $menuList.find("> li").eq(itemsCounter);
                    await Gofast.tour.sequences._actionToAwait(() => Gofast.tour.components.fakeCursor.moveTo($currentTarget[0], 500), 500);
                    $menuList.find("> li").eq(itemsCounter - 1).removeClass("menu-item-hover");
                    if(itemsCounter > 0) {
                        if($menuList.find("> li").eq(itemsCounter - 1).hasClass("menu-item-submenu")){
                            submenuId = $("#gf-spaces-menu > .menu-submenu > .menu-subnav > .menu-content > .menu-item > .menu-inner > li").eq(itemsCounter - 1).attr('id')
                            Gofast.spacesMenu.cleanSubMenus($('#'+submenuId));
                        }
                    }
                    $menuList.find("> li").eq(itemsCounter).addClass("menu-item-hover");
                    if($currentTarget.hasClass("menu-item-submenu")){
                        submenuId = $("#gf-spaces-menu > .menu-submenu > .menu-subnav > .menu-content > .menu-item > .menu-inner > li").eq(itemsCounter).attr('id')
                        Gofast.spacesMenu.loadSubMenu($('#'+submenuId));
                    }
                    itemsCounter++;
                }, 1000);
            },
            showProfileMenuItems($menuList) {
                let itemsCount = $menuList.find("> li").length;
                let itemsCounter = 1;
                const showProfileMenuItemsInterval = setInterval(async function() {
                    //cancel animation if tour step is changed or canceled
                    if(Gofast.tour.currentInstance.getCurrentStep().id != 'gofast-tour-home-profile-step' || Gofast.tour.currentInstance.isActive() == false){
                        clearInterval(showProfileMenuItemsInterval);
                        return;
                    }
                    
                    if (itemsCounter > itemsCount) {
                        $menuList.find("> li:nth-of-type(" + (itemsCounter - 1) + ") > .navi-link").first().removeClass("dropdown-item-hover");
                        clearInterval(showProfileMenuItemsInterval);
                        return;
                    }
                    const $currentTarget = $menuList.find("> li:nth-of-type(" + itemsCounter + ") > .navi-link").first();
                    await Gofast.tour.sequences._actionToAwait(() => Gofast.tour.components.fakeCursor.moveTo($currentTarget[0], 500), 500);
                    $menuList.find("> li:nth-of-type(" + (itemsCounter - 1) + ") > .navi-link").first().removeClass("dropdown-item-hover");
                    $currentTarget.addClass("dropdown-item-hover");
                    itemsCounter++;
                }, 1000);
            },
            simulateSearchTyping(){
                setTimeout(()=>{
                    let simulatedText = "Document"
                    let textLength = simulatedText.length;
                    let textIndex = 0;
                    $input = $("[name='search_block_form']");
                    let e = $.Event('keyup');
                    e.which = 32;
                    const simulateSearchTypingInterval = setInterval(function() {
                        //cancel animation if tour step is changed or canceled
                        if(Gofast.tour.currentInstance.getCurrentStep().id != 'gofast-tour-home-search-step' || Gofast.tour.currentInstance.isActive() == false){
                            clearInterval(simulateSearchTypingInterval);
                            return;
                        }
                        if (textIndex >= textLength) {
                            clearInterval(simulateSearchTypingInterval);
                            return;
                        }
                        $input.val($input.val() + simulatedText[textIndex]).focus().trigger(e);
                        textIndex++;
                    }, 500);
                },500)
            },
            hoverSortByItems($sortList) {
                return new Promise((resolve, reject) => {
                    let itemsCount = $sortList.find("> li").length;
                    let itemsCounter = 1;
                    const hoverSortByItemsInterval = setInterval(async function() {
                        //cancel animation if tour step is changed or canceled
                        if (Gofast.tour.currentInstance.getCurrentStep().id != 'gofast-tour-searchPage-sortby-step' ||
                            Gofast.tour.currentInstance.isActive() == false || Gofast.tour.data.cancelActionsToAwait[Gofast.tour.currentInstance.getCurrentStep().id]) {

                            clearInterval(hoverSortByItemsInterval);
                            Gofast.tour.data.cancelActionsToAwait[Gofast.tour.currentInstance.getCurrentStep().id] = false;
                            resolve();
                    
                        } else {
                        
                        if (itemsCounter > itemsCount) {
                            $sortList.find("> li:nth-of-type(" + (itemsCounter - 1) + ")").first().removeClass("sortby-item-hover");
                            clearInterval(hoverSortByItemsInterval);
                            resolve();
                        }
                        const $currentTarget = $sortList.find("> li:nth-of-type(" + itemsCounter + ")").first();
                        await Gofast.tour.sequences._actionToAwait(() => Gofast.tour.components.fakeCursor.moveTo($currentTarget[0], 500), 500);
                            if(!Gofast.tour.data.cancelActionsToAwait[Gofast.tour.currentInstance.getCurrentStep().id]){
                        $sortList.find("> li:nth-of-type(" + (itemsCounter - 1) + ")").first().removeClass("sortby-item-hover");
                        $currentTarget.addClass("sortby-item-hover");
                        itemsCounter++;
                            }
                        }
                    }, 700);
                });
            },
            showFastActionsMenuItems($menuList) {
                let itemsCount = $menuList.find("> .navi-item > .navi-link:not('.disabled')").length;
                let itemsCounter = 0;
                const showFastActionsMenuItemsInterval = setInterval(async function() {
                    
                    //cancel animation if tour step is changed or canceled
                    if(Gofast.tour.currentInstance.getCurrentStep().id != 'gofast-tour-searchPage-fastActionsDropDownMenu-step' || Gofast.tour.currentInstance.isActive() == false){
                        clearInterval(showFastActionsMenuItemsInterval);
                        return;
                    }
                    
                    if (itemsCounter >= itemsCount) {
                        $menuList.find("> .navi-item > .navi-link:not('.disabled')").eq(itemsCounter-1).removeClass("dropdown-item-hover");
                        clearInterval(showFastActionsMenuItemsInterval);
                        return;
                    }
                    const $currentTarget = $menuList.find("> .navi-item > .navi-link:not('.disabled')").eq(itemsCounter);
                    await Gofast.tour.sequences._actionToAwait(() => Gofast.tour.components.fakeCursor.moveTo($currentTarget[0], 500), 500);
                    $menuList.find("> .navi-item > .navi-link:not('.disabled')").eq(itemsCounter-1).removeClass("dropdown-item-hover");
                    $currentTarget.addClass("dropdown-item-hover");
                    itemsCounter++;
                }, 700);
            },
            simulateSearchFiltersInteractions($filters) {
                if(isSimplified){

                    Gofast.tour.sequences.actionsToAwait([
                        () => Gofast.tour.components.fakeCursor.moveTo($filters[0]),
                        () => {
                            if($($filters[0]).hasClass("collapsed")){
                                $filters[0].click();
                            }
                        },
                        () => Gofast.tour.components.fakeCursor.moveTo($filters[1]),
                        () => {
                            if($($filters[1]).hasClass("collapsed")){
                                $filters[1].click();
                            }
                        },
                    ],1000);
                } else {
                    let itemsCount = $filters.length;
                    let itemsCounter = 0;
                    const simulateSearchFiltersInteractionsInterval = setInterval(async function() {
                        if(itemsCounter > 0){
                            $filters.eq(itemsCounter - 1).click();
                        }
                        //cancel animation if tour step is changed or canceled
                        if(Gofast.tour.currentInstance.getCurrentStep().id != 'gofast-tour-searchPage-filters-step' || Gofast.tour.currentInstance.isActive() == false){
                            clearInterval(simulateSearchFiltersInteractionsInterval);
                            return;
                        }
                        
                        if(itemsCounter >= itemsCount){
                            clearInterval(simulateSearchFiltersInteractionsInterval);
                            return;
                        }
                        const $currentTarget = $filters.eq(itemsCounter);
                        await Gofast.tour.sequences._actionToAwait(() => Gofast.tour.components.fakeCursor.moveTo($currentTarget[0], 500), 500);
                        $filters.eq(itemsCounter).click();
                        itemsCounter++;
                    }, 700);
                }
            },
            async openDocMoreTabIfSelectorNotVisible(selector){
                if ($(selector + ":visible").length) {
                    await Gofast.tour.sequences.actionsToAwait([
                        () => Gofast.tour.components.fakeCursor.moveTo($(selector + ":visible")[0]),
                    ], 1000);
                    return;
                }
                await Gofast.tour.sequences.actionsToAwait([
                    () => Gofast.tour.components.fakeCursor.moveTo($(".dropdown-toggle-more:visible")[0], 500),
                    () => $(".dropdown-toggle-more:visible").dropdown("toggle"),
                    () => {},
                ], 500);
            },
            async toggleDocSideContent(open = true){
                if (!$("#metadataSideButton:not(.invisible)").length) {
                    return;
                }
                let isOpen = $("#metadataSideButton").hasClass("expand");
                if ((open && isOpen) || (!open && !isOpen)) {
                    return;
                }
                await Gofast.tour.sequences.actionsToAwait([
                    () => Gofast.tour.components.fakeCursor.moveTo("#metadataSideButton", 500),
                    () =>  $("#metadataSideButton").click(),
                    () => {},
                ], 500); 
            },
            addInvisibleColumnOverElements(selector) {
                const elements = $(selector + ":visible");
                if (typeof elements == "undefined") {
                    return false;
                }

                const scrollParent = $().getScrollParent(elements[0]);

                let totalHeight = 0;
                const filteredElements = [];
                for (const [index, element] of Object.entries(elements)) {
                    if (isNaN(index)) {
                        elements.splice(index, 1);
                        continue;
                    }
                    const bigRect = scrollParent.getBoundingClientRect();
                    const rect = element.getBoundingClientRect();
                    if (scrollParent) {
                        const parentTop = bigRect.top;
                        const parentBottom = bigRect.bottom;
                        const elementTop = rect.top;
                        const elementBottom = rect.bottom;
                        if (elementTop < parentTop || elementBottom > parentBottom) {
                            continue;
                        }
                    }

                    totalHeight += rect.height;
                    filteredElements.push(element);
                }

                let targetTop = filteredElements[0].getBoundingClientRect().top;
                let targetLeft = filteredElements[0].getBoundingClientRect().left;
                let totalWidth = filteredElements[0].getBoundingClientRect().width;

                const invisibleColumn = document.createElement('div');
                invisibleColumn.classList.add("shepherd-invisible-column");
                invisibleColumn.style.position = 'absolute';
                invisibleColumn.style.top = targetTop + 'px';
                invisibleColumn.style.left = targetLeft + 'px';
                invisibleColumn.style.width = totalWidth + 'px';
                invisibleColumn.style.height = totalHeight + 'px';
                invisibleColumn.style.opacity = '0';
                document.body.appendChild(invisibleColumn);
            },
            removeInvisibleColumn() {
                $(".shepherd-invisible-column").remove();
            },
        },
        components: {
            fakeCursor: {
                cursor: null,
                // create cursor
                create: function() {
                    const cursor = document.createElement("i");
                    cursor.id = "gofast-fake-cursor";
                    cursor.style.backgroundImage = "url('" + window.location.origin + "/sites/all/modules/gofast/img/cursor.png')";
                    cursor.style.backgroundPosition = "center";
                    cursor.style.backgroundRepeat = "no-repeat";
                    cursor.style.backgroundSize = "cover";
                    cursor.style.width = "1.5rem";
                    cursor.style.height = "2.5rem";
                    cursor.style.position = "absolute";
                    cursor.style.left = cursor.style.top = "0";
                    cursor.style.transform = "translate(0, 0)";
                    cursor.style.opacity = "0";
                    cursor.style.transition = "opacity .25s ease-in-out, transform 0s ease-in-out";
                    cursor.style.zIndex = "10000";
                    this.cursor = document.body.appendChild(cursor);
                },
                // destroy cursor
                destroy: function() {
                    if (this.cursor) {
                        this.cursor.remove();
                    }
                    this.cursor = null;
                },
                hide: function() {
                    this.cursor.style.opacity = "0";
                },
                show: function() {
                    this.cursor.style.opacity = "1";
                },
                // cursor coordinates are set by translation only since its absolute coordinates are 0: this helper is here to keep track of the cursor coordinates by getting its current translation
                getCurrentTranslation: function() {
                    const transCoordsString = this.cursor.style.transform.match(/translate\((.*)\)/)[1];
                    const transCoords = transCoordsString.split(",").map(e => parseInt(e.trim()))
                    return {left: transCoords[0], top: transCoords[1] ?? transCoords[0]};
                },
                updateTransitionDuration: function(duration) {
                    const durationInSeconds = duration == 0 ? 0 : duration / 1000;
                    // transform will always be the last transition, and we want to keep other existing transitions
                    const elementTransitions = this.cursor.style.transition.split(",").map(e => e.trim());
                    elementTransitions.pop();
                    const previousElementTransitionsString = elementTransitions.join(", ");
                    this.cursor.style.transition = previousElementTransitionsString + ", transform " + durationInSeconds + "s ease-in-out";
                },
                positionTo: function(element) {
                    if (typeof element == "string") {
                        element = document.querySelector(element);
                    }
                    if (element == null) {
                        return;
                    }
                    // we calculate the target position and the related translation
                    const targetBoundingRect = element.getBoundingClientRect();
                    const targetLeft = targetBoundingRect.left + (targetBoundingRect.width / 2);
                    const targetTop = targetBoundingRect.top + (targetBoundingRect.height / 2);
                    const leftTranslation = targetLeft + "px";
                    const topTranslation = targetTop + "px";
                    // then we update the translate transformation accordingly
                    this.cursor.style.transform = "translate(" + leftTranslation + ", " + topTranslation + ")";
                },
                // move cursor from to DOM element in given duration in ms, creates the cursor if it doesn't exist
                moveTo: function(element, duration = 1000) {
                    if(Gofast.tour.currentInstance.isActive() == false){
                        return;
                    }
                    if (this.cursor == null) {
                        this.create();
                    }
                    this.show();
                    // first we have to set the correct amount of time for the transition
                    this.updateTransitionDuration(duration);
                    // then we translate the cursor to the target element
                    this.positionTo(element);
                },
            }
        },
        descriptions: {
            get subscriptionsModalFragment() {
                return [
                    {
                        id: 'gofast-tour-subscriptions-modal-step',
                        title: Drupal.gft("title.tour.subscriptions.modal-step", {}, { context: "gofast_technical:gofast_tour" }),
                        text: Drupal.gft("text.tour.subscriptions.modal-step", {}, { context: "gofast_technical:gofast_tour" }),
                        attachTo: {
                            element: '#modal-content',
                            on: 'left'
                        },
                        beforeShowPromise: function() {
                            return new Promise(function(resolve, reject) {
                                let showAttempt = 0;
                                const subscriptionsModalShownInterval = setInterval(function() {
                                    showAttempt++;
                                    if (showAttempt > 12) { // after 3 seconds, we consider the modal opening failed
                                        clearInterval(subscriptionsModalShownInterval);
                                        Gofast.tour.data.fragments.subscriptionsModal = 0;
                                        Gofast.tour.storeData()
                                        reject();
                                    }
                                    if (!$('#gofastSubscriptionsTable').length) {
                                        return;
                                    }
                                    clearInterval(subscriptionsModalShownInterval);
                                    resolve();
                                }, 250);

                            });
                        },
                        when: {
                            cancel: Gofast.tour.boilerplates.baseCancel
                        },
                        buttons: [
                            {
                                text: "<i class=\"fas fa-step-forward\"></i>",
                                action: Gofast.tour.currentInstance.next,
                            },
                        ]
                    },
                    {
                        id: 'gofast-tour-subscriptions-filter-step',
                        title: Drupal.gft("title.tour.subscriptions.filter-step", {}, { context: "gofast_technical:gofast_tour" }),
                        text: Drupal.gft("text.tour.subscriptions.filter-step", {}, { context: "gofast_technical:gofast_tour" }),
                        attachTo: {
                            element: '#modal-content .datatable-head',
                            on: 'left'
                        },
                        when: {
                            cancel: Gofast.tour.boilerplates.baseCancel
                        },
                        buttons: Gofast.tour.boilerplates.baseButtons()
                    },
                    {
                        id: 'gofast-tour-subscriptions-frequency-step',
                        title: Drupal.gft("title.tour.subscriptions.frequency-step", {}, { context: "gofast_technical:gofast_tour" }),
                        text: Drupal.gft("text.tour.subscriptions.frequency-step", {}, { context: "gofast_technical:gofast_tour" }),
                        attachTo: {
                            element: '.shepherd-invisible-column',
                            on: 'left'
                        },
                        beforeShowPromise: async function() {
                            return new Promise(async function(resolve) {
                                Gofast.tour.sequences.addInvisibleColumnOverElements("[data-field='frequency']");
                                resolve();
                            });
                        },
                        when: {
                            cancel: function() {
                                Gofast.tour.sequences.removeInvisibleColumn();
                                Gofast.tour.boilerplates.baseCancel();
                            },
                        },
                        buttons: Gofast.tour.boilerplates.baseButtons()
                    },
                    {
                        id: 'gofast-tour-subscriptions-mass-actions-step',
                        title: Drupal.gft("title.tour.subscriptions.mass-actions-step", {}, { context: "gofast_technical:gofast_tour" }),
                        text: Drupal.gft("text.tour.subscriptions.mass-actions-step", {}, { context: "gofast_technical:gofast_tour" }),
                        attachTo: {
                            element: '#gofastSubscriptionsForm',
                            on: 'top'
                        },
                        beforeShowPromise: async function() {
                            return new Promise(async function(resolve) {
                                Gofast.tour.sequences.removeInvisibleColumn();
                                resolve();
                            });
                        },
                        when: {
                            cancel: Gofast.tour.boilerplates.baseCancel
                        },
                        buttons: [
                            {
                                text: "<i class=\"fas fa-step-backward\"></i>",
                                action: Gofast.tour.currentInstance.back,
                            },
                            {
                                text: "<i class=\"fas fa-check\"></i>",
                                classes: "btn btn-success",
                                action() {
                                    Gofast.tour.currentInstance.complete();
                                }  
                            }
                        ]
                    },
                ];
            },
            get documentInformationsTabFragment() {
                return [
                    {
                        id: 'gofast-tour-document-informations-step',
                        title: Drupal.gft("title.tour.document.informations-step", {}, { context: "gofast_technical:gofast_tour" }),
                        text: Drupal.gft("text.tour.document.informations-step", {}, { context: "gofast_technical:gofast_tour" }),
                        attachTo: {
                            element: '#document__infotab',
                            on: 'left'
                        },
                        beforeShowPromise: function() {
                            return new Promise(async function(resolve) {
                                await Gofast.tour.sequences.toggleDocSideContent();
                                if ($(".header_info_tab:visible").length && !$(".header_info_tab:visible").parent().hasClass("show")) {
                                    await Gofast.tour.sequences.actionsToAwait([
                                        () => Gofast.tour.components.fakeCursor.moveTo($(".header_info_tab:visible")[0], 500),
                                        () => $(".header_info_tab:visible").dropdown("toggle"),
                                        () => {},
                                    ], 500);
                                }
                                $("[href='#document__infotab']:visible").click();
                                await waitForElementVisibility("#document__infotab");
                                resolve();
                            });
                        },
                        when: {
                            cancel: Gofast.tour.boilerplates.baseCancel
                        },
                        buttons: [{
                            text: "<i class=\"fas fa-check\"></i>",
                            action: Gofast.tour.currentInstance.cancel,
                            classes: "btn btn-primary",
                        }]
                    },
                ];
            },
            get documentCommentsTabFragment() {
                return [
                    {
                        id: 'gofast-tour-document-comments-tab-step',
                        title: Drupal.gft("title.tour.document.comments-tab-step", {}, { context: "gofast_technical:gofast_tour" }),
                        text: Drupal.gft("text.tour.document.comments-tab-step", {}, { context: "gofast_technical:gofast_tour" }),
                        attachTo: {
                            element: "[href='#document__commentstab'].tour-target",
                            on: 'left'
                        },
                        beforeShowPromise: function() {
                            return new Promise(async function(resolve) {
                                await Gofast.tour.sequences.toggleDocSideContent();
                                await Gofast.tour.sequences.openDocMoreTabIfSelectorNotVisible("[href='#document__commentstab']");
                                $("[href='#document__commentstab']:visible").addClass("tour-target");
                                await waitForElementVisibility("#comments-container");
                                resolve();
                            });
                        },
                        when: {
                            hide: function() {
                                $("[href='#document__commentstab']:visible").removeClass("tour-target");
                            },
                            cancel: Gofast.tour.boilerplates.baseCancel
                        },
                        buttons: [
                            {
                                text: "<i class=\"fas fa-step-forward\"></i>",
                                action: Gofast.tour.currentInstance.next,
                            },
                        ]
                    },
                    {
                        id: 'gofast-tour-document-comments-step',
                        title: Drupal.gft("title.tour.document.comments-step", {}, { context: "gofast_technical:gofast_tour" }),
                        text: Drupal.gft("text.tour.document.comments-step", {}, { context: "gofast_technical:gofast_tour" }),
                        attachTo: {
                            element: '#comments-container',
                            on: 'left'
                        },
                        beforeShowPromise: function() {
                            return new Promise(async function(resolve) {
                                await Gofast.tour.sequences.toggleDocSideContent();
                                await Gofast.tour.sequences.openDocMoreTabIfSelectorNotVisible("[href='#document__commentstab']");
                                $("[href='#document__commentstab']:visible").click();
                                await waitForElementVisibility("#comments-container");
                                resolve();
                            });
                        },
                        when: {
                            cancel: Gofast.tour.boilerplates.baseCancel
                        },
                        buttons: Gofast.tour.boilerplates.baseButtons()
                    },
                    {
                        id: 'gofast-tour-document-comments-modal-step',
                        title: Drupal.gft("title.tour.document.comments-modal-step", {}, { context: "gofast_technical:gofast_tour" }),
                        text: Drupal.gft("text.tour.document.comments-modal-step", {}, { context: "gofast_technical:gofast_tour" }),
                        attachTo: {
                            element: '#edit-comment-body',
                            on: 'left'
                        },
                        beforeShowPromise: function() {
                            return new Promise(async function(resolve) {
                                await Gofast.tour.sequences.toggleDocSideContent();
                                await Gofast.tour.sequences.openDocMoreTabIfSelectorNotVisible("[href='#document__commentstab']");
                                $("[href='#document__commentstab']:visible").click();
                                await Gofast.tour.components.fakeCursor.moveTo(".gofastAddComment > a", 500);
                                $(".gofastAddComment > a").click()
                                await waitForElementVisibility("#edit-comment-body");
                                resolve();
                            });
                        },
                        when: {
                            hide: function() {
                                $(".modal-header > .close").click();
                            },
                            cancel: Gofast.tour.boilerplates.baseCancel,
                        },
                        buttons: [
                            {
                                text: "<i class=\"fas fa-step-backward\"></i>",
                                action: Gofast.tour.currentInstance.back,
                            },
                            {
                                text: "<i class=\"fas fa-check\"></i>",
                                classes: "btn btn-success",
                                action() {
                                    Gofast.tour.components.fakeCursor.destroy();
                                    $(".modal-header > .close").click();
                                    Gofast.tour.currentInstance.complete();
                                }  
                            }
                        ]
                    },
                ];
            },
            get chatSideContentFragment() {
                return [
                    {
                        id: 'gofast-tour-chat-sidecontent-step',
                        title: Drupal.gft("title.tour.chat.sidecontent-step", {}, { context: "gofast_technical:gofast_tour" }),
                        text: Drupal.gft("text.tour.chat.sidecontent-step", {}, { context: "gofast_technical:gofast_tour" }),
                        attachTo: {
                            element: '#conteneurIframe',
                            on: 'left'
                        },
                        beforeShowPromise: function () {
                            return new Promise(async function (resolve) {
                                if ($(".block-gofast-riot > #conteneurIframe").width() != "480") {
                                    $("#animateRiot").click();
                                }
                                const expandChatInterval = setInterval(() => {
                                    if ($(".block-gofast-riot > #conteneurIframe").width() == "480") {
                                        clearInterval(expandChatInterval)
                                        resolve();
                                    }
                                }, 50)
                            });
                        },
                        when: {
                            cancel: Gofast.tour.boilerplates.baseCancel
                        },
                        buttons: [{
                            text: "<i class=\"fas fa-check\"></i>",
                            classes: "btn btn-success",
                            action() {
                                if ($(".block-gofast-riot > #conteneurIframe").width() == "480") {
                                    $("#animateRiot").click();
                                }
                                Gofast.tour.currentInstance.complete();
                            }  
                        }]
                    },
                ];
            },
            get namingRuleInputFragment() {
                return [
                    {
                        id: 'gofast-tour-namingrule-input-step',
                        title: Drupal.gft("title.tour.namingrule.input-step", {}, { context: "gofast_technical:gofast_tour" }),
                        text: Drupal.gft("text.tour.namingrule.input-step", {}, { context: "gofast_technical:gofast_tour" }),
                        attachTo: {
                            element: '#gofastCategoriesTable tbody',
                            on: 'top'
                        },
                        when: {
                            cancel: Gofast.tour.boilerplates.baseCancel
                        },
                        buttons: [{
                            text: "<i class=\"fas fa-check\"></i>",
                            classes: "btn btn-success",
                            action() {
                                Gofast.tour.currentInstance.complete();
                            }  
                        }]
                    },
                ];
            },
            // defines steps of tour of profile function
            get profile() {
                return [
                    {
                        id: 'gofast-tour-profile-information-step',
                        title: Drupal.gft("title.tour.profile.information-step", {}, { context: "gofast_technical:gofast_tour" }),
                        text: Drupal.gft("text.tour.profile.information-step", {}, { context: 'gofast_technical:gofast_tour' }),
                        attachTo: {
                            element: '.GofastUserProfile__info',
                            on: 'right'
                        },
                        when: {
                            cancel: Gofast.tour.boilerplates.baseCancel
                        },
                        buttons: [
                            {
                                text: "<i class=\"fas fa-step-forward\"></i>",
                                action: Gofast.tour.currentInstance.next,
                            }
                        ]
                    },
                    {
                        id: 'gofast-tour-profile-rights-step',
                        title: Drupal.gft("title.tour.profile.rights-step", {}, { context: "gofast_technical:gofast_tour" }),
                        text: Drupal.gft("text.tour.profile.rights-step", {}, { context: 'gofast_technical:gofast_tour' }),
                        attachTo: {
                            element: '.GofastUserProfile__roleinfo',
                            on: 'bottom'
                        },
                        when: {
                            cancel: Gofast.tour.boilerplates.baseCancel
                        },
                        buttons: Gofast.tour.boilerplates.baseButtons()
                    },
                    {
                        id: 'gofast-tour-profile-settings-step',
                        title: Drupal.gft("title.tour.profile.settings-step", {}, { context: "gofast_technical:gofast_tour" }),
                        text: Drupal.gft("text.tour.profile.settings-step", {}, { context: "gofast_technical:gofast_tour" }),
                        attachTo: {
                            element: '.profile-account-settings',
                            on: 'bottom'
                        },
                        when: {
                            show: function() {
                                Gofast.tour.sequences.actionsToAwait([
                                    () => Gofast.tour.components.fakeCursor.moveTo(".profile-account-settings"),
                                    () => {},
                                    () => Gofast.tour.components.fakeCursor.hide(),
                                ], 1000);
                            },
                            cancel: Gofast.tour.boilerplates.baseCancel
                        },
                        buttons: Gofast.tour.boilerplates.baseButtons()
                    },
                    {
                        id: 'gofast-tour-profile-settings-modal-step',
                        title: Drupal.gft("title.tour.profile.modal-step", {}, { context: "gofast_technical:gofast_tour" }),
                        text: Drupal.gft("text.tour.profile.modal-step", {}, { context: "gofast_technical:gofast_tour" }),
                        beforeShowPromise: function() {
                            return new Promise(async function(resolve) {
                                $(".profile-account-settings > a").click();
                                await waitForElementVisibility("#user-profile-form");
                                resolve();
                            });
                        },
                        when: {
                            hide: function() {
                                $(".modal-header > .close").click();
                            },
                            cancel: Gofast.tour.boilerplates.baseCancel,
                        },
                        buttons: [
                            {
                                text: "<i class=\"fas fa-step-backward\"></i>",
                                action: Gofast.tour.currentInstance.back,
                            },
                            {
                                text: "<i class=\"fas fa-check\"></i>",
                                classes: "btn btn-success",
                                action() {
                                    Gofast.tour.components.fakeCursor.destroy();
                                    $("#gofast_over_content").removeClass('tour-processed');
                                    $(".modal-header > .close").click();
                                    Gofast.tour.currentInstance.complete();
                                }  
                            }
                        ]
                    },
                ];
            },
            get essentialTour() {
                return [
                    {
                        id: 'gofast-tour-home-menu-step',
                        title: Drupal.gft("title.tour.home.menu-step", {}, { context: "gofast_technical:gofast_tour" }),
                        text: Drupal.gft("text.tour.home.menu-step", {}, { context: "gofast_technical:gofast_tour" }),
                        attachTo: {
                            element: '#gofastMenuTopbarCreateMenuItem > .menu-submenu',
                            on: 'bottom'
                        },
                        when: {
                            show: function() {
                                $("#gofastMenuTopbarCreateMenuItem").first().addClass("menu-item-hover");
                                $("#gofastMenuTopbarCreateMenuItem .btn").first().addClass("focus");
                                const $menuList = $("#gofastMenuTopbarCreateMenuItem > .menu-submenu > .menu-subnav").first();
                                Gofast.tour.sequences.showMenuItems($menuList);
                                Gofast.tour._actionToWait = () => Gofast.tour.components.fakeCursor.moveTo("#gofastMenuTopbarCreateMenuItem > .menu-submenu > .menu-subnav > li:nth-child(1) > a");
                            },
                            hide: function() {
                                $("#gofastMenuTopbarCreateMenuItem").first().removeClass("menu-item-hover");
                                $("#gofastMenuTopbarCreateMenuItem .btn").first().removeClass("focus");
                            },
                            cancel: function() {
                                Gofast.tour.components.fakeCursor.destroy();
                                $("#gofastMenuTopbarCreateMenuItem").first().removeClass("menu-item-hover");
                                $("#gofastMenuTopbarCreateMenuItem .btn").first().removeClass("focus");
                                $("#gofast_over_content").removeClass('tour-processed');
                            }
                        },
                        buttons: [
                            {
                                text: "<i class=\"fas fa-step-forward\"></i>",
                                action: Gofast.tour.currentInstance.next,
                            }
                        ]
                    },
                    {
                        id: 'gofast-tour-home-spaces-menu-step',
                        title: Drupal.gft("title.tour.home.spaces-step", {}, { context: "gofast_technical:gofast_tour" }),
                        text: Drupal.gft("text.tour.home.spaces-step", {}, { context: "gofast_technical:gofast_tour" }),
                        attachTo: {
                            element: '#gf-spaces-menu > .menu-submenu',
                            on: 'bottom'
                        },
                        when: {
                            show: function() {
                                $("#gf-spaces-menu").first().addClass("menu-item-hover");
                                $("#gf-spaces-menu .btn").first().addClass("focus");
                                const $menuList = $("#gf-spaces-menu > .menu-submenu > .menu-subnav > .menu-content > .menu-item > .menu-inner").first();
                                
                                Gofast.tour.sequences.showSpacesMenuItems($menuList);
                            },
                            hide: function() {
                                $("#gf-spaces-menu").first().removeClass("menu-item-hover");
                                $("#gf-spaces-menu .btn").first().removeClass("focus");
                            },
                            cancel: function() {
                                Gofast.tour.components.fakeCursor.destroy();
                                $("#gf-spaces-menu").first().removeClass("menu-item-hover");
                                $("#gf-spaces-menu .btn").first().removeClass("focus");
                                $("#gofast_over_content").removeClass('tour-processed');
                            }
                        },
                        buttons: Gofast.tour.boilerplates.baseButtons()
                    },
                    {
                        id: 'gofast-tour-home-bookmarks-menu-step',
                        title: Drupal.gft("title.tour.home.bookmarks-step", {}, { context: "gofast_technical:gofast_tour" }),
                        text: Drupal.gft("text.tour.home.bookmarks-step", {}, { context: "gofast_technical:gofast_tour" }),
                        attachTo: {
                            element: '#gofast_topbar_flag_bookmarks > .menu-submenu',
                            on: 'right'
                        },
                        when: {
                            show: function() {
                                $("#gofast_topbar_flag_bookmarks").first().addClass("menu-item-hover");
                                $("#gofast_topbar_flag_bookmarks .btn").first().addClass("focus");
                                setTimeout(()=>{
                                    $("#gofast_topbar_flag_bookmarks_block > .nav > .nav-item > a").click();
                                },1000);
                            },
                            cancel: function() {
                                Gofast.tour.components.fakeCursor.destroy();
                                $("#gofast_topbar_flag_bookmarks").first().removeClass("gofast-menu-active menu-item-hover");
                                $("#gofast_topbar_flag_bookmarks .btn").first().removeClass("focus");
                                $("#gofast_over_content").removeClass('tour-processed');
                            }
                        },
                        buttons: [
                            {
                                text: "<i class=\"fas fa-step-backward\"></i>",
                                action: Gofast.tour.currentInstance.back,
                            },
                            {
                                text: "<i class=\"fas fa-step-forward\"></i>",
                                action() {
                                    $("#gofast_topbar_flag_bookmarks").first().removeClass("gofast-menu-active menu-item-hover");
                                    $("#gofast_topbar_flag_bookmarks .btn").first().removeClass("focus");
                                    Gofast.tour.currentInstance.next();
                                }
                            }
                        ]
                    },
                    {
                        id: 'gofast-tour-home-search-step',
                        title: Drupal.gft("title.tour.home.search-step", {}, { context: "gofast_technical:gofast_tour" }),
                        text: Drupal.gft("text.tour.home.search-step", {}, { context: "gofast_technical:gofast_tour" }),
                        attachTo: {
                            element: '#search-block-form',
                            on: 'bottom'
                        },
                        when: {
                            show: function() {
                                Gofast.tour.sequences.simulateSearchTyping();
                            },
                            hide: function() {
                                $("[name='search_block_form']").val("");
                            },
                            cancel: function() {
                                Gofast.tour.components.fakeCursor.destroy();
                                $("[name='search_block_form']").val("");
                                $("#gofast_over_content").removeClass('tour-processed');
                            }
                        },
                        buttons: Gofast.tour.boilerplates.baseButtons()
                    },
                    {
                        id: 'gofast-tour-home-profile-step',
                        title: Drupal.gft("title.tour.home.profile-step", {}, { context: "gofast_technical:gofast_tour" }),
                        text: Drupal.gft("text.tour.home.profile-step", {}, { context: "gofast_technical:gofast_tour" }),
                        attachTo: {
                            element: '#gf-profile-menu > .menu-submenu',
                            on: 'left'
                        },
                        when: {
                            show: function() {
                                $("#gf-profile-menu").addClass("menu-item-hover");
                                const $menuList = $("#gf-profile-menu > .menu-submenu > .menu-subnav").first();
                                Gofast.tour.sequences.showProfileMenuItems($menuList);
                            },
                            hide: function(){
                                $("#gf-profile-menu").removeClass("menu-item-hover");
                            },
                            cancel: function() {
                                Gofast.tour.components.fakeCursor.destroy();
                                $("#gf-profile-menu").removeClass("menu-item-hover");
                                $("#gofast_over_content").removeClass('tour-processed');
                            }
                        },
                        buttons: Gofast.tour.boilerplates.baseButtons()
                    },
                    {
                        id: 'gofast-tour-home-left-menu-step',
                        title: Drupal.gft("title.tour.home.left-menu-step", {}, { context: "gofast_technical:gofast_tour" }),
                        text: Drupal.gft("text.tour.home.left-menu-step", {}, { context: "gofast_technical:gofast_tour" }),
                        attachTo: {
                            element: '#gofastCollaborativeSpacesMenuItem',
                            on: 'right'
                        },
                        beforeShowPromise: function() {
                            return new Promise(async (resolve) => {
                                Gofast.tour.sequences.actionsToAwait([
                                    () => $(".aside-minimize").addClass("aside-minimize-hover"),
                                    () => $("#gofastCollaborativeSpacesMenuItem .menu-link").addClass("hover"),
                                    () => resolve()
                                ], 500);
                            });

                        },
                        when: {
                            hide: function() {
                                $(".aside-minimize").removeClass("aside-minimize-hover");
                                $("#gofastCollaborativeSpacesMenuItem .menu-link").removeClass("hover");
                            },
                            cancel: function() {
                                Gofast.tour.components.fakeCursor.destroy();
                                $(".aside-minimize").removeClass("aside-minimize-hover");
                                $("#gofastCollaborativeSpacesMenuItem .menu-link").removeClass("hover");
                                $("#gofast_over_content").removeClass('tour-processed');
                            }
                        },
                        buttons: Gofast.tour.boilerplates.baseButtons()
                    },
                    {
                        id: 'gofast-tour-home-button-step',
                        title: Drupal.gft("title.tour.home.home-button-step", {}, { context: "gofast_technical:gofast_tour" }),
                        text: Drupal.gft("text.tour.home.home-button-step", {}, { context: "gofast_technical:gofast_tour" }),
                        attachTo: {
                            element: '#gf-home-button',
                            on: 'bottom'
                        },
                        when: {
                            cancel: Gofast.tour.boilerplates.baseCancel
                        },
                        buttons: Gofast.tour.boilerplates.baseButtons()
                    }
                ]
            },
            // mobile and essential specific steps
            get essentialOptional() {
                return {
                    mobileMenuStep: {
                        id: 'gofast-tour-home-mobile-menu-step',
                        title: Drupal.gft("title.tour.home.mobile-menu-step", {}, { context: "gofast_technical:gofast_tour" }),
                        text: Drupal.gft("text.tour.home.mobile-menu-step", {}, { context: "gofast_technical:gofast_tour" }),
                        attachTo: {
                            element: '.header-mobile .burger-icon',
                            on: 'bottom'
                        },
                        beforeShowPromise: function() {
                            return new Promise(async (resolve) => {
                                Gofast.tour.sequences.actionsToAwait([
                                    () => $(".header-mobile .burger-icon").click(),
                                    () => $(".header-mobile .burger-icon").addClass("hover"),
                                    () => resolve()
                                ], 500);
                            });

                        },
                        when: {
                            hide: function() {
                                $(".header-mobile .burger-icon").removeClass("hover");
                            },
                            cancel: function() {
                                Gofast.tour.components.fakeCursor.destroy();
                                $(".header-mobile .burger-icon").removeClass("hover");
                                $("#gofast_over_content").removeClass('tour-processed');
                            }
                        },
                        buttons: Gofast.tour.boilerplates.baseButtons()
                    },
                    mobileBrowserMenuStep: {
                        id: 'gofast-tour-home-mobile-browser-menu-step',
                        title: Drupal.gft("title.tour.home.mobile-browser-menu-step", {}, { context: "gofast_technical:gofast_tour" }),
                        text: Drupal.gft("text.tour.home.mobile-browser-menu-step", {}, { context: "gofast_technical:gofast_tour" }),
                        attachTo: {
                            element: '#gofastCollaborativeSpacesMenuItem',
                            on: 'right'
                        },
                        beforeShowPromise: function() {
                            return new Promise(async (resolve) => {
                                Gofast.tour.sequences.actionsToAwait([
                                    () => {
                                        if (!($(".aside-overlay").length)) {
                                            $(".header-mobile .burger-icon").click();
                                        }
                                    },
                                    () => $("#gofastCollaborativeSpacesMenuItem .menu-link").addClass("hover"),
                                    () => resolve()
                                ], 500);
                            });

                        },
                        when: {
                            hide: function() {
                                $("#gofastCollaborativeSpacesMenuItem .menu-link").removeClass("hover");
                            },
                            cancel: function() {
                                Gofast.tour.components.fakeCursor.destroy();
                                $("#gofastCollaborativeSpacesMenuItem .menu-link").removeClass("hover");
                                $("#gofast_over_content").removeClass('tour-processed');
                            }
                        },
                        buttons: Gofast.tour.boilerplates.baseButtons()
                    },
                    mobileHomeStep: {
                        id: 'gofast-tour-home-mobile-home-step',
                        title: Drupal.gft("title.tour.home.mobile-home-step", {}, { context: "gofast_technical:gofast_tour" }),
                        text: Drupal.gft("text.tour.home.mobile-home-step", {}, { context: "gofast_technical:gofast_tour" }),
                        attachTo: {
                            element: '#gf-mobile-home-button',
                            on: 'bottom'
                        },
                        beforeShowPromise: function() {
                            return new Promise(async (resolve) => {
                                Gofast.tour.sequences.actionsToAwait([
                                    () => $(".aside-overlay").click(),
                                    () => resolve()
                                ], 500);
                            });

                        },
                        when: {
                            cancel: Gofast.tour.boilerplates.baseCancel
                        },
                        buttons: Gofast.tour.boilerplates.baseButtons()
                    },
                };
            },
            get simplifiedEssentialTour() {
                return [
                    {
                        id: 'gofast-tour-simplified-home-dashboard-step',
                        title: Drupal.gft("title.tour.simplified-home.dashboard-step", {}, { context: "gofast_technical:gofast_tour" }),
                        text: Drupal.gft("text.tour.simplified-home.dashboard-step", {}, { context: "gofast_technical:gofast_tour" }),
                        attachTo: {
                            element: '#topbarNavDashboardButton',
                            on: 'bottom'
                        },
                        when: {
                            show: async function() {
                                //let the fake cursor follow the element and click on it
                                await Gofast.tour.components.fakeCursor.moveTo("#topbarNavDashboardButton");
                                $("#topbarNavDashboardButton").click();
                            },
                            hide: function() {
                                $("#topbarNavDashboardButton").first().removeClass("menu-item-hover");
                                $("#gofastMenuTopbarCreateMenuItem .btn").first().removeClass("focus");
                            },
                            cancel: Gofast.tour.boilerplates.essentialTourLastStepOnCancel
                        },
                        buttons: [
                            {
                                text: "<i class=\"fas fa-step-forward\"></i>",
                                action: Gofast.tour.currentInstance.next,
                            }
                        ]
                    },
                    {
                        id: 'gofast-tour-simplified-home-filebrowser-step',
                        title: Drupal.gft("title.tour.simplified-home.filebrowser-step", {}, { context: "gofast_technical:gofast_tour" }),
                        text: Drupal.gft("text.tour.simplified-home.filebrowser-step", {}, { context: "gofast_technical:gofast_tour" }),
                        attachTo: {
                            element: '#topbarNavFileBrowserButton',
                            on: 'right'
                        },
                        when: {
                            show: async function() {
                                //let the fake cursor follow the element and click on it
                                await Gofast.tour.components.fakeCursor.moveTo("#topbarNavFileBrowserButton");
                                $("#topbarNavFileBrowserButton").click();
                            },
                            hide: function() {
                                $("#topbarNavFileBrowserButton").first().removeClass("menu-item-hover");
                                $("#gofastMenuTopbarCreateMenuItem .btn").first().removeClass("focus");
                            },
                            cancel: Gofast.tour.boilerplates.essentialTourLastStepOnCancel
                        },
                        buttons: Gofast.tour.boilerplates.baseButtons()
                    },
                    {
                        id: 'gofast-tour-home-search-step',
                        title: Drupal.gft("title.tour.home.search-step", {}, { context: "gofast_technical:gofast_tour" }),
                        text: Drupal.gft("text.tour.home.search-step", {}, { context: "gofast_technical:gofast_tour" }),
                        attachTo: {
                            element: '#search-block-form',
                            on: 'bottom'
                        },
                        when: {
                            show: async function() {
                                await Gofast.tour.components.fakeCursor.moveTo("[name='search_block_form']");
                                $("[name='search_block_form']").click();
                                Gofast.tour.sequences.simulateSearchTyping();
                            },
                            hide: function() {
                                $("[name='search_block_form']").val("");
                            },
                            cancel: function() {
                                Gofast.tour.components.fakeCursor.destroy();
                                $("[name='search_block_form']").val("");
                                $("#gofast_over_content").removeClass('tour-processed');
                                Gofast.tour.boilerplates.essentialTourLastStepOnCancel();
                            }
                        },
                        buttons: Gofast.tour.boilerplates.baseButtons()
                    },
                    {
                        id: 'gofast-tour-simplified-home-history-step',
                        title: Drupal.gft("title.tour.simplified-home.history-step", {}, { context: "gofast_technical:gofast_tour" }),
                        text: Drupal.gft("text.tour.simplified-home.history-step", {}, { context: "gofast_technical:gofast_tour" }),
                        attachTo: {
                            element: '#recenlty_read_block_menu > a',
                            on: 'right'
                        },
                        when: {
                            show: async function() {
                                //let the fake cursor follow the element and click on it
                                $("#recenlty_read_block_menu").addClass("menu-item-hover");
                                await Gofast.tour.components.fakeCursor.moveTo("#recenlty_read_block_menu");
                                $("#recenlty_read_block_menu > a").css({
                                    "background-color": "#F3F6F9",
                                    "border-color":" transparent"
                                });
                                $("#recenlty_read_block_menu > a > i").attr('style','color: #3699FF !important');

                            },
                            hide: function() {
                                $("#recenlty_read_block_menu").first().removeClass("menu-item-hover");
                                $("#gofastMenuTopbarCreateMenuItem .btn").first().removeClass("focus");
                                $("#recenlty_read_block_menu > a").removeAttr('style');
                                $("#recenlty_read_block_menu > a > i").attr('style','');
                            },
                            cancel: Gofast.tour.boilerplates.essentialTourLastStepOnCancel
                        },
                        buttons: Gofast.tour.boilerplates.baseButtons()
                    },
                    {
                        id: 'gofast-tour-simplified-home-activity-step',
                        title: Drupal.gft("title.tour.simplified-home.activity-step", {}, { context: "gofast_technical:gofast_tour" }),
                        text: Drupal.gft("text.tour.simplified-home.activity-step", {}, { context: "gofast_technical:gofast_tour" }),
                        attachTo: {
                            element: '#topbarNavActivityFeedButton',
                            on: 'bottom'
                        },
                        when: {
                            show: async function() {
                                //let the fake cursor follow the element and click on it
                                await Gofast.tour.components.fakeCursor.moveTo("#topbarNavActivityFeedButton");
                                $("#topbarNavActivityFeedButton").click();
                            },
                            hide: function() {
                                $("#topbarNavActivityFeedButton").first().removeClass("menu-item-hover");
                                $("#gofastMenuTopbarCreateMenuItem .btn").first().removeClass("focus");
                            },
                            cancel: Gofast.tour.boilerplates.essentialTourLastStepOnCancel
                        },
                        buttons: Gofast.tour.boilerplates.baseButtons()
                    },
                    {
                        id: 'gofast-tour-simplified-home-workflows-step',
                        title: Drupal.gft("title.tour.simplified-home.workflows-step", {}, { context: "gofast_technical:gofast_tour" }),
                        text: Drupal.gft("text.tour.simplified-home.workflows-step", {}, { context: "gofast_technical:gofast_tour" }),
                        attachTo: {
                            element: '#gofast_block_delta-gofast_workflows_light_dashboard-gofast_workflows > a',
                            on: 'bottom'
                        },
                        when: {
                            show: async function() {
                                //let the fake cursor follow the element and click on it
                                await Gofast.tour.components.fakeCursor.moveTo("#gofast_block_delta-gofast_workflows_light_dashboard-gofast_workflows");
                                $("#gofast_block_delta-gofast_workflows_light_dashboard-gofast_workflows").click();
                                
                                $("#gofast_block_delta-gofast_workflows_light_dashboard-gofast_workflows > a").css({
                                    "background-color": "#F3F6F9",
                                    "border-color":" transparent"
                                });
                                $("#gofast_block_delta-gofast_workflows_light_dashboard-gofast_workflows > a > i").attr('style','color: #3699FF !important');
                            },
                            hide: function() {
                                $("#gofast_block_delta-gofast_workflows_light_dashboard-gofast_workflows").first().removeClass("menu-item-hover");
                                $("#gofastMenuTopbarCreateMenuItem .btn").first().removeClass("focus");
                                $("#gofast_block_delta-gofast_workflows_light_dashboard-gofast_workflows > a").removeAttr('style');
                                $("#gofast_block_delta-gofast_workflows_light_dashboard-gofast_workflows > a > i").removeAttr('style');
                            },
                            cancel: Gofast.tour.boilerplates.essentialTourLastStepOnCancel
                        },
                        buttons: Gofast.tour.boilerplates.baseButtons()
                    },
                    {
                        id: 'gofast-tour-simplified-home-chat-step',
                        title: Drupal.gft("title.tour.simplified-home.chat-step", {}, { context: "gofast_technical:gofast_tour" }),
                        text: Drupal.gft("text.tour.simplified-home.chat-step", {}, { context: "gofast_technical:gofast_tour" }),
                        attachTo: {
                            element: '#animateRiot',
                            on: 'left'
                        },
                        when: {
                            show: async function() {
                                //let the fake cursor follow the element and click on it
                                await Gofast.tour.components.fakeCursor.moveTo("#animateRiot");
                                $("#animateRiot").click();
                            },
                            hide: function() {
                                $("#animateRiot").click();
                                $("#gofastMenuTopbarCreateMenuItem .btn").first().removeClass("focus");
                            },
                            cancel: Gofast.tour.boilerplates.essentialTourLastStepOnCancel
                        },
                        buttons: Gofast.tour.boilerplates.baseButtons()
                    },
                    {
                        id: 'gofast-tour-simplified-home-profile-step',
                        title: Drupal.gft("title.tour.simplified-home.profile-step", {}, { context: "gofast_technical:gofast_tour" }),
                        text: Drupal.gft("text.tour.simplified-home.profile-step", {}, { context: "gofast_technical:gofast_tour" }),
                        attachTo: {
                            element: '#gf-profile-menu',
                            on: 'left'
                        },
                        when: {
                            show: async function() {
                                //let the fake cursor follow the element and click on it
                                await Gofast.tour.components.fakeCursor.moveTo("#gf-profile-menu");
                                $("#gf-profile-menu").addClass("menu-item-hover");
                            },
                            hide: function() {
                                $("#gf-profile-menu").first().removeClass("menu-item-hover");
                                $("#gofastMenuTopbarCreateMenuItem .btn").first().removeClass("focus");
                            },
                            cancel: Gofast.tour.boilerplates.essentialTourLastStepOnCancel
                        },
                        buttons: Gofast.tour.boilerplates.baseButtons()
                    },
                    Gofast.tour.descriptions.simplifiedEssentialTourLastStep
                ];
            },
            get simplifiedEssentialTourLastStep() {
                return {
                    id: 'gofast-tour-simplified-home.last-step',
                    title: Drupal.gft("title.tour.simplified-home.last-step", {}, { context: "gofast_technical:gofast_tour" }),
                    text: Drupal.gft("text.tour.simplified-home.last-step", {}, { context: "gofast_technical:gofast_tour" }),
                    attachTo: {
                        element: '#gofastAboutMenu',
                        on: 'left'
                    },
                    when: {
                        cancel: Gofast.tour.boilerplates.baseCancel
                    },
                    buttons: [
                        {
                            text: "<i class=\"fas fa-check\"></i>",
                            classes: "btn btn-success",
                            async action() {
                                $("#gofast_over_content").removeClass('tour-processed');
                                await Gofast.tour.sequences.actionsToAwait([
                                    () => Gofast.tour.components.fakeCursor.destroy(),
                                ], 1000);
                                Gofast.tour.currentInstance.complete();
                            }
                        }
                    ]
                };
            },
            get activity() {
                return [
                    {
                        id: 'gofast-tour-activity-first-step',
                        title: Drupal.gft("title.tour.activity.first-step", {}, { context: "gofast_technical:gofast_tour" }),
                        text: Drupal.gft("text.tour.activity.first-step", {}, { context: "gofast_technical:gofast_tour" }),
                        attachTo: {
                            element: getVersion() == "simplified" ? '#activity-feed' : '#activity-feed-container',
                            on: getVersion() == "simplified" ? 'left' : 'right',
                        },
                        // wait for the activity table to be loaded before displaying the step
                        beforeShowPromise: function() {
                            return new Promise(function(resolve, reject) {
                                let showAttempt = 0;
                                const activityFeedProcessedInterval = setInterval(function() {
                                    showAttempt++;
                                    if (showAttempt > 12) { // after 3 seconds, we consider the navigation to /activity was a "passing-by" navigation
                                        clearInterval(activityFeedProcessedInterval);
                                        Gofast.tour.data.pages.done.activity = 0;
                                        Gofast.tour.storeData()
                                        reject();
                                    }
                                    if ($('#activity-feed-table tbody tr').length <= 1) {
                                        return;
                                    }
                                    clearInterval(activityFeedProcessedInterval);
                                    resolve();
                                }, 250);

                            });
                        },
                        when: {
                          cancel: Gofast.tour.boilerplates.baseCancel
                        },
                        buttons: [
                            getVersion() == "simplified" || getVersion() == "mobile"
                                ? {
                                    text: "<i class=\"fas fa-check\"></i>",
                                    classes: "btn btn-success",
                                    action() {
                                        Gofast.tour.components.fakeCursor.destroy();
                                        $("#gofast_over_content").removeClass('tour-processed');
                                        Gofast.tour.currentInstance.complete();
                                    }  
                                }
                                : {
                                    text: "<i class=\"fas fa-step-forward\"></i>",
                                    action: Gofast.tour.currentInstance.next,
                                }
                        ]
                    },
                    {
                        id: 'gofast-tour-activity-filters-step',
                        title: Drupal.gft("title.tour.activity.filters-step", {}, { context: "gofast_technical:gofast_tour" }),
                        text: Drupal.gft("text.tour.activity.filters-step", {}, { context: "gofast_technical:gofast_tour" }),
                        attachTo: {
                            element: '#gofastActivityStreamFiltersCard',
                            on: 'left'
                        },
                        when: {
                            show: function() {
                                Gofast.tour.sequences.actionsToAwait([
                                        () => Gofast.tour.components.fakeCursor.moveTo($("#gofast_activity_filter_accordion .card-title")[0], 600),
                                        () => $("#gofast_activity_filter_accordion .card-title")[0].click(),
                                        () => Gofast.tour.components.fakeCursor.moveTo($("#gofast_activity_filter_accordion .card-title")[1], 600),
                                        () => $("#gofast_activity_filter_accordion .card-title")[1].click(),
                                        () => Gofast.tour.components.fakeCursor.moveTo($("#gofast_activity_filter_accordion .card-title")[2], 600),
                                        () => $("#gofast_activity_filter_accordion .card-title")[2].click(),
                                        () => Gofast.tour.components.fakeCursor.moveTo($("#gofastActivityStreamFiltersCard .stream_filter_switch.processed")[1], 600),
                                        () => $("#gofastActivityStreamFiltersCard .stream_filter_switch.processed")[1].click(),
                                        () => Gofast.tour.components.fakeCursor.moveTo($("#gofastActivityStreamFiltersCard .stream_filter_switch.processed")[2], 600),
                                        () => $("#gofastActivityStreamFiltersCard .stream_filter_switch.processed")[2].click(),
                                        () => Gofast.tour.components.fakeCursor.moveTo($("#gofastActivityStreamFiltersCard .stream_filter_switch.processed")[3], 600),
                                        () => $("#gofastActivityStreamFiltersCard .stream_filter_switch.processed")[3].click(),
                                    ]
                                    , 600
                                ).then(() => {
                                    setTimeout(()=>{
                                        $("#gofastActivityStreamFiltersCard .stream_filter_switch.processed")[1].click();
                                        $("#gofastActivityStreamFiltersCard .stream_filter_switch.processed")[2].click();
                                        $("#gofastActivityStreamFiltersCard .stream_filter_switch.processed")[3].click();
                                    }, 600);
                                });
                            },
                            cancel: Gofast.tour.boilerplates.baseCancel
                        },
                        buttons: [
                            {
                                text: "<i class=\"fas fa-step-backward\"></i>",
                                action: Gofast.tour.currentInstance.back,
                            },
                            {
                                text: "<i class=\"fas fa-check\"></i>",
                                classes: "btn btn-success",
                                action() {
                                    Gofast.tour.components.fakeCursor.destroy();
                                    $("#gofast_over_content").removeClass('tour-processed');
                                    Gofast.tour.currentInstance.complete();
                                }  
                            }
                        ],

                    },
                ];
            },
            get dashboard() {
                return [
                    {
                        id: 'gofast-tour-dashboard-private-step',
                        title: Drupal.gft("title.tour.dashboard.private-step", {}, { context: "gofast_technical:gofast_tour" }),
                        text: Drupal.gft("text.tour.dashboard.private-step", {}, { context: "gofast_technical:gofast_tour" }),
                        attachTo: {
                            element: '#dashboard_block_private_space',
                            on: 'right'
                        },
                        // wait for the dashboard to be loaded before displaying the first step
                        beforeShowPromise: function() {
                            return new Promise(function(resolve) {
                                const dashboardProcessedInterval = setInterval(function() {
                                    if (!$('#dashboard_block_private_space').length) {
                                        return;
                                    }
                                    clearInterval(dashboardProcessedInterval);
                                    resolve();
                                }, 250);

                            });
                        },
                        when: {
                          cancel: Gofast.tour.boilerplates.baseCancel
                        },
                        buttons: [
                            {
                                text: "<i class=\"fas fa-step-forward\"></i>",
                                action: Gofast.tour.currentInstance.next,
                            }
                        ]
                    },
                    {
                        id: 'gofast-tour-dashboard-calendar-step',
                        title: Drupal.gft("title.tour.dashboard.calendar-step", {}, { context: "gofast_technical:gofast_tour" }),
                        text: Drupal.gft("text.tour.dashboard.calendar-step", {}, { context: "gofast_technical:gofast_tour" }),
                        attachTo: {
                            element: $('#dashboard_block_calendar').parent().get(0),
                            on: 'left'
                        },
                        when: {
                          cancel: Gofast.tour.boilerplates.baseCancel
                        },
                        buttons: Gofast.tour.boilerplates.baseButtons()
                    },
                    {
                        id: 'gofast-tour-dashboard-calendar-add-step',
                        title: Drupal.gft("title.tour.dashboard.calendar-add-step", {}, { context: "gofast_technical:gofast_tour" }),
                        text: Drupal.gft("text.tour.dashboard.calendar-add-step", {}, { context: "gofast_technical:gofast_tour" }),
                        attachTo: {
                            element: '#dashboard_toolbar_calendar',
                            on: 'left'
                        },
                        when: {
                          show: async function() {
                            await Gofast.tour.sequences.actionsToAwait([
                                () => Gofast.tour.components.fakeCursor.moveTo($("#dashboard_toolbar_calendar > a")[0], 500),
                                () => $("#dashboard_toolbar_calendar #dropdown-rapid").dropdown("show"),
                            ], 700);
                          },
                          cancel: Gofast.tour.boilerplates.baseCancel
                        },
                        buttons: Gofast.tour.boilerplates.baseButtons()
                    },
                    {
                        id: 'gofast-tour-dashboard-tasks-step',
                        title: Drupal.gft("title.tour.dashboard.tasks-step", {}, { context: "gofast_technical:gofast_tour" }),
                        text: Drupal.gft("text.tour.dashboard.tasks-step", {}, { context: "gofast_technical:gofast_tour" }),
                        attachTo: {
                            element: '#dashboard_block_workflows',
                            on: 'left'
                        },
                        when: {
                            show: function() {
                                Gofast.tour.components.fakeCursor.destroy();
                                $("#dashboard_toolbar_calendar #dropdown-rapid").dropdown("hide");
                            },
                            cancel: Gofast.tour.boilerplates.baseCancel
                        },
                        buttons: [
                            {
                                text: "<i class=\"fas fa-step-backward\"></i>",
                                action() {
                                    Gofast.tour.currentInstance.back();
                                }
                            },
                            {
                                text: "<i class=\"fas fa-check\"></i>",
                                classes: "btn btn-success",
                                action() {
                                    Gofast.tour.components.fakeCursor.destroy();
                                    $("#gofast_over_content").removeClass('tour-processed');
                                    Gofast.tour.currentInstance.complete();
                                } 
                            }
                        ]
                    },
                ];
            },
            get searchPage(){
                return [
                    {
                        id: 'gofast-tour-searchPage-sortby-step',
                        title: Drupal.gft("title.tour.search-page.sortby-step", {}, { context: "gofast_technical:gofast_tour" }),
                        text: Drupal.gft("text.tour.search-page.sortby-step", {}, { context: "gofast_technical:gofast_tour" }),
                        attachTo: {
                            element: '#gofastSearchSortBy',
                            on: 'bottom'
                        },
                        when: {
                            show: async function () {
                                const $sortList = $('#block-apachesolr-search-sort > ul > .btn-group').first();
                                await Gofast.tour.sequences.hoverSortByItems($sortList);
                                //Gofast.tour.components.fakeCursor.moveTo($("#gofastSearchResultsContent")[0], 700);
                            },
                            cancel: () => {
                                Gofast.tour.boilerplates.baseCancel()
                                $("#block-apachesolr-search-sort li").removeClass("sortby-item-hover");
                            }
                        },
                        buttons: [
                            {
                                text: "<i class=\"fas fa-step-backward\"></i>",
                                async action() {
                                    Gofast.tour.data.cancelActionsToAwait[Gofast.tour.currentInstance.getCurrentStep().id] = true;
                                    $("#block-apachesolr-search-sort li").removeClass("sortby-item-hover");
                                    Gofast.tour.currentInstance.back();
                                }
                            },
                            {
                                text: "<i class=\"fas fa-step-forward\"></i>",
                                async action() {
                                    Gofast.tour.data.cancelActionsToAwait[Gofast.tour.currentInstance.getCurrentStep().id] = true;      
                                    $("#block-apachesolr-search-sort li").removeClass("sortby-item-hover");
                                    Gofast.tour.currentInstance.next();
                                }
                            }
                        ]
                    },
                    {
                        id: 'gofast-tour-searchPage-results-step',
                        title: Drupal.gft("title.tour.search-page.results-step", {}, { context: "gofast_technical:gofast_tour" }),
                        text: Drupal.gft("text.tour.search-page.results-step", {}, { context: "gofast_technical:gofast_tour" }),
                        attachTo: {
                            element: '#gofastSearchResultsContent',
                            on: 'right'
                        },
                        beforeShowPromise: function() {
                            return new Promise(function(resolve) {
                                if(isSimplified()){
                                    if($("#filterSideButton").hasClass("expand")){
                                        Gofast.Essential.toggleSearchFilterTab();
                                    }
                                }
                                const activityFeedProcessedInterval = setInterval(function() {
                                    if ($('#gofastSearchResultsContent').length == 0) {
                                        return;
                                    }
                                    clearInterval(activityFeedProcessedInterval);
                                    resolve();
                                }, 250);

                            });
                        },
                        when: {
                            cancel: Gofast.tour.boilerplates.baseCancel
                        },
                        buttons: Gofast.tour.boilerplates.baseButtons()
                    },
                    {
                        id: 'gofast-tour-searchPage-fastActions-step',
                        title: Drupal.gft("title.tour.search-page.fastactions-step", {}, { context: "gofast_technical:gofast_tour" }),
                        text: Drupal.gft("text.tour.search-page.fastactions-step", {}, { context: "gofast_technical:gofast_tour" }),
                        attachTo: {
                            element: '#gofastFastActions',
                            on: 'left'
                        },
                        when: {
                            cancel: Gofast.tour.boilerplates.baseCancel
                        },
                        buttons: [
                            {
                                text: "<i class=\"fas fa-step-backward\"></i>",
                                action: Gofast.tour.currentInstance.back,
                            },
                            {
                                text: "<i class=\"fas fa-step-forward\"></i>",
                                async action(){
                                    await Gofast.tour.sequences.actionsToAwait([
                                        () => Gofast.tour.components.fakeCursor.moveTo($('#gofastFastActions > .dropdown > .btn')[0]),
                                        () => $('#gofastFastActions > .dropdown > .btn')[0].click(),
                                    ], 1000);
                                    const searchDropDownMenuInterval = setInterval(function() {
                                        if ($('#gofastFastActions').find(' > .gofast-node-actions div.dropdown-menu.show').length) {
                                            clearInterval(searchDropDownMenuInterval);
                                            $('#gofastFastActions').find(' > .gofast-node-actions div.dropdown-menu.show').css("z-index", 10000)
                                            // Add step now to make attachTo element exist on the next step
                                            Gofast.tour.currentInstance.addStep(Gofast.tour.descriptions.searchPageOptional.searchDropdownStep, 4)
                                            Gofast.tour.currentInstance.next();
                                        }
                                    }, 500);
                                } 
                            }
                        ]
                    },
                    {
                        id: 'gofast-tour-searchPage-preview-step',
                        title: Drupal.gft("title.tour.search-page.preview-step", {}, { context: "gofast_technical:gofast_tour" }),
                        text: Drupal.gft("text.tour.search-page.preview-step", {}, { context: "gofast_technical:gofast_tour" }),
                        attachTo: {
                            element: '#Preview',
                            on: 'right'
                        },
                        when: {
                            cancel: Gofast.tour.boilerplates.baseCancel
                        },
                        buttons: [
                            {
                                text: "<i class=\"fas fa-step-backward\"></i>",
                                action(){
                                    Gofast.tour.currentInstance.removeStep(Gofast.tour.descriptions.searchPageOptional.searchDropdownStep.id)
                                    Gofast.tour.currentInstance.back();
                                } 
                            },
                            {
                                text: "<i class=\"fas fa-step-forward\"></i>",
                                async action(){
                                    await Gofast.tour.sequences.actionsToAwait([
                                        () => Gofast.tour.components.fakeCursor.moveTo($('#Preview')[0], 700),
                                        () => {},
                                        () => $('#Preview').click(),
                                    ], 700);
                                    const previewModalInterval = setInterval(function() {
                                        if ($('#gofast_basicModal > .modal-dialog > .modal-content').length) {
                                            clearInterval(previewModalInterval);
                                            Gofast.tour.currentInstance.next();
                                        }
                                    }, 500);
                                } 
                            }
                        ]
                    },
                    {
                        id: 'gofast-tour-searchPage-previewModal-step',
                        title: Drupal.gft("title.tour.search-page.preview-modal-step", {}, { context: "gofast_technical:gofast_tour" }),
                        text: Drupal.gft("text.tour.search-page.preview-modal-step", {}, { context: "gofast_technical:gofast_tour" }),
                        attachTo: {
                            element: '#gofast_basicModal > .modal-dialog > .modal-content',
                            on: 'right'
                        },
                        when: {
                            show: function() {
                                Gofast.tour.components.fakeCursor.destroy();
                            },
                            cancel: function() {
                                Gofast.tour.boilerplates.baseCancel();
                                $('#modal-title').parent().find(" > .close").click();
                                $("#gofast_over_content").removeClass('tour-processed');
                            }
                        },
                        buttons: [
                            {
                                text: "<i class=\"fas fa-step-backward\"></i>",
                                action() {
                                    $('#Preview').click();
                                    const previewModalInterval = setInterval(function () {
                                        if ($('#gofast_basicModal > .modal-dialog > .modal-content').length) {
                                            clearInterval(previewModalInterval);
                                            Drupal.CTools.Modal.dismiss()
                                            Gofast.tour.currentInstance.back();
                                        }
                                    }, 500);
                                }
                            },
                            {
                                text: "<i class=\"fas fa-check\"></i>",
                                classes: "btn btn-success",
                                action() {
                                    Drupal.CTools.Modal.dismiss()
                                    Gofast.tour.components.fakeCursor.destroy();
                                    $("#gofast_over_content").removeClass('tour-processed');
                                    Gofast.tour.currentInstance.complete();
                                } 
                            }
                        ]
                    },
                ]
            },
            get searchPageOptional() {
                return {
                    searchFiltersStep:{
                        id: 'gofast-tour-searchPage-filters-step',
                        title: Drupal.gft("title.tour.search-page.filters-step", {}, { context: "gofast_technical:gofast_tour" }),
                        text: Drupal.gft("text.tour.search-page.filters-step", {}, { context: "gofast_technical:gofast_tour" }),
                        attachTo: {
                            element: '#gofastSearchResultsFilter',
                            on: 'left'
                        },
                        beforeShowPromise: function() {
                            return new Promise(async function(resolve) {
                                if(isSimplified()){
                                    if(!$("#filterSideButton").hasClass("expand")){
                                        await Gofast.tour.sequences.actionsToAwait([
                                            () => Gofast.tour.components.fakeCursor.moveTo($("#filterSideButton")[0], 500),
                                            () => {},
                                            () => Gofast.Essential.toggleSearchFilterTab(),
                                            () => {},
                                        ], 500);
                                    }
                                }
                                resolve()
                            });
                        },
                        when: {
                            show: async function() {
                                $filters = $('#facetapi_search_filters .accordion .card .card-header .card-title');
                                $("#facetapi_search_filters").parent().scrollTop(0)
                                await Gofast.tour.sequences.actionsToAwait([
                                    () => Gofast.tour.sequences.simulateSearchFiltersInteractions($filters),
                                    () => Gofast.tour.components.fakeCursor.moveTo($filters[0], 700),
                                ], 700);
                            },
                            cancel: Gofast.tour.boilerplates.baseCancel
                        },
                        buttons: Gofast.tour.boilerplates.baseButtons()
                    },
                    searchDropdownStep: {
                        id: 'gofast-tour-searchPage-fastActionsDropDownMenu-step',
                        title: Drupal.gft("title.tour.search-page.fastactions-dropdownmenu-step", {}, { context: "gofast_technical:gofast_tour" }),
                        text: Drupal.gft("text.tour.search-page.fastactions-dropdownmenu-step", {}, { context: "gofast_technical:gofast_tour" }),
                        attachTo: {
                            element: $('#gofastFastActions').find(' > .gofast-node-actions div.dropdown-menu.show')[0],
                            on: 'left'
                        },
                        when: {
                            show: function() {
                                
                                $('#gofastFastActions').find('> .gofast-node-actions div.dropdown-menu.show')[0].style.display = "block";
                                const $menuList = $('#gofastFastActions').find('> .gofast-node-actions div.dropdown-menu.show > .navi');
                                Gofast.tour.sequences.showFastActionsMenuItems($menuList);
                            },
                            cancel: function() {
                                Gofast.tour.components.fakeCursor.destroy();
                                $('#gofastFastActions').find('> .gofast-node-actions div.dropdown-menu.show')[0].style.display = "none";
                                $("#gofast_over_content").removeClass('tour-processed');  
                            }
                        },
                        buttons: [
                            {
                                text: "<i class=\"fas fa-step-backward\"></i>",
                                action(){
                                    $('#gofastFastActions').find(' > .gofast-node-actions div.dropdown-menu.show')[0].style.display = "none";
                                    Gofast.tour.currentInstance.back();
                                }
                            },
                            {
                                text: "<i class=\"fas fa-step-forward\"></i>",
                                action(){
                                    $('#gofastFastActions').find(' > .gofast-node-actions div.dropdown-menu.show')[0].style.display = "none";
                                    Gofast.tour.currentInstance.next();
                                } 
                            }
                        ]
                    }
                }
            }, 
            // defines steps of tour of document function
            get document() {
                return [
                    {
                        id: 'gofast-tour-document-breadcrumb-step',
                        title: Drupal.gft("title.tour.document.breadcrumb-step", {}, { context: "gofast_technical:gofast_tour" }),
                        text: Drupal.gft("text.tour.document.breadcrumb-step", {}, { context: "gofast_technical:gofast_tour" }),
                        attachTo: {
                            element: '.breadcrumb-gofast-show-title b',
                            on: 'left'
                        },
                        beforeShowPromise: function() {
                            return new Promise(async function(resolve) {
                                await Gofast.tour.sequences.toggleDocSideContent(false);
                                resolve();
                            });
                        },
                        when: {
                            cancel: Gofast.tour.boilerplates.baseCancel
                        },
                        buttons: [
                            {
                                text: "<i class=\"fas fa-step-forward\"></i>",
                                action: Gofast.tour.currentInstance.next,
                            }
                        ]
                    },
                    {
                        id: 'gofast-tour-document-preview-step',
                        title: Drupal.gft("title.tour.document.preview-step", {}, { context: "gofast_technical:gofast_tour" }),
                        text: Drupal.gft("text.tour.document.preview-step", {}, { context: "gofast_technical:gofast_tour" }),
                        attachTo: {
                            element: '#container_preview_element',
                            on: 'top'
                        },
                        beforeShowPromise: function() {
                            return new Promise(async function(resolve) {
                                $("#dropdown-node-dropdown").dropdown("hide");
                                await Gofast.tour.sequences.toggleDocSideContent(false);
                                resolve();
                            });
                        },
                        when: {
                            cancel: Gofast.tour.boilerplates.baseCancel
                        },
                        buttons: Gofast.tour.boilerplates.baseButtons()
                    },
                    {
                        id: 'gofast-tour-document-actions-step',
                        title: Drupal.gft("title.tour.document.actions-step", {}, { context: "gofast_technical:gofast_tour" }),
                        text: Drupal.gft("text.tour.document.actions-step", {}, { context: "gofast_technical:gofast_tour" }),
                        attachTo: {
                            element: '.dropdown-menu.show',
                            on: 'left'
                        },
                        beforeShowPromise: function() {
                            return new Promise(async function(resolve) {
                                await Gofast.tour.sequences.toggleDocSideContent(false);
                                if (!$("#dropdown-node-dropdown").hasClass("show")) {
                                    await Gofast.tour.sequences.actionsToAwait([
                                        () => Gofast.tour.components.fakeCursor.moveTo("#dropdown-node-dropdown"),
                                        () => {},
                                        () => $("#dropdown-node-dropdown").dropdown("show"),
                                    ], 1000);
                                }
                                resolve();
                            });
                        },
                        when: {
                            cancel: function() {
                                $("#dropdown-node-dropdown").dropdown("hide")
                                Gofast.tour.boilerplates.baseCancel();
                            }
                        },
                        buttons: Gofast.tour.boilerplates.baseButtons()
                    },
                    {
                        id: 'gofast-tour-document-actions-coedition-step',
                        title: Drupal.gft("title.tour.document.actions-coedition-step", {}, { context: "gofast_technical:gofast_tour" }),
                        text: Drupal.gft("text.tour.document.actions-coedition-step", {}, { context: "gofast_technical:gofast_tour" }),
                        attachTo: {
                            element: '.contextual_link_onlyoffice',
                            on: 'left'
                        },
                        when: {
                            show: function() {
                                setTimeout(function() {
                                 $("#dropdown-node-dropdown").dropdown("show");
                                }, 500);
                             },
                             cancel: function() {
                                 $("#dropdown-node-dropdown").dropdown("hide")
                                 Gofast.tour.boilerplates.baseCancel();
                             }
                        },
                        buttons: Gofast.tour.boilerplates.baseButtons()
                    },
                    {
                        id: 'gofast-tour-document-actions-multifile-step',
                        title: Drupal.gft("title.tour.document.actions-multifile-step", {}, { context: "gofast_technical:gofast_tour" }),
                        text: Drupal.gft("text.tour.document.actions-multifile-step", {}, { context: "gofast_technical:gofast_tour" }),
                        attachTo: {
                            element: '#manage-locations',
                            on: 'left'
                        },
                        beforeShowPromise: function() {
                            let element = this.attachTo.element
                            return new Promise(async function(resolve) {
                                if($("#fullscreenNavigationButtons").css("display") != "none"){
                                    Gofast.toggleFullScreen()
                                }
                                await Gofast.tour.sequences.actionsToAwait([
                                    () => Gofast.tour.components.fakeCursor.moveTo($("#dropdown-node-dropdown")[0]),
                                    () => $("#dropdown-node-dropdown").dropdown("show"),
                                    () => Gofast.tour.components.fakeCursor.moveTo(element),
                                ], 200);
                                resolve();
                            });
                        },
                        when: {
                            cancel: function() {
                                $("#dropdown-node-dropdown").dropdown("hide")
                                Gofast.tour.boilerplates.baseCancel();
                            }
                        },
                        buttons: Gofast.tour.boilerplates.baseButtons()
                    },
                    {
                        id: 'gofast-tour-document-fullscreen-step',
                        title: Drupal.gft("title.tour.document.fullscreen-step", {}, { context: "gofast_technical:gofast_tour" }),
                        text: Drupal.gft("text.tour.document.fullscreen-step", {}, { context: "gofast_technical:gofast_tour" }),
                        attachTo: {
                            element: isSimplified() ? "#node-full-screen-button" : "#toggle-fitscreen",
                            on: 'bottom'
                        },
                        beforeShowPromise: function() {
                            let element = this.attachTo.element
                            return new Promise(async function(resolve) {
                                $("#dropdown-node-dropdown").dropdown("hide");
                                await Gofast.tour.sequences.toggleDocSideContent(false);
                                await Gofast.tour.sequences.actionsToAwait([
                                    () => Gofast.tour.components.fakeCursor.moveTo(element),
                                ], 1000);
                                resolve();
                            });
                        },
                        when: {
                            show: async function() {
                                let element = this.options.attachTo.element

                                let closeFullscreenElement = element
                                // In Essential, there is one button for opeing and one button for closing fullscreen mode
                                if(element == "#node-full-screen-button"){
                                    closeFullscreenElement = "#node-normal-screen-button";
                                }
                                await Gofast.tour.sequences.actionsToAwait([
                                    () => {},
                                    () => Gofast.toggleFullScreen(),
                                    () => Gofast.tour.components.fakeCursor.moveTo(closeFullscreenElement),
                                    () => {},
                                    () => Gofast.toggleFullScreen(),
                                ], 1000);
                            },
                            cancel: Gofast.tour.boilerplates.baseCancel
                        },
                        buttons: [
                            {
                                text: "<i class=\"fas fa-step-backward\"></i>",
                                action() {
                                    Gofast.tour.data.cancelActionsToAwait[Gofast.tour.currentInstance.getCurrentStep().id] = true;
                                    Gofast.tour.currentInstance.back();
                                } 
                            },
                            {
                                text: "<i class=\"fas fa-check\"></i>",
                                classes: "btn btn-success",
                                action() {
                                    Gofast.tour.components.fakeCursor.destroy();
                                    $("#gofast_over_content").removeClass('tour-processed');
                                    Gofast.tour.currentInstance.complete();
                                }  
                            }
                        ]
                    },
                ];
            },
            get documentOptional() {
                return {
                    simplifiedDocumentNavigationArrows: {
                        id: 'gofast-tour-simplified-doc-nav-arrows',
                        title: Drupal.gft("title.tour.document.simplified-doc-nav-step", {}, { context: "gofast_technical:gofast_tour" }),
                        text: Drupal.gft("text.tour.document.simplified-doc-nav-step", {}, { context: "gofast_technical:gofast_tour" }),
                        attachTo: {
                            element: "#navigationButtons",
                            on: "bottom"
                        },
                        beforeShowPromise: function() {
                            return new Promise(async function(resolve) {
                                Gofast.tour.sequences.toggleDocSideContent(false);
                                $("#dropdown-node-dropdown").dropdown("hide");
                                resolve();
                            });
                        },
                        when: {
                            cancel: Gofast.tour.boilerplates.baseCancel,
                        },
                        buttons: Gofast.tour.boilerplates.baseButtons()
                    },
                    simplifiedDocumentSideContent: {
                        id: 'gofast-tour-simplified-doc-side-content',
                        title: Drupal.gft("title.tour.document.simplified-doc-side-content-step", {}, { context: "gofast_technical:gofast_tour" }),
                        text: Drupal.gft("text.tour.document.simplified-doc-side-content-step", {}, { context: "gofast_technical:gofast_tour" }),
                        attachTo: {
                            element: ".sideContent",
                            on: "left"
                        },
                        beforeShowPromise: function() {
                            return new Promise(async function(resolve) {
                                await Gofast.tour.sequences.toggleDocSideContent();
                                resolve();
                            });
                        },
                        when: {
                            cancel: Gofast.tour.boilerplates.baseCancel,
                        },
                        buttons: Gofast.tour.boilerplates.baseButtons()
                    },
                }
            },
            get explorer() {
                return [
                    {
                        id: 'gofast-tour-browser-ztree-nav',
                        title: Drupal.gft("title.tour.browser.ztree-nav-step", {}, { context: "gofast_technical:gofast_tour" }),
                        text: Drupal.gft("text.tour.browser.ztree-nav-step", {}, { context: "gofast_technical:gofast_tour" }),
                        attachTo: {
                            element: '#file_browser_full_tree_element',
                            on: 'right'
                        },
                        beforeShowPromise: async function() {
                            return new Promise(async function(resolve) {
                                Gofast.tour.sequences.removeInvisibleColumn();
                                Gofast.ITHit.navigate("/Sites");
                                await waitForElementVisibility("[title='_Extranet']");
                                resolve();
                            });
                        },
                        when: {
                            show: function() {
                                const extranetSwitchItem = $("[title='_Extranet']").parent().find(".switch");
                                Gofast.tour.sequences.actionsToAwait([
                                    () => Gofast.tour.components.fakeCursor.moveTo(extranetSwitchItem[0]),
                                    () => {},
                                    () => extranetSwitchItem.hasClass("center_close") ? extranetSwitchItem.click() : {},
                                ], 500);
                            },
                            cancel: function() {
                                Gofast.tour.sequences.removeInvisibleColumn();
                                Gofast.tour.boilerplates.baseCancel();
                            }
                        },
                        buttons: [
                            {
                                text: "<i class=\"fas fa-step-forward\"></i>",
                                action: Gofast.tour.currentInstance.next,
                            },
                        ]
                    },
                    {
                        id: 'gofast-tour-browser-perms-info',
                        title: Drupal.gft("title.tour.browser.perms-info-step", {}, { context: "gofast_technical:gofast_tour" }),
                        text: Drupal.gft("text.tour.browser.perms-info-step", {}, { context: "gofast_technical:gofast_tour" }),
                        attachTo: {
                            element: '.shepherd-invisible-column',
                            on: 'left'
                        },
                        beforeShowPromise: async function() {
                            return new Promise(async function(resolve) {
                                Gofast.tour.components.fakeCursor.destroy();
                                Gofast.tour.sequences.addInvisibleColumnOverElements(".item-info");
                                resolve();
                            });
                        },
                        when: {
                            cancel: Gofast.tour.boilerplates.baseCancel
                        },
                        buttons: Gofast.tour.boilerplates.baseButtons()
                    },
                    {
                        id: 'gofast-tour-browser-contextual-menu',
                        title: Drupal.gft("title.tour.browser.contextual-menu-step", {}, { context: "gofast_technical:gofast_tour" }),
                        text: Drupal.gft("text.tour.browser.contextual-menu-step", {}, { context: "gofast_technical:gofast_tour" }),
                        attachTo: {
                            element: '#file_browser_full_files_table',
                            on: 'left'
                        },
                        beforeShowPromise: function() {
                            return new Promise(async function(resolve) {
                                Gofast.tour.sequences.removeInvisibleColumn();
                                await Gofast.tour.sequences.actionsToAwait([
                                    () => Gofast.tour.components.fakeCursor.moveTo("#cbxSelect"),
                                    () => {
                                        if(!$("#cbxSelect").first().is(":checked")){
                                            $("#cbxSelect").first().click();
                                        }
                                    },
                                    () => Gofast.tour.components.fakeCursor.moveTo(".file_browser_full_files_element .item-name"),
                                    () => $(".file_browser_full_files_element .item-name").first().mousedown(),
                                    () => $(".file_browser_full_files_element .item-name").first().contextmenu(),
                                ], 1000);
                                resolve()
                            });
                        },
                        when: {
                            cancel: Gofast.tour.boilerplates.baseCancel
                        },
                        buttons: Gofast.tour.boilerplates.baseButtons()
                    },
                    {
                        id: 'gofast-tour-browser-history',
                        title: Drupal.gft("title.tour.browser.history-step", {}, { context: "gofast_technical:gofast_tour" }),
                        text: Drupal.gft("text.tour.browser.history-step", {}, { context: "gofast_technical:gofast_tour" }),
                        attachTo: {
                            element: '#essentialFileBrowserHistory',
                            on: 'right'
                        },
                        beforeShowPromise: function() {
                            return new Promise(async function(resolve) {
                                Gofast.tour.sequences.actionsToAwait([
                                    () => Gofast.tour.components.fakeCursor.moveTo("#select2-fileBrowserSelect-container"),
                                    () => $("#fileBrowserSelect").select2("open"),
                                    () => {},
                                    () => resolve(),
                                ], 1000);
                            });
                        },
                        when: {
                            cancel: Gofast.tour.boilerplates.baseCancel
                        },
                        buttons: Gofast.tour.boilerplates.baseButtons()
                    },
                    {
                        id: 'gofast-tour-browser-toolbar',
                        title: Drupal.gft("title.tour.browser.toolbar-step", {}, { context: "gofast_technical:gofast_tour" }),
                        text: Drupal.gft("text.tour.browser.toolbar-step", {}, { context: "gofast_technical:gofast_tour" }),
                        attachTo: {
                            element: '#file_browser_full_toolbar_container',
                            on: 'right'
                        },
                        beforeShowPromise: function() {
                            return new Promise(async function(resolve) {
                                $("#fileBrowserSelect").select2("close");
                                Gofast.tour.sequences.actionsToAwait([
                                    () => Gofast.tour.components.fakeCursor.moveTo("#file_browser_tooolbar_new_item"),
                                    () => $("#file_browser_tooolbar_new_item").click(),
                                    () => resolve(),
                                ], 1000);
                            });
                        },
                        when: {
                            cancel: Gofast.tour.boilerplates.baseCancel
                        },
                        buttons: Gofast.tour.boilerplates.baseButtons()
                    },
                    {
                        id: 'gofast-tour-browser-drag-drop',
                        title: Drupal.gft("title.tour.browser.drag-drop-step", {}, { context: "gofast_technical:gofast_tour" }),
                        text: Drupal.gft("text.tour.browser.drag-drop-step", {}, { context: "gofast_technical:gofast_tour" }),
                        attachTo: {
                            element: '#file_browser_full_upload_table',
                            on: 'top'
                        },
                        beforeShowPromise: function() {
                            return new Promise(async (resolve) => {
                                Gofast.tour.sequences.actionsToAwait([
                                    () => $("[style='background:url(/sites/all/modules/gofast/gofast_ajax_file_browser/img/home.png) 0 0 no-repeat;']").click(),
                                    () => resolve()
                                ], 1000);
                            });
                        },
                        when: {
                            cancel: Gofast.tour.boilerplates.baseCancel
                        },
                        buttons: Gofast.tour.boilerplates.baseButtons()
                    },
                    {
                        id: 'gofast-tour-browser-drag-drop-progress',
                        title: Drupal.gft("title.tour.browser.drag-drop-progress-step", {}, { context: "gofast_technical:gofast_tour" }),
                        text: Drupal.gft("text.tour.browser.drag-drop-progress-step", {"@brand": BRAND}, { context: "gofast_technical:gofast_tour" }),
                        attachTo: {
                            element: '#file_browser_full_upload_table',
                            on: 'top'
                        },
                        when: {
                            show: function() {
                                let item = {status: 0, displayNamePath: "test.docx (_Groups/Test)", operation: "upload", displayOperation:  Drupal.t("Upload", {}, { context: 'gofast:ajax_file_browser' }), fileName: "test.docx", progression: 0};
                                Gofast.tour.sequences.actionsToAwait([
                                    () => {},
                                    () => {
                                        Gofast.ITHit.freezeQueue();
                                        $("#file_browser_full_upload_label_container").hide();
                                        $(".file_browser_full_upload_element").remove();
                                        let itemHTML = Gofast.ITHit._formatQueueItem(item, 0);
                                        //Add the item to the list after removing the current items of the list
                                        $('#file_browser_full_upload_table').find('tbody:last-child').append(itemHTML);
                                    },
                                    () => {
                                        item.status = 1;
                                        item.progression = 33;
                                        $(".file_browser_full_upload_element").remove();
                                        let itemHTML = Gofast.ITHit._formatQueueItem(item, 0);
                                        $('#file_browser_full_upload_table').find('tbody:last-child').append(itemHTML);
                                    },
                                    () => {
                                        item.progression = 66;
                                        $(".file_browser_full_upload_element").remove();
                                        let itemHTML = Gofast.ITHit._formatQueueItem(item, 0);
                                        $('#file_browser_full_upload_table').find('tbody:last-child').append(itemHTML);
                                    },
                                    () => {
                                        item.status = 4;
                                        item.progression = 100;
                                        $(".file_browser_full_upload_element").remove();
                                        let itemHTML = Gofast.ITHit._formatQueueItem(item, 0);
                                        $('#file_browser_full_upload_table').find('tbody:last-child').append(itemHTML);
                                    },
                                    () => {},
                                    () => {
                                        $(".file_browser_full_upload_element").remove();
                                        Gofast.ITHit.refreshQueue();
                                        $("#file_browser_full_upload_label_container").show();

                                    }
                                ], 1000);
                            },
                            cancel: Gofast.tour.boilerplates.baseCancel
                        },
                        buttons: [
                            {
                                text: "<i class=\"fas fa-step-backward\"></i>",
                                action: Gofast.tour.currentInstance.back,
                            },
                            getVersion() == "simplified"
                                ? {
                                    text: "<i class=\"fas fa-step-forward\"></i>",
                                    action: Gofast.tour.currentInstance.next,
                                }
                                : {
                                    text: "<i class=\"fas fa-check\"></i>",
                                    classes: "btn btn-success",
                                    action() {
                                        Gofast.tour.components.fakeCursor.destroy();
                                        $("#gofast_over_content").removeClass('tour-processed');
                                        Gofast.tour.currentInstance.complete();
                                    }  
                                }
                        ]
                    },

                    {
                        id: 'gofast-tour-browser-tree-drag-drop',
                        title: Drupal.gft("title.tour.browser.tree-drag-drop-step", {}, { context: "gofast_technical:gofast_tour" }),
                        text: Drupal.gft("text.tour.browser.tree-drag-drop-step", {}, { context: "gofast_technical:gofast_tour" }),
                        attachTo: {
                            element: '#gofast_file_browser_side_content',
                            on: 'right'
                        },
                        beforeShowPromise: function(){
                            return new Promise(async function(resolve){
                                await Gofast.tour.sequences.actionsToAwait([
                                    () => Gofast.tour.components.fakeCursor.moveTo("#nav_mobile_file_browser_full_tree_container"),
                                    () => $("#nav_mobile_file_browser_full_tree_container").click(),
                                ], 500);
                                resolve();
                            })
                        },
                        when: {
                            cancel: Gofast.tour.boilerplates.baseCancel
                        },
                        buttons: Gofast.tour.boilerplates.baseButtons()
                    },
                    {
                        id: 'gofast-tour-browser-tree-document-tour-suggestion-step',
                        title: Drupal.gft("title.tour.browser.tree-document-tour-suggestion-step", {}, { context: "gofast_technical:gofast_tour" }),
                        text: Drupal.gft("text.tour.browser.tree-document-tour-suggestion-step", {}, { context: "gofast_technical:gofast_tour" }),
                        buttons: [
                            {
                                text: "<i class=\"fas fa-check\"></i>",
                                classes: "btn btn-success",
                                action() {
                                    $("#gofast_over_content").removeClass('tour-processed');
                                    Gofast.tour.currentInstance.complete();
                                    Gofast.tour.components.fakeCursor.destroy();
                                }  
                            }
                        ] 
                    },
                ];
            },
            get explorerOptional() {
                return {
                    simplifiedWikiTabStep: {
                        id: 'gofast-tour-simplified-wiki-tab-step',
                        title: Drupal.gft("title.tour.browser.simplified-wiki-tab-step", {}, { context: "gofast_technical:gofast_tour" }),
                        text: Drupal.gft("text.tour.browser.simplified-wiki-tab-step", {}, { context: "gofast_technical:gofast_tour" }),
                        attachTo: {
                            element: "#gofast_file_browser_side_content",
                            on: "right"
                        },
                        beforeShowPromise: function(){
                            return new Promise(async function(resolve){
                                await Gofast.tour.sequences.actionsToAwait([
                                    () => Gofast.tour.components.fakeCursor.moveTo("#nav_mobile_file_browser_wiki_container"),
                                    () => $("#nav_mobile_file_browser_wiki_container").click(),
                                ], 500);
                                resolve()
                            })
                        },
                        when: {
                            cancel: Gofast.tour.boilerplates.baseCancel,
                        },
                        buttons: Gofast.tour.boilerplates.baseButtons(),
                    },
                    simplifiedForumTabStep: {
                        id: 'gofast-tour-simplified-forum-tab-step',
                        title: Drupal.gft("title.tour.browser.simplified-forum-tab-step", {}, { context: "gofast_technical:gofast_tour" }),
                        text: Drupal.gft("text.tour.browser.simplified-forum-tab-step", {}, { context: "gofast_technical:gofast_tour" }),
                        attachTo: {
                            element: "#gofast_file_browser_side_content",
                            on: "right"
                        },
                        beforeShowPromise: function(){
                            return new Promise(async function(resolve){
                                await Gofast.tour.sequences.actionsToAwait([
                                    () => Gofast.tour.components.fakeCursor.moveTo("#nav_mobile_file_browser_forum_container"),
                                    () => $("#nav_mobile_file_browser_forum_container").click(),
                                ], 500);
                                resolve()
                            })
                        },
                        when: {
                            cancel: Gofast.tour.boilerplates.baseCancel,
                        },
                        buttons: Gofast.tour.boilerplates.baseButtons(),
                    },                
                }
            },
            get init() {
                return [
                    {
                        id: 'gofast-tour-init-step',
                        title: Drupal.gft("title.tour.init.first-step", {}, { context: "gofast_technical:gofast_tour" }),
                        text: Drupal.gft("text.tour.init.first-step", {}, { context: "gofast_technical:gofast_tour" }),
                        when: {
                            cancel: Gofast.tour.boilerplates.baseCancel,
                        },
                        buttons: [
                            {
                                text: "<i class=\"fas fa-times-circle\"></i>",
                                action: Gofast.tour.currentInstance.next,
                                classes: "btn btn-danger",
                                action() {
                                    Gofast.tour.data.configuration = Gofast.tour.data.configuration || {};
                                    Gofast.tour.data.configuration.hasTour = 0;
                                    Gofast.tour.currentInstance.next();
                                }
                            },
                            {
                                text: "<i class=\"fas fa-check\"></i>",
                                action: Gofast.tour.currentInstance.cancel,
                                classes: "btn btn-primary",
                                action() {
                                    Gofast.tour.data.configuration = Gofast.tour.data.configuration || {};
                                    Gofast.tour.data.configuration.hasTour = 1;
                                    Gofast.tour.currentInstance.complete();
                                    Gofast.tour.components.fakeCursor.destroy();
                                    Gofast.tour.currentInstance = Gofast.tour.boilerplates.newTour();
                                    Gofast.tour.launchEssentialTour();
                                }
                            }
                        ]
                    },
                    {
                        id: 'gofast-tour-disable-step',
                        title: Drupal.gft("title.tour.init.disable-step", {}, { context: "gofast_technical:gofast_tour" }),
                        text: Drupal.gft("text.tour.init.disable-step", {}, { context: "gofast_technical:gofast_tour" }),
                        attachTo: {
                            element: '#gofastAboutMenu',
                            on: 'bottom'
                        },
                        when: {
                            cancel: Gofast.tour.boilerplates.baseCancel,
                        },
                        buttons: [
                            {
                                text: "<i class=\"fas fa-check\"></i>",
                                classes: "btn btn-success",
                                action() {
                                    $("#gofast_over_content").removeClass('tour-processed');
                                    Gofast.tour.currentInstance.complete();
                                    Gofast.tour.components.fakeCursor.destroy();
                                }  
                            }
                        ] 
                    }
                ]
            },
            // mobile and essential specific steps
            get initOptional() {
                return {
                    mobileDisableStep: {
                        id: 'gofast-tour-mobile-disable-step',
                        title: Drupal.gft("title.tour.init.mobile-disable-step", {}, { context: "gofast_technical:gofast_tour" }),
                        text: Drupal.gft("text.tour.init.mobile-disable-step", {}, { context: "gofast_technical:gofast_tour" }),
                        when: {
                            cancel: Gofast.tour.boilerplates.baseCancel,
                        },
                        buttons: [
                            {
                                text: "<i class=\"fas fa-check\"></i>",
                                classes: "btn btn-success",
                                action() {
                                    $("#gofast_over_content").removeClass('tour-processed');
                                    Gofast.tour.currentInstance.complete();
                                    Gofast.tour.components.fakeCursor.destroy();
                                }  
                            }
                        ] 
                    }
                }
            }
        },
        fragments: {
            documentInformationsTab: {
                selector: "#metadataSideButton",
                triggeredBy: "click",
                tourDescription: "documentInformationsTabFragment",
                attachedEvent: null,
            },
            documentCommentsTab: {
                selector: "[href='#document__commentstab']:visible",
                triggeredBy: "click",
                tourDescription: "documentCommentsTabFragment",
                attachedEvent: null,
            },
            subscriptionsModal: {
                selector: "[href$='subscriptions']",
                triggeredBy: "click",
                tourDescription: "subscriptionsModalFragment",
                attachedEvent: null,
            },
            chatSideContent: {
                selector: "#animateRiot",
                triggeredBy: "click",
                tourDescription: "chatSideContentFragment",
                attachedEvent: null,
            },
            triggerNamingRuleInput: {
                selector: "[data-field='naming-rules'] .gofast-ac-drag-input",
                triggeredBy: "mousedown",
                tourDescription: "namingRuleInputFragment",
                attachedEvent: null,
            }
        },
        init: function() {
            if ($("#kt_content").hasClass("init-tour-processed")) {
                return;
            } else {
                $("#kt_content").addClass("init-tour-processed");
            }
            Gofast.tour.currentInstance = Gofast.tour.boilerplates.newTour();
            Gofast.tour.currentInstance.options.defaultStepOptions.cancelIcon.enabled = false;
            Gofast.tour.currentInstance.addSteps(Gofast.tour.descriptions.init);
            // we can safely add and remove steps directly in the instance since steps are not counted on this instance
            if (getVersion() == "mobile") {
                Gofast.tour.currentInstance.removeStep("gofast-tour-disable-step");
                Gofast.tour.currentInstance.addStep(Gofast.tour.descriptions.initOptional.mobileDisableStep, 1);
            }

            let targetSteps = Gofast.tour.currentInstance.steps;
            Gofast.tour.startTour(targetSteps);
            
            return Gofast.tour.currentInstance;
        },
        startTour: async function(steps) {
            let targetSteps = [];
            targetSteps.push(...steps);
            targetSteps = autoStepIndicator(targetSteps);
            Gofast.tour.currentInstance.addSteps(targetSteps);
            Gofast.tour.currentInstance.start();
        },
        //function for the profile page
        profile: function (force = false) {
            if (!force && $(".GofastUserProfile").hasClass("tour-processed")) {
                return;
            } else {
                $(".GofastUserProfile").addClass("tour-processed");
            }
            Gofast.tour.currentInstance = Gofast.tour.boilerplates.newTour();
            const steps = Gofast.tour.descriptions.profile;
            Gofast.tour.startTour(steps);
            return true;
        },
        // intended to be triggered by the essentialTour handler so it doesn't start the tour, just returns the steps
        essentialTour: function(force = false) {
            if (!force && $("#kt_content").hasClass("tour-processed")) {
                return;
            } else {
                $("#kt_content").addClass("tour-processed");
            }
            if (isSimplified()) {
                const steps = Gofast.tour.descriptions.simplifiedEssentialTour;
                return steps;
            }
            
            const steps = Gofast.tour.descriptions.essentialTour;
            if (getVersion() == "mobile") {
                // remove desktop-specific steps
                steps.splice(0, 1); // remove gofast-tour-home-menu-step
                steps.splice(1, 1); // remove gofast-tour-home-bookmarks-menu-step
                steps.splice(3, 1); // remove gofast-tour-home-left-menu-step
                // add mobile-specific steps
                steps.splice(0, 0, Gofast.tour.descriptions.essentialOptional.mobileMenuStep);
                steps.splice(1, 0, Gofast.tour.descriptions.essentialOptional.mobileBrowserMenuStep);
                steps.splice(2, 0, Gofast.tour.descriptions.essentialOptional.mobileHomeStep);
            }
            return steps;
        },
        // function for /activity
        activity: function (force = false) {
            if (!force && $("#activity-feed-table").hasClass("tour-processed")) {
                return;
            } else {
                $("#activity-feed-table").addClass("tour-processed");
            }
            Gofast.tour.currentInstance = Gofast.tour.boilerplates.newTour();

            const steps = Gofast.tour.descriptions.activity;
            if (getVersion() == "simplified" || getVersion() == "mobile") {
                steps.splice(1, 1); // remove gofast-tour-activity-filters-step
            }
            Gofast.tour.startTour(steps);
            return true;
        },
        // function for /dashboard
        dashboard: function(force = false) {
            if (!force && $(".gofastDashboard").hasClass("tour-processed")) {
                return;
            } else {
                $(".gofastDashboard").addClass("tour-processed");
            }
            Gofast.tour.currentInstance = Gofast.tour.boilerplates.newTour();

            const steps = Gofast.tour.descriptions.dashboard;
            Gofast.tour.startTour(steps);
            return true;
        },
        searchPage: function (force = false) {
            if (!force && $("#gofastSearchResultsContent").hasClass("tour-processed")) {
                return;
            } else {
                $("#gofastSearchResultsContent").addClass("tour-processed");
                
                Gofast.tour.currentInstance = Gofast.tour.boilerplates.newTour();
                const steps = Gofast.tour.descriptions.searchPage;
             
                steps.splice(1, 0, Gofast.tour.descriptions.searchPageOptional.searchFiltersStep);
                Gofast.tour.startTour(steps);
                return true;
            }
        },
        //function for a document page
        document: function (force = false) {
            if (!force && $("#fullscreen-node").hasClass("tour-processed")) {
                return;
            } else {
                $("#fullscreen-node").addClass("tour-processed");
            }
            Gofast.tour.currentInstance = Gofast.tour.boilerplates.newTour();

            const steps = Gofast.tour.descriptions.document;
            if (getVersion() == "simplified") {
                steps.splice(2, 0, Gofast.tour.descriptions.documentOptional.simplifiedDocumentNavigationArrows); // add gofast-tour-simplified-doc-nav-arrows
                steps.splice(3, 0, Gofast.tour.descriptions.documentOptional.simplifiedDocumentSideContent); // add gofast-tour-simplified-doc-side-content
            }
            Gofast.tour.startTour(steps);
            return true;
        },
        //launches a tour on the GF explorer
        explorer: function (force = false) {
            if (!force && $("#gofastBrowserContentPanel").hasClass("tour-processed")) {
                return;
            } else {
                $("#gofastBrowserContentPanel").addClass("tour-processed");
            }
            Gofast.tour.currentInstance = Gofast.tour.boilerplates.newTour();
            const steps = Gofast.tour.descriptions.explorer;
            if (getVersion() == "simplified" || getVersion() == "mobile") {
                steps.splice(8, 0, Gofast.tour.descriptions.explorerOptional.simplifiedWikiTabStep); // add gofast-tour-simplified-wiki-tab-step
                steps.splice(9, 0, Gofast.tour.descriptions.explorerOptional.simplifiedForumTabStep); // add gofast-tour-simplified-forum-tab-step
            }
            Gofast.tour.startTour(steps);
            return true;
        },
        attachFragmentEvent: function(fragmentKey) {
            const targetFragment = Gofast.tour.fragments[fragmentKey];
            const $targetElement = $(targetFragment.selector);
            if ($targetElement.hasClass("tour-fragment-added")) {
                return;
            }
            $targetElement.addClass("tour-fragment-added");
            Gofast.tour.fragments[fragmentKey].attachedEvent = async function() {
                if (Gofast.tour.data.fragments[fragmentKey] == 1) {
                    return;
                }
                if(Gofast.tour.hasOwnProperty("currentInstance") && Gofast.tour.currentInstance.isActive()){
                    return;
                }
                Gofast.tour.currentInstance = Gofast.tour.boilerplates.newTour();
                $(this).addClass("tour-processed");
                const steps = Gofast.tour.descriptions[targetFragment.tourDescription];
                Gofast.tour.startTour(steps);
                // once the event has been triggered, we update and store the data object again to avoid triggering it again
                Gofast.tour.data.fragments[fragmentKey] = 1;
                let data = await Gofast.tour.storeData();
                Gofast.tour.setData(data);
            };
            $targetElement.on(targetFragment.triggeredBy, Gofast.tour.fragments[fragmentKey].attachedEvent);
        },
        attachFragment: async function (key) {
            // fetches the users visited pages if they aren't loaded already
            if (Gofast.tour.data.enabled == -1 || !Gofast.tour.data.pages.done.size()) {
                data = await this.retrieveData();
                this.setData(data);
            }
            const visitedFragments = Gofast.tour.data.fragments || {};
            // if visited, don't attach anything
            if (visitedFragments[key] && visitedFragments[key] == 1) {
                return;
            }
            const fragmentValue = Gofast.tour.fragments[key];
            // attach only if element exists on current page
            if ($(fragmentValue.selector).length) {
                Gofast.tour.attachFragmentEvent(key);
            }
        },
        attachFragments: function (key = false) {
            for (const key of Object.keys(Gofast.tour.fragments)) {
                this.attachFragment(key);
            }
        },
        //gets the route name defined in the routes variable that matches the specified value, or undefined otherwise (route and hash value may contain regex)
        getRouteName: function () {
            //cycle through every defined route
            for (let page in routes) {
                //testing if route definition is a string or regexp
                if (routes[page] instanceof String || routes[page] instanceof RegExp || typeof routes[page] === "string") {
                    // handling simple definition
                    let routeExp = pathReg(routes[page]);
                    if (routeExp.test(window.location.pathname)) {
                        return page;
                    }
                }
                //testing if route definition is an object
                else if (typeof routes[page] === "object") {
                    let model = routes[page]
                    let routeExp = pathReg(model.path);
                    let match = true;
                    //matching path
                    match = match && routeExp.test(window.location.pathname);
                    //matching url hash (text with '#' symbol at end of url)
                    if (model.hash !== undefined) match = match && RegExp(model.hash).test(window.location.hash.substring(1));
                    // testing GET parameters
                    if (model.GET !== undefined && typeof model.GET === "object") {
                        let getParams = Gofast.getAllUrlParams(); //getting params
                        for (let key in model.GET) { //looping through params to check
                            if (typeof model.GET[key] === "function") { //if param is defined by check function, execute the function on the parameter value, else simply check equality
                                match = match && model.GET[key](getParams[key]);
                            }
                            else {
                                match = match && getParams[key] === model.GET[key];
                            }
                        }
                    }
                    // checks nodetype
                    if (model.nodeType !== undefined) {
                        let node = Gofast.get("node");
                        if (node !== undefined) {
                            match = match && RegExp(model.nodeType).test(node.type);
                        }
                    }
                    if(model.visibleElement !== undefined) {
                        match = match && $(model.visibleElement).is(":visible");
                    }
                    //if everything matched, then return page
                    if (match)
                        return page;
                }
            }
            // return null;
        },
        //tests if it is the user's first visit on the current page, if it is, it launches the page's tour
        firstVisit: async function () {
            // sets a checking flag so that the function doesn't get called multiple times
            this.checking = true;
            let data = {};
            try {
                let page = this.getRouteName(); //gets route name
                if (page !== undefined) {
                    //fetches the users visited pages if they aren't loaded already
                    if (Gofast.tour.data.enabled == -1 || !Gofast.tour.data.pages.done.size()) {
                        data = await this.retrieveData();
                        this.setData(data);
                    }

                    // don't trigger tour if it has been disabled user-side for some reason
                    if (Gofast.tour.data.enabled == 0) {
                        return;
                    }

                    if (Gofast.tour.data.configuration.hasTour == undefined) {
                        const initTour = this.pageTour("init");
                        const initTourPromise = new Promise((resolve) => {
                            initTour.on("complete", () => {
                                resolve();
                            })
                        });
                        await initTourPromise;
                        data = await this.storeData();
                        this.setData(data);
                    }
                    //gets the status of current page
                    let visited = Gofast.tour.data.pages.done[page];
                    if (visited != 1 && Gofast.tour.data.configuration.hasTour != 0) {
                        //launch tour and wait for positive response
                        if (this.pageTour(page)) {
                            //set the page to visited
                            Gofast.tour.data.pages.done[page] = 1;
                            data = await this.storeData();
                            this.setData(data);
                        }
                    }
                    if (Gofast.tour.data.configuration.hasTour == 0 && Gofast.tour.data.pages.notified[page] != 1) {
                        Gofast.toast(Drupal.gft("text.tour.toaster.available-tour-on-page", {}, { context: "gofast_technical:gofast_tour" }));
                        Gofast.tour.data.pages.notified[page] = 1; 
                        $("#gofast_over_content").removeClass('tour-processed')
                        data = await this.storeData();
                        this.setData(data);
                    }
                    if (Gofast.tour.data.configuration.hasTour == 1) {
                        // add events for non-"visited" tour fragments matching elements in currentPage
                        Gofast.tour.attachFragments();
                    }
                }
            } catch (err) {
                if (Gofast.get("dev_mode")) console.info("gofast_tour: can't access user data, probably because user is not logged in")
            }
            this.checking = false;
        },
        setData: function(data) {
            Gofast.tour.data.pages = data.pages || {};
            Gofast.tour.data.pages.done = data.pages ? (data.pages.done || {}) : {};
            Gofast.tour.data.pages.notified = data.pages ? (data.pages.notified || {}) : {};
            Gofast.tour.data.configuration = data.configuration || {};
            Gofast.tour.data.fragments = data.fragments || {};
            Gofast.tour.data.enabled = typeof data.enabled != "undefined" ? data.enabled : -1;
        },
        //sends a request to store the users visited pages on the server, returns the server's response (usually the data that has been saved)
        storeData: async function () {
            let response;
            await $.post("/gofast/tour/visited_pages", Gofast.tour.data, data => response = JSON.parse(data));
            // log message in dev mode
            if (Gofast.get("dev_mode") && LOG_DATA_REQUESTS) console.count("gofast_tour.js: stored tour user data")
            // return the parsed server response
            return response;

        },
        //fetches the data stored
        retrieveData: async function () {
            let response;
            // fetches data from the server
            response = $.ajax({
                method: "GET",
                url: "/gofast/tour/visited_pages",
            });
            // parses response as JSON
            response = JSON.parse(await response);
            // handle case where returned data is blank
            if (Array.isArray(response) && response.length === 0) response = {};
            // log message in dev mode
            if (Gofast.get("dev_mode") && LOG_DATA_REQUESTS) console.count("gofast_tour.js: fetched tour user data")
            // return parsed response
            return response;
        },
        //sends a request to reset the stored visited pages on the server, resets the local vaalue as well
        resetVisitedPages: async function () {
            try {
                //send request to reset the visited pages of the user
                await $.ajax({
                    method: "GET",
                    url: "/gofast/tour/visited_pages/reset",
                })
                // logs message when response is received
                if (Gofast.get("dev_mode")) console.log("stored visited pages for current user have been reset");
                Gofast.tour.data.pages.done = {};
            } catch (error) {
                //error handling
                if (Gofast.get("dev_mode")) console.error("GoFAST Tour: failed to reset: ajax error\ndetails:", error);
            }
        },
        //function bound to click event on navbar "?" dropdown menu option "Launch tour"
        tourButtonAction: function (e) {
            e.preventDefault()
            e.stopPropagation();
            if (!Gofast._settings.isEssential) {
                return;
            }
            if (this.currentPageTour(true) === false) {
                Gofast.toast("No tour is available for this page.", "info");
            }
        },
        launchEssentialTour: function (e) {
            if (!Gofast._settings.isEssential) {
                return;
            }
            Gofast.tour.currentInstance = Gofast.tour.boilerplates.newTour();
            let targetSteps = Gofast.tour.essentialTour(true);
            targetSteps = autoStepIndicator(targetSteps);
            Gofast.tour.currentInstance.addSteps(targetSteps);
            Gofast.tour.currentInstance.start();
        },
        //launches the tour of the current page. Shortcut for pageTour(getRouteName())
        currentPageTour: function (force = false) {
            return this.pageTour(this.getRouteName(), force)
        },
        //launches a tour for a given page name, verifies if tour exists returns true if the tour could be launched successfully, false otherwise
        //the associated functions for each route name are in a bindings variable.
        pageTour: function (page, force = false) {
            if ($(".gofast-shepherd-tour").length) {
                $('#gofast_over_content').removeClass('tour-processed');
                return;
            }
            //checks if bindings have been defined for this page
            if (bindings[page] !== undefined) {
                // get site version
                let version = getVersion();
                // verify that the corresponding binding is defined and a function
                if (bindings[page][version] !== undefined && typeof bindings[page][version] === "function") {
                    // call bound function
                    return bindings[page][version](force);
                }
                // log warnings in case there is no definition for current page
                else console.warn('TOUR WARNING: no handler set for ' + version + ' version of page "' + page + '"');
            } else console.warn('TOUR WARNING: no object set for current page with page name: ' + page);
            return false;
        },
        get brand() { return BRAND },
        set brand(val) {
            if (Gofast.get("dev_mode"))
                BRAND = val;
            else console.error("Setting the brand from JS is only availaible in dev mode for debugging purposes.")
        },
    };
    //config
    //defines the associated route names of some paths
    /** @type { { [key:string]: string|RegExp|{ path: string|RegExp, nodeType?: "group"|"alfresco_item"|"organisation", hash?: string, GET?: { [key:string]: string|((paramValue:string) => boolean) }, test?: () => boolean } } } */
    let routes = {
        "browser": { path: "/node/*", hash: "ogdocuments", visibleElement: "#ogdocuments" },
        "dashboard": "/dashboard",
        "activity": "/activity",
        "document": { path: "/node/*", nodeType: "alfresco_item" },
        "searchPage": "/search/*",
        "profile": { path: "/user(/*)?" }
    };
    //binds the tour functions for each route name
    //tour is for now disabled in mobile and standard versions
    /** @type { { [key:string]: { mobile:Function, standard:Function } } } */
    let bindings = {
        "init": {
            // mobile: Gofast.tour.init,
            simplified: Gofast.tour.init,
            // standard: Gofast.tour.init,
        },
        "browser": {
            // mobile: Gofast.tour.explorer,
            simplified: Gofast.tour.explorer,
            // standard: Gofast.tour.explorer,
        },
        "activity": {
            // mobile: Gofast.tour.activity,
            simplified: Gofast.tour.activity,
            // standard: Gofast.tour.activity,
        },
        "dashboard": {
            // mobile: Gofast.tour.dashboard,
            simplified: Gofast.tour.dashboard,
           //  standard: Gofast.tour.dashboard,
        },
        "searchPage": {
            simplified: Gofast.tour.searchPage,
        },
        "document": {
            // mobile: Gofast.tour.document,
            simplified: Gofast.tour.document,
            // standard: Gofast.tour.document,
        },
        "profile": {
            // mobile: Gofast.tour.profile,
            simplified: Gofast.tour.profile,
            // standard: Gofast.tour.profile,
        },
    };

    //automatically checks for first visit on page change.
    const AUTO_TRIGGER_ENABLED = true;
    //attach function is called automatically on every load operation (initial and ajax)
    Drupal.behaviors.autoTour = {
        attach: function () {
            BRAND = Drupal.settings.site_name || "GoFAST";
            let allProcessedPages = Object.keys(Gofast.tour.data.pages.done)
            allProcessedPages.push(...Object.keys(Gofast.tour.data.pages.notified))
            let routeName = Gofast.tour.getRouteName()
            if(!$("#gofast_over_content").hasClass('tour-processed') && routeName !== undefined && allProcessedPages.includes(routeName) == false){
                $("#gofast_over_content").addClass('tour-processed');
                if (AUTO_TRIGGER_ENABLED && Gofast._settings.isEssential) {
                    if (!Gofast.tour.checking) {
                        Gofast.tour.firstVisit();
                    }
                }
            }
        }
    }
    Shepherd.on("complete", () => {
        Gofast.tour.data.cancelActionsToAwait = [];
    })
    Shepherd.on("cancel", () => {
        Gofast.tour.data.cancelActionsToAwait = [];
    })
})(jQuery, Gofast, Drupal);
