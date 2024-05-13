#include "skip_list.h"

static Node* NodeCtor(int level, int key)
{
    assert((level >= 0) && "ERROR!!! Invalid value of \'level\'!\n");

    Node* new_node = (Node*) calloc(1, sizeof(Node));
    assert((new_node != NULL) && "ERROR!!! Program can not allocate memory!\n");

    new_node->key   = key;

    new_node->next  = (Node**) calloc(level + 1, sizeof(Node*));
    assert((new_node->next != NULL) && "ERROR!!! Program can not allocate memory!\n");

    return new_node;
}

static void NodeDtor(Node* node)
{
    if (node == NULL) return;

    free(node->next);

    node->key   = 0;
    node->next  = NULL;

    free(node);
}

SkipList* SkipListCtor(void)
{
    SkipList* skiplist = (SkipList*) calloc(1, sizeof(SkipList));
    assert((skiplist != NULL) && "ERROR!!! Program can not allocate memory!\n");

    skiplist->head  = NodeCtor(MAX_LEVEL, INT_MIN);
    skiplist->level = 0;

    return skiplist;
}

void SkipListDtor(SkipList* skiplist)
{
    assert((skiplist != NULL) && "ERROR!!! Pointer to \'skiplist\' is NULL!\n");

    Node *current = skiplist->head->next[0];
    while (current != NULL) 
    {
        Node *next = current->next[0];

        NodeDtor(current);

        current = next;
    }

    free(skiplist->head);
    free(skiplist);
}

void SkipListClear(SkipList* skiplist)
{
    assert((skiplist != NULL) && "ERROR!!! Pointer to \'skiplist\' is NULL!\n");

    Node *current = skiplist->head->next[0];
    while (current != NULL) 
    {
        Node *next = current->next[0];

        NodeDtor(current);

        current = next;
    }

    free(skiplist->head);

    skiplist->head  = NodeCtor(MAX_LEVEL, INT_MIN);
    skiplist->level = 0;
}

static int CreateRandomLevel(void)
{
    int level = 0;

    while (rand() < RAND_MAX / 2 && level < MAX_LEVEL)
    {
        level++;
    }

    return level;
}

void SkipListInsert(SkipList* skiplist, int key)
{
    assert((skiplist != NULL) && "ERROR!!! Pointer to \'skiplist\' is NULL!\n");

    Node* update[MAX_LEVEL + 1] = {};

    Node* current = skiplist->head;

    for (int i = skiplist->level; i >= 0; i--)
    {
        while (current->next[i] != NULL && current->next[i]->key < key) 
        {
            current = current->next[i];
        }
        update[i] = current;
    }

    current = current->next[0];

    if (current != NULL && current->key == key) 
    {
        return;
    }

    int level = CreateRandomLevel();

    if (level > skiplist->level) 
    {
        for (int i = skiplist->level + 1; i <= level; i++) 
        {
            update[i] = skiplist->head;
        }
        skiplist->level = level;
    }

    Node *new_node = NodeCtor(level, key);

    for (int i = 0; i <= level; i++) 
    {
        new_node->next[i] = update[i]->next[i];
        update[i]->next[i] = new_node;
    }
}   

void SkipListDelete(SkipList* skiplist, int key)
{
    assert((skiplist != NULL) && "ERROR!!! Pointer to \'skiplist\' is NULL!\n");

    Node *update[MAX_LEVEL + 1];
    Node *current = skiplist->head;

    for (int i = skiplist->level; i >= 0; i--) 
    {
        while (current->next[i] != NULL && current->next[i]->key < key) 
        {
            current = current->next[i];
        }
        update[i] = current;
    }

    current = current->next[0];

    if (current != NULL && current->key == key) 
    {
        for (int i = 0; i <= skiplist->level; i++) 
        {
            if (update[i]->next[i] != current)
                break;
            update[i]->next[i] = current->next[i];
        }

        NodeDtor(current);

        while (skiplist->level > 0 && skiplist->head->next[skiplist->level] == NULL) 
        {
            skiplist->level--;
        }
    }
}