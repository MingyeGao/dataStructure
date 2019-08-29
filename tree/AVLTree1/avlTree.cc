///* finished
///* 

#include <assert.h>
#include <time.h>

#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <initializer_list>

using namespace std;

class Node {
public:
	Node() {};
	Node(int x) :val(x), bf(0), lchild(nullptr), rchild(nullptr) {};
	int val;
	int bf;
	Node *lchild;
	Node *rchild;
};

class avlTree {
public:
	Node *root;
	avlTree() {};
	bool insert(int x);
	bool remove(int x);
};

void leftRotate(Node **node) {
	Node *r = (*node)->rchild;
	(*node)->rchild = r->lchild;
	r->lchild = *node;
	*node = r;
}

void rightRotate(Node **node) {
	Node *l = (*node)->lchild;
	(*node)->lchild = l->rchild;
	l->rchild = *node;
	*node = l;
}

void leftBalance(Node **node) {
	Node *r = (*node)->rchild;
	if (r->bf == -1) {
		(*node)->bf = 0;
		r->bf = 0;
		leftRotate(node);

	}
	else {
		Node *rl = r->lchild;

		if (rl->bf == -1) {
			(*node)->bf = 1;
			rl->bf = 0;
			r->bf = 0;
		}
		else if (rl->bf == 1) {
			(*node)->bf = 0;
			r->bf = -1;
			rl->bf = 0;
		}
		else {
			(*node)->bf = 0;
			r->bf = 0;
			rl->bf = 0;
		}

		rightRotate(&(*node)->rchild);
		leftRotate(node);
	}
}

void rightBalance(Node **node) {
	Node *l = (*node)->lchild;
	if (l->bf == 1) {

		l->bf = 0;
		(*node)->bf = 0;
		rightRotate(node);
	}
	else {
		Node *lr = l->rchild;

		if (lr->bf == 1) {
			lr->bf = 0;
			(*node)->bf = -1;
			l->bf = 0;
		}
		else if (lr->bf == -1) {
			lr->bf = 0;
			(*node)->bf = 0;
			l->bf = 1;
		}
		else {
			lr->bf = 0;
			(*node)->bf = 0;
			l->bf = 0;
		}
		leftRotate(&(*node)->lchild);
		rightRotate(node);
	}
}

bool nodeInsert(Node **root, int x) {
	if (*root == nullptr) {
		*root = new Node(x);
		return true;
	}

	if ((*root)->val == x) {
		return false;
	}

	if (x > (*root)->val) {
		bool result = nodeInsert(&(*root)->rchild, x);
		if (result == true) {
			(*root)->bf--;
			if ((*root)->bf == -2) {
				leftBalance(root);
				return false;
			}
			else if ((*root)->bf == -1) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
	else {
		bool result = nodeInsert(&(*root)->lchild, x);
		if (result == true) {
			(*root)->bf++;
			if ((*root)->bf == 2) {
				rightBalance(root);
				return false;
			}
			else if ((*root)->bf == 1) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}

	assert(0);


}


bool nodeRemove(Node **root, int x) {
	if ((*root) == nullptr) return false;

	if ((*root)->val == x) {
		if ((*root)->lchild == nullptr && (*root)->rchild == nullptr) {
			(*root) = nullptr;
			return true;
		}
		if ((*root)->lchild == nullptr) {
			Node *toDelete = (*root);
			(*root) = (*root)->rchild;
			delete toDelete;
			return true;
		}
		if ((*root)->rchild == nullptr) {
			Node *toDelete = (*root);
			(*root) = (*root)->lchild;
			delete toDelete;
			return true;
		}
		//*��ɾ���ڵ������ӽڵ�����ڣ��Һ��
		Node *r = (*root)->rchild;
		Node *rl = r->lchild;
		if (rl == nullptr) {
			(*root)->rchild = r->rchild;
			(*root)->bf++;
			(*root)->val = r->val;
			delete r;
			
			if ((*root)->bf == 2) {
				Node *l = (*root)->lchild;
				if (l->bf != 0) {
					rightBalance(root);
					return true;
				}
				else {
					(*root)->bf = 1;
					l->bf = -1;
					rightRotate(root);
					return false;
				}
			}
			else if((*root)->bf == 1){
				return false;
			}
			else {//* (*root)->bf == 0
				return true;
			}
		}

		Node *prev = r;
		Node *current = rl;
		while (current->lchild != nullptr) {
			prev = current;
			current = current->lchild;
		}

		Node *prevRootPointer = *root;
		int val = current->val;
		bool ret = nodeRemove(root, current->val);
		prevRootPointer->val = val;
		return ret;
	}
	if ((*root)->val > x) {
		bool ret = nodeRemove(&(*root)->lchild, x);
		if (ret == false) return false;
		else {
			(*root)->bf--;
			if ((*root)->bf == 0) {
				return true;
			}
			else if ((*root)->bf == -1) {
				return false;
			}
			else {//(*root)->bf == -2
				Node *r = (*root)->rchild;
				if (r->bf == 0) {
					(*root)->bf = -1;
					r->bf = 1;
					leftRotate(root);
					return false;

				}
				else {
					leftBalance(root);
					return true;
				}
			}
		}
	}
	else {// (*root)->val < x
		bool ret = nodeRemove(&(*root)->rchild, x);
		if (ret == false) return false;
		else {
			(*root)->bf++;
			if ((*root)->bf == 0) {
				return true;
			}
			else if ((*root)->bf == 1) {
				return false;
			}
			else {
				Node *l = (*root)->lchild;
				if (l->bf == 0) {
					(*root)->bf = 1;
					l->bf = -1;
					rightRotate(root);
					return false;
				}
				else {
					rightBalance(root);
					return true;
				}
			}
		}
	}

	assert(0);
}

bool avlTree::insert(int x) {
	return nodeInsert(&root, x);
}


bool avlTree::remove(int x) {
	return nodeRemove(&root, x);
}

/*
* @param root: ���ڵ�
* @return : ���root��avl�����������ĸ߶ȣ�������ǣ��򷵻�-1��
*/
int isAvlTree(Node *root) {
	if (root == nullptr) return 0;

	if (root->lchild != nullptr && (root->val < root->lchild->val)) {
		return -1;
	}
	if (root->rchild != nullptr && (root->val > root->rchild->val)) {
		return -1;
	}

	int result1 = isAvlTree(root->lchild);
	int result2 = isAvlTree(root->rchild);

	if (result1 == -1 || result2 == -1) {
		return -1;
	}

	int result = result1 - result2;
	if (result != root->bf) {
		return -1;
	}

	if (result >= -1 && result <= 1) {
		return max(result1, result2) + 1;
	}
	else {
		return -1;
	}
}

void preOrder(Node *root) {
	if (root == nullptr) return;

	printf("%d(%d), ", root->val, root->bf);
	if (root->lchild != nullptr) {
		preOrder(root->lchild);
	}
	if (root->rchild != nullptr) {
		preOrder(root->rchild);
	}
}

int main() {
	avlTree *tree = new avlTree();
	srand(time(0));
	int testNum = 5000;

	vector<int> input;

	for (int i = 0; i < testNum; ++i) {
		int tmp = rand();
		tree->insert(tmp);
		input.push_back(tmp);
		int ret = isAvlTree(tree->root);
		assert(ret > 0);
	}

	int ret = isAvlTree(tree->root);
	assert(ret > 0);



	for (int i = testNum-1; i >=0; --i) {
		tree->remove(input[i]);
		ret = isAvlTree(tree->root);
		assert(ret >= 0);
	}

	//getchar();
}