#include <assert.h>
#include <cstdlib>
#include <iostream>
#include "AVLtree.h"
#include "test.h"



int main(){
    AVLTree *tree = new AVLTree();
    srand(100);
    insertTest(tree, 50, 5000);
    removeTest(tree, 50, 5000);
    
}