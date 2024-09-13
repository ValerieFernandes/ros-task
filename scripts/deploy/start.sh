#!/bin/bash

# Get base.sh funcs
source /root/workspace/install/setup.bash
source "$(dirname "$0")/base.sh"

stop_docker

# declare mode, use gpu by default
mode="gpu"

# declare sim, use sim by default
sim="True"

while getopts 'ch' opt; do
    case "$opt" in
        c)
            mode="cpu"
            ;;
        ?|h)
            echo "Usage: $(basename $0) [-c]"
            exit 1
            ;;
    esac
done
shift "$(($OPTIND -1))"

run_docker \
-v $(dirname "$0")/../../workspace/:/root/workspace/src \
limo_bot:sim "/root/app.sh"
