#include "AVLtree.h"

bool removeLeafNode(AVLTreeNode **start, AVLTreeNode *leaf){
    if(!leaf) return false;
    if(!(*start)) return false;

    if((*start)->val == leaf->val){
        (*start) = (*start)->rchild;
        return true;
    }

    AVLTreeNode **nextNode = leaf->val > (*start)->val ? 
                             &(*start)->rchild :
                             &(*start)->lchild;
    
    removeLeafNode(nextNode, leaf);

    fixup(start);

    return true;
}

bool removeCore(AVLTreeNode **node, int val){
    if(!(*node)) return false;

    if((*node)->val == val){
        
        AVLTreeNode *successor = getSuccessor(*node);
        
        if(!successor){
            (*node) = nullptr;
        }
        else if(successor == (*node)->lchild){
            (*node) = successor;
            fixup(node);
        }
        else if(successor == (*node)->rchild){
            successor->lchild = (*node)->lchild;
            (*node) = successor;
            fixup(node);
        }
        else{
            removeLeafNode(node, successor);
            AVLTreeNode *l = (*node)->lchild;
            AVLTreeNode *r = (*node)->rchild;
            successor->lchild = l;
            successor->rchild = r;
            (*node) = successor;
            fixup(node);
        }

        return true;
    }

    AVLTreeNode **nextNode = (val > (*node)->val)?
                             &(*node)->rchild : 
                             &(*node)->lchild;

    bool result = removeCore(nextNode, val);

    if(!result){
        return false;
    }           
    else{
        fixup(node);
        return true;
    }
}

bool AVLTree::remove(int x){
    int ret = removeCore(&root, x);
    return ret;
}