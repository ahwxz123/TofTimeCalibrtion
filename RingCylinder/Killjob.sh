#!/bin/bash 

run=305087
runend=305373

while [ "$run" -le "$runend" ]
do
	  qdel "$run"
	    run=`expr $run + 1`
	done
exit 0
