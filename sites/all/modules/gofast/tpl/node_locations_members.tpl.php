<?php


?>
<div id="popup-member-list-count"><b><?php print count($members_name); ?></b> <?php print t(' users members of the space(s)',array(),array('context'=>'gofast')); ?></b></div>
<div id="popup-member-list-filter" class="input-group input-group-sm">
    <span class="input-group-addon" id="sizing-addon3"><span class="icon glyphicon glyphicon-search" aria-hidden="true"></span></span>
    <input id="popup-member-list-filter-search-input" type="text" class="form-control" placeholder="<?php print t('Filter',array(),array('context'=>'gofast')); ?>" aria-describedby="sizing-addon3" />
    <button title="<?php print t('Refresh',array(),array('context'=>'gofast')); ?>" id="popup-member-list-filter-filter-refresh" type="button" class="btn btn-default btn-sm dropdown-toggle no-footer"><i class="fa fa-refresh" aria-hidden="true"></i></button>
</div>
<ul id="popup-member-list">

 <?php
 foreach($members_name as $uid => $name) {
        if ($uid == 1) {
            continue;
        }
        $member= $members[$uid];
        if (in_array(GOFAST_OG_ROLE_ADMIN,$members_roles[$uid])){
            $role=GOFAST_OG_ROLE_ADMIN;
        }
        elseif (in_array(GOFAST_OG_ROLE_STANDARD,$members_roles[$uid])){
            $role=GOFAST_OG_ROLE_STANDARD;
        }
        else{
            $role=GOFAST_OG_ROLE_READ_ONLY;
        }

        $icon = '';
        if(!is_numeric($member->member_type)){
            $p = explode('_', $member->member_type);
            if(count($p)>1){
                $list = entity_load_single('userlist',$p[0]);
                $title = htmlentities(check_plain($list->name));
                $link = '<a href="/node/' . $list->nid . '">' . $list->name . "</a>";
                $picture = '<div class="symbol symbol-30 flex-shrink-0">
                    <span class="symbol-label"><i class="fas fa-users"></i></span>
                </div>';
            }
        }

        $picture = theme('user_picture',
            array(
                'account' => $member,
                'dimensions' => '30',
                'popup' => FALSE
            )
        );
         
        if (strlen($title) > 0) {
            $picture = preg_replace("/(.*title=\")(.*)(\".*)/", "$1" . $title . "$3", $picture);
        }

        $link = l($name,'user/' . $member->uid);
        ?>
         <li class="d-flex">
             <div class="d-flex">
                <span class="popup-member-list-picture"><?php print $picture; ?></span>
                <span class="popup-member-list-name"><?php print $link ; ?></span>
             </div>
            <span class="popup-member-list-role"><?php print ucfirst(t($role,array(),array('context'=>'gofast'))); ?></span>
            <span class="popup-member-icon-userlist"><?php print $icon; ?></span>

        </li>
        <?php
    }
 ?>
 </ul>
