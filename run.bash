#!/bin/bash
taskset 4 ./messagerA & 

taskset 6 ./messagerB &
