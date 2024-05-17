#ifndef AVL_TREE_H_INCLUDED
#define AVL_TREE_H_INCLUDED

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
    size_t          height;
    struct Node*    left;
    struct Node*    right;
} Node;

typedef struct AVLTree
{
    Node*   root;
    size_t  size;
} AVLTree;

/*============================================*/

AVLTree*    AVLTreeCtor(void);
void        AVLTreeDtor(AVLTree* avl_tree);

void        AVLTreeClear(AVLTree* avl_tree);

bool        AVLTreeSearch(AVLTree* avl_tree, int key);
void        AVLTreeInsert(AVLTree* avl_tree, int key);
void        AVLTreeDelete(AVLTree* avl_tree, int key);

#endif