<div class="card h-100">
    <!--begin::Header-->
    <legend class="p-2"><?= t("Select a template", array(), array("gofast:gofast_cmis")) ?></legend>
    <!--end::Header-->
    <!--begin::Body-->
    <div class="card-body p-0 pt-4">
        <!--begin::Nav-->
        <ul class="nav nav-pills nav-pills-custom justify-content-between">
            <li class="nav-item" role="presentation" style="width: 49%;">
                <div class="input-group mb-2">
                    <span class="input-group-text"><i class="fas fa-search"></i></span><input id="gofastTemplateNameFilter" type="text" class="form-control" placeholder="<?= t("Search by name", array(), array("gofast:gofast_cmis")) ?>" />
                </div>
            </li>
            <li class="nav-item" role="filter" style="width: 49%">
                <div class="input-group mb-2 flex-nowrap">
                    <span class="input-group-text">
                        <span class="svg-icon svg-icon-1" style="filter: invert(66%) sepia(6%) saturate(688%) hue-rotate(192deg) brightness(101%) contrast(86%);">
                            <svg width="24" height="26" viewBox="0 0 181 173" xmlns="http://www.w3.org/2000/svg">
                                <path d="M149.546 58.9812C152.848 57.7649 156.348 57.1079 159.888 57.0402C152.033 40.7798 138.196 27.824 120.993 20.6228C120.869 23.953 120.136 27.2371 118.827 30.3276C132.111 36.3818 142.914 46.4583 149.546 58.9812Z" fill="black"></path>
                                <path d="M20.9634 57.0402C24.5031 57.1079 28.0031 57.7649 31.3051 58.9812C37.9577 46.4464 48.7889 36.3687 62.1008 30.3276C60.792 27.2371 60.0595 23.953 59.9357 20.6228C42.7033 27.8095 28.8368 40.7669 20.9634 57.0402Z" fill="black"></path>
                                <path d="M150.591 113.643C144.197 126.85 133.235 137.565 119.541 143.995C120.504 146.857 120.995 149.845 120.993 152.851C120.993 153.263 120.993 153.652 120.993 154.064C139.096 146.511 153.453 132.61 161.085 115.245H160.474C157.109 115.238 153.769 114.697 150.591 113.643Z" fill="black"></path>
                                <path d="M30.2608 113.643C27.0829 114.697 23.7425 115.238 20.3776 115.245H19.8427C27.4571 132.596 41.7844 146.495 59.8593 154.064C59.8593 153.652 59.8593 153.263 59.8593 152.851C59.8567 149.845 60.3466 146.857 61.3112 143.995C47.6159 137.565 36.6545 126.85 30.2608 113.643Z" fill="black"></path>
                                <path d="M40.7553 86.1303C40.7553 96.8503 31.632 105.54 20.3777 105.54C9.12337 105.54 0 96.8503 0 86.1303C0 75.4103 9.12337 66.7208 20.3777 66.7208C31.632 66.7208 40.7553 75.4103 40.7553 86.1303Z" fill="black"></path>
                                <path d="M180.852 86.1303C180.852 96.8503 171.729 105.54 160.474 105.54C149.219 105.54 140.096 96.8503 140.096 86.1303C140.096 75.4103 149.219 66.7208 160.474 66.7208C171.729 66.7208 180.852 75.4103 180.852 86.1303Z" fill="black"></path>
                                <path d="M110.804 152.851C110.804 163.571 101.68 172.261 90.4257 172.261C79.1711 172.261 70.0482 163.571 70.0482 152.851C70.0482 142.131 79.1711 133.441 90.4257 133.441C101.68 133.441 110.804 142.131 110.804 152.851Z" fill="black"></path>
                                <path d="M110.804 19.4097C110.804 30.1294 101.68 38.8194 90.4257 38.8194C79.1711 38.8194 70.0482 30.1294 70.0482 19.4097C70.0482 8.69 79.1711 0 90.4257 0C101.68 0 110.804 8.69 110.804 19.4097Z" fill="black"></path>
                                <path d="M69.9616 73.5875H127.769V67.8265C127.769 65.2916 125.692 63.2176 123.154 63.2176H88.5385L75.8461 54.8065C75.0384 54.3456 74.2308 54 73.3077 54H51.6154C49.0769 54 47 56.0739 47 58.6088V115.067C47 115.297 61.8846 79.0029 61.8846 79.0029C63.2692 75.7768 66.3846 73.5875 69.9616 73.5875Z" fill="black"></path>
                                <path d="M137 82.8053C137 80.3856 135.269 78.4268 132.846 78.1964H69.9616C68.2308 78.1964 66.7308 79.2334 66.0385 80.7313L50.4616 118.524H120.846L136.539 84.8792C136.885 84.1879 137 83.4965 137 82.8053Z" fill="black"></path>
                            </svg>
                        </span>
                    </span>
                <input data-get-spaces placeholder="<?= t("Search by space", array(), array("context" => "gofast:gofast_cmis")) ?>" name="ac-list-tags-one-space" id="gofastTemplateSpaceFilter" class="form-control" type="text" />
                </div>
            </li>
            <!--end::Item-->
        </ul>
        <div class="table-responsive" style="<?= gofast_essential_is_essential() ? "" : "max-height: calc(100vh - 400px - 6rem);" ?>">
            <!--begin::Table-->
            <table id="gofastTemplateTable" class="table align-middle my-0">
                <!--begin::Table head-->

                <!--end::Table head-->
                <!--begin::Table body-->
                <tbody>
                    <?php foreach($available_templates as $nid => $template) : ?>
                    <tr class="gofast-template-hoverable-row">
                        <td class="border-0">
                            <div data-toggle="tooltip" data-boundary="window" data-trigger="hover" data-placement="right" data-html="true" title="<?= theme("gofast_cmis_template_widget_tooltip", array("paths" => $template["paths"])) ?>" class="d-flex align-items-center" style="gap: .5rem; width: max-content;">
                                <label class="radio">
                                    <input id="gofastTemplateRadio<?= $nid ?>" name="gofast_cmis_template_radio" class="gofast_cmis_template_radio" type="radio" />
                                    <span></span></label>
                                <div>
                                <?php
                                    // to avoid performance hits, we make a fake node containing only values needed to get the icon
                                    $fake_template_node = new stdClass();
                                    $fake_template_node->type = $template["infos"]->type;
                                    $fake_template_node->field_format['und'][0]['tid'] = $template["infos"]->field_format_tid;
                                    $template_icon = gofast_node_get_icon($fake_template_node);
                                ?>
                                    <i class="<?= $template_icon ?>"></i>
                                </div>
                                <div>
                                    <a href="/node/<?= $nid ?>" target="_blank" class="node-link text-gray-800 fw-bold text-hover-primary mb-1 fs-6"><?= $template["infos"]->field_filename_value ?></a>
                                </div>
                                <div id="gofastTemplateInfo<?= $nid ?>" class="d-none gofast_template_info">
                                    <?= json_encode($template) ?>
                                </div>
                            </div>
                        </td>
                    </tr>
                    <?php endforeach; ?>
                </tbody>
                <!--end::Table body-->
            </table>
            <!--end::Table-->
        </div>
        <!--end::Nav-->
        <!--begin::Tab Content-->

        <!--end::Tab Content-->
    </div>
    <!--end: Card Body-->
</div>
<script>
    jQuery(document).ready(function() {
        const $gofastCmisTemplateSelect = jQuery("#edit-templates");
        const $gofastCmisTitleSelect = jQuery("#edit-title");
        const $gofastCmisExtensionSelect = jQuery("#edit-extension");
        const $gofastCmisLanguageSelect = jQuery("#edit-language");
        // bind displayed templates radios to hidden select values
        jQuery(".gofast_cmis_template_radio").on("change", function() {
            // get needed infos
            const targetNid = this.id.replace("gofastTemplateRadio", "");
            const $templateInfoElement = jQuery("#gofastTemplateInfo" + targetNid);
            // set template select
            $gofastCmisTemplateSelect.val("nid_" + targetNid);
            // set other related fields
            const templateInfo = JSON.parse($templateInfoElement.text());
            const templateTitle = templateInfo.infos.title.split(".").shift();
            const templateExtension = templateInfo.infos.title.split(".").pop();
            $gofastCmisTitleSelect.val(templateTitle);
            // Put "Create an empty file" select to none to prevent error when submitting for "Create from template" with an extension selected
            $("#edit-empty-template").val("none").trigger("change")
            $gofastCmisExtensionSelect.val(templateExtension);
            $gofastCmisLanguageSelect.val(templateInfo.infos.language);
            $gofastCmisLanguageSelect.trigger("change");
        });
        
        jQuery('.gofast-template-hoverable-row').on("click", function() {
            var $this = jQuery(this);
            $this.find('input[type="radio"]').prop('checked', true).trigger("change");
            $this.addClass('selected').siblings().removeClass('selected'); 
        });
    

        function gofastTemplateRefreshFilters() {
            const hasNoActiveFilters = Object.values(activeFilters).every(value => value.length < 3);
            // show everything if there is no value
            if (hasNoActiveFilters) {
                jQuery("#gofastTemplateTable tr").show();
                return;
            }
            const keys = Object.keys(activeFilters);
            const haystacks = {};
            for (const tableRow of jQuery("#gofastTemplateTable tr")) {
                const rowInfo = JSON.parse(jQuery(tableRow).find(".gofast_template_info").text());
                haystacks.name = rowInfo.infos.title.toLowerCase();
                //Store all parent space paths of the results
                haystacks.paths = rowInfo.paths.map(path => Gofast.ITHit.getSpacePath(path))
                let mustNotBeFiltered = false
                if(activeFilters.path == ""){
                    mustNotBeFiltered = haystacks.name.includes(activeFilters.name)
                } else {
                    //Check if the results have at least one path equivalent to the search filter and if the name filter text is in the title.
                    mustNotBeFiltered = haystacks.paths.some(path => path == activeFilters.path) && haystacks.name.includes(activeFilters.name)
                }
                if (mustNotBeFiltered) {
                    jQuery(tableRow).show();
                } else {
                    jQuery(tableRow).hide();
                }
            }
        }

        const activeFilters = {
            name: "",
            path: "",
        };

        // handle template filtering by text
        jQuery("#gofastTemplateNameFilter").on("input", function() {
            if (this.value.trim().length > 2) {
                activeFilters.name = this.value.trim().toLowerCase();
            } else {
                activeFilters.name = "";
            }
            gofastTemplateRefreshFilters();
        });

        // init autocomplete for spaces
        Drupal.attachBehaviors();

        const initTagifyInterval = setInterval(function() {
            if (typeof window.tagify == "undefined" || typeof window.tagify["ac-list-tags-one-space"] == "undefined") {
                return;
            }
            clearInterval(initTagifyInterval);
            window.tagify["ac-list-tags-one-space"].DOM.scope.classList.add("stretchable");
            window.tagify["ac-list-tags-one-space"].settings.maxTags = 1;

            window.tagify["ac-list-tags-one-space"].on('focus', (e) => {
                if(e.detail.tagify.value.length >= 1){
                    $(e.detail.tagify.DOM.input).trigger("blur");
                    Gofast.toast(Drupal.t("You can filter only by one space at a time", {}, {context: "gofast:gofast_cmis"}));

                }
            });
            window.tagify["ac-list-tags-one-space"].on("add", async (e) => {    
                let nid = e.detail.data.value
                await $.get("/essential/get_href_from_nid/"+nid).done((href) => {
                    activeFilters.path = href
                })
                gofastTemplateRefreshFilters();
            });
            window.tagify["ac-list-tags-one-space"].on("remove", (e)=> {
                activeFilters.path = "";
                gofastTemplateRefreshFilters();
            });
        }, 100);

        // precheck matching template if query string is given
        const queryString = new Proxy(new URLSearchParams(window.location.search), {
            get: (searchParams, prop) => searchParams.get(prop),
        });
        const templateQueryString = queryString.template;
        if (templateQueryString != null) {
            jQuery("#gofastTemplateRadio" + templateQueryString).prop("checked", true);
            jQuery("#gofastTemplateRadio" + templateQueryString).trigger("change");
        }

        // init tooltips
        jQuery("[data-toggle='tooltip']").tooltip();
    });
</script>
