(function ($, Drupal, Gofast) {

    var GofastKanbanCardDetail = function(){

        var _detailElement = {
            value: "",
            container: "",
            content: "",
            control: "",
            controlContainer: "",
            render(){
                return this.value
            },
            reload(){
                this.content.innerHTML = this.render()
                this.setOnEditonMode(false)
            },
            setOnEditonMode(onEdition){
                onEdition ? this.container.classList.add('edition') : this.container.classList.remove('edition')
            },
            init(container){
                this.container = container
                this.content = this.container.querySelector('.Detail__content')
                this.control = this.container.querySelector('.Detail__control .form-control')
                this.controlContainer = this.container.querySelector('.Detail__control')


                this.setContentOnClick()
                this.setCustomControl()
                this.reload()
            },
            setContentOnClick(){
                this.content.onclick = (e) => {
                    e.preventDefault()
                    e.stopPropagation()

                    this.setOnEditonMode(true)
                    this.handleControleOnShow()
                }
            },
            handleControleOnShow(){},
            setCustomControl(){},
            setData(newValue){
                this.value = newValue
                this.reload()
            },
            getNewData(newValue){ return data},
            loading(isLoading){
                isLoading ? this.controlContainer.querySelector('.form-loader').classList.add('loading') : this.controlContainer.querySelector('.form-loader').classList.remove('loading')
            },
            async submit(newValue){
                if(newValue === this.value) {
                    this.reload()
                    return
                }

                // Select verification
                if(newValue.id){
                    if(newValue.id == this.value.id){
                        this.reload()
                        return
                    }
                }
                this.loading(true)
                try {

                    let newData = this.getNewData(newValue)
                    let res = await _submit(newData)
                    this.setData(newValue)

                } catch (error) {
                    this.reload()
                }
                this.loading(false)

            }
        }

        var _task;
        var _callback;
        var mainContainer;
        var data;
        var title;
        var deadline;
        var state;
        var created;
        var responsable;
        var members;
        var description;
        var documents;
        var comments;

        const _handleSaveData = async function (field, value){

            let formData = new FormData()
            formData.append(field, value)

            let url = window.origin + "/kanban/task/" + _task.nid + "/update";

            const res = await fetch(url, {
                method: 'POST',
                body: formData
            })
            
            window.ktKanbanItem.reload();
            let field_t = Drupal.t(field, {}, { 'context': 'gofast_kanban' });     
            Gofast.toast(Drupal.t('Your modification on @field has been saved', {'@field': field_t}, { 'context': 'gofast' }), 'info');
            
            let timeline = mainContainer.querySelector('.GofastKanbanTimeLine');
            let auditContainer = timeline.querySelector('#card__audit');
            _getCardAudit(auditContainer, _task.nid);

            return await res
            // await res ? _callback() : ''
            // console.log(await res)

        }
        
        const _handleAddComment = async function(field, value){
            
             let formData = new FormData()
            formData.append(field, value);
            
            let url = window.origin + "/kanban/task/" + _task.nid + "/add/comment";

            const res = await fetch(url, {
                method: 'POST',
                body: formData
            })
                        
            //reload Comments
            _commentsReload(); 
            window.ktKanbanItem.reload();
            Gofast.toast(Drupal.t('New comment added', {}, { 'context': 'gofast' }), 'info');
            
            return await res
        }
        
         const _handleEditComment = async function(field, value, commentId){
            
             let formData = new FormData()
            formData.append(field, value);
            
            let url = window.origin + "/kanban/task/update/comment/" + commentId;

            const res = await fetch(url, {
                method: 'POST',
                body: formData
            })
            
            //reload Comments
            _commentsReload(); 
            
            return await res
        }
        
               
        
        const _handleDeleteCard = async function(){
                               
            let url = window.origin + "/kanban/task/" +_task.nid + "/delete";
            const res = await fetch(url, {
                method: 'POST'
            })

            return await res
        }
        
        var _handleDeleteComment = async function(commentId){
            
            let url = window.origin + "/kanban/task/delete/comment/" +commentId;
            const res = await fetch(url, {
                method: 'POST'
            })
            
            _commentsReload(); 
            window.ktKanbanItem.reload();
            Gofast.toast(Drupal.t('The comment has been deleted', {}, { 'context': 'gofast' }), 'info');

            return await res
        }

        var _init = function(el, initialData, callback){

            mainContainer = el
            _task = initialData
            _callback = callback
            

            // Set Title
            let titleEl =  document.querySelector('.KanbanCard__title > div')
            title = GofastEditableInput(titleEl, _task.title, 'text', {
                isEditable : _task.canEdit,
                templates: {
                    value: function(data){
                        if(data){
                          return "<div class=\"font-size-h1\">" + data + "</div>";
                        }
                        return "<div class=\"text-muted font-size-h4\" >" + Drupal.t("Empty value") + "</div>";
                    }

                },
                save: (newdata) => _handleSaveData('label', newdata)
            })

            // Set created
            let createdEl =  document.querySelector('.KanbanCard__created > div')
            created = GofastEditableInput(createdEl, _task.created_date, 'date', {
                isEditable: false   
            })

            // Set deadline
            let deadlineEl =  document.querySelector('.KanbanCard__deadline > div')
            deadline = GofastEditableInput(deadlineEl, _task.deadline, 'date', {
                isEditable : _task.canEdit,
                save: (newdata) => _handleSaveData('deadline', newdata)
            })


            //get card status from api
            let stateWishlist = [];
            let url = window.origin + "/kanban/cards_status/get";
            
            fetch(url, {
                method: 'POST',
                body : 'json'
            })
            .then((resp) => resp.json())
            .then(function(data) {
                
                data.forEach(function(status){
                    stateWishlist.push({value : status.tid, label : Drupal.t(status.label) });
                });
                
                if(_task.status){
                    _task.status.label = _task.status.value
                    _task.status.value = _task.status.tid
                }
                
                let stateEl =  document.querySelector('.KanbanCard__state > div')
                state = GofastEditableInput(stateEl, _task.status, 'select', {
                    isEditable : _task.canEdit,
                    save: (newData) => {
                        _handleSaveData('status', newData.id);
                    },
                    wishlist: stateWishlist,
                })
                
            });


            

            // set Description
            let descriptionEl =  document.querySelector('.KanbanCard__description > div')
            description = GofastEditableInput(descriptionEl, _task.description, 'ckeditor-classic-enrich', {
                isEditable : _task.canEdit,
                save: (newData) => {
                    let jsondata = JSON.stringify(newData)
                    _handleSaveData('description', jsondata)
                },
                templates: {
                    input : function () {                        
                        return "\n<textarea class=\"input-control form-control CEditor\"></textarea>\n<button type=\"submit\" id=\"save-cke\" name=\"op\" value=\"" + Drupal.t("Save") + "\" class=\"btn btn-sm btn-success form-submit icon-before\"> <span class=\"icon glyphicon glyphicon-ok\" aria-hidden=\"true\"></span> " + Drupal.t("Save") + "\n</button>\n&nbsp;\n<button type=\"submit\" id=\"cancel-cke\" name=\"op\" value=\"" + Drupal.t("Cancel") + "\" class=\"btn btn-sm btn-bg-secondary icon-before\"> <span class=\"icon glyphicon glyphicon-cross\" aria-hidden=\"true\"></span> " + Drupal.t("Cancel") + "\n</button>\n";
                    }
                },
                events: { 
                        showInputCustom : () => {
                            descriptionEl.querySelector('#save-cke').onclick = (e) =>{
                                let data = description.DOM.customInput.getData();
                                description.saveData(data);
                                description.events.toogleInput(description, false) ;
                            };
                            
                            descriptionEl.querySelector('#cancel-cke').onclick = (e) =>{
                                description.events.toogleInput(description, false); 
                            };
                        }
                }
            })

            if(_task.responsible) {
                _task.responsible.id = _task.responsible.uid
                _task.responsible.text = _task.responsible.firstname+' '+_task.responsible.lastname;
            }

            // Set Responsable
            let responsableEl =  document.querySelector('.KanbanCard__responsable > div')
            responsable = GofastEditableInput(responsableEl, _task.responsible , 'userselect', {
                isEditable : _task.canEdit,
                save: (newData) => {
                    let id;
                    if(newData){
                        id = newData.uid
                    }else{
                        id = 0;
                    }
                    _handleSaveData('person-in-charge', id ? id : 0);
                },
                templates: {
                    value: function(data){
                        if (!data || data.uid == 0) {
                            return "<div class=\"text-muted\">" + Drupal.t("Nobody assigned") + "</div>";
                        }

                        var displayName = data.firstname+' '+data.lastname;
                        return "<div class=\"d-flex align-items-center\">\n<div class=\"symbol symbol-40 flex-shrink-0\"> <img alt=\"Pic\" src=\"" + data.picture + "\">\n</div>\n<div class=\"ml-4\"> <div class=\"text-dark-75 font-weight-bolder font-size-lg mb-0\">" + displayName + "</div>\n</div>\n</div>";
                    }         
                }
            })
            //switch select2 data url
            $(responsable.DOM.input).select2({
                ajax: {
                    url: function(params){
                        return window.origin + '/kanban/autocomplete/user-not-readonly/' + _task.space_nid + '/' + params.term;
                    },
                    dataType: 'json',
                    data: function (params) {
                        return {}; 
                    },
                    delay: 250,
                    processResults: function (data) {
  
                      //  let data_array = Object.values(data);
                        let newData  = Object.values(data).map(user => {
                            user.text = user.firstname+' '+user.lastname;
                            user.id = user.uid;
                            return user
                        })
                        
                        //Add none 
                        newData.push({  'text':  Drupal.t('None', {}, {'context': 'gofast_kanban'}),
                                        'id': 0,
                                        'uid' : 0});
                                    
                        return {
                          results: newData
                        };
                    }
                },
                placeholder: Drupal.t('Search User', {}, {'context': 'gofast_kanban'}),
                minimumInputLength: 3,
                // minimumResultsForSearch: Infinity,
                templateResult: responsable.templates.selectionItemTemplate,
                templateSelection: responsable.templates.suggestionItemTemplate,
                language: GofastLocale,
            });
  

            if(_task.members && _task.members.length > 0) {
                _task.members.map(user => {
                    user.value = user.uid
                    return user
                })
            }

            // Set Members
            let membersEl =  document.querySelector('.KanbanCard__members > div')
            members = GofastEditableInput(membersEl, _task.members, 'userstags', {
                isEditable : _task.canEdit,
                searchUrl : (search) => {
                    return window.origin + '/kanban/autocomplete/user/' + _task.space_nid + '/' + search;
                },
                formatData(data){
                   return Object.values(data).map(user => {
                            user.value = Number.parseInt(user.uid);
                            return user;
                        });
                },                
                save: (newData) => {
                    let membersIds = []
                    newData.forEach(user => membersIds.push(user.uid));
                    _handleSaveData('members', membersIds);
                }
              
            })


            // Set Documents
            let formatedDocuments = _task.documents.map(doc => {
                doc.value = doc.id
                doc.name = doc.title
                doc.type = 'node'
                doc.node_type = 'alfresco_item'
                doc.editable = false
                
                delete doc.id
                delete doc.title
                
                return doc
            })

            let documentsEl =  document.querySelector('.KanbanCard__documents > div')
            documents = GofastEditableInput(documentsEl, formatedDocuments ? formatedDocuments : [], 'docstags', {
                isEditable : _task.canEdit,
                save: (newData) => {
                    
                    let docsIds = []
                    newData.forEach(doc => docsIds.push(doc.value))
                    let jsondata = JSON.stringify(docsIds)
                    _handleSaveData('attachements', jsondata)
                },
                isFrom: "kanban",
            })

            // Set TodoList
            let todoContainer = mainContainer.querySelector('.GofastTodoList')
            let todolist = GofastTodoList(todoContainer,{
                tasks: _task.tasks,
                cardId: _task.nid,
                spaceId: _task.space_nid,
                canEdit: _task.canEdit
            })

            // Set Timelines (Comments - History)
            let timeline = mainContainer.querySelector('.GofastKanbanTimeLine');
            timeline.innerHTML = _getCardTimeLine();

            let newCommentEl = timeline.querySelector('.GofastAddComment');
            newComment = GofastEditableInput(newCommentEl, '', 'ckeditor-classic', {
                isEditable: _task.canComment,
                templates: {
                    value: function (data) {
                        if(_task.canComment){
                            return '<div class="text-muted">' + Drupal.t('Enter your comment here ...', {}, {'context': 'gofast_kanban'}) + '</div>';
                        }else{
                            return '<div class="text-muted">' + Drupal.t('You are not allowed to comment here', {}, {'context': 'gofast_kanban'}) + '</div>';
                        }  
                    },
                    input : function () {                        
                        return "\n<textarea class=\"input-control form-control CEditor\"></textarea>\n<button type=\"submit\" id=\"save-cke\" name=\"op\" value=\"" + Drupal.t("Save") + "\" class=\"btn btn-sm btn-success form-submit icon-before\"> <span class=\"icon glyphicon glyphicon-ok\" aria-hidden=\"true\"></span> " + Drupal.t("Save") + "\n</button>\n&nbsp;\n<button type=\"submit\" id=\"cancel-cke\" name=\"op\" value=\"" + Drupal.t("Cancel") + "\" class=\"btn btn-sm btn-bg-secondary icon-before\"> <span class=\"icon glyphicon glyphicon-cross\" aria-hidden=\"true\"></span> " + Drupal.t("Cancel") + "\n</button>\n";
                    }
                },
                save: (newData) => {
                    if(newData.trim().length > 0){ 
                        _handleAddComment('comment_body', JSON.stringify(newData));                        
                
                    }
                },
                initCustomInput : async function(){
                    try {
                        let ckeditor = await ClassicEditor.create(this.DOM.input,{
                        //    removePlugins: ['CKFinderUploadAdapter', 'CKFinder', 'EasyImage', 'Image', 'ImageCaption', 'ImageStyle', 'ImageToolbar', 'ImageUpload', 'MediaEmbed'],
                            language: GofastLocale,
                            toolbar: {
                                items: [
                                        'heading',
                                        '|',
                                        'bold',
                                        'italic',
                                        'underline',
                                        'strikethrough',
                                        '|',
                                        'alignment',
                                        '|',
                                        'numberedList',
                                        'bulletedList',
                                        '|',
                                        'link',
                                        'blockquote',
                                        '|',
                                        'undo',
                                        'redo'
                                ]
                            }
                        });

                        this.DOM.customInput = ckeditor
                    } catch (error) {
                        console.log(error)
                    }
                },
                events: { 
                        showInputCustom : () => {
                            newCommentEl.querySelector('#save-cke').onclick = (e) =>{
                                let data = newComment.DOM.customInput.getData();
                                newComment.saveData(data);
                                newComment.DOM.customInput.setData('');
                                newComment.events.toogleInput(newComment, false) ;
                            };
                            
                            newCommentEl.querySelector('#cancel-cke').onclick = (e) =>{
                                newComment.DOM.customInput.setData('');
                                newComment.events.toogleInput(newComment, false); 
                            };
                        }
                }
            });
                        
            //Set Comment
            let commentsContainer = timeline.querySelector('#card__comments');
             _getCardComments(commentsContainer, _task.nid);
             

            // Set History/Audit
            let auditContainer = timeline.querySelector('#card__audit');
            _getCardAudit(auditContainer, _task.nid);
            
            
        }
        
        var _commentsReload = function(){
              
           let commentsContainer =  mainContainer.querySelector('#card__comments');
            _getCardComments(commentsContainer, _task.nid);
        }
        
        var _getCardComments = function(containerEl, taskid){
            Gofast.removeLoading();
            
              $.ajax({
                url: Drupal.settings.gofast.baseUrl + '/gofast/all_comments/render/' + taskid,
                type: 'GET',
                dataType: 'html',
                async: true,
                success: function (content) {
                    $(containerEl).html(content);
                    _formatCommentTemplateForKanban(containerEl);
                    
                    Drupal.attachBehaviors(containerEl);
                  
                  setTimeout(function () {
                    Gofast.checkReply();
                  }, 500);
                }
            });
            
        };
        
        var _formatCommentTemplateForKanban = function (containerEl) {

            //remove original form to addComment 
            containerEl.querySelector('div.gofastAddComment').remove();

            let commentContainers = containerEl.querySelectorAll('div.timeline-item');           
            commentContainers.forEach(function(container){
                
                container.querySelector('li.comment-reply').remove();
                container.querySelector('li.comment-permalink').remove();
                container.querySelector('div.timeline-content__header').remove();
                
                
                //Adapt edit and delete action to kanban  
                                               
                let btnEdit = container.querySelector('li.comment-edit');
                if(btnEdit){                   
                    let linkEdit = btnEdit.querySelector('a');
                    linkEdit.classList.remove('ctools-use-modal', 'ctools-modal-center', 'ctools-use-modal-processed');

                    var temp = linkEdit.getAttribute('href').split('/');
                    var commentId = temp[temp.length - 1];
                    linkEdit.setAttribute('href', '');
                    linkEdit.removeAttribute('href');
                    $(linkEdit).off('click'); // remove old action
                    
                    linkEdit.onclick = function(e){
                        editComment = container.querySelector('div.EditableInput__value');
                        editComment.dispatchEvent(editFromBtn);
                    }
                } 
                
                let btnDelete = container.querySelector('li.comment-delete');
                if(btnDelete){
                    let linkDelete = btnDelete.querySelector('a');
                    linkDelete.setAttribute('href', '');
                    $(linkDelete).off('click');

                    linkDelete.onclick = function(e){ 
                        _deleteComment(commentId);
                    }
                }
                
                          
                let originalComment = container.querySelector('.timeline-content__body').innerHTML;
                let editCommentEl = document.createElement('div')
                let editCommentObj = GofastEditableInput(editCommentEl, originalComment, 'ckeditor-comment', {
                    isEditable: true,
                    save: (newData) => {
                        if (newData.trim().length > 0 && (newData !== this.initialValue) ) {
                            _handleEditComment('comment_body', JSON.stringify(newData), commentId);
                        }
                    },
                    events: { 
                        showInputCustom: () => {
                            editCommentEl.querySelector('button.save-cke').onclick = (e) =>{
                                let data = editCommentObj.DOM.customInput.getData();
                                editCommentObj.saveData(data);
                                editCommentObj.events.toogleInput(editCommentObj, false) ;
                            };
                    
                            editCommentEl.querySelector('button.cancel-cke').onclick = (e) =>{
                                editCommentObj.events.toogleInput(editCommentObj, false); 
                            };
                        }
                    }
                });
                
                let commentBody = container.querySelector('.timeline-content__body');
                commentBody.innerHTML = '';
                commentBody.appendChild(editCommentEl);
                
                const editFromBtn = new CustomEvent('editFromButton',{
                            detail: {},
                            bubbles: true,
                            cancelable: true,
                            composed: false
                        });
                               
                
            });
        };
        
        var _getCardAudit = function(containerEl, taskid){
            Gofast.removeLoading();
            $.ajax({
                url: Drupal.settings.gofast.baseUrl + '/kanban/task/'+taskid+'/render/audit',
                type: 'GET',
                dataType: 'html',
                async: true,
                success: function (content) {
                  $(containerEl).html(content);
                  Drupal.attachBehaviors(containerEl);
                  // _getCardAuditTemplate();

                }
            });
        }

        var _getCardTimeLine = function (){

            return "<ul class=\"nav nav-tabs nav-fill gofastTab w-100 mb-0 justify-content-end flex-nowrap\">    \n<li class=\"nav-item \"> <a class=\"nav-link px-2 d-flex justify-content-center active\" data-toggle=\"tab\" href=\"#card__comment\"> <span class=\"nav-icon\"><i class=\"fas fa-comments icon-nm\"></i></span> <span class=\"nav-text\">" + Drupal.t("Comments", {}, { context: "gofast_kanban" }) + "</span> </a>\n</li> <li class=\"nav-item \"> <a class=\"nav-link px-2 d-flex justify-content-center\" data-toggle=\"tab\" href=\"#card__audit\"> <span class=\"nav-icon\"><i class=\"fas fa-history icon-nm\"></i></span> <span class=\"nav-text\">" + Drupal.t("Audits", {}, { context: "gofast_kanban" }) + "</span> </a>\n</li>\n</ul>\n<div class=\"card-body p-0 overflow-hidden\">\n<div class=\"tab-content scrollable p-3 w-100\" id=\"myTabContent\"> <div class=\"tab-pane fade show active \" id=\"card__comment\" role=\"tabpanel\" aria-labelledby=\"info-tab\"> <div id=\"card__comment_form\"> <div class = \"row\"> <div class=\"col-lg-12\"> <div class=\"KanbanCard__comment  Detail__container\">  <div class=\"GofastAddComment\"></div> </div> </div> </div>   <div class=\"separator separator-solid my-3\"></div> </div> <div id=\"card__comments\"> <div id=\"node-info-content-unprocessed\" class=\"spinner spinner-center spinner-primary spinner-lg m-5 not-processed h-100 w-100\"></div> </div> </div> <div class=\"tab-pane fade\" id=\"card__audit\" role=\"tabpanel\" aria-labelledby=\"info-tab\"> <div id=\"node-info-content-unprocessed\" class=\"spinner spinner-center spinner-primary spinner-lg m-5 not-processed h-100 w-100\"></div> </div>\n</div> \n</div>";
        }
        
         var _getConfirmModalContent = function () {

            return "<div class=\"modal-dialog\">\n<div class=\"modal-content\"> <div class=\"modal-header\"><h5 class=\"modal-title text-white\"></h5></div>  <div class=\"modal-body\"></div> <div class=\"modal-footer\"></div>\n</div>\n</div>";
        }
        
        
        var _deleteComment = function(cid, callback){
            //mainContainer = el
            _callback = callback
            
            //Confirmation modale
            let confirmModal = document.createElement('div')
            confirmModal.classList = "modal fade"
            confirmModal.innerHTML = _getConfirmModalContent();
                
            confirmModalTitle = confirmModal.querySelector('.modal-title')
            confirmModalTitle.innerText = Drupal.t('Confirm comment deletion', {}, {'context': 'gofast_kanban'})
            
            confirmModalBody = confirmModal.querySelector('.modal-body')
            confirmModalBody.innerHTML = ' <p>'+Drupal.t('Are you sure you want to delete this comment ?', {}, {'context': 'gofast_kanban'})+'</p>'
            
            confirmModalFooter = confirmModal.querySelector('.modal-footer')
            let cancelBtn =  document.createElement('button')
            cancelBtn.type = 'button'
            cancelBtn.classList = 'btn btn-light'
            cancelBtn.innerText = Drupal.t('Cancel', {}, {'context': 'gofast_kanban'})
            cancelBtn.onclick = function(e){
                 e.preventDefault()                              
                 $(confirmModal).modal('hide');
            }
            confirmModalFooter.appendChild(cancelBtn);
            
            let confirmBtn =  document.createElement('button')
            confirmBtn.type = 'button'
            confirmBtn.classList = 'btn btn-sm btn-danger'
            confirmBtn.innerText = Drupal.t('Confirm', {}, {'context': 'gofast_kanban'})
            confirmBtn.onclick = function(e){
                
                 e.preventDefault(); 
                 _handleDeleteComment(cid);
                 $(confirmModal).modal('hide');
            }
            confirmModalFooter.appendChild(confirmBtn);
            
            $(confirmModal).modal('show')    
        }
        
        
        var _delete = function(el, callback){
            
            mainContainer = el
            _callback = callback
            
            //Confirmation modale
            let confirmModal = document.createElement('div')
            confirmModal.classList = "modal fade"
            confirmModal.innerHTML = _getConfirmModalContent();
                
            confirmModalTitle = confirmModal.querySelector('.modal-title')
            confirmModalTitle.innerText = Drupal.t('Confirm card deletion', {}, {'context': 'gofast_kanban'})
            
            confirmModalBody = confirmModal.querySelector('.modal-body')
            confirmModalBody.innerHTML = ' <p>'+Drupal.t('Are you sure you want to delete this card ?', {}, {'context': 'gofast_kanban'})+'</p>'
            
            confirmModalFooter = confirmModal.querySelector('.modal-footer')
            let cancelBtn =  document.createElement('button')
            cancelBtn.type = 'button'
            cancelBtn.classList = 'btn btn-light'
            cancelBtn.innerText = Drupal.t('Cancel', {}, {'context': 'gofast_kanban'})
            cancelBtn.onclick = function(e){
                 e.preventDefault()                              
                 $(confirmModal).modal('hide');
            }
            confirmModalFooter.appendChild(cancelBtn);
            
            let confirmBtn =  document.createElement('button')
            confirmBtn.type = 'button'
            confirmBtn.classList = 'btn btn-sm btn-danger'
            confirmBtn.innerText = Drupal.t('Confirm', {}, {'context': 'gofast_kanban'})
            confirmBtn.onclick = function(e){
                 e.preventDefault(); 
                 _handleDeleteCard();
                 $(confirmModal).modal('hide');
                 window.ktKanbanItem.hideCardModal();
            }
            confirmModalFooter.appendChild(confirmBtn);
            
            $(confirmModal).modal('show')    

        }

        var _submit = function(data){
            console.log(data)
            return new Promise(resolve => setTimeout(resolve, 1000));
        }
        

        return {
            init(el, initialData, callback){
                _init(el, initialData, callback)
            },
            delete(el, callback){
                _delete(el, callback)
            }
        }

    }

    window.GofastKanbanCardDetail = function(){
        return GofastKanbanCardDetail()
    }

})(jQuery, Drupal, Gofast);
