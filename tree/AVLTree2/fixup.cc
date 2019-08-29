#include <assert.h>
#include "AVLtree.h"

///return value: if rotation happened
void fixup(AVLTreeNode **node){
    
    if(!(*node)) return;

    AVLTreeNode *l = (*node)->lchild;
    AVLTreeNode *r = (*node)->rchild;
    int lheight = l ? l->height : 0;
    int rheight = r ? r->height : 0;
    (*node)->height = max(lheight, rheight) + 1;

    if(lheight == (rheight + 2)){
        
        AVLTreeNode *ll = l->lchild;
        AVLTreeNode *lr = l->rchild;
        int llHeight = ll ? ll->height : 0;
        int lrHeight = lr ? lr->height : 0;

        if(llHeight > lrHeight){
            rightRotate(node);
        }
        else{
            leftRotate(&((*node)->lchild));
            rightRotate(node);
        }
    }
    else if(rheight == (lheight + 2)){
        
        AVLTreeNode *rl = r->lchild;
        AVLTreeNode *rr = r->rchild;
        int rlHeight = rl ? rl->height : 0;
        int rrHeight = rr ? rr->height : 0;

        if(rrHeight >= rlHeight){
            leftRotate(node);
        }
        else{
            rightRotate(&((*node)->rchild));
            leftRotate(node);
        }
    }
    
}

AVLTreeNode *getSuccessor(AVLTreeNode *node){
    assert(node);

    if(!node->rchild) return node->lchild;

    AVLTreeNode *current = node->rchild;
    while(current->lchild){
        current = current->lchild;
    }
    return current;
}