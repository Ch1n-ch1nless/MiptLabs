#include "treap.h"

static Node* NodeCtor(int key)
{
    Node*   new_node = (Node*) calloc(1, sizeof(Node));
    assert((new_node != NULL) && "ERROR!!! Program can not allocate memory!\n");

    new_node->data.key      = key;
    new_node->data.priority = rand();
    
    new_node->left  = NULL;
    new_node->right = NULL;

    return new_node;
}

static void NodeDtor(Node* node)
{
    if (node == NULL)
    {
        return;
    }

    node->data.key      = 0;
    node->data.priority = 0;
    
    node->left      = NULL;
    node->right     = NULL;

    free(node);
}

static void SubTreeSplit(Node* old_subtree, int key, Node** left_subtree, Node** right_subtree)
{
    assert((left_subtree  != NULL) && "ERROR!!! Pointer to \'left_subtree\'  is NULL!\n");
    assert((right_subtree != NULL) && "ERROR!!! Pointer to \'right_subtree\' is NULL!\n");

    if (old_subtree == NULL)
    {
        *left_subtree  = NULL;
        *right_subtree = NULL;
    }
    else if (old_subtree->data.key < key)
    {
        SubTreeSplit(old_subtree->right, key, &(old_subtree->right), right_subtree);
        *left_subtree = old_subtree;
    }
    else
    {
        SubTreeSplit(old_subtree->left, key, left_subtree, &(old_subtree->left));
        *right_subtree = old_subtree;
    }
}

static Node* SubTreeMerge(Node* left_subtree, Node* right_subtree)
{
    if (left_subtree == NULL || right_subtree == NULL)
    {
        return (left_subtree != NULL) ? left_subtree : right_subtree;
    }

    if (left_subtree->data.priority > right_subtree->data.priority)
    {
        left_subtree->right = SubTreeMerge(left_subtree->right, right_subtree);
        
        return left_subtree;
    }

    right_subtree->left = SubTreeMerge(left_subtree, right_subtree->left);

    return right_subtree;
}

static void SubTreeDtor(Node* subtree_root)
{
    if (subtree_root == NULL)
    {
        return;
    }

    SubTreeDtor(subtree_root->left);
    SubTreeDtor(subtree_root->right);
    NodeDtor(subtree_root);
}

Treap* TreapCtor(void)
{
    Treap* new_treap = (Treap*) calloc(1, sizeof(Treap));

    new_treap->root             = NULL;
    new_treap->number_of_nodes  = 0;

    return new_treap;
}

void TreapDtor(Treap* treap)
{
    assert((treap != NULL) && "ERROR!!! Pointer to \'treap\' is NULL!");

    SubTreeDtor(treap->root);
    
    treap->root             = NULL;
    treap->number_of_nodes  = 0;

    free(treap);
}

void TreapClear(Treap* treap)
{
    assert((treap != NULL) && "ERROR!!! Pointer to \'treap\' is NULL!");

    SubTreeDtor(treap->root);
    
    treap->root             = NULL;
    treap->number_of_nodes  = 0;
}

bool TreapFind(Treap* treap, int key)
{
    assert((treap != NULL) && "ERROR!!! Pointer to \'treap\' is NULL!\n");

    Node* key_node = treap->root;

    while (key_node != NULL)
    {
        if (key_node->data.key == key)
        {
            break;
        }
        else if (key_node->data.key < key)
        {
            key_node = key_node->right;
        }
        else
        {
            key_node = key_node->left;
        }
    }

    return (key_node != NULL) ? true : false;
}

void TreapInsert(Treap* treap, int key)
{
    assert((treap != NULL) && "ERROR!!! Pointer to \'treap\' is NULL!\n");

    treap->number_of_nodes += 1;

    Node* new_node = NodeCtor(key);

    if (treap->root == NULL)
    {
        treap->root = new_node;
        return;
    }

    Node* left_tree  = NULL;
    Node* right_tree = NULL;

    SubTreeSplit(treap->root, key, &left_tree, &right_tree);

    left_tree   = SubTreeMerge(left_tree, new_node);
    treap->root = SubTreeMerge(left_tree, right_tree);
}

void TreapDelete(Treap* treap, int key)
{
    assert((treap != NULL) && "ERROR!!! Pointer to \'treap\' is NULL!\n");

    treap->number_of_nodes -= 1;

    if (TreapFind(treap, key) == true)
    {
        Node* left_tree  = NULL;
        Node* right_tree = NULL;
        Node* key_node   = NULL;

        SubTreeSplit(treap->root, key, &left_tree, &key_node);
        SubTreeSplit(key_node, key + 1, &key_node, &right_tree);

        Node* new_key_node = SubTreeMerge(key_node->left, key_node->right);
        NodeDtor(key_node);

        treap->root = SubTreeMerge(left_tree, SubTreeMerge(new_key_node, right_tree));
    }
    else
    {
        treap->number_of_nodes += 1;
    }
}
