(function ($, Gofast, Drupal) {
    
    'use strict';

    Drupal.behaviors.gofastPerfectScrollBarInit = {
        attach: function(context, settings){
            
            $('[data-scroll="true"]').each(function() {
                var el = $(this);
                return;
                KTUtil.scrollInit(this, {
                    mobileNativeScroll: true,
                    handleWindowResize: true,
                    rememberPosition: (el.data('remember-position') == 'true' ? true : false)
                });
            });

            const thead = $("#gofastSpaceMembersTable > table > thead"); 
            const tbody = $("#gofastSpaceMembersTable > table > tbody");
            thead.scroll(function() {
            tbody.scrollLeft(thead.scrollLeft());
            });
            tbody.scroll(function() {
                thead.scrollLeft(tbody.scrollLeft());
            });
        }
    };

})(jQuery, Gofast, Drupal);

