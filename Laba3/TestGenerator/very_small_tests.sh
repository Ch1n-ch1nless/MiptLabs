#!/bin/bash
from=0
to=150
step=1
max_value=32768

mkdir "very_small_tests"

for (( i=$from; i <= $to; i += $step))
do
for (( k=0; k < 5; k++ ))
do
touch "very_small_tests/${i}_${k}.in"
touch "very_small_tests/${i}_${k}.out"
./TestGenerator/create_random_array.exe $i $max_value "very_small_tests/${i}_${k}.in" $RANDOM
./TestGenerator/qsort_random_array.exe $i "very_small_tests/${i}_${k}.in" "very_small_tests/${i}_${k}.out"
done
done