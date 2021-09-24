
//search for the folder node using lucene search
var node = search.findNode(args.reference);
var render = "";
var descendants = "";
getdescendants(node);


function getdescendants(node)
{
        for each (n in node.children)
        {
                if(n.isDocument)
                {
			  if(descendants == ""){
                                descendants=n.nodeRef;
                        }else{
                                descendants=descendants+";"+n.nodeRef;
                        }

                }
                if(n.isContainer){
                        getdescendants(n);
		}
        }
}


render = descendants;
//render = utils.toISO8601(history[1].createdDate);
model.myStatus = render;


