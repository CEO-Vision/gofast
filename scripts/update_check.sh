# -------
# Scripts to update or modify the platform
# (C) CEO-VISION 2018
# v1.1 - 2020
# -------
#

# Check if an update is pending. Process it and store it's logs

update_file=/var/www/d7/sites/default/files/update_gofast.sh

if [ -f $update_file ]; then
  chmod 777 /var/www/d7/sites/default/files/update_gofast.sh
  mv /var/www/d7/sites/default/files/update_gofast.sh /var/www/d7/sites/default/files/update_gofast_process.sh
  /var/www/d7/sites/default/files/update_gofast_process.sh >> /var/www/d7/sites/default/files/logs/update_report.gflog 2>&1
  rm -f /var/www/d7/sites/default/files/update_gofast_process.sh
fi

# Restart services if needed
if [ -f /var/www/d7/sites/default/files/restart_alfresco.txt ]
then
        timezone=$(date +"%Z")
        day=$(systemctl status tomcat@alfresco |grep -oP ${timezone}'; \K.*day'|grep -oP '[0-9]{1,2}')
        hour=$(systemctl status tomcat@alfresco |grep -oP ${timezone}'; \K.*h'|grep -oP '[0-9]{2}')
        min=$(systemctl status tomcat@alfresco |grep -oP ${timezone}'; \K.*min'|grep -oP '[0-9]{1,2}')

        if [ ! -z "$day" ] || [ ! -z "$hour" ]
            rm -f /var/www/d7/sites/default/files/restart_alfresco.txt
        then
            echo -e "\n\t\tRestarting Alfresco...\n" >> /var/log/messages
            service tomcat@alfresco restart
            rm -f /var/www/d7/sites/default/files/restart_alfresco.txt
        else
            if [ ! -z "$min" ]
                rm -f /var/www/d7/sites/default/files/restart_alfresco.txt
            then
                if [ "$min" -gt 2 ]
                    rm -f /var/www/d7/sites/default/files/restart_alfresco.txt
                then
                    echo -e "\n\t\tRestarting Alfresco...\n" >> /var/log/messages
                    service tomcat@alfresco restart
                    rm -f /var/www/d7/sites/default/files/restart_alfresco.txt
                fi
            fi
        fi
fi

if [ -f /var/www/d7/sites/default/files/restart_bonita.txt ]
then
        echo -e "\n\t\tRestarting Bonita...\n" >> /var/log/messages
        service tomcat@bonita restart
        rm -f /var/www/d7/sites/default/files/swf/cookie_bonita*
        rm -f /var/www/d7/sites/default/files/restart_bonita.txt
fi

if [ -f /var/www/d7/sites/default/files/restart_solr.txt ]
then
        echo -e "\n\t\tRestarting Solr...\n" >> /var/log/messages
        systemctl restart solr
        rm -f /var/www/d7/sites/default/files/restart_solr.txt
fi

if [ -f /var/www/d7/sites/default/files/restart_soffice.txt ]
then
        echo -e "\n\t\tRestarting soffice...\n" >> /var/log/messages
        systemctl restart soffice
        rm -f /var/www/d7/sites/default/files/restart_soffice.txt
fi

# Stop services if needed
if [ -f /var/www/d7/sites/default/files/stop_alfresco.txt ]
then
        echo -e "\n\t\tStopping Alfresco...\n" >> /var/log/messages
        service tomcat@alfresco stop
        rm -f /var/www/d7/sites/default/files/stop_alfresco.txt
fi

if [ -f /var/www/d7/sites/default/files/stop_bonita.txt ]
then
        echo -e "\n\t\tStopping Bonita...\n" >> /var/log/messages
        service tomcat@bonita stop
        rm -f /var/www/d7/sites/default/files/swf/cookie_bonita*
        rm -f /var/www/d7/sites/default/files/stop_bonita.txt
fi

if [ -f /var/www/d7/sites/default/files/stop_solr.txt ]
then
        echo -e "\n\t\tStopping Solr...\n" >> /var/log/messages
        service solr stop
        rm -f /var/www/d7/sites/default/files/stop_solr.txt
fi

if [ -f /var/www/d7/sites/default/files/stop_soffice.txt ]
then
        echo -e "\n\t\tStopping soffice...\n" >> /var/log/messages
        systemctl stop soffice
        rm -f /var/www/d7/sites/default/files/stop_soffice.txt
fi

# Edit my.cnf if needed
if [ -f /var/www/d7/sites/default/files/my.cnf ]
then
        source ~/.bashrc
        \cp -Rf /var/www/d7/sites/default/files/my.cnf /etc/my.cnf
        rm -f /var/www/d7/sites/default/files/my.cnf
        systemctl restart mysqld
fi

# Check Soffice status ( cannot be done with PHP for the moment )
if ps ax | grep -v grep | grep "/opt/libreoffice" > /dev/null
then
	rm -f /var/www/d7/sites/default/files/soffice_status.txt
        echo "soffice:OK" > /var/www/d7/sites/default/files/soffice_status.txt
else
	rm -f /var/www/d7/sites/default/files/soffice_status.txt
        echo "soffice:KO" > /var/www/d7/sites/default/files/soffice_status.txt
fi
