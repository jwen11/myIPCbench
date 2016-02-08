#!/bin/bash
taskset 4 ./messagerA & 
taskset 5 ./messagerA 100 &
taskset 3 ./messagerA 50 &

taskset 6 ./messagerB &
taskset 7 ./messagerB 100 &
taskset 2 ./messagerB 50 &
