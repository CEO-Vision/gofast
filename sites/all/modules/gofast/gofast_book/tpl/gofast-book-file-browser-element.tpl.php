<?php $has_children = count($book_element->below) > 0; ?>
<?php if ($depth == 0) : ?>
<table class="book_element-explorer-element-table">
<?php endif; ?>
    <!-- BOOK -->
    <tr id="<?php echo $book_element->link->mlid; ?>" class="book-explorer-element book-explorer-element-<?php echo $depth == 0 ? 'visible' : 'collapsed'; ?>">
        <td style="width: <?php echo $depth * 1.5; ?>em;">
        </td>
        <td class="book-explorer-element-parent" style="display: none;">
            <?php echo $book_element->link->plid; ?>
        </td>
        <td class="book-explorer-element-seechild">
            <?php echo $has_children ? '<i id="" class="book-explorer-element-open ki ki-bold-arrow-next"></i>' : ''; ?>
        </td>
        <td class="book-explorer-element-icon">
            <i class="<?php echo $has_children || $depth == 0 ? "fas fa-book" : "far fa-ballot"; ?>"></i>
        </td>
        <td class="book-explorer-element-name" title="<?= $book_element->description ?>" data-toggle="tooltip" data-trigger="hover">
            <a class="item-name" href="/node/<?php echo $book_element->cover ?: $book_element->link->nid; ?>">
                <?php echo $book_element->link->link_title; ?>
            </a>
        </td>
    </tr>
    <!-- ARTICLES AND NESTED BOOKS -->
    <?php
    // recursivity will allow for rendering of nested wiki books as well as wiki articles
    if (count($book_element->below) > 0) {
        $below_depth = $depth + 1;
        echo gofast_book_render_books_elements($book_element->below, $below_depth);
    }
    ?>
<?php if ($depth == 0) : ?>
</table>
<?php endif; ?>