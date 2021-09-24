(function ($, Drupal, Gofast) {


  Drupal.behaviors.gofast_instantiate_xeditable = {
    attach: function (context) {
      Gofast.loadXEditable();
    }
  };


  Gofast.loadXEditable = function () {

    //add translation NL
    $.fn.datetimepicker.dates['nl'] = {

			days: ["zondag", "maandag", "dinsdag", "woensdag", "donderdag", "vrijdag", "zaterdag", "zondag"],
			daysShort: ["zon", "maa", "din", "woe", "don", "vri", "zat", "zon"],
			daysMin: ["zo", "ma", "di", "wo", "do", "wr", "za", "zo"],
			months: ["januari", "februari", "maart", "april", "mei", "juni", "juli", "augustus", "september", "oktober", "november", "december"],
			monthsShort: ["jan", "feb", "mar", "apr", "mei", "jun", "jul", "aug", "sep", "oct", "nov", "dec"],
			meridiem: ["am", "pm"],
			suffix: ["st", "nd", "rd", "th"],
			today: "Vandaag"

	};


    $('.xeditable-field:not(xeditable-field-processed)').addClass('xeditable-field-processed').each(function () {

      function update_field_css(xeditable) {
        xeditable.css('visibility', 'hidden');
        xeditable.css('position', 'absolute');
        var field_width = xeditable.parent().parent().width();
        var field_offset = xeditable.parent().parent().offset();
        xeditable.parent().find('.xeditable-trigger').offset({top: field_offset.top});
      }

      // This is the behavior for xeditable when doing with delegated button
      if ($(this).data('delegated') === true) {
        var xeditable = $(this);

        if (Gofast.isTablet() || Gofast.isMobile()) {
          if (xeditable.data('name') == 'body') {
            xeditable.parent().parent().find('.xeditable-trigger').css('visibility', 'visible');
          } else {
            xeditable.parent().parent().parent().find('.xeditable-trigger').css('visibility', 'visible');
          }
        } else {
          if (xeditable.data('name') == 'body') {
            xeditable.parent().parent().hover(function () {
              update_field_css(xeditable);
              $(this).find('.xeditable-trigger').css('visibility', 'visible');
              if (xeditable.data("inputclass") !== "textarea_ckeditor") {
                $(this).parent().css('background-color', '#f0f0f9');
              } else {
                xeditable.parents('.xeditable_field_wrapper').parent().css('background-color', '#f0f0f9');
              }
            }, function () {
              $(this).find('.xeditable-trigger').css('visibility', 'hidden');
              if (xeditable.data("inputclass") !== "textarea_ckeditor") {
                $(this).parent().css('background-color', 'transparent');
              } else {
                xeditable.parents('.xeditable_field_wrapper').parent().css('background-color', 'transparent');
              }
            });
          } else {
            xeditable.parent().parent().parent().hover(function () {
              update_field_css(xeditable);
              $(this).find('.xeditable-trigger').css('visibility', 'visible');
              if (xeditable.data("inputclass") !== "textarea_ckeditor") {
                $(this).parent().css('background-color', '#f0f0f9');
              } else {
                xeditable.parents('.xeditable_field_wrapper').parent().css('background-color', '#f0f0f9');
              }
            }, function () {
              $(this).find('.xeditable-trigger').css('visibility', 'hidden');
              if (xeditable.data("inputclass") !== "textarea_ckeditor") {
                $(this).parent().css('background-color', 'transparent');
              } else {
                xeditable.parents('.xeditable_field_wrapper').parent().css('background-color', 'transparent');
              }
            });
          }
        }

        // Events
        xeditable.parent().find('.xeditable-trigger').click(function (e) {
          e.stopPropagation();
          xeditable.editable('option', {
            container: '.region-sidebar-second'
          });
          xeditable.editable('show');
          // Display full height for category select box
          if ($(e.target).parent().hasClass('field-field_category')) {
            if(Gofast.isMobile){
              $('ul.select2-results').css('max-height', '200px');
            }else{
              $('ul.select2-results').css('max-height', 'none');
            }
          }
        });
        xeditable.parent().find('.xeditable-trigger-2').click(function (e) {
          e.stopPropagation();
          xeditable.editable('option', {
            container: '.region-sidebar-second'
          });
          xeditable.editable('show');
          // Display full height for category select box
          if ($(e.target).parent().hasClass('field-field_category')) {
            if (Gofast.isMobile) {
              $('ul.select2-results').css('max-height', '200px');
            } else {
              $('ul.select2-results').css('max-height', 'none');
            }
          }
        });
        xeditable.on('init', function (e, editable) {
          var value = editable.options.value !== "" ? editable.options.value : Drupal.t(editable.options.emptytext, {}, {'context' : 'gofast'});
          if (editable.options.data !== undefined) {
            if (editable.options.data.links !== undefined && editable.options.data.links !== null) {
              if (Array.isArray(editable.options.data.links)) {
                value = editable.options.data.links.join('<br/>');
              } else {
                value = editable.options.data.links;
              }
            } else if (editable.options.data.tags !== undefined && editable.options.data.tags !== null) {
              //We prepare the tag table
             if($(".select2-tags").length == 1){
                 return;
             }
              value = '<ul class="select2-tags"></ul>';
              var xeditable_values = $(this).parent().find('.xeditable-values');
              var container = $(this);
              xeditable_values.html(value);
              update_field_css(container);

              //For each tag we need to retrieve and set tha subscribe button
              if (Array.isArray(editable.options.data.tags)) {
                for (var item in editable.options.data.tags) {
                  if (editable.options.data.tags.hasOwnProperty(item)) {
                    $.ajax({ //Call to get subscribe button
                      url : Drupal.settings.gofast.baseUrl+'/xeditable/get/subscribe/'+ editable.options.data.tags[item].replace("/", "*\*") + '/' + Drupal.settings.gofast.node.id,
                      type : 'GET',
                      dataType: 'html',
                      success : function(content, status){
                        value = xeditable_values.html();
                        value = value.slice(0, -5);
                        value += '<li>' + content + '</li></ul>';
                        xeditable_values.html(value);
                        update_field_css(container);
                        $.getScript('/sites/all/modules/flag/theme/flag.js', function() {
                          Drupal.behaviors.flagLink.attach(document);
                        });
                      }
                    });
                  }
                }
              } else {
                $.ajax({ //Call to get subscribe button
                  url : Drupal.settings.gofast.baseUrl+'/xeditable/get/subscribe/'+ editable.options.data.tags.replace("/", "*\*") + '/' + Drupal.settings.gofast.node.id,
                  type : 'GET',
                  dataType: 'html',
                  success : function(content, status){
                    value = xeditable_values.html();
                    value = value.slice(0, -5);
                    value += '<li>' + content + '</li></ul>';
                    xeditable_values.html(value);
                    update_field_css(container);
                    $.getScript('/sites/all/modules/flag/theme/flag.js', function() {
                      Drupal.behaviors.flagLink.attach(document);
                    });
                  }
                });
              }
            }
          }
          $(this).parent().find('.xeditable-values').html(value);
          update_field_css($(this));
        });
        xeditable.on('save', function (e, params) {
          $(this).parent().find('.xeditable-values').html(JSON.parse(params.response).newValue);
          update_field_css($(this));
        });
        xeditable.on('hidden', function (e, reason) {
          if (!Gofast.isTablet() && !Gofast.isMobile()) {
            $(this).parent().find('.xeditable-trigger').css('visibility', 'hidden');
            $(this).parent().find('.xeditable-trigger-2').css('visibility', 'hidden');
            $(this).parent().parent().parent().parent().css('background-color', 'transparent');
          }
        });
      }

      // Here we process special elements for fields that require custom templating
      if ($(this).parent().hasClass('select2-template-image')) {
        // This is the select2 about the managers in user profile
        var userTemplate = function (state) {
          return '<img src="/' + state.pictureurl + '" width="20px" height="20px" alt="' + Drupal.t('Portrait of ', {}, {'context' : 'gofast'}) + state.managername + '" title="' + Drupal.t('Portrait of ', {}, {'context' : 'gofast'}) + state.managername + '" />&nbsp;' + state.text;
        };
        $(this).editable({
          'select2': {
            allowClear: true,
            formatResult: userTemplate,
            formatSelection: userTemplate,
            placeholder: Drupal.t($(this).data('emptytext'), {}, {'context' : 'gofast'}),
            formatSearching: Drupal.t('Searching...', {}, {'context' : 'gofast'}),
            formatNoMatches: Drupal.t('No matches found', {}, {'context' : 'gofast'}),
            formatInputTooShort: function (text, minLength) {
              return Drupal.t('Please enter %input or more characters', {'%input': minLength - text.length}, {'context' : 'gofast'});
            },
          }
        });
      } else if ($(this).parent().hasClass('select2-node-language')) {
        // This is the select2 about the languages in node info
        var langTemplate = function (state) {
          return state.icon + '&nbsp;' + Drupal.t(state.text, {}, {'context' : 'gofast'});
        };
        $(this).editable({
          success: function (response, newValue) {
            response = JSON.parse(response);
            if (response.status === 'error') {
              return response.msg; //msg will be shown in editable form
            }
          },
          'select2': {
            formatResult: langTemplate,
            formatSelection: langTemplate,
            placeholder: Drupal.t($(this).data('emptytext'), {}, {'context' : 'gofast'}),
            formatSearching: Drupal.t('Searching...', {}, {'context' : 'gofast'}),
            formatNoMatches: Drupal.t('No matches found', {}, {'context' : 'gofast'}),
            formatInputTooShort: function (text, minLength) {
              return Drupal.t('Please enter %input or more characters', {'%input': minLength - text.length}, {'context' : 'gofast'});
            },
          }
        });
      } else if ($(this).parent().hasClass('node-info-target-links')) {
        // This is the select2 about the linked nodes in node info
        var nodeTemplate = function (state) {
          var format = '<span class="fa '+state.formatImageUrl+'" />&nbsp; </span>'+ state.format;
          return format + ' - ' + state.text + ' - ' + state.updateDate ;
        };
        $(this).editable({
          success: function (response, newValue) {
            response = JSON.parse(response);
            if (response.status === 'error') {
              return response.msg; //msg will be shown in editable form
            }
          },
          'select2': {
            multiple: true,
            minimumInputLength: 2,
            formatResult: nodeTemplate,
            formatSelection: nodeTemplate,
            placeholder: Drupal.t('Search content by name', {}, {'context' : 'gofast'}),
            formatSearching: Drupal.t('Searching...', {}, {'context' : 'gofast'}),
            formatNoMatches: Drupal.t('No matches found', {}, {'context' : 'gofast'}),
            formatInputTooShort: function (text, minLength) {
              return Drupal.t('Please enter %input or more characters', {'%input': minLength - text.length}, {'context' : 'gofast'});
            },
            initSelection: function (element, callback) {
              $.get("/gofast/node_autocomplete", {nids: element.val()})
                      .done(function (data) {
                        callback(data);
                      });
            }
          }
        });
      } else if ($(this).parent().hasClass('node-info-keywords')) {
        // This is the select2 about the keywords
        var tagTemplate = function (state) {
          return '<li>' + state.text + '</li>';
        };
        $(this).editable({
          success: function (response, newValue) {
            response = JSON.parse(response);
            if (response.status === 'error') {
              return response.msg; //msg will be shown in editable form
            }
          },
          'select2': {
            tags: true,
            createSearchChoice: function (term, data) {
              if ($(data).filter(function () {
                return this.text.localeCompare(term) === 0;
              }).length === 0) {
                return {
                  id: term,
                  text: term + Drupal.t(' (new term)', {}, {'context' : 'gofast'})
                };
              }
            },
            ajax: {
              url: '/gofast/tag_autocomplete/',
              data: function (term) {
                return {
                  query: term
                };
              },
              results: function (data) {
                var text_data = data.map(function (item) {
                  return {'id': item.text, 'text': item.text};
                });
                return {
                  results: text_data
                };
              }
            },
            multiple: true,
            minimumInputLength: 2,
            formatResult: tagTemplate,
            formatSelection: tagTemplate,
            placeholder: Drupal.t('Search keywords by name', {}, {'context' : 'gofast'}),
            formatSearching: Drupal.t('Searching...', {}, {'context' : 'gofast'}),
            formatNoMatches: Drupal.t('No matches found', {}, {'context' : 'gofast'}),
            formatInputTooShort: function (text, minLength) {
              return Drupal.t('Please enter %input or more characters', {'%input': minLength - text.length}, {'context' : 'gofast'});
            },
            initSelection: function (element, callback) {
              var data = [];

              function splitVal(string, separator) {
                var val, i, l;
                if (string === null || string.length < 1)
                  return [];
                val = string.split(separator);
                for (i = 0, l = val.length; i < l; i = i + 1){
                  var splitval = $.trim(val[i]).split("[GOFAST_TAG_SEPARATOR]");
                  val[i] = splitval[0];
                }
                return val;
              }

              $(splitVal(element.val(), ",")).each(function () {
                data.push({
                  id: this,
                  text: this
                });
              });

              callback(data);
            }
          }
        });
      } else if ($(this).parent().hasClass('node-info-document_author')) {
        var __Bl_whitespace = function (str) {
          str = _.toStr(str);
          return str ? str.split(/\s+/) : [];
        };
        var __Bl_filter = function (response) {
          var new_response = [];
          for (var object in response) {
            var name = object.split("<")[0].trim();
            new_response.push(name);
          }
          return new_response;
        }
        $(this).editable({
          success: function (response, newValue) {
            response = JSON.parse(response);
            if (response.status === 'error') {
              return response.msg; //msg will be shown in editable form
            }
          },
          typeahead: {
            name: 'author',
            datumTokenizer: function (datum) {
              return __Bl_whitespace(datum.value);
            },
            queryTokenizer: __Bl_whitespace,
            remote: {
              widcard: "%QUERY",
              url: '/gofast/user-autocomplete/%QUERY',
              filter: __Bl_filter,
            }
          }
        });
      }else if ($(this).parent().hasClass('node-info-document_reference')) {
        var __Bl_whitespace = function (str) {
          str = _.toStr(str);
          return str ? str.split(/\s+/) : [];
        };
        var __Bl_filter = function (response) {
          var new_response = [];
          for (var object in response) {
            var name = object.split("<")[0].trim();
            new_response.push(name);
          }
          return new_response;
        }
        $(this).editable({
          success: function (response, newValue) {
            response = JSON.parse(response);
            if (response.status === 'error') {
              return response.msg; //msg will be shown in editable form
            }
          },
          typeahead: {
            name: 'document_reference',
            datumTokenizer: function (datum) {
              return __Bl_whitespace(datum.value);
            },
            queryTokenizer: __Bl_whitespace,
            local: {
              filter: __Bl_filter,
            }
          }
        });
      }else if ($(this).parent().hasClass('node-info-archive_quote')) {

        var __Bl_whitespace = function (str) {
          str = _.toStr(str);
          return str ? str.split(/\s+/) : [];
        };
        var __Bl_filter = function (response) {
          var new_response = [];
          for (var object in response) {
            var name = object.split("<")[0].trim();
            new_response.push(name);
          }
          return new_response;
        }
        $(this).editable({
          success: function (response, newValue) {
            response = JSON.parse(response);
            if (response.status === 'error') {
              return response.msg; //msg will be shown in editable form
            }
          },
          typeahead: {
            name: 'node_archive_quote',
            datumTokenizer: function (datum) {
              return __Bl_whitespace(datum.value);
            },
            queryTokenizer: __Bl_whitespace,
            local: {
              filter: __Bl_filter,
            }
          }
        });
      }else if ($(this).parent().hasClass('node-info-archive_transfer_name')) {

        var __Bl_whitespace = function (str) {
          str = _.toStr(str);
          return str ? str.split(/\s+/) : [];
        };
        var __Bl_filter = function (response) {
          var new_response = [];
          for (var object in response) {
            var name = object.split("<")[0].trim();
            new_response.push(name);
          }
          return new_response;
        }
        $(this).editable({
          success: function (response, newValue) {
            response = JSON.parse(response);
            if (response.status === 'error') {
              return response.msg; //msg will be shown in editable form
            }
          },
          typeahead: {
            name: 'node_archive_transfer_name',
            datumTokenizer: function (datum) {
              return __Bl_whitespace(datum.value);
            },
            queryTokenizer: __Bl_whitespace,
            local: {
              filter: __Bl_filter,
            }
          }
        });
      }else if ($(this).parent().hasClass('node-info-alias')) {
        var __Bl_whitespace = function (str) {
          str = _.toStr(str);
          return str ? str.split(/\s+/) : [];
        };
        var __Bl_filter = function (response) {
          var new_response = [];
          for (var object in response) {
            var name = object.split("<")[0].trim();
            new_response.push(name);
          }
          return new_response;
        }
        $(this).editable({
          success: function (response, newValue) {
            response = JSON.parse(response);
            if (response.status === 'error') {
              return response.msg; //msg will be shown in editable form
            }
          },
          typeahead: {
            name: 'alias',
            datumTokenizer: function (datum) {
              return __Bl_whitespace(datum.value);
            },
            queryTokenizer: __Bl_whitespace,
            local: {
              filter: __Bl_filter,
            }
          }
        });
      } else {
        // In any other cases, display default module
        $(this).editable({
          success: function (response, newValue) {
            try{
              response = JSON.parse(response);
              if (response.status === 'error') {
                return response.msg; //msg will be shown in editable form
              }
            }catch (e){
              //response is not a JSON string !
            }

            if(jQuery(this.outerHTML).data().name == "title"){
                //if rename zTree space -> navigate(deletetree)
                var deleteTree = true;
                var newCurrentPath = Gofast.ITHit.currentPath.substr(0, Gofast.ITHit.currentPath.lastIndexOf('/')) + "/_" + newValue;
                //Navigate to parent folder in ITHit
                setTimeout(function(){
                    Gofast.ITHit.navigate(newCurrentPath, null, null, null, null, deleteTree);
                    Gofast.ITHitMobile.navigate(newCurrentPath, null, null, null, null, deleteTree);
                }, 2000);
            }
          }
        });
      }
      if ($(this).parent().hasClass('manual_ckeditor')) {
        var current_text = $(this).parent().find('.xeditable-values').html();
        $(this).on('shown', function (e, editable) {
          $(this).parent().find('.xeditable-values').text('');
          CKEDITOR.config.plugins = "dialogui,dialog,about,a11yhelp,dialogadvtab,basicstyles,bidi,blockquote,notification,button,toolbar,clipboard,panelbutton,panel,floatpanel,colorbutton,colordialog,templates,menu,contextmenu,copyformatting,div,resize,elementspath,enterkey,entities,popup,filetools,filebrowser,find,fakeobjects,flash,floatingspace,listblock,richcombo,font,forms,format,horizontalrule,htmlwriter,iframe,wysiwygarea,image,indent,indentblock,indentlist,smiley,justify,menubutton,language,link,list,liststyle,magicline,maximize,newpage,pagebreak,pastetext,pastefromword,preview,print,removeformat,save,selectall,showblocks,showborders,sourcearea,specialchar,scayt,tab,table,tabletools,tableselection,undo,lineutils,widgetselection,widget,notificationaggregator,uploadwidget,uploadimage";
          CKEDITOR.config.toolbar = eval(cke_settings_advanced.settings.toolbar);
          if ($("#ogtab_home").length == 1) {
            CKEDITOR.config.width = "125%";
          } else {
            CKEDITOR.config.width = "100%";
          }

          $('.textarea_ckeditor').ckeditor();


        });
        $(this).on('save', function (e, params) {
          //$(this).attr('data-value', params.newValue);
          var that = $(this);
          setTimeout(function () {
            that.html(params.newValue);
          }, 1);
        });
        $(this).on('hidden', function (e, reason) {
          if (reason === 'cancel' || reason === 'nochange') {
            $(this).parent().find('.xeditable-values').html(current_text);
          }
        });
      }

      //Separating file/space renaming forms
        var timeoutMode;
        if(document.title.indexOf('.') !== -1) {
          timeoutMode = "Gofast.gofast_refresh_fast_actions_node, 4500, Drupal.settings.gofast.node.id";
      }else timeoutMode = "Gofast.ITHit.reload(), 4500";

          $.fn.editableform.buttons = '<button type="submit" onclick="setTimeout('
                  + timeoutMode
                  + ');" class="btn btn-success btn-sm editable-submit">'
                  + '<i class="glyphicon glyphicon-ok"></i>'
                  + Drupal.t('Apply', {}, {'context' : 'gofast'})
                  + '</button>'
                  + '<button type="button" class="btn btn-default btn-sm editable-cancel">'
                  + '<i class="glyphicon glyphicon-remove"></i>'
                  + Drupal.t('Cancel', {}, {'context' : 'gofast'})
                  + '</button>';
  });
  };


})(jQuery, Drupal, Gofast);
