#ifndef AQUEUE
#define AQUEUE
#include "quene.h"
#include <iostream>

using namespace std;

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
		delete [] element;
	}

	void clear(){
		rear = 0;
		front = 1;
	}

	void enqueue(const E& value){
		if((rear + 2) % maxSize == front){
			cout << "queue is full" << endl;
		}else{
			rear = (rear + 1) % maxSize;
			element[rear] = value;
		}
	}

	E dequeue(){
		if(getLength() == 0){
			cout << "queue is empty" << endl;
			return NULL;
		}else{
			E temp = element[front];
			front = (front + 1) % maxSize;
			return temp;
		}
	}

	int getLength(){
		return ((rear - front + 1) % maxSize);
	}

	const E& frontValue() const{
		if(getLength() != 0){
			return element[front];
		}else{
			cout << "queue is empty" << endl;
		}
	}
};

#endif