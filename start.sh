#!/bin/bash

source init.conf

if [ -f $PID_FILE ]; then
	echo "$APP_NAME already started (file $PID_FILE already exist)"
	exit
fi

mkdir -p $LOG_DIR

LOG_FILE=$LOG_DIR/start.log

echo =========================================== >> $LOG_FILE
date >> $LOG_FILE
./projectnull -l $LOG_DIR -c $CONF_FILE -p $PID_FILE >> $LOG_FILE &
