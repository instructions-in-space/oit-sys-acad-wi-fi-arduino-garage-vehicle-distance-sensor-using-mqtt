#!/usr/bin/bash

while read topic; do
	echo $topic >> log.txt
	if [ $topic -gt 50 ]; then
		echo "Greater than 50cm (green)"
	elif [ $topic -lt 51 ] && [ $topic -gt 25 ]; then
		echo "Less than 51cm and greater than 25cm (yellow)"
	elif [ $topic -lt 26 ] && [ $topic -gt 12 ]; then
		echo "Less than 26cm and greater than 12cm (red)"
	elif [ $topic -lt 13 ]; then
		echo "Less than 13cm (flashing red)"
	fi

#done < <(mosquitto_sub -h 127.0.0.1 -t garage/distance)
done < <(mosquitto_sub -h 192.168.180.36 -t garage/distance)

