<!-- Begin: gofast-cart-modal-cart-table-content -->

<?php foreach($items as $item): ?>
    <tr class="GofastCart__tableRow">
        <td class="min-w-200px max-w-300px w-300px">
            <a href="<?php print $item['href']; ?>" class="GofastCart__rowTitle" title="<?php print $item['name']; ?>"><?php print $item['title']; ?></span>
        </td>
        <td class="max-w-400px min-w-200px w-400px text-truncate GofastCart__rowLocation">
            <span class="" title=""><?php print $item['locations']; ?></span>
        </td>
        <td class="text-truncate">
            <?php print $item['date']; ?>
        </td>
        <td class="GofastCart__flag">
            <?php print $item['actions']; ?>
        </td>
    </tr>
<?php endforeach; ?>



<!-- End: gofast-cart-modal-cart-table-content -->
