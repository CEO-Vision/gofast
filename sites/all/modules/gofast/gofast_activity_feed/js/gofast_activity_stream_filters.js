(function ($, Gofast, Drupal) {

    Drupal.behaviors.gofast_activity_stream_filters = {
        attach: function (context, settings) {

            // Get Switchers
            var switchers = $('input.stream_filter_switch').not('.processed');
            // Set on click switcher
            switchers.each(function(){
                setSwichers($(this));
            });
            // Set Switchers state
            setSwichersStateFromCookies();

            // Get jsTrees
            var jstrees = $(".gofast_stream_filter_ztree").not('.processed');
            // Set jsTrees
            jstrees.each(function(){
                setJsTreeView($(this), $(this).attr('data-tree'));
            });

            // Get jsTrees
            var statesFilters = $("a.gofast_stream_filter_state").not('.processed');
            // Set jsTrees
            statesFilters.each(function(){
                $(this).addClass('processed');
                $(this).click(function(){ handleAddStateFilter($(this))});

            });

            // Get jsTrees
            var actorsFilters = $("#kt_actors .datatable-table .datatable-body a").not('.processed');
            // Set jsTrees
            actorsFilters.each(function(){
                $(this).addClass('processed');
                $(this).click(function(e){ e.preventDefault(); handleAddCreatorFilter($(this))});

            });

            //Init actor table
            if(document.querySelector('#kt_actors') != null && !document.querySelector('#kt_actors').classList.contains('processed')){
                document.querySelector('#kt_actors').classList.add('processed');
                let table = document.querySelector('#kt_actors');
                if(table){
                    GofastActivityActorsTable.init(table);
                }   
            }
            

            var cleanFilters = $("a.gofast_stream_filter_clean_filters").not('.processed');
            cleanFilters.each(function(){
                $(this).addClass('processed');
                $(this).click(function(){
                    setInitFiltersCookies();
                    setSwichersStateFromCookies();
                });
            });

            reloadTagsContainer();

        }
    };

    var GofastActivityActorsTable = function() {
        // Private functions
        let _tableEl;
        let _bodyHeight;
        let _table;
        let _columns;

        // user table
        var initTable = function(table) {

            _tableEl = table
            _bodyHeight = table.parentElement.offsetHeight - 50;

            let jsonColumns = _tableEl.dataset.columns
            _columns = JSON.parse(jsonColumns)


            _crateTable(table)
            eventsCapture();

        };

        var _crateTable = function(table){

            _table = $(table).KTDatatable({
                data: {
                    type: 'remote',
                    source: {
                        read: {
                            url: window.origin + "/activity/async/get_actors",
                            method: 'GET',
                            map: function(raw) {
                                // sample data mapping
                                var dataSet = raw;
                                if (typeof raw.data !== 'undefined') {
                                    dataSet = raw.data;
                                }
                                return dataSet;
                            },
                        },

                    },
                    pageSize: 10,
                    serverPaging: false,
                    serverFiltering: true,
                    serverSorting: false,
                },

                // layout definition
                layout: {
                    scroll: true, // enable/disable datatable scroll both horizontal and vertical when needed.
                    class: 'GofastTable',
                    height: _bodyHeight,
                    footer: false, // display/hide footer
                    icons:{
                        pagination: {
                            next: 'la la-angle-right',
                            prev: 'la la-angle-left'
                        }
                    }
                        
                },

                toolbar: {
                    items: {
                        info: false,
                        pagination: {
                            pageSizeSelect : ""
                        }
                    },
                    placement: ['bottom']
                },

                pagination: true,

                search: {
                    input: $('#kt_datatable_search_query'),
                    delay: 400,
                    key: 'generalSearch'
                },
                
                rows: {
                    afterTemplate: function (row, data, index) {
                        Drupal.attachBehaviors(row);
                    }
                },

                translate: {
                    records : {
                        processing : Drupal.t('Please wait...'),
                        noRecords: Drupal.t('No records found')
                    },
                    toolbar: {
                        pagination: {
                            items:{
                                default: {
                                    first: Drupal.t('First'),
                                    prev: Drupal.t('Previous'),
                                    next: Drupal.t('Next'),
                                    last: Drupal.t('Last'),
                                    more: Drupal.t('More pages'),
                                    input: Drupal.t('Page number'),
                                    select: Drupal.t('Select page size')
                                },
                                info: Drupal.t("Displaying {{start}} - {{end}} of {{total}} records")
                            }
                        }
                    }
                },

                // columns definition
                columns: [
                    {
                        field: '',
                        title: _columns.displayname ,
                        autoHide: false,
                        template: function(data) {
                            return '<a class="btn btn-link text-nowrap" data-label="' + data.displayname + '" data-uid="' + data.uid + '" href="#"> ' + data.displayname + '</a>'
                        },
                    }
                ],
            });
        }

        return {

            init: function(table){
                initTable(table)
            },
        };
    }();

    var eventsCapture = function() {
        $('#kt_actors').on('datatable-on-goto-page', function (e, args) {
            Drupal.attachBehaviors();
        })
    };

    window.setInitFiltersCookies = function(refresh = true) {

        var filters = {
            "no_filter": false,
            "display_blog": true,
            "user_filter": false,
            "type_filters": [],
            "space_filters" : [],
            "state_filters" : [],
            "actors_filters" : []
            };
        setFiltersToCookies(filters, refresh);

        return filters;
    }

    window.getFiltersFromCookies = function() {
        var cookies = $.cookie('activity_feed_filters');
        if(cookies){
            var filters = JSON.parse(cookies);
            return filters;
        }

        return setInitFiltersCookies();
    }

    window.setFiltersToCookies = function(filters, refresh = true){
        // we can't set cookie as httpOnly via JS and there is no point doing it on filters, but we at least require HTTPS
        $.cookie('activity_feed_filters', JSON.stringify(filters), {secure: true});
        if (Gofast.get('user').uid !== 0 && refresh) {
            Gofast.reload_activity_feed();
        }
    }

    function setSwichers(switcher){
        switcher.addClass('processed');
        switcher.click(function(){ handleChangeSwitcher($(this)) });

    }

    function setSwichersStateFromCookies(){

        var switchers = $('input.stream_filter_switch.processed');
        var switchersJS = document.querySelectorAll("input.stream_filter_switch.processed");
        let { user_filter, type_filters, display_blog, no_filter } = getFiltersFromCookies();

        switchersJS.forEach(node => {

            let data_filter = node.dataset.filter;

            switch(data_filter){

                case 'display_blog':
                    node.checked = display_blog;
                    break;

                case 'user_filter':
                    node.checked = user_filter;
                    break;

                case 'type_filter':

                    switcherId = node.id;
                    var index = type_filters.indexOf(switcherId);

                    if(index > -1){
                        node.checked = true;
                    } else {
                        node.checked = false;
                    }
                    break;
                case 'no_filter':
                    node.checked = no_filter;
                    break;
                default:
                    break;

            }

        });

    }

    function handleChangeSwitcher(switcher){

        var data_filter = switcher.attr('data-filter');
        var switcherState = switcher.is( ":checked" );

        var filters = getFiltersFromCookies();

        var newFilter = {...filters};

        switch(data_filter){

            case 'display_blog':
                newFilter = {
                    ...filters,
                    no_filter: false,
                    display_blog: switcherState
                };
                break;

            case 'user_filter':
                newFilter = {
                    ...filters,
                    no_filter: false,
                    user_filter: switcherState
                };
                break;

            case 'type_filter':
                const { type_filters } = filters;
                switcherId = switcher.attr('id');
                var index = type_filters.indexOf(switcherId);

                if(switcherState){
                    if(index == -1){

                        newTypeFilters = type_filters;
                        newTypeFilters.push(switcherId);
                        newFilter = {
                            ...filters,
                            no_filter: false,
                            type_filters: newTypeFilters
                        }
                    }
                } else {

                    if(index > -1){
                        newTypeFilters = type_filters;
                        newTypeFilters.splice(index, 1);
                        newFilter = {
                            ...filters,
                            no_filter: false,
                            type_filters: newTypeFilters
                        }
                    }
                }
                break;
            case 'no_filter':
                let fil;
                if(switcherState) {
                    fil = {
                        ...setInitFiltersCookies(false),
                        display_blog: false
                    };
                }else{
                    fil = {
                        ...filters
                    };
                }
                newFilter = {
                    ...fil,
                    no_filter: switcherState
                };
                break;
            default:
                break;

        }

        setFiltersToCookies(newFilter);
    }

    function reloadTagsContainer(){

        var { space_filters, state_filters, actors_filters } = getFiltersFromCookies();
        var container = $('#gofast_activity_stream_filter_tags_container');

        if(container.length == 0){
            return;
        }

        var tags = [];
        container[0].innerHTML = '';

        state_filters.forEach(filter => {
            newTag = '<tag class="tagify__tag tagify--noAnim gofast_activity_stream_filter_tags" ><x data-id="' + filter.id + '" data-type="state_filters" class="tagify__tag__removeBtn" role="button" aria-label="remove tag"></x><div class="d-flex align-items-center"><i class="fas fa-flag font-size-sm mr-1"></i><span class="tagify__tag-text">' + filter.label + '</span></div></tag>';
            tags.push(newTag);
        });

        space_filters.forEach(filter => {
            newTag = '<tag class="tagify__tag tagify--noAnim gofast_activity_stream_filter_tags" ><x data-id="' + filter.id + '" data-type="space_filters" class="tagify__tag__removeBtn" role="button" aria-label="remove tag"></x><div class="d-flex align-items-center"><i class="fas fa-folder font-size-sm mr-1"></i><span class="tagify__tag-text">' + filter.label + '</span></div></tag>';
            tags.push(newTag);
        });
        if(actors_filters == undefined){
            actors_filters = [];
        }
        actors_filters.forEach(filter => {
            newTag = '<tag class="tagify__tag tagify--noAnim gofast_activity_stream_filter_tags" ><x data-id="' + filter.id + '" data-type="actors_filters" class="tagify__tag__removeBtn" role="button" aria-label="remove tag"></x><div class="d-flex align-items-center"><i class="fas fa-user font-size-sm mr-1"></i><span class="tagify__tag-text">' + filter.label + '</span></div></tag>';
            tags.push(newTag);
        });

        container.append(tags);

        tagsRemove = $('.gofast_activity_stream_filter_tags x');

        tagsRemove.off();

        tagsRemove.click(function(){
            handleRemoveSpaceFiler($(this));
        });
    }

    function handleRemoveSpaceFiler(tag){

        const filters = getFiltersFromCookies();
        var { space_filters, state_filters, actors_filters } = filters;
        idTag = tag.attr('data-id');
        typeTag = tag.attr('data-type');
        indexTag = -1;

        if(typeTag == 'state_filters'){
            for(var i = 0; i < state_filters.length ; i ++){

                if( state_filters[i].id == idTag ){
                    indexTag = i;
                }
            }

            if (indexTag > -1){


                newStateFilter = state_filters;
                newStateFilter.splice(indexTag, 1);

                newFilter = {
                    ...filters,
                    no_filter: false,
                    state_filters: newStateFilter
                };

                setFiltersToCookies(newFilter);

            }
        }

        if(typeTag == 'space_filters'){

            for(var i = 0; i < space_filters.length ; i ++){

                if( space_filters[i].id == idTag ){
                    indexTag = i;
                }
            }

            if (indexTag > -1){


                newSpaceFilter = space_filters;
                newSpaceFilter.splice(indexTag, 1);

                newFilter = {
                    ...filters,
                    no_filter: false,
                    space_filters: newSpaceFilter
                };

                setFiltersToCookies(newFilter);
            }

        }

        if(typeTag == 'actors_filters'){

            for(var i = 0; i < actors_filters.length ; i ++){

                if( actors_filters[i].id == idTag ){
                    indexTag = i;
                }
            }

            if (indexTag > -1){


                newSpaceFilter = actors_filters;
                newSpaceFilter.splice(indexTag, 1);

                newFilter = {
                    ...filters,
                    no_filter: false,
                    actors_filters: newSpaceFilter
                };

                setFiltersToCookies(newFilter);
            }

        }

        reloadTagsContainer();

    }

    function handleAddSpaceFilter(data){

        const filter = getFiltersFromCookies();
        const { space_filters } = filter;
        var newSpaceFilter = [];
        var newFilter = {
            ...filter
        }

        var result = false;

        if (space_filters.length > 0){

            var result = space_filters.find(function(e) {
                return e.id === data.id; //Change 3 to what you want to search for
              });

            if(!result){

                newSpaceFilter = [
                    ...space_filters,
                    {
                        id: data.id,
                        label: data.text
                    }
                ];

                newFilter = {
                    ...filter,
                    no_filter: false,
                    space_filters: newSpaceFilter
                };
            }

        } else {

            newSpaceFilter = [
                ...space_filters,
                {
                    id: data.id,
                    label: data.text
                }
            ];

            newFilter = {
                ...filter,
                no_filter: false,
                space_filters: newSpaceFilter
            };

        }

        setFiltersToCookies(newFilter);
        reloadTagsContainer();
    }

    function handleAddStateFilter(state){

        console.log(state);

        data = {
            id: parseInt(state.attr('data-id')),
            text: state.attr('data-label')
        }

        const filter = getFiltersFromCookies();
        const { state_filters } = filter;
        var newStateFilter = [];
        var newFilter = {
            ...filter
        }

        var result = false;

        if (state_filters.length > 0){

            var result = state_filters.find(function(e) {
                return e.id === data.id; //Change 3 to what you want to search for
              });

            if(!result){

                newStateFilter = [
                    ...state_filters,
                    {
                        id: data.id,
                        label: data.text
                    }
                ];

                newFilter = {
                    ...filter,
                    no_filter: false,
                    state_filters: newStateFilter
                };
            }

        } else {

            newStateFilter = [
                ...state_filters,
                {
                    id: data.id,
                    label: data.text
                }
            ];

            newFilter = {
                ...filter,
                no_filter: false,
                state_filters: newStateFilter
            };

        }

        setFiltersToCookies(newFilter);
        reloadTagsContainer();
    }

    function handleAddCreatorFilter(actor){

        console.log(actor);
        data = {
            id: parseInt(actor.attr('data-uid')),
            text: actor.attr('data-label')
        }

        const filter = getFiltersFromCookies();
        var { actors_filters } = filter;
        var newActorFilter = [];
        var newFilter = {
            ...filter
        }

        var result = false;
        if(actors_filters == undefined){
            actors_filters = [];
        }
        if (actors_filters.length > 0){

            var result = actors_filters.find(function(e) {
                return e.id === data.id; //Change 3 to what you want to search for
              });

            if(!result){

                newActorFilter = [
                    ...actors_filters,
                    {
                        id: data.id,
                        label: data.text
                    }
                ];

                newFilter = {
                    ...filter,
                    no_filter: false,
                    actors_filters: newActorFilter
                };
            }

        } else {

            newActorFilter = [
                ...actors_filters,
                {
                    id: data.id,
                    label: data.text
                }
            ];

            newFilter = {
                ...filter,
                no_filter: false,
                actors_filters: newActorFilter
            };

        }

        setFiltersToCookies(newFilter);
        reloadTagsContainer();
    }



    function setJsTreeView(jsTree, mainSpace){

        jsTree.addClass('processed');

        jsTree.jstree({
            "core": {
                "themes": {
                    "responsive": false
                },
                // so that create works
                "check_callback": true,
                "data": {
                    "url": Drupal.settings.gofast.baseUrl + "/activity/ajax/espaces/" + mainSpace,
                    "data": function(node) {
                        return {
                            "id": node.id
                        };
                    }
                },
            },
            "types": {
                "default": {
                    "icon": "fa fa-folder text-primary"
                },
                "file": {
                    "icon": "fa fa-file  text-primary"
                }
            },
            "state": {
                "key": "demo2"
            },
            "plugins": ["contextmenu", "state", "types"]
        });

        jsTree.on('select_node.jstree', function(e, data) {

            handleAddSpaceFilter(data.node);

            data.instance.deselect_node(data.node);
        });
    }


})(jQuery, Gofast, Drupal);
