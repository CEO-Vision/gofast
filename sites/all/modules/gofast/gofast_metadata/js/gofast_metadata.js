
/**
 * @file
 *
 * Overrides for CTools metadata.
 *
 */


(function ($, Gofast, Drupal) {
  
  Gofast = Gofast || {};

  Drupal.settings.gofast = Drupal.settings.gofast || {};
  Drupal.settings.gofast.metadataEditCount = 0;
  var gofastMetadataLabelClickEvent = function () {
    $(this).addClass('d-none')
    let fieldContainer = $(this).next();
    let field = fieldContainer.find(".editable-processed");
    let select = fieldContainer.hasClass("document__editable--select");
    let selectAcAuthor = fieldContainer.hasClass("document__editable--selectAcAuthor");
    let selectTags = fieldContainer.hasClass("document__editable--tags");
    fieldContainer.removeClass('d-none');
    if (select == true || selectTags == true || selectAcAuthor == true) {
      field.select2('open');
    } else  {
      field.focus().click();
    }
  };
  var gofastComputeSelectTemplate = function (item) {
    var flagSvg = $(item.element).data('flag');
    if (flagSvg != undefined){
      var span = $("<div class='d-flex'><div class='symbol symbol-20 mr-3' ><img src='" + flagSvg + "'/></div><span class='navi-text'>" + item.text + "</span></div>");
      return span;
    }else{
      // if text is too ellipsized, we want to be sure it will still show in its entirety on hover
      return $("<div title='" + item.text + "'>" + item.text + "</div>");
    }
  };

  Drupal.behaviors.metadata = {
    attach: async function (context) {
      // we have to wait a little bit for most of the DOM to be rendered to prevent issues with select2
      // @see the "hacky solution" in https://github.com/select2/select2/issues/6154
      await new Promise((resolve) => setTimeout(() => resolve(), 250));

      // call this when needed to reset a select element back to its previous value
      function resetSelectValue(elem) {
          // set the select value
          const originalValue = elem.attr("data-original-value");
          // and the trigger butotn value as well
          const label = elem.parent().parent().find('.document__editable--label');
          let displayValue = "";
          if (elem.attr("data-original-value")) {
            displayValue = elem.find("option[value='" + originalValue + "']").html();
          } else {
            displayValue = Drupal.t("None");
          }
          label.html(displayValue);
          label.prop("title", displayValue);
          // retrigger events to update other related attributes
          elem.val(originalValue).trigger("change");
          label.click();
          elem.select2('open');
          elem.select2('close');
      }

      async function postMetadata(elem, spinner, value = false) {
        if(typeof Gofast.hooks.beforePostMetadata == "object") {
          let shouldPostMetadata = true;
          for (const callback of Gofast.hooks.beforePostMetadata) {
              hasSucceeded = await callback(elem, value); // wait for the hook implementation to resolve
              if (!hasSucceeded) {
                shouldPostMetadata = false;
              }
          }
          if (!shouldPostMetadata) {
            resetSelectValue(elem);
            return;
          }
        }

        var node_nid = elem.attr("data-id") != false ? elem.attr("data-id") : false;
        var vid = elem.attr("data-vid") != false ? elem.attr("data-vid") : false;
        var filed_name = elem.attr("name") != false ? elem.attr("name") : false;
        var is_timestamp = elem.attr("data-is-timestamp") != false ? elem.attr("data-is-timestamp") : false;
        
        // GoFAST-7647 - prevent poll refresh at field update or edit
        Gofast.incrementMetadataEditCounter();
        if(filed_name != "field_external_page_url"){
          spinner.removeClass('d-none')
        }

          var value = value || elem.val();
          $.ajax({
            url: Drupal.settings.gofast.baseUrl + '/update_node_field',
            type: 'POST',
            dataType: 'json',
            data: {
              'name': filed_name,
              'value': value,
              'pk': node_nid,
              'vid': vid,
              'is_timestamp': is_timestamp,
            },
            success: function (content, status) {           
              $.get(Drupal.settings.gofast.baseUrl + "/gofast/metadata/node/" + Gofast.get("node").id + "/load", function (data) {
                data = JSON.parse(data);
                if(filed_name == "language"){
                  // Replace src img attributes with the new flag path
                   $('.metadata-language-flag').attr('src', data.flag);
                }
                if(filed_name == "field_external_page_url"){
                  const externalLinksData = JSON.parse(data.field_external_link_custom_data.und[0].value)
                  Object.keys(externalLinksData).forEach((url) => {
                    if($(`.tmp-external-link[data-url="${url}"]`).length){
                      const urlObj = new URL(url);
                      const newLinkBadge = `<div class="text-truncate ml-auto">
                                              <a class="text-truncate" target="_blank" href="${url}" title="${externalLinksData[url].title}">
                                                <img src="${urlObj.origin}/favicon.ico" onerror="Gofast.metadata.handleExternalLinkIconError(event)" class="external-url-icon">
                                                <span class="external-link-name">${externalLinksData[url].title}</span>
                                              </a>
                                            </div>
                                            <a type="button" class="ml-auto pl-1 d-flex" onclick="Gofast.metadata.updateExternalLink(event, '${url}')">
                                              <i class="fas fa-edit fa-sm pr-0"></i>
                                            </a>`;
                      $(`.tmp-external-link[data-url="${url}"]`).replaceWith(newLinkBadge)
                    }
                  })
                }
                Drupal.settings.gofast.context.entity = data;
                Gofast.decrementMetadataEditCounter();
              });
              spinner.addClass('d-none');
            }
          });
      }



      $('.document__editable--processe:not(.editable-processed)').addClass('editable-processed').each(function () {

        let field = $(this);
        let fieldContainer = field.parent();
        let label = fieldContainer.parent().find('.document__editable--label');
        let isSwitchInput = field.hasClass("document__editable--switch");
        let select = fieldContainer.hasClass("document__editable--select");
        let selectAcAuthor = fieldContainer.hasClass("document__editable--selectAcAuthor");
        let selectTags = fieldContainer.hasClass("document__editable--tags");
        let spinner = fieldContainer.parent().find(".document__editable--spinner");
        let GofastMetadataURLPattern = /^((([A-Za-z]{3,9}:(?:\/\/)?)(?:[\-;:&=\+\$,\w]+@)?[A-Za-z0-9\.\-]+|(?:www\.|[\-;:&=\+\$,\w]+@)[A-Za-z0-9\.\-]+)((?:\/[\+~%\/\.\w\-_]*)?\??(?:[\-\+=&;%@\.\w_]*)#?(?:[\.\!\/\\\w]*))?)$/;

        label.on('click', gofastMetadataLabelClickEvent)

        // BEGIN switch input process
        if (isSwitchInput == true) {
          const switchInput = field.find('input[type="checkbox"]');
          switchInput.on("change", function () {
            let switchValue = switchInput.is(":checked") ? 1 : -1;
            postMetadata(switchInput, spinner, switchValue);
          });
        }
        // END of switch input process

        // BEGIN Normal select process
        if (select == true) {
          field.select2({
            placeholderOption: function () { return undefined; },
            width: '100%',
            templateResult: gofastComputeSelectTemplate,
            templateSelection: gofastComputeSelectTemplate,
            dropdownCssClass: "gofastMetadataDropdown",
          });

          // prevent dropdown from opening when clearing the field
          field.on('select2:opening', function (e) {
            var $dropdown = field.data('select2').dropdown.$dropdownContainer;
            var dropdownTop = $dropdown[0].style.top;
            if (dropdownTop == "0px") {
              e.preventDefault()
            }
          });

          field.on('select2:open', function(e) {
            Gofast.incrementMetadataEditCounter();
            if(field.attr("name") == "field_external_page_url"){
              fieldContainer.find(".select2-selection__rendered").on("click", (e) => {
                // Prevent blocking "x" button on tags
                if($(e.target).hasClass("select2-selection__choice__remove")){
                  return
                }
                e.preventDefault()
                e.stopImmediatePropagation()
                fieldContainer.find(".select2-search__field").focus()
              })
            }
          }); 

          field.on('select2:close', function () {
            fieldContainer.addClass('d-none');
            label.removeClass('d-none');
            Gofast.decrementMetadataEditCounter(); 
          });
          
          field.on("select2:selecting", function (data) {
            $(this).attr("data-original-value", $(this).val());
          });

          field.on('select2:select select2:clear', function (data) {
            if (data.currentTarget.classList.contains("external-links")) {
              return;
            }
            // no wrapper: something is wrong, don't save anything
            if (!label[0]) {
              return;
            }
            // untemplated select
            if (label[0].text && label[0].text != data.params.data.text) {
              // anticipate FF-specific data structure
              if (data.params.data[0]) {
                data.params.data = data.params.data[0];
              }
              if (data.params.data.text.length === 0) {
                label[0].text = Drupal.t('None');
              } else {
                label[0].text = data.params.data.text;
              }
            }
            if (data.type == "select2:clear") {
              label[0].text = Drupal.t('None');
              data.params.data.id = "";
            }
            // templated select
            if (!label[0].text) {
              const selectTemplate = gofastComputeSelectTemplate(data.params.data);
              label.html(selectTemplate);
            }
            // we pass the value as a param instead of setting it to the field in order to avoid showing the user a technical/english value
            postMetadata($(this), spinner, data.params.data.id);
          });
        }
        // END of normal slect process

        // BEGIN select tags process
        if (selectTags == true) {
          field.select2({
            tags: true,
            placeholderOption: function () { return undefined; },
            width: '100%',
            tokenSeparators: [',',''],
            placeholder: Drupal.t("Add your tags here"),
            /* the next 2 lines make sure the user can click away after typing and not lose the new tag */
            selectOnClose: false,
            closeOnSelect: false,
          });

          var oldTagsArray = field.val()

          field.on('select2:open', function() {
            fieldContainer.removeClass('d-none');
            field.data("select2").dropdown.$dropdownContainer.hide();
            Gofast.incrementMetadataEditCounter();
          });

          field.on('select2:select', onTagEvent);
          field.on('select2:unselect', onTagEvent);
          field.on('select2:close', onTagEvent);
          // we have to use the document scope to prevent bubbling issues with the select2 plugin
          $(document).on('keyup', '.select2-search__field', ({target}) => {
            if (typeof field.data("select2") == "undefined") {
              return;
            }
            if (target.value.length === 0) {
              field.data("select2").dropdown.$dropdownContainer.hide();
            } else {
              field.data("select2").dropdown.$dropdownContainer.show();
            }
          });
          $(document).on('paste', '.select2-search__field', onPasteEvent);

          function onPasteEvent(e) {
            const pastedData = e.originalEvent.clipboardData.getData('text');
            if (GofastMetadataURLPattern.test(pastedData)) {
              // if needed, hide dropdown and unhide it on select2:open event
              setTimeout(() => {
                // e.originalEvent.target.dispatchEvent(keyboardEvent);
                let linksValue = field.val();
                linksValue.push(pastedData);
                field.val(linksValue);
                field.trigger("change");
                e.originalEvent.target.value = "";
              }, 100);
            }
          }

          function onTagEvent(e) {
            if (e.type == 'select2:select') {
              let newTagsArray = [...oldTagsArray];
              newTagsArray.push(...field.val());
              field.val(newTagsArray);
              fieldContainer.find(".select2-search__field").val("")
            }
            if (e.type == 'select2:unselect') {
              e.preventDefault();
              
              let allValues = $.map(fieldContainer.parent().find($(".external-links-list a[href]")), (element) => {
                return $(element).attr("href");
              })
              let removedLink = e.params.data.id;
              $(`.external-links-list a[href='${removedLink}']`).parent().parent().remove()
              // Remove the link from the list of links
              allValues = allValues.filter(link => link != removedLink);
              // Prevent updating again by updating the stored oldTagsArray value
              oldTagsArray = allValues;
              if(allValues.length == 0){
                label[0].innerHTML = Drupal.t('None')
              }

              Gofast.incrementMetadataEditCounter();
              $.post("/update_node_field", {
                pk: $(this).attr("data-id"),
                name: "field_external_page_url",
                value: allValues,
              }).done(() => {
                Gofast.decrementMetadataEditCounter();
              })
            }
            if (e.type == "select2:close") {
              Gofast.decrementMetadataEditCounter(); 
              fieldContainer.addClass('d-none');
              label.removeClass('d-none');
              var newTagsArray = field.val();
              field.data("select2").dataAdapter.$search.val("");

              if (JSON.stringify(oldTagsArray) == JSON.stringify(newTagsArray)) {
                return;
              }
              if (newTagsArray && newTagsArray.length > 0) {
                var hasValid = true;
                newTagsArray.forEach((element, index) => {
                  const external_link_url = element;
                  if (!GofastMetadataURLPattern.test(external_link_url)) {
                    Gofast.toast(external_link_url + " " + Drupal.t("is not a valid url", {}, {context: 'gofast:gofast_cmis'}), "warning");
                    delete newTagsArray[index];
                    // Remove the tag in the select2
                    $(`.select2-selection__choice[title='${Gofast.htmlEncode(external_link_url)}']`).remove()
                    hasValid = false;
                  }
                });
                field.val(newTagsArray);
                if (hasValid) {
                  const addedLinks = newTagsArray.filter(item => !oldTagsArray.includes(item));
                  addedLinks.forEach((url) => {
                    var emptyBadge = $(`<li class="text-left">
                                        <div class="btn link-badge w-100 d-flex">
                                          <div class="w-100 d-flex justify-content-center tmp-external-link" data-url="${url}">&nbsp<div class="spinner spinner-sm" style="transform: translateX(-0.75rem);"></div></div>
                                        </div>
                                      </li>`)
                    if(fieldContainer.parent().find($(".external-links-list")).length == 0){
                      fieldContainer.parent().find("> .external-links-list-container").html($('<ul class="p-0 m-0 list-unstyled external-links-list">'));
                    }
                    $(".external-links-list").append(emptyBadge);
                  })
                  oldTagsArray = newTagsArray
                  postMetadata($(this), spinner);
                }
              } else {
                label[0].innerHTML = Drupal.t('None')
              }
            }
          }
        }
        // END of select tags process

        // Begin Select With Autocomplete Process
        if (selectAcAuthor == true) {
          var URL = Drupal.settings.gofast.baseUrl + '/gofast/gofast_ac_config';
          var newOption = new Option(Drupal.t('None'), "", false, false);

          field.select2({
              placeholderOption: function () { return undefined; },
              width: '100%',
              ajax: {
              url: URL,
              params: {
                data: newOption
              },
              dataType: "json",
              type: "POST",
              data: function (params) {
                var queryParameters = {
                  str: params.term,
                  get_user : true
                }
                return queryParameters;
              },
              processResults: function (data, params) {
                var resultArray = {
                  results: $.map(data, function (item) {
                    return {
                      text: item.display_name,
                      id: item.display_name
                    }
                  })
                };

                resultArray.results.push({
                    text: params.term,
                    id: params.term
                  }
                );

                return resultArray;
              }
            }
          });

          field.on('select2:open', function() {
            Gofast.incrementMetadataEditCounter();
          });
          $('.gofast_metadata_field').each(function () {
            var selectElement = $(this);
            selectElement.on('select2:open', function () {
              var dropdown = $('.select2-dropdown');
              var dropdownOffset = dropdown.offset().left + dropdown.outerWidth();
              if (dropdownOffset > $(window).width()) {
                dropdown.addClass('select2-dropdown--dropleft');
              }
            });
          }).on('select2:close', function () {
            $('.select2-dropdown').removeClass('select2-dropdown--dropleft');
          });

          field.on('select2:close', function () {
            Gofast.decrementMetadataEditCounter();
            fieldContainer.addClass('d-none');
            label.removeClass('d-none');
          });

          field.on('select2:select', function (data) {
            if (label[0].text != data.params.data.text) {
                     
              // force update value of field (sometimes it's not updated as it's supposed to)
              $(this).val(data.params.data.id);  
              
              postMetadata($(this), spinner);
              if (data.params.data.text.length === 0) {
                label[0].text = Drupal.t('None');
              } else {
                label[0].text = data.params.data.text;
              }
            }
          });
        }

        // End Select With Autocomplete Process
        
        
        // Detect datetimepicker change (#GOFAST-7536)
        if(field.hasClass('gofastDatepicker')){
          field.on("show", function() {
            Gofast.incrementMetadataEditCounter();
          });
          field.on("hide", function() {
            Gofast.decrementMetadataEditCounter();
          });
          field.on('changeDate',function(){
            setTimeout(function () {
              if (label[0].text != field.val()){
                postMetadata(field, spinner);
                if (field.val().length === 0) {
                  label[0].text = Drupal.t('None');
                }else{
                  label[0].text = field.val();
                }
              }
            }, 500);
            fieldContainer.addClass('d-none');
            label.removeClass('d-none');
          });
        }


        // Handle event for clear button
        $('#document__editable--input--clear:not(.processed)').addClass('processed').on("mousedown", function(e) {
          e.preventDefault();
          e.stopPropagation();
          $('.document__editable--input > input').val('');
          return;
        })

        // Trigger post metadata on save
        field.blur(function () {
            if( select == false){
                setTimeout(function () {
                  if (label[0].text != field.val()){
                    postMetadata(field, spinner);
                    if (field.val().length === 0) {
                      label[0].text = Drupal.t('None');
                    }else{
                      label[0].text = field.val();
                    }
                  }
                }, 500);
                fieldContainer.addClass('d-none');
                label.removeClass('d-none');
            }
        });
      });

      //Call to get subscribe button
      Drupal.getSubButtonHtml = function (termID) {
        return $.ajax({
          url: Drupal.settings.gofast.baseUrl + '/ac/get/subscribe/' + termID,
          type: 'GET',
          dataType: 'html',
          async: false,
          success: function (content, status) {
            value = '<li>' + content + '</li></ul>';
            $.getScript('/sites/all/modules/flag/theme/flag.js', function () {
              Drupal.behaviors.flagLink.attach(document);
            });
          }
        });
      }

      $(document).bind('flagGlobalBeforeLinkUpdate', function (event, data) { //Rebuilding tag name
        let tmpdata = decodeURI(data.newLink);
        if(!tmpdata.includes('flag-subscribe-term-')) return;
        let tmp1 = tmpdata.split('flag-subscribe-term-');
        let tmp2 = tmp1[1].split('">');
        let newtag = tmp2[0].replace('**', '/');
        var html = Drupal.getSubButtonHtml(newtag);
        data.newLink = html.responseText;
      });
    }
  }
  Gofast.metadata = Gofast.metadata ?? {};
  Gofast.metadata.updateExternalLink = function(e, url){
    // Prevent triggering editable input
    e.preventDefault()
    e.stopImmediatePropagation()
    let nid = $("#nodeContainer").attr("data-nid");
    Drupal.CTools.Modal.showCtoolsModal(`/gofast/metadata/ajax/modal/update_external_link/${nid}?url=${url}`);
  }
  Gofast.metadata.refreshExternalLinksData = function(url, newTitle, newIcon){
    $(`.external-links-list a[href='${url}'] > .external-link-name`).text(newTitle)
    $(`.external-links-list a[href='${url}'] > .external-url-icon`).attr("src", newIcon)
  }
  Gofast.metadata.handleExternalLinkIconError = function(e){
    const defaultIcon = $('<i class="fas fa-external-link-square-alt mr-2"></i>')
    $(e.target).replaceWith(defaultIcon)
  }
})(jQuery, Gofast, Drupal);
