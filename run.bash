#!/bin/bash
taskset -c 3 ./messagerA & 

taskset -c 4 ./messagerB &
