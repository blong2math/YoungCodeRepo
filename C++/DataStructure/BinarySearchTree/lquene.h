#ifndef LQUEUE
#define LQUEUE

#include "quene.h"
#include "llist.h"

template<typename E>
class LQueue : public Queue<E>{
private:
	LList<E> llist;
	int length;

public:
	LQueue(){
		llist = LList<E>();
		length = 0;
	}

	~LQueue() {
		clear();
	}

	void print(){
		llist.print();
	}

	void clear(){
		llist.clear();
		length = 0;
	}

	void enqueue(const E& value){
		llist.append(value);
		length++;
	}

	E dequeue(){
		E temp = llist.getValue();
		llist.remove();
		length--;
		return temp;
	}

	int getLength(){
		return length;
	}

	const E& frontValue() const{
		if (length != 0){
			return llist.getValue();
		}
		
	}
};

#endif