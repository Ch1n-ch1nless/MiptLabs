#!/bin/bash

from=100000
to=1000000
step=100000

mkdir "Tests"

for (( i=$from; i <= $to; i += $step))
do
touch "Tests/${i}.in"
./TestGenerator/create_test.exe $i "Tests/${i}.in"
done

touch "Tests/sorted_100000.in"
./TestGenerator/create_sorted_test.exe 100000 "Tests/sorted_100000.in"\