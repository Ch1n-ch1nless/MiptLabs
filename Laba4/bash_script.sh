#!/bin/bash

from=100000
to=1000000
step=100000

mkdir "Tests"
touch time_file.csv

gcc create_random_array.cpp -o create_random_array.out

make FLAG = -DLINEAR_BUILD

for (( i=$from; i <= $to; i += $step))
do
touch "Tests/${i}.csv"
./create_random_array.out $i $max_value "Tests/${i}.csv"
./binary_heap.out $i "Tests/${i}.csv" "time_file.csv"
done

make clean
rm create_random_array.out
rm binary_heap.out