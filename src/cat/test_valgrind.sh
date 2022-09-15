#!/bin/bash

SUCCESSFUL_TESTS=0
FAILED_TESTS=0
TEXTFILE1="../test/text1.txt"
TEXTFILE2="../test/text2.txt"
PATTERNFILE="../test/bytes"
MYUTIL="valgrind ./s21_cat"
STDUTIL="cat"
MYUTIL_OUTPUT="s21grep_output.txt"
STDUTIL_OUTPUT="cat_output.txt"
PATTERN1="dolor"
PATTERN2="dorem"
LEAKS="-e \"^Process.[0-9]\" "
LOG="log_cat.txt"
date >  $LOG
for flag1 in  -b -e -n -s -t -v
do
    TEST1="$flag1 $TEXTFILE1"
    $MYUTIL $TEST1

    TEST2="$flag1 $TEXTFILE1"
    $MYUTIL $TEST2

    TEST3="$flag1 $PATTERNFILE $TEXTFILE1 $TEXTFILE2"
    $MYUTIL $TEST3
    # -e and -f combination
done

for flag1 in  -b -e -n -s -t -v
do
    for flag2 in  -b -e -n -s -t -v
    do
        if [ $flag1 != $flag2 ]
        then
            TEST1="$flag1 $flag2 $TEXTFILE1"
            $MYUTIL $TEST1

            TEST2="$flag1 $flag2 $TEXTFILE1"
            $MYUTIL $TEST2

            TEST3="$flag1 $flag2 $PATTERNFILE $TEXTFILE1 $TEXTFILE2"
            $MYUTIL $TEST3
            fi
    done
done

