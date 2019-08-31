#include "RBTree.h"

void RBNode::setLchild(RBNode *node){
    lchild = node;
    if(node){
        node->parent = this;
    }
}

void RBNode::setRchild(RBNode *node){
    rchild = node;
    if(node){
        node->parent = this;
    }
}
