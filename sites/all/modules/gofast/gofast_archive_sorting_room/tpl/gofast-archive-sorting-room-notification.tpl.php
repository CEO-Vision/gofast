
<div style="padding:10px;">
<p> Hello archivist, <br/>
 It's time to sort through the pre-archived documents. You will find below the information of the documents concerned:
</p>
<?php foreach ($infos as $info ){ ?>
<table width="100%" cellspacing="0" cellpadding="10" border="0" style="border-collapse:separate !important; border:1px solid #d9d9d9; border-radius:4px; background-color:#ededf0; margin:3px">
    <tr>
        <td>
            <table width="100%" cellspacing="0" cellpadding="10" border="0" style="border-collapse:separate !important; background-color:#fafafa; ">
                <tr>
                    <td style="padding:10px;">
                        <table width="100%" cellspacing="0" cellpadding="0" border="0">
                            <tr>
                                <td  height="40" valign="top" style=" height:40px; max-height:40px;">
                                    <table  height="40" cellspacing="0" cellpadding="0" border="0" >
                                        <tr>
                                            <td   style=" height:40px; border-collapse:collapse; line-height:100%; padding:0;">
                                                <b>Document</b> : <?php  print $info['title']; ?> 
                                            </td>
                                        </tr>
                                    </table>
                                </td>
								<td  height="40" valign="top" style=" height:40px; max-height:40px;">
                                    <table  height="40" cellspacing="0" cellpadding="0" border="0" >
                                        <tr>
                                            <td   style=" height:40px; border-collapse:collapse; line-height:100%; padding:0;">
                                                <b> Production department </b> : <?php print user_load($info['uid_product'])->ldap_user_displayname['und']['0']['value'];?>
                                            </td>
                                        </tr>
                                    </table>
                                </td>
                            </tr>
                        </table>
                    </td>
                </tr>
				<tr>
            <table width="100%" cellspacing="0" cellpadding="10" border="0" style="border-collapse:separate !important; border:1px solid #d9d9d9; border-radius:4px; background-color:#fafafa; ">
                            <tr>
                                <td  height="40" valign="top" style=" height:40px; max-height:40px;">
                                    <table  height="40" cellspacing="0" cellpadding="0" border="0" >
                                        <tr>
                                            <td   style=" height:40px; border-collapse:collapse; line-height:100%; padding:0;">
                                                <b> Emplacements </b> :
                                                <ul>
                                                    
                                                <?php
                                                    foreach ($info['emplacements'] as $emplacement){
                                                        foreach($emplacement as $path){
                                                  ?>
                                                         <li> <?php print( $path['value']); ?> </li>
                                                  <?php
                                                        }
                                                    }
                                                  ?>  
                                                </ul>
                                            </td>
                                        </tr>
                                    </table>
                                </td>
                            </tr>
            </table>
	</tr>
    </table>

<?php }?>

</div>