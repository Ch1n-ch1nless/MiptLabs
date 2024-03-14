#include "testing.h"

struct Heap
{
    int* data;
    int  size;
    int  capacity;
    int  children;
};

static void Swap(int* const ptr1, int* const ptr2)
{
    assert((ptr1 != NULL) && "Pointer to \'ptr1\' is NULL!!!\n");
    assert((ptr2 != NULL) && "Pointer to \'ptr2\' is NULL!!!\n");

    int temp = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = temp;
}

static void SiftUp(Heap* const heap, int index)
{
    assert((heap != NULL) && "Pointer to \'heap\' is NULL!!!\n");

    int parent = 0;

    while (index != 0)
    {
        parent = (index - 1) / heap->children;

        if (heap->data[index] > heap->data[parent])
        {
            Swap(heap->data + index, heap->data + parent);
            index = parent;
        }
        else
        {
            return;
        }
    }
}

static void SiftDown(Heap* const heap, int index)
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

        Swap(heap->data + index, heap->data + max_index);
        index = max_index;
    }
}

static void HeapInsert(Heap* const heap, int element)
{
    assert((heap != NULL) && "Pointer to \'heap\' is NULL!!!\n");

    heap->data[heap->size] = element;
    heap->size++;

    SiftUp(heap, heap->size - 1);
}

static int ExtractMax(Heap* const heap)
{
    assert((heap != NULL) && "Pointer to \'heap\' is NULL!!!\n");

    int root_value = heap->data[0];

    heap->data[0] = heap->data[--heap->size];

    SiftDown(heap, 0);

    return root_value;
}

static Heap* HeapCtor(int* const array, const int size, const int children_number)
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
        HeapInsert(heap, array[i]);
    }

    return heap;
}

static void HeapDtor(Heap* const heap)
{
    assert((heap != NULL) && "Pointer to \'heap\' is NULL!!!\n");

    free(heap->data);
    heap->data = NULL;
    heap->size = 0;
    heap->capacity = 0;
    heap->children = 0;

    free(heap);
}

void HeapSort(int* const array, const int array_size)
{
    assert((array != NULL) && "Pointer to \'array\' is NULL!!!\n");

    Heap* temp_heap = HeapCtor(array, array_size, 10);

    for (int i = array_size - 1; i >= 0; i--)
    {
        array[i] = ExtractMax(temp_heap);
    }

    HeapDtor(temp_heap);
}
