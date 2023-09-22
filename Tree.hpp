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

    TreeNode<T>* find(const T& valueToFind) const;
private:
    TreeNode<T>* root;

    void addChild(TreeNode<T>* parentNode, const T& toAddValue);
    void addNextSibling(TreeNode<T>* parentNode, TreeNode<T>* child);
    void traverseTree(TreeNode<T>* node);
    void removeAllChildren(TreeNode<T>* node);
    void remakeLinks(const TreeNode<T>* nodeToRemove);

    bool isRoot(const TreeNode<T>* node) const;

    TreeNode<T>* getNode(TreeNode<T>* searchStartingNode, const T& valueToGet) const;
};