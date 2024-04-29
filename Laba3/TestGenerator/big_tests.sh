#!/bin/bash
from=0
to=1000000 
step=10000
max_value=32768

mkdir "big_tests"

for (( i=$from; i <= $to; i += $step))
do
touch "big_tests/${i}.in"
touch "big_tests/${i}.out"
./TestGenerator/create_random_array.exe $i $max_value "big_tests/${i}.in" $RANDOM
./TestGenerator/qsort_random_array.exe $i "big_tests/${i}.in" "big_tests/${i}.out"
done