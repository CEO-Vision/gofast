#!/bin/sh
# -------
# Script for backing up GoFast data (directores and mysql data)
# (C) CEO-VISION Fev. 2013
# v1.1.0
# -------
#
service tomcat@bonita restart

rm -f /var/www/d7/sites/default/files/swf/cookie_bonita*
