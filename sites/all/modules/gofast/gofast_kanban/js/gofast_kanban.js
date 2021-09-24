class KanbanBoard {

    constructor() {
        this.todos = [];
        this.init();
        this.debug= true;
    }

    init() {
        //event handlers;
        this.handleKanbanModalContent();
        this.debug = true;
        this.sortColumns;

        var card_id = $('div.board').data('cardToDisplay');
        setTimeout(KanbanBoard.openCard(card_id), 5000);

        changeClassContainer();

    }


    /*********************************************************
     * Part in common
     */

    static disableLogger(){
        this.debug = false;
    }

    static enableLogger(){
        this.debug = true;
    }

    static log(message){
        if(this.debug === true){
            console.log(message);
        }
    }

    static ensureOneFieldEditionAtTime(elt) {
        $(elt).parents('div.modal-body:first').find('.gf-kanban-editing').hide();
        $(elt).parents('div.modal-body:first').find('.gf-kanban-not-editing').show();
    }

    /**
     * Clear field date (flatpickr)
     * @param {type} elt
     * @returns {undefined}
     */
    static clearDate(elt) {
        $(elt).parents('div.gf-kanban-field-edit:first').find('input[data-toggle="flatpickr"]').flatpickr().clear();
    }



    static search(elt){
        KanbanBoard.log('search');

        if($(elt).attr('id') == 'gf_kanban_search_clear'){
            filter = '';
        }else{
            var filter = $(elt).val().trim();
        }


        //do not search for less than 3 chars filter
        if(filter.length < 3 && filter.length > 0){
            return;
        }

        var kanbanId = $(elt).data('kanbannid');
        var url= '/kanban/'+kanbanId;

        $.ajax({
            'type': "POST",
            'url': url,
            'data': {
                'filter' : filter
            },
            'success': function (data) {

                var parser = new DOMParser();
                var el = parser.parseFromString(data, "text/html");
                var kanbanBoard = $(el).find('div#board').html();

                $(document).find('div#board').html(kanbanBoard);


            }
        });
    }

    static refreshSortable(){

        //refresh sortables
        var updatedKanban = $(document).find('div#board');

        KanbanBoard.log(updatedKanban);
        KanbanBoard.log(updatedKanban.data('userRole'));

        if(updatedKanban.data('userRole') === 'administrator member'){
            //data-draggable=".tasks" data-handle=".task-header" data-delay="100" data-on-end="KanbanBoard.moveColumn" data-force-fallback="true"
            KanbanBoard.sortColumns = Sortable.create(updatedKanban[0], {
                handle: ".task-header",
                draggable: ".tasks",
                delay: 50,
                onEnd: function (evt) {
                    KanbanBoard.moveColumn(evt);
                },
                forceFallback : true
            });
        }
        //  else if (updatedKanban.data('userRole') !== 'read only member'){
        //    Sortable.create(updatedKanban[0], {
        //      handle: ".task-header",
        //      draggable: ".tasks",
        //      delay: 100,
        //      onEnd: function (evt) {
        //        KanbanBoard.moveColumn(evt);
        //      },
        //      forceFallback : true
        //    });
        //  }

        KanbanBoard.refreshSortableTasks();

    }

    static refreshSortableTasks() {
        var updatedKanban = $(document).find('div#board');
         if(updatedKanban.data('userRole') !== 'read only member'){

            //data-toggle="sortable" data-group="tasks" data-delay="50" data-force-fallback="true" data-on-end="KanbanBoard.updateTaskColumn"
            var tasks = $(document).find('.task-body');

            $.each(tasks, function(key, elt){
                Sortable.create(elt, {
                    group: '.tasks',
                    onEnd: function (evt) {
                        KanbanBoard.updateTaskColumn(evt);
                    },
                    forceFallback : true,
                    fallbackTolerance: 10
                });
            });
        }
    }


    static manageFormAutoSubmit(){

        //Prevent auto submit when the user press "Enter"
        $('form.gf-kanban-column-edit-label').keydown(function(event) {
            var key = event.which;
            if(key == 13){
                event.preventDefault();
                // KanbanBoard.updateColumn($(this).find('.btn.update-column'));
                return false;
            }
        });

        $('input.gf-kanban-new-column-name').keydown(function(event) {
            var key = event.which;
            if(key == 13){
                event.preventDefault();
                //KanbanBoard.addColumn($(this).parents('.tasks-action').find('.btn.btn-primary'));
                return false;
            }
        });
    }

    static manageFormAutoSubmitTask(){

        //Prevent auto submit when the user press "Enter"
        $('form[id^="gf-kanban-task-edit"]').keydown(function(event) {
            var key = event.which;
            if(key == 13){
                event.preventDefault();
                return false;
            }
        });

        $('form#gofast-kanban-checklistitem-form').keydown(function(event) {
            var key = event.which;
            if(key == 13){
                event.preventDefault();
                return false;
            }
        });

        $('form#gofast-kanban-checklistitem-form').find('input[name=label]').keydown(function(event) {
            var key = event.which;
            if(key == 13){
                event.preventDefault();
                return false;
            }
        });

    }


    static showActivityDetails(){

        KanbanBoard.log('showActivityDetails');

        if($('#gf_task_display_details').data('hide') === 1){

            $('ul.timeline').find('.gf-timeline-other').each(function(key, elt){
                $(elt).css('display', 'flex');
            });
            $('#gf_task_display_details').html(window.parent.Drupal.t("Hide details", {}, {'context' : 'gofast_kanban'}));
            $('#gf_task_display_details').data('hide', 0);
        }else{
            $('ul.timeline').find('.gf-timeline-other').each(function(key, elt){
                $(elt).css('display', 'none');
            });
            $('#gf_task_display_details').html(window.parent.Drupal.t("Display details", {}, {'context' : 'gofast_kanban'}));
            $('#gf_task_display_details').data('hide', 1);
        }
    }


    /**
     * Reload task activities part
     * @param {type} taskId
     * @param {type} callback
     * @returns {undefined}
     */
    static reloadTaskDetails(taskId, callback) {

        var showAuditDetails = false;
        if($('#gf_task_display_details').data('hide') === 0){
            showAuditDetails = true;
        }

        $.ajax({
            'type': "GET",
            'url': '/modal/ajax/task/' + taskId + '/view',
            'success': function (data) {
                if (undefined !== callback && typeof callback === 'function') {
                    callback(data);

                    if(showAuditDetails === true){
                        KanbanBoard.showActivityDetails();
                    }
                }
                KanbanBoard.manageFormAutoSubmitTask();
            }
        });
    }

    /**
     * Reload kanban Board
     * @param {type} kanbanId
     * @param {type} callback
     * @param {type} needRefreshSortable
     * @returns {undefined}
     */
    static reloadKanban(kanbanId, needRefreshSortable, callback){

        var filter = $('#gf_kanban_search').val().trim();

        $.ajax({
            'type': "POST",
            'url': '/kanban/'+kanbanId,
            'data': {
                'filter' : filter
            },
            'success': function (data) {
                if (undefined !== callback && typeof callback === 'function') {
                    callback(data);
                    if(needRefreshSortable) {
                        KanbanBoard.refreshSortable();
                    }
                    else
                    {
                        KanbanBoard.refreshSortableTasks();
                    }
                    KanbanBoard.manageFormAutoSubmit();
                    $('#gf_kanban_search').val(filter);

                }
            }
        });
    }

    sortingElems(elems) {
        return elems.sort((a, b) => {
            return $(a)
                    .data('sort')
                    .toUpperCase()
                    .localeCompare($(b).data('sort').toUpperCase());
        });
    }


    closeKanbanModal(){

        var elt =  $('#kanbanModal');
        $(elt).find('.gf-kanban-editing').hide();
        $(elt).find('.gf-kanban-not-editing').show();

        KanbanBoard.hideBtnActionMessage();

        $('button.gf-card-modal-dismiss').click();
        $('#kanbanModal').removeClass('in');
    }

    static hideBtnActionMessage(){
        $('#kanbanModal').find('.gf-btn-action-message').hide();
        $('#kanbanModal').find('.gf-btn-action').show();
    }


    handleKanbanModalContent() {

        $('#kanbanModal').on('show.bs.modal', function (e) {

            const button = $(e.relatedTarget);
            const title = Drupal.t('Card details', {}, {context: "gofast:gofast_kanban"}); //button.attr('title');
            const recipient = button.data('content-layer');
            const action = button.data('action');
            const canDelete = button.data('can-delete');
            var eltId = 'new';
            var eltDataType = 'none';

            if( 'undefined' !== button.data('eltid')){
                eltId = button.data('eltid');
            }

            if( 'undefined' !== button.data('elttype')){
                eltDataType = button.data('elttype');
            }

            var kanbanModal = this;

            $(kanbanModal).addClass('in');
            $(kanbanModal).find('.modal-title').text(window.parent.Drupal.t(title, {}, {'context' : 'gofast_kanban'}));
            var targetUrl = ('undefined' != typeof button.data('url')) ? button.data('url') : button.attr('href');
            $.ajax({
                'url': targetUrl,
                beforeSend: function () {
                    $(kanbanModal).find('.modal-body').html('Loading ... ');
                },
                success: function (data, status) {
                    $(kanbanModal).find('.modal-body').html(data);
                    $(kanbanModal).find('div.modal-footer > .modal-contextual-actions').html(''); // empty contextual actions

                    if(action === 'edit' && canDelete === true ){
                        if(eltDataType === 'task'){
                            $(kanbanModal).find('div.modal-footer > .gf-btn-action > .modal-contextual-actions').html('<button type="button" class="btn btn-danger" data-taskId="'+eltId+'" onclick="KanbanBoard.preDeleteTask('+eltId+');"><i class="fa fa-trash"></i>&nbsp;'+window.parent.Drupal.t('Delete', {}, {'context' : 'gofast_kanban'}) +'</button>');
                        }
                    }

                    //instanciate ckeditor on card description
                    CKEDITOR.config.plugins = "dialogui,dialog,about,a11yhelp,dialogadvtab,basicstyles,bidi,blockquote,notification,button,toolbar,clipboard,panelbutton,panel,floatpanel,colorbutton,colordialog,templates,menu,contextmenu,copyformatting,div,resize,elementspath,enterkey,entities,popup,filetools,filebrowser,find,fakeobjects,flash,floatingspace,listblock,richcombo,font,forms,format,horizontalrule,htmlwriter,iframe,wysiwygarea,image,indent,indentblock,indentlist,smiley,justify,menubutton,language,link,list,liststyle,magicline,maximize,newpage,pagebreak,pastetext,pastefromword,preview,print,removeformat,save,selectall,showblocks,showborders,sourcearea,specialchar,scayt,tab,table,tabletools,tableselection,undo,lineutils,widgetselection,widget,notificationaggregator,uploadwidget,uploadimage";
                    CKEDITOR.config.toolbar = eval(cke_settings_blog.settings.toolbar);
                    Drupal.gofast_kanban_editor = CKEDITOR.replace("task-description");

                    //Manage comment form resize when it loose its focus
                    $('#kanbanModal').find('div.gf-card-comment-body-form').on('focusout', function(){
                        $(this).find('textarea').css('height', '2.25rem');
                    });

                    $('#kanbanModal').find('div.gf-card-comment-body-form').on('focusin', function(){
                        $(this).find('textarea').css('height', 'auto');
                    });

                    // control if there is field in edit mode before closing modal
                    $('.gf-card-modal-pre-dismiss').on('click', function(e){

                        if ($('div.modal-body:first').find('.gf-kanban-editing:visible').length > 0) {

                            $('#kanbanModal').find('.gf-btn-action').hide();
                            $('#kanbanModal').find('.gf-btn-action-message').show();

                        }else{
                            $('button.gf-card-modal-dismiss').click();
                            $('#kanbanModal').removeClass('in');

                        }
                    });

                    KanbanBoard.manageFormAutoSubmitTask();
                }

            });

        });

        $('#kanbanModal').on('hidden.bs.modal', function (e) {

            var kanbanId = $('div#board').data('kanbanid');

            KanbanBoard.reloadKanban(kanbanId, true, function (data) {

                var parser = new DOMParser();
                var el = parser.parseFromString(data, "text/html");

                //Watch out : get relaoding full #board parent's is necessary not to break sortable columns !!
                var kanbanBoard = $(el).find('div#board').parent().html();
                $(document).find('div#board').parent().html(kanbanBoard);
            });

        });

    }

    /*********************************************************
     * Kanban Part
     */

    /**
     *
     * @param {type} elt
     * @returns {undefined}
     */
    static editColumn(elt){
        KanbanBoard.log('editColumn');

        //show form and hide display
        $(elt).parents('.task-header:first').find('.gf-kanban-not-editing').hide();
        $(elt).parents('.task-header:first').find('.gf-kanban-editing').show();

        $(elt).parents('.task-header:first').find('input[name=label]').focus();
        
        //disable sortable widget on click
       KanbanBoard.sortColumns.options.disabled = true;
    }

    static cancelEditColumn(elt){
        KanbanBoard.log('cancelEditColumn');

        //show form and hide display

        $(elt).parents('.task-header:first').find('.gf-kanban-editing').hide();
        $(elt).parents('.task-header:first').find('.gf-kanban-not-editing').show();
        
        //re-enable sortable widget 
        KanbanBoard.sortColumns.options.disabled = false;

    }
    /**
     *
     * @param {type} elt
     * @returns {undefined}
     */
    static updateColumn(elt){
        KanbanBoard.log('updateColumn');

        var form = $(elt).parents('form:first');

        var kanbanId = $(form).data('kanbannid');

        var url= $(form).attr('action');

        $.ajax({
            'type': "POST",
            'url': url,
            'data': $(form).serialize(),
            'success': function (data) {
                KanbanBoard.reloadKanban(kanbanId, false, function (data) {

                    var parser = new DOMParser();
                    var el = parser.parseFromString(data, "text/html");
                    var kanbanBoard = $(el).find('div#board').html();

                    $(document).find('div#board').html(kanbanBoard);
                });
            }
        });

    }

    /**
     *
     * @param {type} columnId
     * @param {type} kanbanId
     * @returns {undefined}
     */
    static preDeleteColumn(columnId, kanbanId){
        KanbanBoard.log('preDeleteColumn');

        var sentence_confirmation = parent.Drupal.t("Are you sure you want to delete this column and the card(s) it contains?", {}, {'context': 'gofast_kanban'});
        var html_content = sentence_confirmation + '<br /><br />'
                + '<input class="btn btn-sm btn-success" type="button" onClick="window.document.getElementById(\'gf_kanban\').contentWindow.kanbanBoard.deleteColumn(' + columnId + ', '+kanbanId+');" \n\ '
                + ' value="' + window.parent.Drupal.t('Validate', {}, {'context': 'gofast_kanban'}) + '" />';

        window.parent.Gofast.modal(html_content, window.parent.Drupal.t("Delete the column", {}, {'context': 'gofast_kanban'}));
    }

    /**
     *
     * @param {type} columnId
     * @param {type} kanbanId
     * @returns {undefined}
     */
    deleteColumn(columnId, kanbanId){
        KanbanBoard.log('deleteColumn');

        var url = '/kanban/'+kanbanId+'/column/'+columnId+'/delete';

        $.ajax({
            'type': "POST",
            'url': url,
            'success': function (data) {

                KanbanBoard.reloadKanban(kanbanId, false, function (data) {

                    var parser = new DOMParser();
                    var el = parser.parseFromString(data, "text/html");
                    var kanbanBoard = $(el).find('div#board').html();

                    $(document).find('div#board').html(kanbanBoard);

                    //close confirmation modal
                    window.parent.Drupal.CTools.Modal.dismiss();
                });
            }
        });
    }

    /**
     *
     * @param {type} elt
     * @returns {Boolean}
     */
    static addColumn(elt){
        KanbanBoard.log('addColumn');

        //Avoid adding empty comment
        var newColumnName = $(elt).parents('div.tasks-action:first').find('input.gf-kanban-new-column-name');
        if(newColumnName.val().trim().length == 0){
            return false;
        }
        var kanbanId = $(elt).data('kanbannid');
        var url = '/kanban/'+kanbanId+'/add/column';

        $.ajax({
            'type': "POST",
            'url': url,
            'data': {
                'name' : newColumnName.val()
            },
            'success': function (data) {

                $(newColumnName).val('');

                KanbanBoard.reloadKanban(kanbanId, false, function (data) {

                    var parser = new DOMParser();
                    var el = parser.parseFromString(data, "text/html");
                    var kanbanBoard = $(el).find('div#board').html();

                    $(document).find('div#board').html(kanbanBoard);
                });
            }
        });
    }

    /**
     *
     * @param {type} evt
     * @returns {undefined}
     */
    static moveColumn(evt){

        KanbanBoard.log('moveColumn');

        var columnId = $(evt.item).data('tid');
        var kanbanId = $(evt.item).data('kanbannid');
        var old_position = evt.oldIndex;
        var new_position = evt.newIndex;


        if (new_position !== old_position) { // avoid unecessary query
            $.ajax({
                'type' : 'POST',
                'url': '/kanban/'+kanbanId+'/column/'+columnId+'/move/'+new_position,
                'data': {
                    'old_index': old_position
                }
            });
        }

    }



    /***********************************************************
     * Task part
     */

    /**
     * Update
     * @param {type} evt
     * @returns {undefined}
     */
    static updateTaskColumn(evt) {
        KanbanBoard.log('updateTaskColumn/Priority');

        var old_column = $(evt.from).data('columnid');
        var new_column = $(evt.to).data('columnid');
        var task_nid = $(evt.item).data('nid');
        var kanbanId = $(evt.item).data('kanbannid');

        KanbanBoard.log(evt);

        if (new_column !== old_column) { // avoid unecessary query
            $.ajax({
                url: '/kanban/task/' + task_nid + '/update_column/' + new_column,
                data: {
                    'index': evt.newIndex
                },
                'success': function (data) {
                }
            });
        } else {
            $.ajax({
                url: '/kanban/task/' + task_nid + '/update_priority/' + evt.newIndex,
                'success': function (data) {
                }
            });
        }
    }

    static editTask(elt){
        KanbanBoard.log('Edit Task');

        KanbanBoard.ensureOneFieldEditionAtTime(elt);

        //show form and hide display
        $(elt).parents('div.gf-kanban-field-edit:first').find('.gf-kanban-not-editing').hide();
        $(elt).parents('div.gf-kanban-field-edit:first').find('.gf-kanban-editing').show();

        //focus field
        var field_to_focus = $(elt).parents(' div.gf-kanban-field-edit:first').find('form').data('field');
        if (field_to_focus != 'task-deadline') {
            $(elt).parents(' div.gf-kanban-field-edit:first').find('#' + field_to_focus).focus();
        }

        if(field_to_focus == 'task-deadline'){ //auto open calendar
            //$(elt).parents(' div.gf-kanban-field-edit:first').find('input.flatpickr-input.input').flatpickr().open();
        }

    }

    static cancelEditTask(elt){

        $(elt).parents('div.gf-kanban-field-edit:first').find('.gf-kanban-not-editing').show();
        $(elt).parents('div.gf-kanban-field-edit:first').find('.gf-kanban-editing').hide();

    }
    /**
     * Ask for confirmation before task(card) deletion
     * @param {type} taskId
     * @returns {undefined}
     */
    static preDeleteTask(taskId) {

        var sentence_confirmation = parent.Drupal.t("Are you sure you want to delete this card?", {}, {'context': 'gofast_kanban'});
        var html_content = sentence_confirmation + '<br /><br />'
                + '<input class="btn btn-sm btn-success" type="button" onClick="window.document.getElementById(\'gf_kanban\').contentWindow.kanbanBoard.deleteTask(' + taskId + ');" \n\ '
                + ' value="' + window.parent.Drupal.t('Validate', {}, {'context': 'gofast_kanban'}) + '" />';

        window.parent.Gofast.modal(html_content, window.parent.Drupal.t("Delete the card", {}, {'context': 'gofast_kanban'}));
    }

    deleteTask(taskId){
        KanbanBoard.log('deleteTask');

        var kanbanId = $('div#board').data('kanbanid');

        var url = '/kanban/task/'+ taskId +'/delete';
        $.ajax({
            'type': "POST",
            'url': url,
            'success': function (data) {

                //Refresh board (all)
                KanbanBoard.reloadKanban(kanbanId, true, function (data) {

                    var parser = new DOMParser();
                    var el = parser.parseFromString(data, "text/html");

                    var kanbanBoard = $(el).find('div#board').html();

                    $(document).find('div#board').html(kanbanBoard);
                });

                //close confirmation modal
                window.parent.Drupal.CTools.Modal.dismiss();
                //close Modal
                $('#kanbanModal').modal('hide');

            }
        });
    }

    static updateTask(elt){

        var form = $(elt).parents('div.gf-kanban-field-edit:first').find('form');
        var url = $(form).attr('action');
        var taskId = $(form).data('taskid');

        var datas = $(form).serialize();



        //Specific case with checkbox
        if($(form).attr('id') === 'gf-kanban-task-edit-content-visibility'){
            if($(form).serialize() == ''){
                datas = {'content-visibility' : 'off' };
            }
        }else  if($(form).attr('id') === 'gf-kanban-task-edit-assignees'){
            var old_datas = datas;
            var members = old_datas.replace(/members=/g, '').split('&');
            datas = { 'members' : members};
        }else  if($(form).attr('id') === 'gf-kanban-task-edit-attachement'){
            var old_datas = datas;
            var attachements = old_datas.replace(/attachements=/g, '').split('&');
            datas = { 'attachements' : attachements};
        }else if ($(form).attr('id') === 'gf-kanban-task-edit-person-in-charge'){
            if(datas.length < 1){
                datas = {'person-in-charge' : ''};
            }
        }else if($(form).attr('id') === 'gf-kanban-task-edit-description'){
            datas = {'description' : Drupal.gofast_kanban_editor.getData() }
        }


        $.ajax({
            'type': "POST",
            'url': url,
            'data': datas,
            'success': function (data) {

                //reload activity feed
                KanbanBoard.reloadTaskDetails(taskId, function (data) {

                    var parser = new DOMParser();
                    var el = parser.parseFromString(data, "text/html");

                    KanbanBoard.cancelEditTask(elt); //used to hide edition

                    var taskDetails = $(el).find('div.task-details').html();
                    $(document).find('div.task-details').html(taskDetails);

                    var checklist = $(el).find('div.task-checklists').html();
                    $(document).find('div.task-checklists').html(checklist);

                    var activities = $(el).find('div.task-activities').html();
                    $(document).find('div.task-activities').html(activities);

                    //Reload ckeditor
                    Drupal.gofast_kanban_editor = CKEDITOR.replace("task-description");

                });
            }
        });
    }




    /**********************************************************
     * Comment Part
     */
    /**
     * Add a new comment to the task
     * @returns {undefined}
     */
    static addNewComment() {
        KanbanBoard.log('addNewComment');

        var form = $('form.comment-form');
        var url = form.attr('action');
        var taskId = form.data('taskid');

        //Avoid adding empty comment
        var comment = $(form).find('.task-new-comment > textarea');
        if(comment.val().trim().length == 0){
            return false;
        }

        $.ajax({
            'type': "POST",
            'url': url,
            'data': form.serialize(),
            'success': function (data) {

                $(form).find('.publisher-input > textarea').val('');

                //reload activity feed
                KanbanBoard.reloadTaskDetails(taskId, function (data) {

                    var parser = new DOMParser();
                    var el = parser.parseFromString(data, "text/html");

                    var activities = $(el).find('div.task-activities').html();
                    $(document).find('div.task-activities').html(activities);

                    $(form).find('.publisher.focus').removeClass('focus active');

                });
            }
        });
    }


    /**
     * Ask for confirmation before  comment deletion
     * @param {type} commentId
     * @returns {undefined}
     */
    static preDeleteComment(commentId) {

        var sentence_confirmation = parent.Drupal.t("Are you sure you want to delete this comment?", {}, {'context': 'gofast_kanban'});
        var html_content = sentence_confirmation + '<br /><br />'
                + '<input class="btn btn-sm btn-success" type="button" onClick="window.document.getElementById(\'gf_kanban\').contentWindow.kanbanBoard.deleteComment(' + commentId + ');" \n\ '
                + ' value="' + window.parent.Drupal.t('Validate', {}, {'context': 'gofast_kanban'}) + '" />';

        window.parent.Gofast.modal(html_content, window.parent.Drupal.t("Delete the comment", {}, {'context': 'gofast_kanban'}));
    }


    static editComment(elt){
        KanbanBoard.log('Edit Comment');

        KanbanBoard.ensureOneFieldEditionAtTime(elt);

        //show form and hide display
        $(elt).parent().parent().find('.gf-kanban-not-editing').hide();
        $(elt).parent().parent().find('.gf-kanban-editing').show();

    }

    static cancelEditComment(elt){
        $(elt).parent().parent().find('.gf-kanban-editing').hide();
        $(elt).parent().parent().find('.gf-kanban-not-editing').show();
    }

    static updateComment(elt){
        KanbanBoard.log('Update Comment');

        //hide form and hide display
        $(elt).parent().parent().find('.gf-kanban-editing').hide();
        $(elt).parent().parent().find('.gf-kanban-not-editing').show();

        var form = $(elt).parent().parent().find('form');
        var taskId = $(form).data('taskid');

        var url = $(form).attr('action');

        $.ajax({
            'type': "POST",
            'url': url,
            'data': $(form).serialize(),
            'success': function (data) {

                //reload activity feed
                KanbanBoard.reloadTaskDetails(taskId, function (data) {

                    var parser = new DOMParser();
                    var el = parser.parseFromString(data, "text/html");

                    var activities = $(el).find('div.task-activities').html();
                    $(document).find('div.task-activities').html(activities);

                });
            }
        });

    }

    /**
     * Delete Comment
     * @param {type} commentId
     * @returns {undefined}
     */
    deleteComment(commentId) {
        KanbanBoard.log('deleteComment');

        var form = $('form.comment-form');
        var url = '/kanban/task/delete/comment/' + commentId;

        $.ajax({
            'type': "POST",
            'url': url,
            'success': function (data) {

                var taskId = data.trim();

                //reload activity feed
                KanbanBoard.reloadTaskDetails(taskId, function (data) {

                    var parser = new DOMParser();
                    var el = parser.parseFromString(data, "text/html");

                    var activities = $(el).find('div.task-activities').html();

                    $(document).find('div.task-activities').html(activities);

                    //close modal
                    window.parent.Drupal.CTools.Modal.dismiss();

                });
            }
        });
    }



    /*********************************************************
     * Checklist Part
     */

    static addTodo(elt){
        KanbanBoard.log('addTodo');

        var form = $(elt).parents('form#gofast-kanban-checklistitem-form');
        var url = form.attr('action');
        var taskId = form.data('taskid');
        var checklistId = form.find('input[name=cid]').val();

        //Avoid adding empty comment
        var todoLabel = $(form).find('input#edit-label');
        if(todoLabel.val().trim().length === 0){
            return false;
        }

        $.ajax({
            'type': "POST",
            'url': url,
            'data': form.serialize(),
            'success': function (data) {

                $(form).find('input#edit-label').val('');

                //reload task details
                KanbanBoard.reloadTaskDetails(taskId, function (data) {

                    var parser = new DOMParser();
                    var el = parser.parseFromString(data, "text/html");

                    //update checklist
                    //@TODO : reload only modified checklist
                    var checklist = $(el).find('div.task-checklists').html();
                    $(document).find('div.task-checklists').html(checklist);

                    //update activities
                    var activities = $(el).find('div.task-activities').html();
                    $(document).find('div.task-activities').html(activities);

                });

                $(form).find('.publisher.focus').removeClass('focus active');
            }
        });
    }

    static cancelAddTodo(elt){
        KanbanBoard.log('cancelAddTodo');

        $('div.todolist-form').removeClass('focus active');
    }

    /**
     * Ask for confirmation before  comment deletion
     * @param {type} commentId
     * @returns {undefined}
     */
    static preDeleteTodo(todoId) {

        var sentence_confirmation = parent.Drupal.t("Are you sure you want to delete this item?", {}, {'context': 'gofast_kanban'});
        var html_content = sentence_confirmation + '<br /><br />'
                + '<input class="btn btn-sm btn-success" type="button" onClick="window.document.getElementById(\'gf_kanban\').contentWindow.kanbanBoard.deleteTodo(' + todoId + ');" \n\ '
                + ' value="' + window.parent.Drupal.t('Validate', {}, {'context': 'gofast_kanban'}) + '" />';

        window.parent.Gofast.modal(html_content, window.parent.Drupal.t("Delete the item", {}, {'context': 'gofast_kanban'}));
    }

    deleteTodo(todoId){
        KanbanBoard.log('deleteComment');

        var url = '/kanban/task/delete/todo/' + todoId;
        var form = $('form#gofast-kanban-checklistitem-form');
        var taskId =  form.data('taskid');

        $.ajax({
            'type': "POST",
            'url': url,
            'success': function (data) {

                //reload activity feed
                KanbanBoard.reloadTaskDetails(taskId, function (data) {

                    var parser = new DOMParser();
                    var el = parser.parseFromString(data, "text/html");

                    //update checklist
                    //@TODO : reload only modified checklist
                    var checklist = $(el).find('div.task-checklists').html();
                    $(document).find('div.task-checklists').html(checklist);

                    //update activities
                    var activities = $(el).find('div.task-activities').html();
                    $(document).find('div.task-activities').html(activities);


                    //close modal
                    window.parent.Drupal.CTools.Modal.dismiss();
                });
            }
        });
    }

    static updateTodoStatus(elt){

        var todoId = $(elt).parents('div.row:first').data('ciid');
        var taskId = $(elt).parents('form:first').data('taskid');
        var status = ($(elt).parent().find('input.todo-status').is(':checked') === true )? 1 : 0;

        var url = '/kanban/task/update_status/todo/' + todoId + '/'+ status;

        $.ajax({
            'type': "POST",
            'url': url,
            'success': function (data) {

                //reload activity feed
                KanbanBoard.reloadTaskDetails(taskId, function (data) {

                    var parser = new DOMParser();
                    var el = parser.parseFromString(data, "text/html");

                    //update checklist
                    var checklist = $(el).find('div.task-checklists').html();
                    $(document).find('div.task-checklists').html(checklist);

                    //update activities
                    var activities = $(el).find('div.task-activities').html();
                    $(document).find('div.task-activities').html(activities);

                });
            }
        });
    }

    static editTodo(elt) {

        KanbanBoard.log("editTodo");

        KanbanBoard.ensureOneFieldEditionAtTime(elt);

        //show form and hide display
        $(elt).parents('div.row:first').find('.gf-kanban-not-editing').hide();
        $(elt).parents('div.row:first').find('.gf-kanban-editing').show();

        // $(elt).parents('div.row:first').find('input[name=label]').focus();
    }

    static cancelEditTodo(elt){

        KanbanBoard.log("cancelEditTodo");

        //show form and hide display
        $(elt).parents('div.row:first').find('.gf-kanban-editing').hide();
        $(elt).parents('div.row:first').find('.gf-kanban-not-editing').show();
    }

    static updateTodo(elt){
        KanbanBoard.log('updateTodo');

        var form = $(elt).parents('form:first');
        var taskId = $(form).data('taskid');

        var url= $(form).attr('action');

        $.ajax({
            'type': "POST",
            'url': url,
            'data': $(form).serialize(),
            'success': function (data) {

                //reload activity feed
                KanbanBoard.reloadTaskDetails(taskId, function (data) {

                    var parser = new DOMParser();
                    var el = parser.parseFromString(data, "text/html");

                    //update checklist
                    //@TODO : reload only modified checklist
                    var checklist = $(el).find('div.task-checklists').html();
                    $(document).find('div.task-checklists').html(checklist);

                    var activities = $(el).find('div.task-activities').html();
                    $(document).find('div.task-activities').html(activities);

                });
            }
        });

    }

    /**
     * Trigger the opening of specific card into modal
     * @param {type} card_id
     * @returns {undefined}
     */
    static openCard(card_id) {

        if (null !== card_id && card_id !== '') {

            $('div.task-issue[data-nid=' + card_id + ']').find('span.gf-link-to').trigger('click');

            //update url + remove data-attr to avoid re-opening card on page reloading
            $('div.board').data('cardToDisplay', '');
            var urlPath = window.parent.location.origin + window.parent.location.pathname + window.parent.location.hash;

            window.parent.history.replaceState( {}, "", urlPath);

        }

    }

};

(function ($) {
    'use strict';

    // Drupal.gofast_kanban = Drupal.gofast_kanban || {};

    $(document).ready(function () {

        window.kanbanBoard = new KanbanBoard();

        $(document).on('theme:init', function () {
            window.kanbanBoard = new KanbanBoard();
        });
        KanbanBoard.refreshSortable();
        KanbanBoard.manageFormAutoSubmit();

    });

})(jQuery);



(function ($, Gofast, Drupal) {
    'use strict';
    Gofast.reloadKanbanFromPolling = function (kanbanId) {

        KanbanBoard.log('reloadKanbanFromPolling');

        var filter = jQuery('#gf_kanban_search').val().trim();

        $.ajax({
            'type': "POST",
            'url': '/kanban/' + kanbanId,
            'data': {
                'filter' : filter
            },
            'success': function (data) {
                var parser = new DOMParser();
                var el = parser.parseFromString(data, "text/html");
                var kanbanBoard = jQuery(el).find('div#board').html();

                //   var source = $('#gf_kanban')[0].contentDocument;
                var source = jQuery(document);
                jQuery(source).find('div#board').html(kanbanBoard);
                if (jQuery(source).find('div#board').data('userRole') !== 'read only member') {

                    //data-toggle="sortable" data-group="tasks" data-delay="50" data-force-fallback="true" data-on-end="KanbanBoard.updateTaskColumn"
                    var tasks = jQuery(document).find('.task-body');

                    jQuery.each(tasks, function (key, elt) {
                        Sortable.create(elt, {
                            group: '.tasks',
                            onEnd: function (evt) {
                                KanbanBoard.updateTaskColumn(evt);
                            },
                            forceFallback: true,
                            fallbackTolerance: 10
                        });
                    });


                    KanbanBoard.manageFormAutoSubmit();


                }

                //keep filter
                jQuery('#gf_kanban_search').val(filter);
            }
        });
    };
})(jQuery, Gofast, Drupal);

function changeClassContainer(){
    var element = document.getElementsByClassName("main-container");
    if(typeof element[0] != 'undefined'){
        element[0].classList.add("container-fluid");
        element[0].classList.remove("container");
    }
};

changeClassContainer();
