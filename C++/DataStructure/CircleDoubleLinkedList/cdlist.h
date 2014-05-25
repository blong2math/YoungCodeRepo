#include "dlink.h"
#include "clist.h"
#include <iostream>

using namespace std;

template <typename E> class CDList : public CList<E> {
private:
	DLink<E>* curr;       // Access to current element
	int cnt;    	       // Size of list

	void init(){
		curr = NULL;
		cnt = 0;
	}

	void removeall(){
		for (int i = 0; i < cnt; i++){
			DLink<E>* temp = curr;
			this->next();
			delete temp;
		}
		cnt = 0;
	}

public:
	CDList() {
		init();
	}

	~CDList() {
		removeall();
	}

	void clear() {
		removeall();
		init();
	}

	void print() {
		if (curr != NULL){
			for (int i = 0; i < cnt; i++){
				cout << curr->element << '\t';
				this->next();
			}
			cout << endl;
		}
		else{
			cout << "no element in this daisy-chain" << endl;
		}
	};

	// Insert "it" at current position
	void insert(const E& it) {
		if (curr != NULL){
			curr->next = new DLink<E>(it, curr->next, curr);
			curr->next->next->prev = curr->next;
		}
		else{
			curr = new DLink<E>(it, NULL, NULL);
			curr->next = curr;
			curr->prev = curr;
		}
		cnt++;
	}

	// Remove and return current element
	E remove() {
		E tempele = curr->element;
		if (curr != NULL){
			DLink<E> *tempnext = curr->next;
			DLink<E> *temppre = curr->prev;
			temppre->next = tempnext;
			tempnext->prev = temppre;
			DLink<E> *tempcurr = curr;
			this->next();
			delete tempcurr;
			cnt--;
		}
		else{
			cout << "There is no element to remove" << endl;
		}
		return tempele;
	}

	// Move curr one step left; no change if already at front
	void prev() {
		curr = curr->prev;
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