
/**
 * @file
 *
 * Overrides for CTools Autocomplete.
 *
 */

(function ($, Drupal) {

  Drupal.behaviors.initTagify = {
    attach: function (context) {
      var inputElmList = document.querySelectorAll('input[name^="ac-list-tags"]'); // get all inputs whose attribute name begins with substring 'ac-list-tags'
        inputElmList.forEach(function (inputElm) {
          if (!$(inputElm).hasClass('js-tagify-processed')) {
            var dataList = null;
            var elementValue = $("#edit-actagify-" + inputElm.name).val() || inputElm.value || inputElm.defaultValue;

            if (elementValue != undefined && elementValue != "null" && elementValue != "") {
              dataList = elementValue;
              inputElm.value = dataList;
            }
            gofastInitTagify(inputElm, dataList);
            $(inputElm).addClass('js-tagify-processed');
          }
        });

      function gofastInitTagify(inputElm, dataList) {
        const emailRegex = /^[a-zA-Z0-9.!#$%&'*+/=?^_`{|}~-]+@[a-zA-Z0-9-]+(?:\.[a-zA-Z0-9-]+)*$/;
        var enforce = !inputElm.hasAttribute("data-enforce");
        var mode = inputElm.hasAttribute("data-oc-select-one");
        var input_id = inputElm.id;
        var is_metadata = input_id == "edit-field-taget-link" || input_id == "edit-field-keywords";
        var custom_dropdown =  input_id == "edit-field-taget-link" || input_id == "edit-list-documents" || input_id == "edit-field-keywords" || input_id.startsWith("edit-translations");
        var tagify = new Tagify(inputElm, {
          placeholder: Drupal.t('None'),
          tagTextProp: 'name', // very important since a custom template is used with this property as text. allows typing a "value" or a "name" to match input with whitelist
          enforceWhitelist: enforce, // true : Do Not allow adding value that not in the whitelist
          skipInvalid: false, // do not temporarily add invalid tags
          dropdown: {
            classname: custom_dropdown ? "gofast_tagify_dropdown" : "",
            enabled: 3,            // show suggestion after 3 typed character
            fuzzySearch: true,    // Do not match only suggestions that starts with the typed characters
            caseSensitive: true,   // allow adding duplicate items if their case is different
            maxItems: 20,           // mixumum allowed rendered suggestions
            enabled: 1,             // show suggestions on focus 1 to set True 0 for false
            closeOnSelect: true,    // hide the suggestions dropdown once an item has been selected
            searchKeys: ['name', 'email', 'request']// very important to set by which keys to search for suggestions when typing
          },
          templates: {
            tag: tagTemplate,
            dropdownItem: suggestionItemTemplate
          },
          whitelist: dataList != null ? JSON.parse(dataList) : []
        }), controller; // for aborting the call
        if(typeof tagify.on == "undefined"){
          //Element is already tagified
          return;
        }
        
        // listen to any keystrokes which modify tagify's input
        tagify.on('keydown', onInput);

        // if the user is pasting a node name or link, we still need to trigger the autocomplete
        if (input_id == "edit-field-taget-link" || input_id == "edit-list-documents" || input_id.startsWith("edit-translations")) {
          tagify.on('invalid', onInput);
        }

        // if the tagify is in the metadata tab, we update the editing/updating field counter
        if (is_metadata) {
          tagify.on("focus", function () {
            Gofast.incrementMetadataEditCounter();
          });
          tagify.on("blur", function () {
            Gofast.decrementMetadataEditCounter();
          });
        }

        // prevent value from being undefined on paste events on "free tags" inputs
        if (!enforce) {
          tagify.on('add', async function(e) {
            if (e.detail.tag.value != "undefined") {
              return;
            }
            let newTag = { value: e.detail.data.name, name: e.detail.data.name };
            if (emailRegex.test(e.detail.data.name)) {
              newTag = await getUserFromMail(e.detail.data.name);
            }
            tagify.replaceTag(e.detail.tag, newTag);
            let isDuplicate = tagify.value.filter(tag => tag.name == e.detail.data.name).length > 1;
            if (isDuplicate) {
              const allTags = tagify.value;
              tagify.removeAllTags();
              tagify.addTags(allTags);
            }
          });
        }

        // Mode For select one element
        if (mode == true){
          tagify.on('add', onAddTag)
                .on('remove', onRemoveTag);

          function onAddTag() {
            tagify.off('keydown', onInput) // example of removing a custom Tagify event
            tagify.settings.whitelist.length = 0;  // reset the whitelist
          }

          function onRemoveTag() {
            tagify.on('keydown', onInput) // example of activating a custom Tagify event
          }
        }

        async function getUserFromMail(user_mail) {
          let newTag = {};
          await $.post("/gofast/get/user_from_mail", {user_mail}).done(function (data) {
            if (data.error) {
              newTag = { value: user_mail, name: user_mail, type: "email", email: user_mail };
            } else {
              newTag = data;
            }
            tagify.settings.whitelist.push(newTag, ...tagify.value);
            tagify.addTags([newTag]);
          });
          return newTag;
        }

        async function onInvalidEmail(e) {
          if (!emailRegex.test(e.detail.data.name)) {
            return;
          }
          let newTag = await getUserFromMail(e.detail.data.name);
          tagify.settings.whitelist.push(newTag, ...tagify.value);
          tagify.addTags([newTag]);
        }

        if (inputElm.hasAttribute("data-email")) {
          tagify.on('invalid', onInvalidEmail);
        }

        if (inputElm.hasAttribute("data-taxonomy_term") && input_id == "edit-field-keywords"){
          $('#' + input_id).parent().find("tags.js-tagify x.tagify__tag__removeBtn").hide();
          $('#' + input_id).parent().find("tags.js-tagify div.gofast-sub-icon span.flag-wrapper.flag-subscribe-term").addClass('d-flex justify-content-center align-items-center');


          tagify.on('focus', onTagifyFocusBlur)
                .on('blur', onTagifyFocusBlur)
                .on('remove', onTagifyFocusBlur)
                .on('dropdown:select', onTagifyFocusBlur);
        }

        if (inputElm.hasAttribute("data-taxonomy_term") && input_id == "edit-field-tags"){
          $('#' + input_id).parent().find("tags.js-tagify x.tagify__tag__removeBtn").hide();
          $('#' + input_id).parent().find("tags.js-tagify div.gofast-sub-icon span.flag-wrapper.flag-subscribe-term").addClass('d-flex justify-content-center align-items-center');


          tagify.on('focus', onTagifyFocusBlur)
                .on('blur', onTagifyFocusBlur)
                .on('remove', onTagifyFocusBlur)
                .on('dropdown:select', onTagifyFocusBlur);
        }


        if (inputElm.hasAttribute("data-node") && input_id == "edit-field-taget-link") {
          $('#' + input_id).parent().find("tags.js-tagify x.tagify__tag__removeBtn").hide();
          $('#' + input_id).parent().find("tags.js-tagify tag").css("background-color", "white");

          tagify.on('focus', onTagifyFocusBlur)
            .on('blur', onTagifyFocusBlur)
            .on('remove', onTagifyFocusBlur)
            .on('dropdown:select', onTagifyFocusBlur);
        }
        //In case of space, with data-extract-user you can extract all members from Group Space
        if(inputElm.hasAttribute("data-extract-user")){
            tagify.on('dropdown:select', onTagifySelectItem);
        }

        function onTagifySelectItem(e){
            if(e.detail.data.type==='node' || e.detail.data.type == 'userlist'){
                if(e.detail.data.type == 'userlist'){
                  var is_userlist = "true";
                }else{
                  var is_userlist = "false";
                }
                $('#' + input_id).closest('form').find(':submit').prop('disabled',true);
                tagify.loading();
                $.get(Drupal.settings.gofast.baseUrl + '/gofast/get/user_from_space/'+e.detail.data.value+"?is_userlist="+is_userlist, function(result){
                    if(result){
                      result.forEach(function (inputElm) {                      
                        let formattedData = [
                          {
                            node_type: "user",
                            type: "user",
                            avatar: inputElm.avatar,
                            name: inputElm.name,
                            value: inputElm.value,
                          }
                        ];
                        tagify.settings.whitelist.push(...formattedData, ...tagify.value);
                        tagify.addTags(formattedData);
                      } );                                          
                    }
                    $('#' + input_id).closest('form').find(':submit').prop('disabled',false);
                });
            }
        }

        // specifique pour la page document
        function onTagifyFocusBlur(e) {
          if (e.type == 'focus' ) { // || e.type == 'click'
            //Stop the Polling
            if (!is_metadata) {
              Gofast.Poll.abort();
            }
            $('#' + input_id).parent().find('tags.js-tagify').addClass("metadata-focus");
            $('#' + input_id).parent().find("tags.js-tagify x.tagify__tag__removeBtn").show();

            if (input_id == "edit-field-taget-link") {
              cleanInput();
              $('#' + input_id).parent().find("tags.js-tagify tag").css("background-color", "#EBEDF3");
            }

            if (input_id == "edit-field-keywords"){
              $('#' + input_id).parent().find("tags.js-tagify div.gofast-sub-icon").hide();
            }
          } else if (e.type == 'blur' && !$(e.detail.relatedTarget).hasClass("tagify__tag")){
            var node_nid = inputElm.hasAttribute("data-pk") == true ? inputElm.getAttribute("data-pk") : null
            var vid = inputElm.hasAttribute("data-vid") == true ? inputElm.getAttribute("data-vid") : null
            var name = inputElm.hasAttribute("data-name") == true ? inputElm.getAttribute("data-name") : null

                $.ajax({
                  url: Drupal.settings.gofast.baseUrl + '/update_node_field',
                  type: 'POST',
                  dataType: 'json',
                  data: {
                    'name': name,
                    'value': tagify.value,
                    'pk': node_nid,
                    'vid': vid
                    },
                  success: function (content, status) {
                    // We can add a validate messge here , or in the php function
                  }
                });

            $('#' + input_id).parent().find('tags.js-tagify').removeClass("metadata-focus");
            $('#' + input_id).parent().find("tags.js-tagify x.tagify__tag__removeBtn").hide();

            if (input_id == "edit-field-taget-link") {
              $('#' + input_id).parent().find("tags.js-tagify tag").css("background-color", "white");
            }

            if (input_id == "edit-field-keywords") {
              $('#' + input_id).parent().find("tags.js-tagify div.gofast-sub-icon").show();
            }
            
            //Run the polling
            if (!is_metadata) {
              Gofast.Poll.run();
            }
          } else if (e.type == 'remove' || e.type == 'dropdown:select') {
            $('#' + input_id).parent().find(".tagify__input").focus().click();
          }
        }

        function triggerTagifyAutocomplete(value) {
          tagify.settings.whitelist.length = 0; // reset the whitelist

          // https://developer.mozilla.org/en-US/docs/Web/API/AbortController/abort
          // we abort the previous request if it is still running
          controller && controller.abort();
          controller = new AbortController();

          // clear current whitelist
          tagify.settings.whitelist.length = 0; // reset current whitelist
          // show loader & hide suggestions dropdown (if opened)
          tagify.loading(true).dropdown.hide.call(tagify);
          var url = Drupal.settings.gofast.baseUrl + '/gofast/gofast_ac_config';
          var formData = new FormData();
          formData.append('str', value);
          formData.append('get_spaces', inputElm.hasAttribute("data-get-spaces"));
          formData.append('get_user', inputElm.hasAttribute("data-user") == true ? true : false);
          formData.append('get_node', inputElm.hasAttribute("data-node") == true ? true : false);
          formData.append('vid', inputElm.hasAttribute("data-vid") == true ? inputElm.getAttribute("data-vid") : false);
          formData.append('enforce', inputElm.hasAttribute("data-enforce") == true ? true : false);
          formData.append('broadcast', inputElm.hasAttribute("data-broadcast") == true ? true : false);
          formData.append('get_userlist', inputElm.hasAttribute("data-userlist") == true ? true : false);
          formData.append('get_taxonomy_term', inputElm.hasAttribute("data-taxonomy_term") == true ? true : false);
          formData.append('input_id', input_id);
          formData.append('get_email', inputElm.hasAttribute("data-email"));         
          // Additional data
          inputElm.hasAttribute("data-space-nid") == true ? formData.append('space_nid', inputElm.getAttribute("data-space-nid")) : false;
          inputElm.hasAttribute("data-language") == true ? formData.append('node_language', inputElm.getAttribute("data-language")) : false;

          fetch(url, { signal: controller.signal, method: "POST", body: formData })
            .then(RES => RES.json())
            .then(function (newWhitelist) {
              // replace tagify "whitelist" array values with new values
              // and add back the ones already choses as Tags
              tagify.settings.whitelist.push(...newWhitelist, ...tagify.value);
              // render the suggestions dropdown
              tagify.loading(false).dropdown.show.call(tagify, value);
              if (newWhitelist.length)  {
                return true;
              }
            }).catch((err) => {
              console.log(err);
            });;
          return false;
        }

        function checkForLinkInput(value, e) {
          const nodeURLRegex = /^(https?:\/\/?)?(www\.)?[A-Za-z0-9\W_]+\/node\/([0-9]+).*/;
          if (!value.match(nodeURLRegex)) {
            return "no match";
          }
          const nodeIDURLMatch = value.match(nodeURLRegex)[3];
          if (nodeIDURLMatch) {
            let languageFilter = false;
            if (e.detail.tagify.DOM.originalInput.hasAttribute("data-language")) {
              languageFilter = e.detail.tagify.DOM.originalInput.getAttribute("data-language")
            }
            fetch(Drupal.settings.gofast.baseUrl + '/gofast/metadata/node/' + nodeIDURLMatch + '/load?icon=true')
              .then(response => response.json())
              .then(data => {
                if (languageFilter && languageFilter != data.language) {
                  return "wrong language";
                }
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

        function cleanInput() {
          tagify.settings.whitelist.length = 0; // reset the whitelist
          // hide loading animation and hide the suggestions dropdown
          tagify.loading(false).dropdown.hide.call(tagify);
        }

        // specifique pour les formulaires
        function onInput(e) {    
          clearTimeout(Gofast.tagifyInterval);
          Gofast.tagifyInterval = setTimeout(function(){
            var value = "";
            // keydown is mandatory if we want to handle "edge" cases such as a a copy-paste performed after filling and emptying the input
            if (e.type == "keydown") {
              var keydownValue = e.detail.tagify.DOM.input.innerText;
              value = keydownValue;
            }
            if (e.type == "invalid") {
              var invalidValue = e.detail.data.name;
              value = invalidValue;
            }

            if (value.length >= 3) {
              if(checkForLinkInput(value, e) == "no match"){ //We haven't pasted a link in the input
                if (typeof keydownValue != "undefined" && value != keydownValue) {
                  value = keydownValue;
                }
                let autocompleteSuccess = triggerTagifyAutocomplete(value);
                if (autocompleteSuccess) {
                  cleanInput();
                }
              }
            } else {
              cleanInput();
            }
          }, 200); //number of ms we wait before sending the ac request
        }

        // Template of element show on the input
        function suggestionItemTemplate(tagData) {
          var imageData;
          var tempate;
          tempate = "<div " + this.getAttributes(tagData) + " class='tagify__dropdown__item " + (tagData.class ? tagData.class : "") + "' tabindex=\"0\" role = \"option\" >";

          if (tagData.type == 'user') {
            imageData = "" + (tagData.avatar ? " <div class='tagify__dropdown__item__avatar-wrap'> <img onerror=\"this.style.visibility='hidden'\" src=\"" + tagData.avatar + "\"> </div>" : "");
          } else if (tagData.type == 'node') {
            if (tagData.node_type == 'alfresco_item') {
              imageData = "<div class='tagify__tag__avatar-wrap'>";
              if (typeof (tagData.icon) != "undefined" && tagData.icon !== null) {
                imageData += "<div><i class=\"" + tagData.icon + " mr-2\"></i></div>";
              } else {
                imageData += "<div><i class=\"fas fa-file mr-2\"></i></div>";
              }
              imageData += "</div>";
            } else {
              imageData = "<div class='tagify__tag__avatar-wrap'><i class=\"" + tagData.icon + " mr-2\"></i></div>";
            }

          } else if (tagData.type == 'userlist') {
            imageData = "<div class='tagify__tag__avatar-wrap'><i class=\"" + tagData.icon + " mr-2\"></i></div>";
          } else if (tagData.type == 'email') {
            imageData = "<div><i class=\"fa fa-envelope text-info mr-2\"></i></div>";
          } else {
            imageData = "<div class='tagify__tag__avatar-wrap'><i class=\"flaticon2-tag icon-2x text-info\"></i></div>";
          }

          tempate += imageData + " <strong>" + tagData.name + "</strong> ";

          if (typeof tagData.email !== 'undefined') {
            tempate += "<span>" + tagData.email + "</span>";
          }

          tempate += "</div>";

          return tempate;
        }

         // Template of element show on the Dropdown list
        function tagTemplate(tagData) {
          var imageData;
          var tagColorClass;
          var subButtonHtml = "";
          var text = "";

          if (tagData.type == 'user') {
            tagColorClass = "tagify__tag-light--success";
            imageData = " <div class='tagify__tag__avatar-wrap'>  <img onerror=\"this.style.visibility='hidden'\" src=\"" + tagData.avatar + "\">  </div>";
          } else if (tagData.type == 'node') {
            if (tagData.node_type == 'alfresco_item' || tagData.node_type == 'article') {
              tagColorClass = "tagify__tag-light";
              if (typeof (tagData.icon) != "undefined" && tagData.icon !== null){
                imageData = "<div><i class=\"" + tagData.icon + " icon-nm mr-2\"></i></div>";
              }else{
                imageData = "<div><i class=\"fas fa-file mr-2\"></i></div>";
              }
            }else if(tagData.node_type == 'article'){
                tagColorClass = "tagify__tag-light";
                 imageData = "<div><i class=\"" + tagData.icon + " icon-nm mr-2\"></i></div>";               
            }else{
              tagColorClass = "tagify__tag-light--primary";
              imageData = "<div><i class=\""+tagData.icon+" text-primary\"></i></div>";
            }
          } else if (tagData.type == 'userlist') {
            tagColorClass = "tagify__tag-light--warning";
            imageData = "<div><i class=\"flaticon-users-1 text-warning\"></i></div>";
          } else if (tagData.type == 'taxonomy_term') {
            if (tagData.subButton === true){
              subButtonHtml = Drupal.getSubButtonHtml(tagData.value);
              subButtonHtml = "<div class='gofast-sub-icon'>" + subButtonHtml.responseText + " </div>";
            }
            imageData = "<div><i class=\"flaticon2-tag icon-nm text-info mr-2\"></i></div>";
            imageData = "";
          } else if (tagData.type == 'email') {
            tagColorClass = "tagify__tag-light--primary";
            imageData = "<div><i class=\"fa fa-envelope text-info mr-2\"></i></div>";
          } else {
            imageData =  "";
          }
          if (tagData.node_type == 'alfresco_item' || tagData.node_type == 'article') {
            text = "<a href=\"/node/" + tagData.value + "\" class=\"text-dark text-hover-primary text-truncate font-size-md\"> " + tagData.name + " </a>";
          }else if(tagData.type == 'taxonomy_term'){
            text = "<span class='font-size-sm'>" + tagData.name + "</span>";
          }else{
            text = tagData.name;
          }
          let removeButton = "<x title='' class='tagify__tag__removeBtn' role='button' aria-label='remove tag'></x>";
          let tagTitle = false;
          if (tagData.undeletable) {
            removeButton = "";
            tagColorClass = "tagify__tag-light--dark";
            tagTitle = Drupal.t("You can't remove this tag");
          }
          
          return "<tag title=\"" + (tagTitle || tagData.email || tagData.name) + "\"  contenteditable='false'  spellcheck='false'  tabIndex=\"-1\"  class=\"" + this.settings.classNames.tag + " " + tagColorClass + " " + (tagData.class ? tagData.class : "") + "\"  " + this.getAttributes(tagData) + ">  " + removeButton + "  <div>  " + imageData + "  <span class='tagify__tag-text'>" + text + "</span>  " + subButtonHtml + "  </div>  </tag>";
        }
      }
    }
  }
})(jQuery, Drupal);
