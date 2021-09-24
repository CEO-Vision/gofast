<?php


?>
<div id="popup-member-list-count"><b><?php print count($members_name); ?></b> <?php print t(' users members of the space(s)',array(),array('context'=>'gofast')); ?></b></div>   
<div id="popup-member-list-filter" class="input-group input-group-sm">
    <span class="input-group-addon" id="sizing-addon3"><span class="icon glyphicon glyphicon-search" aria-hidden="true"></span></span>
    <input id="popup-member-list-filter-search-input" type="text" class="form-control" placeholder="<?php print t('Filter',array(),array('context'=>'gofast')); ?>" aria-describedby="sizing-addon3" />
    <button title="<?php print t('Refresh',array(),array('context'=>'gofast')); ?>" id="popup-member-list-filter-filter-refresh" type="button" class="btn btn-default btn-sm dropdown-toggle"><i class="fa fa-refresh" aria-hidden="true"></i></button>
</div>
<ul id="popup-member-list">
        
 <?php  
 foreach($members_name as $uid => $name) {
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
        
        if($member->picture->uri){
             $picture=theme('image_style',
                array(
                    'style_name' => 'gofast_thumbnail',
                    'path' =>$member->picture->uri,
                    'attributes' => array(
                        'class' => 'avatar'
                    ),
                    'width' => 24,
                    'height' => 24,             
               )
            );
        }
        else{
            $picture = theme('image',
                 array(
                    'path'=>url(variable_get('user_picture_default', ''),['absolute' => TRUE]),
                    'alt'=>$member->name,
                    'width' => 24,
                    'height' => 24,  
                )
            );
        }
        $link=l($name,'user/'.$member->uid);
        
      
        $icon='';
        if(!is_numeric($member->member_type)){
            $p=explode('_',$member->member_type);
            if(count($p)>1){
                $list = entity_load_single('userlist',$p[0]);
                $title=htmlentities(' <b>'.check_plain($list->name).'</b>');
                $icon=' <a href="userlist/'.$p[0].'"  data-html="true" data-placement="left" title="'.$title.'"  data-html="true" data-toggle="tooltip" data-placement="left" title="'.$title.'"><i class="fa fa-users" style=" color: #777;"></i></a>';
            }
        }
        ?>
         <li><span class="popup-member-list-picture"><?php print $picture; ?></span>
            <span class="popup-member-list-name"><?php print $link ; ?></span>
            <span class="popup-member-list-role"><?php print ucfirst(t($role,array(),array('context'=>'gofast'))); ?></span>
            <span class="popup-member-icon-userlist"><?php print $icon; ?></span>
           
        </li>  
        <?php
    }
 ?>
 </ul>
