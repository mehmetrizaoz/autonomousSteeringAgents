#!/bin/sh
####################################################
# generate.sh : runs static analysis
# Usage       : run.sh &
#
# Todo List  :
#
# Date       : 21/05/2021
# Author     : Mehmet Rıza ÖZ
#####################################################

echo "### static analysis result"
cppcheck --enable=style ../../src/
cppcheck --enable=style ../../main.cpp
