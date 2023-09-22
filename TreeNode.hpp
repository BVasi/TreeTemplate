#include <memory>

template<typename T>
struct TreeNode
{
    TreeNode(const T& value);
    T data;
    TreeNode<T>* firstChild;
    TreeNode<T>* nextSibling;
    TreeNode<T>* parent;
};

template<typename T>
TreeNode<T>::TreeNode(const T& value)
{
    data = value;
    firstChild = nullptr;
    nextSibling = nullptr;
    parent = nullptr;
}