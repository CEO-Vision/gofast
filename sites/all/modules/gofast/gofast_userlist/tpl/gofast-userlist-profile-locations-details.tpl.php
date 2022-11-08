<div id='gf_userlist_groups' data-profileUlid="<?php echo $ulid; ?>">
  <!-- Placeholder : Load groups templates ! -->
  <div class="loader-blog"></div>
  <script type="text/javascript">
    var wait_gofast_profile_spaces = setInterval(function() {
      if (typeof Gofast === "object" && typeof Gofast.load_userlist_profile_spaces === "function" && jQuery('#gf_userlist_groups').length === 1) {
        Gofast.load_userlist_profile_spaces();
        clearInterval(wait_gofast_profile_spaces);
      }
    }, 500);
  </script>
</div>
