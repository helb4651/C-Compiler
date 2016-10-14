#!/bin/bash

echo "Running Compiler Regression Test: Assignment 3"

make
rm regression_report
./c- < TestFiles/a3/scope.c- > myscope.out
sdiff -s myscope.out TestFiles/a3/scope.out
sdiff myscope.out TestFiles/a3/scope.out >> regression_report
