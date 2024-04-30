#include "merge_sort.h"

#define MIN(a, b) (a < b) ? a : b

static void Merge(int* const array, int* const add_array, const size_t begin, const size_t middle, const size_t end)
{
    assert((array       != NULL) && "Pointer to \'array\'       is NULL!!!\n");
    assert((add_array   != NULL) && "Pointer to \'add_array\'   is NULL!!!\n");

    size_t  left_index  = begin;                        //< Pointer in left  part of array
    size_t  right_index = middle + 1;                   //< Pointer in right part of array
    size_t  merge_index = begin;                        //< Index in new merged array

    while (left_index <= middle && right_index <= end)
    {
        if (array[left_index] <= array[right_index])
        {
            add_array[merge_index] = array[left_index];
            left_index++;
        }
        else
        {
            add_array[merge_index] = array[right_index];
            right_index++;
        }


        merge_index++;
    }

    while (left_index <= middle)
    {
        add_array[merge_index] = array[left_index];
        left_index++;
        merge_index++;
    }

    while (right_index <= end)
    {
        add_array[merge_index] = array[right_index];
        right_index++;
        merge_index++;
    }
    
    for (size_t index = begin; index <= end; index++)
    {
        array[index] = add_array[index];
    }
}

static void _recursive_merge_sort(int* const array, int * const add_array, const size_t begin, const size_t end)
{
    assert((array != NULL) && "Pointer to \'array\' is NULL!!!\n");
    assert((begin <= end) && "Incorrect values of begin and end!!!\n");

    if (begin == end) return;

    size_t middle = begin + (end - begin) / 2;

    _recursive_merge_sort(array, add_array, begin, middle);
    _recursive_merge_sort(array, add_array, middle + 1, end);
    Merge(array, add_array, begin, middle, end);

}

void RecursiveMergeSort(int* const array, const size_t array_size)
{
    assert((array != NULL) && "Pointer to \'array\' is NULL!!!\n");

    if (array_size == 0) return;

    int* add_array = (int*) calloc(array_size, sizeof(int));
    assert((add_array != NULL) && "ERROR!!! Program can not allocate memory!\n");

    _recursive_merge_sort(array, add_array, 0, array_size - 1);

    free(add_array);
}

void IterativeMergeSort(int* const array, const size_t array_size)
{
    assert((array != NULL) && "Pointer to \'array\' is NULL!!!\n");

    int* add_array = (int*) calloc(array_size * 2, sizeof(int));
    assert((add_array != NULL) && "ERROR!!! Program can not allocate memory!\n");

    size_t mid      = 0;
    size_t right    = 0;

    for (size_t cur_size = 1; cur_size < array_size; cur_size = cur_size * 2)
    {
        for (size_t left = 0; left < array_size - 1; left += 2 * cur_size)
        {
            mid     = left + cur_size - 1;
            right   = left + 2 * cur_size - 1;

            if (right >= array_size)
            {
                right = array_size - 1;
            }

            Merge(array, add_array, left, mid, right);
        }
    }

    free(add_array);
}