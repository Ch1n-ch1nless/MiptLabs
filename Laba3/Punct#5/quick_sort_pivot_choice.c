#include "quick_sort_pivot_choice.h"

#define MAX(a, b) (a > b) ? a : b
#define MIN(a, b) (a < b) ? a : b

/*=================<Get pivot>================*/

static int GetCentalPivot(int* array, int begin, int end)
{
    assert((array != NULL) && "ERROR!!! Pointer to \'array\' is NULL!\n");

    int middle = begin + (end - begin) / 2;

    return array[middle];
}

static int GetMedianOfThreeElements(int* array, int begin, int end)
{
    assert((array != NULL) && "ERROR!!! Pointer to \'array\' is NULL!\n");

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

static int GetRandomPivot(int* array, int begin, int end)
{
    assert((array != NULL) && "ERROR!!! Pointer to \'array\' is NULL!\n");

    int middle = begin + rand() % (end - begin);

    return array[middle];
}

static int GetMedianOfThreeRandomElements(int* array, int begin, int end)
{
    assert((array != NULL) && "ERROR!!! Pointer to \'array\' is NULL!\n");

    int index1 = begin + rand() % (end - begin);
    int index2 = begin + rand() % (end - begin);
    int index3 = begin + rand() % (end - begin);

    int value1  = array[index1];
    int value2  = array[index2];
    int value3  = array[index3];

    if (value1 <= value2 && value2 <= value3)
    {
        return value2;
    }
    else if (value1 <= value2)
    {
        return MAX(value1, value3);
    }
    else if (value2 <= value3)
    {
        return MIN(value1, value3);
    }
    
    //if value1 > value2 > value3
    return value2;
}
/*============================================*/

static void _swap(int* const elem1, int* const elem2)
{
    assert((elem1 != NULL) && "Pointer to \'elem1\' is NULL!!!\n");
    assert((elem2 != NULL) && "Pointer to \'elem2\' is NULL!!!\n");

    int temp = *elem1;
    *elem1 = *elem2;
    *elem2 = temp;
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

static void _hoar_quick_sort(int* const array, const int begin, const int end, int (*get_pivot)(int* array, int begin, int end))
{
    assert((array != NULL) && "Pointer to \'array\' is NULL!!!\n");

    if (begin < end)
    {
        int pivot       = get_pivot(array, begin, end);
        int new_begin   = 0;
        int new_end     = 0;
        
        _hoar_partition(array, begin, end, pivot, &new_begin, &new_end);

        if (begin < new_end)
        {
            _hoar_quick_sort(array, begin, new_end, get_pivot);
        }

        if (new_begin < end)
        {
            _hoar_quick_sort(array, new_begin, end, get_pivot);
        }
    }
}

void QuickSortWithCentralPivot(int* const array, const size_t array_size)
{
    assert((array != NULL) && "ERROR!!! Pointer to \'array\' is NULL!\n");

    _hoar_quick_sort(array, 0, array_size - 1, GetCentalPivot);
}

void QuickSortWithMedianOf3Elements(int* const array, const size_t array_size)
{
    assert((array != NULL) && "ERROR!!! Pointer to \'array\' is NULL!\n");

    _hoar_quick_sort(array, 0, array_size - 1, GetMedianOfThreeElements);
}

void QuickSortWithRandomPivot(int* const array, const size_t array_size)
{
    assert((array != NULL) && "ERROR!!! Pointer to \'array\' is NULL!\n");

    _hoar_quick_sort(array, 0, array_size - 1, GetRandomPivot);
}

void QuickSortWithMedianOf3RandomElements(int* const array, const size_t array_size)
{
    assert((array != NULL) && "ERROR!!! Pointer to \'array\' is NULL!\n");

    _hoar_quick_sort(array, 0, array_size - 1, GetMedianOfThreeRandomElements);
}