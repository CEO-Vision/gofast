
<a class="btn gf-add-rssfeed" ><span class="fa fa-plus"></span>  <?php print t('Add a feed', array(), array('context' => 'gofast:gofast_rssfeed')) ?></a>     
<?php 
    $query = db_query('SELECT title, url, fid FROM aggregator_feed');
    $list_rssfeed = $query->fetchAll();
    $rssfeed_id = -1;
?>
<table class="table table-striped">
    <?php foreach ( $list_rssfeed as $rssfeed ): $rssfeed_id++?>
    <tr class="gf-rssfeed-<?php echo $rssfeed_id; ?>">
      <td class="gf-fid_rssfeed" style="display: none;">
        <?php print $rssfeed->fid; ?>
      </td>
      <td class="gf-title_rssfeed">
        <?php print $rssfeed->title; ?>
      </td>
      <td class="gf-url_rssfeed">
          <a href="<?php print $rssfeed->url; ?>"><?php print $rssfeed->url; ?></a>
      </td>
      <td>
          <a class="btn fa fa-pencil gf-edit-rssfeed-<?php echo $rssfeed_id; ?>"></a>
      </td>
      <td>
        <a class="btn fa fa-times gf-delete-rssfeed-<?php echo $rssfeed_id; ?>"></a>
      </td>
    </tr>
    <?php endforeach; ?>
</table>

<script type="text/javascript" >
    Gofast.addRssFeed = function(){
        var title = jQuery('#title_rssfeed').val();
        var link = jQuery('#url_rssfeed').val();

        Gofast.closeModal();
        Gofast.addLoading();

        jQuery.post(location.origin + "/rssfeed/add", {rssfeed_title : title, url : link}, function(response){
            Gofast.removeLoading();
            
            if(response === "true") {
                Gofast.toast(Drupal.t("The rss feed has been added", {}, {context: 'gofast:gofast_rssfeed'}), "success");
                jQuery('a[href="#edit-rssfeeds"]').remove('processed')
                Gofast.loadSettingsTab('edit-rssfeed');
                jQuery('a[href="#edit-rssfeeds"]').addClass('processed');
            } else {
                Gofast.toast(Drupal.t("The feed URL is invalid. Please enter a fully-qualified URL, such as<br /><br /><blockquote>http://fr.news.yahoo.com/?format=rss</blockquote>", {}, {context: 'gofast:gofast_rssfeed'}), "warning");
            }
        }, "text");
    };
  
    Gofast.editRssFeed = function(fid){
        var title = jQuery('#title_rssfeed').val();
        var link = jQuery('#url_rssfeed').val();
        
        Gofast.closeModal();
        Gofast.addLoading();

        jQuery.post(location.origin + "/rssfeed/edit", {rssfeed_title : title, url : link, rssfeed_fid : fid}, function(response){
            Gofast.removeLoading();
            if(response === "true") {
                Gofast.toast(Drupal.t("The rss feed has been edited", {}, {context: 'gofast:gofast_rssfeed'}), "success");
                jQuery('a[href="#edit-rssfeeds"]').remove('processed')
                Gofast.loadSettingsTab('edit-rssfeed');
                jQuery('a[href="#edit-rssfeeds"]').addClass('processed');
            } else {
                Gofast.toast(Drupal.t("The feed URL is invalid. Please enter a fully-qualified URL, such as<br /><br /><blockquote>http://fr.news.yahoo.com/?format=rss</blockquote>", {}, {context: 'gofast:gofast_rssfeed'}), "warning");
            }
        }, "text");
    };
    
    Gofast.deleteRssFeed = function(fid){
        Gofast.closeModal();
        Gofast.addLoading();

        jQuery.post(location.origin + "/rssfeed/delete", {rssfeed_fid : fid}, function(response){
            Gofast.removeLoading();
            if(response === "true") {
                Gofast.toast(Drupal.t("The rss feed has been deleted", {}, {context: 'gofast:gofast_rssfeed'}), "success");
                jQuery('a[href="#edit-rssfeeds"]').remove('processed')
                Gofast.loadSettingsTab('edit-rssfeed');
                jQuery('a[href="#edit-rssfeeds"]').addClass('processed');
            } else {
                Gofast.toast(Drupal.t("The rss feed has not been deleted", {}, {context: 'gofast:gofast_rssfeed'}), "warning");
            }
        }, "text");
    };
    
    jQuery(document).ready(function(){
        jQuery('a.gf-add-rssfeed').bind('click', function(){
            displayModal("add");
        });
        
        jQuery('.fa-pencil').bind('click', function(){
            var title = jQuery(this).parent().parent().find('.gf-title_rssfeed').text();
            var url = jQuery(this).parent().parent().find('.gf-url_rssfeed').text();
            var fid = jQuery(this).parent().parent().find('.gf-fid_rssfeed').text();
            title = jQuery.trim(title);
            url = jQuery.trim(url);
            fid = jQuery.trim(fid);
            displayModal("edit", title, url, fid);
        });
        
        jQuery(".fa-times").bind('click', function(){
            var title = jQuery(this).parent().parent().find('.gf-title_rssfeed').text();
            var fid = jQuery(this).parent().parent().find('.gf-fid_rssfeed').text();
            title = jQuery.trim(title);
            fid = jQuery.trim(fid);
            displayModal("delete", title, null, fid);
        });
        
        function displayModal(titleModal, title, url, fid) {
            var modal_html = "<label for='title_rssfeed'><?php echo t("Title *", array(), array('context' => 'gofast:gofast_rssfeed')) ?></label><br />";
            modal_html += "<input type='text' name='title_rssfeed' id='title_rssfeed' value='' class='form-control'><br />";
            modal_html += "<?php echo t("The name of the feed (or the name of the website providing the feed).", array(), array('context' => 'gofast:gofast_rssfeed')) ?><br />";
            modal_html += "<br /><label for=''>URL *</label><br />";
            modal_html += "<input type='text' name='url_rssfeed' id='url_rssfeed' value='' class='form-control'><br />";
            modal_html += "<?php echo t("The fully-qualified URL of the feed.", array(), array('context' => 'gofast:gofast_rssfeed')) ?>";
            modal_html += "<br /><br />";
            
            if (titleModal === "add") {
                modal_html += "<button class='btn btn-success btn-sm icon-before' type='submit' onclick='Gofast.addRssFeed()'><i class='fa fa-play'></i> <?php echo t("Add RSS Feed", array(), array('context' => 'gofast:gofast_rssfeed')); ?></button>";
                Gofast.modal(modal_html, "<?php echo t("Add RSS Feed", array(), array('context' => 'gofast:gofast_rssfeed')) ?>");
            } else if (titleModal === "edit") {
                modal_html += "<button class='btn btn-success btn-sm icon-before' type='submit' onclick='Gofast.editRssFeed(\"" + fid + "\")'><i class='fa fa-play'></i> <?php echo t("Edit RSS Feed", array(), array('context' => 'gofast:gofast_rssfeed')); ?></button>";
                Gofast.modal(modal_html, "<?php echo t("Edit RSS Feed", array(), array('context' => 'gofast:gofast_rssfeed')) ?>");
                jQuery('#title_rssfeed').val(title);
                jQuery('#url_rssfeed').val(url);
            }  else if (titleModal === "delete") {
                var modal_html_confirm = "<?php echo t("Are you sure you want to delete this rss feed ? This destructive action cannot be undone.", array(), array('context' => 'gofast:gofast_rssfeed')) ?>";
                modal_html_confirm += "<br /><br />";
                modal_html_confirm += "<button class='btn btn-danger btn-sm icon-before' type='submit' onclick='Gofast.deleteRssFeed(\"" + fid + "\")'><i class='fa fa-trash'></i> <?php echo t("Delete", array(), array('context' => 'gofast:gofast_rssfeed')); ?></button>";
                Gofast.modal(modal_html_confirm, "<?php echo t("Delete RSS Feed", array(), array('context' => 'gofast:gofast_rssfeed')) ?>");
            }
        }
    });
</script>