#include <assert.h>

#include <iostream>
#include <cstdlib>

using namespace std;

enum Color{black = 0, red};

class Node;


class Node{
public:
    Node():lchild(nullptr), rchild(nullptr), p(nullptr){};
    Node(int a):val(a), lchild(nullptr), rchild(nullptr), p(nullptr), color(red){}
    Node(int a, Node *nil):
      val(a), lchild(nil), rchild(nil), p(nil), color(red){}
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
        nil = new Node();
        nil->color = black;
        nil->lchild = nil;
        nil->rchild = nil;
        nil->val = -1;
    }
    Node *nil;
    ~rbTree(){ }

    void insert(int x);
    void insertFixup(Node *node);
    bool remove(int x);
    void removeFixup(Node *node);\
    Node *root() {return nil->lchild;}
};


void Rotate(Node *p, Node *n){
    assert(n == p->lchild || n == p->rchild);

    Node *g = p->p;
    if(p == g->lchild){
        g->setLchild(n);
    }
    else{
        g->setRchild(n);
    }

    if(n == p->lchild){
        p->setLchild(n->rchild);
        n->setRchild(p);

    }
    else{//n == p->rchild
        p->setRchild(n->lchild);
        n->setLchild(p);
    }
}

void rbTree::insert(int x){
    if(nil->lchild == nil){
        Node *newNode = new Node(x, nil);
        nil->setLchild(newNode);
        newNode->color = black;
        return;
    }

    Node *currentNode = root();
    Node *prevNode;
    Node *newNode;
    bool insertFlag = false;

    while(1){

        if(currentNode->val == x) return;
        else if(x < currentNode->val){
            if(currentNode->lchild == nil){
                newNode = new Node(x, nil);
                currentNode->setLchild(newNode);
                insertFlag = true;
                break;
            }
            else{
                currentNode = currentNode->lchild;
            }
        }
        else{
            if(currentNode->rchild == nil){
                newNode = new Node(x, nil);
                currentNode->setRchild(newNode);
                insertFlag = true;
                break;
            }
            else{
                currentNode = currentNode->rchild;
            }
        }
    }

    if(insertFlag == true){
        insertFixup(newNode);
    }
    
    
}

void rbTree::insertFixup(Node *node){
    assert(node->color == red);
    Node *p, *g, *u;

    while(1){
        if(node == root()) break;
        p = node->p;
        if(p->color == black) return;
        g = p->p;

        if(p == g->lchild){
            u = g->rchild;
            if(u->color == red){
                u->color = black;
                p->color = black;
                if(g == root()){
                    break;
                }
                g->color = red;
                node = g;
                continue;
            }
            else{
                if(node == p->rchild){
                    node->color = black;
                    p->color = red;
                    g->color = red;
                    Rotate(p, node);
                    Rotate(g, node);
                    break;
                }
                else{
                    node->color = red;
                    p->color = black;
                    g->color = red;
                    Rotate(g, p);
                    break;
                }
            }
        }
        else{
            u = g->lchild;
            if(u->color == red){
                u->color = black;
                p->color = black;
                if(g == root()){
                    break;
                }
                g->color = red;
                node = g;
                continue;
            }
            else{
                if(node == p->lchild){
                    node->color = black;
                    p->color = red;
                    g->color = red;
                    Rotate(p, node);
                    Rotate(g, node);
                    break;
                }
                else{
                    node->color = red;
                    p->color = black;
                    g->color = red;
                    Rotate(g, p);
                    break;
                }
            }
        }
    }
    


}

int nodeCheck(Node *node, Node *nil){
    if(node == nil){
        return 0;
    }
    if(node->color == red){
        if(node->lchild != nil && node->lchild->color == red){
            cout<<"color error\n";
            return -1;
        }
        if(node->rchild != nil && node->rchild->color == red){
            cout<<"color error\n";
            return -1;
        }
    }

    int lchildBlackNum = nodeCheck(node->lchild, nil);
    if(lchildBlackNum == -1) {
        cout<<"black height error\n";
        return -1;
    }
    int rchildBlackNum = nodeCheck(node->rchild, nil);
    if(rchildBlackNum == -1) {
        cout<<"black height error\n";
        return -1;
    }

    if(lchildBlackNum != rchildBlackNum){
        cout<<"black height doesn't match\n";
        return -1;
    } 

    if(node->color == red){ return lchildBlackNum;}
    else { return lchildBlackNum + 1;}
}


void preOrder(Node *node, Node *nil);

int main(int argc, char *argv[]){
    int num = 500;
    rbTree *t = new rbTree();
    srand(10);
    for(int i = 0; i < num; ++i){
        int tmp = random()%500;
        t->insert(tmp);
        preOrder(t->root(), t->nil);
        int ret = nodeCheck(t->root(), t->nil);
        assert(ret >= 0);
        cout<<"black height is "<<ret<<endl;
    }
}

void preOrder(Node *node, Node *nil){
    if(node == nil) return;
    cout<<node->val<<",";
    preOrder(node->lchild, nil);
    preOrder(node->rchild, nil);
}



