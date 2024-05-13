#ifndef SKIP_LIST_H_INCLUDED
#define SLIP_LIST_H_INCLUDED

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

#define MAX(a, b) (a > b) ? a : b
#define MIN(a, b) (a < b) ? a : b

#define MAX_LEVEL 1000

/*============Structs_&_Constants=============*/

typedef struct Node 
{
    int             key;
    struct Node**   next;
} Node;

typedef struct SkipList 
{
    Node*   head;
    int     level;
} SkipList;

/*============================================*/

SkipList*   SkipListCtor(void);
void        SkipListDtor(SkipList* skiplist);

void        SkipListClear(SkipList* skiplist);

void        SkipListInsert(SkipList* skiplist, int key);
void        SkipListDelete(SkipList* skiplist, int key);

#endif