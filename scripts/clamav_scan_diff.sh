#!/bin/bash

#detect files recently modified into some "data" folders
rm -f /tmp/filelist.txt
#contentstore Alfresco
for folder in /var/alfresco/alf_data/contentstore/
do
find $folder -type f -newerct '10 minutes ago' >> /tmp/filelist.txt
done

#index Solr
for folder in /var/solr/data
do
find $folder -type f -newerct '10 minutes ago' >> /tmp/filelist.txt
done

clamscan -r -i --no-summary -f /tmp/filelist.txt >> /var/log/clamd.log
rm -f /tmp/filelist.txt
