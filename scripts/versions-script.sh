#usr/bin/bash
#Script displaying versions of some of the installed components

source ~/.bashrc

echo 
echo @site_name includes the following technologies:
echo 
cd /var/www/d7
gofast_version=$(cat /var/www/d7/sites/all/modules/gofast/gofast.info  | grep "version" | cut -d'-' -f2 | cut -d'"' -f1)
echo -e GoFAST: ' \t '' \t ' ${gofast_version} ' \t ' Free and Open-source licence GPL-3.0
cd
echo -e GoFAST File Browser: ' \t ' ${gofast_version} ' \t ' Free and Open-source licence GPL-2.0+


ajax_library_version=$(cat /var/www/d7/sites/all/libraries/ajax_file_browser/version.txt)
echo -e WebDAV Ajax Library: ' \t ' $ajax_library_version ' \t ' Free and Open-source licence GPL-2.0+

drupal_version=$(drush @d7 status | grep "Drupal version")
drupal_version=${drupal_version#*:}
echo -e Drupal: ' \t '' \t ' $drupal_version ' \t ' Free and Open-source licence GPL-2.0+

centos_version=$(cat /etc/centos-release | grep -o '[0-9]\.[0-9]')
echo -e CentOS: ' \t '' \t ' $centos_version ' \t ' ' \t ' Free and Open-source licence GPL-2.0+

php_version=$(php --version | grep built | sed 's/[^0-9]*\([0-9.]*\).*/\1/')
echo -e PHP: ' \t ' ' \t '' \t '  $php_version ' \t ' Open-source licence PHP License v3.01

apache_version=$(yum info httpd | grep "Version" | head -1)
apache_version=${apache_version#*:}
echo -e Apache: ' \t '' \t '  $apache_version ' \t ' Free and Open-source licence GPL-3.0

tomcat_version=$(yum info tomcat | grep "Version" | head -1)
tomcat_version=${tomcat_version#*:}
echo -e Tomcat: ' \t '' \t '  $tomcat_version ' \t ' Free and Open-source licence Apache-2.0

openldap_version=$(yum info openldap | grep "Version" | head -1)
openldap_version=${openldap_version#*:}
echo -e OpenLDAP: ' \t '' \t '  $openldap_version ' \t ' Public licence OpenLDAP Public License version 2.8

libreoffice_version=$(find /opt -wholename *libreoffice7*program/soffice*)
libreoffice_version=$($libreoffice_version --version | sed 's/[^0-9]*\([0-9.]*\).*/\1/')
echo -e Libre Office: ' \t '' \t ' $libreoffice_version ' \t ' Free licence LGPL-3.0+ and MPL-2.0

mysql_version=$(mysql --version | awk '{ print $5 }' | awk -F\, '{ print $1 }')
echo -e MySQL: ' \t '' \t ' $mysql_version ' \t ' Free and Open-source licence GNU GPL

jquery_last_version_folder=$(ls -r /var/www/d7/sites/all/modules/jquery_update/replace/jquery | head -n1)
jquery_version=$(grep 'jQuery JavaScript Library v' /var/www/d7/sites/all/modules/jquery_update/replace/jquery/$jquery_last_version_folder/jquery.js | sed 's/[^0-9.]*\([0-9.]*\).*/\1/')
echo -e jQuery: ' \t '' \t ' $jquery_version ' \t ' '\t '  Free licence MIT

pdfjs_version=$(grep 'pdfjsVersion' /var/www/d7/sites/all/libraries/pdf/build/pdf.js | head -n 1 | awk -F "'" '{print $2}')
echo -e PDF.js: ' \t '' \t ' $pdfjs_version ' \t ' Free licence Apache License 2.0

bootstrap_version=$(grep 'Bootstrap v' /var/www/d7/sites/all/themes/bootstrap-keen/keenv2/assets/css/style.bundle.css | sed 's/[^0-9.]*\([0-9.]*\).*/\1/')
echo -e Bootstrap: ' \t '' \t ' $bootstrap_version ' \t ' Free licence MIT

solr_last_version_folder=$(ls -r /opt/ | grep "solr" | head -n1)
solr_version=$(echo $solr_last_version_folder | cut -d'-' -f2);
echo -e Solr: ' \t ' ' \t '' \t ' $solr_version ' \t ' Free licence Apache-2.0

java_version=$(java -version 2>&1 | head -n 1 | awk -F '"' '{print $2}')
echo -e Java: ' \t ' ' \t '' \t ' $java_version ' \t ' Free and Open-source licence GNU GPL

#ithit_version=$(grep 'ITHit.oNS.Version' /var/www/d7/sites/all/libraries/ajax_file_browser/BrowserSource/ITHitAJAXFileBrowser.js | awk -F "'" '{print $2}' )
#echo -e ITHit: ' \t '' \t ' $ithit_version

cd /var/www/d7
tika_version=$(ls tika-app-* | sed 's/[^0-9.]*\([0-9.]*\).*/\1/' | head -c -2)
echo -e Apache Tika: ' \t '' \t ' $tika_version ' \t ' Free licence Apache-2.0
cd

alfresco_build_name=$(grep 'Specification-Title' /var/lib/tomcats/alfresco/webapps/alfresco/META-INF/MANIFEST.MF)
alfresco_build_name=${alfresco_build_name#*:}
echo -e  Alfresco: ' \t ' ' \t ' ' \t '' \t ' Free licence LPGL-3.0 
echo -e '(Build name)' ' \t ' $alfresco_build_name
alfresco_build_date=$(grep 'Build-Date' /var/lib/tomcats/alfresco/webapps/alfresco/META-INF/MANIFEST.MF)
alfresco_build_date=${alfresco_build_date#*:}
echo -e '(Build date)' ' \t ' $alfresco_build_date
alfresco_build_number=$(grep 'Specification-Version' /var/lib/tomcats/alfresco/webapps/alfresco/META-INF/MANIFEST.MF)
alfresco_build_number=${alfresco_build_number#*:}
echo -e '(Build number)' '  ' $alfresco_build_number

test=`drush @d7 pm-info gofast_workflows | grep Status | sed -e "s/ Status           :  //g"` 
if [ $test == 'enabled' ]
    then
bonita_version=$(cat /var/lib/tomcats/bonita/webapps/bonita/VERSION | head -n 1)
echo -e Bonita: ' \t '' \t ' $bonita_version  ' \t ' Free licence GPL-2.0 
fi