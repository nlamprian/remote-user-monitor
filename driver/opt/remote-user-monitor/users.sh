#!/bin/bash

for pts in $(ps ax | grep sshd | grep @pts/ | awk -F ': ' '{print $2}' | awk -F '@' '{print $2}'); do
	pinky -f | grep $pts | rev | cut -d' ' -f1  | rev
done
