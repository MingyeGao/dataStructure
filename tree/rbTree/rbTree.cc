#include <assert.h>

#include <cstdio>

using namespace std;

enum Color{black = 0, red};

class Node;


class Node{
public:
    Node(){};
    Node(int a, Node *nil):val(a), lchild(nil), rchild(nil), p(nil){}
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

Node *nil = new Node();

class rbTree{
public:
    rbTree(){
        nil = new Node();
    }
    Node *nil;
    ~rbTree(){
        delete nil;
    }
};

void leftRotate(Node **node){
    Node *nodeParent = (*node)->p;
    Node *r = (*node)->rchild;

    (*node)->rchild = r->lchild;
    r->lchild->p = (*node)->rchild;

    r->lchild = (*node);
    (*node)->p = r;

    (*node) = r;
    r->p = nodeParent;
}

void preOrder(Node *node, Node *nil){
    if(node == nil) return;
    printf("%d, ", node->val);
    preOrder(node->lchild, nil);
    preOrder(node->rchild, nil);
}

int main(int argc, char *argv[]){
    Node *node1 = new Node(1, nil);
    Node *node2 = new Node(2, nil);
    Node *node3 = new Node(3, nil);

    node1->setLchild(node2);
    node1->setRchild(node3);

    preOrder(node1, nil);
    printf("\n");
    leftRotate(&node1);
    preOrder(node1, nil);
}

