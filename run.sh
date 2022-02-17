#!/bin/bash

CURRENT_DIRECTORY=$(cd `dirname $0` && pwd)

if [[ "$#" != "1" ]];
then
   echo "Expected single argument: JabberHive socket to connect to."
   exit
fi

while true
do
   /my/jabberhive_backup/gateway/irc/bin2/jabberhive-irc $1 "irc.foonetic.net" "nightredbot" "#projectjen" "6667" -u "JabberHive" -r "JabberHive IRC Gateway" -c
done
