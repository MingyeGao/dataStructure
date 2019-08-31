#include <iostream>
#include "test.h"
#include "RBTree.h"

int main(){
    RBTree *tree = new RBTree;
    srand(8);
    insertTest(tree, 500, 2000);
    removeTest(tree, 500, 2000);
}