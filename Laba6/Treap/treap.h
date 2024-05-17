#ifndef TREAP_H_INCLUDED
#define TREAP_H_INCLUDED

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX(a, b) (a > b) ? a : b
#define MIN(a, b) (a < b) ? a : b

/*============Structs_&_Constants=============*/

typedef struct node_elem_t
{
    int     key;
    int     priority;
} node_elem_t;

typedef struct Node 
{
    node_elem_t     data;
    struct Node*    left;
    struct Node*    right;
} Node;

typedef struct Treap 
{
    Node*   root;
    size_t  number_of_nodes;
} Treap;

/*============================================*/

Treap*  TreapCtor(void);
void    TreapDtor(Treap* treap);

void    TreapClear(Treap* treap);

bool    TreapFind(Treap* treap, int key);
void    TreapInsert(Treap* treap, int key);
void    TreapDelete(Treap* treap, int key);


#endif