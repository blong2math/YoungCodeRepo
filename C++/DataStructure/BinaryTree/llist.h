#include "link.h"
#include "list.h"
#include <iostream>

using namespace std;

template<typename E>
class LList : public List<E>{
private:
	int length;
	Link<E>* curr;
	Link<E>* head;
	Link<E>* tail;

public:
	LList() {
		head = curr = tail = new Link<E>();
		length = 0;
	}

	~LList() {
		clear();
	}

	void print(){
		Link<E>* temp = head;
		for (int i = 0; i < length; i++){
			cout << temp->next->value << "\t";
			temp = temp->next;
		}
		cout << endl;
	}

	void clear(){
		this->moveToStart();
		next();
		for (int i = 0; i < length; i++){
			Link<E>* temp = curr->next;
			delete curr;
			curr = temp;
		}
		length = 0;
		tail = head;
		curr = head;
	};

	void insert(const E& v){
		curr->next = new Link<E>(v, curr->next);
		length++;
	}

	void append(const E& v){
		Link<E>* temp = new Link<E>(v);
		tail->next = temp;
		tail = temp;
		length++;
	}

	E remove(){
		if (length > 1){
			Link<E>* temp = curr->next;
			curr->next = temp->next;
			E tempE = temp->value;
			delete temp;
			length--;
			return tempE;
		}
		else if(length = 1){
			E temp = head->next->value;
			clear();
			length = 0;
			return temp;
		}
		else{
			//Assert
		}
	}

	void moveToStart(){
		curr = head;
	}

	void moveToEnd(){
		curr = tail;
	}

	void prev(){
		if (curr != head){
			int pos = this->getCurrPos();
			for (int i = 0; i < pos - 1; i++){
				next();
			}
		}
	}

	void next(){
		if (curr->next != NULL){
			curr = curr->next;
		}
	}

	int getCurrPos() const{
		int i;
		Link<E>* search = head;
		for (i = 0; search->next != curr->next; i++){
			search = search->next;
		}
		return i;
	}

	void moveToPos(int pos){
		for (int i = 0; i < pos; i++){
			curr = curr->next;
		}
	}

	int getLength() const{
		return length;
	}

	const E& getValue() const{
		if (curr->next != NULL){
			return curr->next->value;
		}
	}
};