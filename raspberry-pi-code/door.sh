#!/usr/bin/bash

while read door_topic; do
	echo $door_topic >> door_log.txt
	echo $door_topic
	if [[ $door_topic =~ open ]]; then
		echo "It's open!"
		#bash distance.sh
	elif [[ $door_topic =~ closed ]]; then
		#mosquitto_pub -t garage/led -m 'closed'
		echo "It's closed."
	fi
done < <(mosquitto_sub -h 192.168.180.36 -t garage/door)

