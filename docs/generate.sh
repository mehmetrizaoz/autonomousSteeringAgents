#!/bin/sh
####################################################
# generate.sh : generates doxygen outputs
# Usage       : generate.sh &
#
# Todo List  :
#
# Date       : 16/05/2021
# Author     : Mehmet Rıza ÖZ
#####################################################

doxygen Doxyfile
cd latex
make
cp refman.pdf ..
cd ..
rm -rf html latex
