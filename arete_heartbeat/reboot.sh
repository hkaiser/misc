cd /home/zbyerly/arete_heartbeat
touch reboot.log
TIME=`date`
echo "finished rebooting at $TIME" >> reboot.log

echo "finished rebooting at $TIME" | mail -s "durandal has rebooted" zbyerly@cct.lsu.edu