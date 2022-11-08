jQuery('.dropdown-menu a.dropdown-toggle').on('click', function(e) {
    if (!jQuery(this).next().hasClass('show')) {
      jQuery(this).parents('.dropdown-menu').first().find('.show').removeClass('show');
    }
    var jQuerysubMenu = jQuery(this).next('.dropdown-menu');
    jQuerysubMenu.toggleClass('show');
  
  
    jQuery(this).parents('li.nav-item.dropdown.show').on('hidden.bs.dropdown', function(e) {
      jQuery('.dropdown-submenu .show').removeClass('show');
    });
  
    return false;
  });