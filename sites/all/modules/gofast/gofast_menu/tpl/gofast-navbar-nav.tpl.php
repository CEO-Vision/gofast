<!-- START gofast-navbar-nav.tpl.php -->
<ul class="navbar-nav">
    <?php foreach ($links as $link): ?>
    <?php echo theme('gofast_navbar_item' , ['link' => $link]); ?>
    <?php endforeach ?>
</ul>
<!-- END gofast-navbar-nav.tpl.php -->