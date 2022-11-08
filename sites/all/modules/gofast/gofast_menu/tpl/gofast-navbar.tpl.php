<!-- START gofast-navbar.tpl.php -->
<nav class="navbar navbar-expand-md sticky-top bg-white shadow-sm d-flex justify-content-between m-0">
    <?php echo theme('gofast_navbar_nav', ['links' => $rigthLinks]) ?>
    <div class="d-flex">
        <form class="form-inline mt-2 mt-md-0">
            <div class="input-group input-group-sm">
                <input type="text" class="form-control" aria-label="Text input with dropdown button">
                <div class="input-group-append dropdown no-arrow">
                    <a class="btn btn-primary dropdown-toggle" href="" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
                    <i class="fas fa-search"></i>
                    </a>
                    <?php echo theme('gofast_dropdown_menu') ?>
                </div>
            </div>
        </form>
        <?php echo theme('gofast_navbar_nav', ['links' => $leftLinks] ) ?>
    </div>
</nav>
<!-- END gofast-navbar.tpl.php -->