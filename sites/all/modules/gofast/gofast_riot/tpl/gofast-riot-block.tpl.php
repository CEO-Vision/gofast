<div id="conteneurIframe">
    <div class="gofastRiotReload d-none"><a href="#" class="btn btn-primary btn-lg"><img class="d-inline-block mr-2" src="/sites/all/themes/bootstrap-keen/img/element_logo.svg"><?= t("Reload Element") ?></a></div>
    <iframe id="IframeRiotBloc" title="Frame Riot" src="<?= $src ?>"></iframe>
    <div id="animateRiot"> <i class="fa <?php gofast_essential_is_essential() ? print "w-100 fa-2x" : "" ?> fa-comment"></i><?= gofast_essential_is_essential() ? '<i class="w-100 fa fa-2x fa-chevron-left"></i>' : "" ?></div>
    <div id="blocConnexionRiot">
        <p>
        <div class="spinner spinner-center spinner-primary spinner-lg"></div>
        </p>
    </div>
</div>
