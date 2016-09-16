#!/bin/bash

#Get UIDs

#Get joblist
echo `./parsecsvtojoblist.sh jobList.csv | tail -n +2 > jobs.txt`;

paste -d % uids.txt jobs.txt > temp;


#add head & tail

# eg { 2657528197 , 0 , { 1,2,3,1,1,1,1,2,3,1 } }
awk '{printf(" { %s },\n", $0)}' temp > cardList.h

rm temp;

#less jobList.h

#echo "card cards[40] = {" > jobList.h;
sed -i '1s/^/card cards[40] = {\n/' cardList.h
sed -i 's/%/\, 0\, /g' cardList.h
echo "};" >> cardList.h

cat cardList.h
