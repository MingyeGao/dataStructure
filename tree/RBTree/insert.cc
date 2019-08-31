#include <assert.h>
#include "RBTree.h"

bool insertCore(RBNode **node, RBNode *p, RBNode **root, int val){
    if(!(*node)){
        RBNode *newNode = new RBNode(val);
        if(!p){
            newNode->color = black;
            (*node) = newNode;
        }
        else{
            if(node == &(p->lchild)){
                p->setLchild(newNode);
            }
            else{
                p->setRchild(newNode);
            }
        }
        insertFixup(newNode, root);
        return true;
    }

    if((*node)->val == val){
        return false;
    }

    bool ret;
    if(val < (*node)->val){
        ret = insertCore(&(*node)->lchild, (*node), root, val);
    }
    else{
        ret = insertCore(&(*node)->rchild, (*node), root, val);
    }

    return ret;
}

void insertFixup(RBNode *node, RBNode **root){
    RBNode *u;
    RBNode *p = node->parent;
    while(p && node->color == red && p->color == red){
        RBNode *g = p->parent;
        
        if(p == g->lchild){
            u = g->rchild;
            if(!u || u->color == black){
                if(node == p->rchild){
                    leftRotate(p, root);
                }
                g->lchild->color = black;
                g->color = red;
                rightRotate(g, root);
                break;
            }
            else{
                p->color = black;
                u->color = black;
                g->color = red;
                node = g;
                p = g->parent;
            }
        }
        else{
            u = g->lchild;
            if(!u || u->color == black){
                if(node == p->lchild){
                    rightRotate(p, root);
                }
                g->rchild->color = black;
                g->color = red;
                leftRotate(g, root);
                break;
            }
            else{
                p->color = black;
                u->color = black;
                g->color = red;
                node = g;
                p = node->parent;
            }
        }
    }

    if(node->parent == nullptr) node->color = black;
}

bool RBTree::insert(int val){
    int ret = insertCore(&root, nullptr, &root, val);
    return ret;
}