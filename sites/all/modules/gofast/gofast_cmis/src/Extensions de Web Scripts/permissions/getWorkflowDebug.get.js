//var workflowService = workflow.getWorkflowService();

var noderef = args.reference;
var properties = args.properties;
properties = JSON.parse(properties);
var op = args.op;
var taskId = properties.taskId;

var mytask = workflow.getTaskById(taskId);
var properties_task = mytask.properties;
properties_task["wf:reviewOutcome"] = "approuve mais pas trop";
//mytask.setProperties(properties_task);
// mytask.endTask("Approve");
var return_value = jsonUtils.toJSONString(mytask.getProperties());

model.property = return_value;
