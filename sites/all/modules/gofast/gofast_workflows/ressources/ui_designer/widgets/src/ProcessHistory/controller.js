function displayHistoryWidget($scope, $http, $location, $sce, $filter) {
    $scope.events = [];
    $scope.process = [];

    let search_param = new URLSearchParams(location.search);
    let langcode = search_param.get("locale");
    if(langcode === "fr" || langcode === undefined) {
        $scope.date_format_full = "dd/MM/yyyy HH:mm";
        $scope.date_format = "dd/MM/yyyy";
    } else if(langcode === "en") {
        $scope.date_format_full = "MM/dd/yyyy HH:mm";
        $scope.date_format = "MM/dd/yyyy";
    }
    var type_page = "form";
    if ($location.$$absUrl.indexOf("processInstance/") !== -1) {
        type_page = "summary";
    } else if ($location.$$absUrl.indexOf("historyBdm/") !== -1) {
        type_page = "historybdm";
    }

    if (type_page === "form") {
        //load context manually
        //var url = new URL($location.$$absUrl);
        // var id = url.searchParams.get("id");
        var id = getParameterByName("id");
        $http.get("/bonita/API/bpm/userTask/" + id).then(
                function successCallback(response) {
                    id = response.data.rootCaseId;
                    $http.get("/bonita/API/bpm/case/" + id + "/context").then(
                            function successCallback(response) {
                                $scope.context = response.data;
                            }
                    );
                }
        );
    } else if (type_page === "historybdm") {
        //var url = new URL($location.$$absUrl);
        //var persistenceId = url.searchParams.get("persistenceId");
        var persistenceId = getParameterByName("persistenceId");
        $http.get("/bonita/API/bdm/businessData/com.company.model.ProcessHistory/" + persistenceId).then(
                function successCallback(response) {
                    $scope.context = response;
                }
        );
    } else {
        //load context manually
        //var url = new URL($location.$$absUrl);
        //var id = url.searchParams.get("id");
        var id = getParameterByName("id");
        $http.get("/bonita/API/bpm/case/" + id + "/context").then(
                function successCallback(response) {
                    $scope.context = response.data;
                }
        );
    }

    $scope.$watch("context", function () {
        if (typeof $scope.context == "undefined") {
            return;
        }

        //we loop each variables from context to search processhistory variable
        var processHistory;
        if (type_page === "historybdm") {
            processHistory = $scope.context;
            processHistory.link = "";
        } else {
            for (var property in $scope.context) {
                if ($scope.context.hasOwnProperty(property)) {
                    if ($scope.context[property].type == "com.company.model.ProcessHistory") {
                        processHistory = $scope.context[property];
                    }
                }
            }
        }
        var data_json;
        $http.get("/bonita/" + processHistory.link).then(
                function successCallback(response) {
                    if (type_page === "historybdm") {
                        data_json = processHistory.data;
                    } else {
                        data_json = response.data;
                    }
                    $scope.process.start_date = data_json.start_date;
                    $scope.process.initiator = data_json.initiator;
                    if (typeof data_json.title == "undefined") {
                        $scope.process.title = "";
                    } else {
                        $scope.process.title = data_json.title;
                    }
                    var inverted = "timeline-inverted";
                    data_json.lines.reverse().forEach(function (element) {
                        if (inverted === "") {
                            inverted = "timeline-inverted";
                        } else {
                            inverted = "";
                        }
                        //construct display depending on task infos
                        var task_object = JSON.parse(element.task_object);
                        var badgeclass = "success";
                        var badgeiconclass = "glyphicon-check";
                        var infos_date = task_object.date;
                        var infos_actor = task_object.actor_displayname;
                        var content = "";
                        var content_node = "";
                        var display_content = false;
                        var content_user = "";
                        var display_content_user = false;
                        //then loop inside contents to get all pair key=>values stored by process

                        element.contents.forEach(function (mycontent) {
                            if (mycontent.type === "string") {
                                content = content + $sce.trustAsHtml("<li><span class='ng-binding'> <i class='glyphicon glyphicon-th-list'></i> <u>" + $filter('gfdTranslate')(mycontent.name) + "</u> : " + mycontent.content_value.replace(/(\r\n|\n|\r)/gm, "<br>") + "</span></li>");
                            } else if (mycontent.type === "node") {
                                display_content = true;
                                var json_node = JSON.parse(mycontent.content_value);
                                var content_nid = "";
                                var content_title = "";
                                var content_node_buffer = "";
                                for (var property in json_node) {
                                    if (json_node.hasOwnProperty(property)) {
                                        if (property === "nid") {
                                            content_nid = json_node[property];
                                        } else if (property === "title") {
                                            content_title = json_node[property];
                                        } else {
                                            content_node_buffer = content_node_buffer + "<li><i class='glyphicon glyphicon-tag'></i> " + property + " : " + json_node[property] + "</li>";
                                        }
                                    }
                                }

                                if (content_node_buffer != "") {
                                    content_node_buffer = "<ul>" + content_node_buffer + "</ul>";
                                }
                                content_node = content_node + $sce.trustAsHtml("<li><small class='text-muted ng-binding'><i class='glyphicon glyphicon-file'></i> <a style='cursor:pointer;text-decoration:none;' onClick='window.parent.parent.Gofast.processAjax(\"/node/" + content_nid + "\");window.parent.parent.modalContentClose();'>" + content_title + "</a> " + content_node_buffer + "</small></li>");


                            } else if (mycontent.type === "user" || mycontent.type === "group") {
                                display_content_user = true;
                                var json_node = JSON.parse(mycontent.content_value);
                                var content_displayname = "";
                                var content_user_buffer = "";
                                var content_task_end_date = "";
                                for (var property in json_node) {
                                    if (json_node.hasOwnProperty(property)) {
                                        if (property === "username") {
                                            content_login = json_node[property];
                                        } else if (property === "displayname") {
                                            content_displayname = json_node[property];
                                            
                                            //Try to format assignations
                                            var regExp = /\(([^)]+)\)/;
                                            var matches = regExp.exec(content_displayname);
                                            if(matches !== null && matches.length > 1){
                                                var match = matches[1].trim();
                                                tmatch = $filter('gfdTranslate')(match);
                                                content_displayname = content_displayname.replace(match, tmatch);
                                            }
                                        } else if(property === "task_end_date") {
                                            content_task_end_date = json_node[property];
                                            content_task_end_date = get_deadline_html(content_task_end_date);

                                        } else {
                                            content_user_buffer = content_user_buffer + "<li><i class='glyphicon glyphicon-tag'></i> " + property + " : " + json_node[property] + "</li>";
                                        }
                                    }
                                }

                                if (content_user_buffer != "") {
                                    content_user_buffer = "<ul>" + content_user_buffer + "</ul>";
                                }
                                var content_user_icon = "fas fa-user";
                                if (mycontent.type === "group") {
                                    content_user_icon = "fas fa-users";
                                }
                                content_user = content_user + "<li><small class='text-muted ng-binding'><i class='" + content_user_icon + "'></i> " + content_displayname + content_user_buffer + content_task_end_date + "</small></li>";
                            }
                        });
                        if (display_content) {
                            content_node = "<li><span class='ng-binding'> <i class='glyphicon glyphicon-th-list'></i> <u>" + $filter('gfdTranslate')("Document(s)") + " : </u></span><ul>" + content_node + "</ul></li>";
                        }
                        if (display_content_user) {
                            content_user = "<li><span class='ng-binding'> <i class='glyphicon glyphicon-th-list'></i> <u>" + $filter('gfdTranslate')("Actor(s)") + " : </u></span><ul>" + content_user + "</ul></li>";
                        }
                        var pre_description = "";
                        if (typeof task_object.pre_description !== "undefined") {
                            pre_description = task_object.pre_description;
                        }
                        content = "<div>" + pre_description + $filter('gfdTranslate')(task_object.description) + "</div><ul>" + content + content_node + content_user + "</ul>";

                        if (task_object.type == "AUTOMATIC_TASK") {
                            badgeclass = "info";
                            badgeiconclass = "glyphicon-wrench";
                        }

                        $scope.events.push({
                            badgeClass: badgeclass,
                            badgeIconClass: badgeiconclass,
                            title: $sce.trustAsHtml(task_object.name),
                            description: task_object.description,
                            content: $sce.trustAsHtml(content),
                            inverted: inverted,
                            infos_actor: infos_actor,
                            infos_date: infos_date
                        });
                    });
                }
        );

    });


    function getParameterByName(name) {
        name = name.replace(/[\[]/, "\\[").replace(/[\]]/, "\\]");
        var regex = new RegExp("[\\?&]" + name + "=([^&#]*)"),
                results = regex.exec(location.search);
        return results === null ? "" : decodeURIComponent(results[1].replace(/\+/g, " "));
    }

    
  function get_deadline_html(end_date){
    var d = new Date(end_date);
    var timestamp_now = new Date().getTime() / 1000;
    var timestamp = d.getTime() / 1000;

    let deadline_color = "";
    if(timestamp_now > timestamp){
        deadline_color = "#c0392b";
    }else if(timestamp - timestamp_now < 60*60*24){
        deadline_color = "#d35400";
    }else{
        deadline_color = "#2ecc71";
    }
    if(end_date === null || typeof end_date == "undefined"){
        end_date = " / ";
        deadline_color = "#5bc0de";
    }
    let formatted_end_date = $filter('date')(end_date, $scope.date_format);
    let deadline_html = `<span style="display: inline-block;"><i class="far fa-clock" style="margin: 0 3px;"></i><span style="color:${deadline_color};" title="${$filter('gfdTranslate')("label.process_deadline")}">${formatted_end_date}</span></span>`;

    return deadline_html;
  }

}