#!/bin/sh
make
./server &
sleep 0.2
# for arg in "$@"; do
# 	./client $(pidof server) "$arg"
# done
./client $(pidof server) "$@"
kill $(pidof server)
