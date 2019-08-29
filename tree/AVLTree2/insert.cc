#include "AVLtree.h"

bool insertCore(AVLTreeNode **node, int val){
    if(!(*node)){
        AVLTreeNode *newNode = new AVLTreeNode(val);
        (*node) = newNode;
        return true;
    }

    if((*node)->val == val){
        return false;
    }

    AVLTreeNode **nextNode = (val > (*node)->val) ? 
                             &(*node)->rchild : 
                             &(*node)->lchild;

    bool ret = insertCore(nextNode, val);

    if(!ret){
        return false;
    }else{
        fixup(node);
        return true;
    }
    
}

bool AVLTree::insert(int val){
    bool changeFlag = false;
    int ret = insertCore(&root, val);
    return ret;
}

