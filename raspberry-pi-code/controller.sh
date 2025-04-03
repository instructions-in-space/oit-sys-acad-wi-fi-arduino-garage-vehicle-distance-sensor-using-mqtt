#!/usr/bin/bash

while : ; do
	latest_door_line=$(tail -n 1 door_log.txt)
	if [[ "$latest_door_line" =~ open ]]; then
		latest_distance_line=$(tail -n 1 distance_log.txt)
		if [ $latest_distance_line -gt 50 ]; then
			#echo "green"
			mosquitto_pub -t garage/led -m 'green'
		elif [ $latest_distance_line -lt 51 ] && [ $latest_distance_line -gt 25 ]; then
			#echo "yellow"
			mosquitto_pub -t garage/led -m 'yellow'
		elif [ $latest_distance_line -lt 26 ] && [ $latest_distance_line -gt 12 ]; then
			#echo "red"
			mosquitto_pub -t garage/led -m 'solid_red'
		elif [ $latest_distance_line -lt 13 ]; then
			#echo "flashing red"
			mosquitto_pub -t garage/led -m 'flashing_red'
		fi
	elif [[ "$latest_door_line" =~ closed ]]; then
		mosquitto_pub -t garage/led -m 'closed'
	fi
done

