/**
 * @file
 *  Provides GoFast Essential front-end functionalities.
 *
 *  This file is part of the Gofast main library and is loaded on every page.
 *  Do not insert code that has to be run on specific page.
 */
(function ($, Gofast, Drupal) {
  Gofast.auditAction={
      //function for the profile page
    download:function(nid){
	if(nid.length>0){
	    $.post(location.origin + "/gofast/audit/download", {node_id : nid}).done(function(data) {
		console.log('test');
	    });
	}
    }
  };
})(jQuery, Gofast, Drupal);

