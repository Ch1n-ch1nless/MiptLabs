#include "binary_tree.h"

static Node* NodeCtor(int value)
{
    Node* new_node = (Node*) calloc(1, sizeof(Node));
    assert((new_node != NULL) && "ERROR!!! Pointer to \'new_node\' is NULL!\n");

    new_node->value = value;
    new_node->right = NULL;
    new_node->left  = NULL;

    return new_node;
}

static void NodeDtor(Node* node)
{
    assert((node != NULL) && "ERROR!!! Pointer to \'node\' is NULL!\n");

    node->value = 0;
    node->right = NULL;
    node->left  = NULL;

    free(node);
}

static Node* SubTreeInsert(Node* root, int value)
{
    if (root == NULL)
    {
        return NodeCtor(value);
    }

    if (value < root->value)
    {
        root->left = SubTreeInsert(root->left, value);
    }
    else
    {
        root->right = SubTreeInsert(root->right, value);
    }

    return root;
}

static int FindMaxKeyInSubTree(Node* root)
{
    assert((root != NULL) && "ERROR Invalid value of root\n");

    while (root->right != NULL)
    {
        root = root->right;
    }

    return root->value;
}

static Node* SubTreeDelete(Node* root, int value)
{
    if (root == NULL)
    {
        return root;
    }

    if (value < root->value)
    {
        root->left  = SubTreeDelete(root->left, value);
    }
    else if (value > root->value)
    {
        root->right = SubTreeDelete(root->right, value);
    }
    else
    {
        Node* temp_node = NULL;

        if (root->left != NULL && root->right != NULL)
        {
            root->value = FindMaxKeyInSubTree(root->left);
            root->left  = SubTreeDelete(root->left, root->value);
            return root;
        }
        else if (root->left != NULL)
        {
            temp_node = root->left;
            NodeDtor(root);
            return temp_node;
        }
        else if (root->right != NULL)
        {
            temp_node = root->right;
            NodeDtor(root);
            return temp_node;
        }

        NodeDtor(root);
        return NULL;
    }

    return root;
}

static Node* SubTreeSearch(Node* root, int value)
{
    if (root == NULL)
    {
        return NULL;
    }

    Node* key_node = NULL;

    if (root->value == value)
    {
        key_node = root;
    }
    else if (root->value < value)
    {
        key_node = SubTreeSearch(root->right, value);
    }
    else
    {
        key_node = SubTreeSearch(root->left, value);
    }

    return key_node;
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

    if (SubTreeSearch(binary_tree->root, value) == NULL)
    {
        binary_tree->root   = SubTreeInsert(binary_tree->root, value);
        binary_tree->size  += 1;
    }
}

void BinaryTreeDelete(BinaryTree* binary_tree, int value)
{
    assert((binary_tree != NULL) && "ERROR!!! Pointer to \'binary_tree\' is NULL!\n");

    if (SubTreeSearch(binary_tree->root, value) != NULL)
    {
        binary_tree->root   = SubTreeDelete(binary_tree->root, value);
        binary_tree->size  -= 1;
    }
}   

bool BinaryTreeSearch(BinaryTree* binary_tree, int value)
{
    assert((binary_tree != NULL) && "ERROR!!! Pointer to \'binary_tree\' is NULL!\n");

    return (SubTreeSearch(binary_tree->root, value) != NULL) ? true : false;
}