#!/bin/bash

PrivateKey="/var/www/d7/sites/all/modules/gofast/gofast_graphic_config/gofast_graphic_config_switchSSL_repo/PrivateKey.key"
PublicKey="/var/www/d7/sites/all/modules/gofast/gofast_graphic_config/gofast_graphic_config_switchSSL_repo/PublicKey.crt"

if [ -f "$PublicKey" ] && [ -f "$PrivateKey" ]
then

  dos2unix /var/www/d7/sites/all/modules/gofast/gofast_graphic_config/gofast_graphic_config_switchSSL_repo/*

  chown -R root:apache /var/www/d7/sites/all/modules/gofast/gofast_graphic_config/gofast_graphic_config_switchSSL_repo/PrivateKey.key
  chown -R root:apache /var/www/d7/sites/all/modules/gofast/gofast_graphic_config/gofast_graphic_config_switchSSL_repo/PublicKey.crt

  chmod -R 777 /var/www/d7/sites/all/modules/gofast/gofast_graphic_config/gofast_graphic_config_switchSSL_repo/PrivateKey.key
  chmod -R 777 /var/www/d7/sites/all/modules/gofast/gofast_graphic_config/gofast_graphic_config_switchSSL_repo/PublicKey.crt

  # protect for don't run twice by the cron and move them and rename them
  mv /var/www/d7/sites/all/modules/gofast/gofast_graphic_config/gofast_graphic_config_switchSSL_repo/PrivateKey.key /etc/pki/tls/private/PrivateKeyUsed.key
  mv /var/www/d7/sites/all/modules/gofast/gofast_graphic_config/gofast_graphic_config_switchSSL_repo/PublicKey.crt /etc/pki/tls/certs/PublicKeyUsed.crt

  # if to much right system will be trigger an error
  chmod 600 /etc/pki/tls/certs/PublicKeyUsed.crt
  chmod 600 /etc/pki/tls/private/PrivateKeyUsed.key

  # Apply the right modfication at the right place for change the certificate
  sed -i 's/localhost.key/PrivateKeyUsed.key/' /etc/httpd/conf.d/ssl.conf
  sed -i 's/localhost.crt/PublicKeyUsed.crt/' /etc/httpd/conf.d/ssl.conf

  #Apply the modifications on the  server
  service httpd restart

fi