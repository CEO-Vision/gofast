window.GofastTodoList = (el, props = {}) => {
    
    let todolist = {
        container: undefined,
        tasksContainer: undefined,
        createForm: undefined,
        progressBar: undefined,
        tasks: [],
        tasksEl: [],
        cardId: undefined,
        createForm: undefined,
        spaceId: undefined,
        canEdit : false,
        createTaskEl(task){
            let newTaskEl = GofastTodoItem(task)
            newTaskEl.onDelete = () => {
                this.removeTask(task)
            }

            newTaskEl.onUpdate = (taskId, field, newValue) => {
                this.taskUpdate(taskId, field, newValue);
//                if(field == "deadline"){
//                    this.reloadTaskEl(true);
//                }
            }
            newTaskEl.onChecked = (taskId, isChecked) => this.taskChecked(taskId, isChecked)

            newTaskEl.handleCheck = (task) => {

                if(task.isDone) {
                    newTaskEl.element.querySelector('.GofastTodoList__nameInput').classList.add('isDone')
                } else {
                    newTaskEl.element.querySelector('.GofastTodoList__nameInput').classList.remove('isDone')
                }

                this.reloadTaskEl(true);
            }

            return newTaskEl
        },
        removeTask(task){
            let index = this.tasks.indexOf(task)
            if(index > -1){
                this.tasks.splice(index,1)
            }
            this.reloadTaskEl(true)

        },
        reloadTaskEl : async function(force = false){
            
            //get updated tasks
            if(force == true){
               const resp = await fetch(window.origin + '/kanban/task/' + this.cardId + '/get');
               const data = await resp.json();
               this.tasks = data.tasks;
            }

            if(this.tasks && this.tasks.length > 0){
                let newTasksEl = []
               
                //sort by date
                this.tasks.sort(function(a, b){
                    return a.deadline - b.deadline;
                })

                let spaceId = this.spaceId;
                this.tasks.forEach(task => {
                    task.spaceId = spaceId;
                    let newEl = this.createTaskEl(task);
                    newTasksEl.push(newEl);
                })

                this.tasksEl = newTasksEl;
                this.reloadTaskContainer();

            } else {
                this.tasksContainer.innerHTML = "<div class=\"p-2 text-muted\">" + Drupal.t("No tasks in the list", {}, { context: "gofast_kanban" }) + "</div>";
            }

            this.reloadProgress()

        },
        reloadTaskContainer(){                      
            this.tasksContainer.innerHTML = ''
            this.tasksEl.forEach((task) => {
                this.tasksContainer.appendChild(task.element)
            })
        },
        reloadProgress(){


            let progress = 0
            let progressValue = 0

            if(this.tasks && this.tasks.length > 0){
                this.tasks.forEach(task => {
                    if(task.isDone) progress++
                })
                progressValue = (progress / this.tasks.length) * 100
            }
            this.progressBar.firstChild.style.width = progressValue + "%";
            window.ktKanbanItem.reload();

        },
        handleCreateFormSubmit(task){},
        taskUpdate: async function(taskId, field, value){

            let formData = new FormData()
            formData.append(field, value)

            let url = window.origin + "/kanban/task/update/todo/" + taskId;
            
              //check if card node has not been deleted
              const card_status = this.getCardStatus();
              if( card_status == 0){
                  window.ktKanbanItem.reload();
                  this._displayCardDeletedMsg();
              }else{

                const res = await fetch(url, {
                    method: 'POST',
                    body: formData
                });
                
                let field_t = Drupal.t(field, {}, { 'context': 'gofast_kanban' });     
                Gofast.toast(Drupal.t('Your modification on @field has been saved', {'@field': field_t}, { 'context': 'gofast' }), 'info');
                
            
                return await res
              }
        },
        taskChecked: async function(taskId, isChecked){

            //check if card node has not been deleted
            const card_status = this.getCardStatus();
            if( card_status == 0){
                window.ktKanbanItem.reload();
                this._displayCardDeletedMsg();
            }else{

                let url = window.origin + "/kanban/task/update_status/todo/" + taskId + "/" + (isChecked ? "1" : "0");
                const res = await fetch(url, {
                    method: 'POST',
                })

                return await res
            }
        },
        showCreate(){},
        handleOnSubmitForm: async function(event){

            let taskname = event.target['taskname'].value

            if(taskname.length >= 2) {

                try {
                    let formData = new FormData()
                    formData.append('label', taskname)

                    
                      //check if card node has not been deleted
                    const card_status = this.getCardStatus();
                    if( card_status == 0){
                        window.ktKanbanItem.reload();
                        this._displayCardDeletedMsg();
                    }else{
                        let url = window.origin + "/kanban/task/" + this.cardId + "/add/todo";

                        const res = await fetch(url, {
                            method: 'POST',
                            body: formData
                        })

                        const data = await res.json()
                        const itemId = await data.id

                        let newTask = {
                            id: itemId,
                            name: taskname,
                            deadline: null,
                            responsable: null,
                            isDone: false,
                            canEdit: true,
                            canDo: true
                        }
                        this.tasks.push(newTask);
                    }

                } catch (error) {
                    console.log(error.message)

                }

                this.reloadTaskEl(true);
                event.target['taskname'].classList.remove('is-invalid')
                event.target.reset()

                event.target.scrollIntoView()

            } else {
                event.target['taskname'].classList.add('is-invalid')
            }
            
        },
        getCardStatus(){
            let url = window.origin + "/kanban/task/" + this.cardId + "/get_status";
            var status = 0;
             
             $.ajax({
                 url: url,
                 type: 'POST',
                 dataType: 'json',
                 async: false,
                 success: function (content) {
                     status = content;
                 }
             });
             
             return status;
        },
         _displayCardDeletedMsg(){
            
            var mainContainer = this.container.closest('.gofastKanbanCardDetail');
            if(mainContainer.querySelector('#card_error_message') == null){
                var elCardDeleteMsg = document.createElement("div");
                elCardDeleteMsg.innerHTML =  '<div id="card_error_message" class="alert alert-custom alert-notice alert-light-danger fade show" role="alert"> '
                                    +'<div class="alert-icon"><i class="flaticon-warning"></i></div>' 
                                    +'<div class="alert-text">'+window.parent.Drupal.t("This card has been deleted, your modifications would not be saved.", {},{ context: "gofast_kanban" }) +'</div></div>';
                mainContainer.prepend(elCardDeleteMsg);
                
                Gofast.toast(Drupal.t('Your modification could not be saved: the card had been deleted.', {}, { 'context': 'gofast' }), 'error');
            }
        },

        init(element){

            this.container = element


            this.progressBar = document.createElement('div')
            this.progressBar.className = 'GofastTodoList__progress progress'
            this.progressBar.innerHTML = "<div class=\"progress-bar\" role=\"progressbar\" style=\"width: 0\" aria-valuenow=\"0\" aria-valuemin=\"0\" aria-valuemax=\"100\"></div>";

            this.container.appendChild(this.progressBar)


            this.tasksContainer = document.createElement('div')
            this.tasksContainer.className = 'GofastTodoList__list'
            this.container.appendChild(this.tasksContainer)


            this.createForm = document.createElement('form')
            this.createForm.className = 'GofastTodoList__create fade show d-none'
            this.createForm.innerHTML = "\n<div class=\"input-icon input-icon-right\"> <input type=\"text\" class=\"form-control form-control-sm\" name=\"taskname\" placeholder=\"" + Drupal.t("New task name", {}, { context: "gofast_kanban" }) + "\"> <span> <button class=\"btn btn-icon\" type=\"submit\"><i class=\"fas fa-check text-success\"></i></button> <button class=\"btn btn-icon\" type=\"reset\"><i class=\"fas fa-times text-danger\"></i></button> </span>\n</div>\n";

            this.container.appendChild(this.createForm)

            let createFormToggle = document.createElement('button')
            createFormToggle.className = 'btn btn-sm btn-primary'
            createFormToggle.innerText = Drupal.t('Add new task', {}, {'context' : 'gofast_kanban'});

            this.container.appendChild(createFormToggle)
  
            if(this.canEdit){
                
                this.createForm.onsubmit = (e) => {
                    e.preventDefault()
                    this.handleOnSubmitForm(e)
                }

                createFormToggle.onclick = (e) => {
                    e.preventDefault()
                    e.stopPropagation()

                    e.target.classList.add('d-none')
                    this.createForm.classList.remove('d-none')

                    this.createForm['taskname'].focus()
                }

                this.createForm.onreset = function (e) {
                    e.target.classList.add('d-none')
                    createFormToggle.classList.remove('d-none')
                }
            }else{
                 createFormToggle.className = 'btn btn-sm btn-bg-secondary disabled'
            }

            this.reloadTaskEl()
        },

        ...props

    }

    todolist.init(el)

    return todolist
}

const GofastTodoItem = (task) => {
    let _task = {
        task: {
            id: undefined,
            name: undefined,
            responsable: undefined,
            deadline: undefined,
            spaceId: undefined,
            isDone: false,
            canEdit: false,
            canDo : false
        },
        element: undefined,
        template: undefined,
        inputs: [],
        taskNameUpdate(newValue){
            return new Promise(resolve => setTimeout(resolve, 2000))
        },
        taskResponsableUpdate(newValue){
            let newResponsable = {
                id: newValue.id,
                name: newValue.name,
                avatar: newValue.avatar,
                email: newValue.email
            }
            this.task.responsable = newResponsable
            return new Promise(resolve => setTimeout(resolve, 2000))
        },
        taskDeadlineUpdate(newValue){
            this.task.deadline = newValue
            return new Promise(resolve => setTimeout(resolve, 2000))
        },
        taskDelete : async function(taskId){
            let url = window.origin + "/kanban/task/delete/todo/" + taskId;
            const res = await fetch(url, {
                method: 'POST',
            })

            return await res
        },
        onUpdate: undefined,
        handleCheck: undefined,
        init(task){
            this.task = task
            this.element = document.createElement('div')
            this.element.className = 'GofastTodoList__item'
            
            let checkbox = document.createElement('label')
            checkbox.className = 'checkbox'
            checkbox.innerHTML = "\n<input type=\"checkbox\"/>\n<span></span>\n";
            checkbox.firstElementChild.checked = this.task.isDone
            if(this.task.canDo){
                checkbox.onchange = async (e) => {
                    try {
                        let isChecked = e.target.checked
                        let res = await this.onChecked(this.task.id, isChecked)
                        this.task.isDone = e.target.checked
                        this.handleCheck(this.task)

                    } catch (error) {
                        console.log(error.message)
                    }
                }
            }else{
                checkbox.className = 'checkbox disabled'
                checkbox.querySelector('input').setAttribute('disabled', 'disabled');
            }
            //TODO: handle change
            this.element.appendChild(checkbox)


            // task name
            let nameInputEl = document.createElement('div')
            nameInputEl.classList.add('GofastTodoList__nameInput', 'EditableInput')

            let nameInput = GofastEditableInput(nameInputEl, this.task.name, 'text', { 
              isEditable: this.task.canEdit,
              widenInput: true,
              save: (newData) => this.onUpdate(this.task.id, 'label', newData),
            })
          
            if(this.task.isDone) nameInputEl.classList.add('isDone')
            this.inputs.push(nameInputEl)


            if(this.task.responsible) {
                this.task.responsible.id = this.task.responsible.uid
                this.task.responsible.text = this.task.fullname;
            }

            // task responsible
            let responsableInputEl = document.createElement('div')
            responsableInputEl.classList.add('GofastTodoList__responsableInput', 'EditableInput')

            let responsableInput = GofastEditableInput(responsableInputEl, this.task.responsible , 'userselect', {
                isEditable: this.task.canEdit,
                save: (newData) => this.onUpdate(this.task.id, 'person-in-charge', newData.uid),
            })
            
            
            //switch select2 data url
            $(responsableInput.DOM.input).select2({
                ajax: {
                    url: function(params){
                        return window.origin + "/kanban/autocomplete/user/" + task.spaceId + "/" + params.term;
                    },
                    dataType: 'json',
                    data: function (params) {
                        return { };
                    },
                    delay: 250,
                    processResults: function (data) {
  
                      //  let data_array = Object.values(data);
                        let newData  = Object.values(data).map(user => {
                            user.text = user.firstname+' '+user.lastname;
                            user.id = user.uid;
                            return user;
                        })
                        
                        //Add none 
                        newData.push({  'text':  Drupal.t('None', {}, {'context': 'gofast_kanban'}),
                                        'id': 0,
                                        'uid' : 0,
                                        'picture' : ''});
                                    
                        return {
                          results: newData
                        };
                    }
                },
                placeholder: Drupal.t('Search User', {}, {'context': 'gofast_kanban'}),
                minimumInputLength: 3,
                // minimumResultsForSearch: Infinity,
                templateResult: responsableInput.templates.selectionItemTemplate,
                templateSelection: responsableInput.templates.suggestionItemTemplate,
                language: GofastLocale,
            });
       

            if(responsableInput.data != null){
                Object.entries(responsableInput.data).forEach(([key, value]) => {
                    $(responsableInput.DOM.input).select2("data")[0][key] = value
                })
            }
            this.inputs.push(responsableInputEl)

            // task responsible
            let deadlineInputEl = document.createElement('div')
            deadlineInputEl.classList.add('GofastTodoList__deadlineInput', 'EditableInput')

            let deadlineInput = GofastEditableInput(deadlineInputEl, this.task.deadline , 'date', {
                isEditable: this.task.canEdit,
                save: (newData) => this.onUpdate(this.task.id, 'deadline', newData),
            })

            this.inputs.push(deadlineInputEl)



            this.inputs.forEach((item) => {
                if(!item.container){

                    this.element.appendChild(item)
                } else {

                    this.element.appendChild(item.container)
                }
            })

            if(this.task.canEdit){
                let removeBtn = document.createElement('button')
                removeBtn.className = 'btn btn-icon btn-xs GofastTodoList__removeButton'
                removeBtn.innerHTML = "<i class=\"fas fa-times text-danger\"></i>";

                removeBtn.onclick = (e) => {
                    this.taskDelete(this.task.id);
                    this.onDelete();
                }

                this.element.appendChild(removeBtn)
            }

        },
    }

    _task.init(task)

    return _task
}
