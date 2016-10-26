#!/bin/bash
FILE_NAME = None
echo "Running Compiler Regression Test: Assignment 3"
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


rm regression_report
rm temp.Pout
./c- -P < TestFiles/a3/small.c- > temp.Pout
sdiff -s temp.Pout TestFiles/a3/small.Pout
sdiff temp.Pout TestFiles/a3/small.Pout >> regression_report

if [ -s ]; then
    echo "  Passed: small.Pout"
else
    echo "  Failed: small.Pout"
fi


rm regression_report
rm temp.Pout
./c- -P < TestFiles/a3/tiny.c- > temp.Pout
sdiff -s temp.Pout TestFiles/a3/tiny.Pout
sdiff temp.Pout TestFiles/a3/tiny.Pout >> regression_report

if [ -s ]; then
    echo "  Passed: tiny.Pout"
else
    echo "  Failed: tiny.Pout"
fi

rm regression_report
rm temp.Pout
./c- -P < TestFiles/a3/tinybad.c- > temp.Pout
sdiff -s temp.Pout TestFiles/a3/tinybad.Pout
sdiff temp.Pout TestFiles/a3/tinybad.Pout >> regression_report

if [ -s ]; then
    echo "  Passed: tinybad.Pout"
else
    echo "  Failed: tinybad.Pout"
fi


rm regression_report
rm temp.Pout
./c- -P < TestFiles/a3/tinygood.c- > temp.Pout
sdiff -s temp.Pout TestFiles/a3/tinygood.Pout
sdiff temp.Pout TestFiles/a3/tinygood.Pout >> regression_report

if [ -s ]; then
    echo "  Passed: tinygood.Pout"
else
    echo "  Failed: tinygood.Pout"
fi

rm regression_report
rm temp.Pout
./c- -P < TestFiles/a3/tinyscope.c- > temp.Pout
sdiff -s temp.Pout TestFiles/a3/tinyscope.Pout
sdiff temp.Pout TestFiles/a3/tinyscope.Pout >> regression_report

if [ -s ]; then
    echo "  Passed: tinyscope.Pout"
else
    echo "  Failed: tinyscope.Pout"
fi


rm regression_report
rm temp.Pout
./c- -P < TestFiles/a3/nano.c- > temp.Pout
sdiff -s temp.Pout TestFiles/a3/nano.Pout
sdiff temp.Pout TestFiles/a3/nano.Pout >> regression_report

if [ -s ]; then
    echo "  Passed: nano.Pout"
else
    echo "  Failed: nano.Pout"
fi


rm regression_report
rm temp.Pout
./c- -P < TestFiles/a3/exp.c- > temp.Pout
sdiff -s temp.Pout TestFiles/a3/exp.Pout
sdiff temp.Pout TestFiles/a3/exp.Pout >> regression_report

if [ -s ]; then
    echo "  Passed: exp.Pout"
else
    echo "  Failed: exp.Pout"
fi


rm regression_report
rm temp.Pout
./c- -P < TestFiles/a3/exp2.c- > temp.Pout
sdiff -s temp.Pout TestFiles/a3/exp2.Pout
sdiff temp.Pout TestFiles/a3/exp2.Pout >> regression_report

if [ -s ]; then
    echo "  Passed: exp2.Pout"
else
    echo "  Failed: exp2.Pout"
fi


rm regression_report
rm temp.Pout
./c- -P < TestFiles/a3/arrays.c- > temp.Pout
sdiff -s temp.Pout TestFiles/a3/arrays.Pout
sdiff temp.Pout TestFiles/a3/arrays.Pout >> regression_report

if [ -s ]; then
    echo "  Passed: arrays.Pout"
else
    echo "  Failed: arrays.Pout"
fi

rm regression_report
rm temp.Pout
./c- -P < TestFiles/a3/undefined.c- > temp.Pout
sdiff -s temp.Pout TestFiles/a3/undefined.Pout
sdiff temp.Pout TestFiles/a3/undefined.Pout >> regression_report

if [ -s ]; then
    echo "  Passed: undefined.Pout"
else
    echo "  Failed: undefined.Pout"
fi

rm regression_report
rm temp.Pout
./c- -P < TestFiles/a3/init.c- > temp.Pout
sdiff -s temp.Pout TestFiles/a3/init.Pout
sdiff temp.Pout TestFiles/a3/init.Pout >> regression_report

if [ -s ]; then
    echo "  Passed: init.Pout"
else
    echo "  Failed: init.Pout"
fi

rm regression_report
rm temp.Pout
./c- -P < TestFiles/a3/redefined.c- > temp.Pout
sdiff -s temp.Pout TestFiles/a3/redefined.Pout
sdiff temp.Pout TestFiles/a3/redefined.Pout >> regression_report

if [ -s ]; then
    echo "  Passed: redefined.Pout"
else
    echo "  Failed: redefined.Pout"
fi

rm regression_report
rm temp.Pout
./c- -P < TestFiles/a3/init.c- > temp.Pout
sdiff -s temp.Pout TestFiles/a3/init.Pout
sdiff temp.Pout TestFiles/a3/init.Pout >> regression_report

if [ -s ]; then
    echo "  Passed: init.Pout"
else
    echo "  Failed: init.Pout"
fi

rm regression_report
rm temp.Pout
./c- -P < TestFiles/a3/whileif.c- > temp.Pout
sdiff -s temp.Pout TestFiles/a3/whileif.Pout
sdiff temp.Pout TestFiles/a3/whileif.Pout >> regression_report

if [ -s ]; then
    echo "  Passed: whileif.Pout"
else
    echo "  Failed: whileif.Pout"
fi

rm regression_report
rm temp.Pout
./c- -P < TestFiles/a3/op.c- > temp.Pout
sdiff -s temp.Pout TestFiles/a3/op.Pout
sdiff temp.Pout TestFiles/a3/op.Pout >> regression_report

if [ -s ]; then
    echo "  Passed: op.Pout"
else
    echo "  Failed: op.Pout"
fi

# rm regression_report
# rm temp.Pout
# ./c- -P < TestFiles/a3/everything05.c- > temp.Pout
# sdiff -s temp.Pout TestFiles/a3/everything05.Pout
# sdiff temp.Pout TestFiles/a3/everything05.Pout >> regression_report
#
# if [ -s ]; then
#     echo "  Passed: everything05.Pout"
# else
#     echo "  Failed: everything05.Pout"
# fi


# rm regression_report
# rm temp.Pout
# ./c- -P < TestFiles/a3/overkill.c- > temp.Pout
# sdiff -s temp.Pout TestFiles/a3/overkill.Pout
# sdiff temp.Pout TestFiles/a3/overkill.Pout >> regression_report
#
# if [ -s ]; then
#     echo "  Passed: overkill.Pout"
# else
#     echo "  Failed: overkill.Pout"
# fi
