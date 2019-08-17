#!/bin/bash

for pid in $(ps ax | grep sshd | grep @pts/ | awk -F ' ' '{print $1}'); do
	kill -1 $pid
done

killall rosmaster

source /opt/ros/melodic/setup.bash
yes | rosnode cleanup
