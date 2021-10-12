<table width="100%" cellspacing="0" cellpadding="0" border="0" style="border-bottom:solid 20px #fff;">
    <tr>
        <td>
            <table width="100%" cellspacing="0" cellpadding="10" border="0" style="border-collapse:separate !important; border:1px solid #d9d9d9; border-radius:4px; background-color:#fafafa; ">
                <tr>
                    <td style="padding:10px;">
                        <table width="100%" cellspacing="0" cellpadding="0" border="0">
                            <tr>
                                <td width="40" height="40" valign="top" style="width:40px; max-width:40px; height:40px; max-height:40px;">
                                    <table width="40" height="40" cellspacing="0" cellpadding="0" border="0" style="background:#fff; border:0;">
                                        <tr>
                                            <td width="40" height="40" valign="middle" style="width:40px; height:40px; border-collapse:collapse; line-height:100%; padding:0;">
                                                <?php print $author_pic; ?>
                                            </td>
                                        </tr>
                                    </table>
                                </td>
                                <td width="10" valign="top" style="font-size:1px"></td>
                                <td valign="middle">
                                    <table width="100%" cellspacing="0" cellpadding="0" border="0" align="left" style="font-size:12px;">
                                        <tr>
                                            <td valign="top" style="color: #666666; font-family: Arial; font-size: 13px; font-weight: normal; line-height: 150%;">
                                                <?php 
                                                    print $is_digest ? $author_name : t('!author updated', array('!author' => $author_name), $l);
                                                ?>
                                              <span style="font-size:15px; font-weight:normal; overflow:auto; margin-left: 5px; font-weight: bold; color: #0074A6"><?php print $node_title; ?></span>
                                            </td>
                                        </tr>
                                        <?php if ($is_digest) : ?>
                                            <tr>
                                                <td valign="bottom" style="color: #666666; font-family: Arial; font-size: 12px; font-weight: normal; line-height: 150%; padding-top:1px;">
                                                    <?php print t('updated this content', array(), $l); ?>
                                                </td>
                                            </tr>                     
                                        <?php endif; ?>
                                    </table>
                                </td>
                            </tr>
                        </table>
                        <table width="100%" cellspacing="0" cellpadding="0" border="0" align="center">
                            <!-- comment section -->
                            <tr>
                                <td valign="top">
                                    <table width="100%" cellspacing="0" cellpadding="0" border="0" align="left" style="border-collapse:separate !important;">
                                        <tr>
                                            <td height="10">
                                                <!-- margin -->
                                            </td>
                                        </tr> 

                                        <?php if (isset($modifications)) : ?>
                                        <tr>
                                            <td style="background-color: #F9F9F9;">
                                                <table width="100%" cellspacing="0" cellpadding="10" border="0" align="center">
                                                    <tr>
                                                        <td style=" color:#666666; font-family:Arial; font-size:14px; font-weight:normal; line-height:150%; word-wrap:break-word; word-break:break-word;" >
                                                            <?php print $modifications; ?>
                                                        </td>
                                                <?php 
                                                    if(count($modifications_todolist) > 0){
                                                         $l["context"] = "gofast:gofast_kanban";
                                                          foreach($modifications_todolist as $ciid=>$event){
                                                              if($ciid == "Global Progression_"){
                                                                   $modifications_tdl_overall_progress = ' <table width="100%" cellspacing="0" cellpadding="10" border="0" align="center">
                                                         <tr>
                                                             <td style=" color:#666666; font-family:Arial; font-size:14px; font-weight:normal; line-height:150%; word-wrap:break-word; word-break:break-word;" >
                                                                 ';
                                                              $modifications_tdl_overall_progress .= "<h5>".t("overall progress", array(), $l)."</h5>".$event[0]."</td></tr></table>";
                                                                    //print $modifications_tdl;
                                                              }else{
                                                                    $tdl_label = explode("_", $ciid)[1];
                                                                    $modifications_tdl = ' <table width="100%" cellspacing="0" cellpadding="10" border="0" align="center">
                                                         <tr>
                                                             <td style=" color:#666666; font-family:Arial; font-size:14px; font-weight:normal; line-height:150%; word-wrap:break-word; word-break:break-word;" >
                                                                 ';
                                                                    $modifications_tdl .= "<h4>".$tdl_label."</h4><table id='edits-metadatas' style='width:100%; border-left: 1px solid #dddddd; border-top: 1px solid #dddddd; border-radius:5px;'><tr>";
                                                                    $modifications_tdl .= "<th style='border-right: 1px solid #dddddd; border-bottom: 1px solid #bbbbbb; border-bottom: 1px solid #dddddd; color: #444444;'>".t('Field', array(), $l)."</th>";
                                                                    $modifications_tdl .= "<th style='border-right: 1px solid #dddddd; border-bottom: 1px solid #bbbbbb; border-bottom: 1px solid #dddddd; color: #444444;'>".t('Remove', array(), $l)."</th>";
                                                                    $modifications_tdl .= "<th style='border-right: 1px solid #dddddd; border-bottom: 1px solid #bbbbbb; border-bottom: 1px solid #dddddd; color: #444444;'>".t('Added', array(), $l)."</th>";
                                                                    $modifications_tdl .= "<th style='border-right: 1px solid #dddddd; border-bottom: 1px solid #bbbbbb; border-bottom: 1px solid #dddddd; color: #444444;'>".t('Date', array(), $l)."</th>";
                                                                    $modifications_tdl .= "</tr>";
                                                                    if(count($event) > 0){
                                                                        foreach($event as $key=>$themed_event){
                                                                             $modifications_tdl .= $themed_event;
                                                                        }
                                                                    }
                                                                    $modifications_tdl .= "</table></td></tr></table>";
                                                                    print $modifications_tdl;
                                                              }
                                                          }
                                                          if(isset($modifications_tdl_overall_progress)){
                                                              print $modifications_tdl_overall_progress;
                                                          }
                                                         
                                                    }
                                                     
                                                  
                                                ?>
                                                      
                                                    </tr>
                                                </table>
                                            </td>
                                        </tr>
                                        <?php endif; ?>
                                    </table>
                                    <table width="100%" cellspacing="0" cellpadding="0" border="0" align="center" style="font-size:12px;">
                                        <tr>
                                            <td height="10" style="height:10px; max-height:10px; font-size:10px; line-height:100%">
                                                &nbsp; <!-- margin -->
                                            </td>
                                        </tr>
                                        <tr>
                                            <td width="75">
                                            </td>
                                            <td style="border:none; text-decoration:none; font-family:'Helvetica Neue',Helvetica,Arial,sans-serif; color:#999999; text-align:right;">
                                                <?php print $date; ?>
                                            </td>
                                        </tr>
                                    </table>
                                </td> <!-- comment section end -->
                            </tr>
                        </table>
                    </td>
                </tr>
            </table>
        </td>
    </tr>
</table>