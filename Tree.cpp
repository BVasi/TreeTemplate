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
void Tree<T>::addNextSibling(TreeNode<T>* parentNode, TreeNode<T>* child)
{
    TreeNode<T>* currentChildNode = parentNode->firstChild;
    while (currentChildNode->nextSibling)
    {
        currentChildNode = currentChildNode->nextSibling;
    }
    currentChildNode->nextSibling = child;
    child->parent = parentNode;
}

template<typename T>
void Tree<T>::addChild(TreeNode<T>* parentNode, const T& toAddValue)
{
    TreeNode<T>* child = new TreeNode<T>(toAddValue);

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
        root = new TreeNode<T>(toAddValue);
        std::cout << "Root initialized to: " << root->data << "\n";
        return;
    }
    TreeNode<T>* parentNode = getNode(root, parentValue);
    if (!parentNode)
    {
        std::cout << "Nothing to add!" << "\n";
        return;
    }
    addChild(parentNode, toAddValue);
    std::cout << "Value: " << toAddValue << " added to parent node: " << parentValue << "\n";
}

template<typename T>
void Tree<T>::traverseTree(TreeNode<T>* node)
{
    if (!node)
    {
        return;
    }
    std::cout << node->data << " ";
    TreeNode<T>* currentChild = node->firstChild;
    while (currentChild)
    {
        traverseTree(currentChild);
        currentChild = currentChild->nextSibling;
    }
}

template<typename T>
TreeNode<T>* Tree<T>::getNode(TreeNode<T>* searchStartingNode, const T& valueToGet) const
{
    TreeNode<T>* nodeToFind = nullptr;

    if (!searchStartingNode)
    {
        return nullptr;
    }
    if (searchStartingNode->data == valueToGet)
    {
        return searchStartingNode;
    }
    TreeNode<T>* currentChild = searchStartingNode->firstChild;
    while (!nodeToFind && currentChild)
    {
        nodeToFind = getNode(currentChild, valueToGet);
        currentChild = currentChild->nextSibling;
    }

    return nodeToFind;
}

template<typename T>
TreeNode<T>* Tree<T>::find(const T& valueToFind) const
{
    return getNode(root, valueToFind);
}

template<typename T>
bool Tree<T>::isRoot(const TreeNode<T>* node) const
{
    return node == root;
}

template<typename T>
void Tree<T>::removeAllChildren(TreeNode<T>* parentNode)
{
    if (!parentNode)
    {
        return;
    }
    TreeNode<T>* currentChildNode = parentNode->firstChild;
    while (currentChildNode)
    {
        TreeNode<T>* nextSibling = currentChildNode->nextSibling;
        removeAllChildren(currentChildNode);
        delete currentChildNode;
        currentChildNode = nextSibling;
    }
}

template<typename T>
void Tree<T>::remakeLinks(const TreeNode<T>* nodeToRemove)
{
    TreeNode<T>* parentOfNodeToRemove = nodeToRemove->parent;
    if (parentOfNodeToRemove->firstChild == nodeToRemove)
    {
        parentOfNodeToRemove->firstChild = nodeToRemove->nextSibling;
    }
    else
    {
        TreeNode<T>* prevSibling = parentOfNodeToRemove->firstChild;
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
    TreeNode<T>* nodeToRemove = getNode(root, valueToRemove);
    if (!nodeToRemove)
    {
        std::cout << "The node you want to delete doesn't exist!" << "\n";
        return;
    }
    removeAllChildren(nodeToRemove);
    remakeLinks(nodeToRemove);
    nodeToRemove = nullptr;
    delete nodeToRemove;
}

template<typename T>
void Tree<T>::printTree()
{
    traverseTree(root);
    std::cout << "\n";
}

int main() // TO DO: handle root deletion. It's not working properly
{
    Tree<char> tree('A');
    tree.insertNode('A', 'B');
    tree.insertNode('A', 'C');
    tree.insertNode('A', 'D');
    tree.insertNode('B', 'E');
    tree.insertNode('B', 'F');
    tree.insertNode('D', 'G');
    tree.insertNode('D', 'H');
    tree.insertNode('D', 'I');
    tree.insertNode('B', 'J');
    std::cout << "Tree before deletion:\n";
    tree.printTree();
    tree.removeNode('D');
    std::cout << "Tree after deletion:\n";
    tree.printTree();

    return 0;
}