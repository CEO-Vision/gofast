<?php

/* if started from commandline, wrap parameters to $_POST and $_GET */
	if (!isset($_SERVER["HTTP_HOST"])) {
	  parse_str($argv[1], $_GET);
	  parse_str($argv[1], $_POST);
	}

$old_domain = $_POST['old_domainename'];
$new_domaine = $_POST['domainename'];

$old_extension = $_POST['old_extension'];
$new_extension = $_POST['extension'];

$commande_remove_ldif = "rm -f /tmp/export_finished.ldif";
$commande_duplicate_ldif = "cp /tmp/backup_ldap.ldif /tmp/export_finished.ldif";
$commande_sed_1 = 'sed -i -e "s/dc='.$old_domain.',/dc='.$new_domaine.',/g" /tmp/export_finished.ldif';
$commande_sed_2 = 'sed -i -e "s/dc: '.$old_domain.',/dc: '.$new_domaine.',/g" /tmp/export_finished.ldif';
$commande_sed_3 = 'sed -i -e "s/dc='.$old_extension.'$/dc='.$new_extension.'/g" /tmp/export_finished.ldif';
$commande_sed_4 = 'sed -i -e "s/dc: '.$old_extension.'$/dc: '.$new_extension.'/g" /tmp/export_finished.ldif';
$commande_sed_5 = 'sed -i -e "s/dc: '.$old_domain.'/dc: '.$new_domaine.'/g" /tmp/export_finished.ldif';

exec($commande_remove_ldif);
exec($commande_duplicate_ldif);
exec($commande_sed_1);
exec($commande_sed_2);
exec($commande_sed_3);
exec($commande_sed_4);
exec($commande_sed_5);

$lines = file('/tmp/export_finished.ldif');
$file_contents = file_get_contents('/tmp/export_finished.ldif');

// Affiche toutes les lignes du tableau comme code HTML, avec les numéros de ligne
foreach ($lines as $line_num => $line) {
  if (strpos($line, ':: ') !== FALSE){
      $full_encoded_string_without_dn = explode(":: ", $line)[1];
      $full_decoded_string = base64_decode($full_encoded_string_without_dn);
      $full_decoded_string_with_domaine_replaced = str_replace("dc=".$old_domain.",dc=".$old_extension, "dc=".$new_domaine.",dc=".$new_extension, $full_decoded_string);
      $full_encoded_string_with_domaine_replaced_with_dn = explode(":: ", $line)[0].":: ".base64_encode($full_decoded_string_with_domaine_replaced);

      $file_contents = str_replace($line, $full_encoded_string_with_domaine_replaced_with_dn."\n", $file_contents);
    }
}

file_put_contents('/tmp/export_finished.ldif',$file_contents);

?>
