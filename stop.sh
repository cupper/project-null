#!/bin/bash

source init.conf

if [ ! -f $PID_FILE ]; then
	echo "$APP_NAME not started (file $PID_FILE doesn't exist)"
	exit
fi

PID=`cat $PID_FILE`

kill -s SIGINT $PID

WAIT=0
while [ ! "$WAIT" = "30" ]; do
	STOPPED=`ps -p $PID | grep $PID`
	if [ "$STOPPED" = "" ];then
		echo "$APP_NAME stopped"
		exit
	else
		echo -n .
		sleep 1
		let "WAIT += 1"
	fi
done

echo
echo "Can't correctly stop $APP_NAME, finish him!"
kill -9 $PID
rm -f $PID_FILE
