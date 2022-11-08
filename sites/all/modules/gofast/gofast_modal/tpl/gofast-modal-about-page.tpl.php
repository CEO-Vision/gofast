<?php
global $user;
$is_admin = array_intersect([
  'administrator',
  'business administrator',
], $user->roles); ?>
<div class="d-flex justify-content-center">
    <ul class="list-group w-80 rounded border border-dark">
        <?php foreach ($items as $item) : ?>
            <li class="list-group-item d-flex justify-content-between align-items-center <?= strlen($item[1]) == 0 && strpos($item[0], "following") >= 0 ? "list-group-item-primary" : "" ?> <?= strlen($item[1]) == 0 && !strpos($item[0], "following") ? "list-group-item-warning" : "" ?>"><?= theme("gofast_modal_about_page_item", ["item" => $item, 'is_admin' => $is_admin]) ?></li>
        <?php endforeach; ?>
    </ul>
</div>