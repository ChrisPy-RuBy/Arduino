#!/bin/bash
set -euo pipefail
# wrapper function to compile and upload files for 
# arduino


main () {
        dir=$PWD/$1
        echo $dir
        if [ -d "$dir" ]; then
                echo "Folder exists, compiling."   
                arduino-cli compile --fqbn arduino:avr:uno $dir
                echo "uploading"
                arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:uno $dir
        else
                echo "Folder doesn't exists" && exit 1
        fi
}

main "$@"
