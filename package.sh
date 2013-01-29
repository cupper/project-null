#!/bin/sh

VERSION=`./version.sh show`
PACKAGE=ss_gateway.$VERSION.tar.bz2

echo "Create instalation package of 'SS Gateway' ($PACKAGE)"

TEMP_FOLDER=ss_gateway
BIN=build/release/ss_gateway
START_SH=start.sh
STOP_SH=stop.sh
INI=ini
CONF=gateway.conf
MAPPING=radio_to_mcc.map
TRACKLIST=track.list
LOG_DIR=logs

if [ -d $TEMP_FOLDER ]; then
	rm -rf $TEMP_FOLDER
fi

mkdir $TEMP_FOLDER

echo copy $BIN
cp $BIN $TEMP_FOLDER

echo copy $START_SH
cp $START_SH $TEMP_FOLDER

echo copy $STOP_SH
cp $STOP_SH $TEMP_FOLDER


echo copy $INI/*.*
cp -r $INI $TEMP_FOLDER

echo copy $CONF
cp $CONF $TEMP_FOLDER

echo copy $MAPPING
cp $MAPPING $TEMP_FOLDER

echo copy $TRACKLIST
cp $TRACKLIST $TEMP_FOLDER

echo creat $LOG_DIR
mkdir $TEMP_FOLDER/$LOG_DIR

tar -cvjf $PACKAGE $TEMP_FOLDER
rm -rf $TEMP_FOLDER
