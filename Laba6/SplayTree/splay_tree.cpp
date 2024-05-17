#include "splay_tree.h"

static Node* NodeCtor(int key)
{
    Node* new_node = (Node*) calloc(1, sizeof(Node));
    assert((new_node != NULL) && "ERROR!!! Pointer to \'new_node\' is NULL!\n");

    new_node->key           = key;

    new_node->left_child    = NULL;
    new_node->right_child   = NULL;
    new_node->parent        = NULL;

    return new_node;
}

static void NodeDtor(Node* node)
{
    assert((node != NULL) && "ERROR!!! Pointer to \'node\' is NULL!\n");

    //Null the lines
    node->key           = 0;

    node->left_child    = NULL;
    node->right_child   = NULL;
    node->parent        = NULL;

    free(node);
}

static Node* GetParent(Node* node)
{
    if (node != NULL)
    {
        return node->parent;
    }

    return NULL;
}

static Node* GetGrandParent(Node* node)
{
    if (node != NULL)
    {
        if (node->parent != NULL)
        {
            return node->parent->parent;
        }
    }

    return NULL;
}

static bool IsLeftChild( Node* node)
{
    assert((node         != NULL) && "ERROR!!! Pointer to \'node\'         is NULL!\n");
    assert((node->parent != NULL) && "ERROR!!! Pointer to \'node->parent\' is NULL!\n");

    if (node == node->parent->left_child)
    {
        return true;
    }

    return false;
}

static bool IsRightChild(Node* node)
{
    assert((node         != NULL) && "ERROR!!! Pointer to \'node\'         is NULL!\n");
    assert((node->parent != NULL) && "ERROR!!! Pointer to \'node->parent\' is NULL!\n");

    if (node == node->parent->right_child)
    {
        return true;
    }

    return false;
}

static void RotateRight(Node* parent)
{
    assert((parent != NULL) && "ERROR!!! Pointer to \'parent\' is NULL!\n");

    Node* left          = parent->left_child;
    Node* grand_parent  = parent->parent;

    int is_root = (grand_parent != NULL);
    int is_left = (is_root) && (grand_parent->left_child == parent);  

    parent->left_child = left->right_child;

    if (left->right_child != NULL)
    {
        left->right_child->parent = parent;
    }

    left->right_child = parent;
    parent->parent    = left;
    left->parent      = grand_parent;

    if (is_root && is_left)
    {
        grand_parent->left_child = left;
    }
    else if (is_root)
    {
        grand_parent->right_child = left;
    }
}

static void RotateLeft(Node* parent)
{
    assert((parent != NULL) && "ERROR!!! Pointer to \'parent\' is NULL!\n");

    Node* right          = parent->right_child;
    Node* grand_parent  = parent->parent;

    int is_root = (grand_parent != NULL);
    int is_right = (is_root) && (grand_parent->right_child == parent);  

    parent->right_child = right->left_child;

    if (right->left_child != NULL)
    {
        right->left_child->parent = parent;
    }

    right->left_child = parent;
    parent->parent    = right;
    right->parent      = grand_parent;

    if (is_root && is_right)
    {
        grand_parent->right_child = right;
    }
    else if (is_root)
    {
        grand_parent->left_child = right;
    }
}

static void Zig(Node* node)
{
    if (IsLeftChild(node))
    {   
        RotateRight(GetParent(node));
    }
    else
    {
        RotateLeft(GetParent(node));
    }
}

static void ZigZig(Node* node)
{
    if (IsLeftChild(node)) 
    {
      RotateRight(GetGrandParent(node));
      RotateRight(GetParent(node));
    } 
    else 
    {
      RotateLeft(GetGrandParent(node));
      RotateLeft(GetParent(node));
    }
}

static void ZigZag(Node* node)
{
    if (IsRightChild(node)) 
    {
      RotateLeft(GetParent(node));
      RotateRight(GetParent(node));
    } 
    else 
    {
      RotateRight(GetParent(node));
      RotateLeft(GetParent(node));
    }
}

static Node* SubTreeSplay(Node* root)
{
    while (GetParent(root) != NULL)
    {
        if (GetGrandParent(root) == NULL)
        {
            Zig(root);
        }
        else if ((IsLeftChild(root) && IsLeftChild(GetParent(root)))  ||
                 (IsRightChild(root) && IsRightChild(GetParent(root)))   )
        {
            ZigZig(root);
        }
        else if ((IsRightChild(root) && IsLeftChild(GetParent(root))) ||
                 (IsLeftChild(root) && IsRightChild(GetParent(root)))   ) 
        {
            ZigZag(root);
        }
    }

    return root;
}

static Node* SubTreeSearch(Node* root, int key)
{
    Node* next = NULL;

    while (root != NULL)
    {
        next = NULL;

        if (root->key == key)
        {
            return root;
        }
        else if (key < root->key)
        {
            next = root->left_child;
        }
        else
        {
            next = root->right_child;
        }

        root = next;
    }

    return NULL;
}

static Node* SubTreeInsert(Node* root, int key)
{  
    Node* new_node  = NodeCtor(key);

    if (root == NULL)
    {
        return new_node;
    }

    Node* prev      = NULL;
    Node* next      = NULL;

    int   is_left   = false;

    while (root != NULL)
    {
        if (key <= root->key)
        {
            next    = root->left_child;
            is_left = true;
        }
        else
        {
            next    = root->right_child;
            is_left = false;
        }

        prev = root;
        root = next;
    }

    if (is_left)
    {
        prev->left_child    = new_node;
        new_node->parent    = prev;
    }
    else
    {
        prev->right_child   = new_node;
        new_node->parent    = prev;
    }

    return SubTreeSplay(new_node);
}

static void SubTreeDtor(Node* root)
{
    Node* prev = NULL;

    while (root != NULL)
    {
        if (root->left_child != NULL)
        {
            prev = root;
            root = root->left_child;
        }
        else if (root->right_child != NULL)
        {
            prev = root;
            root = root->right_child;
        }
        else
        {
            if (prev != NULL)
            {
                if (prev->left_child == root)
                {   
                    prev->left_child = NULL;
                }
                else
                {
                    prev->right_child = NULL;
                }
            }

            NodeDtor(root);

            root = prev;

            if (root != NULL)
            {
                prev = root->parent;
            }
        }
    }
}

static Node* FindMaxKeyInSubTree(Node* root)
{
    Node* max_node = root;

    while (root != NULL)
    {
        max_node    = root;
        root        = root->right_child;
    }
    
    return max_node;
}

static Node* SubTreeMerge(Node* left, Node* right)
{
    if (left == NULL)
    {
        return right;
    }

    Node* max_left = FindMaxKeyInSubTree(left);

    max_left = SubTreeSplay(max_left);

    max_left->right_child = right;

    if (right != NULL)
    {
        right->parent   = max_left;
    }

    return max_left;
}

SplayTree* SplayTreeCtor(void)
{
    SplayTree* new_splay_tree = (SplayTree*) calloc(1, sizeof(SplayTree));
    assert((new_splay_tree != NULL) && "ERROR!!! Program can not allocate memory!\n");

    new_splay_tree->number_of_nodes = 0;
    new_splay_tree->root            = NULL;

    return new_splay_tree;
}

void SplayTreeDtor(SplayTree* splay_tree)
{
    assert((splay_tree != NULL) && "ERROR!!! Pointer to \'splay_tree\' is NULL!\n");

    SubTreeDtor(splay_tree->root);

    splay_tree->number_of_nodes = 0;
    splay_tree->root            = NULL;

    free(splay_tree);
}

void SplayTreeClear(SplayTree* splay_tree)
{
    assert((splay_tree != NULL) && "ERROR!!! Pointer to \'splay_tree\' is NULL!\n");

    SubTreeDtor(splay_tree->root);

    splay_tree->number_of_nodes = 0;
    splay_tree->root            = NULL;
}

bool SplayTreeSearch(SplayTree* splay_tree, int key)
{
    assert((splay_tree != NULL) && "ERROR!!! Pointer to \'splay_tree\' is NULL!\n");

    Node* key_node = SubTreeSearch(splay_tree->root, key);

    if (key_node == NULL)
    {
        return false;
    }

    splay_tree->root    = SubTreeSplay(key_node);

    return true;
}

void SplayTreeInsert(SplayTree* splay_tree, int key)
{
    assert((splay_tree != NULL) && "ERROR!!! Pointer to \'splay_tree\' is NULL!\n");

    splay_tree->root    = SubTreeInsert(splay_tree->root, key);
}

void SplayTreeDelete(SplayTree* splay_tree, int key)
{
    assert((splay_tree != NULL) && "ERROR!!! Pointer to \'splay_tree\' is NULL!\n");

    Node* key_node = SubTreeSearch(splay_tree->root, key);

    if (key_node == NULL)
    {
        return;
    }

    splay_tree->root = SubTreeSplay(key_node);

    Node* left  = key_node->left_child;
    Node* right = key_node->right_child;

    if (left != NULL)
    {
        left->parent    = NULL;
    }

    if (right != NULL)
    {
        right->parent   = NULL;
    }

    NodeDtor(key_node);

    splay_tree->root    = SubTreeMerge(left, right);
}