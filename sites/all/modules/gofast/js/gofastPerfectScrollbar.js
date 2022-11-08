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

            console.log('ps:', 'init');

        }
    };

})(jQuery, Gofast, Drupal);

