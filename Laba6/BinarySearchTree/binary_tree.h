#ifndef BINARY_TREE_H_INCLUDED
#define BINARY_TREE_H_INCLUDED

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*============Structs_&_Constants=============*/

typedef struct Node
{
    int value;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
} Node;

typedef struct BinaryTree
{
    Node*   root;
    size_t  size;
} BinaryTree;

/*============================================*/

BinaryTree* BinaryTreeCtor(void);
void        BinaryTreeDtor(BinaryTree* binary_tree);

void        BinaryTreeClear(BinaryTree* binary_tree);

void        BinaryTreeInsert(BinaryTree* binary_tree, int value);
void        BinaryTreeDelete(BinaryTree* binary_tree, int value);
bool        BinaryTreeSearch(BinaryTree* binary_tree, int value);

#endif