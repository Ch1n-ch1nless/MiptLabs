#ifndef SPLAY_TREE_H_INCLUDED
#define SPLAY_TREE_H_INCLUDED

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX(a, b) (a > b) ? a : b
#define MIN(a, b) (a < b) ? a : b

/*============Structs_&_Constants=============*/

typedef struct Node 
{
    int             key;
    struct Node*    left_child;
    struct Node*    right_child;
    struct Node*    parent;
} Node;

typedef struct SplayTree 
{
    Node*   root;
    size_t  number_of_nodes;
} SplayTree;

/*============================================*/

SplayTree*  SplayTreeCtor(void);
void        SplayTreeDtor(SplayTree* splay_tree);

void        SplayTreeClear(SplayTree* splay_tree);

bool        SplayTreeSearch(SplayTree* splay_tree, int key);
void        SplayTreeInsert(SplayTree* splay_tree, int key);
void        SplayTreeDelete(SplayTree* splay_tree, int key);


#endif