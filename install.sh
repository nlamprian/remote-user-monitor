#!/bin/bash

INSTALL_SCRIPT_PATH="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
cd $INSTALL_SCRIPT_PATH/driver

declare -a SRC_FILES
declare -a DST_FILES
for file in $(find . -type f); do
	SRC_FILES+=($file)
	DST_FILES+=(`echo $file | cut -c2-`)
done


function prompt {
	echo -e "You are about to $1 the following files:"
	echo "$2" | tr ' ' '\n' | sed 's/^/ /'
	read -p "Do you want to continue? [Y/n] "
	[[ ! $REPLY =~ ^[Yy]$ ]] && [[ -n $REPLY ]]
}


function install {
	prompt 'install' "${DST_FILES[*]}"
	if [ $? -eq 0 ]; then return; fi

	for (( i=0; i<${#SRC_FILES[@]}; ++i )); do
		DESTINATION=$(dirname "${DST_FILES[$i]}")
		if [ ! -d $DESTINATION ]; then mkdir -p $DESTINATION; fi
		echo "Installing... ${DST_FILES[$i]}"
		cp ${SRC_FILES[$i]} $DESTINATION
	done

	systemctl enable --now remote-user-monitor.service
}


function uninstall {
	FILES=${DST_FILES[*]}
	for dir in $(find . -type d | grep remote-user-monitor); do
		FILES+=(`echo $dir | cut -c2-`)
	done

	prompt 'uninstall' "${FILES[*]}"
	if [ $? -eq 0 ]; then return; fi

	systemctl stop remote-user-monitor.service
	systemctl disable remote-user-monitor.service

	for file in ${FILES[@]}; do
		if [ -a $file ]; then
			echo "Deleting... $file"
			rm -r $file
		fi
	done
}


case $1 in
	-u)
	uninstall
	;;
	"")
	install
	;;
	*)
	echo "Error: unknown argument"
	echo "Usage: install.sh [-u]"
esac
