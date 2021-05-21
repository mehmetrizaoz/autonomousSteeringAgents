#!/bin/sh
####################################################
# generate.sh : runs static analysis and unit tests
# Usage       : run.sh &
#
# Todo List  :
#
# Date       : 21/05/2021
# Author     : Mehmet Rıza ÖZ
#####################################################

echo "###run static analysis" > test.out
cppcheck --enable=style ../src/ >> test.out
echo "-------------" >> test.out
cppcheck --enable=style ../main.cpp >> test.out 2>> test.out
echo "-------------" >> test.out
cppcheck --enable=style test_suites.cpp >> test.out
echo "-------------" >> test.out

echo "###run unit tests" >> test.out
./test_suites >> test.out

echo "check test.out file"