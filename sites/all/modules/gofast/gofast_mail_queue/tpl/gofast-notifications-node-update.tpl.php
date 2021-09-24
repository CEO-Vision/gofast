                        <table width="100%" cellspacing="1" cellpadding="1" border="0">
                            <!--<tr height="5">  //<td height="5" valign="top" style="font-size:1px"></td>//  </tr>-->
                            <tr>
                                <td width="10" valign="top" style="font-size:1px"></td>
                                <td valign="middle">
                                    <table width="100%" cellspacing="0" cellpadding="0" border="0" align="left" style="font-size:12px;">
                                            <?php if ($updates || $com_updates): ?>
                                                <tr>
                                                    <td height="15" style="height:15px; max-height:15px; font-size:15px; line-height:100%">
                                                        &nbsp; <!-- margin -->
                                                    </td>
                                                </tr>
                                                <tr>
                                                    <td>
                                                        <table width="100%" cellspacing="0" cellpadding="10" style="border-collapse:separate; border:1px solid #5bc0de; border-radius:6px 6px 6px 6px; background-color:#ffffff">
                                                            
                                                            <tr>
                                                                <td valign="middle" style="color:#666666; font-family:Arial; font-size:12px; font-weight:normal; line-height:150%; word-wrap:break-word; background-color: #fefefe;">
                                                                        <blockquote height="20" style="margin-left: 0px; height:10px; min-height:10px; font-size:15px; line-height:150%; height: 100%;">
                                                                          <span style='float: left;'><?php print $node_icon; ?></span>
                                                                          <span style="font-size:15px; font-weight:normal; overflow:auto; margin-left: 5px; font-weight: bold; color: #0074A6"><?php print $node_title; ?></span>
                                                                        </blockquote>
                                                                    <blockquote style="padding-bottom: 0px; border-bottom: 0px; font-size:12px; color:#666666; font-weight:normal; overflow:auto; line-height:150%; margin:1px;">
                                                                      <span id="c-node<?php print($count_node); ?>"></span>
                                                                        <?php print $com_updates; ?>
                                                                      <span id="u-node<?php print($count_node); ?>"></span>
                                                                        <?php print $updates; ?>
                                                                    </blockquote>
                                                                </td>
                                                            </tr>
                                                            <tr>
                                                                    <td style="padding-top: 0px; font-size: 10px; font-weight: bold; border:none; text-decoration:none; font-family:'Helvetica Neue',Helvetica,Arial,sans-serif; color:#999999; text-align:right;">
                                                                      <a href="#top" style="text-decoration: none;color:blue;">TOP</a>
                                                                    </td>
                                                            </tr>                                                            
                                                        </table>
                                                    </td>
                                                </tr>
                                            <?php endif; ?>
                                        <?php if ($details): ?>
                                        <tr>
                                            <td valign="middle" style="color:#777777; font-family:Arial; font-size:17px; font-weight:normal; line-height:150%; padding-bottom:0; padding-top:10px;">
                                                <?php print $details; ?>
                                            </td>
                                        </tr>
                                        <?php endif; ?>
                                    </table>
                                    <table width="100%" cellspacing="0" cellpadding="0" border="0" align="center" style="font-size:12px; margin:0; text-align:right; width:100%; max-width:100%;">
                                        <tr>
                                            <td width="100%" align="right" style="width:100%; border:none; text-decoration:none; font-family:'Helvetica Neue', Helvetica, Arial, sans-serif; color:#999999;">
                                                <?php print $date; ?>
                                            </td>
                                        </tr>
                                    </table>
                                </td>
                                <td width="10" valign="top" style="font-size:1px"></td>
                            </tr>
                        </table>