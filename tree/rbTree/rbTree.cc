#include <assert.h>

#include <cstdio>

using namespace std;

enum Color{black = 0, red};

class Node;


class Node{
public:
    Node(){};
    Node(int a):val(a), lchild(nullptr), rchild(nullptr), p(nullptr), color(red){}
    int val;
    Node *lchild;
    Node *rchild;
    Node *p;
    Color color;
    void setLchild(Node *node){
        lchild = node;
        node->p = this;
    }
    void setRchild(Node *node){
        rchild = node;
        node->p = this;
    }
};

class rbTree{
public:
    rbTree(){ 
        sudoHead = new Node();
        sudoHead->color = black;
    }
    Node *sudoHead;
    ~rbTree(){
        delete sudoHead;
    }

    void insert(int x);
    void insertFixup(Node *node);
    bool remove(int x);
    void removeFixup(Node *node);
};

void leftRotate(Node **node){
    Node *p = (*node)->p;
    Node *r = (*node)->rchild;

    (*node)->rchild = r->lchild;
    r->lchild->p = (*node)->rchild;

    r->lchild = (*node);
    (*node)->p = r;

    (*node) = r;
    r->p = p;
}

void rightRotate(Node **node){
    Node *l = (*node)->lchild;
    Node *p = (*node)->p;

    (*node)->lchild = l->rchild;
    l->rchild->p = (*node);

    l->rchild = (*node);
    (*node)->p = l;

    (*node) = l;
    l->p = p;
}

void rbTree::insert(int x){
    if(sudoHead->lchild == nullptr){
        Node *newNode = new Node(x);
        sudoHead->setLchild(newNode);
        return;
    }

    Node *currentNode = sudoHead->lchild;
    Node *prevNode;
    Node *newNode;
    bool insertFlag = false;

    while(1){
        if(currentNode == nullptr){
            newNode = new Node(x);
            if(currentNode == prevNode->lchild){
                prevNode->setLchild(newNode);
            }
            else{
                prevNode->setRchild(newNode);
            }
            insertFlag = true;
            break;
        }

        if(currentNode->val == x) return;
        else if(x < currentNode->val){
            prevNode = currentNode;
            currentNode = currentNode->lchild;
        }
        else{
            prevNode = currentNode;
            currentNode = currentNode->rchild;
        }
    }

    if(insertFlag == true){
        insertFixup(newNode);
    }
    
    
}

void rbTree::insertFixup(Node *node){
    assert(node->color == red);

    

    Node *p;
    Node *g;
    Node *u;

    while(1){
        
        if(p->color == black) return;
        p = node->p;
        g = p->p;

        if(p == g->lchild){
            u = g->rchild;
            if(u->color == red){
                u->color = black;
                p->color = black;
                node = g;
                continue;
            }
            else{
                if(node == p->rchild){
                    leftRotate(&p);
                }
                rightRotate(&p);
                break;
            }
        }
        else{
            u = g->lchild;
            if(u->color == red){
                u->color = black;
                p->color = black;
                node = g;
                continue;
            }
            else{
                if(node == p->lchild){
                    rightRotate(&p);
                }
                leftRotate(&p);
                break;
            }
        }
    }
    


}

int nodeCheck(Node *node){
    if(!node){
        return 0;
    }
    if(node->color == red){
        if(node->lchild && node->lchild->color == red){
            return -1;
        }
        if(node->rchild && node->rchild->color == red){
            return -1;
        }
    }

    int lchildBlackNum = nodeCheck(node->lchild);
    if(lchildBlackNum == -1) return -1;
    int rchildBlackNum = nodeCheck(node->rchild);
    if(rchildBlackNum == -1) return -1;

    if(lchildBlackNum != rchildBlackNum) return -1;

    if(node->color == red){ return lchildBlackNum;}
    else { return lchildBlackNum + 1;}
}

int main(int argc, char *argv[]){
    
}

