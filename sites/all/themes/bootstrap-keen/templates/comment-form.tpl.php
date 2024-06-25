<?php
if($form['#node_has_extranet_location']): ?>
<div class='alert alert-custom alert-notice alert-light-warning fade show' role='alert'>
    <div class='alert-icon'><i class='flaticon-warning'></i></div>
    <div class='alert-text m-0'>
      <?= t(
          'Comments on this file are visible to externs because this file is accessible from Extranet',
          [],
          ['context' => 'gofast'],
        ); ?>
    </div>
</div>
<?php endif; ?>

<div class="show">
  <?php
  // We need a temporary variable since render needs to take a reference
  $form_without_current_theme = [
    ...$form,
    // filter out current theme from themes to prevent circular dependency/infinite recursion
    '#theme' => array_filter(
      $form['#theme'],
      fn ($theme) => $theme !== $theme_hook_original,
    ),
  ];

  echo render($form_without_current_theme);
  ?>
</div>
