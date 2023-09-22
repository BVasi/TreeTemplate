#pragma once
#include <memory>

template<typename T>
struct TreeNode
{
    TreeNode(const T& value);
    T data;
    std::shared_ptr<TreeNode<T>> firstChild;
    std::shared_ptr<TreeNode<T>> nextSibling;
    std::weak_ptr<TreeNode<T>> parent;
};

template<typename T>
TreeNode<T>::TreeNode(const T& value)
{
    data = value;
    firstChild = nullptr;
    nextSibling = nullptr;
    parent.reset();
}