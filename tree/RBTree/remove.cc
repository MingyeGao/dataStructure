#include <assert.h>
#include <iostream>
#include "RBTree.h"

RBNode *getSuccessor(RBNode *node){
    assert(node);

    if(!node->rchild){
        return node->lchild;
    }
    else{
        RBNode *current = node->rchild;
        while(current->lchild){
            current = current->lchild;
        }
        return current;
    }
    assert(0);
}

bool removeCore(RBNode **node, RBNode **root, int val){
    if(!(*node)) return false;

    if((*node)->val == val){
        RBNode *successor = getSuccessor(*node);
        RBNode *nodeP = (*node)->parent, *nodeL = (*node)->lchild, *nodeR = (*node)->rchild;
        

        ///被删除的节点是根节点
        if(nodeP == nullptr){
            if(!successor){
                (*root) = nullptr;
            }
            else if(successor == (*node)->lchild){
                successor->parent = nullptr;
                (*root) = successor;
                (*root)->color = black;
            }
            else if(successor == (*node)->rchild){
                Color removedColor = successor->color;
                successor->parent = nullptr;
                successor->setLchild((*node)->lchild);
                (*root) = successor;
                (*root)->color = black;
                if(removedColor == black){
                    removeFixup(nullptr, successor, root);
                }
            }
            else{
                Color removedColor = successor->color;
                RBNode *successorP = successor->parent, *successorR = successor->rchild;
                successorP->setLchild(successorR);
                successor->parent = nullptr;
                (*root) = successor;
                (*root)->color = black;
                if(removedColor == black){
                    removeFixup(successorP->lchild, successorP, root);
                }
            }
            return true;
        }

        RBNode *fixupNode, *fixupNodeParent;
        Color removedColor = (*node)->color;
        Color successorColor = successor ? successor->color : black;
        if(successor) successor->color = removedColor;

        if(!successor){
            if((*node) == nodeP->lchild){
                nodeP->setLchild(nullptr);
            }
            else{
                nodeP->setRchild(nullptr);
            }
            fixupNode = nullptr;
            fixupNodeParent = nodeP;
        }
        else if(successor == (*node)->lchild){
            if((*node) == nodeP->lchild){
                nodeP->setLchild(successor);
            }
            else{
                nodeP->setRchild(successor);
            }
            fixupNode = successor;
            fixupNodeParent = nodeP;
            
        }
        else if(successor == (*node)->rchild){
            successor->setLchild(nodeL);
            if((*node) == nodeP->lchild){
                nodeP->setLchild(successor);
            }
            else{
                nodeP->setRchild(successor);
            }
            fixupNode = successor->rchild;
            fixupNodeParent = successor;
        }
        else{
            RBNode *successorP = successor->parent, *successorR = successor->rchild;
            successorP->setLchild(successorR);
            successor->setLchild(nodeL);
            successor->setRchild(nodeR);
            if((*node) == nodeP->lchild){
                nodeP->setLchild(successor);
            }
            else{
                nodeP->setRchild(successor);
            }
            fixupNode = successorR;
            fixupNodeParent = successorP;
        }

        if((successor && successorColor == black) || (!successor && removedColor == black)){
            removeFixup(fixupNode, fixupNodeParent, root);
        }
        return true;
    }

    bool ret;
    if(val > (*node)->val){
        ret = removeCore(&(*node)->rchild, root, val);
    }
    else{
        ret = removeCore(&(*node)->lchild, root, val);
    }
    return ret;
}

void removeFixup(RBNode *node, RBNode *p, RBNode **root){
    RBNode *c;
    while(p && (!node || node->color == black)){
        if(node == p->lchild){
            c = p->rchild;
            assert(c);
            if(c->color == red){
                p->color = red;
                c->color = black;
                leftRotate(p, root);
                continue;
            }
            else{
                RBNode *cl = c->lchild, *cr = c->rchild;
                if((!cl || cl->color == black) && (!cr || cr->color == black)){
                    c->color = red;
                    node = p;
                    p = node->parent;
                    continue;
                }
                else if(cr && cr->color == red){
                    c->color = p->color;
                    p->color = black;
                    cr->color = black;
                    leftRotate(p, root);
                    break;
                }
                else if((!cr || cr->color == black) && cl && cl->color == red){
                    c->color = red;
                    cl->color = black;
                    rightRotate(c, root);
                    continue;
                }
                assert(0);
            }
        }
        else if(node == p->rchild){
            c = p->lchild;
            assert(c);
            if(c->color == red){
                c->color = black;
                p->color = red;
                rightRotate(p, root);
                continue;
            }
            else{
                RBNode *cl = c->lchild, *cr = c->rchild;
                if((!cl || cl->color == black) && (!cr || cr->color == black)){
                    c->color = red;
                    node = p;
                    p = node->parent;
                    continue;
                }
                else if(cl && cl->color == red){
                    c->color = p->color;
                    p->color = black;
                    cl->color = black;
                    rightRotate(p, root);
                    break;
                }
                else if((!cl || cl->color == black) && cr && cr->color == red){
                    cr->color = black;
                    c->color = red;
                    leftRotate(c, root);
                    continue;
                }
                std::cout<<"error happend. Removing node is "<<node->val<<std::endl;
                assert(0);
            }
        }

        assert(0);
    }
    if(node) node->color = black;
    
}

bool RBTree::remove(int val){
    bool ret = removeCore(&root, &root, val);
    return ret;
}