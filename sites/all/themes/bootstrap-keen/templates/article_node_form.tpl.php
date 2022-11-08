<div class="card card-custom GofastForm__CardContainer">
    <div class="card-body">
        <div class="GofastForm__Field GofastForm__Field--title">
            <?php echo render($form['wrapper']['title']); ?>
        </div>
        <div class="GofastForm__Field GofastForm__Field--language">
            <?php echo render($form['wrapper']['language']); ?>
        </div>
        <div class="GofastForm__Field GofastForm__Field--content">
            <?php echo render($form['body']); ?>
        </div>
        <div class="GofastForm__Field GofastForm__Field--book">
            <?php echo render($form['book']); ?>
        </div>
        <div class="GofastForm__Field GofastForm__Field--broadcast">
            <?php echo render($form['og_group_content_ref']); ?>
            <?php if (isset($form['fieldset_broadcast_og'])) : ?>
                <?php echo render($form['fieldset_broadcast_og']); ?>
            <?php endif ?>
        </div>
    </div>
    <div class='card-footer pb-0 pt-3 d-flex GofastAddForms__buttons'>
        <?php echo render($form['actions']); ?>
        <?php drupal_process_attached($form); ?>
        <div class="d-none"><?php echo drupal_render_children($form); ?></div>
    </div>
</div>

<script>
    // we make 100% sure the ckeditor is correctly triggered
    Drupal.attachBehaviors();

    function handleArticleTree() {
        const articleEmplacements = Object.keys(<?= json_encode($form[GOFAST_CMIS_LOCATIONS_FIELD][LANGUAGE_NONE]['#default_value']) ?>);
        for (const articleEmplacement of articleEmplacements) {
            Gofast.expandTargetLinkNode(articleEmplacement.replace("/Wikis", "").replaceAll("/_", "/").replace("/Sites", ""));
        }
    }

    jQuery(document).ready(function() {
        const articleTree = $.fn.zTree.getZTreeObj("ztree_component_content");
        const $pageSelector = $("select#edit-book-page-selector");
        // onCheck is already used to sync ztree with hidden inputs so we use another callback
        articleTree.setting.callback.beforeCheck = function(treeId, treeNode) {
            $pageSelector.html("");
                $pageSelector.append("<option value='start'>" + "W001 - " + "<?= trim(t("Insert at the start of the wiki", array(), array("context" => "gofast:gofast_book"))) ?>" + "</option>");
            const gid = treeNode.gid;
            let nid = 0;
            // if we're editing an existing node, we need to get the nid from the URL in order to preselect its location on the fly on zTree check, including the initial check
            if (window.location.pathname.split("/")[1] == "node" && window.location.pathname.split("/")[2] != "add") {
                nid = window.location.pathname.split("/")[2];
            }
            $.get("/space/book/" + gid).done(function(data) {
                if (!data) {
                    return;
                }
                $("#gofast_book_weights").val(JSON.stringify(data));
                let pageCounter = 1;
                for (const wikiItem of data) {
                    if(wikiItem.nid == nid) {
                        $previousElement = $pageSelector.find("option").last();
                        $previousElement.attr("selected", "");
                        continue;
                    }
                    pageCounter++;
                    const paddedPageCounter = String(pageCounter).padStart(3, "0");
                    $pageSelector.append(
                        '<option value="' + wikiItem.nid + '">' + "W" + paddedPageCounter + " - " + "<?= trim(t("Insert after the page", array(), array("context" => "gofast:gofast_book"))) ?>" + " " + wikiItem.title + '</option>'
                    );
                }
            });
        }
        const interval = setInterval(function() {
            if (!jQuery("#ztree_component_content > li").length) {
                return;
            }
            clearInterval(interval);
            handleArticleTree();
            // specific zTree conf for wiki articles
            articleTree.setting.gofast = {
                wiki: true
            };
            articleTree.refresh();
        }, 100);
    });
</script>