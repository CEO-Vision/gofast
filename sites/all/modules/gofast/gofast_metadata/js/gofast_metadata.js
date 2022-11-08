
/**
 * @file
 *
 * Overrides for CTools metadata.
 *
 */


(function ($, Drupal) {
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

  Drupal.behaviors.metadata = {
    attach: function (context) {
      function postMetadata(elem, spinner) {
        var node_nid = elem.attr("data-id") != false ? elem.attr("data-id") : false;
        var vid = elem.attr("data-vid") != false ? elem.attr("data-vid") : false;
        var filed_name = elem.attr("name") != false ? elem.attr("name") : false;
        
        // GoFAST-7647 - prevent poll refresh at field update or edit
        Gofast.incrementMetadataEditCounter();

        spinner.removeClass('d-none')
          var value = elem.val();
          $.ajax({
            url: Drupal.settings.gofast.baseUrl + '/update_node_field',
            type: 'POST',
            dataType: 'json',
            data: {
              'name': filed_name,
              'value': value,
              'pk': node_nid,
              'vid': vid
            },
            success: function (content, status) {           
              $.get(Drupal.settings.gofast.baseUrl + "/gofast/metadata/node/" + Gofast.get("node").id + "/load", function (data) {
                data = JSON.parse(data);
                if(filed_name == "language"){
                  // Replace src img attributes with the new flag path
                   $('.metadata-language-flag').attr('src', data.flag);
                }
                Drupal.settings.gofast.context.entity = data;
                Gofast.decrementMetadataEditCounter();
              });
              if (filed_name == "field_external_page_url") {
                Drupal.gofast_cmis.reloadPreview();
              }
              spinner.addClass('d-none');
            }
          });
      }



      $('.document__editable--processe:not(.editable-processed)').addClass('editable-processed').each(function () {

        let field = $(this);
        let fieldContainer = field.parent();
        let label = fieldContainer.parent().find('.document__editable--label');
        let select = fieldContainer.hasClass("document__editable--select");
        let selectAcAuthor = fieldContainer.hasClass("document__editable--selectAcAuthor");
        let selectTags = fieldContainer.hasClass("document__editable--tags");
        let spinner = fieldContainer.parent().find(".document__editable--spinner");
        let GofastMetadataURLPattern = /((([A-Za-z]{3,9}:(?:\/\/)?)(?:[\-;:&=\+\$,\w]+@)?[A-Za-z0-9\.\-]+|(?:www\.|[\-;:&=\+\$,\w]+@)[A-Za-z0-9\.\-]+)((?:\/[\+~%\/\.\w\-_]*)?\??(?:[\-\+=&;%@\.\w_]*)#?(?:[\.\!\/\\\w]*))?)/;

        label.on('click', gofastMetadataLabelClickEvent)

        // BEGIN Normal select process
        if (select == true) {
          field.select2({
            placeholderOption: function () { return undefined; },
            width: '100%',
            templateResult: function (item) {
              var flagSvg = $(item.element).data('flag');
              if (flagSvg != undefined){
                var span = $("<div class='d-flex'><div class='symbol symbol-20 mr-3' ><img src='" + flagSvg + "'/></div><span class='navi-text'>" + item.text + "</span></div>");
                return span;
              }else{
                return item.text
              }
            },
            templateSelection: function (item) {
              var flagSvg = $(item.element).data('flag');
              if (flagSvg != undefined) {
                var span = $("<div class='d-flex'><div class='symbol symbol-20 mr-3' ><img src='" + flagSvg + "'/></div><span class='navi-text'>" + item.text + "</span></div>");
                return span;
              }else{
               return item.text
              }
            }
          });

          field.on('select2:open', function() {
            //reselect right value:
            $(this).val(field.val());
            $(this).trigger('change');

            label[0].text = field.val();
            Gofast.incrementMetadataEditCounter();
          });

          field.on('select2:close', function () {
            fieldContainer.addClass('d-none');
            label.removeClass('d-none');
            Gofast.decrementMetadataEditCounter(); 
          });

          field.on('select2:select', function (data) {
            if (data.currentTarget.id == "external-Links") {
              return;
            }
            if (label[0].text != data.params.data.text) {
              if (data.params.data.text.length === 0) {
                label[0].text = Drupal.t('None');
              } else {
                label[0].text = data.params.data.text;
              }

              // force update value of field (sometimes it's not updated as it's supposed to)
              $(this).val(data.params.data.id);
              postMetadata($(this), spinner);
            }
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
            if (target.value.length == 0) {
              field.data("select2").dropdown.$dropdownContainer.hide();
              return;
            }
            field.data("select2").dropdown.$dropdownContainer.show();
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
            }
            if (e.type == 'select2.unselect') {
              e.preventDefault();
            }
            if (e.type = "select2:close") {
              Gofast.decrementMetadataEditCounter(); 
              fieldContainer.addClass('d-none');
              label.removeClass('d-none');
              var newTagsArray = field.val();
              field.data("select2").dataAdapter.$search.val("");

              if (JSON.stringify(oldTagsArray) == JSON.stringify(newTagsArray)) {
                return;
              }
              if (newTagsArray && newTagsArray.length > 0) {
                var inputText = "<ul class='list-unstyled pl-3 pt-4 text-left'>";
                var hasValid = false;
                newTagsArray.forEach((element, index) => {
                  const external_link_url = element;
                  if (!GofastMetadataURLPattern.test(external_link_url)) {
                    Gofast.toast(external_link_url + " " + Drupal.t("is not a valid url", {}, {context: 'gofast:gofast_cmis'}), "warning");
                    delete newTagsArray[index];
                  } else if(GofastMetadataURLPattern.test(external_link_url)) {
                    inputText += '<li> <i class="fas fa-external-link-square-alt mr-2"></i> <a class="text-dark text-hover-primary text-truncate font-size-sm" href="' + external_link_url + '" >' + element + '</a> </li>';
                    hasValid = true;
                  }
                });
                inputText += '</ul>';
              }
              if (hasValid) {
                field.val(newTagsArray);
                label[0].innerHTML = inputText;
                postMetadata($(this), spinner);
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
                  },{
                    text: Drupal.t('None'),
                    id: 'null'
                  }
                );

                return resultArray;
              }
            }
          });

          field.on('select2:open', function() {
            Gofast.incrementMetadataEditCounter();
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
})(jQuery, Drupal);
