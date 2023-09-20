template<typename T>
struct TreeNode
{
    TreeNode(const T& value);
    T data;
    TreeNode* firstChild;
    TreeNode* nextSibling;
};

template<typename T>
TreeNode<T>::TreeNode(const T& value)
{
    data = value;
    firstChild = nullptr;
    nextSibling = nullptr;
}