#!/bin/bash
set -euo pipefail
# wrapper function to compile and upload files for 
# arduino


main () {
        dir=$PWD/$1
        echo $dir

        if [[ -d "$dir" ]]; then
                echo "Folder exists, compiling."   
                arduino-cli compile --fqbn arduino:avr:uno $dir
                echo "uploading"
                arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:uno $dir
        else
                echo "Folder doesn't exists" && exit 1
        fi
}


if [[ $# -gt 1 ]]; then
	if [[ $2 == "-k" ]]; then
		echo "Find and kill python processes"
		ps aux | grep -v grep | grep python | awk '{print $2}' | xargs kill
	else
		echo "valid input flags are -k -> kill python processes"
		exit 1;
	fi
fi


main "$@"
