#!/bin/bash
from=0
to=1000
step=50
max_value=32768

mkdir "small_tests"

for (( i=$from; i <= $to; i += $step))
do
for (( k=0; k < 5; k++ ))
do
touch "small_tests/${i}_${k}.in"
touch "small_tests/${i}_${k}.out"
./TestGenerator/create_random_array.exe $i $max_value "small_tests/${i}_${k}.in" $RANDOM
./TestGenerator/qsort_random_array.exe $i "small_tests/${i}_${k}.in" "small_tests/${i}_${k}.out"
done
done