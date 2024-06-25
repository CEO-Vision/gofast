<?php $has_children = count((array) $book_element->children) > 0; ?>
<?php if ($depth == 0) : ?>
<table class="book_element-explorer-element-table w-100" id="<?= random_int(0, 999999) ?>">
<?php endif; ?>
    <!-- BOOK -->
    <tr data-nid="<?= $book_element->nid ?>" data-depth="<?= $depth ?>" id="<?= $book_element->id ?>" data-name="<?= $book_element->name ?>" data-pid="<?= $book_element->pid ?>" class="wiki-tree-widget-item book-explorer-element book-explorer-element-<?php echo $depth == 0 ? 'visible' : 'collapsed'; ?>">
        <td style="width: <?php echo $depth * 1.5; ?>em;">
        </td>
        <td class="book-explorer-element-parent" style="display: none;">
            <?= $book_element->pid ?>
        </td>
        <td class="book-explorer-element-seechild">
            <?php echo $has_children ? '<i class="book-explorer-element-open ki ki-bold-arrow-next"></i>' : ''; ?>
        </td>
        <td class="book-explorer-element-icon">
            <i class="<?php echo $has_children || $depth == 0 ? "fas fa-book" : "far fa-ballot"; ?>"></i>
        </td>
        <td class="book-explorer-element-name w-100 d-flex align-items-center justify-content-between"<?= $has_links ? ' title="' . $book_element->description . '" data-placement="top" data-toggle="tooltip" data-trigger="hover"' : "" ?>>
            <a class="wiki-tree-widget-item-name item-name" href="<?= $has_links ? $book_element->link_path : "" ?>">
                <?= is_numeric($book_element->weight) ? "<strong>W"  . str_pad($book_element->weight, 3, "0", STR_PAD_LEFT) . "</strong> - " . $book_element->name : $book_element->name?>
            </a>
            <?php if (isset($book_element->canUpdate) && $book_element->canUpdate && $has_links) : ?>
                <div class="d-flex align-items-center mr-2 <?= ($book_element->edit_link) ? 'mx-1' : 'mx-2' ?>">
                    <a href="/node/add/article?target_location=<?= $book_element->nid ?>"><i class="fas fa-plus text-muted cursor-pointer"></i></a>
                    <?php if ($book_element->edit_link) : ?>
                        <a href="<?= $book_element->edit_link ?>" class="<?= str_contains($book_element->edit_link, "modal") ? "ctools-use-modal" : "" ?>"><i class="fas fa-pen text-muted cursor-pointer"></i></a>
                    <?php endif; ?>
                </div>
            <?php endif; ?>
        </td>
    </tr>
    <!-- ARTICLES AND NESTED BOOKS -->
    <?php
    // recursivity allows for rendering of nested wiki books as well as wiki articles
    if (count((array) $book_element->children) > 0) {
        $below_depth = $depth + 1;
        echo gofast_book_render_book_tree_widget_elements($book_element->children, $below_depth, $has_links);
    }
    ?>
<?php if ($depth == 0) : ?>
</table>
<?php endif; ?>