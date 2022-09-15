#!/bin/bash

SUCCESSFUL_TESTS=0
FAILED_TESTS=0
TEXTFILE1="../test/text1.txt"
TEXTFILE2="../test/text2.txt"
PATTERNFILE="../test/patterns.txt"
MYUTIL="valgrind ./s21_grep"
STDUTIL="grep"
MYUTIL_OUTPUT="s21grep_output.txt"
STDUTIL_OUTPUT="grep_output.txt"
PATTERN1="dolor"
PATTERN2="dorem"
LEAKS="-e \"^Process.[0-9]\" "
LOG="log_grep.txt"
date >  $LOG
for flag1 in  -v -c -l -n -i -s -o -h
do
    TEST1="$flag1 $PATTERN1 $TEXTFILE1"
    $MYUTIL $TEST1

    TEST2="$flag1 -e $PATTERN1 -e $STDUTIL $TEXTFILE1"
    $MYUTIL $TEST2

    TEST3="$flag1 -f $PATTERNFILE $TEXTFILE1"
    $MYUTIL $TEST3

    TEST4="$flag1 $PATTERN1 $TEXTFILE1 $TEXTFILE2"
    $MYUTIL $TEST4

    TEST5="$flag1 -e $PATTERN1 -e $STDUTIL $TEXTFILE1 $TEXTFILE2"
    $MYUTIL $TEST5

    TEST6="$flag1 -f $PATTERNFILE $TEXTFILE1 $TEXTFILE2"
    $MYUTIL $TEST6

    # -e and -f combination

    TEST7="$flag1 -e $PATTERN2 -f $PATTERNFILE $TEXTFILE1 $TEXTFILE2"
    $MYUTIL $TEST7
done

for flag1 in  -v -c -l -n -i -s -o -h
do
    for flag2 in  -v -c -l -n -i -s -o -h
    do
        if [ $flag1 != $flag2 ]
        then
            TEST1="$flag1 $flag2 $PATTERN1 $TEXTFILE1"
            $MYUTIL $TEST1  

            TEST2="$flag1 $flag2 -e $PATTERN1 -e $STDUTIL $TEXTFILE1"
            $MYUTIL $TEST2 

            TEST3="$flag1 $flag2 -f $PATTERNFILE $TEXTFILE1"
            $MYUTIL $TEST3


            # SAME 3 TEST WITH 2 FILES

            TEST4="$flag1 $flag2 $PATTERN1 $TEXTFILE1 $TEXTFILE2"
            $MYUTIL $TEST4

            TEST5="$flag1 $flag2 -e $PATTERN1 -e $STDUTIL $TEXTFILE1 $TEXTFILE2"
            $MYUTIL $TEST5
           

            TEST6="$flag1 $flag2 -f $PATTERNFILE $TEXTFILE1 $TEXTFILE2"
            $MYUTIL $TEST6
            # -e and -f combination

            TEST7="$flag1 $flag2 -e $PATTERN2 -f $PATTERNFILE $TEXTFILE1 $TEXTFILE2"
            $MYUTIL $TEST7
            fi
    done
done

