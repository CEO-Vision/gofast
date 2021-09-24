#!/bin/bash

if [ -f /var/www/d7/sites/all/modules/gofast/gofast_graphic_config/gofast_graphic_config_switchdomain_exec/gofast-3.x-switchdomain.sh ]
then

  dos2unix /var/www/d7/sites/all/modules/gofast/gofast_graphic_config/gofast_graphic_config_switchdomain_exec/gofast-3.x-switchdomain.sh

  mv /var/www/d7/sites/all/modules/gofast/gofast_graphic_config/gofast_graphic_config_switchdomain_exec/gofast-3.x-switchdomain.sh /var/www/d7/sites/all/modules/gofast/gofast_graphic_config/gofast_graphic_config_switchdomain_exec/switchdomain.sh
  
  dos2unix /var/www/d7/sites/all/modules/gofast/gofast_graphic_config/gofast_graphic_config_switchdomain_exec/switchdomain.sh
  dos2unix /var/www/d7/sites/all/modules/gofast/gofast_graphic_config/gofast_graphic_config_switchdomain_exec/gofast-3.x-switchdomain.php

  chmod 777 -R /var/www/d7/sites/all/modules/gofast/gofast_graphic_config/gofast_graphic_config_switchdomain_exec/
  
  bash /var/www/d7/sites/all/modules/gofast/gofast_graphic_config/gofast_graphic_config_switchdomain_exec/switchdomain.sh >> /var/www/d7/sites/all/modules/gofast/gofast_graphic_config/gofast_graphic_config_switchdomain_exec/config_report.txt 2>&1

  rm -R /var/www/d7/sites/all/modules/gofast/gofast_graphic_config/gofast_graphic_config_switchdomain_exec/gofast-3.x-switchdomain.php
  rm -R /var/www/d7/sites/all/modules/gofast/gofast_graphic_config/gofast_graphic_config_switchdomain_exec/switchdomain.sh
fi