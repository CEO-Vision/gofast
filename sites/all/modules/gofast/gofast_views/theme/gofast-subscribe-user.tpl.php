<span class="gofast_subscribe_user" style='width:100%;'>
    <?php
      $uid = $user->uid;
      //We print the subscribe user flag
      print str_replace('>', '> ', flag_create_link('subscribe_user', $uid));
    ?>
</span>