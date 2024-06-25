<table class="forum-explorer-element-table">
    
    <?php foreach ($comments as $key => $comment) : ?>
    <tr id="<?php echo $comment->cid; ?>" data-nid=<?= $comment->nid ?> class="h-auto forum-explorer-element forum-explorer-element-<?php echo (($key==0) ? 'visible' : 'collapsed'); ?>" style="display: block;">
        <td style="width: <?php echo $comments[$key]->css_indent; ?>em;">
            
        </td>
        <td class="forum-explorer-element-parent" style="display:none;">
            <?php echo (isset($comments[$key]->parent_id) ? $comments[$key]->parent_id : ''); ?>
        </td>
        <td class="forum-explorer-element-seechild">  
            <?php echo ($key==count($comments)-1 || $comments[$key+1]->indent <= 0) ? '' : '<i id="" class="forum-explorer-element-open ki ki-bold-arrow-next"></i>'; ?>
        </td>
        <td class="forum-explorer-element-icon min-w-40px">
            <?php echo $comment->user_picture; ?>
        </td>
        <td class="forum-explorer-element-name">
            <a anchor="<?php echo $comment->link; ?>" class="scrolltoanchor item-name" href="/node/<?php echo $comment->nid . '#' . $comment->link; ?>">
                <?php echo $comment->subject; ?>
            </a>
        </td>
    </tr>
    <?php endforeach; ?>
    
</table>