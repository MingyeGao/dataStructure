#include "AVLtree.h"



void leftRotate(AVLTreeNode **node){
    AVLTreeNode *r = (*node)->rchild;
    AVLTreeNode *l = (*node)->lchild;

    int lheight = l ? l->height : 0;
    int rlheight = r->lchild ? r->lchild->height : 0;
    int rrheight = r->rchild ? r->rchild->height : 0;

    (*node)->height = max(lheight, rlheight) + 1;
    r->height = max(rrheight, 1 + rlheight) + 1;

    (*node)->rchild = r->lchild;
    r->lchild = (*node);
    (*node) = r;
}

void rightRotate(AVLTreeNode ** node){
    AVLTreeNode *r = (*node)->rchild;
    AVLTreeNode *l = (*node)->lchild;

    int rheight = r ? r->height : 0;
    int lrheight = l->rchild ? l->rchild->height : 0;
    int llheight = l->lchild ? l->lchild->height : 0;
    
    (*node)->height = max(lrheight, rheight) + 1;
    l->height = max(llheight, 1 + lrheight) + 1;

    (*node)->lchild = l->rchild;
    l->rchild = (*node);
    (*node) = l;
}