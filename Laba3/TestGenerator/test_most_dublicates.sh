#!/bin/bash
from=0
to=1000000 
step=10000
max_value=10000

mkdir "test_most_dublicates"

for (( i=$from; i <= $to; i += $step))
do
touch "test_most_dublicates/${i}_0.in"
touch "test_most_dublicates/${i}_0.out"
./TestGenerator/create_random_array.exe $i $max_value "test_most_dublicates/${i}_0.in" $RANDOM
./TestGenerator/qsort_random_array.exe $i "test_most_dublicates/${i}_0.in" "test_most_dublicates/${i}_0.out"
done