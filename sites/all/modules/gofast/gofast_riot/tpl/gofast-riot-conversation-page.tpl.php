<?php global $base_url; ?>

<style>
    .main-container{
        width: 100% !important;
        padding-left: 25px;
        padding-right: 25px;
    }

    aside, footer, .breadcrumb-gofast {
      display: none !important;
    }
    
    .block-gofast-riot {
      visibility: hidden !important;
    }
    
</style>

<iframe id="IframeRiot"
        class="gofast-iframe-riot"
        title="Frame Riot"
        src="<?php print $base_url; ?>/sites/all/libraries/riot/index.html?d=<?php print date('dm'); ?>">
</iframe>

<script>
    jQuery(document).ready(function() {
        function riotIframeHeightSize(){
            // Get width and height of the window excluding scrollbars
            var h = document.documentElement.clientHeight;
            // add height to frame
            document.querySelector('#IframeRiot').setAttribute('height', (h-100) + 'px'); 
        }
        // Attaching the event listener function to window's resize event
        window.addEventListener("resize", riotIframeHeightSize);
        riotIframeHeightSize();
        setTimeout(function(){
            jQuery("#gofast_over_content").removeClass("col-lg-8");
            jQuery("#gofast_over_content").addClass("col-lg-12");
            Gofast.Riot.initFetchEvent('#IframeRiot');
        }, 200);
    });
</script>

