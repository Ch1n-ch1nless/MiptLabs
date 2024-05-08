#!/bin/bash

from=100000
to=1000000
step=100000

mkdir "Tests"

for (( i=$from; i <= $to; i += $step))
do
touch "Tests/insert_${i}.in"
./TestGenerator/create_test.exe $i "Tests/insert_${i}.in"
done

from=50000
to=500000
step=50000

for (( i=$from; i <= $to; i += $step))
do
touch "Tests/delete_${i}.in"
./TestGenerator/create_test.exe $i "Tests/delete_${i}.in"
done

touch "Tests/sorted_insert_1000000.in"
./TestGenerator/create_sorted_test.exe 1000000 "Tests/sorted_insert_1000000.in"

touch "Tests/sorted_delete_500000.in"
./TestGenerator/create_sorted_test.exe 500000 "Tests/sorted_delete_500000.in"