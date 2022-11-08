<ul>
  <?php foreach ($documents as $key => $document) : ?>
    <?php $nid = $document->nid; ?>
    <?php $node_ref = $key; ?>
    <?php $locations = gofast_cmis_webservice_get_node_parents($node_ref); ?>
    <li>
      <?php print theme('gofast_node_icon_format', array('node' => node_load($nid)))  ?>
      <?php print node_load($nid)->title; ?>
      <?php if (count($locations) > 1) : ?>
        <?php print theme('gofast_tooltip_emplacements', array('locations' => $locations)); ?>
    <?php endif; ?>
    </li>
  <?php endforeach; ?>
</ul>
