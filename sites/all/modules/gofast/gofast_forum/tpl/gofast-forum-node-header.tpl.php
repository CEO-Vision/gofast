<div class="card card-custom card-stretch" id="<?php echo "forum-". $node->nid ?>">
    <div class="card-header forum-header d-flex align-items-start pl-2">
        <div class="card-title">
            
            <div class="forum-header-user-icon mr-5">
                <img title="<?php echo $node->name ?>" class="w-35px" alt="Pic" src="<?php echo $node->creator_picture ?>">
            </div>
            
            <!-- BEGIN TITLE --->
            <div class="mt-2">
                <span id="forum-header-forum-title" class="font-size-h4">
                    <?php print $node->title; ?>
                </span>
            </div>
            <!-- END TITLE --->
            
        </div>   
        
        <div class="pl-2 pt-2">
            <span class="text-muted"><?php echo $node->creation_date ?></span>
        </div>
        
    </div>
    
    <div class="card-body">
        
        <!-- BEGIN TEXT BODY --->
        <div class="forum-content">
            <?php
                print $node->body[LANGUAGE_NONE][0]['value'];
            ?>
        </div>
        <!-- END TEXT BODY --->
        
    </div>
    
    <div class="card-footer justify-content-between p-5">      
        <!-- BEGIN LINKS --->
        <div class="forum-actions m-0">
            <?php print render($links); ?>
        </div>
        <!-- END TEXT LINKS --->
    </div>
</div>
