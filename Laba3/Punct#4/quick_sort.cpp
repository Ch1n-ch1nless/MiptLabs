#include "testing.h"

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
    assert((array != NULL) && "Pointer to \'array\' is NULL!!!\n");
    assert((begin <= end)  && "Incorrect values of begin and end!!!\n");

    int index1 = begin + rand() % (end - begin);
    int index2 = begin + rand() % (end - begin);
    int index3 = begin + rand() % (end - begin);

    if (array[index1] < array[index2])
    {
        if (array[index3] < array[index1])
        {
            return array[index1];
        }

        return (array[index2] < array[index3]) ? array[index2] : array[index3];
    }
    
    if (array[index3] < array[index2])
    {
        return array[index2];
    }

    return (array[index1] < array[index3]) ? array[index1] : array[index3];
}

static int _lomuto_partition(int* const array, const int begin, const int end)
{
    assert((array != NULL) && "Pointer to \'array\' is NULL!!!\n");
    assert((begin <= end)  && "Incorrect values of begin and end!!!\n");

    int pivot = _get_pivot(array, begin, end);

    int left_index = begin;

    _swap(array + end, array + begin + (end - begin) / 2);

    for (int right_index = begin; right_index <= end; ++right_index)
    {
        if (array[right_index] < pivot)
        {
            _swap(array + left_index, array + right_index);
            left_index++;
        }
    }

    _swap(array + end, array + left_index);

    return left_index;
}

static void _lomuto_quick_sort(int* const array, const int begin, const int end)
{
    assert((array != NULL) && "Pointer to \'array\' is NULL!!!\n");

    if (begin < end)
    {
        int pivot_index = _lomuto_partition(array, begin, end);

        _lomuto_quick_sort(array, begin, pivot_index - 1);
        _lomuto_quick_sort(array, pivot_index + 1, end);
    }
}

static void _hoara_partition(int* const array, const int begin, const int end, const int pivot, int* const new_begin, int* const new_end)
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

static void _hoara_quick_sort(int* const array, const int begin, const int end)
{
    assert((array != NULL) && "Pointer to \'array\' is NULL!!!\n");

    if (begin < end)
    {
        int pivot = _get_pivot(array, begin, end);
        int new_begin = 0;
        int new_end   = 0;

        _hoara_partition(array, begin, end, pivot, &new_begin, &new_end);

        if (begin < new_end)
        {
            _hoara_quick_sort(array, begin, new_end);
        }

        if (new_begin < end)
        {
            _hoara_quick_sort(array, new_begin, end);
        }
    }
}

static void _flag_partition(int* const array, int begin, int end, int* const equals_from, int* const equals_to)
{
    assert((array != NULL) && "Pointer to \'array\' is NULL!!!\n");
    assert((equals_from != NULL) && "Pointer to \'equals_from\' is NULL!!!\n");
    assert((equals_to != NULL) && "Pointer to \'equals_to\' is NULL!!!\n");

    int pivot = _get_pivot(array, begin, end);

    int middle = begin;

    while (middle <= end)
    {
        if (array[middle] < pivot)
        {
            _swap(array + begin, array + middle);
            begin++;
            middle++;
        } 
        else if (array[middle] == pivot)
        {
            middle++;
        }
        else
        {
            _swap(array + middle, array + end);
            end--;
        }
    }

    *equals_from = begin;
    *equals_to   = end;
}

static void _flag_quick_sort(int* const array, int begin, int end)
{
    assert((array != NULL) && "Pointer to \'array\' is NULL!!!\n");

    if (begin < end)
    {
        int pivot = _get_pivot(array, begin, end);
        int equals_from = 0;
        int equals_to   = 0;

        _flag_partition(array, begin, end, &equals_from, &equals_to);

        if (begin < equals_from)
        {
            _flag_quick_sort(array, begin, equals_from - 1);
        }

        if (equals_to < end)
        {
            _flag_quick_sort(array, equals_to + 1, end);
        }
    }
}

static void _one_branch_quick_sort(int* const array, int begin, int end)
{
    assert((array != NULL) && "Pointer to \'array\' is NULL!!!\n");

    while (begin < end)
    {
        int pivot = _get_pivot(array, begin, end);
        int new_begin = 0;
        int new_end   = 0;

        _hoara_partition(array, begin, end, pivot, &new_begin, &new_end);

        if (begin < new_end)
        {
            _one_branch_quick_sort(array, begin, new_end);
        }

        begin = new_begin;
    }
}

void QuickSort(int* const array, const int array_size)
{
    assert((array != NULL) && "Pointer to \'array\' is NULL!!!\n");
    
    if (array_size == 0) return;

    _hoara_quick_sort(array, 0, array_size - 1);
}