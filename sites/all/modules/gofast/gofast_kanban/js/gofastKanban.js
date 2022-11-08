(function ($, Drupal, Gofast) {

    var KTKanbanBoard = function () {

        let component;
        let loader;
        let kanban;
        let kanbanContainer;
        let kanbanId;
        let _psBoardsContainer;
        let _psBoards = [];
        let _searchInput;
        let _modal;
        let _modalTitle;
        let _modalContent;
        let _modalFooter;
        let _cardDetail = null;
        let _selfUpdate = false;

        /*
         *   KANBAN INIT
         */

        var _kanbanElement = {
            title: undefined,
            nid: undefined,
            comments_count: 0,
            deadline: undefined,
            deadline_color_indicator: undefined,
            progress: undefined,
            nb_items: undefined,
            nb_items_completed: undefined,
            members: [],
            board_id: undefined,
            state: undefined,
            element() {

                let members;
                let othersMembers;
                let popOverOthers;
                
                //add responsible to members display
                if( this.person_in_charge && this.person_in_charge != 0){  
                    if (undefined == this.members.find(mem => mem.uid == this.person_in_charge.uid)){
                        this.members.unshift(this.person_in_charge);
                    }
                }
                

                if (this.members.length < 6) {
                    members = this.members
                    othersMembers = []
                } else {
                    //TODO: members.join('') for print string array
                    members = this.members.slice(0, 5)
                    othersMembers = this.members.slice(5)
                    popOverOthers = othersMembers.map(mem => {

                        return "<li class='navi-item text-truncate'>\n<span class='navi-bullet mr-1'><i class='bullet bullet-dot'></i></span>\n<span class='navi-text'>" + mem.fullname + "</span>\n</li>";

                    })
                }

                let membersGroup = []
                members.forEach(mem => {
                    let template = "\n<div class=\"symbol symbol-circle symbol-35\" data-toggle=\"popover\" data-trigger=\"hover\" data-placement=\"top\" data-content=\"" + mem.fullname + "\"> <img alt=\"Gofast user avatar\" loading=\"lazy\" src=\"" + mem.picture + "\">\n</div>\n";
                    membersGroup.push(template)
                })

                let deadline_color =  'label-success';
                if(this.deadline_color_indicator == 'deadline-nearly-reached'){
                    deadline_color =  'label-warning';
                }else if(this.deadline_color_indicator == 'deadline-reached'){
                    deadline_color =  'label-danger';
                }else if(this.deadline_color_indicator == 'deadline-reached-off' || this.deadline_color_indicator == 'deadline-nearly-reached-off' ){
                     deadline_color =  'label-secondary';
                }

                return '\n<div class="card card-custom p-4"> <!--begin::Header--> <div class=""> <!--begin::Info--> <div class="d-flex align-items-center justify-content-between"> <div class="d-flex flex-column w-100"> <div class="d-flex justify-content-between w-100"> <a href="#" class="text-dark-75 text-hover-primary font-weight-bolder font-size-lg">' +
                this.title +
                "</a> " +
                (this.state
                  ? ' <span class="label label-sm label-outline-warning label-pill label-inline">' +
                    this.state +
                    "</span> "
                  : "") +
                " </div> " +
                (this.deadline
                  ? ' <div class="d-flex align-items-center mt-2">  <span class="label label-xl label-dot ' +
                    deadline_color +
                    ' mr-2"></span> <span class="text-muted font-weight-bold line-height-0">' +
                    this.deadline +
                    "</span> </div> "
                  : "") +
                ' </div> </div> <!--end::Info--> </div> <!--end::Header--> <!--begin::Body--> <div class="card-body px-0 pb-0 pt-2 d-flex flex-column"> ' +
                (this.nb_items && this.nb_items > 0
                  ? ' <div class="progress my-2"> <div class="progress-bar" role="progressbar" style="width: ' +
                    this.progress +
                    '%;" aria-valuenow="' +
                    this.progress +
                    '" aria-valuemin="0" aria-valuemax="100">' + 
                        '<span class="'+(this.nb_items_completed == 0 ?'empty-progression text-dark-75' :'') +'">' +
                        this.nb_items_completed +
                        "/" +
                        this.nb_items +
                        "</span>" + 
                    "</div> </div> "
                  : "") +
                ' <div class="d-flex justify-content-between align-items-center"> ' +
                (membersGroup.length > 0
                  ? '<div class="symbol-group symbol-hover"> ' +
                    membersGroup.join("") +
                    " " +
                    (othersMembers.length > 0
                      ? ' <div class="symbol symbol-35 symbol-circle symbol-light-primary" data-toggle="popover" data-html="true" data-trigger="hover" data-placement="top" data-content="<ul class=\'navi\'>' +
                        popOverOthers.join("") +
                        '</ul>"> <span class="symbol-label font-weight-bolder">+' +
                        othersMembers.length +
                        "</span> </div>"
                      : "") +
                    " </div>"
                  : "") +
                " " +
                (this.comments_count > 0
                  ? '<div class=""> <span class="nav-icon"><i class="fas fa-comments icon-lg"></i></span> <span class="nav-text font-size-h4  text-muted">' +
                    this.comments_count +
                    "</span> </div>"
                  : "") +
                " </div> </div> <!--end::Body-->\n</div>\n";
            }
        }

        var _config = {

            element: '#goKanban',
            // space between boards
            gutter: '15px',

            // board width
            widthBoard: '300px',

            // use percentage in the width of the boards
            responsivePercentage: false,

            // make work items draggable?
            dragItems: false,

            // make boards draggable?
            dragBoards: false,

            // add board button
            // addItemButton: true,

            // buttonContent: null,

            itemAddOptions: {
                enabled: true, // add a button to board for easy item creation
                content: '<i class="fas fa-plus"></i>', // text or html content of the board button
                class: 'kanban-title-button btn btn-default btn-xs', // default class of the button
                footer: true                                                // position the button on footer
            },
            itemHandleOptions: {
                enabled: false, // if board item handle is enabled or not
                handleClass: "item_handle", // css class for your custom item handle
                customCssHandler: "drag_handler", // when customHandler is undefined, jKanban will use this property to set main handler class
                customCssIconHandler: "drag_handler_icon", // when customHandler is undefined, jKanban will use this property to set main icon handler class. If you want, you can use font icon libraries here
                customHandler: "<span class='item_handle'>+</span> %s"// your entirely customized handler. Use %s to position item title
            },

            // // add board button content
            // buttonContent: "<a href=\"#\" class=\"btn btn-icon btn-xs btn-facebook\"><i class=\"fas fa-plus\"></i></a>",

            // add board button onClick
            buttonClick: function (el, boardId) {
                modal.dataset.id = boardId
                $(modal).modal('show')
            },

            // item board onClick
            click: function (el) {
                _displayTaskViewModal(el)
            },
            // callback when any board's item are dragged
            dragEl: function (el, source) {},
            // callback when any board's item stop drag
            dragendEl: function (el) {},
            // callback when any board's item drop in a board
            dropEl: function (el, target, source, sibling) {
                _handleDropTask(el, target, source, sibling)
            },
            // callback when any board stop drag
            dragBoard: function (el, source) { },
            // callback when any board stop drag
            dragendBoard: function (el) {
                _handleDropBoard(el)
            }, 
            canEdit: false
        }

        var _initKanban = async function () {
            component = document.querySelector('#gofastKanban')            
            if (component) {
                kanbanId = component.dataset.kid
                if (kanbanId && kanbanId > 0) {
                    loader = component.querySelector('.gofastSpinner')
                    kanbanContainer = component.querySelector('#goKanban')
                    _searchInput = document.querySelector('#gofastKanbanSearchQuery')

                    // set modal task detail
                    _modal = document.querySelector('#gofastKanbanModal')
                    _modalContent = _modal.querySelector('.modal-taskDetail')
                    _modalTitle =  _modal.querySelector('.modal-title')
                    _modalFooter = _modal.querySelector('.modal-footer')

                    $(_modal).on('hidden.bs.modal', function (e) {
                        if (!_modalContent || !_modalFooter || !_modalTitle) {
                            return;
                        }
                        _modalContent.innerHTML = ''
                        _modalFooter.innerHTML = ''
                        _modalFooter.classList = 'modal-footer'
                        _modalTitle.innerText = ''
                        _cardDetail = null
                    });
                   // $(_modal).on('hide.bs.modal', () => _reloadKanban())

                    const kanbanHeight = kanbanContainer.offsetHeight;

                    _createKanban()
                   await _reloadKanban(true);
                   
                    // Set handlers to form and input
                    let bcard = document.querySelector('.gofastKanban__newColumn');
                    let bform = document.querySelector('.newColumn__form');
                    let binput = document.querySelector('.newColumn__input');

                    if (bform && binput) {
                        if(kanban.options.canEdit){
                            bform.querySelector('.newColumn__actions > button').classList = "btn btn-sm btn-primary mr-2";
                            bform.querySelector('.newColumn__actions > button').removeAttribute("disabled");
                            bform.querySelector('.newColumn__input').removeAttribute("readonly");
                            
                            
                            binput.onfocus = function (e) {
                                bform.classList.add('newColumn__form--focus');
                            }
                            bform.onsubmit = function (e) {
                                e.preventDefault();
                                _handleAddBoardOnSubmit(bform);
                            }
                            bform.onreset = function (e) {
                                bform.classList.remove('newColumn__form--focus');
                            }
                        }else{
                            bform.querySelector('.newColumn__actions > button').classList = "btn btn-sm btn-bg-secondary disabled mr-2";
                            bform.querySelector('.newColumn__actions > button').setAttribute("disabled", true);
                            bform.querySelector('.newColumn__input').setAttribute("readonly", true);
                        }
                    }

                    // set onchange search handler
                    let timeout = null
                    _searchInput.oninput = function (e) {
                        clearTimeout(timeout)
                        _setLoadingState(true)
                        timeout = setTimeout(function () {
                            _handleSearhChange(_searchInput.value)
                        }, 500)
                    }
                }
            } else {
                return new Error('Kanban not found');
            }
            
            //Open given card Id
            const queryString = window.location.search;

            const params = queryString.split('&');
            var new_params = [];
            var card_id = null;
            //Remove card_id from url params
            params.forEach(function(param){
                if(! param.startsWith('card_id') && param != "?"){
                    new_params.push(param);
                }else if (param.startsWith('card_id')){
                     card_id = param.replace('card_id=', '');
                }
            });

            if(card_id !== null){
                _openCard(card_id);
                var new_url = window.location.pathname+'?'+ new_params.join('&');
                window.history.replaceState(window.location.hostname,document.title,new_url);
                // window.location.hash = '';
            }
        }

        var _createKanban = function () {    
            kanban = new jKanban({
                ..._config,
                boards: [],
                // Handle item scrolling
                dragEl: function (el, source) {
                    document.addEventListener('mousemove', isDragging);
                },

                dragendEl: function (el) {
                    document.removeEventListener('mousemove', isDragging);
                }
            });
            
            // Set jKanban max height
            const allBoards = kanbanContainer.querySelectorAll('.kanban-drag');
            allBoards.forEach(board => {
                board.style.maxHeight = kanbanHeight + 'px';
            });
            
            const isDragging = (e) => {
                const allBoards = kanbanContainer.querySelectorAll('.kanban-drag');
                
                allBoards.forEach(board => {
                    // Get inner item element
                    const dragItem = board.querySelector('.gu-transit');

                    // Stop drag on inactive board
                    if (!dragItem) {
                        return;
                    }

                    // Get jKanban drag container
                    const containerRect = board.getBoundingClientRect();

                    // Get inner item size
                    const itemSize = dragItem.offsetHeight;

                    // Get dragging element position
                    const dragMirror = document.querySelector('.gu-mirror');
                    const mirrorRect = dragMirror.getBoundingClientRect();
                    
                    // Calculate drag element vs jKanban container
                    const topDiff = mirrorRect.top - containerRect.top;
                    const bottomDiff = containerRect.bottom - mirrorRect.bottom;

                    // Scroll container
                    if (topDiff <= itemSize) {
                        // Scroll up if item at top of container
                        board.scroll({
                            top: board.scrollTop - 3,
                        });
                    } else if (bottomDiff <= itemSize) {
                        // Scroll down if item at bottom of container
                        board.scroll({
                            top: board.scrollTop + 3,
                        });
                    } else {
                        // Stop scroll if item in middle of container
                        board.scroll({
                            top: board.scrollTop,
                        });
                    }
                });
            }
            
        }
        
        /*
         *   UTILS
         */
        var _reloadKanbanItems = function (items) {
            if (items && items.length > 0) {
                items.forEach(item => {
                    if (item.board_id && item.nid) {
                        // if there already are elements in the board, we don't need to add them again
                        // this can happen in case of multiple saveData occurring at the same time
                        // (typically multiple _deleteAllKanbanBoards _then_ multiple _reloadKanbanItems),
                        if ([...kanban.getBoardElements(item.board_id)].some(el => el.dataset.eid == item.board_id)) {
                            return;
                        }
                        item.__proto__ = _kanbanElement
                        
                        kanban.addElement(item.board_id, {
                            id: item.nid,
                            title: item.element(),
                            index: item.column_index,
                            class: ["p-0", "gofastKanban__item"]
                        })
                    }
                })
            }
            _setLoadingState(false)
        }

        var _reloadKanbanBoards = function (data) {

            kanban.options.canEdit = data.canEditBoards;
            kanban.options.canAddCard = data.canAddCard;
            kanban.options.dragBoards = data.canEditBoards;
            kanban.options.dragItems = data.canMoveCards;
           
            if (data.boards && data.tasks) {
                const {boards, tasks, canEdit} = data
                if (boards.length > 0) {
                    let formattedBoards = []
                    boards.forEach(board => {
                        let newBoard = {
                            id: board.id,
                            title: board.title,
                        }
                        formattedBoards.push(newBoard)
                    })
                    // Add board to kanban
                    kanban.addBoards(formattedBoards)
                    // Set custom header
                    _setCustomHeadersBoards(formattedBoards)

                    // Reload board items
                    _reloadKanbanItems(tasks)
                }
            }
        }

        var _reloadKanban = async function (init = false) {

            if( _getIsLoading() == true && init != true ){
                Gofast.xhrPool.abortAll();
            }else{
                _setLoadingState(true);
            }

            _deleteAllKanbanBoards()

            const res = await fetch(window.origin + "/kanban/" + kanbanId + "/view");
            const data = await res.json()
            _reloadKanbanBoards(data)
            _setAllPopovers()

        }

        var _setLoadingState = function (isLoading = true) {
            isLoading ? loader.classList.add('show') : loader.classList.remove('show')
            isLoading ? kanbanContainer.classList.remove('show') : kanbanContainer.classList.add('show')
        }


        var _getIsLoading = function() {
            return loader.classList.contains("show") ? true : false;
        }
        
        var _deleteAllKanbanBoards = function () {
            if (kanban.options.boards) {
                // Delete scroll
                _deleteAllPsBoards()
                _deletePsBoardContainer()
                _deleteAllPopovers()
                // Delete Boards
                let currentBoards = [...kanban.options.boards]
                currentBoards.forEach(board => kanban.removeBoard(board.id))
                // kanban.boardContainer = []
            }
        }

        var _updateAllTaskIndex = function () {
            let boards = kanban.options.boards
            if (boards) {
                boards.forEach(board => {
                    let elements = kanban.getBoardElements(board.id)
                    if (elements.length > 0) {
                        elements.forEach((el, index) => el.dataset.index = index)
                    }
                })
            }
        }

        var _displayBoardHeaderForm = function (header, isDisplay) {

            let form = header.querySelector('form')
            let title = header.querySelector('.kanban-title-board')
            let tools = header.querySelector('.kanban-title-tools')

            if (isDisplay) {

                title.classList.add('d-none')
                tools.classList.add('d-none')

                form.classList.remove('d-none')
                form.classList.add('show')

            } else {

                form.classList.remove('show')
                form.classList.add('d-none')

                title.classList.remove('d-none')
                tools.classList.remove('d-none')

            }


        }

        var _setCustomHeadersBoards = function (boardsList) {
            if (boardsList.length > 0) {
                boardsList.forEach(function (board) {
                    let boardEl = kanban.findBoard(board.id)
                    if (boardEl) {
                        let header = boardEl.querySelector('.kanban-board-header')
                        let board_id = board.id
                        let title = header.querySelector('.kanban-title-board')
                        let div = document.createElement('div')
                        let button = document.createElement('button')

                        let settings = document.createElement('div')
                        settings.innerHTML = "\n<div class=\"dropdown dropdown-inline\"> <button type=\"button\" class=\"btn btn-icon btn-xs\" data-toggle=\"dropdown\" aria-haspopup=\"true\" aria-expanded=\"false\"> <i class=\"fas fa-ellipsis-h\"></i> </button> <div class=\"dropdown-menu dropdown-menu-right\"></div>\n</div>\n";

                        let renameBtn = document.createElement('button')
                        renameBtn.classList = 'dropdown-item navi-link disabled'
                        renameBtn.type = 'button'
                        renameBtn.innerText = Drupal.t('Rename', {}, {context: "gofast:gofast_kanban"})
                        
                        if( kanban.options.canEdit){
                            
                            renameBtn.classList = 'dropdown-item navi-link'
                            renameBtn.onclick = function (e) {
                                e.preventDefault()
                                _displayBoardHeaderForm(header, true)
                            }
                        }

                        let divider = document.createElement('div')
                        divider.classList = 'dropdown-divider'

                        let deleteBtn = document.createElement('button')
                        deleteBtn.classList = 'dropdown-item navi-link disabled'
                        deleteBtn.type = 'button'
                        deleteBtn.innerText = Drupal.t('Delete', {}, {context: "gofast:gofast_kanban"})
                        
                        if( kanban.options.canEdit){
                            deleteBtn.classList = 'dropdown-item navi-link'
                            deleteBtn.onclick = function (e) {
                                e.preventDefault()
                                _displayBoardDeleteModal(board_id);
                            }
                        }
                        settings.querySelector('.dropdown-menu').appendChild(renameBtn)
                        settings.querySelector('.dropdown-menu').appendChild(divider);
                        settings.querySelector('.dropdown-menu').appendChild(deleteBtn)


                        let editBoardForm = document.createElement('form')
                        // rename logic
                        if( kanban.options.canEdit){
                          //  let editBoardForm = document.createElement('form')

                            editBoardForm.innerHTML = "\n<div class=\"input-icon input-icon-right\"> <input type=\"text\" class=\"form-control\" name=\"title\" value=\"" + (title ? title.innerText : "") + "\" placeholder=\"Search...\"> <span> <button class=\"btn btn-icon\" type=\"submit\"><i class=\"fas fa-check text-success\"></i></button> <button class=\"btn btn-icon\" type=\"reset\"><i class=\"fas fa-times text-danger\"></i></button> </span>\n</div>\n";

                            editBoardForm.className = 'w-100 fade d-none'

                            editBoardForm.onsubmit = function (e) {
                                e.preventDefault()
                                const formData = e.target['title'].value;
                                _handleBoardRenameSubmit(board_id, header, formData)

                            }

                            editBoardForm.onreset = function (e) {
                                e.preventDefault()
                                _displayBoardHeaderForm(header, false)
                            }
                        }

                        button.className = 'gofastKanban__addBoard btn btn-icon btn-xs disabled'
                        button.setAttribute('aria-disabled' , true);
                        button.innerHTML = '<i class="fas fa-plus"></i>' 
                        
                        if(kanban.options.canAddCard){
                            button.className = 'gofastKanban__addBoard btn btn-icon btn-xs'
                            button.removeAttribute('aria-disabled' , true);
                            button.onclick = function (e) {
                                // create a form to enter element
                                let formItem = document.createElement('form')
                                formItem.className = 'fadein'
                                formItem.innerHTML = "\n<div class=\"input-icon input-icon-right\"> <input type=\"text\" class=\"form-control form-control-sm\" name=\"taskname\" placeholder=\"" + Drupal.t("New task name", {}, { context: "gofast_kanban" }) + "\"> <span> <button class=\"btn btn-icon\" type=\"submit\"><i class=\"fas fa-check text-success\"></i></button> <button class=\"btn btn-icon\" type=\"reset\"><i class=\"fas fa-times text-danger\"></i></button> </span>\n</div>\n";
                                kanban.addForm(board_id, formItem);

                                formItem['taskname'].focus()

                                formItem.onsubmit = function (e) {
                                    e.preventDefault();
                                    var taskname = e.target[0].value;
                                    _handleAddNewTask(board_id, taskname)
                                    formItem.parentNode.removeChild(formItem);
                                }

                                formItem.onreset = function () {
                                    formItem.parentNode.removeChild(formItem);
                                };
                            }
                        }
                        
                        div.appendChild(button)
                        div.appendChild(settings)
                        div.className = 'kanban-title-tools'
                        div.style = 'display: flex;'
                        header.appendChild(editBoardForm)
                        header.appendChild(div)
                        header.classList.add('d-flex', 'justify-content-between')
                    }
                })
            }
        }

        var _displayTaskFiltred = function (tasks) {
            if (tasks) {
                kanbanContainer.querySelectorAll('.gofastKanban__item').forEach(el => {
                    let idtask = parseInt(el.dataset.eid)
                    if (tasks.includes(idtask)) {
                        el.classList.remove('hidden')
                    } else {
                        el.classList.add('hidden')

                    }
                })
            } else {
                kanbanContainer.querySelectorAll('.gofastKanban__item').forEach(el => {
                    el.classList.add('hidden')
                })
            }
        }

        var _displayAllTask = function () {
            kanbanContainer.querySelectorAll('.gofastKanban__item').forEach(el => {
                el.classList.remove('hidden')
            })
        }


        /*
         *   POPOVER
         */

        var _setAllPopovers = function () {

            let popupItems = kanbanContainer.querySelectorAll('[data-toggle="popover"]')

            if (popupItems && popupItems.length > 0) {
                popupItems.forEach(item => {
                    item.onclick = (e) => {
                        e.stopPropagation()
                    }
                    $(item).popover({
                        template: "\n<div class=\"popover GofastKanbanPopover\" role=\"tooltip\"> <div class=\"arrow\"></div> <div class=\"popover-body\"></div>\n</div>\n"
                    })
                })
            }
        }

        var _deleteAllPopovers = function () {

            let popupItems = kanbanContainer.querySelectorAll('[data-toggle="popover"]')

            if (popupItems && popupItems.length > 0) {
                popupItems.forEach(item => {
                    $(item).popover('dispose')
                })
            }
        }


        /*
         *   SCROLL
         */

        var _setPsBoardContainer = function () {
            // if(kanbanContainer) {
            //     _psBoardsContainer = new PerfectScrollbar(kanbanContainer, {
            //         wheelSpeed: 2,
            //         wheelPropagation: false,
            //         minScrollbarLength: 20,
            //         suppressScrollY: true
            //     })
            // }
        }

        var _scrollBoardContainerToEnd = function () {
            let scroll = kanbanContainer.scrollWidth - kanbanContainer.offsetWidth
            if (scroll > 0) {
                kanbanContainer.scrollLeft = scroll
            }
        }

        var _deletePsBoardContainer = function () {
            if (_psBoardsContainer) {
                _psBoardsContainer.destroy()
                _psBoardsContainer = null
            }
        }

        var _setAllPsBoards = function () {
            let boards = document.querySelectorAll('.kanban-drag')
            if (boards.length > 0) {
                boards.forEach(board => {
                    let ps = new PerfectScrollbar(board, {
                        wheelSpeed: 2,
                        wheelPropagation: false,
                        minScrollbarLength: 20
                    })
                    _psBoards.push(ps)
                    board.classList.add('scroll', 'scroll-pull')
                })
            }
        }

        var _deleteAllPsBoards = function () {
            if (_psBoards.length > 0) {
                _psBoards.forEach(ps => {
                    ps.destroy();
                    ps = null; // to make sure garbages are collected
                })
                _psBoards = []
            }
        }



        /*
         *   EVENTS
         */

        var _handleDropTask = async function (el, target, source, sibling) {

            const targetId = target.parentNode.dataset.id
            const sourceId = source.parentNode.dataset.id
            const taskId = el.dataset.eid
            let siblingIndex = null
            let url = null


            try {

                if (!taskId) {
                    throw Error('Task id not finded');
                }

                if (sibling) {
                    siblingIndex = sibling.dataset.index;
                } else {
                    siblingIndex = kanban.getBoardElements(targetId).length;
                }
                
                if (targetId !== sourceId) {

                    url = new URL(window.origin + '/kanban/task/' + taskId + '/update_column/' + targetId)
                    url.search = new URLSearchParams({
                        index: siblingIndex
                    })


                } else {
                    //TODO: Save new index for task
                    url = new URL(window.origin + '/kanban/task/' + taskId + '/update_priority/' + siblingIndex)

                }

                if (url) {
                    
                    window.ktKanbanItem._selfUpdate = true;
                    const res = await fetch(url);
                    if (res.status != 200) {
                        throw Error('Error status: ' + res.status)
                    }
                    _updateAllTaskIndex();
                } else { throw Error('Url no valid')}

            } catch (error) {
                console.log(error);
                _reloadKanban();
            }
        }

        var _handleDropBoard = async function (el) {
            try {
                const boardId = el.dataset.id
                const order = el.dataset.order
                let url = new URL(window.origin + '/kanban/' + kanbanId + '/column/' + boardId + '/move/' + order)

                const res = await fetch(url)

                if (res.status != 200) {
                    throw Error('Error status: ' + res.status)
                }

            } catch (error) {
                console.log(error)
                _reloadKanban()
            }
        }

        var _handleAddNewTask = async function (boardId, taskname) {

            Gofast.addLoading()

            try {
                let formData = new FormData()
                formData.append('title', taskname)

                let url = window.origin + '/kanban/' + kanbanId + '/column/' + boardId + '/add/task';

                const res = await fetch(url, {
                    method: 'POST',
                    body: formData
                })

                const data = await res.json()

                if(!data.nid) throw new Error('')

                let newTask = {
                    title: taskname,
                    nid: data.nid,
                    created_date: new Date(data.date_created),
                    board_id: boardId
                }

                newTask.__proto__ = _kanbanElement

                kanban.addElement(boardId, {
                    id: newTask.nid,
                    title: newTask.element(),
                    class: ["p-0", "gofastKanban__item"]
                })

            } catch (error) {
                console.log(error.message)

            }

            Gofast.removeLoading()

        }

        var _handleBoardRenameSubmit = async function (boardId, header, title) {

            try {

                let formData = new FormData()
                formData.append('label', title)

                let url = window.origin + '/kanban/' + kanbanId + '/column/' + boardId + '/update';

                const res = await fetch(url, {
                    method: 'POST',
                    body: formData
                })

                const data = await res.json()
                // default columns are replaced by new ones to avoid modifying their taxonomy names, so we need to keep track
                if (data.newColumnId) {
                    const originalBoard = document.querySelector(".kanban-board[data-id='" + boardId + "']");
                    originalBoard.dataset.id = data.newColumnId;
                } 
            } catch (error) {
                console.log(error)
            }

            if (header.querySelector('.kanban-title-board')) {
            header.querySelector('.kanban-title-board').innerText = title
            }
            _displayBoardHeaderForm(header, false)
        }

        var _handleAddBoardOnSubmit = async function (form) {
            // TODO: Handle loading

            try {
                let newBoardTitle = form['title'].value

                if (newBoardTitle.length > 0) {

                    let formData = new FormData()
                    formData.append('label', newBoardTitle)

                    // Handle submit fetch call
                    let url = window.origin + '/kanban/' + kanbanId + '/add/column';
                    const res = await fetch(url, {
                        method: 'POST',
                        body: formData
                    })
                    const data = await res.json()

                    // Handle response to match with kanban params
                    let formattedData = {
                        title: data.label,
                        id: data.id
                    }
                    // Add board to kanban.. have to be an array
                    kanban.addBoards([formattedData])
                    // Set custom header to new board
                    _setCustomHeadersBoards([formattedData])
                    // Scroll to end
                    _scrollBoardContainerToEnd()
                    // Reset form
                    form.reset()
                    
                    
                    Gofast.toast(Drupal.t('New column "@column" added to Kanban', {'@column': newBoardTitle}, { 'context': 'gofast' }), 'info');

                } else {
                    throw new Error('Invalid empty value')
                }

            } catch (error) {
                if (form.querySelector('.newColumn__message')) {
                form.querySelector('.newColumn__message').innerText = error.message
                setTimeout(function () {
                    form.querySelector('.newColumn__message').innerText = ''
                }, 3000)
                }
            }
        }

        var _handleSearhChange = async function (value) {

            if (!!value && value.length > 2) {
                try {

                    let formData = new FormData()
                    formData.append('filter', value)

                    let url = window.origin + '/kanban/' + kanbanId + '/search';
                    const res = await fetch(url, {
                        method: 'POST',
                        body: formData
                    })
                    const data = await res.json()

                    _displayTaskFiltred(await data)


                } catch (error) {
                    console.log(error)
                }

            } else {
                _displayAllTask()

            }
            _setLoadingState(false)


        }


        var _handleBoardDelete = async function (boardId) {

            try {

                _displayBoardDeleteModal();

                let url = window.origin + '/kanban/' + kanbanId + '/column/' + boardId + '/delete';

                const res = await fetch(url, {
                    method: 'POST'
                })
                
                _reloadKanban();
                $(_modal).modal('hide');
                Gofast.toast(Drupal.t('Column has been deleted ', {}, { 'context': 'gofast_kanban' }), 'info');

            } catch (error) {
                console.log(error)
            }
             
        }

        /*
         *   MODAL
         */

        var _displayBoardDeleteModal = async function (el) {

           // Gofast.addLoading()
            let title = Drupal.t('Delete the column', {}, {context: "gofast:gofast_kanban"});
            let boardId = el;
            
            if (_modalTitle) {
                _modalTitle.innerText = title
            }
            if (_modalContent) {
            _modalContent.innerHTML = _getBoardDeleteContent()
            }
            
            let submitBtn = document.createElement('button');
            submitBtn.type = 'button'
            submitBtn.classList = "btn btn-sm btn-danger"
            submitBtn.innerText = Drupal.t('Delete', {}, {'context': 'gofast_kanban'})
            submitBtn.onclick = function (e) {
                e.preventDefault()
                submitBtn.setAttribute("disabled", "true");
                _handleBoardDelete(boardId)
                _modalFooter.innerHTML = '';
                
            }
            _modalFooter.appendChild(submitBtn);

            try {
                $(_modal).modal('show')

            } catch (error) {

                console.log(error.message)
            }

            Gofast.removeLoading()
        }

        var _displayTaskViewModal = async function (el) {

            Gofast.addLoading()
            if (_modalContent) {
            _modalContent.innerHTML = _getTaskModelContent()
            }
            if (_modalTitle) {
            _modalTitle.innerText = Drupal.t('Card detail', {}, {context: "gofast:gofast_kanban"});
            }
            // _modalFooter.classList = 'd-none modal-footer'

            try {

                const tid = el.dataset.eid
                const resp = await fetch(window.origin + '/kanban/task/' + tid + '/get')
                const data = await resp.json()

                let cardEl = document.querySelector('.gofastKanbanCardDetail')
                _cardDetail = window.GofastKanbanCardDetail()
                _cardDetail.init(cardEl, data, _reloadKanban);
                
                
                let closeBtn = document.createElement('button');
                closeBtn.type = 'button';
                closeBtn.innerText = Drupal.t('Close', {}, {'context': 'gofast_kanban'});
                closeBtn.classList = "btn btn-sm btn-bg-secondary";
                closeBtn.setAttribute("data-dismiss", "modal");
                
                let deleteBtn = document.createElement('button');
                deleteBtn.type = 'button'
                deleteBtn.innerText = Drupal.t('Delete this card', {}, {'context': 'gofast_kanban'})
                deleteBtn.classList = "btn btn-sm btn-bg-secondary disabled"
                
                if(data.canDelete == true){
                    deleteBtn.classList = "btn btn-sm btn-danger" 
                    deleteBtn.onclick = function (e) {
                        e.preventDefault()           
                        _cardDetail.delete(cardEl, function(e){    
                            _modalFooter.innerHTML = '';
                        })
                    }
                }
                _modalFooter.appendChild(closeBtn);
                _modalFooter.appendChild(deleteBtn);
                
                $(_modal).modal('show')

            } catch (error) {

                console.log(error.message)
            }

            let title = Drupal.t('Card details', {}, {context: "gofast:gofast_kanban"});

            Gofast.removeLoading()
        }

        var _getTaskModelContent = function () {

            return '\n<div class="gofastKanbanCardDetail pt-1 pb-8 px-8"> <div class ="row"> <div class="col-lg-8 KanbanCard_leftCol"> <div class="row mb-8"> <div class="col-lg-12"> <div class="KanbanCard__title Detail__container"> <div class="KanbanCard__InputEditable EditableInput"></div> </div> </div> </div> <div class="row mb-8"> <div class="col-lg-4"> <div class="KanbanCard__created Detail__container inline-label"> <span class="font-weight-bolder">' +
            window.parent.Drupal.t("Created", {}, { context: "gofast_kanban" }) +
            ':</span> <div class="KanbanCard__InputEditable EditableInput"></div> </div> </div> <div class="col-lg-4"> <div class="KanbanCard__deadline Detail__container inline-label"> <span class="font-weight-bolder">' +
            window.parent.Drupal.t("Deadline", {}, { context: "gofast_kanban" }) +
            ':</span> <div class="KanbanCard__InputEditable EditableInput"></div> </div> </div> <div class="col-lg-4"> <div class="KanbanCard__state Detail__container inline-label"> <span class="font-weight-bolder">' +
            window.parent.Drupal.t("Status", {}, { context: "gofast_kanban" }) +
            ':</span> <div class="KanbanCard__InputEditable EditableInput"></div> </div> </div> </div> <div class="row mb-8 justify-content-between"> <div class="col-lg-6"> <div class="KanbanCard__responsable Detail__container"> <label class="font-weight-bolder">' +
            window.parent.Drupal.t("Responsible", {}, { context: "gofast_kanban" }) +
            ':</label> <div class="KanbanCard__InputEditable EditableInput"></div> </div> </div> <div class="col-lg-6"> <div class="KanbanCard__members Detail__container"> <label class="font-weight-bolder">' +
            window.parent.Drupal.t("Members", {}, { context: "gofast_kanban" }) +
            ':</label> <div class="KanbanCard__InputEditable EditableInput"></div> </div> </div> </div> <div class="separator separator-solid my-3"></div> <div class="row"> <div class="col-lg-12"> <div class="KanbanCard__description Detail__container"> <label class="font-weight-bolder">' +
            window.parent.Drupal.t("Description", {}, { context: "gofast_kanban" }) +
            ':</label> <div class="KanbanCard__InputEditable EditableInput"></div> </div> </div> </div> <div class="separator separator-solid my-3"></div> <div class="row"> <div class="col-lg-12"> <div class="KanbanCard__documents Detail__container"> <label class="font-weight-bolder">' +
            window.parent.Drupal.t("Documents", {}, { context: "gofast_kanban" }) +
            ':</label> <div class="KanbanCard__InputEditable EditableInput"></div> </div> </div> </div> <div class="separator separator-solid my-3"></div> <div class="row"> <div class="col-lg-12"> <div class="KanbanCard__todolist  Detail__container "> <label class="font-weight-bolder">' +
            window.parent.Drupal.t("Tasks List", {}, { context: "gofast_kanban" }) +
            ':</label> <div class="GofastTodoList"></div> </div> </div> </div> </div> <div class="col-lg-4 KanbanCard_rightCol"> <div class="row"> <div class="col-lg-12"> <div class="KanbanCard__timeline Detail__container"> <div class="GofastKanbanTimeLine"></div> </div> </div> </div> </div> </div>\n</div>\n';          
        }


        _getBoardDeleteContent = function () {

            let html_content = document.createElement('div');

            html_content.innerHTML = '<h4>'+Drupal.t("Are you sure you want to delete this column ?", {}, {'context': 'gofast_kanban'})+'</h4>'
                                     +'<br/>'  
                                     +'<i class="fa fa-exclamation-triangle" style="color:red;"></i>'
                                     + Drupal.t("Please note that ALL the card(s) it contains will be deleted as well.", {}, {'context': 'gofast_kanban'})
                                     +'';
                                        
            return  html_content.innerHTML;
        }


        /*
         *   DEVELOPMENT FUNCTION
         */


        var _getKanban = function () {
            return kanban
        }

        var _getKanbanData = async function () {

            let kanbanData = await fetch('/data/kanbanData.json')
                    .then(res => res.json())
                    .then(data => data)

            return kanbanData;
        }
        
        var _openCard = function(cardId){            
            var cardEl = component.querySelector(".kanban-item[data-eid='"+cardId+"']");
            if(cardEl){
                cardEl.click();
            }
        }


        /*
         *   PUBLIC FUNCTION
         */

        return {
            init() {
                _initKanban();
            },
            deleteAll() {
                _deleteAllKanbanBoards()
            },
            reload() {
                _reloadKanban()
            },
            kanban() {
                return _getKanban()
            },
            getData() {
                return _getKanbanData()
            },
            loading(isloading) {
                _setLoadingState(isloading)
            },
            hideCardModal(){
                return  $(_modal).modal('hide');
            }
        };
    }();

    Drupal.behaviors.gofastKanban = {
        attach: function (context, settings) {
            
            let gofastKanban = document.querySelector('#gofastKanban')
            if (gofastKanban) {
                
                var location = window.location.pathname;
                var hash = window.location.hash;

                //For "Essential" version:
                if(location == '/tasks_page_navigation/' && hash == '#navKanban'){

                  //remove modal backdrop
                  jQuery('.modal-backdrop.fade').remove();
                  jQuery('#navigation_kanban').click(); 
                }
                

                if (!gofastKanban.classList.contains('processed')) {
                    console.log('gofastKanban loading....')
                    gofastKanban.classList.add('processed')
                    window.ktKanbanItem = KTKanbanBoard ;
                    window.ktKanbanItem.init();                    
                }
            }

        }
    };
    
    Gofast.reInitKanban = function(kid){
        gofastKanban = document.querySelector('#gofastKanban');
        gofastKanban.dataset.kid = kid;
        if(window.ktKanbanItem){
            window.ktKanbanItem.deleteAll();
            window.ktKanbanItem = KTKanbanBoard;
            window.ktKanbanItem.init();
        }
    };
    
    Gofast.reloadKanbanFromPolling = function() {
        if( ! window.ktKanbanItem._selfUpdate){
        window.ktKanbanItem.reload();
        }else{
            window.ktKanbanItem._selfUpdate = false;
        }
    };

})(jQuery, Drupal, Gofast);
