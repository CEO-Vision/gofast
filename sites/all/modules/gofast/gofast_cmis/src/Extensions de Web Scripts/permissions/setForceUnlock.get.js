
//search for the folder node using lucene search
var node = search.findNode(args.reference);
var working_copy_node = node.checkout();
working_copy_node.cancelCheckout();
model.myStatus = "done";


