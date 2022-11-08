var KTLayoutHeaderTopbarCustom = function() {
    // Private properties
	var _menuElement;
    var _menuObject;

    // Private functions
	var _init = function() {

		_menuObject = new KTMenu(_menuElement, {
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
	}

    // Public methods
	return {
        init: function(menuId) {
			_menuElement = KTUtil.getById(menuId);
            if (!_menuElement) {
                return;
            }

            // Initialize menu
            _init();
		},

		getMenuElement: function() {
			return _menuElement;
		},

        getMenu: function() {
			return _menuObject;
		},

		pauseDropdownHover: function(time) {
			if (_menuObject) {
				_menuObject.pauseDropdownHover(time);
			}
		}

	};
}();

jQuery(document).ready(function() {
    KTLayoutHeaderTopbarCustom.init('gf-topbar-menu');
});