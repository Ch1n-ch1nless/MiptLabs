#include "binary_tree.h"

static Node* NodeCtor(int value)
{
    Node* new_node = (Node*) calloc(1, sizeof(Node));
    assert((new_node != NULL) && "ERROR!!! Pointer to \'new_node\' is NULL!\n");

    new_node->value     = value;
    new_node->right     = NULL;
    new_node->left      = NULL;
    new_node->parent    = NULL;

    return new_node;
}

static void NodeDtor(Node* node)
{
    assert((node != NULL) && "ERROR!!! Pointer to \'node\' is NULL!\n");

    node->value     = 0;
    node->right     = NULL;
    node->left      = NULL;
    node->parent    = NULL;

    free(node);
}

static void SubTreeInsert(Node* root, Node* new_node)
{
    while (root != NULL)
    {
        if (new_node->value > root->value)
        {
            if (root->right == NULL)
            {
                root->right         = new_node;
                new_node->parent    = root;
                break;
            }
            else
            {
                root = root->right;
            }
        }
        else if (new_node->value < root->value)
        {
            if (root->left == NULL)
            {
                root->left          = new_node;
                new_node->parent    = root;
                break;
            }
            else
            {
                root = root->left;
            }
        }
        else
        {
            NodeDtor(new_node);
            break;
        }
    }
}

static Node* FindMaxKeyInSubTree(Node* root)
{
    assert((root != NULL) && "ERROR Invalid value of root\n");

    while (root->right != NULL)
    {
        root = root->right;
    }

    return root;
}

static void SubTreeDelete(Node* root, Node* key_node)
{
    Node* parent = key_node->parent;

    if (key_node->left == NULL && key_node->right == NULL)
    {
        if (parent->left == key_node)
        {
            parent->left    = NULL;
        }
        else
        {
            parent->right   = NULL;
        }
    }
    else if (key_node->left == NULL || key_node->right == NULL)
    {
        if (key_node->left != NULL)
        {
            if (parent != NULL)
            {
                if (parent->left == key_node)
                {
                    parent->left    = key_node->left;
                }
                else
                {
                    parent->right   = key_node->left;
                }
            }
            key_node->left->parent  = parent;
        }
        else
        {
            if (parent != NULL)
            {
                if (parent->left == key_node)
                {
                    parent->left    = key_node->right;
                }
                else
                {
                    parent->right   = key_node->right;
                }
            }
            key_node->right->parent = parent;
        }
    }
    else
    {
        Node* max_left = FindMaxKeyInSubTree(key_node->left);

        key_node->value = max_left->value;

        if (max_left->parent->left == max_left)
        {
            max_left->parent->left  = max_left->left;
            if (max_left->left != NULL)
            {
                max_left->left->parent   = max_left->parent;
            }
        }
        else
        {
            max_left->parent->right  = max_left->left;
            if (max_left->left != NULL)
            {
                max_left->left->parent   = max_left->parent;
            }
        }
    }
}

static Node* SubTreeSearch(Node* root, int value)
{
    while (root != NULL)
    {
        if (root->value > value)
        {
            root = root->left;
        }
        else if (root->value < value)
        {
            root = root->right;
        }
        else
        {
            break;
        }
    }

    return root;    
}

static void SubTreeDtor(Node* node)
{
    if (node == NULL)
    {
        return;
    }

    SubTreeDtor(node->left);
    SubTreeDtor(node->right);

    NodeDtor(node);
}

BinaryTree* BinaryTreeCtor(void)
{
    BinaryTree* new_binary_tree = (BinaryTree*) calloc(1, sizeof(BinaryTree));
    assert((new_binary_tree != NULL) && "ERROR!!! Program can not allocate memory!\n");

    new_binary_tree->root   = NULL;
    new_binary_tree->size   = 0;

    return new_binary_tree;
}

void BinaryTreeDtor(BinaryTree* binary_tree)
{
    assert((binary_tree != NULL) && "ERROR!!! Pointer to \'binary_tree\' is NULL!\n");

    SubTreeDtor(binary_tree->root);

    binary_tree->root   = NULL;
    binary_tree->size   = 0;

    free(binary_tree);
}

void BinaryTreeClear(BinaryTree* binary_tree)
{
    assert((binary_tree != NULL) && "ERROR!!! Pointer to \'binary_tree\' is NULL!\n");

    SubTreeDtor(binary_tree->root);

    binary_tree->root   = NULL;
    binary_tree->size   = 0;
}

void BinaryTreeInsert(BinaryTree* binary_tree, int value)
{
    assert((binary_tree != NULL) && "ERROR!!! Pointer to \'binary_tree\' is NULL!\n");

    Node* new_node = NodeCtor(value);

    if (binary_tree->root == NULL)
    {
        binary_tree->root   = new_node;
    }
    else
    {
        SubTreeInsert(binary_tree->root, new_node);
    }

    binary_tree->size += 1;
}

void BinaryTreeDelete(BinaryTree* binary_tree, int value)
{
    assert((binary_tree != NULL) && "ERROR!!! Pointer to \'binary_tree\' is NULL!\n");

    Node* key_node = SubTreeSearch(binary_tree->root, value);

    if (key_node != NULL)
    {
        SubTreeDelete(binary_tree->root, key_node);
        
        binary_tree->size -= 1;
    }
}   

bool BinaryTreeSearch(BinaryTree* binary_tree, int value)
{
    assert((binary_tree != NULL) && "ERROR!!! Pointer to \'binary_tree\' is NULL!\n");

    return (SubTreeSearch(binary_tree->root, value) != NULL) ? true : false;
}