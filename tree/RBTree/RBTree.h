#ifndef RBTREE_H
#define RBTREE_H

enum Color{red = 0, black};

class RBNode{
public:
    RBNode(int x):val(x), lchild(nullptr), rchild(nullptr), parent(nullptr), color(red){}
    int val;
    RBNode *lchild;
    RBNode *rchild;
    RBNode *parent;
    Color color;

    void setLchild(RBNode *node);
    void setRchild(RBNode *node);
    

};

class RBTree{
public:
    RBNode *root;
    bool insert(int val);
    bool remove(int val);
};

void leftRotate(RBNode *node, RBNode **root);
void rightRotate(RBNode *node, RBNode **root);

bool insertCore(RBNode **node, RBNode *p, RBNode **root, int val);
bool removeCore(RBNode **node, RBNode **root, int val);

void insertFixup(RBNode *node, RBNode **root);
void removeFixup(RBNode *node, RBNode *p, RBNode **root);

RBNode *getSuccessor(RBNode *node);

#endif //RBTREE_H