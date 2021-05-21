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

echo "### static analysis result" > static_analysis.out
cppcheck --enable=style ../src/ >> static_analysis.out
echo "-------------" >> static_analysis.out
cppcheck --enable=style ../main.cpp >> static_analysis.out 2>> static_analysis.out
echo "-------------" >> static_analysis.out
cppcheck --enable=style test_suites.cpp >> static_analysis.out
echo "-------------" >> static_analysis.out

echo "### unit tests result" > unit_test.out
./test_suites >> unit_test.out

echo "check test.out file"