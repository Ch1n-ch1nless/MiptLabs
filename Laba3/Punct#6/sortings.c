#include "sortings.h"

#define MAX(a, b) (a > b) ? a : b
#define MIN(a, b) (a < b) ? a : b

static void _swap(int* const elem1, int* const elem2)
{
    assert((elem1 != NULL) && "Pointer to \'elem1\' is NULL!!!\n");
    assert((elem2 != NULL) && "Pointer to \'elem2\' is NULL!!!\n");

    int temp = *elem1;
    *elem1 = *elem2;
    *elem2 = temp;
}

static int _get_pivot(int* const array, const int begin, const int end)
{
    assert((array != NULL)  && "Pointer to \"array\" is NULL!!!\n");

    int middle = begin + (end - begin) / 2;

    int left_value  = array[begin];
    int mid_value   = array[middle];
    int right_value = array[end];

    if (left_value <= mid_value && mid_value <= right_value)
    {
        return mid_value;
    }
    else if (left_value <= mid_value)
    {
        return MAX(left_value, right_value);
    }
    else if (mid_value <= right_value)
    {
        return MIN(left_value, right_value);
    }
    
    //if left_value > mid_value > right_value
    return mid_value;
}

static void _hoar_partition(int* const array, const int begin, const int end, const int pivot, int* const new_begin, int* const new_end)
{
    assert((array != NULL)  && "Pointer to \"array\" is NULL!!!\n");
    assert((begin >= 0)     && "Function has incorrect value of \"begin\"!!!\n");
    assert((end >= begin)   && "Function has incorrect value of \"end\"!!\n");
    assert((new_begin != NULL)  && "Pointer to \"new_begin\" is NULL!!!\n");
    assert((new_end   != NULL)  && "Pointer to \"new_end\"   is NULL!!!\n");

    *new_begin  = begin;
    *new_end    = end;

    while ((*new_begin) <= (*new_end))
    {
        while (array[*new_begin] < pivot) { (*new_begin)++; }
        while (array[*new_end] > pivot)   { (*new_end)--; }

        if (*new_begin <= *new_end)
        {
            _swap(array + *new_begin, array + *new_end);
            (*new_begin)++;
            (*new_end)--;
        }
    }
}

static void _quick_sort(int* const array, const int begin, const int end)
{
    assert((array != NULL) && "Pointer to \'array\' is NULL!!!\n");

    if (begin < end)
    {
        int pivot       = _get_pivot(array, begin, end);
        int new_begin   = 0;
        int new_end     = 0;
        
        _hoar_partition(array, begin, end, pivot, &new_begin, &new_end);

        if (begin < new_end)
        {
            _quick_sort(array, begin, new_end);
        }

        if (new_begin < end)
        {
            _quick_sort(array, new_begin, end);
        }
    }
}

void QuickSort(int* const array, const size_t array_size)
{
    assert((array != NULL) && "Pointer to \'array\' is NULL!!!\n");

    _quick_sort(array, 0, array_size - 1);
}

void ShellSort(int* const array, const size_t array_size)
{
    assert((array != NULL) && "Pointer to \'array\' is NULL!!!\n");

    size_t step = 1;

    while (step <= array_size / 9)
    {
        step = step * 3 + 1;
    }
    while (step > 0)
    {
        for (size_t i = step; i < array_size; i += step)
        {
            int temp = array[i];
            size_t j = i;

            while (j >= step && array[j - step] > temp)
            {
                array[j] = array[j - step];
                j -= step;
            }

            array[j] = temp;
        }

        step /= 3;
    }
}