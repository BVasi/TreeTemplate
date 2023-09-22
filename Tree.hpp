#pragma once
#include "TreeNode.hpp"

template<typename T>
class Tree
{
public:
    Tree();
    Tree(const T& rootValue);

    void insertNode(const T& parentValue, const T& toAddValue);
    void printTree();
    void removeNode(const T& valueToRemove);

    std::shared_ptr<TreeNode<T>> find(const T& valueToFind) const;
private:
    std::shared_ptr<TreeNode<T>> root;

    void addChild(std::shared_ptr<TreeNode<T>> parentNode, const T& toAddValue);
    void addNextSibling(std::shared_ptr<TreeNode<T>> parentNode, std::shared_ptr<TreeNode<T>> child);
    void traverseTree(std::shared_ptr<TreeNode<T>> node);
    void removeAllChildren(std::shared_ptr<TreeNode<T>> node);
    void remakeLinks(const std::shared_ptr<TreeNode<T>>nodeToRemove);
    std::shared_ptr<TreeNode<T>> deepCopy(const std::shared_ptr<TreeNode<T>> srcNode);

    bool isRoot(const std::shared_ptr<TreeNode<T>> node) const;

    std::shared_ptr<TreeNode<T>> getNode(std::shared_ptr<TreeNode<T>> searchStartingNode, const T& valueToGet) const;
};