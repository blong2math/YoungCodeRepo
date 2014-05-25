#ifndef BNODE
#define BNODE

#include <iostream>
#include "lstack.h"
#include "lquene.h"

using namespace std;

template<typename E>
class BinNode{
private:
	BinNode<E>* rc;
	BinNode<E>* lc;
	E it;

public:
	virtual ~BinNode(){};

	virtual E& element() = 0;

	virtual void setElement(const E&) = 0;

	virtual BinNode* left() const = 0;

	virtual void setLeft(BinNode*) = 0;

	virtual BinNode* right() const = 0;

	virtual void setRight(BinNode*) = 0;
	
	virtual bool isLeaf() = 0;

};


// with recursion
template<typename E>
void preorder(BinNode<E>* root){
	visit(root);
	if (root->left() != NULL){
		preorder(root->left());
	}
	if (root->right() != NULL){
		preorder(root->right());
	}
}

template<typename E>
void inorder(BinNode<E>* root){
	if (root->left() != NULL){
		inorder(root->left());
	}
	visit(root);
	if (root->right() != NULL){
		inorder(root->right());
	}
}

template<typename E>
void postorder(BinNode<E>* root){
	if (root->left() != NULL){
		postorder(root->left());
	}
	if (root->right() != NULL){
		postorder(root->right());
	}
	visit(root);
}

//Without recursion
template<typename E>
void preorder_iter(BinNode<E>* root){
	LStack<BinNode<E>*> s = LStack<BinNode<E>*>();
	BinNode<E>* temp = root;
	bool ctn = true;
	while (ctn){
		if (temp->right() != NULL){
			s.push(temp->right());
		}
		visit(temp);
		if (temp->left() != NULL){
			temp = temp->left();
		}
		else{
			if (s.length() == 0){
				ctn = false;
			}
			temp = s.pop();
		}
	}
}


template<typename E>
void inorder_iter(BinNode<E>* root){
	LStack<BinNode<E>*> s = LStack<BinNode<E>*>();
	while (root != NULL || s.length() != 0){
		while (root != NULL)
		{
			s.push(root);
			root = root->left();
		}
		if (s.length() != 0) {
			root = s.pop();
			visit(root);
			root = root->right();
		}
	}
}

template<typename E>
void postorder_iter(BinNode<E>* root){
	LStack<BinNode<E>*> s_disp = LStack<BinNode<E>*>();
	LStack<BinNode<E>*> s_temp = LStack<BinNode<E>*>();
	BinNode<E>* temp = root;
	bool ctn = true;
	while (ctn){
		if (temp != NULL){
			s_disp.push(temp);
		}
		if (temp->left() != NULL){
			s_temp.push(temp->left());
		}
		if (temp->right() != NULL){
			temp = temp->right();
		}
		else{
			if (s_temp.length() != 0){
				temp = s_temp.pop();
			}
			else{
				ctn = false;
			}
		}
	}
	while (s_disp.length() != 0){
		BinNode<E>* temp = s_disp.pop();
		cout << temp->element() << endl;
	}
}

template<typename E>
void updownorder(BinNode<E>* root){
	LQueue<BinNode<E>*> l = LQueue<BinNode<E>*>();
	BinNode<E>* temp = root;
	bool cnt = true;
	while (cnt){
		visit(temp);
		if (temp->left() != NULL){
			l.enqueue(temp->left());
		}
		if (temp->right() != NULL){
			l.enqueue(temp->right());
		}
		if (l.getLength() != 0){
			temp = l.dequeue();
		}
		else{
			cnt = false;
		}
	}
}

template<typename E>
void visit(BinNode<E>* node){
	cout << node->element() << endl;
}

int frac(int i){
	if (i > 0){
		return frac(i - 1);
	}
	else{
		return 1;
	}
}

#endif