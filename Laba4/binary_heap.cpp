#include "binary_heap.h"

BinaryHeap* BinaryHeapCtor(size_t capacity)
{
    assert((capacity != 0) && "Invalid value of capacity!\n");

    BinaryHeap* new_heap = (BinaryHeap*) calloc(1, sizeof(BinaryHeap));
    assert((new_heap != NULL) && "ERROR! Program can not allocate memory!!!\n");

    *new_heap = {.data = NULL, .size = 0, .capacity = capacity};

    new_heap->data = (node_t*) calloc(capacity, sizeof(node_t));
    if (new_heap->data == NULL)
    {
        free(new_heap);
        assert(0 && "ERROR! Program can allocate memory!!!\n");
    }

    return new_heap;
}

void BinaryHeapDtor(BinaryHeap* heap)
{
    assert((heap != NULL) && "Invalid value of \'heap\'!\n");

    free(heap->data);
    heap->capacity  = 0;
    heap->size      = 0;
    heap->data      = NULL;

    free(heap);
}

void SwapNodes(node_t* node1, node_t* node2)
{
    node_t temp_node = *node1;
    *node1 = *node2;
    *node2 = temp_node;
}

size_t GetParent(size_t index)
{
    return (index - 1) / 2;
}

size_t GetLeftChild(size_t index)
{
    return index * 2 + 1;
}

size_t GetRightChild(size_t index)
{
    return index * 2 + 2;
}

void SiftDown(BinaryHeap* heap, size_t index)
{
    assert((heap != NULL) && "Pointer to \'heap\' is NULL!!!\n");
    assert((heap->data != NULL) && "Pointer to \'heap->data\' is NULL!!!\n");
    assert((index <= heap->size) && "Incorrect value of index!\n");

    size_t left_child  = GetLeftChild(index);
    size_t right_child = GetRightChild(index);
    size_t min_index   = index;

    if (left_child < heap->size && heap->data[left_child] < heap->data[min_index])
    {
        min_index = left_child;
    }

    if (right_child < heap->size && heap->data[right_child] < heap->data[min_index])
    {
        min_index = right_child;
    }

    if (min_index != index)
    {
        SwapNodes(heap->data + min_index, heap->data + index);
        SiftDown(heap, min_index);
    }
}

void SiftUp  (BinaryHeap* heap, size_t index)
{
    assert((heap != NULL) && "Pointer to \'heap\' is NULL!!!\n");
    assert((heap->data != NULL) && "Pointer to \'heap->data\' is NULL!!!\n");
    assert((index <= heap->size) && "Incorrect value of index!\n");

    size_t parent = 0;

    while (index != 0)
    {
        parent = GetParent(index);

        if (heap->data[parent] > heap->data[index])
        {
            SwapNodes(heap->data + parent, heap->data + index);
            index = parent;
        }
        else
        {
            break;
        }
    }
}

int ReallocUp(BinaryHeap* heap)
{
    assert((heap != NULL) && "Pointer to \'heap\' is NULL!!!\n");
    assert((heap->data != NULL) && "Pointer to \'heap->data\' is NULL!!!\n");

    node_t* new_data = (node_t*) realloc(heap->data, heap->capacity * sizeof(node_t));
    if (new_data == NULL)
    {
        return ERROR;
    }

    heap->data      = new_data;
    heap->capacity *= 2;

    return OK;
}

int BinaryHeapInsert(BinaryHeap* heap, node_t new_node)
{
    assert((heap != NULL) && "Pointer to \'heap\' is NULL!!!\n");
    assert((heap->data != NULL) && "Pointer to \'heap->data\' is NULL!!!\n");

    if (heap->size == heap->capacity)
    {
        if (ReallocUp(heap) == ERROR)
        {
            assert(0 && "ERROR! Program can not allocate memory!!!\n");
            return ERROR;
        }
    }

    heap->data[heap->size] = new_node;
    heap->size++;

    SiftUp(heap, heap->size-1);

    return OK;
}

int BinaryHeapBuildForNlogN(BinaryHeap* heap, node_t* buffer_with_nodes, size_t buffer_size)
{
    assert((heap != NULL) && "Pointer to \'heap\' is NULL!!!\n");
    assert((heap->data != NULL) && "Pointer to \'heap->data\' is NULL!!!\n");

    for (size_t i = 0; i < buffer_size; i++)
    {
        BinaryHeapInsert(heap, buffer_with_nodes[i]);
    }

    return OK;
}

int BinaryHeapBuildForN(BinaryHeap* heap, node_t* buffer_with_nodes, size_t buffer_size)
{
    assert((heap != NULL) && "Pointer to \'heap\' is NULL!!!\n");
    assert((heap->data != NULL) && "Pointer to \'heap->data\' is NULL!!!\n");

    memcpy(heap->data, buffer_with_nodes, buffer_size * sizeof(node_t));
    heap->size = buffer_size;

    size_t med = buffer_size / 2;

    for (size_t i = med; i > 0; --i)
    {
        SiftDown(heap, i);
    }

    SiftDown(heap, 0);

    return OK;
}
