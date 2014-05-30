cd /home/zbyerly/arete_heartbeat
TIME=`date`
SINFO=`ssh -q ARETE sinfo -h --format="%N\ %t"`
if [ $? -eq 0 ]
    then echo "$TIME: SSH to arete.cct.lsu.edu successful." > heartbeat.log.last
else
    echo "$TIME: SSH to arete.cct.lsu.edu unsuccessful!" > heartbeat.log.last
    mail -s "arete.cct.lsu.edu is down." zbyerly@cct.lsu.edu < heartbeat.log.last
    exit
fi

if [[ "$SINFO" =~ "down" ]]; then
    echo "$TIME: WARNING: Some nodes appear to be down." >> heartbeat.log.last
    echo "$SINFO" >> heartbeat.log.last
    mail -s "arete.cct.lsu.edu some compute nodes are down." zbyerly@cct.lsu.edu < heartbeat.log.last
else
    echo "$SINFO" >> heartbeat.log.last
    mail -s "arete.cct.lsu.edu is operating normally." zbyerly@cct.lsu.edu < heartbeat.log.last
fi
 
#cat heartbeat.log.last
   
######## 
touch heartbeat.log
cat heartbeat.log heartbeat.log.last > /tmp/tempfile
mv /tmp/tempfile heartbeat.log