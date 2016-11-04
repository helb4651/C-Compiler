#!/usr/bin/env bash
FILE_NAME = None
echo "Running Compiler Regression Test: Assignment 4"
#
#for i in $( cd TestFiles/a3/Q; ls ); do
#    echo item: $ item: $i
#done


make
rm regression_report
./c- -P < TestFiles/a3/scope.c- > temp.Pout
sdiff -s temp.Pout TestFiles/a3/scope.Pout
sdiff temp.Put TestFiles/a3/scope.Pout >> regression_report

if [ -s ]; then
    echo "  Passed: scope.Pout"
else
    echo "  Failed: scope.Pout"
fi