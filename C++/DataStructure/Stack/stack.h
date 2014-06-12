#ifndef STACK
#define STACK

#ifndef LINK
#define LINK

// Link class for linked list
template<typename E>
class Link{
public:
	Link<E>* next;
	E element;

	Link(E value, Link<E>* next = NULL){
		this->element = value;
		this->next = next;
	}

	Link(){
		this->next = NULL;
	}

};

#endif

#include <iostream>
using namespace std;

// Stack base class
template<typename E>
class Stack{
public:
	Stack(){}

	virtual ~Stack(){};

	virtual void clear() = 0;

	virtual void push(const E& value) = 0;

	virtual E pop() = 0;

	virtual int length() const = 0;

	virtual const E& topValue() const = 0;

	virtual void print() const = 0;

};

//Array stack with a maxsize
template<typename E>
class AStack : public Stack<E>{
private:
	E* alist;
	int depth;
	int count;
public:

	AStack(int maxsize){
		depth = maxsize;
		count = 0;
		alist = new E[maxsize];
	}

	~AStack(){

	}

	void push(const E& value){
		if (count < depth){
			alist[count] = value;
			count++;
		}
		else{
			// Assert
		}
	}

	E pop(){
		if (count > 0){
			count--;
			return alist[count];
		}
		else{
			// Assert
		}
	}

	void clear(){
		count = 0;
	}

	const E& topValue() const{
		return alist[count];
	}

	int length() const{
		return count;
	}

	void print() const{
		for (int i = count - 1; i >= 0; i--){
			cout << alist[i] << " ";
		}
		cout << endl;
	}
};

// Linked Stack
template<typename E>
class LStack : public Stack<E>{
private:
	Link<E>* top;
	int count;
public:
	LStack(){
		top = new Link<E>();
	}

	~LStack(){
		clear();
	}

	void clear(){
		count = 0;
		while (top->next != NULL){
			Link<E>* temp = top->next;
			top->next = temp->next; // temp can be substituted by last sentence;
			delete temp;
		}
	}

	void push(const E& value){
		top->next = new Link<E>(value, top->next);
		count++;
	}

	E pop(){
		if (count != 0){
			count--;
			Link<E>* temp = top->next;
			E tempE = temp->element;
			top->next = temp->next; // temp can be substituted by last sentence;
			delete temp;
			return tempE;
		}
	}

	int length() const{
		return count;
	}

	const E& topValue() const{
		return top->element;
	}

	void print() const{
		Link<E>* temp = top;
		while (temp->next != NULL){
			cout << temp->next->element << " ";
			temp = temp->next;
		}
		cout << endl;
	}

};

#endif