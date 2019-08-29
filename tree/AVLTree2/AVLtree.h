#ifndef AVLTREE_H
#define AVLTREE_H

class AVLTreeNode{
public:
    AVLTreeNode(int x = 0):val(x), height(1), lchild(nullptr), rchild(nullptr){}
    int val;
    int height;
    AVLTreeNode *lchild;
    AVLTreeNode *rchild;

};

class AVLTree{
public:
    AVLTree():root(nullptr){};
    AVLTreeNode *root;

    bool insert(int x);
    bool remove(int x);
};

void leftRotate(AVLTreeNode ** node);

void rightRotate(AVLTreeNode **node);

bool insertCore(AVLTreeNode **node, int val);

bool removeCore(AVLTreeNode **node, int val);

void fixup(AVLTreeNode **node);

AVLTreeNode *getSuccessor(AVLTreeNode *node);

inline int max(int x, int y){
    return x>y ? x : y;
}

#endif ///AVLTREE_H