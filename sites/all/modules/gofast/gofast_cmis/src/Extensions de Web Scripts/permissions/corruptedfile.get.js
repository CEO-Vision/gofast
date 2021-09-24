


//var document = TEstReed3j.odt(workspace://SpacesStore/47caa347-4a39-46db-8a46-7305d48d59d4)

var NodeContent = document.getContent();

logger.log(NodeContent.length());

if (NodeContent.length() === 0) {
	// doc is corrupted
	return true;
} else {
		// doc is not corrupted
	return false;
}

