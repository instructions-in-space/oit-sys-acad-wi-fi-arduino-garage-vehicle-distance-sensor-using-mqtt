#!/usr/bin/bash

while read topic; do
	echo $topic >> log.txt
	if [ $topic -gt 50 ]; then
		#echo "green"
		mosquitto_pub -t garage/led -m 'green'
	elif [ $topic -lt 51 ] && [ $topic -gt 25 ]; then
		#echo "yellow"
		mosquitto_pub -t garage/led -m 'yellow'
	elif [ $topic -lt 26 ] && [ $topic -gt 12 ]; then
		#echo "red"
		mosquitto_pub -t garage/led -m 'solid_red'
	elif [ $topic -lt 13 ]; then
		#echo "flashing red"
		mosquitto_pub -t garage/led -m 'flashing_red'
	fi

#done < <(mosquitto_sub -h 127.0.0.1 -t garage/distance)
done < <(mosquitto_sub -h 192.168.180.36 -t garage/distance)

