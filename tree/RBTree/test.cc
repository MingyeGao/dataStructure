#include <assert.h>
#include <cstdlib>
#include "test.h"

int isRBTree(RBNode *node){
    if(!node) return 0;

    if(node->parent == nullptr && node->color == red){
        std::cout<<"root color error"<<std::endl;
        return -1;
    }

    if(node->color == red){
        if(node->lchild && node->lchild->color == red){
            std::cout<<"color error at Node "<<node->val<<std::endl;
            return -1;
        } 

        if(node->rchild && node->rchild->color == red){
            std::cout<<"color error at Node "<<node->val<<std::endl;
            return -1;
        } 
    }

    int lBlackHeight = isRBTree(node->lchild);
    if(lBlackHeight == -1) return -1;

    int rBlackHeight = isRBTree(node->rchild);
    if(rBlackHeight == -1) return -1;

    if(lBlackHeight != rBlackHeight){
        std::cout<<"height unequal at Node "<<node->val<<std::endl;
        return -1;
    }

    if(node->color == black){
        return lBlackHeight + 1;
    }
    else{
        return lBlackHeight;
    }
}

void preOrder(RBNode *node){
    if(!node) return;

    std::cout<<node->val;
    if(node->color == red){
        std::cout<<"(r)"<<", ";
    }
    else{
        std::cout<<"(b)"<<", ";
    }

    preOrder(node->lchild);
    preOrder(node->rchild);
}

void insertTest(RBTree *tree, int range, int num){
    for(int i = 0; i < num; ++i){
        int tmp = rand()%range;
        //int tmp = i;
        tree->insert(tmp);
        if(isRBTree(tree->root) < 0){
            preOrder(tree->root);
            break;
        }
        //preOrder(tree->root);
    }
    //preOrder(tree->root);
    std::cout<<std::endl;
}

void removeTest(RBTree *tree, int range, int num){
    for(int i = 0; i < num; ++i){
        int tmp = rand()%range;
        //int tmp = i;
        tree->remove(tmp);
        if(isRBTree(tree->root) < 0){
            preOrder(tree->root);
            break;
        }
        //preOrder(tree->root);
        //std::cout<<std::endl;
        
    }
    // preOrder(tree->root);
    std::cout<<std::endl;
}