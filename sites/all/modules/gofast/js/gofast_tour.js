/**
 * Describe content of contextual helps.
 */
//function executed at every page load
(function ($, Gofast, Drupal) {
    var previous = Drupal.t("Previous", {}, { context: 'gofast_tour' });
    var next = Drupal.t("Next", {}, { context: 'gofast_tour' });
    var end = Drupal.t("End", {}, { context: 'gofast_tour' });

    var templateLockNext = "<div class='popover tour' style='z-index:1102'>\
        <div class='arrow'></div>\
        <h3 class='popover-title'></h3>\
        <div class='popover-content'></div>\
        <div class='popover-navigation'>\
            <div class='btn-group'>\
                <button class='btn btn-default' data-role='prev'>« "+ previous + "</button>\
                <button class='btn btn-default disabled' disabled tabindex='-1' data-role='next'>"+ next + " »</button>\
            </div>\
            <button class='btn btn-default' data-role='end'>"+ end + "</button>\
        </div>\
    </div>";

    var template = "<div class='popover tour' style='z-index:1102'>\
        <div class='arrow'></div>\
        <h3 class='popover-title'></h3>\
        <div class='popover-content'></div>\
        <div class='popover-navigation'>\
            <div class='btn-group'>\
                <button class='btn btn-default' data-role='prev'>« "+ previous + "</button>\
                <button class='btn btn-default' data-role='next'>"+ next + " »</button>\
            </div>\
            <button class='btn btn-default' data-role='end'>"+ end + "</button>\
        </div>\
    </div>";

    const LOG_DATA_REQUESTS = false; //enables/disables the logging when fetching/storing data on server
    let BRAND;
    function noBubble(e) { return (e = e || window.event, e.stopPropagation()); }
    //"decorates" a steps onShow and onHidden methods to open/close parent dropdowns (activated with hover)
    //* dead code
    function hoverMenuItem(model) {
        let base = { onShow: model.onShow, onHidden: model.onHidden };
        model.onShow = function () {
            model.element.mouseenter().parents(".dropdown-menu").addClass("tutoriel-open").mouseenter();
            model.element.on("mouseleave", noBubble);
            if (base.onShow !== undefined && typeof base.onShow === "function")
                base.onShow();
        };
        model.onHidden = function () {
            if (base.onHidden !== undefined && typeof base.onHidden === "function")
                base.onHidden();
            model.element.off("mouseleave", noBubble);
            model.element.mouseleave().parents(".dropdown-menu").removeClass("tutoriel-open").mouseleave();
        };
        return model;
    }

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
    function isMobile() { return !!Drupal.settings.isMobile && !!Gofast.get("browser").ismobiledevice }
    /**
     * Returns true if on simplifed version, false otherwise.
     * @returns {boolean}
     */
    function isSimplified() { return !!Drupal.settings.isMobile && !Gofast.get("browser").ismobiledevice }
    /**
     * Returns a string representing the current version
     * @returns {"standard"|"simplified"|"mobile"}
     */
    function getVersion() { return ["standard", "simplified", "mobile"][isMobile() ? 2 : isSimplified() ? 1 : 0] }
    /**
     * Defers execution of other code based on visibility of a necessary HTML element.
     * Returns a Jquery Deferred Promise.
     * @param {String|jQuery} selector The selector of the element to check. passing a string can wheck if an element is not present initially on the page
     * @param {number} maxChecks Max number of times to check for element visibility, defaults to 100.
     */
    function waitForElementVisibility(selector, maxChecks = 100) {
        //sets up a delay so that next step can execute normally.
        let def = $.Deferred()
        let fullfilled = false;
        setTimeout(function () {
            let numberChecks = 1;
            // Tests once and then tests again every .1s if the target of next step is not visible. When target becomes visible resolves delay. Gives up after 100 checks.
            setTimeout(function check() {
                if ($(selector).exists() && $(selector).is(":visible")) {
                    def.resolve();
                    fullfilled = true;
                }
                if (maxChecks >= 0 && numberChecks > maxChecks) {
                    def.reject();
                    fullfilled = true;
                }
                if (!fullfilled) {
                    numberChecks++;
                    setTimeout(check, 100);
                }
            });
        });
        return def.promise();
    }
    /**
     * Defers execution of other code based on visibility of a blocking HTML element.
     * Returns a Jquery Deferred Promise.
     * @param {String|jQuery} selector The selector of the element to check. passing a string can wheck if an element is not present initially on the page
     * @param {number} maxChecks Max number of times to check for element visibility, defaults to 100.
     */
    function waitForElementNotVisible(selector, maxChecks = 100) {
        //sets up a delay so that next step can execute normally.
        let def = $.Deferred()
        let fullfilled = false;
        setTimeout(function () {
            let numberChecks = 1;
            // Tests once and then tests again every .1s if the target of next step is visible. When target becomes not visible resolves delay. Gives up after 100 checks.
            setTimeout(function check() {
                if (!$(selector).exists() || $(selector).is(":not(:visible)")) {
                    def.resolve();
                    fullfilled = true;
                }
                if (maxChecks >= 0 && numberChecks > maxChecks) {
                    def.reject();
                    fullfilled = true
                }
                if (!fullfilled) {
                    numberChecks++;
                    setTimeout(check, 100);
                }
            });
        });
        return def.promise();
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
    //makes the tabs of home_page_navigation call firstVisit
    function tourTabHandler() {
        setTimeout(function () {
            Gofast.tour.firstVisit();
        }, 200);
    }
    Gofast.tour = {
        descriptions: {
            // defines steps of tour of profile function
            get profile() {
                return [
                    {
                        element: $(".profile-row.profile-row-1"), //profile general info
                        title: Drupal.t("Informations", {}, { context: 'gofast_tour' }),
                        content: Drupal.t("Change the informations about yourself", {}, { context: 'gofast_tour' }),
                        placement: "right"
                    },
                    {
                        element: $(".profile-row.profile-row-4:first"), //container of everything the user belongs to
                        title: Drupal.t("Informations", {}, { context: 'gofast_tour' }),
                        content: Drupal.t("Look at your rights", {}, { context: 'gofast_tour' }),
                        placement: "top"
                    },
                    {
                        element: $('.btn.btn-default.ctools-use-modal.ctools-use-modal-processed'), //account settings button
                        placement: "auto bottom",
                        title: Drupal.t("Modifications", {}, { context: 'gofast_tour' }),
                        reflex: true,
                        template: templateLockNext,
                        content: Drupal.t("Click here to modify your preferences and informations.", {}, { context: 'gofast_tour' })
                    },
                    {
                        title: Drupal.t("Details", {}, { context: 'gofast_tour' }),
                        content: Drupal.t("You can now modify any information.", {}, { context: 'gofast_tour' }),
                        orphan: true,
                        onPrev: function () {
                            $(".close.ctools-close-modal.processed.ctools-close-modal-processed").click();
                        }
                    }
                ]
            },
            // defines steps of tour of home function
            get home() {
                return [
                    {
                        element: $("table#activity-feed-table>tbody>tr:eq(1)"), //first line in activity
                        title: Drupal.t("Activities", {}, { context: 'gofast_tour' }),
                        content: Drupal.t("Look at the most recent activities.", {}, { context: 'gofast_tour' }),
                        placement: "right",
                        onNext: async function () {
                            $(".btn.btn-default.btn-xs.dropdown-toggle.dropdown-placeholder.dropdown-processed:eq(0)").click();
                            await waitForElementVisibility("ul.dropdown-menu.gofast-dropdown-menu:eq(0)");
                        }
                    },
                    {
                        element: "ul.dropdown-menu.gofast-dropdown-menu:eq(0)", //opened dropdown menu options
                        title: Drupal.t("Menu", {}, { context: 'gofast_tour' }),
                        content: Drupal.t("Look at the menu.", {}, { context: 'gofast_tour' }),
                        placement: "left",
                        onShow: function () {
                            $(".btn.btn-default.btn-xs.dropdown-toggle.dropdown-placeholder.dropdown-processed:eq(0)").parent().addClass("tutoriel-open");
                        }
                    },
                    {
                        element: $("#block-gofast-views-activity-stream-filters"),
                        title: Drupal.t("Filters", {}, { context: 'gofast_tour' }),
                        content: Drupal.t("Use filters to find what you want.", {}, { context: 'gofast_tour' }),
                        placement: "left"
                    }
                ]
            },
            // defines steps of tour of navbar function
            get navbar() {
                return [
                    {
                        element: $("nav>ul>li:eq(1)>a").parent(), //spaces dropdown
                        title: Drupal.t("Spaces", {}, { context: 'gofast_tour' }),
                        content: Drupal.t("Get to your spaces.", {}, { context: 'gofast_tour' })
                    },
                    {
                        element: $("nav>ul>li:eq(0)>a").parent(), //create dropdown
                        title: Drupal.t("Create", {}, { context: 'gofast_tour' }),
                        content: Drupal.t("Create documents, spaces and conferences.", {}, { context: 'gofast_tour' })
                    },
                    {
                        element: $("#block-gofast-menu-gofast-menu-icons"),
                        title: Drupal.t("Fast access", {}, { context: 'gofast_tour' }),
                        content: Drupal.t("Get easilly to your messages and bookmarks.", {}, { context: 'gofast_tour' }),
                        backdropPadding: { bottom: 11 }
                    },
                    {
                        element: $("#edit-search-block-form--2").parent().parent(),
                        title: Drupal.t("Search tool", {}, { context: 'gofast_tour' }),
                        content: Drupal.t("Use it with few keywords to find your desired content faster.", {}, { context: 'gofast_tour' }),
                        placement: "bottom"
                    },
                    {
                        element: $(".username.has-submenu"),
                        title: Drupal.t("Profile", {}, { context: 'gofast_tour' }),
                        content: Drupal.t("Get to your profile.", {}, { context: 'gofast_tour' }),
                        placement: "left"
                    },
                    {
                        element: $(".logo.navbar-btn.pull-left").parent(),
                        title: Drupal.t("Home", {}, { context: 'gofast_tour' }),
                        content: Drupal.t("Click here to go back to the home page.", {}, { context: 'gofast_tour' })
                    }
                ]
            },
            // defines steps of tour of createDocFile function
            get createDocFile() {
                return [
                    {
                        element: $("ul.nav.nav-tabs.vertical-tabs-list"),
                        title: Drupal.t("Creation types", {}, { context: 'gofast_tour' }),
                        content: Drupal.t("3 ways to do it.", {}, { context: 'gofast_tour' }),
                        placement: "right"
                    },
                    {
                        element: $("#edit-group-upload-file-body").parent().parent(),
                        title: Drupal.t("Upload a file", {}, { context: 'gofast_tour' }),
                        content: Drupal.t("Upload.", {}, { context: 'gofast_tour' }),
                        placement: "bottom",
                        onNext: function () {
                            $("ul.nav.nav-tabs.vertical-tabs-list :nth-child(2) :nth-child(1)").trigger("click");
                        }
                    },
                    {
                        element: $("#edit-group-template-file-body").parent().parent(),
                        title: Drupal.t("Create from templates", {}, { context: 'gofast_tour' }),
                        content: Drupal.t("TEMPLATE.", {}, { context: 'gofast_tour' }),
                        placement: "bottom",
                        onNext: function () {
                            $("ul.nav.nav-tabs.vertical-tabs-list :nth-child(3) :nth-child(1)").trigger("click");
                        },
                        onPrev: function () {
                            $("ul.nav.nav-tabs.vertical-tabs-list :nth-child(1) :nth-child(1) :nth-child(1)").trigger("click");
                        }
                    },
                    {
                        element: $("#edit-group-empty-file-body").parent().parent(),
                        title: Drupal.t("Create an empty file", {}, { context: 'gofast_tour' }),
                        content: Drupal.t("Simply create an empty file.", {}, { context: 'gofast_tour' }),
                        placement: "bottom",
                        onPrev: function () {
                            $("ul.nav.nav-tabs.vertical-tabs-list :nth-child(2) :nth-child(1)").trigger("click");
                        }
                    },
                    {
                        element: $(".field-type-entityreference.field-name-og-group-content-ref.field-widget-og-complex.panel.panel-default.form-wrapper"),
                        title: Drupal.t("Location", {}, { context: 'gofast_tour' }),
                        content: Drupal.t("Select the location.", {}, { context: 'gofast_tour' }),
                        placement: "top"
                    }
                ]
            },
            // defines steps of tour of document function
            get document() {
                return [
                    {
                        element: $(".dropdown-menu.dropdown-menu-right.gofast-dropdown-menu:eq(0)"), //versions menu
                        title: Drupal.t("Menu", {}, { context: 'gofast_tour' }),
                        content: Drupal.t("Text about the menu.", {}, { context: 'gofast_tour' }),
                        placement: "left",
                        onShow: function () {
                            $(".dropdown-menu.dropdown-menu-right.gofast-dropdown-menu:eq(0)").addClass("tutoriel-open");
                        },
                        onNext: function () {
                            $(".dropdown-menu.dropdown-menu-right.gofast-dropdown-menu:eq(0)").removeClass("tutoriel-open");
                        }
                    },
                    {
                        element: $("#block-gofast-gofast-node-infos"),
                        title: Drupal.t("Informations", {}, { context: 'gofast_tour' }),
                        content: Drupal.t("Text about informations.", {}, { context: 'gofast_tour' }),
                        placement: "left"
                    },
                    {
                        element: $("#block-gofast-gofast-node-comments-tree"),
                        title: Drupal.t("Comments", {}, { context: 'gofast_tour' }),
                        content: Drupal.t("J'ai choisi de mettre uniquement à droite car je ne peux pas faire les<br>\
                            deux simultanément et qu'il peut ne pas y avoir de commentaire en dessous.", {}, { context: 'gofast_tour' }),
                        placement: "left"
                    }
                ]
            },
            // defines steps of tour of searchResult function
            get searchResult() {
                return [
                    {
                        element: $("dl.search-results.apachesolr_search-results :nth-child(1):eq(0)"), //first displayed search result
                        title: Drupal.t("Result", {}, { context: 'gofast_tour' }),
                        content: Drupal.t("Results of the search.", {}, { context: 'gofast_tour' }),
                        placement: "bottom"
                    },
                    {
                        element: $("dl.search-results.apachesolr_search-results :nth-child(1):eq(0) > dt > span:eq(1)"), //search result dropdown
                        title: Drupal.t("Menu", {}, { context: 'gofast_tour' }),
                        content: Drupal.t("Access the menu.", {}, { context: 'gofast_tour' }),
                        placement: "bottom"
                    },
                    {
                        element: $("dl.search-results.apachesolr_search-results :nth-child(1):eq(0) > dt > a"), //search result preview button
                        title: Drupal.t("Preview", {}, { context: 'gofast_tour' }),
                        content: Drupal.t("And the preview. (Je pouvais pas sélectionner les deux éléments, ou j'aurai pris le titre avec)", {}, { context: 'gofast_tour' }),
                        placement: "bottom",
                        onNext: function () {
                            $("#mCSB_1_container > section:eq(3) > h2").click();
                        }
                    },
                    {
                        element: $("#mCSB_1_container > section:eq(3)"), //filter options (not working, possible fix: $(".container-filter:eq(0)"))
                        title: Drupal.t("Filters", {}, { context: 'gofast_tour' }),
                        content: Drupal.t("Apply filters on your result.", {}, { context: 'gofast_tour' }),
                        placement: "left",
                        onPrev: function () {
                            $("#mCSB_1_container > section:eq(3) > h2").click();
                        }
                    }
                ]
            },
            // defines steps of tour of spaceDocs function
            get spaceDocs() {
                return [
                    {
                        element: $(".breadcrumb.gofast.breadcrumb-gofast"),
                        title: Drupal.t("Location", {}, { context: 'gofast_tour' }),
                        content: Drupal.t("See where you are.", {}, { context: 'gofast_tour' }),
                        placement: "bottom"
                    },
                    {
                        element: $("#file_browser_full_toolbar_container"),
                        title: Drupal.t("Menu", {}, { context: 'gofast_tour' }),
                        content: Drupal.t("Access the menu.", {}, { context: 'gofast_tour' }),
                        placement: "bottom"
                    },
                    {
                        element: $("#file_browser_full_container > div:eq(2)"),
                        title: Drupal.t("Explorer", {}, { context: 'gofast_tour' }),
                        content: Drupal.t("Look at this space's files", {}, { context: 'gofast_tour' }),
                        placement: "left"
                    },
                    {
                        element: $("#file_browser_full_toolbar_search_input").parent(),
                        title: Drupal.t("Filters", {}, { context: 'gofast_tour' }),
                        content: Drupal.t("Apply filters on your result.", {}, { context: 'gofast_tour' }),
                        placement: "bottom",
                        onNext: function () {
                            $(".dropdown-menu.dropdown-menu-right.gofast-dropdown-menu").addClass("tutoriel-open");
                        }
                    },
                    {
                        element: $(".dropdown-menu.dropdown-menu-right.gofast-dropdown-menu"),
                        title: Drupal.t("Actions", {}, { context: 'gofast_tour' }),
                        content: Drupal.t("Text to introduce contextual actions.", {}, { context: 'gofast_tour' }),
                        backdrop: true,
                        placement: "left",
                        onPrev: function () {
                            $(".dropdown-menu.dropdown-menu-right.gofast-dropdown-menu").removeClass("tutoriel-open");
                        }
                    }
                ]
            },
            // defines steps of tour of homeSimplified function
            get homeSimplified() {
                return [
                    {
                        orphan: true,
                        title: Gofast.htmlDecode(Drupal.t("Welcome to @brand", { "@brand": BRAND }, { context: "gofast_tour" })),
                        content: [
                            Drupal.t('Welcome to @brand!', { "@brand": BRAND, "!help": '<i class="fa fa-question-circle"></i>', }, { context: "gofast_tour" }),
                            Drupal.t('This tour will show you how to get started with @brand!', { "@brand": BRAND, "!help": '<i class="fa fa-question-circle"></i>', }, { context: "gofast_tour" }),
                            Drupal.t('Browse the visit by clicking on "Next" and "Previous".', { "@brand": BRAND, "!help": '<i class="fa fa-question-circle"></i>', }, { context: "gofast_tour" }),
                            Drupal.t('To stop the visit at any time, click on "End".', { "@brand": BRAND, "!help": '<i class="fa fa-question-circle"></i>', }, { context: "gofast_tour" }),
                            Drupal.t('You can reopen the visit from !help (top right).', { "@brand": BRAND, "!help": '<i class="fa fa-question-circle"></i>', }, { context: "gofast_tour" })
                        ].join('<br>'),
                        placement: "bottom"
                    },
                    {
                        element: $(".logo.navbar-btn.pull-left").parent(),
                        title: Drupal.t("Logo", {}, { context: 'gofast_tour' }),
                        content: Drupal.t('One-click access to the home page with your:', {}, { context: 'gofast_tour' }) +
                            '<ul>\
                        <li>'+ Drupal.t("Activity Feed", {}, { context: "gofast_tour" }) + '</li>\
                        <li>'+ Drupal.t("Spaces/Documents", {}, { context: "gofast_tour" }) + '</li>\
                        <li>'+ Drupal.t("Dashboard", {}, { context: "gofast_tour" }) + '</li>\
                        </ul>',
                    },
                    {
                        element: $("#dropdown-menu-page"), //burger menu
                        title: Drupal.t('Main "burger" menu', {}, { context: 'gofast_tour' }),
                        content: Drupal.t("Access the main pages of @brand to create and view documents, tasks and other contents.", { "@brand": BRAND }, { context: 'gofast_tour' }),
                    },
                    {
                        element: $("#edit-search-block-form--2").parent().parent(),
                        title: Drupal.t("Search bar", {}, { context: 'gofast_tour' }),
                        content: Drupal.t("Type a few keywords to quickly find a document !", {}, { context: 'gofast_tour' }),
                        placement: "bottom",
                    },
                    {
                        element: $(".username.has-submenu"),
                        title: Drupal.t("User profile", {}, { context: 'gofast_tour' }),
                        content: Drupal.t("Here, manage your profile and subscriptions to activity notifications by Space.", {}, { context: 'gofast_tour' }),
                        placement: "bottom",
                    },
                    {
                        element: $("#gofast_block_delta-gofast_workflows_light_dashboard-gofast_workflows"), //workflow/taches
                        title: Drupal.t("My workflows and tasks", {}, { context: "gofast_tour" }),
                        content: Drupal.t("Here, find the list of all your tasks, with the associated contents.", {}, { context: "gofast_tour" }),
                        placement: "bottom"
                    },
                    {
                        element: $(".visible-lg.btn.btn-sm.gofast-about-btn"), //help button
                        title: Drupal.t("Help", {}, { context: "gofast_tour" }),
                        content: Drupal.t('Here go to the online documentation, user forums and launch this help tour.', {}, { context: "gofast_tour" }),
                        placement: "left",
                    },
                    {
                        element: "#navigation_activity",
                        title: Drupal.t("Activity tab", {}, { context: "gofast_tour" }),
                        content: Drupal.t("View in real time the added contents, modifications and commentaries, according to your permissions.", {}, { context: "gofast_tour" }),
                        placement: "bottom",
                    },
                    {
                        element: "#navigation_browser",
                        title: Drupal.t("Spaces/Documents tab", {}, { context: "gofast_tour" }),
                        content: Drupal.t("Find your Spaces and documents in a classic and very practical file explorer.", {}, { context: "gofast_tour" }),
                        placement: "bottom",
                    },
                    {
                        element: "#navigation_dashboard",
                        title: Drupal.t("Dashboard tab", {}, { context: "gofast_tour" }),
                        content: Drupal.t("View key information, quick access and favorites on your dashboard.", {}, { context: "gofast_tour" }),
                        placement: "bottom",
                    },
                ]
            },
            // defines steps of tour of documentSimplified function
            get documentSimplified() {
                return [
                    {
                        element: "#alfresco_content",
                        title: Drupal.t("Document preview", {}, { context: "gofast_tour" }),
                        content: [Drupal.t('The preview area displays the latest version of the document.', {}, { context: "gofast_tour" }),
                        Drupal.t('Note that the "Office" files have a preview in PDF format in order to read them easily: it is not the Office document itself, nor an editing tool.', {}, { context: "gofast_tour" })].join('<br>'),
                        placement: "top",
                        onShow: function () {
                            return waitForElementVisibility(this.element);
                        },
                    },
                    {
                        element: "#comments-container",
                        title: Drupal.t("Comments", {}, { context: "gofast_tour" }),
                        content: [Drupal.t('Here you can read and respond to user comments on the document.', { "!reply": '<i class="fa fa-reply"></i>' }, { context: "gofast_tour" }), Drupal.t('Click !reply to respond.', { "!reply": '<i class="fa fa-reply"></i>' }, { context: "gofast_tour" })].join('<br>'),
                        placement: "top",
                        onShow: function () {
                            return waitForElementVisibility(this.element);
                        },
                    }, //...
                    {
                        element: "#gofast_mobile_arrow",
                        title: Drupal.t("Actions and Information", {}, { context: "gofast_tour" }),
                        content: [Drupal.t("Click on this arrow to open/close the side panel with the information and possible actions.", { "!warn": '<i class="fa fa-exclamation-triangle"></i>', "!arrow": '<i class="glyphicon glyphicon-menu-left"></i>' }, { context: "gofast_tour" }), Drupal.t("!warn Click on the arrow to continue the tour!", { "!warn": '<i class="fa fa-exclamation-triangle"></i>', "!arrow": '<i class="glyphicon glyphicon-menu-left"></i>' }, { context: "gofast_tour" })].join('<br>'),
                        placement: "left",
                        template: templateLockNext,
                        reflex: true,
                    },
                    {
                        element: "#panel-heading-title", //document file name
                        title: Drupal.t("Document name", {}, { context: "gofast_tour" }),
                        content: Drupal.t("Here you can view and change the name of the document.", {}, { context: "gofast_tour" }),
                        placement: "left",
                        onPrev: function () {
                            $("#gofast_mobile_arrow").mousedown().mouseup();
                        },
                    },
                    {
                        element: ".panel.panel-info > .panel-body", //metadata
                        title: Drupal.t("Information", {}, { context: "gofast_tour" }),
                        content: Drupal.t("Here you can view information about the document.", {}, { context: "gofast_tour" }),
                        placement: "left",
                    },
                    {
                        element: ".panel.panel-info > .panel-footer", //actions
                        title: Drupal.t("Actions", {}, { context: "gofast_tour" }),
                        content: Drupal.t("Here, the actions you can do on the document. Click to get started!", {}, { context: "gofast_tour" }),
                        placement: "left",
                        onNext: function () {
                            $("#gofast_mobile_arrow").mousedown().mouseup();
                        },
                    },
                    {
                        element: "#ithit-toggle",
                        title: Drupal.t("File Explorer", {}, { context: "gofast_tour" }),
                        content: [Drupal.t("Click here to open/close the File Explorer, in the side panel.", { "!warn": '<i class="fa fa-exclamation-triangle"></i>', "!folder": '<i class="fa fa-folder-open-o"></i>' }, { context: "gofast_tour" }), Drupal.t("!warn Click on the “folder” !folder icon to continue the tour!", { "!warn": '<i class="fa fa-exclamation-triangle"></i>', "!folder": '<i class="fa fa-folder-open-o"></i>' }, { context: "gofast_tour" })].join('<br>'),
                        placement: "right",
                    },
                ];
            },
            // defines steps of tour of searchSimplified function
            get searchSimplified() {
                return [
                    {
                        element: "#gofast_mobile_arrow",
                        title: Drupal.t("Search filters", {}, { context: "gofast_tour" }),
                        content: Drupal.t("Open the side menu to filter your search result.", {}, { context: "gofast_tour" }),
                        placement: "left",
                    },
                    {
                        element: ".search-result:eq(0) .gofast-title",
                        title: Drupal.t("Access to the document", {}, { context: "gofast_tour" }),
                        content: Drupal.t("Click on the title to go to the document's page.", {}, { context: "gofast_tour" }),
                        placement: "top",
                    },
                    {
                        element: ".search-result:eq(0) .fast-actions",
                        title: Drupal.t("Action menu", {}, { context: "gofast_tour" }),
                        content: Drupal.t('Click the "burger" menu to view/do the actions allowed on the document.', {}, { context: "gofast_tour" }),
                    }
                ]
            },
            // defines steps of tour of explorerSimplified function
            get explorerSimplified() {
                return [
                    {
                        element: $("#file_browser_full_tree"),
                        title: Drupal.t("Tree navigation: Spaces and folders", {}, { context: 'gofast_tour' }),
                        content:
                            Drupal.t('One click to go to the desired Space or folder:', {}, { context: 'gofast_tour' }) +
                            '<ul style="list-style:none">\
                            <li>' + Drupal.t("!organisations Organisation: My Departments", { "!organisations": '<span class="fa ' + Drupal.settings.ext_map.organisation + '" style="color:#3498db"></span>' }, { context: "gofast_tour" }) + '</li>\
                            <li>'+ Drupal.t("!groups Group: My transversal projects and shared themes", { "!groups": '<span class="fa ' + Drupal.settings.ext_map.group + '" style="color:#3498db"></span>' }, { context: "gofast_tour" }) + '</li>\
                            <li>'+ Drupal.t("!extranet Extranet: Spaces shared with external partners", { "!extranet": '<span class="fa ' + Drupal.settings.ext_map.extranet + '" style="color:#3498db"></span>' }, { context: "gofast_tour" }) + '</li>\
                            <li>'+ Drupal.t("!public Public: Everyone is a member (excluding extranets)!", { "!public": '<span class="fa ' + Drupal.settings.ext_map.public + '" style="color:#3498db"></span>' }, { context: "gofast_tour" }) + '</li>\
                            <li>'+ Drupal.t("!personalSpace private: Only you have access", { "!personalSpace": '<span class="fa ' + Drupal.settings.ext_map.private_space + '" style="color:#3498db"></span>' }, { context: "gofast_tour" }) + '</li>\
                            </ul>\n'+
                            Drupal.t('You only see the Spaces of which you are a member.', {}, { context: 'gofast_tour' }),
                    },
                    {
                        element: $("#file_browser_full_files"),
                        title: Drupal.t("Drag and drop", {}, { context: "gofast_tour" }),
                        content: Drupal.t("You can directly drag and drop documents from your PC in a Space/Folder.", {}, { context: "gofast_tour" }),
                        placement: "top",
                    },
                    {
                        element: $("#file_browser_full_tree"),
                        title: Drupal.t("Drag and drop", {}, { context: "gofast_tour" }),
                        content: Drupal.t("You can also drag and drop your document into a space / folder in the tree view here.", {}, { context: "gofast_tour" }),
                        placement: "right",
                    },
                    {
                        element: $("#file_browser_full_upload_table"),
                        title: Drupal.t("Document Uploading", {}, { context: "gofast_tour" }),
                        content: Drupal.t('After a "drag and drop" from your PC to a @brand location, the progress is displayed here and you can cancel the upload if necessary.', { "@brand": BRAND }, { context: "gofast_tour" }),
                        placement: "top",
                    },
                ]
            },
        },
        //function for the profile page
        profile: function () {
            var tour = new Tour({
                name: "profile",
                storage: false,
                backdrop: true,
                animation: false,
                template: template,
                steps: autoStepIndicator(Gofast.tour.descriptions.profile),
            });
            tour.init();
            tour.start();
            return true;
        },
        //function for page /activity
        home: function () {
            var tour = new Tour({
                backdrop: true,
                storage: false,
                name: "home",
                template: template,
                steps: autoStepIndicator(Gofast.tour.descriptions.home),
            });
            tour.init();
            tour.start();
            return true;
        },
        //function for navbar
        navbar: function () {
            var tour = new Tour({
                backdrop: true,
                storage: false,
                name: "navbar",
                template: template,
                animation: false,
                steps: autoStepIndicator(Gofast.tour.descriptions.navbar),
            });
            tour.init();
            tour.start();
            return true;
        },
        //function the creation of a document or a file (Create > Content > Document File)
        createDocFile: function () {
            var tour = new Tour({
                backdrop: true,
                storage: false,
                name: "createDocFile",
                template: template,
                steps: autoStepIndicator(Gofast.tour.descriptions.createDocFile),
            });
            tour.init();
            tour.start();
            return true;
        },
        //function for a document page
        document: function () {
            var tour = new Tour({
                name: "document",
                storage: false,
                template: template,
                backdrop: true,
                steps: autoStepIndicator(Gofast.tour.descriptions.document),
            });
            tour.init();
            tour.start();
            return true;
        },
        //function for the search page
        searchResult: function () {
            var tour = new Tour({
                name: "searchResult",
                storage: false,
                template: template,
                backdrop: true,
                steps: autoStepIndicator(Gofast.tour.descriptions.searchResult),
            });
            tour.init();
            tour.start();
            return true;
        },
        //function for the search page
        spaceDocs: function () {
            var tour = new Tour({
                name: "spaceDocs",
                storage: false,
                template: template,
                backdrop: true,
                onEnd: function () {
                    $(".dropdown-menu.dropdown-menu-right.gofast-dropdown-menu").removeClass("tutoriel-open");
                },
                steps: autoStepIndicator(Gofast.tour.descriptions.spaceDocs),
            });
            tour.init();
            tour.start();
            return true;
        },
        //launches a tour on the mobile home page (technically any page works since it only affects the navbar)
        homeSimplified: function () {
            var tour = new Tour({
                backdrop: true,
                storage: false,
                name: "homeSimplified",
                template: template,
                animation: false,
                steps: autoStepIndicator(Gofast.tour.descriptions.homeSimplified),
            });
            return waitForElementNotVisible(".modal-dialog", -1)
                .then(function () {
                    tour.init();
                    tour.start();
                    return true;
                })
                .catch(() => false);
        },
        //launches a tour on an open document page on mobile version
        documentSimplified: function () {
            let tour = new Tour({
                backdrop: true,
                storage: false,
                name: "documentSimplified",
                template: template,
                animation: false,
                onEnd: function () {
                    //tests if side panel is open when tour is ended, if it is, close it.
                    if ($("#gofast_mobile_panel").css("right") === "0px")
                        $("#gofast_mobile_arrow").mousedown().mouseup();
                },
                onStart: function () {
                    //tests if side panel is open when tour is started, if it is, close it.
                    if ($("#gofast_mobile_panel").css("right") === "0px")
                        $("#gofast_mobile_arrow").mousedown().mouseup();
                },
                steps: autoStepIndicator(Gofast.tour.descriptions.documentSimplified),
            });

            return waitForElementVisibility('#alfresco_content')
                .then(function () {
                    tour.init();
                    tour.start();
                    return true;
                })
                .catch(() => false)
        },
        //Launches a tour on the search page on mobile/simplified version
        searchSimplified: function () {
            let tour = new Tour({
                name: "searchSimplified",
                storage: false,
                backdrop: true,
                template: template,
                animation: false,
                steps: autoStepIndicator(Gofast.tour.descriptions.searchSimplified),
            });
            return waitForElementVisibility("#gofast_mobile_arrow")
                .then(function () {
                    tour.init();
                    tour.start();
                    return true;
                })
                .catch(() => false)
        },
        //Launches a tour on the GF explorer on the mobile/simplified version
        explorerSimplified: function () {
            let tour = new Tour({
                backdrop: true,
                storage: false,
                name: "explorerSimplified",
                template: template,
                animation: false,
                steps: autoStepIndicator(Gofast.tour.descriptions.explorerSimplified),
            });

            return waitForElementVisibility("#navBrowser")
                .then(function () {
                    tour.init();
                    tour.start();
                    return true;
                })
                .catch(() => false)
        },
        //gets the route name defined in the routes variable that matches the specified value, or undefined otherwise (route value may contain regex)
        getRouteName: function () {
            //cycle through every defined route
            for (let page in routes) {
                //testing if route definition si a string or regexp
                if (routes[page] instanceof String || routes[page] instanceof RegExp || typeof routes[page] === "string") {
                    // handling simple definition
                    let routeExp = pathReg(routes[page]);
                    if (routeExp.test(window.location.pathname)) {
                        return page;
                    }
                }
                //testing if route definitionis an object
                else if (typeof routes[page] === "object") {
                    let model = routes[page]
                    let routeExp = pathReg(model.path);
                    let match = true;
                    //matching path
                    match = match && routeExp.test(window.location.pathname);
                    //matching url hash (text with '#' symbol at end of url)
                    if (model.hash !== undefined) match = match && window.location.hash.substring(1) === model.hash;
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
                            match = match && model.nodeType === node.type;
                        }
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
            try {
                let page = this.getRouteName(); //gets route name
                if (page !== undefined) {
                    //fetches the users visited pages if they aren't loaded already
                    this.visitedPages = this.visitedPages || await this.retrieveData() || {};
                    //gets the status of current page
                    let visited = this.visitedPages[page];
                    if (!visited) {
                        //launch tour and wait for positive response
                        if (await this.pageTour(page)) {
                            //set the page to visited
                            this.visitedPages[page] = 1;
                            this.visitedPages = await this.storeData();
                        }
                    }
                }
            } catch (err) {
                if (Gofast.get("dev_mode")) console.info("gofast_tour: can't access user data, probably because user is not logged in")
            }
            this.checking = false;
        },
        //sends a request to store the users visited pages on the server, returns the server's response (usually the data that has been saved)
        storeData: async function () {
            let data = { pages: this.visitedPages };
            let response
            //sends data to server to be saved.
            response = $.ajax({
                method: "POST",
                url: "/gofast/tour/visited_pages",
                data: data,
            });
            //gets the data sent by the server and parses it as JSON
            response = JSON.parse(await response);
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
                this.visitedPages = {};
            } catch (error) {
                //error handling
                if (Gofast.get("dev_mode")) console.error("GoFAST Tour: failed to reset: ajax error\ndetails:", error);
            }
        },
        //function bound to click event on navabr "?" dropdown menu option "Launch tour"
        tourButtonAction: function (event) {
            noBubble(event);
            setTimeout(() => { $(event.target).parent().removeClass("active") }, 200);
            if (this.currentPageTour() === false) {
                Gofast.toast("No tour is available for this page.", "info");
            }
        },
        //launches the tour of the current page. Shortcut for pageTour(getRouteName())
        currentPageTour: function () {
            return this.pageTour(this.getRouteName())
        },
        //launches a tour for a given page name, verifies if tour exists returns true if the tour could be launched successfully, false otherwise
        //the associated functions for each route name are in a bindings variable.
        pageTour: function (page) {
            //checks is bindings have been defined for this page
            if (bindings[page] !== undefined) {
                // get site version
                let version = getVersion();
                // verify that the corresponding binding is defined and a function
                if (bindings[page][version] !== undefined && typeof bindings[page][version] === "function") {
                    // call bound function
                    return bindings[page][version]();
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
        "browser": { path: "/home_page_navigation", hash: "navBrowser" },
        "home": "/(dashboard|activity|home_page_navigation)",
        "document": { path: "/node/*", nodeType: "alfresco_item" },
        "search": "/search/*",
    };
    //binds the tour functions for each route name
    /** @type { { [key:string]: { mobile:Function, standard:Function } } } */
    let bindings = {
        "browser": {
            mobile: Gofast.tour.explorerSimplified,
            simplified: Gofast.tour.explorerSimplified,
        },
        "home": {
            mobile: Gofast.tour.homeSimplified,
            simplified: Gofast.tour.homeSimplified,
            standard: undefined,
        },
        "document": {
            mobile: Gofast.tour.documentSimplified,
            simplified: Gofast.tour.documentSimplified,
        },
        "profile": {
            standard: Gofast.tour.profile,
        },
        "search": {
            mobile: Gofast.tour.searchSimplified,
            simplified: Gofast.tour.searchSimplified,
        },
    };

    //automatically checks for first visit on page change.
    const AUTO_TRIGGER_ENABLED = true;
    //attach function is called automatically on every load operation (initial and ajax)
    Drupal.behaviors.autoTour = {
        attach: function () {
            BRAND = Drupal.settings.site_name || "GoFAST";

            if (AUTO_TRIGGER_ENABLED) {
                if (!Gofast.tour.checking) Gofast.tour.firstVisit();
                let route = Gofast.tour.getRouteName()
                if (route == "home" || route == "browser") {
                    $(".item_navigation").off("click", tourTabHandler).click(tourTabHandler);
                }
            }
        }
    }
})(jQuery, Gofast, Drupal);
