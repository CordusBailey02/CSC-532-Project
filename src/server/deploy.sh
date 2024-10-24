#!/bin/bash

if [ $# -eq 0 ]; then
    echo "Usage: $0 <start|stop> <number_of_instances>"
    exit 1
fi

action=$1
num_instances=$2

if [ "$action" != "start" ] && [ "$action" != "stop" ]; then
    echo "Invalid action. Please use 'start' or 'stop'."
    exit 1
fi

for i in $(seq 1 $num_instances); do
    port=$((8081 + i - 1))
    
    if [ "$action" = "start" ]; then
        echo "Starting server process on port $port..."
        ./server $port &
    elif [ "$action" = "stop" ]; then
        echo "Stopping server process on port $port..."
        pkill -f "server $port"
    fi
done

echo "All server processes $action."