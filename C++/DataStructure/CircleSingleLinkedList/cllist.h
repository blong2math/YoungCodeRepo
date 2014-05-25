#include "clist.h"
#include "link.h"
#include <iostream>

using namespace std;

template <typename E> class CLList : public CList<E> {
private:
	Link<E>* curr;       // Access to current element
	int cnt;    	       // Size of list

	void init(){
		curr = NULL;
		cnt = 0;
	}

	void removeall(){
		for (int i = 0; i < cnt; i++){
			Link<E>* temp = curr;
			curr = curr->next;
			delete temp;
		}
		cnt = 0;
	}

public:
	CLList() {
		init();
	}

	~CLList() {
		removeall();
	}

	void print() {
		if (curr != NULL){
			for (int i = 0; i < cnt; i++){
				cout << curr->element << '\n';
				this->next();
			}
			cout << endl;
		}
		else{
			cout << "no element in this daisy-chain" << endl;
		}
	};

	void clear() {
		removeall(); 
		init();
	}

	// Insert "it" at current position
	void insert(const E& it) {
		if (curr != NULL){
			curr->next = new Link<E>(it, curr->next);
		}
		else{
			curr = new Link<E>(it, NULL);
			curr->next = curr;
		}
		cnt++;
	}

	// Remove and return current element
	E remove() {
		E tempele = curr->element;
		if (curr != NULL){
			Link<E>* temp = curr;
			this->next();
			delete temp;
			cnt--;
			temp = curr;
			this->prev();
			curr->next = temp;
		}
		return tempele;
	}

	// Move curr one step left; no change if already at front
	void prev() {
		for (int i = 1; i < cnt; i++){
			curr = curr->next;
		}
	}

	// Move curr one step right; no change if already at end
	void next(){
		curr = curr->next;
	}

	int length() const  {
		return cnt; 
	}

	const E& getValue() const { // Return current element
		if (curr != NULL){
			return curr->element;
		}
		else{
			return NULL;
		}
	}
};