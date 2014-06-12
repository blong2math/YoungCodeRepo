#ifndef QUEUE
#define QUEUE

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

// Base queue class
template<typename E>
class Queue{
public:
	Queue(){}

	virtual ~Queue(){}

	virtual void clear() = 0;

	virtual void enqueue(const E& value) = 0;

	virtual E dequeue() = 0;

	virtual int length() = 0;

	virtual const E& frontValue() const = 0;

	virtual void print() const = 0;
};

// Linked list queue
template<typename E>
class LQueue : public Queue<E>{
private:
	Link<E>* head;
	Link<E>* tail;
	int count;

public:
	LQueue(){
		head = tail = new Link<E>();
		count = 0;
	}

	~LQueue() {
		clear();
	}

	void print() const{
		Link<E>* temp = head;
		while (temp->next != NULL){
			cout << temp->next->element << " ";
			temp = temp->next;
		}
		cout << endl;
	}

	void clear(){
		count = 0;
		Link<E>* temp = head;
		while (temp->next != NULL){
			Link<E>* del = temp->next;
			temp->next = del->next;
			delete del;
		}
	}

	void enqueue(const E& value){
		count++;
		tail->next = new Link<E>(value, NULL);
		tail = tail->next;
	}

	E dequeue(){
		if (count > 0){
			count--;
			if (count == 1){
				delete tail;
				head->next = NULL;
				tail = head;
			}
			else{
				Link<E>* temp = head->next;
				E tempE = temp->element;
				head->next = temp->next;
				delete temp;
				return tempE;
			}
		}
	}

	int length(){
		return count;
	}

	const E& frontValue() const{
		if (count != 0){
			return head->next->element;
		}
		else{
			// Assert
		}
	}
};

// Array queue
template <typename E>
class AQueue : public Queue<E>{
private:
	E* element;
	int rear;
	int front;
	int maxSize;

public:
	AQueue(int maxsize){
		rear = 0;
		front = 1;
		maxSize = maxsize + 1;
		element = new E[maxSize];
	}

	~AQueue(){
		delete[] element;
	}

	void clear(){
		rear = 0;
		front = 1;
	}

	void enqueue(const E& value){
		if ((rear + 2) % maxSize == front){
			cout << "queue is full" << endl;
		}
		else{
			rear = (rear + 1) % maxSize;
			element[rear] = value;
		}
	}

	E dequeue(){
		if (length() == 0){
			cout << "queue is empty" << endl;
			return NULL;
		}
		else{
			E temp = element[front];
			front = (front + 1) % maxSize;
			return temp;
		}
	}

	int length(){
		return ((rear - front + maxSize + 1) % maxSize);
	}

	const E& frontValue() const{
		if (((rear - front + maxSize + 1) % maxSize) != 0){
			return element[front];
		}
		else{
			cout << "queue is empty" << endl;
		}
	}

	void print() const{
		for (int i = front; i <= front + ((rear - front + maxSize + 1) % maxSize) - 1; i++){
			cout << element[i % maxSize] << " ";
		}
		cout << endl;
	}
};

#endif