      <i class="fa fa-question-circle" data-toggle="tooltip"
        data-placement="right" data-html="true" title="
          <ul>
          <?php foreach ($locations as $location) : ?>
            <?php if(!empty($location['value'])): ?>
              <?php $location_value = $location['value']; ?>
            <?php else: ?>
              <?php $location_value = $location; ?>
            <?php endif; ?>
            <li><?php print $location_value ?></li>
          <?php endforeach; ?>
          </ul>
        ">
      </i>
