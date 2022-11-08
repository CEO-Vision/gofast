<div class="GofastUserlistProfile mainContent">
    <div class="GofastUserProfile__info">
      <?php echo theme("gofast_userlist_profile_personal_info", ['description' => $description, 'symbol' => $symbol, 'userlist_name' => $userlist_name]); ?>
    </div>
    <div class="GofastUserlistProfile__detail">
      <?php echo theme("gofast_userlist_profile_info", ['node' => $node]); ?>
    </div>

  </div>


