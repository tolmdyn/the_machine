#!/bin/bash
OLDIFS=$IFS
IFS=","

while read cardid job1 job2 job3 job4
do
	echo -e "{$job1, $job2, $job3}"
done < "$1"

IFS=$OLDIFS

#echo -e "[$job1, $job2]\n"
