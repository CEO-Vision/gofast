<div class="author-pane">
<!--  <div class="col-md-7">
    <?php 
//      if (($context instanceof stdClass) && isset($context->vud_comment_widget)) {
//        $vud_widget = $context->vud_comment_widget;
//        print $vud_widget;
//      }
//      print $avatar; 
    ?>
  </div>-->
  <div>
    <?php
      print $avatar; 
    ?>
    <a class="gofast_forum_username" href="/user/<?php print $id; ?>">
      <?php 
        print $displayname; 
      ?>
    </a>

    <div class="gofast_forum_user_title">
      <?php print $ldap['ldap_user_title']['value']; ?>
    </div>
    <div class="gofast_forum_user_department">
      <?php print $ldap['ldap_user_o']['value']; ?>
    </div>
    <div class="gofast_forum_user_score">
      <?php print $profile_score; ?>
    </div>
  </div>
  

</div>