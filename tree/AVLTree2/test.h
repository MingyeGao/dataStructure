#ifndef TEST_H
#define TEST_H

#include "AVLtree.h"

int isAVLTree(AVLTreeNode *node);

void preOrder(AVLTreeNode *node);

void insertTest(AVLTree *tree, int range, int num);

void removeTest(AVLTree *tree, int range, int num);

#endif