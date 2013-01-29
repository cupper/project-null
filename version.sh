#!/bin/bash

MAJOR=1
MINOR=0
REVISION=`svn info | grep Revision | sed s/Revision:\ //`

if [[ "$REVISION" == "" ]]; then
	REVISION=`svn info | grep Редакция: | sed s/Редакция:\ //`
fi

if [[ "$REVISION" == "" ]]; then
	echo "Cannot recognize number of revision"
	exit 1
fi

VERSION=$MAJOR.$MINOR.$REVISION

if [[ $1 == "show" ]]; then
	echo $VERSION
	exit
fi

echo "Update source version.cpp"
echo "current version: $VERSION"

VER_CPP=src/version.cpp
echo "#include \"version.h\"" > $VER_CPP
echo "const char* VERSION = \"$VERSION\";" >> $VER_CPP
