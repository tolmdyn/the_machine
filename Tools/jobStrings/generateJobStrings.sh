#!/bin/bash

#######################################################
#How to format instructions to convert into header file
########################################################
#dos2unix
#sed 's/ *[0-9]*. //' The_Machine_instructions.txt > file.txt
#awk '{printf("const char jobstring%d[] = \"%s\";\n", NR, $0)}' file.txt
########################################################



dos2unix instructions.txt; echo "#define MAX_JOBS `cat instructions.txt | wc -l;echo;echo`" > jobStrings.h
sed 's/ *[0-9]*. //' instructions.txt | awk '{printf("const char jobString%d[] PROGMEM = \"%s\";\n", NR-1, $0)}' >> jobStrings.h; ./footer.sh >> jobStrings.h; cat jobStrings.h





