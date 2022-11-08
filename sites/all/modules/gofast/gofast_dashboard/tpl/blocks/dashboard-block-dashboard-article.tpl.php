<div id="gofastDashboardArticleContent"><?= $dashboard_article->body[LANGUAGE_NONE][0]['value'] ?: t("No content has been filled for the custom block", array(), array("context" => "gofast:gofast_dashboard")) ?></div>

<script>
    jQuery(document).ready(function() {
        jQuery("#gofastDashboardArticleTitle").html("<?= $dashboard_article->title ?>");
        <?php if($is_business_admin) : ?>
            const dashboardTitleElement = jQuery("#gofastDashboardArticleTitle")[0];
            const dashboardTitleContent = jQuery("#gofastDashboardArticleTitle").html();
            jQuery("#gofastDashboardArticleTitle").html("");
            GofastEditableInput(dashboardTitleElement, dashboardTitleContent, "text", {
                save: async (newContent) => {
                _gofastPostSimulator({
                    pk: <?= $dashboard_article->nid ?>,
                    name: "title",
                    value: newContent,
                });
                },
                isEditable: true,
                showConfirmationButtons: true,
            });
            const dashboardArticleElement = jQuery("#gofastDashboardArticleContent")[0];
            const dashboardArticleContent = jQuery("#gofastDashboardArticleContent").html();
            jQuery("#gofastDashboardArticleContent").html("");
            GofastEditableInput(dashboardArticleElement, dashboardArticleContent, "ckeditor-classic", {
                save: async (newContent) => {
                _gofastPostSimulator({
                    pk: <?= $dashboard_article->nid ?>,
                    name: "body",
                    value: newContent,
                });
                },
                isEditable: true,
            });
        <?php endif; ?>
    });
</script>