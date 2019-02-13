#!/bin/bash
echo "generating the jobs ......."

/home/petgroup/tools/gate_v7.1-install/bin/gjs -numberofsplits 400 -clusterplatform openPBS -openPBSscript /home/petgroup/tools/gate_v7.1/cluster_tools/jobsplitter/script/openPBS.script   ringW.mac

exit
