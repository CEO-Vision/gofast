<div class="GofastUserlistProfile mainContent">
    <div class="GofastUserProfile__info">
      <?php echo theme("gofast_userlist_profile_personal_info", ['description' => $description, 'symbol' => $symbol, 'userlist_name' => $userlist_name, 'status' => $status]); ?>
    </div>
    <div class="GofastUserlistProfile__detail">
      <?php if($status) :?>
        <?php echo theme("gofast_userlist_profile_info", ['node' => $node]); ?>
      <?php else:?>
        <div>
          <div class="card card-custom card-stretch GofastNodeOg__container p-3">
            <div class="card-body d-flex flex-column">
              <h2>
                <center>
                  <span class='fa fa-trash-o'></span>
                  <?php echo t("This userlist is deleted.", array(), array("context" => "gofast:gofast_userlist")); ?>
                </center>
              </h2>
            </div>
          </div>
        </div>
      <?php endif;?>
    </div>

  </div>


