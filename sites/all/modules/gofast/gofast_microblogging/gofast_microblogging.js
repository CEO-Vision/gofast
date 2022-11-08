(function ($, Gofast, Drupal) {
    'use strict';
    Drupal.behaviors.gofastMicroBlogging = {
        attach: function(context, settings){
            var container = $('#gofast-blog-container');
            if(container.html() !== ""){
                return;
            }

            //Format the blog click event section
            container.html("<div id='blog-event' class='text-center'></div>");
            var bevent = $("#blog-event");

            //Prepare the editor field

      

            bevent.append('<a href="#" class="btn btn-primary font-weight-bolder font-size-sm" id="blog-placeholder"><i class="fa fa-edit icon-nm"></i>'+ Drupal.t("What's new ?", {}, {'context' : 'gofast:microblogging'}) + ' </a>');
            //bevent.append("<span id='blog-placeholder'><span class='fa fa-edit'></span> " + Drupal.t("What's new ?", {}, {'context' : 'gofast:microblogging'}) + "</span>");
            bevent.append('<div name="gofast-blog-editor" id="gofast-blog-editor"></div>');
            var bplaceholder = $("#blog-placeholder");
            var editor = document.querySelector("#gofast-blog-editor");
            var beditor = $("#gofast-blog-editor");

            //Click event on blog
            bplaceholder.click(function(){
                //Fade out, hide the placeholder and size up the container

                bplaceholder.animate({
                    opacity: 0
                }, 300, function(){
                    bplaceholder.hide();
                    if(!beditor.hasClass("processed")){
                        /*CKEDITOR.config.plugins = "dialogui,dialog,about,a11yhelp,dialogadvtab,basicstyles,bidi,blockquote,notification,button,toolbar,clipboard,panelbutton,panel,floatpanel,colorbutton,colordialog,templates,menu,contextmenu,copyformatting,div,resize,elementspath,enterkey,entities,popup,filetools,filebrowser,find,fakeobjects,flash,floatingspace,listblock,richcombo,font,forms,format,horizontalrule,htmlwriter,iframe,wysiwygarea,image,indent,indentblock,indentlist,smiley,justify,menubutton,language,link,list,liststyle,magicline,maximize,newpage,pagebreak,pastetext,pastefromword,preview,print,removeformat,save,selectall,showblocks,showborders,sourcearea,specialchar,scayt,tab,table,tabletools,tableselection,undo,lineutils,widgetselection,widget,notificationaggregator,uploadwidget,uploadimage";
            CKEDITOR.config.toolbar = eval(cke_settings_blog.settings.toolbar);
            Drupal.gofast_blog_editor = CKEDITOR.replace("gofast-blog-editor");*/
                        Drupal.gofast_blog_editor = Gofast.microBlogging.initCKEditorPost(editor);
                        beditor.addClass("processed");
                    }
                    else{
                        beditor.siblings('.ck').show();
                        $("#blog-send").show();
                        $("#blog-cancel").show();
                    }
                });
            });

        }
    };

    Gofast.microBlogging = {
        edit: async function(id){
            let editor = document.querySelector('#blog_'+id);           
            let next_elt = editor.nextElementSibling;
            if(next_elt &&  next_elt.id !='ckeditor_microblogging_buttons' ){
                //remove previous one
                next_elt.remove();
            }
            try {
                let ckeditor_blog;
                await ClassicEditor
                        .create(editor,{
                            toolbar: {
                                items:[
                                        'heading',
                                        '|',
                                        'bold',
                                        'italic',
                                        'underline',
                                        'strikethrough',
                                        '|',
                                        'numberedList',
                                        'bulletedList',
                                        '|',
                                        'link',
                                        'blockquote',
                                        'insertTable',
                                        '|',
                                        'undo',
                                        'redo'
                                ]
                            }
                })
                        .then(newEditor => {
                            ckeditor_blog = newEditor;
                });
                
                //Display the editor, hide other fields
                $("#ckeditor_microblogging_edit_" + id).css('display','inline');
                $('#ckeditor_microblogging_edit_' + id).parent().find('#block_blog_body').css('display' , 'none');
                $('#ckeditor_microblogging_edit_' + id).parent().find('.gofast-node-actions').css('display' , 'none');

        
                //Click event on cancel button
                $('#blog-cancel-'+id).click(function(e) {

                    //reset data to its original value
                    var element_value = document.querySelector("#ckeditor_microblogging_edit_" + id).nextElementSibling;
                    ckeditor_blog.setData(element_value.innerHTML);

                    //Get back to initial state
                    $("#ckeditor_microblogging_edit_" + id).css('display','none');
                    $('#ckeditor_microblogging_edit_' + id).parent().find('#block_blog_body').css('display' , 'block');
                    $('#ckeditor_microblogging_edit_' + id).parent().find('.gofast-node-actions').css('display' , 'inline');
                    ckeditor_blog.destroy();


                });
        

                //Click event on send button
                $('#blog-update-'+id).click(function(e){
                    //Retrieve data in CKeditor
                    var newBlog = ckeditor_blog.getData();
                    //Prevent submission of empty post
                    if(newBlog.length > 0){
                        //Send post request to the server
                        $.post(location.origin + '/blog/update/' + id, {data: newBlog}  ,function(data){
                            if(data === 'OK'){
                                Gofast.toast(Drupal.t("The blog message has been modified !" , {} , {context: 'gofast:microblogging'}),"info");
                                $("#ckeditor_microblogging_edit_" + id).css('display','none');
                                $('#ckeditor_microblogging_edit_' + id).parent().find('#block_blog_body').css('display' , 'block');
                                $('#ckeditor_microblogging_edit_' + id).parent().find('.gofast-node-actions').css('display' , 'inline');
                            }
                            ckeditor_blog.destroy();
                            Gofast.reload_activity_feed();

                        });
                    }
                });
                     
            } catch (error) {
                console.log(error);
            }
        },
        initCKEditorPost: async function(editor) {
            try {
                let ckeditor;
                await ClassicEditor
                        .create(editor,{
                         toolbar: {
                                items:[
                                        'heading',
                                        '|',
                                        'bold',
                                        'italic',
                                        'underline',
                                        'strikethrough',
                                        '|',
                                        'numberedList',
                                        'bulletedList',
                                        '|',
                                        'link',
                                        'blockquote',
                                        'insertTable',
                                        '|',
                                        'undo',
                                        'redo'
                                ]
                            },
                            language: GofastLocale
                })
                        .then(newEditor => {
                            ckeditor = newEditor;
                            ckeditor.model.document.on('change:data', (evt, data) => {
                                var data = ckeditor.getData();
                                //Prevent submission of empty post
                                if(data.length > 0){
                                    $("#blog-send").removeClass('disabled');
                                }else{
                                     $("#blog-send").addClass('disabled');
                                }
                            });
                });

                var bevent = $("#blog-event");
                var bplaceholder = $("#blog-placeholder");
                var beditor = $("#gofast-blog-editor");
                //Add submit/cancel button
                bevent.append('<button id="blog-send" type="button" class="btn btn-success disabled">' + Drupal.t("Send", {}, {'context' : 'gofast:microblogging'}) + '</button>');
                bevent.append('<button id="blog-cancel" type="button" class="btn btn-danger">' + Drupal.t("Cancel", {}, {'context' : 'gofast:microblogging'}) + '</button>');

                //Click event on cancel button
                $("#blog-cancel").click(function(e){
                    e.stopPropagation();
                    //Get back to initial state
                    beditor.siblings('.ck').hide();
                    $("#blog-send").hide();
                    $("#blog-cancel").hide();
                    bplaceholder.show();
                    bplaceholder.css("opacity", 1);
                    ckeditor.setData("");
                                   
                });
                //Click event on send button
                $("#blog-send").click(function(e){
                    e.stopPropagation();
                    //Retrieve data in CKeditor
                    var data = ckeditor.getData();
                    //Prevent submission of empty post
                    if(data.length > 0){
                        //Display loader
                        beditor.siblings('.ck').hide();
                        $("#blog-send").hide();
                        $("#blog-cancel").hide();
                        bevent.append('<div class="loader-blog"></div>');

                        //Send ajax request to the server
                        $.ajax({
                            'url': '/blog/add',
                            'type': 'POST',
                            'dataType': 'html',
                            'data': {
                                'message': data
                            }
                        }).always(function (result) {
                            //Get back to the initial state
                            $(".loader-blog").remove();
                            bplaceholder.show();
                            bplaceholder.css("opacity", 1);
                            ckeditor.setData("");

                            //Get the activity feed table
                            var afeed_table = $("#activity-feed-table").find("tbody");

                            //We try to get the user profile picture
                            var user_pp = $('.user-picture').first().find("img").attr("src");
                            //Add the line at top of the activity feed
                            if (Gofast._settings.isMobile == false || typeof Gofast._settings.isMobile == 'undefined') {
                                //$("#activity-feed-table tr:first").after('<tr class="blog-new-entry"><td><div class="user-picture profile-to-popup gofast-popup-processed" id="1-7115"> <div class="profile-popup-wrapper"><div class="profile-popup"><!-- ajax load profile popup --></div></div><a href="/user/' + Gofast.get("user").uid + '" data-toggle="tooltip" data-placement="auto left" data-original-title="" title=""><img data-toggle="tooltip" data-placement="auto left" typeof="foaf:Image" src="' + user_pp + '" width="40" height="40" alt="Picture" title="Picture" data-original-title="Picture"></a></div></td><td colspan="5"><div class="gofast-microblogging-actions"><div class="gofast-node-actions btn-group" id="gofast-node-actions-microblogging"><a class="btn btn-default btn-xs dropdown-toggle dropdown-placeholder" type="button" id="dropdown-placeholder-' + result + '" data-toggle="dropdown"><span class="fa fa-bars" style="color:#777;"></span><ul class="dropdown-menu gofast-dropdown-menu" role="menu" id="dropdownactive-placeholder-' + result + '"><li><div class="loader-activity-menu-active"></div></li></ul></a></div></div><div id="ckeditor_microblogging_edit_' + result + '" style="display:none;"><textarea id="blog_' + result + '" name="blog_name_' + result + '">' + data + '</textarea><div style="padding:8px;"><a class="btn btn-sm btn-success" onclick="Gofast.microBlogging.update(\'' + result + '\')"style="margin-right:10px;">' + Drupal.t('Validate') + '</a><a class="btn btn-sm btn-danger" onclick="Gofast.microBlogging.closeCke(\'' + result + '\')">' + Drupal.t('Cancel') + '</a></div></div><div id="block_blog_body">' + data + '</div><br /><div style="text-align: right; clear: both;">' + Drupal.t('Now') + '</div></td></tr>');
                            }else{
                                $("#activity-feed-table tr:first").after('<tr class="blog-new-entry"><td><div class="user-picture profile-to-popup gofast-popup-processed" id="1-7115"> <div class="profile-popup-wrapper"><div class="profile-popup"><!-- ajax load profile popup --></div></div><a href="/user/' + Gofast.get("user").uid + '" data-toggle="tooltip" data-placement="auto left" data-original-title="" title=""><img data-toggle="tooltip" data-placement="auto left" typeof="foaf:Image" src="' + user_pp + '" width="40" height="40" alt="Picture" title="Picture" data-original-title="Picture"></a></div></td><td colspan="5" class="gofast-activity-blog-field-mobil"><div id="block_blog_body">' + data + '<div class="gofast-microblogging-actions"><div class="gofast-node-actions btn-group" id="gofast-node-actions-microblogging"><a class="btn btn-default btn-xs dropdown-toggle dropdown-placeholder" type="button" id="dropdown-placeholder-' + result + '" data-toggle="dropdown"><span class="fa fa-bars" style="color:#777;"></span><ul class="dropdown-menu gofast-dropdown-menu" role="menu" id="dropdownactive-placeholder-' + result + '"><li><div class="loader-activity-menu-active"></div></li></ul></a></div></div><div id="ckeditor_microblogging_edit_' + result + '" style="display:none;"><textarea id="blog_' + result + '" name="blog_name_' + result + '">' + data + '</textarea><div style="padding:8px;"><a class="btn btn-sm btn-success" onclick="Gofast.microBlogging.update(\'' + result + '\')"style="margin-right:10px;">' + Drupal.t('Validate') + '</a><a class="btn btn-sm btn-danger" onclick="Gofast.microBlogging.closeCke(\'' + result + '\')">' + Drupal.t('Cancel') + '</a></div></div></div><div>' + Drupal.t('Now') + '</div></td></tr>');
                            }
                            Gofast.reload_activity_feed();
                        });
                    }
                });
                             
            } catch (error) {
                console.log(error);
            }
        }
    };
})(jQuery, Gofast, Drupal);
