<section id="landscape-backdrop">
    <div id="landscape-warning" class="d-flex flex-column align-items-center">
        <h3><?= t("Please switch your tablet in landscape mode", [], ["context" => "gofast:gofast_mobile"]) ?></h3>
        <img src="<?= $base_url  ?>/sites/all/modules/gofast/img/landscape.png" alt="<?=  t("Tablet in landscape mode", [], ["context" => "gofast:gofast_mobile"]) ?>" id="landscape-image">
    </div>
</section>

<style>
    /* Semi-transparent element preventing interactions with the page */
    #landscape-backdrop {
        display: none;
        align-items: center;
        justify-content: center;
        position: fixed;
        top: 0;
        left: 0;
        width: 100%;
        height: 100%;
        background-color: rgb(0, 0, 0);
        z-index: 9999;
    }

    #landscape-warning {
	    background-color: white;
	    border-radius: 10px;
	    padding: 1rem;
    }

    @media screen and (orientation: portrait) {
        #landscape-backdrop {
            display: flex;
        }
    }

    #landscape-image {
        width: 100px;
    }
</style>