#!/usr/bin/bash

while read led_topic; do
	echo $led_topic >> distance_log.txt
	#if [ $led_topic -gt 50 ]; then
		#echo "green"
		#mosquitto_pub -t garage/led -m 'green'
	#elif [ $led_topic -lt 51 ] && [ $led_topic -gt 25 ]; then
		#echo "yellow"
		#mosquitto_pub -t garage/led -m 'yellow'
	#elif [ $led_topic -lt 26 ] && [ $led_topic -gt 12 ]; then
		#echo "red"
		#mosquitto_pub -t garage/led -m 'solid_red'
	#elif [ $led_topic -lt 13 ]; then
		#echo "flashing red"
		#mosquitto_pub -t garage/led -m 'flashing_red'
	#fi
#done < <(mosquitto_sub -h 127.0.0.1 -t garage/distance)
done < <(mosquitto_sub -h 192.168.180.36 -t garage/distance)

