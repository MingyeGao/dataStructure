#ifndef TEST_H
#define TEST_H

#include <iostream>
#include "RBTree.h"


int isRBTree(RBNode *node);

void preOrder(RBNode *node);

void insertTest(RBTree *tree, int range, int num);

void removeTest(RBTree *tree, int range, int num);

#endif//TEST_H