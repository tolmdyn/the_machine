#######################################################
#How to format instructions to convert into header file
########################################################
#dos2unix
#sed 's/ *[0-9]*. //' The_Machine_instructions.txt > file.txt
#awk '{printf("const char jobstring%d[] = \"%s\";\n", NR, $0)}' file.txt
########################################################

dos2unix instructions.txt; sed 's/ *[0-9]*. //' instructions.txt | awk '{printf("const char jobString%d[] PROGMEM = \"%s\";\n", NR-1, $0)}' > jobStrings.h; ./footer.sh >> jobStrings.h; cat jobStrings.h


put instructions in instructions.txt and then type ./generateJobString.sh into a terminal and it will generate jobStrings.h
