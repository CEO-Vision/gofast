#!/bin/bash


#site_alias = "d7"
#hostname = "new-gofast-community.corp.com
#  DRUPAL_HOME="/var/www/${1}"
# DRUPAL_BASE="/var/www"


use_ssl ${site_alias} ${hostname}
#Generate the needed java keystore
keytool -genkey -alias ${hostname} -keyalg RSA -keystore /etc/pki/keystore

function generate_self_signed_certificate() {

	echo '01' > /etc/pki/CA/serial
	touch /etc/pki/CA/index.txt
	openssl req -new -x509 -extensions v3_ca -keyout /etc/pki/CA/private/ceov_cakey.pem  -out /etc/pki/CA/certs/ceov_cacert.pem -days 3650 -config ./openssl.cnf
	# export in windows format to distribute the CA certificate. it is then importable as a CA root authority in the browser
	openssl rsa -out ceov_cakey_noenc.pem -in  /etc/pki/CA/private/ceov_cakey.pem
	openssl pkcs12  -export -out certificate.pfx -inkey /etc/pki/CA/private/ceov_cakey.pem  -in /etc/pki/CA/certs/ceov_cacert.pem

	# create the CSR
	openssl req -new -nodes -keyout  /etc/pki/tls/private/csr_key.key -out /etc/pki/tls/certs/csr_req.pem -config ./openssl.cnf
	# sign the CSR with the CA
	openssl ca -out cert.pem -config ./openssl.cnf -infiles /etc/pki/tls/certs/csr_req.pem

	cp cert.pem /etc/pki/tls/certs/localhost.crt
	cp /etc/pki/tls/private/csr_key.key /etc/pki/tls/private/localhost.key

}

function use_ssl() {

  read -p "Do you wish to generate self-signed certificate?" yn
  case $yn in
      [Yy]* ) generate_self_signed_certificate; break;;
      [Nn]* ) break;;
      * ) echo "Please answer y or n.";;
  esac

  yum install -y mod_proxy_html mod_ssl

  firewall-cmd --permanent --zone=public --remove-service=http
  firewall-cmd --permanent --zone=public --add-service=https

  site_alias=${1}
  hostname=${2}
  DRUPAL_HOME="/var/www/${1}"

  echo "writing proxy conf file"
cat << EOF >>  /etc/httpd/conf.d/proxy_html.conf
    # Configuration example.
    #
    # First, to load the module with its prerequisites.  Note: mod_xml2enc
    # is not always necessary, but without it mod_proxy_html is likely to
    # mangle pages in encodings other than ASCII or Unicode (utf-8).
    #
    # For Unix-family systems:
    LoadModule      proxy_html_module       modules/mod_proxy_html.so
    LoadModule      xml2enc_module          modules/mod_xml2enc.so
    #
    # For Windows (I don't know if there's a standard path for the libraries)
    # LoadFile      C:/path/zlib.dll
    # LoadFile      C:/path/iconv.dll
    # LoadFile      C:/path/libxml2.dll
    # LoadModule    proxy_html_module       modules/mod_proxy_html.so
    # LoadModule    xml2enc_module          modules/mod_xml2enc.so
    #
    # All knowledge of HTML links has been removed from the mod_proxy_html
    # code itself, and is instead read from httpd.conf (or included file)
    # at server startup.  So you MUST declare it.  This will normally be
    # at top level, but can also be used in a <Location>.
    #
    # Here's the declaration for W3C HTML 4.01 and XHTML 1.0

    ProxyHTMLLinks  a               href
    ProxyHTMLLinks  area            href
    ProxyHTMLLinks  link            href
    ProxyHTMLLinks  img             src longdesc usemap
    ProxyHTMLLinks  object          classid codebase data usemap
    ProxyHTMLLinks  q               cite
    ProxyHTMLLinks  blockquote      cite
    ProxyHTMLLinks  ins             cite
    ProxyHTMLLinks  del             cite
    ProxyHTMLLinks  form            action
    ProxyHTMLLinks  input           src usemap
    ProxyHTMLLinks  head            profile
    ProxyHTMLLinks  base            href
    ProxyHTMLLinks  script          src for

    # To support scripting events (with ProxyHTMLExtended On),
    # you'll need to declare them too.

    ProxyHTMLEvents onclick ondblclick onmousedown onmouseup \
                    onmouseover onmousemove onmouseout onkeypress \
                    onkeydown onkeyup onfocus onblur onload \
                    onunload onsubmit onreset onselect onchange

    # If you need to support legacy (pre-1998, aka 'transitional') HTML or XHTML,
    # you'll need to uncomment the following deprecated link attributes.
    # Note that these are enabled in earlier mod_proxy_html versions
    #
    # ProxyHTMLLinks        frame           src longdesc
    # ProxyHTMLLinks        iframe          src longdesc
    # ProxyHTMLLinks        body            background
    # ProxyHTMLLinks        applet          codebase
    #
    # If you're dealing with proprietary HTML variants,

    <proxy *>
    AddDefaultCharset Off
    Require all granted
    </proxy>
    ProxyPassMatch ^.*\.~lock\..* !
    ProxyPass /alfresco/cmisbrowse !
    ProxyPassReverse /alfresco/cmisbrowse !
    ProxyPass /alfresco/faces/jsp/dashboards/container.jsp !
    ProxyPassReverse /alfresco/faces/jsp/dashboards/container.jsp !
    ProxyPass /alfresco/faces/jsp/login.jsp !
    ProxyPassReverse /alfresco/faces/jsp/login.jsp !

    # We use ajp proxy module as this prevent us to get PROPFIND or OPTIONS method not allowed by some web browser.
    ProxyPass /alfresco ajp://localhost:8009/alfresco
    ProxyPassReverse /alfresco ajp://localhost:8009/alfresco

    ProxyPass /share ajp://localhost:8009/share
    ProxyPassReverse /share ajp://localhost:8009/share

    ProxyPass /solr http://localhost:8983/solr
    ProxyPassReverse /solr http://localhost:8983/solr

    ProxyPass /_vti_bin ajp://localhost:8009/_vti_bin
    ProxyPassReverse /_vti_bin ajp://localhost:8009/_vti_bin

    ProxyPass /_vti_inf ajp://localhost:8009/_vti_inf
    ProxyPassReverse /_vti_inf ajp://localhost:8009/_vti_inf

    ProxyPass /aos ajp://localhost:8009/aos
    ProxyPassReverse /aos ajp://localhost:8009/aos
EOF

  cat << EOF >>  /etc/httpd/conf.d/proxy_html.conf	
    <Location /alfresco/webdav/ >
        <Limit OPTIONS PROPFIND GET REPORT MKACTIVITY PROPPATCH PUT CHECKOUT MKCOL MOVE COPY DELETE LOCK UNLOCK MERGE ACL CANCELUPLOAD CHECKIN HEAD MKCALENDAR POST SEARCH UNCHECKOUT UPDATE VERSION-CONTROL>
            Order Deny,Allow
            Allow from all
            Satisfy Any
        </Limit>
    </Location>

    RedirectMatch ^/share(\/.*)$ /share/
    RedirectMatch ^/alfresco(\/.*)$ /alfresco/
    RedirectMatch ^/_vti_bin(\/.*)$ /_vti_bin/

    <Location "/share">
      AuthType Basic
      AuthName "Wrapper auth"
      AuthBasicProvider file
      AuthUserFile "/etc/httpd/conf.d/proxy.htpasswd"
      Require valid-user
    </Location>
EOF

  if [ "$INSTALL_TYPE" == "enterprise" ]
  then
    cat << EOF >>  /etc/httpd/conf.d/proxy_html.conf
      rulem "second condition bonita"
      <Location "/bonita/login.jsp">
        AuthType Basic
        AuthName "Wrapper auth"
        AuthBasicProvider file
        AuthUserFile "/etc/httpd/conf.d/proxy.htpasswd"
        Require valid-user
      </Location>
EOF
  fi

  cat << EOF >>  /etc/httpd/conf.d/proxy_html.conf
    <Location "/solr">
      AuthType Basic
      AuthName "Wrapper auth"
      AuthBasicProvider file
      AuthUserFile "/etc/httpd/conf.d/proxy.htpasswd"
      Require valid-user
    </Location>
EOF

  echo "proxy conf file written"
  rm -r /etc/httpd/conf.d/welcome.conf

  echo "creating proxy.htpasswd file"
  htpasswd -b -c /etc/httpd/conf.d/proxy.htpasswd admin ${db_pw}

  mv /etc/httpd/conf/httpd.conf /etc/httpd/conf/httpd.noSSL.ORI
  touch /etc/httpd/conf/httpd.conf

  echo "changing httpd conf file"
  cat << EOF >> /etc/httpd/conf/httpd.conf
    ServerRoot "/etc/httpd"

    Listen 80

    Include conf.modules.d/*.conf
    LoadModule proxy_module modules/mod_proxy.so 
    LoadModule proxy_fcgi_module modules/mod_proxy_fcgi.so

    User apache
    Group apache

    ServerAdmin root@localhost

    ServerName ${hostname}

    <Directory />
        AllowOverride none
        Require all denied
    </Directory>

    DocumentRoot "${DRUPAL_HOME}"
    DirectoryIndex /index.php index.php

    KeepAlive Off

    RewriteEngine On
    RewriteOptions inherit
    ProxyPassMatch ^/(.*\.php(/.*)?)$ fcgi://127.0.0.1:9000/var/www/d7/

    <Directory "${DRUPAL_HOME}">
        Require all granted
        AllowOverride all
    </Directory>

    <Directory "${DRUPAL_BASE}">
        AllowOverride None
        Require all granted
    </Directory>

    <IfModule dir_module>
        DirectoryIndex index.html
    </IfModule>

    <Files ".ht*">
        Require all denied
    </Files>

    ErrorLog "logs/error_log"

    LogLevel warn

    <IfModule log_config_module>
        LogFormat "%h %l %u %t \"%r\" %>s %b \"%{Referer}i\" \"%{User-Agent}i\"" combined
        LogFormat "%h %l %u %t \"%r\" %>s %b" common

        <IfModule logio_module>
          LogFormat "%h %l %u %t \"%r\" %>s %b \"%{Referer}i\" \"%{User-Agent}i\" %I %O" combinedio
        </IfModule>

        CustomLog "logs/access_log" combined
    </IfModule>

    <IfModule mod_headers.c>
        Header set Access-Control-Allow-Origin: *
        Header set Access-Control-Allow-Headers "Authorization, Overwrite, Destination, Content-Type, Depth, User-Agent, Translate, Range, Content-Range, Timeout, X-File-Size, X-Requested-With, If-Modified-Since, X-File-Name, Cache-Control, Location, Lock-Token, X-Jitsi-Shard, X-Proxy-Region, X-Jitsi-Region, If"
        Header set Access-Control-Allow-Methods "ACL, CANCELUPLOAD, CHECKIN, CHECKOUT, COPY, DELETE, GET, HEAD, LOCK, MKCALENDAR, MKCOL, MOVE, OPTIONS, POST, PROPFIND, PROPPATCH, PUT, REPORT, SEARCH, UNCHECKOUT, UNLOCK, UPDATE, VERSION-CONTROL"
        Header set Access-Control-Allow-Credentials "true"
        Header set Access-Control-Expose-Headers "DAV, content-length, Allow"
    </IfModule>

    <IfModule alias_module>
        ScriptAlias /cgi-bin/ "/var/www/cgi-bin/"
    </IfModule>

    <Directory "/var/www/cgi-bin">
        AllowOverride None
        Options None
        Require all granted
    </Directory>

    <IfModule mime_module>
        TypesConfig /etc/mime.types

        AddType application/x-compress .Z
        AddType application/x-gzip .gz .tgz

        AddType text/html .shtml
        AddOutputFilter INCLUDES .shtml
    </IfModule>

    AddDefaultCharset UTF-8

    <IfModule mime_magic_module>
        MIMEMagicFile conf/magic
    </IfModule>

    EnableSendfile on

    <VirtualHost *:80>
        DocumentRoot "${DRUPAL_HOME}"

        <Directory "${DRUPAL_HOME}">
            Require all granted
            AllowOverride all
        </Directory>
    </VirtualHost>

    IncludeOptional conf.d/*.conf
EOF
	
  echo "httpd conf file changed"

  sed -i -e "s/\$base_url = 'http:\/\/${hostname}'/\$base_url = 'https:\/\/${hostname}'/g"  ${DRUPAL_HOME}/sites/default/settings.php

  /usr/bin/mysql_secure_installation

  #addsecurity configuration for https (configure SSL.conf)
  sed -i -e "s%^SSLProtocol all -SSLv2%SSLProtocol all -SSLv2 -SSLv3%g" /etc/httpd/conf.d/ssl.conf 
  sed -i -e "s%^#SSLHonorCipherOrder on%SSLHonorCipherOrder on%g" /etc/httpd/conf.d/ssl.conf
  sed -i -e "/SSLHonorCipherOrder on/a SSLCipherSuite EECDH+AES128:RSA+AES128:EECDH+AES256:RSA+AES256" /etc/httpd/conf.d/ssl.conf 

  service php-fpm restart
  service httpd restart
  echo "Setup completed"
}
