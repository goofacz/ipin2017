#!/bin/sh
opp_runall -j5 ../src/ipin2017 -u Cmdenv -r 0..10000 -n ../src:.:../../inet/examples:../../inet/src:../../inet/tutorials -l ../../inet/src/INET --debug-on-errors=false tdoa.ini -c TDoA_moving_imperfect_clock
