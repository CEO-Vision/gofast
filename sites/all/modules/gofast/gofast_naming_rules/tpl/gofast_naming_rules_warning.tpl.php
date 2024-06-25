<div>
    <span id="gofast_naming_rules_warning" class="label label-xl label-light-warning label-inline w-100 h-100 mb-4 font-size-h5 d-none"><?= $message ?></span>
    <script>
        jQuery(document).ready(function() {
            clearInterval(Gofast.namingRules.intervals.waitForElement);
            Gofast.namingRules.intervals.waitForElement = setInterval(() => {
                if (!$("<?= $selector ?>").length) {
                    return;
                }
                clearInterval(Gofast.namingRules.intervals.waitForElement);
                <?= $callback ?>("<?= $selector ?>");
            }, 100);
        });
    </script>
</div>