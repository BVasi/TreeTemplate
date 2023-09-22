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
    root = std::make_shared<TreeNode<T>>(rootValue);
}

template<typename T>
void Tree<T>::addNextSibling(std::shared_ptr<TreeNode<T>> parentNode, std::shared_ptr<TreeNode<T>> child)
{
    std::shared_ptr<TreeNode<T>> currentChildNode = parentNode->firstChild;
    while (currentChildNode->nextSibling)
    {
        currentChildNode = currentChildNode->nextSibling;
    }
    currentChildNode->nextSibling = child;
    child->parent = parentNode;
}

template<typename T>
void Tree<T>::addChild(std::shared_ptr<TreeNode<T>> parentNode, const T& toAddValue)
{
    std::shared_ptr<TreeNode<T>> child = std::make_shared<TreeNode<T>>(toAddValue);

    if (!parentNode->firstChild)
    {
        parentNode->firstChild = child;
        child->parent = parentNode;
    }
    else
    {
        addNextSibling(parentNode, child);
    }
}

template<typename T>
void Tree<T>::insertNode(const T& parentValue, const T& toAddValue)
{
    if (!root)
    {
        root = std::make_shared<TreeNode<T>>(toAddValue);
        std::cout << "Root initialized to: " << root->data << "\n";
        return;
    }
    std::shared_ptr<TreeNode<T>> parentNode = getNode(root, parentValue);
    if (!parentNode)
    {
        std::cout << "Nothing to add!" << "\n";
        return;
    }
    addChild(parentNode, toAddValue);
    std::cout << "Value: " << toAddValue << " added to parent node: " << parentValue << "\n";
}

template<typename T>
void Tree<T>::traverseTree(std::shared_ptr<TreeNode<T>> node)
{
    if (!node)
    {
        return;
    }
    std::cout << node->data << " ";
    std::shared_ptr<TreeNode<T>> currentChild = node->firstChild;
    while (currentChild)
    {
        traverseTree(currentChild);
        currentChild = currentChild->nextSibling;
    }
}

template<typename T>
std::shared_ptr<TreeNode<T>> Tree<T>::getNode(std::shared_ptr<TreeNode<T>> searchStartingNode, const T& valueToGet) const
{
    std::shared_ptr<TreeNode<T>> nodeToFind = nullptr;

    if (!searchStartingNode)
    {
        return nullptr;
    }
    if (searchStartingNode->data == valueToGet)
    {
        return searchStartingNode;
    }
    std::shared_ptr<TreeNode<T>> currentChild = searchStartingNode->firstChild;
    while (!nodeToFind && currentChild)
    {
        nodeToFind = getNode(currentChild, valueToGet);
        currentChild = currentChild->nextSibling;
    }

    return nodeToFind;
}

template<typename T>
std::shared_ptr<TreeNode<T>> Tree<T>::find(const T& valueToFind) const
{
    return getNode(root, valueToFind);
}

template<typename T>
bool Tree<T>::isRoot(const std::shared_ptr<TreeNode<T>> node) const
{
    return node == root;
}

template<typename T>
void Tree<T>::removeAllChildren(std::shared_ptr<TreeNode<T>> parentNode)
{
    if (!parentNode)
    {
        return;
    }
    std::shared_ptr<TreeNode<T>> currentChildNode = parentNode->firstChild;
    while (currentChildNode)
    {
        std::shared_ptr<TreeNode<T>> nextSibling = currentChildNode->nextSibling;
        removeAllChildren(currentChildNode);
        currentChildNode.reset();
        currentChildNode = nextSibling;
    }
}

template<typename T>
void Tree<T>::remakeLinks(const std::shared_ptr<TreeNode<T>> nodeToRemove)
{
    std::shared_ptr<TreeNode<T>> parentOfNodeToRemove = nodeToRemove->parent.lock();
    if (parentOfNodeToRemove->firstChild == nodeToRemove)
    {
        parentOfNodeToRemove->firstChild = nodeToRemove->nextSibling;
    }
    else
    {
        std::shared_ptr<TreeNode<T>> prevSibling = parentOfNodeToRemove->firstChild;
        while (prevSibling->nextSibling != nodeToRemove)
        {
            prevSibling = prevSibling->nextSibling;
        }
        prevSibling->nextSibling = nodeToRemove->nextSibling;
    }
}

template<typename T>
void Tree<T>::removeNode(const T& valueToRemove)
{
    std::shared_ptr<TreeNode<T>> nodeToRemove = getNode(root, valueToRemove);
    if (!nodeToRemove)
    {
        std::cout << "The node you want to delete doesn't exist!" << "\n";
        return;
    }
    removeAllChildren(nodeToRemove);
    if (isRoot(nodeToRemove))
    {
        root.reset();
        return;
    }
    remakeLinks(nodeToRemove);
    nodeToRemove.reset();
}

template<typename T>
void Tree<T>::printTree()
{
    traverseTree(root);
    std::cout << "\n";
}