<!--begin::Breadcrumb-->
<ul class="breadcrumb flex-nowrap breadcrumb-transparent gofast breadcrumb-gofast font-weight-bold p-0 my-2 font-size-sm" id="subheader-breadcrumbs">
  <?php foreach ($breadcrumb as $crumbs) : ?>
    <li class="breadcrumb-item">
      <?php print $crumbs; ?>
    </li>
    <?php endforeach; ?>
  <?php if(!empty($userlist_final_role)) : ?>
    <?php print '<span class="ml-2"> (' . $userlist_final_role . ') </span>'; ?>
  <?php endif; ?>
  <?php if(!empty($user_final_role)) : ?>
    <?php print '<span class="ml-2"> (' . $user_final_role . ') </span>'; ?>
  <?php endif; ?>
</ul>
<!--end::Breadcrumb-->
