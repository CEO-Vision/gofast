jQuery(document).ready(function() {
	const _menuElement = KTUtil.getById("gf-topbar-menu");
    window.GFTopbarMenu = new KTMenu(_menuElement, {
		submenu: {
			desktop: 'dropdown',
			tablet: 'dropdown',
			mobile: 'dropdown'
		},
		accordion: {
			slideSpeed: 200, // accordion toggle slide speed in milliseconds
			expandAll: false // allow having multiple expanded accordions in the menu
		}
	});
});