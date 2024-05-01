#include "intro_sort.h"

#define MAX(a, b) (a > b) ? a : b
#define MIN(a, b) (a < b) ? a : b

static void _shell_sort(int* const array, const size_t array_size)
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

static void _swap(int* const ptr1, int* const ptr2)
{
    assert((ptr1 != NULL) && "Pointer to \'ptr1\' is NULL!!!\n");
    assert((ptr2 != NULL) && "Pointer to \'ptr2\' is NULL!!!\n");

    int temp = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = temp;
}

static void _sift_up(Heap* const heap, int index)
{
    assert((heap != NULL) && "Pointer to \'heap\' is NULL!!!\n");

    int parent = 0;

    while (index != 0)
    {
        parent = (index - 1) / heap->children;

        if (heap->data[index] > heap->data[parent])
        {
            _swap(heap->data + index, heap->data + parent);
            index = parent;
        }
        else
        {
            return;
        }
    }
}

static void _sift_down(Heap* const heap, int index)
{
    assert((heap != NULL) && "Pointer to \'heap\' is NULL!!!\n");

    if (index >= heap->size) return;

    int max_index = index;

    while (index * heap->children + 1 < heap->size)
    {
        int child = 0;

        for (int i = 1; i <= heap->children; i++)
        {
            child = index * heap->children + i;

            if (child < heap->size && heap->data[child] > heap->data[max_index])
            {
                max_index = child;
            }
        }

        if (heap->data[index] >= heap->data[max_index])
        {
            break;
        }

        _swap(heap->data + index, heap->data + max_index);
        index = max_index;
    }
}

static void _heap_insert(Heap* const heap, int element)
{
    assert((heap != NULL) && "Pointer to \'heap\' is NULL!!!\n");

    heap->data[heap->size] = element;
    heap->size++;

    _sift_up(heap, heap->size - 1);
}

static int _extract_max(Heap* const heap)
{
    assert((heap != NULL) && "Pointer to \'heap\' is NULL!!!\n");

    int root_value = heap->data[0];

    heap->data[0] = heap->data[--heap->size];

    _sift_down(heap, 0);

    return root_value;
}

static Heap* _heap_ctor(int* const array, const int size, const int children_number)
{
    Heap* heap = (Heap*) calloc(1, sizeof(Heap));
    assert((heap != NULL) && "Program can not allocate memory!\n");

    heap->size      = 0;
    heap->capacity  = size;
    heap->children  = children_number;

    heap->data = (int*) calloc(size, sizeof(int));
    assert((heap->data != NULL) && "Program can not allocate memory!\n");

    for (int i = 0; i < size; i++)
    {
        _heap_insert(heap, array[i]);
    }

    return heap;
}

static void _heap_dtor(Heap* const heap)
{
    assert((heap != NULL) && "Pointer to \'heap\' is NULL!!!\n");

    free(heap->data);
    heap->data = NULL;
    heap->size = 0;
    heap->capacity = 0;
    heap->children = 0;

    free(heap);
}

void _heap_sort(int* const array, const int array_size, const int number_of_childrens)
{
    assert((array != NULL) && "Pointer to \'array\' is NULL!!!\n");

    Heap* temp_heap = _heap_ctor(array, array_size, number_of_childrens);

    for (int i = array_size - 1; i >= 0; i--)
    {
        array[i] = _extract_max(temp_heap);
    }

    _heap_dtor(temp_heap);
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

static void _intro_sort(int* const array, const int begin, const int end, const size_t depth_limit)
{
    assert((array != NULL) && "Pointer to \'array\' is NULL!!!\n");

    if (begin < end)
    {
        if (end - begin < BLOCK_SIZE_FOR_SHELL_SORT)
        {
            _shell_sort(array + begin, end - begin + 1);
            return;
        }

        if (depth_limit == 0)
        {
            _heap_sort(array + begin, end - begin + 1, NUMBER_OF_HEAP_CHILDREN);
            return;
        }

        int pivot       = _get_pivot(array, begin, end);
        int new_begin   = 0;
        int new_end     = 0;
        
        _hoar_partition(array, begin, end, pivot, &new_begin, &new_end);

        if (begin < new_end)
        {
            _intro_sort(array, begin, new_end, depth_limit - 1);
        }

        if (new_begin < end)
        {
            _intro_sort(array, new_begin, end, depth_limit - 1);
        }
    }
}

void IntroSort(int* const array, const size_t array_size, const size_t depth_limit)
{
    assert((array != NULL) && "Pointer to \'array\' is NULL!!!\n");

    _intro_sort(array, 0, array_size - 1, depth_limit);
}