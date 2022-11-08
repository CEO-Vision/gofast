
//search for the folder node using lucene search
var node = search.findNode(args.reference);
var render = "";
var totalsize = 0;
var totalnumberdoc = 0;
var totalnumberfolders = 0; 
var includehistory = args.history;
calculatesize(node);


function calculatesize(node)
{
        for each (n in node.children)
        {
                if(n.isDocument)
                {
			if(includehistory == 1){
				history = n.versionHistory;
				for each (h in history)
        			{
					version = n.getVersion(h.label);
					totalsize =  totalsize + h.node.size;
				}
			}
			totalnumberdoc = totalnumberdoc + 1;
			totalsize = totalsize + n.size;
                }
		 var last_character = n.properties["cm:name"].charAt(n.properties["cm:name"].length - 1)
                  if(n.isContainer && last_character !== "_"){
			totalnumberfolders = totalnumberfolders + 1;
                        calculatesize(n);
		 }
		
        }
}
//render = debugstringsize;
render = totalsize+";"+totalnumberdoc+";"+totalnumberfolders;
//render = utils.toISO8601(history[1].createdDate);
model.myStatus = render;


