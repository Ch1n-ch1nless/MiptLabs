#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*===Structs_&_Constants===*/

// Point on graphic with coordinates: (size of array; time of sorting this array)
typedef struct GraphicPoint
{
    size_t size;
    double time;
} GraphicPoint;

const char* const VERY_SMALL_TESTS_PATH     = "very_small_tests/";
const char* const SMALL_TESTS_PATH          = "small_tests/";
const char* const BIG_TESTS_PATH            = "big_tests/";
const char* const TEST_MOST_DUBLICATES_PATH = "test_most_dublicates/";

const int TRUE  = 1;
const int FALSE = 0;

/*===Declaration_of_sortings===*/

void    BubbleSort(int* const array, const size_t array_size);
void    InsertionSort(int* const array, const size_t array_size);
void    SelectionSort(int* const array, const size_t array_size);

void    ShellSort(int* const array, const int array_size);

void    RecursiveMergeSort(int* const array, const size_t array_size);
void    IterativeMergeSort(int* const array, const size_t array_size);

void    QuickSort(int* const array, const int array_size);

void    HeapSort(int* const array, const int array_size);

void    IntroSort(int* const array, const int array_size);

void    LeastSignificantDigitSort(int* const src_array, const int array_size);
void    MostSignificantDigitSort(int* const array, const int array_size);

/*===Test_programms===*/

FILE*   OpenFile(const char* const dir_path, const size_t cur_size, const size_t k, const char* const extension);

void    TestCorrectnessOfSortings(const char* const dir_path, const size_t from, const size_t to, 
                                  const size_t step, FILE* time_list, size_t number_of_repetitions,
                                  void (*sort_function) (int* const array, const int array_size));

