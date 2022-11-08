//var workflowService = workflow.getWorkflowService();

var noderef = args.reference;
var description = args.description;
var taskID = args.task_id;
var op = args.op;
var transitionID = args.transitionID;
var return_value = "OK";
var type_workflow = args.type_workflow;

//var type_workflow = "activiti$activitiAdhoc";
// var mytask = workflow.getInstance("activiti$10947");
//mytask['delete']();
//var op = "delete";
// var node = search.findNode(noderef);
//var createanneedocument = nomDocument.substring(19,23);
//var createmoisdocument = nomDocument.substring(23,25);
//var createjourdocument = nomDocument.substring(25,27);

// Modification des dates
//node.properties["cm:creator"] = people.getPerson("sjeandroz");
//node.properties["cm:creator"] = "sjeandroz";
//node.save();
//return_value = "OK!";
// return_value = node.properties["cm:created"];

var W = {
        next: function(taskID){
                var mytask = workflow.getTaskById(taskID);
	//	mytask.parameters["wf:reviewOutcome"] = "Approve";
                mytask.endTask(transitionID);
        }

}

if(op == "new_workflow_task"){
        var personassignee =  args.assignee;
	//personassignee est actuellement une chaine de la forme user1,user2,user3
	//il faut la transformer en tableau d'objets user
	var array_users=personassignee.split(',');
        var array_users_object = new Array();
	for (index = 0; index < array_users.length; ++index) {
		array_users_object[index] = people.getPerson(array_users[index]);
	}
        var node = search.findNode(args.reference);
	if(args.date == 'null'){
		var DueDate = "null";
	}else{
		var DueDate = new Date(args.date*1000);
	}
	try{
        	var myworkflow = initWorkflow(args.reference);
	}catch(ex){
		return_value = "KO";
	}

}else if(op == "end_task"){
	try{
        	W.next(taskID);
	}catch(ex){
		 return_value = "KO";
	}
}


function initWorkflow(noderef)
{
	var wflow = actions.create("start-workflow");
	wflow.parameters.workflowName
             = type_workflow; // your workflow name
	if(type_workflow == "activiti$activitiAdhoc"){
		wflow.parameters["bpm:assignee"]
                        = personassignee;
	}else{
		wflow.parameters["bpm:assignees"]
	     //		= personassignee;
		//= [people.getPerson("sjeandroz")];
		= array_users_object

		wflow.parameters["wf:requiredApprovePercent"]
             		= 100;
	}
	wflow.parameters["bpm:workflowDescription"]
             = description;

	if(DueDate != "null"){
		wflow.parameters["bpm:workflowDueDate"]
	     		= DueDate;
	}
	wflow.execute(node);
}

//var myworkflow = initWorkflow(args.reference);
//W.move();
model.property = return_value;
