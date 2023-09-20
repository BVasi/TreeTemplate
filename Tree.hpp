#include "TreeNode.hpp"

template<typename T>
class Tree
{
public:
    Tree();
    Tree(const T& rootValue);

    void add(const T& parentValue, const T& toAddValue);
    void printTree();
    TreeNode<T>* find(const T& valueToFind);
private:
    TreeNode<T>* root;

    void addChild(TreeNode<T>* parentNode, const T& toAddValue);
    void traverse(TreeNode<T>* node);
    TreeNode<T>* find(TreeNode<T>* node, const T& valueToFind);
};