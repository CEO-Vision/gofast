#!/bin/bash
# GoFast 3 Switch domain
# (c) CEO-Vision S.A.S

#############################################################
################ - Variables declarations - #################
#############################################################

source ~/.bashrc
ALF_HOME='/var/lib/tomcats/alfresco'

setenforce 0

#############################################################
################## - Gather informations - ##################
#############################################################

 echo -n "entrez l'ancien sous domaine (ex: gofast) :"
 #read old_subdomain
 old_subdomain="mygf-community"
 echo -n "entrez l'ancien de domaine *sans* le .com (ex: ceo-vision): "
 #read old_domainename
 old_domainename="ceo-vision"
 echo -n "entrez l'ancienne extension(ex: com): "
 #read old_extension
 old_extension="com"
 old_domaine=$old_subdomain"."$old_domainename"."$old_extension

 echo -n "entrez le sous domaine (ex: gofast) :"
 #read subdomain
 subdomaintoreplace
 #echo subdomain
 echo -n "entrez le nom de domaine *sans* le .com (ex: ceo-vision): "
 #read domainename
 domainnametoreplace
 #echo domainname
 echo -n "entrez l'extension(ex: com): "
 #read extension
 extentiontoreplace
 #echo extention
 domaine=$subdomain"."$domainename"."$extension

echo "renommage de la machine en $domaine"
echo "$subdomain" >> /var/www/d7/sites/all/modules/gofast/gofast_graphic_config/gofast_graphic_config_generateSelf-SignedCertificate/config_report.txt 2>&1

hostnamectl set-hostname ${domaine}

# echo technical_password
 echo -n "entrez le mot de passe technique"
 #read technical_password
passwordtoreplace

#############################################################
################## - Shut down services - ###################
#############################################################
systemctl stop tomcat@alfresco
systemctl stop tomcat@bonita
systemctl stop slapd

#############################################################
################### - Reconfigure LDAP - ####################
#############################################################

echo "renommage du domaine ldap dans les fichiers de config alfresco"
sed -i -e "s/dc\\\=${old_domainename},dc\\\=${old_extension}/dc\\\=${domainename},dc\\\=${extension}/g" $ALF_HOME/shared/classes/alfresco-global.properties

echo "changement du hostname dans l'arborescence LDAP, export base actuelle en LDIF"
slapcat -l /tmp/backup_ldap_full.ldif
rm -rf /var/lib/ldap/*saz$

cat <<EOT > /var/lib/ldap/DB_CONFIG
#DB_CONFIG
set_cachesize 0 268435456 1
set_lg_regionmax 262144
set_lg_bsize 2097152
EOT

sed -i -e "s/dc=$old_domainename,/dc=$domainename,/g" /etc/openldap/slapd.d/cn\=config/olcDatabase\=\{2\}hdb.ldif
sed -i -e "s/dc=$old_extension$/dc=$extension/g" /etc/openldap/slapd.d/cn\=config/olcDatabase\=\{2\}hdb.ldif

awk 'NR>1 && !sub(/^ /,""){print s; s=""} {s = s $0} END{print s}' /tmp/backup_ldap_full.ldif > /tmp/backup_ldap.ldif

php /var/www/d7/sites/all/modules/gofast/gofast_graphic_config/gofast_graphic_config_switchdomain_exec/gofast-3.x-switchdomain.php "old_domainename=${old_domainename}&domainename=${domainename}&old_extension=${old_extension}&extension=${extension}"

/usr/sbin/slapadd -l /tmp/export_finished.ldif
chown ldap:ldap /var/lib/ldap/*
systemctl start slapd

#Replace ldap conf in features and revert
sed -i -e "s/dc=${old_domainename},dc=${old_extension}/dc=${domainename},dc=${extension}/g" /var/www/d7/sites/all/modules/gofast_features/gofast_features_ldap/gofast_features_ldap.ldap_servers.inc
sed -i -e "s/dc=${old_domainename},dc=${old_extension}/dc=${domainename},dc=${extension}/g" /var/www/d7/sites/all/modules/gofast_features/gofast_features_ldap/gofast_features_ldap.strongarm.inc
drush -v @d7 features-revert gofast_features_ldap -y

#Replace fields in database
drush @d7 sqlq "update field_revision_ldap_user_manager set ldap_user_manager_value=REPLACE(ldap_user_manager_value, 'dc=${old_domainename},dc=${old_extension}', 'dc=${domainename},dc=${extension}');"
drush @d7 sqlq "update field_data_ldap_user_manager set ldap_user_manager_value=REPLACE(ldap_user_manager_value, 'dc=${old_domainename},dc=${old_extension}', 'dc=${domainename},dc=${extension}');"

drush @d7 sqlq "update field_revision_ldap_user_prov_entries set ldap_user_prov_entries_value=REPLACE(ldap_user_prov_entries_value, 'dc=${old_domainename},dc=${old_extension}', 'dc=${domainename},dc=${extension}');"
drush @d7 sqlq "update field_data_ldap_user_prov_entries set ldap_user_prov_entries_value=REPLACE(ldap_user_prov_entries_value, 'dc=${old_domainename},dc=${old_extension}', 'dc=${domainename},dc=${extension}');"

drush @d7 sqlq "update field_data_field_ldap_group_dn set field_ldap_group_dn_value=REPLACE(field_ldap_group_dn_value, 'dc=${old_domainename},dc=${old_extension}', 'dc=${domainename},dc=${extension}');"
drush @d7 sqlq "update field_revision_field_ldap_group_dn set field_ldap_group_dn_value=REPLACE(field_ldap_group_dn_value, 'dc=${old_domainename},dc=${old_extension}', 'dc=${domainename},dc=${extension}');"

# Change password for drupal
mysql -u root -p@C0mmunity! -v  << QUERY_INPUT
grant all on d7.* to 'drupal'@'%' identified by "${technical_password}";
grant all on d7.* to 'drupal'@'localhost' identified by "${technical_password}";
grant all on d7.* to 'drupal'@'127.0.0.1' identified by "${technical_password}";
QUERY_INPUT

# Change password for alfresco
mysql -u root -p@C0mmunity! -v  << QUERY_INPUT
grant all on d7.* to 'alfresco'@'localhost' identified by "${technical_password}";
grant all on d7.* to 'alfresco'@'localhost.localdomain' identified by "${technical_password}";
grant all on d7.* to 'alfresco'@'127.0.0.1' identified by "${technical_password}";
QUERY_INPUT

# Change password for alfresco
mysql -u root -p@C0mmunity! -v  << QUERY_INPUT
grant all on alfresco.* to 'alfresco'@'localhost' identified by "${technical_password}" with grant option;
grant all on alfresco.* to 'alfresco'@'localhost.localdomain' identified by "${technical_password}" with grant option;
grant all on alfresco.* to 'alfresco'@'127.0.0.1' identified by "${technical_password}" with grant option;
QUERY_INPUT

# change mysql root password
mysql -u root -p@C0mmunity! -v  << QUERY_INPUT
ALTER USER 'root'@'localhost' IDENTIFIED BY '${technical_password}';
QUERY_INPUT

#############################################################
############ - Reconfigure Configuration Files - ############
#############################################################
sed -i -e "s/${old_subdomain}.${old_domainename}.${old_extension}/${subdomain}.${domainename}.${extension}/g" /var/www/d7/sites/default/settings.php
sed -i -e "s%^\$base_url = .*%\$base_url = 'https://${domaine}';\$conf['base_url_standard'] = \$base_url;%g" /var/www/d7/sites/default/settings.php
sed -i "s/\$base_url = 'https:\/\/'.\$conf\['mobile_prefix_url'\].*/\$base_url = 'https:\/\/'.\$conf\['mobile_prefix_url'\].'.${domainename}.${extension}';/" /var/www/d7/sites/default/settings.php
sed -i -e "s/@C0mmunity\!/${technical_password}/g" /var/www/d7/sites/default/settings.php
sed -i -e "s/@C0mmunity\!/${technical_password}/g" /var/lib/tomcats/alfresco/shared/classes/alfresco-global.properties
sed -i -e "s%\$ldap_servers_conf->bindpw =.*%\$ldap_servers_conf->bindpw ='${technical_password}';%g" /var/www/d7/sites/all/modules/gofast_features/gofast_features_ldap/gofast_features_ldap.ldap_servers.inc

#Change root password in LDAP y technical password
olcRootPW=$(slappasswd -s ${technical_password} -h {MD5} -u)
ldap_files=${SRC_HOME}/ldap
mkdir -p ${ldap_files}

cat << EOF > ${ldap_files}/chadmin.ldif
dn: uid=admin,ou=people,dc=${domainename},dc=${extension}
changetype: modify
replace: userPassword
userPassword: ${olcRootPW}
EOF

ldapmodify -x -D cn=Manager,dc=${domainename},dc=${extension} -w '@C0mmunity!' -f ${ldap_files}/chadmin.ldif



cat << EOF > ${ldap_files}/chrootpw.ldif
dn: olcDatabase={0}config,cn=config
changetype: modify
replace: olcRootPW
olcRootPW: ${olcRootPW}
EOF

ldapmodify -Y EXTERNAL -H ldapi:/// -f ${ldap_files}/chrootpw.ldif


# Set olcDatabase (hdb) config & set domain names.
cat << EOF > ${ldap_files}/chdomain.ldif
dn: olcDatabase={2}hdb,cn=config
changetype: modify
replace: olcRootPW
olcRootPW: ${olcRootPW}
EOF

ldapmodify -Y EXTERNAL -H ldapi:/// -f ${ldap_files}/chdomain.ldif

htpasswd -b -c /etc/httpd/conf.d/proxy.htpasswd admin ${technical_password}
sed -i -e "s/${old_subdomain}.${old_domainename}.${old_extension}/${subdomain}.${domainename}.${extension}/g" /var/lib/tomcats/alfresco/shared/classes/alfresco-global.properties
sed -i -e "s/${old_subdomain}.${old_domainename}.${old_extension}/${subdomain}.${domainename}.${extension}/g" /etc/httpd/conf.d/proxy_html.conf
sed -i -e "s/${old_subdomain}.${old_domainename}.${old_extension}/${subdomain}.${domainename}.${extension}/g" /etc/httpd/conf/httpd.conf
echo -e ${technical_password} | (passwd --stdin root)
#Restart httpd
systemctl restart httpd

#Restart LDAP
systemctl restart slapd

#############################################################
################### - Restart services - ####################
#############################################################
systemctl start tomcat@alfresco

until $(curl --output /dev/null --silent --head --fail http://localhost:8080/alfresco); do
    printf '.'
    sleep 1
done

drush @d7 user-password admin --password=${technical_password}

# Set timezone to Paris
timedatectl set-timezone Europe/Paris

drush @d7 flush-advagg

systemctl restart memcached

drush @d7 php-eval "drush_gofast_post_install();";

drush @d7 php-eval "field_cache_clear();"
drush @d7 php-eval "gofast_og_cron();"

drush @d7 php-eval "variable_set('membership_waiting_build',json_encode(array('4','5','6','7')));"
drush @d7 php-eval "variable_set('user_membership_waiting_build', json_encode(array('1','4')));"
sleep 5

drush @d7 php-eval "variable_set('current_config_community',FALSE);"
sleep 65

drush @d7 php-eval "gofast_graphic_config_create_begin_spaces();"

drush @d7 flush-advagg

setenforce 1

touch /var/www/d7/sites/all/modules/gofast/gofast_graphic_config/validate.txtinfo
chmod  777 /var/www/d7/sites/all/modules/gofast/gofast_graphic_config/validate.txtinfo

