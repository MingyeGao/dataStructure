#include <assert.h>
#include "RBTree.h"

void leftRotate(RBNode *node, RBNode **root){
    assert(node);
    RBNode *nodeParent = node->parent;
    RBNode *r = node->rchild;
    RBNode *rl = r->lchild;

    if(nodeParent){
        if(node == nodeParent->lchild){
            nodeParent->setLchild(r);
        }
        else{
            nodeParent->setRchild(r);
        }
    }
    else{
        r->parent = nullptr;
        (*root) = r;
    }

    r->setLchild(node);
    node->setRchild(rl);
}

void rightRotate(RBNode *node, RBNode **root){
    assert(node);
    RBNode *nodeParent = node->parent;
    RBNode *l = node->lchild;
    RBNode *lr = l->rchild;

    if(nodeParent){
        if(node == nodeParent->lchild){
            nodeParent->setLchild(l);
        }
        else{
            nodeParent->setRchild(l);
        }
    }
    else{
        l->parent = nullptr;
        (*root) = l;
    }

    l->setRchild(node);
    node->setLchild(lr);
}