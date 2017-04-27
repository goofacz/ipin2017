#!/bin/sh
opp_runall -j5 ../src/ipin2017 -u Cmdenv -r 0..10000 -n ../src:.:../../inet/examples:../../inet/src:../../inet/tutorials -l ../../inet/src/INET --debug-on-errors=false omnet.ini -c Whistle_stationary_imperfect_clock
