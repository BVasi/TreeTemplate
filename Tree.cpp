//TO DO: REFACTOR
#include <iostream>
#include "Tree.hpp"

template<typename T>
Tree<T>::Tree()
{
    root = nullptr;
}

template<typename T>
Tree<T>::Tree(const T& rootValue)
{
    root = new TreeNode<T>(rootValue);
}

template<typename T>
void Tree<T>::addChild(TreeNode<T>* parentNode, const T& toAddValue)
{
    TreeNode<T>* child = new TreeNode<T>(toAddValue);

    if (!parentNode->firstChild)
    {
        parentNode->firstChild = child;
    }
    else
    {
        TreeNode<T>* currentChildNode = parentNode->firstChild;
        while (currentChildNode->nextSibling != nullptr)
        {
            currentChildNode = currentChildNode->nextSibling;
        }
        currentChildNode->nextSibling = child;
    }
}

template<typename T>
void Tree<T>::add(const T& parentValue, const T& toAddValue)
{
    TreeNode<T>* parentNode = find(root, parentValue);
    if (!root)
    {
        root = new TreeNode<T>(toAddValue);
        std::cout << "Root initialized to: " << root->data;
        return;
    }
    if (!parentNode)
    {
        std::cout << "Nothing to add!" << "\n";
        return;
    }
    else
    {
        addChild(parentNode, toAddValue);
        std::cout << "Value: " << toAddValue << " added to parent node: " << parentValue << "\n";
    }
}

template<typename T>
void Tree<T>::traverse(TreeNode<T>* node)
{
    if (!node)
    {
        return;
    }
    std::cout << node->data << " ";
    TreeNode<T>* currentChild = node->firstChild;
    while (currentChild != nullptr)
    {
        traverse(currentChild);
        currentChild = currentChild->nextSibling;
    }
}

template<typename T>
TreeNode<T>* Tree<T>::find(TreeNode<T>* node, const T& valueToFind)
{
    TreeNode<T>* result = nullptr;

    if (!node)
    {
        return nullptr;
    }
    if (node->data == valueToFind)
    {
        return node;
    }
    TreeNode<T>* currentChild = node->firstChild;
    while (!result && currentChild)
    {
        result = find(currentChild, valueToFind);
        currentChild = currentChild->nextSibling;
    }

    return result;
}

template<typename T>
TreeNode<T>* Tree<T>::find(const T& valueToFind)
{
    return find(root, valueToFind);
}

template<typename T>
void Tree<T>::printTree()
{
    traverse(root);
}

int main()
{
    
    return 0;
}