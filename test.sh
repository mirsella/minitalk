#!/bin/sh
make
./server &
sleep 0.2
./client $(pidof server) "$@"
pkill server
