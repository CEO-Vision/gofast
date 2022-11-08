var document = search.findNode(args.reference);
check_folder(document);

function check_folder(node) {
    for each(n in node.children) {
        if (n.isDocument) {
            var ext = n.name.substr(n.name.lastIndexOf('.') + 1);
            if (ext != "doc" && ext != "docx" && ext != "xls" && ext != "xlsx" && ext != "ppt" && ext != "pptx" && ext != "pdf" && ext != "txt") {
                var newname = "null";
                if (n.mimetype == "application/msword") {
                    var newname = n.name + ".doc";
                } else if (n.mimetype == "application/vnd.openxmlformats-officedocument.wordprocessingml.document") {
                    var newname = n.name + ".docx";
                } else if (n.mimetype == "application/pdf") {
                    var newname = n.name + ".pdf";
                }else if (n.mimetype == "application/vnd.ms-excel") {
                    var newname = n.name + ".xls";
                } else if (n.mimetype == "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet") {
                    var newname = n.name + ".xlsx";
                } else if (n.mimetype == "application/vnd.ms-powerpoint") {
                    var newname = n.name + ".ppt";
                }else if (n.mimetype == "application/vnd.openxmlformats-officedocument.presentationml.presentation") {
                    var newname = n.name + ".pptx";
                }

                if (newname !== "null") {
                    logger.log(newname);
                    n.name = newname;
                    //n.save();
                }

                /*logger.log(n.name)
				logger.log(ext);
				logger.log(n.mimetype);
				logger.log(newname);*/
            }

        } else if (n.isContainer) {

            check_folder(n);
        }

    }
}

model.myStatus = "";
