#!/bin/bash

START=0
END=(`cat jobStrings.h | wc -l`)-1

#echo $LIMIT

echo
echo "/*array*/"
echo
echo -n "const char* const jobStringTable[] PROGMEM = {"

for (( c=$START; c<$END; c++ ))
do
	echo -n "jobString$c"
	
	if [ "$c" != `echo -n $(($END-1))` ]; then
			echo -n ", "
    fi
done
 
echo -e " };" 
echo





