#ifndef BINARY_HEAP_H_INCLUDED
#define BINARY_HEAP_H_INCLUDED

#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef int node_t;

/*==================CONSTANTS=================*/

const int   OK      = 1;
const int   ERROR   = 0;

const int   INITIAL_CAPACITY    = 1048576;

/*===================STRUCTS==================*/

typedef struct 
{
    node_t* data;
    size_t  size;
    size_t  capacity;
}   BinaryHeap;

/*===================FUNCTIONS================*/

BinaryHeap* BinaryHeapCtor(size_t capacity);
void        BinaryHeapDtor(BinaryHeap* heap);

void        SwapNodes(node_t* node1, node_t* node2);

size_t      GetParent    (size_t index);
size_t      GetLeftChild (size_t index);
size_t      GetRightChild(size_t index);

void        SiftDown(BinaryHeap* heap, size_t index);
void        SiftUp  (BinaryHeap* heap, size_t index);

int         ReallocUp(BinaryHeap* heap);

int         BinaryHeapInsert(BinaryHeap* heap, node_t new_node);

int         BinaryHeapBuildForNlogN(BinaryHeap* heap, node_t* buffer_with_nodes, size_t buffer_size);
int         BinaryHeapBuildForN    (BinaryHeap* heap, node_t* buffer_with_nodes, size_t buffer_size);

#endif