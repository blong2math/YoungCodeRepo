#include "BSTNode.h"
#include <iostream>

using namespace std;

template<typename Key, typename E>
class BST{
private:
	BSTNode<Key, E>* root;
	int nodeCount;

	// this is some helpers frequently used
	void clearhelp(BSTNode<Key, E>* rt){
		if (root == NULL){
			return;
		}
		else{
			if (rt->left() != NULL){
				clearhelp(rt->left());
			}
			if (rt->right() != NULL){
				clearhelp(rt->right());
			}
			delete rt;
		}
	}

	BSTNode<Key, E>* inserthelp(BSTNode<Key, E>* rt, const Key& k, const E& e){
		if (rt == NULL){
			return new BSTNode<Key, E>(k, e);
		}
		else{
			if (k < rt->key()){
				rt->setLeft(inserthelp(rt->left(), k, e));
			}
			else{
				rt->setRight(inserthelp(rt->right(), k, e));
			}
			return rt;
		}
	}

	E findhelp(BSTNode<Key, E>* rt, const Key& k){
		if (root == NULL){
			return NULL;
		}
		else{
			if (k < rt->key()){
				if (rt->left() != NULL){
					return findhelp(rt->left(), k);
				}
				else{
					if (rt->key() == k){
						return rt->element();
					}
					else{
						return NULL;
					}
				}
			}
			else if(k > rt->key()){
				if (rt->right() != NULL){
					return findhelp(rt->right(), k);
				}
				else{
					if (rt->key() == k){
						return rt->element();
					}
					else{
						return NULL;
					}
				}
			}
			else{
				return rt->element();
			}
		}
	}

	BSTNode<Key, E>* deletemin(BSTNode<Key, E>* rt){
		if (root == NULL){
			cout << "this is empty tree" << endl;
			return NULL;
		}
		else{
			if (rt->left() == NULL){
				return rt->right();
			}
			else{
				rt->setLeft(deletemin(rt->left()));
				return rt;
			}
		}
	}

	BSTNode<Key, E>* getmin(BSTNode<Key, E>* rt){
		if (root == NULL){
			return NULL;
		}
		else{
			if (rt->left() != NULL){
				return getmin(rt->left());
			}
			else{
				return rt;
			}
		}
	}

	void printhelp(BSTNode<Key, E>* rt){
		if (rt->left() != NULL){
			printhelp(rt->left());
		}
		cout << rt->element() << endl;
		if (rt->right() != NULL){
			printhelp(rt->right());
		}	
	}

	BSTNode<Key, E>* removehelp(BSTNode<Key, E>* rt, const Key& k){
		if (root == NULL){
			cout << "the value is not in this tree" << endl;
			return NULL;
		}
		else if(k < rt->key()){
			rt->setLeft(removehelp(rt -> left(), k));
		}
		else if (k > rt->key()){
			rt->setRight(removehelp(rt->right(), k));
		}
		else{
			BSTNode<Key, E>* temp = rt;
			if (rt->left() == NULL){
				rt = rt->right();
				delete temp;
			}
			else if(rt->right() == NULL){
				rt = rt->left();
				delete temp;
			}
			else{
				BSTNode<Key, E>* temp = getmin(rt->right());
				rt->setElement(temp->element());
				rt->setKey(temp->key());
				rt->setRight(deletemin(rt->right()));
				delete temp;
			}
		}
		return rt;
	}


public:
	void clear(){
		clearhelp(root);
		nodeCount = 0;
		root = NULL;
	}

	BST(){
		root = NULL;
		nodeCount = 0;
	}

	~BST(){
		clearhelp(root);
	}

	void print(){
		if (root == NULL){
			cout << "the tree is empty" << endl;
		}
		else{
			this->printhelp(root);
		}
	}

	E remove(const Key& k){
		E temp = findhelp(root, k);
		if (temp != NULL){
			root = removehelp(root, k);
			nodeCount--;
		}
		return temp;
	}

	E removert(){
		if (root != NULL){
			E temp = root->element();
			rt = removehelp(root, root->key());
			nodeCount--;
			return temp;
		}
		else{
			cout << "there is not rt in this tree" << endl;
			return NULL;
		}
	}

	int size(){
		return nodeCount;
	}

	E find(const Key& k){
		E temp = findhelp(root, k);
		if (temp == NULL){
			cout << "the value is not in this tree" << endl;
		}
		return temp;
	}

	void insert(const Key& k, const E& e){
		root = inserthelp(root, k, e);
		nodeCount++;
	}

};