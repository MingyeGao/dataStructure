#include <iostream>
#include "test.h"

int isAVLTree(AVLTreeNode *node){
    if(!node) return 0;

    int lret = isAVLTree(node->lchild);
    if(lret < 0) return -1;

    int rret = isAVLTree(node->rchild);
    if(rret < 0) return -1;

    int lheight = (node->lchild) ? node->lchild->height : 0;
    int rheight = (node->rchild) ? node->rchild->height : 0;

    if(lheight - rheight >= 2 || rheight - lheight >= 2){
        std::cout<<"height error at Node "<<node->val<<std::endl;
        return -1;
    }

    if(node->lchild && node->val < node->lchild->val){
        std::cout<<"value error at Node "<<node->val<<std::endl;
        return -1;
    }

    if(node->rchild && node->val > node->rchild->val){
        std::cout<<"value error at Node "<<node->val<<std::endl;
        return -1;
    }

    return node->height;
}

void preOrder(AVLTreeNode *node){
    if(!node) return;
    std::cout<<node->val<<", ";
    preOrder(node->lchild);
    preOrder(node->rchild);
}

void insertTest(AVLTree *tree, int range, int num){
    for(int i = 0; i < num; ++i){
        int tmp = rand()%range;
        //int tmp = i;
        tree->insert(tmp);
        if(isAVLTree(tree->root) < 0){
            std::cout<<"inserted node is "<<tmp<<std::endl;
            preOrder(tree->root);
            break;
        }
    }
}

void removeTest(AVLTree *tree, int range, int num){
    for(int i = 0; i < num; ++i){
        int tmp = rand()%range;
        //int tmp = i;
        tree->remove(tmp);
        if(isAVLTree(tree->root) < 0){
            std::cout<<"removed node is "<<tmp<<std::endl;
            preOrder(tree->root);
            break;
        }
    }
}